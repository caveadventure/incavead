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
    tag_t meat;
    tag_t bad_meat;
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

    double health_shield_max;

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

    struct damage_to_turns_t {
        int scale;
        int offset;
        
        damage_to_turns_t(int s = 0, int o = 0) : scale(s), offset(o) {}
    };

    damage_to_turns_t damage_to_sleepturns;
    damage_to_turns_t damage_to_scareturns;
    damage_to_turns_t damage_to_blindturns;

    unsigned int blindturns_to_radius;

    struct ailment_t {
        damage::attacks_t attacks;
        unsigned int level;
        std::string name;
        unsigned int triggers;

        ailment_t() : level(0), triggers(1) {}
    };

    std::map<tag_t, ailment_t> ailments;

    unsigned int max_ailments;

    struct mean_deviation_t {
        double mean;
        double deviation;
        
        mean_deviation_t(double m = 0.0, double d = 0.0) : mean(m), deviation(d) {}
    };

    mean_deviation_t treasure_chance;

    double monetary_supply_base;

    mean_deviation_t bonus_a_items;
    mean_deviation_t bonus_b_items;

    struct flavor_moon_frequency_t {
        double height;
        double mean;
        double deviation;

        flavor_moon_frequency_t() : height(0), mean(0), deviation(1) {}
    };

    std::map<tag_t,flavor_moon_frequency_t> flavor_moon_frequency;

    unsigned int player_level_cap;


    ConstantsBank() : max_permafeats(150), max_bones(1000),
                      hunger_rate(0), starvation_damage(0), uniques_timeout(0), 
                      health_shield_max(0), min_money_value(0.01), max_celauto_cells(1000),
                      achievement_trigger_rate(15),
                      damage_to_sleepturns(20, 15),
                      damage_to_scareturns(30, 20),
                      damage_to_blindturns(10, 0),
                      blindturns_to_radius(10),
                      max_ailments(6u),
                      monetary_supply_base(1e6),
                      player_level_cap(12) {}

};

inline ConstantsBank& __constants__() {
    static ConstantsBank ret;
    return ret;
}

inline const ConstantsBank& constants() {
    return __constants__();
}

#endif
