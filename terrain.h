#ifndef __TERRAIN_H
#define __TERRAIN_H

#include <string>

struct Terrain {
    enum class placement_t : unsigned int {
        floor,
        water
    };

    std::string tag;
    std::string name;
    maudit::glyph skin;

    placement_t placement;

    unsigned int stairs;
    
    Terrain() : placement(placement_t::floor), stairs(0) {}

    Terrain(const std::string& _tag, const std::string& _name, const std::string& _chr, maudit::color _fore,
            placement_t _placement, unsigned int _stairs) :
        tag(_tag), name(_name), skin(_chr, _fore, maudit::color::bright_black),
        placement(_placement), stairs(_stairs)
        {}
};

#endif
