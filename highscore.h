#ifndef __HIGHSCORE_H
#define __HIGHSCORE_H

#include "serialize.h"
#include "common_types.h"
#include "common.h"
#include "bones.h"
#include "nlp.h"


namespace highscore {

struct Scores {

    struct order_t {
        int dlev;
        unsigned int plev;
        double worth;
        bones::bone_t bone;

        size_t scum_streak;
        bool victory;

        // HACK!

        order_t() : dlev(0), plev(0), worth(0), scum_streak(0), victory(false) {}

        order_t(int l, const bones::bone_t& b, size_t ss) : 
            dlev(l), 
            plev(b.level), 
            worth(std::max(b.worth, 0.0)), 
            bone(b), 
            scum_streak(ss),
            victory(b.cause.name == "VICTORY") 
            {}
    };

    std::vector<order_t> scores;

    Scores() {

        try {
            serialize::Source source("bones.dat");

            std::unordered_map<bones::session_t, size_t> scum_streaks;

            while (1) {
                try {
                    bones::key_t key;
                    bones::pt xy;
                    bones::bone_t bone;
                    bones::session_t sess;

                    serialize::read(source, key);
                    serialize::read(source, xy);
                    serialize::read(source, bone);
                    serialize::read(source, sess);

                    size_t& ss = scum_streaks[sess];

                    scores.push_back(order_t(key.worldz, bone, ss));

                    ++ss;

                } catch (...) {
                    break;
                }
            }

        } catch (...) {
        }
    }

    static bool sort_plev(const order_t& a, const order_t& b) {
        if (a.victory > b.victory) return true;
        if (a.victory == b.victory && a.plev > b.plev) return true;
        if (a.victory == b.victory && a.plev == b.plev && a.dlev > b.dlev) return true;
        if (a.victory == b.victory && a.plev == b.plev && a.dlev == b.dlev && a.worth > b.worth) return true;
        if (a.victory == b.victory && a.plev == b.plev && a.dlev == b.dlev && a.worth == b.worth &&
            a.scum_streak < b.scum_streak) return true;
        return false;
    }

    static bool sort_dlev_d(const order_t& a, const order_t& b) {
        if (a.victory > b.victory) return true;
        if (a.victory == b.victory && a.dlev > b.dlev) return true;
        if (a.victory == b.victory && a.dlev == b.dlev && a.plev > b.plev) return true;
        if (a.victory == b.victory && a.dlev == b.dlev && a.plev == b.plev && a.worth > b.worth) return true;
        if (a.victory == b.victory && a.dlev == b.dlev && a.plev == b.plev && a.worth > b.worth &&
            a.scum_streak < b.scum_streak) return true;
        return false;
    }

    static bool sort_dlev_a(const order_t& a, const order_t& b) {
        if (a.victory > b.victory) return true;
        if (a.victory == b.victory && a.dlev < b.dlev) return true;
        if (a.victory == b.victory && a.dlev == b.dlev && a.plev > b.plev) return true;
        if (a.victory == b.victory && a.dlev == b.dlev && a.plev == b.plev && a.worth > b.worth) return true;
        if (a.victory == b.victory && a.dlev == b.dlev && a.plev == b.plev && a.worth > b.worth &&
            a.scum_streak < b.scum_streak) return true;
        return false;
    }

    static bool sort_worth(const order_t& a, const order_t& b) {
        if (a.victory > b.victory) return true;
        if (a.victory == b.victory && a.worth > b.worth) return true;
        if (a.victory == b.victory && a.worth == b.worth && a.plev > b.plev) return true;
        if (a.victory == b.victory && a.worth == b.worth && a.plev == b.plev && a.dlev > b.dlev) return true;
        if (a.victory == b.victory && a.worth == b.worth && a.plev == b.plev && a.dlev > b.dlev &&
            a.scum_streak < b.scum_streak) return true;
        return false;
    }


    template <typename FUNC>
    void _process(FUNC f) {

        size_t n = 0;

        for (auto i = scores.begin(); i != scores.end() && n < 10; ++i, ++n) {

            bones::bone_t& bone = i->bone;

            if (bone.cause.name.empty())
                bone.cause.name = "unnatural causes";

            if (bone.name.name.empty())
                bone.name.name = "anonymous";

            f(n, bone.name, bone.cause, i->plev, i->dlev, i->worth, i->victory, i->scum_streak);
        }
    }

    template <typename FUNC>
    void by_ts(FUNC f) {
        std::reverse(scores.begin(), scores.end());
        _process(f);
    }

    template <typename FUNC>
    void by_plev(FUNC f) {
        std::sort(scores.begin(), scores.end(), sort_plev);
        _process(f);
    }

    template <typename FUNC>
    void by_dlev_d(FUNC f) {
        std::sort(scores.begin(), scores.end(), sort_dlev_d);
        _process(f);
    }

    template <typename FUNC>
    void by_dlev_a(FUNC f) {
        std::sort(scores.begin(), scores.end(), sort_dlev_a);
        _process(f);
    }

    template <typename FUNC>
    void by_worth(FUNC f) {
        std::sort(scores.begin(), scores.end(), sort_worth);
        _process(f);
    }
};

}

#endif
