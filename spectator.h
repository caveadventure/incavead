#ifndef __SPECTATOR_H
#define __SPECTATOR_H

#include <map>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>


namespace spectator {


template <typename SCREEN>
struct Screens {

    struct viewer_t {
        viewer_t() {}
    };

    struct data_t {
        std::vector<maudit::glyph> data;
        unsigned int w;
        unsigned int h;
    };

    struct sender_t {
        std::string name;
        time_t ts;

        size_t max_frame;
        size_t min_frame;
        std::map<size_t, data_t> datastream;

        size_t num_viewers;

        sender_t() : ts(0), max_frame(0), min_frame(0), num_viewers(0) {}
    };

    std::map<SCREEN*, sender_t> players;
    std::map<SCREEN*, viewer_t> viewers;

    std::mutex player_mutex;
    std::mutex viewer_mutex;

    void add_player(SCREEN& s, const std::string& name) {

        std::unique_lock<std::mutex> l(player_mutex);

        auto& tmp = players[&s];
        tmp.name = name;
        tmp.ts = ::time(NULL);
    }

    struct list_entry_t {
        void* tag;
        std::string name;
    };

    std::map< time_t, std::vector<list_entry_t> > list_players() {

        std::map< time_t, std::vector<list_entry_t> > ret;

        std::unique_lock<std::mutex> l(player_mutex);

        for (const auto& i : players) {
            ret[i.second.ts].push_back(list_entry_t{(void*)i.first, i.second.name});
        }

        return ret;
    }

    void remove_player(SCREEN& s) {

        std::unique_lock<std::mutex> l(player_mutex);

        auto i = players.find((SCREEN*)tag);

        if (i == players.end())
            return;

        players.erase(i);
    }

    void add_viewer(SCREEN& s) {

        std::unique_lock<std::mutex> l(viewer_mutex);

        auto& tmp = viewers[&s];
        tmp.parent = nullptr;
        tmp.last_frame_no = 0;
    }

    void remove_viewer(SCREEN& s) {

        std::unique_lock<std::mutex> l(viewer_mutex);

        auto i = viewers.find((SCREEN*)tag);

        if (i == viewers.end())
            return;

        viewers.erase(i);
    }

    bool link(void* tag, SCREEN& another) {

        std::unique_lock<std::mutex> l(player_mutex);

        std::unique_lock<std::mutex> l2(viewer_mutex);

        auto i = players.find((SCREEN*)tag);

        if (i == players.end())
            return false;

        auto j = viewers.find(&another);

        if (j == viewers.end()) 
            return false;

        sender_t& sender = i->second;
        viewer_t& viewer = j->second;

        auto& links = sender.links;

        links.push_back(&another);

        viewer.parent = (SCREEN*)tag;
        viewer.last_frame_no = sender.min_frame;

        // HACK
        // Connect parent screen's guts to this machinery.
        if (links.size() == 1) {
            i->first->callback = std::bind(&Screens<SCREEN>::watching_callback, this, std::placeholders::_1, std::placeholders::_2);
        }

        return true;
    }

    void unlink(void* tag, SCREEN& another) {

        std::unique_lock<std::mutex> l(player_mutex);

        std::unique_lock<std::mutex> l2(viewer_mutex);

        auto i = players.find((SCREEN*)tag);

        if (i == players.end())
            return;

        auto j = viewers.find(&another);

        if (j == viewers.end())
            return false;

        sender_t& sender = i->second;
        viewer_t& viewer = j->second;

        viewer.parent = nullptr;
        viewer.last_frame_no = 0;

        auto& links = sender.links;

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


    void watching_callback(SCREEN* parent, sender_t& sender, std::vector<maudit::glyph>& data) {

        std::unique_lock<std::mutex> l(player_mutex);

        auto i = players.find(parent);

        if (i == players.end())
            return;

        sender_t& sender = i->second;

        ++(sender.max_frame);

        auto ds& = sender.datastream[sender.max_frame];
        ds.data.swap(data);
        ds.w = parent->w;
        ds.h = parent->h;
    }


    bool get_next_data(void* tag, data_t& out, size_t last_frame_no) {

        SCREEN* parent = (SCREEN*)tag;

        std::unique_lock<std::mutex> l(players_mutex);

        auto i = players.find(parent);

        if (i == players.end()) 
            return false;
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
void watcher_input_thread(SCREEN& screen) {

    while (1) {

    }
}


template <typename SCREEN>
void choose_and_watch(SCREEN& screen) {

    grender::Grid render;
    render.init(0, 0);

    screens<SCREEN>().add_watcher(screen);
    std::thread thread(watcher_input_thread<SCREEN>, &screen);

    bool done = false;

    while (!done) {

        time_t now = ::time(NULL);
        auto games = screens<SCREEN>().list_players();

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

        try {

            maudit::keypress k = render.draw_window(screen, window);

            auto i = games_c.find(k.letter);

            if (i != games_c.end()) {

                while (1) {

                    Screens<SCREEN>::data_t data;

                    if (!screens<SCREEN>().get_next_data(i->second, data)) {
                        // Spin about doing nothing, keeping the last screen in view.
                        ::sleep(1);
                        continue;
                    }

                    if (!copy_screen(data.data, data.w, data.h, screen)) {
                        done = true;
                        break;
                    }
                }
            }

        } catch (...) {
            done = true;
        }
    }

    screens<SCREEN>().remove_watcher(screen);
    thread.join();

}

}

#endif

