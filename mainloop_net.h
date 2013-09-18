#ifndef __MAINLOOP_H
#define __MAINLOOP_H

#include <functional>

#include "logging.h"

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
    counters::Counts vaults_counts;

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
        serialize::read(s, state.terrain_counts);
        serialize::read(s, state.vaults_counts);
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
        serialize::write(s, state.vaults_counts);
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
    bool is_cr;
    size_t ticks;

    GameState state;


    Main(SCREEN& s, bool debug) : game(debug), screen(s), view_w(0), view_h(0), is_cr(false), ticks(1) {}



    bool load(const std::string& filename) {
        try {

            serialize::Source s(filename);

            serialize::read(s, state);
            serialize::read(s, ticks);

            unsigned int tmp_w;
            unsigned int tmp_h;
            serialize::read(s, tmp_w);
            serialize::read(s, tmp_h);

            game.load(s);

        } catch (std::exception& e) {
            return false;
        }
        return true;
    }

    void save(const std::string& filename) {

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


    bool start(const std::string& savefile, std::string& window, const screen_params_t& sp) {

        if (load(savefile)) {
            return false;
        }

        std::string code;
        unsigned int seed;

        {
            window += "\n\3Do you want to enter a replay code? (Y/N)\2";
            maudit::keypress k = state.render.draw_window(screen, view_w, view_h, is_cr, window);

            if (k.letter == 'Y' || k.letter == 'y') {
                window += "\n\3Enter a replay code (case insensitive):\2 ";
                enter_text(window, code, false);

                seed = rcode::decode<unsigned int>(code) & 0xFFFFFFFF;

            } else {
                seed = (::time(NULL) & 0xFFFFFFFF);
            }
        }

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
        state.vaults_counts = vaults().counts;

        state.features.init();
        state.items.init();
        state.monsters.init();

        ticks = 1;

        game.init(seed);
        game.generate(state, [this](const std::string& msg) { screen.io.write(msg + "\r\n"); });

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

        game.generate(state, [this](const std::string& msg) { screen.io.write(msg + "\r\n"); });
    }

    void draw() {

        drawing_context_t ctx;
        ctx.view_w = view_w;
        ctx.view_h = view_h;
        game.drawing_context(ctx);

        if (ctx.do_hud) {
            game.draw_hud(state, ticks);
        }

        state.render.draw(screen, 
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

        game.process_world(state, ticks, done, dead, regen, need_input, draw);

        if (ticks != oldticks) {
            need_input = false;
        }

        return true;
    }

    void pump_event(bool need_input, bool& done, bool& dead, bool& regen) {

        if (need_input) {

            grender::Grid::keypress k = state.render.wait_for_key(screen, view_w, view_h, is_cr);
            game.handle_input(state, ticks, done, dead, regen, k);

            while (state.window_stack.size() > 0) {

                k = state.render.draw_window(screen, view_w, view_h, is_cr, state.window_stack.back().message);

                game.handle_input(state, ticks, done, dead, regen, k);
            }
        }
    }

    bool check_done(bool done, bool dead, const std::string& name, const std::string& savefile) {

        if (done) {

            if (dead) {

                game.endgame(state, name);

                clobber_savefile(savefile);

            } else {
                save(savefile);
            }

            return true;
        }

        return false;
    }

    void goodbye_message() {

        while (1) {
            grender::Grid::keypress k = state.render.wait_for_key(screen, view_w, view_h, is_cr);

            if (k.letter == ' ')
                break;
        }
    }

    void enter_text(std::string& prompt, std::string& out, bool secret) {

        while (1) {
            maudit::keypress k = state.render.draw_window(screen, view_w, view_h, is_cr, prompt);

            if (k.letter >= ' ' && k.letter <= '~') {
                out += k.letter;
                prompt += (secret ? '*' : k.letter);
                continue;

            } else if (k.letter == '\x7F' || k.letter == '\x08' || k.key == maudit::keycode::del) {

                if (out.size() > 0) {
                    out.resize(out.size() - 1);
                    prompt.resize(prompt.size() - 1);
                }

            } else if (k.letter == '\n') {
                return;

            } else {
                continue;
            }
        }
    }



    std::string _mainloop_start(bool singleplayer, 
                                std::string& name, unsigned int& seed, bool& new_game) {

        screen_params_t sp;

        game.make_screen(sp);

        // //
        name.clear();
        std::string pass;

        std::string window = 
            "\n\1The name and passcode will identify your savefile.\n"
            "If a name/passcode combination doesn't exist, then a new savefile will be created.\n"
            "\n\3Enter your name:\2 ";

        enter_text(window, name, false);

        if (!singleplayer) {

            window += "\n\3Enter a passcode:\2 ";
            enter_text(window, pass, true);
        }        

        std::string savefile;
        {
            size_t h = std::hash<std::string>()(name) + std::hash<std::string>()(pass);
            std::ostringstream tmp;
            tmp << h << ".sav";
            savefile = tmp.str();
        }

        // //
        new_game = start(savefile, window, sp);
        seed = game.game_seed;

        return savefile;
    }

    bool _mainloop_main(const std::string& name, const std::string& savefile) {

        size_t oldticks = 0;

        state.render.do_message("Press '?' for help on controls.");

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

                if (check_done(done, dead, name, savefile)) {
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

            if (check_done(done, dead, name, savefile)) {
                draw();
                goodbye_message();
                return dead;
            }
        }
    }
    
    

    bool mainloop(bool singleplayer) {

        std::string name;
        unsigned int seed;
        bool new_game;

        std::string savefile = _mainloop_start(singleplayer, name, seed, new_game);

        try {
            
            {
                logger::Sink gamelog("game.log");

                if (new_game) {
                    gamelog << nlp::message("START\t%s\t%s\t%d\n", name, rcode::encode(seed), ::time(NULL));
                } else {
                    gamelog << nlp::message("LOAD\t%s\t%s\t%d\n", name, rcode::encode(seed), ::time(NULL));
                }
            }

            bool dead = _mainloop_main(name, savefile);

            {
                logger::Sink gamelog("game.log");

                if (dead) {
                    gamelog << nlp::message("DEAD\t%s\t%s\t%d\n", name, rcode::encode(seed), ::time(NULL));
                } else {
                    gamelog << nlp::message("QUIT\t%s\t%s\t%d\n", name, rcode::encode(seed), ::time(NULL));
                }
            }

            return dead;

        } catch (...) {

            save(savefile);

            {
                logger::Sink gamelog("game.log");
                gamelog << nlp::message("OOPS\t%s\t%s\t%d\n", name, rcode::encode(seed), ::time(NULL));
            }

            throw;
        }
    }

};


}

#endif
