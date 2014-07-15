#ifndef __MONSTERS_H
#define __MONSTERS_H

#include <unordered_map>


namespace monsters {

typedef std::pair<unsigned int, unsigned int> pt;


struct Monster {
    tag_t tag;
    pt xy;

    double health;
    double magic;
    unsigned int sleep;
    unsigned int stun;
    unsigned int blind;
    unsigned int fear;
    pt target;

    Monster() : xy(0, 0), health(3.0), magic(3.0), sleep(0), stun(0), blind(0), fear(0) {}

    Monster(tag_t _tag, const pt& _xy) : 
        tag(_tag), xy(_xy), health(3.0), magic(3.0), sleep(0), stun(0), blind(0), fear(0)
        {}
};


}


namespace serialize {

template <>
struct reader<monsters::Monster> {
    void read(Source& s, monsters::Monster& m) {
        serialize::read(s, m.tag);
        serialize::read(s, m.xy);
        serialize::read(s, m.health);
        serialize::read(s, m.magic);
        serialize::read(s, m.sleep);
        serialize::read(s, m.stun);
        serialize::read(s, m.blind);
        serialize::read(s, m.fear);
        serialize::read(s, m.target);
    }
};

template <>
struct writer<monsters::Monster> {
    void write(Sink& s, const monsters::Monster& m) {
        serialize::write(s, m.tag);
        serialize::write(s, m.xy);
        serialize::write(s, m.health);
        serialize::write(s, m.magic);
        serialize::write(s, m.sleep);
        serialize::write(s, m.stun);
        serialize::write(s, m.blind);
        serialize::write(s, m.fear);
        serialize::write(s, m.target);
    }
};

}


namespace monsters {

struct Monsters {

    std::unordered_map<pt, Monster> mons;

    void init() {
        mons.clear();
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
                             FUNC f, FUNCP fp) {

        unsigned int ret = 0;

        for (unsigned int j = 0; j < n; ++j) {
                    
            if (clump.empty()) {

                pt tmp;
                if (!f(ptsource, rng, tmp)) 
                    break;

                clump.insert(tmp);
            }

            size_t clumpn = rng.n(clump.size());
            auto clumpi = clump.begin();

            while (clumpn > 0) {
                --clumpn;
                ++clumpi;
            }

            pt xy = *clumpi;
            clump.erase(clumpi);

            mons[xy] = Monster(tag, xy);
            placed.insert(xy);
            ++ret;

            for (const pt& v : neigh(xy)) {

                if (fp(grid, v.first, v.second) && 
                    !ptsource.is_nogen(v.first, v.second) &&
                    placed.count(v) == 0 &&
                    mons.count(v) == 0) {

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
                             std::unordered_set<pt>& placed) {


        const Species& s = species().get(tag);

        Species::habitat_t h = s.habitat; 

        switch (h) {

        case Species::habitat_t::walk:
            return place_clump(neigh, rng, grid, ptsource, tag, n, clump, placed,
                               std::mem_fn(&T::one_of_walk), std::mem_fn(&grid::Map::is_walk));

        case Species::habitat_t::floor:
            return place_clump(neigh, rng, grid, ptsource, tag, n, clump, placed,
                               std::mem_fn(&T::one_of_floor), std::mem_fn(&grid::Map::is_floor));

        case Species::habitat_t::water:
            return place_clump(neigh, rng, grid, ptsource, tag, n, clump, placed,
                               std::mem_fn(&T::one_of_lake), std::mem_fn(&grid::Map::is_lake));

        case Species::habitat_t::corner:
            return place_clump(neigh, rng, grid, ptsource, tag, n, clump, placed,
                               std::mem_fn(&T::one_of_corner), std::mem_fn(&grid::Map::is_corner));

        case Species::habitat_t::shoreline:
            return place_clump(neigh, rng, grid, ptsource, tag, n, clump, placed,
                               std::mem_fn(&T::one_of_shore), std::mem_fn(&grid::Map::is_shore));

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
                mons.count(v) == 0) {

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
                       unsigned int level, tag_t tag, unsigned int n) {

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

        unsigned int ret = place_clump(neigh, rng, grid, ptsource, tag, n, clump, placed);

        for (const auto& comp : s.companion) {

            double v = rng.gauss(0.0, 1.0);

            if (v <= comp.chance)
                continue;

            unsigned int n2 = counts.take(level, comp.tag, 1);

            if (n2 == 0) 
                continue;

            pt tmp;
            if (filter_habitat_find_one(grid, ptsource, clump, placed, tmp, species().get(comp.tag).habitat)) {

                place(neigh, rng, grid, ptsource, counts, &tmp, placed, level, comp.tag, n2);

            } else {

                place(neigh, rng, grid, ptsource, counts, nullptr, placed, level, comp.tag, n2);
            }
        }

        return ret;
    }


    unsigned int summon(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, 
                        counters::Counts& counts, grender::Grid& render, 
                        const std::unordered_set<pt>& places, const unsigned int* px, const unsigned int* py,
                        tag_t tag, unsigned int count, bool counts_taken) {

        std::unordered_set<pt> placed;

        if (px != nullptr && py != nullptr) {

            placed.insert(pt(*px, *py));
        }

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

            unsigned int ret = place(neigh, rng, grid, grid, counts, &start, placed, s.level, tag, count);

            for (const pt& xy : placed) {
                render.invalidate(xy.first, xy.second);
            }

            return ret;
        }

        return 0;
    }

    unsigned int summon(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, 
                        counters::Counts& counts, grender::Grid& render, 
                        unsigned int x, unsigned int y, const unsigned int* px, const unsigned int* py,
                        tag_t tag, unsigned int count, bool counts_taken) {


        std::unordered_set<pt> n;

        for (const pt& xy : neigh(pt(x, y))) {
            n.insert(xy);
        }

        n.insert(pt(x, y));

        return summon(neigh, rng, grid, counts, render, n, px, py, tag, count, counts_taken);
    }


    unsigned int summon_any(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, counters::Counts& counts, 
                            grender::Grid& render, 
                            unsigned int x, unsigned int y, const unsigned int* px, const unsigned int* py, 
                            unsigned int level, unsigned int count) {

        std::map<tag_t, unsigned int> q = counts.take(rng, level, count, true);

        unsigned int ret = 0;

        for (auto& i : q) {

            ret += summon(neigh, rng, grid, counts, render, x, y, px, py, i.first, i.second, true);
        }

        return ret;
    }

    unsigned int summon_genus(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, counters::Counts& counts, 
                              grender::Grid& render, 
                              unsigned int x, unsigned int y, const unsigned int* px, const unsigned int* py, 
                              tag_t genus, unsigned int level, unsigned int count) {

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

        return summon(neigh, rng, grid, counts, render, x, y, px, py, maxlev[rng.n(maxlev.size())], count, false);
    }


    template <typename T>
    void generate(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, T& ptsource,
                  counters::Counts& counts, unsigned int level, bool exclusive) {

        std::map<tag_t, unsigned int> q = counts.take(rng, level, 1, exclusive);
        std::unordered_set<pt> placed;

        for (auto& i : q) {

            place(neigh, rng, grid, ptsource, counts, nullptr, placed, level, i.first, i.second);

        }
    }

    bool get(unsigned int x, unsigned int y, Monster& ret) {
        auto i = mons.find(pt(x, y));

        if (i == mons.end()) {
            return false;
        }

        ret = i->second;
        return true;
    }

    template <typename FUNC>
    void change(const Monster& mon, FUNC f) {
        auto i = mons.find(mon.xy);

        if (i != mons.end()) {
            f(i->second);
        }
    }

    void dispose(counters::Counts& counts) {

        for (const auto& i : mons) {
            const Species& s = species().get(i.second.tag);
            counts.replace(s.level, s.tag);
        }
    }


    template <typename FUNC>
    void process(grender::Grid& grid, FUNC f) {

        size_t sbefore = mons.size();

        std::unordered_map<pt, Monster> neuw;
        std::unordered_set<pt> wipe;
        unsigned int deadcount = 0;

        for (const auto& i : mons) {
            const Species& s = species().get(i.second.tag);

            pt nxy;
            bool dead = false;

            if (f(i.second, s, nxy, dead)) {

                if (dead) {
                    deadcount++;
                    wipe.insert(i.first);

                } else if (neuw.count(nxy) == 0) {

                    neuw[nxy] = i.second;
                }
            }
        }

        for (auto& i : neuw) {
            if (mons.count(i.first) == 0 || wipe.count(i.first) != 0) {

                wipe.insert(i.second.xy);

                i.second.xy = i.first;
                mons[i.first] = i.second;

                wipe.erase(i.first);

                grid.invalidate(i.first.first, i.first.second);

            }
        }

        for (const pt& i : wipe) {
            mons.erase(i);

            grid.invalidate(i.first, i.second);
        }

        if (mons.size() != sbefore - deadcount) {

            for (const auto& i : mons) {
                std::cout << "   | " << i.first.first << "," << i.first.second << std::endl;
            }
            std::cout << mons.size() << " != " << sbefore << " - " << deadcount << std::endl;
            std::cout << "  " << neuw.size() << " " << wipe.size() << std::endl;
            
            throw std::runtime_error("Lost a monster in monster::process()!");
        }
    }

};

}

namespace serialize {

template <>
struct reader<monsters::Monsters> {
    void read(Source& s, monsters::Monsters& t) {
        serialize::read(s, t.mons);
    }
};

template <>
struct writer<monsters::Monsters> {
    void write(Sink& s, const monsters::Monsters& t) {
        serialize::write(s, t.mons);
    }
};

}


#endif
