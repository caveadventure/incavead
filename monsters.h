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

    bool get_placement(rnd::Generator& rng, grid::Map& grid, 
                       Species::habitat_t h, pt& ret) {
        switch (h) {

        case Species::habitat_t::floor:
            if (!grid.one_of_floor(rng, ret)) return false;
            break;

        case Species::habitat_t::water:
            if (!grid.one_of_water(rng, ret)) return false;

        case Species::habitat_t::corner:
            if (!grid.one_of_corner(rng, ret)) return false;

        case Species::habitat_t::shoreline:
            if (!grid.one_of_shore(rng, ret)) return false;

        }

        grid.add_nogen(ret.first, ret.second);
        return true;
    }
        
    void generate(rnd::Generator& rng, grid::Map& grid, counters::Counts& counts, 
                  unsigned int level, unsigned int n) {

        std::cout << "!!! " << level << " " << n << std::endl;

        std::map<std::string, unsigned int> q = counts.take(rng, level, n);

        std::cout << "!!k " << q.size() << std::endl;

        bm _z("monster placement");

        for (const auto& i : q) {

            for (unsigned int j = 0; j < i.second; ++j) {

                pt xy;

                Species::habitat_t h = species().get(i.first).habitat; 
    
                if (!get_placement(rng, grid, h, xy))
                    break;

                mons[xy] = Monster(i.first, xy);
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

    inline void write(serialize::Sink& s) {
        serialize::write(s, mons);
    }

    inline void read(serialize::Source& s) {
        serialize::read(s, mons);
    }
};


}

#endif
