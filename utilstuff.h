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

inline bool reachable(GameState& state, unsigned int ax, unsigned int ay, unsigned int bx, unsigned int by) {
    unsigned int _x = ax;
    unsigned int _y = ay;

    XXX

    state.render.draw_line(ax, ay, bx, by, false, 
                           maudit::color::dim_red, maudit::color::bright_white,
                           [&](unsigned int x, unsigned int y) {
                                   
                               if (x == ax && y == ay)
                                   return true;

                               if (state.render.is_walkblock(x, y) ||
                                   state.render.is_viewblock(x, y))
                                   return false;

                               _x = x;
                               _y = y;
                               return true;
                           });

    if (_x == bx && _y == by) return true;
    return false;
}

void radial_points(unsigned int px, unsigned int py, GameState& state, unsigned int radius, std::unordered_set< std::pair<unsigned int, unsigned int> >& points) {

    unsigned int r2 = radius * radius;

    for (int dx = -radius; dx <= radius; ++dx) {

        unsigned int dy = ::sqrt(r2 - dx*dx);

        int x = px + dx;

        if (x < 0 || x > (int)state.neigh.w)
            continue;

        int y1 = py + dy;

        if (y1 >= 0 && y1 < (int)state.neigh.h) {

            if (reachable(state, x, y1, px, py)) {
                range.insert(monsters::pt(x, y));
            }
        }

        int y2 = py - dy;

        if (y2 >= 0 && y2 < (int)state.neigh.h) {
            if (reachable(state, x, y1, px, py)) {
                range.insert(monsters::pt(x, y));
            }
        }
    }

}

#endif
