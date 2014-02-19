#ifndef __FOV_H
#define __FOV_H


namespace fov {

template <typename T>
void cast_light(unsigned int w, unsigned int h, std::vector<T>& grid, 
                unsigned int cx, unsigned int cy,
                unsigned int cx2, unsigned int cy2,
                int row, float start, float end, 
                unsigned int radius, unsigned int r2,
                int xx, int xy, int yx, int yy,
                std::set< std::pair<unsigned int, unsigned int> >& ret) {

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

            if (cx2 != cx || cy2 != cy) {

                unsigned int dx2 = (X - cx2) * (X - cx2);
                unsigned int dy2 = (Y - cy2) * (Y - cy2);

                unsigned int dist2 = dx2 + dy2;

                dist = dist + dist2 + 2.0 * ::sqrt(dist * dist2);
                
                /*
                unsigned int dx2 = (X - cx2) * (X - cx2);
                unsigned int dy2 = (Y - cy2) * (Y - cy2);

                double z = ::sqrt(dx2 + dy2) + ::sqrt(dist);
                dist = z * z;
                */
            }

            if (dist <= r2) {

                uint8_t newfov = ::sqrt((double)dist / (double)r2) * 100 + 1;

                if (thispoint.is_lightsource && thispoint.in_fov == 0) {
                    ret.insert(std::make_pair(X, Y));
                }

                if (thispoint.in_fov == 0 || thispoint.in_fov > newfov) {
                    thispoint.in_fov = newfov;
                }
            }

            if (blocked) {

                if (thispoint.is_viewblock) {

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
                               cx2, cy2,
                               j+1, start, l_slope, radius, r2, 
                               xx, xy, yx, yy,
                               ret);

                    new_start = r_slope;

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

    for (auto& i : grid) {
        i.in_fov = 0;
    }

    static int mult[4][8] = {
	{1, 0,  0, -1, -1,  0,  0,  1},
	{0, 1, -1,  0,  0, -1,  1,  0},
	{0, 1,  1,  0,  0, -1, -1,  0},
	{1, 0,  0,  1, -1,  0,  0, -1},
    };


    std::set< std::pair<unsigned int, unsigned int> > lights;

    for (unsigned int oct = 0; oct < 8; ++oct) {

        cast_light(w, h, grid, x, y, x, y,
                   1, 1.0, 0.0, radius, radius * radius,
                   mult[0][oct],
                   mult[1][oct],
                   mult[2][oct],
                   mult[3][oct],
                   lights);
    }

    grid[x+w*y].in_fov = 1;

    while (lights.size() > 0) {

        std::pair<unsigned int, unsigned int> pt = *(lights.begin());
        lights.erase(lights.begin());

        int _x = (x - pt.first);
        int _y = (y - pt.second);
        unsigned int rad = ::sqrt(_x*_x + _y*_y) + radius;
        unsigned int r2 = ((rad + radius) * (rad + radius));

        for (unsigned int oct = 0; oct < 8; ++oct) {

            cast_light(w, h, grid, x, y, pt.first, pt.second,
                       1, 1.0, 0.0, rad, r2,
                       mult[0][oct],
                       mult[1][oct],
                       mult[2][oct],
                       mult[3][oct],
                       lights);
        }

    }
}


}


#endif 

