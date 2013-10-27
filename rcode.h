#ifndef __RCODE_H
#define __RCODE_H

#include <string>
#include <cstdint>

namespace rcode {

std::string magick_encode(uint32_t x) {

    static const char* topchar = "om";

    static const char* hichars[32] = {
        "e",     "ao",    "yi",    "wu",    "si",
        "shi",   "ti",    "di",    "ni",    "tian",
        "dian",  "nian",  "yin",   "da",    "ta",
        "ting",  "niao",  "feng",  "ming",  "kong",
        "long",  "hong",  "shu",   "sheng", "chi",
        "chu",   "cheng", "lu",    "liao",  "hao",
        "ru",    "ri"
    };

    /*
    static const char* lochars[16] = {
        "a",   "ard", "als", "amz",  // anp
        "emp", "est", "elz", "erp",
        "orz", "ond", "olp", "osf",
        "urd", "und", "ump", "upl"
    };
    */

    static const char* lochars[16] = {
        "a",   "e",   "o",   "u",
        "ash", "es",  "oh",  "uz",
        "am",  "er",  "ol",  "um",
        "amz", "erp", "olf", "ump"
    };

    uint16_t low = x & 0xFFFF;
    uint16_t hic = (x >> 16) & 0x1F;
    uint16_t hib = (x >> 21) & 0x1F;
    uint16_t hia = (x >> 26) & 0x1F;
    bool top = (x >> 31);

    std::string ret;

    if (top) {
        ret += topchar;
        ret += "-";
    }

    if (hia) {
        ret += hichars[hia];
        ret += " ";
    }

    if (hib) {
        ret += hichars[hib];
    }

    ret += hichars[hic];
    ret += "-";
    
    ret += lochars[low >> 12];
    ret += lochars[(low >> 8) & 0xF];
    ret += lochars[(low >> 4) & 0xF];
    ret += lochars[low & 0xF];

    return ret;
}


template <typename T>
std::string encode(T x) {

    static const std::string v = 
        "0123456789ABCDEFGHJKMNPQRSTUWXYZ";

    std::string ret;

    while (x != 0) {
        ret += v[x&31];
        x = x >> 5;
    }

    return ret;
}

template <typename T>
T decode(const std::string& x) {

    const T v[128] = {

        0, 0, 0, 0, 0, 0, 0, 0, // 0x00-0x07
        0, 0, 0, 0, 0, 0, 0, 0, // 0x08-0x0f
        0, 0, 0, 0, 0, 0, 0, 0, // 0x10-0x17
        0, 0, 0, 0, 0, 0, 0, 0, // 0x18-0x1f
        0, 0, 0, 0, 0, 0, 0, 0, // 0x20-0x27 ' '-"'"
        0, 0, 0, 0, 0, 0, 0, 0, // 0x28-0x2f '('-'/'

        1, 2, 3, 4, 5, 6, 7, 8,  // 0x30-0x37 '0'-'7'
        9, 10, 0, 0, 0, 0, 0, 0, // 0x38-0x3f '8'-'?'

        0, 11, 12, 13, 14, 15, 16, 17,  // 0x40-0x47 '@'-'G'
        18, 2, 19, 20, 2, 21, 22, 1,    // 0x48-0x4f 'H'-'O'
        23, 24, 25, 26, 27, 28, 28, 29, // 0x50-0x57 'P'-'W'
        30, 31, 32, 0, 0, 0, 0, 0,      // 0x58-0x5f 'X'-'_'

        0, 11, 12, 13, 14, 15, 16, 17,  // 0x40-0x47 '`'-'g'
        18, 2, 19, 20, 2, 21, 22, 1,    // 0x48-0x4f 'h'-'o'
        23, 24, 25, 26, 27, 28, 28, 29, // 0x50-0x57 'p'-'w'
        30, 31, 32, 0, 0, 0, 0, 0       // 0x58-0x5f 'x'-DEL
    };

    T ret = 0;

    for (int j = x.size() - 1; j >= 0; --j) {
        unsigned int i = x[j];

        if (i >= 128) continue;

        T n = v[i & 0x7F];

        if (n > 0) {
            ret = ret << 5;
            ret |= (n-1);
        }
    }

    return ret;
}


}

#endif
