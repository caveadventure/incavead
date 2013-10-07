#ifndef __GAMESTATE_H
#define __GAMESTATE_H

#include "random.h"
#include "random_serialize.h"
#include "neighbors.h"
#include "celauto.h"
#include "grid.h"

#include "render_maudit.h"

#include "moon.h"

#include "counters.h"
#include "counters_serialize.h"
#include "ffeatures.h"
#include "items.h"
#include "monsters.h"

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


namespace serialize {

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
struct writer<GameState::window_t> {
    void write(Sink& s, const GameState::window_t& w) {
        serialize::write(s, w.message);
        serialize::write(s, w.type);
    }
};

template <>
struct writer<GameState> {
    void write(Sink& s, const GameState& state) {

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


#endif
