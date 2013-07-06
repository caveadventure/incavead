#ifndef __WORLD_KEY_H
#define __WORLD_KEY_H

namespace worldkey {

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

    bool operator==(const key_t& a) const {
        return (worldx == a.worldx && worldy == a.worldy && worldz == a.worldz);
    }
};

}

namespace serialize {

template <>
struct reader<worldkey::key_t> {
    void read(Source& s, worldkey::key_t& t) {
        serialize::read(s, t.worldx);
        serialize::read(s, t.worldy);
        serialize::read(s, t.worldz);
    }
};

template <>
struct writer<worldkey::key_t> {
    void write(Sink& s, const worldkey::key_t& t) {
        serialize::write(s, t.worldx);
        serialize::write(s, t.worldy);
        serialize::write(s, t.worldz);
    }
};

}


namespace std {

template <>
struct hash<worldkey::key_t> {
    size_t operator()(const worldkey::key_t& k) const {
        return hash<int>()(k.worldx) + hash<int>()(k.worldy) + hash<int>()(k.worldz);
    }
};

}


#endif

