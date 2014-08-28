#ifndef __MAINLOOP_H
#define __MAINLOOP_H

#include <functional>

#include "logging.h"
#include "spectator.h"

#include "serialize.h"




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
    unsigned int num_messages;
    bool do_hud;

    bool do_center_view;
    bool do_fade_colors;

    drawing_context_t() :
        view_w(0), view_h(0),
        voff_off_x(0), voff_off_y(0), px(0), py(0), lightradius(1000), 
        hlx(std::numeric_limits<unsigned int>::max()), 
        hly(hlx),
        rangemin(0),
        rangemax(hlx),
        num_messages(3),
        do_hud(true),
        do_center_view(false),
        do_fade_colors(true)
        {}
};

struct screen_params_t {
    unsigned int w; 
    unsigned int h; 
    unsigned int w2; 
    unsigned int h2;

    screen_params_t() : w(0), h(0), w2(0), h2(0) {}
};


template <typename GAME, typename GAMESTATE, typename GAMEOPTIONS, typename SCREEN>
struct Main {

    GAME game;
    SCREEN& screen;

    std::vector<std::string> messages;

    GAMEOPTIONS options;
    GAMESTATE state;

    static const unsigned int SAVEFILE_VERSION = 20;


    Main(SCREEN& s, bool debug, size_t n_skin, bool fullwidth) : 
        game(debug, n_skin), 
        screen(s)
        {

            // HACK!
            state.fullwidth = fullwidth;
        }


    bool load(const std::string& filename) {
        try {

            serialize::Source s(filename);

            unsigned int ver;
            serialize::read(s, ver);

            if (ver != SAVEFILE_VERSION)
                return false;

            serialize::read(s, options);

            // HACK!!
            state.render.set_ui_symbol(options.menu_theme);

            serialize::read(s, state);

            game.load(s);

        } catch (std::exception& e) {
            return false;
        }
        return true;
    }

    void save(const std::string& filename) {

        // HACK!!
        options.menu_theme = state.render.ui_symbol_index;

        serialize::Sink s(filename);

        serialize::write(s, SAVEFILE_VERSION);
        serialize::write(s, options);
        serialize::write(s, state);

        game.save(s);
    }

    void clobber_savefile(const std::string& filename) {

        // HACK!!
        options.menu_theme = state.render.ui_symbol_index;

        serialize::Sink s(filename);

        serialize::write(s, SAVEFILE_VERSION);
        serialize::write(s, options);
    }


    bool start(const std::string& savefile, std::string& window, const screen_params_t& sp) {

        if (load(savefile)) {
            return false;
        }

        std::string code;
        unsigned int seed;

        {
            window += "\n\3Do you want to enter a replay code? (Y/N)\2";
            maudit::keypress k = state.render.draw_window(screen, window);

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
        state.path.init(sp.w, sp.h);
        state.render.init(sp.w2, sp.h2);
        state.camap.init();
        state.moon.init(seed);

        state.designs_counts = designs().counts;
        state.species_counts = species().counts;
        state.terrain_counts = terrain().counts;
        state.vaults_counts = vaults().counts;

        state.bonus_designs_a_counts = designs().bonus_a_counts;
        state.bonus_designs_b_counts = designs().bonus_b_counts;

        state.features.init();
        state.items.init();
        state.monsters.init();

        state.ticks = 1;

        game.init(state, screen.address, seed);

        screen.clear();
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

        screen.clear();
        game.generate(state, [this](const std::string& msg) { screen.io.write(msg + "\r\n"); });
    }

    void draw(bool dead) {

        if (spectator::screens<SCREEN>().get_messages(screen, messages)) {

            for (const std::string& msg : messages) {
                state.render.do_message("Chat message: " + msg, true);
            }

            messages.clear();
        }

        drawing_context_t ctx;
        ctx.view_w = screen.w;
        ctx.view_h = screen.h;
        ctx.do_center_view = options.center_view;
        ctx.do_fade_colors = !options.no_fade_colors;
        game.drawing_context(ctx, state);

        if (ctx.do_hud) {
            game.draw_hud(state);
        }

        ctx.num_messages = (dead ? 7 : 3);

        state.render.draw(screen, 
                          state.ticks, 
                          ctx,
                          state.fullwidth,
                          std::bind(&GAME::set_skin, &game, std::ref(state),
                                    std::placeholders::_1, std::placeholders::_2));
    }

    bool process(size_t& oldticks, bool& done, bool& dead, bool& regen, bool& need_input, bool& draw) {

        if (state.ticks == oldticks) {
            need_input = true;
            return false;
        }

        oldticks = state.ticks;

        game.process_world(state, done, dead, regen, need_input, draw);

        if (state.ticks != oldticks) {
            need_input = false;
        }

        return true;
    }

    void pump_event(bool need_input, bool& done, bool& dead, bool& regen) {

        if (need_input) {

            grender::Grid::keypress k = state.render.wait_for_key(screen);

            game.handle_input(state, options, done, dead, regen, k);

            while (state.window_stack.size() > 0) {

                k = state.render.draw_window(screen, 
                                             state.window_stack.back().message, 
                                             state.window_stack.back().allow_tab);

                game.handle_input(state, options, done, dead, regen, k);
            }
        }
    }

    bool check_done(bool done, bool dead, const std::string& name, const std::string& savefile) {

        if (done) {

            if (dead) {

                game.endgame(state, name, screen.address, game.game_seed);

                clobber_savefile(savefile);

            } else {
                save(savefile);
            }

            return true;
        }

        return false;
    }

    void goodbye_message(bool dead) {

        while (1) {
            grender::Grid::keypress k = state.render.wait_for_key(screen);

            if (k.letter == ' ')
                break;
        }

        screen.reset_color();

        if (dead) {

            game.goodbye_message(state, [this](const std::string& msg) { screen.io.write(msg + "\r\n"); });
 
            state.render.wait_for_key(screen);
       }
    }

    void enter_text(std::string& prompt, std::string& out, bool secret) {

        while (1) {
            maudit::keypress k = state.render.draw_window(screen, prompt);

            // HACK
            // Disable parens to prevent cheating achievements in the highscore table.

            if (k.letter >= ' ' && k.letter <= '~' && k.letter != '(' && k.letter != ')' && out.size() < 75) {
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

        game.make_screen(sp, state);

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

    void _mainloop_main(const std::string& name, const std::string& savefile, bool& dead) {

        size_t oldticks = 0;

        state.render.do_message("Press '?' twice for detailed instructions.");
        state.render.do_message("Press '?' for help on controls.");

        draw(dead);

        bool done = false;
        dead = false;
        bool regen = false;

        while (1) {

            bool need_input = false;

            do {
                bool do_draw = false;
                bool time_passed = process(oldticks, done, dead, regen, need_input, do_draw);

                if (regen) {
                    regenerate();
                    draw(dead);
                    regen = false;
                }

                if (check_done(done, dead, name, savefile)) {
                    draw(dead);
                    goodbye_message(dead);
                    return;
                }

                if (do_draw) {
                    draw(dead);
                }

                if (!time_passed) break;
            } while (1);

            draw(dead);

            pump_event(need_input, done, dead, regen);

            if (check_done(done, dead, name, savefile)) {
                draw(dead);
                goodbye_message(dead);
                return;
            }
        }
    }
    
    

    bool mainloop(bool singleplayer) {

        std::string name;
        unsigned int seed;
        bool new_game;

        std::string savefile = _mainloop_start(singleplayer, name, seed, new_game);

        bool dead;

        try {
            
            {
                logger::Sink gamelog("game.log");

                if (new_game) {
                    gamelog << nlp::message("START\t%s\t%s\t%d\n", name, rcode::encode(seed), ::time(NULL));
                } else {
                    gamelog << nlp::message("LOAD\t%s\t%s\t%d\n", name, rcode::encode(seed), ::time(NULL));
                }
            }

            if (!singleplayer)
                spectator::screens<SCREEN>().add(screen, name);

            _mainloop_main(name, savefile, dead);

            if (!singleplayer)
                spectator::screens<SCREEN>().remove(screen);

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

            if (!singleplayer)
                spectator::screens<SCREEN>().remove(screen);

            if (dead) {
                clobber_savefile(savefile);

            } else {
                save(savefile);
            }

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
