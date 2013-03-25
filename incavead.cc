
#include <thread>

#include <sstream>

#include <iostream>

#include "libmaudit/maudit.h"

#include "debug_benchmark.h"

////

#include "damage.h"
#include "terrain.h"
#include "designs.h"
#include "species.h"
#include "vaults.h"

#include "terrain_bank.h"
#include "designs_bank.h"
#include "species_bank.h"
#include "vaults_bank.h"

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
#include "monster_ai.h"

enum class screens_t : unsigned int {
    messages = 0,
    inventory,
    inv_item,
    floor_item,
    spells,
    help
};

#include "inv_screens2.h"


void init_statics() {

    /*

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

    configparser::parse_config("vaults.cfg");

    configparser::parse_config("celauto.cfg");

    configparser::parse_config("levelskins.cfg");

    ////

    
    // -m,m2 (f)
    // -rv,rh (d)
    // -v (h)
    // +w (dg)
    // +sc
    // +sl
    // +sw,+sf 

    // +food
    // +heal

    // +teleport?
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
        std::cout << "Writing grid... " << cached_grid << std::endl;

        serialize::Sink sink(cached_grid);
        serialize::write(sink, state.grid);

        std::cout << "Writing OK" << std::endl;
    }

    void generate_vault(const Vault& vault, mainloop::GameState& state, std::vector<summons_t>& summons) {

        grid::pt xy;

        for (unsigned int i = 0; i < 10; ++i) {

            switch (vault.placement) {
            case Vault::placement_t::floor:
                if (!state.grid.one_of_floor(state.rng, xy)) return;
                break;
            case Vault::placement_t::water:
                if (!state.grid.one_of_lake(state.rng, xy)) return;
                break;
            case Vault::placement_t::corner:
                if (!state.grid.one_of_corner(state.rng, xy)) return;
                break;
            }

            std::cout << "VAULT XXX " << vault.tag << " " << xy.first << " " << xy.second 
                      << " " << vault.w << " " << vault.h 
                      << " " << state.grid.w << " " << state.grid.h << std::endl;
            
            if (xy.first  >= state.grid.w - vault.w ||
                xy.second >= state.grid.h - vault.h)
                continue;

            if (i >= 9) return;

            break;
        }

        std::set<grid::pt> affected;

        for (int i = -1; i <= (int)vault.w; ++i) {
            affected.insert(grid::pt(xy.first + i, xy.second - 1));
            affected.insert(grid::pt(xy.first + i, xy.second + vault.h));
        }

        for (int i = 0; i < (int)vault.h; ++i) {
            affected.insert(grid::pt(xy.first - 1, xy.second + i));
            affected.insert(grid::pt(xy.first + vault.w, xy.second + i));
        }

        for (unsigned int y = 0; y < vault.h; ++y) {
             for (unsigned int x = 0; x < vault.w; ++x) {

                 const std::string& line = vault.pic[y];
                 if (x >= line.size()) 
                     continue;

                 unsigned int c = line[x];
                 auto bi = vault.brushes.find(c);

                 if (bi == vault.brushes.end()) {
                     throw std::runtime_error("Invalid brush char for " + vault.tag + ": '" + 
                                              std::string(1, c) + "'");
                 }

                 const Vault::brush& b = bi->second;

                 unsigned int xi = xy.first + x;
                 unsigned int yi = xy.second + y;

                 affected.insert(grid::pt(xi, yi));

                 std::cout << "VAULT " << vault.tag << " " << xi << " " << yi << std::endl;
                 std::cout << "brush " << c << " " << b.is_blank << " " << b.is_walk << " " << b.is_water 
                           << " " << b.species << std::endl;

                 if (!b.is_blank) {

                     if (b.is_walk) {
                         state.grid.walkmap.insert(grid::pt(xi, yi));
                     } else {
                         state.grid.walkmap.erase(grid::pt(xi, yi));
                     }

                     if (b.is_water) {
                         state.grid.watermap.insert(grid::pt(xi, yi));
                     } else {
                         state.grid.watermap.erase(grid::pt(xi, yi));
                     }
                 }

                 if (b.terrain.size() > 0) {
                     state.features.set(xi, yi, b.terrain, state.render);
                 }

                 if (b.design.size() > 0) {
                     state.items.place(xi, yi, 
                                       state.items.make_item(b.design, items::pt(xi, yi), state.rng), 
                                       state.render);
                 }

                 if (b.species.size() > 0) {
                     if (!state.grid.is_walk(xi, yi))
                         throw std::runtime_error("Invalid vault monster placement");

                     summons.push_back(summons_t{xi, yi, b.species, ""});
                 }
             }
        }


        state.grid._set_maps_of(state.neigh, affected);
    }

    void generate(mainloop::GameState& state) {

        bm _zz("level generation");

        // Read or generate cached map.

        std::ostringstream cached_grid;

        cached_grid << "_level_" << p.worldx << "_" << p.worldy << "_" << p.worldz << ".dat";

        uint64_t gridseed = (((uint64_t)p.worldx) ^ 
                             ((uint64_t)p.worldy << 16) ^
                             ((uint64_t)p.worldz << 32)) + 1;

        try {
            bm _rg("reading grid");

            std::cout << "Reading grid... " << cached_grid.str() << std::endl;

            serialize::Source source(cached_grid.str());
            serialize::read(source, state.grid);

            std::cout << "Reading grid OK" << std::endl;

        } catch (std::exception& e) {

            make_map(state, gridseed, cached_grid.str());
        }

        // //

        for (const auto& xy : state.grid.cornermap) {
            if (state.grid.walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 1.1");
        }

        for (const auto& xy : state.grid.lakemap) {
            if (state.grid.walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 1.2.1");

            if (state.grid.watermap.count(xy) == 0)
                throw std::runtime_error("Sanity error 1.2.2");
        }

        for (const auto& xy : state.grid.shoremap) {
            if (state.grid.walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 1.3");
        }

        state.rng.init(gridseed);

        std::vector<summons_t> summons;

        {
            bm _gg("vault generation");

            std::map<std::string, unsigned int> vc = state.vaults_counts.take(state.rng, p.worldz, 100);

            for (const auto vi : vc) {
                const Vault& v = vaults().get(vi.first);

                for (unsigned int ci = 0; ci < vi.second; ++ci) {
                    generate_vault(v, state, summons);
                }
            }
        }

        for (const auto& xy : state.grid.cornermap) {
            if (state.grid.walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 2.1");
        }

        for (const auto& xy : state.grid.lakemap) {
            if (state.grid.walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 2.2.1");

            if (state.grid.watermap.count(xy) == 0)
                throw std::runtime_error("Sanity error 2.2.2");
        }

        for (const auto& xy : state.grid.shoremap) {
            if (state.grid.walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 2.3");
        }

        for (const auto& xy : state.grid.floormap) {
            if (state.grid.walkmap.count(xy) == 0)
                throw std::runtime_error("Sanity error 2.4");
        }

        for (const auto& mv : state.monsters.mons) {
            if (state.grid.walkmap.count(mv.first) == 0)
                throw std::runtime_error("Sanity error 3");
        }

        grid::Map::genmaps_t maps(state.grid);

        {
            bm _gg("feature generation");

            // Place some dungeon features on the same spots every time.

            state.terrain_counts = terrain().counts;

            unsigned int featscount = ::fabs(state.rng.gauss(35.0, 5.0));

            for (unsigned int i = 0; i < featscount; ++i) {

                unsigned int takecount = ::fabs(state.rng.gauss(5.0, 1.0));

                std::map<std::string, unsigned int> t = state.terrain_counts.take(state.rng, 0, takecount);

                for (const auto& j : t) {
                    state.features.generate(state.rng, state.grid, maps, j.first, j.second);
                }
            }
        }

        // Place some random items.

        state.rng.init(::time(NULL));

        {
            bm _y("placing player");

            grid::pt xy;
            if (!maps.one_of_lowlands(state.rng, xy))
                throw std::runtime_error("Failed to generate grid");

            p.px = xy.first;
            p.py = xy.second;

            maps.add_nogen_expand(state.neigh, p.px, p.py, 3);
        }

        {
            bm _y("item generation");

            unsigned int itemgroups = ::fabs(state.rng.gauss(300.0, 50.0));

            for (unsigned int i = 0; i < itemgroups; ++i) {
                bm _yy("one item gen");

                unsigned int itemcount = std::max(1.0, state.rng.gauss(1.5, 1.0));
                unsigned int itemlevel = p.worldz;

                state.items.generate(state.neigh, state.rng, state.grid, maps,
                                     state.designs_counts, itemlevel, itemcount);
            }
        }

        // Place some random monsters.

        {
            bm _z("monster generation");

            for (const auto& s : summons) {
                unsigned int X = state.monsters.summon(state.neigh, state.rng, state.grid, state.species_counts, 
                                                       state.render, s.x, s.y, s.summontag);
                std::cout << "Summoned " << X << " of " << s.summontag << std::endl;
            }

            unsigned int mongroups = ::fabs(state.rng.gauss(250.0, 20.0));

            for (unsigned int i = 0; i < mongroups; ++i) {

                unsigned int monlevel = p.worldz;

                state.monsters.generate(state.neigh, state.rng, state.grid, maps,
                                        state.species_counts, monlevel);
            }
        }

        for (const auto& mv : state.monsters.mons) {
            if (state.grid.walkmap.count(mv.first) == 0)
                throw std::runtime_error("Sanity error 4");
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
            state.render.set_is_lit(x, y, 1, t.is_lit);

        } else {
            state.render.unset_skin(x, y, 1);
            state.render.set_is_viewblock(x, y, 1, false);
            state.render.set_is_walkblock(x, y, 1, false);
            state.render.set_is_lit(x, y, 1, false);
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
    void save(SINK& s) {
        serialize::write(s, p);
    }

    template <typename SOURCE>
    void load(SOURCE& s) {
        serialize::read(s, p);
    }

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

        const Levelskin& ls = levelskins().get(p.worldz);

        return std::min(ls.lightradius_max, ls.lightradius + p.inv.get_lightradius());
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

    void draw_one_stat(mainloop::GameState& state, const stat_t& s, const std::string& name) {

        double v = s.val;
        int vp = 0;

        if (v > 2) vp = 3;
        else if (v > 1) vp = 2;
        else if (v > 0) vp = 1;
        else if (v < -2) vp = -3;
        else if (v < -1) vp = -2;
        else if (v < 0) vp = -1;

        if (v != 0) {
            state.render.push_hud_line(name, maudit::color::dim_green,
                                       vp, '-', '+',
                                       maudit::color::dim_red, maudit::color::dim_green);
        }
    }

    void draw_hud(mainloop::GameState& state, size_t ticks) {

        draw_one_stat(state, p.health, "Health");
        draw_one_stat(state, p.food,   "Food");
        draw_one_stat(state, p.karma,  "Karma");

        if (p.sleep > 0) {
            state.render.push_hud_line("Sleep", maudit::color::bright_red,
                                       std::min(p.sleep / 15 + 1, (unsigned int)6), 
                                       '+', 
                                       (ticks & 1 ? maudit::color::bright_red : maudit::color::dim_red));
        }

        if (p.digging) {

            double q = state.grid._get(p.dig_x, p.dig_y);

            q = ((q + 10) / 3.0) + 1.0;
            q = std::max(1.0, std::min(q, 6.0));

            state.render.push_hud_line("Tunnel", maudit::color::dim_green,
                                       q,
                                       '+', 
                                       (ticks & 1 ? maudit::color::bright_blue : maudit::color::dim_blue));

            std::cout << "DIG " << q << std::endl;
        }

        //state.render.push_hud_line("Foo", maudit::color::bright_yellow, 
        //                           4, '+', maudit::color::bright_green);
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

        state.camap.step(
            [&state](unsigned int x, unsigned int y, const CelAuto& ca) {

                std::set<neighbors::pt> ret;
                for (const auto& xy : state.neigh(neighbors::pt(x,y))) {

                    if (state.grid.is_walk(xy.first, xy.second) == ca.is_walk && 
                        state.grid.get_karma(xy.first, xy.second) * ca.karma_scale < 1.0)
                        ret.insert(xy);
                }
                return ret;
                std::cout << ret.size() << std::endl;
            },

            [&state](unsigned int x, unsigned int y, const CelAuto& ca) {

                if (ca.make_walk) {
                    state.grid.set_walk_water(state.neigh, x, y, true, state.grid.is_water(x, y));
                    state.render.invalidate(x, y);
                }

                state.features.x_set(x, y, ca.terrain, state.render);
                state.grid.get_karma(x, y) += ca.karma_step;
            },

            [&state](unsigned int x, unsigned int y, const CelAuto& ca) {

                state.features.x_unset(x, y, ca.terrain, state.render);
            }
            );


        features::Feature feat;
        if (state.features.get(p.px, p.py, feat)) {

            const Terrain& t = terrain().get(feat.tag);

            if (!t.attacks.empty()) {

                damage::defenses_t defenses;
                p.inv.get_defense(defenses);

                defend(p, defenses, p.level, t, state);
            }
        }

        std::vector<summons_t> summons;

        state.monsters.process(state.render, 
                               std::bind(move_monster, std::ref(p), std::ref(state), ticks, std::ref(summons),
                                         std::placeholders::_1, std::placeholders::_2, 
                                         std::placeholders::_3, std::placeholders::_4));

        state.features.process(state.render, 
                               std::bind(&Game::process_feature, this, std::ref(state),
                                         std::placeholders::_1, std::placeholders::_2));

        for (const auto& i : summons) {

            unsigned int nm = state.monsters.summon(state.neigh, state.rng, state.grid, state.species_counts, 
                                                    state.render, i.x, i.y, i.summontag);

            if (nm > 0 && state.render.is_in_fov(i.x, i.y)) {

                state.render.do_message(nlp::message("%s summons %s!", species().get(i.summonertag), 
                                                     nlp::count(), species().get(i.summontag), nm));
            }
        }


        for (std::vector<Terrain::spell_t>::iterator si = p.spells.begin(); si != p.spells.end(); ) {
            double k = p.karma.val;
            auto& sp = *si;

            if (sp.karma_bound < 0 && k > sp.karma_bound) {
                sp.timeout -= (k - sp.karma_bound);

            } else if (sp.karma_bound > 0 && k < sp.karma_bound) {
                sp.timeout -= (sp.karma_bound - k);
            }

            if (sp.timeout <= 0) {
                si = p.spells.erase(si);

                state.render.do_message("You feel a sense of arcane foreboding.", true);
            } else {
                ++si;
            }
        }

        p.food.dec(0.003);

        if (p.food.val <= -3.0) {
            state.render.do_message("You desperately need something to eat!", true);
            p.food.dec(0.1);
        }

        if (p.health.val <= -3.0) {
            state.render.do_message("You are dead. (Press space to quit.)", true);
            dead = true;
            done = true;
            return;
        }

        if (p.sleep > 0) {
            ++ticks;
            --(p.sleep);
            do_draw = true;
            return;
        }

        if (p.digging) {

            std::cout << "digging .. " << p.dig_x << "," << p.dig_y << std::endl;

            if (state.grid.is_walk(p.dig_x, p.dig_y)) {
                state.render.do_message("OOPS");
                p.digging = false;
                return;
            }

            ++ticks;
            do_draw = true;
            

            double digspeed = p.inv.get_digging();

            double& height = state.grid._get(p.dig_x, p.dig_y);

            std::cout << "DIG: " << height << " " << digspeed << std::endl;

            height -= digspeed;

            if (height < -10) {
                height = -10;
                state.grid.set_walk_water(state.neigh, p.dig_x, p.dig_y, true, state.grid.is_water(p.dig_x, p.dig_y));
                state.render.invalidate(p.dig_x, p.dig_y);

                p.digging = false;
                state.render.do_message("Digging done.");
            }
        }
    }

    void move_player(mainloop::GameState& state) {
        
        size_t nstack = state.items.stack_size(p.px, p.py);

        if (nstack == 1) {
            items::Item item;
            state.items.get(p.px, p.py, 0, item);
            const Design& d = designs().get(item.tag);

            state.render.do_message(nlp::message("You see %s.", nlp::count(), d, item.count));

        } else if (nstack > 1) {

            state.render.do_message(nlp::message("You see %d items here.", nstack));

        } else {
            features::Feature feat;
            if (state.features.get(p.px, p.py, feat)) {
                const Terrain& t = terrain().get(feat.tag);

                if (t.name.size() > 0) {
                    state.render.do_message(nlp::message("There is %s here.", t));
                }
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

            damage::attacks_t attacks;
            p.inv.get_attack(attacks);

            if (attack(p, attacks, p.level, state, mon)) {
                ++ticks;
            }

            return;
        }

        ++ticks;

        features::Feature feat;
        if (state.features.get(p.px, p.py, feat)) {

            const Terrain& t = terrain().get(feat.tag);

            if (t.sticky) {
                state.render.do_message("You are stuck!");

                state.features.uncharge(p.px, p.py, state.render);
                return;
            }
        }

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

            std::cout << "^: " << t.tunnel_x << "," << t.tunnel_y << " " << p.worldx << "," << p.worldy << std::endl;

            if (p.worldx > 1) p.worldx = -1;
            else if (p.worldx < -1) p.worldx = 1;

            if (p.worldy > 1) p.worldy = -1;
            else if (p.worldy < -1) p.worldy = 1;

            std::cout << "^: " << p.worldx << "," << p.worldy << std::endl;

            ++ticks;
            regen = true;
            return;
        }

        if (t.grant_spell.timeout > 0) {

            const auto& sp = t.grant_spell;

            if ((sp.karma_bound < 0 && p.karma.val <= sp.karma_bound) ||
                (sp.karma_bound > 0 && p.karma.val >= sp.karma_bound)) {

                for (const auto& i : p.spells) {
                    if (i.name == sp.name) {
                        state.render.do_message("Nothing happens.");
                        return;
                    }
                }

                p.spells.push_back(sp);
                state.render.do_message(nlp::message("You are granted the power of %s.", sp.name), true);

            } else {
                state.render.do_message("You want nothing to do with this vile thing.");
            }

            return;
        }

        state.render.do_message("There is nothing here to use.");
    }

    void rest(mainloop::GameState& state, size_t& ticks) {

        //REMOVEME
        state.render.do_message(nlp::message("%d %d", p.px, p.py));

        ++ticks;
    }

    void seed_celauto(mainloop::GameState& state, 
                      unsigned int _x, unsigned int _y, const std::string& tag) {

        const CelAuto& ca = celautos().get(tag);

        for (const auto& dxy : ca.seed) {

            int x = _x + dxy.first;
            int y = _y + dxy.second;

            if (x < 0 || y < 0 || x > (int)state.neigh.w || y > (int)state.neigh.h)
                continue;

            state.camap.seed(x, y, tag);
        }
    }

    std::string show_spells(std::vector<Terrain::spell_t>& spells) {

        std::string m;

        m = "\2Your arcane powers:\n\n";

        char z = 'a';
        for (const auto& sp : spells) {

            m += nlp::message("   \2%c\1) %S\n", z, sp);
            ++z;
        }

        return m;
    }

    void handle_input_spells(mainloop::GameState& state, size_t& ticks, maudit::keypress k) {

        int z = k.letter - 'a';

        if (z < 0 || z >= (int)p.spells.size()) {
            state.window_stack.pop_back();
            return;
        }

        const auto& sp = p.spells[z];

        seed_celauto(state, p.px, p.py, sp.ca_tag);        
        ++ticks;
        state.window_stack.pop_back();
    }


    std::string help_text() {

        std::string ret = 
            "\3Essential commands:\1\n"
            "  \2h j k l\1 "
            "  \2arrow keys\1 : Move left, down, up and right.\n"
            "  \2y u b n\1 "
            "  \2keypad\1 :     Move diagonally.\n"
            "  \2.\1 :          Stand still.\n"
            "  \2S\1 :          Save and quit.\n"
            "  \2Q\1 :          Commit suicide and quit.\n"
            "  \2>\1 :          Use terrain. (Enter holes and tunnels, use statues.)\n"
            "  \2i\1 :          Interact with inventory and show character info.\n"
            "  \2z\1 :          Cast spells if you know them.\n"
            "  \2/\1 :          Look around you using arrow keys.\n"
            "  \2tab\1 :        Look at monsters and items in view.\n"
            "  \2P\1 :          Show message history.\n"
            "  \2?\1 :          Show this help message.\n"
            "\n\3Shortcut commands:\1\n"
            "  \2T\1 :          Take the first item laying on the floor.\n"
            "  \2,\1 :          Examine the first item laying on the floor.\n"
            "  \2H\1 :          Use medicine if you have any.\n"
            "  \2F\1 :          Eat food if you have any.\n"
            "  \2Z\1 :          Fire a magical item if you have one.\n"
            "  \2D\1 :          Tunnel at rock if you have a instrument for digging.\n"
            ;

        return ret;
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
            state.render.do_message("Your game has been saved. Press any key.", true);
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

        case 'T':
            take_item(p.px, p.py, 0, p, state, ticks);
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

        case 'z':
            state.push_window(show_spells(p.spells), screens_t::spells);
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

            //
        case 'D':
            p.inv.selected_slot = "d";
            if (!handle_input_inv_item(p, state, ticks, done, dead, regen, maudit::keypress('D')))
                state.render.do_message("You don't have a tool you can dig with.");
            break;

        case 'H':
            p.inv.selected_slot = "e";
            if (!handle_input_inv_item(p, state, ticks, done, dead, regen, maudit::keypress('a')))
                state.render.do_message("You have nothing in your 'medical' slot.");
            break;

        case 'F':
            p.inv.selected_slot = "f";
            if (!handle_input_inv_item(p, state, ticks, done, dead, regen, maudit::keypress('a')))
                state.render.do_message("You have nothing in your 'food' slot.");
            break;

        case 'Z':
            p.inv.selected_slot = "m1";
            if (!handle_input_inv_item(p, state, ticks, done, dead, regen, maudit::keypress('f')))
                state.render.do_message("You have nothing in your 'magical' slot.");
            break;

        case '?':
            state.push_window(help_text(), screens_t::help);
            break;

            ////
            // REMOVEME

            /*
        case 'z':
            seed_celauto(state, p.px, p.py, "m");
            break;

        case 'x':
            seed_celauto(state, p.px, p.py, "w");
            break;
            */
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
        case maudit::keycode::kp_7:
            move(state, -1, -1, ticks);
            break;
        case maudit::keycode::kp_9:
            move(state, 1, -1, ticks);
            break;
        case maudit::keycode::kp_1:
            move(state, -1, 1, ticks);
            break;
        case maudit::keycode::kp_3:
            move(state, 1, 1, ticks);
            break;
        default:
            break;
        }            

        if (redraw) {
            state.render.clear();
        }
    }


    void handle_input_pick_direction(unsigned int& pstate, unsigned int px, unsigned int py, size_t& ticks,
                                     mainloop::GameState& state, maudit::keypress k) {

        unsigned int nx = px;
        unsigned int ny = py;

        switch (k.letter) {
        case 'h':
            nx--;
            break;
        case 'j':
            ny++;
            break;
        case 'k':
            ny--;
            break;
        case 'l':
            nx++;
            break;
        case 'y':
            nx--;
            ny--;
            break;
        case 'u':
            nx++;
            ny--;
            break;
        case 'b':
            nx--;
            ny++;
            break;
        case 'n':
            nx++;
            ny++;
            break;

        default:
            break;
        }

        switch (k.key) {
        case maudit::keycode::up:
            ny--;
            break;
        case maudit::keycode::left:
            nx--;
            break;
        case maudit::keycode::right:
            nx++;
            break;
        case maudit::keycode::down:
            ny++;
            break;

        default:
            break;
        }            

        std::cout << "PD " << k.letter << " " << (int)k.key << " : " 
                  << px << "," << py << " " << nx << "," << ny << std::endl;

        if (!state.neigh.linked(neighbors::pt(px, py), neighbors::pt(nx, ny))) {

            std::cout << "Not linked" << std::endl;
            pstate = Player::MAIN;
            return;
        }

        if (pstate & Player::DIGGING) {

            std::cout << "Dig ok" << std::endl;

            if (state.grid.is_walk(nx, ny)) {
                state.render.do_message("There is nothing to dig there.");

            } else {
                state.render.do_message("You start digging.");
                p.digging = true;
                p.dig_x = nx;
                p.dig_y = ny;
                ++ticks;
            }

            pstate = Player::MAIN;
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

            if (p.state & Player::FIRED) {

                if (p.state & Player::THROWING) {
                    end_throw_item(p, p.inv.selected_slot, p.look.x, p.look.y, state);

                } else if (p.state & Player::BLASTING) {
                    end_blast_item(p, p.inv.selected_slot, p.look.x, p.look.y, state);
                }

                ++ticks;
                p.state = Player::MAIN;
            }

            return;
        }

        if (p.state & Player::PICK_DIRECTION) {

            std::cout << "PICK DIRECTION" << std::endl;
            handle_input_pick_direction(p.state, p.px, p.py, ticks, state, k);
            return;
        }

        if (state.window_stack.empty()) {
            handle_input_main(state, ticks, done, dead, regen, k);
            return;
        }

        switch ((screens_t)state.window_stack.back().type) {

        case screens_t::messages:
        case screens_t::help:
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

        case screens_t::spells:
            handle_input_spells(state, ticks, k);
            break;
        }
    }
};


void client_mainloop(int client_fd, bool singleplayer) {

    try {

        maudit::client_socket client(client_fd);

        typedef maudit::screen<maudit::client_socket> screen_t;

        std::cout << "Making screen..." << std::endl;
        screen_t screen(client);

        mainloop::Main<Game, screen_t> main(screen);

        std::cout << "Starting mainloop..." << std::endl;
        main.mainloop(singleplayer, ::time(NULL));

    } catch (std::exception& e) {
        std::cout << "Caught error: " << e.what() << std::endl;

    } catch (...) {
    }
}


int main(int argc, char** argv) {

    maudit::server_socket server("0.0.0.0", 20020);

    init_statics();

    bool singleplayer = false;

    if (argc > 1 && (std::string(argv[1]) == "-s" ||
                     std::string(argv[1]) == "--singleplayer")) {
        singleplayer = true;
    }

    if (singleplayer) {
        int client = server.accept();
        client_mainloop(client, true);

    } else {

        while (1) {

            std::cout << "Accepting..." << std::endl;
            int client = server.accept();

            std::cout << "Making thread..." << std::endl;
            std::thread thr(client_mainloop, client, false);
            thr.detach();
        }
    }

    return 0;
}
