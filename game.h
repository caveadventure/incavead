#ifndef __GAME_H
#define __GAME_H

struct Game {

    Player p;

    // HACK TODO WARNING
    // Magic number
    static const unsigned int GRID_W = 256;
    static const unsigned int GRID_H = 256;

    unsigned int game_seed;

    bool debug_enabled;

    size_t n_skin;

    Game(bool debug, size_t _n_skin) : debug_enabled(debug), n_skin(_n_skin) {}

    template <typename SINK>
    void save(SINK& s) {
        serialize::write(s, game_seed);
        serialize::write(s, p);
    }

    template <typename SOURCE>
    void load(SOURCE& s) {
        serialize::read(s, game_seed);
        serialize::read(s, p);

        p.current_wx = p.worldx;
        p.current_wy = p.worldy;
        p.current_wz = p.worldz;
    }

    // generation

    template <typename FUNC>
    void generate(GameState& state, FUNC progressbar);

    // rendering

    void make_screen(mainloop::screen_params_t& sp, GameState& state);

    void set_skin(GameState& state, unsigned int x, unsigned int y);

    void drawing_context(mainloop::drawing_context_t& ctx);

    void draw_hud(GameState& state, size_t ticks);

    // processing

    void init(unsigned int address, unsigned int seed);

    void dispose(GameState& state);

    void endgame(GameState& state, const std::string& name, unsigned int address, unsigned int seed);

    void process_world(GameState& state, size_t& ticks, 
                       bool& done, bool& dead, bool& regen, bool& need_input, bool& do_draw);

    // actions

    /* (None as members of this class.) */

    // ui

    void handle_input(GameState& state,
                      size_t& ticks, bool& done, bool& dead, bool& regen, 
                      maudit::keypress k);

    template <typename FUNC>
    void goodbye_message(GameState& state, FUNC println);

};

#include "game_generation.h"
#include "game_rendering.h"
#include "game_processing.h"
#include "actions.h"
#include "inv_screens.h"
#include "look_screens.h"
#include "apply.h"
#include "inv_screens2.h"
#include "highscore.h"
#include "game_ui.h"



#endif
