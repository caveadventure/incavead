#ifndef __SPECIES_H
#define __SPECIES_H

#include <string>

#include "counters.h"

struct Species {
    enum class habitat_t : unsigned int {
        floor,
        water,
        corner,
        shoreline
    };


    std::string tag;
    std::string name;
    maudit::glyph skin;
    
    unsigned int level;
    unsigned int count;

    habitat_t habitat;

    Species() : level(0), count(0), habitat(habitat_t::floor) {}

    Species(const std::string& _tag, unsigned int _level, unsigned int _count,
            const std::string& _name, const std::string& _chr, maudit::color _fore,
            habitat_t _habitat) :

        tag(_tag), name(_name), skin(_chr, _fore, maudit::color::bright_black),
        level(_level), count(_count), habitat(_habitat)
        {}
};

#endif
