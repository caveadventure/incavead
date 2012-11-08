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

    static const unsigned int MAIN         = 0x0;
    static const unsigned int LOOKING      = 0x1;
    static const unsigned int TARGET       = 0x2;
    static const unsigned int THROWING     = 0x8;

    unsigned int state;


    struct look_t {
        unsigned int x;
        unsigned int y;
        int target;

        int rangemin;
        int rangemax;

        look_t(unsigned int _x = 0, unsigned int _y = 0) : 
            x(_x), y(_y), target(-1), rangemin(-1), rangemax(-1) {}
    };

    look_t look;

    Player() : px(0), py(0), worldx(0), worldy(0), worldz(0), level(0), lightradius(8), 
               state(MAIN) {}

};



#endif
