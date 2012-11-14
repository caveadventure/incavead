#ifndef __MONSTERS_H
#define __MONSTERS_H

#include <unordered_map>


namespace monsters {

typedef std::pair<unsigned int, unsigned int> pt;


struct Monster {
    std::string tag;
    pt xy;

    double health;
    double magic;
    unsigned int sleep;

    Monster() : xy(0, 0), health(3.0), magic(3.0), sleep(0) {}

    Monster(const std::string& _tag, const pt& _xy) : 
        tag(_tag), xy(_xy), health(3.0), magic(3.0), sleep(0)
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

    static bool is_walkable(const grid::Map& grid, const Species& s, const pt& xy) {

        switch (s.move) {
        case Species::move_t::floor: 
            if (!grid.is_floor(xy.first, xy.second)) return false;
            break;

        case Species::move_t::water: 
            if (!grid.is_lake(xy.first, xy.second)) return false;
            break;

        case Species::move_t::corner:
            if (!grid.is_corner(xy.first, xy.second)) return false;
            break;

        default:
            if (!grid.is_walk(xy.first, xy.second)) return false;
            break;
        }

        return true;
    }

    static std::vector<pt> get_walkables(const neighbors::Neighbors& neigh, const grid::Map& grid,
                                         const Species& s, const pt& xy) {

        std::vector<pt> ret;

        for (const pt& v : neigh(xy)) {
            if (is_walkable(grid, s, v)) {
                ret.push_back(v);
            }
        }

        return ret;
    }
    
    template <typename FUNC, typename FUNCP>
    unsigned int place_clump(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid,
                             const std::string& tag, unsigned int n,
                             std::unordered_set<pt>& clump, 
                             std::unordered_set<pt>& placed,
                             FUNC f, FUNCP fp) {

        unsigned int ret = 0;

        for (unsigned int j = 0; j < n; ++j) {
                    
            if (clump.empty()) {

                pt tmp;
                if (!f(grid, rng, tmp)) 
                    break;

                clump.insert(tmp);
            }

            pt xy = *(clump.begin());
            clump.erase(clump.begin());

            mons[xy] = Monster(tag, xy);
            grid.add_nogen(xy.first, xy.second);
            placed.insert(xy);
            ++ret;

            for (const pt& v : neigh(xy)) {

                if (fp(grid, v.first, v.second) && 
                    !grid.is_nogen(v.first, v.second) &&
                    mons.count(v) == 0) {

                    clump.insert(v);
                }
            }
        }

        return ret;
    }

    unsigned int place_clump(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid,
                             const std::string& tag, unsigned int n,
                             std::unordered_set<pt>& clump,
                             std::unordered_set<pt>& placed) {


        const Species& s = species().get(tag);

        Species::habitat_t h = s.habitat; 

        switch (h) {

        case Species::habitat_t::walk:
            return place_clump(neigh, rng, grid, tag, n, clump, placed,
                               std::mem_fn(&grid::Map::one_of_walk), std::mem_fn(&grid::Map::is_walk));

        case Species::habitat_t::floor:
            return place_clump(neigh, rng, grid, tag, n, clump, placed,
                               std::mem_fn(&grid::Map::one_of_floor), std::mem_fn(&grid::Map::is_floor));

        case Species::habitat_t::water:
            return place_clump(neigh, rng, grid, tag, n, clump, placed,
                               std::mem_fn(&grid::Map::one_of_lake), std::mem_fn(&grid::Map::is_lake));

        case Species::habitat_t::corner:
            return place_clump(neigh, rng, grid, tag, n, clump, placed,
                               std::mem_fn(&grid::Map::one_of_corner), std::mem_fn(&grid::Map::is_corner));

        case Species::habitat_t::shoreline:
            return place_clump(neigh, rng, grid, tag, n, clump, placed,
                               std::mem_fn(&grid::Map::one_of_shore), std::mem_fn(&grid::Map::is_shore));

        }

        return 0;
    }

    template <typename FUNC>
    bool filter_habitat_find_one(grid::Map& grid, const std::unordered_set<pt>& clump, pt& out, FUNC f) {

        for (const pt& v : clump) {

            if (f(grid, v.first, v.second) && 
                !grid.is_nogen(v.first, v.second) && 
                mons.count(v) == 0) {

                out = v;
                return true;
            }
        }

        return false;
    }

    bool filter_habitat_find_one(grid::Map& grid, const std::unordered_set<pt>& clump, pt& out, Species::habitat_t h) {

        switch (h) {
        case Species::habitat_t::walk: 
            return filter_habitat_find_one(grid, clump, out, std::mem_fn(&grid::Map::is_walk));

        case Species::habitat_t::floor:
            return filter_habitat_find_one(grid, clump, out, std::mem_fn(&grid::Map::is_floor));

        case Species::habitat_t::water:
            return filter_habitat_find_one(grid, clump, out, std::mem_fn(&grid::Map::is_lake));

        case Species::habitat_t::corner:
            return filter_habitat_find_one(grid, clump, out, std::mem_fn(&grid::Map::is_corner));

        case Species::habitat_t::shoreline:
            return filter_habitat_find_one(grid, clump, out, std::mem_fn(&grid::Map::is_shore));
        }

        return false;
    }


    unsigned int place(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, counters::Counts& counts, 
                       pt* start, std::unordered_set<pt>& placed,
                       unsigned int level, const std::string& tag, unsigned int n) {

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

            if (n_ <= 0)
                n_ = 0;

            n += counts.take(level, tag, n_);
        }

        std::unordered_set<pt> clump;

        if (start != nullptr) {
            clump.insert(*start);
        }

        unsigned int ret = place_clump(neigh, rng, grid, tag, n, clump, placed);

        for (const auto& comp : s.companion) {

            double v = rng.gauss(0.0, 1.0);

            if (v <= comp.chance)
                continue;

            unsigned int n2 = counts.take(level, comp.tag, 1);

            if (n2 == 0) 
                continue;

            pt tmp;
            if (filter_habitat_find_one(grid, clump, tmp, species().get(comp.tag).habitat)) {

                place(neigh, rng, grid, counts, &tmp, placed, level, comp.tag, n2);

            } else {

                place(neigh, rng, grid, counts, nullptr, placed, level, comp.tag, n2);
            }
        }

        std::cout << "[s] placed " << ret << std::endl;
        return ret;
    }

    unsigned int summon(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, counters::Counts& counts,
                        grender::Grid& render,
                        unsigned int x, unsigned int y, const std::string& tag) {


        std::unordered_set<pt> n;

        for (const pt& xy : neigh(pt(x, y))) {
            n.insert(xy);
        }

        const Species& s = species().get(tag);

        pt start;
        if (filter_habitat_find_one(grid, n, start, s.habitat)) {

            unsigned int n2 = counts.take(s.level, tag, 1);

            if (n2 == 0) {
                std::cout << "[s] no counts" << std::endl;
                return 0;
            }

            std::unordered_set<pt> placed;
            unsigned int ret = place(neigh, rng, grid, counts, &start, placed, s.level, tag, n2);

            for (const pt& xy : placed) {
                render.invalidate(xy.first, xy.second);
            }

            return ret;
        }

        std::cout << "[s] no habitat" << std::endl;

        return 0;
    }


    void generate(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, counters::Counts& counts, 
                  unsigned int level) {

        std::map<std::string, unsigned int> q = counts.take(rng, level, 1);
        std::unordered_set<pt> placed;

        for (auto& i : q) {
            
            place(neigh, rng, grid, counts, nullptr, placed, level, i.first, i.second);

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

    inline void write(serialize::Sink& s) {
        serialize::write(s, mons);
    }

    inline void read(serialize::Source& s) {
        serialize::read(s, mons);
    }
};


}

#endif
