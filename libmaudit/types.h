#ifndef __MAUDIT_TYPES_H
#define __MAUDIT_TYPES_H

#include <string.h>
#include <cstdint>
#include <string>
#include <stdexcept>

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
    //std::string text;
    uint64_t text;
    color fore;
    color back;

    void set_text(const std::string& c) {

        if (c.size() > 7) 
            throw std::runtime_error("Glyph character too large: " + c);

        ::memcpy((void*)(&text), (void*)(c.c_str()), c.size() + 1);
    }

    const char* get_text() const {
        return (const char*)(&text);
    }

    glyph() : fore(color::none), back(color::bright_black) { set_text(" "); }

    glyph(const std::string& c, color f, color b) : fore(f), back(b) { set_text(c); }

    glyph(uint64_t t, color f, color b) : text(t), fore(f), back(b) {}
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
