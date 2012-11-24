#ifndef __LOOK_SCREENS_H
#define __LOOK_SCREENS_H


inline void center_draw_text(grender::Grid& render, unsigned int x, unsigned int y, const std::string& t) {

    int _x = x;
    unsigned int x1 = std::max(0, _x-(int)t.size()/2);
    render.draw_text(x1, y+1, t, maudit::color::bright_white, maudit::color::dim_blue);
}

inline void look_move(Player::look_t& look, mainloop::GameState& state, int dx, int dy) {

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

inline void look_cycle(unsigned int& pstate, Player::look_t& look, unsigned int px, unsigned int py,
                       mainloop::GameState& state) {

    (look.target)++;

    int n = 0;

    for (const auto& i : state.monsters.mons) {
        if (!state.render.is_in_fov(i.first.first, i.first.second))
            continue;

        if (n == look.target) {
            look.x = i.first.first;
            look.y = i.first.second;
            return;
        }

        ++n;
    }

    for (const auto& i : state.items.stuff) {
        if (!state.render.is_in_fov(i.first.first, i.first.second))
            continue;

        if (n == look.target) {
            look.x = i.first.first;
            look.y = i.first.second;
            return;
        }

        ++n;
    }

    look.target = -1;
    look.x = px;
    look.y = py;

    if (n > 0) {
        look_cycle(pstate, look, px, py, state);
    }
}

inline void handle_input_looking(unsigned int& pstate, Player::look_t& look, unsigned int px, unsigned int py,
                                 mainloop::GameState& state, maudit::keypress k) {

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

        state.render.draw_line(px, py, look.x, look.y, true, 
                               maudit::color::dim_red, maudit::color::bright_white,
                               [&](unsigned int x, unsigned int y) {

                                   double dist = distance(px, py, x, y);

                                   if (!state.grid.is_walk(x, y) || 
                                       !state.render.is_in_fov(x, y) ||
                                       monc > 0 ||
                                       dist < look.rangemin ||
                                       dist > look.rangemax) {

                                       return false;
                                   }

                                   monsters::Monster tmp;
                                   if (state.monsters.get(x, y, tmp)) {
                                       monc++;
                                   }

                                   look.x = x;
                                   look.y = y;
                                   return true;
                               });
    }


    std::string msg;
    monsters::Monster mon;
    items::Item itm;

    unsigned int x = look.x;
    unsigned int y = look.y;
    size_t n = state.items.stack_size(x, y);

    if (!state.render.is_in_fov(x, y)) {

    } else if (state.monsters.get(x, y, mon)) {
        msg = nlp::message(" %s", species().get(mon.tag));

    } else if (n > 1) {
        msg = nlp::message(" %d items", n);

    } else if (n == 1 && state.items.get(x, y, 0, itm)) {
            
        msg = nlp::message(" %s", nlp::count(), designs().get(itm.tag), itm.count);

    } else if (x == px && y == py) {
        msg = " This is you";
    }

    state.render.draw_text(look.x+1, look.y, msg, maudit::color::bright_white, maudit::color::dim_blue);
}

inline void start_look_target(unsigned int& pstate, Player::look_t& look, unsigned int px, unsigned int py,
                              mainloop::GameState& state, int rangemin, int rangemax) {

    pstate = (Player::LOOKING | Player::TARGET);
    look = Player::look_t(px, py);
    look.rangemin = rangemin;
    look.rangemax = rangemax;

    center_draw_text(state.render, px, py, 
                     "Use <TAB> or arrow keys to select target, '.' to fire");
}

inline void start_look_plain(unsigned int& pstate, Player::look_t& look, unsigned int px, unsigned int py,
                             mainloop::GameState& state) {

    pstate = Player::LOOKING;
    look = Player::look_t(px, py);

    center_draw_text(state.render, px, py, 
                     "Use arrow keys to look around; <TAB> to cycle targets");
}

inline void start_look_cycle(unsigned int& pstate, Player::look_t& look, unsigned int px, unsigned int py,
                             mainloop::GameState& state, maudit::keypress k) {

    pstate = Player::LOOKING;
    look = Player::look_t(px, py);
        
    handle_input_looking(pstate, look, px, py, state, k);
}

#endif
