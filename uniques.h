#ifndef __UNIQUES_H
#define __UNIQUES_H

#include <time.h>

#include <sstream>
#include <mutex>

#include <unordered_map>

#include "items.h"


namespace uniques {

struct key_t {

    int wx;
    int wy;
    int wz;

    bool operator==(const key_t& a) const {
        return (wx == a.wx && wy == a.wy && wz == a.wz);
    }
};

}

namespace std {

template <>
struct hash<uniques::key_t> {
    size_t operator()(const uniques::key_t& k) const {
        return hash<int>()(k.wx) + hash<int>()(k.wy) + hash<int>()(k.wz);
    }
};

}


namespace serialize {

template <>
struct reader<uniques::key_t> {
    void read(Source& s, uniques::key_t& t) {
        serialize::read(s, t.wx);
        serialize::read(s, t.wy);
        serialize::read(s, t.wz);
    }
};

template <>
struct writer<uniques::key_t> {
    void write(Sink& s, const uniques::key_t& t) {
        serialize::write(s, t.wx);
        serialize::write(s, t.wy);
        serialize::write(s, t.wz);
    }
};

}

namespace uniques {

struct Uniques {

    std::unordered_map< key_t, std::vector<items::Item> > data;
    
    size_t series;;
    time_t placetime;

    std::mutex mutex;

    void load() {

        std::unique_lock<std::mutex> l(mutex);

        try {

            serialize::Source source("uniques.dat");
            serialize::read(source, data);
            serialize::read(source, series);
            serialize::read(source, placetime);

        } catch (...) {
            data.clear();
            series = 1;
            placetime = 0;
        }
    }

private:

    void write() {
        serialize::Sink sink("uniques.dat");
        serialize::write(sink, data);
        serialize::write(sink, series);
        serialize::write(sink, placetime);
    }

public:

    
    std::vector<items::Item> get(int wx, int wy, int wz, size_t& out_series) {

        std::unique_lock<std::mutex> l(mutex);

        auto i = data.get(key_t{wx, wy, wz});

        if (i == data.end())
            return std::vector<items::Item>();

        auto ret = i->second;
        out_series = series;

        data.erase(i);

        write();

        return ret;
    }

    void put(int wx, int wy, int wz, const std::vector<items::Item>& i, size_t in_series) {

        std::unique_lock<std::mutex> l(mutex);

        if (series != in_series) {
            return;
        }

        data[key_t{wx, wy, wz}].insert(i.begin(), i.end());

        placetime = ::time(NULL);

        write();
    }

    bool generate(time_t timeout, size_t& out_series) {

        time_t now = ::time(NULL);

        std::unique_lock<std::mutex> l(mutex);

        if (data.empty() && (now - placetime) > timeout) {
            placetime = now;
            ++series;
            out_series = series;
            write();
            return true;
        }

        return false;
    }
};


Uniques& uniques() {
    static Uniques ret;
    return ret;
}

}


#endif
