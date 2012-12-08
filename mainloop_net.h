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
    counters::Counts terrain_counts;

    monsters::Monsters monsters;
    items::Items items;
    features::Features features;

    struct window_t {
        std::string message;
        unsigned int type;
        
        window_t() : type(0) {}
        
        window_t(const std::string& s, unsigned int t) : message(s), type(t) {}
    };

    std::vector<window_t> window_stack;

    template <typename T>
    void push_window(const std::string& m, T t) {
        window_stack.push_back(window_t{m, (unsigned int)t});
    }
};

}

namespace serialize {

template <>
struct reader<mainloop::GameState::window_t> {
    void read(Source& s, mainloop::GameState::window_t& w) {

        serialize::read(s, w.message);
        serialize::read(s, w.type);
    }
};

template <>
struct reader<mainloop::GameState> {
    void read(Source& s, mainloop::GameState& state) {

        serialize::read(s, state.rng);
        serialize::read(s, state.neigh);
        serialize::read(s, state.camap);
        serialize::read(s, state.grid);
        serialize::read(s, state.render);
        serialize::read(s, state.moon);
        serialize::read(s, state.designs_counts);
        serialize::read(s, state.species_counts);
        // REMOVEME
        state.designs_counts = designs().counts;
        state.species_counts = species().counts;
        serialize::read(s, state.terrain_counts);
        serialize::read(s, state.monsters);
        serialize::read(s, state.items);
        serialize::read(s, state.features);

        serialize::read(s, state.window_stack);
    }
};

template <>
struct writer<mainloop::GameState::window_t> {
    void write(Sink& s, const mainloop::GameState::window_t& w) {
        serialize::write(s, w.message);
        serialize::write(s, w.type);
    }
};

template <>
struct writer<mainloop::GameState> {
    void write(Sink& s, const mainloop::GameState& state) {

        serialize::write(s, state.rng);
        serialize::write(s, state.neigh);
        serialize::write(s, state.camap);
        serialize::write(s, state.grid);
        serialize::write(s, state.render);
        serialize::write(s, state.moon);
        serialize::write(s, state.designs_counts);
        serialize::write(s, state.species_counts);
        serialize::write(s, state.terrain_counts);
        serialize::write(s, state.monsters);
        serialize::write(s, state.items);
        serialize::write(s, state.features);

        serialize::write(s, state.window_stack);
    }
};

}

namespace mainloop {

struct drawing_context_t {
    unsigned int view_w;
    unsigned int view_h;
    int voff_off_x;
    int voff_off_y;
    unsigned int px;
    unsigned int py;
    unsigned int centerx;
    unsigned int centery;
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
            bm _l("loading savefile");

            serialize::Source s(filename);

            serialize::read(s, state);
            serialize::read(s, ticks);
            serialize::read(s, view_w);
            serialize::read(s, view_h);

            game.load(s);

        } catch (std::exception& e) {
            return false;
        }
        return true;
    }

    void save(const std::string& filename) {
        bm _s("saving savefile");

        serialize::Sink s(filename);

        serialize::write(s, state);
        serialize::write(s, ticks);
        serialize::write(s, view_w);
        serialize::write(s, view_h);

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

        state.designs_counts = designs().counts;
        state.species_counts = species().counts;
        state.terrain_counts = terrain().counts;

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
        bm _p("draw");

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

    bool process(size_t& oldticks, bool& done, bool& dead, bool& regen, bool& need_input, bool& draw) {

        if (ticks == oldticks) {
            need_input = true;
            return false;
        }

        oldticks = ticks;

        bm _p("process");

        game.process_world(state, ticks, done, dead, regen, need_input, draw);

        if (ticks != oldticks) {
            need_input = false;
        }

        return true;
    }

    void pump_event(bool need_input, bool& done, bool& dead, bool& regen) {

        if (need_input) {

            grender::Grid::keypress k = state.render.wait_for_key(screen, view_w, view_h);
            game.handle_input(state, ticks, done, dead, regen, k);

            while (state.window_stack.size() > 0) {

                k = state.render.draw_window(screen, view_w, view_h, state.window_stack.back().message);

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

            return true;
        }

        return false;
    }

    void goodbye_message() {
        //screen.io.write("\r\nPress any key.\r\n");
        state.render.wait_for_anykey(screen, view_w, view_h);
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

            do {
                bool do_draw = false;
                bool time_passed = process(oldticks, done, dead, regen, need_input, do_draw);

                if (regen) {
                    regenerate();
                    draw();
                    regen = false;
                }

                if (check_done(done, dead, savefile)) {
                    draw();
                    goodbye_message();
                    return dead;
                }

                if (do_draw) {
                    draw();
                }

                if (!time_passed) break;
            } while (1);

            draw();

            pump_event(need_input, done, dead, regen);

            if (check_done(done, dead, savefile)) {
                draw();
                goodbye_message();
                return dead;
            }
        }
    }
    

};


}

#endif
