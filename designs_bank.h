#ifndef __DESIGNS_BANK
#define __DESIGNS_BANK

#include <string>
#include <map>

struct DesignsBank {

    std::map<std::string,Design> bank;
    counters::Counts counts;

    template <typename... ARGS>
    void init(const std::string& tag, unsigned int level, unsigned int count,
              ARGS... args) {

        if (bank.count(tag) != 0) {
            throw std::runtime_error("Duplicate design tag: " + tag);
        }

        bank[tag] = Design(tag, level, count, std::forward<ARGS>(args)...);
        counts.init(tag, level, count);
    }

    void copy(const Design& d) {

        if (bank.count(d.tag) != 0) {
            throw std::runtime_error("Duplicate design tag: " + d.tag);
        }

        bank[d.tag] = d;
        counts.init(d.tag, d.level, d.count);
    }

    const Design& get(const std::string& tag) const {
        auto i = bank.find(tag);

        if (i == bank.end()) {
            throw std::runtime_error("Invalid designs tag: " + tag);
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

template <typename... ARGS>
void init_design(ARGS... args) {
    __designs__().init(std::forward<ARGS>(args)...);
}

void init_design_copy(const Design& d) {
    __designs__().copy(d);
}

#endif
