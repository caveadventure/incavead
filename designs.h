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

    double attack;
    double defense;

    unsigned int stackrange;

    double heal;

    bool usable;

    Design() : level(0), count(0), attack(0), defense(0), stackrange(0), heal(0), usable(false) {}

};

#endif
