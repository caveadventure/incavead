#ifndef __GAME_UI_H
#define __GAME_UI_H

std::string show_victory() {

    std::string ret = "\n\2Status of the \3One Ring:\1\n\n";

    std::vector<uniques::key_t> levels;
    time_t placetime;

    uniques::uniques().locate(placetime, levels);

    time_t now = ::time(NULL);
    time_t tdiff = now - placetime;
    unsigned int timeout = constants().uniques_timeout;

    if (levels.empty()) {
    
        if (placetime == 0 || tdiff >= (time_t)timeout) {
            ret += "Ready to regenerate on dungeon level \21\1.";

        } else {
            ret += "Destroyed or in possession.\n";
            ret += nlp::message("\2%d\1 minutes left until regeneration.", (timeout - tdiff) / 60);
        }

    } else {

        const auto& wk = levels.back();

        static const std::string tunnels[3][3] = {
            { "follow a tunnel due north-west",
              "follow a tunnel due west", 
              "follow a tunnel due south-west" },
            { "follow a tunnel due north",
              "main branch", 
              "follow a tunnel due south" },
            { "follow a tunnel due north-east",
              "follow a tunnel due east", 
              "follow a tunnel due south-east" } };

        if (wk.worldy < -1 || wk.worldy > 1 || wk.worldx < -1 || wk.worldy > 1)
            throw std::runtime_error("Sanity error in worldkey");

        tdiff /= 60;
        std::string units = "minutes";

        if (tdiff > 1440) {
            tdiff /= 1440;
            units = "days";

        } else if (tdiff > 60) {
            tdiff /= 60;
            units = "hours";
        }

        ret += nlp::message("Found somewhere on dungeon level \2%d\1 (\2%s\1).\n", 
                            wk.worldz+1, tunnels[wk.worldx+1][wk.worldy+1]);

        ret += nlp::message("It has been there for \2%d %s\1.\n", tdiff, units);
    }

    return ret;
}

std::string show_spells(const std::vector<Terrain::spell_t>& p_spells, 
                        const std::vector<Design::spell_t>& i_spells,
                        const std::vector<uint32_t>& r_spells) {

    std::string m;

    m = "\2Your arcane powers:\n\n";

    char z = 'a';
    for (const auto& sp : p_spells) {

        m += nlp::message("   \2%c\1) %S\n", z, sp);
        ++z;
    }

    for (const auto& sp : i_spells) {

        m += nlp::message("   \2%c\1) %S\n", z, sp);
        ++z;
    }

    for (const auto& rp : r_spells) {

        m += nlp::message("   \2%c\1) Labeled '%s'\n", z, rcode::magick_encode(rp));
        ++z;
    }
        
    return m;
}

void handle_input_spells(const Player& p, GameState& state, size_t& ticks, maudit::keypress k) {

    int _z = k.letter - 'a';

    if (_z < 0) {
        state.window_stack.pop_back();
        return;
    }

    size_t z = (size_t)_z;

    const auto& p_spells = p.spells;
    const auto& i_spells = p.inv.spells();
    const auto& r_spells = p.inv.random_spells();

    if (z < p_spells.size()) {

        const auto& sp = p_spells[z];

        seed_celauto(state, p.px, p.py, sp.ca_tag);        
        ++ticks;

    } else if (z < p_spells.size() + i_spells.size()) {

        const auto& sp = i_spells[z - p_spells.size()];

        seed_celauto(state, p.px, p.py, sp.ca_tag);
        ++ticks;

    } else if (z < p_spells.size() + i_spells.size() + r_spells.size()) {

        uint32_t rspell = r_spells[z - p_spells.size() - i_spells.size()];

        cast_random_spell(p, rspell, state);
        ++ticks;
    }

    state.window_stack.pop_back();
}

std::string show_achievements(const Player& p) {

    const auto& achievements = constants().achievements;

    // achieved, next_target

    std::map<tag_t, std::pair<bool, unsigned int> > resorted;

    for (const auto& z : achievements) {

        const auto& ach = z.second;

        auto j = p.kills.find(ach.genus);

        if (j == p.kills.end())
            continue;

        unsigned int kills = j->second;

        auto& ri = resorted[ach.genus];

        if (kills >= ach.kills && !ri.first)
            ri.first = true;

        ri.second = std::max(ach.kills, ri.second);
    }

    std::string ret = "\nEnemies defeated:\n\n";

    const auto& names = constants().genus_names;

    for (const auto& i : p.kills) {

        auto n = names.find(i.first);

        if (n == names.end())
            continue;
            
        std::string s = " ";

        unsigned int kills = i.second;

        if (kills < 1000) s += " ";
        if (kills < 100)  s += " ";

        s += "\2";
            
        nlp::parsed_name pn(n->second);
        s += pn.make(kills, false);

        s += "\1";

        auto r = resorted.find(i.first);

        if (r != resorted.end()) {

            if (s.size() < 40) {
                s += std::string(40 - s.size(), ' ');
            }

            if (r->second.first) {
                s += " \3Achievement unlocked!\1";
            }

            if (kills < r->second.second) {
                s += nlp::message(" (%d needed to unlock)", r->second.second);
            }
        }

        s += "\n";

        ret += s;
    }

    return ret;
}

std::string help_text() {

    std::string ret = 
        "\3Essential commands:\1\n"
        "  \2h j k l\1 "
        "  \2arrow keys\1 : Move left, down, up and right.\n"
        "  \2y u b n\1 "
        "  \2keypad\1 :     Move diagonally.\n"
        "  \2.\1 :          Stand still.\n"
        "  \2S\1 :          Save and quit.\n"
        "  \2Q\1 :          Commit suicide and quit.\n"
        "  \2>\1 :          Use terrain. (Enter holes and tunnels, use statues.)\n"
        "  \2i\1 :          Interact with inventory, use items and show character info.\n"
        "  \2z\1 :          Cast spells if you know them.\n"
        "  \2/\1 :          Look around you using arrow keys.\n"
        "  \2tab\1 :        Look at monsters and items in view.\n"
        "  \2P\1 :          Show message history.\n"
        "  \2K\1 :          Show kills and achievements.\n"
        "  \2*\1 :          Show the Ring of Power's current status.\n"
        "  \2?\1 :          Show this help message.\n"
        "  \2??\1 :         Show detailed instructions.\n"
        "\n\3Shortcut commands:\1\n"
        "  \2T\1 :          Take the first item laying on the floor.\n"
        "  \1a\1 :            (Same as 'T'.)\n"
        "  \1s\1 :            (Same as '>'.)\n"
        "  \2q\1 :          Move away from the monsters in view. (Optimal direction is chosen automatically.)\n"
        "  \2,\1 :          Examine the first item laying on the floor.\n"
        ;

    for (const auto& shortcut : constants().shortcuts) {
        ret += "  \2";
        ret += shortcut.first;
        ret += "\1 :          ";
        ret += shortcut.second.help_message;
        ret += '\n';
    }

    return ret;
}


void handle_input_main(Player& p, GameState& state,
                       size_t& ticks, bool& done, bool& dead, bool& regen, 
                       maudit::keypress k, bool debug_enabled, size_t n_skin) {

    bool redraw = false;

    switch (k.letter) {
    case 'Q':
        state.render.do_message("You quit the game. (Press space to exit.)", true);
        p.attacker = "suicide";
        done = true;
        dead = true;
        break;

    case 'S':
        state.render.do_message("Your game has been saved. (Press space to exit.)", true);
        done = true;
        dead = false;
        break;

    case 'q':
        run_away(p, state, ticks, n_skin);
        break;

    case 'h':
        move(p, state, -1, 0, ticks, n_skin);
        break;
    case 'j':
        move(p, state, 0, 1, ticks, n_skin);
        break;
    case 'k':
        move(p, state, 0, -1, ticks, n_skin);
        break;
    case 'l':
        move(p, state, 1, 0, ticks, n_skin);
        break;
    case 'y':
        move(p, state, -1, -1, ticks, n_skin);
        break;
    case 'u':
        move(p, state, 1, -1, ticks, n_skin);
        break;
    case 'b':
        move(p, state, -1, 1, ticks, n_skin);
        break;
    case 'n':
        move(p, state, 1, 1, ticks, n_skin);
        break;

    case '>':
    case '<':
    case 's':
        use_terrain(p, state, ticks, regen, done, dead);
        break;

    case '.':
        rest(state, ticks);
        break;

    case 'T':
    case 'a':
        take_item(p.px, p.py, 0, p, state, ticks);
        break;

    case ',':
        if (state.items.stack_size(p.px, p.py) == 0) {
            state.render.do_message("There are no items here.");

        } else {
            state.push_window(select_floor_item(p.inv, state.items, p.px, p.py, 0), screens_t::floor_item);
        }
        break;

    case 'i':
        state.push_window(show_inventory(p.inv, p.level, 
                                         levelskins().get(p.worldz).name, 
                                         state.moon.pi.phase_str, 
                                         state.items, p.px, p.py), 
                          screens_t::inventory);
        break;

    case 'z':
        state.push_window(show_spells(p.spells, p.inv.spells(), p.inv.random_spells()), screens_t::spells);
        break;

    case 'P':
        state.push_window(state.render.all_messages(), screens_t::messages);
        break;

    case 'K':
        state.push_window(show_achievements(p), screens_t::achievements);
        break;

    case '*':
        state.push_window(show_victory(), screens_t::victory_status);
        break;

    case '/':
        start_look_plain(p.state, p.look, p.px, p.py, state);
        break;

    case '\t':
        start_look_cycle(p.state, p.look, p.px, p.py, state, k);
        break;

    case '?':
        state.push_window(help_text(), screens_t::help);
        break;

        // WATCH OUT!
    case '!':
        if (debug_enabled) {
            p.state = Player::DEBUG;
        }
        break;

    default:
        break;
    }

    switch (k.key) {
    case maudit::keycode::up:
        move(p, state, 0, -1, ticks, n_skin);
        break;
    case maudit::keycode::left:
        move(p, state, -1, 0, ticks, n_skin);
        break;
    case maudit::keycode::right:
        move(p, state, 1, 0, ticks, n_skin);
        break;
    case maudit::keycode::down:
        move(p, state, 0, 1, ticks, n_skin);
        break;
    case maudit::keycode::kp_7:
        move(p, state, -1, -1, ticks, n_skin);
        break;
    case maudit::keycode::kp_9:
        move(p, state, 1, -1, ticks, n_skin);
        break;
    case maudit::keycode::kp_1:
        move(p, state, -1, 1, ticks, n_skin);
        break;
    case maudit::keycode::kp_3:
        move(p, state, 1, 1, ticks, n_skin);
        break;
    default:
        break;
    }            

    {
        const auto& shortcut = constants().shortcuts.find(k.letter);

        if (shortcut != constants().shortcuts.end()) {

            bool ok = false;
            for (const auto& slot_keypress : shortcut->second.slot_keypress) {

                p.inv.selected_slot = slot_keypress.first;
                if (handle_input_inv_item(p, state, ticks, done, dead, regen, 
                                              maudit::keypress(slot_keypress.second))) {
                    ok = true;
                    break;
                }
            }

            if (!ok) {
                state.render.do_message(shortcut->second.fail_message);
            }
        }
    }

    if (redraw) {
        state.render.clear();
    }
}


void handle_input_debug(Player& p, GameState& state, size_t& ticks, bool& regen, maudit::keypress k) {

    switch (k.letter) {

    case '@':
        p.health.shield += 1000;
        break;

    case 's':
        state.species_counts = species().counts;
        state.render.do_message("Wiped species counts.");
        break;

    case 'd':
        state.designs_counts = designs().counts;
        state.render.do_message("Wiped designs counts.");
        break;

    case '>':
        p.worldz++;
        regen = true;
        state.render.do_message("Descended.");
        break;

    case '<':
        p.worldz--;
        regen = true;
        state.render.do_message("Ascended.");
        break;

    case 't':
    {
        grid::pt xy;
        if (state.grid.one_of_walk(state.rng, xy)) {

            state.render.invalidate(p.px, p.py);
            p.px = xy.first;
            p.py = xy.second;
            state.render.invalidate(p.px, p.py);
        }
        break;
    }

    case '.':
        state.render.do_message(nlp::message("%d %d", p.px, p.py));
        break;

    case '+':
        p.level++;
        state.render.do_message("Level gained.");
        break;

    case 'i':
    {
        std::map<tag_t, unsigned int> q = state.designs_counts.take(state.rng, p.worldz, 1);

        if (q.size() == 1) {
            state.items.place(p.px, p.py, 
                              state.items.make_item(q.begin()->first, items::pt(p.px, p.py), state.rng),
                              state.render);
        }
        break;
    }

    case 'Z':
    {
        uint32_t rnd = state.rng.range(0u, 0xFFFFFFFF);
        std::cout << "** " << rcode::magick_encode(rnd) << std::endl;
        cast_random_spell(p, rnd, state);
        break;
    }

    case 'S':
    {
        tag_mem_t tagmem;

        unsigned int n = summon_out_of_view(p, state, tag_t("angelgift", tagmem), 0);
        state.render.do_message(nlp::message("Summoned %d", n));
        break;
    }

    case 'z':
    {
        for (const auto& c : celautos().bank) {
            Terrain::spell_t s;
            s.karma_bound = 0;
            s.ca_tag = c.first;
            s.timeout = 9999;
            s.name = c.second.debug_name;
            p.spells.push_back(s);
        }
        state.render.do_message("Granted spells.");
        break;
    }

    }

    p.state &= ~(Player::DEBUG);
}


bool handle_input_pick_direction(unsigned int px, unsigned int py, GameState& state, maudit::keypress k, 
                                 unsigned int& nx, unsigned int& ny) {

    nx = px;
    ny = py;

    switch (k.letter) {
    case 'h':
        nx--;
        break;
    case 'j':
        ny++;
        break;
    case 'k':
        ny--;
        break;
    case 'l':
        nx++;
        break;
    case 'y':
        nx--;
        ny--;
        break;
    case 'u':
        nx++;
        ny--;
        break;
    case 'b':
        nx--;
        ny++;
        break;
    case 'n':
        nx++;
        ny++;
        break;

    default:
        break;
    }

    switch (k.key) {
    case maudit::keycode::up:
        ny--;
        break;
    case maudit::keycode::left:
        nx--;
        break;
    case maudit::keycode::right:
        nx++;
        break;
    case maudit::keycode::down:
        ny++;
        break;

    default:
        break;
    }            

    if (!state.neigh.linked(neighbors::pt(px, py), neighbors::pt(nx, ny))) {
        return false;
    }

    return true;
}

void handle_input_messages(GameState& state, maudit::keypress k, bool do_howto) {

    if (do_howto && k.letter == '?') {
        state.push_window(constants().howto_text, screens_t::howto);
        return;
    }

    state.window_stack.pop_back();
}

void Game::handle_input(GameState& state,
                        size_t& ticks, bool& done, bool& dead, bool& regen, 
                        maudit::keypress k) {

    if (p.state == Player::DEBUG) {
        handle_input_debug(p, state, ticks, regen, k);
        return;
    }

    if (p.state & Player::LOOKING) {

        handle_input_looking(p.state, p.look, p.px, p.py, state, k);

        if (p.state & Player::FIRED) {

            if (p.state & Player::THROWING) {
                end_throw_item(p, p.inv.selected_slot, p.look.x, p.look.y, state);

            } else if (p.state & Player::BLASTING) {
                end_blast_item(p, p.inv.selected_slot, p.look.x, p.look.y, state);
            }

            ++ticks;
            p.state = Player::MAIN;
        }

        return;
    }

    if (p.state & Player::DIGGING) {

        unsigned int nx;
        unsigned int ny;

        bool ok = handle_input_pick_direction(p.px, p.py, state, k, nx, ny);

        if (!ok || state.grid.is_walk(nx, ny)) {
            state.render.do_message("There is nothing to dig there.");

        } else {
            state.render.do_message("You start digging.");
            p.digging = true;
            p.dig_x = nx;
            p.dig_y = ny;
            ++ticks;
        }

        p.state = Player::MAIN;
        return;
    }

    if (state.window_stack.empty()) {
        handle_input_main(p, state, ticks, done, dead, regen, k, debug_enabled, n_skin);
        return;
    }

    switch ((screens_t)state.window_stack.back().type) {

    case screens_t::messages:
    case screens_t::tombstone:
    case screens_t::howto:
    case screens_t::achievements:
        handle_input_messages(state, k, false);
        break;

    case screens_t::help:
        handle_input_messages(state, k, true);
        break;

    case screens_t::inventory:
        handle_input_inventory(p, state, ticks, done, dead, regen, k);
        break;

    case screens_t::inv_item:
        handle_input_inv_item(p, state, ticks, done, dead, regen, k);
        break;

    case screens_t::floor_item:
        handle_input_floor_item(p, state, ticks, done, dead, regen, k);
        break;

    case screens_t::spells:
        handle_input_spells(p, state, ticks, k);
        break;

    default:
        // This is a sanity error check condition.
        state.window_stack.pop_back();
        break;
    }
}

template <typename FUNC>
void Game::goodbye_message(GameState& state, FUNC println) {

    highscore::Scores scores;

    println("");
    println("");
    println("Highscore table:");
    println("");

    scores.by_plev([println](size_t n, const bones::bone_t::fakeobj& name, const bones::bone_t::fakeobj& cause,
                             unsigned int plev, int dlev, double worth, bool victory) {

                       std::string line1;
                       std::string line2;
                       std::string pad;

                       ++n;

                       if (n < 10)
                           pad = " ";

                       if (victory) {
                           line1 = nlp::message("%s%d) %S, a glorious victor of level %d.", pad, n, name, plev+1);
                           line2 = nlp::message("    Last seen on level %d. Net worth: %d $ZM.");

                       } else {
                           line1 = nlp::message("%s%d) %S, level %d.", pad, n, name, plev+1);
                           line2 = nlp::message("    Killed on level %d by %s. Net worth: %d $ZM.",  
                                                dlev+1, cause, worth);
                       }

                       println(line1);
                       println(line2);
                       println("");
                   });

}

#endif
