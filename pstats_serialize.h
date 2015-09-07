#ifndef __PSTATS_SERIALIZE_H
#define __PSTATS_SERIALIZE_H

namespace serialize {

template <>
struct reader<pstats::stat_t> {
    void read(Source& s, pstats::stat_t& sp) {
        serialize::read(s, sp.val);
    }
};

template <>
struct writer<pstats::stat_t> {
    void write(Sink& s, const pstats::stat_t& sp) {
        serialize::write(s, sp.val);
    }
};

template <>
struct reader<pstats::count_t> {
    void read(Source& s, pstats::count_t& sp) {
        serialize::read(s, sp.val);
    }
};

template <>
struct writer<pstats::count_t> {
    void write(Sink& s, const pstats::count_t& sp) {
        serialize::write(s, sp.val);
    }
};

template <>
struct reader<pstats::stats_t> {
    void read(Source& s, pstats::stats_t& sp) {
        serialize::read(s, sp.stats);
        serialize::read(s, sp.counts);
    }
};

template <>
struct writer<pstats::stats_t> {
    void write(Sink& s, const pstats::stats_t& sp) {
        serialize::write(s, sp.stats);
        serialize::write(s, sp.counts);
    }
};

}

#endif
