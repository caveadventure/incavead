#ifndef __NEIGHBORS_H
#define __NEIGHBORS_H

#include <vector>
#include <unordered_map>
#include <set>


namespace neighbors {

typedef std::pair<unsigned int, unsigned int> pt;


struct Neighbors {
    
    typedef std::pair<int, int> p0_t;

    typedef std::unordered_map< pt, std::set<p0_t> > ns_t;
    ns_t nbmap;
    std::set<p0_t> defaults;
    unsigned int w;
    unsigned int h;

    void init(unsigned int _w, unsigned int _h) {

        w = _w;
        h = _h;

        for (int xi = -1; xi <= 1; xi++) {
            for (int yi = -1; yi <= 1; yi++) { 

                if (xi == 0 && yi == 0) continue;

                defaults.insert(p0_t(xi, yi));
            }
        }

        nbmap.clear();

        for (unsigned int x = 0; x < w; x++) {
            for (unsigned int y = 0; y < h; y++) {

                if (x > 0 && x < w - 1 && 
                    y > 0 && y < h - 1)
                    continue;

                auto& v = nbmap[std::make_pair(x, y)];

                for (int xi = -1; xi <= 1; xi++) {
                    for (int yi = -1; yi <= 1; yi++) { 

                        if (xi == 0 && yi == 0) continue;

                        p0_t tmp(x+xi, y+yi);

                        if (tmp.first < 0 || tmp.first >= (int)w || tmp.second < 0 || tmp.second >= (int)h)
                            continue;

                        v.insert(v.end(), p0_t(xi, yi));
                    }
                }
            }
        }
    }

    void clear() {
        init(w, h);
    }

    const std::set<p0_t>& operator()(const pt& xy) const {

        ns_t::const_iterator i = nbmap.find(xy);

        if (i != nbmap.end()) {
            return i->second;
	}
        
        return defaults;
    }

    static pt mk(const p0_t& off, unsigned int x, unsigned int y) {
        return pt(off.first + x, off.second + y);
    }

    static pt mk(const p0_t& off, const pt& xy) {
        return pt(off.first + xy.first, off.second + xy.second);
    }

    bool linked(const pt& xy1, const pt& xy2) const {

        ns_t::const_iterator i = nbmap.find(xy1);

        if (i == nbmap.end())
            return true;

        p0_t tmp((int)xy2.first - (int)xy1.first, (int)xy2.second - (int)xy1.second);

        return i->second.count(tmp);
    }

};

}


namespace serialize {

template <>
struct reader<neighbors::Neighbors> {
    void read(Source& s, neighbors::Neighbors& t) {
        serialize::read(s, t.w);
        serialize::read(s, t.h);
        t.init(t.w, t.h);
    }
};

template <>
struct writer<neighbors::Neighbors> {
    void write(Sink& s, const neighbors::Neighbors& t) {
        serialize::write(s, t.w);
        serialize::write(s, t.h);
    }
};

}

#endif
