#ifndef __MAINLOOP_H
#define __MAINLOOP_H

#include "serialize.h"
#include "neighbors.h"
#include "celauto.h"
#include "render_maudit.h"
#include "random.h"
#include "grid.h"

#include "moon.h"


namespace mainloop {


struct drawing_context_t {
    unsigned int view_w;
    unsigned int view_h;
    int voff_x;
    int voff_y;
    unsigned int px;
    unsigned int py;
    unsigned int lightradius;
    unsigned int hlx;
    unsigned int hly;
    unsigned int rangemin;
    unsigned int rangemax;
    bool do_hud;

    drawing_context_t() :
        view_w(0), view_h(0),
        voff_x(0), voff_y(0), px(0), py(0), lightradius(1000), 
        hlx(std::numeric_limits<unsigned int>::max()), 
        hly(hlx),
        rangemin(0),
        rangemax(hlx),
        do_hud(true)
        {}
};

struct screen_params_t {
    unsigned int w; 
    unsigned int h; 
    unsigned int w2; 
    unsigned int h2;

    screen_params_t() : w(0), h(0), w2(0), h2(0) {}
};


template <typename GAME, typename SCREEN>
struct Main {

    GAME game;
    SCREEN& screen;

    unsigned int view_w;
    unsigned int view_h;
    size_t ticks;

    Main(SCREEN& s) : screen(s), view_w(0), view_h(0), ticks(1) {}



    bool load(const std::string& filename) {
        try {
            serialize::Source s(filename);

            rnd::get().read(s);
            neighbors::get().read(s);
            grid::get().read(s);
            grender::get().read(s);
            celauto::get().read(s);
            moon::get().read(s);

            serialize::read(s, ticks);

            game.load(s);

        } catch (std::exception& e) {
            return false;
        }
        return true;
    }

    void save(const std::string& filename) {

        serialize::Sink s(filename);

        rnd::get().write(s);
        neighbors::get().write(s);
        grid::get().write(s);
        grender::get().write(s);
        celauto::get().write(s);
        moon::get().write(s);

        serialize::write(s, ticks);

        game.save(s);
    }

    void clobber_savefile(const std::string& filename) {
        serialize::Sink s(filename);
    }


    bool start(const std::string& savefile,
               long seed,
               const screen_params_t& sp) {

        std::cout << "++ load savefile" << std::endl;
        if (load(savefile)) {
            return false;
        }

        std::cout << "++ init" << std::endl;
        screen.io.write("\r\nInitializing game...\r\n");

        rnd::get().init(seed);
        neighbors::get().init(sp.w, sp.h);
        grid::get().init(sp.w, sp.h);
        grender::get().init(sp.w2, sp.h2);
        grender::get().keylog.clear();
        celauto::get().init();
        moon::get().init();

        ticks = 1;

        std::cout << "++ init2" << std::endl;
        screen.io.write("Generating world...\r\n");

        game.init();
        game.generate();

        return true;
    }

    void draw() {

        drawing_context_t ctx;
        ctx.view_w = view_w;
        ctx.view_h = view_h;
        game.drawing_context(ctx);

        if (ctx.do_hud) {
            game.draw_hud();
        }
        
        grender::get().draw(screen, 
                            ticks, ctx.voff_x, ctx.voff_y,
                            ctx.px, ctx.py, ctx.hlx, ctx.hly,
                            ctx.rangemin, ctx.rangemax, ctx.lightradius, 
                            ctx.do_hud,
                            view_w, view_h,
                            std::bind(&GAME::set_skin, &game, 
                                      std::placeholders::_1, std::placeholders::_2));

    }

    void process(size_t& oldticks, bool& done, bool& dead, bool& need_input) {

        if (ticks == oldticks) {
            need_input = true;
            return;
        }

        oldticks = ticks;

        game.process_world(ticks, done, dead, need_input);
    }

    void pump_event(bool need_input, bool& done, bool& dead) {

        if (need_input) {

            grender::Grid::keypress k = grender::get().wait_for_key(screen);
            game.handle_input(ticks, done, dead, k);
        }
    }

    bool check_done(bool done, bool dead, const std::string& savefile) {

        if (done) {
                
            if (dead) {

                game.endgame();

                clobber_savefile(savefile);

            } else {
                save(savefile);
            }

            screen.io.write("\r\nPress any key.\r\n");

            grender::get().wait_for_anykey(screen);
            return true;
        }

        return false;
    }

    bool mainloop(const std::string& savefile,
                  long seed) {

        screen_params_t sp;

        std::cout << "+ make_screen" << std::endl;
        game.make_screen(sp);

        std::cout << "+ start" << std::endl;
        start(savefile, seed, sp);

        size_t oldticks = 0;

        std::cout << "+ draw" << std::endl;
        draw();

        bool done = false;
        bool dead = false;

        while (1) {

            bool need_input = false;

            std::cout << "+ process" << std::endl;
            process(oldticks, done, dead, need_input);

            std::cout << "+ draw" << std::endl;
            draw();

            if (check_done(done, dead, savefile)) 
                return dead;

            pump_event(need_input, done, dead);

            if (check_done(done, dead, savefile)) {

                draw();
                return dead;
            }
        }
    }
    

};


}

#endif
