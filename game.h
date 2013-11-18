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

    static void make_mapname(int worldx, int worldy, int worldz, uint64_t& gridseed, std::string& filename);

    template <typename FUNC>
    static void make_map(int worldx, int worldy, int worldz, GameState& state,
                         uint64_t gridseed, const std::string& cached_grid,
                         FUNC progressbar);

    template <typename FUNC>
    void generate(GameState& state, FUNC progressbar);

    // rendering

    void make_screen(mainloop::screen_params_t& sp, GameState& state);

    void set_skin(GameState& state, unsigned int x, unsigned int y);

    void drawing_context_center_at(mainloop::drawing_context_t& ctx, unsigned int x, unsigned int y);

    unsigned int get_lightradius();

    void drawing_context(mainloop::drawing_context_t& ctx);

    void draw_one_stat(GameState& state, const stat_t& s, const std::string& name);

    void draw_hud(GameState& state, size_t ticks);

    // processing

    void init(unsigned int code);

    void dispose(GameState& state);

    void endgame(GameState& state, const std::string& name);

    bool process_feature(GameState& state, features::Feature& f, const Terrain& t);

    void process_world(GameState& state, size_t& ticks, 
                       bool& done, bool& dead, bool& regen, bool& need_input, bool& do_draw);

    unsigned int summon_out_of_view(GameState& state, tag_t monster, unsigned int count);

    // actions

    void move_player(GameState& state);

    void rest(GameState& state, size_t& ticks);

    void move(GameState& state, int dx, int dy, size_t& ticks);

    void run_away(GameState& state, size_t& ticks);

    void use_terrain(GameState& state, size_t& ticks, bool& regen, bool& done, bool& dead);

    void seed_celauto(GameState& state, 
                      unsigned int _x, unsigned int _y, tag_t tag);

    void cast_random_spell(uint32_t rs, GameState& state);

    // ui

    std::string show_spells(const std::vector<Terrain::spell_t>& p_spells, 
                            const std::vector<Design::spell_t>& i_spells,
                            const std::vector<uint32_t>& r_spells);

    std::string show_achievements();

    std::string help_text();

    std::string tombstone_text();

    void handle_input_pick_direction(unsigned int& pstate, unsigned int px, unsigned int py, size_t& ticks,
                                     GameState& state, maudit::keypress k);

    void handle_input_messages(GameState& state, maudit::keypress k, bool do_howto);

    void handle_input_spells(GameState& state, size_t& ticks, maudit::keypress k);

    void handle_input_debug(GameState& state, size_t& ticks, bool& regen, maudit::keypress k);

    void handle_input_main(GameState& state,
                           size_t& ticks, bool& done, bool& dead, bool& regen, 
                           maudit::keypress k);

    void handle_input(GameState& state,
                      size_t& ticks, bool& done, bool& dead, bool& regen, 
                      maudit::keypress k);

};

#include "game_generation.h"
#include "game_rendering.h"
#include "game_processing.h"
#include "game_actions.h"
#include "game_ui.h"



#endif
