#ifndef __INVENTORY_H
#define __INVENTORY_H

struct inventory_t {

    std::unordered_map<std::string, items::Item> stuff;

    std::string selected_slot;
    unsigned int selected_floor_item;

    struct slot_t {
        std::string slot;
        std::string name;
        char letter;
    };

    std::map<std::string, slot_t> slots;
    std::map<char, std::string> slot_keys;

    inventory_t() {
        make_slot(slot_t{"w",  " Weapon", 'a'});
        make_slot(slot_t{"s",  " Shield", 'b'});
        make_slot(slot_t{"a",  " Armour", 'c'});
        make_slot(slot_t{"f",  " Edible", 'd'});
        make_slot(slot_t{"p",  " Potion", 'e'});
        make_slot(slot_t{"t",  "Missile", 'f'});
        make_slot(slot_t{"r1", "   Ring", 'g'});
        make_slot(slot_t{"m1", "Magical", 'h'});
    }

    void make_slot(const slot_t& s) {
        slots[s.slot] = s;
        slot_keys[s.letter] = s.slot;
    }

    bool get(const std::string& slot, items::Item& ret) const {
        auto i = stuff.find(slot);

        if (i == stuff.end())
            return false;

        ret = i->second;
        return true;
    }

    bool valid(const std::string& slot) const {

        if (stuff.count(slot) == 0) 
            return false;

        return true;
    }

    bool take(const std::string& slot, items::Item& ret, unsigned int count = 0) {
        auto i = stuff.find(slot);

        if (i == stuff.end())
            return false;

        ret = i->second;

        if (count == 0) {
            stuff.erase(i);

        } else {
            unsigned int n = std::min(i->second.count, count);
            ret.count = n;
            i->second.count -= n;

            if (i->second.count == 0) {
                stuff.erase(i);
            }
        }

        return true;
    }

    bool place(const std::string& slot, const items::Item& i, items::Item& old) {

        auto j = stuff.find(slot);

        if (j == stuff.end()) {
            stuff[slot] = i;
            return false;
        }

        items::Item& o = j->second;

        const Design& d = designs().get(o.tag);

        if (o.tag == i.tag) {

            if (o.count < d.stackrange) {
            
                unsigned int n = std::min(i.count, d.stackrange - o.count);

                o.count += n;

                if (n == i.count) {
                    return false;

                } else {
                    old = i;
                    old.count -= n;
                    return true;
                }

            } else {
                old = i;
                return true;
            }
        }

        old = o;
        o = i;
        return true;
    }

    bool inv_to_floor(const std::string& slot, unsigned int x, unsigned int y, items::Items& items, 
                      grender::Grid& grid) {

        items::Item tmp;

        if (!take(slot, tmp))
            return false;

        items.place(x, y, tmp, grid);
        return true;
    }

    bool floor_to_inv(unsigned int x, unsigned int y, unsigned int z, items::Items& items, 
                      grender::Grid& render, items::Item& itmp) {

        items::Item ftmp;

        if (!items.take(x, y, z, ftmp, render))
            return false;

        const std::string& slot = designs().get(ftmp.tag).slot;

        if (slots.count(slot) == 0)
            return false;

        if (place(slot, ftmp, itmp)) {
            items.place(x, y, itmp, render);
        }

        return true;
    }

    /*
    template <typename T>
    T get_inv_sum(T Design::* ptr) {
        T ret{};

        for (const auto& i : stuff) {
            const Design& dp = designs().get(i.second.tag);

            ret += (dp.*ptr) * i.second.count;
        }

        return ret;
    }

    double get_attack() {
        return get_inv_sum(&Design::attack);
    }
    */

    void get_attack(damage::attacks_t& out) {

        for (const auto& i : stuff) {
            const Design& dp = designs().get(i.second.tag);

            // HACK
            if (!dp.melee)
                continue;

            out.add(dp.attacks);
        }
    }

    void get_defense(damage::defenses_t& out) {

        for (const auto& i : stuff) {
            const Design& dp = designs().get(i.second.tag);

            for (unsigned int j = 0; j < i.second.count; ++j) {
                out.add(dp.defenses);
            }
        }
    }
    
};

#endif
