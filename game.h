#ifndef __GAME_H
#define __GAME_H


struct Game {

    Player p;

    static const unsigned int GRID_W = 256;
    static const unsigned int GRID_H = 256;

    unsigned int game_seed;

    bool debug_enabled;

    Game(bool debug) : debug_enabled(debug) {}

    void make_screen(mainloop::screen_params_t& sp) {

        sp.w = GRID_W;
        sp.h = GRID_H;
        sp.w2 = sp.w;
        sp.h2 = sp.h;
    }

    void init(unsigned int code) {

        game_seed = code;
    }

    static void make_mapname(int worldx, int worldy, int worldz, uint64_t& gridseed, std::string& filename) {

        std::ostringstream cached_grid;

        cached_grid << "_level_" << worldx << "_" << worldy << "_" << worldz << ".dat";

        gridseed = (((uint64_t)worldx) ^ 
                    ((uint64_t)worldy << 16) ^
                    ((uint64_t)worldz << 32)) + 1;

        filename = cached_grid.str();
    }

    template <typename FUNC>
    static void make_map(int worldx, int worldy, int worldz, mainloop::GameState& state,
                         uint64_t gridseed, const std::string& cached_grid,
                         FUNC progressbar) {

        state.rng.init(gridseed);

        const Levelskin& lev = levelskins().get(worldz);

        auto genparams = lev.genparams;

        if (genparams.nflatten < 0) {
            genparams.nflatten = std::max(0, 4 - 2*(worldx + worldy));
        }

        if (genparams.nunflow < 0) {
            genparams.nunflow = std::min(std::max(0, worldz), 8);
        }

        state.grid.generate(state.neigh, state.rng, genparams, progressbar);

        {
            // Having two threads generate the same level at the same time is very rare,
            // but let's put a lock in place just in case anyways.
            static std::mutex m;
            std::unique_lock<std::mutex> l(m);

            serialize::Sink sink(cached_grid);
            serialize::write(sink, state.grid);
        }
    }


    template <typename FUNC>
    void generate(mainloop::GameState& state, FUNC progressbar) {

        // Read or generate cached map.

        uint64_t gridseed;
        std::string filename;
        make_mapname(p.worldx, p.worldy, p.worldz, gridseed, filename);

        progressbar("Generating dungeon...");

        try {

            serialize::Source source(filename);
            serialize::read(source, state.grid);

        } catch (std::exception& e) {

            make_map(p.worldx, p.worldy, p.worldz, state, gridseed, filename, progressbar);
        }

        // //

        for (const auto& xy : state.grid.cornermap) {
            if (state.grid.walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 1.1");
        }

        for (const auto& xy : state.grid.lakemap) {
            if (state.grid.walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 1.2.1");

            if (state.grid.watermap.count(xy) == 0)
                throw std::runtime_error("Sanity error 1.2.2");
        }

        for (const auto& xy : state.grid.shoremap) {
            if (state.grid.walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 1.3");
        }

        state.rng.init(gridseed);


        const Levelskin& lev = levelskins().get(p.worldz);

        unsigned int species_level = (lev.species_level >= 0 ? lev.species_level : std::max(p.worldz, 0));
        unsigned int designs_level = (lev.designs_level >= 0 ? lev.designs_level : std::max(p.worldz, 0));
        unsigned int vaults_level  = (lev.vaults_level  >= 0 ? lev.vaults_level  : std::max(p.worldz, 0));


        std::vector<summons_t> summons;

        {
            progressbar("Placing vaults...");

            std::map<tag_t, unsigned int> vc = state.vaults_counts.take(state.rng, vaults_level, lev.number_vaults);

            for (const auto vi : vc) {
                const Vault& v = vaults().get(vi.first);

                for (unsigned int ci = 0; ci < vi.second; ++ci) {
                    generate_vault(v, state, summons);
                }
            }
        }

        for (const auto& xy : state.grid.cornermap) {
            if (state.grid.walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 2.1");
        }

        for (const auto& xy : state.grid.lakemap) {
            if (state.grid.walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 2.2.1");

            if (state.grid.watermap.count(xy) == 0)
                throw std::runtime_error("Sanity error 2.2.2");
        }

        for (const auto& xy : state.grid.shoremap) {
            if (state.grid.walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 2.3");
        }

        for (const auto& xy : state.grid.floormap) {
            if (state.grid.walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 2.4");
        }

        for (const auto& mv : state.monsters.mons) {
            if (state.grid.walkmap.count(mv.first) == 0)
                throw std::runtime_error("Sanity error 3");
        }

        // 
        //

        grid::Map::genmaps_t maps(state.grid);


        if (!lev.noterrain) {

            progressbar("Placing features...");

            // Place some dungeon features on the same spots every time.

            state.terrain_counts = terrain().counts;

            unsigned int featscount = ::fabs(state.rng.gauss(35.0, 5.0));

            for (unsigned int i = 0; i < featscount; ++i) {

                unsigned int takecount = ::fabs(state.rng.gauss(5.0, 1.0));

                std::map<tag_t, unsigned int> t = state.terrain_counts.take(state.rng, 0, takecount);

                for (const auto& j : t) {
                    state.features.generate(state.rng, state.grid, maps, j.first, j.second);
                }
            }
        }

        // Place bones.
        {
            progressbar("Scattering bones...");

            std::vector< std::pair<bones::pt, double> > bxy;

            bones::bones().get_marks(p.worldx, p.worldy, p.worldz, bxy);

            tag_t grave = constants().grave;

            for (const auto& marks : bxy) {

                const bones::pt& xy = marks.first;
                double worth = marks.second;

                state.features.set(xy.first, xy.second, grave, state.render);

                for (const auto& nxy : state.neigh(xy)) {

                    if (!state.grid.is_walk(nxy.first, nxy.second))
                        continue;

                    const Design& d = designs().get(constants().money);
                    unsigned int stackrange = d.stackrange;

                    while (worth >= 1) {
                        unsigned int c = (worth < stackrange ? worth : stackrange);
                        items::Item zm(constants().money, nxy, c);
                        state.items.place(nxy.first, nxy.second, zm, state.render);
                        worth -= c;
                    }

                    break;
                }
            }
        }

        // Place saved features.
        {
            auto feats = permafeats::features().get(p);

            for (const auto& i : feats) {
                state.features.set(i.first.first, i.first.second, i.second, state.render);
            }
        }


        // Place some random items.

        state.rng.init((game_seed + gridseed) & 0xFFFFFFFF);

        {
            grid::pt xy;
            if (!maps.one_of_lowlands(state.rng, xy))
                throw std::runtime_error("Failed to generate grid");

            p.px = xy.first;
            p.py = xy.second;

            maps.add_nogen_expand(state.neigh, p.px, p.py, 3);
        }


        // Place the victory item
        {
            size_t unique_series = p.dungeon_unique_series;

            if (p.worldx == 0 && p.worldy == 0 && p.worldz == 0 &&
                uniques::uniques().generate(constants().uniques_timeout, unique_series)) {

                grid::pt xy;
                if (maps.one_of_lowlands(state.rng, xy)) {

                    items::Item vi(constants().unique_item, xy, 1);
                    state.items.place(xy.first, xy.second, vi, state.render);
                }

            } else {

                std::vector<items::Item> vic = uniques::uniques().get(p.worldx, p.worldy, p.worldz, unique_series);

                for (const auto& i : vic) {
                    state.items.place(i.xy.first, i.xy.second, i, state.render);
                }
            }

            p.dungeon_unique_series = unique_series;
        }

        // Place saved items.
        {
            size_t tmp;
            std::vector<items::Item> perms = uniques::items().get(p.worldx, p.worldy, p.worldz, tmp);

            for (const auto& i : perms) {
                state.items.place(i.xy.first, i.xy.second, i, state.render);
            }
        }

        {
            progressbar("Placing items...");

            unsigned int itemgroups = ::fabs(state.rng.gauss(300.0, 50.0));

            for (unsigned int i = 0; i < itemgroups; ++i) {

                unsigned int itemcount = std::max(1.0, state.rng.gauss(1.5, 1.0));

                state.items.generate(state.neigh, state.rng, state.grid, maps,
                                     state.designs_counts, designs_level, itemcount);
            }
        }

        // Place some random monsters.

        {
            progressbar("Placing monsters...");

            for (const auto& s : summons) {
                state.monsters.summon(state.neigh, state.rng, state.grid, state.species_counts, 
                                      state.render, s.x, s.y, nullptr, nullptr, s.summontag, 0);
            }

            unsigned int mongroups = ::fabs(state.rng.gauss(250.0, 20.0));

            for (unsigned int i = 0; i < mongroups; ++i) {

                state.monsters.generate(state.neigh, state.rng, state.grid, maps,
                                        state.species_counts, species_level, lev.exclusive);
            }
        }

        for (const auto& mv : state.monsters.mons) {
            if (state.grid.walkmap.count(mv.first) == 0)
                throw std::runtime_error("Sanity error 4");
        }

        p.current_wx = p.worldx;
        p.current_wy = p.worldy;
        p.current_wz = p.worldz;

        progressbar("Done!");
    }

    void dispose(mainloop::GameState& state) {

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

        if (vic.size() > 0) {
        
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

    void endgame(mainloop::GameState& state, const std::string& name) {

        const Design& d_victory = designs().get(constants().unique_item);

        p.inv.inv_to_floor(d_victory.slot, p.px, p.py, state.items, state.render);

        dispose(state);

        bones::bones().add(name, p);
    }

    template <typename SINK>
    void save(SINK& s) {
        serialize::write(s, game_seed);
        serialize::write(s, p);
    }

    template <typename SOURCE>
    void load(SOURCE& s) {
        serialize::read(s, game_seed);
        serialize::read(s, p);

        p.current_wx = p.worldx;
        p.current_wy = p.worldy;
        p.current_wz = p.worldz;
    }



    void set_skin(mainloop::GameState& state, unsigned int x, unsigned int y) {

        bool walkable = state.grid.is_walk(x, y);
        bool water = state.grid.is_water(x, y);

        state.render.set_is_viewblock(x, y, 0, !walkable);
        state.render.set_is_walkblock(x, y, 0, !walkable);

        grender::Grid::skin s;

        double z = state.grid._get(x, y);

        const Levelskin& lev = levelskins().get(p.worldz);

        if (walkable) {
            if (water) {

                if (z <= -5) {
                    s = lev.deep_water;
                } else {
                    s = lev.shallow_water;
                }

            } else {

                if (z <= -8) {
                    s = lev.floor1;
                } else if (z <= -7) {
                    s = lev.floor2;
                } else if (z <= -6) {
                    s = lev.floor3;
                } else if (z <= -5) {
                    s = lev.floor4;
                } else if (z <= -4) {
                    s = lev.floor5;
                } else if (z <= -3) {
                    s = lev.floor6;
                } else if (z <= -2) {
                    s = lev.floor7;
                } else {
                    s = lev.floor8;
                }
            }

        } else {
            if (water) {
                s = lev.water_wall;
            } else {
                s = lev.wall;
            }
        }

        state.render.set_skin(x, y, 0, s);

        // //

        features::Feature feat;

        if (state.features.get(x, y, feat)) {

            const Terrain& t = terrain().get(feat.tag);
            state.render.set_skin(x, y, 1, t.skin);
            state.render.set_is_viewblock(x, y, 1, t.viewblock);
            state.render.set_is_walkblock(x, y, 1, t.walkblock);
            state.render.set_is_lit(x, y, 1, t.is_lit);

        } else {
            state.render.unset_skin(x, y, 1);
            state.render.set_is_viewblock(x, y, 1, false);
            state.render.set_is_walkblock(x, y, 1, false);
            state.render.set_is_lit(x, y, 1, false);
        }

        // //

        items::Item item;

        if (state.items.get(x, y, 0, item)) {

            const Design& d = designs().get(item.tag);
            state.render.set_skin(x, y, 2, d.skin);
            state.render.set_is_lit(x, y, 2, d.is_lit);

        } else {
            state.render.unset_skin(x, y, 2);
            state.render.set_is_lit(x, y, 2, false);
        }

        // //

        monsters::Monster mon;

        if (x == p.px && y == p.py) {

            s = grender::Grid::skin("@", maudit::color::bright_white, maudit::color::bright_black);
            state.render.set_skin(x, y, 5, s);

        } else if (state.monsters.get(x, y, mon)) {

            const Species& s = species().get(mon.tag);
            state.render.set_skin(x, y, 5, s.skin);
            state.render.set_is_walkblock(x, y, 5, true);

        } else {
            state.render.unset_skin(x, y, 5);
            state.render.set_is_walkblock(x, y, 5, false);
        }
    }


    void drawing_context_center_at(mainloop::drawing_context_t& ctx, unsigned int x, unsigned int y) {
        
        unsigned int grid_x = ctx.view_w / 4;
        unsigned int grid_y = ctx.view_h / 4;

        if (grid_x > 1) {
            ctx.voff_off_x = -(x % grid_x) + (grid_x / 2);
        } else {
            ctx.voff_off_x = 0;
        }

        if (grid_y > 1) {
            ctx.voff_off_y = -(y % grid_y) + (grid_y / 2);
        } else {
            ctx.voff_off_y = 0;
        }

        ctx.centerx = x;
        ctx.centery = y;
    }

    unsigned int get_lightradius() {

        const Levelskin& ls = levelskins().get(p.worldz);

        return std::min(ls.lightradius_max, ls.lightradius + p.inv.get_lightradius());
    }

    void drawing_context(mainloop::drawing_context_t& ctx) {

        ctx.px = p.px;
        ctx.py = p.py;
        ctx.lightradius = get_lightradius();

        if (p.state & Player::LOOKING) {

            if (p.look.rangemin >= 0) {
                ctx.rangemin = p.look.rangemin;
            }

            if (p.look.rangemax >= 0) {
                ctx.rangemax = p.look.rangemax;
            }

            ctx.hlx = p.look.x;
            ctx.hly = p.look.y;

            drawing_context_center_at(ctx, p.look.x, p.look.y);

        } else {
            drawing_context_center_at(ctx, p.px, p.py);
        }
    }

    void draw_one_stat(mainloop::GameState& state, const stat_t& s, const std::string& name) {

        double v = s.val;
        int vp = 0;

        if (v > 2) vp = 3;
        else if (v > 1) vp = 2;
        else if (v > 0) vp = 1;
        else if (v < -2) vp = -3;
        else if (v < -1) vp = -2;
        else if (v < 0) vp = -1;

        if (v != 0) {
            state.render.push_hud_line(name, maudit::color::dim_green,
                                       vp, '-', '+',
                                       maudit::color::dim_red, maudit::color::dim_green);
        }
    }

    void draw_hud(mainloop::GameState& state, size_t ticks) {

        draw_one_stat(state, p.health, "Health");
        draw_one_stat(state, p.food,   "Food");
        draw_one_stat(state, p.karma,  "Karma");

        std::cout << "/L " << p.luck.val << std::endl;

        if (p.luck.val > 0.1 || p.luck.val < -0.1) {
            draw_one_stat(state, p.luck, "Luck");
        }

        if (p.sleep > 0) {
            state.render.push_hud_line("Sleep", maudit::color::bright_red,
                                       std::min(p.sleep / 15 + 1, (unsigned int)6), 
                                       '+', 
                                       (ticks & 1 ? maudit::color::bright_red : maudit::color::dim_red));
        }

        if (p.digging) {

            double q = state.grid._get(p.dig_x, p.dig_y);

            q = ((q + 10) / 3.0) + 1.0;
            q = std::max(1.0, std::min(q, 6.0));

            state.render.push_hud_line("Tunnel", maudit::color::dim_green,
                                       q,
                                       '+', 
                                       (ticks & 1 ? maudit::color::bright_blue : maudit::color::dim_blue));
        }

        //state.render.push_hud_line("Foo", maudit::color::bright_yellow, 
        //                           4, '+', maudit::color::bright_green);
    }

    bool process_feature(mainloop::GameState& state, features::Feature& f, const Terrain& t) {

        if (f.decay > 0) {
            --(f.decay);

            if (f.decay == 0)
                return false;
        }

        return true;
    }

    void process_world(mainloop::GameState& state, size_t& ticks, 
                       bool& done, bool& dead, bool& regen, bool& need_input, bool& do_draw) {


        // Handle victory items.
        {
            tag_t unique_item = constants().unique_item;

            const Design& d_victory = designs().get(unique_item);

            items::Item vi;
            items::Item tmp;

            if (p.inv.take(d_victory.slot, vi)) {

                ++vi.count;

                p.food.dec(1e-5 * vi.count);

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
            }
            );


        features::Feature feat;
        if (state.features.get(p.px, p.py, feat)) {

            const Terrain& t = terrain().get(feat.tag);

            if (!t.attacks.empty()) {

                damage::defenses_t defenses;
                p.inv.get_defense(defenses);

                defend(p, defenses, p.get_computed_level(state.rng), t, state);
            }
        }

        std::vector<summons_t> summons;

        state.monsters.process(state.render, 
                               std::bind(move_monster, std::ref(p), std::ref(state), ticks, std::ref(summons),
                                         std::placeholders::_1, std::placeholders::_2, 
                                         std::placeholders::_3, std::placeholders::_4));

        state.features.process(state.render, 
                               std::bind(&Game::process_feature, this, std::ref(state),
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


        p.luck.inc(p.inv.get_luck(state.moon.pi.phase_n));

        p.food.dec(0.003);

        {
            const Levelskin& ls = levelskins().get(p.worldz);
            p.health.dec(ls.damage);
        }

        if (p.food.val <= -3.0) {
            state.render.do_message("You desperately need something to eat!", true);
            p.health.dec(0.05);
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

                p.digging = false;
                state.render.do_message("Digging done.");
            }
        }
    }

    void move_player(mainloop::GameState& state) {
        
        size_t nstack = state.items.stack_size(p.px, p.py);

        if (nstack == 1) {
            items::Item item;
            state.items.get(p.px, p.py, 0, item);
            const Design& d = designs().get(item.tag);

            state.render.do_message(nlp::message("You see %s.", nlp::count(), d, item.count));

        } else if (nstack > 1) {

            state.render.do_message(nlp::message("You see %d items here.", nstack));

        } else {
            features::Feature feat;
            if (state.features.get(p.px, p.py, feat)) {
                const Terrain& t = terrain().get(feat.tag);

                if (t.name.size() > 0) {
                    state.render.do_message(nlp::message("There is %s here.", t));
                }
            }
        }
    }

    void move(mainloop::GameState& state, int dx, int dy, size_t& ticks) {
        int nx = p.px + dx;
        int ny = p.py + dy;

        if (nx < 0 || ny < 0) 
            return;

        if (!state.neigh.linked(neighbors::pt(p.px, p.py), neighbors::pt(nx, ny)) ||
            !state.grid.is_walk(nx, ny)) {

            return;
        }

        monsters::Monster mon;
        if (state.monsters.get(nx, ny, mon)) {

            damage::attacks_t attacks;
            p.inv.get_attack(attacks);

            if (attack(p, attacks, p.get_computed_level(state.rng), state, mon)) {
                ++ticks;
            }

            return;
        }

        ++ticks;

        features::Feature feat;
        if (state.features.get(p.px, p.py, feat)) {

            const Terrain& t = terrain().get(feat.tag);

            if (t.sticky) {
                state.render.do_message("You are stuck!");

                state.features.uncharge(p.px, p.py, state.render);
                return;
            }
        }

        state.render.unset_skin(p.px, p.py, 5);

        p.px = nx;
        p.py = ny;

        state.render.set_skin(p.px, p.py, 5, 
                              grender::Grid::skin("@", maudit::color::bright_white, 
                                                  maudit::color::bright_black));

        move_player(state);
    }

    void use_terrain(mainloop::GameState& state, size_t& ticks, bool& regen, bool& done, bool& dead) {

        features::Feature feat;
        if (!state.features.get(p.px, p.py, feat)) {
            state.render.do_message("There is nothing here to use.");
            return;
        }

        const Terrain& t = terrain().get(feat.tag);


        if (!t.victory_item.null()) {

            const Design& d_victory = designs().get(t.victory_item);

            items::Item vi;

            if (p.inv.take(d_victory.slot, vi)) {

                state.render.do_message("Congratulations! (press space to close window)", true);
                state.render.do_message(" ~*~   You win the game!   ~*~ ", true);

                // HACK!
                p.attacker = "VICTORY";
                done = true;
                dead = true;

                return;
            }
        }

        if (feat.tag == constants().grave) {

            state.push_window(tombstone_text(), screens_t::tombstone);
            return;
        }

        if (t.stairs != 0) {

            if (t.stairs > 0) {
                state.render.do_message("You climb down the hole.");
            } else {
                state.render.do_message("You are magically teleported!");
            }

            p.worldz += t.stairs;

            ++ticks;
            regen = true;
            return;
        }

        if (t.tunnel_x != 0 || t.tunnel_y != 0) {
            state.render.do_message("You climb into the tunnel.");
            p.worldx += t.tunnel_x;
            p.worldy += t.tunnel_y;

            if (p.worldx > 1) p.worldx = -1;
            else if (p.worldx < -1) p.worldx = 1;

            if (p.worldy > 1) p.worldy = -1;
            else if (p.worldy < -1) p.worldy = 1;

            ++ticks;
            regen = true;
            return;
        }

        if (t.grant_spell.timeout > 0) {

            const auto& sp = t.grant_spell;

            if ((sp.karma_bound < 0 && p.karma.val <= sp.karma_bound) ||
                (sp.karma_bound > 0 && p.karma.val >= sp.karma_bound)) {

                for (const auto& i : p.spells) {
                    if (i.name == sp.name) {
                        state.render.do_message("Nothing happens.");
                        return;
                    }
                }

                p.spells.push_back(sp);
                state.render.do_message(nlp::message("You are granted the power of %s.", sp.name), true);

            } else {
                state.render.do_message("You want nothing to do with this vile thing.");
            }

            return;
        }

        state.render.do_message("There is nothing here to use.");
    }

    void rest(mainloop::GameState& state, size_t& ticks) {

        ++ticks;
    }

    void seed_celauto(mainloop::GameState& state, 
                      unsigned int _x, unsigned int _y, tag_t tag) {

        const CelAuto& ca = celautos().get(tag);

        for (const auto& dxy : ca.seed) {

            int x = _x + dxy.first;
            int y = _y + dxy.second;

            if (x < 0 || y < 0 || x > (int)state.neigh.w || y > (int)state.neigh.h)
                continue;

            state.camap.seed(state.neigh, celauto::pt(x, y), tag);
        }
    }

    std::string show_spells(std::vector<Terrain::spell_t>& spells) {

        std::string m;

        m = "\2Your arcane powers:\n\n";

        char z = 'a';
        for (const auto& sp : spells) {

            m += nlp::message("   \2%c\1) %S\n", z, sp);
            ++z;
        }

        return m;
    }

    void handle_input_spells(mainloop::GameState& state, size_t& ticks, maudit::keypress k) {

        int z = k.letter - 'a';

        if (z < 0 || z >= (int)p.spells.size()) {
            state.window_stack.pop_back();
            return;
        }

        const auto& sp = p.spells[z];

        seed_celauto(state, p.px, p.py, sp.ca_tag);        
        ++ticks;
        state.window_stack.pop_back();
    }


    std::string help_text() {

        std::string ret = 
            "\3Essential commands:\1\n"
            "  \2h j k l\1 "
            "  \2arrow keys\1 : Move left, down, up and right.\n"
            "  \2y u b n\1 "
            "  \2keypad\1 :     Move diagonally.\n"
            "  \2.\1 :          Stand still.\n"
            "  \2S\1 :          Save and quit.\n"
            "  \2Q\1 :          Commit suicide and quit.\n"
            "  \2>\1 :          Use terrain. (Enter holes and tunnels, use statues.)\n"
            "  \2i\1 :          Interact with inventory, use items and show character info.\n"
            "  \2z\1 :          Cast spells if you know them.\n"
            "  \2/\1 :          Look around you using arrow keys.\n"
            "  \2tab\1 :        Look at monsters and items in view.\n"
            "  \2P\1 :          Show message history.\n"
            "  \2?\1 :          Show this help message.\n"
            "\n\3Shortcut commands:\1\n"
            "  \2T\1 :          Take the first item laying on the floor.\n"
            "  \2,\1 :          Examine the first item laying on the floor.\n"
            ;

        for (const auto& shortcut : constants().shortcuts) {
            ret += "  \2";
            ret += shortcut.first;
            ret += "\1 :          ";
            ret += shortcut.second.help_message;
            ret += '\n';
        }

        return ret;
    }

    std::string tombstone_text() {

        bones::bone_t bone;

        if (!bones::bones().get(p, bone)) {

            return "\n\nHm, this tombstone is blank...";
        }

        if (bone.name.name.empty())
            bone.name.name = "anonymous";

        if (bone.cause.name.empty())
            bone.cause.name = "unnatural causes";

        return nlp::message("\n\n"
                            "    \2.--==~  Here lies \3%S\2  ~==--.\n\n"
                            "    \1He was a valiant adventurer of level \2%d\1.\n"
                            "    \1He was killed by \2%s\1.\n"
                            "    \1His net worth was \2%d\1 zorkmids.\n\n"
                            "    \1May ye rest in peace.",
                            bone.name,
                            bone.level+1, 
                            bone.cause, 
                            bone.worth);
    }

    void handle_input_main(mainloop::GameState& state,
                           size_t& ticks, bool& done, bool& dead, bool& regen, 
                           maudit::keypress k) {

        bool redraw = false;

        switch (k.letter) {
        case 'Q':
            state.render.do_message("You quit the game. (Press space to exit.)", true);
            p.attacker = "suicide";
            done = true;
            dead = true;
            break;

        case 'S':
            state.render.do_message("Your game has been saved. (Press space to exit.)", true);
            done = true;
            dead = false;
            break;

        case 'h':
            move(state, -1, 0, ticks);
            break;
        case 'j':
            move(state, 0, 1, ticks);
            break;
        case 'k':
            move(state, 0, -1, ticks);
            break;
        case 'l':
            move(state, 1, 0, ticks);
            break;
        case 'y':
            move(state, -1, -1, ticks);
            break;
        case 'u':
            move(state, 1, -1, ticks);
            break;
        case 'b':
            move(state, -1, 1, ticks);
            break;
        case 'n':
            move(state, 1, 1, ticks);
            break;

        case '>':
        case '<':
            use_terrain(state, ticks, regen, done, dead);
            break;

        case '.':
            rest(state, ticks);
            break;

        case 'T':
            take_item(p.px, p.py, 0, p, state, ticks);
            break;

        case ',':
            if (state.items.stack_size(p.px, p.py) == 0) {
                state.render.do_message("There are no items here.");

            } else {
                state.push_window(select_floor_item(p.inv, state.items, p.px, p.py, 0), screens_t::floor_item);
            }
            break;

        case 'i':
            state.push_window(show_inventory(p.inv, p.level, 
                                             levelskins().get(p.worldz).name, 
                                             state.moon.pi.phase_str, 
                                             state.items, p.px, p.py), 
                              screens_t::inventory);
            break;

        case 'z':
            state.push_window(show_spells(p.spells), screens_t::spells);
            break;

        case 'P':
            state.push_window(state.render.all_messages(), screens_t::messages);
            break;

        case '/':
            start_look_plain(p.state, p.look, p.px, p.py, state);
            break;

        case '\t':
            start_look_cycle(p.state, p.look, p.px, p.py, state, k);
            break;

        case '?':
            state.push_window(help_text(), screens_t::help);
            break;

            // WATCH OUT!
        case '!':
            if (debug_enabled) {
                p.state = Player::DEBUG;
            }
            break;

        default:
            break;
        }

        switch (k.key) {
        case maudit::keycode::up:
            move(state, 0, -1, ticks);
            break;
        case maudit::keycode::left:
            move(state, -1, 0, ticks);
            break;
        case maudit::keycode::right:
            move(state, 1, 0, ticks);
            break;
        case maudit::keycode::down:
            move(state, 0, 1, ticks);
            break;
        case maudit::keycode::kp_7:
            move(state, -1, -1, ticks);
            break;
        case maudit::keycode::kp_9:
            move(state, 1, -1, ticks);
            break;
        case maudit::keycode::kp_1:
            move(state, -1, 1, ticks);
            break;
        case maudit::keycode::kp_3:
            move(state, 1, 1, ticks);
            break;
        default:
            break;
        }            

        {
            const auto& shortcut = constants().shortcuts.find(k.letter);

            if (shortcut != constants().shortcuts.end()) {

                bool ok = false;
                for (const auto& slot_keypress : shortcut->second.slot_keypress) {

                    p.inv.selected_slot = slot_keypress.first;
                    if (handle_input_inv_item(p, state, ticks, done, dead, regen, 
                                              maudit::keypress(slot_keypress.second))) {
                        ok = true;
                        break;
                    }
                }

                if (!ok) {
                    state.render.do_message(shortcut->second.fail_message);
                }
            }
        }

        if (redraw) {
            state.render.clear();
        }
    }


    void handle_input_debug(mainloop::GameState& state, size_t& ticks, bool& regen, maudit::keypress k) {

        switch (k.letter) {

        case 's':
            state.species_counts = species().counts;
            state.render.do_message("Wiped species counts.");
            break;

        case 'd':
            state.designs_counts = designs().counts;
            state.render.do_message("Wiped designs counts.");
            break;

        case '>':
            p.worldz++;
            regen = true;
            state.render.do_message("Descended.");
            break;

        case '<':
            p.worldz--;
            regen = true;
            state.render.do_message("Ascended.");
            break;

        case 't':
        {
            grid::pt xy;
            if (state.grid.one_of_walk(state.rng, xy)) {

                state.render.invalidate(p.px, p.py);
                p.px = xy.first;
                p.py = xy.second;
                state.render.invalidate(p.px, p.py);
            }
            break;
        }

        case '.':
            state.render.do_message(nlp::message("%d %d", p.px, p.py));
            break;

        case '+':
            p.level++;
            state.render.do_message("Level gained.");
            break;

        case 'i':
        {
            std::map<tag_t, unsigned int> q = state.designs_counts.take(state.rng, p.worldz, 1);

            if (q.size() == 1) {
                state.items.place(p.px, p.py, 
                                  state.items.make_item(q.begin()->first, items::pt(p.px, p.py), state.rng),
                                  state.render);
            }
            break;
        }

        case 'z':
        {
            for (const auto& c : celautos().bank) {
                Terrain::spell_t s;
                s.karma_bound = 0;
                s.ca_tag = c.first;
                s.timeout = 9999;
                p.spells.push_back(s);
            }
            state.render.do_message("Granted spells.");
            break;
        }

        }

        p.state &= ~(Player::DEBUG);
    }


    void handle_input_pick_direction(unsigned int& pstate, unsigned int px, unsigned int py, size_t& ticks,
                                     mainloop::GameState& state, maudit::keypress k) {

        unsigned int nx = px;
        unsigned int ny = py;

        switch (k.letter) {
        case 'h':
            nx--;
            break;
        case 'j':
            ny++;
            break;
        case 'k':
            ny--;
            break;
        case 'l':
            nx++;
            break;
        case 'y':
            nx--;
            ny--;
            break;
        case 'u':
            nx++;
            ny--;
            break;
        case 'b':
            nx--;
            ny++;
            break;
        case 'n':
            nx++;
            ny++;
            break;

        default:
            break;
        }

        switch (k.key) {
        case maudit::keycode::up:
            ny--;
            break;
        case maudit::keycode::left:
            nx--;
            break;
        case maudit::keycode::right:
            nx++;
            break;
        case maudit::keycode::down:
            ny++;
            break;

        default:
            break;
        }            

        if (!state.neigh.linked(neighbors::pt(px, py), neighbors::pt(nx, ny))) {

            pstate = Player::MAIN;
            return;
        }

        if (pstate & Player::DIGGING) {

            if (state.grid.is_walk(nx, ny)) {
                state.render.do_message("There is nothing to dig there.");

            } else {
                state.render.do_message("You start digging.");
                p.digging = true;
                p.dig_x = nx;
                p.dig_y = ny;
                ++ticks;
            }

            pstate = Player::MAIN;
        }
    }

    void handle_input_messages(mainloop::GameState& state, maudit::keypress k) {

        state.window_stack.pop_back();
    }

    void handle_input(mainloop::GameState& state,
                      size_t& ticks, bool& done, bool& dead, bool& regen, 
                      maudit::keypress k) {

        if (p.state == Player::DEBUG) {
            handle_input_debug(state, ticks, regen, k);
            return;
        }

        if (p.state & Player::LOOKING) {

            handle_input_looking(p.state, p.look, p.px, p.py, state, k);

            if (p.state & Player::FIRED) {

                if (p.state & Player::THROWING) {
                    end_throw_item(p, p.inv.selected_slot, p.look.x, p.look.y, state);

                } else if (p.state & Player::BLASTING) {
                    end_blast_item(p, p.inv.selected_slot, p.look.x, p.look.y, state);
                }

                ++ticks;
                p.state = Player::MAIN;
            }

            return;
        }

        if (p.state & Player::PICK_DIRECTION) {

            handle_input_pick_direction(p.state, p.px, p.py, ticks, state, k);
            return;
        }

        if (state.window_stack.empty()) {
            handle_input_main(state, ticks, done, dead, regen, k);
            return;
        }

        switch ((screens_t)state.window_stack.back().type) {

        case screens_t::messages:
        case screens_t::help:
        case screens_t::tombstone:
            handle_input_messages(state, k);
            break;

        case screens_t::inventory:
            handle_input_inventory(p, state, ticks, done, dead, regen, k);
            break;

        case screens_t::inv_item:
            handle_input_inv_item(p, state, ticks, done, dead, regen, k);
            break;

        case screens_t::floor_item:
            handle_input_floor_item(p, state, ticks, done, dead, regen, k);
            break;

        case screens_t::spells:
            handle_input_spells(state, ticks, k);
            break;
        }
    }
};



#endif
