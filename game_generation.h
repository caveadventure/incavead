#ifndef __GAME_GENERATION_H
#define __GAME_GENERATION_H

void make_mapname(int worldx, int worldy, int worldz, uint64_t& gridseed, std::string& filename) {

    std::ostringstream cached_grid;

    cached_grid << "_level_" << worldx << "_" << worldy << "_" << worldz << ".dat";

    gridseed = (((uint64_t)worldx) ^ 
                ((uint64_t)worldy << 16) ^
                ((uint64_t)worldz << 32)) + 1;

    filename = cached_grid.str();
}

template <typename FUNC>
void make_map(int worldx, int worldy, int worldz, GameState& state,
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
void Game::generate(GameState& state, FUNC progressbar) {

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

    for (const auto& xy : state.grid.floormap) {
        if (state.grid.watermap.count(xy) != 0)
            throw std::runtime_error("Sanity error 1.4");
    }

    state.rng.init(gridseed);


    const Levelskin& lev = levelskins().get(p.worldz);

    unsigned int species_level = (lev.species_level >= 0 ? lev.species_level : std::max(p.worldz, 0));
    unsigned int designs_level = (lev.designs_level >= 0 ? lev.designs_level : std::max(p.worldz, 0));
    unsigned int vaults_level  = (lev.vaults_level  >= 0 ? lev.vaults_level  : std::max(p.worldz, 0));


    std::vector<summons_t> summons;

    bool did_place_player = false;

    {
        progressbar("Placing vaults...");

        state.vaults_counts = vaults().counts;

        std::set<grid::pt> affected;

        std::map<tag_t, unsigned int> vc = state.vaults_counts.take(state.rng, vaults_level, lev.number_vaults, true);

        for (unsigned int priority = 0; priority <= 1; ++priority) {

            for (const auto vi : vc) {
                const Vault& v = vaults().get(vi.first);

                if (v.priority != priority)
                    continue;

                for (unsigned int ci = 0; ci < vi.second; ++ci) {

                    generate_vault(v, state, summons, affected, did_place_player, p.px, p.py);
                }
            }

            vault_generation_cleanup(state, affected);
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

    for (const auto& xy : state.grid.floormap) {
        if (state.grid.watermap.count(xy) != 0)
            throw std::runtime_error("Sanity error 2.5");
    }

    for (const auto& mv : state.monsters.mons) {
        if (state.grid.walkmap.count(mv.first) == 0)
            throw std::runtime_error("Sanity error 3");
    }

    // 
    //

    grid::Map::genmaps_t maps(state.grid);


    {
        progressbar("Placing features...");

        // Place some dungeon features on the same spots every time.

        state.terrain_counts = terrain().counts;

        unsigned int featscount = ::fabs(state.rng.gauss(lev.number_features.mean, lev.number_features.deviation));

        for (unsigned int i = 0; i < featscount; ++i) {

            unsigned int takecount = 1;

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

        double net_worth = 0;

        for (const auto& marks : bxy) {
            net_worth += marks.second;
        }

        for (const auto& marks : bxy) {

            const bones::pt& xy = marks.first;
            double worth = marks.second;

            state.features.set(xy.first, xy.second, grave, state.render);

            if (net_worth <= 0 || worth < 0)
                continue;

            worth = std::min(net_worth, std::min(worth, (double)constants().max_gold_per_grave));
            net_worth -= worth;

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
            unsigned int x = i.first.first;
            unsigned int y = i.first.second;
            tag_t tag = i.second;

            state.grid.set_walk_water(state.neigh, x, y, true, state.grid.is_water(x, y));

            if (!tag.null())
                state.features.set(x, y, tag, state.render);
        }
    }


    // Initialize a known random sequence.
        
    size_t& num_visits = state.dungeon_visits_count[worldkey::key_t(p.worldx, p.worldy, p.worldz)];

    state.rng.init((game_seed + gridseed + num_visits) & 0xFFFFFFFF);

    num_visits++;

    // Place player.

    if (!did_place_player) {
        grid::pt xy;
        if (!maps.one_of_lowlands(state.rng, xy))
            throw std::runtime_error("Failed to generate grid");

        p.px = xy.first;
        p.py = xy.second;

        maps.add_nogen_expand(state.neigh, p.px, p.py, 3);
    }


    // Place the victory item
    if (!p.uniques_disabled) {

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

    // Place some random items.

    {
        progressbar("Placing items...");

        unsigned int itemgroups = ::fabs(state.rng.gauss(lev.number_items.mean, lev.number_items.deviation));

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

        unsigned int mongroups = ::fabs(state.rng.gauss(lev.number_monsters.mean, lev.number_monsters.deviation));

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


#endif
