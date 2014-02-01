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
    psi,
    eat_brain,
    drain,
    make_meat,
    scare,
    vampiric,
    heavenly_fire,
    hellish_fire,
    electric,
    sonic,
    magic,
    hunger,
    unluck,
    blindness,
    voidness
};

inline std::string name(type_t d) {
    switch (d) {
    case type_t::physical:       return "physical";
    case type_t::sleep:          return "sleep";
    case type_t::poison:         return "poison";
    case type_t::turn_undead:    return "undead cancellation";
    case type_t::cancellation:   return "magic cancellation";
    case type_t::scare_animal:   return "scare animal";
    case type_t::psi:            return "psionic";
    case type_t::eat_brain:      return "brain eating";
    case type_t::drain:          return "lifeforce drain";
    case type_t::make_meat:      return "fog of man-to-meat";
    case type_t::scare:          return "fear";
    case type_t::vampiric:       return "vampiric";
    case type_t::heavenly_fire:  return "heavenly fire";
    case type_t::hellish_fire:   return "hellfire";
    case type_t::electric:       return "electric";
    case type_t::sonic:          return "sonic";
    case type_t::magic:          return "aetherial";
    case type_t::hunger:         return "hunger";
    case type_t::blindness:      return "blinding";
    case type_t::unluck:         return "unluck";
    default:                     return "oops";
    }
}        

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

