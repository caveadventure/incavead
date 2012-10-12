#ifndef __ITEMS_H
#define __ITEMS_H

#include <unordered_map>


namespace items {

typedef std::pair<unsigned int, unsigned int> pt;


struct Item {
    std::string tag;
    pt xy;

    Item() : xy(0, 0) {}

    Item(const std::string& _tag, const pt& _xy) : 
        tag(_tag), xy(_xy) 
        {}
};


}


namespace serialize {

template <>
struct reader<items::Item> {
    void read(Source& s, items::Item& m) {
        serialize::read(s, m.tag);
        serialize::read(s, m.xy);
    }
};

template <>
struct writer<items::Item> {
    void write(Sink& s, const items::Item& m) {
        serialize::write(s, m.tag);
        serialize::write(s, m.xy);
    }
};

}


namespace items {

struct Items {

    std::unordered_map< pt, std::vector<Item> > stuff;

    void init() {
        stuff.clear();
    }

    void clear() {
        init();
    }

    

        
    void generate(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, counters::Counts& counts, 
                  unsigned int level, unsigned int n) {

        std::cout << "!!! " << level << " " << n << std::endl;

        std::map<std::string, unsigned int> q = counts.take(rng, level, n);

        bm _z("monster placement");

        for (const auto& i : q) {

            Species::habitat_t h = species().get(i.first).habitat; 
    
            std::cout << "!-| " << i.first << " " << i.second << " " << (int)h << std::endl;


            switch (h) {

            case Species::habitat_t::walk:
                place_scatter(rng, grid, i.first, i.second, std::mem_fn(&grid::Map::one_of_walk));
                break;

            case Species::habitat_t::floor:
                place_scatter(rng, grid, i.first, i.second, std::mem_fn(&grid::Map::one_of_floor));
                break;

            case Species::habitat_t::water:
                place_scatter(rng, grid, i.first, i.second, std::mem_fn(&grid::Map::one_of_water));
                break;

            case Species::habitat_t::corner:
                place_scatter(rng, grid, i.first, i.second, std::mem_fn(&grid::Map::one_of_corner));
                break;

            case Species::habitat_t::shoreline:
                place_scatter(rng, grid, i.first, i.second, std::mem_fn(&grid::Map::one_of_shore));
                break;

            case Species::habitat_t::clumped_floor:
                place_clump(neigh, rng, grid, i.first, i.second, 
                            std::mem_fn(&grid::Map::one_of_floor), std::mem_fn(&grid::Map::is_floor));
                break;

            case Species::habitat_t::clumped_water:
                place_clump(neigh, rng, grid, i.first, i.second, 
                            std::mem_fn(&grid::Map::one_of_water), std::mem_fn(&grid::Map::is_water));
                break;

            }
        }
    }

    size_t stack_size(unsigned int x, unsigned int y) {
        auto i = stuff.find(pt(x, y));

        if (i == stuff.end()) {
            return false;
        }

        return i->second.size();
    }

    bool get(unsigned int x, unsigned int y, unsigned int z, Item& ret) {
        auto i = stuff.find(pt(x, y));

        if (i == stuff.end() || z >= i->second.size()) {
            return false;
        }

        ret = i->second[z];
        return true;
    }

    void dispose(counters::Counts& counts) {

        for (const auto& i : stuff) {
            const Specimen& s = specimens().get(i.second.tag);
            counts.replace(s.level, s.tag);
        }
    }

    inline void write(serialize::Sink& s) {
        serialize::write(s, stuff);
    }

    inline void read(serialize::Source& s) {
        serialize::read(s, stuff);
    }
};


}

#endif
