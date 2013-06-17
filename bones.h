#ifndef __BONES_H
#define __BONES_H

#include <list>
#include <mutex>

namespace bones {

typedef std::pair<unsigned int, unsigned int> pt;

struct key_t {

    int worldx;
    int worldy;
    int worldz;

    key_t(int x = 0, int y = 0, int z = 0) : worldx(x), worldy(y), worldz(z)
        {}
        
    template <typename PLAYER>
    key_t(const PLAYER& p) :
        worldx(p.worldx), worldy(p.worldy), worldz(p.worldz)
        {}

    bool operator<(const key_t& a) const {
        if (worldz < a.worldz) return true;
        if (worldz == a.worldz && worldx < a.worldx) return true;
        if (worldz == a.worldz && worldx == a.worldx && worldy < a.worldy) return true;
        return false;
    }
};

struct bone_t {

    struct fakeobj {
        std::string name;
        fakeobj() {}
        fakeobj(const std::string& s) : name(s) {}
    };

    fakeobj name;
    unsigned int level;
    fakeobj cause;
    double worth;

    bone_t() : level(0), worth(0)
        {}

    template <typename PLAYER>
    bone_t(const std::string& _name, const PLAYER& p) :
        name(_name), level(p.level), cause(p.attacker), worth(p.inv.get_worth())
        {}
};

}


namespace serialize {

template <>
struct reader<bones::key_t> {
    void read(Source& s, bones::key_t& t) {
        serialize::read(s, t.worldx);
        serialize::read(s, t.worldy);
        serialize::read(s, t.worldz);
    }
};

template <>
struct writer<bones::key_t> {
    void write(Sink& s, const bones::key_t& t) {
        serialize::write(s, t.worldx);
        serialize::write(s, t.worldy);
        serialize::write(s, t.worldz);
    }
};

template <>
struct reader<bones::bone_t> {
    void read(Source& s, bones::bone_t& t) {
        serialize::read(s, t.name.name);
        serialize::read(s, t.level);
        serialize::read(s, t.cause.name);
        serialize::read(s, t.worth);
    }
};

template <>
struct writer<bones::bone_t> {
    void write(Sink& s, const bones::bone_t& t) {
        serialize::write(s, t.name.name);
        serialize::write(s, t.level);
        serialize::write(s, t.cause.name);
        serialize::write(s, t.worth);
    }
};

}


namespace bones {

struct Bones {

    std::map< key_t, std::unordered_map<pt, bone_t> > data;
    
    std::mutex mutex;

    template <typename PLAYER>
    void add(const std::string& name, const PLAYER& p) {

        key_t key(p);
        pt xy(p.px, p.py);
        bone_t bone(name, p);

        std::unique_lock<std::mutex> l(mutex);

        auto& m = data[key];
        m[xy] = bone;

        while (m.size() > 1000) {
            m.erase(m.begin());
        }

        serialize::Sink sink("bones.dat", true);
        serialize::write(sink, key);
        serialize::write(sink, xy);
        serialize::write(sink, bone);
    }

    void load() {

        try {
            serialize::Source source("bones.dat");

            while (1) {
                try {
                    key_t key;
                    pt xy;
                    bone_t bone;

                    serialize::read(source, key);
                    serialize::read(source, xy);
                    serialize::read(source, bone);

                    data[key][xy] = bone;

                } catch (...) {
                    break;
                }
            }

        } catch (...) {
        }

        for (auto& i : data) {
            while (i.second.size() > 1000) {
                i.second.erase(i.second.begin());
            }
        }
    }

    template <typename PLAYER>
    bool get(const PLAYER& p, bone_t& ret) {

        std::unique_lock<std::mutex> l(mutex);
        
        const auto& i = data.find(key_t(p));

        if (i == data.end())
            return false;

        const auto& j = i->second.find(pt(p.px, p.py));

        if (j == i->second.end())
            return false;

        ret = j->second;
        return true;
    }

    void get_marks(int x, int y, int z, std::vector< std::pair<pt,double> >& out) {

        std::unique_lock<std::mutex> l(mutex);

        const auto& i = data.find(key_t(x, y, z));

        if (i == data.end())
            return;

        for (const auto& j : i->second) {
            out.push_back(std::make_pair(j.first, j.second.worth));
        }
    }
};

Bones& bones() {
    static Bones ret;
    return ret;
}

}


#endif
