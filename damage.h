#ifndef __DAMAGE_H
#define __DAMAGE_H

#include <vector>
#include <map>

namespace damage {

enum class type_t : unsigned int {
    physical,
    sleep,
    poison,
    turn_undead,
    cancellation,
    scare_animal,
    psi
};

struct val_t {

    double val;
    type_t type;

    val_t(double v = 0, type_t t = type_t::physical) : val(v), type(t) {} 
};

struct attacks_t {
    std::vector<val_t> attacks;

    void add(const val_t& a) { 
        attacks.push_back(a);
    }

    void add(const attacks_t& a) {
        attacks.insert(attacks.end(), a.begin(), a.end());
    }

    std::vector<val_t>::const_iterator begin() const {
        return attacks.begin();
    }

    std::vector<val_t>::const_iterator end() const {
        return attacks.end();
    }

    bool empty() const { return attacks.empty(); }
};

struct defenses_t {
    std::map<type_t,double> defenses;

    void add(const val_t& d) {
        defenses[d.type] += d.val;
    }

    void add(const defenses_t& d) {
        for (const auto& v : d) {
            defenses[v.first] += v.second;
        }
    }

    double get(const type_t& t) const {

        auto i = defenses.find(t);

        if (i == defenses.end()) {
            return 0;
        }

        return i->second;
    }

    std::map<type_t,double>::const_iterator begin() const {
        return defenses.begin();
    }

    std::map<type_t,double>::const_iterator end() const {
        return defenses.end();
    }
};

}


#endif

