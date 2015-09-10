#ifndef __MAUDIT_TYPES_H
#define __MAUDIT_TYPES_H

#include <string.h>
#include <cstdint>
#include <string>
#include <stdexcept>

namespace maudit {

enum class color : uint8_t {
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
    uint64_t text;
    color fore;
    color back;
    bool underline;

    static uint64_t get_sym(const char* c, size_t len) {

        if (len > 7)
            throw std::runtime_error("Glyph character too large: " + std::string(c));

        uint64_t ret;
        ::memcpy((void*)(&ret), (void*)c, len + 1);
        return ret;
    }

    void set_text(const std::string& c) {
        text = get_sym(c.c_str(), c.size());
    }

    void set_text(unsigned char c) {
        unsigned char tmp[2] = { c, '\0' };
        text = get_sym((const char*)tmp, 1);
    }

    const char* get_text() const {
        return (const char*)(&text);
    }

    glyph() : fore(color::none), 
              back(color::bright_black), 
              underline(false) 
        { set_text(" "); }

    glyph(const std::string& c, color f, color b, bool u = false) : 
        fore(f), 
        back(b), 
        underline(u) 
        { set_text(c); }

    glyph(uint64_t t, color f, color b, bool u = false) : 
        text(t), 
        fore(f), 
        back(b), 
        underline(u) {}
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
