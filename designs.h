#ifndef __DESIGNS_H
#define __DESIGNS_H

#include <string>

struct Design {

    tag_t tag;
    std::string name;
    maudit::glyph skin;
    
    unsigned int level;
    unsigned int count;

    std::string slot;
    std::string descr;

    damage::attacks_t attacks;
    damage::defenses_t defenses;
    bool defense_only_one;

    unsigned int stackrange;

    double heal;
    double feed;
    double karma;

    bool usable;
    bool destructible;

    unsigned int throwrange;

    struct blast_t {
        unsigned int radius;
        unsigned int range;

        blast_t() : radius(0), range(0) {}
    };

    blast_t blast;

    struct mean_deviation_t {
        double mean;
        double deviation;
        
        mean_deviation_t(double m = 0.0, double d = 0.0) : mean(m), deviation(d) {}
    };

    mean_deviation_t gencount;

    bool melee;

    unsigned int lightradius;

    double digging;

    unsigned int descend;
    unsigned int safe_descend;

    struct useflags_t {
        bool blink;

        useflags_t() : blink(false) {}
    };

    useflags_t flags;

    struct cloud_t {
        tag_t terraintag;
        unsigned int radius;

        cloud_t() : radius(0) {}
    };

    cloud_t cast_cloud;

    double worth;

    bool is_lit;

    tag_t place_permafeat;

    struct luck_t {
        double height;
        double mean;
        double deviation;

        luck_t() : height(0), mean(0), deviation(1) {}
    };

    std::vector<luck_t> luck;

    double hunger;
    double other_hunger_multiplier;

    double shield;

    Design() : level(0), count(0), defense_only_one(false), stackrange(0), heal(0), feed(0), karma(0), usable(false), 
               destructible(false), throwrange(0),
               gencount(1, 0), melee(false), lightradius(0), digging(0), descend(0), safe_descend(0), worth(0),
               is_lit(false), hunger(0), other_hunger_multiplier(0), shield(0) {}
    
};

#endif
