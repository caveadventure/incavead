#ifndef __SPECIES_BANK
#define __SPECIES_BANK

#include <string>
#include <map>

struct SpeciesBank {

    std::map<std::string,Species> bank;
    counters::Counts counts;

    template <typename... ARGS>
    void init(const std::string& tag, unsigned int level, unsigned int count,
              ARGS... args) {

        if (bank.count(tag) != 0) {
            throw std::runtime_error("Duplicate species tag: " + tag);
        }

        bank[tag] = Species(tag, level, count, std::forward<ARGS>(args)...);
        counts.init(tag, level, count);
    }

    const Species& get(const std::string& tag) const {
        auto i = bank.find(tag);

        if (i == bank.end()) {
            throw std::runtime_error("Invalid species tag: " + tag);
        }

        return i->second;
    }
};

SpeciesBank& __species__() {
    static SpeciesBank ret;
    return ret;
}

const SpeciesBank& species() {
    return __species__();
}

template <typename... ARGS>
void init_species(ARGS... args) {
    __species__().init(std::forward<ARGS>(args)...);
}

#endif
