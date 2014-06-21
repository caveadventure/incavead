#ifndef __INV_SCREENS_H
#define __INV_SCREENS_H



inline std::string select_inv_item(inventory_t& inv, tag_t slot) {
    std::string window;
        
    items::Item tmp;

    if (!inv.get(slot, tmp))
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

    if (d.usable) {
        window += nlp::message("  \2a)\1 Apply or use this item.\n");
    }

    if (d.destructible) {
        window += nlp::message("  \2D)\1 Destroy this item.\n");
    }

    if (d.throwrange > 0) {
        window += nlp::message("  \2t)\1 Throw item.\n");
    }

    if (d.blast.radius > 0 || d.blast.range > 0 || d.cast_cloud.radius > 0) {
        window += nlp::message("  \2f)\1 Fire.\n");
    }

    if (d.digging > 0) {
        window += nlp::message("  \2D)\1 Tunnel into rock.\n");
    }

    inv.selected_slot = slot;

    return window;
}

inline std::string select_floor_item(inventory_t& inv, items::Items& items, 
                                     unsigned int px, unsigned int py, unsigned int z) {

    std::string window;

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

    if (inv.slots.count(d.slot) != 0) {
        window += "  \2t\1) Take.\n";
    }

    inv.selected_floor_item = z;

    return window;
}


inline std::string show_inventory(Player& p, const std::string& moon_phase, items::Items& items) {

    std::string m;

    std::string level_name = levelskins().get(p.worldz).name;

    if (p.worldx != 0 || p.worldy != 0) {
        static const std::string tunnels[3][3] = {
            { "due NW", "due W", "due SW" },
            { "due N", "", "due S" },
            { "due NE", "due E", "due SE" } };


        level_name += ", ";
        level_name += tunnels[p.worldx+1][p.worldy+1];
    }

    unsigned int plevel = p.get_level() + 1;

    std::string pad1(plevel < 10 ? "  " : " ");

    int dlevel = p.worldz + 1;

    std::string pad2(dlevel >= 10 ? " "  :
                     dlevel >=  0 ? "  " :
                     dlevel >= -9 ? " " : "");

    std::string poly = (p.polymorph.species.null() ? std::string() :
                        nlp::message("(in the form of \2%s\1)", species().get(p.polymorph.species)));

    m = nlp::message("\2Player stats:\n"
                     "  Character level:%s%d  %s\n"
                     "  Dungeon level:  %s%d  (%s)    (phase of the moon: %s)\n"
                     "\n"
                     "\2Inventory:\n",
                     pad1, plevel, poly, pad2, dlevel, level_name, moon_phase);

    for (const auto& slotk : p.inv.slot_keys) {

        items::Item tmp;

        if (!p.inv.get(slotk.second, tmp)) 
            continue;

        const auto& slot = p.inv.slots[slotk.second];

        const Design& d = designs().get(tmp.tag);

        m += nlp::message("   %s: \2%c\1) %S\n", 
                          slot.label,
                          slot.letter,
                          nlp::count(), d, tmp.count);
    }

    // HACK
    for (const auto& ii : p.inv.stuff) {

        const auto& slot = p.inv.slots[ii.first];

        if (slot.letter != ' ')
            continue;

        const Design& d = designs().get(ii.second.tag);

        m += nlp::message("   %s:    \1%S\n", 
                          slot.label, nlp::count(), d, ii.second.count);
    }
        

    m += nlp::message("\n"
                      "\2Floor items:\n");

    size_t nz = items.stack_size(p.px, p.py);
    char letter = '1';

    for (size_t z = 0; z < nz; ++z) {

        items::Item tmp;

        if (!items.get(p.px, p.py, z, tmp))
            throw std::runtime_error("sanity error");

        const Design& d = designs().get(tmp.tag);

        m += nlp::message("            \2%c\1) %S\n",
                          letter,
                          nlp::count(), d, tmp.count);
        ++letter;

        if (letter == '9') {
            m += "               \1(There are more items here in the pile.)\n";
            break;
        }
    }

    return m;
}


#endif
