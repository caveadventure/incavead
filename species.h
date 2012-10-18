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
        shoreline,
        clumped_floor,
        clumped_water,
        clumped_corner,
        clumped_shoreline
    };

    enum class ai_t : unsigned int {
        none,
        seek_player
    };

    enum class move_t : unsigned int {
        any,
        floor,
        water
    };

    std::string tag;
    std::string name;
    maudit::glyph skin;
    
    unsigned int level;
    unsigned int count;

    habitat_t habitat;
    ai_t ai;
    move_t move;

    unsigned int range;

    struct mean_deviation_t {
        double mean;
        double deviation;
        
        mean_deviation_t(double m = 0.0, double d = 0.0) : mean(m), deviation(d) {}
    };

    mean_deviation_t clumpsize;

    Species() : level(0), count(0), habitat(habitat_t::floor), ai(ai_t::none), move(move_t::any), range(0),
                clumpsize() {}

    Species(const std::string& _tag, unsigned int _level, unsigned int _count,
            const std::string& _name, const std::string& _chr, maudit::color _fore,
            habitat_t _habitat, ai_t _ai, move_t _move, unsigned int _range,
            double _clumpsize_m, double _clumpsize_d) :

        tag(_tag), name(_name), skin(_chr, _fore, maudit::color::bright_black),
        level(_level), count(_count), habitat(_habitat), ai(_ai), move(_move),
        range(_range), clumpsize(_clumpsize_m, _clumpsize_d)
        {}
};

#endif
