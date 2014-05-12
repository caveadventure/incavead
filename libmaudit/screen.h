#ifndef __MAUDIT_SCREEN_H
#define __MAUDIT_SCREEN_H

#include <ctype.h>
#include <stdlib.h>

#include <functional>

#include "lz77.h"

namespace maudit {

#define CSI "\033["

template <typename IO>
struct screen {
    
    IO& io;

    bool compressed;

    unsigned int w;
    unsigned int h;
    bool is_cr;

    unsigned int address;

    std::function<void (screen<IO>*, std::vector<glyph>&)> callback;


    screen(IO& _io) : io(_io), compressed(false), w(0), h(0), is_cr(false), address(io.peer_ip()) {

        // Turn off echo in the client.
        io.write("\xFF\xFB\x01"); 

        // Turn off line buffering in the client.
        io.write("\xFF\xFB\x03");

        // Turn on compression.
        io.write("\xFF\xFB\x57");
    }

    void reset_color() {
        io.write(CSI "0m");
    }

    void clear() {
        io.write(CSI "H" CSI "J");
    }

    template <typename FUNC>
    bool refresh(const FUNC& f) {

        if (w == 0 || h == 0) {
            keypress tmp;

            // Request terminal size.

            //io.write(CSI "18t");
            io.write("\xFF\xFD\x1F");

            if (!wait_key(tmp)) {
                throw std::runtime_error("Could not detect terminal size.");
            }

            //w = tmp.w;
            //h = tmp.h;
        }

        std::vector<glyph> screen;
        screen.resize(w*h);

        f(screen, w, h);

        bool ok = send_screen(screen);

        if (!ok)
            return false;

        if (callback) {
            callback(this, screen);
        }

        return true;
    }

    bool send_screen(const std::vector<glyph>& glyphs) {

        std::string data;

        data += CSI "H";       // Move cursor to home position.
        //data += CSI "2J";      // Erase screen.

        color fore_prev = color::none;
        color back_prev = color::none;

        bool first = true;

        for (size_t y = 0; y < h; ++y) {
            for (size_t x = 0; x < w; ++x) {

                const glyph& g = glyphs[y*w+x];

                if (g.text.empty())
                    continue;

                bool do_fore = false;
                bool do_back = false;

                if (first) {

                    data += CSI;
                    data += "0m";
                    do_fore = true;
                    do_back = true;
                    first = false;

                } else {

                    if (fore_prev != g.fore) {
                        do_fore = true;

                        if (fore_prev >= color::bright_black && g.fore < color::bright_black) {
                            data += CSI;
                            data += "0m";
                            do_fore = true;
                            do_back = true;
                        }
                    }
                
                    if (back_prev != g.back) {
                        do_back = true;
                    }
                }
                
                if (do_fore || do_back) {

                    data += CSI;

                    if (do_fore) {

                        switch (g.fore) {
                        case color::none:        data += "39"; break;
                        case color::dim_black:   data += "30"; break;
                        case color::dim_red:     data += "31"; break;
                        case color::dim_green:   data += "32"; break;
                        case color::dim_yellow:  data += "33"; break;
                        case color::dim_blue:    data += "34"; break;
                        case color::dim_magenta: data += "35"; break;
                        case color::dim_cyan:    data += "36"; break;
                        case color::dim_white:   data += "37"; break;
                        case color::bright_black:   data += "1;30"; break;
                        case color::bright_red:     data += "1;31"; break;
                        case color::bright_green:   data += "1;32"; break;
                        case color::bright_yellow:  data += "1;33"; break;
                        case color::bright_blue:    data += "1;34"; break;
                        case color::bright_magenta: data += "1;35"; break;
                        case color::bright_cyan:    data += "1;36"; break;
                        case color::bright_white:   data += "1;37"; break;
                        }
                    }

                    if (do_back) {

                        if (do_fore) data += ";";

                        switch (g.back) {
                        case color::none:        data += "49"; break;
                        case color::dim_black:   data += "40"; break;
                        case color::dim_red:     data += "41"; break;
                        case color::dim_green:   data += "42"; break;
                        case color::dim_yellow:  data += "43"; break;
                        case color::dim_blue:    data += "44"; break;
                        case color::dim_magenta: data += "45"; break;
                        case color::dim_cyan:    data += "46"; break;
                        case color::dim_white:   data += "47"; break;
                        case color::bright_black:   data += "40"; break;
                        case color::bright_red:     data += "41"; break;
                        case color::bright_green:   data += "42"; break;
                        case color::bright_yellow:  data += "43"; break;
                        case color::bright_blue:    data += "44"; break;
                        case color::bright_magenta: data += "45"; break;
                        case color::bright_cyan:    data += "46"; break;
                        case color::bright_white:   data += "47"; break;
                        }
                    }
                    
                    data += 'm';
                }

                data += g.text;

                fore_prev = g.fore;
                back_prev = g.back;
            }
        }

        if (compressed) {
            std::cout << "Before size: " << data.size() << std::endl;
            data = lz77::compress(data);
            std::cout << "After size: " << data.size() << std::endl;
        }

        return io.write(data);
    }


    bool wait_key(keypress& out) {

        out.w = w;
        out.h = h;

        bool prev_is_cr = is_cr;

      again:

        is_cr = false;

        unsigned char c;

        bool ok = io.read(c);
        if (!ok) return false;

        // Handle telnet escape codes.

        if (c == 0xFF) {

            ok = io.read(c);
            if (!ok) return false;

            switch (c) {

            case 0xFF:
                // Escape 0xFF
                out.letter = 0xFF;
                return true;

            case 0xFB:
            case 0xFC:
            case 0xFE:
                // Will/won't/don't silliness, ignore it.
                ok = io.read(c);
                if (!ok) return false;
                goto again;

            case 0xFD:
                // 'Do' silliness.
                ok = io.read(c);
                if (!ok) return false;

                if (c == 0x57) {
                    // Enable compression.
                    compressed = true;
                    io.write("\xFF\xFA\x57\xFF\xF0");
                }
                goto again;

            case 0xFA:
                ok = io.read(c);
                if (!ok) return false;

                if (c != 0x1F)
                    goto again;

                // 0xFA 0x1F: response to screen size request.

                ok = io.read(c);
                if (!ok) return false;

                out.w = ((size_t)c << 8);

                ok = io.read(c);
                if (!ok) return false;

                out.w |= (size_t)c;
    
                ok = io.read(c);
                if (!ok) return false;

                out.h = ((size_t)c << 8);

                ok = io.read(c);
                if (!ok) return false;

                out.h |= (size_t)c;
                
                out.key = keycode::resize;

                w = out.w;
                h = out.h;
                return true;

                goto again;

            default:
                goto again;
            }
        }

        // Handle ANSI/vt100 terminal escapes.

        if (c == '\033') {

            ok = io.read(c);
            if (!ok) return false;

            if (c == '[') {
                // Try for some special characters.

                ok = io.read(c);
                if (!ok) return false;

                switch (c) {
                case 'D':  out.key = keycode::left;  break;
                case 'A':  out.key = keycode::up;    break;
                case 'C':  out.key = keycode::right; break;
                case 'B':  out.key = keycode::down;  break;
                    
                case '1':  out.key = keycode::kp_7;  break;
                case '5':  out.key = keycode::kp_9;  break;
                case '4':  out.key = keycode::kp_1;  break;
                case '6':  out.key = keycode::kp_3;  break;

                case '3':  out.key = keycode::del;   break;
                }

                if (out.key == keycode::kp_7 || 
                    out.key == keycode::kp_9 || 
                    out.key == keycode::kp_1 || 
                    out.key == keycode::kp_3 ||
                    out.key == keycode::del) {

                    ok = io.read(c);
                    if (!ok) return false;
                }

            } else {
                out.key = keycode::esc;
            }

            return true;
        }

        // Handle CR/LF insane madness.

        /*
          \r   -> \n
          \r\n -> \n
          \r\0 -> \n
        */

        if (prev_is_cr && (c == '\n' || c == '\0')) {
            goto again;
        }

        if (c == '\r') {

            is_cr = true;
            out.letter = '\n';

            return true;
        } 

        out.letter = c;
        return true;
    }

};


}

#endif
