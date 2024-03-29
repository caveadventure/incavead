#ifndef __RENDER_H
#define __RENDER_H

#include <list>
#include <stdexcept>

#include "libmaudit/maudit.h"

#include "fov.h"
#include "bresenham.h"


namespace serialize {

template <>
struct reader<maudit::color> {
    void read(Source& s, maudit::color& v) {
	reader<uint32_t>().read(s, (uint32_t&)v);
    }
};

template <>
struct writer<maudit::color> {
    void write(Sink& s, const maudit::color& v) {
	writer<uint32_t>().write(s, (uint32_t)v);
    }
};

template <>
struct reader<maudit::glyph> {
    void read(Source& s, maudit::glyph& v) {
        serialize::read(s, v.text);
        serialize::read(s, v.fore);
        serialize::read(s, v.back);
    }
};

template <>
struct writer<maudit::glyph> {
    void write(Sink& s, const maudit::glyph& v) {
        serialize::write(s, v.text);
        serialize::write(s, v.fore);
        serialize::write(s, v.back);
    }
};

template <>
struct reader<maudit::keycode> {
    void read(Source& s, maudit::keycode& v) {
	reader<uint32_t>().read(s, (uint32_t&)v);
    }
};

template <>
struct writer<maudit::keycode> {
    void write(Sink& s, const maudit::keycode& v) {
	writer<uint32_t>().write(s, (uint32_t)v);
    }
};

template <>
struct reader<maudit::keypress> {
    void read(Source& s, maudit::keypress& v) {
        serialize::read(s, v.letter);
        serialize::read(s, v.key);
    }
};

template <>
struct writer<maudit::keypress> {
    void write(Sink& s, const maudit::keypress& v) {
        serialize::write(s, v.letter);
        serialize::write(s, v.key);
    }
};

}


namespace grender {


typedef std::pair<unsigned int, unsigned int> pt;

typedef maudit::color color_t;

struct Grid {

    static const size_t skincount = 8;

    static const color_t black_color  = color_t::bright_black;
    static const color_t blue_color   = color_t::dim_blue;
    static const color_t yellow_color = color_t::bright_yellow;
    static const color_t gray_color   = color_t::dim_white;
    static const color_t white_color  = color_t::bright_white;
    static const color_t no_color     = color_t::none;

    typedef maudit::glyph skin;

    typedef maudit::keypress keypress;

    struct gridpoint {
	std::vector<skin> skins;
	uint8_t is_lit;
        uint8_t is_lightsource;
	uint8_t in_fov;
        uint8_t is_viewblock;
        uint8_t is_walkblock;

        bool valid;

	gridpoint() : is_lit(0), is_lightsource(0), in_fov(0), is_viewblock(0), is_walkblock(0), valid(false)
            {
                skins.resize(skincount);
            }
    };


    struct message {
        std::string text;
        bool important;
        bool temporary;
        unsigned int timestamp;

        message(const std::string& t = "", bool i = false, unsigned int ts = 0, bool temp = false) :
            text(t), important(i), temporary(temp), timestamp(ts) {}
    };

    struct hud_line {
        enum numtype_t { SIGNED, UNSIGNED };
        numtype_t numtype;
        int npips;
        std::string label;
        skin lskin;
        skin pskin;
        skin nskin;

        hud_line(numtype_t nt, int np, const std::string& l,
                 const skin& ls, const skin& ps, const skin& ns) : 
            numtype(nt), npips(np), label(l), lskin(ls), pskin(ps), nskin(ns) {}
    };

    unsigned int w;
    unsigned int h;

    std::vector<gridpoint> grid;

    std::list<message> messages;

    // transient, not saved in dump.
    uint32_t current_draw_n;
    std::vector< std::pair<uint32_t, skin> > overlay;

    struct textlabel_t {
        std::string label;
        unsigned int x;
        unsigned int y;
        color_t fg;
        color_t bg;

        textlabel_t(const std::string& l = "", unsigned int _x = 0, unsigned int _y = 0, 
                    color_t _fg = white_color, color_t _bg = black_color) :
            label(l), x(_x), y(_y), fg(_fg), bg(_bg) {}
    };

    std::map< uint32_t, std::vector<textlabel_t> > textlabels;

    // transient, not saved in dump.
    std::vector<hud_line> hud_pips;

    std::vector<ui_symbol_t> ui_symbol_themes;
    ui_symbol_t ui_symbol;
    size_t ui_symbol_index;

private:

    color_t color_fade(color_t c, double v, uint8_t mask, bool true_fade) {

        if (v > 10 && (mask & 0xF0)) {
            v -= 10;
        }

        if (!true_fade) {

            if (v > 90) {
                return color_t::dim_black;

            } else {
                return c;
            }
        }

        if (v <= 30) {
            return c;

        } else if (v <= 70) {
            switch (c) {
            case color_t::bright_black:   return color_t::bright_black;
            case color_t::bright_red:     return color_t::dim_red;
            case color_t::bright_green:   return color_t::dim_green;
            case color_t::bright_yellow:  return color_t::dim_yellow;
            case color_t::bright_blue:    return color_t::dim_blue;
            case color_t::bright_magenta: return color_t::dim_magenta;
            case color_t::bright_cyan:    return color_t::dim_cyan;
            case color_t::bright_white:   return color_t::dim_white;
            default: return c;
            }

        } else if (v <= 90) {
            return color_t::bright_black;

        } else {
            return color_t::dim_black;
        }
    }

    double _dist(const pt& a, const pt& b) {

        unsigned int dx = abs((int)a.first - (int)b.first);
        unsigned int dy = abs((int)a.second - (int)b.second);
        return sqrt(dx*dx + dy*dy);
    }

    bool _translate_v2g(int voff_x, int voff_y, const pt& vxy, pt& gxy) {

        int rx = (int)vxy.first + voff_x;
        int ry = (int)vxy.second + voff_y;

        if (rx < 0 || (unsigned int)rx >= w || ry < 0 || (unsigned int)ry >= h)
            return false;

        gxy.first = (unsigned int)rx;
        gxy.second = (unsigned int)ry;
        return true;
    }

    bool _translate_g2v(int voff_x, int voff_y, unsigned int view_w, unsigned int view_h, const pt& gxy, pt& vxy) {

        int rx = (int)gxy.first - voff_x;
        int ry = (int)gxy.second - voff_y;

        if (rx < 0 || (unsigned int)rx >= view_w || ry < 0 || (unsigned int)ry >= view_h)
            return false;

        vxy.first = (unsigned int)rx;
        vxy.second = (unsigned int)ry;
        return true;
    }


public:
    skin& _overlay_set(const pt& xy) {

        if (xy.first >= w || xy.second >= h) {
            static skin tmp;
            return tmp;
        }

        auto& tmp = overlay[xy.second*w+xy.first];
        tmp.first = current_draw_n;
        return tmp.second;
    }

private:

    const std::pair<uint32_t, skin>& _overlay_get(const pt& xy) {
        return overlay[xy.second*w+xy.first];
    }

    template <typename FUNC1, typename FUNC2>
    void _draw_circle(unsigned int x, unsigned int y, unsigned int r, 
                      color_t fore, color_t back,  FUNC1 f_chk, FUNC2 f_do) {

        unsigned int x0 = (x < r ? 0 : x - r);
        unsigned int y0 = (y < r ? 0 : y - r);

        unsigned int x1 = std::min(x + r + 1, w);
        unsigned int y1 = std::min(y + r + 1, h);

        std::vector<pt> pts;

        for (unsigned int _x = x0; _x < x1; ++_x) {
            for (unsigned int _y = y0; _y < y1; ++_y) {

                pt _xy(_x, _y);

                double d = _dist(pt(x,y), _xy);

                if (d <= r && f_chk(_x, _y)) {
                    pts.push_back(_xy);
                }
            }
        }

        for (const auto& xy : pts) {

            _overlay_set(xy) = skin(ui_symbol.circle.text, fore, back);
        }

        for (const auto& xy : pts) {
            f_do(xy.first, xy.second);
        }
    }


    void _draw_messages(std::vector<skin>& hud,
                        unsigned int x, unsigned int y, unsigned int view_w, 
                        unsigned int box_w, unsigned int box_h,
                        unsigned int t) {

        std::vector< std::pair<color_t, std::string> > lines;

        unsigned int i = 0;
        auto li = messages.begin();

        while (i < box_h && li != messages.end()) {

            color_t fore = gray_color;

            if (li->timestamp == 0 || li->timestamp >= t) {

                if (li->important) {
                    fore = yellow_color;
                } else {
                    fore = white_color;
                }

                li->timestamp = t;
            }

            size_t si = 0;
            while (si < li->text.size()) {
                lines.push_back(std::make_pair(fore, li->text.substr(si, box_w)));
                si += box_w;
            }

            ++i;
            ++li;
        }

        lines.resize(box_h);

        for (size_t j = 0; j < lines.size(); ++j) {

            auto hudi = hud.begin() + ((y+j) * view_w) + x;

            color_t fore = lines[j].first;
            const std::string& text = lines[j].second;

            for (size_t si = 0; si < box_w; ++si) {

                if (si < text.size()) {
                    hudi->text = text[si];
                    hudi->fore = fore;

                } else {
                    hudi->fore = black_color;
                }

                ++hudi;
            }
        }
    } 


    void _draw_pipline(std::vector<skin>& hud,
                       unsigned int x, unsigned int y, unsigned int view_w,
                       const hud_line& line) {

        auto hudi = hud.begin() + (y * view_w) + x;

        std::string l;
        
        if (line.label.size() < 7)
            l += std::string(7 - line.label.size(), ' ');

        l += line.label;
        l += ": ";

        for (unsigned char c : l) {
            *hudi = line.lskin;
            hudi->set_text(c);
            ++hudi;
        }

        skin tmp(".", color_t::dim_black, color_t::dim_black);

        if (line.numtype == hud_line::UNSIGNED) {

            for (int i = 0; i < 6; ++i) {

                if (i < line.npips) {
                    *hudi = line.pskin;
                } else {
                    *hudi = tmp;
                }

                ++hudi;
            }

        } else {

            for (int i = -3; i < 0; ++i) {

                if (i >= line.npips) {
                    *hudi = line.nskin;
                } else {
                    *hudi = tmp;
                }

                ++hudi;
            }

            for (int i = 0; i < 3; ++i) {

                if (i <= line.npips) {
                    *hudi = line.pskin;
                } else {
                    *hudi = skin();
                }

                ++hudi;
            }
        }
    }

    void _draw_textlabels(std::vector<skin>& ret_glyphs, int voff_x, int voff_y, 
                          unsigned int view_w, unsigned int view_h, bool fullwidth) {

        unsigned int scale = (fullwidth ? 2 : 1);

        auto i = textlabels.begin();
        while (i != textlabels.end()) {

            if (i->first != current_draw_n) {
                i = textlabels.erase(i);
                continue;
            }

            for (textlabel_t& tl : i->second) {

                unsigned int xx = tl.x;
                unsigned int yy = tl.y;

                pt xy;
                bool is_ok = _translate_g2v(voff_x, voff_y, view_w / scale, view_h, pt(xx, yy), xy);

                xy.first *= scale;

                if (!is_ok) 
                    continue;

                // Render text in half-width, but keep the label itself even-sized.

                if (fullwidth && tl.label.size() & 1) {
                    tl.label += " ";
                }
                
                for (unsigned int x = 0; x < tl.label.size(); ++x) {

                    if (xy.first + x >= view_w)
                        break;

                    maudit::glyph& ret = ret_glyphs[xy.second * view_w + xy.first + x];
                    ret = skin(std::string(1, tl.label[x]), tl.fg, tl.bg);
                }
            }

            ++i;
        }
    }


public:

    Grid() : w(0), h(0), 
             current_draw_n(0),
             ui_symbol_index(0)
        {}

    ~Grid() {}

    void init(unsigned int _w, unsigned int _h) {


        if (w != _w || h != _h) {

            w = _w;
            h = _h;

            grid.clear();
            grid.resize(w*h);

            overlay.resize(w*h);
        }
    }

    void set_ui_symbol(size_t i = 0) {

        if (ui_symbol_themes.empty())
            return;

        ui_symbol_index += i;
        ui_symbol_index = ui_symbol_index % ui_symbol_themes.size();
        ui_symbol = ui_symbol_themes[ui_symbol_index];
    }

    void clear() {
        grid.clear();
        grid.resize(w*h);
    }

    bool is_valid(unsigned int x, unsigned int y) {
        if (x < w && y < h) return true;
        return false;
    }

    const gridpoint& _get(unsigned int x, unsigned int y) const {
	return grid[y*w+x];
    }

    gridpoint& _get(unsigned int x, unsigned int y) {
	return grid[y*w+x];
    }

    gridpoint& _get(const pt& xy) {
	return grid[xy.second*w+xy.first];
    }

    void set_back(unsigned int x, unsigned int y, unsigned int z, const color_t& color) {
	_get(x,y).skins[z].back = color;
    }

    void set_is_lit(unsigned int x, unsigned int y, unsigned int z, bool is_lit) {
	uint8_t& il = _get(x,y).is_lit;

        if (is_lit) {
            il |= (1<<z);
	} else {
	    il &= ~(1<<z);
	}
    }

    void set_is_lightsource(unsigned int x, unsigned int y, unsigned int z, bool is_lightsource) {
	uint8_t& il = _get(x,y).is_lightsource;

        if (is_lightsource) {
            il |= (1<<z);
	} else {
	    il &= ~(1<<z);
	}
    }

    void set_is_viewblock(unsigned int x, unsigned int y, unsigned int z, bool t) {
	gridpoint& g = _get(x,y);

        if (t) {
            g.is_viewblock |= (1<<z);
        } else {
            g.is_viewblock &= ~(1<<z);
        }
    }

    void set_is_walkblock(unsigned int x, unsigned int y, unsigned int z, bool t) {
	gridpoint& g = _get(x,y);

        if (t) {
            g.is_walkblock |= (1<<z);
        } else {
            g.is_walkblock &= ~(1<<z);
        }
    }

    bool is_walkblock(unsigned int x, unsigned int y) {
	gridpoint& g = _get(x,y);
        return g.is_walkblock;
    }

    bool is_viewblock(unsigned int x, unsigned int y) {
	gridpoint& g = _get(x,y);
        return g.is_viewblock;
    }

    void set_skin(unsigned int x, unsigned int y, unsigned int z, const skin& s) {

        gridpoint& g = _get(x,y);
	std::vector<skin>& skins = g.skins; 
        skin& s_ = skins[z];

        s_ = s;
    }

    void unset_skin(unsigned int x, unsigned int y, unsigned int z) {

        gridpoint& g = _get(x,y);
	std::vector<skin>& skins = g.skins;

        skins[z] = skin();
    }

    void validate(unsigned int x, unsigned int y) {

        _get(x, y).valid = true;
    }

    void invalidate(unsigned int x, unsigned int y) {

        _get(x, y).valid = false;
    }

    bool is_in_fov(unsigned int x, unsigned int y) {
        const gridpoint& gp = _get(x,y);
        return (gp.in_fov || gp.is_lit != 0);
    }

    
    template <typename SCREEN, typename PARAMS, typename FUNC>
    void draw(SCREEN& screen,
              unsigned int t,
              const PARAMS& params,
              bool fullwidth,
              FUNC make_valid) {

        int voff_x;
        int voff_y;

        unsigned int px = params.px;
        unsigned int py = params.py;
        unsigned int cx = params.centerx;
        unsigned int cy = params.centery;

        bool ok = screen.refresh(
            [&](std::vector<maudit::glyph>& ret_glyphs, size_t view_w, size_t view_h) {

                // Do some initialization.

                unsigned int sc_view_w = (fullwidth ? view_w / 2 : view_w);

                voff_x = cx - (sc_view_w / 2) + params.voff_off_x;
                voff_y = cy - (view_h / 2) + params.voff_off_y;

                //

                for (size_t vy = 0; vy < view_h; ++vy) {
                    for (size_t vx = 0; vx < sc_view_w; ++vx) {

                        pt xy;
                        bool is_ok = _translate_v2g(voff_x, voff_y, pt(vx, vy), xy);

                        if (!is_ok) {
                            continue;
                        }

                        gridpoint& gp = _get(xy);

                        if (gp.valid) {
                            continue;
                        }

                        make_valid(xy.first, xy.second);
                    }
                }

                fov::fov_shadowcasting(w, h, grid, px, py, params.lightradius);

                // HUD

                bool do_hud = params.do_hud;

                if (view_w <= 30 || view_h <= std::max(hud_pips.size(), (size_t)3)) {
                    do_hud = false;
                }

                if (do_hud) {
                    bool ontop = (cy > h / 2);
                    bool atleft = (ontop || cx > view_w / 2);

                    unsigned int hl = 0;
                    unsigned int hpx = (atleft ? 0 : view_w - 15);

                    if (fullwidth && hpx & 1)
                        --hpx;

                    for (const auto& hudline : hud_pips) {
                        _draw_pipline(ret_glyphs, hpx, hl, view_w, hudline);
                        ++hl;
                    }

                    unsigned int mx = (atleft ? 16 : 2);

                    if (ontop) {
                        _draw_messages(ret_glyphs, mx, 0, 
                                       view_w,
                                       view_w - 17, params.num_messages,
                                       t);
                    } else {
                        _draw_messages(ret_glyphs, 2, view_h - params.num_messages, 
                                       view_w,
                                       view_w - 17, params.num_messages,
                                       t);
                    }
                }

                // LABELS

                _draw_textlabels(ret_glyphs, voff_x, voff_y, view_w, view_h, fullwidth);

                auto one_space = (fullwidth ? skin::get_sym("  ", 2) : skin::get_sym(" ", 1));

                for (size_t _vy = 0; _vy < view_h; ++_vy) {

                    bool did_widechar = false;

                    for (size_t _vx_ = 0; _vx_ < view_w; ++_vx_) {

                        maudit::glyph& ret = ret_glyphs[_vy*view_w+_vx_];

                        // This cell is already taken by a double-width character.
                        if (did_widechar) {
                            ret = skin("", no_color, no_color);
                            did_widechar = false;
                            continue;
                        }

                        if (ret.fore != no_color)
                            continue;

                        if (fullwidth) {

                            if (_vx_ & 1) {
                                // Right half of a two-cell tile where the left part is already filled in.
                                ret = skin(" ", black_color, black_color);
                                continue;

                            } else if (_vx_ == view_w - 1) {
                                // If the screen has an odd-sized width, ignore the extra half-tile
                                ret = skin(" ", black_color, black_color);
                                continue;
                            }
                        }

                        // Everything below this line is a full tile.
                        did_widechar = fullwidth;

                        // OVERLAY

                        size_t _vx = (fullwidth ? _vx_ / 2 : _vx_);

                        pt xy;
                        bool is_ok = _translate_v2g(voff_x, voff_y, pt(_vx, _vy), xy);

                        if (!is_ok) {
                            ret = skin(one_space, black_color, black_color);
                            continue;
                        }

                        const auto& overlay_char = _overlay_get(xy);

                        if (overlay_char.first == current_draw_n &&
                            overlay_char.second.fore != no_color) {

                            ret = overlay_char.second;
                            continue;
                        }

                        // GRID POINT

                        gridpoint& gp = _get(xy);

                        unsigned int x = xy.first;
                        unsigned int y = xy.second;

                        auto in_fov = gp.in_fov; 

                        const std::vector<skin>& skins = gp.skins;

                        color_t back = black_color;

                        const skin* skin_c = nullptr;
                        uint8_t found_s = 0;
                        uint8_t found_b = 0;

                        for (int skin_i = skincount - 1; skin_i >= 0; --skin_i) {

                            const skin& sk = skins[skin_i];

                            if (!found_s && sk.fore != no_color) {
                                found_s |= (1 << skin_i);
                                skin_c = &sk;
                            }

                            if (!found_b && sk.back != black_color) {
                                found_b |= (1 << skin_i);
                                back = sk.back;
                            }

                            if (found_s && found_b) break;
                        }


                        if (skin_c == nullptr) {
                            ret = skin(one_space, black_color, black_color);
                            continue;
                        }

                        const skin& sk = *skin_c;

                        color_t fore = sk.fore;
                        auto text = sk.text;
                        bool underline = sk.underline;

                        if (gp.is_lit == 0) {

                            if (!in_fov) {
                                back = black_color;
                                fore = black_color;
                                text = one_space;
                                underline = false;
                                
                            } else {

                                double d = _dist(xy, pt(px, py));

                                if (d < params.rangemin || d > params.rangemax) {
                                    fore = color_t::bright_black;
                                    back = black_color;

                                } else {

                                    fore = color_fade(fore, in_fov, found_s, params.do_fade_colors);
                                }
                            }
                        }

                        if (x == params.hlx && y == params.hly) {
                            back = blue_color;
                        }

                        ret = skin(text, fore, back, underline);
                    }
                }
	    });

        if (!ok)
            throw std::runtime_error("broken pipe");

        hud_pips.clear();
        current_draw_n++;
    }


    void push_hud_line(unsigned int npips, const std::string& label,
                       const skin& lskin, const skin& pskin) {

        if (npips == 0)
            ++npips;

        hud_pips.emplace_back(hud_line::UNSIGNED, npips, label, lskin, pskin, pskin);
    }


    void push_hud_line(int npips, const std::string& label,
                       const skin& lskin, const skin& pskin, const skin& nskin) {

        hud_pips.emplace_back(hud_line::SIGNED, npips, label, lskin, pskin, nskin);
    }


    //////


    template <typename SCREEN>
    void wait_for_anykey(SCREEN& screen) {

        keypress tmp;

        if (!screen.wait_key(tmp)) {

            throw std::runtime_error("end of input");
        }
    }

    template <typename SCREEN>
    keypress wait_for_key(SCREEN& screen) {

        keypress ret;
        
        if (!screen.wait_key(ret)) {

            throw std::runtime_error("end of input");
        }

        return ret;
    }

    /////

    template <typename SCREEN>
    keypress draw_window(SCREEN& screen, const std::string& msg, unsigned int ix, unsigned int iy) {

        const skin& wspace = ui_symbol.wspace;

        std::vector< std::vector<skin> > glyphs;

        glyphs.push_back(std::vector<skin>());
        color_t fore = gray_color;

        unsigned int nc = 0;
        unsigned int nl = 0;

        unsigned int max_nc = 0;

        for (unsigned char c : msg) {

            if (c == '\n') {

                if (nl >= iy) {
                    glyphs.push_back(std::vector<skin>());
                }

                fore = gray_color;
                nl++;
                max_nc = std::max(nc, max_nc);
                nc = 0;
                continue;
            }

            if (c == 3) {
                fore = yellow_color;
            } else if (c == 2) {
                fore = white_color;
            } else if (c == 1) {
                fore = gray_color;
            } else {

                if (nc >= ix && nl >= iy) {
                    glyphs.back().push_back(skin(std::string(1, c), fore, wspace.back));
                }

                nc++;
            }
        }

        std::string help_message = "[ Use arrow keys to scroll view, tab to change color scheme ]"_m;

        bool ok = screen.refresh(
            [&](std::vector<maudit::glyph>& ret_glyphs, size_t view_w, size_t view_h) {

                unsigned int hm_start = view_w;
                unsigned int hm_end = view_w - 2;

                if (view_w > help_message.size() + 2) {
                    hm_start = view_w - help_message.size() - 2;
                }

                for (unsigned int y = 0; y < view_h; ++y) {
                    for (unsigned int x = 0; x < view_w; ++x) {

                        skin& ret = ret_glyphs[y*view_w+x];

                        if (y <= 1 || y >= view_h-2 ||
                            x <= 1 || x >= view_w-2) {

                            if (y <= 0 && x <= 0) {
                                ret = ui_symbol.box_rd;

                            } else if (y <= 0 && x >= view_w-1) {
                                ret = ui_symbol.box_ld;

                            } else if (y >= view_h-1 && x <= 0) {
                                ret = ui_symbol.box_ru;

                            } else if (y >= view_h-1 && x >= view_w-1) {
                                ret = ui_symbol.box_lu;

                            } else if (y <= 0 || y >= view_h-1) {

                                if (y >= view_h-1 && x <= 10 && nl+4-iy > view_h) {
                                    ret = ui_symbol.arrow_d;

                                } else if (y <= 0 && x <= 10 && iy > 0) {

                                    ret = ui_symbol.arrow_u;

                                } else {

                                    ret = ui_symbol.box_h;

                                    if (y == 0 && x >= hm_start && x < hm_end) {
                                        ret.text = help_message[x - hm_start];
                                    }

                                }

                            } else if (x <= 0 || x >= view_w-1) {

                                if (x >= view_w-1 && y <= 5 && max_nc+4-ix > view_w) {
                                    ret = ui_symbol.arrow_r;

                                } else if (x <= 0 && y <= 5 && ix > 0) {
                                    ret = ui_symbol.arrow_l;

                                } else {
                                    ret = ui_symbol.box_v;
                                }

                            } else {
                                ret = wspace;
                            }

                            continue;
                        }

                        if (y-2 >= glyphs.size()) {
                            ret = wspace;
                            continue;
                        }

                        const auto& line = glyphs[y-2];

                        if (x-2 >= line.size()) {
                            ret = wspace;
                            continue;
                        }

                        ret = line[x-2];
                    }
                }
            });

        if (!ok)
            throw std::runtime_error("broken pipe");

        return wait_for_key(screen);
    }

    template <typename SCREEN>
    keypress draw_window(SCREEN& screen, const std::string& msg, bool allow_tab = true) {

        unsigned int ix = 0;
        unsigned int iy = 0;
        
        while (1) {
            keypress k = draw_window(screen, msg, ix, iy);

            switch (k.key) {
            case maudit::keycode::up:
                if (iy > 0) --iy;
                break;
            case maudit::keycode::left:
                if (ix > 0) --ix;
                break;
            case maudit::keycode::right:
                ++ix;
                break;
            case maudit::keycode::down:
                ++iy;
                break;

            default:

                if (allow_tab && k.letter == '\t') {
                    set_ui_symbol(1);
                    break;
                }

                return k;
            }
        }
    }


    template <typename FUNC>
    void draw_circle(unsigned int x, unsigned int y, unsigned int r, 
                     color_t fore, color_t back, 
                     FUNC func) {

        _draw_circle(x, y, r, 
                     fore, back,
                     [](unsigned int, unsigned int) { return true; },
                     func);
    }

    template <typename FUNC>
    void draw_floodfill(neighbors::Neighbors& neigh,
                        unsigned int x, unsigned int y, 
                        color_t fore, color_t back,
                        FUNC func) {

        std::set<pt> procd;
        std::set<pt> toproc;

        toproc.insert(pt(x,y));

        while (1) {

            pt xy = *(toproc.begin());
            toproc.erase(toproc.begin());

            for (const auto& xyi_ : neigh(xy)) {

                auto xyi = neigh.mk(xyi_, xy);

                if (procd.count(xyi) != 0) 
                    continue;

                procd.insert(xyi);

                if (func(xyi.first, xyi.second)) {
                    toproc.insert(xyi);
                }
            }

            if (toproc.empty()) {
                break;
            }
        }

        for (const auto& xy : procd) {

            _overlay_set(xy) = skin(ui_symbol.fill.text, fore, back);
        }
    }

    template <typename FUNC>
    void draw_line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, 
                   color_t fore, color_t back, FUNC func) {
        
        bresenham::Line line(x0, y0, x1, y1);

        std::vector<pt> pts;

        unsigned int x = x0;
        unsigned int y = y0;
        while (1) {
            if (!func(x, y))
                break;

            pts.push_back(pt(x, y));

            bool ret = line.step((int&)x, (int&)y);
            if (!ret)
                break;
        }

        for (const auto& xy : pts) {

            _overlay_set(xy) = skin(ui_symbol.line.text, fore, back);
        }
    }

    void draw_text(unsigned int x0, unsigned int y0, const std::string& text,
                   color_t fore, color_t back) {

        textlabels[current_draw_n].emplace_back(text, x0, y0, fore, back);
    }

    template <typename FUNC>
    void replace_message(FUNC f) {
        if (!messages.empty()) {
            message& m = messages.front();
            f(m.text);
        }
    }

    void do_message(const std::string& msg, bool important = false, bool temporary = false) {
        if (!messages.empty()) {
            message& m = messages.front();

            if (m.temporary) {
                m.text = msg;
                m.important = important;
                m.temporary = temporary;
                m.timestamp = 0;
                return;

            } else if (m.text == msg) {
                m.timestamp = 0;
                return;
            }
        }

        messages.emplace_front(msg, important, 0, temporary);
    }

    std::string all_messages() {

        std::string m;

        for (const auto& li : messages) {

            if (li.important) {
                m += (char)3;
            } else if (m.empty()) {
                m += (char)2;
            } else {
                m += (char)1;
            }

            m += li.text;
            m += '\n';
        }

        return m;
    }

};

}


namespace serialize {

template <>
struct reader<grender::Grid> {
    inline void read(serialize::Source& s, grender::Grid& g) {
        unsigned int _w;
        unsigned int _h;

        serialize::read(s, _w);
        serialize::read(s, _h);

        g.init(_w, _h);

	for (size_t i = 0; i < g.grid.size(); ++i) {

            grender::Grid::gridpoint& p = g.grid[i];

            serialize::read(s, p.skins);
            serialize::read(s, p.is_lit);
            serialize::read(s, p.is_lightsource);
            serialize::read(s, p.in_fov);
            serialize::read(s, p.is_viewblock);
            serialize::read(s, p.is_walkblock);
        }

        size_t messages_size;
        serialize::read(s, messages_size);

        g.messages.clear();

        for (size_t i = 0; i < messages_size; ++i) {
            g.messages.emplace_back();
            grender::Grid::message& m = g.messages.back();
            serialize::read(s, m.text);
            serialize::read(s, m.important);
            serialize::read(s, m.temporary);
            serialize::read(s, m.timestamp);
        }
    }
};

template <>
struct writer<grender::Grid> {
    inline void write(serialize::Sink& s, const grender::Grid& g) {
	serialize::write(s, g.w);
	serialize::write(s, g.h);

        for (const auto& t : g.grid) {

            serialize::write(s, t.skins);
            serialize::write(s, t.is_lit);
            serialize::write(s, t.is_lightsource);
            serialize::write(s, t.in_fov);
            serialize::write(s, t.is_viewblock);
            serialize::write(s, t.is_walkblock);
        }

        serialize::write(s, g.messages.size());
        for (const auto& m : g.messages) {
            serialize::write(s, m.text);
            serialize::write(s, m.important);
            serialize::write(s, m.temporary);
            serialize::write(s, m.timestamp);
        }
    }
};

}

#endif
