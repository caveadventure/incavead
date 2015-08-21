#ifndef __GAME_RENDERING_H
#define __GAME_RENDERING_H


void Game::make_screen(mainloop::screen_params_t& sp, GameState& state) {

    sp.w = GRID_W;
    sp.h = GRID_H;
    sp.w2 = sp.w;
    sp.h2 = sp.h;

    auto& themes = state.render.ui_symbol_themes;

    for (const auto& i : constants().ui_symbols) {
        themes.push_back(i[n_skin]);
    }

    state.render.set_ui_symbol();
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
        state.render.set_is_lightsource(x, y, 1, t.is_lightsource);

    } else {
        state.render.unset_skin(x, y, 1);
        state.render.set_is_viewblock(x, y, 1, false);
        state.render.set_is_walkblock(x, y, 1, false);
        state.render.set_is_lit(x, y, 1, false);
        state.render.set_is_lightsource(x, y, 1, false);
    }

    // //

    items::Item item;

    if (state.items.get(x, y, 0, item)) {

        const Design& d = designs().get(item.tag);
        state.render.set_skin(x, y, 4, d.skin[n_skin]);
        state.render.set_is_lit(x, y, 4, d.is_lit);

    } else {
        state.render.unset_skin(x, y, 4);
        state.render.set_is_lit(x, y, 4, false);
    }

    // //

    if (x == p.px && y == p.py) {

        tag_t polytag = p.polymorph.species;

        if (!polytag.null()) {
            s = species().get(polytag).skin[n_skin];

        } else {
            s = constants().player_skin[n_skin];
        }

        state.render.set_skin(x, y, 5, s);

    } else {

        monsters::Monster& mon = state.monsters.get(x, y);

        if (!mon.null() && !mon.hidden) {

            const Species& s = species().get(mon.tag);

            auto skin = s.skin[n_skin];

            if (!mon.ally.null()) {
                skin.underline = true;
            }

            state.render.set_skin(x, y, 5, skin);
            state.render.set_is_walkblock(x, y, 5, true);
            
        } else {
            state.render.unset_skin(x, y, 5);
            state.render.set_is_walkblock(x, y, 5, false);
        }
    }

    state.render.validate(x, y);
}


void drawing_context_center_at(mainloop::drawing_context_t& ctx, unsigned int x, unsigned int y) {
        
    unsigned int grid_x = ctx.view_w / 4;
    unsigned int grid_y = ctx.view_h / 4;

    if (!ctx.do_center_view && grid_x > 1) {
        ctx.voff_off_x = -(x % grid_x) + (grid_x / 2);
    } else {
        ctx.voff_off_x = 0;
    }

    if (!ctx.do_center_view && grid_y > 1) {
        ctx.voff_off_y = -(y % grid_y) + (grid_y / 2);
    } else {
        ctx.voff_off_y = 0;
    }

    ctx.centerx = x;
    ctx.centery = y;
}

unsigned int get_lightradius(const Player& p, const GameState& state) {

    int r = -1;

    features::Feature feat;
    if (state.features.get(p.px, p.py, feat)) {

        r = terrain().get(feat.tag).view_radius;
    }

    if (r < 0) {
        const Levelskin& ls = levelskins().get(p.worldz);

        r = std::min(ls.lightradius_max, ls.lightradius + p.get_lightradius());
    }

    if (p.blind > 0) {
        r = std::max(1, r - static_cast<int>(p.blind / constants().blindturns_to_radius) - 1);
    }

    return r;
}

void Game::drawing_context(mainloop::drawing_context_t& ctx, const GameState& state) {

    ctx.px = p.px;
    ctx.py = p.py;
    ctx.lightradius = get_lightradius(p, state);

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

void draw_one_stat(GameState& state, tag_t s) {

    const Stat& st = stats().get(s);
    double val = p.stats.gets(s);

    if (st.hidden && val <= st.min)
        return;

    double v;

    if (st.progressbar) {
        v = 6.0 * (val - st.min) / (st.max - st.min);

    } else {
        v = 3.0 * (2 * val - st.max - st.min) / (st.max - st.min);
    }

    int vp = std::lround(v);

    const auto& zs = st.label;

    if (st.progressbar) {
        state.render.push_hud_line(vp, zs.label, zs.lskin[n_skin], zs.pskin[n_skin]);

    } else {
        state.render.push_hud_line(vp, zs.label, zs.lskin[n_skin], zs.pskin[n_skin], zs.nskin[n_skin]);
    }
}

void draw_one_count(GameState& state, tag_t s) {

    const Stat& st = stats().get(s);
    double val = p.stats.getc(s);

    if (st.hidden && val == 0)
        return;

    unsigned int v = (6u * s.val) / s.max;

    const auto& zs = st.label;

    state.render.push_hud_line(vp, zs.label, zs.lskin[n_skin], (state.ticks & 1 ? zs.pskin[n_skin] : zs.nskin[n_skin]));
}

void Game::draw_hud(GameState& state) {

    const auto& hso = constants().hud_stats_order;
    const auto& hco = constants().hud_counts_order;

    for (const tag_t& i : hso) {
        draw_one_stat(state, i);
    }

    for (const tag_t& i : hco) {
        draw_one_count(state, i);
    }

    if (p.digging) {

        double q = state.grid._get(p.dig.x, p.dig.y);

        q = ((q + 10) / 3.0) + 1.0;
        q = std::max(1.0, std::min(q, 6.0));

        state.render.push_hud_line("Tunnel", maudit::color::dim_green,
                                   q,
                                   '+', 
                                   (state.ticks & 1 ? maudit::color::bright_blue : maudit::color::dim_blue));
    }

    if (p.rest > 0) {
        state.render.push_hud_line("Resting", maudit::color::dim_green,
                                   std::min(p.rest / 16 + 1, (unsigned int)6), 
                                   '+', 
                                   (state.ticks & 1 ? maudit::color::dim_green : maudit::color::bright_black));
    }
}


#endif
