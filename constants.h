#ifndef __CONSTANTS_BANK_H
#define __CONSTANTS_BANK_H

#include <vector>
#include <set>
#include <map>

struct ConstantsBank {

    size_t max_permafeats;
    size_t max_bones;

    double hunger_rate;
    double starvation_damage;

    tag_t grave;
    tag_t pit;
    tag_t bad_grave;
    tag_t ghost;

    std::set<tag_t> money;

    tag_t unique_item;

    struct slot_t {
        tag_t slot;
        std::string label;
        std::string name;
        char letter;

        slot_t() : letter(' ') {}
    };

    std::vector<slot_t> slots;

    tag_t money_slot;

    struct shortcut_t {
        std::vector< std::pair<tag_t, unsigned char> > slot_keypress;
        std::string fail_message;
        std::string help_message;
    };

    std::map<unsigned char, shortcut_t> shortcuts;
    
    unsigned int uniques_timeout;

    double min_money_value;

    std::vector<ui_symbols_t> ui_symbols;

    size_t max_celauto_cells;

    std::string howto_text;

    std::string tombstone_text;

    struct achievement_t {
        tag_t genus;
        unsigned int kills;
        unsigned int priority;
        std::string label;
        tag_t summon;

        achievement_t() : kills(0), priority(0) {}
    };

    std::map<tag_t, achievement_t> achievements;

    std::map<tag_t, std::string> genus_names;

    size_t achievement_trigger_rate;

    skins player_skin;

    unsigned int blindturns_to_radius;

    struct ailment_t {
        damage::attacks_t attacks;
        unsigned int level;
        std::string name;
        unsigned int triggers;
        bool oneshot;

        ailment_t() : level(0), triggers(1), oneshot(false) {}
    };

    std::map<tag_t, ailment_t> ailments;

    unsigned int max_ailments;

    mean_deviation_t treasure_chance;

    double monetary_supply_base;

    mean_deviation_t bonus_a_items;
    mean_deviation_t bonus_b_items;

    struct flavor_moon_frequency_t {
        double height;
        mean_deviation_t curve;

        flavor_moon_frequency_t() : height(0), curve(0, 1) {}
    };

    std::map<tag_t,flavor_moon_frequency_t> flavor_moon_frequency;

    unsigned int player_level_cap;

    struct starsigns_t {
        time_t zero;
        unsigned int nday;
        unsigned int nsign;
        std::map<unsigned int, std::string> names;

        starsigns_t() : zero(0), nday(13), nsign(20) {}
    };

    starsigns_t starsigns;

    unsigned int ai_radius;

    std::vector<tag_t> hud_stats_order;
    std::vector<tag_t> hud_counts_order;

    ConstantsBank() : max_permafeats(150), max_bones(1000),
                      hunger_rate(0), starvation_damage(0), uniques_timeout(0), 
                      min_money_value(0.01), max_celauto_cells(1000),
                      achievement_trigger_rate(15),
                      blindturns_to_radius(10),
                      max_ailments(6u),
                      monetary_supply_base(1e6),
                      player_level_cap(12),
                      ai_radius(30) {}

};

inline ConstantsBank& __constants__() {
    static ConstantsBank ret;
    return ret;
}

inline const ConstantsBank& constants() {
    return __constants__();
}

#endif
