#ifndef __MONSTER_AI_H
#define __MONSTER_AI_H


// HACK
struct summons_t {
    unsigned int x;
    unsigned int y;
    tag_t summontag;
    unsigned int level;
    tag_t summonertag;
};


inline bool reachable(GameState& state, unsigned int ax, unsigned int ay, unsigned int bx, unsigned int by) {
    unsigned int _x = ax;
    unsigned int _y = ay;

    state.render.draw_line(ax, ay, bx, by, false, 
                           maudit::color::dim_red, maudit::color::bright_white,
                           [&](unsigned int x, unsigned int y) {
                                   
                               if (x == ax && y == ay)
                                   return true;

                               if (state.render.is_walkblock(x, y) ||
                                   state.render.is_viewblock(x, y))
                                   return false;

                               _x = x;
                               _y = y;
                               return true;
                           });

    if (_x == bx && _y == by) return true;
    return false;
}


inline void monster_blast_process_point(Player& p, GameState& state, const Species& s,
                                        unsigned int _x, unsigned int _y, const damage::attacks_t& attacks) {

    if (_x == p.px && _y == p.py) {

        damage::defenses_t defenses;
        p.inv.get_defense(defenses);

        defend(p, defenses, p.get_computed_level(state.rng), s, attacks, state);

    } else {

        monsters::Monster mon;
        if (state.monsters.get(_x, _y, mon)) {

            attack(attacks, s.get_computed_level(), state, mon, species().get(mon.tag));
        }
    }
}

inline void do_monster_blast(Player& p, GameState& state, const Species& s, 
                             unsigned int tx, unsigned int ty, unsigned int rad, 
                             const damage::attacks_t& attacks) {

    if (rad == 0) {

        monster_blast_process_point(p, state, s, tx, ty, attacks);

    } else {

        state.render.draw_circle(tx, ty, rad, true, s.skin.a.fore, maudit::color::bright_black,
                                 [&](unsigned int _x, unsigned int _y) {
                                 
                                     monster_blast_process_point(p, state, s, _x, _y, attacks);
                                 });
    }
}


inline bool do_monster_magic(Player& p, GameState& state, size_t ticks, double dist, 
                             std::vector<summons_t>& summons, 
                             const monsters::Monster& m, const Species& s) {

    bool reachd = false;

    if (dist < s.range && 
        (s.blast.size() > 0 || s.cast_cloud.size() > 0)) {

        reachd = reachable(state, m.xy.first, m.xy.second, p.px, p.py);
    }

    if (reachd) {

        for (const auto& b : s.blast) {

            if (dist >= b.range) 
                continue;

            if ((ticks % b.turns) != 0)
                continue;

            double v = state.rng.gauss(0.0, 1.0);
            if (v <= b.chance) continue;

            do_monster_blast(p, state, s, p.px, p.py, b.radius, b.attacks);
            return true;
        }

        for (const auto& c : s.cast_cloud) {

            if ((ticks % c.turns) != 0) continue;
                    
            double v = state.rng.gauss(0.0, 1.0);
            if (v <= c.chance) continue;

            cast_cloud(state, p.px, p.py, c.radius, c.terraintag);
            state.render.do_message(nlp::message("%s casts %s!", s, c.name));
            return true;
        }
    }

    if (s.summon.size() > 0 && dist < s.range) {

        for (const auto& c : s.summon) {

            if ((ticks & c.turns) != 0) continue;

            const Species& s = species().get(c.speciestag);
            if (!state.species_counts.has(s.level, c.speciestag))
                continue;

            double v = state.rng.gauss(0.0, 1.0);
            if (v <= c.chance) continue;

            summons.push_back(summons_t{m.xy.first, m.xy.second, c.speciestag, 0, m.tag});
        }
    }

    if (s.spawns.size() > 0 && dist < s.range) {

        for (const auto& c : s.spawns) {

            if ((ticks & c.turns) != 0) continue;

            double v = state.rng.gauss(0.0, 1.0);
            if (v <= c.chance) continue;

            summons.push_back(summons_t{m.xy.first, m.xy.second, tag_t(), c.level, m.tag});
        }        
    }

    return false;
}


inline bool move_monster(Player& p, GameState& state, size_t ticks, 
                         std::vector<summons_t>& summons,
                         const monsters::Monster& m, const Species& s,
                         monsters::pt& nxy, bool& do_die) {

    bool do_stop = false;

    features::Feature feat;
    if (state.features.get(m.xy.first, m.xy.second, feat) && 
        !s.flags.terrain_immune) {

        const Terrain& t = terrain().get(feat.tag);

        if (!t.attacks.empty()) {

            attack(t.attacks, t.attack_level, state, m, s);
        }

        if (t.sticky) {
            state.features.uncharge(m.xy.first, m.xy.second, state.render);
            do_stop = true;
        }
    }


    if (m.health < -3) {
        do_die = true;
        return true;
    }

    if (do_stop) {
        return false;
    }

    if (m.sleep > 0) {
        state.monsters.change(m, [](monsters::Monster& m) { --(m.sleep); });
        return false;
    }

    if (m.fear > 0) {
        state.monsters.change(m, [](monsters::Monster& m) { --(m.fear); });
    }

    double dist = distance(m.xy.first, m.xy.second, p.px, p.py);

    if (m.magic > -3.0 && !(s.ai == Species::ai_t::none_nosleep && p.sleep > 0)) {

        if (do_monster_magic(p, state, ticks, dist, summons, m, s)) 
            return false;
    }

    // HACK!
    bool do_random = false;
    bool do_seek = false;

    if (s.ai == Species::ai_t::seek_player ||
        (s.ai == Species::ai_t::seek_nosleep && p.sleep == 0)) {

        if (dist <= s.range + 5) {
            do_seek = true;
        }
    }


    if (m.fear > 0 || s.ai == Species::ai_t::random) {
        do_random = true;

    } else if (s.ai == Species::ai_t::inrange_random && dist <= s.range) {
        do_random = true;

    } else if (do_seek && !do_random &&
               state.render.path_walk(m.xy.first, m.xy.second, p.px, p.py, 1, 
                                      s.range, nxy.first, nxy.second)) {

        // Nothing, nxy is good.

    } else {

        switch (s.idle_ai) {

        case Species::idle_ai_t::random:

            if (dist > s.range + 10)
                return false;

            do_random = true;
            break;

        default:
            return false;
        }
    }

    if (do_random) {
        std::vector<monsters::pt> tmp = monsters::Monsters::get_walkables(state.neigh, state.grid, s, m.xy);

        if (tmp.empty())
            return false;

        nxy = tmp[state.rng.n(tmp.size())];
    }

    if (!monsters::Monsters::is_walkable(state.grid, s, nxy))
        return false;

    if (nxy.first == p.px && nxy.second == p.py) {

        damage::defenses_t defenses;
        p.inv.get_defense(defenses);

        defend(p, defenses, p.get_computed_level(state.rng), s, state);
        return false;

    } else {
        return true;
    }
}


#endif
