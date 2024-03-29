#ifndef __ACTIONS_H
#define __ACTIONS_H


void do_player_input(GameState& state, Player& p, const std::string& prompt, int limit = -1) {

    p.input.s.clear();
    p.input.limit = limit;
    state.render.do_message(prompt, true);
    p.state = Player::INPUTTING;
}

void do_player_wish(GameState& state, Player& p) {

    do_player_input(state, p, "Wish for what: >>> "_m);
}

void do_player_label(GameState& state, Player& p, int limit) {

    do_player_input(state, p, "Write what: >>> "_m, limit);
}

void move_player(const Player& p, GameState& state) {
        
    size_t nstack = state.items.stack_size(p.px, p.py);

    if (nstack == 1) {
        items::Item item;
        state.items.get(p.px, p.py, 0, item);
        const Design& d = designs().get(item.tag);

        state.render.do_message(nlp::message("You see %s."_m, nlp::count(), d, item.count));

    } else if (nstack > 1) {

        state.render.do_message(nlp::message("You see %d items here."_m, nstack));

    } else {
        features::Feature feat;
        if (state.features.get(p.px, p.py, feat)) {
            const Terrain& t = terrain().get(feat.tag);

            if (t.message.size() > 0) {

                std::string label = state.features.label(p.px, p.py);

                if (label.size() > 0) {
                    state.render.do_message(nlp::message("\"%s\""_m, label));

                } else {
                    state.render.do_message(nlp::message("\"%s\""_m, t.message));
                }

            } else if (t.name.size() > 0) {
                state.render.do_message(nlp::message("There is %s here."_m, t));
            }
        }
    }
}


bool run_away(Player& p, GameState& state, size_t n_skin);

void move(Player& p, GameState& state, int dx, int dy, size_t n_skin, bool do_fear = true) {

    if (do_fear && p.fear) {

        if (run_away(p, state, n_skin))
            return;
    }

    if (p.stun) {

        if (dx != 0 && state.rng.range(0, 2) == 0) {
            dx = -dx;
        }

        if (dy != 0 && state.rng.range(0, 2) == 0) {
            dy = -dy;
        }
    }

    int nx = p.px + dx;
    int ny = p.py + dy;

    if (nx < 0 || ny < 0) 
        return;

    const Species& pspecies = p.get_species();

    if (!state.neigh.linked(neighbors::pt(p.px, p.py), neighbors::pt(nx, ny)))
        return;

    if (pspecies.digging > 0 && !state.grid.is_walk(nx, ny)) {

        if (!digging_step(state, nx, ny, pspecies.digging)) {
            state.render.do_message("You remove some of the rock."_m);
            return;
        }
    }

    switch (pspecies.move) {

    case Species::move_t::floor:
        if (!state.grid.is_floor(nx, ny)) return;
        break;
                
    case Species::move_t::water:
        if (!state.grid.is_water(nx, ny)) return;
        break;

    case Species::move_t::corner:
        if (!state.grid.is_corner(nx, ny)) return;
        break;

    case Species::move_t::shoreline:
        if (!state.grid.is_shore(nx, ny)) return;
        break;
            
    default:
        if (!state.grid.is_walk(nx, ny)) return;
        break;
    }

    monsters::Monster& mon = state.monsters.get(nx, ny);

    if (!mon.null()) {

        if (!mon.ally.null())
            return;

        damage::attacks_t attacks;
        p.get_attack(attacks);

        if (attack_from_player(p, attacks, p.get_computed_level(), state, monsters::pt(nx, ny), mon, false)) {
            ++(state.ticks);
        }

        return;
    }

    bool terrain_immune = pspecies.flags.terrain_immune;


    features::Feature feat;
    if (!terrain_immune && state.features.get(nx, ny, feat)) {

        const Terrain& t = terrain().get(feat.tag);

        if (t.uncharge.bump) {
            state.features.uncharge(nx, ny, state.render);
            ++(state.ticks);
            return;
        }

        if (t.sensor_toggle.size() > 0) {

            if (t.uncharge.sensor) {
                state.features.uncharge(nx, ny, state.render);
            }
            
            for (const auto& nn : state.neigh(neighbors::pt(nx, ny))) {

                unsigned int nnx = nx + nn.first;
                unsigned int nny = ny + nn.second;

                features::Feature feat2;
                if (state.features.get(nnx, nny, feat2)) {

                    const auto& tmp = t.sensor_toggle.find(feat2.tag);

                    if (tmp != t.sensor_toggle.end()) {
                        state.features.set(nnx, nny, tmp->second, state.render);
                    }
                }
            }
        }

        if (t.walkblock)
            return;
    }

    /*
    if (state.render.is_walkblock(nx, ny)) {
        return;
    }
    */

    if (p.fast.turns > 0 && (p.fast.turns % p.fast.slice) == 0) {
        --(p.fast.turns);

    } else {
        ++(state.ticks);
    }

    if (!terrain_immune && state.features.get(p.px, p.py, feat)) {

        const Terrain& t = terrain().get(feat.tag);

        if (t.sticky) {
            state.render.do_message("You are stuck!"_m);

            if (t.uncharge.move) {
                state.features.uncharge(p.px, p.py, state.render);
            }

            return;
        }
    }

    state.render.invalidate(p.px, p.py);

    p.px = nx;
    p.py = ny;

    state.render.invalidate(p.px, p.py);

    move_player(p, state);
}


bool run_away(Player& p, GameState& state, size_t n_skin) {

    unsigned int radius = get_lightradius(p, state);

    std::unordered_set<neighbors::pt> ns;

    radial_points(p.px, p.py, state, radius, ns, player_walkable);

    state.monsters.find_nearest(state.grid.w, state.grid.h, p.px, p.py);

    std::unordered_set<neighbors::pt> ms;

    bool full_empty;
    auto nearest = state.monsters.nearest.get(p.px, p.py, radius * radius, full_empty);

    for (const auto& i : nearest) {

        if (!state.render.is_in_fov(i.x, i.y))
            continue;

        ms.insert(neighbors::pt(i.x, i.y));
    }

    if (ms.empty()) {
        return false;
    }

    while (!ns.empty()) {

        double maxd = 0.0;
        neighbors::pt maxn;

        for (const auto& z : ns) {

            double thisd = 0.0;

            for (const auto& i : ms) {
                double dist = distance(z.first, z.second, i.first, i.second);

                thisd += dist;
            }

            if (thisd > maxd) {
                maxd = thisd;
                maxn = z;
            }
        }

        if (maxd == 0.0) {
            return false;
        }

        unsigned int nnx;
        unsigned int nny;

        bool found = path_walk(state, p.px, p.py, maxn.first, maxn.second, 1, radius, 
                               [&state](unsigned int a, unsigned int b, unsigned int c, unsigned int d) {
                                   return (player_walkable(state, c, d) ? 1.0f : 0.0f);
                               },
                               nnx, nny);

        if (found) {

            move(p, state, nnx - p.px, nny - p.py, n_skin, false);
            return true;

        } else {
            ns.erase(maxn);
        }
    }

    return false;
}

std::string tombstone_text(const Player& p) {

    bones::bone_t bone;

    if (!bones::bones().get(p, bone)) {

        return "\n\nHm, this tombstone is blank..."_m;
    }

    if (bone.name.name.empty())
        bone.name.name = "anonymous"_m;

    if (bone.cause.name.empty())
        bone.cause.name = "unnatural causes"_m;

    return nlp::message("tombstone_text_placeholder"_m,
                        bone.name,
                        bone.level+1, 
                        bone.cause, 
                        std::max(bone.worth, 0.0));
}

void take_followers(Player& p, GameState& state) {

    neighbors::pt pxy(p.px, p.py);

    for (const auto& xy_ : state.neigh(pxy)) {

        auto xy = state.neigh.mk(xy_, pxy);

        state.monsters.take(xy.first, xy.second, [](const monsters::Monster& m) { return !m.ally.null(); },
                            p.followers);
    }
}

void use_terrain(Player& p, GameState& state, bool& regen, bool& done, bool& dead) {

    features::Feature feat;
    if (!state.features.get(p.px, p.py, feat)) {
        state.render.do_message("There is nothing here to use."_m);
        return;
    }

    bool wished = false;

    const Terrain& t = terrain().get(feat.tag);

    if (t.wishing) {

        bool ok = false;

        if (p.state & Player::TERRAIN_STEP2) {

            bool special = (t.wishing == Terrain::SPECIAL_WISH);

            ok = (special ? 
                  special_wish(state, p, p.input.s) :
                  simple_wish(state, p, p.input.s));

            p.state &= ~(Player::TERRAIN_STEP2);
        }

        if (ok) {

            ++(state.ticks);
            wished = true;

        } else {

            do_player_wish(state, p);
            p.state |= Player::TERRAIN_STEP2;
            return;
        }
    }

    if (t.uncharge.use) {
        state.features.uncharge(p.px, p.py, state.render);
    }

    for (const auto& v : t.inc_stat) {

        if (v.val != 0) {

            if (p.stats.sinc(v.stat, v.val))
                p.dead = true;

            if (v.msg.size() > 0)
                state.render.do_message(v.msg);
        }
    }

    if (wished)
        return;

    if (!t.victory_item.null()) {

        const Design& d_victory = designs().get(t.victory_item);

        items::Item vi;

        if (p.inv.take(d_victory.slot, vi)) {

            state.render.do_message("Congratulations! (press space to close window)"_m, true);
            state.render.do_message(" ~*~   You win the game!   ~*~ "_m, true);

            // HACK!
            p.attacker = "VICTORY";
            done = true;
            dead = true;

            return;
        }
    }

    if (feat.tag == constants().grave || feat.tag == constants().bad_grave) {

        state.push_window(tombstone_text(p), screens_t::tombstone);
        return;
    }

    if (t.banking.sell_margin > 0 || t.banking.stat_bonus > 0) {

        state.push_window(show_banking_menu(p, state, feat.tag, t.banking), screens_t::bank_main);
        return;
    }

    if (t.stairs != 0) {

        if (t.stairs > 0) {
            state.render.do_message("You climb down the hole."_m);
        } else {
            state.render.do_message("You are magically teleported!"_m);
        }

        p.worldz += t.stairs;

        if (t.stairs > 0) {
            take_followers(p, state);
        }

        ++(state.ticks);
        regen = true;
        return;
    }

    if (t.tunnel_x != 0 || t.tunnel_y != 0) {

        state.render.do_message("You climb into the tunnel."_m);
        p.worldx += t.tunnel_x;
        p.worldy += t.tunnel_y;

        if (p.worldx > 1) p.worldx = -1;
        else if (p.worldx < -1) p.worldx = 1;

        if (p.worldy > 1) p.worldy = -1;
        else if (p.worldy < -1) p.worldy = 1;

        take_followers(p, state);

        ++(state.ticks);
        regen = true;
        return;
    }

    if (t.grant_spell.timeout > 0) {

        const auto& sp = t.grant_spell;
        double v = p.stats.gets(sp.stat);

        if (v >= sp.stat_min && v <= sp.stat_max) {

            for (const auto& i : p.spells) {
                if (i.name == sp.name) {
                    state.render.do_message("Nothing happens."_m);
                    return;
                }
            }

            p.spells.push_back(sp);
            state.render.do_message(nlp::message("You are granted the power of %s."_m, sp.name), true);

        } else {
            state.render.do_message("You want nothing to do with this vile thing."_m);
        }

        return;
    }

    if (t.crafting.size() > 0) {

        for (const auto& c : t.crafting) {

            const Design& cfrom = designs().get(c.from);
            const Design& cto = designs().get(c.to);

            items::Item vi;
            items::Item tmp;

            if (p.inv.take(cfrom.slot, vi)) {

                if (vi.tag != c.from) {
                    p.inv.place(cfrom.slot, vi, tmp);
                    continue;
                }

                vi = state.items.make_item(c.to, items::pt(p.px, p.py), state.rng);

                bool leftover = p.inv.place(cto.slot, vi, tmp);

                ++(state.ticks);

                if (leftover && tmp.tag == c.to) {

                    state.render.do_message("Nothing happens..."_m);

                } else {

                    state.render.do_message(nlp::message(c.msg, nlp::count(), cto, vi.count), true);

                    if (leftover) {
                        state.items.place(p.px, p.py, tmp, state.render);
                    }
                }

                return;
            }
        }

        state.render.do_message(nlp::message("You need a specific kind of item for %s."_m, t));
        return;
    }

    state.render.do_message("There is nothing here to use."_m);
}

void rest(GameState& state) {
    ++(state.ticks);
}

void seed_celauto(GameState& state, 
                  unsigned int _x, unsigned int _y, tag_t tag) {

    const CelAuto& ca = celautos().get(tag);

    for (const auto& dxy : ca.seed) {

        int x = _x + dxy.first;
        int y = _y + dxy.second;

        if (x < 0 || y < 0 || x > (int)state.neigh.w || y > (int)state.neigh.h)
            continue;

        state.camap.seed(state.neigh, celauto::pt(x, y), tag);
    }
}

void cast_random_spell(const Player& p, uint32_t rs, GameState& state) {

    tag_t catag = celautos().get_n(rs >> 16);

    int offx = -3 + (rs & 0x3);
    int offy = -3 + ((rs >> 2) & 0x3);

    for (size_t z = 0; z < 16; ++z) {

        if (rs & (1 << (16+z))) {

            int _x = offx + p.px + (z % 4);
            int _y = offy + p.py + (z / 4);

            if (_x < 0 || _y < 0 || _x > (int)state.neigh.w || _y > (int)state.neigh.h)
                continue;

            state.camap.seed(state.neigh, celauto::pt(_x, _y), catag);
        }
    }
}

#endif
