#ifndef __BRESENHAM_H
#define __BRESENHAM_H

namespace bresenham {

struct Line {
    int origx; 
    int origy; 
    int destx; 
    int desty; 
    int deltax;
    int deltay;

    int stepx;
    int stepy;
    int e;

    Line(int x1, int y1, int x2, int y2) : 
        origx(x1), origy(y1), destx(x2), desty(y2),
        deltax(destx - origx), deltay(desty - origy)
        {

            if (deltax > 0) {
		stepx = 1;
            } else if (deltax < 0) {
		stepx = -1;
            } else {
                stepx = 0;
            }

            if (deltay > 0) {
		stepy = 1;
            } else if (deltay < 0){
		stepy = -1;
            } else {
                stepy = 0;
            }

            if (stepx*deltax > stepy*deltay) {
		e = stepx*deltax;
		deltax *= 2;
		deltay *= 2;
            } else {
		e = stepy*deltay;
		deltax *= 2;
		deltay *= 2;
            }
        }

    bool step(int& xo, int& yo) {

	if (stepx*deltax > stepy*deltay) {

            if (origx == destx) return false;

            origx += stepx;
            e -= stepy*deltay;

            if (e < 0) {
                origy += stepy;
                e += stepx*deltax;
            }

	} else {

            if (origy == desty) return false;

            origy += stepy;
            e -= stepx*deltax;

            if (e < 0) {
                origx += stepx;
                e += stepy*deltay;
            }
	}

	xo = origx;
	yo = origy;
	return true;
    }
};

}

#endif
