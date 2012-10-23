#ifndef __MONSTERS_H
#define __MONSTERS_H

#include <unordered_map>


namespace monsters {

typedef std::pair<unsigned int, unsigned int> pt;


struct Monster {
    std::string tag;
    pt xy;

    Monster() : xy(0, 0) {}

    Monster(const std::string& _tag, const pt& _xy) : 
        tag(_tag), xy(_xy) 
        {}
};


}


namespace serialize {

template <>
struct reader<monsters::Monster> {
    void read(Source& s, monsters::Monster& m) {
        serialize::read(s, m.tag);
        serialize::read(s, m.xy);
    }
};

template <>
struct writer<monsters::Monster> {
    void write(Sink& s, const monsters::Monster& m) {
        serialize::write(s, m.tag);
        serialize::write(s, m.xy);
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
    void place_clump(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid,
                     const std::string& tag, unsigned int n,
                     std::unordered_set<pt>& clump,
                     FUNC f, FUNCP fp) {

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

            for (const pt& v : neigh(xy)) {

                if (fp(grid, v.first, v.second) && !grid.is_nogen(v.first, v.second)) {
                    clump.insert(v);
                }
            }
        }
    }

    void generate(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, counters::Counts& counts, 
                  unsigned int level) {

        std::map<std::string, unsigned int> q = counts.take(rng, level, 1);

        for (auto& i : q) {
            
            const Species& s = species().get(i.first);

            double m = s.clumpsize.mean;
            double d = s.clumpsize.deviation;

            int n;

            if (d == 0) {
                n = m;

            } else {
                n = rng.gauss(m, d);
            }

            if (n <= 0)
                continue;

            i.second += counts.take(level, i.first, n);
        }

        for (const auto& i : q) {

            const Species& s = species().get(i.first);

            Species::habitat_t h = s.habitat; 

            std::cout << " - " << i.first << " " << i.second << std::endl;

            std::unordered_set<pt> clump;

            switch (h) {

            case Species::habitat_t::walk:
                place_clump(neigh, rng, grid, i.first, i.second, clump,
                            std::mem_fn(&grid::Map::one_of_walk), std::mem_fn(&grid::Map::is_walk));
                break;

            case Species::habitat_t::floor:
                place_clump(neigh, rng, grid, i.first, i.second, clump,
                            std::mem_fn(&grid::Map::one_of_floor), std::mem_fn(&grid::Map::is_floor));
                break;

            case Species::habitat_t::water:
                place_clump(neigh, rng, grid, i.first, i.second, clump,
                            std::mem_fn(&grid::Map::one_of_lake), std::mem_fn(&grid::Map::is_lake));
                break;

            case Species::habitat_t::corner:
                place_clump(neigh, rng, grid, i.first, i.second, clump,
                            std::mem_fn(&grid::Map::one_of_corner), std::mem_fn(&grid::Map::is_corner));
                break;

            case Species::habitat_t::shoreline:
                place_clump(neigh, rng, grid, i.first, i.second, clump,
                            std::mem_fn(&grid::Map::one_of_shore), std::mem_fn(&grid::Map::is_shore));
                break;
            }
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

        for (const auto& i : mons) {
            const Species& s = species().get(i.second.tag);

            pt nxy;

            if (f(i.second, s, nxy) && neuw.count(nxy) == 0) {

                neuw[nxy] = i.second;
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

        if (mons.size() != sbefore) {

            for (const auto& i : mons) {
                std::cout << "   | " << i.first.first << "," << i.first.second << std::endl;
            }
            std::cout << mons.size() << " " << sbefore << std::endl;

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
