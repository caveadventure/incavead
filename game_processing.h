#ifndef __GAME_PROCESSING_H
#define __GAME_PROCESSING_H

#include <valarray>


void add_ailments(Player& p, GameState& state) {

    const auto& ailments = constants().ailments;

    if (ailments.empty())
        return;

    unsigned int num_ails = p.num_replay_codes / 2;

    num_ails = std::min(num_ails, constants().max_ailments);

    for (unsigned int i = 0; i < num_ails; ++i) {

        size_t na = state.rng.n(ailments.size());

        auto a = ailments.begin();
        while (na > 0) {
            ++a;
            --na;
        }

        const auto& ailment = a->second;

        p.add_ailment(state.rng, a->first, ailment.triggers);
    }

    if (num_ails > 0) {

        std::string& msg = state.triggers[1].message.message;
        state.triggers[1].message.important = true;

        switch (num_ails) {
        case 1:
            msg = "This reincarnation of your body seems frail. (Press '@')";
            break;
        case 2:
            msg = "This reincarnation of your body is very frail.";
            break;
        case 3:
            msg = "This reincarnation of your body is extremely fragile.";
            break;
        default:
            msg = "This reincarnation of your body is no good at all.";
            break;
        }
    }
}

void Game::init(GameState& state, unsigned int address, unsigned int seed) {

    game_seed = seed;

    // Figure out how many replay codes were used.

    p.num_replay_codes = bones::bones().get_replay_code_count(address, seed);

    // Add some ailments.

    add_ailments(p, state);

    // Calculate the player's starsign.
    // The zero date of July 30 2012 is the mythological date of first git commit in this repo. :)

    const auto& starsigns = constants().starsigns;

    p.starsign.init(seed, starsigns.zero, starsigns.nday, starsigns.nsign);

    // Change item counts based on moon phase, item flavor and starsign.

    const auto& fmf = constants().flavor_moon_frequency;
    double phase = state.moon.pi.phase_n;

    const auto& starsign = p.starsign;

    state.designs_counts.change_counts(
        [&](tag_t tag, unsigned int count) {

            const Design& d = designs().get(tag);

            tag_t flavor = d.flavor;

            auto i = fmf.find(flavor);

            double mult = 1.0;

            if (i != fmf.end()) {
            
                const auto& f = i->second;
            
                mult = 
                    gaussian_function(f.height, f.mean, f.deviation, phase) +
                    gaussian_function(f.height, f.mean, f.deviation, 1.0 - phase);
            }

            if (d.starsign.sign > 0 && d.starsign.sign != starsign.sign) {
                count = -1;

            } else if (d.starsign.day > 0) {

                count -= std::abs(d.starsign.day - starsign.day);
            }

            count = mult * count;

            if (count == 0) {
                count = 1;

            } else if (count < 0) {
                count = 0;
            }

            return count;
        });
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

void Game::endgame(GameState& state, const std::string& name, unsigned int address, unsigned int seed) {

    // HACK. 
    // The special player name of '_' will not leave highscores or bones.

    if (name != "_") {
        std::string polyform;

        if (!p.polymorph_species.null()) {
            polyform = nlp::message(" %s", species().get(p.polymorph_species));
        }

        bones::bones().add(name, p, constants().achievements, polyform, address, seed);
    }

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

    int radius = get_lightradius(p, state) + 1;

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
                                             range, &p.px, &p.py, monster, count, false);

    return res;
}

inline bool give_change(GameState& state, unsigned int x, unsigned int y, double amount) {

    if (amount <= constants().min_money_value)
        return false;

    std::map< double, std::pair<double, tag_t> > currencies;

    for (const auto& i : constants().money) {

        const Design& m = designs().get(i);

        currencies[m.worth * m.stackrange] = std::make_pair(m.worth, i);
    }

    if (currencies.empty())
        return false;

    for (const auto& i : currencies) {
        if (amount <= i.first) {

            items::Item zm(i.second.second, items::pt(x, y), 
                           std::max(1u, (unsigned int)(amount / i.second.first)));
            state.items.place(x, y, zm, state.render);
            return true;
        }
    }

    tag_t maxc = currencies.rbegin()->second.second;
    const Design& m = designs().get(maxc);

    items::Item zm(maxc, items::pt(x, y), m.stackrange);
    state.items.place(x, y, zm, state.render);

    return true;
}

void finish_digging(const Player& p, GameState& state, unsigned int x, unsigned int y, double h) {

    features::Feature feat;

    if (!state.grid.is_walk(x, y)) {
            
        bool water = state.grid.is_water(x, y);

        state.grid.set_walk_water(state.neigh, x, y, true, water);
        state.render.invalidate(x, y);

        permafeats::features().add(p, x, y, true, water);

    } else if (state.features.get(x, y, feat) && feat.tag == constants().grave) {

        state.features.set(x, y, constants().bad_grave, state.render);        
        permafeats::features().add(p, x, y, constants().bad_grave);

        bones::bone_t bone;

        if (!bones::bones().get(p, x, y, bone))
            return;

        auto& trig = state.triggers[state.ticks];

        trig.summon_genus.genus = constants().ghost;
        trig.summon_genus.level = bone.level;
        trig.summon_genus.count = 1;
        trig.summon_genus.x = x;
        trig.summon_genus.y = y;

        give_change(state, x, y, bone.worth);

    } else {

        state.features.set(x, y, constants().pit, state.render);        
        permafeats::features().add(p, x, y, constants().pit);
                
        const Levelskin& ls = levelskins().get(p.worldz);

        if (!ls.has_treasure)
            return;
                
        const auto& tc = constants().treasure_chance;
        double lev = state.rng.gauss(h + tc.mean, tc.deviation);

        if (lev < 0 || lev + ls.treasure_level < 0)
            return;

        int tlev = lev + ls.treasure_level;

        auto is = state.designs_counts.take(state.rng, tlev);

        for (const auto& ii : is) {
            items::Item made = state.items.make_item(ii.first, items::pt(x, y), state.rng);
            state.items.place(x, y, made, state.render);

            state.render.do_message(nlp::message("You found %s!", nlp::count(), 
                                                 designs().get(made.tag), made.count));
        }
    }
}


void do_digging_step(Player& p, GameState& state) {

    double digspeed = p.inv.get_digging();

    double& height = state.grid._get(p.dig.x, p.dig.y);

    height -= digspeed;

    if (height < -10) {
        height = -10;

        p.digging = false;
        state.render.do_message("Digging done.");

        finish_digging(p, state, p.dig.x, p.dig.y, p.dig.h);
    }
}

void Game::process_world(GameState& state, 
                         bool& done, bool& dead, bool& regen, bool& need_input, bool& do_draw) {


    // Ailments.

    if (p.ailments.size() > 0) {

        unsigned int t = state.rng.range(0u, 99u);

        auto a = p.ailments.find(t);

        if (a != p.ailments.end()) {

            auto b = constants().ailments.find(a->second);

            if (b != constants().ailments.end()) {

                size_t n = defend(p, b->second, state);

                if (b->second.oneshot && n > 0) {
                    p.ailments.erase(a);
                }
            }
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


    bool terrain_immune = false;

    if (!p.polymorph_species.null()) {

        terrain_immune = species().get(p.polymorph_species).flags.terrain_immune;
    }


    features::Feature feat;
    if (!terrain_immune && state.features.get(p.px, p.py, feat)) {

        const Terrain& t = terrain().get(feat.tag);

        if (!t.attacks.empty()) {

            damage::defenses_t defenses;
            p.get_defense(defenses);

            defend(p, defenses, p.get_computed_level(state.rng), t, state);

            if (t.uncharge.attack) {
                state.features.uncharge(p.px, p.py, state.render);
            }
        }
    }

    if (state.triggers.size() > 0) {
        
        auto i = state.triggers.begin();

        while (i != state.triggers.end() && i->first <= state.ticks) {

            const auto& trig = i->second;

            if (!trig.summon_out_of_view.monster.null()) {

                unsigned int n = summon_out_of_view(p, state, 
                                                    trig.summon_out_of_view.monster, 
                                                    trig.summon_out_of_view.count);

                if (n == 0) {
                    ++i;
                    continue;
                }
            }

            if (trig.summon_genus.count > 0) {

                const auto& sg = trig.summon_genus;

                unsigned int n = state.monsters.summon_genus(state.neigh, state.rng, state.grid, state.species_counts,
                                                             state.render, 
                                                             sg.x, sg.y, &p.px, &p.py, 
                                                             sg.genus, sg.level, sg.count);

                if (n == 0) {
                    ++i;
                    continue;
                }
            }

            if (trig.message.message.size() > 0) {

                state.render.do_message(trig.message.message, trig.message.important);
            }
            
            i = state.triggers.erase(i);
        }
    }

    std::vector<summons_t> summons;

    state.monsters.process(state.render, 
                           std::bind(move_monster, std::ref(p), std::ref(state), std::ref(summons),
                                     std::placeholders::_1, std::placeholders::_2, 
                                     std::placeholders::_3, std::placeholders::_4));

    state.features.process(state.render, 
                           std::bind(process_feature, std::ref(state),
                                     std::placeholders::_1, std::placeholders::_2));

    for (const auto& i : summons) {

        unsigned int nm = 0;

        if (i.summontag.null()) {
            nm = state.monsters.summon_any(state.neigh, state.rng, state.grid, state.species_counts, state.render,
                                           i.x, i.y, &p.px, &p.py, i.arg, 1);

        } else {
            nm = state.monsters.summon(state.neigh, state.rng, state.grid, state.species_counts, state.render, 
                                       i.x, i.y, &p.px, &p.py, i.summontag, 1, false);
        }

        if (nm > 0 && state.render.is_in_fov(i.x, i.y) && i.msg.size() > 0) {

            if (i.summontag.null()) {
                state.render.do_message(nlp::message(i.msg, species().get(i.summonertag)));

            } else {
                state.render.do_message(nlp::message(i.msg, species().get(i.summonertag), 
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
        
    p.inv.process_inventory(state.moon.pi.phase_n, inc_luck, inc_hunger, inc_shield);

    p.luck.inc(inc_luck);

    if (p.health.shield < consts.health_shield_max) {
        p.health.shield += inc_shield;
    }

    p.food.dec(consts.hunger_rate + inc_hunger);

    {
        const Levelskin& ls = levelskins().get(p.worldz);

        if (!ls.damage_terrain.null() && p.health.val > -3.0) {

            // HACK. Assume player level is always 0.
            // This is how it should be when the damage is actually coming from 
            // the environment itself.

            damage::defenses_t defenses;
            p.get_defense(defenses);

            defend(p, defenses, 0, terrain().get(ls.damage_terrain), state);
        }
    }

    if (p.blind > 0) {
        --(p.blind);
    }

    if (p.polymorph_turns > 0) {
        --(p.polymorph_turns);

        if (p.polymorph_turns == 0) {
            p.polymorph_species = tag_t();
            state.render.invalidate(p.px, p.py);
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
        ++(state.ticks);
        --(p.sleep);
        do_draw = true;
        return;
    }

    if (p.digging) {

        ++(state.ticks);
        do_draw = true;            

        do_digging_step(p, state);
    }
}

void genocide(GameState& state, tag_t genus) {

    state.species_counts.change_counts(
        [genus](tag_t sp, unsigned int count) { 
            if (species().get(sp).genus == genus) {
                return 0u;
            } else {
                return count;
            }
        });
}

inline size_t longest_common_subsequence(const std::string& a, const std::string& b) {
    
    size_t w = b.size() + 1;
    size_t h = a.size() + 1;

    std::valarray<size_t> c(w * h);

    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < b.size(); ++j) {

            size_t ix = w * (i + 1) + (j + 1);

            if (a[i] == b[j]) {
                c[ix] = c[w * i + j] + 1;
            } else {
                c[ix] = std::max(c[w * (i + 1) + j], c[w * i + (j + 1)]);
            }
        }
    }

    return c[w * h - 1];
}


inline tag_t find_existing_item_search(GameState& state, const std::string& name, bool forbid_luck = true) {

    const auto& data = state.designs_counts.data;

    size_t maxlcs = 0;
    std::vector<double> counts;
    std::vector<tag_t> desgns;

    for (const auto& i : data) {
        for (const auto& j : i.second) {

            const Design& _design = designs().get(j.first);

            // HACK
            if (forbid_luck && (_design.luck.size() > 0 || _design.consume_luck > 0))
                continue;

            if (_design.forbid_wish)
                continue;

            size_t lcs = longest_common_subsequence(_design.name, name);

            if (lcs < maxlcs)
                continue;

            if (lcs > maxlcs) {
                maxlcs = lcs;
                counts.clear();
                desgns.clear();
            }

            counts.push_back(j.second);
            desgns.push_back(j.first);
        }
    }

    while (1) {

        if (counts.empty()) {
            return tag_t();
        }

        std::discrete_distribution<unsigned int> d(counts.begin(), counts.end());
        unsigned int ntag = d(state.rng.gen);

        tag_t design = desgns[ntag];

        return design;
    }
}


inline void find_existing_item_make(GameState& state, unsigned int px, unsigned int py, tag_t design) {

    unsigned int trucount = state.designs_counts.take(design);

    if (trucount == 0) {
        state.render.do_message("Strange. Nothing happened.");
        return;
    }

    const Design& _design = designs().get(design);

    items::Item made = state.items.make_item(design, items::pt(px, py), state.rng);
    state.items.place(px, py, made, state.render);

    state.render.do_message(nlp::message("You see %s.", nlp::count(), _design, made.count));
}

inline bool find_existing_item(GameState& state, unsigned int px, unsigned int py, const std::string& name) {

    tag_t d = find_existing_item_search(state, name);

    if (d.null()) {
        state.render.do_message("Strange. Nothing happened.");
        return false;
    }

    find_existing_item_make(state, px, py, d);

    return true;
}


inline bool find_any_item(GameState& state, Player& p, unsigned int px, unsigned int py, const std::string& name) {

    const auto& d = designs();

    size_t maxlcs = 0;    
    std::vector<tag_t> desgns;

    for (const auto& i : d.bank) {

        const Design& _design = designs().get(i.first);

        if (_design.wishing)
            continue;

        size_t lcs = longest_common_subsequence(_design.name, name);

        if (lcs < maxlcs)
            continue;

        if (lcs > maxlcs) {
            maxlcs = lcs;
            desgns.clear();
        }

        desgns.push_back(i.first);
    }

    if (desgns.empty()) {
        state.render.do_message("Strange. Nothing happened.");
        return false;
    }

    tag_t design = desgns[state.rng.n(desgns.size())];
    const Design& _design = designs().get(design);

    items::Item made = state.items.make_item(design, items::pt(px, py), state.rng);

    // HACK
    if (design == constants().unique_item) {
        p.uniques_disabled = true;

        // TODO Really this is just a way to hardcode a value.
        made.count = 0.5/_design.hunger;
    }

    state.items.place(px, py, made, state.render);

    state.render.do_message(nlp::message("You see %s.", nlp::count(), _design, made.count));
    return true;
}


inline bool simple_wish(GameState& state, Player& p, const std::string& wish) {

    if (wish.empty())
        return true;

    bool ok = find_existing_item(state, p.px, p.py, wish);

    if (ok) {
        p.karma.shield = 6;
        p.luck.dec(6);
    }

    return ok;
}

inline bool special_wish(GameState& state, Player& p, const std::string& wish) {

    return find_any_item(state, p, p.px, p.py, wish);
}

#endif
