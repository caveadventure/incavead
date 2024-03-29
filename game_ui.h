#ifndef __GAME_UI_H
#define __GAME_UI_H

std::string show_overmap(Player& p, const GameState& state, size_t scale = 12) {

    p.overmap.scale = scale;

    std::string ret = "\2The overview map. Use '+' and '-' to zoom in and out.\n\n"_m;

    std::string level_name = levelskins().get(p.worldz).name;

    if (p.worldx != 0 || p.worldy != 0) {
        static const std::string tunnels[3][3] = {
            { "due NW"_m, "due W"_m, "due SW"_m },
            { "due N"_m,  ""_m,      "due S"_m },
            { "due NE"_m, "due E"_m, "due SE"_m } };


        level_name += ", ";
        level_name += tunnels[p.worldx+1][p.worldy+1];
    }

    ret += nlp::message("\1Dungeon level %d (%s), %s moon.\n\n\3"_m,
                        p.worldz+1, level_name, state.moon.pi.phase_str);

    for (unsigned int y = 0; y < state.render.h; y += scale) {
        for (unsigned int x = 0; x < state.render.w; x += scale) {

            std::string charz = " "_m;
            unsigned int intensity = 0;

            if (x == 0 || y == 0 || 
                x >= state.render.w - scale ||
                y >= state.render.h - scale) {

                charz = "."_m;
            }

            for (unsigned int yi = 0; yi < scale; ++yi) {
                for (unsigned int xi = 0; xi < scale; ++xi) {

                    unsigned int xx = x + xi;
                    unsigned int yy = y + yi;

                    if (xx >= state.render.w || yy >= state.render.h)
                        continue;
                    
                    const auto& gp = state.render._get(xx, yy);

                    if (xx == p.px && yy == p.py) {
                        charz = p.get_species().skin[0].get_text();
                        intensity = 3;
                    }

                    items::Item item;
                    if (state.items.get(xx, yy, 0, item) && intensity <= 2) {
                        const Design& d = designs().get(item.tag);

                        if (d.is_lit || gp.is_lit) {
                            charz = d.skin[0].get_text();
                            intensity = 2;
                        }
                    }

                    features::Feature feat;
                    if (state.features.get(xx, yy, feat) && intensity <= 1) {
                        const Terrain& t = terrain().get(feat.tag);

                        if (t.is_lit || gp.is_lit) {
                            charz = t.skin[0].get_text();

                            if (charz == std::string(" "_m))
                                charz = "."_m;

                            intensity = 1;
                        }
                    }

                }
            }

            ret += charz;
        }

        ret += "\n\3"_m;
    }

    return ret;
}


std::string show_victory(const Player& p, const GameState& state) {

    std::string ret = "\n\2Status of the \3Ring of Power:\1\n\n"_m;

    if (p.uniques_disabled) {
        ret += "Indeterminate status due to wishing.\n"_m;
        return ret;
    }

    std::vector<uniques::key_t> levels;
    time_t placetime;

    uniques::uniques().locate(placetime, levels);

    time_t now = ::time(NULL);
    time_t tdiff = now - placetime;
    unsigned int timeout = constants().uniques_timeout;

    if (levels.empty()) {
    
        bool found = false;

        for (const auto& is : state.items.stuff) {
            for (const auto& i : is.second) {
                if (i.tag == constants().unique_item) {
                    found = true;
                }
            }
        }

        if (found) {
            ret += "Found somewhere on this level.\n"_m;

        } else {

            bool inv = false;

            for (const auto& i : p.inv.stuff) {
                if (i.second.tag == constants().unique_item) {
                    inv = true;
                }
            }

            if (inv) {
                ret += "In your inventory.\n"_m;
                found = true;
            }
        }

        if (!found) {
            if (placetime == 0 || tdiff >= (time_t)timeout) {
                ret += "Ready to regenerate on dungeon level\2 1\1."_m;

            } else {
                ret += "Destroyed and not yet ready to regenerate.\n"_m;
            }
        }

    } else {

        const auto& wk = levels.back();

        static const std::string tunnels[3][3] = {
            { "follow a tunnel due north-west"_m,
              "follow a tunnel due west"_m, 
              "follow a tunnel due south-west"_m },
            { "follow a tunnel due north"_m,
              "main branch"_m, 
              "follow a tunnel due south"_m },
            { "follow a tunnel due north-east"_m,
              "follow a tunnel due east"_m, 
              "follow a tunnel due south-east"_m } };

        if (wk.worldy < -1 || wk.worldy > 1 || wk.worldx < -1 || wk.worldy > 1)
            throw std::runtime_error("Sanity error in worldkey");

        tdiff /= 60;
        std::string units = "minutes"_m;

        if (tdiff > 1440) {
            tdiff /= 1440;
            units = "days"_m;

        } else if (tdiff > 60) {
            tdiff /= 60;
            units = "hours"_m;
        }

        ret += nlp::message("Found somewhere on dungeon level \2%d\1 (\2%s\1).\n"_m, 
                            wk.worldz+1, tunnels[wk.worldx+1][wk.worldy+1]);

        ret += nlp::message("It has been there for \2%d %s\1.\n"_m, tdiff, units);
    }

    return ret;
}

std::string show_stats(const Player& p) {

    std::string ret;

    tag_t polytag = p.polymorph.species;

    if (!polytag.null()) {

        ret = nlp::message("\n\2Character level:\1 %d    (in the form of \2%s\1)\n"_m, p.get_level()+1,
                           species().get(polytag));

    } else {
        ret = nlp::message("\n\2Character level:\1 %d\n"_m, p.get_level()+1);
    }

    damage::attacks_t att;
    p.get_attack(att);

    if (att.attacks.empty()) {

        ret += "\n\2You have no attack capabilities.\1\n\n"_m;

    } else {

        ret += "\n\2Your attack capabilities:\1\n\n"_m;

        for (const auto& i : att.attacks) {

            // HACK
            if (i.val < 0.01)
                continue;

            const Damage& dam = damages().get(i.type);
            std::string s = dam.name;

            if (s.size() < 25) 
                s += std::string(25 - s.size(), ' ');

            ret += nlp::message("  \1%S\2: %d\n"_m, s, i.val);
        }
    }

    damage::defenses_t def;
    p.get_defense(def);

    if (def.defenses.empty()) {

        ret += "\n\2You have no defense capabilities.\1\n\n"_m;

    } else {

        ret += "\n\2Your defense capabilities:\1\n\n"_m;

        for (const auto& i : def.defenses) {

            // HACK
            if (i.second < 0.01)
                continue;

            const Damage& dam = damages().get(i.first);
            std::string s = dam.name;

            if (s.size() < 25) 
                s += std::string(25 - s.size(), ' ');

            ret += nlp::message("  \1%S\2: %d\n"_m, s, i.second);
        }
    }

    auto j = constants().starsigns.names.find(p.starsign.sign);

    std::string sign(j == constants().starsigns.names.end() ? "Unnamed"_m : j->second);

    ret += nlp::message("\n\2Your starsign:\1 %d-%S\n\n"_m, p.starsign.day, sign);


    if (p.ailments.size() > 0) {
        ret += "\n\nYour degenerative ailments:\n\n"_m;

        std::map<std::string, std::pair<size_t,size_t> > ails;

        for (const auto& a : p.ailments) {
            const auto i = constants().ailments.find(a.second);

            if (i != constants().ailments.end()) {
                auto& zz = ails[i->second.name];
                zz.first++;
                zz.second = i->second.triggers;
            }
        }

        for (const auto& a : ails) {
            size_t n = a.second.first / a.second.second;
            if (n <= 1) {
                ret += nlp::message("  \2%S\1\n"_m, a.first);
            } else {
                ret += nlp::message("  \2%S\1 (x\2%d\1)\n"_m, a.first, n);
            }
        }
    }

    return ret;
}

std::string show_spells(const Player& p, const GameState& state) {

    const std::vector<Terrain::spell_t>& p_spells = p.spells;
    const std::vector<Design::spell_t>& i_spells = p.inv.spells();
    const std::vector<uint32_t>& r_spells = p.inv.random_spells();

    std::string m;

    m = "\2Your arcane powers:\n\n"_m;

    char z = 'a';
    for (const auto& sp : p_spells) {

        m += nlp::message("   \2%c\1) %S\n"_m, z, sp);
        ++z;
    }

    for (const auto& sp : i_spells) {

        m += nlp::message("   \2%c\1) %S\n"_m, z, sp);
        ++z;
    }

    for (const auto& rp : r_spells) {

        m += nlp::message("   \2%c\1) Labeled '%s'\n"_m, z, rcode::magick_encode(rp));
        ++z;
    }

    const Species& s = p.get_species();

    if (!s.magic_cost.stat.null() && p.stats.is_min(s.magic_cost.stat))
        return m;

    for (const auto& pb : s.blast) {

        m += nlp::message("   \2%c\1) %S%s\n"_m, z, pb.name, 
                          ((state.ticks % pb.turns) == 0 ? std::string() : std::string(" \2(not ready)\1"_m)));
        ++z;
    }

    for (const auto& pc : s.cast_cloud) {

        m += nlp::message("   \2%c\1) %S%s\n"_m, z, pc.name, 
                          ((state.ticks % pc.turns) == 0 ? std::string() : std::string(" \2(not ready)\1"_m)));
        ++z;
    }

    for (const auto& ps : s.summon) {

        m += nlp::message("   \2%c\1) Summon %s%s\n"_m, z, species().get(ps.speciestag),
                          ((state.ticks % ps.turns) == 0 ? std::string() : std::string(" \2(not ready)\1"_m)));
        ++z;
    }

    for (const auto& ps : s.spawns) {

        m += nlp::message("   \2%c\1) Summon level %d monster%s\n"_m, z, ps.level,
                          ((state.ticks % ps.turns) == 0 ? std::string() : std::string(" \2(not ready)\1"_m)));
        ++z;
    }
        
    return m;
}

std::string show_options(GameState& state, GameOptions& options) {

    std::string ret;

    ret += "\n";

    ret += "\2a\1) Always center view on player:    \3"_m;
    ret += (options.center_view ? "Yes\n"_m : "No\n"_m);

    ret += "\2b\1) Don't fade colors with distance: \3"_m;
    ret += (options.no_fade_colors ? "Yes\n"_m : "No\n"_m);

    ret += "\2c\1) Color theme in menus:            \3"_m;
    ret += (state.render.ui_symbol_index ? "Black\n"_m : "Blue\n"_m);

    return ret;
}

void handle_input_spells(Player& p, GameState& state, maudit::keypress k) {

    int _z = k.letter - 'a';

    if (_z < 0) {
        state.window_stack.pop_back();
        return;
    }

    size_t z = (size_t)_z;

    const auto& p_spells = p.spells;
    const auto& i_spells = p.inv.spells();
    const auto& r_spells = p.inv.random_spells();

    size_t size1 = p_spells.size();
    size_t size2 = size1 + i_spells.size();
    size_t size3 = size2 + r_spells.size();

    if (z < size1) {

        const auto& sp = p_spells[z];

        seed_celauto(state, p.px, p.py, sp.ca_tag);        
        ++(state.ticks);

    } else if (z < size2) {

        const auto& sp = i_spells[z - size1];

        seed_celauto(state, p.px, p.py, sp.ca_tag);
        ++(state.ticks);

    } else if (z < size3) {

        uint32_t rspell = r_spells[z - size2];

        cast_random_spell(p, rspell, state);
        ++(state.ticks);
    }

    const Species& s = p.get_species();

    if (!s.magic_cost.stat.null()) {

        if (p.stats.is_min(s.magic_cost.stat)) {
            state.window_stack.pop_back();
            return;
        }

        if (p.stats.sinc(s.magic_cost.stat, -s.magic_cost.cost))
            p.dead = true;
    }

    size_t x = z - size3;

    size1 = s.blast.size();
    size2 = size1 + s.cast_cloud.size();
    size3 = size2 + s.summon.size();
    size_t size4 = size3 + s.spawns.size();

    if (x < size1) {

        start_poly_blast(p, x, state);

    } else if (x < size2) {

        start_poly_cloud(p, x - size1, state);

    } else if (x < size3) {

        summon_poly(p, x - size2, state);

    } else if (x < size4) {

        spawn_poly(p, x - size3, state);
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

        if (kills >= ach.kills) {
            ri.first = true;

        } else if (ach.kills < ri.second || ri.second == 0) {
            ri.second = ach.kills;
        }
    }

    std::string ret = "\nEnemies defeated:\n\n"_m;

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
                s += " \3Achievement unlocked!\1"_m;
            }

            if (r->second.second != 0) {
                s += nlp::message(" (%d needed to unlock)"_m, r->second.second);
            }
        }

        s += "\n";

        ret += s;
    }

    return ret;
}

std::string show_monsters(const Player& p, const GameState& state) {

    std::string ret = "\nKnown enemies:\n"_m;

    for(auto t = p.seen_monsters.timeline.rbegin(); t != p.seen_monsters.timeline.rend(); ++t) {

        const Species& s = species().get(*t);

        double danger = 0;

        for (const auto& i : s.attacks.attacks) {
            danger += (i.val / 6.0);
        }

        for (const auto& i : s.cast_cloud) {
            danger += (-i.chance / i.turns) / 2.0;
        }

        for (const auto& i : s.summon) {
            danger += (-i.chance / i.turns);
        }

        for (const auto& i : s.spawns) {
            danger += (-i.chance / i.turns);
        }

        for (const auto& i : s.blast) {

            double f = (-i.chance / i.turns) * 2;
            
            for (const auto& j : i.attacks.attacks) {
                danger += (j.val / 6.0) / f;
            }
        }


        auto i = constants().genus_names.find(s.genus);

        if (i != constants().genus_names.end()) {

            nlp::parsed_name pn(i->second);

            ret += nlp::message("\n\3%S\1: \2%s\1 of level \2%d\1."_m, s, pn.make(1, false), s.get_computed_level() + 1);

        } else {

            ret += nlp::message("\n\3%S\1: level \2%d\1."_m, s, s.get_computed_level() + 1);
        }

        if (!s.ally.null()) {
            ret += " \2It is usually friendly.\1"_m;
        }

        if (s.count == 0) {
            ret += " (\2Exceedingly rare, "_m;

        } else if (s.count <= 5) {
            ret += " (\2Rare, "_m;

        } else if (s.count <= 10) {
            ret += " (\2Uncommon, "_m;

        } else if (s.count <= 20) {
            ret += " (\2Common, "_m;

        } else {
            ret += " (\2Very common, "_m;
        }

        if (danger >= 3) {
            ret += "epically dangerous.\1)"_m;

        } else if (danger >= 2.5) {
            ret += "terribly dangerous.\1)"_m;

        } else if (danger >= 1.7) {
            ret += "highly dangerous.\1)"_m;

        } else if (danger >= 0.8) {
            ret += "dangerous.\1)"_m;

        } else if (danger >= 0.6) {
            ret += "slightly dangerous.\1)"_m;

        } else if (danger >= 0.4) {
            ret += "mostly harmless.\1)"_m;

        } else {
            ret += "harmless.\1)"_m;
        }

        if (s.descr.size() > 0) {
            ret += "\n";
            ret += "    \"";

            for (unsigned char c : s.descr) {
                if (c == '\n') {
                    ret += "\n    ";
                } else {
                    ret += c;
                }
            }

            ret += "\"\n";

        } else {
            ret += "\n";
        }
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
        "  \2>\1 :          Use terrain. (Enter holes and tunnels, use statues, etc.)\n"
        "  \2i\1 :          Interact with inventory, use items and show character info.\n"
        "  \2z\1 :          Cast spells if you know them.\n"
        "\3Information commands:\1\n"
        "  \2/\1 :          Look around you using arrow keys.\n"
        "  \2tab\1 :        Look at monsters and items in view.\n"
        "  \2P\1 :          Show message history.\n"
        "  \2@\1 :          Show your attack and defense stats.\n"
        "  \2#\1 :          Show the current level's map overview.\n"
        "  \2*\1 :          Show the Ring of Power's current status.\n"
        "  \2K\1 :          Show kills and achievements.\n"
        "  \2M\1 :          Show a detailed log of all encountered enemies.\n"
        "  \2=\1 :          Set game options.\n"
        "  \2\"\1 :          Send a message in spectator mode chat. (Also useful for notes to self.)\n"
        "  \2?\1 :          Show this help message.\n"
        "  \2??\1 :         Show detailed instructions.\n"
        "\n\3Shortcut commands:\1\n"
        "  \2T\1 :          Take the first item laying on the floor.\n"
        "  \1a\1 :            (Same as 'T'.)\n"
        "  \1s\1 :            (Same as '>'.)\n"
        "  \2q\1 :          Move away from the monsters in view. (Optimal direction is chosen automatically.)\n"
        "  \2,\1 :          Examine the first item laying on the floor.\n"
        "  \2R\1 :          Stand still for 100 turns.\n"_m
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


void handle_input_main(Player& p, GameState& state, GameOptions& options,
                       bool& done, bool& dead, bool& regen, 
                       maudit::keypress k, bool debug_enabled, size_t n_skin) {

    bool redraw = false;

    switch (k.letter) {
    case 'Q':
        state.render.do_message("Are you sure you want to commit suicide? (Press 'Y' if you are.)"_m, true);
        p.state |= Player::QUITTING;
        break;

    case 'S':
        state.render.do_message("Your game has been saved. (Press space to exit.)"_m, true);
        done = true;
        dead = false;
        break;

    case 'q':
        run_away(p, state, n_skin);
        break;

    case 'h':
        move(p, state, -1, 0, n_skin);
        break;
    case 'j':
        move(p, state, 0, 1, n_skin);
        break;
    case 'k':
        move(p, state, 0, -1, n_skin);
        break;
    case 'l':
        move(p, state, 1, 0, n_skin);
        break;
    case 'y':
        move(p, state, -1, -1, n_skin);
        break;
    case 'u':
        move(p, state, 1, -1, n_skin);
        break;
    case 'b':
        move(p, state, -1, 1, n_skin);
        break;
    case 'n':
        move(p, state, 1, 1, n_skin);
        break;

    case '>':
    case '<':
    case 's':
        use_terrain(p, state, regen, done, dead);
        break;

    case '.':
        rest(state);
        break;

    case 'R':
        p.stats.cinc(constants().rest_count, 100);
        ++(state.ticks);
        break;
        
    case 'T':
    case 'a':
        take_item(p.px, p.py, 0, p, state);
        break;

    case ',':
        if (state.items.stack_size(p.px, p.py) == 0) {
            state.render.do_message("There are no items here."_m);

        } else {
            state.push_window(select_floor_item(p.inv, state.items, p.px, p.py, 0), screens_t::floor_item);
        }
        break;

    case 'i':
        state.push_window(show_inventory(p, state.moon.pi.phase_str, state.items), screens_t::inventory);
        break;

    case 'z':
        state.push_window(show_spells(p, state), screens_t::spells);
        break;

    case 'P':
        state.push_window(state.render.all_messages(), screens_t::messages);
        break;

    case 'K':
        state.push_window(show_achievements(p), screens_t::achievements);
        break;

    case 'M':
        state.push_window(show_monsters(p, state), screens_t::monsters);
        break;
        
    case '*':
        state.push_window(show_victory(p, state), screens_t::victory_status);
        break;

    case '@':
        state.push_window(show_stats(p), screens_t::stats);
        break;

    case '#':
        state.push_window(show_overmap(p, state), screens_t::overmap);
        break;

    case '=':
        state.push_window(show_options(state, options), screens_t::options, false);
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

    case '\"':
        do_player_input(state, p, ">>> "_m);
        p.state |= Player::SELFNOTE;
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
        move(p, state, 0, -1, n_skin);
        break;
    case maudit::keycode::left:
        move(p, state, -1, 0, n_skin);
        break;
    case maudit::keycode::right:
        move(p, state, 1, 0, n_skin);
        break;
    case maudit::keycode::down:
        move(p, state, 0, 1, n_skin);
        break;
    case maudit::keycode::kp_7:
        move(p, state, -1, -1, n_skin);
        break;
    case maudit::keycode::kp_9:
        move(p, state, 1, -1, n_skin);
        break;
    case maudit::keycode::kp_1:
        move(p, state, -1, 1, n_skin);
        break;
    case maudit::keycode::kp_3:
        move(p, state, 1, 1, n_skin);
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
                if (handle_input_inv_item(p, state, done, dead, regen, 
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


void handle_input_debug(Player& p, GameState& state, bool& regen, maudit::keypress k) {

    switch (k.letter) {

    case '@':
    {
        tag_mem_t tagmem;
        p.stats.sinc(tag_t("shield", tagmem), 1000);
        break;
    }
    case '2':
    {
        tag_mem_t tagmem;
        p.stats.stats[tag_t("shield", tagmem)].val = 0;
        break;
    }
    case '$':
        state.render.do_message(nlp::message("Monetary base: %d", finance::supply().get_base()));
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
        //state.render.do_message(nlp::message("%d %d | %d", p.px, p.py, state.grid._get(p.px, p.py)));
        state.render.do_message(dowsing_message(p, state));
        break;

    case 'k':
        state.render.do_message(nlp::message("%d %d | %d", p.px, p.py, state.grid.get_karma(p.px, p.py)));
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
        state.render.do_message("** " + rcode::magick_encode(rnd));
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
        tag_mem_t tagmem;

        for (const auto& c : celautos().bank) {
            Terrain::spell_t s;
            s.stat = tag_t("karma", tagmem);
            s.stat_min = -3;
            s.stat_max = 3;
            s.ca_tag = c.first;
            s.timeout = 9999;
            s.name = c.second.debug_name;
            p.spells.push_back(s);
        }
        state.render.do_message("Granted spells.");
        break;
    }

    case 'M':
        state.render.do_message("Long message message lorem ispum alpha beta gamma one "
                                "two three four lorem ipsum long message spanning many lines "
                                "qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, "
                                "sed quia non numquam eius modi tempora incidunt.");
        break;

    case 'w':
        do_player_wish(state, p);
        return;

    case 'I':
        simple_wish(state, p, p.input.s);
        break;

    case 'O':
        special_wish(state, p, p.input.s);
        break;

    case 'l':
    {
        tag_mem_t tagmem;

        state.features.x_set(p.px, p.py, tag_t("light", tagmem), state.render);
        break;
    }
                             
    case 'A':
    {
        tag_mem_t tagmem;

        state.monsters.summon_any(state.neigh, state.rng, state.grid, state.species_counts, state.render, 
                                  p.px, p.py, p.px, p.py, p.level, 1, tag_t("something", tagmem));
        break;
    }

    case 'L':
        for (unsigned int y = 0; y < state.render.h; ++y) {
            for (unsigned int x = 0; x < state.render.w; ++x) {
                state.render.set_is_lit(x, y, 5,  true);
                state.render.invalidate(x, y);
            }
        }
        break;
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

    case '.':
    case '>':
        return true;

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
        state.push_window("howto_text_placeholder"_m, screens_t::howto);
        return;
    }

    state.window_stack.pop_back();
}

void handle_input_overmap(Player& p, GameState& state, maudit::keypress k) {

    if (k.letter == '-') {
        state.window_stack.pop_back();
        state.push_window(show_overmap(p, state, p.overmap.scale * 2), screens_t::overmap);

    } else if (k.letter == '+') {

        if (p.overmap.scale > 2) {
            state.window_stack.pop_back();
            state.push_window(show_overmap(p, state, p.overmap.scale / 2), screens_t::overmap);
        }

    } else {
        state.window_stack.pop_back();
    }
}

bool handle_input_input(GameState& state, std::string& input_string, int limit, maudit::keypress k) {

    if (k.letter == '\n') {
        return false;

    } else if (k.letter == '\x7F' || k.letter == '\x08' || k.key == maudit::keycode::del) {

        if (!input_string.empty()) {

            state.render.replace_message([](std::string& msg) {
                    msg.pop_back();
                });

            input_string.pop_back();
        }

    } else if (k.letter >= ' ' && k.letter <= '~') {

        if (limit >= 0 && input_string.size() >= (size_t)limit)
            return true;
        
        unsigned char letter = k.letter;

        state.render.replace_message([letter](std::string& msg) {
                msg += letter;
            });

        input_string += k.letter;
    }

    return true;
}


void handle_input_options(GameState& state, GameOptions& options, maudit::keypress k) {

    switch (k.letter) {

    case 'a':
        options.center_view = !(options.center_view);
        break;

    case 'b':
        options.no_fade_colors = !(options.no_fade_colors);
        break;

    case 'c':
    case '\t':
        state.render.set_ui_symbol(1);
        break;

    default:
        state.window_stack.pop_back();
        return;
    }

    state.window_stack.back().message = show_options(state, options);
}

void start_digging(Player& p, GameState& state, unsigned int nx, unsigned int ny) {

    state.render.do_message("You start digging."_m);

    p.dig.x = nx;
    p.dig.y = ny;
    p.dig.h = state.grid.get(nx, ny);

    p.stats.cinc(constants().digging_count, 2 + ((p.dig.h + 10) / p.inv.get_digging()));
}

void Game::handle_input(GameState& state, GameOptions& options,
                        bool& done, bool& dead, bool& regen, 
                        maudit::keypress k) {

    if (p.state == Player::DEBUG) {
        handle_input_debug(p, state, regen, k);
        return;
    }

    if (p.state & Player::QUITTING) {
        if (k.letter == 'y' || k.letter == 'Y') {

            state.render.do_message("See you later. (Press space to exit.)"_m);

            p.attacker = "suicide"_m;
            done = true;
            dead = true;
            return;
        }

        p.state &= ~(Player::QUITTING);
    }

    if (p.state & Player::INPUTTING) {

        if (!handle_input_input(state, p.input.s, p.input.limit, k)) {

            p.state &= ~(Player::INPUTTING);

        } else {

            return;
        }
    }

    // //

    if (p.state & Player::TERRAIN_STEP2) {

        use_terrain(p, state, regen, done, dead);
        p.state = Player::MAIN;
        return;
    }

    if (p.state & Player::DESIGN_STEP2) {

        apply_item(p, p.inv.selected_slot, state, regen);
        p.state = Player::MAIN;
        return;
    }

    if (p.state & Player::SELFNOTE) {
        state.render.do_message(std::string(">>> "_m) + p.input.s);
        p.state = Player::MAIN;
        return;
    }

    // //

    if (p.state & Player::LOOKING) {

        handle_input_looking(p.state, p.look, p.px, p.py, state, k);

        if (p.state & Player::FIRED) {

            if (p.state & Player::THROWING) {
                end_throw_item(p, p.inv.selected_slot, p.look.x, p.look.y, state);

            } else if (p.state & Player::BLASTING) {
                end_blast_item(p, p.inv.selected_slot, p.look.x, p.look.y, state);

            } else if (p.state & Player::CLOUDING) {
                end_cloud_item(p, p.inv.selected_slot, p.look.x, p.look.y, state);

            } else if (p.state & Player::P_BLASTING) {
                end_poly_blast(p, p.polymorph_ability, p.look.x, p.look.y, state);

            } else if (p.state & Player::P_CLOUDING) {
                end_poly_cloud(p, p.polymorph_ability, p.look.x, p.look.y, state);
            }

            ++(state.ticks);
            p.state = Player::MAIN;
        }

        return;
    }

    if (p.state & Player::DIGGING) {

        unsigned int nx;
        unsigned int ny;

        bool ok = handle_input_pick_direction(p.px, p.py, state, k, nx, ny);

        if (ok) {
            if (nx == p.px && ny == p.py) {

                bool ok = false;

                features::Feature feat;
                if (state.features.get(nx, ny, feat)) {

                    if (feat.tag == constants().grave) {
                        ok = true;
                    }

                } else if (state.grid.is_floor(nx, ny)) {
                    ok = true;
                }

                if (!ok) {
                    state.render.do_message("You cannot dig here."_m);

                } else {
                    start_digging(p, state, nx, ny);
                    ++(state.ticks);
                }

            } else {

                if (state.grid.is_walk(nx, ny)) {
                    state.render.do_message("There is nothing to dig there."_m);

                } else {
                    start_digging(p, state, nx, ny);
                    ++(state.ticks);
                }
            }
        }

        p.state = Player::MAIN;
        return;
    }

    if (state.window_stack.empty()) {
        handle_input_main(p, state, options, done, dead, regen, k, debug_enabled, n_skin);
        return;
    }

    switch ((screens_t)state.window_stack.back().type) {

    case screens_t::messages:
    case screens_t::tombstone:
    case screens_t::howto:
    case screens_t::achievements:
    case screens_t::victory_status:
    case screens_t::stats:
        handle_input_messages(state, k, false);
        break;

    case screens_t::help:
        handle_input_messages(state, k, true);
        break;

    case screens_t::overmap:
        handle_input_overmap(p, state, k);
        break;

    case screens_t::inventory:
        handle_input_inventory(p, state, done, dead, regen, k);
        break;

    case screens_t::inv_item:
        handle_input_inv_item(p, state, done, dead, regen, k);
        break;

    case screens_t::floor_item:
        handle_input_floor_item(p, state, done, dead, regen, k);
        break;

    case screens_t::spells:
        handle_input_spells(p, state, k);
        break;

    case screens_t::bank_main:
    case screens_t::bank_withdrawal:
    case screens_t::bank_deposit:
    case screens_t::bank_buy:
    case screens_t::bank_buy_confirm:
        handle_input_banking(p, state, k);
        break;

    case screens_t::options:
        handle_input_options(state, options, k);
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
    println("Highscore table:"_m);
    println("");

    scores.by_plev();
    scores.process([println](size_t n, const bones::bone_t::fakeobj& name, const bones::bone_t::fakeobj& cause,
                             unsigned int plev, int dlev, double worth, bool victory, size_t rcodes) {

                       std::string line1;
                       std::string line2;
                       std::string pad;

                       ++n;

                       if (n < 10)
                           pad = " ";

                       if (victory) {
                           line1 = nlp::message("%s%d) %S, a glorious victor of level %d."_m, pad, n, name, plev+1);
                           line2 = nlp::message("    Last seen on level %d. Net worth: %d $ZM."_m,
                                                dlev+1, worth);

                       } else {
                           line1 = nlp::message("%s%d) %S, level %d."_m, pad, n, name, plev+1);
                           line2 = nlp::message("    Killed on level %d by %s. Net worth: %d $ZM."_m,  
                                                dlev+1, cause, worth);
                       }

                       if (rcodes == 1) {
                           line1 += nlp::message(" (Replay codes were used once.)"_m);

                       } else if (rcodes > 1) {
                           line1 += nlp::message(" (Replay codes were used %d times.)"_m, rcodes);
                       }

                       println(line1);
                       println(line2);
                       println("");
                   });

    println("(Press any key)"_m);

}

#endif
