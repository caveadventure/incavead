#ifndef __APPLY_H
#define __APPLY_H


inline std::string dowsing_message(const Player& p, const GameState& state) {

    const Levelskin& ls = levelskins().get(p.worldz);

    if (!ls.has_treasure) {
        return "Dowsing is useless here.";
    }

    double h = state.grid.get(p.px, p.py);

    if (h <= -1) {
        return "Completely cold.";

    } else if (h < 0.5) {
        return "Very cold.";

    } else if (h < 0) {
        return "Cold.";

    } else if (h < 0.5) {
        return "A little bit warm.";

    } else if (h < 1) {
        return "Warm.";

    } else if (h < 1.5) {
        return "Warm and getting warmer.";

    } else if (h < 2) {
        return "A little bit hot.";

    } else if (h < 2.5) {
        return "Hot.";

    } else if (h < 3.0) {
        return "Very hot.";

    } else {
        return "Extremely hot.";
    }
}


inline bool apply_item(Player& p, tag_t slot, GameState& state, bool& regen) {

    items::Item tmp;

    if (!p.inv.get(slot, tmp))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (!d.usable) 
        return false;
        
    // Dowsing rods are permanent.
    if (d.flags.dowsing) {
        state.render.do_message(dowsing_message(p, state));
        return true;
    }

    if (!p.inv.take(slot, tmp, 1))
        return false;

    bool ret = false;

    if (d.action_name.size() > 0) {
        state.render.do_message(nlp::message("You %s %s.", d.action_name, d));
    }

    if (!d.attacks.empty()) {

        damage::defenses_t defenses;
        p.get_defense(defenses);

        defend(p, defenses, p.get_computed_level(state.rng), d, state);
    }

    if (d.heal > 0) {

        p.health.inc(d.heal);
        state.render.do_message("You feel better.");
        ret = true;
    } 

    if (d.feed > 0) {

        p.food.inc(d.feed);

        ret = true;
    } 

    if (d.heal_blind) {

        if (p.blind > 0) {
            p.blind = 0;
            state.render.do_message("You can see again!", true);
        }

        ret = true;
    }

    if (d.heal_stun) {

        if (p.stun > 0) {
            p.stun = 0;
            state.render.do_message("You feel more stable.");
        }

        ret = true;
    }

    if (d.heal_fear) {

        if (p.fear > 0) {
            p.fear = 0;
            state.render.do_message("You feel a surge of courage!");
        }

        ret = true;
    }

    if (d.heal_unluck) {

        if (p.luck.val < 0) {
            p.luck.val = 0;
            state.render.do_message("You lucky stiff.");
        }
        
        ret = true;
    }

    if (d.heal_ailments && p.ailments.size() > 0) {

        p.ailments.clear();
        state.render.do_message("You feel cured.");
        ret = true;
    }

    if (d.heal_polymorph && !p.polymorph.species.null()) {
        
        p.polymorph.species = tag_t();
        p.polymorph.turns = 0;
        state.render.do_message("You return to your original form.", true);
        state.render.invalidate(p.px, p.py);
        ret = true;
    }

    if (d.karma != 0) {
        p.karma.inc(d.karma);
        ret = true;
    }

    if (d.consume_luck != 0) {
        p.luck.inc(d.consume_luck);
        ret = true;
    }

    if (d.flags.blink) {

        grid::pt xy;
        if (!state.grid.one_of_walk(state.rng, xy))
            return false;

        state.render.invalidate(p.px, p.py);

        p.px = xy.first;
        p.py = xy.second;

        state.render.invalidate(p.px, p.py);
        ret = true;
    }

    // WARNING, don't change the order of blocks, as worldz can be modified.
    if (!d.place_permafeat.feat.null()) {

        // HACK!
        const Levelskin& ls = levelskins().get(p.worldz);
        const Terrain& t = terrain().get(d.place_permafeat.feat);

        if (ls.no_phase_level && t.stairs > 0) {

            state.render.do_message("Nothing happened. Strange.", true);
            ret = false;

        } else {
            state.features.set(p.px, p.py, d.place_permafeat.feat, state.render);        
            permafeats::features().add(p, d.place_permafeat.feat);
            ret = true;
        }

    } else if (d.place_permafeat.walk != -1 || d.place_permafeat.water != -1) {

        bool walk = (d.place_permafeat.walk == -1 ? state.grid.is_walk(p.px, p.py) : d.place_permafeat.walk);
        bool water = (d.place_permafeat.water == -1 ? state.grid.is_water(p.px, p.py) : d.place_permafeat.water);

        state.grid.set_walk_water(state.neigh, p.px, p.py, walk, water);
        state.render.invalidate(p.px, p.py);
        permafeats::features().add(p, walk, water);
        ret = true;
    }

    if (d.descend != 0) {
        p.worldz += d.descend;
        regen = true;
        ret = true;
    }

    if (d.safe_descend != 0) {
        
        const Levelskin& ls = levelskins().get(p.worldz);

        if (ls.no_phase_level) {
            state.render.do_message("Nothing happened. Strange.", true);
            ret = false;

        } else {
            p.worldz += d.safe_descend;
            regen = true;
            ret = true;
        }
    }

    if (!d.genocide.null()) {

        state.render.do_message("You sense a great disturbance in the force.", true);

        genocide(state, d.genocide);
        ret = true;
    }

    if (d.wishing) {
        if (d.wishing == Design::SPECIAL_WISH) {
            do_player_wish(state, p, true);
        } else {
            do_player_wish(state, p, false);
        }

        ret = true;
    }

    if (d.magic_mapping) {

        for (const auto& f : state.features.feats) {
            const Terrain& t = terrain().get(f.second.tag);

            if (t.air)
                continue;

            const grender::pt& xy = f.first;
            state.render.set_is_lit(xy.first, xy.second, 3, true);
            state.render.invalidate(xy.first, xy.second);
        }

        ret = true;
    }

    if (!d.summon.species.null()) {
        
        state.triggers[state.ticks].summon.species = d.summon.species;
        state.triggers[state.ticks].summon.count = d.summon.count;

        ret = true;
    }

    if (!d.raise_monsters.null()) {

        state.items.consume([&p,&state](const items::Item& item) {

                const Design& d = designs().get(item.tag);

                if (d.monster_raised.null())
                    return false;

                const Species& s = species().get(d.monster_raised);

                if (distance(item.xy.first, item.xy.second, p.px, p.py) > s.range)
                    return false;

                if (!reachable(state, item.xy.first, item.xy.second, p.px, p.py,
                               [&s](GameState& state, unsigned int xx, unsigned int yy) {
                                   return monster_move_cost(state, s, xx, yy) >= 0;
                               }))
                    return false;

                int nm = state.monsters.summon(state.neigh, state.rng, state.grid, state.species_counts, state.render, 
                                               item.xy.first, item.xy.second, &p.px, &p.py, 
                                               d.monster_raised, 1, true, d.raise_monsters);

                return (nm > 0);
            });

        ret = true;
    }

    if (!d.polymorph.species.null()) {

        p.polymorph.species = d.polymorph.species;
        p.polymorph.turns = std::max(state.rng.gauss(d.polymorph.turns.mean, d.polymorph.turns.deviation), 1.0);

        state.render.invalidate(p.px, p.py);
        state.render.do_message(d.polymorph.msg, true);

        ret = true;
    }

    if (d.fast.slice > 0) {
        
        p.fast.slice = d.fast.slice;
        p.fast.turns = std::max(state.rng.gauss(d.fast.turns.mean, d.fast.turns.deviation), 1.0);

        state.render.do_message("You feel your movements speed up unnaturally.", true);
        
        ret = true;
    }

    if (ret && !d.attacks.empty()) {

        damage::defenses_t defenses;
        p.get_defense(defenses);

        defend(p, defenses, p.get_computed_level(state.rng), d, state);
    }

    if (ret && !d.use_for_free) {

        ++(state.ticks);
    }

    if (d.lucky_free_apply && p.luck.val > 1.0) {

        double chance = 1.0 - (1.0 / p.luck.val);

        if (state.rng.uniform(0.0, 1.0) < chance) {
            ret = false;
        }
    }

    if (!ret) {
        items::Item tmp2;
        p.inv.place(slot, tmp, tmp2);
    }

    return true;
}


inline bool destroy_item(Player& p, tag_t slot) {

    items::Item tmp;

    if (!p.inv.get(slot, tmp))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (!d.destructible) 
        return false;
        
    if (!p.inv.take(slot, tmp))
        return false;

    return true;
}

inline void blast_process_point(Player& p, GameState& state, const Design& d,
                                unsigned int _x, unsigned int _y) {

    if (_x == p.px && _y == p.py) {

        damage::defenses_t defenses;
        p.get_defense(defenses);

        defend(p, defenses, p.get_computed_level(state.rng), d, state);

    } else {

        monsters::Monster& mon = state.monsters.get(_x, _y);

        if (!mon.null()) {

            unsigned int lev = (d.attack_level >= 0 ? d.attack_level : p.get_computed_level(state.rng));

            attack_from_player(p, d.attacks, lev, state, monsters::pt(_x, _y), mon, false);
        }
    }
}

inline bool end_blast_item(Player& p, tag_t slot, unsigned int lx, unsigned int ly, GameState& state) {

    items::Item tmp;
        
    if (!p.inv.take(slot, tmp, 1))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (distance(p.px, p.py, lx, ly) > d.blast.range) {
        return false;
    }

    if (d.blast.radius == 0) {

        blast_process_point(p, state, d, lx, ly);

    } else {

        state.render.draw_circle(lx, ly, d.blast.radius, d.skin.a.fore, maudit::color::bright_black,
                                 [&](unsigned int _x, unsigned int _y) {
                                 
                                     blast_process_point(p, state, d, _x, _y);
                                 });
    }

    return true;
}

inline bool start_blast_item(Player& p, tag_t slot, GameState& state) {

    items::Item tmp;
    if (!p.inv.get(slot, tmp)) {
        return false;
    }

    const Design& d = designs().get(tmp.tag);

    if (d.blast.radius == 0 && d.blast.range == 0) {
        return false;
    }

    if (d.blast.range > 0) {
        
        start_look_target(p.state, p.look, p.px, p.py, state, 0, d.blast.range);
        p.state |= Player::BLASTING;

    } else {

        if (!end_blast_item(p, slot, p.px, p.py, state)) 
            return false;

        ++(state.ticks);
    }

    return true;
}

inline bool end_cloud_item(Player& p, tag_t slot, unsigned int lx, unsigned int ly, GameState& state) {

    items::Item tmp;

    if (!p.inv.take(slot, tmp, 1))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (distance(p.px, p.py, lx, ly) > d.cast_cloud.range) {
        return false;
    }

    cast_cloud(state, lx, ly, d.cast_cloud.radius, d.cast_cloud.terraintag);

    return true;
}

inline bool start_cloud_item(Player& p, tag_t slot, GameState& state) {

    items::Item tmp;
    if (!p.inv.get(slot, tmp)) {
        return false;
    }

    const Design& d = designs().get(tmp.tag);

    if (d.cast_cloud.radius == 0 && d.cast_cloud.range == 0) {
        return false;
    }

    if (d.cast_cloud.range > 0) {
        
        start_look_target(p.state, p.look, p.px, p.py, state, 0, d.cast_cloud.range);
        p.state |= Player::CLOUDING;

    } else {

        if (!end_cloud_item(p, slot, p.px, p.py, state))
            return false;

        ++(state.ticks);
    }

    return true;
}


inline bool end_throw_item(Player& p, tag_t slot, unsigned int lx, unsigned int ly,
                           GameState& state) {

    items::Item tmp;
        
    if (!p.inv.take(slot, tmp, 1))
        return false;

    const Design& d = designs().get(tmp.tag);

    double v = distance(p.px, p.py, lx, ly);

    if (d.throwrange == 0 || v > d.throwrange) {
        return false;
    }

    monsters::Monster& mon = state.monsters.get(lx, ly);

    if (!mon.null()) {
            
        double v2 = std::max(0.0, (v-1) / d.throwrange);

        unsigned int ilev = (d.attack_level >= 0 ? d.attack_level : p.get_computed_level(state.rng));

        unsigned int lev = (1 - v2) * ilev;

        attack_from_player(p, d.attacks, lev, state, monsters::pt(lx, ly), mon, false);
    }

    state.items.place(lx, ly, tmp, state.render);

    return true;
}

inline bool start_throw_item(Player& p, tag_t slot, GameState& state) {

    items::Item tmp;
    if (!p.inv.get(slot, tmp))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (d.throwrange == 0)
        return false;
    
    start_look_target(p.state, p.look, p.px, p.py, state, 0, d.throwrange);
    p.state |= Player::THROWING;

    return true;
}

inline bool end_poly_blast(Player& p, size_t i, unsigned int x, unsigned int y, GameState& state) {

    if (p.polymorph.species.null())
        return false;

    const Species& s = species().get(p.polymorph.species);

    if (i >= s.blast.size())
        return false;

    const auto& b = s.blast[i];

    do_monster_blast(p, state, s, x, y, b.radius, b.attacks, true);

    return true;
}

inline bool start_poly_blast(Player& p, size_t i, GameState& state) {

    if (p.polymorph.species.null())
        return false;

    const Species& s = species().get(p.polymorph.species);

    if (i >= s.blast.size())
        return false;

    const auto& b = s.blast[i];

    if ((state.ticks % b.turns) != 0) {

        state.render.do_message("You failed to activate your ability properly.");
        return false;
    }
    
    double v = state.rng.gauss(0.0, 1.0);

    if (v <= b.chance) {
        state.render.do_message("You failed to activate your ability properly.");
        return false;
    }

    p.polymorph_ability = i;

    if (b.range > 0) {
        
        start_look_target(p.state, p.look, p.px, p.py, state, 0, b.range);
        p.state |= Player::P_BLASTING;

    } else {

        if (!end_poly_blast(p, i, p.px, p.py, state)) 
            return false;

        ++(state.ticks);
    }

    return true;
}

inline bool end_poly_cloud(Player& p, size_t i, unsigned int x, unsigned int y, GameState& state) {

    if (p.polymorph.species.null())
        return false;

    const Species& s = species().get(p.polymorph.species);

    if (i >= s.cast_cloud.size())
        return false;

    const auto& c = s.cast_cloud[i];

    cast_cloud(state, x, y, c.radius, c.terraintag);

    return true;
}

inline bool start_poly_cloud(Player& p, size_t i, GameState& state) {

    if (p.polymorph.species.null())
        return false;

    const Species& s = species().get(p.polymorph.species);

    if (i >= s.cast_cloud.size())
        return false;

    const auto& c = s.cast_cloud[i];

    if ((state.ticks % c.turns) != 0) {

        state.render.do_message("You failed to activate your ability properly.");
        return false;
    }
    
    double v = state.rng.gauss(0.0, 1.0);

    if (v <= c.chance) {
        state.render.do_message("You failed to activate your ability properly.");
        return false;
    }

    p.polymorph_ability = i;

    start_look_target(p.state, p.look, p.px, p.py, state, 0, s.range);
    p.state |= Player::P_CLOUDING;

    return true;
}

inline bool summon_poly(Player& p, size_t i, GameState& state) {

    if (p.polymorph.species.null())
        return false;

    const Species& s = species().get(p.polymorph.species);

    if (i >= s.summon.size())
        return false;

    const auto& c = s.summon[i];

    if ((state.ticks % c.turns) != 0) {

        state.render.do_message("You failed to activate your ability properly.");
        return false;
    }
    
    double v = state.rng.gauss(0.0, 1.0);

    if (v <= c.chance) {
        state.render.do_message("You failed to activate your ability properly.");
        return false;
    }

    size_t n = state.monsters.summon(state.neigh, state.rng, state.grid, state.species_counts, state.render, 
                                     p.px, p.py, &p.px, &p.py, c.speciestag, 1, false, p.polymorph.species);

    ++(state.ticks);

    return (n > 0);
}

inline bool spawn_poly(Player& p, size_t i, GameState& state) {

    if (p.polymorph.species.null())
        return false;

    const Species& s = species().get(p.polymorph.species);

    if (i >= s.spawns.size())
        return false;

    const auto& c = s.spawns[i];

    if ((state.ticks % c.turns) != 0) {

        state.render.do_message("You failed to activate your ability properly.");
        return false;
    }
    
    double v = state.rng.gauss(0.0, 1.0);

    if (v <= c.chance) {
        state.render.do_message("You failed to activate your ability properly.");
        return false;
    }

    size_t n = state.monsters.summon_any(state.neigh, state.rng, state.grid, state.species_counts, state.render, 
                                         p.px, p.py, &p.px, &p.py, c.level, 1, p.polymorph.species);

    ++(state.ticks);

    return (n > 0);
}


inline bool start_digging(Player& p, tag_t slot, GameState& state) {

    items::Item tmp;
    if (!p.inv.get(slot, tmp))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (d.digging <= 0)
        return false;
    
    p.state |= Player::DIGGING;

    return true;
}


inline bool take_item(unsigned int x, unsigned int y, unsigned int z, 
                      Player& p, GameState& state) {

    items::Item discarded_item;
    items::Item taken_item;
        
    if (p.inv.floor_to_inv(x, y, z, state.items, state.render, discarded_item, taken_item)) {

        if (!discarded_item.tag.null()) {

            const Design& d = designs().get(discarded_item.tag);

            // HACK
            state.render.do_message(nlp::message("You discard %s to make space.", nlp::count(), d, 
                                                 discarded_item.count));
        }

        {
            const Design& d = designs().get(taken_item.tag);

            if (!d.take_summon.species.null() && 
                taken_item.count >= d.take_summon.needs_count) {

                state.triggers[state.ticks].summon_out_of_view.monster = d.take_summon.species;
                state.triggers[state.ticks].summon_out_of_view.count = 0;
            }
        }

        ++(state.ticks);
        return true;
    }

    return false;
}

#endif
