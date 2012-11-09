#ifndef __TERRAIN_BANK
#define __TERRAIN_BANK

#include <string>
#include <map>

struct TerrainBank {

    std::map<std::string,Terrain> bank;
    counters::Counts counts;

    template <typename... ARGS>
    void init(const std::string& tag, unsigned int count, ARGS... args) {

        if (bank.count(tag) != 0) {
            throw std::runtime_error("Duplicate terrain tag: " + tag);
        }

        bank[tag] = Terrain(tag, count, std::forward<ARGS>(args)...);
        counts.init(tag, 0, count);
    }

    void copy(const Terrain& t) {

        if (bank.count(t.tag) != 0) {
            throw std::runtime_error("Duplicate terrain tag: " + t.tag);
        }

        bank[t.tag] = t;
        counts.init(t.tag, 0, t.count);
    }

    const Terrain& get(const std::string& tag) const {
        auto i = bank.find(tag);

        if (i == bank.end()) {
            throw std::runtime_error("Invalid terrain tag: " + tag);
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

template <typename... ARGS>
void init_terrain(ARGS... args) {
    __terrain__().init(std::forward<ARGS>(args)...);
}

void init_terrain_copy(const Terrain& t) {
    __terrain__().copy(t);
}

#endif
