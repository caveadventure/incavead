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

    unsigned int dist2() const {
        return x*x + y*y;
    }

    template <typename S>
    unsigned int dist2(const point<S>& a) const {
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

    pt center;
    unsigned int r2;
    double r;

    circle() : r2(0), r(0) {}

    template <typename S>
    circle(const point<S>& _c, double _r2) : center(_c), r2(_r2), r(::sqrt(r2)) {}

    template <typename S>
    circle(const point<S>& _c, double _r, bool) : center(_c), r2(_r*_r), r(_r) {}

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

        std::cout << "\t\t\t" << q << std::endl;

        if (q == 0) {

            circ = circle(pt(0, 0), 0);
            return;
        }

        double D = 0.5 / q;

        auto center = point<double>((da * b_c.y + db * c_a.y + dc * a_b.y),
                                    -(da * b_c.x + db * c_a.x + dc * a_b.x)) * D;

        std::cout << "\t\t\t" << (da * b_c.y + db * c_a.y + dc * a_b.y) << "\t" << -(da * b_c.x + db * c_a.x + dc * a_b.x) << std::endl;

        unsigned int radius = std::max(center.dist2(a), std::max(center.dist2(b), center.dist2(c)));

        std::cout << "<|> " << a.x << "," << a.y << " " << b.x << "," << b.y << " "
                  << c.x << "," << c.y << " +++ " << center.x << "," << center.y << std::endl;
        std::cout << "< > " << center.dist2(a) << " " << center.dist2(b) << " " << center.dist2(c) << std::endl;

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

struct flower_t {

    std::set<tri> data;
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

        std::cout << "~insert " << super.center.x << "," << super.center.y << "|" << super.r
                  << " .. " << t.circ.center.x << "," << t.circ.center.y << "|" << t.circ.r << std::endl;

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

        std::cout << "~inserted" << std::endl;
        root->data.insert(t);
    }

    static void query(const flower& root, const circle& super, const pt& q, std::set<tri>& ret) {

        if (!root)
            return;

        std::cout << "~query " << super.center.x << "," << super.center.y << "|" << super.r
                  << " .. " << q.x << "," << q.y << std::endl;

        for (int i = 0; i < 7; ++i) {

            const flower& f = root->bud[i];

            circle fc = petal(super, i);

            if (fc.has(q))
                query(f, fc, q, ret);
        }

        auto i = root->data.begin();
        while (i != root->data.end()) {

            if (i->circ.has(q)) {
                std::cout << "~ found " << i->circ.center.x << "," << i->circ.center.y << "|" << i->circ.r << std::endl;
                ret.insert(*i);
                i = root->data.erase(i);
            } else {
                ++i;
            }
        }

        std::cout << "~done q" << super.center.x << "," << super.center.y << "|" << super.r << std::endl;
    }

    static void result(const flower& root, std::set<tri>& ret) {

        if (!root)
            return;

        for (int i = 0; i < 7; ++i) {

            const flower& f = root->bud[i];

            result(f, ret);
        }

        ret.insert(root->data.begin(), root->data.end());
    }
};

void check_pt(const tri& t, const pt& p) {

    if (t.a == p || t.b == p || t.c == p || !t.circ.has(p))
        return;

    std::cout << "!!! " << p.x << "," << p.y << " " 
              << t.a.x << "," << t.a.y << " " << t.b.x << "," << t.b.y << " " << t.c.x << "," << t.c.y << " | "
              << t.circ.center.x << "," << t.circ.center.y << "|" << t.circ.r2 << " ~~~ " << p.dist2(t.circ.center) << std::endl;
    ::abort();
}

void check_delaunay(const std::set<tri>& s) {

    for (const tri& t : s) {
        for (const tri& i : s) {
            if (i < t && t < i) continue;

            check_pt(t, i.a);
            check_pt(t, i.b);
            check_pt(t, i.c);
        }
    }
}

void print_tris(const std::set<tri>& s) {
    for (const auto& t : s) {

        std::cout << t.a.x << " " << t.a.y << std::endl;
        std::cout << t.b.x << " " << t.b.y << std::endl;
        std::cout << t.c.x << " " << t.c.y << std::endl;
        std::cout << t.a.x << " " << t.a.y << std::endl << std::endl;
    }
}

struct Triangulation {

    std::map< pt, std::set<pt> > res;
    std::set<pt> fakes;

    void clear() {

        res.clear();
        fakes.clear();
    }

    void init(unsigned int w, unsigned int h, const std::vector<pt>& points) {

        //bm __("delaunay");

        res.clear();
        fakes.clear();

        if (points.empty())
            return;

        flower tree(new flower_t);

        pt fake1(0, 0);
        pt fake2(w-1, 0);
        pt fake3(w-1, h-1);
        pt fake4(0, h-1);

        circle super(point<double>(w / 2, h / 2), fake3.dist2() + 1);

        /*
        double sqrt3 = ::sqrt(3);

        tri supertri(pt(0.0 - h * sqrt3 / 3.0, 0),
                     pt(w + h * sqrt3 / 3.0, 0),
                     pt(w * 0.5, h + w * sqrt3 * 0.5));
                     
        circle super = supertri.circ;
        */

        //flower_t::insert(tree, super, supertri);

        std::set<tri> queue;
        queue.insert(tri(fake1, fake2, fake3));
        queue.insert(tri(fake1, fake3, fake4));

        for (const pt& p : points) {

            std::map<edge, size_t> loose_edges;

            std::set<tri> bad;

            //flower_t::query(tree, super, p, bad);

            std::cout << "~ " << p.x << "," << p.y << " " << bad.size() << std::endl;

            auto i = queue.begin();
            while (i != queue.end()) {
                if (i->circ.has(p)) {
                    bad.insert(*i);
                    i = queue.erase(i);
                } else {
                    ++i;
                }
            }

            for (const tri& t : bad) {

                std::cout << "[ " << t.a.x << "," << t.a.y << " " << t.b.x << "," << t.b.y << " "
                          << t.c.x << "," << t.c.y << std::endl;
                std::cout << "( " << t.circ.center.x << "," << t.circ.center.y << "|" << t.circ.r2 << std::endl;

                loose_edges[edge(t.a, t.b)]++;
                loose_edges[edge(t.b, t.c)]++;
                loose_edges[edge(t.c, t.a)]++;
            }

            std::set<tri> good;

            for (const auto& v : loose_edges) {
        
                // A double edge means this is an internal edge, so we delete it.

                if (v.second > 1)
                    continue;
                
                tri tmp(v.first.a, v.first.b, p);

                if (!tmp.null())    
                    good.insert(tmp);
                    //flower_t::insert(tree, super, tmp);
            }

            queue.insert(good.begin(), good.end());

            print_tris(queue);
            check_delaunay(queue);
        }

        std::set<tri> finaltri;

        //flower_t::result(tree, finaltri);
        finaltri = queue;

        for (const auto& t : finaltri) {

            auto& ta = res[t.a];
            auto& tb = res[t.b];
            auto& tc = res[t.c];

            std::cout << t.a.x << " " << t.a.y << std::endl;
            std::cout << t.b.x << " " << t.b.y << std::endl;
            std::cout << t.c.x << " " << t.c.y << std::endl;
            std::cout << t.a.x << " " << t.a.y << std::endl << std::endl;

            ta.insert(t.b);
            ta.insert(t.c);
            tb.insert(t.a);
            tb.insert(t.c);
            tc.insert(t.a);
            tc.insert(t.b);
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

            if (fakes.count(p) != 0)
                continue;

            ret.insert(neighbor_t(p0.dist(p), p.x, p.y));
        }

        return ret;
    }
};

}

#endif
