#ifndef __ATTACK_H
#define __ATTACK_H

namespace damage {

enum class type_t : unsigned int {
    physical,
    sleep,
    poison
};

struct val_t {

    double val;
    type_t type;

    val_t() : val(0), type(type_t::physical) {} 
};

struct attacks_t {
    std::vector<val_t> attacks;

    void add(const val_t& a) { 
        attack.push_back(a);
    }

    void add(const attacks_t& a) {
        attacks.insert(attacks.end(), a.begin(), a.end());
    }
};

struct defenses_t {
    std::map<type_t,val_t> defenses;

    void add(const val_t& d) {
        defenses[d.type].val += d.val;
    }

    void add(const defenses_t& d) {
        for (const val_t& v : d) {
            defenses[v.type].val += v.val;
        }
    }

    val_t get(const type_t& t) const {
        auto i = defenses.find(t);

        if (i == defenses.end()) {
            return val_t{0, t};
        }

        return i->second;
    }
};

}


#endif

