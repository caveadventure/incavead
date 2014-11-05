#ifndef __PERMAFEATS_H
#define __PERMAFEATS_H

#include <list>
#include <mutex>

#include "common.h"

#include "worldkey.h"

namespace permafeats {

typedef std::pair<unsigned int, unsigned int> pt;

using key_t = worldkey::key_t;

struct tristate_t {
    int v;

    tristate_t() : v(-1) {}
    tristate_t(bool _v) : v(_v ? 1 : 0) {}

    bool is(bool x) const {
        return (v >= 0 && (x ? v == 1 : v == 0));
    }

    bool set() const {
        return (v >= 0);
    }
    
    void set(tristate_t x) {
        if (x.v >= 0)
            v = x.v;
    }
};


struct Features {

    static const size_t NUMBER = 300;

    struct terrain_t {
        tag_t feat;
        tristate_t walk;
        tristate_t water;
        tristate_t label;
        std::string text;
    };

    struct q_t {
        std::list< std::pair<pt, terrain_t> > l;
        size_t size;

        q_t() : size(0) {}
    };

    std::unordered_map<key_t, q_t> data;

    std::mutex mutex;

    size_t max_level_feats;

    Features() : max_level_feats(NUMBER) {}

    void _append(const key_t& key, const pt& xy,
                 tag_t feat, tristate_t walk, tristate_t water, tristate_t label, const std::string& text) {

        auto& m = data[key];

        if (m.size > 0 && m.l.back().first == xy) {

            terrain_t& last = m.l.back().second;

            if (!feat.null()) {
                last.feat = feat;
            }

            last.walk.set(walk);
            last.water.set(water);
            last.label.set(label);
            
            if (label.is(true)) {
                last.text = text;
            }

        } else {
        
            m.l.push_back(std::make_pair(xy, terrain_t{feat, walk, water, label, text}));
            ++m.size;

            while (m.size > max_level_feats) {
                m.l.pop_front();
                --m.size;
            }
        }
    }

    
    template <typename PLAYER>
    void add(const PLAYER& p, unsigned int x, unsigned int y,
             tag_t feat, tristate_t walk, tristate_t water, tristate_t label, const std::string& text = "") {

        key_t key(p);
        pt xy(x, y);

        std::unique_lock<std::mutex> l(mutex);

        _append(key, xy, feat, walk, water, label, text);

        serialize::Sink sink("permafeats.dat", true);
        serialize::write(sink, key);
        serialize::write(sink, xy);
        serialize::write(sink, feat);
        serialize::write(sink, walk.v);
        serialize::write(sink, water.v);
        serialize::write(sink, label.v);
        
        if (label.is(true)) {
            serialize::write(sink, text);
        }
    }

    template <typename PLAYER>
    void add(const PLAYER& p, unsigned int x, unsigned int y, tag_t feat) {
        add(p, x, y, feat, tristate_t(), tristate_t(), tristate_t());
    }

    template <typename PLAYER>
    void add(const PLAYER& p, unsigned int x, unsigned int y, bool walk, bool water) {
        add(p, x, y, tag_t(), walk, water, tristate_t());
    }

    template <typename PLAYER>
    void add(const PLAYER& p, unsigned int x, unsigned int y, const std::string& label) {
        add(p, x, y, tag_t(), tristate_t(), tristate_t(), tristate_t(!label.empty()), label);
    }

    template <typename PLAYER>
    void add(const PLAYER& p, tag_t feat) {
        add(p, p.px, p.py, feat);
    }

    template <typename PLAYER>
    void add(const PLAYER& p, bool walk, bool water) {
        add(p, p.px, p.py, walk, water);
    }

    template <typename PLAYER>
    void add(const PLAYER& p, const std::string& label) {
        add(p, p.px, p.py, label);
    }

    void load(size_t _max = NUMBER) {

        max_level_feats = _max;

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

                    tristate_t walk;
                    tristate_t water;
                    tristate_t label;

                    serialize::read(source, walk.v);
                    serialize::read(source, water.v);
                    serialize::read(source, label.v);

                    std::string text;

                    if (label.is(true)) {
                        serialize::read(source, text);
                    }

                    _append(key, xy, tag, walk, water, label, text);

                } catch (...) {
                    break;
                }
            }

        } catch (...) {
        }
    }

    template <typename PLAYER>
    std::vector< std::pair<pt,terrain_t> > get(const PLAYER& p) {

        std::vector< std::pair<pt,terrain_t> > ret;

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
