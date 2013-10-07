#ifndef __COUNTERS_SERIALIZE_H
#define __COUNTERS_SERIALIZE_H

namespace serialize {

template <>
struct reader<counters::Counts> {
    void read(Source& s, counters::Counts& t) {
        serialize::read(s, t.data);
    }
};

template <>
struct writer<counters::Counts> {
    void write(Sink& s, const counters::Counts& t) {
        serialize::write(s, t.data);
    }
};

}


#endif
