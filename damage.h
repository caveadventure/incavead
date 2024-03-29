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

        inline unsigned int get(double v) const {
            int n = (v * scale) - offset;
            return std::max(0, n);
        }
    };

    std::vector< std::pair<tag_t,damage_to_turns_t> > inc_counts;

    std::vector<tag_t> dec_stats;
    std::vector<tag_t> inc_stats;

    std::vector<tag_t> transfer_stats;

    double threshold;
    double levelup_threshold;

    bool visible_damage;

    std::vector< std::pair<tag_t,double> > karmic_scale;

    tag_t polymorph;

    damage_to_turns_t player_poly;

    struct flags_t {

        struct tristate_t {
            int v;

            tristate_t() : v(-1) {}

            bool operator()(bool f) const {

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
        tristate_t player;
        tristate_t cosmic;
    };

    flags_t flags;

    struct msg_t {
        std::string str;
        bool important;

        msg_t(const std::string& s = "", bool i = false) : str(s), important(i) {}
    };

    msg_t melee_msg;
    msg_t env_msg;

    std::pair<tag_t,tag_t> infect;

    tag_t ally;

    Damage() : threshold(0), levelup_threshold(0), visible_damage(false) {}
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

    size_t size() const { return attacks.size(); }
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

    double get(tag_t t) const {

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

