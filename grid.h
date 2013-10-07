#ifndef __GRID_H
#define __GRID_H

#include <math.h>
#include <stdlib.h>

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

    std::vector<double> grid;

    std::vector<double> karma;
 
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

            std::set<pt> ng(neigh(xy));
            std::set<pt> proc;
        
            nogens.insert(xy);
            proc.insert(xy);

            for (unsigned int i = 1; i < depth; ++i) {
            
                std::set<pt> ngtmp;

                for (const pt& z : ng) {

                    if (proc.count(z) != 0)
                        continue;

                    proc.insert(z);
                    const auto& tmp = neigh(z);
                    ngtmp.insert(tmp.begin(), tmp.end());
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

    double& _get(unsigned int x, unsigned int y) {
        return grid[y*w+x];
    }

    double& _get(const pt& xy) {
        return grid[xy.second*w+xy.first];
    }

    double& get_karma(unsigned int x, unsigned int y) {
        return karma[y*w+x];
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

        for (double& i : grid) {
            i -= avg;
            if (i > max) max = i;
            else if (i < min) min = i;
        }

        double scale = (max - min) / 20.0;

        for (double& i : grid) {
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

        for (const auto& xy_ : neigh(xy)) {

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
                  std::unordered_map<pt, int>& watr,
                  double n, double q) {

        size_t index = ddist(rng.gen);
        
        unsigned int y = index / w;
        unsigned int x = index % w;

        std::unordered_set<pt> out;

        flow(neigh, rng, genparams, pt(x, y), out, n);

        for (const pt& xy : out) {

            watr[xy] += 1;

            double& i = _get(xy);

            i -= q;
            if (i < -10.0) i = -10.0;
        }

        gout.insert(out.begin(), out.end());
    }

    template <typename PARAMS>
    void makerivers(neighbors::Neighbors& neigh, rnd::Generator& rng, const PARAMS& genparams) {

        std::unordered_set<pt> gout;
        std::unordered_map<pt, int> watr;

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

        std::map< int, std::vector<pt> > walk_r;

        for (const pt& xy : gout) {

            double h = _get(xy);
            auto tmp = watr.find(xy);
            int w = (tmp == watr.end() ? 0 : tmp->second);

            if (h <= genparams.walk_threshold) {
                walkmap.insert(xy);

                walk_r[w].push_back(xy);

                if (h <= -10 && w >= genparams.lowlands_threshold) {
                    lowlands.insert(xy);
                }
            }
        }

        if (walk_r.empty() || lowlands.empty())
            throw std::runtime_error("Failed to generate map");

        ///
        
        std::vector< std::pair<int,pt> > watr_r;

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

    template <typename PARAMS>
    void flatten_pass(neighbors::Neighbors& neigh, const PARAMS& genparams) {

        std::unordered_map<pt, size_t> nwalk;
        std::unordered_map<pt, size_t> nwater;

        for (const auto& xy : walkmap) {

            bool iswater = watermap.count(xy);

            for (const auto& ij : neigh(xy)) {

                // For all solid squares neighboring a walkable square, count the number of neighbor walkable squares.
                if (walkmap.count(ij) == 0)
                    nwalk[ij]++;

                // For all dry squares neighboring a walkable water square, count the number of neighbor walkable water squares.
                if (iswater && watermap.count(ij) == 0)
                    nwater[ij]++;
            }
        }

        for (const auto& z : nwalk) {
            if (z.second >= genparams.flatten_walk_ng) {
                walkmap.insert(z.first);
            }
        }

        for (const auto& z : nwater) {
            if (z.second >= genparams.flatten_water_ng) {
                watermap.insert(z.first);
                walkmap.insert(z.first);
            }
        }

        /*
        std::unordered_set<pt> towalk;
        std::unordered_set<pt> towater;

        for (size_t x = 0; x < w; ++x) {
            for (size_t y = 0; y < h; ++y) {

                int nwall = 0;
                int nwater = 0;

                pt xy(x, y);

                for (const auto& xy_ : neigh(xy)) {

                    if (walkmap.count(xy_) == 0)
                        nwall++;

                    if (watermap.count(xy_) != 0)
                        nwater++;
                }

                if (walkmap.count(xy) == 0 && nwall < 3) {
                    towalk.insert(xy);
                }

                if (watermap.count(xy) == 0 && nwater > 2) {
                    towater.insert(xy);
                }
            }
        }

        walkmap.insert(towalk.begin(), towalk.end());
        walkmap.insert(towater.begin(), towater.end());
        watermap.insert(towater.begin(), towater.end());
        */
    }


    template <typename PARAMS>
    void unflow(neighbors::Neighbors& neigh, const PARAMS& genparams) {

        std::unordered_set<pt> unwater;

        for (const pt& xy : watermap) {
            unsigned int nwater = 0;

            for (const auto& xy_ : neigh(xy)) {

                if (watermap.count(xy_) != 0)
                    nwater++;
            }

            if (nwater < genparams.unflow_ng) {
                unwater.insert(xy);
            }
        }

        for (const pt& xy : unwater) {
            watermap.erase(xy);
        }
    }

    template <typename PARAMS, typename FUNC>
    void flatten(neighbors::Neighbors& neigh, const PARAMS& genparams, FUNC progressbar) {

        for (unsigned int i = 0; i < genparams.nflatten; ++i) {
            progressbar("Aging rock, " + std::to_string((int)((double)i/genparams.nflatten*100)) + "%...");
            flatten_pass(neigh, genparams);
        }

        for (unsigned int i = 0; i < genparams.nunflow; ++i) {
            progressbar("Flowing water, " + std::to_string((int)((double)i/genparams.nunflow*100)) + "%...");
            unflow(neigh, genparams);
        }
    }

    void _set_maps(neighbors::Neighbors& neigh) {

        for (const pt& xy : walkmap) {

            if (watermap.count(xy) == 0) {

                floormap.insert(xy);

                for (const auto& v : neigh(xy)) {
                    if (watermap.count(v) != 0) {
                        shoremap.insert(xy);
                        break;
                    }
                }
            }

            for (const auto& v : neigh(xy)) {
                if (walkmap.count(v) == 0) {
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

                double& k = get_karma(x, y);

                if (y > 0 && x > 0) {
                    k = ((get_karma(x-1, y) + get_karma(x, y-1) + get_karma(x-1, y-1)) / 3.0);
                }

                k += rng.gauss(genparams.karma_mean, genparams.karma_dev);

                k = std::min(std::max(k, -1.0), 1.0);
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
            progressbar("Placing shiprock...");
            makegrid(rng);
        }

        {
            progressbar("Placing water...");
            makerivers(neigh, rng, genparams);
        }        

        // nflatten, nunflow:
        // 5, 0; 
        // 1, 6;

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
            progressbar("Allotting karma...");
            make_karma(rng, genparams);
        }

        {
            progressbar("Combining...");
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

            floormap.insert(xy);
                
            if (watermap.count(xy) != 0) {
                lakemap.insert(xy);
            }

            for (const auto& v : neigh(xy)) {
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
            affected.insert(v);
        }

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
