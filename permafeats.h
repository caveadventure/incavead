#ifndef __PERMAFEATS_H
#define __PERMAFEATS_H

#include "common.h"

#include "worldkey.h"

namespace permafeats {

typedef std::pair<unsigned int, unsigned int> pt;

using key_t = worldkey::key_t;


struct Features {

    static const size_t NUMBER = 150;

    std::unordered_map< key_t, std::unordered_map<pt, tag_t> > data;

    std::mutex mutex;

    template <typename PLAYER>
    void add(const PLAYER& p, tag_t feat) {

        key_t key(p);
        pt xy(p.px, p.py);

        std::unique_lock<std::mutex> l(mutex);

        auto& m = data[key];
        m[xy] = feat;

        while (m.size() > NUMBER) {
            m.erase(m.begin());
        }

        serialize::Sink sink("permafeats.dat", true);
        serialize::write(sink, key);
        serialize::write(sink, xy);
        serialize::write(sink, feat);
    }

    void load() {

        try {
            serialize::Source source("permafeats.dat");

            while (1) {
                try {
                    key_t key;
                    pt xy;
                    tag_t tag;

                    serialize::read(source, key);
                    serialize::read(source, xy);
                    serialize::read(source, tag);

                    data[key][xy] = tag;

                } catch (...) {
                    break;
                }
            }

        } catch (...) {
        }

        for (auto& i : data) {
            while (i.second.size() > NUMBER) {
                i.second.erase(i.second.begin());
            }
        }
    }

    template <typename PLAYER>
    std::unordered_map<pt,tag_t> get(const PLAYER& p) {

        std::unique_lock<std::mutex> l(mutex);
        
        const auto& i = data.find(key_t(p));

        if (i == data.end())
            return std::unordered_map<pt,tag_t>();

        return i->second;
    }
};

Features& features() {
    static Features ret;
    return ret;
}

}


#endif
