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
        clumped_water
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

    Species() : level(0), count(0), habitat(habitat_t::floor), ai(ai_t::none), move(move_t::any), range(0) {}

    Species(const std::string& _tag, unsigned int _level, unsigned int _count,
            const std::string& _name, const std::string& _chr, maudit::color _fore,
            habitat_t _habitat, ai_t _ai, move_t _move, unsigned int _range) :

        tag(_tag), name(_name), skin(_chr, _fore, maudit::color::bright_black),
        level(_level), count(_count), habitat(_habitat), ai(_ai), move(_move),
        range(_range)
        {}
};

#endif
