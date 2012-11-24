#ifndef __APPLY_H
#define __APPLY_H


inline bool apply_item(Player& p, const std::string& slot, grender::Grid& render) {

    items::Item tmp;
        
    if (!p.inv.take(slot, tmp, 1))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (!d.usable) 
        return false;

    bool ret = false;

    if (d.heal > 0) {

        p.health.inc(d.heal);
        render.do_message("You feel better.");
        ret = true;
    } 

    if (d.feed > 0) {

        p.food.inc(d.feed);
        render.do_message(nlp::message("You eat %s.", d));
        ret = true;
    } 

    return ret;
}


inline void blast_process_point(Player& p, mainloop::GameState& state, const Design& d,
                                unsigned int _x, unsigned int _y) {

    if (_x == p.px && _y == p.py) {

        damage::defenses_t defenses;
        p.inv.get_defense(defenses);

        defend(p, defenses, p.level, d, state);

    } else {

        monsters::Monster mon;
        if (state.monsters.get(_x, _y, mon)) {

            attack(p, d.attacks, d.level, state, mon, true);
        }
    }
}

inline bool end_blast_item(Player& p, const std::string& slot, unsigned int lx, unsigned int ly, 
                           mainloop::GameState& state) {

    items::Item tmp;
        
    if (!p.inv.take(slot, tmp, 1))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (distance(p.px, p.py, lx, ly) > d.blastrange) {
        std::cout << "OOPZ " << distance(p.px, p.py, lx, ly) << " " << d.blastrange 
                  << "   " << tmp.tag << " " << d.name << std::endl;
        return false;
    }

    if (d.blastradius == 0) {

        blast_process_point(p, state, d, lx, ly);

    } else {

        state.render.draw_circle(lx, ly, d.blastradius, true, d.skin.fore, maudit::color::bright_black,
                                 [&](unsigned int _x, unsigned int _y) {
                                 
                                     blast_process_point(p, state, d, _x, _y);
                                 });
    }

    return true;
}

inline bool start_blast_item(Player& p, const std::string& slot, mainloop::GameState& state, size_t& ticks) {

    items::Item tmp;
    if (!p.inv.get(slot, tmp))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (d.blastradius == 0)
        return false;

    if (d.blastrange > 0) {
        
        start_look_target(p.state, p.look, p.px, p.py, state, 0, d.blastrange);
        p.state |= Player::BLASTING;

    } else {

        if (!end_blast_item(p, slot, p.px, p.py, state)) 
            return false;

        ++ticks;
    }

    return true;
}


inline bool end_throw_item(Player& p, const std::string& slot, unsigned int lx, unsigned int ly,
                           mainloop::GameState& state) {

    items::Item tmp;
        
    if (!p.inv.take(slot, tmp, 1))
        return false;

    const Design& d = designs().get(tmp.tag);

    double v = distance(p.px, p.py, lx, ly);

    if (d.throwrange == 0 || v > d.throwrange) {
        std::cout << "OOPS " << v << " " << d.throwrange << std::endl;
        return false;
    }

    monsters::Monster mon;
    if (state.monsters.get(lx, ly, mon)) {
        std::cout << "!! attack" << std::endl;
            
        double v2 = std::max(0.0, (v-1) / d.throwrange);

        unsigned int lev = (1 - v2) * p.level;

        attack(p, d.attacks, lev, state, mon);
    }

    state.items.place(lx, ly, tmp, state.render);

    return true;
}

inline bool start_throw_item(Player& p, const std::string& slot, mainloop::GameState& state) {

    items::Item tmp;
    if (!p.inv.get(slot, tmp))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (d.throwrange == 0)
        return false;
    
    start_look_target(p.state, p.look, p.px, p.py, state, 0, d.throwrange);
    p.state |= Player::THROWING;

    return true;
}

inline bool take_item(unsigned int x, unsigned int y, unsigned int z, 
                      Player& p, mainloop::GameState& state, size_t& ticks) {

    items::Item disc;
        
    if (p.inv.floor_to_inv(x, y, z, state.items, state.render, disc)) {

        if (!disc.tag.empty()) {

            const Design& d = designs().get(disc.tag);

            // HACK
            state.render.do_message(nlp::message("You discard %s to make space.", nlp::count(), d, disc.count));
        }

        ticks++;
        return true;
    }

    return false;
}

#endif
