#ifndef __GAME_PROCESSING_H
#define __GAME_PROCESSING_H

void Game::init(unsigned int code) {

    game_seed = code;
}

void Game::dispose(GameState& state) {

    std::vector<items::Item> vic;
    std::map<items::pt,items::Item> safe;

    tag_t vic_tag = constants().unique_item;

    state.items.dispose(state.designs_counts,
                        [&](const items::Item& i) {

                            if (i.tag == vic_tag) {
                                vic.push_back(i);
                                return false;
                            }

                            features::Feature feat;
                            if (state.features.get(i.xy.first, i.xy.second, feat)) {

                                const Terrain& t = terrain().get(feat.tag);

                                if (t.safebox && safe.count(i.xy) == 0) {
                                    safe[i.xy] = i;
                                    return false;
                                }
                            }


                            return true;
                        });

    state.monsters.dispose(state.species_counts);

    if (vic.size() > 0 && !p.uniques_disabled) {
        
        uniques::uniques().put(p.current_wx, p.current_wy, p.current_wz, vic, p.dungeon_unique_series);
    }

    vic.clear();
    for (const auto& i : safe) {
        vic.push_back(i.second);
    }

    if (vic.size() > 0) {

        uniques::items().put(p.current_wx, p.current_wy, p.current_wz, vic, 1);
    }
}

void Game::endgame(GameState& state, const std::string& name) {

    bones::bones().add(name, p, constants().achievements);

    const Design& d_victory = designs().get(constants().unique_item);

    p.inv.inv_to_floor(d_victory.slot, p.px, p.py, state.items, state.render);

    dispose(state);
}

bool process_feature(GameState& state, features::Feature& f, const Terrain& t) {

    if (f.decay > 0) {
        --(f.decay);

        if (f.decay == 0)
            return false;
    }

    return true;
}

unsigned int summon_out_of_view(const Player& p, GameState& state, tag_t monster, unsigned int count) {

    int radius = get_lightradius(p) + 1;

    std::unordered_set<monsters::pt> range;

    for (int dx = -radius; dx <= radius; ++dx) {
        for (int dy = -radius; dy <= radius; ++dy) {

            int x = p.px + dx;
            int y = p.py + dy;

            if (x < 0 || y < 0 || x > (int)state.neigh.w || y > (int)state.neigh.h)
                continue;

            double dist = distance(x, y, p.px, p.py);

            if (dist >= radius && dist <= radius + 1.5) {

                bool r = reachable(state, x, y, p.px, p.py);

                if (r)
                    range.insert(monsters::pt(x, y));
            }
        }
    }

    unsigned int res = state.monsters.summon(state.neigh, state.rng, state.grid, 
                                             state.species_counts, state.render, 
                                             range, &p.px, &p.py, monster, count);

    return res;
}

void Game::process_world(GameState& state, size_t& ticks, 
                         bool& done, bool& dead, bool& regen, bool& need_input, bool& do_draw) {


    // Handle victory items.
    {
        tag_t unique_item = constants().unique_item;

        const Design& d_victory = designs().get(unique_item);

        items::Item vi;
        items::Item tmp;

        if (p.inv.take(d_victory.slot, vi)) {

            ++vi.count;

            p.inv.place(d_victory.slot, vi, tmp);
        }
    }

    //
    //

    state.camap.step(
        state.neigh,

        // Check for cells
        [&state](unsigned int x, unsigned int y, const CelAuto& ca) {

            if (state.grid.is_walk(x, y) == ca.is_walk && 
                state.grid.get_karma(x, y) * ca.karma_scale < 1.0) {

                return true;
            }

            return false;
        },

        // Cell on
        [&state](unsigned int x, unsigned int y, const CelAuto& ca) {

            if (ca.make_walk) {
                state.grid.set_walk_water(state.neigh, x, y, true, state.grid.is_water(x, y));
                state.render.invalidate(x, y);
            }

            state.features.x_set(x, y, ca.terrain, state.render);
            state.grid.get_karma(x, y) += ca.karma_step;
        },

        // Cell off
        [&state](unsigned int x, unsigned int y, const CelAuto& ca) {

            state.features.x_unset(x, y, ca.terrain, state.render);
        },

        // Max number of cells
        constants().max_celauto_cells
        );


    features::Feature feat;
    if (state.features.get(p.px, p.py, feat)) {

        const Terrain& t = terrain().get(feat.tag);

        if (!t.attacks.empty()) {

            damage::defenses_t defenses;
            p.inv.get_defense(defenses);

            defend(p, defenses, p.get_computed_level(state.rng), t, state);

            if (t.uncharge.attack) {
                state.features.uncharge(p.px, p.py, state.render);
            }
        }
    }

    if ((ticks % constants().achievement_trigger_rate) == 0) {

        for (auto& a : p.achievements) {

            if (a.second.triggered)
                continue;

            const auto& ach = constants().achievements;
            auto i = ach.find(a.first);

            if (i == ach.end())
                throw std::runtime_error("Sanity error in achievement trigger");
                
            if (!(i->second.summon.null())) {

                summon_out_of_view(p, state, i->second.summon, 0);
            }

            a.second.triggered = true;
        }
    }

    std::vector<summons_t> summons;

    state.monsters.process(state.render, 
                           std::bind(move_monster, std::ref(p), std::ref(state), ticks, std::ref(summons),
                                     std::placeholders::_1, std::placeholders::_2, 
                                     std::placeholders::_3, std::placeholders::_4));

    state.features.process(state.render, 
                           std::bind(process_feature, std::ref(state),
                                     std::placeholders::_1, std::placeholders::_2));

    for (const auto& i : summons) {

        unsigned int nm = 0;

        if (i.summontag.null()) {
            nm = state.monsters.summon_any(state.neigh, state.rng, state.grid, state.species_counts, state.render,
                                           i.x, i.y, &p.px, &p.py, i.level, 1);

        } else {
            nm = state.monsters.summon(state.neigh, state.rng, state.grid, state.species_counts, state.render, 
                                       i.x, i.y, &p.px, &p.py, i.summontag, 1);
        }

        if (nm > 0 && state.render.is_in_fov(i.x, i.y)) {

            if (i.summontag.null()) {
                state.render.do_message(nlp::message("%s summons monsters!", species().get(i.summonertag)));

            } else {
                state.render.do_message(nlp::message("%s summons %s!", species().get(i.summonertag), 
                                                     nlp::count(), species().get(i.summontag), nm));
            }
        }
    }


    for (std::vector<Terrain::spell_t>::iterator si = p.spells.begin(); si != p.spells.end(); ) {
        double k = p.karma.val;
        auto& sp = *si;

        if (sp.karma_bound < 0 && k > sp.karma_bound) {
            sp.timeout -= (k - sp.karma_bound);

        } else if (sp.karma_bound > 0 && k < sp.karma_bound) {
            sp.timeout -= (sp.karma_bound - k);
        }

        if (sp.timeout <= 0) {
            si = p.spells.erase(si);

            state.render.do_message("You feel a sense of arcane foreboding.", true);
        } else {
            ++si;
        }
    }

    //
    const auto& consts = constants();

    double inc_luck;
    double inc_hunger;
    double inc_shield;
        
    p.inv.get_turn_coeffs(state.moon.pi.phase_n, inc_luck, inc_hunger, inc_shield);

    p.luck.inc(inc_luck);

    if (p.health.shield < consts.health_shield_max) {
        p.health.shield += inc_shield;
    }

    p.food.dec(consts.hunger_rate + inc_hunger);

    {
        const Levelskin& ls = levelskins().get(p.worldz);

        if (ls.damage > 0 && p.health.val > -3.0) {
            p.attacker = "void emanations";
            p.health.dec(ls.damage);
        }
    }

    if (p.food.val <= -3.0 && p.health.val > -3.0) {
        state.render.do_message("You desperately need something to eat!", true);
        p.attacker = "starvation";
        p.health.dec(consts.starvation_damage);
    }

    if (p.health.val <= -3.0) {

        std::string code = rcode::encode(game_seed);

        state.render.do_message("You are dead. (Press space to exit.)", true);
        state.render.do_message(nlp::message("Replay code: %s", code), true);
        dead = true;
        done = true;
        return;
    }

    if (p.sleep > 0) {
        ++ticks;
        --(p.sleep);
        do_draw = true;
        return;
    }

    if (p.digging) {

        if (state.grid.is_walk(p.dig_x, p.dig_y)) {
            state.render.do_message("OOPS");
            p.digging = false;
            return;
        }

        ++ticks;
        do_draw = true;
            

        double digspeed = p.inv.get_digging();

        double& height = state.grid._get(p.dig_x, p.dig_y);

        height -= digspeed;

        if (height < -10) {
            height = -10;
            state.grid.set_walk_water(state.neigh, p.dig_x, p.dig_y, true, state.grid.is_water(p.dig_x, p.dig_y));
            state.render.invalidate(p.dig_x, p.dig_y);

            permafeats::features().add(p, p.dig_x, p.dig_y, tag_t());

            p.digging = false;
            state.render.do_message("Digging done.");
        }
    }
}


#endif
