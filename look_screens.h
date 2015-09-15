#ifndef __LOOK_SCREENS_H
#define __LOOK_SCREENS_H


inline void center_draw_text(grender::Grid& render, unsigned int x, unsigned int y, bool fullwidth, 
                             const std::string& t) {

    int halfstr = (int)t.size() / (fullwidth ? 4 : 2);

    int _x = x;
    unsigned int x1 = std::max(0, _x - halfstr);
    render.draw_text(x1, y+1, t, maudit::color::bright_white, maudit::color::dim_black);
}

inline void look_move(Player::look_state_t& look, GameState& state, int dx, int dy) {

    int nx = look.x + dx;
    int ny = look.y + dy;

    if (nx < 0 || ny < 0) 
        return;

    if (!state.neigh.linked(neighbors::pt(look.x, look.y), neighbors::pt(nx, ny))) {

        return;
    }
    
    look.x = nx;
    look.y = ny;
}

inline void look_cycle(unsigned int& pstate, Player::look_state_t& look, unsigned int px, unsigned int py,
                       GameState& state) {

    (look.target)++;

    std::vector<monsters::pt> points;
    size_t mons;
    size_t items;

    for (const auto& i : state.monsters.mgrid) {
        if (!state.render.is_in_fov(i.first.first, i.first.second))
            continue;

        points.push_back(i.first);
    }

    mons = points.size();

    for (const auto& i : state.items.stuff) {
        if (!state.render.is_in_fov(i.first.first, i.first.second))
            continue;

        points.push_back(i.first);
    }

    items = points.size();

    for (const auto& i : state.features.feats) {
        if (!state.render.is_in_fov(i.first.first, i.first.second))
            continue;

        const Terrain& t = terrain().get(i.second.tag);

        if (!t.important)
            continue;

        points.push_back(i.first);
    }

    auto distcmp = [px, py](const monsters::pt& a, const monsters::pt& b) {
        return distance(px, py, a.first, a.second) < distance(px, py, b.first, b.second);
    };

    if ((size_t)look.target >= points.size()) {

        look.target = -1;
        look.x = px;
        look.y = py;
        
        if (points.size() > 0) {
            look_cycle(pstate, look, px, py, state);
        }

        return;
    }

    std::sort(points.begin(), points.begin() + mons, distcmp);
    std::sort(points.begin() + mons, points.begin() + items, distcmp);
    std::sort(points.begin() + items, points.end(), distcmp);

    const auto& xy = points[look.target];

    look.x = xy.first;
    look.y = xy.second;
}

inline void handle_input_looking(unsigned int& pstate, Player::look_state_t& look, unsigned int px, unsigned int py,
                                 GameState& state, maudit::keypress k) {

    int stop = 0;

    switch (k.letter) {
    case 'h':
        look_move(look, state, -1, 0);
        break;
    case 'j':
        look_move(look, state, 0, 1);
        break;
    case 'k':
        look_move(look, state, 0, -1);
        break;
    case 'l':
        look_move(look, state, 1, 0);
        break;
    case 'y':
        look_move(look, state, -1, -1);
        break;
    case 'u':
        look_move(look, state, 1, -1);
        break;
    case 'b':
        look_move(look, state, -1, 1);
        break;
    case 'n':
        look_move(look, state, 1, 1);
        break;
            
    case '\t':
        look_cycle(pstate, look, px, py, state);
        break;

    case '.':
        if (pstate & Player::TARGET) {
            pstate |= Player::FIRED;
            pstate &= ~(Player::TARGET | Player::LOOKING);
            return;
        }

    default:
        ++stop;
        break;
    }

    switch (k.key) {
    case maudit::keycode::up:
        look_move(look, state, 0, -1);
        break;
    case maudit::keycode::left:
        look_move(look, state, -1, 0);
        break;
    case maudit::keycode::right:
        look_move(look, state, 1, 0);
        break;
    case maudit::keycode::down:
        look_move(look, state, 0, 1);
        break;

    default:
        ++stop;
        break;
    }

    if (stop > 1) {
        pstate = Player::MAIN;
        return;
    }


    if (pstate & Player::TARGET) {

        unsigned int monc = 0;

        state.render.draw_line(px, py, look.x, look.y, 
                               maudit::color::bright_white, maudit::color::dim_blue,
                               [&](unsigned int x, unsigned int y) {

                                   double dist = distance(px, py, x, y);

                                   if (!state.grid.is_walk(x, y) || 
                                       !state.render.is_in_fov(x, y) ||
                                       monc > 0 ||
                                       dist < look.rangemin ||
                                       dist > look.rangemax) {

                                       return false;
                                   }

                                   monsters::Monster& tmp = state.monsters.get(x, y);
                                   if (!tmp.null()) {
                                       monc++;
                                   }

                                   look.x = x;
                                   look.y = y;
                                   return true;
                               });
    }


    std::string msg;
    items::Item itm;
    features::Feature feat;

    unsigned int x = look.x;
    unsigned int y = look.y;
    size_t n = state.items.stack_size(x, y);

    bool ok = true;

    monsters::Monster& mon = state.monsters.get(x, y);

    if (!state.render.is_in_fov(x, y)) {

    } else if (!mon.null()) {

        const Species& s = species().get(mon.tag);

        std::vector<std::string> state;

        if (!mon.ally.null()) {
            state.push_back("ally"_map);
        }

        for (const auto& i : mon.stats.counts) {

            const Count& ct = counts().get(i.first);

            if (ct.status_msg.size() > 0)
                state.push_back(ct.status_msg);
        }

        double health = 1.0;

        for (const auto& i : mon.stats.stats) {

            const Stat& st = stats().get(i.first);

            if (st.status_min_msg.size() > 0 &&
                mon.stats.is_min(i.first)) {

                state.push_back(st.status_min_msg);
            }

            if (st.critical) {
                health = std::min(health, (i.second.val - st.min) / (st.max - st.min));
            }
        }

        if (s.flags.robot) {

            if (health < 0.1666) {
                state.push_back("badly damaged"_map);
            } else if (health < 0.5) {
                state.push_back("damaged"_map);
            } else if (health < 0.9) {
                state.push_back("slightly damaged"_map);
            }

        } else if (!s.flags.plant) {

            if (health < 0.1666) {
                state.push_back("badly wounded"_map);
            } else if (health < 0.5) {
                state.push_back("wounded"_map);
            } else if (health < 0.9) {
                state.push_back("lightly wounded"_map);
            }
        }

        if (state.empty()) {
            msg = nlp::message(" %s", species().get(mon.tag));

        } else {
            std::string tmp;

            for (const std::string& i : state) {

                if (!tmp.empty())
                    tmp += ", ";

                tmp += i;
            }

            msg = nlp::message(" %s (%s)", s, tmp);
        }

    } else if (n > 1) {
        msg = nlp::message(" %d items"_m, n);

    } else if (n == 1 && state.items.get(x, y, 0, itm)) {
            
        msg = nlp::message(" %s", nlp::count(), designs().get(itm.tag), itm.count);

    } else if (state.features.get(x, y, feat)) {

        const Terrain& ter = terrain().get(feat.tag);

        if (ter.name.empty()) {
            ok = false;

        } else if (ter.descr.empty()) {
            msg = nlp::message(" %s", ter);

        } else {
            msg = nlp::message(" %s (%s)", ter, ter.descr);
        }            

    } else if (x == px && y == py) {
        msg = " This is you"_map;

    } else {
        ok = false;
    }

    if (!ok) {

        bool walk = state.grid.is_walk(x, y);
        bool water = state.grid.is_water(x, y);

        if (!walk) {
            msg = " rock"_map;
        } else if (water) {
            msg = " water"_map;
        } else {
            msg = " floor"_map;
        }
    }

    state.render.draw_text(look.x+1, look.y, msg, maudit::color::bright_white, maudit::color::dim_blue);
}

inline void start_look_target(unsigned int& pstate, Player::look_state_t& look, unsigned int px, unsigned int py,
                              GameState& state, int rangemin, int rangemax) {

    pstate = (Player::LOOKING | Player::TARGET);
    look = Player::look_state_t(px, py);
    look.rangemin = rangemin;
    look.rangemax = rangemax;

    //center_draw_text(state.render, px, py-3, state.fullwidth,
    //                 "Use <TAB> or arrow keys to select target, '.' to fire");

    state.render.do_message("Use <TAB> or arrow keys to select target, '.' to fire"_m, false, true);

    handle_input_looking(pstate, look, px, py, state, '\t');
}

inline void start_look_plain(unsigned int& pstate, Player::look_state_t& look, unsigned int px, unsigned int py,
                             GameState& state) {

    unsigned int x0 = px;
    unsigned int y0 = py;

    pstate = Player::LOOKING;
    look = Player::look_state_t(x0, y0);

    //center_draw_text(state.render, px, py-3, state.fullwidth,
    //                 "Use arrow keys to look around; <TAB> to cycle targets");

    state.render.do_message("Use arrow keys to look around; <TAB> to cycle targets"_m, false, true);
}

inline void start_look_cycle(unsigned int& pstate, Player::look_state_t& look, unsigned int px, unsigned int py,
                             GameState& state, maudit::keypress k) {

    pstate = Player::LOOKING;
    look = Player::look_state_t(px, py);
        
    handle_input_looking(pstate, look, px, py, state, k);
}

#endif
