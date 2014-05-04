#ifndef __DAMAGE_H
#define __DAMAGE_H

#include <vector>
#include <unordered_map>
#include <map>

struct Damage {

    tag_t tag;
    std::string name;

    struct damage_to_turns_t {
        int scale;
        int offset;

        damage_to_turns_t(int s = 0, int o = 0) : scale(s), offset(o) {}

        template <typename PARAM>
        inline unsigned int operator()(double v) {
            int n = (v * scale) - offset;
            return std::max(0, n);
        }
    };

    damage_to_turns_t sleepturns;
    damage_to_turns_t scareturns;
    damage_to_turns_t blindturns;

    double threshold;

    bool heavenly;
    bool hellish;
    bool cancellation;
    bool vampiric;
    bool hunger;
    bool unluck;
    bool make_meat;
    bool health;

    struct flags_t {

        struct tristate_t {
            int v;

            tristate_t() : v(-1) {}

            bool operator()(bool f) {

                if (v < 0) return true;

                return ((bool)v == f);
            }
        };

        tristate_t eyeless;
        tristate_t undead;
        tristate_t animal;
        tristate_t plant;
        tristate_t robot;
        tristate_t magic;
    };

    flags_t flags;

    struct msg_t {
        std::string str;
        bool important;

        msg_t(const std::string& s = "", bool i = false) : str(s), important(i) {}
    };

    msg_t melee_msg;
    msg_t env_msg;

    Damage() : threshold(0), heavenly(false), hellish(false), cancellation(false), vampiric(false),
               hunger(false), unluck(false), make_meat(false), health(false) 
        {}
};

struct DamageBank {

    std::unordered_map<tag_t, Damage> bank;

    void copy(const Damage& t) {

        if (bank.count(t.tag) != 0) {
            throw std::runtime_error("Duplicate damage tag: " + t.name);
        }

        bank[t.tag] = t;
    }

    const Damage& get(tag_t tag) const {
        auto i = bank.find(tag);

        if (i == bank.end()) {
            throw std::runtime_error("Invalid damage tag: " + std::to_string(tag.v));
        }

        return i->second;
    }
};

inline DamageBank& __damages__() {
    static DamageBank ret;
    return ret;
}

inline const DamageBank& damages() {
    return __damages__();
}

inline void init_damage_copy(const Damage& t) {
    __damages__().copy(t);
}


namespace damage {

struct val_t {

    double val;
    tag_t type;

    val_t(double v = 0, tag_t t = tag_t()) : val(v), type(t) {} 
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
    std::map<tag_t,double> defenses;

    void add(const val_t& d) {
        defenses[d.type] += d.val;
    }

    void add(const defenses_t& d) {
        for (const auto& v : d) {
            defenses[v.first] += v.second;
        }
    }

    double get(const tag_t& t) const {

        auto i = defenses.find(t);

        if (i == defenses.end()) {
            return 0;
        }

        return i->second;
    }

    std::map<tag_t,double>::const_iterator begin() const {
        return defenses.begin();
    }

    std::map<tag_t,double>::const_iterator end() const {
        return defenses.end();
    }
};

}


#endif

