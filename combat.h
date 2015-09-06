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

inline double karmic_damage_scale(double scale, double karma, double dmg) {

    double kk = karma * scale;

    if (kk > 0) {
        double factor = (kk)/2;
        factor = factor * factor;

        dmg *= factor;

    } else {
        dmg = 0;
    }

    return dmg;
}

inline bool luck_level_scale(rnd::Generator& rng, pstats::stats_t& stats, tag_t stat,
                             double factor, double threshold, unsigned int& level) {

    double v = stats.gets(stat);

    double denom = v + threshold;

    if (denom == 0)
        return false;

    double p = factor / denom;
    double pv = ::fabs(p);

    if (pv <= 0 || pv >= 1)
        return false;

    bool neg = (pv < 0);

    unsigned int fudge = rng.geometric(pv);

    if (neg) {
        level -= std::max(level, fudge);
        return false;

    } else {
        level += fudge;
        return stats.sinc(stat, -fudge / factor);
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


inline bool attack_damage_monster(const damage::val_t& v, 
                                  const monsters::pt& mxy, monsters::Monster& mon, const Species& s,
                                  Player& p, GameState& state,
                                  std::map<tag_t,double>& stathits,
                                  std::map<tag_t,unsigned int>& counthits,
                                  std::set<tag_t>& types, bool& did_poly, bool& did_level,
                                  double& visible_damage) {

    double dmg = v.val;

    const Damage& dam = damages().get(v.type);

    if (!dam.flags.cosmic(s.flags.cosmic) ||
        !dam.flags.robot(s.flags.robot) || 
        !dam.flags.undead(s.flags.undead) ||
        !dam.flags.animal(s.flags.animal) ||
        !dam.flags.plant(s.flags.plant) ||
        !dam.flags.magic(s.flags.magic) ||
        !dam.flags.eyeless(s.flags.eyeless) ||
        !dam.flags.player(false)) 
        return false;

    if (dam.karmic_scale.size() > 0) {
        double mk = 0;

        for (const auto& i : dam.karmic_scale) {

            mk = std::max(mk, karmic_damage_scale(i.second, mon.stats.gets(i.first), dmg));
        }

        dmg = mk;
    }
   
    if (dmg <= dam.threshold)
        return false;

    if (dam.visible_damage) {
        visible_damage += dmg;
    }

    for (const auto& i : dam.inc_counts) {

        unsigned int turns = i.second.get(dmg);

        if (turns > 0) {
            mon.stats.cinc(i.first, turns);
            counthits[i.first] += turns;
        }
    }

    for (const tag_t& i : dam.dec_stats) {

        bool kill = mon.stats.sinc(i, -dmg);

        if (dmg > 0) {
            stathits[i] += dmg;
        }

        if (kill) {
            types.insert(v.type);
        }
    }

    for (const tag_t& i : dam.inc_stats) {

        if (p.stats.sinc(i, dmg)) {

            types.insert(v.type);
        }
    }

    for (const tag_t& i : dam.transfer_stats) {

        if (p.stats.sinc(i, -mon.stats.gets(i) * dmg)) {

            types.insert(v.type);
        }
    }

    unsigned int polyturns = dam.player_poly.get(dmg);
    
    if (polyturns > 0) {

        p.polymorph.species = mon.tag;
        p.polymorph.turns = polyturns;
        p.stats = mon.stats;

        state.render.invalidate(p.px, p.py);
        did_poly = true;
    }

    if (!dam.polymorph.null()) {

        mon.tag = dam.polymorph;
        mon.stats = species().get(mon.tag).stats;

        state.render.invalidate(mxy.first, mxy.second);
    }

    if (!dam.ally.null()) {
        
        mon.ally = dam.ally;
        state.render.invalidate(mxy.first, mxy.second);
    }

    if (dam.levelup_threshold > 0 && dmg > dam.levelup_threshold) {

        did_level = true;
    }

    return true;
}


inline bool attack_from_env(Player& p, const damage::attacks_t& attacks, unsigned int plevel,
                            GameState& state, const monsters::pt& mxy, monsters::Monster& mon,
                            bool track_kills, bool zero_mon_level = false) {

    if (attacks.empty()) {
        return false;
    }

    const Species& s = species().get(mon.tag);

    damage::attacks_t attack_res;
    roll_attack(state.rng, s.defenses, (zero_mon_level ? 1 : s.get_computed_level()+1), 
                attacks, plevel+1, attack_res);

    if (attack_res.empty()) {
        return false;
    }

    std::map<tag_t,double> stathits;
    std::map<tag_t,unsigned int> counthits;
    std::set<tag_t> types;
    bool did_poly = false;
    bool did_level = false;
    double visible_damage = 0;

    bool ret = false;

    for (const auto& v : attack_res) {

        bool tmp = attack_damage_monster(v, mxy, mon, s, p, state, stathits, counthits,
                                         types, did_poly, did_level, visible_damage);

        if (tmp)
            ret = true;
    }

    if (did_poly) {
        state.render.do_message(nlp::message("You polymorph into %s!", s), true);
    }

    if (types.size() > 0 && mon.stats.crit()) {

        monster_kill(p, state, mxy, mon, s, track_kills, types);
        mon.dead = true;
    }

    return ret;
}


inline bool attack_from_player(Player& p, const damage::attacks_t& attacks, unsigned int plevel, 
                               GameState& state, const monsters::pt& mxy, monsters::Monster& mon, 
                               bool quiet) {

    const Species& s = species().get(mon.tag);

    unsigned int species_level = s.get_computed_level();

    if (attacks.empty()) {
        state.render.do_message("You can't attack without a weapon!", true);
        return false;
    }

    const auto& luck = constants().luck;

    if (!luck.stat.null()) {

        if (luck_level_scale(state.rng, p.stats, luck.stat, luck.factor, luck.threshold, plevel))
            mon.dead = true;
    }

    damage::attacks_t attack_res;
    roll_attack(state.rng, s.defenses, s.get_computed_level()+1, attacks, plevel+1, attack_res);

    if (attack_res.empty()) {

        if (!quiet)
            state.render.do_message(nlp::message("You attack %s but do no damage.", s));

        return true;
    }

    std::map<tag_t,double> stathits;
    std::map<tag_t,unsigned int> counthits;
    std::set<tag_t> types;
    bool did_poly = false;
    bool did_level = false;
    double visible_damage = 0;

    bool ret = false;

    for (const auto& v : attack_res) {

        bool tmp = attack_damage_monster(v, mxy, mon, s, p, state, stathits, counthits,
                                         types, did_poly, did_level, visible_damage);

        if (tmp)
            ret = true;
    }

    for (const auto& i : stathits) {

        const Stat& st = stats().get(i.first);

        if (st.monster_hit_msg.size() > 0)
            state.render.do_message(nlp::message(st.monster_hit_msg, s));
    }

    for (const auto& i : counthits) {

        const Count& ct = counts().get(i.first);

        if (ct.monster_hit_msg.size() > 0)
            state.render.do_message(nlp::message(ct.monster_hit_msg, s));
    }

    if (did_poly) {
        state.render.do_message(nlp::message("You polymorph into %s!", s), true);
    }

    bool allow_gain_level = (!s.flags.plant && p.polymorph.species.null());

    if (types.size() > 0 && mon.stats.crit()) {

        if (s.flags.plant || s.flags.robot) {
            state.render.do_message(nlp::message("You destroyed %s.", s));
        } else {
            state.render.do_message(nlp::message("You killed %s.", s));
        }

        monster_kill(p, state, mxy, mon, s, true, types);

        if (allow_gain_level && species_level > p.level) {

            p.level = species_level;

            // Don't gain a level twice.
            did_level = false;
            
            state.render.do_message(nlp::message("You gained level %d!", p.level+1), true);
        }

        mon.dead = true;

    } else if (!quiet && visible_damage > 0) {

        if (s.flags.plant) {
            state.render.do_message(nlp::message("You smash %s.", s));

        } else if (s.flags.robot) {
            state.render.do_message(nlp::message("You damage %s.", s));

        } else if (visible_damage < 0.1) {
            state.render.do_message(nlp::message("You almost miss %s.", s));

        } else if (visible_damage < 0.5) {
            state.render.do_message(nlp::message("You hit %s.", s));

        } else if (visible_damage < 1.0) {
            state.render.do_message(nlp::message("You wound %s.", s));

        } else if (visible_damage < 2.0) {
            state.render.do_message(nlp::message("You heavily wound %s.", s));

        } else if (visible_damage < 2.8) {
            state.render.do_message(nlp::message("You critically wound %s.", s));

        } else {
            state.render.do_message(nlp::message("You mortally wound %s.", s));
        }
    }

    if (species_level >= p.level && did_level && allow_gain_level) {

        p.level = species_level+1;
        state.render.do_message(nlp::message("You gained level %d!", p.level+1), true);
    }

    return ret;
}


inline void handle_post_defend(Player& p, GameState& state) {

    p.stats.cancel();

    /*
    if (p.digging) {
        state.render.do_message("You stop digging.");
        p.digging = false;
    }

    if (p.rest > 0) {
        state.render.do_message("You stop resting.");
        p.rest = 0;
    }
    */
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

inline void defend_sinc_stats(monsters::Monster& mon, tag_t stat, double v) {

    if (mon.stats.sinc(stat, v)) {
        mon.dead = true;
    }
}

inline void defend_sinc_stats(int, tag_t, double) {
}


template <typename S, typename T>
inline void defend(Player& p, 
                   const damage::defenses_t& defenses, unsigned int plevel, 
                   const damage::attacks_t& attacks, unsigned int alevel, 
                   GameState& state, const std::string& attacker_name, bool env,
                   const S& s, T mon, size_t& n) {

    if (attacks.empty())
        return;

    const auto& luck = constants().luck;

    if (!luck.stat.null()) {

        if (luck_level_scale(state.rng, p.stats, luck.stat, luck.factor, luck.threshold, plevel))
            p.dead = true;
    }

    damage::attacks_t attack_res;

    roll_attack(state.rng, defenses, plevel+1, attacks, alevel+1, attack_res);

    n = 0;

    if (attack_res.empty()) {

        if (!env) {
            Damage::msg_t msg("%s attacks but does no damage.");
            defend_message(state, s, msg);
        }

        return;
    }

    p.attacker = attacker_name;

    for (const auto& v : attack_res) {

        double dmg = v.val;

        const Damage& dam = damages().get(v.type);

        const Species& sp = p.get_species();

        if (!dam.flags.robot(sp.flags.robot) || 
            !dam.flags.undead(sp.flags.undead) ||
            !dam.flags.animal(sp.flags.animal) ||
            !dam.flags.plant(sp.flags.plant) ||
            !dam.flags.magic(sp.flags.magic) ||
            !dam.flags.eyeless(sp.flags.eyeless) ||
            !dam.flags.cosmic(sp.flags.cosmic) ||
            !dam.flags.player(sp.flags.player)) 
            continue;

        if (dam.karmic_scale.size() > 0) {
            double mk = 0;
            
            for (const auto& i : dam.karmic_scale) {
                mk = std::max(mk, karmic_damage_scale(i.second, p.stats.gets(i.first), dmg));
            }

            dmg = mk;
        }

        if (dmg <= dam.threshold)
            continue;

        n++;

        for (const auto& i : dam.inc_counts) {

            unsigned int turns = i.second.get(dmg);

            if (turns > 0) {
                p.stats.cinc(i.first, turns);
            }
        }

        for (const tag_t& i : dam.dec_stats) {

            if (p.stats.sinc(i, -dmg))
                p.dead = true;
        }

        for (const tag_t& i : dam.inc_stats) {

            defend_sinc_stats(mon, i, dmg);
        }

        for (const tag_t& i : dam.transfer_stats) {

            defend_sinc_stats(mon, i, -p.stats.gets(i) * dmg);
        }

        // HACK!
        if (!dam.polymorph.null()) {

            p.stats.die();
            p.dead = true;
        }

        if (!dam.infect.first.null()) {

            auto i = constants().ailments.find(dam.infect.first);

            if (i == constants().ailments.end())
                throw std::runtime_error("Sanity error: unknown ailment in damage " + dam.name);

            p.add_ailment(state.rng, dam.infect.first, i->second.triggers);

            defend_sinc_stats(mon, dam.infect.second, -dmg);
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
}

inline void defend(Player& p, 
                   const damage::defenses_t& defenses, unsigned int plevel, 
                   const Species& s, monsters::Monster& mon, const damage::attacks_t& attacks,
                   GameState& state, bool friendly_fire = false) {

    size_t tmp;
    defend(p, defenses, plevel, attacks, s.get_computed_level(), state, s.name, friendly_fire, s,
           std::ref(mon), tmp);
}

inline void defend(Player& p, 
                   const damage::defenses_t& defenses, unsigned int plevel, 
                   const Species& s, monsters::Monster& mon, 
                   GameState& state, bool friendly_fire = false) {

    defend(p, defenses, plevel, s, mon, s.attacks, state, friendly_fire);
}



inline void defend(Player& p, 
                   const damage::defenses_t& defenses, unsigned int plevel, 
                   const Terrain& t, 
                   GameState& state) {

    size_t tmp;
    defend(p, defenses, plevel, t.attacks, t.attack_level, state, t.name, true, t, 1234, tmp);
}

inline void defend(Player& p, 
                   const damage::defenses_t& defenses, unsigned int plevel, 
                   const Design& d, 
                   GameState& state) {

    unsigned int level = (d.attack_level >= 0 ? d.attack_level : d.level);

    size_t tmp;
    defend(p, defenses, plevel, d.attacks, level, state, d.name, true, d, 1234, tmp);
}

inline size_t defend(Player& p, const ConstantsBank::ailment_t& ailment, GameState& state) {

    damage::defenses_t defenses;
    p.get_defense(defenses);

    size_t tmp = 0;

    defend(p, defenses, /*p.get_computed_level(state.rng)*/ 0, ailment.attacks, ailment.level, state, 
           ailment.name, true, ailment, 1234, tmp);

    return tmp;
}


#endif
