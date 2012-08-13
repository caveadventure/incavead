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

struct GameState {

    rnd::Generator rng;
    neighbors::Neighbors neigh;
    celauto::CaMap camap;
    grid::Map grid;
    grender::Grid render;
    moon::Moon moon;
};


struct drawing_context_t {
    unsigned int view_w;
    unsigned int view_h;
    int voff_off_x;
    int voff_off_y;
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
        voff_off_x(0), voff_off_y(0), px(0), py(0), lightradius(1000), 
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

    GameState state;


    Main(SCREEN& s) : screen(s), view_w(0), view_h(0), ticks(1) {}



    bool load(const std::string& filename) {
        try {
            serialize::Source s(filename);

            state.rng.read(s);
            state.neigh.read(s);
            state.grid.read(s);
            state.render.read(s);
            state.camap.read(s);
            state.moon.read(s);

            serialize::read(s, ticks);

            game.load(s);

        } catch (std::exception& e) {
            return false;
        }
        return true;
    }

    void save(const std::string& filename) {

        serialize::Sink s(filename);

        state.rng.write(s);
        state.neigh.write(s);
        state.grid.write(s);
        state.render.write(s);
        state.camap.write(s);
        state.moon.write(s);

        serialize::write(s, ticks);

        game.save(s);
    }

    void clobber_savefile(const std::string& filename) {
        serialize::Sink s(filename);
    }


    bool start(const std::string& savefile,
               long seed,
               const screen_params_t& sp) {

        if (load(savefile)) {
            return false;
        }

        screen.io.write("\r\nInitializing game...\r\n");

        state.rng.init(seed);
        state.neigh.init(sp.w, sp.h);
        state.grid.init(sp.w, sp.h);
        state.render.init(sp.w2, sp.h2);
        state.render.keylog.clear();
        state.camap.init();
        state.moon.init();

        ticks = 1;

        screen.io.write("Generating world...\r\n");

        game.init();
        game.generate(state);

        return true;
    }

    void draw() {

        drawing_context_t ctx;
        ctx.view_w = view_w;
        ctx.view_h = view_h;
        game.drawing_context(ctx);

        if (ctx.do_hud) {
            game.draw_hud(state);
        }
        
        state.render.draw(screen, 
                          state.camap,
                          ticks, 
                          ctx,
                          view_w, view_h,
                          std::bind(&GAME::set_skin, &game, std::ref(state),
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

            grender::Grid::keypress k = state.render.wait_for_key(screen);
            game.handle_input(state, ticks, done, dead, k);
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

            state.render.wait_for_anykey(screen);
            return true;
        }

        return false;
    }

    bool mainloop(const std::string& savefile,
                  long seed) {

        screen_params_t sp;

        game.make_screen(sp);

        start(savefile, seed, sp);

        size_t oldticks = 0;

        draw();

        bool done = false;
        bool dead = false;

        while (1) {

            bool need_input = false;

            process(oldticks, done, dead, need_input);

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
