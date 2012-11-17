#ifndef __SPECIES_H
#define __SPECIES_H

#include <string>

#include "counters.h"

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
        seek_nosleep
    };

    enum class idle_ai_t : unsigned int {
        none,
        random
    };

    enum class move_t : unsigned int {
        walk,
        floor,
        water,
        corner
    };

    std::string tag;
    std::string name;
    maudit::glyph skin;
    
    unsigned int level;
    unsigned int count;

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
        std::string tag;
        double chance;

        companion_t(const std::string& t = "", double c = 0.0) : tag(t), chance(c) {}
    };

    std::vector<companion_t> companion;

    struct drop_t {
        std::string tag;
        double chance;

        drop_t(const std::string& t = "", double c = 0.0) : tag(t), chance(c) {}
    };

    std::vector<drop_t> drop;

    damage::attacks_t attacks;
    damage::defenses_t defenses;

    struct cloud_t {
        double chance;
        std::string terraintag;
        unsigned int radius;
        unsigned int turns;
        std::string name;

        cloud_t() : chance(0), radius(0), turns(0) {}
    };

    std::vector<cloud_t> cast_cloud;

    struct summon_t {
        double chance;
        std::string speciestag;
        unsigned int turns;

        summon_t() : chance(0), turns(0) {}
    };

    std::vector<summon_t> summon;

    struct flags_t {
        bool undead;
        bool animal;
        bool magic;
        bool plant;

        flags_t() : undead(false), animal(false), magic(false), plant(false) {}
    };

    flags_t flags;

    double karma;

    Species() : level(0), count(0), habitat(habitat_t::walk), ai(ai_t::none), idle_ai(idle_ai_t::none),
                move(move_t::walk), range(0), clumpsize(), flags(), karma(0) {}

};

#endif
