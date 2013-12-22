#ifndef __FEATURES_H
#define __FEATURES_H

#include <unordered_map>


namespace features {

typedef std::pair<unsigned int, unsigned int> pt;


struct Feature {
    tag_t tag;
    pt xy;
    unsigned int decay;
    unsigned int charges;

    Feature() : xy(0, 0), decay(0), charges(0) {}

    Feature(tag_t _tag, const pt& _xy, unsigned int d, unsigned int c) : 
        tag(_tag), xy(_xy), decay(d), charges(c)
        {}
};


}


namespace serialize {

template <>
struct reader<features::Feature> {
    void read(Source& s, features::Feature& m) {
        serialize::read(s, m.tag);
        serialize::read(s, m.xy);
        serialize::read(s, m.decay);
        serialize::read(s, m.charges);
    }
};

template <>
struct writer<features::Feature> {
    void write(Sink& s, const features::Feature& m) {
        serialize::write(s, m.tag);
        serialize::write(s, m.xy);
        serialize::write(s, m.decay);
        serialize::write(s, m.charges);
    }
};

}


namespace features {

struct Features {

    std::unordered_map<pt, Feature> feats;

    void init() {
        feats.clear();
    }

    void clear() {
        init();
    }

    void x_set(unsigned int x, unsigned int y, tag_t tag, grender::Grid& render) {

        pt xy(x, y);
        if (feats.find(xy) == feats.end()) {
            set(x, y, tag, render);
        }
    }

    void x_unset(unsigned int x, unsigned int y, tag_t tag, grender::Grid& render) {

        pt xy(x, y);
        auto i = feats.find(xy);

        if (i != feats.end() && i->second.tag == tag) {
            feats.erase(i);
            render.invalidate(x, y);
        }
    }

    void set(unsigned int x, unsigned int y, tag_t tag, grender::Grid& render) {

        const Terrain& t = terrain().get(tag);

        pt xy(x, y);
        feats[xy] = Feature(tag, xy, t.decay, t.charges);
        render.invalidate(x, y);
    }

    void unset(unsigned int x, unsigned int y, grender::Grid& render) {

        pt xy(x, y);
        feats.erase(xy);
        render.invalidate(x, y);
    }

    template <typename T>
    bool get_placement(rnd::Generator& rng, grid::Map& grid, T& ptsource,
                       Terrain::placement_t p, pt& ret) {

        switch (p) {

        case Terrain::placement_t::floor:
            if (!ptsource.one_of_floor(rng, ret)) return false;
            break;

        case Terrain::placement_t::water:
            if (!ptsource.one_of_lake(rng, ret)) return false;
            break;

        case Terrain::placement_t::corner:
            if (!ptsource.one_of_corner(rng, ret)) return false;
            break;

        case Terrain::placement_t::lowlands:
            if (!ptsource.one_of_lowlands(rng, ret)) return false;
            break;

        case Terrain::placement_t::shoreline:
            if (!ptsource.one_of_shore(rng, ret)) return false;
            break;
        }

        ptsource.add_nogen(ret.first, ret.second);
        return true;
    }

    template <typename T>
    void generate(rnd::Generator& rng, grid::Map& grid, T& ptsource,
                  tag_t tag, unsigned int n) {

        // Check that the tag exists.
        const Terrain& ter = terrain().get(tag);

        for (unsigned int i = 0; i < n; ++i) {

            pt xy;

            if (!get_placement(rng, grid, ptsource, ter.placement, xy)) 
                break;
            
            const Terrain& t = terrain().get(tag);

            feats[xy] = Feature(tag, xy, t.decay, t.charges);
        }
    }

    bool uncharge(unsigned int x, unsigned int y, grender::Grid& render) {
        auto i = feats.find(pt(x, y));

        if (i == feats.end())
            return false;

        if (i->second.charges > 0) {
            --(i->second.charges);

            if (i->second.charges == 0) {
                feats.erase(i);
                render.invalidate(x, y);
                return false;
            }
        }

        return true;
    }

    bool get(unsigned int x, unsigned int y, Feature& ret) {
        auto i = feats.find(pt(x, y));

        if (i == feats.end()) {
            return false;
        }

        ret = i->second;
        return true;
    }

    template <typename FUNC>
    void process(grender::Grid& render, FUNC f) {

        std::unordered_set<pt> wipe;

        for (auto& i : feats) {
            const Terrain& t = terrain().get(i.second.tag);

            if (!f(i.second, t)) {
                wipe.insert(i.first);
            }
        }

        for (const auto& xy : wipe) {
            feats.erase(xy);
            render.invalidate(xy.first, xy.second);
        }
    }

};

}

namespace serialize {

template <>
struct reader<features::Features> {
    void read(Source& s, features::Features& t) {
        serialize::read(s, t.feats);
    }
};

template <>
struct writer<features::Features> {
    void write(Sink& s, const features::Features& t) {
        serialize::write(s, t.feats);
    }
};

}

#endif
