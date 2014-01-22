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

template <typename PARAM>
inline unsigned int damage_to_turns(double v, const PARAM& p) {
    int n = (v * p.scale) - p.offset;
    return std::max(0, n);
}

inline void roll_attack(rnd::Generator& rng,
                        const damage::defenses_t& defenses, unsigned int dlevel,
                        const damage::attacks_t& attacks, unsigned int alevel,
                        damage::attacks_t& out) {


    for (const auto& v : attacks) {
        double dmg = roll_attack(rng, defenses.get(v.type), dlevel, v.val, alevel);

        if (v.type == damage::type_t::sleep) {
            dmg = damage_to_turns(dmg, constants().damage_to_sleepturns);

        } else if (v.type == damage::type_t::scare_animal ||
                   v.type == damage::type_t::scare) {
            dmg = damage_to_turns(dmg, constants().damage_to_scareturns);

        } else if (v.type == damage::type_t::blindness) {
            dmg = damage_to_turns(dmg, constants().damage_to_blindturns);
        }

        if (dmg > 0) {
            out.add(damage::val_t{dmg, v.type});
        }
    }
}

inline void monster_kill(Player& p, GameState& state, const monsters::Monster& mon, 
                         const Species& s, bool do_track) {

    for (const auto& drop : s.drop) {
        double v = state.rng.gauss(0.0, 1.0);

        if (v <= drop.chance)
            continue;

        tag_t item = drop.tag;

        if (item.null()) {

            auto is = state.designs_counts.take(state.rng, drop.level);

            if (is.size() > 0) {
                item = is.begin()->first;
            }
        }

        if (!item.null()) {
            items::Item idrop = state.items.make_item(item, mon.xy, state.rng);
            state.items.place(mon.xy.first, mon.xy.second, idrop, state.render);
        }
    }

    if (do_track && !s.genus.null()) {
        p.track_kill(s.genus, state);
    }
}


inline void attack_damage_monster(const damage::val_t& v, const monsters::Monster& mon, const Species& s,
                                  Player& p, GameState& state,
                                  double& totdamage, double& totmagic, 
                                  double& totsleep, double& totfear, double& totvamp, 
                                  bool& mortal) {

    double dmg = v.val;
    double hurt = 0;

    if (v.type == damage::type_t::sleep) {

        state.monsters.change(mon, [dmg](monsters::Monster& m) { m.sleep += dmg; });
        totsleep += dmg;

    } else if (v.type == damage::type_t::blindness) {

        if (!s.flags.eyeless) {
            state.monsters.change(mon, [dmg](monsters::Monster& m) { m.blind += dmg; });
        }

    } else if (v.type == damage::type_t::turn_undead) {

        if (s.flags.undead) {
            hurt = dmg;
        }

    } else if (v.type == damage::type_t::scare_animal) {

        if (s.flags.animal) {
            state.monsters.change(mon, [dmg](monsters::Monster& m) { m.fear += dmg; });
            totfear += dmg;
        }

    } else if (v.type == damage::type_t::scare) {

        if (!s.flags.undead && !s.flags.plant) {
            state.monsters.change(mon, [dmg](monsters::Monster& m) { m.fear += dmg; });
            totfear += dmg;
        }
        
    } else if (v.type == damage::type_t::cancellation) {

        if (s.flags.magic) {
            state.monsters.change(mon, [dmg](monsters::Monster& m) { m.magic -= dmg; });
            totmagic += dmg;
        }

    } else if (v.type == damage::type_t::make_meat) {

        //
        if (dmg > 0.5 && !s.flags.robot) {
            if (s.karma < 0 || s.flags.undead) {
                state.monsters.change(mon, [dmg](monsters::Monster& m) { m.tag = constants().bad_meat; });
            } else {
                state.monsters.change(mon, [dmg](monsters::Monster& m) { m.tag = constants().meat; });
            }

            state.render.invalidate(mon.xy.first, mon.xy.second);
        }

    } else if (v.type == damage::type_t::vampiric) {

        if (!s.flags.robot && !s.flags.undead && !s.flags.plant) {

            p.health.inc(dmg);
            totvamp += dmg;

            hurt = dmg;
        }

    } else if (v.type == damage::type_t::heavenly_fire || v.type == damage::type_t::hellish_fire) {

        double fac = (v.type == damage::type_t::hellish_fire ? -1 : 1);
        double karma = s.karma * fac;

        if (karma > 0) {
            double factor = (karma)/2;
            factor = factor * factor;

            hurt = dmg * factor;
        }

    } else if (v.type == damage::type_t::sonic) {

        if (s.flags.robot) {
            hurt = dmg;
        }

    } else if (v.type == damage::type_t::poison ||
               v.type == damage::type_t::psi ||
               v.type == damage::type_t::eat_brain ||
               v.type == damage::type_t::drain) {

        if (!s.flags.robot && !s.flags.plant) {
            hurt = dmg;
        }

    } else if (v.type == damage::type_t::hunger || v.type == damage::type_t::unluck) {
        // Monsters don't feel hunger and don't have luck.

    } else {
        // physical
        // electric
        // magic
        
        hurt = dmg;
    }

    if (hurt > 0) {
        state.monsters.change(mon, [hurt](monsters::Monster& m) { m.health -= hurt; });
        totdamage += hurt;

        if (hurt >= 2.8) {
            mortal = true;
        }
    }
}


inline void attack_from_env(Player& p, const damage::attacks_t& attacks, unsigned int plevel,
                            GameState& state, const monsters::Monster& mon,
                            bool track_kills) {

    if (attacks.empty()) {
        return;
    }

    const Species& s = species().get(mon.tag);

    damage::attacks_t attack_res;
    roll_attack(state.rng, s.defenses, s.get_computed_level()+1, attacks, plevel+1, attack_res);

    if (attack_res.empty()) {
        return;
    }

    double totdamage = 0.0;
    double totmagic = 0.0;
    double totsleep = 0.0;
    double totfear = 0.0;
    double totvamp = 0.0;
    bool mortal = false;

    for (const auto& v : attack_res) {

        attack_damage_monster(v, mon, s, p, state, totdamage, totmagic, totsleep, totfear, totvamp, mortal);
    }

    if (mon.health - totdamage < -3) {

        monster_kill(p, state, mon, s, track_kills);
    }
}


inline bool attack_from_player(Player& p, const damage::attacks_t& attacks, unsigned int plevel, 
                               GameState& state, const monsters::Monster& mon, 
                               bool quiet) {

    const Species& s = species().get(mon.tag);

    unsigned int species_level = s.get_computed_level();

    std::cout << "ATTACK: " << plevel << " ( " << species_level << ") " << std::endl;
        
    if (attacks.empty()) {
        state.render.do_message("You can't attack without a weapon!", true);
        return false;
    }

    damage::attacks_t attack_res;
    roll_attack(state.rng, s.defenses, s.get_computed_level()+1, attacks, plevel+1, attack_res);

    if (attack_res.empty()) {

        if (!quiet)
            state.render.do_message(nlp::message("You attack %s but do no damage.", s));

        return true;
    }

    double totdamage = 0.0;
    double totmagic = 0.0;
    double totsleep = 0.0;
    double totfear = 0.0;
    double totvamp = 0.0;
    bool mortal = false;

    for (const auto& v : attack_res) {

        attack_damage_monster(v, mon, s, p, state, totdamage, totmagic, totsleep, totfear, totvamp, mortal);
    }

    p.karma.inc(s.karma * totdamage);

    if (totsleep > 0) {

        state.render.do_message(nlp::message("%s falls asleep.", s));

    } else if (totfear > 0) {

        state.render.do_message(nlp::message("%s flees in terror.", s));
    }

    if (mon.health - totdamage < -3) {

        if (s.flags.plant || s.flags.robot) {
            state.render.do_message(nlp::message("You destroyed %s.", s));
        } else {
            state.render.do_message(nlp::message("You killed %s.", s));
        }

        monster_kill(p, state, mon, s, true);

        if (!s.flags.plant && species_level > p.level) {

            p.level = species_level;

            // Don't gain a level twice.
            mortal = false;
            
            state.render.do_message(nlp::message("You gained level %d!", p.level+1), true);
        }

    } else if (!quiet) {

        if (s.flags.plant || s.flags.robot) {
            state.render.do_message(nlp::message("You smash %s.", s));

        } else if (totdamage < 0.1) {
            state.render.do_message(nlp::message("You almost miss %s.", s));

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

    if (species_level >= p.level && mortal && !s.flags.plant) {

        p.level = species_level+1;
        state.render.do_message(nlp::message("You gained level %d!", p.level+1), true);
    }

    return true;
}


inline void handle_post_defend(Player& p, GameState& state) {

    if (p.digging) {
        state.render.do_message("You stop digging.");
        p.digging = false;
    }
}


inline void defend(Player& p, 
                   const damage::defenses_t& defenses, unsigned int plevel, 
                   const damage::attacks_t& attacks, unsigned int alevel, 
                   GameState& state, damage::attacks_t& attack_res) {

    if (attacks.empty())
        return;

    roll_attack(state.rng, defenses, plevel+1, attacks, alevel+1, attack_res);

    for (const auto& v : attack_res) {

        if (v.type == damage::type_t::sleep) {
            p.sleep += v.val;

        } else if (v.type == damage::type_t::blindness) {
            p.blind += v.val;

        } else if (v.type == damage::type_t::make_meat) {

            if (v.val > 0.5) {
                p.health.dec(6.0);
            }

        } else if (v.type == damage::type_t::heavenly_fire || v.type == damage::type_t::hellish_fire) {

            double fac = (v.type == damage::type_t::hellish_fire ? -1 : 1);
            double karma = p.karma.val * fac;

            if (karma < 0) {
                double factor = (-karma)/2;
                factor = factor * factor;

                p.health.dec(v.val * factor);
            }

        } else if (v.type == damage::type_t::hunger) {
            p.food.dec(v.val);

        } else if (v.type == damage::type_t::unluck) {
            p.luck.dec(v.val);

        } else if (v.type == damage::type_t::physical || 
                   v.type == damage::type_t::poison ||
                   v.type == damage::type_t::psi ||
                   v.type == damage::type_t::eat_brain ||
                   v.type == damage::type_t::drain ||
                   v.type == damage::type_t::vampiric ||
                   v.type == damage::type_t::electric ||
                   v.type == damage::type_t::magic) {

            // No sonic damage for the player.

            p.health.dec(v.val);
        }
    }
}

inline double defend(Player& p, 
                     const damage::defenses_t& defenses, unsigned int plevel, 
                     const Species& s, const damage::attacks_t& attacks,
                     GameState& state) {


    double vamp = 0;

    damage::attacks_t attack_res;
    defend(p, defenses, plevel, attacks, s.get_computed_level(), state, attack_res);

    if (attack_res.empty()) {

        state.render.do_message(nlp::message("%s attacks but does no damage.", s));

    } else {

        p.attacker = s.name;

        for (const auto& v : attack_res) {

            if (v.type == damage::type_t::sleep) {
                state.render.do_message(nlp::message("%s casts a sleep charm!", s), true);

            } else if (v.type == damage::type_t::blindness) {
                state.render.do_message(nlp::message("%s blinds you!", s));

            } else if (v.type == damage::type_t::psi) {
                state.render.do_message(nlp::message("%s is destroying your mind!", s));

            } else if (v.type == damage::type_t::make_meat) {

                if (v.val > 0.5)
                    state.render.do_message("You feel yourself turning into a slab of brainless meat!", true);

            } else if (v.type == damage::type_t::eat_brain) {
                state.render.do_message(nlp::message("%s is eating your brain!", s));

            } else if (v.type == damage::type_t::drain) {
                state.render.do_message(nlp::message("%s is draining your vital forces!", s));

            } else if (v.type == damage::type_t::electric) {
                state.render.do_message(nlp::message("%s shocks you with lightning!", s));

            } else if (v.type == damage::type_t::heavenly_fire) {

                if (p.karma.val < 0)
                    state.render.do_message(nlp::message("%s blasts you with heavenly fire.", s));

            } else if (v.type == damage::type_t::hellish_fire) {

                if (p.karma.val > 0)
                    state.render.do_message(nlp::message("%s blasts you with hellfire.", s));

            } else if (v.type == damage::type_t::hunger) {
                state.render.do_message(nlp::message("%s casts a hunger charm.", s));

            } else if (v.type == damage::type_t::unluck) {
                state.render.do_message(nlp::message("%s casts the evil eye.", s));

            } else if (v.type == damage::type_t::vampiric) {

                vamp += v.val;
                state.render.do_message(nlp::message("%s is sucking your blood.", s));

            } else if (v.type == damage::type_t::physical || 
                       v.type == damage::type_t::poison ||
                       v.type == damage::type_t::magic) {

                state.render.do_message(nlp::message("%s hits!", s));
            }
        }

        handle_post_defend(p, state);
    }

    return vamp;
}

inline double defend(Player& p, 
                     const damage::defenses_t& defenses, unsigned int plevel, 
                     const Species& s,
                     GameState& state) {

    return defend(p, defenses, plevel, s, s.attacks, state);
}


inline bool defend_env_message(Player& p, GameState& state, const damage::attacks_t& attack_res) {

    bool ret = true;

    std::set<damage::type_t> damages;

    for (const auto& v : attack_res) {

        if ((v.type == damage::type_t::make_meat && v.val <= 0.5) ||
            (v.type == damage::type_t::heavenly_fire && p.karma.val >= 0) ||
            (v.type == damage::type_t::hellish_fire && p.karma.val <= 0)) {

            continue;
        }

        damages.insert(v.type);
    }

    for (const auto& v : damages) {
        switch (v) {

        case damage::type_t::sleep:
            state.render.do_message("You fall asleep.");
            break;

        case damage::type_t::blindness:
            state.render.do_message("You feel your eyesight fail you!");
            ret = false;
            break;

        case damage::type_t::poison:
            state.render.do_message("You feel sick.");
            break;

        case damage::type_t::psi:
            state.render.do_message("You feel a cosmic existential madness.");
            break;

        case damage::type_t::make_meat:
            state.render.do_message("You feel yourself turning into a slab of brainless meat!", true);
            break;

        case damage::type_t::heavenly_fire:
            state.render.do_message("You are blasted with heavenly fire.");
            break;

        case damage::type_t::hellish_fire:
            state.render.do_message("You are blasted with hellfire.");
            break;

        case damage::type_t::hunger:
            state.render.do_message("You feel an unnatural hunger.");
            ret = false;
            break;

        case damage::type_t::unluck:
            state.render.do_message("You feel unlucky.");
            ret = false;
            break;

        case damage::type_t::physical:
        case damage::type_t::eat_brain:
        case damage::type_t::drain:
        case damage::type_t::vampiric:
        case damage::type_t::electric:
        case damage::type_t::magic:
            state.render.do_message("Ouch, that hurts.");
            break;

        default:
            break;
        }
    }

    return ret;
}

inline void defend(Player& p, 
                   const damage::defenses_t& defenses, unsigned int plevel, 
                   const Terrain& t, 
                   GameState& state) {

    damage::attacks_t attack_res;
    defend(p, defenses, plevel, t.attacks, t.attack_level, state, attack_res);

    p.attacker = t.name;

    defend_env_message(p, state, attack_res);

    if (!attack_res.empty()) {
        handle_post_defend(p, state);
    }
}

inline void defend(Player& p, 
                   const damage::defenses_t& defenses, unsigned int plevel, 
                   const Design& d, 
                   GameState& state) {

    damage::attacks_t attack_res;
    defend(p, defenses, plevel, d.attacks, d.level, state, attack_res);

    p.attacker = d.name;

    defend_env_message(p, state, attack_res);

    if (!attack_res.empty()) {
        handle_post_defend(p, state);
    }
}

inline void defend(Player& p, const ConstantsBank::ailment_t& ailment, GameState& state) {

    damage::defenses_t defenses;
    p.inv.get_defense(defenses);

    damage::attacks_t attack_res;
    defend(p, defenses, p.get_computed_level(state.rng), ailment.attacks, ailment.level, state, attack_res);

    p.attacker = ailment.name;

    bool stop = defend_env_message(p, state, attack_res);

    if (!attack_res.empty() && stop) {
        handle_post_defend(p, state);
    }
}


#endif
