#ifndef __COMMON_H
#define __COMMON_H

#include <functional>
#include <string>
#include <unordered_map>


namespace std {

template <typename A, typename B>
struct hash< pair<A,B> > {
    size_t operator()(const pair<A,B>& p) const {
        return hash<A>()(p.first) + hash<B>()(p.second);
    }
};

}


namespace serialize {

template <>
struct reader<tag_t> {
    void read(Source& s, tag_t& t) {
        serialize::read(s, t.v);
    }
};

template <>
struct writer<tag_t> {
    void write(Sink& s, tag_t t) {
        serialize::write(s, t.v);
    }
};

}

#endif
