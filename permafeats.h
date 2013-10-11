#ifndef __PERMAFEATS_H
#define __PERMAFEATS_H

#include <list>

#include "common.h"

#include "worldkey.h"

namespace permafeats {

typedef std::pair<unsigned int, unsigned int> pt;

using key_t = worldkey::key_t;


struct Features {

    // HACK TODO WARNING
    // Magic number
    static const size_t NUMBER = 150;

    struct q_t {
        std::list< std::pair<pt, tag_t> > l;
        size_t size;

        q_t() : size(0) {}
    };

    std::unordered_map<key_t, q_t> data;

    std::mutex mutex;

    template <typename PLAYER>
    void add(const PLAYER& p, tag_t feat) {

        key_t key(p);
        pt xy(p.px, p.py);

        std::unique_lock<std::mutex> l(mutex);

        auto& m = data[key];
        m.l.push_back(std::make_pair(xy, feat));
        ++m.size;

        while (m.size > NUMBER) {
            m.l.pop_front();
            --m.size;
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

                    auto& m = data[key];
                    m.l.push_back(std::make_pair(xy, tag));
                    ++m.size;

                } catch (...) {
                    break;
                }
            }

        } catch (...) {
        }

        for (auto& i : data) {
            while (i.second.size > NUMBER) {
                i.second.l.pop_front();
                --i.second.size;
            }
        }
    }

    template <typename PLAYER>
    std::vector< std::pair<pt,tag_t> > get(const PLAYER& p) {

        std::vector< std::pair<pt,tag_t> > ret;

        std::unique_lock<std::mutex> l(mutex);
        
        const auto& i = data.find(key_t(p));

        if (i != data.end()) {
            ret.assign(i->second.l.begin(), i->second.l.end());
        }

        return ret;
    }
};

Features& features() {
    static Features ret;
    return ret;
}

}


#endif
