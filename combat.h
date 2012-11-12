#ifndef __COMBAT_H
#define __COMBAT_H

inline double roll_attack(rnd::Generator& rng, 
                   double ddefense, unsigned int dlevel,
                   double aattack, unsigned int alevel) {

    double a = 0;
    for (unsigned int i = 0; i < alevel; ++i) {
        a += rng.uniform(0.0, aattack);
    }

    double d = 0;
    for (unsigned int i = 0; i < dlevel; ++i) {
        d += rng.uniform(0.0, ddefense);
    }

    std::cout << "** " << ddefense << ":" << dlevel << " <- " << aattack << ":" << alevel 
              << " = " << a << " " << d << std::endl;

    return std::max(a - d, 0.0);
}

inline unsigned int damage_to_sleepturns(double v) {
    int n = (v * 20) - 15;
    return std::max(0, n);
}

inline void roll_attack(rnd::Generator& rng,
                        const damage::defenses_t& defenses, unsigned int dlevel,
                        const damage::attacks_t& attacks, unsigned int alevel,
                        damage::attacks_t& out) {


    for (const auto& v : attacks) {
        double dmg = roll_attack(rng, defenses.get(v.type), dlevel, v.val, alevel);

        if (v.type == damage::type_t::sleep) {
            dmg = damage_to_sleepturns(dmg);
        }

        if (dmg > 0) {
            out.add(damage::val_t{dmg, v.type});
        }
    }
}

inline void monster_kill(Player& p, mainloop::GameState& state, const monsters::Monster& mon, const Species& s) {

    for (const auto& drop : s.drop) {
        double v = state.rng.gauss(0.0, 1.0);

        std::cout << "?? " << v << " " << drop.chance << std::endl;

        if (v <= drop.chance)
            continue;

        state.items.place(mon.xy.first, mon.xy.second, items::Item(drop.tag, mon.xy), state.render);
    }

    if (s.ai == Species::ai_t::none)
        return;

    if (s.level > p.level) {
        p.level = s.level;
        state.render.do_message(nlp::message("You gained level %d!", p.level+1), true);
    }
}


inline bool attack(Player& p, const damage::attacks_t& attacks, unsigned int plevel, 
                   mainloop::GameState& state, const monsters::Monster& mon) {

    const Species& s = species().get(mon.tag);
        
    if (attacks.empty()) {
        state.render.do_message("You can't attack without a weapon!", true);
        return false;
    }

    damage::attacks_t attack_res;
    roll_attack(state.rng, s.defenses, s.level+1, attacks, plevel+1, attack_res);

    if (attack_res.empty()) {

        state.render.do_message(nlp::message("You attack %s but do no damage.", s));
        return true;
    }

    for (const auto& v : attack_res) {

        if (v.type == damage::type_t::sleep) {

            unsigned int sleepturns = v.val;

            state.monsters.change(mon, [sleepturns](monsters::Monster& m) { m.sleep += sleepturns; });
            state.render.do_message(nlp::message("%s falls asleep.", s));
            continue;
        }

        double dmg = v.val;

        state.monsters.change(mon, [dmg](monsters::Monster& m) { m.health -= dmg; });

        if (mon.health - dmg < -3) {

            if (s.ai == Species::ai_t::none) {
                state.render.do_message(nlp::message("You destroyed %s.", s));
            } else {
                state.render.do_message(nlp::message("You killed %s.", s));
            }

            monster_kill(p, state, mon, s);

        } else if (s.ai == Species::ai_t::none) {
            state.render.do_message(nlp::message("You smash %s.", s));

        } else if (dmg < 0.5) {
            state.render.do_message(nlp::message("You hit %s.", s));

        } else if (dmg < 1.0) {
            state.render.do_message(nlp::message("You wound %s.", s));

        } else if (dmg < 2.0) {
            state.render.do_message(nlp::message("You heavily wound %s.", s));

        } else if (dmg < 2.8) {
            state.render.do_message(nlp::message("You critically wound %s.", s));

        } else {
            state.render.do_message(nlp::message("You mortally wound %s.", s));
        }

        std::cout << "     ----    " << dmg << " " << s.level << " " << p.level << std::endl;

        if (s.level == p.level && dmg >= 2.8 && s.ai != Species::ai_t::none) {

            ++p.level;
            state.render.do_message(nlp::message("You gained level %d!", p.level+1), true);
        }
    }

    return true;
}


inline void defend(Player& p, 
                   const damage::defenses_t& defenses, unsigned int plevel, 
                   const damage::attacks_t& attacks, unsigned int alevel, 
                   mainloop::GameState& state, damage::attacks_t& attack_res) {


    if (attacks.empty())
        return;

    roll_attack(state.rng, defenses, plevel+1, attacks, alevel+1, attack_res);

    for (const auto& v : attack_res) {

        if (v.type == damage::type_t::sleep) {
            p.sleep += v.val;

        } else {
            p.health.dec(v.val);
        }
    }
}

inline void defend(Player& p, 
                   const damage::defenses_t& defenses, unsigned int plevel, 
                   const Species& s,
                   mainloop::GameState& state) {


    damage::attacks_t attack_res;
    defend(p, defenses, plevel, s.attacks, s.level, state, attack_res);

    if (attack_res.empty()) {

        state.render.do_message(nlp::message("%s attacks but does no damage.", s));

    } else {

        for (const auto& v : attack_res) {

            if (v.type == damage::type_t::sleep) {
                state.render.do_message(nlp::message("%s casts a sleep charm!", s), true);
            } else {
                state.render.do_message(nlp::message("%s hits!", s));
            }
        }
    }
}


inline void defend(Player& p, 
                   const damage::defenses_t& defenses, unsigned int plevel, 
                   const Terrain& t, 
                   mainloop::GameState& state) {

    damage::attacks_t attack_res;
    defend(p, defenses, plevel, t.attacks, t.attack_level, state, attack_res);

    bool do_sleep = false;
    bool do_hurt = false;
    bool do_pois = false;

    for (const auto& v : attack_res) {

        if (v.type == damage::type_t::sleep) {
            do_sleep = true;

        } else if (v.type == damage::type_t::poison) {
            do_pois = true;

        } else {
            do_hurt = true;
        }
    }

    if (do_hurt) {
        state.render.do_message("Ouch, that hurts.");
    }

    if (do_pois) {
        state.render.do_message("You feel sick.");
    }

    if (do_sleep) {
        state.render.do_message("You fall asleep.");
    }
}


#endif
