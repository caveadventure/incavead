#ifndef __GAMESTATE_H
#define __GAMESTATE_H

#include "random.h"
#include "random_serialize.h"
#include "neighbors.h"
#include "celauto.h"
#include "grid.h"

#include "worldkey.h"

#include "astar.h"
#include "render_maudit.h"

#include "moon.h"

#include "counters.h"
#include "counters_serialize.h"
#include "ffeatures.h"
#include "items.h"
#include "monsters.h"

struct GameState {

    size_t ticks;

    rnd::Generator rng;
    neighbors::Neighbors neigh;
    celauto::CaMap camap;
    grid::Map grid;
    grender::Grid render;
    astar::Path path;
    moon::Moon moon;

    counters::Counts designs_counts;
    counters::Counts species_counts;

    counters::Counts bonus_designs_a_counts;
    counters::Counts bonus_designs_b_counts;

    monsters::Monsters monsters;
    items::Items items;
    features::Features features;

    struct trigger_t {

        struct summon_out_of_view_t {
            tag_t monster;
            unsigned int count;

            summon_out_of_view_t() : count(0) {}
        };

        summon_out_of_view_t summon_out_of_view;

        struct summon_genus_t {
            tag_t genus;
            unsigned int level;
            unsigned int count;
            unsigned int x;
            unsigned int y;
            
            summon_genus_t() : level(0), count(0), x(0), y(0) {}
        };

        summon_genus_t summon_genus;

        struct summon_t {
            tag_t species;
            unsigned int count;
            tag_t ally;
            unsigned int x;
            unsigned int y;

            summon_t() : count(0), x(0), y(0) {}
        };

        summon_t summon;

        struct message_t {
            std::string message;
            bool important;

            message_t() : important(false) {}
        };

        message_t message;
    };

    std::multimap<size_t, trigger_t> triggers;

    struct window_t {
        std::string message;
        unsigned int type;
        bool allow_tab;
        
        window_t() : type(0), allow_tab(true) {}
        
        window_t(const std::string& s, unsigned int t, bool tab = true) : message(s), type(t), allow_tab(tab) {}
    };

    std::vector<window_t> window_stack;

    std::unordered_map<worldkey::key_t, size_t> dungeon_visits_count;

    template <typename T>
    void push_window(const std::string& m, T t, bool allow_tab = true) {
        window_stack.push_back(window_t{m, (unsigned int)t, allow_tab});
    }

    // HACK
    bool fullwidth;

    GameState() : ticks(1), fullwidth(false) {}
};

struct GameOptions {

    bool center_view;
    bool no_fade_colors;
    size_t menu_theme;

    GameOptions() : center_view(false), no_fade_colors(false), menu_theme(0) {}
};


struct summons_t {
    unsigned int x;
    unsigned int y;
    
    enum class type_t : unsigned int {
        SPECIFIC,
        LEVEL,
        GENUS
    };

    type_t type;

    tag_t summontag;
    unsigned int level;
    unsigned int count;
    tag_t summonertag;
    tag_t ally;
    std::string msg;

    summons_t() : x(0), y(0), type(type_t::SPECIFIC), level(0), count(0) {}

    summons_t(unsigned int _x, unsigned int _y, type_t _t, tag_t _st, unsigned int _l, unsigned int _c, 
              tag_t _sut, tag_t _al, const std::string& _m) : 
        x(_x), y(_y), type(_t), summontag(_st), level(_l), count(_c), summonertag(_sut), ally(_al), msg(_m) {}
};

struct itemplace_t {
    unsigned int x;
    unsigned int y;

    enum class type_t : unsigned int {
        SPECIFIC,
        LEVEL,
        LEVEL_ANY
    };

    type_t type;

    tag_t tag;
    unsigned int level;

    itemplace_t() : x(0), y(0), type(type_t::SPECIFIC), level(0) {}

    itemplace_t(unsigned int _x, unsigned int _y, type_t _t, tag_t _dt, unsigned int _l) :
        x(_x), y(_y), type(_t), tag(_dt), level(_l) {}
};


/*** ***/

namespace serialize {

template <>
struct reader<GameState::trigger_t> {
    void read(Source& s, GameState::trigger_t& t) {

        serialize::read(s, t.summon_out_of_view.monster);
        serialize::read(s, t.summon_out_of_view.count);
        serialize::read(s, t.summon_genus.genus);
        serialize::read(s, t.summon_genus.level);
        serialize::read(s, t.summon_genus.count);
        serialize::read(s, t.summon_genus.x);
        serialize::read(s, t.summon_genus.y);
        serialize::read(s, t.summon.species);
        serialize::read(s, t.summon.count);
        serialize::read(s, t.message.message);
        serialize::read(s, t.message.important);
    }
};

template <>
struct reader<GameState::window_t> {
    void read(Source& s, GameState::window_t& w) {

        serialize::read(s, w.message);
        serialize::read(s, w.type);
    }
};

template <>
struct reader<GameState> {
    void read(Source& s, GameState& state) {

        serialize::read(s, state.ticks);
        serialize::read(s, state.rng);
        serialize::read(s, state.neigh);
        serialize::read(s, state.camap);
        serialize::read(s, state.grid);
        serialize::read(s, state.render);
        serialize::read(s, state.moon);
        serialize::read(s, state.designs_counts);
        serialize::read(s, state.species_counts);
        serialize::read(s, state.bonus_designs_a_counts);
        serialize::read(s, state.bonus_designs_b_counts);
        serialize::read(s, state.monsters);
        serialize::read(s, state.items);
        serialize::read(s, state.features);
        serialize::read(s, state.dungeon_visits_count);

        serialize::read(s, state.triggers);
        serialize::read(s, state.window_stack);

        state.path.init(state.grid.w, state.grid.h);
    }
};

template <>
struct writer<GameState::trigger_t> {
    void write(Sink& s, const GameState::trigger_t& t) {

        serialize::write(s, t.summon_out_of_view.monster);
        serialize::write(s, t.summon_out_of_view.count);
        serialize::write(s, t.summon_genus.genus);
        serialize::write(s, t.summon_genus.level);
        serialize::write(s, t.summon_genus.count);
        serialize::write(s, t.summon_genus.x);
        serialize::write(s, t.summon_genus.y);
        serialize::write(s, t.summon.species);
        serialize::write(s, t.summon.count);
        serialize::write(s, t.message.message);
        serialize::write(s, t.message.important);
    }
};

template <>
struct writer<GameState::window_t> {
    void write(Sink& s, const GameState::window_t& w) {
        serialize::write(s, w.message);
        serialize::write(s, w.type);
    }
};

template <>
struct writer<GameState> {
    void write(Sink& s, const GameState& state) {

        serialize::write(s, state.ticks);
        serialize::write(s, state.rng);
        serialize::write(s, state.neigh);
        serialize::write(s, state.camap);
        serialize::write(s, state.grid);
        serialize::write(s, state.render);
        serialize::write(s, state.moon);
        serialize::write(s, state.designs_counts);
        serialize::write(s, state.species_counts);
        serialize::write(s, state.bonus_designs_a_counts);
        serialize::write(s, state.bonus_designs_b_counts);
        serialize::write(s, state.monsters);
        serialize::write(s, state.items);
        serialize::write(s, state.features);
        serialize::write(s, state.dungeon_visits_count);

        serialize::write(s, state.triggers);
        serialize::write(s, state.window_stack);
    }
};


template <>
struct reader<GameOptions> {
    void read(Source& s, GameOptions& t) {
        serialize::read(s, t.center_view);
        serialize::read(s, t.no_fade_colors);
        serialize::read(s, t.menu_theme);
    }
};

template <>
struct writer<GameOptions> {
    void write(Sink& s, const GameOptions& t) {
        serialize::write(s, t.center_view);
        serialize::write(s, t.no_fade_colors);
        serialize::write(s, t.menu_theme);
    }
};


template <>
struct reader<summons_t> {
    void read(Source& s, summons_t& t) {
        serialize::read(s, t.x);
        serialize::read(s, t.y);
        unsigned int tmp;
        serialize::read(s, tmp);
        t.type = (summons_t::type_t)tmp;
        serialize::read(s, t.summontag);
        serialize::read(s, t.level);
        serialize::read(s, t.count);
        serialize::read(s, t.summonertag);
        serialize::read(s, t.ally);
        serialize::read(s, t.msg);
    }
};

template <>
struct writer<summons_t> {
    void write(Sink& s, const summons_t& t) {
        serialize::write(s, t.x);
        serialize::write(s, t.y);
        serialize::write(s, (unsigned int)t.type);
        serialize::write(s, t.summontag);
        serialize::write(s, t.level);
        serialize::write(s, t.count);
        serialize::write(s, t.summonertag);
        serialize::write(s, t.ally);
        serialize::write(s, t.msg);
    }
};

template <>
struct reader<itemplace_t> {
    void read(Source& s, itemplace_t& t) {
        serialize::read(s, t.x);
        serialize::read(s, t.y);
        unsigned int tmp;
        serialize::read(s, tmp);
        t.type = (itemplace_t::type_t)tmp;
        serialize::read(s, t.tag);
        serialize::read(s, t.level);
    }
};

template <>
struct writer<itemplace_t> {
    void write(Sink& s, const itemplace_t& t) {
        serialize::write(s, t.x);
        serialize::write(s, t.y);
        serialize::write(s, (unsigned int)t.type);
        serialize::write(s, t.tag);
        serialize::write(s, t.level);
    }
};

}


#endif
