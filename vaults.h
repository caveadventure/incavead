#ifndef __VAULTS_H
#define __VAULTS_H

#include <set>
#include <map>
#include <string>
#include <memory>

struct Vault {

    std::string tag;
    unsigned int level;
    unsigned int count;

    struct brush {
        bool is_blank;
        bool is_walk;
        bool is_water;
        std::string terrain;
        std::string design;
        std::string species;

        brush() : is_blank(false), is_walk(false), is_water(false) {}
    };

    std::map<unsigned char, brush> brushes;
    std::vector<std::string> pic;
    
    unsigned int ax;
    unsigned int ay;

    enum class placement_t : unsigned int {
        floor,
        water,
        corner
    };

    placement_t placement;

    unsigned int w;
    unsigned int h;

    Vault() : level(0), count(0), ax(0), ay(0), placement(placement_t::floor), w(0), h(0) {}

    void postprocess() {

        h = pic.size();
        w = 0;

        for (const std::string& s : pic) {
            w = std::max((unsigned int)s.size(), w);
        }
    }

};

#endif
