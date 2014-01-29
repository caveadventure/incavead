#ifndef __BANK_SCREENS_H
#define __BANK_SCREENS_H


inline void purchase_protection(Player& p, GameState& state, double cost) {

    double shield_bonus = p.banking.shield_bonus * cost;
    double money_curse = p.banking.money_curse * cost;

    if (shield_bonus <= 0 || p.health.shield >= constants().health_shield_max)
        return;

    items::Item money;
    if (!p.inv.take(constants().money_slot, money))
        return;
                
    if (p.health.shield + shield_bonus < constants().health_shield_max) {
        p.health.shield += shield_bonus;
        state.render.do_message("Your body glows with a shiny gold aura.");

        ++(state.ticks);

    } else {
        double x = constants().health_shield_max - p.health.shield;
        double xcost = x / p.banking.shield_bonus;

        p.health.shield = constants().health_shield_max;
        money_curse = p.banking.money_curse * xcost;

        if (x > 0) {
            state.render.do_message("Your body glows with a shiny gold aura.");

            ++(state.ticks);
        }

        if (give_change(state, p.px, p.py, cost - xcost)) {
            state.render.do_message("Please keep the change.");
        }
    }

    if (money_curse > 0) {
        p.money_curse -= money_curse;
    }
}

inline void purchase_item(Player& p, GameState& state) {

    tag_t pitem = p.banking.item;

    if (p.banking.assets < p.banking.item_price || pitem.null())
        return;

    items::Item money;
    if (!p.inv.take(constants().money_slot, money))
        return;

    items::Item made(pitem, items::pt(p.px, p.py), 1);
    state.items.place(p.px, p.py, made, state.render);

    ++(state.ticks);

    if (give_change(state, p.px, p.py, p.banking.assets - p.banking.item_price)) {
        state.render.do_message("Please keep the change.");
    }

    if (constants().money.count(money.tag) == 0) {

        const Design& md = designs().get(money.tag);

        unsigned int count = (md.count_is_only_one ? 1 : money.count);

        finance::supply().purchase(money.tag, 0, count);
    }

    finance::supply().purchase(pitem, p.banking.item_price);
}

inline void account_deposit(Player& p, GameState& state, unsigned int account) {

    if (p.banking.assets < constants().min_money_value) {
        return;
    }

    items::Item money;
    if (!p.inv.take(constants().money_slot, money))
        return;

    double b = finance::supply().deposit(account, p.banking.assets);

    state.render.do_message(nlp::message("Thank you for your patronage. Your account balance: %f $ZM.", b));

    ++(state.ticks);
}

inline void account_withdraw(Player& p, GameState& state, unsigned int account) {

    double sum = finance::supply().withdraw(account);

    if (give_change(state, p.px, p.py, sum)) {
        state.render.do_message(nlp::message("%f $ZM withdrawn. Enjoy your newfound wealth.", sum));

    } else {
        state.render.do_message("This account is empty, sorry.");
    }

    ++(state.ticks);
}

inline bool handle_input_pincode(Player& p, GameState& state, maudit::keypress k) {

    if (k.letter >= '0' && k.letter <= '9') {

        if (p.input.s.size() < 3) {
            p.input.s += k.letter;
            state.window_stack.back().message += k.letter;
        }

        if (p.input.s.size() == 3) {
            return true;
        }

    } else if (k.letter == '\x7F' || k.letter == '\x08' || k.key == maudit::keycode::del) {

        if (p.input.s.size() > 0) {
            p.input.s.pop_back();
            state.window_stack.back().message.pop_back();
        }
    }

    return false;
}

inline bool handle_input_text(Player& p, GameState& state, maudit::keypress k) {

    if (k.letter >= ' ' && k.letter <= '~') {

        p.input.s += k.letter;
        state.window_stack.back().message += k.letter;

    } else if (k.letter == '\x7F' || k.letter == '\x08' || k.key == maudit::keycode::del) {

        if (p.input.s.size() > 0) {
            p.input.s.pop_back();
            state.window_stack.back().message.pop_back();
        }

    } else if (k.letter == '\n') {
        return true;
    }

    return false;
}

inline void show_banking_buy_item_menu(Player& p, GameState& state) {

    tag_t item = find_existing_item_search(state, p.input.s);

    if (item.null()) {

        state.window_stack.clear();
        state.push_window("No such item exists. Please try again.", screens_t::messages);
        return;
    }

    const Design& d = designs().get(item);

    unsigned int count = 1;

    double price = finance::supply().get_price(d) * p.banking.sell_margin;

    std::string msg;

    if (price < constants().min_money_value) {
        msg = nlp::message("\n"
                           "Sorry, but \3%s\1 is not currently for sale.",
                           nlp::count(), d, count);
        
    } else {
        msg = nlp::message("\n"
                           "Your assets: \2%f\1 $ZM.\n"
                           "Quote for \3%s\1: \2%f\1 $ZM.\n\n", 
                           p.banking.assets, nlp::count(), d, count, price);
    }

    if (p.banking.assets < price) {
        msg += "You cannot afford this item, sorry.";

        state.window_stack.clear();
        state.push_window(msg, screens_t::messages);

    } else {
        msg += "  \2y\1) Yes, I agree to buy this item.\n";

        p.banking.item = item;
        p.banking.item_price = price;

        state.push_window(msg, screens_t::bank_buy_confirm);
    }
}

inline void handle_input_banking_main(Player& p, GameState& state, maudit::keypress k) {

    switch (k.letter) {
    case 'w':
        p.input.s.clear();
        state.push_window("\2Input your account's PIN code (three digits)\1: \3", 
                          screens_t::bank_withdrawal);
        break;

    case 'd':
        if (p.banking.assets < constants().min_money_value) {
            state.window_stack.pop_back(); 
        } else {
            p.input.s.clear();
            state.push_window("\2Choose a PIN code for your account (three digits)\1: \3",
                              screens_t::bank_deposit);
        }
        break;

    case 'p':
        purchase_protection(p, state, p.banking.assets);
        state.window_stack.pop_back();
        break;

    case 'i':
        if (p.banking.assets < constants().min_money_value) {
            state.window_stack.pop_back(); 
        } else {
            p.input.s.clear();
            state.push_window("\2Buy what (enter the name)\1: \3", screens_t::bank_buy);
        }
        break;

    default:
        state.window_stack.pop_back();
        break;
    }
}

inline std::string show_banking_menu(Player& p, GameState& state, const Terrain::banking_t& bank) {

    const auto& money = constants().money;

    if (money.empty()) {
        return "Sorry, money doesn't exist yet.";
    }

    tag_t money_slot = constants().money_slot;

    p.banking.sell_margin = bank.sell_margin;
    p.banking.shield_bonus = bank.shield_bonus;
    p.banking.money_curse = bank.money_curse;

    double& assets = p.banking.assets;
    assets = 0;

    std::string msg = "\2Welcome.\n\n";

    items::Item vi;
    if (p.inv.get(money_slot, vi)) {

        const Design& liq = designs().get(vi.tag);

        unsigned int count = (liq.count_is_only_one ? 1 : vi.count);

        if (money.count(vi.tag) != 0) {
            assets = liq.worth * count;

            msg += nlp::message("Your liquid assets: \2%f\1 $ZM.\n", assets);

        } else {

            // Always assume that there is 1 more of the item than there really is;
            // this is to prevent the player from selling a gem to buy another gem of
            // the same type, only to sell it again at a higher price, thus creating 
            // infinite money.
            assets = finance::supply().get_price(liq, 1) * count * bank.buy_margin;

            if (assets < 0) {
                assets = 0;

                msg += nlp::message("You have no liquid assets. (Suspected countefeit goods: %s)\n", 
                                    nlp::count(), liq, vi.count);

            } else if (assets == 0) {
                msg += nlp::message("You have no liquid assets.\n");

            } else {
                msg += nlp::message("Your liquid assets: \2%f\1 $ZM. (%S)\n", 
                                    assets, nlp::count(), liq, vi.count);
            }
        }

    } else {
        msg += nlp::message("You have no liquid assets.\n");
    }
    
    msg += "\nPlease choose:\n\n";

    msg += "  \2w\1) Withdraw from an account.\n";

    if (assets >= constants().min_money_value) {
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

inline void handle_input_banking(Player& p, GameState& state, maudit::keypress k) {
    
    switch ((screens_t)state.window_stack.back().type) {

    case screens_t::bank_main:
        handle_input_banking_main(p, state, k);
        break;

    case screens_t::bank_withdrawal:
        if (handle_input_pincode(p, state, k)) {
            account_withdraw(p, state, std::stoul(p.input.s));
            state.window_stack.clear();
        }
        break;
            
    case screens_t::bank_deposit:
        if (handle_input_pincode(p, state, k)) {
            account_deposit(p, state, std::stoul(p.input.s));
            state.window_stack.clear();
        }
        break;

    case screens_t::bank_buy:
        if (handle_input_text(p, state, k)) {
            show_banking_buy_item_menu(p, state);
        }
        break;

    case screens_t::bank_buy_confirm:
        if (k.letter == 'y') {
            purchase_item(p, state);
        }
        state.window_stack.clear();
        break;

    default:
        break;
    }
}


#endif
