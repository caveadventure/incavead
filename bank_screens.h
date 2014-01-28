#ifndef __BANK_SCREENS_H
#define __BANK_SCREENS_H


inline void purchase_protection(Player& p, GameState& state, double cost) {

    features::Feature feat;
    if (!state.features.get(p.px, p.py, feat)) {
        return;
    }

    const Terrain& t = terrain().get(feat.tag);

    double shield_bonus = t.banking.shield_bonus * cost;
    double money_curse = t.banking.money_curse * cost;

    if (shield_bonus <= 0)
        return;
                
    if (p.health.shield + shield_bonus < constants().health_shield_max) {
        p.health.shield += shield_bonus;
        state.render.do_message("Your body glows with a shiny gold aura.");

        ++(state.ticks);

    } else {
        double x = constants().health_shield_max - p.health.shield;
        double xcost = x / t.banking.shield_bonus;

        p.health.shield = constants().health_shield_max;
        money_curse = t.banking.money_curse * xcost;

        if (x > 0) {
            state.render.do_message("Your body glows with a shiny gold aura.");

            ++(state.ticks);
        }

        if (xcost < cost) {
            give_change(state, p.px, p.py, cost - xcost);
            state.render.do_message("Please keep the change.");
        }
    }

    if (money_curse > 0) {
        p.money_curse -= money_curse;
    }
}

inline std::string show_banking_menu(Player& p, GameState& state, const Terrain::banking_t& bank) {

    const auto& money = constants().money;

    if (money.empty()) {
        return "Sorry, money doesn't exist yet.";
    }

    const Design& zm = designs().get(*(money.begin()));

    double assets = 0;

    std::string msg = "\2Welcome.\n";

    items::Item vi;
    if (p.inv.take(zm.slot, vi)) {

        const Design& liq = designs().get(vi.tag);

        unsigned int count = (liq.count_is_only_one ? 1 : vi.count);

        if (money.count(vi.tag) != 0) {
            assets = zm.worth * count;

            msg += nlp::message("Your liquid assets: \2%d\1 $ZM.\n", assets);

        } else {

            assets = finance::supply().get_price(liq) * count * bank.buy_margin;

            if (assets < 0) {
                assets = 0;

                msg += nlp::message("You have no liquid assets. (Suspected countefeit goods: %s)\n", 
                                    nlp::count(), liq, vi.count);

            } else if (assets == 0) {
                msg += nlp::message("You have no liquid assets.\n");

            } else {
                msg += nlp::message("Your liquid assets: \2%d\1 $ZM. (Your %s)\n", 
                                    assets, nlp::count(), liq, vi.count);
            }
        }

    } else {
        msg += nlp::message("You have no liquid assets.\n");
    }
    
    msg += "\nPlease choose:\n\n";

    msg += "  \2w\1) Withdraw from an account.\n";

    if (assets > 0) {
        msg += "  \2d\1) Deposit to an account.\n";

        if (bank.shield_bonus > 0 &&
            p.health.shield < constants().health_shield_max) {

            msg += "  \2p\1) Purchase divine protection.\n";
        }

        if (bank.sell_margin > 0) {
            msg += "  \2i\1) Purchase an item.\n";
        }
    }

    return msg;
}


#endif
