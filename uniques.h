#ifndef __UNIQUES_H
#define __UNIQUES_H

#include <time.h>

#include <sstream>
#include <mutex>

#include <unordered_map>

#include "items.h"

#include "worldkey.h"


namespace uniques {

using key_t = worldkey::key_t;


struct Uniques {

    std::unordered_map< key_t, std::vector<items::Item> > data;

    std::string filename;

    Uniques(const std::string& fn) : filename(fn) {}
    
    size_t series;;
    time_t placetime;

    std::mutex mutex;

    void load() {

        std::unique_lock<std::mutex> l(mutex);

        try {

            serialize::Source source(filename);
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
        serialize::Sink sink(filename);
        serialize::write(sink, data);
        serialize::write(sink, series);
        serialize::write(sink, placetime);
    }

public:

    
    std::vector<items::Item> get(int wx, int wy, int wz, size_t& out_series) {

        std::unique_lock<std::mutex> l(mutex);

        auto i = data.find(key_t(wx, wy, wz));

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

        auto& v = data[key_t(wx, wy, wz)];
        v.insert(v.end(), i.begin(), i.end());

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
    static Uniques ret("uniques.dat");
    return ret;
}

Uniques& items() {
    static Uniques ret("permaitems.dat");
    return ret;
}

}


#endif
