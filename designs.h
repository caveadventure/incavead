#ifndef __DESIGNS_H
#define __DESIGNS_H

#include <string>

struct Design {

    tag_t tag;
    std::string name;
    skins skin;
    tag_t flavor;
    
    unsigned int level;
    unsigned int count;

    unsigned int bonus_a_count;
    unsigned int bonus_b_count;

    tag_t slot;
    std::string descr;

    damage::attacks_t attacks;
    damage::defenses_t defenses;
    bool count_is_only_one;

    unsigned int stackrange;

    struct inc_stat_t {
        tag_t stat;
        double val;
        std::string msg;

        inc_stat_t() : val(0) {}
    };

    std::vector<inc_stat_t> inc_stat;

    struct inc_count_t {
        tag_t stat;
        int val;
        std::string msg_a;
        std::string msg_b;

        inc_count_t() : val(0) {}
    };

    std::vector<inc_count_t> inc_count;

    struct zero_stat_t {
        tag_t stat;
        std::string msg;
    };

    std::vector<zero_stat_t> zero_stat;

    bool usable;
    bool use_for_free;
    bool destructible;

    unsigned int throwrange;

    struct blast_t {
        unsigned int radius;
        unsigned int range;

        blast_t() : radius(0), range(0) {}
    };

    blast_t blast;

    int attack_level;

    mean_deviation_t gencount;

    bool melee;

    unsigned int lightradius;

    double digging;

    int descend;
    int safe_descend;

    struct useflags_t {
        bool blink;
        bool enable_spells;
        bool random_spell;
        bool dowsing;

        useflags_t() : blink(false), enable_spells(false), random_spell(false), dowsing(false) {}
    };

    useflags_t flags;

    struct cloud_t {
        tag_t terraintag;
        unsigned int radius;
        unsigned int range;

        cloud_t() : radius(0), range(0) {}
    };

    cloud_t cast_cloud;

    double worth;

    bool is_lit;

    struct permafeat_t {
        tag_t feat;
        int walk;
        int water;

        permafeat_t() : feat(), walk(-1), water(-1) {}
    };

    permafeat_t place_permafeat;

    struct tickstat_moon_t {
        tag_t stat;
        double height;
        mean_deviation_t v;

        tickstat_moon_t() : height(0), v(0, 1) {}
    };

    std::vector<tickstat_moon_t> tickstat_moon;

    struct tickstat_t {
        tag_t stat;
        double add;
        double mul;
        bool apply_count;

        tickstat_t() : add(0.0), mul(1.0), apply_count(true) {}
    };

    std::vector<tickstat_t> tickstat;

    struct spell_t {
        tag_t ca_tag;
        std::string name;
    };

    std::vector<spell_t> spells;

    bool count_is_rcode;

    tag_t genocide;

    enum {
        NO_WISH = 0,
        SIMPLE_WISH = 1,
        SPECIAL_WISH = 2
    } wishing;

    bool magic_mapping;
    
    bool heal_ailments;
    bool heal_polymorph;

    std::string action_name;

    struct take_summon_t {
        tag_t species;
        unsigned int needs_count;

        take_summon_t() : needs_count(0) {}
    };

    take_summon_t take_summon;

    bool forbid_wish;

    int change_count;

    struct starsign_t {
        unsigned int day;
        unsigned int sign;
        
        starsign_t() : day(0), sign(0) {}
    };

    starsign_t starsign;

    struct summon_t {
        tag_t species;
        unsigned int count;

        summon_t() : count(0) {}
    };

    summon_t summon;

    struct polymorph_t {
        tag_t species;
        mean_deviation_t turns;
        std::string msg;
    };

    polymorph_t polymorph;

    struct fast_t {
        unsigned int slice;
        mean_deviation_t turns;

        fast_t() : slice(0) {}
    };

    fast_t fast;

    tag_t monster_raised;

    tag_t raise_monsters;

    struct charm_t {
        unsigned int range;
        std::string msg;
        charm_t() : range(0) {}
    };

    charm_t charm;
    
    bool label_spot;

    Design() : level(0), count(0), bonus_a_count(0), bonus_b_count(0), count_is_only_one(false), stackrange(0), 
               usable(false), use_for_free(false), destructible(false), 
               throwrange(0), attack_level(-1), gencount(1, 0), melee(false), lightradius(0), digging(0), 
               descend(0), safe_descend(0), worth(0), is_lit(false), count_is_rcode(false), wishing(NO_WISH),
               magic_mapping(false), 
               heal_ailments(false), heal_polymorph(false), 
               forbid_wish(false), change_count(0), label_spot(false)
        {}
    
};

#endif
