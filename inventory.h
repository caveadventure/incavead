#ifndef __INVENTORY_H
#define __INVENTORY_H

struct inventory_t {

    std::unordered_map<tag_t, items::Item> stuff;

    tag_t selected_slot;
    unsigned int selected_floor_item;

    struct slot_t {
        tag_t slot;
        std::string label;
        std::string name;
        char letter;
    };

    std::map<tag_t, slot_t> slots;
    std::map<char, tag_t> slot_keys;

    inventory_t() {

        for (const auto& s : constants().slots) {
            make_slot(slot_t{s.slot, s.label, s.name, s.letter});
        }
    }

    void make_slot(const slot_t& s) {
        slots[s.slot] = s;

        // HACK
        if (s.letter != ' ') {
            slot_keys[s.letter] = s.slot;
        }
    }

    bool get(tag_t slot, items::Item& ret) const {
        auto i = stuff.find(slot);

        if (i == stuff.end())
            return false;

        ret = i->second;
        return true;
    }

    bool valid(tag_t slot) const {

        if (stuff.count(slot) == 0) 
            return false;

        return true;
    }

    bool take(tag_t slot, items::Item& ret, unsigned int count = 0) {
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

    bool place(tag_t slot, const items::Item& i, items::Item& old) {

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

                if (d.stackrange == 0) {
                    old = o;
                    o = i;
                } else {
                    old = i;
                }

                return true;
            }
        }

        old = o;
        o = i;
        return true;
    }

    bool inv_to_floor(tag_t slot, unsigned int x, unsigned int y, items::Items& items, 
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

        tag_t slot = designs().get(ftmp.tag).slot;

        if (slots.count(slot) == 0)
            return false;

        if (place(slot, ftmp, itmp)) {
            items.place(x, y, itmp, render);
        }

        return true;
    }


    ///
    ///
    ///


    std::vector<Design::spell_t> spells() const {

        std::vector<Design::spell_t> ret;
        bool is_ok = false;

        for (const auto& i : stuff) {
            const Design& dp = designs().get(i.second.tag);

            ret.insert(ret.end(), dp.spells.begin(), dp.spells.end());

            if (dp.flags.enable_spells)
                is_ok = true;
        }

        if (!is_ok) {
            ret.clear();
        }

        return ret;
    }

    std::vector<uint32_t> random_spells() const {

        std::vector<uint32_t> ret;

        for (const auto& i : stuff) {
            const Design& dp = designs().get(i.second.tag);

            if (dp.flags.random_spell)
                ret.push_back(i.second.count);
        }

        return ret;
    }

    void get_attack(damage::attacks_t& out) const {

        for (const auto& i : stuff) {
            const Design& dp = designs().get(i.second.tag);

            // HACK
            if (!dp.melee)
                continue;

            out.add(dp.attacks);
        }
    }

    void get_defense(damage::defenses_t& out) const {

        for (const auto& i : stuff) {
            const Design& dp = designs().get(i.second.tag);

            unsigned int c = (dp.count_is_only_one ? 1 : i.second.count);

            for (unsigned int j = 0; j < c; ++j) {
                out.add(dp.defenses);
            }
        }
    }

    unsigned int get_lightradius() const {
        unsigned int ret = 0;

        for (const auto& i : stuff) {
            const Design& dp = designs().get(i.second.tag);

            unsigned int c = (dp.count_is_only_one ? 1 : i.second.count);

            ret += (dp.lightradius * c);
        }

        return ret;
    }


    double get_digging() const {
        double ret = 0;

        for (const auto& i : stuff) {
            const Design& dp = designs().get(i.second.tag);
            ret += dp.digging;
        }

        return ret;
    }

    double get_worth() const {
        double ret = 0;

        for (const auto& i : stuff) {
            const Design& dp = designs().get(i.second.tag);

            unsigned int c = (dp.count_is_only_one ? 1 : i.second.count);

            ret += (dp.worth * c);
        }

        return ret;
    }

    void get_turn_coeffs(double moon_angle, double& inc_luck, double& inc_hunger, double& inc_shield) const {

        inc_luck = 0;
        inc_hunger = 0;
        inc_shield = 0;

        double hunger_coeff = 0;

        for (const auto& i : stuff) {
            const Design& dp = designs().get(i.second.tag);

            for (const auto& l : dp.luck) {
                inc_luck = std::max(inc_luck, gaussian_function(l.height, l.mean, l.deviation, moon_angle));
            }

            // Hack, 'count_is_only_one' does not apply.
            inc_hunger += (dp.hunger * i.second.count);

            hunger_coeff = std::max(hunger_coeff, dp.other_hunger_multiplier);

            inc_shield += dp.shield;
        }

        if (hunger_coeff > 1) {
            inc_hunger *= hunger_coeff;
        }
    }

};

namespace serialize {

template <>
struct reader<inventory_t> {
    void read(Source& s, inventory_t& t) {
        serialize::read(s, t.stuff);
        serialize::read(s, t.selected_slot);
        serialize::read(s, t.selected_floor_item);
    }
};

template <>
struct writer<inventory_t> {
    void write(Sink& s, const inventory_t& t) {
        serialize::write(s, t.stuff);
        serialize::write(s, t.selected_slot);
        serialize::write(s, t.selected_floor_item);
    }
};

}

#endif
