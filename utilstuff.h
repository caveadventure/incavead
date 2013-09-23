#ifndef __UTILSTUFF_H
#define __UTILSTUFF_H

double pow2(double a) {
    return a*a;
}

double gaussian_function(double a, double b, double c, double x) {

    // a * e ^ ( - ((x-b)^2) / (2*c^2) )

    return a * ::exp(-(pow2(x - b) / (2*pow2(c))));
}

inline double distance(double ax, double ay, double bx, double by) {
    double q = (ax - bx);
    double p = (ay - by);
    return ::sqrt(q*q + p*p);
}

#endif
