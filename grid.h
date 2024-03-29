#ifndef __GRID_H
#define __GRID_H

#include "neighbors.h"
#include "random.h"

#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <limits>

#include <iostream>


namespace grid {

typedef std::pair<unsigned int, unsigned int> pt;


struct Map {

    unsigned int w;
    unsigned int h;

    std::vector<float> grid;

    std::vector<float> karma;
 
    std::unordered_set<pt> walkmap;
    std::unordered_set<pt> watermap;

    std::unordered_set<pt> floormap;
    std::unordered_set<pt> cornermap;
    std::unordered_set<pt> shoremap;
    std::unordered_set<pt> lakemap;
    std::unordered_set<pt> lowlands;

    struct genmaps_t {
        
        std::vector<pt> walkmap;
        std::vector<pt> watermap;
        std::vector<pt> floormap;
        std::vector<pt> cornermap;
        std::vector<pt> shoremap;
        std::vector<pt> lakemap;
        std::vector<pt> lowlands;

        std::unordered_set<pt> nogens;

        bool is_nogen(unsigned int x, unsigned int y) {
            return nogens.count(pt(x, y));
        }

        void add_nogen(unsigned int x, unsigned int y) {
            nogens.insert(pt(x, y));
        }

        void add_nogen_expand(neighbors::Neighbors& neigh,
                              unsigned int x, unsigned int y, unsigned int depth) {

            pt xy(x, y);

            std::set<pt> ng;

            for (const auto& xy_ : neigh(xy)) {
                ng.insert(neigh.mk(xy_, xy));
            }

            std::set<pt> proc;
        
            nogens.insert(xy);
            proc.insert(xy);

            for (unsigned int i = 1; i < depth; ++i) {
            
                std::set<pt> ngtmp;

                for (const pt& z : ng) {

                    if (proc.count(z) != 0)
                        continue;

                    proc.insert(z);

                    for (const auto& xy_ : neigh(z)) {
                        ngtmp.insert(neigh.mk(xy_, z));
                    }
                }

                ng.insert(ngtmp.begin(), ngtmp.end());
            }

            nogens.insert(ng.begin(), ng.end());
        }

        bool _one_of(rnd::Generator& rng, const std::vector<pt>& map, pt& ret) const {

            if (map.empty())
                return false;

            for (unsigned int i = 0; i < 10; ++i) {

                ret = map[rng.n(map.size())];

                if (nogens.count(ret) != 0)
                    continue;

                return true;
            }

            return false;
        }

        bool one_of_walk(rnd::Generator& rng, pt& ret) const {
            return _one_of(rng, walkmap, ret);
        }

        bool one_of_floor(rnd::Generator& rng, pt& ret) const {
            return _one_of(rng, floormap, ret);
        }

        bool one_of_corner(rnd::Generator& rng, pt& ret) const {
            return _one_of(rng, cornermap, ret);
        }

        bool one_of_shore(rnd::Generator& rng, pt& ret) const {
            return _one_of(rng, shoremap, ret);
        }

        bool one_of_water(rnd::Generator& rng, pt& ret) const {
            return _one_of(rng, watermap, ret);
        }

        bool one_of_lake(rnd::Generator& rng, pt& ret) const {
            return _one_of(rng, lakemap, ret);
        }

        bool one_of_lowlands(rnd::Generator& rng, pt& ret) const {
            return _one_of(rng, lowlands, ret);
        }

        template <typename T>
        genmaps_t(const T& g) {
            walkmap.assign(g.walkmap.begin(), g.walkmap.end());
            floormap.assign(g.floormap.begin(), g.floormap.end());
            cornermap.assign(g.cornermap.begin(), g.cornermap.end());
            shoremap.assign(g.shoremap.begin(), g.shoremap.end());
            watermap.assign(g.watermap.begin(), g.watermap.end());
            lakemap.assign(g.lakemap.begin(), g.lakemap.end());
            lowlands.assign(g.lowlands.begin(), g.lowlands.end());
        }

        template <typename T>
        genmaps_t(const genmaps_t& maps, const T& g) : genmaps_t(g) {
            nogens = maps.nogens;
        }

        void swap(genmaps_t&& maps) {
            walkmap.swap(maps.walkmap);
            floormap.swap(maps.floormap);
            cornermap.swap(maps.cornermap);
            shoremap.swap(maps.shoremap);
            watermap.swap(maps.watermap);
            lakemap.swap(maps.lakemap);
            lowlands.swap(maps.lowlands);
            nogens.swap(maps.nogens);
        }
    };




    void init(unsigned int _w, unsigned int _h) {
        w = _w;
        h = _h;

        grid.resize(w*h);
        karma.resize(w*h);
        walkmap.clear();
        watermap.clear();
        floormap.clear();
        cornermap.clear();
        shoremap.clear();
        lakemap.clear();
        lowlands.clear();

        for (size_t i = 0; i < w*h; ++i) {
            grid[i] = 10.0;
            karma[i] = 0.0;
        }
    }

    void clear() {
        init(w, h);
    }

    float& _get(unsigned int x, unsigned int y) {
        return grid[y*w+x];
    }

    float& _get(const pt& xy) {
        return grid[xy.second*w+xy.first];
    }

    float& get_karma(unsigned int x, unsigned int y) {
        return karma[y*w+x];
    }

    float get(unsigned int x, unsigned int y) const {
        return grid[y*w+x];
    }


    /*** *** *** *** *** ***/


    void subdivide_mapgen(rnd::Generator& rng,
                          unsigned int a, unsigned int b, 
                          unsigned int c, unsigned int d, bool domid) {

        unsigned int x = ((c - a) / 2) + a;
        unsigned int y = ((d - b) / 2) + b;

        if ((a == x || c == x) &&
            (b == y || d == y))
            return;

        //int s = std::max(c-a, d-b);
        int step = 0;
        int s = 1;

        double mid;

        if (!domid) {
            mid = _get(x, y);

        } else {

            mid = _get(a, b) + _get(c, b) + _get(a, d) + _get(c, d);
            mid = (mid / 4.0) - step + rng.range(-s, s);

            _get(x, y) = mid;
        }

        double top = ((_get(a, b) + _get(c, b) + mid) / 3.0) - step + rng.range(-s, s);
        _get(x, b) = top;

        double bot = ((_get(a, d) + _get(c, d) + mid) / 3.0) - step + rng.range(-s, s);
        _get(x, d) = bot;

        double lef = ((_get(a, b) + _get(a, d) + mid) / 3.0) - step + rng.range(-s, s);
        _get(a, y) = lef;

        double rig = ((_get(c, b) + _get(c, d) + mid) / 3.0) - step + rng.range(-s, s);
        _get(c, y) = rig;

        subdivide_mapgen(rng, a, b, x, y, true);
        subdivide_mapgen(rng, x, b, c, y, true);
        subdivide_mapgen(rng, a, y, x, d, true);
        subdivide_mapgen(rng, x, y, c, d, true);
    }


    void normalize() {
        double avg = 0.0;
        double min = std::numeric_limits<double>::max();
        double max = std::numeric_limits<double>::min();

        for (double i : grid) {
            avg += i;
        }

        avg /= (w * h);

        for (float& i : grid) {
            i -= avg;
            if (i > max) max = i;
            else if (i < min) min = i;
        }

        double scale = (max - min) / 20.0;

        for (float& i : grid) {
            i = (i / scale);

            if (i > 10.0) i = 10.0;
            else if (i < -10.0) i = -10.0;
        }
    }

    void makegrid(rnd::Generator& rng) {

        _get((w-1)/2, (h-1)/2) = -10;

        subdivide_mapgen(rng, 0, 0, w - 1, h - 1, false);

        normalize();
    }


    template <typename PARAMS>
    void flow(neighbors::Neighbors& neigh, rnd::Generator& rng, const PARAMS& genparams,
              const pt& xy, std::unordered_set<pt>& out, double n) {

        if (n < genparams.flow_epsilon) {
            return;
        }

        if (out.count(xy) != 0)
            return;

        out.insert(xy);

        double v0 = _get(xy);

        std::vector< std::pair<double, pt> > l;
        double vtotal = 0.0;

        for (const auto& _xy_ : neigh(xy)) {

            auto xy_ = neigh.mk(_xy_, xy);

            double v = _get(xy_);

            if (out.count(xy_) == 0 && v <= v0) {

                l.push_back(std::make_pair(v, xy_));
                vtotal += v;
            }
        }

        if (l.size() == 0) {
            return;
        }

        for (auto& i : l) {
            flow(neigh, rng, genparams, i.second, out, n * (i.first / vtotal));
        }
    }

    template <typename PARAMS>
    void makeflow(neighbors::Neighbors& neigh,
                  rnd::Generator& rng,
                  const PARAMS& genparams,
                  std::discrete_distribution<size_t>& ddist,
                  std::unordered_set<pt>& gout, 
                  std::unordered_map<pt, unsigned int>& watr,
                  double n, double q) {

        size_t index = ddist(rng.gen);
        
        unsigned int y = index / w;
        unsigned int x = index % w;

        std::unordered_set<pt> out;

        flow(neigh, rng, genparams, pt(x, y), out, n);

        for (const pt& xy : out) {

            watr[xy] += 1;

            float& i = _get(xy);

            i -= q;
            if (i < -10.0) i = -10.0;
        }

        gout.insert(out.begin(), out.end());
    }

    template <typename PARAMS>
    void makerivers(neighbors::Neighbors& neigh, rnd::Generator& rng, const PARAMS& genparams) {

        std::unordered_set<pt> gout;
        std::unordered_map<pt, unsigned int> watr;

        unsigned int N1 = grid.size() / genparams.flow_n_freq; //100;
        double N2 = genparams.flow_volume;
        double N3 = genparams.flow_erosion;

        {
            std::discrete_distribution<size_t> ddist;

            for (unsigned int i = 0; i < N1; i++) {

                if (i % genparams.flow_renorm_freq == 0) {
                    std::vector<double> grid_norm;

                    for (double v : grid) {
                        grid_norm.push_back((v + 10.0) * genparams.flow_renorm_scale); //5);
                    }

                    ddist = std::discrete_distribution<size_t>(grid_norm.begin(), grid_norm.end());
                }

                makeflow(neigh, rng, genparams, ddist, gout, watr, N2, N3);
            }
        }


        double hmin = 10;
        unsigned int wmax = 0;

        for (const pt& xy : gout) {

            double h = _get(xy);
            auto tmp = watr.find(xy);
            unsigned int w = (tmp == watr.end() ? 0 : tmp->second);

            hmin = std::min(hmin, h);
            wmax = std::max(wmax, w);
        }

        double walk_threshold = std::max(genparams.walk_threshold, hmin);
        unsigned int lowlands_threshold = std::min(genparams.lowlands_threshold, wmax);

        for (const pt& xy : gout) {

            double h = _get(xy);
            auto tmp = watr.find(xy);
            unsigned int w = (tmp == watr.end() ? 0 : tmp->second);

            if (h <= walk_threshold) {
                walkmap.insert(xy);

                if (h <= hmin && w >= lowlands_threshold) {
                    lowlands.insert(xy);
                }
            }
        }

        if (walkmap.empty() || lowlands.empty())
            throw std::runtime_error("Failed to generate map");

        ///
        
        std::vector< std::pair<unsigned int,pt> > watr_r;

        for (const auto& v : watr) {
            watr_r.push_back(std::make_pair(v.second, v.first));
        }

        std::sort(watr_r.begin(), watr_r.end());
        std::reverse(watr_r.begin(), watr_r.end());

        unsigned int pctwater = rng.gauss(genparams.water_quantile_mean, genparams.water_quantile_dev);
        if (pctwater <= 1) pctwater = 1;

        pctwater = watr_r.size() / pctwater;

        if (watr_r.size() > pctwater) {
            watr_r.resize(pctwater);
        }

        for (const auto& v : watr_r) {
            watermap.insert(v.second);
        }

    }

    template <typename PARAMS, typename FUNC>
    void flatten_pass(neighbors::Neighbors& neigh, const PARAMS& genparams, FUNC progressbar,
                      size_t np_walk, size_t np_water) {

        std::unordered_set<pt> newwalkmap;

        auto* walkmap_p = &walkmap;

        size_t npass = std::max(np_walk, np_water);
        
        for (size_t np = 0; np < npass; ++np) {

            if (walkmap_p->size() > 2000)
                progressbar("  ..."_m);

            std::unordered_map<pt, size_t> nwalk;
            std::unordered_map<pt, size_t> nwater;

            for (const auto& xy : *walkmap_p) {

                bool iswater = watermap.count(xy);

                for (const auto& ij_ : neigh(xy)) {

                    auto ij = neigh.mk(ij_, xy);

                    // For all solid squares neighboring a walkable square,
                    // count the number of neighbor walkable squares.
                    if (np < np_walk && walkmap.count(ij) == 0)
                        nwalk[ij]++;

                    // For all dry squares neighboring a walkable water square,
                    // count the number of neighbor walkable water squares.
                    if (np < np_water && iswater && watermap.count(ij) == 0)
                        nwater[ij]++;
                }
            }

            newwalkmap.clear();

            auto add_newwalkmap = [&](const pt& xy) {

                newwalkmap.insert(xy);

                for (const auto& ij_ : neigh(xy)) {
                    auto ij = neigh.mk(ij_, xy);

                    if (walkmap.count(ij))
                        newwalkmap.insert(ij);
                }
            };
            
            for (const auto& z : nwalk) {
                if (genparams.flatten_walk_ng & (1 << z.second)) {
                    walkmap.insert(z.first);
                    add_newwalkmap(z.first);
                }
            }

            for (const auto& z : nwater) {
                if (genparams.flatten_water_ng & (1 << z.second)) {
                    watermap.insert(z.first);
                    walkmap.insert(z.first);
                    add_newwalkmap(z.first);
                }
            }

            walkmap_p = &newwalkmap;
        }
    }


    template <typename PARAMS, typename FUNC>
    void unflow(neighbors::Neighbors& neigh, const PARAMS& genparams, FUNC progressbar, size_t npass) {

        std::unordered_set<pt> unwater;

        auto* watermap_p = &watermap;

        for (size_t np = 0; np < npass; ++np) {

            if (watermap_p->size() > 2000)
                progressbar("  ..."_m);
            
            unwater.clear();

            for (const pt& xy : *watermap_p) {
                unsigned int nwater = 0;

                for (const auto& xy_ : neigh(xy)) {

                    if (watermap.count(neigh.mk(xy_, xy)) != 0)
                        nwater++;
                }

                if (genparams.unflow_ng & (1 << nwater)) {
                    unwater.insert(xy);
                }
            }

            for (const pt& xy : unwater) {
                watermap.erase(xy);
            }

            watermap_p = &unwater;
        }
    }

    template <typename PARAMS, typename FUNC>
    void flatten(neighbors::Neighbors& neigh, const PARAMS& genparams, FUNC progressbar) {

        {
            progressbar("Aging rock..."_m);
            flatten_pass(neigh, genparams, progressbar, genparams.nflatten_walk, genparams.nflatten_water);
        }

        {
            progressbar("Flowing water..."_m);
            unflow(neigh, genparams,  progressbar, genparams.nunflow);
        }
    }

    void _set_maps(neighbors::Neighbors& neigh) {

        for (const pt& xy : walkmap) {

            if (watermap.count(xy) == 0) {

                floormap.insert(xy);

                for (const auto& v : neigh(xy)) {
                    if (watermap.count(neigh.mk(v, xy)) != 0) {
                        shoremap.insert(xy);
                        break;
                    }
                }
            }

            for (const auto& v : neigh(xy)) {
                if (walkmap.count(neigh.mk(v, xy)) == 0) {
                    cornermap.insert(xy);
                    break;
                }
            }
        }

        for (const pt& xy : watermap) {

            if (walkmap.count(xy) != 0) {
                lakemap.insert(xy);
            }
        }
    }

    template <typename PARAMS>
    void make_karma(rnd::Generator& rng, const PARAMS& genparams) {

        for (unsigned int y = 0; y < h; ++y) {
            for (unsigned int x = 0; x < w; ++x) {

                float& k = get_karma(x, y);

                if (y > 0 && x > 0) {
                    k = ((get_karma(x-1, y) + get_karma(x, y-1) + get_karma(x-1, y-1)) / 3.0);
                }

                k += rng.gauss(genparams.karma_mean, genparams.karma_dev);

                k = std::min(std::max(k, -1.0f), 1.0f);
            }
        }
    }

    template <typename PARAMS, typename FUNC>
    void generate(neighbors::Neighbors& neigh,
                  rnd::Generator& rng,
                  const PARAMS& genparams,
                  FUNC progressbar) {

        clear();

        {
            progressbar("Placing shiprock..."_m);
            makegrid(rng);
        }

        {
            progressbar("Placing water..."_m);
            makerivers(neigh, rng, genparams);
        }        

        flatten(neigh, genparams, progressbar);

        for (const auto& xy : lakemap) {
            if (walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 0.1.1");

            if (watermap.count(xy) == 0)
                throw std::runtime_error("Sanity error 0.1.2");
        }

        for (const auto& xy : shoremap) {
            if (walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 0.1.3");
        }

        //
        {
            progressbar("Allotting karma..."_m);
            make_karma(rng, genparams);
        }

        {
            progressbar("Combining..."_m);
            set_maps(neigh);
        }
    }

    void set_maps(neighbors::Neighbors& neigh) {

        floormap.clear();
        shoremap.clear();
        cornermap.clear();
        lakemap.clear();

        _set_maps(neigh);

        for (const auto& xy : lakemap) {
            if (walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 0.2.1");

            if (watermap.count(xy) == 0)
                throw std::runtime_error("Sanity error 0.2.2");
        }

        for (const auto& xy : shoremap) {
            if (walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 0.2.3");
        }
    }


    /*** *** *** *** ***/

    void set_height(unsigned int x, unsigned int y, double h) {
        _get(x, y) = h;
    }

    double get_height(unsigned int x, unsigned int y) {
        return _get(x, y);
    }

    bool is_walk(unsigned int x, unsigned int y) const {
        return (walkmap.count(pt(x, y)) != 0);
    }

    bool is_water(unsigned int x, unsigned int y) const {
        return (watermap.count(pt(x, y)) != 0);
    }

    bool is_lake(unsigned int x, unsigned int y) const {
        return (lakemap.count(pt(x, y)) != 0);
    }

    bool is_floor(unsigned int x, unsigned int y) const {
        return (floormap.count(pt(x, y)) != 0);
    }

    bool is_corner(unsigned int x, unsigned int y) const {
        return (cornermap.count(pt(x, y)) != 0);
    }

    bool is_shore(unsigned int x, unsigned int y) const {
        return (shoremap.count(pt(x, y)) != 0);
    }

    bool is_lowlands(unsigned int x, unsigned int y) const {
        return (lowlands.count(pt(x, y)) != 0);
    }

    void _set_maps_of(neighbors::Neighbors& neigh, const std::set<pt>& affected) {

        for (const pt& xy : affected) {

            floormap.erase(xy);
            shoremap.erase(xy);
            cornermap.erase(xy);
            lakemap.erase(xy);

            if (walkmap.count(xy) == 0) {
                lowlands.erase(xy);
                continue;
            }
                
            if (watermap.count(xy) != 0) {
                lakemap.insert(xy);
            } else {
                floormap.insert(xy);
            }

            for (const auto& v_ : neigh(xy)) {

                auto v = neigh.mk(v_, xy);

                if (watermap.count(v) != 0 && walkmap.count(v) != 0) {
                    shoremap.insert(xy);
                }

                if (walkmap.count(v) == 0) {
                    cornermap.insert(xy);
                }
            }
        }
    }

    void set_walk_water(neighbors::Neighbors& neigh, unsigned int x, unsigned int y, bool walk, bool water) { 

        pt tmp(x, y);

        if (walk) {
            walkmap.insert(tmp);
        } else {
            walkmap.erase(tmp);
        }

        if (water) {
            watermap.insert(tmp);
        } else {
            watermap.erase(tmp);
        }

        std::set<pt> affected;

        for (const auto& v : neigh(tmp)) {
            affected.insert(neigh.mk(v, tmp));
        }

        affected.insert(tmp);

        _set_maps_of(neigh, affected);
    }

    bool _one_of(rnd::Generator& rng, const std::unordered_set<pt>& s, pt& ret) {

        if (s.size() == 0)
            return false;

        size_t n = rng.n(s.size());

        auto i = s.begin();

        while (n > 0) {
            ++i;
            --n;
        }

        ret = *i;
        return true;
    }

    bool one_of_walk(rnd::Generator& rng, pt& ret) {
        return _one_of(rng, walkmap, ret);
    }

    bool one_of_floor(rnd::Generator& rng, pt& ret) {
        return _one_of(rng, floormap, ret);
    }

    bool one_of_corner(rnd::Generator& rng, pt& ret) {
        return _one_of(rng, cornermap, ret);
    }

    bool one_of_shore(rnd::Generator& rng, pt& ret) {
        return _one_of(rng, shoremap, ret);
    }

    bool one_of_water(rnd::Generator& rng, pt& ret) {
        return _one_of(rng, watermap, ret);
    }

    bool one_of_lake(rnd::Generator& rng, pt& ret) {
        return _one_of(rng, lakemap, ret);
    }

    bool one_of_lowlands(rnd::Generator& rng, pt& ret) {
        return _one_of(rng, lowlands, ret);
    }

    // Fake functions to adhere to a template interface.

    bool is_nogen(unsigned int x, unsigned int y) { return false; }

    void add_nogen(unsigned int x, unsigned int y) { }

};


}


namespace serialize {

template <>
struct reader<grid::Map> {
    void read(Source& s, grid::Map& t) {
        serialize::read(s, t.w);
        serialize::read(s, t.h);
        serialize::read(s, t.grid);
        serialize::read(s, t.karma);
        serialize::read(s, t.walkmap);
        serialize::read(s, t.watermap);
        serialize::read(s, t.floormap);
        serialize::read(s, t.cornermap);
        serialize::read(s, t.shoremap);
        serialize::read(s, t.lakemap);
        serialize::read(s, t.lowlands);
    }
};

template <>
struct writer<grid::Map> {
    void write(Sink& s, const grid::Map& t) {
        serialize::write(s, t.w);
        serialize::write(s, t.h);
        serialize::write(s, t.grid);
        serialize::write(s, t.karma);
        serialize::write(s, t.walkmap);
        serialize::write(s, t.watermap);
        serialize::write(s, t.floormap);
        serialize::write(s, t.cornermap);
        serialize::write(s, t.shoremap);
        serialize::write(s, t.lakemap);
        serialize::write(s, t.lowlands);
    }
};

}

#endif
