#ifndef __PSTATS_H
#define __PSTATS_H

#include <unordered_map>

struct Stat {

    tag_t tag;

    struct label_t {
        std::string label;
        skins lskin;
        skins pskin;
        skins nskin;
    };

    label_t label;

    double min;
    double max;

    unsigned int cmax;

    bool critical;

    tag_t chain_pos;
    tag_t chain_neg;

    std::string monster_hit_msg;
    std::string player_hit_msg;

    Stat() : min(-3), max(3), cmax(1000), critical(false) {}
};

struct StatsBank {

    std::unordered_map<tag_t,Stat> stats;

    void copy(const Stat& t) {

        if (stats.count(t.tag) != 0) {
            throw std::runtime_error("Duplicate pstat tag: " + t.label.label);
        }

        stats[t.tag] = t;
    }

    const Stat& get(tag_t tag) const {
        auto i = stats.find(tag);

        if (i == stats.end()) {
            throw std::runtime_error("Invalid pstat tag: " + std::to_string(tag.v));
        }

        return i->second;
    }
};

inline StatsBank& __stats__() {
    static StatsBank ret;
    return ret;
}

inline const StatsBank& stats() {
    return __stats__();
}

inline void init_stats_copy(const Stats& t) {
    __stats__().copy(t);
}

namespace pstats {

struct count_t {

    unsigned int val;

    count_t() : val(0) {}

    bool inc(int v, const Stat& s) {

        if (v < 0 && -v > val) {
            v = -val;
        }

        val += v;
        if (val > s.cmax) val = s.cmax;

        return (val == 0);
    }
};

struct stat_t {

    double val;

    stat_t() : val(0) {}

    bool inc(double v, const Stat& s) {

        val += v;
        if (val > s.max) val = s.max;
        else if (val < s.min) val = s.min;

        return (s.critical && val == s.min);
    }

    bool chain(double& v, const Stat& s) {

        if (val > s.min) {
            double sgn = (v > 0) - (v < 0);
            double nv = std::min(sgn*v, val - s.min);
            v -= sgn*nv;
            val -= nv;
        }

        return (s.critical && val == s.min);
    }
};


struct stats_t {

    std::unordered_map<tag_t,stat_t> stats;
    std::unordered_map<tag_t,count_t> counts;
    
    bool sinc(tag_t t, double v) {

        const Stat& st = ::stats().get(t);

        if (v > 0 && !t.chain_pos.null()) {

            if (stats[t.chain_pos].chain(v, ::stats().get(t.chain_pos)))
                return true;
        }

        if (v < 0 && !t.chain_neg.null()) {

            if (stats[t.chain_neg].chain(v, ::stats().get(t.chain_neg)))
                return true;
        }

        return stats[t].inc(v, ::stats().get(t));
    }

    bool cinc(tag_t t, int v) {

        return counts[t].inc(v, ::stats().get(t));
    }

    double gets(tag_t t) {
        return stats[t].val;
    }

    unsigned int getc(tag_t t) {
        return counts[t].val;
    }

    bool crit() const {

        for (const auto& i : stats) {

            const Stat& st = ::stats().get(t);

            if (st.critical && i.second.val <= st.min)
                return true;
        }

        return false;
    }
};

}


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
