#ifndef __PLAYER_H
#define __PLAYER_H


struct Player {

    const Species& species;

    unsigned int px;
    unsigned int py;

    int worldx;
    int worldy;
    int worldz;

    // Only needed in dispose(), so that we know the actual level, not the one being generated.
    int current_wx;
    int current_wy;
    int current_wz;

    std::vector<monsters::Monster> followers;

    unsigned int level;
    bool dead;

    pstats::stats_t stats;

    /* //
    shielded_a_stat_t health;
    stat_t food;
    shielded_b_stat_t karma;
    stat_t luck;

    unsigned int sleep;
    unsigned int blind;
    unsigned int stun;
    unsigned int fear;
    unsigned int rest;
    */ //
    
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

    unsigned int polymorph_turns;

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
    static const unsigned int TERRAIN_STEP2  = 0x200;
    static const unsigned int DESIGN_STEP2   = 0x400;
    static const unsigned int QUITTING       = 0x800;
    static const unsigned int SELFNOTE       = 0x1000;
    static const unsigned int CLOUDING       = 0x2000;
    static const unsigned int P_CLOUDING     = 0x4000;
    static const unsigned int P_BLASTING     = 0x8000;

    unsigned int state;

    struct input_state_t {
        std::string s;
        int limit;

        input_state_t() : limit(-1) {}
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
        tag_t terrain;
        double assets;
        tag_t item;
        unsigned int item_count;
        double item_price;

        banking_state_t() : assets(0), item_count(0), item_price(0) {}
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

    struct seen_monsters_t {
        std::set<tag_t> tally;
        std::vector<tag_t> timeline;
    };

    seen_monsters_t seen_monsters;

    Player() : species(species().get(constants().player_species)),
               px(0), py(0), worldx(0), worldy(0), worldz(-1), 
               current_wx(0), current_wy(0), current_wz(0), level(species.level), dead(false),
               stats(species.stats),
               sleep(0), blind(0), stun(0), fear(0), rest(0), digging(false), polymorph_ability(0), state(MAIN), 
               uniques_disabled(false), dungeon_unique_series(0), money_curse(0), num_replay_codes(0)
        {}

    const Species& get_speciestag() {

        return (polymorph.species.null() ? constants().player_species : polymorph.species);
    }

    const Species& get_species() {

        return (polymorph.species.null() ? species : species().get(polymorph.species));
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

                auto trig = state.triggers.insert(std::make_pair(time, GameState::trigger_t()));

                auto& summon = trig->second.summon_out_of_view;

                summon.monster = i.second.summon;
                summon.count = 0;
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

        return std::min(level, constants().player_level_cap);
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
        serialize::read(s, sp.stat);
        serialize::read(s, sp.stat_min);
        serialize::read(s, sp.stat_max);
        serialize::read(s, sp.ca_tag);
        serialize::read(s, sp.name);
        serialize::read(s, sp.timeout);
    }
};

template <>
struct writer<Terrain::spell_t> {
    void write(Sink& s, const Terrain::spell_t& sp) {
        serialize::write(s, sp.stat);
        serialize::write(s, sp.stat_min);
        serialize::write(s, sp.stat_max);
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
        serialize::read(s, p.followers);
        serialize::read(s, p.level);
        serialize::read(s, p.dead);
        serialize::read(s, p.stats);
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
        serialize::read(s, p.banking.terrain);
        serialize::read(s, p.banking.assets);
        serialize::read(s, p.banking.item);
        serialize::read(s, p.banking.item_count);
        serialize::read(s, p.banking.item_price);
        serialize::read(s, p.spells);
        serialize::read(s, p.uniques_disabled);
        serialize::read(s, p.dungeon_unique_series);
        serialize::read(s, p.money_curse);
        serialize::read(s, p.kills);
        serialize::read(s, p.achievements);
        serialize::read(s, p.input.s);
        serialize::read(s, p.input.limit);
        serialize::read(s, p.overmap.scale);
        serialize::read(s, p.num_replay_codes);
        serialize::read(s, p.ailments);
        serialize::read(s, p.starsign.day);
        serialize::read(s, p.starsign.sign);
        serialize::read(s, p.seen_monsters.tally);
        serialize::read(s, p.seen_monsters.timeline);
        
        p.current_wx = p.worldx;
        p.current_wy = p.worldy;
        p.current_wz = p.worldz;
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
        serialize::write(s, p.followers);
        serialize::write(s, p.level);
        serialize::write(s, p.dead);
        serialize::write(s, p.stats);
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
        serialize::write(s, p.banking.terrain);
        serialize::write(s, p.banking.assets);
        serialize::write(s, p.banking.item);
        serialize::write(s, p.banking.item_count);
        serialize::write(s, p.banking.item_price);
        serialize::write(s, p.spells);
        serialize::write(s, p.uniques_disabled);
        serialize::write(s, p.dungeon_unique_series);
        serialize::write(s, p.money_curse);
        serialize::write(s, p.kills);
        serialize::write(s, p.achievements);
        serialize::write(s, p.input.s);
        serialize::write(s, p.input.limit);
        serialize::write(s, p.overmap.scale);
        serialize::write(s, p.num_replay_codes);
        serialize::write(s, p.ailments);
        serialize::write(s, p.starsign.day);
        serialize::write(s, p.starsign.sign);
        serialize::write(s, p.seen_monsters.tally);
        serialize::write(s, p.seen_monsters.timeline);
    }
};

}


#endif
