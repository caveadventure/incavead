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

inline bool attack(Player& p, double attack, unsigned int plevel, 
                   mainloop::GameState& state, const monsters::Monster& mon) {

    const Species& s = species().get(mon.tag);
        
    if (attack == 0) {
        state.render.do_message("You can't attack without a weapon!", true);
        return false;
    }

    double v = roll_attack(state.rng,
                           s.defense, s.level+1, attack, plevel+1);

    if (v > 0) {

        state.monsters.change(mon, [v](monsters::Monster& m) { m.health -= v; });

        if (mon.health - v < -3) {

            if (s.ai == Species::ai_t::none) {
                state.render.do_message(nlp::message("You destroyed %s.", s));
            } else {
                state.render.do_message(nlp::message("You killed %s.", s));
            }

            monster_kill(p, state, mon, s);

        } else if (s.ai == Species::ai_t::none) {
            state.render.do_message(nlp::message("You smash %s.", s));

        } else if (v < 0.5) {
            state.render.do_message(nlp::message("You hit %s.", s));

        } else if (v < 1.0) {
            state.render.do_message(nlp::message("You wound %s.", s));

        } else if (v < 2.0) {
            state.render.do_message(nlp::message("You heavily wound %s.", s));

        } else if (v < 2.8) {
            state.render.do_message(nlp::message("You critically wound %s.", s));

        } else {
            state.render.do_message(nlp::message("You mortally wound %s.", s));
        }

        std::cout << "     ----    " << v << " " << s.level << " " << p.level << std::endl;

        if (s.level == p.level && v >= 2.8 && s.ai != Species::ai_t::none) {

            ++p.level;
            state.render.do_message(nlp::message("You gained level %d!", p.level+1), true);
        }

    } else {
        state.render.do_message(nlp::message("You attack %s but do no damage.", s));
    }

    return true;
}

inline void defend(Player& p, double defense, unsigned int plevel, 
                   mainloop::GameState& state, const monsters::Monster& mon, const Species& s) {

    if (s.attack > 0) {

        double v = roll_attack(state.rng, 
                               defense, plevel+1, s.attack, s.level+1);

        if (v > 0) {
            p.health.dec(v);

            state.render.do_message(nlp::message("%s hits!", s));
        } else {
            state.render.do_message(nlp::message("%s attacks but does no damage.", s));
        }
    }

    if (s.sleepattack > 0) {

        double v = roll_attack(state.rng, 
                               defense, plevel+1, s.sleepattack, s.level+1);

        int n = (v * 20) - 15;

        if (n > 0) {

            p.sleep += n;
            state.render.do_message(nlp::message("%s casts a sleep charm!", s), true);
        }
    }
}

#endif
