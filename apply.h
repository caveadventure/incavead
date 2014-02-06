#ifndef __APPLY_H
#define __APPLY_H


inline std::string dowsing_message(const Player& p, const GameState& state) {

    const Levelskin& ls = levelskins().get(p.worldz);

    if (!ls.has_treasure) {
        return "Dowsing is useless here.";
    }

    double h = state.grid.get(p.px, p.py);

    if (h <= -1) {
        return "Completely cold.";

    } else if (h < 0.5) {
        return "Very cold.";

    } else if (h < 0) {
        return "Cold.";

    } else if (h < 0.5) {
        return "A little bit warm.";

    } else if (h < 1) {
        return "Warm.";

    } else if (h < 1.5) {
        return "Warm and getting warmer.";

    } else if (h < 2) {
        return "A little bit hot.";

    } else if (h < 2.5) {
        return "Hot.";

    } else if (h < 3.0) {
        return "Very hot.";

    } else {
        return "Extremely hot.";
    }
}


inline bool apply_item(Player& p, tag_t slot, GameState& state, bool& regen) {

    items::Item tmp;

    if (!p.inv.get(slot, tmp))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (!d.usable) 
        return false;
        
    // Dowsing rods are permanent.
    if (d.flags.dowsing) {
        state.render.do_message(dowsing_message(p, state));
        return true;
    }

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

    if (d.heal_blind) {

        if (p.blind > 0) {
            p.blind = 0;
            state.render.do_message("You can see again!", true);
        }

        ret = true;
    }

    if (d.heal_unluck) {

        if (p.luck.val < 0) {
            p.luck.val = 0;
            state.render.do_message("You lucky stiff.");
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

    ++(state.ticks);
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

inline bool start_blast_item(Player& p, tag_t slot, GameState& state) {

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

        ++(state.ticks);
    }

    return true;
}


inline bool start_cloud_item(Player& p, tag_t slot, GameState& state) {

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

    ++(state.ticks);

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
                      Player& p, GameState& state) {

    items::Item disc;
        
    if (p.inv.floor_to_inv(x, y, z, state.items, state.render, disc)) {

        if (!disc.tag.null()) {

            const Design& d = designs().get(disc.tag);

            // HACK
            state.render.do_message(nlp::message("You discard %s to make space.", nlp::count(), d, disc.count));
        }

        ++(state.ticks);
        return true;
    }

    return false;
}

#endif
