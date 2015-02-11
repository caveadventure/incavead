#ifndef __VAULT_PLACE_H
#define __VAULT_PLACE_H

struct vault_packing_t {
    unsigned int x;
    unsigned int y;
    unsigned int w;
    unsigned int h;
};

namespace serialize {

template <>
struct reader<vault_packing_t> {
    void read(Source& s, vault_packing_t& t) {
        serialize::read(s, t.x);
        serialize::read(s, t.y);
        serialize::read(s, t.w);
        serialize::read(s, t.h);
    }
};

template <>
struct writer<vault_packing_t> {
    void write(Sink& s, const vault_packing_t& t) {
        serialize::write(s, t.x);
        serialize::write(s, t.y);
        serialize::write(s, t.w);
        serialize::write(s, t.h);
    }
};

}


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


struct vault_state_t {
    std::vector<summons_t> summons;
    std::vector<itemplace_t> itemplace;
    std::set<grid::pt> affected;
    std::vector<vault_packing_t> packed;
    std::vector<grid::pt> player_positions;

    void affect(GameState& state, const grid::pt& xy) {

        for (const auto& v : state.neigh(xy)) {
            affected.insert(state.neigh.mk(v, xy));
        }

        affected.insert(xy);
    }
};


const Vault::brush& vault_get_brush(const Vault::brushes_t& brushes, unsigned char c) {

    auto bi = brushes.find(c);

    if (bi == brushes.end()) {
        throw std::runtime_error("Invalid brush char: '" + std::string(1, c) + "'");
    }

    return bi->second;
}

inline void vault_draw_point(unsigned int xi, unsigned int yi, const Vault::brush& b,
                             GameState& state, vault_state_t& vaultstate, bool use_species_counts) {

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

    switch (b.design.type) {
    case Vault::brush::design_t::type_t::NONE:
        break;

    case Vault::brush::design_t::type_t::SPECIFIC:
        vaultstate.itemplace.emplace_back(xi, yi, itemplace_t::type_t::SPECIFIC, b.design.tag, 0);
        break;

    case Vault::brush::design_t::type_t::LEVEL:
        vaultstate.itemplace.emplace_back(xi, yi, itemplace_t::type_t::LEVEL, tag_t(), b.design.level);
        break;

    case Vault::brush::design_t::type_t::LEVEL_ANY:
        vaultstate.itemplace.emplace_back(xi, yi, itemplace_t::type_t::LEVEL_ANY, tag_t(), b.design.level);
        break;
    }
            
    if (b.species.type != Vault::brush::species_t::type_t::NONE && 
        !state.grid.is_walk(xi, yi)) {

        throw std::runtime_error("Invalid vault monster placement");
    }

    switch (b.species.type) {
    case Vault::brush::species_t::type_t::NONE:
        break;

    case Vault::brush::species_t::type_t::SPECIFIC:
        vaultstate.summons.emplace_back(xi, yi, summons_t::type_t::SPECIFIC, b.species.tag, 
                                        0, (use_species_counts ? 1u : 0u), tag_t(), tag_t(), "");
        break;

    case Vault::brush::species_t::type_t::LEVEL:
        vaultstate.summons.emplace_back(xi, yi, summons_t::type_t::LEVEL, b.species.tag, 
                                        b.species.level, (use_species_counts ? 1u : 0u), tag_t(), tag_t(), "");
        break;

    case Vault::brush::species_t::type_t::GENUS:
        vaultstate.summons.emplace_back(xi, yi, summons_t::type_t::GENUS, b.species.tag, 
                                        b.species.level, (use_species_counts ? 1u : 0u), tag_t(), tag_t(), "");
        break;
    }
}


inline void vault_draw_cloud(GameState& state, vault_state_t& vaultstate,
                             const grid::pt& xy, unsigned int ax, unsigned int ay,
                             const Vault::brushes_t& brushes, const Vault::cloud_t& cloud,
                             bool use_species_counts) {

    std::unordered_set<grid::pt> used;

    for (size_t i = 0; i < cloud.n; ++i) {

        grid::pt cxy;

        size_t j;
        for (j = 0; j < 10; ++j) {

            double xx = state.rng.gauss(cloud.distrib.mean, cloud.distrib.deviation);
            double yy = state.rng.gauss(cloud.distrib.mean, cloud.distrib.deviation);

            int xi = (int)(xy.first + ax) + xx;
            int yi = (int)(xy.second + ay) + yy;

            if (xi < 0 || yi < 0 || xi >= (int)state.grid.w || yi >= (int)state.grid.h)
                continue;

            cxy = grid::pt(xi, yi);

            if (used.count(cxy) != 0)
                continue;

            used.insert(cxy);
            break;
        }

        if (j >= 10)
            continue;

        std::discrete_distribution<size_t> d(cloud.chances.begin(), cloud.chances.end());
        unsigned char c = cloud.brushes[d(state.rng.gen)];

        const Vault::brush& b = vault_get_brush(brushes, c);

        vault_draw_point(cxy.first, cxy.second, b, state, vaultstate, use_species_counts);

        vaultstate.affect(state, cxy);
    }
}

inline void vault_draw_blob(GameState& state, vault_state_t& vaultstate, grid::pt xy,
                            const Vault::brushes_t& brushes, const Vault::blob_t& blob,
                            bool use_species_counts) {

    auto check_memfn = std::mem_fn(&grid::Map::is_floor);

    switch (blob.placement) {

    case Vault::placement_t::water:
        check_memfn = std::mem_fn(&grid::Map::is_lake);
        break;
        
    case Vault::placement_t::corner:
        check_memfn = std::mem_fn(&grid::Map::is_corner);
        break;

    case Vault::placement_t::shoreline:
        check_memfn = std::mem_fn(&grid::Map::is_shore);
        break;

    case Vault::placement_t::lowlands:
        check_memfn = std::mem_fn(&grid::Map::is_lowlands);
        break;
        
    default:
        break;
    }

    std::unordered_set<grid::pt> used;

    for (size_t i = 0; i < blob.n; ++i) {

        std::vector<grid::pt> possibles;

        for (const auto& v : state.neigh(xy)) {

            grid::pt nxy = state.neigh.mk(v, xy);

            if (check_memfn(state.grid, nxy.first, nxy.second) && used.count(nxy) == 0) {

                possibles.push_back(nxy);
            }
        }

        if (possibles.empty())
            break;

        xy = possibles[state.rng.n(possibles.size())];

        used.insert(xy);

        const Vault::brush& b = vault_get_brush(brushes, blob.brush);

        vault_draw_point(xy.first, xy.second, b, state, vaultstate, use_species_counts);

        vaultstate.affect(state, xy);
    }
}

inline void vault_draw_river(GameState& state, vault_state_t& vaultstate, double x, double y,
                             const Vault::brushes_t& brushes, const Vault::river_t& river,
                             double angle, double width, size_t length,
                             bool use_species_counts) {

    const Vault::brush& b = vault_get_brush(brushes, river.brush);

    std::unordered_set<grid::pt> drawn;

    auto do_draw = [&](int px, int py) {

        while (px < 0) px += state.grid.w;
        while (py < 0) py += state.grid.h;

        px = px % state.grid.w;
        py = py % state.grid.h;

        grid::pt pxy(px, py);
        
        if (drawn.count(pxy) == 0) {

            vault_draw_point(px, py, b, state, vaultstate, use_species_counts);
            drawn.insert(pxy);
        }
    };

    for (size_t i = 0; i < length; ++i) {

        double ax = ::cos(angle);
        double ay = ::sin(angle);

        double o1x = ay;
        double o1y = -ax;
        double o2x = -ay;
        double o2y = ax;

        int fromx = ::round(x + o1x * width);
        int fromy = ::round(y + o1y * width);
        int tox = ::round(x + o2x * width);
        int toy = ::round(y + o2y * width);

        bresenham::Line line(fromx, fromy, tox, toy);

        int px;
        int py;

        while (line.step(px, py)) {

            do_draw(px, py);
        }

        int tmpx = ::round(x);
        int tmpy = ::round(y);

        do_draw(tmpx, tmpy);

        x += ax * 0.5;
        y += ay * 0.5;

        angle += state.rng.gauss(river.angle.mean, river.angle.deviation);
        width += state.rng.gauss(river.width.mean, river.width.deviation);

        if (width < 1)
            width = 1;
        
        if (river.splitchance > 0 && state.rng.n(river.splitchance) == 0) {

            vault_draw_river(state, vaultstate, x, y, brushes, river, angle, width, length-i, use_species_counts);
        }
    }

    for (const grid::pt& xy : drawn) {
        vaultstate.affect(state, xy);
    }
}

inline void vault_draw_tunnel(GameState& state, vault_state_t& vaultstate, grid::pt xy, grid::pt xy2,
                              const Vault::brushes_t& brushes, const Vault::tunnel_t& tunnel,
                              bool transpose, bool use_species_counts) {


    unsigned int xo = std::min(xy.first, xy2.first);
    unsigned int xd = std::max(xy.first, xy2.first);
    unsigned int yo = std::min(xy.second, xy2.second);
    unsigned int yd = std::max(xy.second, xy2.second);

    auto draw_line = [&](bool orient, bool neg,
                         unsigned int _xo, unsigned int _xd, unsigned int _yv,
                         std::list<grid::pt>& prevpt, bool& ground, int& tstate) {

        const Vault::brush& brush_p = vault_get_brush(brushes, tunnel.plain_brush);
        const Vault::brush& brush_b = vault_get_brush(brushes, tunnel.b_brush);
        const Vault::brush& brush_a = vault_get_brush(brushes, tunnel.a_brush);

        for (unsigned int _xi = _xo; _xi <= _xd; ++_xi) {

            unsigned int xi = (neg ? _xo + _xd - _xi : _xi);

            bool next_ground = state.grid.is_walk(xi, yo);

            auto b = std::cref(brush_p);

            if (tstate == 1) {
                b = std::cref(brush_b);
                --tstate;

            } else if (ground != next_ground) {

                auto ptli = prevpt.rbegin();

                if (!ground) {

                    if (ptli != prevpt.rend()) {

                        vault_draw_point(ptli->first, ptli->second, brush_a, state, vaultstate, use_species_counts);
                        ++ptli;
                    }

                    if (ptli != prevpt.rend()) {

                        vault_draw_point(ptli->first, ptli->second, brush_b, state, vaultstate, use_species_counts);
                    }

                    b = std::cref(brush_b);

                } else {

                    if (ptli != prevpt.rend()) {

                        vault_draw_point(ptli->first, ptli->second, brush_b, state, vaultstate, use_species_counts);
                    }

                    b = std::cref(brush_a);
                    tstate = 1;
                }
            }

            ground = next_ground;

            grid::pt tmp(orient ? xi : _yv, orient ? _yv : xi);
            vault_draw_point(tmp.first, tmp.second, b, state, vaultstate, use_species_counts);
            vaultstate.affect(state, tmp);

            prevpt.push_back(tmp);

            if (prevpt.size() > 2)
                prevpt.pop_front();
        }

    };
    
    
    if (xy == grid::pt(xo, yo) || xy2 == grid::pt(xo, yo)) {

        std::list<grid::pt> tmp;
        bool ground = state.grid.is_walk(xo, yo);
        int tstate = 0;

        if (transpose) {
            draw_line(false, false, yo,   yd, xo, tmp, ground, tstate);
            draw_line(true,  false, xo+1, xd, yd, tmp, ground, tstate);

        } else {
            draw_line(true,  false, xo,   xd, yo, tmp, ground, tstate);
            draw_line(false, false, yo+1, yd, xd, tmp, ground, tstate);
        }

    } else {

        std::list<grid::pt> tmp;
        bool ground = state.grid.is_walk(xo, yd);
        int tstate = 0;

        if (transpose) {
            draw_line(false, true,  yo,   yd, xo, tmp, ground, tstate);
            draw_line(true,  false, xo+1, xd, yo, tmp, ground, tstate);
            
        } else {
            draw_line(true,  false, xo, xd,   yd, tmp, ground, tstate);
            draw_line(false, true,  yo, yd-1, xd, tmp, ground, tstate);
        }
    }
}

template <typename T>
inline bool get_vault_placement(GameState& state, T& ptsource, vault_state_t& vaultstate,
                                unsigned int w, unsigned int h, unsigned int ax, unsigned int ay,
                                Vault::placement_t placement, grid::pt& xy) {

    if (placement == Vault::placement_t::packing) {

        return packing_placement(state, w, h, vaultstate.packed, xy);

    } else {

        for (unsigned int i = 0; i < 10; ++i) {

            switch (placement) {
            case Vault::placement_t::floor:
                if (!ptsource.one_of_floor(state.rng, xy)) return false;
                break;
            case Vault::placement_t::water:
                if (!ptsource.one_of_lake(state.rng, xy)) return false;
                break;
            case Vault::placement_t::corner:
                if (!ptsource.one_of_corner(state.rng, xy)) return false;
                break;
            case Vault::placement_t::shoreline:
                if (!ptsource.one_of_shore(state.rng, xy)) return false;
                break;
            case Vault::placement_t::lowlands:
                if (!ptsource.one_of_lowlands(state.rng, xy)) return false;
                break;
            default:
                return false;
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
                return false;
            }

            break;
        }
    }

    return true;
}

template <typename T>
inline void generate_vault(const Vault& vault, GameState& state, T& ptsource, vault_state_t& vaultstate) {

    grid::pt xy;

    unsigned int _w = (vault.inherit.null() ? vault.w : vaults().get(vault.inherit).w);
    unsigned int _h = (vault.inherit.null() ? vault.h : vaults().get(vault.inherit).h);

    unsigned int w = (vault.transpose ? _h : _w);
    unsigned int h = (vault.transpose ? _w : _h);

    unsigned int ax = (vault.transpose ? vault.ay : vault.ax);
    unsigned int ay = (vault.transpose ? vault.ax : vault.ay);

    int _px = (vault.transpose ? vault.py : vault.px);
    int _py = (vault.transpose ? vault.px : vault.py);

    const auto& brushes = (vault.inherit.null() ?
                           vault.brushes :
                           vaults().get(vault.inherit).brushes);

    const auto& pic = (vault.inherit.null() ?
                       vault.pic :
                       vaults().get(vault.inherit).pic);

    const auto& cloud = (vault.inherit.null() ?
                         vault.cloud :
                         vaults().get(vault.inherit).cloud);

    const auto& blob = (vault.inherit.null() ?
                        vault.blob :
                        vaults().get(vault.inherit).blob);

    const auto& river = (vault.inherit.null() ?
                         vault.river :
                         vaults().get(vault.inherit).river);

    const auto& room = (vault.inherit.null() ?
                        vault.room :
                        vaults().get(vault.inherit).room);

    const auto& tunnel = (vault.inherit.null() ?
                          vault.tunnel :
                          vaults().get(vault.inherit).tunnel);

    unsigned int roomw = state.rng.range(room.w1, room.w2);
    unsigned int roomh = state.rng.range(room.h1, room.h2);

    unsigned int picw = w;
    unsigned int pich = h;
    
    w = std::max(picw, vault.transpose ? roomh : roomw);
    h = std::max(pich, vault.transpose ? roomw : roomh);

    if (w > picw)
        ax += (w - picw) / 2;

    if (h > pich)
        ay += (h - pich) / 2;
    
    if (w > 0 && h > 0 && (ax >= w || ay >= h)) {
        std::cerr << "Sanity error in vault anchor! " << ax << "," << ay << " "
                  << w << "," << h << " : " << vault.tag.v << " " << vault.inherit.v << std::endl;
        return;
    }

    if (!get_vault_placement(state, ptsource, vaultstate, w, h, ax, ay, vault.placement, xy))
        return;

    //

    if (_px >= 0 && _py >= 0) {
        vaultstate.player_positions.push_back(grid::pt(xy.first + _px, xy.second +_py));
    }

    for (int i = -1; i <= (int)w; ++i) {
        vaultstate.affected.insert(grid::pt(xy.first + i, xy.second - 1));
        vaultstate.affected.insert(grid::pt(xy.first + i, xy.second + h));
    }

    for (int i = 0; i < (int)h; ++i) {
        vaultstate.affected.insert(grid::pt(xy.first - 1, xy.second + i));
        vaultstate.affected.insert(grid::pt(xy.first + w, xy.second + i));
    }


    /*** Pre-drawn vault (possibly in a room) ***/

    if (w > picw || h > pich) {

        for (unsigned int y = 0; y < h; ++y) {
            for (unsigned int x = 0; x < w; ++x) {

                const Vault::brush& b = vault_get_brush(brushes, room.brush);

                unsigned int xi = xy.first  + x;
                unsigned int yi = xy.second + y;

                vaultstate.affected.insert(grid::pt(xi, yi));

                vault_draw_point(xi, yi, b, state, vaultstate, vault.use_species_counts);
            }
        }
    }
        
    if (pic.size() > 0) {

        unsigned int offx = (w - picw) / 2;
        unsigned int offy = (h - pich) / 2;
        
        for (unsigned int y = 0; y < _h; ++y) {
            for (unsigned int x = 0; x < _w; ++x) {

                const std::string& line = pic[y];
                if (x >= line.size())
                    continue;

                unsigned int c = line[x];
                const Vault::brush& b = vault_get_brush(brushes, c);

                unsigned int xi = xy.first  + offx + (vault.transpose ? y : x);
                unsigned int yi = xy.second + offy + (vault.transpose ? x : y);

                vaultstate.affected.insert(grid::pt(xi, yi));

                vault_draw_point(xi, yi, b, state, vaultstate, vault.use_species_counts);
            }
        }
    }

    /*** Cloud ***/
    
    if (cloud.n > 0) {

        vault_draw_cloud(state, vaultstate, xy, ax, ay, brushes, cloud, vault.use_species_counts);
    }

    /*** Blobs ***/
    
    if (blob.n > 0) {

        vault_draw_blob(state, vaultstate, xy, brushes, blob, vault.use_species_counts);
    }

    /*** Rivers ***/

    if (river.n > 0) {

        vault_draw_river(state, vaultstate, xy.first, xy.second, brushes, river,
                         state.rng.uniform(0.0, 2*M_PI), 1.0, river.n, vault.use_species_counts);
    }        

    if (tunnel.enabled) {

        grid::pt xy2;

        if (!get_vault_placement(state, ptsource, vaultstate, w, h, ax, ay, vault.placement, xy2))
            return;

        vault_draw_tunnel(state, vaultstate, xy, xy2, brushes, tunnel, vault.transpose, vault.use_species_counts);
    }
    
}


inline void vault_generation_cleanup(GameState& state, std::set<grid::pt>& affected) {

    state.grid._set_maps_of(state.neigh, affected);
    affected.clear();
}


#endif
