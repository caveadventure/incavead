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
    bone_t(const std::string& _name, const PLAYER& p, const ACHI& achievements, const std::string& polyform) :
        name(_name), 
        level(p.level), 
        cause(p.attacker), 
        worth(p.inv.get_worth() + p.money_curse)
        {

            if (name.name.empty()) {
                name.name = "anonymous"_m;
            }

            std::string label;
            unsigned int pri = 0;

            for (const auto& i : p.achievements) {

                auto j = achievements.find(i);

                if (j == achievements.end())
                    throw std::runtime_error("sanity error in achievements");

                const auto& a = j->second;

                if (a.label.empty())
                    continue;

                if (a.priority < pri) 
                    continue;

                if (a.priority > pri) {
                    pri = a.priority;
                    label.clear();
                }

                if (!label.empty())
                    label += ", ";

                label += a.label;
            }

            if (polyform.size() > 0) {

                if (label.size() > 0) {
                    label += ", ";
                }

                label += "in the form of"_m;
                label += polyform;
            }

            if (!label.empty()) {
                name.name += " (";
                name.name += label;
                name.name += ")";
            }
        }
};

struct session_t {
    unsigned int address;
    unsigned int seed;

    session_t(unsigned int a = 0, unsigned int s = 0) : address(a), seed(s) {}
    
    bool operator==(const session_t& s) const {
        return address == s.address && seed == s.seed;
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

template <>
struct reader<bones::session_t> {
    void read(Source& s, bones::session_t& t) {
        serialize::read(s, t.address);
        serialize::read(s, t.seed);
    }
};

template <>
struct writer<bones::session_t> {
    void write(Sink& s, const bones::session_t& t) {
        serialize::write(s, t.address);
        serialize::write(s, t.seed);
    }
};

}

namespace std {

template <>
struct hash<bones::session_t> {
    size_t operator()(const bones::session_t& k) const {
        return hash<unsigned int>()(k.address) + hash<unsigned int>()(k.seed);
    }
};

}


namespace bones {

struct Bones {

    static const size_t NUMBER = 1000;

    struct data_t {
        bone_t bone;
        session_t session;
    };

    std::map< key_t, std::unordered_map<pt, data_t> > data;

    std::unordered_map<session_t, size_t> replay_codes;
    
    std::mutex mutex;

    size_t max_bones;

    Bones() : max_bones(NUMBER) {}

    template <typename PLAYER, typename ACHI>
    void add(const std::string& name, const PLAYER& p, const ACHI& achievements, const std::string& polyform,
             unsigned int addr, unsigned int seed) {

        key_t key(p);
        pt xy(p.px, p.py);
        bone_t bone(name, p, achievements, polyform);
        session_t sess(addr, seed);

        std::unique_lock<std::mutex> l(mutex);

        auto& m = data[key];
        m[xy].bone = bone;
        m[xy].session = sess;

        replay_codes[sess]++;

        while (m.size() > max_bones) {
            m.erase(m.begin());
        }

        serialize::Sink sink("bones.dat", true);
        serialize::write(sink, key);
        serialize::write(sink, xy);
        serialize::write(sink, bone);
        serialize::write(sink, sess);
    }

    void load(size_t _max = NUMBER) {

        max_bones = _max;

        try {
            serialize::Source source("bones.dat");

            while (1) {
                try {
                    key_t key;
                    pt xy;
                    bone_t bone;
                    session_t sess;

                    serialize::read(source, key);
                    serialize::read(source, xy);
                    serialize::read(source, bone);
                    serialize::read(source, sess);

                    auto& m = data[key][xy];
                    m.bone = bone;
                    m.session = sess;

                    replay_codes[sess]++;

                } catch (...) {
                    break;
                }
            }

        } catch (...) {
        }

        for (auto& i : data) {
            while (i.second.size() > max_bones) {
                i.second.erase(i.second.begin());
            }
        }
    }

    template <typename PLAYER>
    bool get(const PLAYER& p, unsigned int x, unsigned int y, bone_t& ret) {

        std::unique_lock<std::mutex> l(mutex);
        
        const auto& i = data.find(key_t(p));

        if (i == data.end())
            return false;

        const auto& j = i->second.find(pt(x, y));

        if (j == i->second.end())
            return false;

        // HACK
        if (j->second.bone.cause.name == "VICTORY") 
            return false;

        ret = j->second.bone;
        return true;
    }

    template <typename PLAYER>
    bool get(const PLAYER& p, bone_t& ret) {

        return get(p, p.px, p.py, ret);
    }

    void get_marks(int x, int y, int z, std::vector< std::pair<pt,double> >& out) {

        std::unique_lock<std::mutex> l(mutex);

        const auto& i = data.find(key_t(x, y, z));

        if (i == data.end())
            return;

        for (const auto& j : i->second) {
            // HACK!! FIXME!
            if (j.second.bone.cause.name != "VICTORY") {
                out.push_back(std::make_pair(j.first, j.second.bone.worth));
            }
        }
    }

    size_t get_replay_code_count(unsigned int addr, unsigned int seed) {

        session_t sess(addr, seed);

        std::unique_lock<std::mutex> l(mutex);
        return replay_codes[sess];
    }
};

Bones& bones() {
    static Bones ret;
    return ret;
}

}


#endif
