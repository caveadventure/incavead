#ifndef __CONSTANTS_BANK_H
#define __CONSTANTS_BANK_H

struct ConstantsBank {

    tag_t grave;
    tag_t meat;
    tag_t bad_meat;
    tag_t money;

    tag_t victory_item;

    struct slot_t {
        std::string slot;
        std::string label;
        std::string name;
        char letter;

        slot_t() : letter(0) {}
    };

    std::vector<slot_t> slots;

    struct shortcut_t {
        std::vector< std::pair<std::string, unsigned char> > slot_keypress;
        std::string fail_message;
        std::string help_message;
    };

    std::map<unsigned char, shortcut_t> shortcuts;

};

ConstantsBank& __constants__() {
    static ConstantsBank ret;
    return ret;
}

const ConstantsBank& constants() {
    return __constants__();
}

#endif
