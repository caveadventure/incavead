#ifndef __INV_SCREENS2_H
#define __INV_SCREENS2_H


inline void handle_input_inventory(Player& p, mainloop::GameState& state,
                                   size_t& ticks, bool& done, bool& dead, bool& regen, 
                                   maudit::keypress k) {

    auto i = p.inv.slot_keys.find(k.letter);

    if (i != p.inv.slot_keys.end() &&
        p.inv.valid(i->second)) {
        
        state.push_window(select_inv_item(p.inv, i->second), screens_t::inv_item);
        return;
    }

    if (k.letter >= '1' && k.letter <= '9') {
        unsigned int i = k.letter - '1';

        if (i < state.items.stack_size(p.px, p.py)) {

            state.push_window(select_floor_item(p.inv, state.items, p.px, p.py, i), screens_t::floor_item);
            return;
        }
    }

    state.window_stack.pop_back();
}

inline void handle_input_inv_item(Player& p, mainloop::GameState& state,
                                  size_t& ticks, bool& done, bool& dead, bool& regen, 
                                  maudit::keypress k) {

    if (k.letter == 'd') {
        p.inv.inv_to_floor(p.inv.selected_slot, p.px, p.py, state.items, state.render);

        ticks++;
        state.window_stack.clear();
        return;

    } else if (k.letter == 'a' && apply_item(p, p.inv.selected_slot, state.render)) {

        ticks++;
        state.window_stack.clear();
        return;

    } else if (k.letter == 't' && start_throw_item(p, p.inv.selected_slot, state)) {

        state.window_stack.clear();
        return;

    } else if (k.letter == 'f' && start_blast_item(p, p.inv.selected_slot, state, ticks)) {

        state.window_stack.clear();
        return;
    }

    state.window_stack.pop_back();
}

inline void handle_input_floor_item(Player& p, mainloop::GameState& state,
                                    size_t& ticks, bool& done, bool& dead, bool& regen, 
                                    maudit::keypress k) {

    if (k.letter == 't') {

        if (take_item(p.px, p.py, p.inv.selected_floor_item, p, state, ticks)) {

            state.window_stack.clear();
            return;
        }
    }

    state.window_stack.pop_back();
}


#endif
