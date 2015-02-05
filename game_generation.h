#ifndef __GAME_GENERATION_H
#define __GAME_GENERATION_H


inline std::string make_mapname(int worldx, int worldy, int worldz) {

    std::ostringstream cached_map;

    cached_map << "_level_" << worldx << "_" << worldy << "_" << worldz << ".dat";

    return cached_map.str();
}

inline uint64_t make_fixedseed(int worldx, int worldy, int worldz) {

    uint64_t ret = (((uint64_t)worldx) ^ 
                    ((uint64_t)worldy << 16) ^
                    ((uint64_t)worldz << 32)) + 1;

    return ret;
}

template <typename FUNC>
void make_map(int worldx, int worldy, int worldz, GameState& state, const Levelskin& lev, FUNC progressbar) {

    auto genparams = lev.genparams;

    if (genparams.nflatten_walk < 0) {
        genparams.nflatten_walk = std::max(0, 5 - 2*(worldx + worldy));
    }

    if (genparams.nflatten_water < 0) {
        genparams.nflatten_water = std::max(0, 3 - 2*(worldx + worldy));
    }

    if (genparams.nunflow < 0) {
        genparams.nunflow = std::min(std::max(0, worldz), 8);
    }

    state.grid.generate(state.neigh, state.rng, genparams, progressbar);
}


inline void generate_vaults(GameState& state, grid::Map::genmaps_t& ptsource, 
                            unsigned int vaults_level, unsigned int number_vaults, Vault::type_t type,
                            std::vector<summons_t>& summons,
                            std::vector<itemplace_t>& itemplace,
                            std::vector<grid::pt>& player_positions,
                            std::vector<vault_packing_t>& vault_packing) {

    std::set<grid::pt> affected;

    counters::Counts vaults_counts;

    switch (type) {
    case Vault::type_t::FIXED:
        vaults_counts = vaults().fixed_counts;
        break;
    case Vault::type_t::SEMIRANDOM:
        vaults_counts = vaults().semirandom_counts;
        break;
    case Vault::type_t::RANDOM:
        vaults_counts = vaults().random_counts;
        break;
    }

    std::map<tag_t, unsigned int> vc = vaults_counts.take(state.rng, vaults_level, number_vaults, true);

    std::map< unsigned int, std::map<tag_t, unsigned int> > s_vc;

    for (const auto& vi : vc) {
        const Vault& v = vaults().get(vi.first);

        s_vc[v.priority].insert(vi);
    }

    for (const auto& tmp : s_vc) {

        for (const auto vi : tmp.second) {

            const Vault& v = vaults().get(vi.first);

            for (unsigned int ci = 0; ci < vi.second; ++ci) {
                generate_vault(v, state, ptsource, summons, itemplace, affected, vault_packing, player_positions);
            }
        }

        vault_generation_cleanup(state, affected);

        ptsource.swap(grid::Map::genmaps_t(ptsource, state.grid));
    }
}


template <typename FUNC>
inline grid::Map::genmaps_t
generate_or_read_cached(const std::string& filename, GameState& state, const Levelskin& lev,
                        int worldx, int worldy, int worldz, unsigned int vaults_level,
                        FUNC progressbar,
                        std::vector<summons_t>& summons,
                        std::vector<itemplace_t>& itemplace,
                        std::vector<grid::pt>& player_positions,
                        std::vector<vault_packing_t>& vault_packing) {

    try {

        serialize::Source source(filename);
        serialize::read(source, state.grid);
        serialize::read(source, state.features);
        serialize::read(source, summons);
        serialize::read(source, itemplace);
        serialize::read(source, player_positions);
        serialize::read(source, vault_packing);

        return grid::Map::genmaps_t(state.grid);
        
    } catch (std::exception& e) {
        state.features.init();
        summons.clear();
        itemplace.clear();
        player_positions.clear();
        vault_packing.clear();
    }

    make_map(worldx, worldy, worldz, state, lev, progressbar);

    grid::Map::genmaps_t maps(state.grid);

    // Place some dungeon features on the same spots every time.
    
    {
        progressbar("Placing features...");

        counters::Counts terrain_counts = terrain().counts;

        unsigned int featscount = ::fabs(state.rng.gauss(lev.number_features.mean, lev.number_features.deviation));

        for (unsigned int i = 0; i < featscount; ++i) {

            std::map<tag_t, unsigned int> t = terrain_counts.take(state.rng, 0, 1);

            for (const auto& j : t) {
                state.features.generate(state.rng, state.grid, maps, j.first, j.second);
            }
        }
    }

    {
        progressbar("Placing vaults...");

        generate_vaults(state, maps, vaults_level, lev.number_fixed_vaults, Vault::type_t::FIXED,
                        summons, itemplace, player_positions, vault_packing);
    }

    {
        // Having two threads generate the same level at the same time is very rare,
        // but let's put a lock in place just in case anyways.
        static std::mutex m;
        std::unique_lock<std::mutex> l(m);

        serialize::Sink sink(filename);
        serialize::write(sink, state.grid);
        serialize::write(sink, state.features);
        serialize::write(sink, summons);
        serialize::write(sink, itemplace);
        serialize::write(sink, player_positions);
        serialize::write(sink, vault_packing);
    }
    
    return maps;
}
                                    
                                    
template <typename FUNC>
void Game::generate(GameState& state, FUNC progressbar) {

    // Read or generate cached map.

    const Levelskin& lev = levelskins().get(p.worldz);

    uint64_t fixedseed = make_fixedseed(p.worldx, p.worldy, p.worldz);

    std::string filename = make_mapname(p.worldx, p.worldy, p.worldz);

    progressbar("Generating dungeon...");

    unsigned int species_level = lev.get_species_level(p.worldz);
    unsigned int designs_level = lev.get_designs_level(p.worldz);
    unsigned int vaults_level  = lev.get_vaults_level(p.worldz);

    std::vector<summons_t> summons;
    std::vector<itemplace_t> itemplace;

    std::vector<grid::pt> player_positions;
    std::vector<vault_packing_t> vault_packing;

    // Level-specific random seed that's always the same.

    state.rng.init(fixedseed);

    grid::Map::genmaps_t maps = generate_or_read_cached(filename, state, lev,
                                                        p.worldx, p.worldy, p.worldz,
                                                        vaults_level, progressbar,
                                                        summons, itemplace, player_positions, vault_packing);

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
        if (state.grid.walkmap.count(xy) == 0)
            throw std::runtime_error("Sanity error 1.5");
    }

    // A known random seed for the randomized dungeon parts.
        
    size_t& num_visits = state.dungeon_visits_count[worldkey::key_t(p.worldx, p.worldy, p.worldz)];

    uint64_t semirandomseed = ((fixedseed + (int)state.moon.pi.phase) & 0xFFFFFFFF);
    uint64_t randomseed = ((game_seed + fixedseed + num_visits) & 0xFFFFFFFF);

    num_visits++;

    
    //

    // Place some vaults. Some are randomized, some are always on the same spots every time.

    {
        progressbar("Placing vaults...");

        state.rng.init(semirandomseed);

        generate_vaults(state, maps, vaults_level, lev.number_semirandom_vaults, Vault::type_t::SEMIRANDOM,
                        summons, itemplace, player_positions, vault_packing);

        // Initialize a known random sequence here!!

        state.rng.init(randomseed);

        generate_vaults(state, maps, vaults_level, lev.number_random_vaults, Vault::type_t::RANDOM,
                        summons, itemplace, player_positions, vault_packing);
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

            if (!state.grid.is_walk(xy.first, xy.second))
                continue;

            state.features.set(xy.first, xy.second, grave, state.render);
        }
    }

    // Place saved features.
    {
        auto feats = permafeats::features().get(p);

        for (const auto& i : feats) {
            unsigned int x = i.first.first;
            unsigned int y = i.first.second;

            features::Feature feat;
            if (state.features.get(x, y, feat)) {

                const Terrain& t = terrain().get(feat.tag);

                if (t.preserve)
                    continue;
            }

            const auto& spec = i.second;

            if (spec.walk.set() && spec.water.set()) {

                state.grid.set_walk_water(state.neigh, x, y, spec.walk.is(true), spec.water.is(true));
            }

            if (!state.grid.is_walk(x, y))
                continue;

            if (!spec.feat.null()) {
                state.features.set(x, y, spec.feat, state.render);
            }

            if (spec.label.set()) {
                state.features.label(x, y, spec.text);
            }
        }
    }

    maps.swap(grid::Map::genmaps_t(maps, state.grid));

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

            if (!state.grid.is_walk(i.xy.first, i.xy.second))
                continue;

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

    // Place non-random items.
    {
        for (const auto& s : itemplace) {
        
            tag_t item;

            switch (s.type) {

            case itemplace_t::type_t::SPECIFIC:
                item = s.tag;
                break;

            case itemplace_t::type_t::LEVEL:
            {
                auto is = state.designs_counts.take(state.rng, s.level);

                if (is.size() > 0) {
                    item = is.begin()->first;
                }
                break;
            }

            case itemplace_t::type_t::LEVEL_ANY:
                item = state.designs_counts.find(state.rng, s.level);
                break;
            }

            if (!item.null()) {
                state.items.place(s.x, s.y,
                                  state.items.make_item(item, items::pt(s.x, s.y), state.rng),
                                  state.render);
            }
        }
    }

    // Place some random monsters.
    {
        progressbar("Placing monsters...");

        for (const auto& s : summons) {

            switch (s.type) {
            case summons_t::type_t::SPECIFIC:
                state.monsters.summon(state.neigh, state.rng, state.grid, state.species_counts, state.render, 
                                      s.x, s.y, p.px, p.py, s.summontag, s.count, false, s.ally);
                break;

            case summons_t::type_t::LEVEL:
                state.monsters.summon_any(state.neigh, state.rng, state.grid, state.species_counts, state.render,
                                          s.x, s.y, p.px, p.py, s.level, s.count, s.ally);
                break;

            case summons_t::type_t::GENUS:
                state.monsters.summon_genus(state.neigh, state.rng, state.grid, state.species_counts, state.render,
                                            s.x, s.y, p.px, p.py, s.summontag, s.level, s.count, s.ally);
                break;
            }
        }

        unsigned int mongroups = ::fabs(state.rng.gauss(lev.number_monsters.mean, lev.number_monsters.deviation));

        for (unsigned int i = 0; i < mongroups; ++i) {

            state.monsters.generate(state.neigh, state.rng, state.grid, maps,
                                    state.species_counts, species_level, lev.exclusive_monsters);
        }
    }

    state.monsters.replace(state.neigh, state.grid, p.px, p.py, p.followers);

    p.followers.clear();

    for (const auto& mv : state.monsters.mgrid) {
        if (state.grid.walkmap.count(mv.first) == 0) {
            throw std::runtime_error("Sanity error 4");
        }
    }

    p.current_wx = p.worldx;
    p.current_wy = p.worldy;
    p.current_wz = p.worldz;

    progressbar("Done!");
}


#endif
