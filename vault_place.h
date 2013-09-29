#ifndef __VAULT_PLACE_H
#define __VAULT_PLACE_H


inline void generate_vault(const Vault& vault, mainloop::GameState& state, 
                           std::vector<summons_t>& summons, std::set<grid::pt>& affected) {

    bm __x("generating vault");

    grid::pt xy;

    unsigned int _w = (vault.inherit.null() ? vault.w : vaults().get(vault.inherit).w);
    unsigned int _h = (vault.inherit.null() ? vault.h : vaults().get(vault.inherit).h);

    unsigned int w = (vault.transpose ? _h : _w);
    unsigned int h = (vault.transpose ? _w : _h);

    unsigned int ax = (vault.transpose ? vault.ay : vault.ax);
    unsigned int ay = (vault.transpose ? vault.ax : vault.ay);

    if (ax >= w || ay >= h) {
        std::cerr << "Sanity error in vault anchor! " << ax << "," << ay << " " 
                  << w << "," << h << std::endl;
        return;
    }

    const auto& brushes = (vault.inherit.null() ?
                           vault.brushes :
                           vaults().get(vault.inherit).brushes);

    const auto& pic = (vault.inherit.null() ? 
                       vault.pic :
                       vaults().get(vault.inherit).pic);

    {
    bm __x("finding vault place");


    for (unsigned int i = 0; i < 10; ++i) {

        switch (vault.placement) {
        case Vault::placement_t::floor:
            if (!state.grid.one_of_floor(state.rng, xy)) return;
            break;
        case Vault::placement_t::water:
            if (!state.grid.one_of_lake(state.rng, xy)) return;
            break;
        case Vault::placement_t::corner:
            if (!state.grid.one_of_corner(state.rng, xy)) return;
            break;
        case Vault::placement_t::shoreline:
            if (!state.grid.one_of_shore(state.rng, xy)) return;
            break;
        }

        std::cout << " " << i;

        if ((int)xy.first  - (int)ax < 0 ||
            (int)xy.second - (int)ay < 0) 
            continue;
            
        xy.first -= ax;
        xy.second -= ay;

        if (xy.first  >= state.grid.w - w ||
            xy.second >= state.grid.h - h)
            continue;

        if (i >= 9) {
            return;
        }

        break;
    }
    std::cout << std::endl;
    }

    //

    for (int i = -1; i <= (int)w; ++i) {
        affected.insert(grid::pt(xy.first + i, xy.second - 1));
        affected.insert(grid::pt(xy.first + i, xy.second + h));
    }

    for (int i = 0; i < (int)h; ++i) {
        affected.insert(grid::pt(xy.first - 1, xy.second + i));
        affected.insert(grid::pt(xy.first + w, xy.second + i));
    }

    for (unsigned int y = 0; y < _h; ++y) {
        for (unsigned int x = 0; x < _w; ++x) {

            const std::string& line = pic[y];
            if (x >= line.size()) 
                continue;

            unsigned int c = line[x];
            auto bi = brushes.find(c);

            if (bi == brushes.end()) {
                throw std::runtime_error("Invalid brush char: '" + 
                                         std::string(1, c) + "'");
            }

            const Vault::brush& b = bi->second;

            unsigned int xi = xy.first  + (vault.transpose ? y : x);
            unsigned int yi = xy.second + (vault.transpose ? x : y);

            affected.insert(grid::pt(xi, yi));

            if (!b.is_blank) {

                if (b.is_walk) {
                    state.grid.walkmap.insert(grid::pt(xi, yi));
                } else {
                    state.grid.walkmap.erase(grid::pt(xi, yi));
                }

                if (b.is_water) {
                    state.grid.watermap.insert(grid::pt(xi, yi));
                } else {
                    state.grid.watermap.erase(grid::pt(xi, yi));
                }
            }
            
            if (!b.terrain.null()) {
                state.features.set(xi, yi, b.terrain, state.render);

            } else {
                state.features.unset(xi, yi, state.render);
            }

            if (!b.design.null()) {
                state.items.place(xi, yi, 
                                  state.items.make_item(b.design, items::pt(xi, yi), state.rng), 
                                  state.render);
            }

            if (!b.species.null()) {
                if (!state.grid.is_walk(xi, yi))
                    throw std::runtime_error("Invalid vault monster placement");

                summons.push_back(summons_t{xi, yi, b.species, 0, tag_t()});
            }
        }
    }
}


inline void vault_generation_cleanup(mainloop::GameState& state, std::set<grid::pt>& affected) {

    bm __y("vault set_maps_of");
    
    state.grid._set_maps_of(state.neigh, affected);
    affected.clear();
}


#endif
