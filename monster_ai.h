#ifndef __MONSTER_AI_H
#define __MONSTER_AI_H


// HACK
struct summons_t {
    unsigned int x;
    unsigned int y;
    tag_t summontag;
    unsigned int arg;
    tag_t summonertag;
    tag_t ally;
    std::string msg;

    summons_t() : x(0), y(0), arg(0) {}

    summons_t(unsigned int _x, unsigned int _y, tag_t _st, unsigned int _a, tag_t _sut, tag_t _al, 
              const std::string& _m) : x(_x), y(_y), summontag(_st), arg(_a), 
                                       summonertag(_sut), ally(_al), msg(_m) {}
};


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

inline void monster_blast_process_point(Player& p, GameState& state, const Species& s,
                                        unsigned int _x, unsigned int _y, const damage::attacks_t& attacks,
                                        bool friendly_fire) {

    if (_x == p.px && _y == p.py) {

        damage::defenses_t defenses;
        p.get_defense(defenses);

        defend(p, defenses, p.get_computed_level(state.rng), s, attacks, state, friendly_fire);

    } else {

        monsters::Monster& mon = state.monsters.get(_x, _y);

        if (!mon.null()) {

            attack_from_env(p, attacks, s.get_computed_level(), state, monsters::pt(_x, _y), mon, friendly_fire);
        }
    }
}

inline void do_monster_blast(Player& p, GameState& state, const Species& s, 
                             unsigned int tx, unsigned int ty, unsigned int rad, 
                             const damage::attacks_t& attacks, bool friendly_fire = false) {

    if (rad == 0) {

        monster_blast_process_point(p, state, s, tx, ty, attacks, friendly_fire);

    } else {

        state.render.draw_circle(tx, ty, rad, s.skin.a.fore, maudit::color::bright_black,
                                 [&](unsigned int _x, unsigned int _y) {
                                 
                                     monster_blast_process_point(p, state, s, _x, _y, attacks, friendly_fire);
                                 });
    }
}


inline bool do_monster_magic(Player& p, GameState& state, std::vector<summons_t>& summons, 
                             const monsters::pt& target, unsigned int dist2, bool is_player, tag_t ally,
                             const monsters::pt& mxy, monsters::Monster& m, const Species& s) {

    std::cout << " magic: " << dist2 << " " << is_player << " " << ally.null() << std::endl;
    std::cout << "  " << s.summon.size() << std::endl;

    if (s.summon.size() > 0) {

        for (const auto& c : s.summon) {

            if ((state.ticks & c.turns) != 0) continue;

            double v = state.rng.gauss(0.0, 1.0);
            if (v <= c.chance) continue;

            std::cout << "  Summoned!" << std::endl;

            summons.emplace_back(mxy.first, mxy.second, c.speciestag, 1, m.tag, m.ally, c.msg);
        }
    }

    if (s.spawns.size() > 0) {

        for (const auto& c : s.spawns) {

            if ((state.ticks & c.turns) != 0) continue;

            double v = state.rng.gauss(0.0, 1.0);
            if (v <= c.chance) continue;

            summons.emplace_back(mxy.first, mxy.second, tag_t(), c.level, m.tag, m.ally, c.msg);
        }        
    }

    if ((is_player && !m.ally.null()) || (!is_player && ally == m.ally))
        return false;

    std::cout << "  Doing other stuff" << std::endl;

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

        do_monster_blast(p, state, s, target.first, target.second, b.radius, b.attacks);
        return true;
    }

    for (const auto& c : s.cast_cloud) {

        if ((state.ticks % c.turns) != 0) continue;
                    
        double v = state.rng.gauss(0.0, 1.0);
        if (v <= c.chance) continue;

        std::cout << "  Casting cloud" << std::endl;

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

}

inline bool move_monster(Player& p, GameState& state, 
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


    if (m.health <= -3) {

        if (!s.death_summon.null()) {
            summons.emplace_back(mxy.first, mxy.second, s.death_summon, 1, m.tag, m.ally, "");
        }

        do_die = true;
        return true;
    }

    if (do_stop) {
        return false;
    }

    monsters::pt target(p.px, p.py);

    if (m.sleep > 0) {
        --(m.sleep);
        return false;
    }

    if (m.stun > 0) {
        --(m.stun);
    }

    if (m.fear > 0) {
        --(m.fear);

        if (m.target == mxy) {

            if (!make_monster_run(state, p.px, p.py, mxy, m, s))
                return false;
        }

        target = m.target;
    }

    if (m.blind > 0) {
        range = std::max(0, (int)range - static_cast<int>(m.blind / constants().blindturns_to_radius) - 1);

        --(m.blind);
    }


    bool do_random = false;

    unsigned int maxd2 = (range + 1) * (range + 1);

    auto nearest = state.monsters.nearest.get(mxy.first, mxy.second, maxd2);

    if (nearest.empty()) {

        // Short-path AI for out-of-range monsters.
        if (s.idle_ai == Species::idle_ai_t::random) {

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

            std::cout << ": " << s.name << " " << (int)s.ai << " " << maxd2 << " " << nearest.size() << " / " 
                      << pow2((int)mxy.first - (int)p.px) + pow2((int)mxy.second - (int)p.py) << std::endl;

            std::vector<monsters::pt> possible_xy;

            if (s.ai != Species::ai_t::magic && s.ai != Species::ai_t::magic_awake) {

                for (const neighbors::pt& v_ : state.neigh(mxy)) {

                    auto v = state.neigh.mk(v_, mxy);

                    if (!monster_walkable(state, s, v.first, v.second))
                        continue;

                    possible_xy.push_back(v);
                }
            }


            for (const auto& i : nearest) {

                const monsters::Monster& other = state.monsters.get(i.x, i.y);

                bool is_player = (i.x == p.px && i.y == p.py);

                std::cout << "  --- " << (is_player ? std::string("(player)") : species().get(other.tag).name)
                          << std::endl;

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

                std::cout << "  --| " << thispri << "," << d2 << " " << pri << "," << maxd2 << std::endl;

                if (thispri < pri)
                    continue;

                bool enemy_sleeping = (is_player ? p.sleep > 0 : other.sleep > 0);

                if (enemy_sleeping && (s.ai == Species::ai_t::magic_awake || s.ai == Species::ai_t::seek_awake))
                    continue;

                
                unsigned int tmpnn = 0;
                monsters::pt bxy;

                bool ok = reachable(state, mxy.first, mxy.second, i.x, i.y, 
                                    [&tmpnn,&bxy](GameState& state, unsigned int x, unsigned int y) {

                                        if (!player_walkable(state, x, y))
                                            return false;

                                        ++tmpnn;

                                        if (tmpnn == 2) 
                                            bxy = monsters::pt(x, y);

                                        return true;
                                    });

                if (!ok)
                    continue;

                std::cout << "   (ok)" << std::endl;

                if (thispri == pri && d2 >= maxd2)
                    continue;

                pri = thispri;
                maxd2 = d2;
                beeline_xy = bxy;
                target = monsters::pt(i.x, i.y);
                enemy_is_player = is_player;
                enemy_ally = (is_player ? tag_t() : other.ally);

                std::cout << "  (yeah!)" << std::endl;
            }

            if (pri < 0) {

                if (s.ai == Species::ai_t::magic || s.ai == Species::ai_t::magic_awake) {

                    return false;

                } else {

                    do_random = true;
                }

            } else {

                // We found a target.

                std::cout << ":: " << s.name << " " << (int)s.ai << " " << m.magic << std::endl;

                if (m.magic > -3.0 &&
                    do_monster_magic(p, state, summons, target, maxd2, enemy_is_player, enemy_ally, mxy, m, s)) {
 
                    return false;
                }

                if (possible_xy.empty())
                    return false;

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

                // OK! If we got here, then 'nxy' holds a valid move and the monster
                // is actually doing something intelligent.
            }
        }
    }


    if (do_random) {
        std::vector<monsters::pt> tmp;

        for (const neighbors::pt& v_ : state.neigh(mxy)) {

            auto v = state.neigh.mk(v_, mxy);

            if (monster_walkable(state, s, v.first, v.second)) {
                tmp.push_back(v);
            }
        }

        if (tmp.empty())
            return false;

        nxy = tmp[state.rng.n(tmp.size())];
    }

    if (m.stun > 0) {
        
        if (mxy.first != nxy.first && state.rng.range(0, 2) == 0) {
            nxy.first = mxy.first + mxy.first - nxy.first;
        }

        if (mxy.second != nxy.second && state.rng.range(0, 2) == 0) {
            nxy.second = mxy.second + mxy.second - nxy.second;
        }

        if (!monster_walkable(state, s, nxy.first, nxy.second))
            return false;
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

        double vamp = defend(p, defenses, p.get_computed_level(state.rng), s, state);

        if (vamp != 0) {

            if (m.health + vamp <= -3.0) {
                do_die = true;
                return true;
            }
            
            m.health += vamp; 
            m.health = std::min(3.0, m.health);
        }

        return false;
    }

    if (!s.trail.terrain.null() &&
        state.features.x_set(nxy.first, nxy.second, s.trail.terrain, state.render)) {

        double c = state.rng.gauss(s.trail.cost.mean, s.trail.cost.deviation);

        if (c != 0) {
            m.health -= c;
        }
    }

    return true;
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

    if (ma.health <= -3) {

        do_message(state, mxya, ma, sa);

        ret |= 2;
    }

    if (mb.health <= -3) {

        do_message(state, mxyb, mb, sb);

        ret |= 1;
    }

    return ret;
}

#endif
