
#line 1 "configparser.rl"
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

    
#line 280 "configparser.rl"

/*

*/

    
#line 112 "configparser.h"
static const int ConfigParser_start = 1;
static const int ConfigParser_first_final = 413;
static const int ConfigParser_error = 0;

static const int ConfigParser_en_strchar_escape = 25;
static const int ConfigParser_en_one_species = 26;
static const int ConfigParser_en_one_design = 276;
static const int ConfigParser_en_main = 1;


#line 286 "configparser.rl"
    
#line 125 "configparser.h"
	{
	 state.cs = ConfigParser_start;
	 state.top = 0;
	}

#line 287 "configparser.rl"

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

        
#line 154 "configparser.h"
	{
	if ( ( state.p) == ( state.pe) )
		goto _test_eof;
	goto _resume;

_again:
	switch (  state.cs ) {
		case 1: goto st1;
		case 0: goto st0;
		case 2: goto st2;
		case 3: goto st3;
		case 4: goto st4;
		case 5: goto st5;
		case 6: goto st6;
		case 7: goto st7;
		case 8: goto st8;
		case 9: goto st9;
		case 10: goto st10;
		case 11: goto st11;
		case 12: goto st12;
		case 413: goto st413;
		case 414: goto st414;
		case 13: goto st13;
		case 14: goto st14;
		case 15: goto st15;
		case 16: goto st16;
		case 17: goto st17;
		case 18: goto st18;
		case 19: goto st19;
		case 20: goto st20;
		case 21: goto st21;
		case 22: goto st22;
		case 23: goto st23;
		case 24: goto st24;
		case 415: goto st415;
		case 25: goto st25;
		case 416: goto st416;
		case 26: goto st26;
		case 27: goto st27;
		case 28: goto st28;
		case 29: goto st29;
		case 30: goto st30;
		case 31: goto st31;
		case 32: goto st32;
		case 33: goto st33;
		case 34: goto st34;
		case 417: goto st417;
		case 35: goto st35;
		case 36: goto st36;
		case 37: goto st37;
		case 38: goto st38;
		case 39: goto st39;
		case 40: goto st40;
		case 41: goto st41;
		case 42: goto st42;
		case 43: goto st43;
		case 44: goto st44;
		case 45: goto st45;
		case 46: goto st46;
		case 47: goto st47;
		case 48: goto st48;
		case 49: goto st49;
		case 50: goto st50;
		case 51: goto st51;
		case 52: goto st52;
		case 53: goto st53;
		case 54: goto st54;
		case 55: goto st55;
		case 56: goto st56;
		case 57: goto st57;
		case 58: goto st58;
		case 59: goto st59;
		case 60: goto st60;
		case 61: goto st61;
		case 62: goto st62;
		case 63: goto st63;
		case 64: goto st64;
		case 65: goto st65;
		case 66: goto st66;
		case 67: goto st67;
		case 68: goto st68;
		case 69: goto st69;
		case 70: goto st70;
		case 71: goto st71;
		case 72: goto st72;
		case 73: goto st73;
		case 74: goto st74;
		case 75: goto st75;
		case 76: goto st76;
		case 77: goto st77;
		case 78: goto st78;
		case 79: goto st79;
		case 80: goto st80;
		case 81: goto st81;
		case 82: goto st82;
		case 83: goto st83;
		case 84: goto st84;
		case 85: goto st85;
		case 86: goto st86;
		case 87: goto st87;
		case 88: goto st88;
		case 89: goto st89;
		case 90: goto st90;
		case 91: goto st91;
		case 92: goto st92;
		case 93: goto st93;
		case 94: goto st94;
		case 95: goto st95;
		case 96: goto st96;
		case 97: goto st97;
		case 98: goto st98;
		case 99: goto st99;
		case 100: goto st100;
		case 101: goto st101;
		case 102: goto st102;
		case 103: goto st103;
		case 104: goto st104;
		case 105: goto st105;
		case 106: goto st106;
		case 107: goto st107;
		case 108: goto st108;
		case 109: goto st109;
		case 110: goto st110;
		case 111: goto st111;
		case 112: goto st112;
		case 113: goto st113;
		case 114: goto st114;
		case 115: goto st115;
		case 116: goto st116;
		case 117: goto st117;
		case 118: goto st118;
		case 119: goto st119;
		case 120: goto st120;
		case 121: goto st121;
		case 122: goto st122;
		case 123: goto st123;
		case 124: goto st124;
		case 125: goto st125;
		case 126: goto st126;
		case 127: goto st127;
		case 128: goto st128;
		case 129: goto st129;
		case 130: goto st130;
		case 131: goto st131;
		case 132: goto st132;
		case 133: goto st133;
		case 134: goto st134;
		case 135: goto st135;
		case 136: goto st136;
		case 137: goto st137;
		case 138: goto st138;
		case 139: goto st139;
		case 140: goto st140;
		case 141: goto st141;
		case 142: goto st142;
		case 143: goto st143;
		case 144: goto st144;
		case 145: goto st145;
		case 146: goto st146;
		case 147: goto st147;
		case 148: goto st148;
		case 149: goto st149;
		case 150: goto st150;
		case 151: goto st151;
		case 152: goto st152;
		case 153: goto st153;
		case 154: goto st154;
		case 155: goto st155;
		case 156: goto st156;
		case 157: goto st157;
		case 158: goto st158;
		case 159: goto st159;
		case 160: goto st160;
		case 161: goto st161;
		case 162: goto st162;
		case 163: goto st163;
		case 164: goto st164;
		case 165: goto st165;
		case 166: goto st166;
		case 167: goto st167;
		case 168: goto st168;
		case 169: goto st169;
		case 170: goto st170;
		case 171: goto st171;
		case 172: goto st172;
		case 173: goto st173;
		case 174: goto st174;
		case 175: goto st175;
		case 176: goto st176;
		case 177: goto st177;
		case 178: goto st178;
		case 179: goto st179;
		case 180: goto st180;
		case 181: goto st181;
		case 182: goto st182;
		case 183: goto st183;
		case 184: goto st184;
		case 185: goto st185;
		case 186: goto st186;
		case 187: goto st187;
		case 188: goto st188;
		case 189: goto st189;
		case 190: goto st190;
		case 191: goto st191;
		case 192: goto st192;
		case 193: goto st193;
		case 194: goto st194;
		case 195: goto st195;
		case 196: goto st196;
		case 197: goto st197;
		case 198: goto st198;
		case 199: goto st199;
		case 200: goto st200;
		case 201: goto st201;
		case 202: goto st202;
		case 203: goto st203;
		case 204: goto st204;
		case 205: goto st205;
		case 206: goto st206;
		case 207: goto st207;
		case 208: goto st208;
		case 209: goto st209;
		case 210: goto st210;
		case 211: goto st211;
		case 212: goto st212;
		case 213: goto st213;
		case 214: goto st214;
		case 215: goto st215;
		case 216: goto st216;
		case 217: goto st217;
		case 218: goto st218;
		case 219: goto st219;
		case 220: goto st220;
		case 221: goto st221;
		case 222: goto st222;
		case 223: goto st223;
		case 224: goto st224;
		case 225: goto st225;
		case 226: goto st226;
		case 227: goto st227;
		case 228: goto st228;
		case 229: goto st229;
		case 230: goto st230;
		case 231: goto st231;
		case 232: goto st232;
		case 233: goto st233;
		case 234: goto st234;
		case 235: goto st235;
		case 236: goto st236;
		case 237: goto st237;
		case 238: goto st238;
		case 239: goto st239;
		case 240: goto st240;
		case 241: goto st241;
		case 242: goto st242;
		case 243: goto st243;
		case 244: goto st244;
		case 245: goto st245;
		case 246: goto st246;
		case 247: goto st247;
		case 248: goto st248;
		case 249: goto st249;
		case 250: goto st250;
		case 251: goto st251;
		case 252: goto st252;
		case 253: goto st253;
		case 254: goto st254;
		case 255: goto st255;
		case 256: goto st256;
		case 257: goto st257;
		case 258: goto st258;
		case 259: goto st259;
		case 260: goto st260;
		case 261: goto st261;
		case 262: goto st262;
		case 263: goto st263;
		case 264: goto st264;
		case 265: goto st265;
		case 266: goto st266;
		case 267: goto st267;
		case 268: goto st268;
		case 269: goto st269;
		case 270: goto st270;
		case 271: goto st271;
		case 272: goto st272;
		case 273: goto st273;
		case 274: goto st274;
		case 275: goto st275;
		case 276: goto st276;
		case 277: goto st277;
		case 278: goto st278;
		case 279: goto st279;
		case 280: goto st280;
		case 281: goto st281;
		case 282: goto st282;
		case 283: goto st283;
		case 284: goto st284;
		case 285: goto st285;
		case 286: goto st286;
		case 418: goto st418;
		case 287: goto st287;
		case 288: goto st288;
		case 289: goto st289;
		case 290: goto st290;
		case 291: goto st291;
		case 292: goto st292;
		case 293: goto st293;
		case 294: goto st294;
		case 295: goto st295;
		case 296: goto st296;
		case 297: goto st297;
		case 298: goto st298;
		case 299: goto st299;
		case 300: goto st300;
		case 301: goto st301;
		case 302: goto st302;
		case 303: goto st303;
		case 304: goto st304;
		case 305: goto st305;
		case 306: goto st306;
		case 307: goto st307;
		case 308: goto st308;
		case 309: goto st309;
		case 310: goto st310;
		case 311: goto st311;
		case 312: goto st312;
		case 313: goto st313;
		case 314: goto st314;
		case 315: goto st315;
		case 316: goto st316;
		case 317: goto st317;
		case 318: goto st318;
		case 319: goto st319;
		case 320: goto st320;
		case 321: goto st321;
		case 322: goto st322;
		case 323: goto st323;
		case 324: goto st324;
		case 325: goto st325;
		case 326: goto st326;
		case 327: goto st327;
		case 328: goto st328;
		case 329: goto st329;
		case 330: goto st330;
		case 331: goto st331;
		case 332: goto st332;
		case 333: goto st333;
		case 334: goto st334;
		case 335: goto st335;
		case 336: goto st336;
		case 337: goto st337;
		case 338: goto st338;
		case 339: goto st339;
		case 340: goto st340;
		case 341: goto st341;
		case 342: goto st342;
		case 343: goto st343;
		case 344: goto st344;
		case 345: goto st345;
		case 346: goto st346;
		case 347: goto st347;
		case 348: goto st348;
		case 349: goto st349;
		case 350: goto st350;
		case 351: goto st351;
		case 352: goto st352;
		case 353: goto st353;
		case 354: goto st354;
		case 355: goto st355;
		case 356: goto st356;
		case 357: goto st357;
		case 358: goto st358;
		case 359: goto st359;
		case 360: goto st360;
		case 361: goto st361;
		case 362: goto st362;
		case 363: goto st363;
		case 364: goto st364;
		case 365: goto st365;
		case 366: goto st366;
		case 367: goto st367;
		case 368: goto st368;
		case 369: goto st369;
		case 370: goto st370;
		case 371: goto st371;
		case 372: goto st372;
		case 373: goto st373;
		case 374: goto st374;
		case 375: goto st375;
		case 376: goto st376;
		case 377: goto st377;
		case 378: goto st378;
		case 379: goto st379;
		case 380: goto st380;
		case 381: goto st381;
		case 382: goto st382;
		case 383: goto st383;
		case 384: goto st384;
		case 385: goto st385;
		case 386: goto st386;
		case 387: goto st387;
		case 388: goto st388;
		case 389: goto st389;
		case 390: goto st390;
		case 391: goto st391;
		case 392: goto st392;
		case 393: goto st393;
		case 394: goto st394;
		case 395: goto st395;
		case 396: goto st396;
		case 397: goto st397;
		case 398: goto st398;
		case 399: goto st399;
		case 400: goto st400;
		case 401: goto st401;
		case 402: goto st402;
		case 403: goto st403;
		case 404: goto st404;
		case 405: goto st405;
		case 406: goto st406;
		case 407: goto st407;
		case 408: goto st408;
		case 409: goto st409;
		case 410: goto st410;
		case 411: goto st411;
		case 412: goto st412;
	default: break;
	}

	if ( ++( state.p) == ( state.pe) )
		goto _test_eof;
_resume:
	switch (  state.cs )
	{
st1:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof1;
case 1:
	switch( (*( state.p)) ) {
		case 13: goto st1;
		case 32: goto st1;
		case 100: goto tr2;
		case 115: goto tr3;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1;
	goto st0;
st0:
 state.cs = 0;
	goto _out;
tr2:
#line 270 "configparser.rl"
	{ des = Design(); }
	goto st2;
tr598:
#line 273 "configparser.rl"
	{ std::cout << "design done: " << std::endl; print_design(des); }
#line 270 "configparser.rl"
	{ des = Design(); }
	goto st2;
tr602:
#line 237 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
#line 270 "configparser.rl"
	{ des = Design(); }
	goto st2;
st2:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof2;
case 2:
#line 625 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr4;
	goto st0;
tr4:
#line 270 "configparser.rl"
	{ des = Design(); }
	goto st3;
st3:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof3;
case 3:
#line 637 "configparser.h"
	if ( (*( state.p)) == 115 )
		goto tr5;
	goto st0;
tr5:
#line 270 "configparser.rl"
	{ des = Design(); }
	goto st4;
st4:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof4;
case 4:
#line 649 "configparser.h"
	if ( (*( state.p)) == 105 )
		goto tr6;
	goto st0;
tr6:
#line 270 "configparser.rl"
	{ des = Design(); }
	goto st5;
st5:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof5;
case 5:
#line 661 "configparser.h"
	if ( (*( state.p)) == 103 )
		goto tr7;
	goto st0;
tr7:
#line 270 "configparser.rl"
	{ des = Design(); }
	goto st6;
st6:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof6;
case 6:
#line 673 "configparser.h"
	if ( (*( state.p)) == 110 )
		goto tr8;
	goto st0;
tr8:
#line 270 "configparser.rl"
	{ des = Design(); }
	goto st7;
st7:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof7;
case 7:
#line 685 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st8;
		case 32: goto st8;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st8;
	goto st0;
st8:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof8;
case 8:
	switch( (*( state.p)) ) {
		case 13: goto st8;
		case 32: goto st8;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr10;
	} else if ( (*( state.p)) >= 9 )
		goto st8;
	goto st0;
tr10:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st9;
tr12:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st9;
st9:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof9;
case 9:
#line 727 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr11;
		case 32: goto tr11;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr12;
	} else if ( (*( state.p)) >= 9 )
		goto tr11;
	goto st0;
tr11:
#line 263 "configparser.rl"
	{ des.level = ::atoi(state.match.c_str()); }
	goto st10;
st10:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof10;
case 10:
#line 746 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st10;
		case 32: goto st10;
		case 95: goto tr14;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto st10;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr14;
		} else if ( (*( state.p)) >= 65 )
			goto tr14;
	} else
		goto tr14;
	goto st0;
tr14:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st11;
tr16:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st11;
st11:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof11;
case 11:
#line 784 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr15;
		case 32: goto tr15;
		case 95: goto tr16;
		case 123: goto tr17;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto tr15;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr16;
		} else if ( (*( state.p)) >= 65 )
			goto tr16;
	} else
		goto tr16;
	goto st0;
tr15:
#line 266 "configparser.rl"
	{ des.tag = state.match; }
	goto st12;
st12:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof12;
case 12:
#line 811 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st12;
		case 32: goto st12;
		case 123: goto tr19;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st12;
	goto st0;
tr17:
#line 266 "configparser.rl"
	{ des.tag = state.match; }
#line 272 "configparser.rl"
	{{ state.stack[ state.top++] = 413; goto st276;}}
	goto st413;
tr19:
#line 272 "configparser.rl"
	{{ state.stack[ state.top++] = 413; goto st276;}}
	goto st413;
st413:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof413;
case 413:
#line 834 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr597;
		case 32: goto tr597;
		case 100: goto tr598;
		case 115: goto tr599;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr597;
	goto st0;
tr597:
#line 273 "configparser.rl"
	{ std::cout << "design done: " << std::endl; print_design(des); }
	goto st414;
tr601:
#line 237 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
	goto st414;
st414:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof414;
case 414:
#line 856 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st414;
		case 32: goto st414;
		case 100: goto tr2;
		case 115: goto tr3;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st414;
	goto st0;
tr3:
#line 234 "configparser.rl"
	{ spe = Species(); }
	goto st13;
tr599:
#line 273 "configparser.rl"
	{ std::cout << "design done: " << std::endl; print_design(des); }
#line 234 "configparser.rl"
	{ spe = Species(); }
	goto st13;
tr603:
#line 237 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
#line 234 "configparser.rl"
	{ spe = Species(); }
	goto st13;
st13:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof13;
case 13:
#line 886 "configparser.h"
	if ( (*( state.p)) == 112 )
		goto tr20;
	goto st0;
tr20:
#line 234 "configparser.rl"
	{ spe = Species(); }
	goto st14;
st14:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof14;
case 14:
#line 898 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr21;
	goto st0;
tr21:
#line 234 "configparser.rl"
	{ spe = Species(); }
	goto st15;
st15:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof15;
case 15:
#line 910 "configparser.h"
	if ( (*( state.p)) == 99 )
		goto tr22;
	goto st0;
tr22:
#line 234 "configparser.rl"
	{ spe = Species(); }
	goto st16;
st16:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof16;
case 16:
#line 922 "configparser.h"
	if ( (*( state.p)) == 105 )
		goto tr23;
	goto st0;
tr23:
#line 234 "configparser.rl"
	{ spe = Species(); }
	goto st17;
st17:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof17;
case 17:
#line 934 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr24;
	goto st0;
tr24:
#line 234 "configparser.rl"
	{ spe = Species(); }
	goto st18;
st18:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof18;
case 18:
#line 946 "configparser.h"
	if ( (*( state.p)) == 115 )
		goto tr25;
	goto st0;
tr25:
#line 234 "configparser.rl"
	{ spe = Species(); }
	goto st19;
st19:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof19;
case 19:
#line 958 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st20;
		case 32: goto st20;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st20;
	goto st0;
st20:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof20;
case 20:
	switch( (*( state.p)) ) {
		case 13: goto st20;
		case 32: goto st20;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr27;
	} else if ( (*( state.p)) >= 9 )
		goto st20;
	goto st0;
tr27:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st21;
tr29:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st21;
st21:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof21;
case 21:
#line 1000 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr28;
		case 32: goto tr28;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr29;
	} else if ( (*( state.p)) >= 9 )
		goto tr28;
	goto st0;
tr28:
#line 227 "configparser.rl"
	{ spe.level = ::atoi(state.match.c_str()); }
	goto st22;
st22:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof22;
case 22:
#line 1019 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st22;
		case 32: goto st22;
		case 95: goto tr31;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto st22;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr31;
		} else if ( (*( state.p)) >= 65 )
			goto tr31;
	} else
		goto tr31;
	goto st0;
tr31:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st23;
tr33:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st23;
st23:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof23;
case 23:
#line 1057 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr32;
		case 32: goto tr32;
		case 95: goto tr33;
		case 123: goto tr34;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto tr32;
	} else if ( (*( state.p)) > 57 ) {
		if ( (*( state.p)) > 90 ) {
			if ( 97 <= (*( state.p)) && (*( state.p)) <= 122 )
				goto tr33;
		} else if ( (*( state.p)) >= 65 )
			goto tr33;
	} else
		goto tr33;
	goto st0;
tr32:
#line 230 "configparser.rl"
	{ spe.tag = state.match; }
	goto st24;
st24:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof24;
case 24:
#line 1084 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st24;
		case 32: goto st24;
		case 123: goto tr36;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st24;
	goto st0;
tr34:
#line 230 "configparser.rl"
	{ spe.tag = state.match; }
#line 236 "configparser.rl"
	{{ state.stack[ state.top++] = 415; goto st26;}}
	goto st415;
tr36:
#line 236 "configparser.rl"
	{{ state.stack[ state.top++] = 415; goto st26;}}
	goto st415;
st415:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof415;
case 415:
#line 1107 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr601;
		case 32: goto tr601;
		case 100: goto tr602;
		case 115: goto tr603;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr601;
	goto st0;
st25:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof25;
case 25:
	switch( (*( state.p)) ) {
		case 34: goto tr37;
		case 92: goto tr38;
		case 110: goto tr39;
	}
	goto st0;
tr37:
#line 136 "configparser.rl"
	{ state.match += '"';  { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st416;
tr38:
#line 138 "configparser.rl"
	{ state.match += '\\'; { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st416;
tr39:
#line 137 "configparser.rl"
	{ state.match += '\n'; { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st416;
st416:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof416;
case 416:
#line 1143 "configparser.h"
	goto st0;
st26:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof26;
case 26:
	switch( (*( state.p)) ) {
		case 13: goto st26;
		case 32: goto st26;
		case 97: goto st27;
		case 99: goto st35;
		case 100: goto st75;
		case 104: goto st98;
		case 105: goto st133;
		case 109: goto st151;
		case 110: goto st175;
		case 114: goto st182;
		case 115: goto st189;
		case 125: goto st248;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st26;
	goto st0;
st27:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof27;
case 27:
	switch( (*( state.p)) ) {
		case 105: goto st28;
		case 116: goto st266;
	}
	goto st0;
st28:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof28;
case 28:
	switch( (*( state.p)) ) {
		case 13: goto st29;
		case 32: goto st29;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st29;
	goto st0;
st29:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof29;
case 29:
	switch( (*( state.p)) ) {
		case 13: goto st29;
		case 32: goto st29;
		case 110: goto st30;
		case 114: goto st249;
		case 115: goto st255;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st29;
	goto st0;
st30:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof30;
case 30:
	if ( (*( state.p)) == 111 )
		goto st31;
	goto st0;
st31:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof31;
case 31:
	if ( (*( state.p)) == 110 )
		goto st32;
	goto st0;
st32:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof32;
case 32:
	if ( (*( state.p)) == 101 )
		goto st33;
	goto st0;
st33:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof33;
case 33:
	switch( (*( state.p)) ) {
		case 13: goto tr60;
		case 32: goto tr60;
		case 59: goto tr61;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr60;
	goto st0;
tr60:
#line 176 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st34;
tr83:
#line 203 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st34;
tr107:
#line 208 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st34;
tr115:
#line 190 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
	goto st34;
tr129:
#line 199 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st34;
tr146:
#line 213 "configparser.rl"
	{ spe.drop.back().chance = ::atof(state.match.c_str()); }
	goto st34;
tr166:
#line 172 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st34;
tr172:
#line 170 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st34;
tr182:
#line 173 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st34;
tr188:
#line 169 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st34;
tr192:
#line 171 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st34;
tr206:
#line 181 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st34;
tr213:
#line 182 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st34;
tr225:
#line 185 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st34;
tr232:
#line 188 "configparser.rl"
	{ spe.move = Species::move_t::corner; }
	goto st34;
tr238:
#line 186 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st34;
tr244:
#line 187 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st34;
tr254:
#line 191 "configparser.rl"
	{ spe.name = state.match; }
	goto st34;
tr262:
#line 197 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st34;
tr305:
#line 192 "configparser.rl"
	{ spe.skin = skin; }
	goto st34;
tr308:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 192 "configparser.rl"
	{ spe.skin = skin; }
	goto st34;
tr313:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 192 "configparser.rl"
	{ spe.skin = skin; }
	goto st34;
tr319:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 192 "configparser.rl"
	{ spe.skin = skin; }
	goto st34;
tr327:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 192 "configparser.rl"
	{ spe.skin = skin; }
	goto st34;
tr331:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 192 "configparser.rl"
	{ spe.skin = skin; }
	goto st34;
tr337:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 192 "configparser.rl"
	{ spe.skin = skin; }
	goto st34;
tr344:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 192 "configparser.rl"
	{ spe.skin = skin; }
	goto st34;
tr359:
#line 221 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st34;
tr366:
#line 178 "configparser.rl"
	{ spe.ai = Species::ai_t::random; }
	goto st34;
tr378:
#line 177 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st34;
tr388:
#line 198 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st34;
st34:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof34;
case 34:
#line 1375 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st34;
		case 32: goto st34;
		case 59: goto st417;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st34;
	goto st0;
tr61:
#line 176 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st417;
tr85:
#line 203 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st417;
tr109:
#line 208 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st417;
tr117:
#line 190 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
	goto st417;
tr131:
#line 199 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st417;
tr148:
#line 213 "configparser.rl"
	{ spe.drop.back().chance = ::atof(state.match.c_str()); }
	goto st417;
tr167:
#line 172 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st417;
tr173:
#line 170 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st417;
tr183:
#line 173 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st417;
tr189:
#line 169 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st417;
tr193:
#line 171 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st417;
tr207:
#line 181 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st417;
tr214:
#line 182 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st417;
tr226:
#line 185 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st417;
tr233:
#line 188 "configparser.rl"
	{ spe.move = Species::move_t::corner; }
	goto st417;
tr239:
#line 186 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st417;
tr245:
#line 187 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st417;
tr255:
#line 191 "configparser.rl"
	{ spe.name = state.match; }
	goto st417;
tr264:
#line 197 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st417;
tr306:
#line 192 "configparser.rl"
	{ spe.skin = skin; }
	goto st417;
tr309:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 192 "configparser.rl"
	{ spe.skin = skin; }
	goto st417;
tr314:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 192 "configparser.rl"
	{ spe.skin = skin; }
	goto st417;
tr320:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 192 "configparser.rl"
	{ spe.skin = skin; }
	goto st417;
tr328:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 192 "configparser.rl"
	{ spe.skin = skin; }
	goto st417;
tr332:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 192 "configparser.rl"
	{ spe.skin = skin; }
	goto st417;
tr338:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 192 "configparser.rl"
	{ spe.skin = skin; }
	goto st417;
tr345:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 192 "configparser.rl"
	{ spe.skin = skin; }
	goto st417;
tr360:
#line 221 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st417;
tr367:
#line 178 "configparser.rl"
	{ spe.ai = Species::ai_t::random; }
	goto st417;
tr379:
#line 177 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st417;
tr390:
#line 198 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st417;
st417:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof417;
case 417:
#line 1526 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st26;
		case 32: goto st26;
		case 97: goto st27;
		case 99: goto st35;
		case 100: goto st75;
		case 104: goto st98;
		case 105: goto st133;
		case 109: goto st151;
		case 110: goto st175;
		case 114: goto st182;
		case 115: goto st189;
		case 125: goto st248;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st26;
	goto st0;
st35:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof35;
case 35:
	switch( (*( state.p)) ) {
		case 108: goto st36;
		case 111: goto st54;
	}
	goto st0;
st36:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof36;
case 36:
	if ( (*( state.p)) == 117 )
		goto st37;
	goto st0;
st37:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof37;
case 37:
	if ( (*( state.p)) == 109 )
		goto st38;
	goto st0;
st38:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof38;
case 38:
	if ( (*( state.p)) == 112 )
		goto st39;
	goto st0;
st39:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof39;
case 39:
	if ( (*( state.p)) == 115 )
		goto st40;
	goto st0;
st40:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof40;
case 40:
	if ( (*( state.p)) == 105 )
		goto st41;
	goto st0;
st41:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof41;
case 41:
	if ( (*( state.p)) == 122 )
		goto st42;
	goto st0;
st42:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof42;
case 42:
	if ( (*( state.p)) == 101 )
		goto st43;
	goto st0;
st43:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof43;
case 43:
	switch( (*( state.p)) ) {
		case 13: goto st44;
		case 32: goto st44;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st44;
	goto st0;
st44:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof44;
case 44:
	switch( (*( state.p)) ) {
		case 13: goto st44;
		case 32: goto st44;
		case 45: goto tr74;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr75;
	} else if ( (*( state.p)) >= 9 )
		goto st44;
	goto st0;
tr74:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st45;
st45:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof45;
case 45:
#line 1642 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr76;
	goto st0;
tr75:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st46;
tr76:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st46;
st46:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof46;
case 46:
#line 1666 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr77;
		case 32: goto tr77;
		case 46: goto tr78;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr76;
	} else if ( (*( state.p)) >= 9 )
		goto tr77;
	goto st0;
tr77:
#line 202 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st47;
st47:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof47;
case 47:
#line 1686 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st47;
		case 32: goto st47;
		case 45: goto tr80;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr81;
	} else if ( (*( state.p)) >= 9 )
		goto st47;
	goto st0;
tr80:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st48;
st48:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof48;
case 48:
#line 1712 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr82;
	goto st0;
tr81:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st49;
tr82:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st49;
st49:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof49;
case 49:
#line 1736 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr83;
		case 32: goto tr83;
		case 46: goto tr84;
		case 59: goto tr85;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr82;
	} else if ( (*( state.p)) >= 9 )
		goto tr83;
	goto st0;
tr84:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st50;
st50:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof50;
case 50:
#line 1759 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr86;
	goto st0;
tr86:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st51;
st51:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof51;
case 51:
#line 1773 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr83;
		case 32: goto tr83;
		case 59: goto tr85;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr86;
	} else if ( (*( state.p)) >= 9 )
		goto tr83;
	goto st0;
tr78:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st52;
st52:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof52;
case 52:
#line 1795 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr87;
	goto st0;
tr87:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st53;
st53:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof53;
case 53:
#line 1809 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr77;
		case 32: goto tr77;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr87;
	} else if ( (*( state.p)) >= 9 )
		goto tr77;
	goto st0;
st54:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof54;
case 54:
	switch( (*( state.p)) ) {
		case 109: goto st55;
		case 117: goto st70;
	}
	goto st0;
st55:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof55;
case 55:
	if ( (*( state.p)) == 112 )
		goto st56;
	goto st0;
st56:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof56;
case 56:
	if ( (*( state.p)) == 97 )
		goto st57;
	goto st0;
st57:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof57;
case 57:
	if ( (*( state.p)) == 110 )
		goto st58;
	goto st0;
st58:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof58;
case 58:
	if ( (*( state.p)) == 105 )
		goto st59;
	goto st0;
st59:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof59;
case 59:
	if ( (*( state.p)) == 111 )
		goto st60;
	goto st0;
st60:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof60;
case 60:
	if ( (*( state.p)) == 110 )
		goto st61;
	goto st0;
st61:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof61;
case 61:
	switch( (*( state.p)) ) {
		case 13: goto tr96;
		case 32: goto tr96;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr96;
	goto st0;
tr96:
#line 206 "configparser.rl"
	{ spe.companion.push_back(Species::companion_t()); }
	goto st62;
st62:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof62;
case 62:
#line 1890 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st62;
		case 32: goto st62;
		case 34: goto tr98;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st62;
	goto st0;
tr99:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st63;
tr98:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st63;
tr101:
#line 142 "configparser.rl"
	{{ state.stack[ state.top++] = 63; goto st25;}}
	goto st63;
st63:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof63;
case 63:
#line 1919 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st64;
		case 92: goto tr101;
	}
	goto tr99;
st64:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof64;
case 64:
	switch( (*( state.p)) ) {
		case 13: goto tr102;
		case 32: goto tr102;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr102;
	goto st0;
tr102:
#line 207 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st65;
st65:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof65;
case 65:
#line 1944 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st65;
		case 32: goto st65;
		case 45: goto tr104;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr105;
	} else if ( (*( state.p)) >= 9 )
		goto st65;
	goto st0;
tr104:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st66;
st66:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof66;
case 66:
#line 1970 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr106;
	goto st0;
tr105:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st67;
tr106:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st67;
st67:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof67;
case 67:
#line 1994 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr107;
		case 32: goto tr107;
		case 46: goto tr108;
		case 59: goto tr109;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr106;
	} else if ( (*( state.p)) >= 9 )
		goto tr107;
	goto st0;
tr108:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st68;
st68:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof68;
case 68:
#line 2017 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr110;
	goto st0;
tr110:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st69;
st69:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof69;
case 69:
#line 2031 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr107;
		case 32: goto tr107;
		case 59: goto tr109;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr110;
	} else if ( (*( state.p)) >= 9 )
		goto tr107;
	goto st0;
st70:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof70;
case 70:
	if ( (*( state.p)) == 110 )
		goto st71;
	goto st0;
st71:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof71;
case 71:
	if ( (*( state.p)) == 116 )
		goto st72;
	goto st0;
st72:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof72;
case 72:
	switch( (*( state.p)) ) {
		case 13: goto st73;
		case 32: goto st73;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st73;
	goto st0;
st73:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof73;
case 73:
	switch( (*( state.p)) ) {
		case 13: goto st73;
		case 32: goto st73;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr114;
	} else if ( (*( state.p)) >= 9 )
		goto st73;
	goto st0;
tr114:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
tr116:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
st74:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof74;
case 74:
#line 2102 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr115;
		case 32: goto tr115;
		case 59: goto tr117;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr116;
	} else if ( (*( state.p)) >= 9 )
		goto tr115;
	goto st0;
st75:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof75;
case 75:
	switch( (*( state.p)) ) {
		case 101: goto st76;
		case 114: goto st87;
	}
	goto st0;
st76:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof76;
case 76:
	if ( (*( state.p)) == 102 )
		goto st77;
	goto st0;
st77:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof77;
case 77:
	if ( (*( state.p)) == 101 )
		goto st78;
	goto st0;
st78:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof78;
case 78:
	if ( (*( state.p)) == 110 )
		goto st79;
	goto st0;
st79:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof79;
case 79:
	if ( (*( state.p)) == 115 )
		goto st80;
	goto st0;
st80:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof80;
case 80:
	if ( (*( state.p)) == 101 )
		goto st81;
	goto st0;
st81:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof81;
case 81:
	switch( (*( state.p)) ) {
		case 13: goto st82;
		case 32: goto st82;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st82;
	goto st0;
st82:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof82;
case 82:
	switch( (*( state.p)) ) {
		case 13: goto st82;
		case 32: goto st82;
		case 45: goto tr126;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr127;
	} else if ( (*( state.p)) >= 9 )
		goto st82;
	goto st0;
tr126:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st83;
st83:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof83;
case 83:
#line 2198 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr128;
	goto st0;
tr127:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st84;
tr128:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st84;
st84:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof84;
case 84:
#line 2222 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr129;
		case 32: goto tr129;
		case 46: goto tr130;
		case 59: goto tr131;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr128;
	} else if ( (*( state.p)) >= 9 )
		goto tr129;
	goto st0;
tr130:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st85;
st85:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof85;
case 85:
#line 2245 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr132;
	goto st0;
tr132:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st86;
st86:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof86;
case 86:
#line 2259 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr129;
		case 32: goto tr129;
		case 59: goto tr131;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr132;
	} else if ( (*( state.p)) >= 9 )
		goto tr129;
	goto st0;
st87:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof87;
case 87:
	if ( (*( state.p)) == 111 )
		goto st88;
	goto st0;
st88:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof88;
case 88:
	if ( (*( state.p)) == 112 )
		goto st89;
	goto st0;
st89:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof89;
case 89:
	switch( (*( state.p)) ) {
		case 13: goto tr135;
		case 32: goto tr135;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr135;
	goto st0;
tr135:
#line 211 "configparser.rl"
	{ spe.drop.push_back(Species::drop_t()); }
	goto st90;
st90:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof90;
case 90:
#line 2304 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st90;
		case 32: goto st90;
		case 34: goto tr137;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st90;
	goto st0;
tr138:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st91;
tr137:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st91;
tr140:
#line 142 "configparser.rl"
	{{ state.stack[ state.top++] = 91; goto st25;}}
	goto st91;
st91:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof91;
case 91:
#line 2333 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st92;
		case 92: goto tr140;
	}
	goto tr138;
st92:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof92;
case 92:
	switch( (*( state.p)) ) {
		case 13: goto tr141;
		case 32: goto tr141;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr141;
	goto st0;
tr141:
#line 212 "configparser.rl"
	{ spe.drop.back().tag = state.match; }
	goto st93;
st93:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof93;
case 93:
#line 2358 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st93;
		case 32: goto st93;
		case 45: goto tr143;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr144;
	} else if ( (*( state.p)) >= 9 )
		goto st93;
	goto st0;
tr143:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st94;
st94:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof94;
case 94:
#line 2384 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr145;
	goto st0;
tr144:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st95;
tr145:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st95;
st95:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof95;
case 95:
#line 2408 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr146;
		case 32: goto tr146;
		case 46: goto tr147;
		case 59: goto tr148;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr145;
	} else if ( (*( state.p)) >= 9 )
		goto tr146;
	goto st0;
tr147:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st96;
st96:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof96;
case 96:
#line 2431 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr149;
	goto st0;
tr149:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st97;
st97:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof97;
case 97:
#line 2445 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr146;
		case 32: goto tr146;
		case 59: goto tr148;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr149;
	} else if ( (*( state.p)) >= 9 )
		goto tr146;
	goto st0;
st98:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof98;
case 98:
	if ( (*( state.p)) == 97 )
		goto st99;
	goto st0;
st99:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof99;
case 99:
	if ( (*( state.p)) == 98 )
		goto st100;
	goto st0;
st100:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof100;
case 100:
	if ( (*( state.p)) == 105 )
		goto st101;
	goto st0;
st101:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof101;
case 101:
	if ( (*( state.p)) == 116 )
		goto st102;
	goto st0;
st102:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof102;
case 102:
	if ( (*( state.p)) == 97 )
		goto st103;
	goto st0;
st103:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof103;
case 103:
	if ( (*( state.p)) == 116 )
		goto st104;
	goto st0;
st104:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof104;
case 104:
	switch( (*( state.p)) ) {
		case 13: goto st105;
		case 32: goto st105;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st105;
	goto st0;
st105:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof105;
case 105:
	switch( (*( state.p)) ) {
		case 13: goto st105;
		case 32: goto st105;
		case 99: goto st106;
		case 102: goto st112;
		case 115: goto st117;
		case 119: goto st126;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st105;
	goto st0;
st106:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof106;
case 106:
	if ( (*( state.p)) == 111 )
		goto st107;
	goto st0;
st107:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof107;
case 107:
	if ( (*( state.p)) == 114 )
		goto st108;
	goto st0;
st108:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof108;
case 108:
	if ( (*( state.p)) == 110 )
		goto st109;
	goto st0;
st109:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof109;
case 109:
	if ( (*( state.p)) == 101 )
		goto st110;
	goto st0;
st110:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof110;
case 110:
	if ( (*( state.p)) == 114 )
		goto st111;
	goto st0;
st111:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof111;
case 111:
	switch( (*( state.p)) ) {
		case 13: goto tr166;
		case 32: goto tr166;
		case 59: goto tr167;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr166;
	goto st0;
st112:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof112;
case 112:
	if ( (*( state.p)) == 108 )
		goto st113;
	goto st0;
st113:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof113;
case 113:
	if ( (*( state.p)) == 111 )
		goto st114;
	goto st0;
st114:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof114;
case 114:
	if ( (*( state.p)) == 111 )
		goto st115;
	goto st0;
st115:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof115;
case 115:
	if ( (*( state.p)) == 114 )
		goto st116;
	goto st0;
st116:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof116;
case 116:
	switch( (*( state.p)) ) {
		case 13: goto tr172;
		case 32: goto tr172;
		case 59: goto tr173;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr172;
	goto st0;
st117:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof117;
case 117:
	if ( (*( state.p)) == 104 )
		goto st118;
	goto st0;
st118:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof118;
case 118:
	if ( (*( state.p)) == 111 )
		goto st119;
	goto st0;
st119:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof119;
case 119:
	if ( (*( state.p)) == 114 )
		goto st120;
	goto st0;
st120:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof120;
case 120:
	if ( (*( state.p)) == 101 )
		goto st121;
	goto st0;
st121:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof121;
case 121:
	if ( (*( state.p)) == 108 )
		goto st122;
	goto st0;
st122:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof122;
case 122:
	if ( (*( state.p)) == 105 )
		goto st123;
	goto st0;
st123:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof123;
case 123:
	if ( (*( state.p)) == 110 )
		goto st124;
	goto st0;
st124:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof124;
case 124:
	if ( (*( state.p)) == 101 )
		goto st125;
	goto st0;
st125:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof125;
case 125:
	switch( (*( state.p)) ) {
		case 13: goto tr182;
		case 32: goto tr182;
		case 59: goto tr183;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr182;
	goto st0;
st126:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof126;
case 126:
	if ( (*( state.p)) == 97 )
		goto st127;
	goto st0;
st127:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof127;
case 127:
	switch( (*( state.p)) ) {
		case 108: goto st128;
		case 116: goto st130;
	}
	goto st0;
st128:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof128;
case 128:
	if ( (*( state.p)) == 107 )
		goto st129;
	goto st0;
st129:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof129;
case 129:
	switch( (*( state.p)) ) {
		case 13: goto tr188;
		case 32: goto tr188;
		case 59: goto tr189;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr188;
	goto st0;
st130:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof130;
case 130:
	if ( (*( state.p)) == 101 )
		goto st131;
	goto st0;
st131:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof131;
case 131:
	if ( (*( state.p)) == 114 )
		goto st132;
	goto st0;
st132:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof132;
case 132:
	switch( (*( state.p)) ) {
		case 13: goto tr192;
		case 32: goto tr192;
		case 59: goto tr193;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr192;
	goto st0;
st133:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof133;
case 133:
	if ( (*( state.p)) == 100 )
		goto st134;
	goto st0;
st134:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof134;
case 134:
	if ( (*( state.p)) == 108 )
		goto st135;
	goto st0;
st135:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof135;
case 135:
	if ( (*( state.p)) == 101 )
		goto st136;
	goto st0;
st136:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof136;
case 136:
	if ( (*( state.p)) == 95 )
		goto st137;
	goto st0;
st137:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof137;
case 137:
	if ( (*( state.p)) == 97 )
		goto st138;
	goto st0;
st138:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof138;
case 138:
	if ( (*( state.p)) == 105 )
		goto st139;
	goto st0;
st139:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof139;
case 139:
	switch( (*( state.p)) ) {
		case 13: goto st140;
		case 32: goto st140;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st140;
	goto st0;
st140:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof140;
case 140:
	switch( (*( state.p)) ) {
		case 13: goto st140;
		case 32: goto st140;
		case 110: goto st141;
		case 114: goto st145;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st140;
	goto st0;
st141:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof141;
case 141:
	if ( (*( state.p)) == 111 )
		goto st142;
	goto st0;
st142:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof142;
case 142:
	if ( (*( state.p)) == 110 )
		goto st143;
	goto st0;
st143:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof143;
case 143:
	if ( (*( state.p)) == 101 )
		goto st144;
	goto st0;
st144:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof144;
case 144:
	switch( (*( state.p)) ) {
		case 13: goto tr206;
		case 32: goto tr206;
		case 59: goto tr207;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr206;
	goto st0;
st145:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof145;
case 145:
	if ( (*( state.p)) == 97 )
		goto st146;
	goto st0;
st146:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof146;
case 146:
	if ( (*( state.p)) == 110 )
		goto st147;
	goto st0;
st147:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof147;
case 147:
	if ( (*( state.p)) == 100 )
		goto st148;
	goto st0;
st148:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof148;
case 148:
	if ( (*( state.p)) == 111 )
		goto st149;
	goto st0;
st149:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof149;
case 149:
	if ( (*( state.p)) == 109 )
		goto st150;
	goto st0;
st150:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof150;
case 150:
	switch( (*( state.p)) ) {
		case 13: goto tr213;
		case 32: goto tr213;
		case 59: goto tr214;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr213;
	goto st0;
st151:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof151;
case 151:
	if ( (*( state.p)) == 111 )
		goto st152;
	goto st0;
st152:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof152;
case 152:
	if ( (*( state.p)) == 118 )
		goto st153;
	goto st0;
st153:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof153;
case 153:
	if ( (*( state.p)) == 101 )
		goto st154;
	goto st0;
st154:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof154;
case 154:
	switch( (*( state.p)) ) {
		case 13: goto st155;
		case 32: goto st155;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st155;
	goto st0;
st155:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof155;
case 155:
	switch( (*( state.p)) ) {
		case 13: goto st155;
		case 32: goto st155;
		case 97: goto st156;
		case 99: goto st159;
		case 102: goto st165;
		case 119: goto st170;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st155;
	goto st0;
st156:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof156;
case 156:
	if ( (*( state.p)) == 110 )
		goto st157;
	goto st0;
st157:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof157;
case 157:
	if ( (*( state.p)) == 121 )
		goto st158;
	goto st0;
st158:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof158;
case 158:
	switch( (*( state.p)) ) {
		case 13: goto tr225;
		case 32: goto tr225;
		case 59: goto tr226;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr225;
	goto st0;
st159:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof159;
case 159:
	if ( (*( state.p)) == 111 )
		goto st160;
	goto st0;
st160:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof160;
case 160:
	if ( (*( state.p)) == 114 )
		goto st161;
	goto st0;
st161:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof161;
case 161:
	if ( (*( state.p)) == 110 )
		goto st162;
	goto st0;
st162:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof162;
case 162:
	if ( (*( state.p)) == 101 )
		goto st163;
	goto st0;
st163:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof163;
case 163:
	if ( (*( state.p)) == 114 )
		goto st164;
	goto st0;
st164:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof164;
case 164:
	switch( (*( state.p)) ) {
		case 13: goto tr232;
		case 32: goto tr232;
		case 59: goto tr233;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr232;
	goto st0;
st165:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof165;
case 165:
	if ( (*( state.p)) == 108 )
		goto st166;
	goto st0;
st166:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof166;
case 166:
	if ( (*( state.p)) == 111 )
		goto st167;
	goto st0;
st167:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof167;
case 167:
	if ( (*( state.p)) == 111 )
		goto st168;
	goto st0;
st168:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof168;
case 168:
	if ( (*( state.p)) == 114 )
		goto st169;
	goto st0;
st169:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof169;
case 169:
	switch( (*( state.p)) ) {
		case 13: goto tr238;
		case 32: goto tr238;
		case 59: goto tr239;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr238;
	goto st0;
st170:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof170;
case 170:
	if ( (*( state.p)) == 97 )
		goto st171;
	goto st0;
st171:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof171;
case 171:
	if ( (*( state.p)) == 116 )
		goto st172;
	goto st0;
st172:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof172;
case 172:
	if ( (*( state.p)) == 101 )
		goto st173;
	goto st0;
st173:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof173;
case 173:
	if ( (*( state.p)) == 114 )
		goto st174;
	goto st0;
st174:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof174;
case 174:
	switch( (*( state.p)) ) {
		case 13: goto tr244;
		case 32: goto tr244;
		case 59: goto tr245;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr244;
	goto st0;
st175:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof175;
case 175:
	if ( (*( state.p)) == 97 )
		goto st176;
	goto st0;
st176:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof176;
case 176:
	if ( (*( state.p)) == 109 )
		goto st177;
	goto st0;
st177:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof177;
case 177:
	if ( (*( state.p)) == 101 )
		goto st178;
	goto st0;
st178:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof178;
case 178:
	switch( (*( state.p)) ) {
		case 13: goto st179;
		case 32: goto st179;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st179;
	goto st0;
st179:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof179;
case 179:
	switch( (*( state.p)) ) {
		case 13: goto st179;
		case 32: goto st179;
		case 34: goto tr250;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st179;
	goto st0;
tr251:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st180;
tr250:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st180;
tr253:
#line 142 "configparser.rl"
	{{ state.stack[ state.top++] = 180; goto st25;}}
	goto st180;
st180:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof180;
case 180:
#line 3151 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st181;
		case 92: goto tr253;
	}
	goto tr251;
st181:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof181;
case 181:
	switch( (*( state.p)) ) {
		case 13: goto tr254;
		case 32: goto tr254;
		case 59: goto tr255;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr254;
	goto st0;
st182:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof182;
case 182:
	if ( (*( state.p)) == 97 )
		goto st183;
	goto st0;
st183:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof183;
case 183:
	if ( (*( state.p)) == 110 )
		goto st184;
	goto st0;
st184:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof184;
case 184:
	if ( (*( state.p)) == 103 )
		goto st185;
	goto st0;
st185:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof185;
case 185:
	if ( (*( state.p)) == 101 )
		goto st186;
	goto st0;
st186:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof186;
case 186:
	switch( (*( state.p)) ) {
		case 13: goto st187;
		case 32: goto st187;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st187;
	goto st0;
st187:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof187;
case 187:
	switch( (*( state.p)) ) {
		case 13: goto st187;
		case 32: goto st187;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr261;
	} else if ( (*( state.p)) >= 9 )
		goto st187;
	goto st0;
tr261:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st188;
tr263:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st188;
st188:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof188;
case 188:
#line 3242 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr262;
		case 32: goto tr262;
		case 59: goto tr264;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr263;
	} else if ( (*( state.p)) >= 9 )
		goto tr262;
	goto st0;
st189:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof189;
case 189:
	if ( (*( state.p)) == 107 )
		goto st190;
	goto st0;
st190:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof190;
case 190:
	if ( (*( state.p)) == 105 )
		goto st191;
	goto st0;
st191:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof191;
case 191:
	if ( (*( state.p)) == 110 )
		goto st192;
	goto st0;
st192:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof192;
case 192:
	switch( (*( state.p)) ) {
		case 13: goto st193;
		case 32: goto st193;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st193;
	goto st0;
st193:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof193;
case 193:
	switch( (*( state.p)) ) {
		case 13: goto st193;
		case 32: goto st193;
		case 34: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st193;
	goto st0;
tr270:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st194;
tr269:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st194;
tr272:
#line 142 "configparser.rl"
	{{ state.stack[ state.top++] = 194; goto st25;}}
	goto st194;
st194:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof194;
case 194:
#line 3318 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st195;
		case 92: goto tr272;
	}
	goto tr270;
st195:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof195;
case 195:
	switch( (*( state.p)) ) {
		case 13: goto tr273;
		case 32: goto tr273;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr273;
	goto st0;
tr273:
#line 164 "configparser.rl"
	{ skin.text = state.match; }
	goto st196;
st196:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof196;
case 196:
#line 3343 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st196;
		case 32: goto st196;
		case 98: goto st197;
		case 100: goto st242;
		case 110: goto st245;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st196;
	goto st0;
st197:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof197;
case 197:
	if ( (*( state.p)) == 114 )
		goto st198;
	goto st0;
st198:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof198;
case 198:
	if ( (*( state.p)) == 105 )
		goto st199;
	goto st0;
st199:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof199;
case 199:
	if ( (*( state.p)) == 103 )
		goto st200;
	goto st0;
st200:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof200;
case 200:
	if ( (*( state.p)) == 104 )
		goto st201;
	goto st0;
st201:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof201;
case 201:
	if ( (*( state.p)) == 116 )
		goto st202;
	goto st0;
st202:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof202;
case 202:
	switch( (*( state.p)) ) {
		case 13: goto tr283;
		case 32: goto tr283;
		case 95: goto tr284;
		case 98: goto tr285;
		case 99: goto tr286;
		case 103: goto tr287;
		case 109: goto tr288;
		case 114: goto tr289;
		case 119: goto tr290;
		case 121: goto tr291;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr283;
	goto st0;
tr283:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st203;
tr348:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st203;
st203:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof203;
case 203:
#line 3420 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st203;
		case 32: goto st203;
		case 98: goto st204;
		case 99: goto st211;
		case 103: goto st215;
		case 109: goto st220;
		case 114: goto st227;
		case 119: goto st230;
		case 121: goto st235;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st203;
	goto st0;
tr285:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st204;
tr350:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st204;
st204:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof204;
case 204:
#line 3447 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st205;
	goto st0;
st205:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof205;
case 205:
	switch( (*( state.p)) ) {
		case 97: goto st206;
		case 117: goto st209;
	}
	goto st0;
st206:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof206;
case 206:
	if ( (*( state.p)) == 99 )
		goto st207;
	goto st0;
st207:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof207;
case 207:
	if ( (*( state.p)) == 107 )
		goto st208;
	goto st0;
st208:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof208;
case 208:
	switch( (*( state.p)) ) {
		case 13: goto tr305;
		case 32: goto tr305;
		case 59: goto tr306;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr305;
	goto st0;
st209:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof209;
case 209:
	if ( (*( state.p)) == 101 )
		goto st210;
	goto st0;
st210:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof210;
case 210:
	switch( (*( state.p)) ) {
		case 13: goto tr308;
		case 32: goto tr308;
		case 59: goto tr309;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr308;
	goto st0;
tr286:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st211;
tr351:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st211;
st211:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof211;
case 211:
#line 3517 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st212;
	goto st0;
st212:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof212;
case 212:
	if ( (*( state.p)) == 97 )
		goto st213;
	goto st0;
st213:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof213;
case 213:
	if ( (*( state.p)) == 110 )
		goto st214;
	goto st0;
st214:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof214;
case 214:
	switch( (*( state.p)) ) {
		case 13: goto tr313;
		case 32: goto tr313;
		case 59: goto tr314;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr313;
	goto st0;
tr287:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st215;
tr352:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st215;
st215:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof215;
case 215:
#line 3559 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st216;
	goto st0;
st216:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof216;
case 216:
	if ( (*( state.p)) == 101 )
		goto st217;
	goto st0;
st217:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof217;
case 217:
	if ( (*( state.p)) == 101 )
		goto st218;
	goto st0;
st218:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof218;
case 218:
	if ( (*( state.p)) == 110 )
		goto st219;
	goto st0;
st219:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof219;
case 219:
	switch( (*( state.p)) ) {
		case 13: goto tr319;
		case 32: goto tr319;
		case 59: goto tr320;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr319;
	goto st0;
tr288:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st220;
tr353:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st220;
st220:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof220;
case 220:
#line 3608 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st221;
	goto st0;
st221:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof221;
case 221:
	if ( (*( state.p)) == 103 )
		goto st222;
	goto st0;
st222:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof222;
case 222:
	if ( (*( state.p)) == 101 )
		goto st223;
	goto st0;
st223:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof223;
case 223:
	if ( (*( state.p)) == 110 )
		goto st224;
	goto st0;
st224:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof224;
case 224:
	if ( (*( state.p)) == 116 )
		goto st225;
	goto st0;
st225:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof225;
case 225:
	if ( (*( state.p)) == 97 )
		goto st226;
	goto st0;
st226:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof226;
case 226:
	switch( (*( state.p)) ) {
		case 13: goto tr327;
		case 32: goto tr327;
		case 59: goto tr328;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr327;
	goto st0;
tr289:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st227;
tr354:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st227;
st227:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof227;
case 227:
#line 3671 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st228;
	goto st0;
st228:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof228;
case 228:
	if ( (*( state.p)) == 100 )
		goto st229;
	goto st0;
st229:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof229;
case 229:
	switch( (*( state.p)) ) {
		case 13: goto tr331;
		case 32: goto tr331;
		case 59: goto tr332;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr331;
	goto st0;
tr290:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st230;
tr355:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st230;
st230:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof230;
case 230:
#line 3706 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st231;
	goto st0;
st231:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof231;
case 231:
	if ( (*( state.p)) == 105 )
		goto st232;
	goto st0;
st232:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof232;
case 232:
	if ( (*( state.p)) == 116 )
		goto st233;
	goto st0;
st233:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof233;
case 233:
	if ( (*( state.p)) == 101 )
		goto st234;
	goto st0;
st234:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof234;
case 234:
	switch( (*( state.p)) ) {
		case 13: goto tr337;
		case 32: goto tr337;
		case 59: goto tr338;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr337;
	goto st0;
tr291:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st235;
tr356:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st235;
st235:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof235;
case 235:
#line 3755 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st236;
	goto st0;
st236:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof236;
case 236:
	if ( (*( state.p)) == 108 )
		goto st237;
	goto st0;
st237:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof237;
case 237:
	if ( (*( state.p)) == 108 )
		goto st238;
	goto st0;
st238:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof238;
case 238:
	if ( (*( state.p)) == 111 )
		goto st239;
	goto st0;
st239:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof239;
case 239:
	if ( (*( state.p)) == 119 )
		goto st240;
	goto st0;
st240:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof240;
case 240:
	switch( (*( state.p)) ) {
		case 13: goto tr344;
		case 32: goto tr344;
		case 59: goto tr345;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr344;
	goto st0;
tr284:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st241;
tr349:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st241;
st241:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof241;
case 241:
#line 3811 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st204;
		case 99: goto st211;
		case 103: goto st215;
		case 109: goto st220;
		case 114: goto st227;
		case 119: goto st230;
		case 121: goto st235;
	}
	goto st0;
st242:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof242;
case 242:
	if ( (*( state.p)) == 105 )
		goto st243;
	goto st0;
st243:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof243;
case 243:
	if ( (*( state.p)) == 109 )
		goto st244;
	goto st0;
st244:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof244;
case 244:
	switch( (*( state.p)) ) {
		case 13: goto tr348;
		case 32: goto tr348;
		case 95: goto tr349;
		case 98: goto tr350;
		case 99: goto tr351;
		case 103: goto tr352;
		case 109: goto tr353;
		case 114: goto tr354;
		case 119: goto tr355;
		case 121: goto tr356;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr348;
	goto st0;
st245:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof245;
case 245:
	if ( (*( state.p)) == 111 )
		goto st246;
	goto st0;
st246:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof246;
case 246:
	if ( (*( state.p)) == 110 )
		goto st247;
	goto st0;
st247:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof247;
case 247:
	if ( (*( state.p)) == 101 )
		goto st208;
	goto st0;
st248:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof248;
case 248:
	switch( (*( state.p)) ) {
		case 13: goto tr359;
		case 32: goto tr359;
		case 59: goto tr360;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr359;
	goto st0;
st249:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof249;
case 249:
	if ( (*( state.p)) == 97 )
		goto st250;
	goto st0;
st250:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof250;
case 250:
	if ( (*( state.p)) == 110 )
		goto st251;
	goto st0;
st251:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof251;
case 251:
	if ( (*( state.p)) == 100 )
		goto st252;
	goto st0;
st252:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof252;
case 252:
	if ( (*( state.p)) == 111 )
		goto st253;
	goto st0;
st253:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof253;
case 253:
	if ( (*( state.p)) == 109 )
		goto st254;
	goto st0;
st254:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof254;
case 254:
	switch( (*( state.p)) ) {
		case 13: goto tr366;
		case 32: goto tr366;
		case 59: goto tr367;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr366;
	goto st0;
st255:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof255;
case 255:
	if ( (*( state.p)) == 101 )
		goto st256;
	goto st0;
st256:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof256;
case 256:
	if ( (*( state.p)) == 101 )
		goto st257;
	goto st0;
st257:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof257;
case 257:
	if ( (*( state.p)) == 107 )
		goto st258;
	goto st0;
st258:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof258;
case 258:
	if ( (*( state.p)) == 95 )
		goto st259;
	goto st0;
st259:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof259;
case 259:
	if ( (*( state.p)) == 112 )
		goto st260;
	goto st0;
st260:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof260;
case 260:
	if ( (*( state.p)) == 108 )
		goto st261;
	goto st0;
st261:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof261;
case 261:
	if ( (*( state.p)) == 97 )
		goto st262;
	goto st0;
st262:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof262;
case 262:
	if ( (*( state.p)) == 121 )
		goto st263;
	goto st0;
st263:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof263;
case 263:
	if ( (*( state.p)) == 101 )
		goto st264;
	goto st0;
st264:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof264;
case 264:
	if ( (*( state.p)) == 114 )
		goto st265;
	goto st0;
st265:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof265;
case 265:
	switch( (*( state.p)) ) {
		case 13: goto tr378;
		case 32: goto tr378;
		case 59: goto tr379;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr378;
	goto st0;
st266:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof266;
case 266:
	if ( (*( state.p)) == 116 )
		goto st267;
	goto st0;
st267:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof267;
case 267:
	if ( (*( state.p)) == 97 )
		goto st268;
	goto st0;
st268:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof268;
case 268:
	if ( (*( state.p)) == 99 )
		goto st269;
	goto st0;
st269:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof269;
case 269:
	if ( (*( state.p)) == 107 )
		goto st270;
	goto st0;
st270:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof270;
case 270:
	switch( (*( state.p)) ) {
		case 13: goto st271;
		case 32: goto st271;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st271;
	goto st0;
st271:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof271;
case 271:
	switch( (*( state.p)) ) {
		case 13: goto st271;
		case 32: goto st271;
		case 45: goto tr385;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr386;
	} else if ( (*( state.p)) >= 9 )
		goto st271;
	goto st0;
tr385:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st272;
st272:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof272;
case 272:
#line 4085 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr387;
	goto st0;
tr386:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st273;
tr387:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st273;
st273:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof273;
case 273:
#line 4109 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr388;
		case 32: goto tr388;
		case 46: goto tr389;
		case 59: goto tr390;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr387;
	} else if ( (*( state.p)) >= 9 )
		goto tr388;
	goto st0;
tr389:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st274;
st274:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof274;
case 274:
#line 4132 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr391;
	goto st0;
tr391:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st275;
st275:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof275;
case 275:
#line 4146 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr388;
		case 32: goto tr388;
		case 59: goto tr390;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr391;
	} else if ( (*( state.p)) >= 9 )
		goto tr388;
	goto st0;
st276:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof276;
case 276:
	switch( (*( state.p)) ) {
		case 13: goto st276;
		case 32: goto st276;
		case 97: goto st277;
		case 99: goto st287;
		case 100: goto st294;
		case 104: goto st312;
		case 110: goto st321;
		case 115: goto st328;
		case 117: goto st404;
		case 125: goto st410;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st276;
	goto st0;
st277:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof277;
case 277:
	if ( (*( state.p)) == 116 )
		goto st278;
	goto st0;
st278:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof278;
case 278:
	if ( (*( state.p)) == 116 )
		goto st279;
	goto st0;
st279:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof279;
case 279:
	if ( (*( state.p)) == 97 )
		goto st280;
	goto st0;
st280:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof280;
case 280:
	if ( (*( state.p)) == 99 )
		goto st281;
	goto st0;
st281:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof281;
case 281:
	if ( (*( state.p)) == 107 )
		goto st282;
	goto st0;
st282:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof282;
case 282:
	switch( (*( state.p)) ) {
		case 13: goto st283;
		case 32: goto st283;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st283;
	goto st0;
st283:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof283;
case 283:
	switch( (*( state.p)) ) {
		case 13: goto st283;
		case 32: goto st283;
		case 45: goto tr407;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr408;
	} else if ( (*( state.p)) >= 9 )
		goto st283;
	goto st0;
tr407:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st284;
st284:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof284;
case 284:
#line 4252 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr409;
	goto st0;
tr408:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st285;
tr409:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st285;
st285:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof285;
case 285:
#line 4276 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr410;
		case 32: goto tr410;
		case 46: goto tr411;
		case 59: goto tr412;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr409;
	} else if ( (*( state.p)) >= 9 )
		goto tr410;
	goto st0;
tr410:
#line 247 "configparser.rl"
	{ des.attack = ::atof(state.match.c_str()); }
	goto st286;
tr421:
#line 242 "configparser.rl"
	{ des.count = ::atoi(state.match.c_str()); }
	goto st286;
tr435:
#line 248 "configparser.rl"
	{ des.defense = ::atof(state.match.c_str()); }
	goto st286;
tr446:
#line 246 "configparser.rl"
	{ des.descr = state.match; }
	goto st286;
tr455:
#line 250 "configparser.rl"
	{ des.heal = ::atof(state.match.c_str()); }
	goto st286;
tr467:
#line 243 "configparser.rl"
	{ des.name = state.match; }
	goto st286;
tr511:
#line 244 "configparser.rl"
	{ des.skin = skin; }
	goto st286;
tr514:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 244 "configparser.rl"
	{ des.skin = skin; }
	goto st286;
tr519:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 244 "configparser.rl"
	{ des.skin = skin; }
	goto st286;
tr525:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 244 "configparser.rl"
	{ des.skin = skin; }
	goto st286;
tr533:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 244 "configparser.rl"
	{ des.skin = skin; }
	goto st286;
tr537:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 244 "configparser.rl"
	{ des.skin = skin; }
	goto st286;
tr543:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 244 "configparser.rl"
	{ des.skin = skin; }
	goto st286;
tr550:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 244 "configparser.rl"
	{ des.skin = skin; }
	goto st286;
tr572:
#line 245 "configparser.rl"
	{ des.slot = state.match; }
	goto st286;
tr584:
#line 249 "configparser.rl"
	{ des.stackrange = ::atoi(state.match.c_str()); }
	goto st286;
tr592:
#line 251 "configparser.rl"
	{ des.usable = true; }
	goto st286;
tr594:
#line 257 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st286;
st286:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof286;
case 286:
#line 4379 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st286;
		case 32: goto st286;
		case 59: goto st418;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st286;
	goto st0;
tr412:
#line 247 "configparser.rl"
	{ des.attack = ::atof(state.match.c_str()); }
	goto st418;
tr423:
#line 242 "configparser.rl"
	{ des.count = ::atoi(state.match.c_str()); }
	goto st418;
tr437:
#line 248 "configparser.rl"
	{ des.defense = ::atof(state.match.c_str()); }
	goto st418;
tr447:
#line 246 "configparser.rl"
	{ des.descr = state.match; }
	goto st418;
tr457:
#line 250 "configparser.rl"
	{ des.heal = ::atof(state.match.c_str()); }
	goto st418;
tr468:
#line 243 "configparser.rl"
	{ des.name = state.match; }
	goto st418;
tr512:
#line 244 "configparser.rl"
	{ des.skin = skin; }
	goto st418;
tr515:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 244 "configparser.rl"
	{ des.skin = skin; }
	goto st418;
tr520:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 244 "configparser.rl"
	{ des.skin = skin; }
	goto st418;
tr526:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 244 "configparser.rl"
	{ des.skin = skin; }
	goto st418;
tr534:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 244 "configparser.rl"
	{ des.skin = skin; }
	goto st418;
tr538:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 244 "configparser.rl"
	{ des.skin = skin; }
	goto st418;
tr544:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 244 "configparser.rl"
	{ des.skin = skin; }
	goto st418;
tr551:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 244 "configparser.rl"
	{ des.skin = skin; }
	goto st418;
tr573:
#line 245 "configparser.rl"
	{ des.slot = state.match; }
	goto st418;
tr586:
#line 249 "configparser.rl"
	{ des.stackrange = ::atoi(state.match.c_str()); }
	goto st418;
tr593:
#line 251 "configparser.rl"
	{ des.usable = true; }
	goto st418;
tr595:
#line 257 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st418;
st418:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof418;
case 418:
#line 4478 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st276;
		case 32: goto st276;
		case 97: goto st277;
		case 99: goto st287;
		case 100: goto st294;
		case 104: goto st312;
		case 110: goto st321;
		case 115: goto st328;
		case 117: goto st404;
		case 125: goto st410;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st276;
	goto st0;
st287:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof287;
case 287:
	if ( (*( state.p)) == 111 )
		goto st288;
	goto st0;
st288:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof288;
case 288:
	if ( (*( state.p)) == 117 )
		goto st289;
	goto st0;
st289:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof289;
case 289:
	if ( (*( state.p)) == 110 )
		goto st290;
	goto st0;
st290:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof290;
case 290:
	if ( (*( state.p)) == 116 )
		goto st291;
	goto st0;
st291:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof291;
case 291:
	switch( (*( state.p)) ) {
		case 13: goto st292;
		case 32: goto st292;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st292;
	goto st0;
st292:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof292;
case 292:
	switch( (*( state.p)) ) {
		case 13: goto st292;
		case 32: goto st292;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr420;
	} else if ( (*( state.p)) >= 9 )
		goto st292;
	goto st0;
tr420:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st293;
tr422:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st293;
st293:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof293;
case 293:
#line 4567 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr421;
		case 32: goto tr421;
		case 59: goto tr423;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr422;
	} else if ( (*( state.p)) >= 9 )
		goto tr421;
	goto st0;
st294:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof294;
case 294:
	if ( (*( state.p)) == 101 )
		goto st295;
	goto st0;
st295:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof295;
case 295:
	switch( (*( state.p)) ) {
		case 102: goto st296;
		case 115: goto st306;
	}
	goto st0;
st296:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof296;
case 296:
	if ( (*( state.p)) == 101 )
		goto st297;
	goto st0;
st297:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof297;
case 297:
	if ( (*( state.p)) == 110 )
		goto st298;
	goto st0;
st298:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof298;
case 298:
	if ( (*( state.p)) == 115 )
		goto st299;
	goto st0;
st299:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof299;
case 299:
	if ( (*( state.p)) == 101 )
		goto st300;
	goto st0;
st300:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof300;
case 300:
	switch( (*( state.p)) ) {
		case 13: goto st301;
		case 32: goto st301;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st301;
	goto st0;
st301:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof301;
case 301:
	switch( (*( state.p)) ) {
		case 13: goto st301;
		case 32: goto st301;
		case 45: goto tr432;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr433;
	} else if ( (*( state.p)) >= 9 )
		goto st301;
	goto st0;
tr432:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st302;
st302:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof302;
case 302:
#line 4663 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr434;
	goto st0;
tr433:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st303;
tr434:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st303;
st303:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof303;
case 303:
#line 4687 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr435;
		case 32: goto tr435;
		case 46: goto tr436;
		case 59: goto tr437;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr434;
	} else if ( (*( state.p)) >= 9 )
		goto tr435;
	goto st0;
tr436:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st304;
st304:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof304;
case 304:
#line 4710 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr438;
	goto st0;
tr438:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st305;
st305:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof305;
case 305:
#line 4724 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr435;
		case 32: goto tr435;
		case 59: goto tr437;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr438;
	} else if ( (*( state.p)) >= 9 )
		goto tr435;
	goto st0;
st306:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof306;
case 306:
	if ( (*( state.p)) == 99 )
		goto st307;
	goto st0;
st307:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof307;
case 307:
	if ( (*( state.p)) == 114 )
		goto st308;
	goto st0;
st308:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof308;
case 308:
	switch( (*( state.p)) ) {
		case 13: goto st309;
		case 32: goto st309;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st309;
	goto st0;
st309:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof309;
case 309:
	switch( (*( state.p)) ) {
		case 13: goto st309;
		case 32: goto st309;
		case 34: goto tr442;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st309;
	goto st0;
tr443:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st310;
tr442:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st310;
tr445:
#line 142 "configparser.rl"
	{{ state.stack[ state.top++] = 310; goto st25;}}
	goto st310;
st310:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof310;
case 310:
#line 4793 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st311;
		case 92: goto tr445;
	}
	goto tr443;
st311:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof311;
case 311:
	switch( (*( state.p)) ) {
		case 13: goto tr446;
		case 32: goto tr446;
		case 59: goto tr447;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr446;
	goto st0;
st312:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof312;
case 312:
	if ( (*( state.p)) == 101 )
		goto st313;
	goto st0;
st313:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof313;
case 313:
	if ( (*( state.p)) == 97 )
		goto st314;
	goto st0;
st314:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof314;
case 314:
	if ( (*( state.p)) == 108 )
		goto st315;
	goto st0;
st315:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof315;
case 315:
	switch( (*( state.p)) ) {
		case 13: goto st316;
		case 32: goto st316;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st316;
	goto st0;
st316:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof316;
case 316:
	switch( (*( state.p)) ) {
		case 13: goto st316;
		case 32: goto st316;
		case 45: goto tr452;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr453;
	} else if ( (*( state.p)) >= 9 )
		goto st316;
	goto st0;
tr452:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st317;
st317:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof317;
case 317:
#line 4872 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr454;
	goto st0;
tr453:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st318;
tr454:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st318;
st318:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof318;
case 318:
#line 4896 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr455;
		case 32: goto tr455;
		case 46: goto tr456;
		case 59: goto tr457;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr454;
	} else if ( (*( state.p)) >= 9 )
		goto tr455;
	goto st0;
tr456:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st319;
st319:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof319;
case 319:
#line 4919 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr458;
	goto st0;
tr458:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st320;
st320:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof320;
case 320:
#line 4933 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr455;
		case 32: goto tr455;
		case 59: goto tr457;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr458;
	} else if ( (*( state.p)) >= 9 )
		goto tr455;
	goto st0;
st321:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof321;
case 321:
	if ( (*( state.p)) == 97 )
		goto st322;
	goto st0;
st322:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof322;
case 322:
	if ( (*( state.p)) == 109 )
		goto st323;
	goto st0;
st323:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof323;
case 323:
	if ( (*( state.p)) == 101 )
		goto st324;
	goto st0;
st324:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof324;
case 324:
	switch( (*( state.p)) ) {
		case 13: goto st325;
		case 32: goto st325;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st325;
	goto st0;
st325:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof325;
case 325:
	switch( (*( state.p)) ) {
		case 13: goto st325;
		case 32: goto st325;
		case 34: goto tr463;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st325;
	goto st0;
tr464:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st326;
tr463:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st326;
tr466:
#line 142 "configparser.rl"
	{{ state.stack[ state.top++] = 326; goto st25;}}
	goto st326;
st326:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof326;
case 326:
#line 5009 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st327;
		case 92: goto tr466;
	}
	goto tr464;
st327:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof327;
case 327:
	switch( (*( state.p)) ) {
		case 13: goto tr467;
		case 32: goto tr467;
		case 59: goto tr468;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr467;
	goto st0;
st328:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof328;
case 328:
	switch( (*( state.p)) ) {
		case 107: goto st329;
		case 108: goto st387;
		case 116: goto st393;
	}
	goto st0;
st329:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof329;
case 329:
	if ( (*( state.p)) == 105 )
		goto st330;
	goto st0;
st330:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof330;
case 330:
	if ( (*( state.p)) == 110 )
		goto st331;
	goto st0;
st331:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof331;
case 331:
	switch( (*( state.p)) ) {
		case 13: goto st332;
		case 32: goto st332;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st332;
	goto st0;
st332:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof332;
case 332:
	switch( (*( state.p)) ) {
		case 13: goto st332;
		case 32: goto st332;
		case 34: goto tr475;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st332;
	goto st0;
tr476:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st333;
tr475:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st333;
tr478:
#line 142 "configparser.rl"
	{{ state.stack[ state.top++] = 333; goto st25;}}
	goto st333;
st333:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof333;
case 333:
#line 5094 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st334;
		case 92: goto tr478;
	}
	goto tr476;
st334:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof334;
case 334:
	switch( (*( state.p)) ) {
		case 13: goto tr479;
		case 32: goto tr479;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr479;
	goto st0;
tr479:
#line 164 "configparser.rl"
	{ skin.text = state.match; }
	goto st335;
st335:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof335;
case 335:
#line 5119 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st335;
		case 32: goto st335;
		case 98: goto st336;
		case 100: goto st381;
		case 110: goto st384;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st335;
	goto st0;
st336:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof336;
case 336:
	if ( (*( state.p)) == 114 )
		goto st337;
	goto st0;
st337:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof337;
case 337:
	if ( (*( state.p)) == 105 )
		goto st338;
	goto st0;
st338:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof338;
case 338:
	if ( (*( state.p)) == 103 )
		goto st339;
	goto st0;
st339:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof339;
case 339:
	if ( (*( state.p)) == 104 )
		goto st340;
	goto st0;
st340:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof340;
case 340:
	if ( (*( state.p)) == 116 )
		goto st341;
	goto st0;
st341:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof341;
case 341:
	switch( (*( state.p)) ) {
		case 13: goto tr489;
		case 32: goto tr489;
		case 95: goto tr490;
		case 98: goto tr491;
		case 99: goto tr492;
		case 103: goto tr493;
		case 109: goto tr494;
		case 114: goto tr495;
		case 119: goto tr496;
		case 121: goto tr497;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr489;
	goto st0;
tr489:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st342;
tr554:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st342;
st342:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof342;
case 342:
#line 5196 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st342;
		case 32: goto st342;
		case 98: goto st343;
		case 99: goto st350;
		case 103: goto st354;
		case 109: goto st359;
		case 114: goto st366;
		case 119: goto st369;
		case 121: goto st374;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st342;
	goto st0;
tr491:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st343;
tr556:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st343;
st343:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof343;
case 343:
#line 5223 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st344;
	goto st0;
st344:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof344;
case 344:
	switch( (*( state.p)) ) {
		case 97: goto st345;
		case 117: goto st348;
	}
	goto st0;
st345:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof345;
case 345:
	if ( (*( state.p)) == 99 )
		goto st346;
	goto st0;
st346:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof346;
case 346:
	if ( (*( state.p)) == 107 )
		goto st347;
	goto st0;
st347:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof347;
case 347:
	switch( (*( state.p)) ) {
		case 13: goto tr511;
		case 32: goto tr511;
		case 59: goto tr512;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr511;
	goto st0;
st348:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof348;
case 348:
	if ( (*( state.p)) == 101 )
		goto st349;
	goto st0;
st349:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof349;
case 349:
	switch( (*( state.p)) ) {
		case 13: goto tr514;
		case 32: goto tr514;
		case 59: goto tr515;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr514;
	goto st0;
tr492:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st350;
tr557:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st350;
st350:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof350;
case 350:
#line 5293 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st351;
	goto st0;
st351:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof351;
case 351:
	if ( (*( state.p)) == 97 )
		goto st352;
	goto st0;
st352:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof352;
case 352:
	if ( (*( state.p)) == 110 )
		goto st353;
	goto st0;
st353:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof353;
case 353:
	switch( (*( state.p)) ) {
		case 13: goto tr519;
		case 32: goto tr519;
		case 59: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr519;
	goto st0;
tr493:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st354;
tr558:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st354;
st354:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof354;
case 354:
#line 5335 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st355;
	goto st0;
st355:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof355;
case 355:
	if ( (*( state.p)) == 101 )
		goto st356;
	goto st0;
st356:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof356;
case 356:
	if ( (*( state.p)) == 101 )
		goto st357;
	goto st0;
st357:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof357;
case 357:
	if ( (*( state.p)) == 110 )
		goto st358;
	goto st0;
st358:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof358;
case 358:
	switch( (*( state.p)) ) {
		case 13: goto tr525;
		case 32: goto tr525;
		case 59: goto tr526;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr525;
	goto st0;
tr494:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st359;
tr559:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st359;
st359:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof359;
case 359:
#line 5384 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st360;
	goto st0;
st360:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof360;
case 360:
	if ( (*( state.p)) == 103 )
		goto st361;
	goto st0;
st361:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof361;
case 361:
	if ( (*( state.p)) == 101 )
		goto st362;
	goto st0;
st362:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof362;
case 362:
	if ( (*( state.p)) == 110 )
		goto st363;
	goto st0;
st363:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof363;
case 363:
	if ( (*( state.p)) == 116 )
		goto st364;
	goto st0;
st364:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof364;
case 364:
	if ( (*( state.p)) == 97 )
		goto st365;
	goto st0;
st365:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof365;
case 365:
	switch( (*( state.p)) ) {
		case 13: goto tr533;
		case 32: goto tr533;
		case 59: goto tr534;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr533;
	goto st0;
tr495:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st366;
tr560:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st366;
st366:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof366;
case 366:
#line 5447 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st367;
	goto st0;
st367:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof367;
case 367:
	if ( (*( state.p)) == 100 )
		goto st368;
	goto st0;
st368:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof368;
case 368:
	switch( (*( state.p)) ) {
		case 13: goto tr537;
		case 32: goto tr537;
		case 59: goto tr538;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr537;
	goto st0;
tr496:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st369;
tr561:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st369;
st369:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof369;
case 369:
#line 5482 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st370;
	goto st0;
st370:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof370;
case 370:
	if ( (*( state.p)) == 105 )
		goto st371;
	goto st0;
st371:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof371;
case 371:
	if ( (*( state.p)) == 116 )
		goto st372;
	goto st0;
st372:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof372;
case 372:
	if ( (*( state.p)) == 101 )
		goto st373;
	goto st0;
st373:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof373;
case 373:
	switch( (*( state.p)) ) {
		case 13: goto tr543;
		case 32: goto tr543;
		case 59: goto tr544;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr543;
	goto st0;
tr497:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st374;
tr562:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st374;
st374:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof374;
case 374:
#line 5531 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st375;
	goto st0;
st375:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof375;
case 375:
	if ( (*( state.p)) == 108 )
		goto st376;
	goto st0;
st376:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof376;
case 376:
	if ( (*( state.p)) == 108 )
		goto st377;
	goto st0;
st377:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof377;
case 377:
	if ( (*( state.p)) == 111 )
		goto st378;
	goto st0;
st378:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof378;
case 378:
	if ( (*( state.p)) == 119 )
		goto st379;
	goto st0;
st379:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof379;
case 379:
	switch( (*( state.p)) ) {
		case 13: goto tr550;
		case 32: goto tr550;
		case 59: goto tr551;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr550;
	goto st0;
tr490:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st380;
tr555:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st380;
st380:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof380;
case 380:
#line 5587 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st343;
		case 99: goto st350;
		case 103: goto st354;
		case 109: goto st359;
		case 114: goto st366;
		case 119: goto st369;
		case 121: goto st374;
	}
	goto st0;
st381:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof381;
case 381:
	if ( (*( state.p)) == 105 )
		goto st382;
	goto st0;
st382:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof382;
case 382:
	if ( (*( state.p)) == 109 )
		goto st383;
	goto st0;
st383:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof383;
case 383:
	switch( (*( state.p)) ) {
		case 13: goto tr554;
		case 32: goto tr554;
		case 95: goto tr555;
		case 98: goto tr556;
		case 99: goto tr557;
		case 103: goto tr558;
		case 109: goto tr559;
		case 114: goto tr560;
		case 119: goto tr561;
		case 121: goto tr562;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr554;
	goto st0;
st384:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof384;
case 384:
	if ( (*( state.p)) == 111 )
		goto st385;
	goto st0;
st385:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof385;
case 385:
	if ( (*( state.p)) == 110 )
		goto st386;
	goto st0;
st386:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof386;
case 386:
	if ( (*( state.p)) == 101 )
		goto st347;
	goto st0;
st387:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof387;
case 387:
	if ( (*( state.p)) == 111 )
		goto st388;
	goto st0;
st388:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof388;
case 388:
	if ( (*( state.p)) == 116 )
		goto st389;
	goto st0;
st389:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof389;
case 389:
	switch( (*( state.p)) ) {
		case 13: goto st390;
		case 32: goto st390;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st390;
	goto st0;
st390:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof390;
case 390:
	switch( (*( state.p)) ) {
		case 13: goto st390;
		case 32: goto st390;
		case 34: goto tr568;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st390;
	goto st0;
tr569:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st391;
tr568:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st391;
tr571:
#line 142 "configparser.rl"
	{{ state.stack[ state.top++] = 391; goto st25;}}
	goto st391;
st391:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof391;
case 391:
#line 5709 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st392;
		case 92: goto tr571;
	}
	goto tr569;
st392:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof392;
case 392:
	switch( (*( state.p)) ) {
		case 13: goto tr572;
		case 32: goto tr572;
		case 59: goto tr573;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr572;
	goto st0;
st393:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof393;
case 393:
	if ( (*( state.p)) == 97 )
		goto st394;
	goto st0;
st394:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof394;
case 394:
	if ( (*( state.p)) == 99 )
		goto st395;
	goto st0;
st395:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof395;
case 395:
	if ( (*( state.p)) == 107 )
		goto st396;
	goto st0;
st396:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof396;
case 396:
	if ( (*( state.p)) == 114 )
		goto st397;
	goto st0;
st397:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof397;
case 397:
	if ( (*( state.p)) == 97 )
		goto st398;
	goto st0;
st398:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof398;
case 398:
	if ( (*( state.p)) == 110 )
		goto st399;
	goto st0;
st399:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof399;
case 399:
	if ( (*( state.p)) == 103 )
		goto st400;
	goto st0;
st400:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof400;
case 400:
	if ( (*( state.p)) == 101 )
		goto st401;
	goto st0;
st401:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof401;
case 401:
	switch( (*( state.p)) ) {
		case 13: goto st402;
		case 32: goto st402;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st402;
	goto st0;
st402:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof402;
case 402:
	switch( (*( state.p)) ) {
		case 13: goto st402;
		case 32: goto st402;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr583;
	} else if ( (*( state.p)) >= 9 )
		goto st402;
	goto st0;
tr583:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st403;
tr585:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st403;
st403:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof403;
case 403:
#line 5828 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr584;
		case 32: goto tr584;
		case 59: goto tr586;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr585;
	} else if ( (*( state.p)) >= 9 )
		goto tr584;
	goto st0;
st404:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof404;
case 404:
	if ( (*( state.p)) == 115 )
		goto st405;
	goto st0;
st405:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof405;
case 405:
	if ( (*( state.p)) == 97 )
		goto st406;
	goto st0;
st406:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof406;
case 406:
	if ( (*( state.p)) == 98 )
		goto st407;
	goto st0;
st407:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof407;
case 407:
	if ( (*( state.p)) == 108 )
		goto st408;
	goto st0;
st408:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof408;
case 408:
	if ( (*( state.p)) == 101 )
		goto st409;
	goto st0;
st409:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof409;
case 409:
	switch( (*( state.p)) ) {
		case 13: goto tr592;
		case 32: goto tr592;
		case 59: goto tr593;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr592;
	goto st0;
st410:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof410;
case 410:
	switch( (*( state.p)) ) {
		case 13: goto tr594;
		case 32: goto tr594;
		case 59: goto tr595;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr594;
	goto st0;
tr411:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st411;
st411:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof411;
case 411:
#line 5909 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr596;
	goto st0;
tr596:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st412;
st412:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof412;
case 412:
#line 5923 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr410;
		case 32: goto tr410;
		case 59: goto tr412;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr596;
	} else if ( (*( state.p)) >= 9 )
		goto tr410;
	goto st0;
	}
	_test_eof1:  state.cs = 1; goto _test_eof; 
	_test_eof2:  state.cs = 2; goto _test_eof; 
	_test_eof3:  state.cs = 3; goto _test_eof; 
	_test_eof4:  state.cs = 4; goto _test_eof; 
	_test_eof5:  state.cs = 5; goto _test_eof; 
	_test_eof6:  state.cs = 6; goto _test_eof; 
	_test_eof7:  state.cs = 7; goto _test_eof; 
	_test_eof8:  state.cs = 8; goto _test_eof; 
	_test_eof9:  state.cs = 9; goto _test_eof; 
	_test_eof10:  state.cs = 10; goto _test_eof; 
	_test_eof11:  state.cs = 11; goto _test_eof; 
	_test_eof12:  state.cs = 12; goto _test_eof; 
	_test_eof413:  state.cs = 413; goto _test_eof; 
	_test_eof414:  state.cs = 414; goto _test_eof; 
	_test_eof13:  state.cs = 13; goto _test_eof; 
	_test_eof14:  state.cs = 14; goto _test_eof; 
	_test_eof15:  state.cs = 15; goto _test_eof; 
	_test_eof16:  state.cs = 16; goto _test_eof; 
	_test_eof17:  state.cs = 17; goto _test_eof; 
	_test_eof18:  state.cs = 18; goto _test_eof; 
	_test_eof19:  state.cs = 19; goto _test_eof; 
	_test_eof20:  state.cs = 20; goto _test_eof; 
	_test_eof21:  state.cs = 21; goto _test_eof; 
	_test_eof22:  state.cs = 22; goto _test_eof; 
	_test_eof23:  state.cs = 23; goto _test_eof; 
	_test_eof24:  state.cs = 24; goto _test_eof; 
	_test_eof415:  state.cs = 415; goto _test_eof; 
	_test_eof25:  state.cs = 25; goto _test_eof; 
	_test_eof416:  state.cs = 416; goto _test_eof; 
	_test_eof26:  state.cs = 26; goto _test_eof; 
	_test_eof27:  state.cs = 27; goto _test_eof; 
	_test_eof28:  state.cs = 28; goto _test_eof; 
	_test_eof29:  state.cs = 29; goto _test_eof; 
	_test_eof30:  state.cs = 30; goto _test_eof; 
	_test_eof31:  state.cs = 31; goto _test_eof; 
	_test_eof32:  state.cs = 32; goto _test_eof; 
	_test_eof33:  state.cs = 33; goto _test_eof; 
	_test_eof34:  state.cs = 34; goto _test_eof; 
	_test_eof417:  state.cs = 417; goto _test_eof; 
	_test_eof35:  state.cs = 35; goto _test_eof; 
	_test_eof36:  state.cs = 36; goto _test_eof; 
	_test_eof37:  state.cs = 37; goto _test_eof; 
	_test_eof38:  state.cs = 38; goto _test_eof; 
	_test_eof39:  state.cs = 39; goto _test_eof; 
	_test_eof40:  state.cs = 40; goto _test_eof; 
	_test_eof41:  state.cs = 41; goto _test_eof; 
	_test_eof42:  state.cs = 42; goto _test_eof; 
	_test_eof43:  state.cs = 43; goto _test_eof; 
	_test_eof44:  state.cs = 44; goto _test_eof; 
	_test_eof45:  state.cs = 45; goto _test_eof; 
	_test_eof46:  state.cs = 46; goto _test_eof; 
	_test_eof47:  state.cs = 47; goto _test_eof; 
	_test_eof48:  state.cs = 48; goto _test_eof; 
	_test_eof49:  state.cs = 49; goto _test_eof; 
	_test_eof50:  state.cs = 50; goto _test_eof; 
	_test_eof51:  state.cs = 51; goto _test_eof; 
	_test_eof52:  state.cs = 52; goto _test_eof; 
	_test_eof53:  state.cs = 53; goto _test_eof; 
	_test_eof54:  state.cs = 54; goto _test_eof; 
	_test_eof55:  state.cs = 55; goto _test_eof; 
	_test_eof56:  state.cs = 56; goto _test_eof; 
	_test_eof57:  state.cs = 57; goto _test_eof; 
	_test_eof58:  state.cs = 58; goto _test_eof; 
	_test_eof59:  state.cs = 59; goto _test_eof; 
	_test_eof60:  state.cs = 60; goto _test_eof; 
	_test_eof61:  state.cs = 61; goto _test_eof; 
	_test_eof62:  state.cs = 62; goto _test_eof; 
	_test_eof63:  state.cs = 63; goto _test_eof; 
	_test_eof64:  state.cs = 64; goto _test_eof; 
	_test_eof65:  state.cs = 65; goto _test_eof; 
	_test_eof66:  state.cs = 66; goto _test_eof; 
	_test_eof67:  state.cs = 67; goto _test_eof; 
	_test_eof68:  state.cs = 68; goto _test_eof; 
	_test_eof69:  state.cs = 69; goto _test_eof; 
	_test_eof70:  state.cs = 70; goto _test_eof; 
	_test_eof71:  state.cs = 71; goto _test_eof; 
	_test_eof72:  state.cs = 72; goto _test_eof; 
	_test_eof73:  state.cs = 73; goto _test_eof; 
	_test_eof74:  state.cs = 74; goto _test_eof; 
	_test_eof75:  state.cs = 75; goto _test_eof; 
	_test_eof76:  state.cs = 76; goto _test_eof; 
	_test_eof77:  state.cs = 77; goto _test_eof; 
	_test_eof78:  state.cs = 78; goto _test_eof; 
	_test_eof79:  state.cs = 79; goto _test_eof; 
	_test_eof80:  state.cs = 80; goto _test_eof; 
	_test_eof81:  state.cs = 81; goto _test_eof; 
	_test_eof82:  state.cs = 82; goto _test_eof; 
	_test_eof83:  state.cs = 83; goto _test_eof; 
	_test_eof84:  state.cs = 84; goto _test_eof; 
	_test_eof85:  state.cs = 85; goto _test_eof; 
	_test_eof86:  state.cs = 86; goto _test_eof; 
	_test_eof87:  state.cs = 87; goto _test_eof; 
	_test_eof88:  state.cs = 88; goto _test_eof; 
	_test_eof89:  state.cs = 89; goto _test_eof; 
	_test_eof90:  state.cs = 90; goto _test_eof; 
	_test_eof91:  state.cs = 91; goto _test_eof; 
	_test_eof92:  state.cs = 92; goto _test_eof; 
	_test_eof93:  state.cs = 93; goto _test_eof; 
	_test_eof94:  state.cs = 94; goto _test_eof; 
	_test_eof95:  state.cs = 95; goto _test_eof; 
	_test_eof96:  state.cs = 96; goto _test_eof; 
	_test_eof97:  state.cs = 97; goto _test_eof; 
	_test_eof98:  state.cs = 98; goto _test_eof; 
	_test_eof99:  state.cs = 99; goto _test_eof; 
	_test_eof100:  state.cs = 100; goto _test_eof; 
	_test_eof101:  state.cs = 101; goto _test_eof; 
	_test_eof102:  state.cs = 102; goto _test_eof; 
	_test_eof103:  state.cs = 103; goto _test_eof; 
	_test_eof104:  state.cs = 104; goto _test_eof; 
	_test_eof105:  state.cs = 105; goto _test_eof; 
	_test_eof106:  state.cs = 106; goto _test_eof; 
	_test_eof107:  state.cs = 107; goto _test_eof; 
	_test_eof108:  state.cs = 108; goto _test_eof; 
	_test_eof109:  state.cs = 109; goto _test_eof; 
	_test_eof110:  state.cs = 110; goto _test_eof; 
	_test_eof111:  state.cs = 111; goto _test_eof; 
	_test_eof112:  state.cs = 112; goto _test_eof; 
	_test_eof113:  state.cs = 113; goto _test_eof; 
	_test_eof114:  state.cs = 114; goto _test_eof; 
	_test_eof115:  state.cs = 115; goto _test_eof; 
	_test_eof116:  state.cs = 116; goto _test_eof; 
	_test_eof117:  state.cs = 117; goto _test_eof; 
	_test_eof118:  state.cs = 118; goto _test_eof; 
	_test_eof119:  state.cs = 119; goto _test_eof; 
	_test_eof120:  state.cs = 120; goto _test_eof; 
	_test_eof121:  state.cs = 121; goto _test_eof; 
	_test_eof122:  state.cs = 122; goto _test_eof; 
	_test_eof123:  state.cs = 123; goto _test_eof; 
	_test_eof124:  state.cs = 124; goto _test_eof; 
	_test_eof125:  state.cs = 125; goto _test_eof; 
	_test_eof126:  state.cs = 126; goto _test_eof; 
	_test_eof127:  state.cs = 127; goto _test_eof; 
	_test_eof128:  state.cs = 128; goto _test_eof; 
	_test_eof129:  state.cs = 129; goto _test_eof; 
	_test_eof130:  state.cs = 130; goto _test_eof; 
	_test_eof131:  state.cs = 131; goto _test_eof; 
	_test_eof132:  state.cs = 132; goto _test_eof; 
	_test_eof133:  state.cs = 133; goto _test_eof; 
	_test_eof134:  state.cs = 134; goto _test_eof; 
	_test_eof135:  state.cs = 135; goto _test_eof; 
	_test_eof136:  state.cs = 136; goto _test_eof; 
	_test_eof137:  state.cs = 137; goto _test_eof; 
	_test_eof138:  state.cs = 138; goto _test_eof; 
	_test_eof139:  state.cs = 139; goto _test_eof; 
	_test_eof140:  state.cs = 140; goto _test_eof; 
	_test_eof141:  state.cs = 141; goto _test_eof; 
	_test_eof142:  state.cs = 142; goto _test_eof; 
	_test_eof143:  state.cs = 143; goto _test_eof; 
	_test_eof144:  state.cs = 144; goto _test_eof; 
	_test_eof145:  state.cs = 145; goto _test_eof; 
	_test_eof146:  state.cs = 146; goto _test_eof; 
	_test_eof147:  state.cs = 147; goto _test_eof; 
	_test_eof148:  state.cs = 148; goto _test_eof; 
	_test_eof149:  state.cs = 149; goto _test_eof; 
	_test_eof150:  state.cs = 150; goto _test_eof; 
	_test_eof151:  state.cs = 151; goto _test_eof; 
	_test_eof152:  state.cs = 152; goto _test_eof; 
	_test_eof153:  state.cs = 153; goto _test_eof; 
	_test_eof154:  state.cs = 154; goto _test_eof; 
	_test_eof155:  state.cs = 155; goto _test_eof; 
	_test_eof156:  state.cs = 156; goto _test_eof; 
	_test_eof157:  state.cs = 157; goto _test_eof; 
	_test_eof158:  state.cs = 158; goto _test_eof; 
	_test_eof159:  state.cs = 159; goto _test_eof; 
	_test_eof160:  state.cs = 160; goto _test_eof; 
	_test_eof161:  state.cs = 161; goto _test_eof; 
	_test_eof162:  state.cs = 162; goto _test_eof; 
	_test_eof163:  state.cs = 163; goto _test_eof; 
	_test_eof164:  state.cs = 164; goto _test_eof; 
	_test_eof165:  state.cs = 165; goto _test_eof; 
	_test_eof166:  state.cs = 166; goto _test_eof; 
	_test_eof167:  state.cs = 167; goto _test_eof; 
	_test_eof168:  state.cs = 168; goto _test_eof; 
	_test_eof169:  state.cs = 169; goto _test_eof; 
	_test_eof170:  state.cs = 170; goto _test_eof; 
	_test_eof171:  state.cs = 171; goto _test_eof; 
	_test_eof172:  state.cs = 172; goto _test_eof; 
	_test_eof173:  state.cs = 173; goto _test_eof; 
	_test_eof174:  state.cs = 174; goto _test_eof; 
	_test_eof175:  state.cs = 175; goto _test_eof; 
	_test_eof176:  state.cs = 176; goto _test_eof; 
	_test_eof177:  state.cs = 177; goto _test_eof; 
	_test_eof178:  state.cs = 178; goto _test_eof; 
	_test_eof179:  state.cs = 179; goto _test_eof; 
	_test_eof180:  state.cs = 180; goto _test_eof; 
	_test_eof181:  state.cs = 181; goto _test_eof; 
	_test_eof182:  state.cs = 182; goto _test_eof; 
	_test_eof183:  state.cs = 183; goto _test_eof; 
	_test_eof184:  state.cs = 184; goto _test_eof; 
	_test_eof185:  state.cs = 185; goto _test_eof; 
	_test_eof186:  state.cs = 186; goto _test_eof; 
	_test_eof187:  state.cs = 187; goto _test_eof; 
	_test_eof188:  state.cs = 188; goto _test_eof; 
	_test_eof189:  state.cs = 189; goto _test_eof; 
	_test_eof190:  state.cs = 190; goto _test_eof; 
	_test_eof191:  state.cs = 191; goto _test_eof; 
	_test_eof192:  state.cs = 192; goto _test_eof; 
	_test_eof193:  state.cs = 193; goto _test_eof; 
	_test_eof194:  state.cs = 194; goto _test_eof; 
	_test_eof195:  state.cs = 195; goto _test_eof; 
	_test_eof196:  state.cs = 196; goto _test_eof; 
	_test_eof197:  state.cs = 197; goto _test_eof; 
	_test_eof198:  state.cs = 198; goto _test_eof; 
	_test_eof199:  state.cs = 199; goto _test_eof; 
	_test_eof200:  state.cs = 200; goto _test_eof; 
	_test_eof201:  state.cs = 201; goto _test_eof; 
	_test_eof202:  state.cs = 202; goto _test_eof; 
	_test_eof203:  state.cs = 203; goto _test_eof; 
	_test_eof204:  state.cs = 204; goto _test_eof; 
	_test_eof205:  state.cs = 205; goto _test_eof; 
	_test_eof206:  state.cs = 206; goto _test_eof; 
	_test_eof207:  state.cs = 207; goto _test_eof; 
	_test_eof208:  state.cs = 208; goto _test_eof; 
	_test_eof209:  state.cs = 209; goto _test_eof; 
	_test_eof210:  state.cs = 210; goto _test_eof; 
	_test_eof211:  state.cs = 211; goto _test_eof; 
	_test_eof212:  state.cs = 212; goto _test_eof; 
	_test_eof213:  state.cs = 213; goto _test_eof; 
	_test_eof214:  state.cs = 214; goto _test_eof; 
	_test_eof215:  state.cs = 215; goto _test_eof; 
	_test_eof216:  state.cs = 216; goto _test_eof; 
	_test_eof217:  state.cs = 217; goto _test_eof; 
	_test_eof218:  state.cs = 218; goto _test_eof; 
	_test_eof219:  state.cs = 219; goto _test_eof; 
	_test_eof220:  state.cs = 220; goto _test_eof; 
	_test_eof221:  state.cs = 221; goto _test_eof; 
	_test_eof222:  state.cs = 222; goto _test_eof; 
	_test_eof223:  state.cs = 223; goto _test_eof; 
	_test_eof224:  state.cs = 224; goto _test_eof; 
	_test_eof225:  state.cs = 225; goto _test_eof; 
	_test_eof226:  state.cs = 226; goto _test_eof; 
	_test_eof227:  state.cs = 227; goto _test_eof; 
	_test_eof228:  state.cs = 228; goto _test_eof; 
	_test_eof229:  state.cs = 229; goto _test_eof; 
	_test_eof230:  state.cs = 230; goto _test_eof; 
	_test_eof231:  state.cs = 231; goto _test_eof; 
	_test_eof232:  state.cs = 232; goto _test_eof; 
	_test_eof233:  state.cs = 233; goto _test_eof; 
	_test_eof234:  state.cs = 234; goto _test_eof; 
	_test_eof235:  state.cs = 235; goto _test_eof; 
	_test_eof236:  state.cs = 236; goto _test_eof; 
	_test_eof237:  state.cs = 237; goto _test_eof; 
	_test_eof238:  state.cs = 238; goto _test_eof; 
	_test_eof239:  state.cs = 239; goto _test_eof; 
	_test_eof240:  state.cs = 240; goto _test_eof; 
	_test_eof241:  state.cs = 241; goto _test_eof; 
	_test_eof242:  state.cs = 242; goto _test_eof; 
	_test_eof243:  state.cs = 243; goto _test_eof; 
	_test_eof244:  state.cs = 244; goto _test_eof; 
	_test_eof245:  state.cs = 245; goto _test_eof; 
	_test_eof246:  state.cs = 246; goto _test_eof; 
	_test_eof247:  state.cs = 247; goto _test_eof; 
	_test_eof248:  state.cs = 248; goto _test_eof; 
	_test_eof249:  state.cs = 249; goto _test_eof; 
	_test_eof250:  state.cs = 250; goto _test_eof; 
	_test_eof251:  state.cs = 251; goto _test_eof; 
	_test_eof252:  state.cs = 252; goto _test_eof; 
	_test_eof253:  state.cs = 253; goto _test_eof; 
	_test_eof254:  state.cs = 254; goto _test_eof; 
	_test_eof255:  state.cs = 255; goto _test_eof; 
	_test_eof256:  state.cs = 256; goto _test_eof; 
	_test_eof257:  state.cs = 257; goto _test_eof; 
	_test_eof258:  state.cs = 258; goto _test_eof; 
	_test_eof259:  state.cs = 259; goto _test_eof; 
	_test_eof260:  state.cs = 260; goto _test_eof; 
	_test_eof261:  state.cs = 261; goto _test_eof; 
	_test_eof262:  state.cs = 262; goto _test_eof; 
	_test_eof263:  state.cs = 263; goto _test_eof; 
	_test_eof264:  state.cs = 264; goto _test_eof; 
	_test_eof265:  state.cs = 265; goto _test_eof; 
	_test_eof266:  state.cs = 266; goto _test_eof; 
	_test_eof267:  state.cs = 267; goto _test_eof; 
	_test_eof268:  state.cs = 268; goto _test_eof; 
	_test_eof269:  state.cs = 269; goto _test_eof; 
	_test_eof270:  state.cs = 270; goto _test_eof; 
	_test_eof271:  state.cs = 271; goto _test_eof; 
	_test_eof272:  state.cs = 272; goto _test_eof; 
	_test_eof273:  state.cs = 273; goto _test_eof; 
	_test_eof274:  state.cs = 274; goto _test_eof; 
	_test_eof275:  state.cs = 275; goto _test_eof; 
	_test_eof276:  state.cs = 276; goto _test_eof; 
	_test_eof277:  state.cs = 277; goto _test_eof; 
	_test_eof278:  state.cs = 278; goto _test_eof; 
	_test_eof279:  state.cs = 279; goto _test_eof; 
	_test_eof280:  state.cs = 280; goto _test_eof; 
	_test_eof281:  state.cs = 281; goto _test_eof; 
	_test_eof282:  state.cs = 282; goto _test_eof; 
	_test_eof283:  state.cs = 283; goto _test_eof; 
	_test_eof284:  state.cs = 284; goto _test_eof; 
	_test_eof285:  state.cs = 285; goto _test_eof; 
	_test_eof286:  state.cs = 286; goto _test_eof; 
	_test_eof418:  state.cs = 418; goto _test_eof; 
	_test_eof287:  state.cs = 287; goto _test_eof; 
	_test_eof288:  state.cs = 288; goto _test_eof; 
	_test_eof289:  state.cs = 289; goto _test_eof; 
	_test_eof290:  state.cs = 290; goto _test_eof; 
	_test_eof291:  state.cs = 291; goto _test_eof; 
	_test_eof292:  state.cs = 292; goto _test_eof; 
	_test_eof293:  state.cs = 293; goto _test_eof; 
	_test_eof294:  state.cs = 294; goto _test_eof; 
	_test_eof295:  state.cs = 295; goto _test_eof; 
	_test_eof296:  state.cs = 296; goto _test_eof; 
	_test_eof297:  state.cs = 297; goto _test_eof; 
	_test_eof298:  state.cs = 298; goto _test_eof; 
	_test_eof299:  state.cs = 299; goto _test_eof; 
	_test_eof300:  state.cs = 300; goto _test_eof; 
	_test_eof301:  state.cs = 301; goto _test_eof; 
	_test_eof302:  state.cs = 302; goto _test_eof; 
	_test_eof303:  state.cs = 303; goto _test_eof; 
	_test_eof304:  state.cs = 304; goto _test_eof; 
	_test_eof305:  state.cs = 305; goto _test_eof; 
	_test_eof306:  state.cs = 306; goto _test_eof; 
	_test_eof307:  state.cs = 307; goto _test_eof; 
	_test_eof308:  state.cs = 308; goto _test_eof; 
	_test_eof309:  state.cs = 309; goto _test_eof; 
	_test_eof310:  state.cs = 310; goto _test_eof; 
	_test_eof311:  state.cs = 311; goto _test_eof; 
	_test_eof312:  state.cs = 312; goto _test_eof; 
	_test_eof313:  state.cs = 313; goto _test_eof; 
	_test_eof314:  state.cs = 314; goto _test_eof; 
	_test_eof315:  state.cs = 315; goto _test_eof; 
	_test_eof316:  state.cs = 316; goto _test_eof; 
	_test_eof317:  state.cs = 317; goto _test_eof; 
	_test_eof318:  state.cs = 318; goto _test_eof; 
	_test_eof319:  state.cs = 319; goto _test_eof; 
	_test_eof320:  state.cs = 320; goto _test_eof; 
	_test_eof321:  state.cs = 321; goto _test_eof; 
	_test_eof322:  state.cs = 322; goto _test_eof; 
	_test_eof323:  state.cs = 323; goto _test_eof; 
	_test_eof324:  state.cs = 324; goto _test_eof; 
	_test_eof325:  state.cs = 325; goto _test_eof; 
	_test_eof326:  state.cs = 326; goto _test_eof; 
	_test_eof327:  state.cs = 327; goto _test_eof; 
	_test_eof328:  state.cs = 328; goto _test_eof; 
	_test_eof329:  state.cs = 329; goto _test_eof; 
	_test_eof330:  state.cs = 330; goto _test_eof; 
	_test_eof331:  state.cs = 331; goto _test_eof; 
	_test_eof332:  state.cs = 332; goto _test_eof; 
	_test_eof333:  state.cs = 333; goto _test_eof; 
	_test_eof334:  state.cs = 334; goto _test_eof; 
	_test_eof335:  state.cs = 335; goto _test_eof; 
	_test_eof336:  state.cs = 336; goto _test_eof; 
	_test_eof337:  state.cs = 337; goto _test_eof; 
	_test_eof338:  state.cs = 338; goto _test_eof; 
	_test_eof339:  state.cs = 339; goto _test_eof; 
	_test_eof340:  state.cs = 340; goto _test_eof; 
	_test_eof341:  state.cs = 341; goto _test_eof; 
	_test_eof342:  state.cs = 342; goto _test_eof; 
	_test_eof343:  state.cs = 343; goto _test_eof; 
	_test_eof344:  state.cs = 344; goto _test_eof; 
	_test_eof345:  state.cs = 345; goto _test_eof; 
	_test_eof346:  state.cs = 346; goto _test_eof; 
	_test_eof347:  state.cs = 347; goto _test_eof; 
	_test_eof348:  state.cs = 348; goto _test_eof; 
	_test_eof349:  state.cs = 349; goto _test_eof; 
	_test_eof350:  state.cs = 350; goto _test_eof; 
	_test_eof351:  state.cs = 351; goto _test_eof; 
	_test_eof352:  state.cs = 352; goto _test_eof; 
	_test_eof353:  state.cs = 353; goto _test_eof; 
	_test_eof354:  state.cs = 354; goto _test_eof; 
	_test_eof355:  state.cs = 355; goto _test_eof; 
	_test_eof356:  state.cs = 356; goto _test_eof; 
	_test_eof357:  state.cs = 357; goto _test_eof; 
	_test_eof358:  state.cs = 358; goto _test_eof; 
	_test_eof359:  state.cs = 359; goto _test_eof; 
	_test_eof360:  state.cs = 360; goto _test_eof; 
	_test_eof361:  state.cs = 361; goto _test_eof; 
	_test_eof362:  state.cs = 362; goto _test_eof; 
	_test_eof363:  state.cs = 363; goto _test_eof; 
	_test_eof364:  state.cs = 364; goto _test_eof; 
	_test_eof365:  state.cs = 365; goto _test_eof; 
	_test_eof366:  state.cs = 366; goto _test_eof; 
	_test_eof367:  state.cs = 367; goto _test_eof; 
	_test_eof368:  state.cs = 368; goto _test_eof; 
	_test_eof369:  state.cs = 369; goto _test_eof; 
	_test_eof370:  state.cs = 370; goto _test_eof; 
	_test_eof371:  state.cs = 371; goto _test_eof; 
	_test_eof372:  state.cs = 372; goto _test_eof; 
	_test_eof373:  state.cs = 373; goto _test_eof; 
	_test_eof374:  state.cs = 374; goto _test_eof; 
	_test_eof375:  state.cs = 375; goto _test_eof; 
	_test_eof376:  state.cs = 376; goto _test_eof; 
	_test_eof377:  state.cs = 377; goto _test_eof; 
	_test_eof378:  state.cs = 378; goto _test_eof; 
	_test_eof379:  state.cs = 379; goto _test_eof; 
	_test_eof380:  state.cs = 380; goto _test_eof; 
	_test_eof381:  state.cs = 381; goto _test_eof; 
	_test_eof382:  state.cs = 382; goto _test_eof; 
	_test_eof383:  state.cs = 383; goto _test_eof; 
	_test_eof384:  state.cs = 384; goto _test_eof; 
	_test_eof385:  state.cs = 385; goto _test_eof; 
	_test_eof386:  state.cs = 386; goto _test_eof; 
	_test_eof387:  state.cs = 387; goto _test_eof; 
	_test_eof388:  state.cs = 388; goto _test_eof; 
	_test_eof389:  state.cs = 389; goto _test_eof; 
	_test_eof390:  state.cs = 390; goto _test_eof; 
	_test_eof391:  state.cs = 391; goto _test_eof; 
	_test_eof392:  state.cs = 392; goto _test_eof; 
	_test_eof393:  state.cs = 393; goto _test_eof; 
	_test_eof394:  state.cs = 394; goto _test_eof; 
	_test_eof395:  state.cs = 395; goto _test_eof; 
	_test_eof396:  state.cs = 396; goto _test_eof; 
	_test_eof397:  state.cs = 397; goto _test_eof; 
	_test_eof398:  state.cs = 398; goto _test_eof; 
	_test_eof399:  state.cs = 399; goto _test_eof; 
	_test_eof400:  state.cs = 400; goto _test_eof; 
	_test_eof401:  state.cs = 401; goto _test_eof; 
	_test_eof402:  state.cs = 402; goto _test_eof; 
	_test_eof403:  state.cs = 403; goto _test_eof; 
	_test_eof404:  state.cs = 404; goto _test_eof; 
	_test_eof405:  state.cs = 405; goto _test_eof; 
	_test_eof406:  state.cs = 406; goto _test_eof; 
	_test_eof407:  state.cs = 407; goto _test_eof; 
	_test_eof408:  state.cs = 408; goto _test_eof; 
	_test_eof409:  state.cs = 409; goto _test_eof; 
	_test_eof410:  state.cs = 410; goto _test_eof; 
	_test_eof411:  state.cs = 411; goto _test_eof; 
	_test_eof412:  state.cs = 412; goto _test_eof; 

	_test_eof: {}
	if ( ( state.p) == ( state.eof) )
	{
	switch (  state.cs ) {
	case 415: 
#line 237 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
	break;
	case 413: 
#line 273 "configparser.rl"
	{ std::cout << "design done: " << std::endl; print_design(des); }
	break;
#line 6367 "configparser.h"
	}
	}

	_out: {}
	}

#line 309 "configparser.rl"

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
