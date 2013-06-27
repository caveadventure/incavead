#ifndef __DESIGNS_BANK
#define __DESIGNS_BANK

#include <string>
#include <unordered_map>

struct DesignsBank {

    std::unordered_map<tag_t,Design> bank;
    counters::Counts counts;

    void copy(const Design& d) {

        if (bank.count(d.tag) != 0) {
            throw std::runtime_error("Duplicate design tag: " + d.name);
        }

        bank[d.tag] = d;
        counts.init(d.tag, d.level, d.count);
    }

    const Design& get(tag_t tag) const {
        auto i = bank.find(tag);

        if (i == bank.end()) {
            throw std::runtime_error("Invalid designs tag");
        }

        return i->second;
    }
};

DesignsBank& __designs__() {
    static DesignsBank ret;
    return ret;
}

const DesignsBank& designs() {
    return __designs__();
}

void init_design_copy(const Design& d) {
    __designs__().copy(d);
}

#endif
