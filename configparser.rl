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

        real = ([0-9]+ '\.' [0-9]+) | ([0-9]+)
            >start $push;

        tag = [a-zA-Z0-9_]+ 
            >start $push;

        #/* 34 is the double quote character, the only reason for writing it like this is to make Emacs happy */
        quote = 34;

        strdata = ('\\"' | ^quote)*  
            >start $push;

        string = '"' strdata '"';


        colorname = 
            'black'   | 
            'red'     %{ add_color(spe.skin.fore, 1); } | 
            'green'   %{ add_color(spe.skin.fore, 2); } | 
            'yellow'  %{ add_color(spe.skin.fore, 3); } | 
            'blue'    %{ add_color(spe.skin.fore, 4); } | 
            'magenta' %{ add_color(spe.skin.fore, 5); } | 
            'cyan'    %{ add_color(spe.skin.fore, 6); } | 
            'white'   %{ add_color(spe.skin.fore, 7); } ;

        color = 
            ('none') | 
            ('dim'    %{ spe.skin.fore = maudit::color::dim_black; }    sep colorname) | 
            ('bright' %{ spe.skin.fore = maudit::color::bright_black; } sep colorname) ;

        skin = string %{ spe.skin.text = state.match; } ws1 color;

        habitat = 
            'walk'              %{ spe.habitat = Species::habitat_t::walk; }              | 
            'floor'             %{ spe.habitat = Species::habitat_t::floor; }             | 
            'water'             %{ spe.habitat = Species::habitat_t::water; }             | 
            'corner'            %{ spe.habitat = Species::habitat_t::corner; }            | 
            'shoreline'         %{ spe.habitat = Species::habitat_t::shoreline; }         | 
            'clumped_floor'     %{ spe.habitat = Species::habitat_t::clumped_floor; }     | 
            'clumped_water'     %{ spe.habitat = Species::habitat_t::clumped_water; }     |
            'clumped_corner'    %{ spe.habitat = Species::habitat_t::clumped_corner; }    |
            'clumped_shoreline' %{ spe.habitat = Species::habitat_t::clumped_shoreline; } ;

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
        species_skin      = 'skin'      ws1 skin    ;
        species_habitat   = 'habitat'   ws1 habitat ;
        species_ai        = 'ai'        ws1 ai      ;
        species_idle_ai   = 'idle_ai'   ws1 idle_ai ;
        species_move      = 'move'      ws1 move    ;
        species_range     = 'range'     ws1 number  %{ spe.range = ::atoi(state.match.c_str()); } ;

        species_clumpsize = 'clumpsize' 
            ws1 real %{ spe.clumpsize.mean = ::atof(state.match.c_str()); } 
            ws1 real %{ spe.clumpsize.deviation = ::atof(state.match.c_str()); } 
        ;

        species_one_data = 
            (species_count | species_name | species_skin | species_habitat | species_ai |
            species_idle_ai | species_move | species_range | species_clumpsize |
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

      main := (ws species)+ ws ;
        
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

        if (state.cs == ConfigParser_error) {
            throw std::runtime_error("Parse error.");
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
