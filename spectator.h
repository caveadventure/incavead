#ifndef __SPECTATOR_H
#define __SPECTATOR_H

#include <map>
#include <vector>
#include <mutex>
#include <functional>

namespace spectator {


struct lo_fi_rw_mutex {

    std::mutex mutex;
    size_t reading;

    lo_fi_rw_mutex() : reading(0) {}

    struct r_lock {
        lo_fi_rw_mutex& self;

        r_lock(lo_fi_rw_mutex& s) : self(s) {
            self.mutex.lock();
            self.reading++;
            self.mutex.unlock();
        }

        ~r_lock() {
            self.mutex.lock();
            self.reading--;
            self.mutex.unlock();
        }
    };

    struct w_lock {
        lo_fi_rw_mutex& self;

        w_lock(lo_fi_rw_mutex& s) : self(s) {

            while (1) {
                self.mutex.lock();

                if (self.reading > 0) {
                    self.mutex.unlock();
                    continue;
                }
                
                break;
            }
        }

        ~w_lock() {
            self.mutex.unlock();
        }
    };
};


template <typename SCREEN>
bool copy_screen(const std::vector<maudit::glyph>& data, unsigned int ow, unsigned int oh, SCREEN& target);

template <typename SCREEN>
struct Screens {

    struct info_t {
        std::string name;
        time_t ts;

        std::vector<SCREEN*> links;

        info_t() : ts(0) {}
    };

    std::map<SCREEN*, info_t> screens;

    //std::mutex mutex;
    lo_fi_rw_mutex mutex;

    void add(SCREEN& s, const std::string& name) {

        //std::unique_lock<std::mutex> l(mutex);
        lo_fi_rw_mutex::w_lock l(mutex);

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

        //std::unique_lock<std::mutex> l(mutex);
        lo_fi_rw_mutex::w_lock l(mutex);

        for (const auto& i : screens) {
            ret[i.second.ts].push_back(list_entry_t{(void*)i.first, i.second.name});
        }

        return ret;
    }

    void remove(SCREEN& s) {

        //std::unique_lock<std::mutex> l(mutex);
        lo_fi_rw_mutex::w_lock l(mutex);

        screens.erase(&s);
    }

    bool link(void* tag, SCREEN& another) {

        //std::unique_lock<std::mutex> l(mutex)
        lo_fi_rw_mutex::w_lock l(mutex);

        auto i = screens.find((SCREEN*)tag);

        if (i == screens.end())
            return false;

        i->second.links.push_back(&another);

        i->first->callback = std::bind(&Screens<SCREEN>::watching_callback, 
                                       this, std::placeholders::_1, std::placeholders::_2);

        return true;
    }

    void unlink(void* tag, SCREEN& another) {

        //std::unique_lock<std::mutex> l(mutex);
        lo_fi_rw_mutex::w_lock l(mutex);

        auto i = screens.find((SCREEN*)tag);

        if (i == screens.end())
            return;

        auto& links = i->second.links;

        auto j = links.begin();
        while (j != links.end()) {

            if (*j == &another) {
                j = links.erase(j);
            } else {
                ++j;
            }
        }

        if (links.empty()) {
            i->first->callback = nullptr;
        }
    }


    void watching_callback(SCREEN* parent, const std::vector<maudit::glyph>& data) {

        // TODO: This really needs read-write locks.

        //std::unique_lock<std::mutex> l(mutex);
        lo_fi_rw_mutex::r_lock l(mutex);

        auto i = screens.find(parent);

        if (i == screens.end())
            return;

        auto& links = i->second.links;

        auto li = links.begin();
        while (li != links.end()) {
            auto& l = **li;

            if (!copy_screen(data, parent->w, parent->h, l)) {
                li = links.erase(li);
            } else {
                ++li;
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
bool copy_screen(const std::vector<maudit::glyph>& data, unsigned int ow, unsigned int oh, SCREEN& target) {

    if (target.w == ow && target.h == oh) {
        return target.send_screen(data);
    }

    std::vector<maudit::glyph> temp;
    temp.resize(target.w * target.h);

    unsigned int truw = std::min(target.w, ow);
    unsigned int truh = std::min(target.h, oh);

    // Clip to an even-sized width.
    if (target.w < ow && (truw & 1)) {
        truw--;
    }

    for (unsigned int y = 0; y < truh; ++y) {
        auto i = temp.begin() + (y * target.w);
        auto j = data.begin() + (y * ow);

        for (unsigned int x = 0; x < truw; ++x) {
            *i = *j;
            ++i;
            ++j;
        }
    }

    return target.send_screen(temp);
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

