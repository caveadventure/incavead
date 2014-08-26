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

inline void karmic_damage_scale(bool positive, double karma, double penance, double& dmg) {

    double kk = karma;

    if (!positive) {
        kk = -kk;
    }

    kk = std::min(kk, -penance);

    if (kk < 0) {
        double factor = (kk)/2;
        factor = factor * factor;

        dmg *= factor;

    } else {
        dmg = 0;
    }
}


inline void roll_attack(rnd::Generator& rng,
                        const damage::defenses_t& defenses, unsigned int dlevel,
                        const damage::attacks_t& attacks, unsigned int alevel,
                        damage::attacks_t& out) {


    for (const auto& v : attacks) {
        double dmg = roll_attack(rng, defenses.get(v.type), dlevel, v.val, alevel);

        if (dmg > 0) {
            out.add(damage::val_t{dmg, v.type});
        }
    }
}


inline void monster_kill(Player& p, GameState& state, const monsters::pt& mxy, monsters::Monster& mon, 
                         const Species& s, bool do_track, const std::set<tag_t>& types) {

    for (const auto& drop : s.drop) {
        double v = state.rng.gauss(0.0, 1.0);

        if (v <= drop.chance)
            continue;

        if (!drop.damage_type.null() && types.count(drop.damage_type) == 0) 
            continue;

        tag_t item = drop.tag;

        if (item.null()) {

            auto is = state.designs_counts.take(state.rng, drop.level);

            if (is.size() > 0) {
                item = is.begin()->first;
            }
        }

        if (!item.null()) {
            items::Item idrop = state.items.make_item(item, mxy, state.rng);
            state.items.place(mxy.first, mxy.second, idrop, state.render);
        }
    }

    if (do_track && !s.genus.null()) {
        p.track_kill(s.genus, state);
    }
}


inline void attack_damage_monster(const damage::val_t& v, 
                                  const monsters::pt& mxy, monsters::Monster& mon, const Species& s,
                                  Player& p, GameState& state,
                                  double& totdamage, double& totmagic, double& totsleep, double& totstun, 
                                  double& totfear, double& totblind, double& totpoly,
                                  std::set<tag_t>& types,
                                  bool& mortal) {

    double dmg = v.val;

    const Damage& dam = damages().get(v.type);

    if (!dam.flags.robot(s.flags.robot) || 
        !dam.flags.undead(s.flags.undead) ||
        !dam.flags.animal(s.flags.animal) ||
        !dam.flags.plant(s.flags.plant) ||
        !dam.flags.magic(s.flags.magic) ||
        !dam.flags.eyeless(s.flags.eyeless) ||
        !dam.flags.player(false)) 
        return;

    if (dam.heavenly) {

        karmic_damage_scale(true, -s.karma, 0, dmg);

    } else if (dam.hellish) {

        karmic_damage_scale(false, -s.karma, 0, dmg);
    }

    if (dmg <= dam.threshold)
        return;

    unsigned int sleepturns = dam.sleepturns(dmg);
    unsigned int stunturns = dam.stunturns(dmg);
    unsigned int fearturns = dam.fearturns(dmg);
    unsigned int blindturns = dam.blindturns(dmg);
    unsigned int polyturns = dam.player_poly(dmg);

    if (sleepturns > 0) {
        mon.sleep += sleepturns;
        totsleep += sleepturns;
    }

    if (blindturns > 0) {
        mon.blind += blindturns;
        totblind += blindturns;
    }

    if (stunturns > 0) {
        mon.stun += stunturns;
        totstun += stunturns;
    }

    if (fearturns > 0) {
        mon.fear += fearturns;
        totfear += fearturns;

        make_monster_run(state, p.px, p.py, mon, s);
    }

    if (polyturns > 0) {

        p.polymorph.species = mon.tag;
        p.polymorph.turns = polyturns;
        p.sleep = mon.sleep;
        p.blind = mon.blind;
        p.health.val = mon.health;

        state.render.invalidate(p.px, p.py);

        totpoly += polyturns;
    }

    if (dam.cancellation) {
        mon.magic -= dmg;
        totmagic += dmg;
    }

    if (!dam.polymorph.first.null()) {

        //
        auto tmp = dam.polymorph;

        if (s.karma < 0 || s.flags.undead) {
            mon.tag = tmp.second;
        } else {
            mon.tag = tmp.first;
        }

        state.render.invalidate(mxy.first, mxy.second);
    }

    if (dam.health || dam.vampiric) {

        if (dam.vampiric) {

            p.health.inc(dmg);
        }

        mon.health -= dmg;
        totdamage += dmg;

        if (dmg >= 2.8) {
            mortal = true;
        }

        types.insert(v.type);
    }

    // dam.hunger, dam.unluck:
    // Monsters don't feel hunger and don't have luck.
    // They also cannot be infected.
}


inline void attack_from_env(Player& p, const damage::attacks_t& attacks, unsigned int plevel,
                            GameState& state, const monsters::pt& mxy, monsters::Monster& mon,
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
    double totstun = 0.0;
    double totfear = 0.0;
    double totblind = 0.0;
    double totpoly = 0.0;
    bool mortal = false;

    std::set<tag_t> types;

    for (const auto& v : attack_res) {

        attack_damage_monster(v, mxy, mon, s, p, state, 
                              totdamage, totmagic, totsleep, totstun, totfear, totblind, totpoly,
                              types, mortal);
    }

    if (totpoly > 0) {
        state.render.do_message(nlp::message("You polymorph into %s!", s), true);
    }

    if (mon.health - totdamage <= -3) {

        monster_kill(p, state, mxy, mon, s, track_kills, types);
    }
}


inline bool attack_from_player(Player& p, const damage::attacks_t& attacks, unsigned int plevel, 
                               GameState& state, const monsters::py& mxy, monsters::Monster& mon, 
                               bool quiet) {

    const Species& s = species().get(mon.tag);

    unsigned int species_level = s.get_computed_level();

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
    double totstun = 0.0;
    double totfear = 0.0;
    double totblind = 0.0;
    double totpoly = 0.0;
    bool mortal = false;

    std::set<tag_t> types;

    for (const auto& v : attack_res) {

        attack_damage_monster(v, mxy, mon, s, p, state, 
                              totdamage, totmagic, totsleep, totstun, totfear, totblind, totpoly,
                              types, mortal);
    }

    p.karma.inc(s.karma * totdamage);

    if (totsleep > 0) {
        state.render.do_message(nlp::message("%s falls asleep.", s));
    }

    if (totstun > 0) {
        state.render.do_message(nlp::message("%s is stunned.", s));
    }

    if (totfear > 0) {
        state.render.do_message(nlp::message("%s flees in terror.", s));
    }

    if (totblind > 0) {
        state.render.do_message(nlp::message("%s is blinded.", s));
    }

    if (totpoly > 0) {
        state.render.do_message(nlp::message("You polymorph into %s!", s), true);
    }

    bool allow_gain_level = (!s.flags.plant && p.polymorph.species.null());

    if (mon.health - totdamage <= -3) {

        if (s.flags.plant || s.flags.robot) {
            state.render.do_message(nlp::message("You destroyed %s.", s));
        } else {
            state.render.do_message(nlp::message("You killed %s.", s));
        }

        monster_kill(p, state, mxy, mon, s, true, types);

        if (allow_gain_level && species_level > p.level) {

            p.level = species_level;

            // Don't gain a level twice.
            mortal = false;
            
            state.render.do_message(nlp::message("You gained level %d!", p.level+1), true);
        }

    } else if (!quiet && totdamage > 0) {

        if (s.flags.plant) {
            state.render.do_message(nlp::message("You smash %s.", s));

        } else if (s.flags.robot) {
            state.render.do_message(nlp::message("You damage %s.", s));

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

        if (mon.magic - totmagic <= -3) {
            state.render.do_message(nlp::message("%s is magically cancelled.", s));

        } else {
            state.render.do_message(nlp::message("%s is showered in sparkles.", s));
        }
    }

    if (species_level >= p.level && mortal && allow_gain_level) {

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


inline void defend_message(GameState& state, const Species& s, const Damage::msg_t& msg) {

    state.render.do_message(nlp::message(msg.str, s), msg.important);
}

inline void defend_message(GameState& state, const Terrain& t, const Damage::msg_t& msg) {

    state.render.do_message(nlp::message(msg.str, t), msg.important);
}

inline void defend_message(GameState& state, const Design& d, const Damage::msg_t& msg) {

    state.render.do_message(nlp::message(msg.str, d), msg.important);
}

inline void defend_message(GameState& state, const ConstantsBank::ailment_t& a, const Damage::msg_t& msg) {

    state.render.do_message(nlp::message(msg.str, a), msg.important);
}


template <typename S>
inline double defend(Player& p, 
                     const damage::defenses_t& defenses, unsigned int plevel, 
                     const damage::attacks_t& attacks, unsigned int alevel, 
                     GameState& state, const std::string& attacker_name, bool env,
                     const S& s, size_t& n) {

    double vamp = 0;

    if (attacks.empty())
        return vamp;

    damage::attacks_t attack_res;

    roll_attack(state.rng, defenses, plevel+1, attacks, alevel+1, attack_res);

    n = 0;

    if (attack_res.empty()) {

        if (!env) {
            Damage::msg_t msg("%s attacks but does no damage.");
            defend_message(state, s, msg);
        }

        return vamp;
    }

    p.attacker = attacker_name;

    for (const auto& v : attack_res) {

        double dmg = v.val;

        const Damage& dam = damages().get(v.type);

        if (p.polymorph.species.null()) {

            if (!dam.flags.robot(false) || 
                !dam.flags.undead(false) ||
                !dam.flags.animal(false) ||
                !dam.flags.plant(false) ||
                !dam.flags.magic(false) ||
                !dam.flags.eyeless(false) ||
                !dam.flags.player(true)) 
                continue;

        } else {

            const Species& sp = species().get(p.polymorph.species);

            if (!dam.flags.robot(sp.flags.robot) || 
                !dam.flags.undead(sp.flags.undead) ||
                !dam.flags.animal(sp.flags.animal) ||
                !dam.flags.plant(sp.flags.plant) ||
                !dam.flags.magic(sp.flags.magic) ||
                !dam.flags.eyeless(sp.flags.eyeless) ||
                !dam.flags.player(false)) 
                continue;
        }



        if (dam.heavenly) {

            karmic_damage_scale(true, p.karma.val, p.karma.shield, dmg);

        } else if (dam.hellish) {

            karmic_damage_scale(false, p.karma.val, p.karma.shield, dmg);
        }

        if (dmg <= dam.threshold)
            continue;

        n++;

        unsigned int sleepturns = dam.sleepturns(dmg);
        unsigned int blindturns = dam.blindturns(dmg);
        unsigned int stunturns = dam.stunturns(dmg);
        unsigned int fearturns = dam.fearturns(dmg);

        // 

        if (sleepturns > 0) {
            p.sleep += sleepturns;
        }

        if (blindturns > 0) {
            p.blind += blindturns;
        }

        if (stunturns > 0) {
            p.stun += stunturns;
        }

        if (fearturns > 0) {
            p.fear += fearturns;
        }

        if (!dam.polymorph.first.null()) {
            p.health.dec(6.0);
        }

        if (dam.hunger) {
            p.food.dec(dmg);
        } 

        if (dam.unluck) {
            p.luck.dec(dmg);
        }

        if (dam.health || dam.vampiric) {
            p.health.dec(dmg);
        }

        if (!dam.infect.null()) {

            auto i = constants().ailments.find(dam.infect);

            if (i == constants().ailments.end())
                throw std::runtime_error("Sanity error: unknown ailment in damage " + dam.name);

            p.add_ailment(state.rng, dam.infect, i->second.triggers);

            vamp = -6.0;
        }

        if (env) {
            defend_message(state, s, dam.env_msg);
        } else {
            defend_message(state, s, dam.melee_msg);
        }
    }

    if (n > 0) {
        handle_post_defend(p, state);
    }

    return vamp;
}

inline double defend(Player& p, 
                     const damage::defenses_t& defenses, unsigned int plevel, 
                     const Species& s, const damage::attacks_t& attacks,
                     GameState& state, bool friendly_fire = false) {

    size_t tmp;
    return defend(p, defenses, plevel, attacks, s.get_computed_level(), state, s.name, friendly_fire, s, tmp);
}

inline double defend(Player& p, 
                     const damage::defenses_t& defenses, unsigned int plevel, 
                     const Species& s,
                     GameState& state, bool friendly_fire = false) {
    
    return defend(p, defenses, plevel, s, s.attacks, state, friendly_fire);
}



inline void defend(Player& p, 
                   const damage::defenses_t& defenses, unsigned int plevel, 
                   const Terrain& t, 
                   GameState& state) {

    size_t tmp;
    defend(p, defenses, plevel, t.attacks, t.attack_level, state, t.name, true, t, tmp);
}

inline void defend(Player& p, 
                   const damage::defenses_t& defenses, unsigned int plevel, 
                   const Design& d, 
                   GameState& state) {

    unsigned int level = (d.attack_level >= 0 ? d.attack_level : d.level);

    size_t tmp;
    defend(p, defenses, plevel, d.attacks, level, state, d.name, true, d, tmp);
}

inline size_t defend(Player& p, const ConstantsBank::ailment_t& ailment, GameState& state) {

    damage::defenses_t defenses;
    p.get_defense(defenses);

    size_t tmp = 0;

    defend(p, defenses, p.get_computed_level(state.rng), ailment.attacks, ailment.level, state, 
           ailment.name, true, ailment, tmp);

    return tmp;
}


#endif
