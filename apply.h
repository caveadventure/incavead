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


#endif
