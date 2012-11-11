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
        inrange_random
    };

    enum class idle_ai_t : unsigned int {
        none,
        random
    };

    enum class move_t : unsigned int {
        any,
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

    double attack;
    double defense;

    struct cloud_t {
        double chance;
        std::string terraintag;
        unsigned int radius;
        unsigned int turns;
        std::string name;

        cloud_t() : chance(0), radius(0), turns(0) {}
    };

    std::vector<cloud_t> cast_cloud;

    double sleepattack;

    Species() : level(0), count(0), habitat(habitat_t::floor), ai(ai_t::none), idle_ai(idle_ai_t::none),
                move(move_t::any), range(0), clumpsize(),
                attack(0), defense(0), sleepattack(0) {}

};

#endif
