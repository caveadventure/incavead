#ifndef __SKINS_H
#define __SKINS_H

struct skins {
    maudit::glyph a;
    maudit::glyph b;
    maudit::glyph c;

    void set(const maudit::glyph& _a, const maudit::glyph& _b, const maudit::glyph& _c) {
        a = _a;
        b = _b;
        c = _c;
    }

    const maudit::glyph& operator[](size_t n) const {
        switch (n) {
        case 2:
            return c;
            break;
        case 1:
            return b;
            break;
        default:
            return a;
            break;
        }
    }
};

struct ui_symbol_t {
    maudit::glyph circle;
    maudit::glyph fill;
    maudit::glyph line;
    maudit::glyph box_v;
    maudit::glyph box_h;
    maudit::glyph box_rd;
    maudit::glyph box_ru;
    maudit::glyph box_ld;
    maudit::glyph box_lu;
    maudit::glyph arrow_l;
    maudit::glyph arrow_r;
    maudit::glyph arrow_u;
    maudit::glyph arrow_d;
    maudit::glyph wspace;
};

struct ui_symbols_t {
    skins circle;
    skins fill;
    skins line;
    skins box_v;
    skins box_h;
    skins box_rd;
    skins box_ru;
    skins box_ld;
    skins box_lu;
    skins arrow_l;
    skins arrow_r;
    skins arrow_u;
    skins arrow_d;
    skins wspace;
    
    ui_symbol_t operator[](size_t n) const {
        return ui_symbol_t{ 
                   circle[n], fill[n], line[n], box_v[n], box_h[n], box_rd[n], box_ru[n],
                   box_ld[n], box_lu[n], arrow_l[n], arrow_r[n], arrow_u[n], arrow_d[n], wspace[n]
               };    
    }
};


#endif
