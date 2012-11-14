#ifndef __APPLY_H
#define __APPLY_H


inline bool apply_item(Player& p, const std::string& slot, grender::Grid& render) {

    items::Item tmp;
        
    if (!p.inv.take(slot, tmp, 1))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (!d.usable) 
        return false;

    if (d.heal > 0) {

        p.health.inc(d.heal);
        render.do_message(nlp::message("You feel better. %d %d", d.heal, p.health.val));
        return true;
    } 

    return false;
}

inline bool start_throw_item(Player& p, const std::string& slot, mainloop::GameState& state) {

    items::Item tmp;
    if (!p.inv.get(slot, tmp))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (d.throwrange == 0)
        return false;
    
    start_look_target(p.state, p.look, p.px, p.py, state, 0, d.throwrange);
    
    return true;
}

inline bool end_cloud_item(Player& p, const std::string& slot, unsigned int lx, unsigned int ly, 
                           mainloop::GameState& state) {

    items::Item tmp;
        
    if (!p.inv.take(slot, tmp, 1))
        return false;

    const Design& d = designs().get(tmp.tag);

    if (distance(p.px, p.py, lx, ly) > d.throwrange) {
        std::cout << "OOPS " << v << " " << d.throwrange << std::endl;
        return false;
    }

    state.render.draw_circle(lx, ly, d.cloudradius, true, d.skin.fore, maudit::color::bright_black,
                             [&](unsigned int _x, unsigned int _y) {
                                     
                                 monsters::Monster mon;
                                 if (state.monsters.get(_x, _y, mon)) {

                                     attack(p, d.attacks, d.level, state, mon, true);
                                 }
                             });

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

#endif
