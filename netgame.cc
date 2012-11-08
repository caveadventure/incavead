
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

#include "nlp.h"

#include "mainloop_net.h"

#include "configparser.h"

#include "inventory.h"
#include "inv_screens.h"
#include "player.h"
#include "apply.h"


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

    ////
    /*
    init_designs("twig", 0, 90, "%{a} twig%(s)", "~", maudit::color::dim_green, "w",
                 "A twig from a dry, bleached branch.\n"
                 "Can be used as an extremely ineffective melee weapon.");

    init_designs("rock", 0, 200, "%{a} pebble%(s)", "*", maudit::color::dim_white, "w",
                 "A fist-sized rock.\n"
                 "Can be used as an ineffective melee or projectile weapon.");

    init_designs("log", 0, 30, "%{a} log%(s)", "~", maudit::color::bright_green, "",
                 "Part of a washed up, bleached tree.\n"
                 "A useless item.");

    init_designs("leaf", 0, 100, "%{a} lea%{f}%(ves)", "~", maudit::color::dim_yellow, "",
                 "A dry leaf from a tree.\n"
                 "A useless item.");

    init_designs("sword0", 0, 20, "%{a} rusted sword%(s)", "(", maudit::color::dim_white, "w",
                 "A discarded, rusty sword.\n"
                 "Can be used a melee weapon.");
    */
    ////

    init_terrain(">", "hole in the floor", ">", maudit::color::bright_white, Terrain::placement_t::floor, 1);
}

enum class screens_t : unsigned int {
    messages = 0,
    inventory,
    inv_item,
    floor_item
};


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

        unsigned int nflatten = std::max(8 - (::abs(p.worldx) + ::abs(p.worldy)), 0);
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

        unsigned int stairscount = ::fabs(state.rng.gauss(50.0, 2.0));

        state.features.generate(state.rng, state.grid, ">", stairscount);

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

    maudit::color floor_color(double z) {

        if (z <= -9) {
            return maudit::color::dim_red;
        } else if (z <= -8) {
            return maudit::color::bright_red;
        } else if (z <= -7) {
            return maudit::color::dim_green;
        } else if (z <= -6) {
            return maudit::color::bright_green;
        } else if (z <= -5) {
            return maudit::color::dim_yellow;
        } else if (z <= -4) {
            return maudit::color::bright_yellow;
        } else if (z <= -3) {
            return maudit::color::dim_white;
        }

        return maudit::color::bright_white;
    }

    void set_skin(mainloop::GameState& state, unsigned int x, unsigned int y) {

        bool walkable = state.grid.is_walk(x, y);
        bool water = state.grid.is_water(x, y);

        state.render.set_is_viewblock(x, y, 0, !walkable);
        state.render.set_is_walkblock(x, y, 0, !walkable);

        grender::Grid::skin s;

        double z = state.grid._get(x, y);

        if (walkable) {
            if (water) {

                if (z <= -5) {
                    s = grender::Grid::skin("+", maudit::color::bright_blue, maudit::color::bright_black);
                } else {
                    s = grender::Grid::skin("-", maudit::color::bright_blue, maudit::color::bright_black);
                }

            } else {
                s = grender::Grid::skin(".", floor_color(z), maudit::color::bright_black);
            }

        } else {
            if (water) {
                s = grender::Grid::skin("#", maudit::color::bright_blue, maudit::color::bright_black);
            } else {
                s = grender::Grid::skin("#", maudit::color::bright_white, maudit::color::bright_black);
            }
        }

        state.render.set_skin(x, y, 0, s);

        // //

        features::Feature feat;

        if (state.features.get(x, y, feat)) {

            const Terrain& t = terrain().get(feat.tag);
            state.render.set_skin(x, y, 1, t.skin);

        } else {
            state.render.unset_skin(x, y, 1);
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

    void drawing_context(mainloop::drawing_context_t& ctx) {

        ctx.px = p.px;
        ctx.py = p.py;
        ctx.lightradius = p.lightradius;

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

    double distance(double ax, double ay, double bx, double by) {
        double q = (ax - bx);
        double p = (ay - by);
        return ::sqrt(q*q + p*p);
    }

    bool move_monster(mainloop::GameState& state, const monsters::Monster& m, const Species& s,
                      monsters::pt& nxy, bool& do_die) {

        if (m.health < -3) {
            do_die = true;
            return true;
        }

        bool do_random = false;

        double dist = distance(m.xy.first, m.xy.second, p.px, p.py);

        if (s.ai == Species::ai_t::seek_player &&
            state.render.path_walk(m.xy.first, m.xy.second, p.px, p.py, 1, s.range, nxy.first, nxy.second)) {

            // Nothing, nxy is good.

        } else if (s.ai == Species::ai_t::random) {
            do_random = true;

        } else if (s.ai == Species::ai_t::inrange_random && dist <= s.range) {
            do_random = true;

        } else {

            switch (s.idle_ai) {

            case Species::idle_ai_t::random:

                if (dist > p.lightradius + 5)
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
            defend(state, m, s);
            return false;

        } else {
            return true;
        }
    }

    void process_world(mainloop::GameState& state, size_t& ticks, 
                       bool& done, bool& dead, bool& regen, bool& need_input) {

        if (p.health.val <= -3.0) {
            state.render.do_message("You are dead.", true);
            dead = true;
            done = true;
            return;
        }

        state.monsters.process(state.render, 
                               std::bind(&Game::move_monster, this, std::ref(state), 
                                         std::placeholders::_1, std::placeholders::_2, 
                                         std::placeholders::_3, std::placeholders::_4));

    }

    double roll_attack(rnd::Generator& rng, 
                       double ddefense, unsigned int dlevel,
                       double aattack, unsigned int alevel) {

        double a = 0;
        for (unsigned int i = 0; i < alevel; ++i) {
            a += rng.uniform(0.0, aattack);
        }

        double d = 0;
        for (unsigned int i = 0; i < dlevel; ++i) {
            d += rng.uniform(0.0, ddefense);
        }

        std::cout << "** " << ddefense << ":" << dlevel << " <- " << aattack << ":" << alevel 
                  << " = " << a << " " << d << std::endl;

        return std::max(a - d, 0.0);
    }

    void monster_kill(mainloop::GameState& state, const monsters::Monster& mon, const Species& s) {

        for (const auto& drop : s.drop) {
            double v = state.rng.gauss(0.0, 1.0);

            std::cout << "?? " << v << " " << drop.chance << std::endl;

            if (v <= drop.chance)
                continue;

            state.items.place(mon.xy.first, mon.xy.second, items::Item(drop.tag, mon.xy), state.render);
        }

        if (s.ai == Species::ai_t::none)
            return;

        if (s.level > p.level) {
            p.level = s.level;
            state.render.do_message(nlp::message("You gained level %d!", p.level+1), true);
        }
    }

    bool attack(mainloop::GameState& state, const monsters::Monster& mon) {

        const Species& s = species().get(mon.tag);

        double attack = p.inv.get_attack();

        if (attack == 0) {
            state.render.do_message("You can't attack without a weapon!", true);
            return false;
        }

        double v = roll_attack(state.rng,
                               s.defense, s.level+1, attack, p.level+1);

        if (v > 0) {

            state.monsters.change(mon, [v](monsters::Monster& m) { m.health -= v; });

            if (mon.health - v < -3) {

                if (s.ai == Species::ai_t::none) {
                    state.render.do_message(nlp::message("You destroyed %s.", s));
                } else {
                    state.render.do_message(nlp::message("You killed %s.", s));
                }

                monster_kill(state, mon, s);

            } else if (s.ai == Species::ai_t::none) {
                state.render.do_message(nlp::message("You smash %s.", s));

            } else if (v < 0.5) {
                state.render.do_message(nlp::message("You hit %s.", s));

            } else if (v < 1.0) {
                state.render.do_message(nlp::message("You wound %s.", s));

            } else if (v < 2.0) {
                state.render.do_message(nlp::message("You heavily wound %s.", s));

            } else if (v < 2.8) {
                state.render.do_message(nlp::message("You critically wound %s.", s));

            } else {
                state.render.do_message(nlp::message("You mortally wound %s.", s));
            }

            std::cout << "     ----    " << v << " " << s.level << " " << p.level << std::endl;

            if (s.level == p.level && v >= 2.8) {

                ++p.level;
                state.render.do_message(nlp::message("You gained level %d!", p.level+1), true);
            }

        } else {
            state.render.do_message(nlp::message("You attack %s but do no damage.", s));
        }

        return true;
    }

    void defend(mainloop::GameState& state, const monsters::Monster& mon, const Species& s) {

        double defense = p.inv.get_defense();

        double v = roll_attack(state.rng, 
                               defense, p.level+1, s.attack, s.level+1);

        if (v > 0) {
            p.health.dec(v);

            state.render.do_message(nlp::message("%s hits!", s));
        } else {
            state.render.do_message(nlp::message("%s attacks but does no damage.", s));
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

            if (attack(state, mon)) {
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

    template <typename FUNC>
    bool toggle_feature(mainloop::GameState& state, size_t& ticks, FUNC f) {

        features::Feature feat;
        if (state.features.get(p.px, p.py, feat)) {

            const Terrain& t = terrain().get(feat.tag);

            if (f(t)) {
                ticks++;
                return true;
            }
        }

        return false;
    }

    bool descend(mainloop::GameState& state, size_t& ticks) {

        if (toggle_feature(state, ticks, [&](const Terrain& t) {
                    
                    if (t.stairs) {

                        state.render.do_message("You climb down the hole.");
                        p.worldz += t.stairs;
                        return true;
                    } 

                    return false;
                }))
            return true;

        state.render.do_message("You can't descend here.");
        return false;
    }

    void rest(mainloop::GameState& state, size_t& ticks) {

        ++ticks;
    }

    void handle_input_main(mainloop::GameState& state,
                           size_t& ticks, bool& done, bool& dead, bool& regen, 
                           maudit::keypress k) {

        bool redraw = false;

        switch (k.letter) {
        case 'Q':
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
            if (descend(state, ticks)) {
                regen = true;
            }
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
            start_look_plain(state);
            break;

        case '\t':
            start_look_cycle(state, k);
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

    void center_draw_text(grender::Grid& render, unsigned int x, unsigned int y, const std::string& t) {

        int _x = x;
        unsigned int x1 = std::max(0, _x-(int)t.size()/2);
        render.draw_text(x1, y+1, t, maudit::color::bright_white, maudit::color::dim_blue);
    }

    void start_look_plain(mainloop::GameState& state) {

        p.state = Player::LOOKING;
        p.look = Player::look_t(p.px, p.py);

        center_draw_text(state.render, p.px, p.py, 
                         "Use arrow keys to look around; <TAB> to cycle targets");
    }

    void start_look_cycle(mainloop::GameState& state, maudit::keypress k) {

        p.state = Player::LOOKING;
        p.look = Player::look_t(p.px, p.py);
        
        handle_input_looking(state, k);
    }

    void look_move(mainloop::GameState& state, int dx, int dy) {
        int nx = p.look.x + dx;
        int ny = p.look.y + dy;

        if (nx < 0 || ny < 0) 
            return;

        if (!state.neigh.linked(neighbors::pt(p.look.x, p.look.y), neighbors::pt(nx, ny))) {

            return;
        }

        p.look.x = nx;
        p.look.y = ny;
    }

    void look_cycle(mainloop::GameState& state) {

        std::cout << "| " << p.look.target << std::endl;

        (p.look.target)++;

        int n = 0;

        for (const auto& i : state.monsters.mons) {
            if (!state.render.is_in_fov(i.first.first, i.first.second))
                continue;

            const Species& s = species().get(i.second.tag);
            std::cout << "   = " << n << " " << p.look.target << " " << nlp::message("%s", s) << std::endl;
            if (n == p.look.target) {
                p.look.x = i.first.first;
                p.look.y = i.first.second;
                return;
            }

            ++n;
        }

        for (const auto& i : state.items.stuff) {
            if (!state.render.is_in_fov(i.first.first, i.first.second))
                continue;

            const Design& d = designs().get(i.second.front().tag);

            std::cout << "   = " << n << " " << p.look.target << " " << nlp::message("%s", d) << std::endl;
            if (n == p.look.target) {
                p.look.x = i.first.first;
                p.look.y = i.first.second;
                return;
            }

            ++n;
        }

        std::cout << " | " << std::endl;

        p.look.target = -1;
        p.look.x = p.px;
        p.look.y = p.py;

        if (n > 0) {
            look_cycle(state);
        }
    }

    void handle_input_looking(mainloop::GameState& state, maudit::keypress k) {

        int stop = 0;

        switch (k.letter) {
        case 'h':
            look_move(state, -1, 0);
            break;
        case 'j':
            look_move(state, 0, 1);
            break;
        case 'k':
            look_move(state, 0, -1);
            break;
        case 'l':
            look_move(state, 1, 0);
            break;
        case 'y':
            look_move(state, -1, -1);
            break;
        case 'u':
            look_move(state, 1, -1);
            break;
        case 'b':
            look_move(state, -1, 1);
            break;
        case 'n':
            look_move(state, 1, 1);
            break;
            
        case '\t':
            look_cycle(state);
            break;

        case '.':
            if (p.state & Player::TARGET) {
                p.state = Player::FIRING;
                return;
            }

        default:
            ++stop;
            break;
        }

        switch (k.key) {
        case maudit::keycode::up:
            look_move(state, 0, -1);
            break;
        case maudit::keycode::left:
            look_move(state, -1, 0);
            break;
        case maudit::keycode::right:
            look_move(state, 1, 0);
            break;
        case maudit::keycode::down:
            look_move(state, 0, 1);
            break;

        default:
            ++stop;
            break;
        }            

        if (stop > 1) {
            p.state = Player::MAIN;
            return;
        }


        if (p.state & Player::TARGET) {

            unsigned int monc = 0;

            state.render.draw_line(p.px, p.py, p.look.x, p.look.y, true, 
                                   maudit::color::bright_red, maudit::color::white_red,
                                   [&](unsigned int x, unsigned int y) {

                                       double dist = distance(p.px, p.py, x, y);

                                       if (!state.grid.is_walk(x, y) || 
                                           !state.render.is_in_fov(x, y) ||
                                           monc > 0 ||
                                           dist < p.look.rangemin ||
                                           dist > p.look.rangemax) {

                                           return false;
                                       }

                                       monsters::Monster tmp;
                                       if (state.monsters.get(x, y, tmp)) {
                                           monc++;
                                       }

                                       p.look.x = x;
                                       p.look.y = y;
                                       return true;
                                   });
        }


        std::string msg;
        monsters::Monster mon;
        items::Item itm;

        unsigned int x = p.look.x;
        unsigned int y = p.look.y;
        size_t n = state.items.stack_size(x, y);

        if (!state.render.is_in_fov(x, y)) {

        } else if (state.monsters.get(x, y, mon)) {
            msg = nlp::message(" %s", species().get(mon.tag));

        } else if (n > 1) {
            msg = nlp::message(" %d items", n);

        } else if (n == 1 && state.items.get(x, y, 0, itm)) {
            
            msg = nlp::message(" %s", designs().get(itm.tag));

        } else if (x == p.px && y == p.py) {
            msg = " This is you";
        }

        state.render.draw_text(p.look.x+1, p.look.y, msg, maudit::color::bright_white, maudit::color::dim_blue);
    }

    void start_look_target(mainloop::GameState& state, int rangemin, int rangemax) {

        p.state = (Player::LOOKING | Player::TARGET);
        p.look = Player::look_t(p.px, p.py);
        p.look.rangemin = rangemin;
        p.look.rangemax = rangemax;

        center_draw_text(state.render, p.px, p.py, 
                         "Use <TAB> or arrow keys to select target, '.' to fire");
    }

    bool throw_item(const std::string& slot, mainloop::GameState& state) {

        items::Item tmp;
        if (!p.inv.get(slot, tmp))
            return false;

        const Design& d = designs().get(tmp.tag);

        if (d.throwrange == 0)
            return false;

        start_look_target(state, 0, d.throwrange);
        return true;
    }

    void handle_input_inventory(mainloop::GameState& state,
                                size_t& ticks, bool& done, bool& dead, bool& regen, 
                                maudit::keypress k) {

        auto i = p.inv.slot_keys.find(k.letter);

        if (i != p.inv.slot_keys.end() &&
            p.inv.valid(i->second)) {
        
            state.push_window(select_inv_item(p.inv, i->second), screens_t::inv_item);
            return;
        }

        if (k.letter >= '1') {
            unsigned int i = k.letter - '1';

            if (i < state.items.stack_size(p.px, p.py)) {

                state.push_window(select_floor_item(p.inv, state.items, p.px, p.py, i), screens_t::floor_item);
                return;
            }
        }

        state.window_stack.pop_back();
    }

    void handle_input_inv_item(mainloop::GameState& state,
                               size_t& ticks, bool& done, bool& dead, bool& regen, 
                               maudit::keypress k) {

        if (k.letter == 'd') {
            p.inv.inv_to_floor(p.inv.selected_slot, p.px, p.py, state.items, state.render);

            ticks++;
            state.window_stack.clear();
            return;

        } else if (k.letter == 'a' && apply_item(p, p.inv.selected_slot, state.render)) {

            ticks++;
            state.window_stack.clear();
            return;

        } else if (k.letter == 't' && throw_item(p.inv.selected_slot, state)) {

            state.window_stack.clear();
            return;
        }

        state.window_stack.pop_back();
    }

    void handle_input_floor_item(mainloop::GameState& state,
                                 size_t& ticks, bool& done, bool& dead, bool& regen, 
                                 maudit::keypress k) {

        if (k.letter == 't') {
            if (p.inv.floor_to_inv(p.px, p.py, p.inv.selected_floor_item, state.items, state.render)) {

                ticks++;
                state.window_stack.clear();
                return;
            }
        }

        state.window_stack.pop_back();
    }

    void handle_input_messages(mainloop::GameState& state, maudit::keypress k) {

        state.window_stack.pop_back();
    }

    void handle_input(mainloop::GameState& state,
                      size_t& ticks, bool& done, bool& dead, bool& regen, 
                      maudit::keypress k) {

        if (p.state & Player::LOOKING) {
            handle_input_looking(state, k);
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
            handle_input_inventory(state, ticks, done, dead, regen, k);
            break;

        case screens_t::inv_item:
            handle_input_inv_item(state, ticks, done, dead, regen, k);
            break;

        case screens_t::floor_item:
            handle_input_floor_item(state, ticks, done, dead, regen, k);
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
