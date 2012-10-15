#ifndef __MAINLOOP_H
#define __MAINLOOP_H

#include "serialize.h"
#include "neighbors.h"
#include "celauto.h"
#include "render_maudit.h"
#include "random.h"
#include "grid.h"

#include "moon.h"

#include "counters.h"
#include "ffeatures.h"
#include "items.h"
#include "monsters.h"


namespace mainloop {


struct GameState {

    rnd::Generator rng;
    neighbors::Neighbors neigh;
    celauto::CaMap camap;
    grid::Map grid;
    grender::Grid render;
    moon::Moon moon;

    counters::Counts designs_counts;
    counters::Counts species_counts;

    monsters::Monsters monsters;
    items::Items items;
    features::Features features;

    std::string message_window;
    std::vector<unsigned int> window_stack;
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
            state.designs_counts.read(s);
            state.species_counts.read(s);
            state.features.read(s);
            state.items.read(s);
            state.monsters.read(s);

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
        state.designs_counts.write(s);
        state.species_counts.write(s);
        state.features.write(s);
        state.items.write(s);
        state.monsters.write(s);

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

        state.species_counts = species().counts;

        state.features.init();
        state.items.init();
        state.monsters.init();

        ticks = 1;

        screen.io.write("Generating world...\r\n");

        game.init();
        game.generate(state);

        return true;
    }

    void regenerate() {
        
        game.dispose(state);

        state.neigh.clear();
        state.grid.clear();
        state.render.clear();
        state.camap.clear();
        state.features.clear();
        state.items.clear();
        state.monsters.clear();

        game.generate(state);
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

    void process(size_t& oldticks, bool& done, bool& dead, bool& regen, bool& need_input) {

        if (ticks == oldticks) {
            need_input = true;
            return;
        }

        oldticks = ticks;

        game.process_world(state, ticks, done, dead, regen, need_input);
    }

    void pump_event(bool need_input, bool& done, bool& dead, bool& regen) {

        if (need_input) {

            grender::Grid::keypress k = state.render.wait_for_key(screen, view_w, view_h);
            game.handle_input(state, ticks, done, dead, regen, k);

            while (state.window_stack.size() > 0) {

                k = state.render.draw_window(screen, view_w, view_h, state.message_window);

                game.handle_input(state, ticks, done, dead, regen, k);
            }
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

            state.render.wait_for_anykey(screen, view_w, view_h);
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
        bool regen = false;

        while (1) {

            bool need_input = false;

            process(oldticks, done, dead, regen, need_input);

            if (regen) {
                regenerate();
                regen = false;
            }

            draw();

            if (check_done(done, dead, savefile)) 
                return dead;

            pump_event(need_input, done, dead, regen);

            if (check_done(done, dead, savefile)) {

                draw();
                return dead;
            }
        }
    }
    

};


}

#endif
