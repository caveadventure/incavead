#ifndef __SPECIES_H
#define __SPECIES_H

#include <string>

struct Species {
    enum class habitat_t : unsigned int {
        walk,
        floor,
        water,
        corner,
        shoreline
    };

    enum class ai_t : unsigned int {
        none,
        seek_player,
        random,
        inrange_random,
        seek_nosleep,
        none_nosleep,
        suicide
    };

    enum class idle_ai_t : unsigned int {
        none,
        random
    };

    enum class move_t : unsigned int {
        walk,
        floor,
        water,
        corner,
        shoreline
    };

    tag_t tag;
    std::string name;
    skins skin;
    
    unsigned int level;
    unsigned int count;

    int true_level;

    tag_t genus;

    habitat_t habitat;
    ai_t ai;
    idle_ai_t idle_ai;
    move_t move;

    unsigned int range;

    struct mean_deviation_t {
        double mean;
        double deviation;
        
        mean_deviation_t(double m = 0.0, double d = 0.0) : mean(m), deviation(d) {}
    };

    mean_deviation_t clumpsize;

    struct companion_t {
        tag_t tag;
        double chance;

        companion_t(tag_t t = tag_t(), double c = 0.0) : tag(t), chance(c) {}
    };

    std::vector<companion_t> companion;

    struct drop_t {
        tag_t tag;
        double chance;
        unsigned int level;

        drop_t(tag_t t = tag_t(), double c = 0.0, unsigned int l = 0) : tag(t), chance(c), level(0) {}
    };

    std::vector<drop_t> drop;

    damage::attacks_t attacks;
    damage::defenses_t defenses;

    struct cloud_t {
        double chance;
        tag_t terraintag;
        unsigned int radius;
        unsigned int turns;
        std::string name;

        cloud_t() : chance(0), radius(0), turns(0) {}
    };

    std::vector<cloud_t> cast_cloud;

    struct summon_t {
        double chance;
        tag_t speciestag;
        unsigned int turns;
        std::string msg;

        summon_t() : chance(0), turns(0) {}
    };

    std::vector<summon_t> summon;

    tag_t death_summon;

    struct spawn_t {
        double chance;
        unsigned int level;
        unsigned int turns;
        std::string msg;

        spawn_t() : chance(0), turns(0) {}
    };

    std::vector<spawn_t> spawns;

    struct flags_t {
        bool undead;
        bool animal;
        bool magic;
        bool plant;
        bool robot;
        bool terrain_immune;
        bool eyeless;

        flags_t() : 
            undead(false), animal(false), magic(false), plant(false), robot(false), 
            terrain_immune(false), eyeless(false)
            {}
    };

    flags_t flags;

    double karma;

    struct blast_t {
        double chance;
        unsigned int radius;
        unsigned int range;
        unsigned int turns;
        damage::attacks_t attacks;

        blast_t() : chance(0), radius(0), range(0), turns(0) {}
    }; 

    std::vector<blast_t> blast;

    struct trail_t {
        tag_t terrain;
        mean_deviation_t cost;
    };

    trail_t trail;

    tag_t steal;

    struct morph_t {
        tag_t species;
        double chance;

        morph_t() : chance(0) {}
    };

    morph_t morph;

    Species() : level(0), count(0), true_level(-1), habitat(habitat_t::walk), ai(ai_t::none), idle_ai(idle_ai_t::none),
                move(move_t::walk), range(0), clumpsize(), flags(), karma(0) {}


    unsigned int get_computed_level() const {
        return (true_level >= 0 ? true_level : level);
    }
};

#endif
