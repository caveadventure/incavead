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
    }

    // generation

    template <typename FUNC>
    void generate(GameState& state, FUNC progressbar);

    // rendering

    void make_screen(mainloop::screen_params_t& sp, GameState& state);

    void set_skin(GameState& state, unsigned int x, unsigned int y);

    void drawing_context(mainloop::drawing_context_t& ctx, const GameState& state);

    void draw_hud(GameState& state);

    // processing

    void init(GameState& state, unsigned int address, unsigned int seed);

    void dispose(GameState& state);

    void endgame(GameState& state, const std::string& name, unsigned int address, unsigned int seed);

    void process_world(GameState& state, 
                       bool& done, bool& dead, bool& regen, bool& need_input, bool& do_draw);

    // actions

    /* (None as members of this class.) */

    // ui

    void handle_input(GameState& state, GameOptions& options,
                      bool& done, bool& dead, bool& regen, 
                      maudit::keypress k);

    template <typename FUNC>
    void goodbye_message(GameState& state, FUNC println);

};


enum class screens_t : unsigned int {
    messages = 0,
    inventory,
    inv_item,
    floor_item,
    spells,
    help,
    tombstone,
    howto,
    achievements,
    monsters,
    victory_status,
    stats,
    overmap,
    bank_main,
    bank_withdrawal,
    bank_deposit,
    bank_buy,
    bank_buy_confirm,
    options
};

#include "game_generation.h"
#include "game_rendering.h"
#include "game_processing.h"
#include "bank_screens.h"
#include "actions.h"
#include "inv_screens.h"
#include "look_screens.h"
#include "apply.h"
#include "inv_screens2.h"
#include "highscore.h"
#include "game_ui.h"



#endif
