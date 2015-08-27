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
        seek,
        random,
        seek_awake,
        magic_none,
        magic_none_awake,
        suicide,
        magic_random
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

    std::string descr;

    habitat_t habitat;
    ai_t ai;
    idle_ai_t idle_ai;
    move_t move;

    pstats::stats stats;

    double digging;
    
    unsigned int range;

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
        tag_t damage_type;

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
        bool cosmic;
        bool stealthy;
        bool player;
        
        flags_t() : 
            undead(false), animal(false), magic(false), plant(false), robot(false), 
            terrain_immune(false), eyeless(false), cosmic(false), stealthy(false),
            player(false)
            {}
    };

    flags_t flags;

    struct blast_t {
        double chance;
        unsigned int radius;
        unsigned int range;
        unsigned int turns;
        damage::attacks_t attacks;
        std::string name;

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

    std::map<tag_t, double> inc_stat;

    tag_t ally;

    Species() : level(0), count(0), true_level(-1), habitat(habitat_t::walk), ai(ai_t::none), idle_ai(idle_ai_t::none),
                move(move_t::walk), digging(0), range(0), clumpsize(), flags() {}


    unsigned int get_computed_level() const {
        return (true_level >= 0 ? true_level : level);
    }
};

#endif
