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

struct shielded_stat_t : stat_t {

    double shield;

    shielded_stat_t() : stat_t(), shield(0) {}

    void dec(double v) {

        if (shield > 0 && v > 0) {
            double sm = std::min(shield, v);

            shield -= sm;
            v -= sm;
        }

        stat_t::dec(v);
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

    shielded_stat_t health;
    stat_t food;
    stat_t karma;
    stat_t luck;

    unsigned int sleep;

    unsigned int dig_x;
    unsigned int dig_y;
    bool digging;

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

    unsigned int state;

    std::string input_string;
    size_t overmap_scale;


    struct look_t {
        unsigned int x;
        unsigned int y;
        int target;

        int rangemin;
        int rangemax;

        look_t(unsigned int _x = 0, unsigned int _y = 0) : 
            x(_x), y(_y), target(-1), rangemin(-1), rangemax(-1) {}
    };

    look_t look;

    std::vector<Terrain::spell_t> spells;

    std::string attacker;

    bool uniques_disabled;
    size_t dungeon_unique_series;

    double money_curse;

    std::map<tag_t, unsigned int> kills;

    struct achievement_t {
        bool triggered;

        achievement_t() : triggered(false) {}
    };

    std::map<tag_t, achievement_t> achievements;


    Player() : px(0), py(0), worldx(0), worldy(0), worldz(-1), 
               current_wx(0), current_wy(0), current_wz(0), level(0),
               sleep(0), dig_x(0), dig_y(0), digging(false), state(MAIN), overmap_scale(0),
               uniques_disabled(false), dungeon_unique_series(0), money_curse(0)
        {
            karma.val = 0;
            luck.val = 0;
        }

    void track_kill(tag_t genus) {

        const auto& _ach = constants().achievements;

        unsigned int& k = kills[genus];
        k++;

        for (const auto& i : _ach) {

            const auto& a = i.second;

            if (a.genus != genus || k < a.kills)
                continue;

            if (achievements.count(i.first) != 0)
                continue;

            achievements[i.first] = achievement_t();
        }
    }
    
    unsigned int get_computed_level(rnd::Generator& rng) {

        bool neg = (luck.val < 0);
        double l = ::fabs(luck.val);

        // Warning, magic numbers.
        double p = (0.9 / l);

        if (p > 1.0)
            return level;

        int fudge = rng.geometric(p);

        if (neg) {

            fudge = -std::max(-fudge, (int)(l - 3));

            luck.dec(fudge);

            return level - fudge;

        } else {

            fudge = std::min(fudge, (int)(l + 3));

            luck.dec(fudge);

            return level + fudge;
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
struct reader<Player::achievement_t> {
    void read(Source& s, Player::achievement_t& a) {
        serialize::read(s, a.triggered);
    }
};

template <>
struct writer<Player::achievement_t> {
    void write(Sink& s, const Player::achievement_t& a) {
        serialize::write(s, a.triggered);
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
        serialize::read(s, p.luck.val);
        serialize::read(s, p.sleep);
        serialize::read(s, p.dig_x);
        serialize::read(s, p.dig_y);
        serialize::read(s, p.inv);
        serialize::read(s, p.state);
        serialize::read(s, p.look.x);
        serialize::read(s, p.look.y);
        serialize::read(s, p.look.target);
        serialize::read(s, p.look.rangemin);
        serialize::read(s, p.look.rangemax);
        serialize::read(s, p.spells);
        serialize::read(s, p.uniques_disabled);
        serialize::read(s, p.dungeon_unique_series);
        serialize::read(s, p.money_curse);
        serialize::read(s, p.kills);
        serialize::read(s, p.achievements);
        serialize::read(s, p.input_string);
        serialize::read(s, p.overmap_scale);
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
        serialize::write(s, p.luck.val);
        serialize::write(s, p.sleep);
        serialize::write(s, p.dig_x);
        serialize::write(s, p.dig_y);
        serialize::write(s, p.inv);
        serialize::write(s, p.state);
        serialize::write(s, p.look.x);
        serialize::write(s, p.look.y);
        serialize::write(s, p.look.target);
        serialize::write(s, p.look.rangemin);
        serialize::write(s, p.look.rangemax);
        serialize::write(s, p.spells);
        serialize::write(s, p.uniques_disabled);
        serialize::write(s, p.dungeon_unique_series);
        serialize::write(s, p.money_curse);
        serialize::write(s, p.kills);
        serialize::write(s, p.achievements);
        serialize::write(s, p.input_string);
        serialize::write(s, p.overmap_scale);
    }
};

}


#endif
