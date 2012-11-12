#ifndef __DESIGNS_H
#define __DESIGNS_H

#include <string>

#include "counters.h"

struct Design {

    std::string tag;
    std::string name;
    maudit::glyph skin;
    
    unsigned int level;
    unsigned int count;

    std::string slot;
    std::string descr;

    damage::attacks_t attacks;
    damage::defenses_t defenses;

    unsigned int stackrange;

    double heal;

    bool usable;

    unsigned int throwrange;

    double poison_defense;

    Design() : level(0), count(0), stackrange(0), heal(0), usable(false),
               throwrange(0), poison_defense(0) {}

};

#endif
