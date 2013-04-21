#ifndef __CONSTANTS_BANK_H
#define __CONSTANTS_BANK_H

struct ConstantsBank {

    tag_t meat;
    tag_t bad_meat;

};

ConstantsBank& __constants__() {
    static ConstantsBank ret;
    return ret;
}

const ConstantsBank& constants() {
    return __constants__();
}

#endif
