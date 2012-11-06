#ifndef __PLAYER_H
#define __PLAYER_H


struct stat_t {
    double val;
        
    stat_t() : val(3.0) {}

    void inc(double v) {
        val += v;
        if (val > 3) val = 3;
    }

    void dec(double v) {
        val -= v;
        if (val < -3) val = -3;
    }
};


struct Player {

    unsigned int px;
    unsigned int py;

    int worldx;
    int worldy;
    int worldz;

    unsigned int level;

    unsigned int lightradius;

    stat_t health;

    inventory_t inv;

    bool is_looking;
    unsigned int look_x;
    unsigned int look_y;
    int look_target;

    Player() : px(0), py(0), worldx(0), worldy(0), worldz(0), level(1), lightradius(8), 
               is_looking(false), look_x(0), look_y(0), look_target(-1) {}

};



#endif
