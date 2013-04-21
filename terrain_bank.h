#ifndef __TERRAIN_BANK
#define __TERRAIN_BANK

#include <string>
#include <map>

struct TerrainBank {

    std::map<tag_t,Terrain> bank;
    counters::Counts counts;

    void copy(const Terrain& t) {

        if (bank.count(t.tag) != 0) {
            throw std::runtime_error("Duplicate terrain tag: " + t.name);
        }

        std::cout << "Terrain bank <- " << t.tag.v << " (" << t.name << ")" << std::endl;

        bank[t.tag] = t;
        counts.init(t.tag, 0, t.count);
    }

    const Terrain& get(tag_t tag) const {
        auto i = bank.find(tag);

        if (i == bank.end()) {
            throw std::runtime_error("Invalid terrain tag: " + std::to_string(tag.v));
        }

        return i->second;
    }
};

TerrainBank& __terrain__() {
    static TerrainBank ret;
    return ret;
}

const TerrainBank& terrain() {
    return __terrain__();
}

void init_terrain_copy(const Terrain& t) {
    __terrain__().copy(t);
}

#endif
