#ifndef __UTILSTUFF_H
#define __UTILSTUFF_H


inline double pow2(double a) {
    return a*a;
}

inline double gaussian_function(double a, double b, double c, double x) {

    // a * e ^ ( - ((x-b)^2) / (2*c^2) )

    return a * ::exp(-(pow2(x - b) / (2*pow2(c))));
}

inline double distance(double ax, double ay, double bx, double by) {
    double q = (ax - bx);
    double p = (ay - by);
    return ::sqrt(q*q + p*p);
}

inline bool player_walkable(GameState& state, unsigned int x, unsigned int y, bool walk_rock = false) {

    if (!walk_rock && !state.grid.is_walk(x, y))
        return false;

    features::Feature feat;

    if (state.features.get(x, y, feat)) {

        const Terrain& t = terrain().get(feat.tag);

        if (t.viewblock || t.walkblock)
            return false;
    }

    return true;
}

inline bool monster_walkable(GameState& state, const Species& s, unsigned int x, unsigned int y) {

    if (!monsters::Monsters::is_walkable(state.grid, s, x, y))
        return false;

    features::Feature feat;
    if (state.features.get(x, y, feat)) {

        const Terrain& t = terrain().get(feat.tag);

        if (t.walkblock)
            return false;
    }

    return true;
}

template <typename FUNC>
bool reachable(GameState& state, unsigned int ax, unsigned int ay, unsigned int bx, unsigned int by,
               FUNC f) {

    bresenham::Line line(ax, ay, bx, by);

    unsigned int x = ax;
    unsigned int y = ay;

    while (1) {

        bool ok = f(state, x, y);

        if (!ok)
            break;

        bool ret = line.step((int&)x, (int&)y);

        if (!ret)
            return true;
    }

    return false;
}

template <typename FUNC>
void radial_points(unsigned int px, unsigned int py, GameState& state, unsigned int radius, 
                   std::unordered_set<neighbors::pt>& points, FUNC f) {

    unsigned int r2 = radius * radius;

    for (int dx = -radius; dx <= (int)radius; ++dx) {

        unsigned int dy = ::sqrt(r2 - dx*dx);

        int x = px + dx;

        if (x < 0 || x > (int)state.neigh.w)
            continue;

        int y1 = py + dy;

        if (y1 >= 0 && y1 < (int)state.neigh.h) {

            if (reachable(state, x, y1, px, py, f)) {
                points.insert(neighbors::pt(x, y1));
            }
        }

        int y2 = py - dy;

        if (y2 >= 0 && y2 < (int)state.neigh.h) {
            if (reachable(state, x, y2, px, py, f)) {
                points.insert(neighbors::pt(x, y2));
            }
        }
    }
}


template <typename FUNC>
bool path_walk(GameState& state, 
               unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1,
               unsigned int n, unsigned int cutoff, FUNC cost,
               unsigned int& xo, unsigned int& yo) {

    bool tmp = state.path.compute(x0, y0, x1, y1, 1.41, cutoff, cost);

    if (!tmp) return false;

    for (unsigned int i = 0; i < n; ++i) {
        if (!state.path.walk(xo, yo))
            return false;
    }

    return true;
}

inline bool digging_step(GameState& state, unsigned int x, unsigned int y, double speed) {

    float& height = state.grid._get(x, y);

    height -= speed;

    if (height < -10) {
        height = -10;
            
        bool water = state.grid.is_water(x, y);

        state.grid.set_walk_water(state.neigh, x, y, true, water);
        state.render.invalidate(x, y);
        return true;
    }

    return false;
}


#endif
