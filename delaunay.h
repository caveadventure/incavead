#ifndef __DELAUNAY_H
#define __DELAUNAY_H

#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <utility>
#include <memory>
#include <array>

#include <math.h>

namespace delaunay {

template <typename T>
struct point {
    T x;
    T y;

    point(T _x = 0, T _y = 0) : x(_x), y(_y) {}

    template <typename S>
    point(const point<S>& a) : x(a.x), y(a.y) {}

    template <typename S>
    point(const std::pair<S, S>& _pt) : x(_pt.first), y(_pt.second) {}

    template <typename S>
    point<T> operator+(const point<S>& a) const {
        return point<T>(x + a.x, y + a.y);
    }

    template <typename S>
    point<T> operator-(const point<S>& a) const {
        return point<T>(x - a.x, y - a.y);
    }

    template <typename POD>
    point<T> operator*(POD d) const {
        return point<T>(x * d, y * d);
    }

    template <typename POD>
    point<T> operator/(POD d) const {
        return point<T>(x / d, y / d);
    }

    bool operator<(const point<T>& a) const {
        if (x < a.x) return true;
        if (x == a.x && y < a.y) return true;
        return false;
    }

    bool operator==(const point<T>& a) const {
        return (x == a.x && y == a.y);
    }

    T dist2() const {
        return x*x + y*y;
    }

    template <typename S>
    T dist2(const point<S>& a) const {
        return (*this - a).dist2();
    }

    double dist() const {
        return ::sqrt(dist2());
    }

    template <typename S>
    double dist(const point<S>& a) const {
        return ::sqrt(dist2(a));
    }
};

typedef point<int> pt;

struct circle {

    point<double> center;
    double r2;
    double r;

    circle() : r2(0), r(0) {}

    template <typename S, typename T>
    circle(const point<S>& _c, T _r2) : center(_c), r2(_r2), r(::sqrt(r2)) {}

    template <typename S, typename T>
    circle(const point<S>& _c, T _r, bool) : center(_c), r2(_r*_r), r(_r) {}

    bool null() const {
        return (r2 == 0);
    }

    template <typename T>
    bool has(const point<T>& p) const {
        return (center.dist2(p) <= r2);
    }

    bool has(const circle& c) const {
        return (center.dist(c.center) + c.r <= r);
    }

    bool intersects(const circle& c) const {
        return (center.dist(c.center) - c.r <= r);
    }

    bool operator<(const circle& c) const {
        if (center < c.center) return true;
        if (center == c.center && r2 < c.r2) return true;
        return false;
    }
};

struct tri {

    pt a;
    pt b;
    pt c;

    circle circ;

    tri() {}

    tri(const pt& _a, const pt& _b, const pt& _c) : a(_a), b(_b), c(_c) { circumscribe(); }

    void circumscribe() {

        int da = a.dist2();
        int db = b.dist2();
        int dc = c.dist2();
        pt a_b = a - b;
        pt b_c = b - c;
        pt c_a = c - a;

        // Small q or large radius means a degenerate non-triangle. (Three points that are almost collinear.)

        int q = (a.x * b_c.y + b.x * c_a.y + c.x * a_b.y);

        if (q == 0) {

            circ = circle(pt(0, 0), 0);
            return;
        }

        double D = 0.5 / q;

        point<double> center( D * (da * b_c.y + db * c_a.y + dc * a_b.y),
                             -D * (da * b_c.x + db * c_a.x + dc * a_b.x));

        double radius = std::max(center.dist2(a), std::max(center.dist2(b), center.dist2(c)));

        circ = circle(center, radius);
    }

    bool operator<(const tri& t) const {
        if (a < t.a) return true;
        if (a == t.a && b < t.b) return true;
        if (a == t.a && b == t.b && c < t.c) return true;
        return false;
    }

    bool null() const {

        return circ.null(); 
    }
};

struct edge {

    pt a;
    pt b;

    edge() {}

    edge(const pt& _a, const pt& _b) {

        if (_a < _b) {
            a = _a;
            b = _b;

        } else {
            a = _b;
            b = _a;
        }
    };

    bool operator<(const edge& o) const {
        if (a < o.a) return true;
        if (a == o.a && b < o.b) return true;
        return false;
    }
};


struct flower_t;
typedef std::unique_ptr<flower_t> flower;

//
// Circle-based spatial indexing tree.
//
// Based on this picture: http://www2.stetson.edu/~efriedma/circovcir/7.gif
//
// A circle of radius R can be completely covered by 7 circles of radii R/2,
// one circle in the center and 6 centered on the midpoints of edges of the hexagon
// inscribed in the larger (radius R) circle.
//

struct flower_t {

    std::vector<tri> data;
    std::array<flower, 7> bud;

    static circle petal(const circle& super, int i) {

        static double sqrt3_2 = 0.8660254037844386;

        static double centers[7][2] = {
            { 0,             0 },
            { sqrt3_2,       0 },
            { sqrt3_2 / 2,   0.75 },
            { sqrt3_2 / 2,   -0.75 },
            { -sqrt3_2,      0 },
            { -sqrt3_2 / 2,  0.75 },
            { -sqrt3_2 / 2,  -0.75 }
        };

        return circle(point<double>(super.center.x + centers[i][0] * super.r,
                                    super.center.y + centers[i][1] * super.r), 
                      super.r / 2, true);
    }

    static void insert(flower& root, const circle& super, const tri& t) {

        if (!root) 
            root = flower(new flower_t);

        for (int i = 0; i < 7; ++i) {

            flower& f = root->bud[i];

            circle fc = petal(super, i);

            if (fc.has(t.circ)) {
                insert(f, fc, t);
                return;
            }
        }

        root->data.push_back(t);
    }

    static void query(const flower& root, const circle& super, const pt& q, std::vector<tri>& ret) {

        if (!root)
            return;

        for (int i = 0; i < 7; ++i) {

            const flower& f = root->bud[i];

            circle fc = petal(super, i);

            if (fc.has(q))
                query(f, fc, q, ret);
        }

        auto i = root->data.begin();
        while (i != root->data.end()) {

            if (i->circ.has(q)) {
                ret.push_back(*i);
                i = root->data.erase(i);
            } else {
                ++i;
            }
        }
    }

    static void result(const flower& root, std::vector<tri>& ret) {

        if (!root)
            return;

        for (int i = 0; i < 7; ++i) {

            const flower& f = root->bud[i];

            result(f, ret);
        }

        ret.insert(ret.end(), root->data.begin(), root->data.end());
    }
};


struct Triangulation {

    std::map< pt, std::map<pt,unsigned int> > res;

    void clear() {

        res.clear();
    }

    void init(unsigned int w, unsigned int h, const std::vector<pt>& points, bool do_print = false) {

        res.clear();

        if (points.empty())
            return;

        flower tree(new flower_t);

        pt fake1(0, 0);
        pt fake2(w-1, 0);
        pt fake3(w-1, h-1);
        pt fake4(0, h-1);

        circle super(point<double>(w / 2, h / 2), fake3.dist2() + 1);

        flower_t::insert(tree, super, tri(fake1, fake2, fake3));
        flower_t::insert(tree, super, tri(fake1, fake3, fake4));

        for (const pt& p : points) {

            std::vector<tri> bad;

            flower_t::query(tree, super, p, bad);

            while (1) {

                std::map<edge, size_t> loose_edges;

                for (const tri& t : bad) {

                    loose_edges[edge(t.a, t.b)]++;
                    loose_edges[edge(t.b, t.c)]++;
                    loose_edges[edge(t.c, t.a)]++;
                }

                std::map< pt, std::set<pt> > hull;

                for (const auto& v : loose_edges) {

                    if (v.second > 2)
                        throw std::runtime_error("Sanity error: not a mesh.");
        
                    // A double edge means this is an internal edge, so we delete it.

                    if (v.second == 2)
                        continue;
                
                    hull[v.first.a].insert(v.first.b);
                    hull[v.first.b].insert(v.first.a);
                }

                std::set<edge> hull_edges;
                bool try_again = false;

                for (const auto& v : hull) {

                    if (v.second.size() != 2) {

                        // We found a set of triangles that isn't a triangulation.

                        // Oops, theoretically this should never happen, but it does.
                        // (Rounding errors and such.)
                        // Remove the triangles that are the furthest away,
                        // hopefully this will get rid of non-connected triangles.
                        // TODO.

                        unsigned int minr2 = 0;
                        std::set<tri> to_remove;
                        
                        for (const tri& t : bad) {

                            unsigned int d = t.circ.r2 - t.circ.center.dist2(p);

                            if (to_remove.empty() || d <= minr2) {

                                if (d != minr2) {
                                    to_remove.clear();
                                }

                                to_remove.insert(t);
                                minr2 = d;
                            }
                        }

                        for (auto i = bad.begin(); i != bad.end();) {
                            if (to_remove.count(*i) != 0) {
                                i = bad.erase(i);
                            } else {
                                ++i;
                            }
                        }

                        try_again = true;
                        break;
                    }


                    const pt& a = v.first;
                    const pt& b = *(v.second.begin());
                    const pt& c = *(++v.second.begin());

                    hull_edges.insert(edge(a, b));
                    hull_edges.insert(edge(a, c));
                }

                if (try_again)
                    continue;

                // hull_edges is only needed to make the inserted triangles unique.

                for (const edge& e : hull_edges) {

                    tri tmp(e.a, e.b, p);

                    if (!tmp.null())
                        flower_t::insert(tree, super, tmp);                    
                }
            
                break;
            }

            if (do_print) {
                static unsigned int nn = 0;
                ++nn;

                if (nn != points.size())
                    continue;

                std::stringstream ss;
                ss << "_tmp." << nn;
                std::ofstream of(ss.str().c_str());

                std::vector<tri> finaltri;
                flower_t::result(tree, finaltri);

                for (const tri& t : finaltri) {
                    of << t.a.x << " " << t.a.y << std::endl;
                    of << t.b.x << " " << t.b.y << std::endl;
                    of << t.c.x << " " << t.c.y << std::endl;
                    of << t.a.x << " " << t.a.y << std::endl << std::endl;
                }
            }

        }

        std::vector<tri> finaltri;
        flower_t::result(tree, finaltri);

        for (const auto& t : finaltri) {

            auto& ta = res[t.a];
            auto& tb = res[t.b];
            auto& tc = res[t.c];

            unsigned int a_b = t.a.dist2(t.b);
            unsigned int b_c = t.b.dist2(t.c);
            unsigned int c_a = t.c.dist2(t.a);

            ta[t.b] = a_b;
            ta[t.c] = c_a;
            tb[t.a] = a_b;
            tb[t.c] = b_c;
            tc[t.a] = c_a;
            tc[t.b] = b_c;
        }
    }

    struct neighbor_t {
        unsigned int dist2;
        unsigned int x;
        unsigned int y;

        neighbor_t(unsigned int d2 = 0, unsigned int _x = 0, unsigned int _y = 0) : dist2(d2), x(_x), y(_y) {}

        bool operator<(const neighbor_t& a) const {
            if (dist2 < a.dist2) return true;
            if (dist2 == a.dist2 && x < a.x) return true;
            if (dist2 == a.dist2 && x < a.x && y < a.y) return true;
            return false;
        }
    };
    
    std::set<neighbor_t> get(unsigned int x, unsigned int y, unsigned int d2max, bool& full_empty) const {
    
        std::set<neighbor_t> ret;

        pt p0(x, y);

        const auto i = res.find(p0);

        if (i == res.end()) {
            full_empty = true;
            return ret;
        }

        full_empty = false;

        for (const auto& p_d : i->second) {

            if (p_d.second < d2max) {
                ret.insert(neighbor_t(p_d.second, p_d.first.x, p_d.first.y));
            }
        }

        return ret;
    }
};

}

#endif
