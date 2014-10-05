#ifndef __MONSTERS_H
#define __MONSTERS_H

#include <unordered_map>

#include "delaunay.h"

namespace monsters {

typedef std::pair<unsigned int, unsigned int> pt;

struct Monster {
    size_t serial;
    tag_t tag;

    double health;
    double magic;
    unsigned int sleep;
    unsigned int stun;
    unsigned int blind;
    unsigned int fear;
    bool did_attack;
    tag_t ally;
    pt target;

    Monster() : serial(0), health(3.0), magic(3.0), sleep(0), stun(0), blind(0), fear(0), did_attack(false) {}

    Monster(tag_t _tag, size_t ser, tag_t a) : 
        serial(ser), tag(_tag), health(3.0), magic(3.0), sleep(0), stun(0), blind(0), fear(0), did_attack(false), ally(a)
        {}

    bool null() const {
        return tag.null();
    }
};


}


namespace serialize {

template <>
struct reader<monsters::Monster> {
    void read(Source& s, monsters::Monster& m) {
        serialize::read(s, m.serial);
        serialize::read(s, m.tag);
        serialize::read(s, m.health);
        serialize::read(s, m.magic);
        serialize::read(s, m.sleep);
        serialize::read(s, m.stun);
        serialize::read(s, m.blind);
        serialize::read(s, m.fear);
        serialize::read(s, m.did_attack);
        serialize::read(s, m.ally);
        serialize::read(s, m.target);
    }
};

template <>
struct writer<monsters::Monster> {
    void write(Sink& s, const monsters::Monster& m) {
        serialize::write(s, m.serial);
        serialize::write(s, m.tag);
        serialize::write(s, m.health);
        serialize::write(s, m.magic);
        serialize::write(s, m.sleep);
        serialize::write(s, m.stun);
        serialize::write(s, m.blind);
        serialize::write(s, m.fear);
        serialize::write(s, m.did_attack);
        serialize::write(s, m.ally);
        serialize::write(s, m.target);
    }
};

}


namespace monsters {

namespace {

inline unsigned int dist2(int x1, int x2, int y1, int y2) {
    int a = x1 - x2;
    int b = y1 - y2;
    return a*a + b*b;
}

}

struct Monsters {

    size_t serial;
    std::unordered_map<size_t, Monster> mons;
    std::unordered_map<pt, size_t> mgrid;

    delaunay::Triangulation nearest;

    Monsters() : serial(0) {}

    void init() {
        mons.clear();
        mgrid.clear();
        nearest.clear();
    }

    void clear() {
        init();
    }

    static bool is_walkable(const grid::Map& grid, const Species& s, unsigned int x, unsigned int y) {

        switch (s.move) {
        case Species::move_t::floor: 
            if (!grid.is_floor(x, y)) return false;
            break;

        case Species::move_t::water: 
            if (!grid.is_lake(x, y)) return false;
            break;

        case Species::move_t::corner:
            if (!grid.is_corner(x, y)) return false;
            break;

        case Species::move_t::shoreline:
            if (!grid.is_shore(x, y)) return false;
            break;

        default:
            if (!grid.is_walk(x, y)) return false;
            break;
        }

        return true;
    }
    
    template <typename T, typename FUNC, typename FUNCP>
    unsigned int place_clump(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, T& ptsource,
                             tag_t tag, unsigned int n,
                             std::unordered_set<pt>& clump, 
                             std::unordered_set<pt>& placed,
                             FUNC f, FUNCP fp, tag_t ally) {

        unsigned int ret = 0;

        for (unsigned int j = 0; j < n; ++j) {
                    
            if (clump.empty()) {

                pt tmp;
                if (!f(ptsource, rng, tmp)) 
                    break;

                clump.insert(tmp);
            }

            std::vector<pt> _clump;
            _clump.reserve(clump.size());

            for (auto i = clump.begin(); i != clump.end();) {

                if (mgrid.count(*i) == 0) {
                    _clump.push_back(*i);
                    ++i;
                } else {
                    i = clump.erase(i);
                }
            }

            if (_clump.empty()) {
                continue;
            }

            pt xy = _clump[rng.n(_clump.size())];

            if (mgrid.count(xy) != 0) {
                throw std::runtime_error("Sanity error: overwrote a monster while generating.");
            }

            serial++;
            mons[serial] = Monster(tag, serial, ally);
            mgrid[xy] = serial;
            placed.insert(xy);
            ++ret;

            for (const auto& v_ : neigh(xy)) {

                auto v = neigh.mk(v_, xy);

                if (fp(grid, v.first, v.second) && 
                    !ptsource.is_nogen(v.first, v.second) &&
                    placed.count(v) == 0 &&
                    mgrid.count(v) == 0) {

                    clump.insert(v);
                }
            }
        }

        return ret;
    }

    template <typename T>
    unsigned int place_clump(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, T& ptsource,
                             tag_t tag, unsigned int n,
                             std::unordered_set<pt>& clump,
                             std::unordered_set<pt>& placed, tag_t ally) {


        const Species& s = species().get(tag);

        Species::habitat_t h = s.habitat; 

        if (ally.null())
            ally = s.ally;

        switch (h) {

        case Species::habitat_t::walk:
            return place_clump(neigh, rng, grid, ptsource, tag, n, clump, placed,
                               std::mem_fn(&T::one_of_walk), std::mem_fn(&grid::Map::is_walk), ally);

        case Species::habitat_t::floor:
            return place_clump(neigh, rng, grid, ptsource, tag, n, clump, placed,
                               std::mem_fn(&T::one_of_floor), std::mem_fn(&grid::Map::is_floor), ally);

        case Species::habitat_t::water:
            return place_clump(neigh, rng, grid, ptsource, tag, n, clump, placed,
                               std::mem_fn(&T::one_of_lake), std::mem_fn(&grid::Map::is_lake), ally);

        case Species::habitat_t::corner:
            return place_clump(neigh, rng, grid, ptsource, tag, n, clump, placed,
                               std::mem_fn(&T::one_of_corner), std::mem_fn(&grid::Map::is_corner), ally);

        case Species::habitat_t::shoreline:
            return place_clump(neigh, rng, grid, ptsource, tag, n, clump, placed,
                               std::mem_fn(&T::one_of_shore), std::mem_fn(&grid::Map::is_shore), ally);

        }

        return 0;
    }

    template <typename T, typename FUNC>
    bool filter_habitat_find_one(grid::Map& grid, T& ptsource, const std::unordered_set<pt>& clump, 
                                 const std::unordered_set<pt>& placed, pt& out, FUNC f) {

        for (const pt& v : clump) {

            if (f(grid, v.first, v.second) && 
                !ptsource.is_nogen(v.first, v.second) && 
                placed.count(v) == 0 &&
                mgrid.count(v) == 0) {

                out = v;
                return true;
            }
        }

        return false;
    }

    template <typename T>
    bool filter_habitat_find_one(grid::Map& grid, T& ptsource, const std::unordered_set<pt>& clump, 
                                 const std::unordered_set<pt>& placed, pt& out, Species::habitat_t h) {

        switch (h) {
        case Species::habitat_t::walk: 
            return filter_habitat_find_one(grid, ptsource, clump, placed, out, std::mem_fn(&grid::Map::is_walk));

        case Species::habitat_t::floor:
            return filter_habitat_find_one(grid, ptsource, clump, placed, out, std::mem_fn(&grid::Map::is_floor));

        case Species::habitat_t::water:
            return filter_habitat_find_one(grid, ptsource, clump, placed, out, std::mem_fn(&grid::Map::is_lake));

        case Species::habitat_t::corner:
            return filter_habitat_find_one(grid, ptsource, clump, placed, out, std::mem_fn(&grid::Map::is_corner));

        case Species::habitat_t::shoreline:
            return filter_habitat_find_one(grid, ptsource, clump, placed, out, std::mem_fn(&grid::Map::is_shore));
        }

        return false;
    }


    template <typename T>
    unsigned int place(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, T& ptsource,
                       counters::Counts& counts, pt* start, std::unordered_set<pt>& placed,
                       unsigned int level, tag_t tag, unsigned int n, tag_t ally) {

        const Species& s = species().get(tag);


        {
            double m = s.clumpsize.mean;
            double d = s.clumpsize.deviation;

            int n_;

            if (d == 0) {
                n_ = m;

            } else {
                n_ = rng.gauss(m, d);
            }

            if (n_ > 0) {
                n += counts.take(level, tag, n_);
            }
        }

        std::unordered_set<pt> clump;

        if (start != nullptr) {
            clump.insert(*start);
        }

        unsigned int ret = place_clump(neigh, rng, grid, ptsource, tag, n, clump, placed, ally);

        for (const auto& comp : s.companion) {

            double v = rng.gauss(0.0, 1.0);

            if (v <= comp.chance)
                continue;

            unsigned int n2 = counts.take(level, comp.tag, 1);

            if (n2 == 0) 
                continue;

            pt tmp;
            if (filter_habitat_find_one(grid, ptsource, clump, placed, tmp, species().get(comp.tag).habitat)) {

                place(neigh, rng, grid, ptsource, counts, &tmp, placed, level, comp.tag, n2, ally);

            } else {

                place(neigh, rng, grid, ptsource, counts, nullptr, placed, level, comp.tag, n2, ally);
            }
        }

        return ret;
    }


    unsigned int summon(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, 
                        counters::Counts& counts, grender::Grid& render, 
                        const std::unordered_set<pt>& places, unsigned int px, unsigned int py,
                        tag_t tag, unsigned int count, bool counts_taken, tag_t ally = tag_t()) {

        std::unordered_set<pt> placed;
        placed.insert(pt(px, py));

        const Species& s = species().get(tag);

        pt start;
        if (filter_habitat_find_one(grid, grid, places, placed, start, s.habitat)) {

            if (count > 0) {

                if (!counts_taken) {
                    count = counts.take(s.level, tag, count);
                }

                if (count == 0) {
                    return 0;
                }

            } else {
                count = 1;
            }

            unsigned int ret = place(neigh, rng, grid, grid, counts, &start, placed, s.level, tag, count, ally);

            for (const pt& xy : placed) {
                render.invalidate(xy.first, xy.second);
            }

            return ret;
        }

        return 0;
    }

    unsigned int summon(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, 
                        counters::Counts& counts, grender::Grid& render, 
                        unsigned int x, unsigned int y, unsigned int px, unsigned int py,
                        tag_t tag, unsigned int count, bool counts_taken, tag_t ally = tag_t()) {


        std::unordered_set<pt> n;

        pt xy(x, y);

        for (const auto& xy_ : neigh(xy)) {
            n.insert(neigh.mk(xy_, xy));
        }

        n.insert(pt(x, y));

        return summon(neigh, rng, grid, counts, render, n, px, py, tag, count, counts_taken, ally);
    }


    unsigned int summon_any(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, counters::Counts& counts, 
                            grender::Grid& render, 
                            unsigned int x, unsigned int y, unsigned int px, unsigned int py, 
                            unsigned int level, unsigned int count, tag_t ally = tag_t()) {

        std::map<tag_t, unsigned int> q = counts.take(rng, level, count, true);

        unsigned int ret = 0;

        for (auto& i : q) {

            ret += summon(neigh, rng, grid, counts, render, x, y, px, py, i.first, i.second, true, ally);
        }

        return ret;
    }

    unsigned int summon_genus(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, counters::Counts& counts, 
                              grender::Grid& render, 
                              unsigned int x, unsigned int y, unsigned int px, unsigned int py, 
                              tag_t genus, unsigned int level, unsigned int count, tag_t ally = tag_t()) {

        std::map< unsigned int, std::vector<tag_t> > found;

        for (const auto& i : counts.data) {
            for (const auto& j : i.second) {

                const Species& s = species().get(j.first);

                if (s.get_computed_level() <= level && s.genus == genus) {
                    found[s.get_computed_level()].push_back(j.first);
                }
            }
        }

        if (found.empty())
            return 0;

        const std::vector<tag_t>& maxlev = found.rbegin()->second;

        if (maxlev.empty())
            return 0;

        return summon(neigh, rng, grid, counts, render, x, y, px, py, maxlev[rng.n(maxlev.size())], count, false, ally);
    }


    template <typename T>
    void generate(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, T& ptsource,
                  counters::Counts& counts, unsigned int level, bool exclusive) {

        std::map<tag_t, unsigned int> q = counts.take(rng, level, 1, exclusive);
        std::unordered_set<pt> placed;

        for (auto& i : q) {

            place(neigh, rng, grid, ptsource, counts, nullptr, placed, level, i.first, i.second, tag_t());

        }
    }

    Monster& get(size_t serial) {

        auto j = mons.find(serial);

        if (j == mons.end())
            throw std::runtime_error("Sanity error: monster lists unsynced.");

        return j->second;
    }

    Monster& get(unsigned int x, unsigned int y) {

        static Monster none;

        auto i = mgrid.find(pt(x, y));

        if (i == mgrid.end()) {
            return none;
        }

        return get(i->second);
    }

    template <typename FUNC>
    bool take(unsigned int x, unsigned int y, FUNC f, std::vector<Monster>& out) {

        auto i = mgrid.find(pt(x, y));

        if (i == mgrid.end())
            return false;

        auto j = mons.find(i->second);

        if (j == mons.end())
            throw std::runtime_error("Sanity error: monster lists unsynced.");

        if (!f(j->second))
            return false;

        out.push_back(j->second);

        mons.erase(j);
        mgrid.erase(i);

        return true;
    }

    void replace(neighbors::Neighbors& neigh, grid::Map& grid, 
                 unsigned int x, unsigned int y, const std::vector<Monster>& ms) {

        std::unordered_set<pt> places;
        pt xy(x, y);

        for (const auto& xy_ : neigh(xy)) {
            places.insert(neigh.mk(xy_, xy));
        }

        std::unordered_set<pt> placed;
        placed.insert(xy);

        for (const Monster& m : ms) {

            const Species& s = species().get(m.tag);

            pt place;
            if (!filter_habitat_find_one(grid, grid, places, placed, place, s.habitat))
                continue;

            placed.insert(place);

            serial++;
            mons[serial] = m;
            mgrid[place] = serial;
        }
    }

    void dispose(counters::Counts& counts) {

        for (const auto& i : mons) {
            const Species& s = species().get(i.second.tag);
            counts.replace(s.level, s.tag);
        }
    }


    template <typename FUNC1, typename FUNC2>
    void process(grender::Grid& render, FUNC1 fmove, FUNC2 fconf) {

        bm __("mprocess");

        size_t sbefore = mgrid.size();

        std::unordered_map< pt, std::vector< std::pair<pt,size_t> > > neuw;
        std::vector<size_t> trash;
        unsigned int deadcount = 0;

        for (const auto& i : mgrid) {

            const pt& xy = i.first;
            size_t m_num = i.second;

            Monster& m = get(m_num);

            m.did_attack = false;

            const Species& s = species().get(m.tag);

            pt nxy;
            bool dead = false;

            if (fmove(xy, m, s, nxy, dead)) {

                if (dead) {

                    deadcount++;
                    trash.push_back(m_num);
                    render.invalidate(xy.first, xy.second);

                } else {

                    neuw[nxy].push_back(std::make_pair(xy, m_num));
                }

            } else {

                neuw[xy].push_back(std::make_pair(xy, m_num));
            }
        }

        for (size_t m_num : trash) {
            mons.erase(m_num);
        }

        while (1) {

            decltype(neuw)::mapped_type failures;

            for (auto& i : neuw) {

                auto& v = i.second;

                while (v.size() > 1) {

                    auto mona = v.end();
                    mona--;
                    auto monb = mona;
                    monb--;

                    int result = fconf(mona->first, get(mona->second), monb->first, get(monb->second));

                    if ((result & 3) == 0) {

                        failures.push_back(*monb);
                        v.erase(monb);

                    } else {

                        if (result & 1) {

                            deadcount++;
                            mons.erase(monb->second);
                            render.invalidate(monb->first.first, monb->first.second);
                            v.erase(monb);
                        }

                        if (result & 2) {

                            deadcount++;
                            mons.erase(mona->second);
                            render.invalidate(mona->first.first, mona->first.second);
                            v.erase(mona);
                        }
                    }
                }
            }

            bool done = true;

            for (const auto& i : failures) {

                auto& tmp = neuw[i.first];
                tmp.push_back(i);

                if (tmp.size() > 1)
                    done = false;
            }

            if (done) break;
        }

        mgrid.clear();

        for (auto& i : neuw) {

            const pt& nxy = i.first;
            const auto& v = i.second;

            if (v.empty())
                continue;

            if (v.size() != 1)
                throw std::runtime_error("Sanity error: monster conflicts not resolved.");

            mgrid[nxy] = v[0].second;

            if (nxy != v[0].first) {

                render.invalidate(nxy.first, nxy.second);
                render.invalidate(v[0].first.first, v[0].first.second);
            }
        }

        if (mons.size() != mgrid.size()) {

            throw std::runtime_error("Monster structs unsynced");
        }

        if (mgrid.size() != sbefore - deadcount) {

            for (const auto& i : mgrid) {
                std::cout << "   | " << i.first.first << "," << i.first.second << std::endl;
            }
            std::cout << mgrid.size() << " != " << sbefore << " - " << deadcount << std::endl;
            std::cout << "  " << neuw.size() << std::endl;
            
            throw std::runtime_error("Lost a monster in monster::process()!");
        }
    }

    void find_nearest(unsigned int w, unsigned int h, unsigned int px, unsigned int py) {

        bm __("delaunay");

        unsigned int ai_radius = constants().ai_radius;

        ai_radius = ai_radius * ai_radius;

        std::vector<delaunay::pt> tmp;

        tmp.push_back(delaunay::pt(px, py));

        for (const auto& i : mgrid) {

            const pt& xy = i.first;

            if (dist2(xy.first, px, xy.second, py) > ai_radius)
                continue;

            tmp.push_back(xy);
        }

        nearest.init(w, h, tmp);
    }

};

}

namespace serialize {

template <>
struct reader<monsters::Monsters> {
    void read(Source& s, monsters::Monsters& t) {
        serialize::read(s, t.serial);
        serialize::read(s, t.mons);
        serialize::read(s, t.mgrid);
    }
};

template <>
struct writer<monsters::Monsters> {
    void write(Sink& s, const monsters::Monsters& t) {
        serialize::write(s, t.serial);
        serialize::write(s, t.mons);
        serialize::write(s, t.mgrid);
    }
};

}


#endif
