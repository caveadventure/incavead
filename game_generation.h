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

    std::vector<grid::pt> player_positions;
    std::vector<vault_packing_t> vault_packing;

    {
        progressbar("Placing vaults...");

        state.vaults_counts = vaults().counts;

        std::set<grid::pt> affected;

        std::map<tag_t, unsigned int> vc = state.vaults_counts.take(state.rng, vaults_level, lev.number_vaults, true);

        std::map< unsigned int, std::map<tag_t, unsigned int> > s_vc;

        for (const auto& vi : vc) {
            const Vault& v = vaults().get(vi.first);

            s_vc[v.priority].insert(vi);
        }

        for (const auto& tmp : s_vc) {

            for (const auto vi : tmp.second) {

                const Vault& v = vaults().get(vi.first);

                for (unsigned int ci = 0; ci < vi.second; ++ci) {
                    generate_vault(v, state, summons, affected, vault_packing, player_positions);
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

    for (const auto& mv : state.monsters.mgrid) {
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

        for (const auto& marks : bxy) {

            const bones::pt& xy = marks.first;

            features::Feature feat;
            if (state.features.get(xy.first, xy.second, feat)) {

                const Terrain& t = terrain().get(feat.tag);

                if (t.preserve)
                    continue;
            }

            state.features.set(xy.first, xy.second, grave, state.render);
        }
    }

    // Place saved features.
    {
        auto feats = permafeats::features().get(p);

        for (const auto& i : feats) {
            unsigned int x = i.first.first;
            unsigned int y = i.first.second;
            tag_t tag = i.second.feat;
            bool walk = i.second.walk;
            bool water = i.second.water;

            features::Feature feat;
            if (state.features.get(x, y, feat)) {

                const Terrain& t = terrain().get(feat.tag);

                if (t.preserve)
                    continue;
            }

            if (tag.null()) {
                state.grid.set_walk_water(state.neigh, x, y, walk, water);

            } else {
                state.grid.set_walk_water(state.neigh, x, y, true, state.grid.is_water(x, y));
                state.features.set(x, y, tag, state.render);
            }
        }
    }


    // Initialize a known random sequence.
        
    size_t& num_visits = state.dungeon_visits_count[worldkey::key_t(p.worldx, p.worldy, p.worldz)];

    state.rng.init((game_seed + gridseed + num_visits) & 0xFFFFFFFF);

    num_visits++;

    // Place player.

    if (player_positions.empty()) {

        grid::pt xy;
        if (!maps.one_of_lowlands(state.rng, xy))
            throw std::runtime_error("Failed to generate grid");

        p.px = xy.first;
        p.py = xy.second;

        maps.add_nogen_expand(state.neigh, p.px, p.py, 3);

    } else {

        std::vector<grid::pt> pp;

        for (const auto& xy : player_positions) {

            if (state.grid.is_walk(xy.first, xy.second)) {
                pp.push_back(xy);
            }
        }

        if (pp.empty())
            throw std::runtime_error("Failed to generate grid (placement packed)");

        const grid::pt& xy = pp[state.rng.n(pp.size())];

        p.px = xy.first;
        p.py = xy.second;
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

        unsigned int items = std::max(0.0, state.rng.gauss(lev.number_items.mean, lev.number_items.deviation));

        state.items.generate(state.neigh, state.rng, state.grid, maps,
                             state.designs_counts, designs_level, items, lev.exclusive_items);


        if (p.worldx != 0 || p.worldy != 0) {

            if (p.worldx == 0 || p.worldy == 0) {

                const auto& bac = constants().bonus_a_items;

                unsigned int bonusa = std::max(0.0, state.rng.gauss(bac.mean, bac.deviation));

                state.items.generate(state.neigh, state.rng, state.grid, maps,
                                     state.bonus_designs_a_counts, designs_level, bonusa, lev.exclusive_items);

            } else {

                const auto& bbc = constants().bonus_b_items;

                unsigned int bonusb = std::max(0.0, state.rng.gauss(bbc.mean, bbc.deviation));

                state.items.generate(state.neigh, state.rng, state.grid, maps,
                                     state.bonus_designs_b_counts, designs_level, bonusb, lev.exclusive_items);
            }
        }
    }

    // Place some random monsters.

    {
        progressbar("Placing monsters...");

        for (const auto& s : summons) {
            state.monsters.summon(state.neigh, state.rng, state.grid, state.species_counts, 
                                  state.render, s.x, s.y, nullptr, nullptr, s.summontag, s.arg, false);
        }

        unsigned int mongroups = ::fabs(state.rng.gauss(lev.number_monsters.mean, lev.number_monsters.deviation));

        for (unsigned int i = 0; i < mongroups; ++i) {

            state.monsters.generate(state.neigh, state.rng, state.grid, maps,
                                    state.species_counts, species_level, lev.exclusive_monsters);
        }
    }

    for (const auto& mv : state.monsters.mgrid) {
        if (state.grid.walkmap.count(mv.first) == 0)
            throw std::runtime_error("Sanity error 4");
    }

    p.current_wx = p.worldx;
    p.current_wy = p.worldy;
    p.current_wz = p.worldz;

    progressbar("Done!");
}


#endif
