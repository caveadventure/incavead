#ifndef __RANDOM_H
#define __RANDOM_H

#include <random>

#include "serialize.h"

namespace rnd {

struct Generator {

    std::mt19937 gen;

    size_t seed;

    template <typename T>
    void init(T _seed) {
        gen.seed(_seed);
        seed = _seed;
    }

    template <typename T>
    T range(T a, T b) {
        std::uniform_int_distribution<T> dist(a, b);
        return dist(gen);
    }

    template <typename T>
    T gauss(T mean, T stddev) {
        std::normal_distribution<T> dist(mean, stddev);
        return dist(gen);
    }

    template <typename T>
    T uniform(T a, T b) {
        std::uniform_real_distribution<T> dist(a, b);
        return dist(gen);
    }

    unsigned int geometric(double p) {
        std::geometric_distribution<unsigned int> dist(p);
        return dist(gen);
    }

    template <typename T>
    T n(T n_) {
        return range((unsigned int)0, n_-1);
    }

    template <typename T>
    T biased_gauss(T mean, T stddev, T bias, T factor) {
        if (bias < 0)
            factor = -factor;
        mean += (stddev * factor * log((bias*bias) + 1.0));

        return gauss(mean, stddev);
    }

    //***  ***//

    inline void write(serialize::Sink& s) {
        serialize::write(s, seed);
    }

    inline void read(serialize::Source& s) {
        serialize::read(s, seed);
        init(seed);
    }

};

inline Generator& get() {
    static Generator ret;
    return ret;
}

}

#endif
