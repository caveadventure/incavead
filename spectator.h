#ifndef __SPECTATOR_H
#define __SPECTATOR_H

#include <map>
#include <vector>
#include <mutex>

namespace spectator {

template <typename SCREEN>
struct Screens {

    struct info_t {
        std::string name;
        time_t ts;

        info_t() : ts(0) {}
    };

    std::map<SCREEN*, info_t> screens;

    std::mutex mutex;

    void add(SCREEN& s, const std::string& name) {

        std::unique_lock<std::mutex> l(mutex);

        auto& tmp = screens[&s];
        tmp.name = name;
        tmp.ts = ::time(NULL);
    }

    struct list_entry_t {
        void* tag;
        std::string name;
    };

    std::map< time_t, std::vector<list_entry_t> > list() {

        std::map< time_t, std::vector<list_entry_t> > ret;

        std::unique_lock<std::mutex> l(mutex);

        for (const auto& i : screens) {
            ret[i.second.ts].push_back(list_entry_t{(void*)i.first, i.second.name});
        }

        return ret;
    }

    void remove(SCREEN& s) {

        std::unique_lock<std::mutex> l(mutex);
    
        screens.erase(&s);
    }

    bool link(void* tag, SCREEN& another) {

        std::unique_lock<std::mutex> l(mutex);

        auto i = screens.find((SCREEN*)tag);

        if (i == screens.end())
            return false;

        i->first->links.push_back(&another);
        return true;
    }

    void unlink(void* tag, SCREEN& another) {

        std::unique_lock<std::mutex> l(mutex);

        auto i = screens.find((SCREEN*)tag);

        if (i == screens.end())
            return;

        auto& links = i->first->links;

        auto j = links.begin();
        while (j != links.end()) {

            if (*j == &another) {
                j = links.erase(j);
            } else {
                ++j;
            }
        }
    }

};

template <typename SCREEN>
Screens<SCREEN>& screens() {
    static Screens<SCREEN> ret;
    return ret;
}



template <typename SCREEN>
void choose_and_watch(SCREEN& screen) {

    grender::Grid render;
    render.init(0, 0);

    while (1) {

        time_t now = ::time(NULL);
        auto games = screens<SCREEN>().list();

        std::string window = 
            "Active games:\n"
            " (press space to refresh; when viewing a game, press 'q' to stop and return to this screen.)\n\n";

        char c = 'a';

        std::map<char, void*> games_c;

        for (const auto& i : games) {
            for (const auto& j : i.second) {

                std::string name = j.name;

                if (name.empty()) 
                    name = "anonymous";

                if (name == "_")
                    continue;
                
                window += nlp::message("%c) %S, started playing %d minutes ago.\n", c, name, (now - i.first) / 60);
                games_c[c] = j.tag;
                ++c;
            }
        }

        maudit::keypress k = render.draw_window(screen, window);

        auto i = games_c.find(k.letter);

        if (i != games_c.end() && 
            screens<SCREEN>().link(i->second, screen)) {

            while (1) {

                maudit::keypress k;

                if (!screen.wait_key(k)) {

                    screens<SCREEN>().unlink(i->second, screen);
                    return;

                } else if (k.letter == 'q') {
                    screens<SCREEN>().unlink(i->second, screen);
                    break;
                }
            }
        }
    }
}

}

#endif

