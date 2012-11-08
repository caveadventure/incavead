#ifndef __UTILSTUFF_H
#define __UTILSTUFF_H

inline double distance(double ax, double ay, double bx, double by) {
    double q = (ax - bx);
    double p = (ay - by);
    return ::sqrt(q*q + p*p);
}

#endif
