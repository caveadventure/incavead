#ifndef __ASTAR_H
#define __ASTAR_H

#include <vector>
#include <algorithm>

namespace astar {

struct Path {
    unsigned int w;
    unsigned int h;

    unsigned int ox;
    unsigned int oy;
    unsigned int dx;
    unsigned int dy;
    float diagonalCost;

    enum dir_t { NORTH_WEST, NORTH, NORTH_EAST, WEST, NONE, EAST, SOUTH_WEST, SOUTH, SOUTH_EAST };

    std::vector<float> grid;    // wxh djikstra distance grid (covered distance)
    std::vector<float> heur;    // wxh A* score grid (covered distance + estimated remaining distance)
    std::vector<dir_t> prev;    // wxh 'previous' grid : direction to the previous cell

    std::vector<size_t> heap;   // min_heap used in the algorithm. stores the offset in grid/heur (offset=x+y*w)

    std::vector< std::pair<unsigned int, unsigned int> > path;

    Path() : w(0), h(0) {}

    void init(unsigned int _w, unsigned int _h) {

        if (w == _w && h == _h)
            return;

        w = _w;
        h = _h;
        grid.resize(w*h);
        heur.resize(w*h);
        prev.resize(w*h);
    }

    template <typename FUNC>
    bool compute(unsigned int _ox, unsigned int _oy, unsigned int _dx, unsigned int _dy, 
                 float _diagCost, unsigned int cutoff, FUNC walk_cost) {

        ox = _ox;
        oy = _oy;
        dx = _dx;
        dy = _dy;
        diagonalCost = _diagCost;

        path.clear();
        heap.clear();

        if (ox == dx && oy == dy)
            return true;

        if (ox >= w || dx >= w || oy >= h || dy >= h) {
            return false;
        }

        grid.assign(w*h, 0.0);
        prev.assign(w*h, NONE);
        heur.assign(w*h, 0.0);

        heur[ox + oy*w] = 1.0;

        heap.push_back(ox + oy*w);

        _set_cells(cutoff, walk_cost);

        if (grid[dx + dy * w] == 0) {
            return false;
        }

        static int dirx[] = { -1,  0,  1, -1,  0,  1, -1,  0,  1 };
        static int diry[] = { -1, -1, -1,  0,  0,  0,  1,  1,  1 };

        path.push_back(std::make_pair(dx, dy));

        while (1) {
            dir_t step = prev[dx + dy*w];
            dx -= dirx[step];
            dy -= diry[step];

            if (dx == ox && dy == oy)
                break;

            path.push_back(std::make_pair(dx, dy));
        }

	return true;
    }

    bool walk(unsigned int& rx, unsigned int& ry) {

        if (path.empty())
            return false;

        rx = path.back().first;
        ry = path.back().second;
        path.pop_back();
        return true;
    }

private:

    template <typename FUNC>
    void _set_cells(unsigned int cutoff, FUNC _walk_cost) {

	unsigned int stepstaken = 0;

	while (grid[dx + dy*w] == 0 && heap.size() > 0) {

            stepstaken++;
            if (stepstaken > cutoff) {
                break;
            }

            size_t offset = heap[0];
            std::pop_heap(heap.begin(), heap.end(), [this](size_t a, size_t b) { return (heur[a] > heur[b]); });
            heap.pop_back();

            unsigned int x = offset % w;
            unsigned int y = offset / w;
            double distance = grid[offset];

            unsigned int imax = (diagonalCost == 0.0f ? 4 : 8);

            for (unsigned int i = 0; i < imax; i++) {

                static int idirx[] = {  0, -1,  1,  0,  -1,  1, -1,  1 };
                static int idiry[] = { -1,  0,  0,  1,  -1, -1,  1,  1 };

                static dir_t prevdirs[] = {
                    NORTH, WEST, EAST, SOUTH, NORTH_WEST, NORTH_EAST, SOUTH_WEST, SOUTH_EAST
                };

                
                int cx = x + idirx[i];
                int cy = y + idiry[i];

                if (cx >= 0 && cy >= 0 && (unsigned int)cx < w && (unsigned int)cy < h) {

                    float walk_cost = _walk_cost(x, y, cx, cy);

                    if (walk_cost <= 0)
                        continue;

                    float covered = distance + walk_cost * (i>=4 ? diagonalCost : 1.0f);

                    size_t coffset = cx + cy*w;

                    float previousCovered = grid[coffset];

                    if (previousCovered == 0) {

                        float remaining = ::sqrt((cx-dx)*(cx-dx) + (cy-dy)*(cy-dy));

                        grid[coffset] = covered;
                        heur[coffset] = covered + remaining;
                        prev[coffset] = prevdirs[i];

                        heap.push_back(coffset);

                        std::push_heap(heap.begin(), heap.end(), 
                                       [this](size_t a, size_t b) { return (heur[a] > heur[b]); });

                    } else if (previousCovered > covered) {

                        grid[coffset] = covered;
                        heur[coffset] -= (previousCovered - covered);
                        prev[coffset] =  prevdirs[i];

                        std::make_heap(heap.begin(), heap.end(), 
                                       [this](size_t a, size_t b) { return (heur[a] > heur[b]); });

                    }
                }
            }
        }
    }
};

}


#endif
