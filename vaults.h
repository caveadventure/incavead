#ifndef __VAULTS_H
#define __VAULTS_H

#include <set>
#include <map>
#include <string>
#include <memory>

struct Vault {

    tag_t tag;
    unsigned int level;
    unsigned int count;

    struct brush {
        bool is_blank;
        bool is_walk;
        bool is_water;
        tag_t terrain;

        struct design_t {
            enum class type_t : unsigned int {
                NONE,
                SPECIFIC,
                LEVEL,
                LEVEL_ANY
            };

            type_t type;
            tag_t tag;
            unsigned int level;

            design_t() : type(type_t::NONE), level(0) {}
        };

        design_t design;

        struct species_t {
            enum class type_t : unsigned int {
                NONE,
                SPECIFIC,
                GENUS,
                LEVEL
            };
            
            type_t type;
            tag_t tag;
            unsigned int level;

            species_t() : type(type_t::NONE), level(0) {}
        };

        species_t species;

        brush() : is_blank(false), is_walk(false), is_water(false) {}
    };

    typedef std::map<unsigned char, brush> brushes_t;
    brushes_t brushes;

    std::vector<std::string> pic;

    unsigned int ax;
    unsigned int ay;

    enum class placement_t : unsigned int {
        floor,
        water,
        corner,
        shoreline,
        lowlands,
        packing
    };

    placement_t placement;

    unsigned int w;
    unsigned int h;

    tag_t inherit;
    bool transpose;

    unsigned int priority;

    int px;
    int py;

    bool use_species_counts;

    enum class type_t : unsigned int {
        FIXED,
        SEMIRANDOM,
        RANDOM
    };

    type_t type;

    struct cloud_t {
        size_t n;
        mean_deviation_t distrib;
        std::vector<double> chances;
        std::vector<unsigned char> brushes;

        cloud_t() : n(0) {}
    };

    cloud_t cloud;

    struct blob_t {
        size_t n;
        placement_t placement;
        unsigned char brush;

        blob_t() : n(0), placement(placement_t::floor), brush(0) {}
    };

    blob_t blob;

    struct river_t {
        size_t n;
        unsigned char brush;
        mean_deviation_t angle;
        mean_deviation_t width;
        unsigned int splitchance;

        river_t() : n(0), brush(0), splitchance(0) {}
    };

    river_t river;
    
    Vault() : level(0), count(0), ax(0), ay(0), placement(placement_t::floor), 
              w(0), h(0), transpose(false), priority(0), px(-1), py(-1),
              use_species_counts(false), type(type_t::FIXED) {}

    void postprocess() {

        unsigned int _h = pic.size();
        unsigned int _w = 0;

        for (const std::string& s : pic) {
            _w = std::max((unsigned int)s.size(), _w);
        }

        w = std::max(w, _w);
        h = std::max(h, _h);
    }

};

#endif
