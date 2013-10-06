#ifndef __SPECIES_BANK
#define __SPECIES_BANK

#include <string>
#include <unordered_map>

struct SpeciesBank {

    std::unordered_map<tag_t,Species> bank;
    counters::Counts counts;

    void copy(const Species& s) {

        std::cout << " " << s.name << " " << s.level << " " << s.count << std::endl;

        if (bank.count(s.tag) != 0) {
            std::cout << "OOPS!" << std::endl;
            throw std::runtime_error("Duplicate species tag: " + s.name);
        }

        std::cout << "  added to bank" << std::endl;
        bank[s.tag] = s;
        std::cout << "  initted counts" << std::endl;
        counts.init(s.tag, s.level, s.count);
        std::cout << "    -" << std::endl;
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
    std::cout << "Copied species." << std::endl;
}

#endif
