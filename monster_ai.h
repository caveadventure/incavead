#ifndef __MONSTER_AI_H
#define __MONSTER_AI_H


// HACK
struct summons_t {
    unsigned int x;
    unsigned int y;
    tag_t summontag;
    unsigned int arg;
    tag_t summonertag;
    std::string msg;
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
        p.get_defense(defenses);

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


inline bool do_monster_magic(Player& p, GameState& state, double dist, unsigned int range,
                             std::vector<summons_t>& summons, 
                             const monsters::Monster& m, const Species& s) {

    bool reachd = false;

    if (dist >= range)
        return false;

    if (s.blast.size() > 0 || s.cast_cloud.size() > 0) {

        reachd = reachable(state, m.xy.first, m.xy.second, p.px, p.py);
    }

    if (reachd) {

        for (const auto& b : s.blast) {

            if (dist >= b.range) 
                continue;

            if ((state.ticks % b.turns) != 0)
                continue;

            double v = state.rng.gauss(0.0, 1.0);
            if (v <= b.chance) continue;

            do_monster_blast(p, state, s, p.px, p.py, b.radius, b.attacks);
            return true;
        }

        for (const auto& c : s.cast_cloud) {

            if ((state.ticks % c.turns) != 0) continue;
                    
            double v = state.rng.gauss(0.0, 1.0);
            if (v <= c.chance) continue;

            cast_cloud(state, p.px, p.py, c.radius, c.terraintag);
            state.render.do_message(nlp::message("%s casts %s!", s, c.name));
            return true;
        }
    }

    if (s.summon.size() > 0) {

        for (const auto& c : s.summon) {

            if ((state.ticks & c.turns) != 0) continue;

            //const Species& s = species().get(c.speciestag);
            //if (!state.species_counts.has(s.level, c.speciestag))
            //    continue;

            double v = state.rng.gauss(0.0, 1.0);
            if (v <= c.chance) continue;

            summons.push_back(summons_t{m.xy.first, m.xy.second, c.speciestag, 0, m.tag, c.msg});
        }
    }

    if (s.spawns.size() > 0) {

        for (const auto& c : s.spawns) {

            if ((state.ticks & c.turns) != 0) continue;

            double v = state.rng.gauss(0.0, 1.0);
            if (v <= c.chance) continue;

            summons.push_back(summons_t{m.xy.first, m.xy.second, tag_t(), c.level, m.tag, c.msg});
        }        
    }

    if (!s.morph.species.null()) {

        double v = state.rng.gauss(0.0, 1.0);

        if (v > s.morph.chance) {

            tag_t news = s.morph.species;
            state.monsters.change(m, [news](monsters::Monster& m) { m.tag = news; });

            state.render.invalidate(m.xy.first, m.xy.second);
            return true;
        }
    }

    return false;
}

inline float monster_move_cost(GameState& state, const Species& s, unsigned int x, unsigned int y) {

    if (!monsters::Monsters::is_walkable(state.grid, s, x, y))
        return 0.0f;
    
    features::Feature feat;
    if (state.features.get(x, y, feat)) {

        const Terrain& t = terrain().get(feat.tag);

        if (t.walkblock)
            return 0.0f;

        if (t.viewblock)
            return 3.0f;
    }

    return 1.0f;
}



inline bool move_monster(Player& p, GameState& state, 
                         std::vector<summons_t>& summons,
                         const monsters::Monster& m, const Species& s,
                         monsters::pt& nxy, bool& do_die) {

    bool do_stop = false;

    unsigned int range = s.range;

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

        if (t.view_radius >= 0) {
            // HACK. Monsters are dumber than the player, give the player a slight advantage.
            range = std::max(0, t.view_radius - 1);
        }
    }


    if (m.health <= -3) {

        if (!s.death_summon.null()) {
            summons.push_back(summons_t{m.xy.first, m.xy.second, s.death_summon, 1, m.tag, ""});
        }

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

    if (m.blind > 0) {
        range = std::max(0, (int)range - static_cast<int>(m.blind / constants().blindturns_to_radius) - 1);

        state.monsters.change(m, [](monsters::Monster& m) { --(m.blind); });
    }

    if (m.magic > -3.0 && !(s.ai == Species::ai_t::none_nosleep && p.sleep > 0)) {

        if (do_monster_magic(p, state, dist, range, summons, m, s)) 
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
               state.render.path_walk(m.xy.first, m.xy.second, p.px, p.py, 1, range, 
                                      [&state,&s](unsigned int a, unsigned int b, unsigned int c, unsigned int d) {
                                          return monster_move_cost(state, s, c, d);
                                      },
                                      nxy.first, nxy.second)) {

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
        std::vector<monsters::pt> tmp;

        for (const neighbors::pt& v : state.neigh(m.xy)) {
            if (monster_move_cost(state, s, v.first, v.second) != 0.0f) {
                tmp.push_back(v);
            }
        }

        if (tmp.empty())
            return false;

        nxy = tmp[state.rng.n(tmp.size())];
    }

    //if (!monsters::Monsters::is_walkable(state.grid, s, nxy))
    //    return false;

    if (nxy.first == p.px && nxy.second == p.py) {

        if (s.ai == Species::ai_t::suicide) {

            monster_kill(p, state, m, s, false);

            do_die = true;
            return true;
        }

        if (!s.steal.null()) {

            items::Item tmp;
            if (p.inv.take(s.steal, tmp)) {

                state.render.do_message(nlp::message("%S disappears in a puff of smoke.", s), true);

                do_die = true;
                return true;
            }
        }

        damage::defenses_t defenses;
        p.get_defense(defenses);

        double vamp = defend(p, defenses, p.get_computed_level(state.rng), s, state);

        if (vamp != 0) {

            if (m.health + vamp <= -3.0) {
                do_die = true;
                return true;
            }
            
            state.monsters.change(m, [vamp](monsters::Monster& m) { 
                    m.health += vamp; 
                    m.health = std::min(3.0, m.health);
                });
        }

        return false;
    }

    if (!s.trail.terrain.null() &&
        state.features.x_set(nxy.first, nxy.second, s.trail.terrain, state.render)) {

        double c = state.rng.gauss(s.trail.cost.mean, s.trail.cost.deviation);

        if (c != 0) {
            state.monsters.change(m, [c](monsters::Monster& m) { m.health -= c; });
        }
    }

    return true;
}


#endif
