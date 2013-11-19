#ifndef __BONES_H
#define __BONES_H

#include <list>
#include <mutex>

#include "worldkey.h"

namespace bones {

typedef std::pair<unsigned int, unsigned int> pt;

using key_t = worldkey::key_t;

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

    template <typename PLAYER, typename ACHI>
    bone_t(const std::string& _name, const PLAYER& p, const ACHI& achievements) :
        name(_name), 
        level(p.level), 
        cause(p.attacker), 
        worth(p.inv.get_worth() + p.money_curse)
        {

            if (name.name.empty()) {
                name.name = "anonymous";
            }

            std::string label;
            unsigned int pri = 0;

            for (const auto& i : p.achievements) {

                auto j = achievements.find(i.first);

                if (j == achievements.end())
                    throw std::runtime_error("sanity error in achievements");

                const auto& a = j->second;

                if (a.label.empty())
                    continue;

                if (a.priority > pri) {
                    pri = a.priority;
                    label.clear();
                }

                if (!label.empty())
                    label += ", ";

                label += a.label;
            }

            if (!label.empty()) {
                name.name += " (";
                name.name += label;
                name.name += ")";
            }
        }
};

}

namespace serialize {

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

    // HACK TODO WARNING
    // Magic number
    static const size_t NUMBER = 1000;

    std::map< key_t, std::unordered_map<pt, bone_t> > data;
    
    std::mutex mutex;

    template <typename PLAYER, typename ACHI>
    void add(const std::string& name, const PLAYER& p, const ACHI& achievements) {

        key_t key(p);
        pt xy(p.px, p.py);
        bone_t bone(name, p, achievements);

        std::unique_lock<std::mutex> l(mutex);

        auto& m = data[key];
        m[xy] = bone;

        while (m.size() > NUMBER) {
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
            while (i.second.size() > NUMBER) {
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
