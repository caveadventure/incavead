#ifndef __DELAUNAY_H
#define __DELAUNAY_H

#include <vector>
#include <set>
#include <algorithm>
#include <utility>

#include <math.h>


namespace delaunay {

struct pt {
    unsigned int x;
    unsigned int y;

    pt(unsigned int _x = 0, unsigned int _y = 0) : x(_x), y(_y) {}

    pt(const std::pair<unsigned int, unsigned int>& _pt) : x(_pt.first), y(_pt.second) {}

    pt operator+(const pt& a) const {
        return pt(x + a.x, y + a.y);
    }

    pt operator-(const pt& a) const {
        return pt(x - a.x, y - a.y);
    }

    template <typename POD>
    pt operator*(POD d) const {
        return pt(x * d, y * d);
    }

    template <typename POD>
    pt operator/(POD d) const {
        return pt(x / d, y / d);
    }

    bool operator<(const pt& a) const {
        if (x < a.x) return true;
        if (x == a.x && y < a.y) return true;
        return false;
    }

    bool operator==(const pt& a) const {
        return (x == a.x && y == a.y);
    }

    unsigned int dist2() const {
        return x*x + y*y;
    }

    unsigned int dist2(const pt& a) const {
        return (*this - a).dist2();
    }
};

struct tri {

    pt a;
    pt b;
    pt c;

    pt center;
    double radius;

    tri() : radius(0) {}

    tri(const pt& _a, const pt& _b, const pt& _c) : a(_a), b(_b), c(_c), radius(0) { circumscribe(); }

    void circumscribe() {

        double da = a.dist2();
        double db = b.dist2();
        double dc = c.dist2();
        pt a_b = a - b;
        pt b_c = b - c;
        pt c_a = c - a;

        // Small q or large radius means a degenerate non-triangle. (Three points that are almost collinear.)

        double q = (a.x * b_c.y + b.x * c_a.y + c.x * a_b.y);

        if (q < 0.00001) {
            radius = 0;
            return;
        }

        double D = 0.5 / q;

        center = pt((da * b_c.y + db * c_a.y + dc * a_b.y),
                   -(da * b_c.x + db * c_a.x + dc * a_b.x)) * D;

        radius = (a - center).dist2();
    }

    bool operator<(const tri& a) const {
        return center < a.center;
    }

    bool null(unsigned int maxr) const {

        return (radius == 0 || radius >= maxr);
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

struct Triangulation {

    std::map< pt, std::set<pt> > res;

    std::set<pt> trash;

    void clear() {

        res.clear();
        trash.clear();
    }

    void init(unsigned int w, unsigned int h, unsigned int maxr, const std::set<pt>& points) {

        bm __("delaunay");

        res.clear();
        trash.clear();

        if (points.empty())
            return;

        std::multiset<tri> queue;

        pt fake1(0, 0);
        pt fake2(w-1, 0);
        pt fake3(w-1, h-1);
        pt fake4(0, h-1);

        trash.insert(fake1);
        trash.insert(fake2);
        trash.insert(fake3);
        trash.insert(fake4);

        auto pi = points.begin();

        {
            tri top(fake1, fake2, *pi);
            tri rig(fake2, fake3, *pi);
            tri bot(fake3, fake4, *pi);
            tri lef(fake4, fake1, *pi);

            unsigned int maxr2 = (std::max(w, h) * 2);
            maxr2 = maxr2 * maxr2;

            if (!top.null(maxr2)) queue.insert(top);
            if (!rig.null(maxr2)) queue.insert(rig);
            if (!bot.null(maxr2)) queue.insert(bot);
            if (!lef.null(maxr2)) queue.insert(lef);
        }

        ++pi;
        while (pi != points.end()) {

            const pt& p = *pi;

            std::map<edge, size_t> loose_edges;

            for (auto i = queue.begin(); i != queue.end();) {

                const tri& t = *i;

                if (p.x > t.center.x + ::sqrt(t.radius)) {

                    // The triangle is too far away from the inserted point and so will not change.

                    auto& ta = res[t.a];
                    auto& tb = res[t.b];
                    auto& tc = res[t.c];

                    ta.insert(t.b);
                    ta.insert(t.c);
                    tb.insert(t.a);
                    tb.insert(t.c);
                    tc.insert(t.a);
                    tc.insert(t.b);

                    i = queue.erase(i);

                } else if ((p - t.center).dist2() <= t.radius) {

                    // The inserted point intersects the triangle.

                    loose_edges[edge(t.a, t.b)]++;
                    loose_edges[edge(t.b, t.c)]++;
                    loose_edges[edge(t.c, t.a)]++;

                    i = queue.erase(i);

                } else {

                    ++i;
                }
            }

            for (const auto& v : loose_edges) {
        
                // A double edge means this is an internal edge, so we delete it.

                if (v.second > 1)
                    continue;
                
                tri tmp(v.first.a, v.first.b, p);

                if (!tmp.null(maxr))    
                    queue.insert(tmp);
            }

            if (p == fake1 || p == fake2 || p == fake3 || p == fake4)
                trash.erase(p);

            ++pi;
        }

        for (const auto& t : queue) {
            
            auto& ta = res[t.a];
            auto& tb = res[t.b];
            auto& tc = res[t.c];

            ta.insert(t.b);
            ta.insert(t.c);
            tb.insert(t.a);
            tb.insert(t.c);
            tc.insert(t.a);
            tc.insert(t.b);
        }

        for (const auto& i : res) {
            for (const auto& j : i.second) {
                std::cout << i.first.x << "," << i.first.y << " " << j.x << "," << j.y << std::endl;
            }
        }
    }

    struct neighbor_t {
        double dist;
        unsigned int x;
        unsigned int y;

        neighbor_t(double d = 0, unsigned int _x = 0, unsigned int _y = 0) : dist(d), x(_x), y(_y) {}

        bool operator<(const neighbor_t& a) const {
            if (dist < a.dist) return true;
            if (dist == a.dist && x < a.x) return true;
            if (dist == a.dist && x < a.x && y < a.y) return true;
            return false;
        }
    };
    
    std::set<neighbor_t> get_neighbors(unsigned int x, unsigned int y) const {
    
        std::set<neighbor_t> ret;

        pt p0(x, y);

        const auto i = res.find(p0);

        if (i == res.end())
            return ret;

        for (const pt& p : i->second) {

            if (trash.count(p) != 0)
                continue;

            ret.insert(neighbor_t(::sqrt((p0 - p).dist2()), p.x, p.y));
        }

        return ret;
    }
};

}

#endif
