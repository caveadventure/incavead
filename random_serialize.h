#ifndef __RANDOM_SERIALIZE_H
#define __RANDOM_SERIALIZE_H

namespace serialize {

template <>
struct reader<rnd::Generator> {
    void read(Source& s, rnd::Generator& t) {
        serialize::read(s, t.seed);
        t.init(t.seed);
    }
};

template <>
struct writer<rnd::Generator> {
    void write(Sink& s, const rnd::Generator& t) {
        serialize::write(s, t.seed);
    }
};

}

#endif
