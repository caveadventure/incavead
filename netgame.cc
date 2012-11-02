
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


void init_statics() {

    /*
      0 kobold caves
        kobold child
        kobold farmer
        kobold warrior
        female kobold
        kobold slave 
        kobold slavedriver
        kobold miner
        kobold chieftain
        kobold warlord
        kobold sex slave
        kobold shaman
        kobold hunter
        kobold infant
        kobold cannibal
        renegade kobold
        dog
        lichen
        pond scum
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
    
    /*
    init_species("moss1", 0, 150, "pond scum", "x", maudit::color::bright_green, 
                 Species::habitat_t::shoreline, Species::ai_t::none, Species::move_t::any, 0);

    init_species("moss2", 0, 150, "lichen", "x", maudit::color::dim_white, 
                 Species::habitat_t::corner, Species::ai_t::none, Species::move_t::any, 0);

    init_species("peasant", 0, 100, "dirty peasant", "h", maudit::color::dim_green, 
                 Species::habitat_t::clumped_floor, Species::ai_t::seek_player, Species::move_t::any, 8);

    init_species("cavefish", 0, 100, "cavefish", "f", maudit::color::bright_white, 
                 Species::habitat_t::clumped_water, Species::ai_t::seek_player, Species::move_t::water, 8);

    init_species("vagrant", 1, 75, "vagrant", "h", maudit::color::dim_red,
                 Species::habitat_t::walk, Species::ai_t::seek_player, Species::move_t::any, 12);

    init_species("pirahna", 1, 90, "pirahna", "f", maudit::color::dim_cyan,
                 Species::habitat_t::clumped_water, Species::ai_t::seek_player, Species::move_t::water, 20);

    init_species("knight", 2, 60, "knight errant", "h", maudit::color::dim_white,
                 Species::habitat_t::corner, Species::ai_t::seek_player, Species::move_t::any, 22);
    */

    configparser::parse_config("species.cfg");

    ////

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

    ////

    init_terrain(">", "hole in the floor", ">", maudit::color::bright_white, Terrain::placement_t::floor, 1);
}

enum class screens_t : unsigned int {
    messages = 0,
    inventory,
    inv_item,
    floor_item
};



struct stat_t {
    double val;
        
    stat_t() : val(3.0) {}

    void inc(double v) {
        val += v;
        if (val > 3) val = 3;
    }

    void dec(double v) {
        val -= v;
        if (val < -3) val = -3;
    }
};



struct inventory_t {

    std::unordered_map<std::string, items::Item> stuff;

    std::string selected_slot;
    unsigned int selected_floor_item;

    struct slot_t {
        std::string name;
        std::string letter;
    };

    std::map<std::string, slot_t> slots;

    inventory_t() {
        slots["w"] = slot_t{"Weapon", "a"};
    }

    bool get(const std::string& slot, items::Item& ret) {
        auto i = stuff.find(slot);

        if (i == stuff.end())
            return false;

        ret = i->second;
        return true;
    }

    bool valid(const std::string& slot) const {

        if (stuff.count(slot) == 0) 
            return false;

        return true;
    }

    bool take(const std::string& slot, items::Item& ret) {
        auto i = stuff.find(slot);

        if (i == stuff.end())
            return false;

        ret = i->second;
        stuff.erase(i);
        return true;
    }

    void place(const std::string& slot, const items::Item& i) {
        stuff[slot] = i;
    }

    bool inv_to_floor(const std::string& slot, unsigned int x, unsigned int y, items::Items& items, 
                      grender::Grid& grid) {

        items::Item tmp;

        if (!take(slot, tmp))
            return false;

        items.place(x, y, tmp, grid);
        return true;
    }

    bool floor_to_inv(unsigned int x, unsigned int y, unsigned int z, items::Items& items, 
                      grender::Grid& grid) {

        items::Item ftmp;

        if (!items.take(x, y, z, ftmp, grid))
            return false;

        const std::string& slot = designs().get(ftmp.tag).slot;

        if (slots.count(slot) == 0)
            return false;

        items::Item itmp;

        if (take(slot, itmp)) {
            items.place(x, y, itmp, grid);
        }

        place(slot, ftmp);
        return true;
    }

    void select_inv_item(std::string& window, const std::string& slot) {
        
        items::Item tmp;

        if (!get(slot, tmp))
            throw std::runtime_error("sanity error");

        const Design& d = designs().get(tmp.tag);

        window = nlp::message("\n"
                              "\3%S\1: (in your inventory)\n"
                              "\n"
                              "%s\n"
                              "\n"
                              "  \2d\1) Drop.\n",
                              nlp::count(), d, tmp.count,
                              d.descr);

        selected_slot = slot;
    }

    void select_floor_item(std::string& window, items::Items& items,
                           unsigned int px, unsigned int py, unsigned int z) {

        items::Item tmp;

        if (!items.get(px, py, z, tmp))
            throw std::runtime_error("sanity error");

        const Design& d = designs().get(tmp.tag);

        window = nlp::message("\n"
                              "\3%S\1: (on the floor)\n"
                              "\n"
                              "%s\n"
                              "\n",
                              nlp::count(), d, tmp.count,
                              d.descr);

        if (slots.count(d.slot) != 0) {
            window += "  \2t\1) Take.\n";
        }

        selected_floor_item = z;
    }
    
};



struct Player {

    unsigned int px;
    unsigned int py;

    int worldx;
    int worldy;
    int worldz;

    unsigned int level;

    unsigned int lightradius;

    stat_t health;

    inventory_t inv;

    Player() : px(0), py(0), worldx(0), worldy(0), worldz(0), level(1), lightradius(8) {}

    void show_info(std::string& m, items::Items& items) {

        m = nlp::message("\2Player stats:\n"
                         "  Character level: %d\n"
                         "  Dungeon level:   %d\n"
                         "\n"
                         "\2Inventory:\n",
                         level, 
                         worldz+1);

        for (const auto& slot : inv.slots) {

            items::Item tmp;

            if (!inv.get(slot.first, tmp)) 
                continue;

            const Design& d = designs().get(tmp.tag);

            m += nlp::message("  %s: \2%s\1) %S\n", 
                              slot.second.name,
                              slot.second.letter,
                              nlp::count(), d, tmp.count);
        }

        m += nlp::message("\n"
                          "\2Floor items:\n");

        size_t nz = items.stack_size(px, py);
        char letter = 'j';

        for (size_t z = 0; z < nz; ++z) {

            items::Item tmp;

            if (!items.get(px, py, z, tmp))
                throw std::runtime_error("sanity error");

            const Design& d = designs().get(tmp.tag);

            m += nlp::message("          \2%c\1) %S\n",
                              letter,
                              nlp::count(), d, tmp.count);
            ++letter;
        }
    }
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

    void drawing_context(mainloop::drawing_context_t& ctx) {

        unsigned int grid_x = ctx.view_w / 4;
        unsigned int grid_y = ctx.view_h / 4;

        if (grid_x > 1) {
            ctx.voff_off_x = -(p.px % grid_x) + (grid_x / 2);
        } else {
            ctx.voff_off_x = 0;
        }

        if (grid_y > 1) {
            ctx.voff_off_y = -(p.py % grid_y) + (grid_y / 2);
        } else {
            ctx.voff_off_y = 0;
        }

        ctx.px = p.px;
        ctx.py = p.py;
        ctx.lightradius = p.lightradius;
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

        if (s.ai == Species::ai_t::seek_player &&
            state.render.path_walk(m.xy.first, m.xy.second, p.px, p.py, 1, s.range, nxy.first, nxy.second)) {

            // Nothing, nxy is good.

        } else {

            switch (s.idle_ai) {

            case Species::idle_ai_t::random:
            {
                double dist = distance(m.xy.first, m.xy.second, p.px, p.py);

                if (dist > p.lightradius + 5)
                    return false;

                std::vector<monsters::pt> tmp = monsters::Monsters::get_walkables(state.neigh, state.grid, s, m.xy);

                if (tmp.empty())
                    return false;

                nxy = tmp[state.rng.n(tmp.size())];
            }
            break;

            default:
                return false;
            }
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

        bm _p("process_world");

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

    bool attack(mainloop::GameState& state, const monsters::Monster& mon) {

        const Species& s = species().get(mon.tag);

        double v = roll_attack(state.rng,
                               s.defense, s.level+1, 3.0, 1);

        if (v > 0) {

            state.monsters.change(mon, [v](monsters::Monster& m) { m.health -= v; });

            if (mon.health - v < -3) {
                state.render.do_message(nlp::message("You killed %s.", s));

            } else {
                state.render.do_message(nlp::message("You hit %s.", s));
            }

        } else {
            state.render.do_message(nlp::message("You attack %s but do no damage.", s));
        }

        return true;
    }

    void defend(mainloop::GameState& state, const monsters::Monster& mon, const Species& s) {

        double v = roll_attack(state.rng, 
                               1.0, 1, s.attack, s.level+1);

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

        std::ostringstream s;

        s << "[" << p.px << "," << p.py << "] : " << state.grid._get(p.px, p.py);

        state.render.do_message(s.str(), false);

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

        case 'i':
            p.show_info(state.message_window, state.items);
            state.window_stack.push_back((unsigned int)screens_t::inventory);
            break;

        case 'P':
            state.message_window = state.render.all_messages();
            state.window_stack.push_back((unsigned int)screens_t::messages);
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

    void handle_input_inventory(mainloop::GameState& state,
                                size_t& ticks, bool& done, bool& dead, bool& regen, 
                                maudit::keypress k) {

        switch (k.letter) {

        case 'a':
            if (!p.inv.valid("w")) return;

            p.inv.select_inv_item(state.message_window, "w");
            state.window_stack.push_back((unsigned int)screens_t::inv_item);
            return;

        default:
            break;
        }

        if (k.letter >= 'j') {
            unsigned int i = k.letter - 'j';

            if (i < state.items.stack_size(p.px, p.py)) {

                p.inv.select_floor_item(state.message_window, state.items, p.px, p.py, i);
                state.window_stack.push_back((unsigned int)screens_t::floor_item);
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

        if (state.window_stack.empty()) {
            handle_input_main(state, ticks, done, dead, regen, k);
            return;
        }

        switch ((screens_t)state.window_stack.back()) {

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
