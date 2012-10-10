#ifndef __RENDER_H
#define __RENDER_H

#include <math.h>
#include <stdlib.h>

#include <list>
#include <stdexcept>

#include "celauto.h"

#include "maudit.h"

extern "C" {
#include "talgo.h"
}

#include <iostream>
#include <sys/time.h>


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
    static const color_t yellow_color = color_t::bright_yellow;
    static const color_t gray_color   = color_t::dim_white;
    static const color_t white_color  = color_t::bright_white;
    static const color_t no_color     = color_t::none;

    typedef maudit::glyph skin;

    typedef maudit::keypress keypress;

    struct gridpoint {
	std::vector<skin> skins;
	unsigned int is_lit;
	bool in_fov;
        unsigned int is_viewblock;
        unsigned int is_walkblock;

        bool valid;

	gridpoint() : is_lit(0), in_fov(false), 
                      is_viewblock(0), is_walkblock(0),
                      valid(false)
            {
                skins.resize(skincount);
            }
    };


    struct message {
        std::string text;
        bool important;
        unsigned int timestamp;

        message(const std::string& t = "", bool i = false, unsigned int ts = 0) :
            text(t), important(i), timestamp(ts) {}
    };

    struct hud_line {
        std::string label;
        color_t labelcolor;
        enum numtype_t { SIGNED, UNSIGNED };
        numtype_t numtype;
        int npips;
        char pipstyle[2];
        color_t pipcolor[2];

        hud_line(const std::string& l, color_t lc,
                 numtype_t nt, int np,
                 char s[2],
                 color_t c[2]) : 
            label(l), labelcolor(lc), numtype(nt), npips(np)
            {
                pipstyle[0] = s[0];
                pipstyle[1] = s[1];
                pipcolor[0] = c[0];
                pipcolor[1] = c[1];
            }
    };

    unsigned int w;
    unsigned int h;

    std::vector<gridpoint> grid;

    std::vector<keypress> keylog;

    std::list<message> messages;

    // transient, not saved in dump.
    size_t current_draw_n;
    std::vector< std::pair<size_t, skin> > overlay;

    // transient, not saved in dump.
    TCOD_map_t tcodmap;
    TCOD_path_t tcodpath;

    // transient, not saved in dump.
    std::vector<hud_line> hud_pips;

    // transient, not saved in dump.
    bool keylog_do_replay;
    size_t keylog_index;

private:

    color_t color_fade(color_t c, double v) {

        if (v <= 0.3) {
            return c;

        } else if (v <= 0.7) {
            switch (c) {
            case color_t::bright_black:   return color_t::dim_black;
            case color_t::bright_red:     return color_t::dim_red;
            case color_t::bright_green:   return color_t::dim_green;
            case color_t::bright_yellow:  return color_t::dim_yellow;
            case color_t::bright_blue:    return color_t::dim_blue;
            case color_t::bright_magenta: return color_t::dim_magenta;
            case color_t::bright_cyan:    return color_t::dim_cyan;
            case color_t::bright_white:   return color_t::dim_white;
            default: return c;
            }

        } else if (v <= 0.90) {
            return color_t::bright_black;

        } else {
            return color_t::dim_black;
        }
    }

    double _dist(const pt& a, const pt& b) {

        unsigned int dx = abs(a.first - b.first);
        unsigned int dy = abs(a.second - b.second);
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


    skin& _overlay_set(const pt& xy) {
        auto& tmp = overlay[xy.second*w+xy.first];
        tmp.first = current_draw_n;
        return tmp.second;
    }

    const std::pair<size_t, skin>& _overlay_get(const pt& xy) {
        return overlay[xy.second*w+xy.first];
    }

    template <typename FUNC1, typename FUNC2>
    void _draw_circle(unsigned int x, unsigned int y, unsigned int r, 
                      bool do_draw, color_t fore, color_t back, 
                      FUNC1 f_chk, FUNC2 f_do) {

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

        if (do_draw) {
        
            for (const auto& xy : pts) {

                _overlay_set(xy) = skin("*", fore, back);
            }
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
        
        if (line.label.size() < 6)
            l += std::string(6 - line.label.size(), ' ');

        l += line.label;
        l += ": ";

        for (unsigned char c : l) {
            hudi->text = c;
            hudi->fore = line.labelcolor;
            ++hudi;
        }

        if (line.numtype == hud_line::UNSIGNED) {

            for (int i = 0; i < 6; ++i) {

                if (i < line.npips) {
                    hudi->text = line.pipstyle[0];
                    hudi->fore = line.pipcolor[0];
                } else {
                    hudi->fore = black_color;
                }

                ++hudi;
            }

        } else {

            for (int i = -3; i < 0; ++i) {

                if (i >= line.npips) {
                    hudi->text = line.pipstyle[0];
                    hudi->fore = line.pipcolor[0];
                } else {
                    hudi->fore = black_color;
                }

                ++hudi;
            }

            for (int i = 0; i < 3; ++i) {

                if (i < line.npips) {
                    hudi->text = line.pipstyle[1];
                    hudi->fore = line.pipcolor[1];
                } else {
                    hudi->fore = black_color;
                }

                ++hudi;
            }
        }
    }


public:

    Grid() : w(0), h(0), 
             current_draw_n(0),
             tcodmap(TCOD_map_new(0, 0)), 
             tcodpath(TCOD_path_new_using_map(tcodmap, 1.41)),
             keylog_do_replay(false), keylog_index(0)
        {}

    ~Grid() {
        TCOD_map_delete(tcodmap);
        TCOD_path_delete(tcodpath);
    }

    void init(unsigned int _w, unsigned int _h) {


        if (w != _w || h != _h) {

            w = _w;
            h = _h;

            grid.clear();
            grid.resize(w*h);

            overlay.resize(w*h);

            TCOD_map_delete(tcodmap);
            tcodmap = TCOD_map_new(w, h);
            TCOD_map_clear(tcodmap, false, false);

            TCOD_path_delete(tcodpath);
            tcodpath = TCOD_path_new_using_map(tcodmap, 1.41);
        }
    }

    void clear() {
        grid.clear();
        grid.resize(w*h);
        TCOD_map_clear(tcodmap, false, false);
    }

    bool is_valid(unsigned int x, unsigned int y) {
        if (x < w && y < h) return true;
        return false;
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
	unsigned int& il = _get(x,y).is_lit;

        if (is_lit) {
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

        TCOD_map_set_properties(tcodmap, x, y, (g.is_viewblock == 0), (g.is_walkblock == 0));
    }

    void set_is_walkblock(unsigned int x, unsigned int y, unsigned int z, bool t) {
	gridpoint& g = _get(x,y);

        if (t) {
            g.is_walkblock |= (1<<z);
        } else {
            g.is_walkblock &= ~(1<<z);
        }

        TCOD_map_set_properties(tcodmap, x, y, (g.is_viewblock == 0), (g.is_walkblock == 0));
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

        g.valid = true;
    }

    void unset_skin(unsigned int x, unsigned int y, unsigned int z) {

        gridpoint& g = _get(x,y);
	std::vector<skin>& skins = g.skins;

        skins[z] = skin();

        g.valid = true;
    }


    bool is_in_fov(unsigned int x, unsigned int y) {
        const gridpoint& gp = _get(x,y);
        return (gp.in_fov || gp.is_lit != 0);
    }

    
    template <typename SCREEN, typename PARAMS, typename FUNC>
    void draw(SCREEN& screen,
              celauto::CaMap& camap,
              unsigned int t,
              const PARAMS& params,
              unsigned int& ret_view_w, 
              unsigned int& ret_view_h,
              FUNC make_valid) {

        int voff_x;
        int voff_y;

        unsigned int px = params.px;
        unsigned int py = params.py;

        bool ok = screen.refresh(ret_view_w, ret_view_h,
            [&](std::vector<maudit::glyph>& ret_glyphs, size_t view_w, size_t view_h) {

                // Do some initialization.

                ret_view_w = view_w;
                ret_view_h = view_h;

                voff_x = px - (view_w / 2) + params.voff_off_x;
                voff_y = py - (view_h / 2) + params.voff_off_y;

                //

                for (size_t vy = 0; vy < view_h; ++vy) {
                    for (size_t vx = 0; vx < view_w; ++vx) {

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
                   
                TCOD_map_compute_fov(tcodmap, px, py, params.lightradius, true, FOV_SHADOW);

                bool do_hud = params.do_hud;

                if (view_w <= 30 || view_h <= std::max(hud_pips.size(), (size_t)3)) {
                    do_hud = false;
                }

                if (do_hud) {
                    unsigned int hl = 0;
                    unsigned int hpx = (px > view_w / 2 ? 0 : view_w - 14);

                    for (const auto& hudline : hud_pips) {
                        _draw_pipline(ret_glyphs, hpx, hl, view_w, hudline);
                        ++hl;
                    }

                    if (py > h / 2) {
                        _draw_messages(ret_glyphs, 15, 0, 
                                       view_w,
                                       view_w - 30, 3,
                                       t);
                    } else {
                        _draw_messages(ret_glyphs, 15, view_h - 3, 
                                       view_w,
                                       view_w - 30, 3,
                                       t);
                    }
                }
            

                for (size_t _vy = 0; _vy < view_h; ++_vy) {
                    for (size_t _vx = 0; _vx < view_w; ++_vx) {

                        maudit::glyph& ret = ret_glyphs[_vy*view_w+_vx];

                        if (ret.fore != no_color)
                            continue;

                        // OVERLAY

                        pt xy;
                        bool is_ok = _translate_v2g(voff_x, voff_y, pt(_vx, _vy), xy);

                        if (!is_ok) {
                            ret = skin(" ", black_color, black_color);
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

                        bool in_fov = TCOD_map_is_in_fov(tcodmap, x, y);

                        double d = _dist(xy, pt(px, py));

                        const std::vector<skin>& skins = gp.skins;

                        gp.in_fov = in_fov;

                        color_t back = black_color;
                        
                        auto skin_i = skins.rbegin();
                        auto skin_c = skin_i;
                        bool found_s = false;
                        bool found_b = false;

                        while (skin_c != skins.rend()) {

                            if (!found_s && skin_c->fore != no_color) {
                                found_s = true;
                                skin_i = skin_c;
                            }

                            if (!found_b && skin_c->back != black_color) {
                                found_b = true;
                                back = skin_c->back;
                            }

                            if (found_s && found_b) break;

                            ++skin_c;
                        }


                        if (!found_s) {
                            ret = skin(" ", black_color, black_color);
                            continue;
                        }

                        const skin& sk = *skin_i;

                        color_t fore = sk.fore;
                        std::string text = sk.text;

                        size_t caid;
                        unsigned int caage;
                        camap.get_state(xy, caid, caage);

                        if (caid) {
                            unsigned int maxage = camap.rules[caid]->age;
                            double intrp = (double)caage / (maxage*2.0);
                            back = color_fade(back, intrp);
                        }

                        if (gp.is_lit == 0) {

                            if (!in_fov) {
                                back = black_color;
                                fore = black_color;
                                text = " ";
                                
                            } else {

                                double d1 = d / params.lightradius;

                                if (d < params.rangemin || d > params.rangemax) {
                                    fore = gray_color;
                                    back = black_color;

                                } else {

                                    fore = color_fade(fore, std::min(d1, 1.0));
                                }
                            }
                        }

                        if (x == params.hlx && y == params.hly) {
                            back = white_color;
                        }

                        ret = skin(text, fore, back);
                    }
                }
	    });

        if (!ok)
            throw std::runtime_error("broken pipe");

        hud_pips.clear();
        current_draw_n++;
    }


    void push_hud_line(const std::string& label, color_t labelcolor,
                       unsigned int npips, char style_, color_t color_) {


        char style[2] = { style_, style_ };
        color_t color[2] = { color_, color_ };

        hud_pips.emplace_back(label, labelcolor, hud_line::UNSIGNED, npips, style, color);
    }


    void push_hud_line(const std::string& label, color_t labelcolor,
                       int npips, char nstyle, char pstyle,
                       color_t ncolor, color_t pcolor) {

        char style[2] = { nstyle, pstyle };
        color_t color[2] = { ncolor, pcolor };

        hud_pips.emplace_back(label, labelcolor, hud_line::SIGNED, npips, style, color);
    }


    //////


    template <typename SCREEN>
    void wait_for_anykey(SCREEN& screen, unsigned int& view_w, unsigned int& view_h) {

        keypress tmp;
        
        if (!screen.wait_key(tmp)) {

            throw std::runtime_error("end of input");
        }

        view_w = tmp.w;
        view_h = tmp.h;
    }

    template <typename SCREEN>
    keypress wait_for_key(SCREEN& screen, unsigned int& view_w, unsigned int& view_h) {

        keypress ret;
        
        if (!screen.wait_key(ret)) {

            throw std::runtime_error("end of input");
        }

        view_w = ret.w;
        view_h = ret.h;

        return ret;
    }

    void push_replay_keypress(const keypress& kp) {

        if (!keylog_do_replay) {
            keylog_do_replay = true;
            keylog_index = keylog.size();
        }

        keylog.push_back(kp);
    }

    void stop_keypress_replay() {
        if (keylog_index < keylog.size())
            throw std::runtime_error("Malformed replay file: not all keypresses were consumed.");
        keylog_do_replay = false;
    }

    /////

    template <typename SCREEN>
    keypress draw_window(SCREEN& screen, unsigned int view_w, unsigned int view_h,
                         const std::vector<std::string>& msg) {

        std::vector< std::vector<skin> > glyphs;

        for (const std::string& line : msg) {

            glyphs.push_back(std::vector<skin>());

            color_t fore = gray_color;

            for (unsigned char c : line) {

                if (c == 3) {
                    fore = yellow_color;
                } else if (c == 2) {
                    fore = white_color;
                } else if (c == 1) {
                    fore = gray_color;
                } else {
                    glyphs.back().push_back(skin(c, fore, black_color));
                }
            }
        }

        bool ok = screen.refresh(view_w, view_h, 
            [&](std::vector<maudit::glyph>& ret_glyphs, size_t view_w, size_t view_h) {

                for (unsigned int y = 0; y < view_h; ++y) {
                    for (unsigned int x = 0; x < view_w; ++x) {

                        skin& ret = ret_glyphs[y*view_w+x];

                        if (y <= 1 || y >= view_h-2 ||
                            x <= 1 || x >= view_w-2) {

                            ret = skin();
                            continue;
                        }

                        if (y-2 >= glyphs.size()) {
                            ret = skin(" ", black_color, black_color);
                            continue;
                        }

                        const auto& line = glyphs[y-2];

                        if (x-2 >= line.size()) {
                            ret = skin(" ", black_color, black_color);
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

    template <typename FUNC>
    void draw_circle(unsigned int x, unsigned int y, unsigned int r, 
                     bool do_draw, color_t fore, color_t back, 
                     FUNC func) {

        _draw_circle(x, y, r, 
                     do_draw, fore, back,
                     [](unsigned int, unsigned int) { return true; },
                     func);
    }

    template <typename FUNC>
    void draw_fov_circle(unsigned int x, unsigned int y, unsigned int r, 
                         bool do_draw, color_t fore, color_t back,
                         FUNC func) {

	TCOD_map_compute_fov(tcodmap, x, y, r, false, FOV_SHADOW);

        _draw_circle(x, y, r, do_draw, fore, back, 
                     [this](unsigned int x, unsigned int y) { return TCOD_map_is_in_fov(tcodmap, x, y); },
                     func);
    }


    template <typename FUNC>
    void draw_floodfill(neighbors::Neighbors& neigh,
                        unsigned int x, unsigned int y, 
                        bool do_draw, color_t fore, color_t back,
                        FUNC func) {

        std::set<pt> procd;
        std::set<pt> toproc;

        toproc.insert(pt(x,y));

        while (1) {

            pt xy = *(toproc.begin());
            toproc.erase(toproc.begin());

            for (const auto& xyi : neigh(xy)) {

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

        if (do_draw) {

            for (const auto& xy : procd) {

                _overlay_set(xy) = skin("*", fore, back);
            }
        }
    }

    template <typename FUNC>
    void draw_line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, 
                   bool do_draw, color_t fore, color_t back,
                   FUNC func) {
        
        TCOD_line_init(x0, y0, x1, y1);

        std::vector<pt> pts;

        unsigned int x = x0;
        unsigned int y = y0;
        while (1) {
            if (!func(x, y))
                break;

            pts.push_back(pt(x, y));

            bool ret = TCOD_line_step((int*)&x, (int*)&y);
            if (ret)
                break;
        }

        if (do_draw) {
            for (const auto& xy : pts) {

                _overlay_set(xy) = skin("*", fore, back);
            }
        }
    }



    void do_message(const std::string& msg, bool important = false) {
        if (!messages.empty()) {
            message& m = messages.front();

            if (m.text == msg) {
                m.timestamp = 0;
                return;
            }
        }

        messages.emplace_front(msg, important, 0);
    }

    template <typename SCREEN>
    void draw_messages_window(SCREEN& screen, unsigned int view_w, unsigned int view_h) {

        unsigned int i = 0;
        std::list<message>::const_iterator li = messages.begin();
        std::vector<std::string> lines;

        while (i < 23 && li != messages.end()) {
            lines.emplace_back();
            std::string& m = lines.back();

            if (li->important) {
                m += (char)3;
            } else if (li == messages.begin()) {
                m += (char)2;
            } else {
                m += (char)1;
            }

            m += li->text;
            ++i;
            ++li;
        }

        draw_window(screen, view_w, view_h, lines);
    }

    bool path_walk(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1,
                   unsigned int n, unsigned int cutoff, 
                   unsigned int& xo, unsigned int& yo) {

        bool tmp = TCOD_path_compute(tcodpath, x0, y0, x1, y1, cutoff);

        if (!tmp) return false;

        for (unsigned int i = 0; i < n; ++i) {
            if (!TCOD_path_walk(tcodpath, (int*)&xo, (int*)&yo, true, cutoff))
                return false;
        }
        return true;
    }



    //***  ***//

    inline void write(serialize::Sink& s) {
	serialize::write(s, w);
	serialize::write(s, h);

        for (const auto& t : grid) {

            serialize::write(s, t.skins);
            serialize::write(s, t.is_lit);
            serialize::write(s, t.in_fov);
            serialize::write(s, t.is_viewblock);
            serialize::write(s, t.is_walkblock);
        }

	serialize::write(s, keylog);

        serialize::write(s, messages.size());
        for (const auto& m : messages) {
            serialize::write(s, m.text);
            serialize::write(s, m.important);
            serialize::write(s, m.timestamp);
        }
    }

    inline void read(serialize::Source& s) {
        unsigned int _w;
        unsigned int _h;

        serialize::read(s, _w);
        serialize::read(s, _h);

        init(_w, _h);

	for (size_t i = 0; i < grid.size(); ++i) {

	    gridpoint& p = grid[i];

            serialize::read(s, p.skins);
            serialize::read(s, p.is_lit);
            serialize::read(s, p.in_fov);
            serialize::read(s, p.is_viewblock);
            serialize::read(s, p.is_walkblock);

            TCOD_map_set_properties(tcodmap, i % w, i / w, 
                                    (p.is_viewblock == 0), (p.is_walkblock == 0));
        }

	serialize::read(s, keylog);

        size_t messages_size;
        serialize::read(s, messages_size);

        messages.clear();

        for (size_t i = 0; i < messages_size; ++i) {
            messages.emplace_back();
            message& m = messages.back();
            serialize::read(s, m.text);
            serialize::read(s, m.important);
            serialize::read(s, m.timestamp);
        }
    }

};


}


#endif
