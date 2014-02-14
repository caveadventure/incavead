#ifndef __FOV_H
#define __FOV_H


namespace fov {

template <typename T>
void cast_light(unsigned int w, unsigned int h, std::vector<T>& grid, 
                unsigned int cx, unsigned int cy,
                int row, float start, float end, 
                unsigned int radius, unsigned int origradius, unsigned int r2,
                int xx, int xy, int yx, int yy) {

    float new_start = 0.0;

    if (start < end) 
        return;

    for (int j = row; j < (int)radius + 1; j++) {

        int dx = -j - 1;
        int dy = -j;

        bool blocked = false;

        while (dx <= 0) {

            int X;
            int Y;

            dx++;

            X = cx + dx * xx + dy * xy;
            Y = cy + dx * yx + dy * yy;

            if (X < 0 || (unsigned int)X >= w || Y < 0 || (unsigned int)Y >= h)
                continue;

            size_t offset = X + Y*w;

            float l_slope = (dx-0.5f) / (dy+0.5f);
            float r_slope = (dx+0.5f) / (dy-0.5f);

            if (start < r_slope) {
                continue;

            } else if (end > l_slope) {
                break;
            }

            auto& thispoint = grid[offset];

            unsigned int dist = dx*dx + dy*dy;

            if (dist <= r2) {

                uint8_t newfov = ::sqrt((double)dist / (double)r2) * 100 + 1;

                if (thispoint.in_fov == 0 || thispoint.in_fov > newfov) {
                    thispoint.in_fov = newfov;
                }
            }

            if (blocked) {

                if (thispoint.is_viewblock /*|| thispoint.is_lightsource*/) {

                    new_start = r_slope;
                    continue;

                } else {
                    blocked = false;
                    start = new_start;
                }

            } else {

                if (thispoint.is_viewblock && j < (int)radius) {

                    blocked = true;

                    cast_light(w, h, grid,
                               cx, cy, 
                               j+1, start, l_slope, radius, origradius, r2, 
                               xx, xy, yx, yy);

                    new_start = r_slope;

                } else if (thispoint.is_lightsource && j < (int)radius) {

                    //blocked = true;

                    thispoint.in_fov = 1;

                    unsigned int newrad = origradius * 2 + j + 1;

                    cast_light(w, h, grid, 
                               cx, cy,
                               j+1, start, l_slope, newrad, origradius, newrad * newrad,
                               xx, xy, yx, yy);

                    //new_start = r_slope;
                }
            }
        }

        if (blocked) 
            break;
    }
}


template <typename T>
void fov_shadowcasting(unsigned int w, unsigned int h, std::vector<T>& grid, 
                       unsigned int x, unsigned int y, unsigned int radius) {

    static int mult[4][8] = {
	{1, 0,  0, -1, -1,  0,  0,  1},
	{0, 1, -1,  0,  0, -1,  1,  0},
	{0, 1,  1,  0,  0, -1, -1,  0},
	{1, 0,  0,  1, -1,  0,  0, -1},
    };

    for (auto& i : grid) {
        i.in_fov = 0;
    }

    unsigned int r2 = radius * radius;

    for (unsigned int oct = 0; oct < 8; ++oct) {

        cast_light(w, h, grid, x, y, 

                   1, 1.0, 0.0, radius, radius, r2,
                   mult[0][oct],
                   mult[1][oct],
                   mult[2][oct],
                   mult[3][oct]);
    }

    grid[x+w*y].in_fov = 1;
}


}


#endif 

