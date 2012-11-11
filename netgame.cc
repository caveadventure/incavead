
#include <thread>

#include <sstream>

#include <iostream>

#include "maudit.h"

#include "debug_benchmark.h"

////

#include "terrain.h"
#include "designs.h"
#include "species.h"

#include "terrain_bank.h"
#include "designs_bank.h"
#include "species_bank.h"

#include "levelskins.h"

#include "nlp.h"

#include "mainloop_net.h"

#include "configparser.h"

#include "utilstuff.h"
#include "inventory.h"
#include "inv_screens.h"
#include "player.h"
#include "look_screens.h"
#include "combat.h"
#include "apply.h"

enum class screens_t : unsigned int {
    messages = 0,
    inventory,
    inv_item,
    floor_item
};

#include "inv_screens2.h"


void init_statics() {

    /*
      0 kobold caves
        *kobold child
        *kobold farmer
        *kobold warrior
        *female kobold
        *kobold slave 
        *kobold slavedriver
        *kobold miner
        *kobold chieftain
        *kobold warlord
        *kobold sex slave
        kobold shaman
        *kobold fisherman
        kobold infant
        *kobold cannibal
        *renegade kobold
        dog
        *lichen
        *pond scum
        orc raider
        lizardman envoy

      1 drow & orcs
        *kobold slave
        *orcish raider
        *orcish slavemaster
        *orcish slave
        *drow flaneur
        drow noble
        drow sorceror
        drow torturer
        drow puppetmaster
        orcish sex slave
        drow warrior
        drow slaver
        drow priest of darkness
        drow priest of insanity
        drow priestess of lust
        cave spider
        spider queen
        sacred spider
        drow queen
        spiderdrow guard

      1 lizardmen 
      2 drow & orcs
      3 beholders/d&d
      4 mutants/psi
      5 dinosaur/megafauna
      6 dragon
      7 south asian/oriental
      8 demons
      9 cthulhu
      10 robots
      11 cyberpunk
      12 zombie apocalypse
      13 humanoid aliens
      14 insectoid aliens
      15 computer programs
      16 abstract
    */
    

    configparser::parse_config("species.cfg");

    configparser::parse_config("designs.cfg");

    configparser::parse_config("terrain.cfg");

    configparser::parse_config("levelskins.cfg");

    ////
}



struct Game {

    Player p;

    static const unsigned int GRID_W = 256;
    static const unsigned int GRID_H = 256;

    Game() {}

    void make_screen(mainloop::screen_params_t& sp) {

        sp.w = GRID_W;
        sp.h = GRID_H;
        sp.w2 = sp.w;
        sp.h2 = sp.h;
    }

    void init() {}

    void make_map(mainloop::GameState& state,
                  uint64_t gridseed, const std::string& cached_grid) {

        state.rng.init(gridseed);

        unsigned int nflatten = std::max(0, 4 - 2*(p.worldx + p.worldy));
        unsigned int nunflow = std::min(std::max(0, p.worldz), 8);

        //nflatten = 0;

        std::cout << "Generating... " << gridseed << " " 
                  << nflatten << " " << nunflow << std::endl;

        state.grid.generate(state.neigh, state.rng, nflatten, nunflow);

        std::cout << "Generating OK" << std::endl;

        for (unsigned int x = 0; x < GRID_W; ++x) {
            state.grid.set_walk(state.neigh, x, 0, false);
            state.grid.set_walk(state.neigh, x, GRID_H-1, false);
        }

        for (unsigned int y = 1; y < GRID_H-1; ++y) {
            state.grid.set_walk(state.neigh, 0, y, false);
            state.grid.set_walk(state.neigh, GRID_W-1, y, false);
        }

        std::cout << "Writing grid... " << cached_grid << std::endl;

        serialize::Sink sink(cached_grid);
        state.grid.write(sink);

        std::cout << "Writing OK" << std::endl;
    }

    void generate(mainloop::GameState& state) {

        // Read or generate cached map.

        std::ostringstream cached_grid;

        cached_grid << "_level_" << p.worldx << "_" << p.worldy << "_" << p.worldz << ".dat";

        uint64_t gridseed = (((uint64_t)p.worldx) ^ 
                             ((uint64_t)p.worldy << 16) ^
                             ((uint64_t)p.worldz << 32)) + 1;

        try {

            std::cout << "Reading grid... " << cached_grid.str() << std::endl;

            serialize::Source source(cached_grid.str());
            state.grid.read(source);

            std::cout << "Reading grid OK" << std::endl;

        } catch (std::exception& e) {

            make_map(state, gridseed, cached_grid.str());
        }

        // Place the player on the same starting point every time.

        state.rng.init(gridseed);

        grid::pt xy;
        if (!state.grid.one_of_floor(state.rng, xy))
            throw std::runtime_error("Failed to generate grid");

        p.px = xy.first;
        p.py = xy.second;

        state.grid.add_nogen(p.px, p.py);

        // Place some dungeon features on the same spots every time.

        state.terrain_counts = terrain().counts;

        unsigned int featscount = ::fabs(state.rng.gauss(35.0, 5.0));

        for (unsigned int i = 0; i < featscount; ++i) {

            unsigned int takecount = ::fabs(state.rng.gauss(5.0, 1.0));

            std::map<std::string, unsigned int> t = state.terrain_counts.take(state.rng, 0, takecount);

            for (const auto& j : t) {
                state.features.generate(state.rng, state.grid, j.first, j.second);
            }
        }

        // Place some random items.

        state.rng.init(::time(NULL));

        bm _y("item generation");

        unsigned int itemgroups = ::fabs(state.rng.gauss(200.0, 10.0));

        for (unsigned int i = 0; i < itemgroups; ++i) {

            unsigned int itemcount = std::max(1.0, state.rng.gauss(1.0, 0.25));
            unsigned int itemlevel = p.worldz;

            state.items.generate(state.neigh, state.rng, state.grid, state.designs_counts, 
                                 itemlevel, itemcount);
        }

        // Place some random monsters.

        bm _z("monster generation");

        unsigned int mongroups = ::fabs(state.rng.gauss(250.0, 20.0));

        for (unsigned int i = 0; i < mongroups; ++i) {

            unsigned int monlevel = p.worldz;

            state.monsters.generate(state.neigh, state.rng, state.grid, state.species_counts, 
                                    monlevel);
        }
    }

    void dispose(mainloop::GameState& state) {

        state.items.dispose(state.designs_counts);
        state.monsters.dispose(state.species_counts);

    }

    void set_skin(mainloop::GameState& state, unsigned int x, unsigned int y) {

        bool walkable = state.grid.is_walk(x, y);
        bool water = state.grid.is_water(x, y);

        state.render.set_is_viewblock(x, y, 0, !walkable);
        state.render.set_is_walkblock(x, y, 0, !walkable);

        grender::Grid::skin s;

        double z = state.grid._get(x, y);

        const Levelskin& lev = levelskins().get(p.worldz);

        if (walkable) {
            if (water) {

                if (z <= -5) {
                    s = lev.deep_water;
                } else {
                    s = lev.shallow_water;
                }

            } else {

                if (z <= -8) {
                    s = lev.floor1;
                } else if (z <= -7) {
                    s = lev.floor2;
                } else if (z <= -6) {
                    s = lev.floor3;
                } else if (z <= -5) {
                    s = lev.floor4;
                } else if (z <= -4) {
                    s = lev.floor5;
                } else if (z <= -3) {
                    s = lev.floor6;
                } else if (z <= -2) {
                    s = lev.floor7;
                } else {
                    s = lev.floor8;
                }
            }

        } else {
            if (water) {
                s = lev.water_wall;
            } else {
                s = lev.wall;
            }
        }

        state.render.set_skin(x, y, 0, s);

        // //

        features::Feature feat;

        if (state.features.get(x, y, feat)) {

            const Terrain& t = terrain().get(feat.tag);
            state.render.set_skin(x, y, 1, t.skin);
            state.render.set_is_viewblock(x, y, 1, t.viewblock);
            state.render.set_is_walkblock(x, y, 1, t.walkblock);

        } else {
            state.render.unset_skin(x, y, 1);
            state.render.set_is_viewblock(x, y, 1, false);
            state.render.set_is_walkblock(x, y, 1, false);
        }

        // //

        items::Item item;

        if (state.items.get(x, y, 0, item)) {

            const Design& d = designs().get(item.tag);
            state.render.set_skin(x, y, 2, d.skin);

        } else {
            state.render.unset_skin(x, y, 2);
        }

        // //

        monsters::Monster mon;

        if (x == p.px && y == p.py) {

            s = grender::Grid::skin("@", maudit::color::bright_white, maudit::color::bright_black);
            state.render.set_skin(x, y, 5, s);

        } else if (state.monsters.get(x, y, mon)) {

            const Species& s = species().get(mon.tag);
            state.render.set_skin(x, y, 5, s.skin);
            state.render.set_is_walkblock(x, y, 5, true);

        } else {
            state.render.unset_skin(x, y, 5);
            state.render.set_is_walkblock(x, y, 5, false);
        }
    }

    void endgame() {}

    template <typename SINK>
    void save(SINK& s) {}

    template <typename SOURCE>
    void load(SOURCE& s) {}

    void drawing_context_center_at(mainloop::drawing_context_t& ctx, unsigned int x, unsigned int y) {
        
        unsigned int grid_x = ctx.view_w / 4;
        unsigned int grid_y = ctx.view_h / 4;

        if (grid_x > 1) {
            ctx.voff_off_x = -(x % grid_x) + (grid_x / 2);
        } else {
            ctx.voff_off_x = 0;
        }

        if (grid_y > 1) {
            ctx.voff_off_y = -(y % grid_y) + (grid_y / 2);
        } else {
            ctx.voff_off_y = 0;
        }

        ctx.centerx = x;
        ctx.centery = y;
    }

    unsigned int get_lightradius() {
        return levelskins().get(p.worldz).lightradius;
    }

    void drawing_context(mainloop::drawing_context_t& ctx) {

        ctx.px = p.px;
        ctx.py = p.py;
        ctx.lightradius = get_lightradius();

        if (p.state & Player::LOOKING) {

            if (p.look.rangemin >= 0) {
                ctx.rangemin = p.look.rangemin;
            }

            if (p.look.rangemax >= 0) {
                ctx.rangemax = p.look.rangemax;
            }

            ctx.hlx = p.look.x;
            ctx.hly = p.look.y;

            drawing_context_center_at(ctx, p.look.x, p.look.y);

        } else {
            drawing_context_center_at(ctx, p.px, p.py);
        }
    }

    void draw_hud(mainloop::GameState& state) {

        double v = p.health.val;
        int vp = 0;

        if (v > 2) vp = 3;
        else if (v > 1) vp = 2;
        else if (v > 0) vp = 1;
        else if (v < -2) vp = -3;
        else if (v < -1) vp = -2;
        else if (v < 0) vp = -1;

        state.render.push_hud_line("Health", maudit::color::dim_green,
                                   vp, '-', '+',
                                   maudit::color::dim_red, maudit::color::dim_green);

        state.render.push_hud_line("Foo", maudit::color::bright_yellow, 
                                   4, '+', maudit::color::bright_green);
    }

    bool reachable(mainloop::GameState& state, unsigned int ax, unsigned int ay, unsigned int bx, unsigned int by) {
        unsigned int _x = ax;
        unsigned int _y = ay;

        state.render.draw_line(ax, ay, bx, by, false, 
                               maudit::color::dim_red, maudit::color::bright_white,
                               [&](unsigned int x, unsigned int y) {
                                   
                                   if (x == ax && y == ay)
                                       return true;

                                   if (state.render.is_walkblock(x, y) ||
                                       state.render.is_viewblock(x, y))
                                       return false;

                                   _x = x;
                                   _y = y;
                                   std::cout << "    ~ " << x << "," << y << std::endl;
                                   return true;
                               });

        std::cout << "  ~~~ " << _x << "," << _y << " " << bx << "," << by << std::endl;
        if (_x == bx && _y == by) return true;
        return false;
    }

    bool move_monster(mainloop::GameState& state, size_t ticks, const monsters::Monster& m, const Species& s,
                      monsters::pt& nxy, bool& do_die) {

        if (m.health < -3) {
            do_die = true;
            return true;
        }

        bool do_random = false;

        double dist = distance(m.xy.first, m.xy.second, p.px, p.py);

        if (s.cast_cloud.size() > 0) {

            if (dist < s.range && reachable(state, m.xy.first, m.xy.second, p.px, p.py)) {

                for (const auto& c : s.cast_cloud) {

                    std::cout << "!! " << ticks << " " << c.turns << std::endl;

                    if ((ticks % c.turns) != 0)
                        continue;
                    
                    double v = state.rng.gauss(0.0, 1.0);

                    std::cout << "!!! " << v << " " << c.chance << std::endl;
                    
                    if (v <= c.chance)
                        continue;

                    std::cout << "!!!! " << c.radius << " " << c.terraintag << std::endl;

                    cast_cloud(state, p.px, p.py, c.radius, c.terraintag);
                    state.render.do_message(nlp::message("%s casts %s!", s, c.name));
                    return false;
                }
            }
        }

        // HACK!
        if (s.sleepattack > 0 && p.sleep > 0) {
            do_random = true;
        }

        if (s.ai == Species::ai_t::seek_player && !do_random &&
            state.render.path_walk(m.xy.first, m.xy.second, p.px, p.py, 1, s.range, nxy.first, nxy.second)) {

            // Nothing, nxy is good.

        } else if (s.ai == Species::ai_t::random) {
            do_random = true;

        } else if (s.ai == Species::ai_t::inrange_random && dist <= s.range) {
            do_random = true;

        } else {

            switch (s.idle_ai) {

            case Species::idle_ai_t::random:

                if (dist > get_lightradius() + 5)
                    return false;

                do_random = true;
                break;

            default:
                return false;
            }
        }

        if (do_random) {
            std::vector<monsters::pt> tmp = monsters::Monsters::get_walkables(state.neigh, state.grid, s, m.xy);

            if (tmp.empty())
                return false;

            nxy = tmp[state.rng.n(tmp.size())];
        }

        if (!monsters::Monsters::is_walkable(state.grid, s, nxy))
            return false;

        if (nxy.first == p.px && nxy.second == p.py) {

            defend(p, p.inv.get_defense(), p.level, state, m, s);
            return false;

        } else {
            return true;
        }
    }

    bool process_feature(mainloop::GameState& state, features::Feature& f, const Terrain& t) {

        if (f.decay > 0) {
            --(f.decay);

            if (f.decay == 0)
                return false;
        }

        return true;
    }

    void process_world(mainloop::GameState& state, size_t& ticks, 
                       bool& done, bool& dead, bool& regen, bool& need_input, bool& do_draw) {

        if (p.health.val <= -3.0) {
            state.render.do_message("You are dead.", true);
            dead = true;
            done = true;
            return;
        }

        state.monsters.process(state.render, 
                               std::bind(&Game::move_monster, this, std::ref(state), ticks, 
                                         std::placeholders::_1, std::placeholders::_2, 
                                         std::placeholders::_3, std::placeholders::_4));

        state.features.process(state.render, 
                               std::bind(&Game::process_feature, this, std::ref(state),
                                         std::placeholders::_1, std::placeholders::_2));

        if (p.sleep > 0) {
            ++ticks;
            --(p.sleep);
            do_draw = true;
        }
    }

    void move_player(mainloop::GameState& state) {
        
        size_t nstack = state.items.stack_size(p.px, p.py);

        if (nstack == 1) {
            items::Item item;
            state.items.get(p.px, p.py, 0, item);
            const Design& d = designs().get(item.tag);

            state.render.do_message(nlp::message("You see %s.", d));

        } else if (nstack > 1) {

            state.render.do_message(nlp::message("You see %d items here.", nstack));

        } else {
            features::Feature feat;
            if (state.features.get(p.px, p.py, feat)) {
                const Terrain& t = terrain().get(feat.tag);

                state.render.do_message(nlp::message("There is %s here.", t));
            }
        }
    }

    void move(mainloop::GameState& state, int dx, int dy, size_t& ticks) {
        int nx = p.px + dx;
        int ny = p.py + dy;

        if (nx < 0 || ny < 0) 
            return;

        if (!state.neigh.linked(neighbors::pt(p.px, p.py), neighbors::pt(nx, ny)) ||
            !state.grid.is_walk(nx, ny)) {

            return;
        }

        monsters::Monster mon;
        if (state.monsters.get(nx, ny, mon)) {

            if (attack(p, p.inv.get_attack(), p.level, state, mon)) {
                ++ticks;
            }

            return;
        }

        ++ticks;

        state.render.unset_skin(p.px, p.py, 5);

        p.px = nx;
        p.py = ny;

        state.render.set_skin(p.px, p.py, 5, 
                              grender::Grid::skin("@", maudit::color::bright_white, 
                                                  maudit::color::bright_black));

        move_player(state);
    }

    void use_terrain(mainloop::GameState& state, size_t& ticks, bool& regen) {

        features::Feature feat;
        if (!state.features.get(p.px, p.py, feat)) {
            state.render.do_message("There is nothing here to use.");
            return;
        }

        const Terrain& t = terrain().get(feat.tag);

        if (t.stairs > 0) {
            state.render.do_message("You climb down the hole.");
            p.worldz += t.stairs;

            ++ticks;
            regen = true;
            return;
        }

        if (t.tunnel_x != 0 || t.tunnel_y != 0) {
            state.render.do_message("You climb into the tunnel.");
            p.worldx += t.tunnel_x;
            p.worldy += t.tunnel_y;

            p.worldx = std::min(p.worldx, 1);
            p.worldx = std::max(p.worldx, -1);
            p.worldy = std::min(p.worldy, 1);
            p.worldy = std::max(p.worldy, -1);

            ++ticks;
            regen = true;
            return;
        }

        state.render.do_message("There is nothing here to use.");
    }

    void rest(mainloop::GameState& state, size_t& ticks) {

        state.render.do_message(nlp::message("%d", state.grid._get(p.px, p.py)));
        ++ticks;
    }

    void cast_cloud(mainloop::GameState& state, unsigned int x, unsigned int y, unsigned int r,
                    const std::string& terraintag) {

        state.render.draw_circle(x, y, r, false, maudit::color::bright_blue, maudit::color::bright_black,
                                 [&](unsigned int _x, unsigned int _y) {

                                     features::Feature tmp;
                                     if (state.features.get(_x, _y, tmp) && tmp.tag != terraintag) return;

                                     if (!state.grid.is_walk(_x, _y)) return;

                                     state.features.set(_x, _y, terraintag, state.render);
                                 });
    }

    void handle_input_main(mainloop::GameState& state,
                           size_t& ticks, bool& done, bool& dead, bool& regen, 
                           maudit::keypress k) {

        bool redraw = false;

        switch (k.letter) {
        case 'Q':
            state.render.do_message("You quit the game.", true);
            done = true;
            dead = true;
            break;

        case 'S':
            done = true;
            dead = false;
            break;

        case 'h':
            move(state, -1, 0, ticks);
            break;
        case 'j':
            move(state, 0, 1, ticks);
            break;
        case 'k':
            move(state, 0, -1, ticks);
            break;
        case 'l':
            move(state, 1, 0, ticks);
            break;
        case 'y':
            move(state, -1, -1, ticks);
            break;
        case 'u':
            move(state, 1, -1, ticks);
            break;
        case 'b':
            move(state, -1, 1, ticks);
            break;
        case 'n':
            move(state, 1, 1, ticks);
            break;

        case '>':
            use_terrain(state, ticks, regen);
            break;

        case '.':
            rest(state, ticks);
            break;

        case ',':
            if (state.items.stack_size(p.px, p.py) == 0) {
                state.render.do_message("There are no items here.");

            } else {
                state.push_window(select_floor_item(p.inv, state.items, p.px, p.py, 0), screens_t::floor_item);
            }
            break;

        case 'i':
            state.push_window(show_inventory(p.inv, p.level, p.worldz, state.items, p.px, p.py), screens_t::inventory);
            break;

        case 'P':
            state.push_window(state.render.all_messages(), screens_t::messages);
            break;

        case '/':
            start_look_plain(p.state, p.look, p.px, p.py, state);
            break;

        case '\t':
            start_look_cycle(p.state, p.look, p.px, p.py, state, k);
            break;

        case 'z':
            cast_cloud(state, p.px, p.py, 5, "cd");
            break;
        }

        switch (k.key) {
        case maudit::keycode::up:
            move(state, 0, -1, ticks);
            break;
        case maudit::keycode::left:
            move(state, -1, 0, ticks);
            break;
        case maudit::keycode::right:
            move(state, 1, 0, ticks);
            break;
        case maudit::keycode::down:
            move(state, 0, 1, ticks);
            break;
        default:
            break;
        }            

        if (redraw) {
            state.render.clear();
        }
    }


    void handle_input_messages(mainloop::GameState& state, maudit::keypress k) {

        state.window_stack.pop_back();
    }

    void handle_input(mainloop::GameState& state,
                      size_t& ticks, bool& done, bool& dead, bool& regen, 
                      maudit::keypress k) {

        if (p.state & Player::LOOKING) {

            handle_input_looking(p.state, p.look, p.px, p.py, state, k);

            if (p.state & Player::THROWING) {

                end_throw_item(p, p.inv.selected_slot, p.look.x, p.look.y, state);
                ++ticks;
                p.state = Player::MAIN;
            }

            return;
        }

        if (state.window_stack.empty()) {
            handle_input_main(state, ticks, done, dead, regen, k);
            return;
        }

        switch ((screens_t)state.window_stack.back().type) {

        case screens_t::messages:
            handle_input_messages(state, k);
            break;

        case screens_t::inventory:
            handle_input_inventory(p, state, ticks, done, dead, regen, k);
            break;

        case screens_t::inv_item:
            handle_input_inv_item(p, state, ticks, done, dead, regen, k);
            break;

        case screens_t::floor_item:
            handle_input_floor_item(p, state, ticks, done, dead, regen, k);
            break;
        }
    }
};


void client_mainloop(int client_fd) {

    try {

        maudit::client_socket client(client_fd);

        typedef maudit::screen<maudit::client_socket> screen_t;

        std::cout << "Making screen..." << std::endl;
        screen_t screen(client);

        mainloop::Main<Game, screen_t> main(screen);

        std::cout << "Starting mainloop..." << std::endl;
        main.mainloop("_ngsave.tmp", ::time(NULL));

    } catch (std::exception& e) {
        std::cout << "Caught error: " << e.what() << std::endl;

    } catch (...) {
    }
}


int main(int argc, char** argv) {

    maudit::server_socket server("0.0.0.0", 20020);

    init_statics();

    while (1) {

        std::cout << "Accepting..." << std::endl;
        int client = server.accept();

        std::cout << "Making thread..." << std::endl;
        std::thread thr(client_mainloop, client);
        thr.detach();
    }

    return 0;
}
