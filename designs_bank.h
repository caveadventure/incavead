#ifndef __DESIGNS_BANK
#define __DESIGNS_BANK

#include <string>
#include <unordered_map>

struct DesignsBank {

    std::unordered_map<tag_t,Design> bank;
    counters::Counts counts;

    counters::Counts bonus_a_counts;
    counters::Counts bonus_b_counts;

    void copy(const Design& d) {

        if (bank.count(d.tag) != 0) {
            throw std::runtime_error("Duplicate design tag: " + d.name);
        }

        bank[d.tag] = d;
        counts.init(d.tag, d.level, d.count);

        if (d.bonus_a_count > 0) {
            bonus_a_counts.init(d.tag, d.level, d.bonus_a_count);
        }

        if (d.bonus_b_count > 0) {
            bonus_b_counts.init(d.tag, d.level, d.bonus_b_count);
        }
    }

    const Design& get(tag_t tag) const {
        auto i = bank.find(tag);

        if (i == bank.end()) {
            throw std::runtime_error("Invalid designs tag");
        }

        return i->second;
    }
};

inline DesignsBank& __designs__() {
    static DesignsBank ret;
    return ret;
}

inline const DesignsBank& designs() {
    return __designs__();
}

inline void init_design_copy(const Design& d) {
    __designs__().copy(d);
}

#endif
