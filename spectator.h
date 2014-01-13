#ifndef __SPECTATOR_H
#define __SPECTATOR_H

#include <map>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <functional>


namespace spectator {


template <typename SCREEN>
struct Screens {

    struct data_t {
        std::vector<maudit::glyph> data;
        unsigned int w;
        unsigned int h;
    };

    struct sender_t {
        std::string name;
        time_t ts;

        size_t max_frame;
        std::map<size_t, data_t> datastream;
        size_t refcount;
        std::condition_variable cv;

        sender_t() : ts(0), max_frame(0), refcount(0) {}
    };

    std::map<SCREEN*, sender_t> players;

    std::mutex player_mutex;

    std::map< SCREEN*, std::vector<std::string> > messages;

    std::mutex message_mutex;

    void add(SCREEN& s, const std::string& name) {

        std::unique_lock<std::mutex> l(player_mutex);

        auto& tmp = players[&s];
        tmp.name = name;
        tmp.ts = ::time(NULL);

        // HACK
        // Connect parent screen's guts to this machinery.
        s.callback = std::bind(&Screens<SCREEN>::watching_callback, this, 
                               std::placeholders::_1, std::placeholders::_2);
    }

    struct list_entry_t {
        void* tag;
        std::string name;
    };

    std::map< time_t, std::vector<list_entry_t> > list() {

        std::map< time_t, std::vector<list_entry_t> > ret;

        std::unique_lock<std::mutex> l(player_mutex);

        for (const auto& i : players) {
            ret[i.second.ts].push_back(list_entry_t{(void*)i.first, i.second.name});
        }

        return ret;
    }

    void remove(SCREEN& s) {

        std::unique_lock<std::mutex> l(player_mutex);

        auto i = players.find(&s);

        if (i == players.end())
            return;

        i->first->callback = nullptr;
        i->second.cv.notify_all();

        players.erase(i);
    }

    bool link(void* tag, SCREEN& another) {

        std::unique_lock<std::mutex> l(player_mutex);

        auto i = players.find((SCREEN*)tag);

        if (i == players.end())
            return false;

        sender_t& sender = i->second;

        sender.refcount++;

        return true;
    }

    void unlink(void* tag, SCREEN& another) {

        std::unique_lock<std::mutex> l(player_mutex);

        auto i = players.find((SCREEN*)tag);

        if (i == players.end())
            return;

        sender_t& sender = i->second;

        sender.refcount--;
    }

    bool notify(void* tag) {
        std::unique_lock<std::mutex> l(player_mutex);

        auto i = players.find((SCREEN*)tag);

        if (i == players.end())
            return false;

        sender_t& sender = i->second;

        sender.cv.notify_all();

        return true;
    }

    void send_message(void* tag, const std::string& message) {
        std::unique_lock<std::mutex> l(message_mutex);

        messages[(SCREEN*)tag].push_back(message);
    }

    bool get_messages(SCREEN& tag, std::vector<std::string>& out) {
        std::unique_lock<std::mutex> l(message_mutex);

        auto i = messages.find(&tag);

        if (i != messages.end()) {
            messages[&tag].swap(out);
            return true;
        }

        return false;
    }

    // HARCODED VALUES
    static const size_t MAX_FRAMES = 5;

    void watching_callback(SCREEN* parent, std::vector<maudit::glyph>& data) {

        std::unique_lock<std::mutex> l(player_mutex);

        auto i = players.find(parent);

        if (i == players.end())
            return;

        sender_t& sender = i->second;

        ++(sender.max_frame);

        auto& ds = sender.datastream[sender.max_frame];
        ds.data.swap(data);
        ds.w = parent->w;
        ds.h = parent->h;

        while (sender.datastream.size() > MAX_FRAMES) {
            sender.datastream.erase(sender.datastream.begin());
        }

        sender.cv.notify_all();
    }

    // Tri-state return value:
    // -1 means a lost connection,
    // 1 means a valid frame,
    // 0 means we tried to wait for a frame and need to call this function again. (No frame is returned.)

    int get_next_data(void* tag, data_t& out, size_t& last_frame_no) {

        SCREEN* parent = (SCREEN*)tag;

        std::unique_lock<std::mutex> l(player_mutex);

        std::cout << " | locked " << last_frame_no << std::endl;

        auto i = players.find(parent);

        if (i == players.end()) {
            std::cout << " | oops, no tag" << std::endl;
            return -1;
        }

        sender_t& sender = i->second;

        auto j = sender.datastream.upper_bound(last_frame_no);

        if (j == sender.datastream.end()) {
            std::cout << " | no frame found, waiting" << std::endl;
            sender.cv.wait(l);
            return 0;
        }

        out = j->second;
        last_frame_no = j->first;

        std::cout << " | frame found, ok" << std::endl;

        return 1;
    }
};

template <typename SCREEN>
Screens<SCREEN>& screens() {
    static Screens<SCREEN> ret;
    return ret;
}

void add_message_line(std::vector<maudit::glyph>& data, unsigned int w, unsigned int h, const std::string& message) {

    if (message.empty())
        return;

    if (w < 5)
        return;

    size_t x = 0;
    size_t i = (h - 1) * w;

    std::string gt(">");
    std::string space(" ");

    while (x < 3) {
        data[i].text = gt;
        data[i].fore = maudit::color::bright_yellow;
        data[i].back = maudit::color::bright_black;
        ++x;
        ++i;
    }

    data[i].text = space;
    data[i].fore = maudit::color::bright_yellow;
    data[i].back = maudit::color::bright_black;
    ++x;
    ++i;

    for (unsigned char c : message) {

        if (x >= w)
            break;

        data[i].text = std::string(1, c);
        data[i].fore = maudit::color::bright_white;
        data[i].back = maudit::color::bright_black;
        ++x;
        ++i;
    }

    while (x < w) {
        data[i].text = space;
        data[i].fore = maudit::color::bright_white;
        data[i].back = maudit::color::bright_black;
        ++x;
        ++i;
    }
}

template <typename SCREEN>
bool copy_screen(const std::vector<maudit::glyph>& data, const std::string& message, 
                 unsigned int ow, unsigned int oh, SCREEN& target) {

    if (target.w == ow && target.h == oh && message.empty()) {
        return target.send_screen(data);
    }

    unsigned int tw = target.w;
    unsigned int th = target.h;

    std::vector<maudit::glyph> temp;
    temp.resize(tw * th);

    unsigned int truw = std::min(tw, ow);
    unsigned int truh = std::min(th, oh);

    // Clip to an even-sized width.
    if (tw < ow && (truw & 1)) {
        truw--;
    }

    for (unsigned int y = 0; y < truh; ++y) {
        auto i = temp.begin() + (y * tw);
        auto j = data.begin() + (y * ow);

        for (unsigned int x = 0; x < truw; ++x) {
            *i = *j;
            ++i;
            ++j;
        }
    }

    add_message_line(temp, tw, th, message);

    return target.send_screen(temp);
}

template <typename SCREEN>
void watcher_input_thread(SCREEN& screen, void* tag, std::mutex& mutex, bool& done, std::string& message) {

    while (1) {

        maudit::keypress k;

        std::cout << "+  waiting for key" << std::endl;
        if (!screen.wait_key(k) || k.key == maudit::keycode::esc) {

            screens<SCREEN>().notify(tag);

            std::cout << "Got 'ESC'!" << std::endl;
            std::unique_lock<std::mutex> l(mutex);
            done = true;
            return;
        }

        std::cout << "Keypress: " << k.letter << std::endl;

        unsigned char cc = '\0';

        if (k.letter == '\n' || (k.letter >= ' ' && k.letter <= '~')) {
            cc = k.letter;

        } else if (k.letter == '\x7F' || k.letter == '\x08' || k.key == maudit::keycode::del) {
            cc = '\x08';
        }

        std::unique_lock<std::mutex> l(mutex);

        if (done)
            return;

        if (cc == '\n') {
            screens<SCREEN>().send_message(tag, message);
            message.clear();
            screens<SCREEN>().notify(tag);

        } else if (cc == '\x08' && message.size() > 0) {
            message.resize(message.size() - 1);
            screens<SCREEN>().notify(tag);

        } else if (cc != '\0' && message.size() < 60) {
            message += cc;
            screens<SCREEN>().notify(tag);
        }
        
    }
}


template <typename SCREEN>
void choose_and_watch(SCREEN& screen) {

    grender::Grid render;
    render.init(0, 0);

    while (1) {

        time_t now = ::time(NULL);
        auto games = screens<SCREEN>().list();

        std::string window = 
            "   When viewing a game, press 'ESC' twice to stop and return to this screen.\n"
            "   Simply start typing and press 'Enter' to send a chat message.\n\n"
            "Active games: (press space to refresh)\n\n";

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

        maudit::keypress k;

        try {

            k = render.draw_window(screen, window);

        } catch (...) {
            return;
        }

        auto i = games_c.find(k.letter);
        
        if (i == games_c.end())
            continue;

        void* parent = i->second;

        {
            std::cout << "start loop" << std::endl;
            std::mutex mutex;
            bool done = false;
            std::string message;

            screens<SCREEN>().link(parent, screen);

            std::thread thread(watcher_input_thread<SCREEN>, 
                               std::ref(screen), parent, std::ref(mutex), std::ref(done), std::ref(message));


            typename Screens<SCREEN>::data_t data;
            size_t last_frame_no = 0;

            while (1) {

                std::string tmp;

                {
                    std::unique_lock<std::mutex> l(mutex);

                    if (done)
                        break;

                    tmp = message;
                }

                std::cout << "get_next_data()" << std::endl;

                int ret = screens<SCREEN>().get_next_data(parent, data, last_frame_no);

                if (ret < 0) {
                    // Lost connection.
                    // Spin about doing nothing, keeping the last screen in view.
                    ::sleep(1);
                    continue;
                }

                std::cout << "copy_screen()" << std::endl;

                if (!copy_screen(data.data, message, data.w, data.h, screen)) {
                    std::unique_lock<std::mutex> l(mutex);
                    done = true;
                    break;
                }
            }

            std::cout << "loop done" << std::endl;

            thread.join();
            screens<SCREEN>().unlink(parent, screen);

            std::cout << "ok!" << std::endl;
        }
    }
}

}

#endif

