#ifndef __APPLY_H
#define __APPLY_H

#include <valarray>

inline bool apply_item(Player& p, tag_t slot, GameState& state, bool& regen, size_t& ticks) {

    items::Item tmp;

    if (!p.inv.get(slot, tmp))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (!d.usable) 
        return false;
        
    if (!p.inv.take(slot, tmp, 1))
        return false;

    bool ret = false;

    if (d.heal > 0) {

        p.health.inc(d.heal);
        state.render.do_message("You feel better.");
        ret = true;
    } 

    if (d.feed > 0) {

        p.food.inc(d.feed);
        state.render.do_message(nlp::message("You eat %s.", d));
        ret = true;
    } 

    if (d.heal_blind > 0) {

        if (p.blind > 0) {
            p.blind = 0;
            state.render.do_message("You can see again!", true);
        }

        ret = true;
    }

    if (d.karma != 0) {
        p.karma.inc(d.karma);
        ret = true;
    }

    if (d.flags.blink) {

        grid::pt xy;
        if (!state.grid.one_of_walk(state.rng, xy))
            return false;

        state.render.invalidate(p.px, p.py);

        p.px = xy.first;
        p.py = xy.second;

        state.render.invalidate(p.px, p.py);
        ret = true;
    }

    // WARNING, don't change the order of blocks, as worldz can be modified.
    if (!d.place_permafeat.feat.null()) {

        // HACK!
        const Levelskin& ls = levelskins().get(p.worldz);
        const Terrain& t = terrain().get(d.place_permafeat.feat);

        bool bad = false;

        if (ls.no_phase_level && t.stairs > 0) {
            bad = true;

        } else {

            features::Feature feat;
            if (state.features.get(p.px, p.py, feat)) {

                const Terrain& to = terrain().get(feat.tag);

                if (!to.victory_item.null()) {
                    bad = true;
                }
            }
        }

        if (bad) {
            state.render.do_message("Nothing happened. Strange.", true);
            ret = false;

        } else {
            state.features.set(p.px, p.py, d.place_permafeat.feat, state.render);        
            permafeats::features().add(p, d.place_permafeat.feat);
            ret = true;
        }

    } else if (d.place_permafeat.walk != -1 || d.place_permafeat.water != -1) {

        bool walk = (d.place_permafeat.walk == -1 ? state.grid.is_walk(p.px, p.py) : d.place_permafeat.walk);
        bool water = (d.place_permafeat.water == -1 ? state.grid.is_water(p.px, p.py) : d.place_permafeat.water);

        state.grid.set_walk_water(state.neigh, p.px, p.py, walk, water);
        state.render.invalidate(p.px, p.py);
        permafeats::features().add(p, walk, water);
        ret = true;
    }

    if (d.descend != 0) {
        p.worldz += d.descend;
        regen = true;
        ret = true;
    }

    if (d.safe_descend != 0) {
        
        const Levelskin& ls = levelskins().get(p.worldz);

        if (ls.no_phase_level) {
            state.render.do_message("Nothing happened. Strange.", true);
            ret = false;

        } else {
            p.worldz += d.safe_descend;
            regen = true;
            ret = true;
        }
    }

    if (!d.genocide.null()) {

        state.render.do_message("You sense a great disturbance in the force.");

        genocide(state, d.genocide);
        ret = true;
    }

    if (d.wishing) {
        if (d.wishing == Design::SPECIAL_WISH) {
            do_player_wish(state, p, true);
        } else {
            do_player_wish(state, p, false);
        }

        ret = true;
    }

    if (d.magic_mapping) {

        for (const auto& f : state.features.feats) {
            const Terrain& t = terrain().get(f.second.tag);

            if (t.air)
                continue;

            const grender::pt& xy = f.first;
            state.render.set_is_lit(xy.first, xy.second, 3, true);
            state.render.invalidate(xy.first, xy.second);
        }

        ret = true;
    }

    if (!ret) {
        items::Item tmp2;
        p.inv.place(slot, tmp, tmp2);

        return true;
    }

    ++ticks;
    return true;
}


inline bool destroy_item(Player& p, tag_t slot) {

    items::Item tmp;

    if (!p.inv.get(slot, tmp))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (!d.destructible) 
        return false;
        
    if (!p.inv.take(slot, tmp))
        return false;

    return true;
}

inline void blast_process_point(Player& p, GameState& state, const Design& d,
                                unsigned int _x, unsigned int _y) {

    if (_x == p.px && _y == p.py) {

        damage::defenses_t defenses;
        p.inv.get_defense(defenses);

        defend(p, defenses, p.get_computed_level(state.rng), d, state);

    } else {

        monsters::Monster mon;
        if (state.monsters.get(_x, _y, mon)) {

            attack_from_player(p, d.attacks, d.level, state, mon, true);
        }
    }
}

inline bool end_blast_item(Player& p, tag_t slot, unsigned int lx, unsigned int ly, 
                           GameState& state) {

    items::Item tmp;
        
    if (!p.inv.take(slot, tmp, 1))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (distance(p.px, p.py, lx, ly) > d.blast.range) {
        return false;
    }

    if (d.blast.radius == 0) {

        blast_process_point(p, state, d, lx, ly);

    } else {

        state.render.draw_circle(lx, ly, d.blast.radius, true, d.skin.a.fore, maudit::color::bright_black,
                                 [&](unsigned int _x, unsigned int _y) {
                                 
                                     blast_process_point(p, state, d, _x, _y);
                                 });
    }

    return true;
}

inline bool start_blast_item(Player& p, tag_t slot, GameState& state, size_t& ticks) {

    items::Item tmp;
    if (!p.inv.get(slot, tmp)) {
        return false;
    }

    const Design& d = designs().get(tmp.tag);

    if (d.blast.radius == 0 && d.blast.range == 0) {
        return false;
    }

    if (d.blast.range > 0) {
        
        start_look_target(p.state, p.look, p.px, p.py, state, 0, d.blast.range);
        p.state |= Player::BLASTING;

    } else {

        if (!end_blast_item(p, slot, p.px, p.py, state)) 
            return false;

        ++ticks;
    }

    return true;
}


inline bool start_cloud_item(Player& p, tag_t slot, GameState& state, size_t& ticks) {

    items::Item tmp;
    if (!p.inv.get(slot, tmp)) {
        return false;
    }

    const Design& d = designs().get(tmp.tag);

    if (d.cast_cloud.radius == 0) {
        return false;
    }

    if (!p.inv.take(slot, tmp, 1))
        return false;

    cast_cloud(state, p.px, p.py, d.cast_cloud.radius, d.cast_cloud.terraintag);

    ++ticks;

    return true;
}


inline bool end_throw_item(Player& p, tag_t slot, unsigned int lx, unsigned int ly,
                           GameState& state) {

    items::Item tmp;
        
    if (!p.inv.take(slot, tmp, 1))
        return false;

    const Design& d = designs().get(tmp.tag);

    double v = distance(p.px, p.py, lx, ly);

    if (d.throwrange == 0 || v > d.throwrange) {
        return false;
    }

    monsters::Monster mon;
    if (state.monsters.get(lx, ly, mon)) {
            
        double v2 = std::max(0.0, (v-1) / d.throwrange);

        unsigned int lev = (1 - v2) * p.get_computed_level(state.rng);

        attack_from_player(p, d.attacks, lev, state, mon, false);
    }

    state.items.place(lx, ly, tmp, state.render);

    return true;
}

inline bool start_throw_item(Player& p, tag_t slot, GameState& state) {

    items::Item tmp;
    if (!p.inv.get(slot, tmp))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (d.throwrange == 0)
        return false;
    
    start_look_target(p.state, p.look, p.px, p.py, state, 0, d.throwrange);
    p.state |= Player::THROWING;

    return true;
}

inline bool start_digging(Player& p, tag_t slot, GameState& state) {

    items::Item tmp;
    if (!p.inv.get(slot, tmp))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (d.digging <= 0)
        return false;
    
    p.state |= Player::DIGGING;

    return true;
}


inline bool take_item(unsigned int x, unsigned int y, unsigned int z, 
                      Player& p, GameState& state, size_t& ticks) {

    items::Item disc;
        
    if (p.inv.floor_to_inv(x, y, z, state.items, state.render, disc)) {

        if (!disc.tag.null()) {

            const Design& d = designs().get(disc.tag);

            // HACK
            state.render.do_message(nlp::message("You discard %s to make space.", nlp::count(), d, disc.count));
        }

        ticks++;
        return true;
    }

    return false;
}


inline size_t longest_common_subsequence(const std::string& a, const std::string& b) {
    
    size_t w = b.size() + 1;
    size_t h = a.size() + 1;

    std::valarray<size_t> c(w * h);

    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < b.size(); ++j) {

            size_t ix = w * (i + 1) + (j + 1);

            if (a[i] == b[j]) {
                c[ix] = c[w * i + j] + 1;
            } else {
                c[ix] = std::max(c[w * (i + 1) + j], c[w * i + (j + 1)]);
            }
        }
    }

    return c[w * h - 1];
}


inline bool find_existing_item(GameState& state, unsigned int px, unsigned int py, const std::string& name) {

    const auto& data = state.designs_counts.data;

    size_t maxlcs = 0;
    std::vector<double> counts;
    std::vector<tag_t> desgns;

    for (const auto& i : data) {
        for (const auto& j : i.second) {

            const Design& _design = designs().get(j.first);

            // HACK
            if (_design.luck.size() > 0)
                continue;

            size_t lcs = longest_common_subsequence(_design.name, name);

            if (lcs < maxlcs)
                continue;

            if (lcs > maxlcs) {
                maxlcs = lcs;
                counts.clear();
                desgns.clear();
            }

            counts.push_back(j.second);
            desgns.push_back(j.first);
        }
    }

    while (1) {

        if (counts.empty()) {
            state.render.do_message("Strange. Nothing happened.");
            return false;
        }

        std::discrete_distribution<unsigned int> d(counts.begin(), counts.end());
        unsigned int ntag = d(state.rng.gen);

        tag_t design = desgns[ntag];

        unsigned int trucount = state.designs_counts.take(design);

        if (trucount == 0) {
            counts.erase(counts.begin() + ntag);
            desgns.erase(desgns.begin() + ntag);
            continue;
        }

        const Design& _design = designs().get(design);

        items::Item made = state.items.make_item(design, items::pt(px, py), state.rng);
        state.items.place(px, py, made, state.render);

        state.render.do_message(nlp::message("You see %s.", nlp::count(), _design, made.count));
        return true;
    }
}


inline bool find_any_item(GameState& state, Player& p, unsigned int px, unsigned int py, const std::string& name) {

    const auto& d = designs();

    size_t maxlcs = 0;    
    std::vector<tag_t> desgns;

    for (const auto& i : d.bank) {

        const Design& _design = designs().get(i.first);

        if (_design.wishing)
            continue;

        size_t lcs = longest_common_subsequence(_design.name, name);

        if (lcs < maxlcs)
            continue;

        if (lcs > maxlcs) {
            maxlcs = lcs;
            desgns.clear();
        }

        desgns.push_back(i.first);
    }

    if (desgns.empty()) {
        state.render.do_message("Strange. Nothing happened.");
        return false;
    }

    tag_t design = desgns[state.rng.n(desgns.size())];
    const Design& _design = designs().get(design);

    // HACK
    if (design == constants().unique_item) {
        p.uniques_disabled = true;
    }

    items::Item made = state.items.make_item(design, items::pt(px, py), state.rng);
    state.items.place(px, py, made, state.render);

    state.render.do_message(nlp::message("You see %s.", nlp::count(), _design, made.count));
    return true;
}


inline bool simple_wish(GameState& state, Player& p, const std::string& wish) {

    if (wish.empty())
        return true;

    bool ok = find_existing_item(state, p.px, p.py, wish);

    if (ok) {
        p.luck.dec(6);
    }

    return ok;
}

inline bool special_wish(GameState& state, Player& p, const std::string& wish) {

    return find_any_item(state, p, p.px, p.py, wish);
}

#endif
