#ifndef __PLAYER_H
#define __PLAYER_H


struct stat_t {
    double val;
        
    stat_t() : val(3.0) {}

    void inc(double v) {
        val += v;
        if (val > 3) val = 3;
        else if (val < -3) val = -3;
    }

    void dec(double v) {
        val -= v;
        if (val < -3) val = -3;
        else if (val > 3) val = 3;
    }
};

struct shielded_a_stat_t : stat_t {

    double shield;

    shielded_a_stat_t() : stat_t(), shield(0) {}

    void dec(double v) {

        if (shield > 0 && v > 0) {
            double sm = std::min(shield, v);

            shield -= sm;
            v -= sm;
        }

        stat_t::dec(v);
    }
};

struct shielded_b_stat_t : stat_t {

    double shield;

    shielded_b_stat_t() : stat_t(), shield(0) {}

    double buff(double v) {

        double _v = ::fabs(v);

        if (_v < shield) {
            shield -= _v;
            return 0;

        } else {
            _v = _v - shield;
            shield = 0;

            if (v < 0)
                _v = -_v;

            return _v;
        }
    }

    void inc(double v) {

        v = buff(v);

        if (v != 0) {
            stat_t::inc(v);
        }
    }

    void dec(double v) {

        v = buff(v);

        if (v != 0) {
            stat_t::dec(v);
        }
    }
};


struct Player {

    unsigned int px;
    unsigned int py;

    int worldx;
    int worldy;
    int worldz;

    // Only needed in dispose(), so that we know the actual level, not the one being generated.
    int current_wx;
    int current_wy;
    int current_wz;

    unsigned int level;

    shielded_a_stat_t health;
    stat_t food;
    shielded_b_stat_t karma;
    stat_t luck;

    unsigned int sleep;
    unsigned int blind;
    unsigned int stun;
    unsigned int fear;

    struct dig_state_t {
        unsigned int x;
        unsigned int y;
        double h;

        dig_state_t() : x(0), y(0), h(0) {}
    };

    dig_state_t dig;
    bool digging;

    struct polymorph_t {
        tag_t species;
        unsigned int turns;

        polymorph_t() : turns(0) {}
    };

    polymorph_t polymorph;

    size_t polymorph_ability;

    struct fast_t {
        unsigned int slice;
        unsigned int turns;
        
        fast_t() : slice(1), turns(0) {}
    };

    fast_t fast;

    inventory_t inv;

    static const unsigned int MAIN           = 0x0;
    static const unsigned int LOOKING        = 0x1;
    static const unsigned int TARGET         = 0x2;
    static const unsigned int FIRED          = 0x8;
    static const unsigned int THROWING       = 0x10;
    static const unsigned int BLASTING       = 0x20;
    static const unsigned int DIGGING        = 0x40;
    static const unsigned int DEBUG          = 0x80;
    static const unsigned int INPUTTING      = 0x100;
    static const unsigned int WISHING        = 0x200;
    static const unsigned int SPECIAL_WISH   = 0x400;
    static const unsigned int QUITTING       = 0x800;
    static const unsigned int SELFNOTE       = 0x1000;
    static const unsigned int CLOUDING       = 0x2000;
    static const unsigned int P_CLOUDING     = 0x4000;
    static const unsigned int P_BLASTING     = 0x8000;

    unsigned int state;

    struct input_state_t {
        std::string s;
    };

    input_state_t input;

    struct overmap_state_t {
        size_t scale;

        overmap_state_t() : scale(0) {}
    };

    overmap_state_t overmap;

    struct look_state_t {
        unsigned int x;
        unsigned int y;
        int target;

        int rangemin;
        int rangemax;

        look_state_t(unsigned int _x = 0, unsigned int _y = 0) : 
            x(_x), y(_y), target(-1), rangemin(-1), rangemax(-1) {}
    };

    look_state_t look;

    struct banking_state_t {
        double assets;
        double sell_margin;
        double shield_bonus;
        double money_curse;
        tag_t item;
        unsigned int item_count;
        double item_price;
        double gives_change;

        banking_state_t() : assets(0), sell_margin(1.0), shield_bonus(0), money_curse(0), 
                            item_count(0), item_price(0), gives_change(0) {}
    };

    banking_state_t banking;

    std::vector<Terrain::spell_t> spells;

    std::string attacker;

    bool uniques_disabled;
    size_t dungeon_unique_series;

    double money_curse;

    std::map<tag_t, unsigned int> kills;

    std::set<tag_t> achievements;

    size_t num_replay_codes;

    std::map<unsigned int, tag_t> ailments;

    struct starsign_t {
        unsigned int day;
        unsigned int sign;

        starsign_t() : day(0), sign(0) {}

        void init(time_t now, time_t zero, unsigned int nday, unsigned int nsign) {

            long diff = (now - zero) / (3600 * 24);

            day = diff % nday;
            sign = diff % nsign;

            if (day < 0) {
                day = nday + day;
            }

            if (sign < 0) {
                sign = nsign + sign;
            }

            day = day + 1;
            sign = sign + 1;
            
        }
    };

    starsign_t starsign;


    Player() : px(0), py(0), worldx(0), worldy(0), worldz(-1), 
               current_wx(0), current_wy(0), current_wz(0), level(0),
               sleep(0), blind(0), stun(0), fear(0), digging(false), polymorph_ability(0), state(MAIN), 
               uniques_disabled(false), dungeon_unique_series(0), money_curse(0), num_replay_codes(0)
        {
            karma.val = 0;
            luck.val = 0;
        }

    void track_kill(tag_t genus, GameState& state) {

        const auto& _ach = constants().achievements;

        unsigned int& k = kills[genus];
        k++;

        for (const auto& i : _ach) {

            const auto& a = i.second;

            if (a.genus != genus || k < a.kills)
                continue;

            if (achievements.count(i.first) != 0)
                continue;

            achievements.insert(i.first);

            if (!i.second.summon.null()) {

                size_t time = state.ticks + state.rng.n(constants().achievement_trigger_rate);

                state.triggers[time].summon_out_of_view.monster = i.second.summon;
                state.triggers[time].summon_out_of_view.count = 0;
            }
        }
    }

    unsigned int get_level() const {

        if (!polymorph.species.null()) {

            return species().get(polymorph.species).get_computed_level();
        }

        return level;
    }

    unsigned int get_computed_level(rnd::Generator& rng) {

        if (!polymorph.species.null()) {

            return species().get(polymorph.species).get_computed_level();
        }

        unsigned int _lev = std::min(level, constants().player_level_cap);

        if (luck.val == 0)
            return _lev;

        bool neg = (luck.val < 0);
        double l = ::fabs(luck.val);

        // Warning, magic numbers.
        double p = (0.9 / l);

        if (p > 1.0)
            return _lev;

        int fudge = rng.geometric(p);

        if (neg) {

            fudge = -std::max(-fudge, (int)(-l - 3));

            luck.dec(fudge);

            if (fudge > (int)_lev)
                return 0;

            return _lev - fudge;

        } else {

            fudge = std::min(fudge, (int)(l + 3));

            luck.dec(fudge);

            return _lev + fudge;
        }
    }

    void get_attack(damage::attacks_t& out) const {

        if (!polymorph.species.null()) {
            
            out = species().get(polymorph.species).attacks;

        } else {

            inv.get_attack(out);
        }
    }

    void get_defense(damage::defenses_t& out) const {

        if (!polymorph.species.null()) {
            
            out = species().get(polymorph.species).defenses;

        } else {

            inv.get_defense(out);
        }
    }

    unsigned int get_lightradius() const {

        if (!polymorph.species.null()) {
            
            return species().get(polymorph.species).range;

        } else {

            return inv.get_lightradius();
        }
    }


    template <typename RNG>
    void add_ailment(RNG& rng, tag_t ailment, size_t triggers) {

        for (size_t z = 0; z < triggers; ++z) {
            for (size_t j = 0; j < 3; ++j) {
                unsigned int t = rng.range(0u, 99u);

                if (ailments.count(t) == 0) {
                    ailments[t] = ailment;
                    break;
                }
            }
        }
    }

};


namespace serialize {

template <>
struct reader<Terrain::spell_t> {
    void read(Source& s, Terrain::spell_t& sp) {
        serialize::read(s, sp.karma_bound);
        serialize::read(s, sp.ca_tag);
        serialize::read(s, sp.name);
        serialize::read(s, sp.timeout);
    }
};

template <>
struct writer<Terrain::spell_t> {
    void write(Sink& s, const Terrain::spell_t& sp) {
        serialize::write(s, sp.karma_bound);
        serialize::write(s, sp.ca_tag);
        serialize::write(s, sp.name);
        serialize::write(s, sp.timeout);
    }
};

template <>
struct reader<Player> {
    void read(Source& s, Player& p) {
        serialize::read(s, p.px);
        serialize::read(s, p.py);
        serialize::read(s, p.worldx);
        serialize::read(s, p.worldy);
        serialize::read(s, p.worldz);
        serialize::read(s, p.level);
        serialize::read(s, p.health.val);
        serialize::read(s, p.health.shield);
        serialize::read(s, p.food.val);
        serialize::read(s, p.karma.val);
        serialize::read(s, p.karma.shield);
        serialize::read(s, p.luck.val);
        serialize::read(s, p.sleep);
        serialize::read(s, p.blind);
        serialize::read(s, p.stun);
        serialize::read(s, p.fear);
        serialize::read(s, p.dig.x);
        serialize::read(s, p.dig.y);
        serialize::read(s, p.dig.h);
        serialize::read(s, p.digging);
        serialize::read(s, p.polymorph.species);
        serialize::read(s, p.polymorph.turns);
        serialize::read(s, p.polymorph_ability);
        serialize::read(s, p.fast.slice);
        serialize::read(s, p.fast.turns);
        serialize::read(s, p.inv);
        serialize::read(s, p.state);
        serialize::read(s, p.look.x);
        serialize::read(s, p.look.y);
        serialize::read(s, p.look.target);
        serialize::read(s, p.look.rangemin);
        serialize::read(s, p.look.rangemax);
        serialize::read(s, p.banking.assets);
        serialize::read(s, p.banking.sell_margin);
        serialize::read(s, p.banking.shield_bonus);
        serialize::read(s, p.banking.money_curse);
        serialize::read(s, p.banking.item);
        serialize::read(s, p.banking.item_count);
        serialize::read(s, p.banking.item_price);
        serialize::read(s, p.banking.gives_change);
        serialize::read(s, p.spells);
        serialize::read(s, p.uniques_disabled);
        serialize::read(s, p.dungeon_unique_series);
        serialize::read(s, p.money_curse);
        serialize::read(s, p.kills);
        serialize::read(s, p.achievements);
        serialize::read(s, p.input.s);
        serialize::read(s, p.overmap.scale);
        serialize::read(s, p.num_replay_codes);
        serialize::read(s, p.ailments);
        serialize::read(s, p.starsign.day);
        serialize::read(s, p.starsign.sign);
    }
};

template <>
struct writer<Player> {
    void write(Sink& s, const Player& p) {
        serialize::write(s, p.px);
        serialize::write(s, p.py);
        serialize::write(s, p.worldx);
        serialize::write(s, p.worldy);
        serialize::write(s, p.worldz);
        serialize::write(s, p.level);
        serialize::write(s, p.health.val);
        serialize::write(s, p.health.shield);
        serialize::write(s, p.food.val);
        serialize::write(s, p.karma.val);
        serialize::write(s, p.karma.shield);
        serialize::write(s, p.luck.val);
        serialize::write(s, p.sleep);
        serialize::write(s, p.blind);
        serialize::write(s, p.stun);
        serialize::write(s, p.fear);
        serialize::write(s, p.dig.x);
        serialize::write(s, p.dig.y);
        serialize::write(s, p.dig.h);
        serialize::write(s, p.digging);
        serialize::write(s, p.polymorph.species);
        serialize::write(s, p.polymorph.turns);
        serialize::write(s, p.polymorph_ability);
        serialize::write(s, p.fast.slice);
        serialize::write(s, p.fast.turns);
        serialize::write(s, p.inv);
        serialize::write(s, p.state);
        serialize::write(s, p.look.x);
        serialize::write(s, p.look.y);
        serialize::write(s, p.look.target);
        serialize::write(s, p.look.rangemin);
        serialize::write(s, p.look.rangemax);
        serialize::write(s, p.banking.assets);
        serialize::write(s, p.banking.sell_margin);
        serialize::write(s, p.banking.shield_bonus);
        serialize::write(s, p.banking.money_curse);
        serialize::write(s, p.banking.item);
        serialize::write(s, p.banking.item_count);
        serialize::write(s, p.banking.item_price);
        serialize::write(s, p.banking.gives_change);
        serialize::write(s, p.spells);
        serialize::write(s, p.uniques_disabled);
        serialize::write(s, p.dungeon_unique_series);
        serialize::write(s, p.money_curse);
        serialize::write(s, p.kills);
        serialize::write(s, p.achievements);
        serialize::write(s, p.input.s);
        serialize::write(s, p.overmap.scale);
        serialize::write(s, p.num_replay_codes);
        serialize::write(s, p.ailments);
        serialize::write(s, p.starsign.day);
        serialize::write(s, p.starsign.sign);
    }
};

}


#endif
