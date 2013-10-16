#ifndef __APPLY_H
#define __APPLY_H


inline void cast_cloud(GameState& state, unsigned int x, unsigned int y, unsigned int r,
                       tag_t terraintag) {

    state.render.draw_circle(x, y, r, false, maudit::color::bright_blue, maudit::color::bright_black,
                             [&](unsigned int _x, unsigned int _y) {

                                 features::Feature tmp;
                                 if (state.features.get(_x, _y, tmp) && tmp.tag != terraintag) {

                                     const Terrain& t = terrain().get(tmp.tag);

                                     if (!t.air) 
                                         return;
                                 }


                                 if (!state.grid.is_walk(_x, _y)) return;

                                 state.features.set(_x, _y, terraintag, state.render);
                             });
}


inline bool apply_item(Player& p, const std::string& slot, GameState& state, bool& regen) {

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
    if (!d.place_permafeat.null()) {

        state.features.set(p.px, p.py, d.place_permafeat, state.render);        
        permafeats::features().add(p, d.place_permafeat);
        ret = true;
    }

    if (d.descend != 0) {
        p.worldz += d.descend;
        regen = true;
        ret = true;
    }

    if (d.safe_descend != 0) {
        
        const Levelskin& ls = levelskins().get(p.worldz);

        if (ls.noterrain) {
            state.render.do_message("Nothing happened. Strange.", true);
            ret = false;

        } else {
            p.worldz += d.safe_descend;
            regen = true;
            ret = true;
        }
    }

    return ret;
}


inline bool destroy_item(Player& p, const std::string& slot) {

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

            attack(p, d.attacks, d.level, state, mon, true);
        }
    }
}

inline bool end_blast_item(Player& p, const std::string& slot, unsigned int lx, unsigned int ly, 
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

inline bool start_blast_item(Player& p, const std::string& slot, GameState& state, size_t& ticks) {

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


inline bool start_cloud_item(Player& p, const std::string& slot, GameState& state, size_t& ticks) {

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


inline bool end_throw_item(Player& p, const std::string& slot, unsigned int lx, unsigned int ly,
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

        attack(p, d.attacks, lev, state, mon);
    }

    state.items.place(lx, ly, tmp, state.render);

    return true;
}

inline bool start_throw_item(Player& p, const std::string& slot, GameState& state) {

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

inline bool start_digging(Player& p, const std::string& slot, GameState& state) {

    items::Item tmp;
    if (!p.inv.get(slot, tmp))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (d.digging <= 0)
        return false;
    
    p.state |= (Player::DIGGING | Player::PICK_DIRECTION);

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

#endif
