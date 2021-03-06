#ifndef __SPECIES_BANK
#define __SPECIES_BANK

#include <string>
#include <unordered_map>

struct SpeciesBank {

    std::unordered_map<tag_t,Species> bank;
    counters::Counts counts;

    void copy(const Species& s) {

        if (bank.count(s.tag) != 0) {
            throw std::runtime_error("Duplicate species tag: " + s.name);
        }

        bank[s.tag] = s;
        counts.init(s.tag, s.level, s.count);
    }

    const Species& get(tag_t tag) const {
        auto i = bank.find(tag);

        if (i == bank.end()) {
            throw std::runtime_error("Invalid species tag");
        }

        return i->second;
    }
};

inline SpeciesBank& __species__() {
    static SpeciesBank ret;
    return ret;
}

inline const SpeciesBank& species() {
    return __species__();
}

inline void init_species_copy(const Species& s) {
    __species__().copy(s);
}

#endif
