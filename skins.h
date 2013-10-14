#ifndef __SKINS_H
#define __SKINS_H

struct skins {
    maudit::glyph a;
    maudit::glyph b;

    void set(const maudit::glyph& _a, const maudit::glyph& _b) {
        a = _a;
        b = _b;
    }

    const maudit::glyph& operator[](size_t n) const {
        return (n ? b : a);
    }
};

struct ui_symbols_t {
    std::string circle;
    std::string fill;
    std::string line;
    std::string box_v;
    std::string box_h;
    std::string box_rd;
    std::string box_ru;
    std::string box_ld;
    std::string box_lu;
    std::string arrow_l;
    std::string arrow_r;
    std::string arrow_u;
    std::string arrow_d;

    ui_symbols_t() : circle("*"), fill("*"), line("*"), box_v("|"), box_h("-"),
                     box_rd("+"), box_ru("+"), box_ld("+"), box_lu("+"),
                     arrow_l("<"), arrow_r(">"), arrow_u("^"), arrow_d("v")
        {}
};


#endif
