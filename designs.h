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

    double heal;
    double feed;
    double karma;
    double consume_luck;

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

    struct mean_deviation_t {
        double mean;
        double deviation;
        
        mean_deviation_t(double m = 0.0, double d = 0.0) : mean(m), deviation(d) {}
    };

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

    struct luck_t {
        double height;
        double mean;
        double deviation;

        luck_t() : height(0), mean(0), deviation(1) {}
    };

    std::vector<luck_t> luck;

    double hunger;
    double other_hunger_multiplier;

    double shield;

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

    bool heal_blind;
    bool heal_unluck;
    bool heal_ailments;

    std::string action_name;

    struct take_summon_t {
        tag_t species;
        unsigned int needs_count;

        take_summon_t() : needs_count(0) {}
    };

    take_summon_t take_summon;

    Design() : level(0), count(0), bonus_a_count(0), bonus_b_count(0), count_is_only_one(false), stackrange(0), 
               heal(0), feed(0), karma(0), consume_luck(0), usable(false), use_for_free(false), destructible(false), 
               throwrange(0), attack_level(-1), gencount(1, 0), melee(false), lightradius(0), digging(0), 
               descend(0), safe_descend(0), worth(0), is_lit(false), hunger(0), other_hunger_multiplier(0), 
               shield(0), count_is_rcode(false), wishing(NO_WISH), magic_mapping(false), heal_blind(false), 
               heal_unluck(false), heal_ailments(false)
        {}
    
};

#endif
