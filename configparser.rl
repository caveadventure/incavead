#ifndef __CONFIGPARSER_H
#define __CONFIGPARSER_H

// This file needs to be preprocessed with the 'ragel' tool.
// Run it like this:
//
//   ragel -G2 configparser.rl -o configparser.h
//

#include <string>
#include <stdexcept>
#include <iostream>

#include <string.h>
#include <stdio.h>

#include "maudit.h"
#include "species.h"
#include "species_bank.h"

namespace configparser {

struct ragel_state {

    /** Ragel scanner cruft. **/

    // Iterators for start and end of buffer data.
    char* p;
    char* pe;

    // Iterator for 'end of file'.
    char* eof;

    // Iterator for start and end of token.
    char* ts;
    char* te;

    // Internal state and rollback variables.
    int cs, act;

    // Stack for ragel machine states.
    int stack[32];
    int top;

    // Not part of ragel's variables; this is a buffer to hold the current match.
    std::string match;
};

inline void print_species(const Species& s) {
    std::cout << "  tag: " << s.tag << std::endl;
    std::cout << "  name: " << s.name << std::endl;
    std::cout << "  skin: " << s.skin.text << " " << (int)s.skin.fore << " " << (int)s.skin.back << std::endl;
    std::cout << "  level: " << s.level << std::endl;
    std::cout << "  count: " << s.count << std::endl;
    std::cout << "  habitat: " << (int)s.habitat << std::endl;
    std::cout << "  ai: " << (int)s.ai << std::endl;
    std::cout << "  idle_ai: " << (int)s.idle_ai << std::endl;
    std::cout << "  move: " << (int)s.move << std::endl;
    std::cout << "  range: " << s.range << std::endl;
    std::cout << "  clumpsize: " << s.clumpsize.mean << " " << s.clumpsize.deviation << std::endl;

    init_species_copy(s);
}

inline void print_design(const Design& d) {
    std::cout << "  tag: " << d.tag << std::endl;
    std::cout << "  name: " << d.name << std::endl;
    std::cout << "  skin: " << d.skin.text << " " << (int)d.skin.fore << " " << (int)d.skin.back << std::endl;
    std::cout << "  level: " << d.level << std::endl;
    std::cout << "  count: " << d.count << std::endl;
    std::cout << "  descr: " << d.descr << std::endl;
    std::cout << "  attack: " << d.attack << std::endl;
    std::cout << "  defense: " << d.defense << std::endl;

    init_design_copy(d);
}

inline void add_color(maudit::color& c, unsigned int i) {
    c = (maudit::color)((uint32_t)c + i);
}

void parse_config(const std::string& filename) {

    /** File reading cruft. **/

    char buf[4096];

    FILE* fn = ::fopen(filename.c_str(), "r");

    if (fn == NULL) {
        throw std::runtime_error("Could not open: \"" + filename + "\"");
    }

    ragel_state state;

    Species spe;
    Design des;

    maudit::glyph skin;

    %%{

        machine ConfigParser;

        access state.;
        variable p state.p;
        variable pe state.pe;
        variable eof state.eof;

        action start {
            state.match.clear();
        }

        action push {
            state.match += fc;
        }

        onews = [ \t\r\n];
        ws = onews*;
        ws1 = onews+;
        sep = '_' | ws;

        number = [0-9]+ 
            >start $push;

        real = (('-'?) (([0-9]+ '\.' [0-9]+) | ([0-9]+)))
            >start $push;

        tag = [a-zA-Z0-9_]+ 
            >start $push;

        #/* 34 is the double quote character, the only reason for writing it like this is to make Emacs happy */
        quote = 34;

        strchar_escape := 
            ( ('"'   ${ state.match += '"';  fret; }) |
              ('n'   ${ state.match += '\n'; fret; }) |
              ('\\'  ${ state.match += '\\'; fret; }) )
            ;

        strchar = ( (^ (quote | '\\') $push ) |
                    ('\\'             ${fcall strchar_escape;} ) );

        strdata = strchar*;

        string = '"' >start strdata '"';


        colorname = 
            'black'   | 
            'red'     %{ add_color(skin.fore, 1); } | 
            'green'   %{ add_color(skin.fore, 2); } | 
            'yellow'  %{ add_color(skin.fore, 3); } | 
            'blue'    %{ add_color(skin.fore, 4); } | 
            'magenta' %{ add_color(skin.fore, 5); } | 
            'cyan'    %{ add_color(skin.fore, 6); } | 
            'white'   %{ add_color(skin.fore, 7); } ;

        color = 
            ('none') | 
            ('dim'    %{ skin.fore = maudit::color::dim_black; }    sep colorname) | 
            ('bright' %{ skin.fore = maudit::color::bright_black; } sep colorname) ;

        skin = string %{ skin.text = state.match; } ws1 color;

        ####

        habitat = 
            'walk'              %{ spe.habitat = Species::habitat_t::walk; }              | 
            'floor'             %{ spe.habitat = Species::habitat_t::floor; }             | 
            'water'             %{ spe.habitat = Species::habitat_t::water; }             | 
            'corner'            %{ spe.habitat = Species::habitat_t::corner; }            | 
            'shoreline'         %{ spe.habitat = Species::habitat_t::shoreline; }         ; 

        ai = 
            'none'        %{ spe.ai = Species::ai_t::none; }        |
            'seek_player' %{ spe.ai = Species::ai_t::seek_player; } ;

        idle_ai = 
            'none'   %{ spe.idle_ai = Species::idle_ai_t::none; }        |
            'random' %{ spe.idle_ai = Species::idle_ai_t::random; } ;

        move = 
            'any'   %{ spe.move = Species::move_t::any; }   | 
            'floor' %{ spe.move = Species::move_t::floor; } | 
            'water' %{ spe.move = Species::move_t::water; } ;

        species_count     = 'count'     ws1 number  %{ spe.count = ::atoi(state.match.c_str()); } ;
        species_name      = 'name'      ws1 string  %{ spe.name = state.match; } ;
        species_skin      = 'skin'      ws1 skin    %{ spe.skin = skin; };
        species_habitat   = 'habitat'   ws1 habitat ;
        species_ai        = 'ai'        ws1 ai      ;
        species_idle_ai   = 'idle_ai'   ws1 idle_ai ;
        species_move      = 'move'      ws1 move    ;
        species_range     = 'range'     ws1 number  %{ spe.range = ::atoi(state.match.c_str()); } ;
        species_attack    = 'attack'    ws1 real %{ spe.attack = ::atof(state.match.c_str()); } ;
        species_defense   = 'defense'   ws1 real %{ spe.defense = ::atof(state.match.c_str()); } ;

        species_clumpsize = 'clumpsize' 
            ws1 real %{ spe.clumpsize.mean = ::atof(state.match.c_str()); } 
            ws1 real %{ spe.clumpsize.deviation = ::atof(state.match.c_str()); } 
        ;

        species_companion = 'companion' %{ spe.companion.push_back(Species::companion_t()); }
            ws1 string %{ spe.companion.back().tag = state.match; }
            ws1 real   %{ spe.companion.back().chance = ::atof(state.match.c_str()); }
            ;

        species_drop = 'drop' %{ spe.drop.push_back(Species::drop_t()); }
            ws1 string %{ spe.drop.back().tag = state.match; }
            ws1 real   %{ spe.drop.back().chance = ::atof(state.match.c_str()); }
            ;

        species_one_data = 
            (species_count | species_name | species_skin | species_habitat | species_ai |
            species_idle_ai | species_move | species_range | species_clumpsize |
            species_companion | species_attack | species_defense | species_drop |
            '}'
            %{ fret; })
            ;

        one_species :=  (ws species_one_data ws ';')+
            ;

        species_level = number %{ spe.level = ::atoi(state.match.c_str()); }
        ;

        species_tag   = tag    %{ spe.tag = state.match; }
        ;

        species = 
            'species' ${ spe = Species(); }
            ws1 species_level ws1 species_tag ws
            '{' ${fcall one_species;} 
            %{ std::cout << "species done: " << std::endl; print_species(spe); }
            ;

        ####

        design_count      = 'count'      ws1 number  %{ des.count = ::atoi(state.match.c_str()); } ;
        design_name       = 'name'       ws1 string  %{ des.name = state.match; } ;
        design_skin       = 'skin'       ws1 skin    %{ des.skin = skin; };
        design_slot       = 'slot'       ws1 string  %{ des.slot = state.match; } ;
        design_descr      = 'descr'      ws1 string  %{ des.descr = state.match; } ;
        design_attack     = 'attack'     ws1 real    %{ des.attack = ::atof(state.match.c_str()); } ;
        design_defense    = 'defense'    ws1 real    %{ des.defense = ::atof(state.match.c_str()); } ;
        design_stackrange = 'stackrange' ws1 number  %{ des.stackrange = ::atoi(state.match.c_str()); };
        design_heal       = 'heal'       ws1 real    %{ des.heal = ::atof(state.match.c_str()); };
        design_usable     = 'usable'                 %{ des.usable = true; };

        design_one_data = 
            (design_count | design_name | design_skin | design_slot | design_descr |
            design_attack | design_defense | design_stackrange | design_heal | design_usable |
            '}'
            %{ fret; })
            ;
            
        one_design :=  (ws design_one_data ws ';')+
            ;

        design_level = number %{ des.level = ::atoi(state.match.c_str()); }
        ;

        design_tag   = tag    %{ des.tag = state.match; }
        ;

        design =
            'design' ${ des = Design(); }
            ws1 design_level ws1 design_tag ws
            '{' ${fcall one_design;}
            %{ std::cout << "design done: " << std::endl; print_design(des); }
            ;

        entry = species | design ;
            
      main := (ws entry)+ ws ;
        
    }%%
/*

*/

    %% write data;
    %% write init;

    bool done = false;
    int have = 0;

    while (!done) {
        int space = sizeof(buf) - have;
        if (space == 0) {
            throw std::runtime_error("Token too big!");
        }

        state.p = buf + have;
        int len = ::fread(state.p, 1, space, fn);
        
        state.pe = state.p + len;
        state.eof = 0;
        
        if (len == 0) {
            state.eof = state.pe;
            done = true;
        }

        %% write exec;

        // Avoid spurious gcc warnings.
        (void)ConfigParser_first_final;
        (void)ConfigParser_en_strchar_escape;
        (void)ConfigParser_en_one_species;
        (void)ConfigParser_en_one_design;
        (void)ConfigParser_en_main;

        if (state.cs == ConfigParser_error) {
            throw std::runtime_error("Parse error. Unconsumed input: " + std::string(state.p, state.pe));
        }

        if (state.ts == 0) {
            have = 0;

        } else {
            have = state.pe - state.ts;
            ::memmove(buf, state.ts, have);
            state.te = buf + (state.te - state.ts);
            state.ts = buf;
        }
    }
}

}

#endif
