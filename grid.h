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


namespace std {

template <typename A, typename B>
struct hash< pair<A,B> > {
    size_t operator()(const pair<A,B>& p) const {
        return hash<A>()(p.first) ^ hash<B>()(p.second);
    }
};

}



namespace grid {

typedef std::pair<unsigned int, unsigned int> pt;


struct Map {

    unsigned int w;
    unsigned int h;

    std::vector<double> grid;
 
    std::unordered_set<pt> walkmap;
    std::unordered_set<pt> watermap;

    std::unordered_set<pt> floormap;
    std::unordered_set<pt> cornermap;
    std::unordered_set<pt> shoremap;
    std::unordered_set<pt> lakemap;

    std::unordered_set<pt> nogens;

    void init(unsigned int _w, unsigned int _h) {
        w = _w;
        h = _h;

        grid.resize(w*h);
        walkmap.clear();
        watermap.clear();
        floormap.clear();
        cornermap.clear();
        shoremap.clear();
        nogens.clear();

        for (size_t i = 0; i < w*h; ++i) {
            grid[i] = 10.0;
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


    void flow(neighbors::Neighbors& neigh,
              const pt& xy,
              std::unordered_set<pt>& out, 
              double n) {

        if (n < 1e-5) {
            return;
        }

        if (out.count(xy) != 0)
            return;

        out.insert(xy);

        double v0 = _get(xy);
        std::vector< std::pair<double, pt> > l;

        for (const auto& xy_ : neigh(xy)) {

            double v = _get(xy_);

            double pressure = 0.0; //n / 10.0;

            if (out.count(xy_) == 0 && v + pressure <= v0) {
                //fabs(v - v0) <= pressure /*1.0*/) {
                l.push_back(std::make_pair(v, xy_));
            }
        }

        if (l.size() == 0) {
            return;
        }

        std::sort(l.begin(), l.end());
        std::reverse(l.begin(), l.end());

        unsigned int culln = 4;

        if (l.size() > culln) {
            l.resize(culln);
        }

        double vtotal = 0.0;
        for (auto& i : l) {
            vtotal += i.first;
        }

        for (auto& i : l) {
            flow(neigh, i.second, out, n * (i.first / vtotal));
        }
    }

    void makeflow(neighbors::Neighbors& neigh,
                  rnd::Generator& rng,
                  std::unordered_set<pt>& gout, 
                  std::unordered_map<pt, int>& watr,
                  double n, double q) {

        std::vector<double> grid_norm;

        for (double v : grid) {
            grid_norm.push_back((v + 10.0) * 5);
        }

        std::discrete_distribution<size_t> ddist(grid_norm.begin(), grid_norm.end());
        size_t index = ddist(rng.gen);
        
        unsigned int y = index / w;
        unsigned int x = index % w;

        std::unordered_set<pt> out;
        flow(neigh, pt(x, y), out, n);

        for (const pt& xy : out) {

            watr[xy] += 1;

            double& i = _get(xy);

            i -= q;
            if (i < -10.0) i = -10.0;
        }

        gout.insert(out.begin(), out.end());
    }

    void makerivers(neighbors::Neighbors& neigh,
                    rnd::Generator& rng) {

        std::unordered_set<pt> gout;
        std::unordered_map<pt, int> watr;

        unsigned int N1 = grid.size() / 20; //100;
        double N2 = 50.0;

        for (unsigned int i = 0; i < N1; i++) {
            makeflow(neigh, rng, gout, watr, N2, 1);
        }

        for (const pt& xy : gout) {

            if (_get(xy) <= 0) {
                walkmap.insert(xy);
            }
        }
        
        std::vector< std::pair<int,pt> > watr_r;

        for (const auto& v : watr) {
            watr_r.push_back(std::make_pair(v.second, v.first));
        }

        std::sort(watr_r.begin(), watr_r.end());
        std::reverse(watr_r.begin(), watr_r.end());

        unsigned int pctwater = rng.gauss(5.0, 1.0);
        if (pctwater <= 1) pctwater = 1;

        pctwater = watr_r.size() / pctwater;

        if (watr_r.size() > pctwater) {
            watr_r.resize(pctwater);
        }

        for (const auto& v : watr_r) {
            watermap.insert(v.second);
        }

    }

    void flatten_pass(neighbors::Neighbors& neigh) {

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

        std::cout << "+ flatten... " << towalk.size() << " " << towater.size() << std::endl;

        walkmap.insert(towalk.begin(), towalk.end());
        walkmap.insert(towater.begin(), towater.end());
        watermap.insert(towater.begin(), towater.end());
    }


    void unflow(neighbors::Neighbors& neigh) {

        std::unordered_set<pt> unwater;

        for (const pt& xy : watermap) {
            int nwater = 0;

            for (const auto& xy_ : neigh(xy)) {

                if (watermap.count(xy_) != 0)
                    nwater++;
            }

            if (nwater < 5) {
                unwater.insert(xy);
            }
        }

        for (const pt& xy : unwater) {
            watermap.erase(xy);
        }
    }

    void flatten(neighbors::Neighbors& neigh, unsigned int nflatten, unsigned int nunflow) {

        for (unsigned int i = 0; i < nflatten; ++i) {
            std::cout << "flatten..." << std::endl;
            flatten_pass(neigh);
        }

        for (unsigned int i = 0; i < nunflow; ++i) {
            unflow(neigh);
        }
    }

    void _set_maps1(neighbors::Neighbors& neigh, const pt& xy) {

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

    void _set_maps2(const pt& xy) {

        if (walkmap.count(xy) != 0) {
            lakemap.insert(xy);
        }
    }

    void set_maps(neighbors::Neighbors& neigh) {

        for (const pt& xy : walkmap) {
            _set_maps1(neigh, xy);
        }

        for (const pt& xy : watermap) {
            _set_maps2(xy);
        }
    }

    void generate(neighbors::Neighbors& neigh,
                  rnd::Generator& rng,
                  unsigned int nflatten = 0, unsigned int nunflow = 0) {

        makegrid(rng);
        makerivers(neigh, rng);
        
        // nflatten, nunflow:
        // 5, 0; 
        // 1, 6;

        std::cout << "+ nflatten: " << nflatten << std::endl;

        flatten(neigh, nflatten, nunflow);

        set_maps(neigh);
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

    bool is_nogen(unsigned int x, unsigned int y) const {
        return (nogens.count(pt(x, y)) != 0);
    }
    
    void set_walk(neighbors::Neighbors& neigh, unsigned int x, unsigned int y, bool v) {
        pt tmp(x, y);

        if (v) {
            walkmap.insert(tmp);
            _set_maps1(neigh, tmp);

        } else {
            walkmap.erase(tmp);
            floormap.erase(tmp);
            cornermap.erase(tmp);
            shoremap.erase(tmp);
        }
    }

    void set_water(unsigned int x, unsigned int y, bool v) {
        pt tmp(x, y);

        if (v) {
            watermap.insert(tmp);
            _set_maps2(tmp);

        } else {
            watermap.erase(tmp);
            lakemap.erase(tmp);
        }
    }

    void add_nogen(unsigned int x, unsigned int y) {
        nogens.insert(pt(x, y));
    }

    void add_nogen_expand(neighbors::Neighbors& neigh,
                          unsigned int x, unsigned int y, unsigned int depth) {

        std::set<pt> ng(neigh(pt(x, y)));
        std::set<pt> proc;
        
        proc.insert(pt(x, y));

        for (unsigned int i = 1; i < depth; ++i) {
            
            std::set<pt> ngtmp;

            for (const pt& z : ng) {
                if (proc.count(z) == 0) {
                    proc.insert(z);

                    const auto& tmp = neigh(z);
                    ngtmp.insert(tmp.begin(), tmp.end());
                }
            }

            ng.insert(ngtmp.begin(), ngtmp.end());
        }

        nogens.insert(ng.begin(), ng.end());
    }


    bool _one_of(rnd::Generator& rng, std::vector<pt>& tmp, pt& ret) {
        if (tmp.size() == 0) {
            return false;
        }

        std::sort(tmp.begin(), tmp.end());
        ret = tmp[rng.range(0, (int)tmp.size()-1)];
        return true;
    }

    bool _one_of(rnd::Generator& rng, const std::unordered_set<pt>& s, pt& ret) {
        std::vector<pt> tmp;

        for (const pt& v : s) {
            if (nogens.count(v) != 0)
                continue;

            tmp.push_back(v);
        }

        return _one_of(rng, tmp, ret);
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
        return _one_of(rng, lakemap, ret);
    }

    inline void write(serialize::Sink& s) {
        serialize::write(s, w);
        serialize::write(s, h);
        serialize::write(s, grid);
        serialize::write(s, walkmap);
        serialize::write(s, watermap);
        serialize::write(s, floormap);
        serialize::write(s, cornermap);
        serialize::write(s, shoremap);
        serialize::write(s, lakemap);
    }

    inline void read(serialize::Source& s) {
        serialize::read(s, w);
        serialize::read(s, h);
        serialize::read(s, grid);
        serialize::read(s, walkmap);
        serialize::read(s, watermap);
        serialize::read(s, floormap);
        serialize::read(s, cornermap);
        serialize::read(s, shoremap);
        serialize::read(s, lakemap);
    }
};


}

#endif
