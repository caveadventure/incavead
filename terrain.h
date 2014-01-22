#ifndef __TERRAIN_H
#define __TERRAIN_H

#include <string>

struct Terrain {
    enum class placement_t : unsigned int {
        floor,
        water,
        corner,
        lowlands,
        shoreline
    };

    tag_t tag;
    std::string name;
    std::string descr;
    skins skin;

    unsigned int count;

    placement_t placement;

    int stairs;
    int tunnel_x;
    int tunnel_y;

    bool viewblock;
    bool walkblock;

    unsigned int decay;

    unsigned int attack_level;
    damage::attacks_t attacks;

    bool sticky;
    bool is_lit;
    bool air;
    unsigned int charges;

    struct spell_t {
        double karma_bound;
        tag_t ca_tag;
        std::string name;
        double timeout;

        spell_t() : karma_bound(0), timeout(0) {}
    };

    spell_t grant_spell;

    tag_t victory_item;

    bool safebox;

    struct racket_t {
        double shield_bonus;
        double money_curse;

        racket_t() : shield_bonus(0), money_curse(0) {}
    };

    racket_t protection_racket;

    struct uncharge_t {
        bool attack;
        bool move;
        bool use;
        bool summon;

        uncharge_t() : attack(false), move(false), use(false), summon(false) {}
    };

    uncharge_t uncharge;

    struct craft_t {
        tag_t from;
        tag_t to;
    };

    std::vector<craft_t> crafting;

    enum {
        NO_WISH = 0,
        SIMPLE_WISH = 1,
        SPECIAL_WISH = 2
    } wishing;

    bool important;

    int view_radius;

    struct summon_t {
        tag_t genus;
        unsigned int level;
        unsigned int count;

        summon_t() : level(0), count(0) {}
    };

    summon_t summon;

    Terrain() : count(0), placement(placement_t::floor), stairs(0), tunnel_x(0), tunnel_y(0),
                viewblock(false), walkblock(false), decay(0), attack_level(0),
                sticky(false), is_lit(false), air(false), charges(0), safebox(false),
                wishing(NO_WISH), important(false), view_radius(-1) {}

};

#endif
