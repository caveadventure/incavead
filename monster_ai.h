#ifndef __MONSTER_AI_H
#define __MONSTER_AI_H


inline void cast_cloud(GameState& state, unsigned int x, unsigned int y, unsigned int r,
                       tag_t terraintag) {

    const Terrain& tt = terrain().get(terraintag);

    auto fg = tt.skin[0].fore;
    auto bg = tt.skin[0].back;

    state.render.draw_circle(x, y, r, fg, bg,
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

inline void monster_blast_process_point(Player& p, GameState& state, const Species& s, monsters::Monster& mon,
                                        unsigned int _x, unsigned int _y, const damage::attacks_t& attacks,
                                        bool friendly_fire) {

    if (_x == p.px && _y == p.py) {

        damage::defenses_t defenses;
        p.get_defense(defenses);

        defend(p, defenses, p.get_computed_level(), s, mon, attacks, state, friendly_fire);

    } else {

        monsters::Monster& mon = state.monsters.get(_x, _y);

        if (!mon.null()) {

            attack_from_env(p, attacks, s.get_computed_level(), state, monsters::pt(_x, _y), mon, friendly_fire);
        }
    }
}

inline void do_monster_blast(Player& p, GameState& state, const Species& s, monsters::Monster& mon,
                             unsigned int tx, unsigned int ty, unsigned int rad, 
                             const damage::attacks_t& attacks, bool friendly_fire = false) {

    if (rad == 0) {

        monster_blast_process_point(p, state, s, mon, tx, ty, attacks, friendly_fire);

    } else {

        state.render.draw_circle(tx, ty, rad, s.skin.a.fore, maudit::color::bright_black,
                                 [&](unsigned int _x, unsigned int _y) {
                                 
                                     monster_blast_process_point(p, state, s, mon, _x, _y, attacks, friendly_fire);
                                 });
    }
}


inline bool do_monster_magic(Player& p, GameState& state, std::vector<summons_t>& summons, 
                             const monsters::pt& target, unsigned int dist2, bool is_player, tag_t ally,
                             const monsters::pt& mxy, monsters::Monster& m, const Species& s) {

    if (!s.magic_cost.stat.null()) {

        if (m.stats.sinc(s.magic_cost.stat, -s.magic_cost.cost)) {

            m.dead = true;
            return true;
        }

        if (m.stats.is_min(s.magic_cost.stat))
            return false;
    }
                    
    if ((is_player && !m.ally.null()) || (!is_player && ally == m.ally))
        return false;

    if (s.summon.size() > 0) {

        for (const auto& c : s.summon) {

            if ((state.ticks & c.turns) != 0) continue;

            double v = state.rng.gauss(0.0, 1.0);
            if (v <= c.chance) continue;

            summons.emplace_back(mxy.first, mxy.second, summons_t::type_t::SPECIFIC,
                                 c.speciestag, 0, 1, m.tag, m.ally, c.msg);
        }
    }

    if (s.spawns.size() > 0) {

        for (const auto& c : s.spawns) {

            if ((state.ticks & c.turns) != 0) continue;

            double v = state.rng.gauss(0.0, 1.0);
            if (v <= c.chance) continue;

            summons.emplace_back(mxy.first, mxy.second, summons_t::type_t::LEVEL,
                                 tag_t(), c.level, 1, m.tag, m.ally, c.msg);
        }        
    }

    if (!s.morph.species.null()) {

        double v = state.rng.gauss(0.0, 1.0);

        if (v > s.morph.chance) {

            tag_t news = s.morph.species;
            m.tag = news;

            state.render.invalidate(mxy.first, mxy.second);
            return true;
        }
    }

    for (const auto& b : s.blast) {

        if (dist2 >= b.range * b.range) 
            continue;

        if ((state.ticks % b.turns) != 0)
            continue;

        double v = state.rng.gauss(0.0, 1.0);
        if (v <= b.chance) continue;

        do_monster_blast(p, state, s, m, target.first, target.second, b.radius, b.attacks);
        return true;
    }

    for (const auto& c : s.cast_cloud) {

        if ((state.ticks % c.turns) != 0) continue;
                    
        double v = state.rng.gauss(0.0, 1.0);
        if (v <= c.chance) continue;

        cast_cloud(state, target.first, target.second, c.radius, c.terraintag);

        if (state.render.is_in_fov(mxy.first, mxy.second)) 
            state.render.do_message(nlp::message("%s casts %s!", s, c.name));

        return true;
    }

    return false;
}

namespace {

inline unsigned int dist2(int x1, int x2, int y1, int y2) {
    int a = x1 - x2;
    int b = y1 - y2;
    return a*a + b*b;
}

inline bool is_closer(const monsters::pt& a, const monsters::pt& b, const monsters::pt& target) {

    unsigned int da = dist2(a.first, a.second, target.first, target.second);
    unsigned int db = dist2(b.first, b.second, target.first, target.second);
    
    if (da < db)
        return true;

    return false;
}

inline void find_furthest(const std::vector<monsters::pt>& possible_xy,
                          const monsters::pt& beeline_xy, const monsters::pt& target,
                          monsters::pt& nxy) {

    bool found = false;

    for (const auto& v : possible_xy) {

        if (!found) {
            nxy = v;
            found = true;

        } else if (!is_closer(v, nxy, target)) {
            nxy = v;
        }
    }
}
    
inline void find_closest(const std::vector<monsters::pt>& possible_xy,
                         const monsters::pt& beeline_xy, const monsters::pt& target,
                         monsters::pt& nxy) {

    bool found = false;

    for (const auto& v : possible_xy) {

        if (beeline_xy == v) {
            nxy = v;
            break;

        } else if (!found) {
            nxy = v;
            found = true;

        } else if (is_closer(v, nxy, target)) {
            nxy = v;
        }
    }
}

}

inline bool move_monster_main(Player& p, GameState& state, 
                              std::vector<summons_t>& summons,
                              const monsters::pt& mxy, monsters::Monster& m, const Species& s,
                              monsters::pt& nxy, bool& do_die) {

    bool do_stop = false;

    unsigned int range = s.range;

    if (s.ai == Species::ai_t::none)
        do_stop = true;

    features::Feature feat;
    if (state.features.get(mxy.first, mxy.second, feat) && 
        !s.flags.terrain_immune) {

        const Terrain& t = terrain().get(feat.tag);

        if (!t.attacks.empty()) {

            attack_from_env(p, t.attacks, t.attack_level, state, mxy, m, false);

            if (t.uncharge.attack) {
                state.features.uncharge(mxy.first, mxy.second, state.render);
            }
        }

        if (t.sticky && !do_stop) {

            if (t.uncharge.move) {
                state.features.uncharge(mxy.first, mxy.second, state.render);
            }

            do_stop = true;
        }

        if (t.view_radius >= 0) {
            // HACK. Monsters are dumber than the player, give the player a slight advantage.
            range = std::max(0, t.view_radius - 1);
        }
    }

    {
        const Levelskin& ls = levelskins().get(p.worldz);

        if (!ls.ailment.null()) {

            auto a = constants().ailments.find(ls.ailment);

            if (a == constants().ailments.end())
                throw std::runtime_error("Unknown ailment in levelskin.");

            attack_from_env(p, a->second.attacks, a->second.level, state, mxy, m, false, true);
        }
    }


    if (m.dead) {

        if (!s.death_summon.null()) {
            summons.emplace_back(mxy.first, mxy.second, summons_t::type_t::SPECIFIC,
                                 s.death_summon, 0, 1, m.tag, m.ally, "");
        }

        do_die = true;
        return true;
    }

    // Keep track of seen monsters, hack.

    if (p.seen_monsters.tally.count(m.tag) == 0 && state.render.is_in_fov(mxy.first, mxy.second)) {
                
        p.seen_monsters.tally.insert(m.tag);
        p.seen_monsters.timeline.push_back(m.tag);
    }

    if (do_stop) {
        return false;
    }

    //

    m.stats.tick();

    double blind = 0;
    bool stun = false;
    bool fear = false;
    m.sleep = false;

    for (const auto& i : m.stats.counts) {

        const Count& ct = counts().get(i.first);

        if (ct.blind) blind = (double)i.second.val / (double)ct.cmax;
        if (ct.stun)  stun = true;
        if (ct.fear)  fear = true;
        if (ct.sleep) m.sleep = true;
    }

    if (m.sleep)
        return false;

    if (blind > 0) {
        range = std::max(0, (int)(range * (1.0 - blind)));
    }


    std::vector<monsters::pt> possible_xy;
    bool did_possible = false;
    bool do_random = false;

    unsigned int maxd2 = (range + 1) * (range + 1);

    bool full_empty;
    auto nearest = state.monsters.nearest.get(mxy.first, mxy.second, maxd2, full_empty);

    if (nearest.empty()) {

        // Short-path AI for out-of-range monsters.

        if (s.idle_ai == Species::idle_ai_t::random && !full_empty) {

            do_random = true;

        } else {

            return false;
        }

    } else {

        if (s.ai == Species::ai_t::random) {

            do_random = true;

        } else {

            int pri = -1;

            monsters::pt target;
            bool enemy_is_player = false;
            tag_t enemy_ally;

            monsters::pt beeline_xy;


            if (s.ai != Species::ai_t::magic_none && s.ai != Species::ai_t::magic_none_awake) {

                for (const auto& v_ : state.neigh(mxy)) {

                    auto v = state.neigh.mk(v_, mxy);

                    if (!monster_walkable(state, s, v.first, v.second))
                        continue;

                    possible_xy.push_back(v);
                }

                did_possible = true;
            }

            for (const auto& i : nearest) {

                const monsters::Monster& other = state.monsters.get(i.x, i.y);

                bool is_player = (i.x == p.px && i.y == p.py);

                if (other.null() && !is_player)
                    continue;

                if (!is_player && m.ally == other.ally && i.dist2 <= 2)
                    continue;

                int thispri = 0;

                if (m.ally.null() && is_player) {
                    thispri = 3;

                } else if (!m.ally.null() && is_player) {
                    thispri = 1;

                } else if (m.ally != other.ally) {
                    thispri = 2;
                }

                unsigned int d2 = i.dist2;

                if (thispri < pri)
                    continue;

                bool enemy_sleeping = (is_player ? p.sleep > 0 : other.sleep > 0);

                if (enemy_sleeping && (s.ai == Species::ai_t::magic_none_awake || s.ai == Species::ai_t::seek_awake))
                    continue;

                
                unsigned int tmpnn = 0;
                monsters::pt bxy;

                bool ok = reachable(state, mxy.first, mxy.second, i.x, i.y, 
                                    [&tmpnn,&bxy,&s](GameState& state, unsigned int x, unsigned int y) {

                                        if (!player_walkable_aux(state, x, y, (s.digging > 0)))
                                            return false;

                                        ++tmpnn;

                                        if (tmpnn == 2) 
                                            bxy = monsters::pt(x, y);

                                        return true;
                                    });

                if (!ok)
                    continue;

                if (thispri == pri && d2 >= maxd2)
                    continue;

                pri = thispri;
                maxd2 = d2;
                beeline_xy = bxy;
                target = monsters::pt(i.x, i.y);
                enemy_is_player = is_player;
                enemy_ally = (is_player ? tag_t() : other.ally);
            }

            // HACK
            if (!m.ally.null() && enemy_is_player && maxd2 <= 2) {
                pri = -1;
            }

            if (pri < 0) {

                if (s.ai == Species::ai_t::magic_none || s.ai == Species::ai_t::magic_none_awake) {

                    return false;

                } else {

                    do_random = true;
                }

            } else {

                // We found a target.

                if (!fear &&
                    do_monster_magic(p, state, summons, target, maxd2, enemy_is_player, enemy_ally, mxy, m, s)) {
 
                    return false;
                }

                if (possible_xy.empty())
                    return false;

                if (s.ai == Species::ai_t::magic_random ||
                    !monster_walkable(state, s, target.first, target.second)) {

                    do_random = true;

                } else {

                    if (fear) {

                        find_furthest(possible_xy, beeline_xy, target, nxy);

                    } else {

                        find_closest(possible_xy, beeline_xy, target, nxy);
                    }

                    // OK! If we got here, then 'nxy' holds a valid move and the monster
                    // is actually doing something intelligent.
                }
            }
        }
    }

    if (do_random) {

        if (!did_possible) {

            for (const auto& v_ : state.neigh(mxy)) {

                auto v = state.neigh.mk(v_, mxy);

                if (monster_walkable(state, s, v.first, v.second)) {
                    possible_xy.push_back(v);
                }
            }

            did_possible = true;
        }

        if (possible_xy.empty())
            return false;

        nxy = possible_xy[state.rng.n(possible_xy.size())];
    }

    if (stun) {
        
        if (mxy.first != nxy.first && state.rng.range(0, 2) == 0) {
            nxy.first = mxy.first + mxy.first - nxy.first;
        }

        if (mxy.second != nxy.second && state.rng.range(0, 2) == 0) {
            nxy.second = mxy.second + mxy.second - nxy.second;
        }

        if (!monster_walkable(state, s, nxy.first, nxy.second))
            return false;
    }

    if (!state.grid.is_walk(nxy.first, nxy.second)) {

        if (digging_step(state, nxy.first, nxy.second, s.digging)) {

            state.render.do_message("You hear a loud crashing noise.");

        } else {
            return false;
        }
    }
    
    if (nxy.first == p.px && nxy.second == p.py) {

        if (s.ai == Species::ai_t::suicide) {

            monster_kill(p, state, mxy, m, s, false, std::set<tag_t>());

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

        if (!m.ally.null())
            return false;

        damage::defenses_t defenses;
        p.get_defense(defenses);

        defend(p, defenses, p.get_computed_level(), s, m, state);

        return false;
    }

    if (!s.trail.terrain.null() &&
        state.features.x_set(nxy.first, nxy.second, s.trail.terrain, state.render)) {

        double c = state.rng.gauss(s.trail.cost.mean, s.trail.cost.deviation);

        if (c != 0 && m.stats.sinc(s.trail.stat, c)) {

            do_die = true;
            return true;
        }
    }

    return true;
}


inline bool move_monster(Player& p, GameState& state, 
                         std::vector<summons_t>& summons,
                         const monsters::pt& mxy, monsters::Monster& m, const Species& s,
                         monsters::pt& nxy, bool& do_die) {

    bool moved = move_monster_main(p, state, summons, mxy, m, s, nxy, do_die);

    if (s.flags.stealthy && !moved && !do_die) {

        m.hidden = true;
        state.render.invalidate(mxy.first, mxy.second);
    }
    
    return moved;
}
    

inline int conflict_monster(Player& p, GameState& state, 
                            const monsters::pt& mxya, monsters::Monster& ma, 
                            const monsters::pt& mxyb, monsters::Monster& mb) {

    // 1 means first monster wins and second dies.
    // 2 means second monster wins and first dies.
    // 0 means nobody dies and conflicts are resolved by not moving.

    // No double attacks for monsters!

    if (ma.ally == mb.ally)
        return 0;

    const Species& sa = species().get(ma.tag);
    const Species& sb = species().get(mb.tag);

    if (!ma.did_attack) {

        ma.did_attack = true;
        attack_from_env(p, sa.attacks, sa.get_computed_level(), state, mxyb, mb, false);
    }

    if (!mb.did_attack) {

        mb.did_attack = true;
        attack_from_env(p, sb.attacks, sb.get_computed_level(), state, mxya, ma, false);
    }

    int ret = 0;

    auto do_message = [](GameState& state, const monsters::pt& mxy, const monsters::Monster& m,
                         const Species& s) {

        if (state.render.is_in_fov(mxy.first, mxy.second)) {

            std::string verb = (s.flags.robot || s.flags.plant ? "destroyed" : "killed");

            if (m.ally.null()) {
                state.render.do_message(nlp::message("%S is %s.", s, verb));
            } else {
                state.render.do_message(nlp::message("%S ally is %s!", s, verb));
            }
        }
    };

    if (ma.dead) {

        do_message(state, mxya, ma, sa);

        ret |= 2;
    }

    if (mb.dead) {

        do_message(state, mxyb, mb, sb);

        ret |= 1;
    }

    return ret;
}

#endif
