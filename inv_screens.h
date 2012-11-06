#ifndef __INV_SCREENS_H
#define __INV_SCREENS_H



inline std::string select_inv_item(inventory_t& inv, const std::string& slot) {
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


inline std::string show_inventory(inventory_t& inv, unsigned int level, int worldz, 
                                  items::Items& items, unsigned int px, unsigned int py) {

    std::string m;

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

        m += nlp::message("   %s: \2%c\1) %S\n", 
                          slot.second.name,
                          slot.second.letter,
                          nlp::count(), d, tmp.count);
    }

    m += nlp::message("\n"
                      "\2Floor items:\n");

    size_t nz = items.stack_size(px, py);
    char letter = '1';

    for (size_t z = 0; z < nz; ++z) {

        items::Item tmp;

        if (!items.get(px, py, z, tmp))
            throw std::runtime_error("sanity error");

        const Design& d = designs().get(tmp.tag);

        m += nlp::message("           \2%c\1) %S\n",
                          letter,
                          nlp::count(), d, tmp.count);
        ++letter;
    }

    return m;
}


#endif
