#ifndef __GAME_RENDERING_H
#define __GAME_RENDERING_H


void Game::make_screen(mainloop::screen_params_t& sp, GameState& state) {

    sp.w = GRID_W;
    sp.h = GRID_H;
    sp.w2 = sp.w;
    sp.h2 = sp.h;

    state.render.ui_symbol = constants().ui_symbols[n_skin];
}

void Game::set_skin(GameState& state, unsigned int x, unsigned int y) {

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
                s = lev.deep_water[n_skin];
            } else {
                s = lev.shallow_water[n_skin];
            }

        } else {

            if (z <= -8) {
                s = lev.floor1[n_skin];
            } else if (z <= -7) {
                s = lev.floor2[n_skin];
            } else if (z <= -6) {
                s = lev.floor3[n_skin];
            } else if (z <= -5) {
                s = lev.floor4[n_skin];
            } else if (z <= -4) {
                s = lev.floor5[n_skin];
            } else if (z <= -3) {
                s = lev.floor6[n_skin];
            } else if (z <= -2) {
                s = lev.floor7[n_skin];
            } else {
                s = lev.floor8[n_skin];
            }
        }

    } else {
        if (water) {
            s = lev.water_wall[n_skin];
        } else {
            s = lev.wall[n_skin];
        }
    }

    state.render.set_skin(x, y, 0, s);

    // //

    features::Feature feat;

    if (state.features.get(x, y, feat)) {

        const Terrain& t = terrain().get(feat.tag);
        state.render.set_skin(x, y, 1, t.skin[n_skin]);
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
        state.render.set_skin(x, y, 2, d.skin[n_skin]);
        state.render.set_is_lit(x, y, 2, d.is_lit);

    } else {
        state.render.unset_skin(x, y, 2);
        state.render.set_is_lit(x, y, 2, false);
    }

    // //

    monsters::Monster mon;

    if (x == p.px && y == p.py) {

        s = constants().player_skin[n_skin];
        state.render.set_skin(x, y, 5, s);

    } else if (state.monsters.get(x, y, mon)) {

        const Species& s = species().get(mon.tag);
        state.render.set_skin(x, y, 5, s.skin[n_skin]);
        state.render.set_is_walkblock(x, y, 5, true);

    } else {
        state.render.unset_skin(x, y, 5);
        state.render.set_is_walkblock(x, y, 5, false);
    }
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

unsigned int get_lightradius(const Player& p) {

    const Levelskin& ls = levelskins().get(p.worldz);

    unsigned int r = std::min(ls.lightradius_max, ls.lightradius + p.inv.get_lightradius());

    if (p.blind > 0) {
        r = std::max(0, (int)r - static_cast<int>(p.blind / constants().blindturns_to_radius) + 1);
    }

    return r;
}

void Game::drawing_context(mainloop::drawing_context_t& ctx) {

    ctx.px = p.px;
    ctx.py = p.py;
    ctx.lightradius = get_lightradius(p);

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

void draw_one_stat(GameState& state, const stat_t& s, const std::string& name) {

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

void Game::draw_hud(GameState& state, size_t ticks) {

    draw_one_stat(state, p.health, "Health");
    draw_one_stat(state, p.food,   "Food");
    draw_one_stat(state, p.karma,  "Karma");

    if (p.luck.val > 0.1 || p.luck.val < -0.1) {
        draw_one_stat(state, p.luck, "Luck");
    }

    if (p.health.shield > 0) {
        state.render.push_hud_line("Shield", maudit::color::dim_green,
                                   std::min((unsigned int)(p.health.shield + 1), (unsigned int)6),
                                   '*',
                                   maudit::color::bright_yellow);
    }

    if (p.sleep > 0) {
        state.render.push_hud_line("Sleep", maudit::color::bright_red,
                                   std::min(p.sleep / 15 + 1, (unsigned int)6), 
                                   '+', 
                                   (ticks & 1 ? maudit::color::bright_red : maudit::color::dim_red));
    }

    if (p.blind > 0) {
        state.render.push_hud_line("Blind", maudit::color::bright_red,
                                   std::min(p.blind / constants().blindturns_to_radius + 1, (unsigned int)6), 
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
    }

    //state.render.push_hud_line("Foo", maudit::color::bright_yellow, 
    //                           4, '+', maudit::color::bright_green);
}


#endif
