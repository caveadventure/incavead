#ifndef __PSTATS_H
#define __PSTATS_H

#include <vector>
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
    std::string status_min_msg;

    bool hidden;
    bool progressbar;
    bool reversed;

    tag_t ailment;

    Stat() : min(-3), max(3), cmax(1000), critical(false), hidden(false), progressbar(true),
             reversed(false) {}
};

struct Count {

    tag_t tag;

    struct label_t {
        std::string label;
        skins lskin;
        skins pskin;
        skins nskin;
    };

    label_t label;

    unsigned int cmax;

    std::string monster_hit_msg;
    std::string status_msg;

    bool hidden;

    bool blind;
    bool stun;
    bool fear;
    bool sleep;

    bool cancellable;

    tag_t ailment;

    Count() : cmax(1000), hidden(true), blind(false), stun(false), fear(false), sleep(false),
              cancellable(false) {}
};

template <typename T>
struct StatsBank {

    std::unordered_map<tag_t,T> stats;

    void copy(const T& t) {

        if (stats.count(t.tag) != 0) {
            throw std::runtime_error("Duplicate pstat tag: " + t.label.label);
        }

        stats[t.tag] = t;
    }

    const T& get(tag_t tag) const {
        auto i = stats.find(tag);

        if (i == stats.end()) {
            throw std::runtime_error("Invalid pstat tag: " + std::to_string(tag.v));
        }

        return i->second;
    }
};

template <typename T>
inline StatsBank<T>& __stats__() {
    static StatsBank<T> ret;
    return ret;
}

inline const StatsBank<Stat>& stats() {
    return __stats__<Stat>();
}

inline void init_stat_copy(const Stat& t) {
    __stats__<Stat>().copy(t);
}

inline const StatsBank<Count>& counts() {
    return __stats__<Count>();
}

inline void init_count_copy(const Count& t) {
    __stats__<Count>().copy(t);
}

namespace pstats {

struct count_t {

    unsigned int val;

    count_t() : val(0) {}

    bool inc(int v, const Count& s, bool levelcheck = false) {

        if (v < 0 && -v > (int)val) {
            v = -val;
        }

        unsigned int prev = val;

        val += v;
        if (val > s.cmax) val = s.cmax;

        return (val == 0 && (levelcheck || prev != 0));
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

        if (v > 0 && !st.chain_pos.null()) {

            if (stats[st.chain_pos].chain(v, ::stats().get(st.chain_pos)))
                return true;
        }

        if (v < 0 && !st.chain_neg.null()) {

            if (stats[st.chain_neg].chain(v, ::stats().get(st.chain_neg)))
                return true;
        }

        return stats[t].inc(v, ::stats().get(t));
    }

    bool is_min(tag_t t) const {
        const Stat& st = ::stats().get(t);
        auto i = stats.find(t);
        return ((i != stats.end() ? i->second.val : 0.0) <= st.min);
    }

    bool cinc(tag_t t, int v) {

        bool ret = counts[t].inc(v, ::counts().get(t));

        if (ret)
            counts.erase(t);

        return ret;
    }

    double gets(tag_t t) {
        return stats[t].val;
    }

    unsigned int getc(tag_t t) {
        auto i = counts.find(t);
        return (i != counts.end() ? i->second.val : 0);
    }

    bool crit() const {

        for (const auto& i : stats) {

            const Stat& st = ::stats().get(i.first);

            if (st.critical && i.second.val <= st.min)
                return true;
        }

        return false;
    }

    void die() {

        for (auto& i : stats) {

            const Stat& st = ::stats().get(i.first);

            if (st.critical)
                i.second.val = st.min;
        }
    }

    void cancel() {

        for (auto& i : counts) {

            const Count& ct = ::counts().get(i.first);

            if (ct.cancellable)
                i.second.val = 0;
        }

        clean();
    }

    void tick() {
        bool del = false;

        for (auto& i : counts) {
            if (i.second.inc(-1, ::counts().get(i.first)), true)
                del = true;
        }

        if (del)
            clean();
    }

    void clean() {
        std::vector<tag_t> x;

        for (auto& i : counts) {
            if (i.second.val == 0)
                x.push_back(i.first);
        }

        for (tag_t t : x) {
            counts.erase(t);
        }
    }
};

}

#endif
