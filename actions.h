#ifndef __ACTIONS_H
#define __ACTIONS_H


void do_player_input(GameState& state, Player& p, const std::string& prompt) {

    p.input.s.clear();
    state.render.do_message(prompt, true);
    p.state = Player::INPUTTING;
}

void do_player_wish(GameState& state, Player& p, bool special) {

    do_player_input(state, p, "Wish for what: >>> ");
    p.state |= Player::WISHING;

    if (special) {
        p.state |= Player::SPECIAL_WISH;
    }
}

void move_player(const Player& p, GameState& state) {
        
    size_t nstack = state.items.stack_size(p.px, p.py);

    if (nstack == 1) {
        items::Item item;
        state.items.get(p.px, p.py, 0, item);
        const Design& d = designs().get(item.tag);

        state.render.do_message(nlp::message("You see %s.", nlp::count(), d, item.count));

    } else if (nstack > 1) {

        state.render.do_message(nlp::message("You see %d items here.", nstack));

    } else {
        features::Feature feat;
        if (state.features.get(p.px, p.py, feat)) {
            const Terrain& t = terrain().get(feat.tag);

            if (t.name.size() > 0) {
                state.render.do_message(nlp::message("There is %s here.", t));
            }
        }
    }
}

void move(Player& p, GameState& state, int dx, int dy, size_t n_skin) {
    int nx = p.px + dx;
    int ny = p.py + dy;

    if (nx < 0 || ny < 0) 
        return;

    tag_t poly = p.polymorph_species;

    if (!state.neigh.linked(neighbors::pt(p.px, p.py), neighbors::pt(nx, ny)) ||
        !state.grid.is_walk(nx, ny))
        return;

    if (!poly.null()) {

        const Species& s = species().get(poly);

        switch (s.move) {

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
            break;
        }
    }

    monsters::Monster mon;
    if (state.monsters.get(nx, ny, mon)) {

        damage::attacks_t attacks;
        p.get_attack(attacks);

        if (attack_from_player(p, attacks, p.get_computed_level(state.rng), state, mon, false)) {
            ++(state.ticks);
        }

        return;
    }

    bool terrain_immune = false;

    if (!poly.null()) {

        terrain_immune = species().get(poly).flags.terrain_immune;
    }


    features::Feature feat;
    if (!terrain_immune && state.features.get(nx, ny, feat)) {

        const Terrain& t = terrain().get(feat.tag);

        if (t.uncharge.bump) {
            state.features.uncharge(nx, ny, state.render);
            ++(state.ticks);
            return;
        }

        if (!t.sensor_toggle.first.null()) {
            
            for (const auto& nn : state.neigh(neighbors::pt(nx, ny))) {

                unsigned int nnx = nn.first;
                unsigned int nny = nn.second;

                features::Feature feat2;
                if (state.features.get(nnx, nny, feat2)) {

                    if (feat2.tag == t.sensor_toggle.first) {
                        state.features.set(nnx, nny, t.sensor_toggle.second, state.render);

                    } else if (feat2.tag == t.sensor_toggle.second) {
                        state.features.set(nnx, nny, t.sensor_toggle.first, state.render);
                    }
                }
            }
        }
    }

    if (state.render.is_walkblock(nx, ny)) {
        return;
    }

    ++(state.ticks);

    if (!terrain_immune && state.features.get(p.px, p.py, feat)) {

        const Terrain& t = terrain().get(feat.tag);

        if (t.sticky) {
            state.render.do_message("You are stuck!");

            if (t.uncharge.move) {
                state.features.uncharge(p.px, p.py, state.render);
            }

            return;
        }
    }

    //state.render.unset_skin(p.px, p.py, 5);
    state.render.invalidate(p.px, p.py);

    p.px = nx;
    p.py = ny;

    //state.render.set_skin(p.px, p.py, 5, constants().player_skin[n_skin]);
    state.render.invalidate(p.px, p.py);

    move_player(p, state);
}

void run_away(Player& p, GameState& state, size_t n_skin) {

    std::vector< std::pair<int, int> > ns;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {

            unsigned int nx = p.px + dx;
            unsigned int ny = p.py + dy;

            if (!state.neigh.linked(neighbors::pt(p.px, p.py), neighbors::pt(nx, ny)) ||
                !state.grid.is_walk(nx, ny) ||
                state.render.is_walkblock(nx, ny)) {

                continue;
            }

            ns.push_back(std::make_pair(dx, dy));
        }
    }

    if (ns.empty())
        return;

    double maxd = 0.0;
    size_t maxi = 0;

    for (size_t z = 0; z < ns.size(); ++z) {

        double thisd = 0.0;
        int nn = 0;

        for (const auto& i : state.monsters.mons) {

            if (!state.render.is_in_fov(i.first.first, i.first.second))
                continue;

            double dist = distance(p.px + ns[z].first, p.py + ns[z].second,
                                   i.first.first, i.first.second);

            thisd += dist;
            ++nn;
        }

        if (thisd > maxd) {
            maxd = thisd;
            maxi = z;
        }
    }

    if (maxd == 0)
        return;

    int dx = ns[maxi].first;
    int dy = ns[maxi].second;

    move(p, state, dx, dy, n_skin);
}

std::string tombstone_text(const Player& p) {

    bones::bone_t bone;

    if (!bones::bones().get(p, bone)) {

        return "\n\nHm, this tombstone is blank...";
    }

    if (bone.name.name.empty())
        bone.name.name = "anonymous";

    if (bone.cause.name.empty())
        bone.cause.name = "unnatural causes";

    return nlp::message(constants().tombstone_text,
                        bone.name,
                        bone.level+1, 
                        bone.cause, 
                        std::max(bone.worth, 0.0));
}

void use_terrain(Player& p, GameState& state, bool& regen, bool& done, bool& dead) {

    features::Feature feat;
    if (!state.features.get(p.px, p.py, feat)) {
        state.render.do_message("There is nothing here to use.");
        return;
    }

    const Terrain& t = terrain().get(feat.tag);

    if (t.uncharge.use) {
        state.features.uncharge(p.px, p.py, state.render);
    }

    if (!t.victory_item.null()) {

        const Design& d_victory = designs().get(t.victory_item);

        items::Item vi;

        if (p.inv.take(d_victory.slot, vi)) {

            state.render.do_message("Congratulations! (press space to close window)", true);
            state.render.do_message(" ~*~   You win the game!   ~*~ ", true);

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

    if (t.banking.sell_margin > 0 || t.banking.shield_bonus > 0) {

        state.push_window(show_banking_menu(p, state, t.banking), screens_t::bank_main);
        return;
    }

    if (t.stairs != 0) {

        if (t.stairs > 0) {
            state.render.do_message("You climb down the hole.");
        } else {
            state.render.do_message("You are magically teleported!");
        }

        p.worldz += t.stairs;

        ++(state.ticks);
        regen = true;
        return;
    }

    if (t.tunnel_x != 0 || t.tunnel_y != 0) {
        state.render.do_message("You climb into the tunnel.");
        p.worldx += t.tunnel_x;
        p.worldy += t.tunnel_y;

        if (p.worldx > 1) p.worldx = -1;
        else if (p.worldx < -1) p.worldx = 1;

        if (p.worldy > 1) p.worldy = -1;
        else if (p.worldy < -1) p.worldy = 1;

        ++(state.ticks);
        regen = true;
        return;
    }

    if (t.grant_spell.timeout > 0) {

        const auto& sp = t.grant_spell;

        if ((sp.karma_bound < 0 && p.karma.val <= sp.karma_bound) ||
            (sp.karma_bound > 0 && p.karma.val >= sp.karma_bound)) {

            for (const auto& i : p.spells) {
                if (i.name == sp.name) {
                    state.render.do_message("Nothing happens.");
                    return;
                }
            }

            p.spells.push_back(sp);
            state.render.do_message(nlp::message("You are granted the power of %s.", sp.name), true);

        } else {
            state.render.do_message("You want nothing to do with this vile thing.");
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

                state.render.do_message(nlp::message("You now have %s!", nlp::count(), cto, vi.count));

                ++(state.ticks);

                // HACK
                if (leftover && tmp.tag != c.to) {
                    state.items.place(p.px, p.py, tmp, state.grid);
                }

                return;
            }
        }

        state.render.do_message("You need a specific kind of item to use this.");
        return;
    }


    if (t.wishing) {
        if (t.wishing == Terrain::SPECIAL_WISH) {
            do_player_wish(state, p, true);
        } else {
            do_player_wish(state, p, false);
        }

        return;
    }


    state.render.do_message("There is nothing here to use.");
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
