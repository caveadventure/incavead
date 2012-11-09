#ifndef __LEVELSKINS_H
#define __LEVELSKINS_H

struct Levelskin {

    maudit::glyph deep_water;
    maudit::glyph shallow_water;
    maudit::glyph wall;
    maudit::glyph water_wall;
    maudit::glyph floor1;
    maudit::glyph floor2;
    maudit::glyph floor3;
    maudit::glyph floor4;
    maudit::glyph floor5;
    maudit::glyph floor6;
    maudit::glyph floor7;
    maudit::glyph floor8;

    unsigned int lightradius;

    unsigned int level;

    Levelskin() : lightradius(8), level(0) {}
};

struct Levelskins {
    std::map<unsigned int,Levelskin> skins;

    const Levelskin& get(unsigned int level) const {

        if (skins.size() == 0)
            throw std::runtime_error("sanity error: no levelskins defined");

        auto i = skins.upper_bound(level);

        if (i == skins.begin()) {
            return i->second;

        } else {
            --i;
            return i->second;
        }
    }

    void set(const Levelskin& skin) {
        skins[skin.level] = skin;
    }
};


Levelskins& __levelskins__() {
    static Levelskins ret;
    return ret;
}

const Levelskins& levelskins() {
    return __levelskins__();
}

void init_levelskin(const Levelskin& skin) {
    __levelskins__().set(skin);
}


#endif

