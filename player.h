#ifndef __PLAYER_H
#define __PLAYER_H


struct stat_t {
    double val;
        
    stat_t() : val(3.0) {}

    void inc(double v) {
        val += v;
        if (val > 3) val = 3;
        else if (val < 3) val = -3;
    }

    void dec(double v) {
        val -= v;
        if (val < -3) val = -3;
        else if (val > 3) val = 3;
    }
};


struct Player {

    unsigned int px;
    unsigned int py;

    int worldx;
    int worldy;
    int worldz;

    unsigned int level;

    stat_t health;
    stat_t hunger;
    stat_t karma;

    unsigned int sleep;

    inventory_t inv;

    static const unsigned int MAIN         = 0x0;
    static const unsigned int LOOKING      = 0x1;
    static const unsigned int TARGET       = 0x2;
    static const unsigned int FIRED        = 0x8;
    static const unsigned int THROWING     = 0x10;
    static const unsigned int BLASTING     = 0x20;

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

    Player() : px(0), py(0), worldx(0), worldy(0), worldz(0), level(0),
               sleep(0), state(MAIN) 
        {
            karma.val = 0;
        }

};


namespace serialize {

template <>
struct reader<Player> {
    void read(Source& s, Player& p) {
        serialize::read(s, p.px);
        serialize::read(s, p.py);
        serialize::read(s, p.worldx);
        serialize::read(s, p.worldy);
        serialize::read(s, p.worldz);
        serialize::read(s, p.level);
        serialize::read(s, p.health.val);
        serialize::read(s, p.hunger.val);
        serialize::read(s, p.karma.val);
        serialize::read(s, p.sleep);
        serialize::read(s, p.inv);
        serialize::read(s, p.state);
        serialize::read(s, p.look.x);
        serialize::read(s, p.look.y);
        serialize::read(s, p.look.target);
        serialize::read(s, p.look.rangemin);
        serialize::read(s, p.look.rangemax);
    }
};

template <>
struct writer<Player> {
    void write(Sink& s, const Player& p) {
        serialize::write(s, p.px);
        serialize::write(s, p.py);
        serialize::write(s, p.worldx);
        serialize::write(s, p.worldy);
        serialize::write(s, p.worldz);
        serialize::write(s, p.level);
        serialize::write(s, p.health.val);
        serialize::write(s, p.hunger.val);
        serialize::write(s, p.karma.val);
        serialize::write(s, p.sleep);
        serialize::write(s, p.inv);
        serialize::write(s, p.state);
        serialize::write(s, p.look.x);
        serialize::write(s, p.look.y);
        serialize::write(s, p.look.target);
        serialize::write(s, p.look.rangemin);
        serialize::write(s, p.look.rangemax);
    }
};

}


#endif
