#ifndef __CELAUTO_BANK_H
#define __CELAUTO_BANK_H

#include <set>
#include <vector>
#include <unordered_map>

struct CelAuto {
    tag_t tag;

    std::set<unsigned int> survive;
    std::set<unsigned int> born;
    unsigned int age;

    tag_t terrain;

    bool is_walk;
    bool make_walk;
    double karma_scale;
    double karma_step;

    std::vector< std::pair<int,int> > seed;

    std::string debug_name;

    CelAuto() : age(0), is_walk(false), make_walk(false), karma_scale(1.0), karma_step(1.0) {}

};

struct CelAutoBank {

    std::unordered_map<tag_t,CelAuto> bank;

    void copy(const CelAuto& ca) {

        if (bank.count(ca.tag) != 0) {
            throw std::runtime_error("Duplicate celauto tag");
        }

        bank[ca.tag] = ca;
    }

    const CelAuto& get(tag_t tag) const {
        auto i = bank.find(tag);

        if (i == bank.end()) {
            throw std::runtime_error("Invalid celauto tag");
        }

        return i->second;
    }
};


inline CelAutoBank& __celautos__() {
    static CelAutoBank ret;
    return ret;
}

inline const CelAutoBank& celautos() {
    return __celautos__();
}

inline void init_celauto_copy(const CelAuto& ca) {
    __celautos__().copy(ca);
}


#endif

