#ifndef __CONSTANTS_BANK_H
#define __CONSTANTS_BANK_H

struct ConstantsBank {

    double hunger_rate;
    double starvation_damage;

    tag_t grave;
    tag_t meat;
    tag_t bad_meat;
    tag_t money;

    tag_t unique_item;

    struct slot_t {
        tag_t slot;
        std::string label;
        std::string name;
        char letter;

        slot_t() : letter(' ') {}
    };

    std::vector<slot_t> slots;

    struct shortcut_t {
        std::vector< std::pair<tag_t, unsigned char> > slot_keypress;
        std::string fail_message;
        std::string help_message;
    };

    std::map<unsigned char, shortcut_t> shortcuts;
    
    unsigned int uniques_timeout;

    double health_shield_max;

    size_t max_gold_per_grave;

    ui_symbols_t ui_symbols;

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

    ConstantsBank() : hunger_rate(0), starvation_damage(0), uniques_timeout(0), 
                      health_shield_max(0), max_gold_per_grave(1000), max_celauto_cells(1000),
                      achievement_trigger_rate(15) {}

};

inline ConstantsBank& __constants__() {
    static ConstantsBank ret;
    return ret;
}

inline const ConstantsBank& constants() {
    return __constants__();
}

#endif
