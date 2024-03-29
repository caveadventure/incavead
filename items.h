#ifndef __ITEMS_H
#define __ITEMS_H

#include <unordered_map>


namespace items {

typedef std::pair<unsigned int, unsigned int> pt;


struct Item {
    tag_t tag;
    pt xy;
    uint32_t count;

    Item() : xy(0, 0), count(1) {}

    Item(tag_t _tag, const pt& _xy, unsigned int c = 1) : 
        tag(_tag), xy(_xy), count(c)
        {}
};


}


namespace serialize {

template <>
struct reader<items::Item> {
    void read(Source& s, items::Item& m) {
        serialize::read(s, m.tag);
        serialize::read(s, m.xy);
        serialize::read(s, m.count);
    }
};

template <>
struct writer<items::Item> {
    void write(Sink& s, const items::Item& m) {
        serialize::write(s, m.tag);
        serialize::write(s, m.xy);
        serialize::write(s, m.count);
    }
};

}


namespace items {

struct Items {

    std::unordered_map< pt, std::vector<Item> > stuff;

    void init() {
        stuff.clear();
    }

    void clear() {
        init();
    }

    Item make_item(tag_t tag, const pt& xy, rnd::Generator& rng) {

        const Design& d = designs().get(tag);

        uint32_t _c = 1;

        if (d.count_is_rcode) {

            _c = rng.range(0u, 0xFFFFFFFF);

        } else {
            double mean = d.gencount.mean;
            double dev = d.gencount.deviation;

            if (dev == 0) {
                _c = mean;

            } else {
                _c = rng.gauss(mean, dev);
            }
            
            if (_c > d.stackrange)
                _c = d.stackrange;

            if (_c <= 0)
                _c = 1;
        }

        return Item(tag, xy, _c);
    }


    template <typename T>
    void generate(neighbors::Neighbors& neigh, rnd::Generator& rng, grid::Map& grid, T& ptsource,
                  counters::Counts& counts, unsigned int level, unsigned int n, bool exclusive) {

        std::map<tag_t, unsigned int> q = counts.take(rng, level, n, exclusive);

        for (const auto& i : q) {

            for (unsigned int j = 0; j < i.second; ++j) {

                pt xy;
                if (!ptsource.one_of_floor(rng, xy))
                    return;

                stuff[xy].push_back(make_item(i.first, xy, rng));
            }
        }
    }

    size_t stack_size(unsigned int x, unsigned int y) const {
        auto i = stuff.find(pt(x, y));

        if (i == stuff.end()) {
            return false;
        }

        return i->second.size();
    }

    bool get(unsigned int x, unsigned int y, unsigned int z, Item& ret) const {
        auto i = stuff.find(pt(x, y));

        if (i == stuff.end() || z >= i->second.size()) {
            return false;
        }

        auto j = i->second.rbegin() + z;
        ret = *j;
        return true;
    }

    bool take(unsigned int x, unsigned int y, unsigned int z, Item& ret, grender::Grid& grid) {
        auto i = stuff.find(pt(x, y));

        if (i == stuff.end() || z >= i->second.size()) {
            return false;
        }

        auto j = i->second.rbegin() + z;
        ret = *j;
        i->second.erase(j.base()-1);

        if (i->second.empty())
            stuff.erase(i);
        
        grid.invalidate(x, y);

        return true;
    }

    template <typename FUNC>
    size_t consume(grender::Grid& grid, FUNC f) {

        size_t ret = 0;

        for (auto& j : stuff) {

            for (auto i = j.second.begin(); i != j.second.end(); ) {

                bool wipe = f(*i);

                if (wipe) {
                    i = j.second.erase(i);

                    grid.invalidate(j.first.first, j.first.second);
                    ret++;

                } else {
                    ++i;
                }
            }
        }

        return ret;
    }

    void place(unsigned int x, unsigned int y, const Item& i, grender::Grid& grid) {

        grid.invalidate(x, y);

        auto j = stuff.find(pt(x, y));

        if (j == stuff.end()) {

            auto& v = stuff[pt(x, y)];
            v.push_back(i);
            v.back().xy = pt(x, y);
            return;
        }

        const Design& d = designs().get(i.tag);
        unsigned int icount = i.count;

        for (Item& it : j->second) {

            if (it.tag == i.tag && it.count < d.stackrange) {

                unsigned int n = std::min(icount, d.stackrange - it.count);
                it.count += n;
                icount -= n;

                if (icount == 0)
                    return;
            }
        }

        j->second.push_back(i);
        j->second.back().xy = pt(x, y);
        j->second.back().count = icount;
    }

    template <typename FUNC>
    void dispose(counters::Counts& counts, FUNC callback) {

        for (const auto& j : stuff) {
            for (const Item& i : j.second) {

                if (!callback(i))
                    continue;

                const Design& d = designs().get(i.tag);
                counts.replace(d.level, d.tag);
            }
        }
    }

};

}

namespace serialize {

template <>
struct reader<items::Items> {
    void read(Source& s, items::Items& t) {
        serialize::read(s, t.stuff);
    }
};

template <>
struct writer<items::Items> {
    void write(Sink& s, const items::Items& t) {
        serialize::write(s, t.stuff);
    }
};

}


#endif
