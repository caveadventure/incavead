#ifndef __MAUDIT_TYPES_H
#define __MAUDIT_TYPES_H

#include <string>

namespace maudit {

enum class color : uint32_t {
    none = 0,

    dim_black,
    dim_red,
    dim_green,
    dim_yellow,
    dim_blue,
    dim_magenta,
    dim_cyan,
    dim_white,

    bright_black,
    bright_red,
    bright_green,
    bright_yellow,
    bright_blue,
    bright_magenta,
    bright_cyan,
    bright_white
};

struct glyph {
    std::string text;
    color fore;
    color back;

    glyph() : text(" "), fore(color::none), back(color::bright_black) {}

    glyph(const std::string& c, color f, color b) : text(c),  fore(f), back(b) {}
};


enum class keycode : uint32_t {
    none = 0,

    left,
    right,
    up,
    down,
    kp_7,
    kp_9,
    kp_1,
    kp_3,
    del,
    esc,
    resize
};


struct keypress {
    unsigned char letter;
    keycode key;

    unsigned int w;
    unsigned int h;

    keypress(unsigned char l = 0) : letter(l), key(keycode::none), w(0), h(0) {}
};

}

#endif
