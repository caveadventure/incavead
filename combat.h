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

    return std::max(a - d, 0.0);
}

inline unsigned int damage_to_sleepturns(double v) {
    int n = (v * 20) - 15;
    return std::max(0, n);
}

inline unsigned int damage_to_scareturns(double v) {
    int n = (v * 30) - 20;
    return std::max(0, n);
}

inline void roll_attack(rnd::Generator& rng,
                        const damage::defenses_t& defenses, unsigned int dlevel,
                        const damage::attacks_t& attacks, unsigned int alevel,
                        damage::attacks_t& out) {


    for (const auto& v : attacks) {
        double dmg = roll_attack(rng, defenses.get(v.type), dlevel, v.val, alevel);

        std::cout << "ROLL " << (int)v.type << " : " << defenses.get(v.type) << " vs " << v.val << std::endl;

        if (v.type == damage::type_t::sleep) {
            dmg = damage_to_sleepturns(dmg);

        } else if (v.type == damage::type_t::scare_animal) {
            dmg = damage_to_scareturns(dmg);
        }

        if (dmg > 0) {
            out.add(damage::val_t{dmg, v.type});
        }
    }
}

inline void monster_kill(Player& p, mainloop::GameState& state, const monsters::Monster& mon, const Species& s) {

    for (const auto& drop : s.drop) {
        double v = state.rng.gauss(0.0, 1.0);

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
                   mainloop::GameState& state, const monsters::Monster& mon, bool quiet = false) {

    const Species& s = species().get(mon.tag);
        
    if (attacks.empty()) {
        state.render.do_message("You can't attack without a weapon!", true);
        return false;
    }

    damage::attacks_t attack_res;
    roll_attack(state.rng, s.defenses, s.level+1, attacks, plevel+1, attack_res);

    if (attack_res.empty()) {

        if (!quiet)
            state.render.do_message(nlp::message("You attack %s but do no damage.", s));

        return true;
    }

    double totdamage = 0.0;
    double totmagic = 0.0;
    double totsleep = 0.0;
    double totfear = 0.0;
    bool mortal = false;

    for (const auto& v : attack_res) {

        double dmg = v.val;

        if (v.type == damage::type_t::sleep) {

            state.monsters.change(mon, [dmg](monsters::Monster& m) { m.sleep += dmg; });
            totsleep += dmg;

        } else if (v.type == damage::type_t::turn_undead) {

            if (s.flags.undead) {
                state.monsters.change(mon, [dmg](monsters::Monster& m) { m.health -= dmg; });
                totdamage += dmg;
            }

        } else if (v.type == damage::type_t::scare_animal) {

            if (s.flags.animal) {
                state.monsters.change(mon, [dmg](monsters::Monster& m) { m.fear += dmg; });
                totfear += dmg;
            }

        } else if (v.type == damage::type_t::cancellation) {

            if (s.flags.magic) {
                state.monsters.change(mon, [dmg](monsters::Monster& m) { m.magic -= dmg; });
                totmagic += dmg;
            }

        } else {

            std::cout << "HIT: " << (int)v.type << " : " <<mon.health << " " << dmg << std::endl;

            state.monsters.change(mon, [dmg](monsters::Monster& m) { m.health -= dmg; });
            totdamage += dmg;

            if (dmg >= 2.8) {
                mortal = true;
            }
        }
    }

    std::cout << "karma " << s.karma << " " << totdamage << std::endl;
    p.karma.inc(s.karma * totdamage);

    if (totsleep > 0) {

        state.render.do_message(nlp::message("%s falls asleep.", s));

    } else if (totfear > 0) {

        state.render.do_message(nlp::message("%s flees in terror.", s));
    }

    if (mon.health - totdamage < -3) {

        if (s.ai == Species::ai_t::none) {
            state.render.do_message(nlp::message("You destroyed %s.", s));
        } else {
            state.render.do_message(nlp::message("You killed %s.", s));
        }

        monster_kill(p, state, mon, s);

    } else if (!quiet) {

        if (s.ai == Species::ai_t::none) {
            state.render.do_message(nlp::message("You smash %s.", s));

        } else if (totdamage < 0.5) {
            state.render.do_message(nlp::message("You hit %s.", s));

        } else if (totdamage < 1.0) {
            state.render.do_message(nlp::message("You wound %s.", s));

        } else if (totdamage < 2.0) {
            state.render.do_message(nlp::message("You heavily wound %s.", s));

        } else if (totdamage < 2.8) {
            state.render.do_message(nlp::message("You critically wound %s.", s));

        } else {
            state.render.do_message(nlp::message("You mortally wound %s.", s));
        }
    }

    if (totmagic > 0.5) {

        if (mon.magic - totmagic < -3) {
            state.render.do_message(nlp::message("%s is magically cancelled.", s));

        } else {
            state.render.do_message(nlp::message("%s is showered in sparkles.", s));
        }
    }

    if (s.level == p.level && mortal && s.ai != Species::ai_t::none) {

        ++p.level;
        state.render.do_message(nlp::message("You gained level %d!", p.level+1), true);
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

        } else if (v.type == damage::type_t::physical || v.type == damage::type_t::poison) {

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

            } else if (v.type == damage::type_t::physical || v.type == damage::type_t::poison) {
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

        } else if (v.type == damage::type_t::physical || v.type == damage::type_t::poison) {
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



inline void defend(Player& p, 
                   const damage::defenses_t& defenses, unsigned int plevel, 
                   const Design& d, 
                   mainloop::GameState& state) {

    damage::attacks_t attack_res;
    defend(p, defenses, plevel, d.attacks, d.level, state, attack_res);

    bool do_sleep = false;
    bool do_hurt = false;
    bool do_pois = false;

    for (const auto& v : attack_res) {

        if (v.type == damage::type_t::sleep) {
            do_sleep = true;

        } else if (v.type == damage::type_t::poison) {
            do_pois = true;

        } else if (v.type == damage::type_t::physical || v.type == damage::type_t::poison) {
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
