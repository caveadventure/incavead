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

inline void monster_blast_process_point(Player& p, GameState& state, const Species& s,
                                        unsigned int _x, unsigned int _y, const damage::attacks_t& attacks) {

    if (_x == p.px && _y == p.py) {

        damage::defenses_t defenses;
        p.inv.get_defense(defenses);

        defend(p, defenses, p.get_computed_level(state.rng), s, attacks, state);

    } else {

        monsters::Monster mon;
        if (state.monsters.get(_x, _y, mon)) {

            attack_from_env(p, attacks, s.get_computed_level(), state, mon, false);
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


inline bool do_monster_magic(Player& p, GameState& state, size_t ticks, double dist, unsigned int range,
                             std::vector<summons_t>& summons, 
                             const monsters::Monster& m, const Species& s) {

    bool reachd = false;

    if (dist < range && 
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

    if (s.summon.size() > 0 && dist < range) {

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

    if (s.spawns.size() > 0 && dist < range) {

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

            attack_from_env(p, t.attacks, t.attack_level, state, m, false);

            if (t.uncharge.attack) {
                state.features.uncharge(m.xy.first, m.xy.second, state.render);
            }
        }

        if (t.sticky) {

            if (t.uncharge.move) {
                state.features.uncharge(m.xy.first, m.xy.second, state.render);
            }

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

    unsigned int range = s.range;

    if (m.blind > 0) {
        range = std::max(0, (int)range - static_cast<int>(m.blind / constants().blindturns_to_radius) - 1);

        state.monsters.change(m, [](monsters::Monster& m) { --(m.blind); });
    }

    if (m.magic > -3.0 && !(s.ai == Species::ai_t::none_nosleep && p.sleep > 0)) {

        if (do_monster_magic(p, state, ticks, dist, range, summons, m, s)) 
            return false;
    }

    // HACK!
    // Performance tweak.
    bool do_random = false;
    bool do_seek = false;

    if (s.ai == Species::ai_t::seek_player ||
        s.ai == Species::ai_t::suicide ||
        (s.ai == Species::ai_t::seek_nosleep && p.sleep == 0)) {

        if (dist <= s.range + 5) {
            do_seek = true;
        }
    }

    if (m.fear > 0 || s.ai == Species::ai_t::random) {
        do_random = true;

    } else if (s.ai == Species::ai_t::inrange_random && dist <= range) {
        do_random = true;

    } else if (do_seek && !do_random &&
               state.render.path_walk(m.xy.first, m.xy.second, p.px, p.py, 1, 
                                      range, nxy.first, nxy.second)) {

        // Nothing, nxy is good.

    } else {

        switch (s.idle_ai) {

        case Species::idle_ai_t::random:

            if (dist > range + 10)
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

        if (s.ai == Species::ai_t::suicide) {

            monster_kill(p, state, m, s, false);

            do_die = true;
            return true;
        }

        damage::defenses_t defenses;
        p.inv.get_defense(defenses);

        defend(p, defenses, p.get_computed_level(state.rng), s, state);
        return false;

    } else {
        return true;
    }
}


#endif
