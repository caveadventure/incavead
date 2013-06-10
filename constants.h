#ifndef __CONSTANTS_BANK_H
#define __CONSTANTS_BANK_H

struct ConstantsBank {

    tag_t meat;
    tag_t bad_meat;

    struct slot_t {
        std::string slot;
        std::string label;
        std::string name;
        char letter;

        slot_t() : letter(0) {}
    };

    std::vector<slot_t> slots;

};

ConstantsBank& __constants__() {
    static ConstantsBank ret;
    return ret;
}

const ConstantsBank& constants() {
    return __constants__();
}

#endif
