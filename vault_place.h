#ifndef __VAULT_PLACE_H
#define __VAULT_PLACE_H

struct vault_packing_t {
    unsigned int x;
    unsigned int y;
    unsigned int w;
    unsigned int h;
};

/* (i is inner rectangle, o is outer rectangle)

 +-----------------------------------+
 |      |                            |
 |      |       1                    |
 |      |                            |
 |      +--------------------+-------|
 | 4    |....................|       |
 |      |....................|       |
 |      |....................|       |
 |      |....................|   2   |
 |------+--------------------+       |
 |                           |       |
 |             3             |       |
 +-----------------------------------+
 
  offx = i.x - o.x
  offy = i.y - o.y

 1: 
    i.x, o.y, o.w - offx, offy

 2:
    i.x + i.w, i.y, o.w - offx - i.w, o.h - offy

 3:
    o.x, i.y + i.h, offx + i.w, o.h - offy - i.h

 4:
    o.y, o.y, offx, offy + i.h

*/


inline bool packing_placement(GameState& state, unsigned int w, unsigned int h,
                              std::vector<vault_packing_t>& packed, grid::pt& out) {

    if (packed.empty()) {
        packed.push_back(vault_packing_t{0, 0, state.grid.w, state.grid.h});
    }

    auto i = packed.begin();
    while (i != packed.end()) {

        const auto& vp = *i;

        if (vp.w < w || vp.h < h) {
            ++i;
            continue;
        }


        unsigned int offx = state.rng.range(0u, vp.w - w);
        unsigned int offy = state.rng.range(0u, vp.h - h);

        out.first = vp.x + offx;
        out.second = vp.y + offy;

        vault_packing_t tmp = vp;

        packed.erase(i);

        vault_packing_t s1{out.first, tmp.y, tmp.w - offx, offy};
        if (s1.w > 0 && s1.h > 0) packed.push_back(s1);

        vault_packing_t s2{out.first + w, out.second, tmp.w - offx - w, tmp.h - offy};
        if (s2.w > 0 && s2.h > 0) packed.push_back(s2);

        vault_packing_t s3{tmp.x, out.second + h, offx + w, tmp.h - offy - h};
        if (s3.w > 0 && s3.h > 0) packed.push_back(s3);

        vault_packing_t s4{tmp.x, tmp.y, offx, offy + h};
        if (s4.w > 0 && s4.h > 0) packed.push_back(s4);

        std::sort(packed.begin(), packed.end(), 
                  [](const vault_packing_t& a, const vault_packing_t& b) { return (a.w*a.h) > (b.w*b.h); });

        return true;
    }

    return false;
}


inline void generate_vault(const Vault& vault, GameState& state,
                           std::vector<summons_t>& summons, std::set<grid::pt>& affected,
                           std::vector<vault_packing_t>& packed, std::vector<grid::pt>& player_positions) {

    grid::pt xy;

    unsigned int _w = (vault.inherit.null() ? vault.w : vaults().get(vault.inherit).w);
    unsigned int _h = (vault.inherit.null() ? vault.h : vaults().get(vault.inherit).h);

    unsigned int w = (vault.transpose ? _h : _w);
    unsigned int h = (vault.transpose ? _w : _h);

    unsigned int ax = (vault.transpose ? vault.ay : vault.ax);
    unsigned int ay = (vault.transpose ? vault.ax : vault.ay);

    int _px = (vault.transpose ? vault.py : vault.px);
    int _py = (vault.transpose ? vault.px : vault.py);

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


    if (vault.placement == Vault::placement_t::packing) {

        if (!packing_placement(state, w, h, packed, xy)) {
            return;
        }

    } else {

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
            case Vault::placement_t::lowlands:
                if (!state.grid.one_of_lowlands(state.rng, xy)) return;
                break;
            default:
                return;
            }

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
    }

    //

    if (_px >= 0 && _py >= 0) {
        player_positions.push_back(grid::pt(xy.first + _px, xy.second +_py));
    }

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


inline void vault_generation_cleanup(GameState& state, std::set<grid::pt>& affected) {

    state.grid._set_maps_of(state.neigh, affected);
    affected.clear();
}


#endif
