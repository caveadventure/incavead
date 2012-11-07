
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

    
#line 283 "configparser.rl"

/*

*/

    
#line 112 "configparser.h"
static const int ConfigParser_start = 1;
static const int ConfigParser_first_final = 439;
static const int ConfigParser_error = 0;

static const int ConfigParser_en_strchar_escape = 25;
static const int ConfigParser_en_one_species = 26;
static const int ConfigParser_en_one_design = 290;
static const int ConfigParser_en_main = 1;


#line 289 "configparser.rl"
    
#line 125 "configparser.h"
	{
	 state.cs = ConfigParser_start;
	 state.top = 0;
	}

#line 290 "configparser.rl"

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
		case 439: goto st439;
		case 440: goto st440;
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
		case 441: goto st441;
		case 25: goto st25;
		case 442: goto st442;
		case 26: goto st26;
		case 27: goto st27;
		case 28: goto st28;
		case 29: goto st29;
		case 30: goto st30;
		case 31: goto st31;
		case 32: goto st32;
		case 33: goto st33;
		case 34: goto st34;
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
		case 443: goto st443;
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
		case 444: goto st444;
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
		case 413: goto st413;
		case 414: goto st414;
		case 415: goto st415;
		case 416: goto st416;
		case 417: goto st417;
		case 418: goto st418;
		case 419: goto st419;
		case 420: goto st420;
		case 421: goto st421;
		case 422: goto st422;
		case 423: goto st423;
		case 424: goto st424;
		case 425: goto st425;
		case 426: goto st426;
		case 427: goto st427;
		case 428: goto st428;
		case 429: goto st429;
		case 430: goto st430;
		case 431: goto st431;
		case 432: goto st432;
		case 433: goto st433;
		case 434: goto st434;
		case 435: goto st435;
		case 436: goto st436;
		case 437: goto st437;
		case 438: goto st438;
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
#line 273 "configparser.rl"
	{ des = Design(); }
	goto st2;
tr629:
#line 276 "configparser.rl"
	{ std::cout << "design done: " << std::endl; print_design(des); }
#line 273 "configparser.rl"
	{ des = Design(); }
	goto st2;
tr633:
#line 238 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
#line 273 "configparser.rl"
	{ des = Design(); }
	goto st2;
st2:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof2;
case 2:
#line 651 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr4;
	goto st0;
tr4:
#line 273 "configparser.rl"
	{ des = Design(); }
	goto st3;
st3:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof3;
case 3:
#line 663 "configparser.h"
	if ( (*( state.p)) == 115 )
		goto tr5;
	goto st0;
tr5:
#line 273 "configparser.rl"
	{ des = Design(); }
	goto st4;
st4:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof4;
case 4:
#line 675 "configparser.h"
	if ( (*( state.p)) == 105 )
		goto tr6;
	goto st0;
tr6:
#line 273 "configparser.rl"
	{ des = Design(); }
	goto st5;
st5:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof5;
case 5:
#line 687 "configparser.h"
	if ( (*( state.p)) == 103 )
		goto tr7;
	goto st0;
tr7:
#line 273 "configparser.rl"
	{ des = Design(); }
	goto st6;
st6:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof6;
case 6:
#line 699 "configparser.h"
	if ( (*( state.p)) == 110 )
		goto tr8;
	goto st0;
tr8:
#line 273 "configparser.rl"
	{ des = Design(); }
	goto st7;
st7:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof7;
case 7:
#line 711 "configparser.h"
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
#line 753 "configparser.h"
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
#line 266 "configparser.rl"
	{ des.level = ::atoi(state.match.c_str()); }
	goto st10;
st10:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof10;
case 10:
#line 772 "configparser.h"
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
#line 810 "configparser.h"
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
#line 269 "configparser.rl"
	{ des.tag = state.match; }
	goto st12;
st12:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof12;
case 12:
#line 837 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st12;
		case 32: goto st12;
		case 123: goto tr19;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st12;
	goto st0;
tr17:
#line 269 "configparser.rl"
	{ des.tag = state.match; }
#line 275 "configparser.rl"
	{{ state.stack[ state.top++] = 439; goto st290;}}
	goto st439;
tr19:
#line 275 "configparser.rl"
	{{ state.stack[ state.top++] = 439; goto st290;}}
	goto st439;
st439:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof439;
case 439:
#line 860 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr628;
		case 32: goto tr628;
		case 100: goto tr629;
		case 115: goto tr630;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr628;
	goto st0;
tr628:
#line 276 "configparser.rl"
	{ std::cout << "design done: " << std::endl; print_design(des); }
	goto st440;
tr632:
#line 238 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
	goto st440;
st440:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof440;
case 440:
#line 882 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st440;
		case 32: goto st440;
		case 100: goto tr2;
		case 115: goto tr3;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st440;
	goto st0;
tr3:
#line 235 "configparser.rl"
	{ spe = Species(); }
	goto st13;
tr630:
#line 276 "configparser.rl"
	{ std::cout << "design done: " << std::endl; print_design(des); }
#line 235 "configparser.rl"
	{ spe = Species(); }
	goto st13;
tr634:
#line 238 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
#line 235 "configparser.rl"
	{ spe = Species(); }
	goto st13;
st13:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof13;
case 13:
#line 912 "configparser.h"
	if ( (*( state.p)) == 112 )
		goto tr20;
	goto st0;
tr20:
#line 235 "configparser.rl"
	{ spe = Species(); }
	goto st14;
st14:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof14;
case 14:
#line 924 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr21;
	goto st0;
tr21:
#line 235 "configparser.rl"
	{ spe = Species(); }
	goto st15;
st15:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof15;
case 15:
#line 936 "configparser.h"
	if ( (*( state.p)) == 99 )
		goto tr22;
	goto st0;
tr22:
#line 235 "configparser.rl"
	{ spe = Species(); }
	goto st16;
st16:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof16;
case 16:
#line 948 "configparser.h"
	if ( (*( state.p)) == 105 )
		goto tr23;
	goto st0;
tr23:
#line 235 "configparser.rl"
	{ spe = Species(); }
	goto st17;
st17:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof17;
case 17:
#line 960 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr24;
	goto st0;
tr24:
#line 235 "configparser.rl"
	{ spe = Species(); }
	goto st18;
st18:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof18;
case 18:
#line 972 "configparser.h"
	if ( (*( state.p)) == 115 )
		goto tr25;
	goto st0;
tr25:
#line 235 "configparser.rl"
	{ spe = Species(); }
	goto st19;
st19:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof19;
case 19:
#line 984 "configparser.h"
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
#line 1026 "configparser.h"
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
#line 228 "configparser.rl"
	{ spe.level = ::atoi(state.match.c_str()); }
	goto st22;
st22:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof22;
case 22:
#line 1045 "configparser.h"
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
#line 1083 "configparser.h"
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
#line 231 "configparser.rl"
	{ spe.tag = state.match; }
	goto st24;
st24:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof24;
case 24:
#line 1110 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st24;
		case 32: goto st24;
		case 123: goto tr36;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st24;
	goto st0;
tr34:
#line 231 "configparser.rl"
	{ spe.tag = state.match; }
#line 237 "configparser.rl"
	{{ state.stack[ state.top++] = 441; goto st26;}}
	goto st441;
tr36:
#line 237 "configparser.rl"
	{{ state.stack[ state.top++] = 441; goto st26;}}
	goto st441;
st441:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof441;
case 441:
#line 1133 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr632;
		case 32: goto tr632;
		case 100: goto tr633;
		case 115: goto tr634;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr632;
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
	goto st442;
tr38:
#line 138 "configparser.rl"
	{ state.match += '\\'; { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st442;
tr39:
#line 137 "configparser.rl"
	{ state.match += '\n'; { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st442;
st442:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof442;
case 442:
#line 1169 "configparser.h"
	goto st0;
st26:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof26;
case 26:
	switch( (*( state.p)) ) {
		case 13: goto st26;
		case 32: goto st26;
		case 97: goto st27;
		case 99: goto st45;
		case 100: goto st85;
		case 104: goto st108;
		case 105: goto st143;
		case 109: goto st161;
		case 110: goto st185;
		case 114: goto st192;
		case 115: goto st199;
		case 125: goto st258;
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
		case 116: goto st280;
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
		case 105: goto st30;
		case 110: goto st259;
		case 114: goto st263;
		case 115: goto st269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st29;
	goto st0;
st30:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof30;
case 30:
	if ( (*( state.p)) == 110 )
		goto st31;
	goto st0;
st31:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof31;
case 31:
	if ( (*( state.p)) == 114 )
		goto st32;
	goto st0;
st32:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof32;
case 32:
	if ( (*( state.p)) == 97 )
		goto st33;
	goto st0;
st33:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof33;
case 33:
	if ( (*( state.p)) == 110 )
		goto st34;
	goto st0;
st34:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof34;
case 34:
	if ( (*( state.p)) == 103 )
		goto st35;
	goto st0;
st35:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof35;
case 35:
	if ( (*( state.p)) == 101 )
		goto st36;
	goto st0;
st36:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof36;
case 36:
	if ( (*( state.p)) == 95 )
		goto st37;
	goto st0;
st37:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof37;
case 37:
	if ( (*( state.p)) == 114 )
		goto st38;
	goto st0;
st38:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof38;
case 38:
	if ( (*( state.p)) == 97 )
		goto st39;
	goto st0;
st39:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof39;
case 39:
	if ( (*( state.p)) == 110 )
		goto st40;
	goto st0;
st40:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof40;
case 40:
	if ( (*( state.p)) == 100 )
		goto st41;
	goto st0;
st41:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof41;
case 41:
	if ( (*( state.p)) == 111 )
		goto st42;
	goto st0;
st42:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof42;
case 42:
	if ( (*( state.p)) == 109 )
		goto st43;
	goto st0;
st43:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof43;
case 43:
	switch( (*( state.p)) ) {
		case 13: goto tr71;
		case 32: goto tr71;
		case 59: goto tr72;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr71;
	goto st0;
tr71:
#line 179 "configparser.rl"
	{ spe.ai = Species::ai_t::inrange_random; }
	goto st44;
tr94:
#line 204 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st44;
tr118:
#line 209 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st44;
tr126:
#line 191 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
	goto st44;
tr140:
#line 200 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st44;
tr157:
#line 214 "configparser.rl"
	{ spe.drop.back().chance = ::atof(state.match.c_str()); }
	goto st44;
tr177:
#line 172 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st44;
tr183:
#line 170 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st44;
tr193:
#line 173 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st44;
tr199:
#line 169 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st44;
tr203:
#line 171 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st44;
tr217:
#line 182 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st44;
tr224:
#line 183 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st44;
tr236:
#line 186 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st44;
tr243:
#line 189 "configparser.rl"
	{ spe.move = Species::move_t::corner; }
	goto st44;
tr249:
#line 187 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st44;
tr255:
#line 188 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st44;
tr265:
#line 192 "configparser.rl"
	{ spe.name = state.match; }
	goto st44;
tr273:
#line 198 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st44;
tr316:
#line 193 "configparser.rl"
	{ spe.skin = skin; }
	goto st44;
tr319:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 193 "configparser.rl"
	{ spe.skin = skin; }
	goto st44;
tr324:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 193 "configparser.rl"
	{ spe.skin = skin; }
	goto st44;
tr330:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 193 "configparser.rl"
	{ spe.skin = skin; }
	goto st44;
tr338:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 193 "configparser.rl"
	{ spe.skin = skin; }
	goto st44;
tr342:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 193 "configparser.rl"
	{ spe.skin = skin; }
	goto st44;
tr348:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 193 "configparser.rl"
	{ spe.skin = skin; }
	goto st44;
tr355:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 193 "configparser.rl"
	{ spe.skin = skin; }
	goto st44;
tr370:
#line 222 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st44;
tr375:
#line 176 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st44;
tr382:
#line 178 "configparser.rl"
	{ spe.ai = Species::ai_t::random; }
	goto st44;
tr394:
#line 177 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st44;
tr404:
#line 199 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st44;
st44:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof44;
case 44:
#line 1476 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st44;
		case 32: goto st44;
		case 59: goto st443;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st44;
	goto st0;
tr72:
#line 179 "configparser.rl"
	{ spe.ai = Species::ai_t::inrange_random; }
	goto st443;
tr96:
#line 204 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st443;
tr120:
#line 209 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st443;
tr128:
#line 191 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
	goto st443;
tr142:
#line 200 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st443;
tr159:
#line 214 "configparser.rl"
	{ spe.drop.back().chance = ::atof(state.match.c_str()); }
	goto st443;
tr178:
#line 172 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st443;
tr184:
#line 170 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st443;
tr194:
#line 173 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st443;
tr200:
#line 169 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st443;
tr204:
#line 171 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st443;
tr218:
#line 182 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st443;
tr225:
#line 183 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st443;
tr237:
#line 186 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st443;
tr244:
#line 189 "configparser.rl"
	{ spe.move = Species::move_t::corner; }
	goto st443;
tr250:
#line 187 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st443;
tr256:
#line 188 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st443;
tr266:
#line 192 "configparser.rl"
	{ spe.name = state.match; }
	goto st443;
tr275:
#line 198 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st443;
tr317:
#line 193 "configparser.rl"
	{ spe.skin = skin; }
	goto st443;
tr320:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 193 "configparser.rl"
	{ spe.skin = skin; }
	goto st443;
tr325:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 193 "configparser.rl"
	{ spe.skin = skin; }
	goto st443;
tr331:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 193 "configparser.rl"
	{ spe.skin = skin; }
	goto st443;
tr339:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 193 "configparser.rl"
	{ spe.skin = skin; }
	goto st443;
tr343:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 193 "configparser.rl"
	{ spe.skin = skin; }
	goto st443;
tr349:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 193 "configparser.rl"
	{ spe.skin = skin; }
	goto st443;
tr356:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 193 "configparser.rl"
	{ spe.skin = skin; }
	goto st443;
tr371:
#line 222 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st443;
tr376:
#line 176 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st443;
tr383:
#line 178 "configparser.rl"
	{ spe.ai = Species::ai_t::random; }
	goto st443;
tr395:
#line 177 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st443;
tr406:
#line 199 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st443;
st443:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof443;
case 443:
#line 1631 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st26;
		case 32: goto st26;
		case 97: goto st27;
		case 99: goto st45;
		case 100: goto st85;
		case 104: goto st108;
		case 105: goto st143;
		case 109: goto st161;
		case 110: goto st185;
		case 114: goto st192;
		case 115: goto st199;
		case 125: goto st258;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st26;
	goto st0;
st45:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof45;
case 45:
	switch( (*( state.p)) ) {
		case 108: goto st46;
		case 111: goto st64;
	}
	goto st0;
st46:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof46;
case 46:
	if ( (*( state.p)) == 117 )
		goto st47;
	goto st0;
st47:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof47;
case 47:
	if ( (*( state.p)) == 109 )
		goto st48;
	goto st0;
st48:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof48;
case 48:
	if ( (*( state.p)) == 112 )
		goto st49;
	goto st0;
st49:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof49;
case 49:
	if ( (*( state.p)) == 115 )
		goto st50;
	goto st0;
st50:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof50;
case 50:
	if ( (*( state.p)) == 105 )
		goto st51;
	goto st0;
st51:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof51;
case 51:
	if ( (*( state.p)) == 122 )
		goto st52;
	goto st0;
st52:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof52;
case 52:
	if ( (*( state.p)) == 101 )
		goto st53;
	goto st0;
st53:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof53;
case 53:
	switch( (*( state.p)) ) {
		case 13: goto st54;
		case 32: goto st54;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st54;
	goto st0;
st54:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof54;
case 54:
	switch( (*( state.p)) ) {
		case 13: goto st54;
		case 32: goto st54;
		case 45: goto tr85;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr86;
	} else if ( (*( state.p)) >= 9 )
		goto st54;
	goto st0;
tr85:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st55;
st55:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof55;
case 55:
#line 1747 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr87;
	goto st0;
tr86:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st56;
tr87:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st56;
st56:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof56;
case 56:
#line 1771 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr88;
		case 32: goto tr88;
		case 46: goto tr89;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr87;
	} else if ( (*( state.p)) >= 9 )
		goto tr88;
	goto st0;
tr88:
#line 203 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st57;
st57:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof57;
case 57:
#line 1791 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st57;
		case 32: goto st57;
		case 45: goto tr91;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr92;
	} else if ( (*( state.p)) >= 9 )
		goto st57;
	goto st0;
tr91:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st58;
st58:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof58;
case 58:
#line 1817 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr93;
	goto st0;
tr92:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st59;
tr93:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st59;
st59:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof59;
case 59:
#line 1841 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr94;
		case 32: goto tr94;
		case 46: goto tr95;
		case 59: goto tr96;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr93;
	} else if ( (*( state.p)) >= 9 )
		goto tr94;
	goto st0;
tr95:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
st60:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof60;
case 60:
#line 1864 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr97;
	goto st0;
tr97:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st61;
st61:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof61;
case 61:
#line 1878 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr94;
		case 32: goto tr94;
		case 59: goto tr96;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr97;
	} else if ( (*( state.p)) >= 9 )
		goto tr94;
	goto st0;
tr89:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st62;
st62:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof62;
case 62:
#line 1900 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr98;
	goto st0;
tr98:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st63;
st63:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof63;
case 63:
#line 1914 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr88;
		case 32: goto tr88;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr98;
	} else if ( (*( state.p)) >= 9 )
		goto tr88;
	goto st0;
st64:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof64;
case 64:
	switch( (*( state.p)) ) {
		case 109: goto st65;
		case 117: goto st80;
	}
	goto st0;
st65:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof65;
case 65:
	if ( (*( state.p)) == 112 )
		goto st66;
	goto st0;
st66:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof66;
case 66:
	if ( (*( state.p)) == 97 )
		goto st67;
	goto st0;
st67:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof67;
case 67:
	if ( (*( state.p)) == 110 )
		goto st68;
	goto st0;
st68:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof68;
case 68:
	if ( (*( state.p)) == 105 )
		goto st69;
	goto st0;
st69:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof69;
case 69:
	if ( (*( state.p)) == 111 )
		goto st70;
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
	switch( (*( state.p)) ) {
		case 13: goto tr107;
		case 32: goto tr107;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr107;
	goto st0;
tr107:
#line 207 "configparser.rl"
	{ spe.companion.push_back(Species::companion_t()); }
	goto st72;
st72:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof72;
case 72:
#line 1995 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st72;
		case 32: goto st72;
		case 34: goto tr109;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st72;
	goto st0;
tr110:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st73;
tr109:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st73;
tr112:
#line 142 "configparser.rl"
	{{ state.stack[ state.top++] = 73; goto st25;}}
	goto st73;
st73:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof73;
case 73:
#line 2024 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st74;
		case 92: goto tr112;
	}
	goto tr110;
st74:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof74;
case 74:
	switch( (*( state.p)) ) {
		case 13: goto tr113;
		case 32: goto tr113;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr113;
	goto st0;
tr113:
#line 208 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st75;
st75:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof75;
case 75:
#line 2049 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st75;
		case 32: goto st75;
		case 45: goto tr115;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr116;
	} else if ( (*( state.p)) >= 9 )
		goto st75;
	goto st0;
tr115:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st76;
st76:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof76;
case 76:
#line 2075 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr117;
	goto st0;
tr116:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st77;
tr117:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st77;
st77:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof77;
case 77:
#line 2099 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr118;
		case 32: goto tr118;
		case 46: goto tr119;
		case 59: goto tr120;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr117;
	} else if ( (*( state.p)) >= 9 )
		goto tr118;
	goto st0;
tr119:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st78;
st78:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof78;
case 78:
#line 2122 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr121;
	goto st0;
tr121:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st79;
st79:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof79;
case 79:
#line 2136 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr118;
		case 32: goto tr118;
		case 59: goto tr120;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr121;
	} else if ( (*( state.p)) >= 9 )
		goto tr118;
	goto st0;
st80:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof80;
case 80:
	if ( (*( state.p)) == 110 )
		goto st81;
	goto st0;
st81:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof81;
case 81:
	if ( (*( state.p)) == 116 )
		goto st82;
	goto st0;
st82:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof82;
case 82:
	switch( (*( state.p)) ) {
		case 13: goto st83;
		case 32: goto st83;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st83;
	goto st0;
st83:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof83;
case 83:
	switch( (*( state.p)) ) {
		case 13: goto st83;
		case 32: goto st83;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr125;
	} else if ( (*( state.p)) >= 9 )
		goto st83;
	goto st0;
tr125:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st84;
tr127:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st84;
st84:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof84;
case 84:
#line 2207 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr126;
		case 32: goto tr126;
		case 59: goto tr128;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr127;
	} else if ( (*( state.p)) >= 9 )
		goto tr126;
	goto st0;
st85:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof85;
case 85:
	switch( (*( state.p)) ) {
		case 101: goto st86;
		case 114: goto st97;
	}
	goto st0;
st86:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof86;
case 86:
	if ( (*( state.p)) == 102 )
		goto st87;
	goto st0;
st87:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof87;
case 87:
	if ( (*( state.p)) == 101 )
		goto st88;
	goto st0;
st88:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof88;
case 88:
	if ( (*( state.p)) == 110 )
		goto st89;
	goto st0;
st89:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof89;
case 89:
	if ( (*( state.p)) == 115 )
		goto st90;
	goto st0;
st90:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof90;
case 90:
	if ( (*( state.p)) == 101 )
		goto st91;
	goto st0;
st91:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof91;
case 91:
	switch( (*( state.p)) ) {
		case 13: goto st92;
		case 32: goto st92;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st92;
	goto st0;
st92:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof92;
case 92:
	switch( (*( state.p)) ) {
		case 13: goto st92;
		case 32: goto st92;
		case 45: goto tr137;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr138;
	} else if ( (*( state.p)) >= 9 )
		goto st92;
	goto st0;
tr137:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st93;
st93:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof93;
case 93:
#line 2303 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr139;
	goto st0;
tr138:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st94;
tr139:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st94;
st94:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof94;
case 94:
#line 2327 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr140;
		case 32: goto tr140;
		case 46: goto tr141;
		case 59: goto tr142;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr139;
	} else if ( (*( state.p)) >= 9 )
		goto tr140;
	goto st0;
tr141:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st95;
st95:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof95;
case 95:
#line 2350 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr143;
	goto st0;
tr143:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st96;
st96:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof96;
case 96:
#line 2364 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr140;
		case 32: goto tr140;
		case 59: goto tr142;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr143;
	} else if ( (*( state.p)) >= 9 )
		goto tr140;
	goto st0;
st97:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof97;
case 97:
	if ( (*( state.p)) == 111 )
		goto st98;
	goto st0;
st98:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof98;
case 98:
	if ( (*( state.p)) == 112 )
		goto st99;
	goto st0;
st99:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof99;
case 99:
	switch( (*( state.p)) ) {
		case 13: goto tr146;
		case 32: goto tr146;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr146;
	goto st0;
tr146:
#line 212 "configparser.rl"
	{ spe.drop.push_back(Species::drop_t()); }
	goto st100;
st100:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof100;
case 100:
#line 2409 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st100;
		case 32: goto st100;
		case 34: goto tr148;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st100;
	goto st0;
tr149:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st101;
tr148:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st101;
tr151:
#line 142 "configparser.rl"
	{{ state.stack[ state.top++] = 101; goto st25;}}
	goto st101;
st101:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof101;
case 101:
#line 2438 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st102;
		case 92: goto tr151;
	}
	goto tr149;
st102:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof102;
case 102:
	switch( (*( state.p)) ) {
		case 13: goto tr152;
		case 32: goto tr152;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr152;
	goto st0;
tr152:
#line 213 "configparser.rl"
	{ spe.drop.back().tag = state.match; }
	goto st103;
st103:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof103;
case 103:
#line 2463 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st103;
		case 32: goto st103;
		case 45: goto tr154;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr155;
	} else if ( (*( state.p)) >= 9 )
		goto st103;
	goto st0;
tr154:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st104;
st104:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof104;
case 104:
#line 2489 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr156;
	goto st0;
tr155:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st105;
tr156:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st105;
st105:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof105;
case 105:
#line 2513 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr157;
		case 32: goto tr157;
		case 46: goto tr158;
		case 59: goto tr159;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr156;
	} else if ( (*( state.p)) >= 9 )
		goto tr157;
	goto st0;
tr158:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st106;
st106:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof106;
case 106:
#line 2536 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr160;
	goto st0;
tr160:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st107;
st107:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof107;
case 107:
#line 2550 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr157;
		case 32: goto tr157;
		case 59: goto tr159;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr160;
	} else if ( (*( state.p)) >= 9 )
		goto tr157;
	goto st0;
st108:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof108;
case 108:
	if ( (*( state.p)) == 97 )
		goto st109;
	goto st0;
st109:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof109;
case 109:
	if ( (*( state.p)) == 98 )
		goto st110;
	goto st0;
st110:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof110;
case 110:
	if ( (*( state.p)) == 105 )
		goto st111;
	goto st0;
st111:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof111;
case 111:
	if ( (*( state.p)) == 116 )
		goto st112;
	goto st0;
st112:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof112;
case 112:
	if ( (*( state.p)) == 97 )
		goto st113;
	goto st0;
st113:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof113;
case 113:
	if ( (*( state.p)) == 116 )
		goto st114;
	goto st0;
st114:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof114;
case 114:
	switch( (*( state.p)) ) {
		case 13: goto st115;
		case 32: goto st115;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st115;
	goto st0;
st115:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof115;
case 115:
	switch( (*( state.p)) ) {
		case 13: goto st115;
		case 32: goto st115;
		case 99: goto st116;
		case 102: goto st122;
		case 115: goto st127;
		case 119: goto st136;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st115;
	goto st0;
st116:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof116;
case 116:
	if ( (*( state.p)) == 111 )
		goto st117;
	goto st0;
st117:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof117;
case 117:
	if ( (*( state.p)) == 114 )
		goto st118;
	goto st0;
st118:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof118;
case 118:
	if ( (*( state.p)) == 110 )
		goto st119;
	goto st0;
st119:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof119;
case 119:
	if ( (*( state.p)) == 101 )
		goto st120;
	goto st0;
st120:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof120;
case 120:
	if ( (*( state.p)) == 114 )
		goto st121;
	goto st0;
st121:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof121;
case 121:
	switch( (*( state.p)) ) {
		case 13: goto tr177;
		case 32: goto tr177;
		case 59: goto tr178;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr177;
	goto st0;
st122:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof122;
case 122:
	if ( (*( state.p)) == 108 )
		goto st123;
	goto st0;
st123:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof123;
case 123:
	if ( (*( state.p)) == 111 )
		goto st124;
	goto st0;
st124:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof124;
case 124:
	if ( (*( state.p)) == 111 )
		goto st125;
	goto st0;
st125:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof125;
case 125:
	if ( (*( state.p)) == 114 )
		goto st126;
	goto st0;
st126:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof126;
case 126:
	switch( (*( state.p)) ) {
		case 13: goto tr183;
		case 32: goto tr183;
		case 59: goto tr184;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr183;
	goto st0;
st127:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof127;
case 127:
	if ( (*( state.p)) == 104 )
		goto st128;
	goto st0;
st128:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof128;
case 128:
	if ( (*( state.p)) == 111 )
		goto st129;
	goto st0;
st129:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof129;
case 129:
	if ( (*( state.p)) == 114 )
		goto st130;
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
	if ( (*( state.p)) == 108 )
		goto st132;
	goto st0;
st132:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof132;
case 132:
	if ( (*( state.p)) == 105 )
		goto st133;
	goto st0;
st133:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof133;
case 133:
	if ( (*( state.p)) == 110 )
		goto st134;
	goto st0;
st134:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof134;
case 134:
	if ( (*( state.p)) == 101 )
		goto st135;
	goto st0;
st135:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof135;
case 135:
	switch( (*( state.p)) ) {
		case 13: goto tr193;
		case 32: goto tr193;
		case 59: goto tr194;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr193;
	goto st0;
st136:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof136;
case 136:
	if ( (*( state.p)) == 97 )
		goto st137;
	goto st0;
st137:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof137;
case 137:
	switch( (*( state.p)) ) {
		case 108: goto st138;
		case 116: goto st140;
	}
	goto st0;
st138:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof138;
case 138:
	if ( (*( state.p)) == 107 )
		goto st139;
	goto st0;
st139:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof139;
case 139:
	switch( (*( state.p)) ) {
		case 13: goto tr199;
		case 32: goto tr199;
		case 59: goto tr200;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr199;
	goto st0;
st140:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof140;
case 140:
	if ( (*( state.p)) == 101 )
		goto st141;
	goto st0;
st141:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof141;
case 141:
	if ( (*( state.p)) == 114 )
		goto st142;
	goto st0;
st142:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof142;
case 142:
	switch( (*( state.p)) ) {
		case 13: goto tr203;
		case 32: goto tr203;
		case 59: goto tr204;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr203;
	goto st0;
st143:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof143;
case 143:
	if ( (*( state.p)) == 100 )
		goto st144;
	goto st0;
st144:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof144;
case 144:
	if ( (*( state.p)) == 108 )
		goto st145;
	goto st0;
st145:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof145;
case 145:
	if ( (*( state.p)) == 101 )
		goto st146;
	goto st0;
st146:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof146;
case 146:
	if ( (*( state.p)) == 95 )
		goto st147;
	goto st0;
st147:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof147;
case 147:
	if ( (*( state.p)) == 97 )
		goto st148;
	goto st0;
st148:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof148;
case 148:
	if ( (*( state.p)) == 105 )
		goto st149;
	goto st0;
st149:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof149;
case 149:
	switch( (*( state.p)) ) {
		case 13: goto st150;
		case 32: goto st150;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st150;
	goto st0;
st150:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof150;
case 150:
	switch( (*( state.p)) ) {
		case 13: goto st150;
		case 32: goto st150;
		case 110: goto st151;
		case 114: goto st155;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st150;
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
	if ( (*( state.p)) == 110 )
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
		case 13: goto tr217;
		case 32: goto tr217;
		case 59: goto tr218;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr217;
	goto st0;
st155:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof155;
case 155:
	if ( (*( state.p)) == 97 )
		goto st156;
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
	if ( (*( state.p)) == 100 )
		goto st158;
	goto st0;
st158:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof158;
case 158:
	if ( (*( state.p)) == 111 )
		goto st159;
	goto st0;
st159:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof159;
case 159:
	if ( (*( state.p)) == 109 )
		goto st160;
	goto st0;
st160:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof160;
case 160:
	switch( (*( state.p)) ) {
		case 13: goto tr224;
		case 32: goto tr224;
		case 59: goto tr225;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr224;
	goto st0;
st161:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof161;
case 161:
	if ( (*( state.p)) == 111 )
		goto st162;
	goto st0;
st162:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof162;
case 162:
	if ( (*( state.p)) == 118 )
		goto st163;
	goto st0;
st163:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof163;
case 163:
	if ( (*( state.p)) == 101 )
		goto st164;
	goto st0;
st164:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof164;
case 164:
	switch( (*( state.p)) ) {
		case 13: goto st165;
		case 32: goto st165;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st165;
	goto st0;
st165:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof165;
case 165:
	switch( (*( state.p)) ) {
		case 13: goto st165;
		case 32: goto st165;
		case 97: goto st166;
		case 99: goto st169;
		case 102: goto st175;
		case 119: goto st180;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st165;
	goto st0;
st166:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof166;
case 166:
	if ( (*( state.p)) == 110 )
		goto st167;
	goto st0;
st167:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof167;
case 167:
	if ( (*( state.p)) == 121 )
		goto st168;
	goto st0;
st168:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof168;
case 168:
	switch( (*( state.p)) ) {
		case 13: goto tr236;
		case 32: goto tr236;
		case 59: goto tr237;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr236;
	goto st0;
st169:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof169;
case 169:
	if ( (*( state.p)) == 111 )
		goto st170;
	goto st0;
st170:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof170;
case 170:
	if ( (*( state.p)) == 114 )
		goto st171;
	goto st0;
st171:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof171;
case 171:
	if ( (*( state.p)) == 110 )
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
		case 13: goto tr243;
		case 32: goto tr243;
		case 59: goto tr244;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr243;
	goto st0;
st175:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof175;
case 175:
	if ( (*( state.p)) == 108 )
		goto st176;
	goto st0;
st176:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof176;
case 176:
	if ( (*( state.p)) == 111 )
		goto st177;
	goto st0;
st177:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof177;
case 177:
	if ( (*( state.p)) == 111 )
		goto st178;
	goto st0;
st178:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof178;
case 178:
	if ( (*( state.p)) == 114 )
		goto st179;
	goto st0;
st179:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof179;
case 179:
	switch( (*( state.p)) ) {
		case 13: goto tr249;
		case 32: goto tr249;
		case 59: goto tr250;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr249;
	goto st0;
st180:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof180;
case 180:
	if ( (*( state.p)) == 97 )
		goto st181;
	goto st0;
st181:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof181;
case 181:
	if ( (*( state.p)) == 116 )
		goto st182;
	goto st0;
st182:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof182;
case 182:
	if ( (*( state.p)) == 101 )
		goto st183;
	goto st0;
st183:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof183;
case 183:
	if ( (*( state.p)) == 114 )
		goto st184;
	goto st0;
st184:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof184;
case 184:
	switch( (*( state.p)) ) {
		case 13: goto tr255;
		case 32: goto tr255;
		case 59: goto tr256;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr255;
	goto st0;
st185:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof185;
case 185:
	if ( (*( state.p)) == 97 )
		goto st186;
	goto st0;
st186:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof186;
case 186:
	if ( (*( state.p)) == 109 )
		goto st187;
	goto st0;
st187:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof187;
case 187:
	if ( (*( state.p)) == 101 )
		goto st188;
	goto st0;
st188:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof188;
case 188:
	switch( (*( state.p)) ) {
		case 13: goto st189;
		case 32: goto st189;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st189;
	goto st0;
st189:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof189;
case 189:
	switch( (*( state.p)) ) {
		case 13: goto st189;
		case 32: goto st189;
		case 34: goto tr261;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st189;
	goto st0;
tr262:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st190;
tr261:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st190;
tr264:
#line 142 "configparser.rl"
	{{ state.stack[ state.top++] = 190; goto st25;}}
	goto st190;
st190:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof190;
case 190:
#line 3256 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st191;
		case 92: goto tr264;
	}
	goto tr262;
st191:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof191;
case 191:
	switch( (*( state.p)) ) {
		case 13: goto tr265;
		case 32: goto tr265;
		case 59: goto tr266;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr265;
	goto st0;
st192:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof192;
case 192:
	if ( (*( state.p)) == 97 )
		goto st193;
	goto st0;
st193:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof193;
case 193:
	if ( (*( state.p)) == 110 )
		goto st194;
	goto st0;
st194:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof194;
case 194:
	if ( (*( state.p)) == 103 )
		goto st195;
	goto st0;
st195:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof195;
case 195:
	if ( (*( state.p)) == 101 )
		goto st196;
	goto st0;
st196:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof196;
case 196:
	switch( (*( state.p)) ) {
		case 13: goto st197;
		case 32: goto st197;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st197;
	goto st0;
st197:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof197;
case 197:
	switch( (*( state.p)) ) {
		case 13: goto st197;
		case 32: goto st197;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr272;
	} else if ( (*( state.p)) >= 9 )
		goto st197;
	goto st0;
tr272:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st198;
tr274:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st198;
st198:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof198;
case 198:
#line 3347 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr273;
		case 32: goto tr273;
		case 59: goto tr275;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr274;
	} else if ( (*( state.p)) >= 9 )
		goto tr273;
	goto st0;
st199:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof199;
case 199:
	if ( (*( state.p)) == 107 )
		goto st200;
	goto st0;
st200:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof200;
case 200:
	if ( (*( state.p)) == 105 )
		goto st201;
	goto st0;
st201:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof201;
case 201:
	if ( (*( state.p)) == 110 )
		goto st202;
	goto st0;
st202:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof202;
case 202:
	switch( (*( state.p)) ) {
		case 13: goto st203;
		case 32: goto st203;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st203;
	goto st0;
st203:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof203;
case 203:
	switch( (*( state.p)) ) {
		case 13: goto st203;
		case 32: goto st203;
		case 34: goto tr280;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st203;
	goto st0;
tr281:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st204;
tr280:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st204;
tr283:
#line 142 "configparser.rl"
	{{ state.stack[ state.top++] = 204; goto st25;}}
	goto st204;
st204:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof204;
case 204:
#line 3423 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st205;
		case 92: goto tr283;
	}
	goto tr281;
st205:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof205;
case 205:
	switch( (*( state.p)) ) {
		case 13: goto tr284;
		case 32: goto tr284;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr284;
	goto st0;
tr284:
#line 164 "configparser.rl"
	{ skin.text = state.match; }
	goto st206;
st206:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof206;
case 206:
#line 3448 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st206;
		case 32: goto st206;
		case 98: goto st207;
		case 100: goto st252;
		case 110: goto st255;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st206;
	goto st0;
st207:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof207;
case 207:
	if ( (*( state.p)) == 114 )
		goto st208;
	goto st0;
st208:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof208;
case 208:
	if ( (*( state.p)) == 105 )
		goto st209;
	goto st0;
st209:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof209;
case 209:
	if ( (*( state.p)) == 103 )
		goto st210;
	goto st0;
st210:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof210;
case 210:
	if ( (*( state.p)) == 104 )
		goto st211;
	goto st0;
st211:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof211;
case 211:
	if ( (*( state.p)) == 116 )
		goto st212;
	goto st0;
st212:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof212;
case 212:
	switch( (*( state.p)) ) {
		case 13: goto tr294;
		case 32: goto tr294;
		case 95: goto tr295;
		case 98: goto tr296;
		case 99: goto tr297;
		case 103: goto tr298;
		case 109: goto tr299;
		case 114: goto tr300;
		case 119: goto tr301;
		case 121: goto tr302;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr294;
	goto st0;
tr294:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st213;
tr359:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st213;
st213:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof213;
case 213:
#line 3525 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st213;
		case 32: goto st213;
		case 98: goto st214;
		case 99: goto st221;
		case 103: goto st225;
		case 109: goto st230;
		case 114: goto st237;
		case 119: goto st240;
		case 121: goto st245;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st213;
	goto st0;
tr296:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st214;
tr361:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st214;
st214:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof214;
case 214:
#line 3552 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st215;
	goto st0;
st215:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof215;
case 215:
	switch( (*( state.p)) ) {
		case 97: goto st216;
		case 117: goto st219;
	}
	goto st0;
st216:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof216;
case 216:
	if ( (*( state.p)) == 99 )
		goto st217;
	goto st0;
st217:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof217;
case 217:
	if ( (*( state.p)) == 107 )
		goto st218;
	goto st0;
st218:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof218;
case 218:
	switch( (*( state.p)) ) {
		case 13: goto tr316;
		case 32: goto tr316;
		case 59: goto tr317;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr316;
	goto st0;
st219:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof219;
case 219:
	if ( (*( state.p)) == 101 )
		goto st220;
	goto st0;
st220:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof220;
case 220:
	switch( (*( state.p)) ) {
		case 13: goto tr319;
		case 32: goto tr319;
		case 59: goto tr320;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr319;
	goto st0;
tr297:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st221;
tr362:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st221;
st221:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof221;
case 221:
#line 3622 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st222;
	goto st0;
st222:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof222;
case 222:
	if ( (*( state.p)) == 97 )
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
	switch( (*( state.p)) ) {
		case 13: goto tr324;
		case 32: goto tr324;
		case 59: goto tr325;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr324;
	goto st0;
tr298:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st225;
tr363:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st225;
st225:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof225;
case 225:
#line 3664 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st226;
	goto st0;
st226:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof226;
case 226:
	if ( (*( state.p)) == 101 )
		goto st227;
	goto st0;
st227:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof227;
case 227:
	if ( (*( state.p)) == 101 )
		goto st228;
	goto st0;
st228:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof228;
case 228:
	if ( (*( state.p)) == 110 )
		goto st229;
	goto st0;
st229:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof229;
case 229:
	switch( (*( state.p)) ) {
		case 13: goto tr330;
		case 32: goto tr330;
		case 59: goto tr331;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr330;
	goto st0;
tr299:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st230;
tr364:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st230;
st230:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof230;
case 230:
#line 3713 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st231;
	goto st0;
st231:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof231;
case 231:
	if ( (*( state.p)) == 103 )
		goto st232;
	goto st0;
st232:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof232;
case 232:
	if ( (*( state.p)) == 101 )
		goto st233;
	goto st0;
st233:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof233;
case 233:
	if ( (*( state.p)) == 110 )
		goto st234;
	goto st0;
st234:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof234;
case 234:
	if ( (*( state.p)) == 116 )
		goto st235;
	goto st0;
st235:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof235;
case 235:
	if ( (*( state.p)) == 97 )
		goto st236;
	goto st0;
st236:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof236;
case 236:
	switch( (*( state.p)) ) {
		case 13: goto tr338;
		case 32: goto tr338;
		case 59: goto tr339;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr338;
	goto st0;
tr300:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st237;
tr365:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st237;
st237:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof237;
case 237:
#line 3776 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st238;
	goto st0;
st238:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof238;
case 238:
	if ( (*( state.p)) == 100 )
		goto st239;
	goto st0;
st239:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof239;
case 239:
	switch( (*( state.p)) ) {
		case 13: goto tr342;
		case 32: goto tr342;
		case 59: goto tr343;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr342;
	goto st0;
tr301:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st240;
tr366:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st240;
st240:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof240;
case 240:
#line 3811 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st241;
	goto st0;
st241:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof241;
case 241:
	if ( (*( state.p)) == 105 )
		goto st242;
	goto st0;
st242:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof242;
case 242:
	if ( (*( state.p)) == 116 )
		goto st243;
	goto st0;
st243:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof243;
case 243:
	if ( (*( state.p)) == 101 )
		goto st244;
	goto st0;
st244:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof244;
case 244:
	switch( (*( state.p)) ) {
		case 13: goto tr348;
		case 32: goto tr348;
		case 59: goto tr349;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr348;
	goto st0;
tr302:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st245;
tr367:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st245;
st245:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof245;
case 245:
#line 3860 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st246;
	goto st0;
st246:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof246;
case 246:
	if ( (*( state.p)) == 108 )
		goto st247;
	goto st0;
st247:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof247;
case 247:
	if ( (*( state.p)) == 108 )
		goto st248;
	goto st0;
st248:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof248;
case 248:
	if ( (*( state.p)) == 111 )
		goto st249;
	goto st0;
st249:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof249;
case 249:
	if ( (*( state.p)) == 119 )
		goto st250;
	goto st0;
st250:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof250;
case 250:
	switch( (*( state.p)) ) {
		case 13: goto tr355;
		case 32: goto tr355;
		case 59: goto tr356;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr355;
	goto st0;
tr295:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st251;
tr360:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st251;
st251:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof251;
case 251:
#line 3916 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st214;
		case 99: goto st221;
		case 103: goto st225;
		case 109: goto st230;
		case 114: goto st237;
		case 119: goto st240;
		case 121: goto st245;
	}
	goto st0;
st252:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof252;
case 252:
	if ( (*( state.p)) == 105 )
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
		case 13: goto tr359;
		case 32: goto tr359;
		case 95: goto tr360;
		case 98: goto tr361;
		case 99: goto tr362;
		case 103: goto tr363;
		case 109: goto tr364;
		case 114: goto tr365;
		case 119: goto tr366;
		case 121: goto tr367;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr359;
	goto st0;
st255:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof255;
case 255:
	if ( (*( state.p)) == 111 )
		goto st256;
	goto st0;
st256:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof256;
case 256:
	if ( (*( state.p)) == 110 )
		goto st257;
	goto st0;
st257:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof257;
case 257:
	if ( (*( state.p)) == 101 )
		goto st218;
	goto st0;
st258:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof258;
case 258:
	switch( (*( state.p)) ) {
		case 13: goto tr370;
		case 32: goto tr370;
		case 59: goto tr371;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr370;
	goto st0;
st259:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof259;
case 259:
	if ( (*( state.p)) == 111 )
		goto st260;
	goto st0;
st260:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof260;
case 260:
	if ( (*( state.p)) == 110 )
		goto st261;
	goto st0;
st261:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof261;
case 261:
	if ( (*( state.p)) == 101 )
		goto st262;
	goto st0;
st262:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof262;
case 262:
	switch( (*( state.p)) ) {
		case 13: goto tr375;
		case 32: goto tr375;
		case 59: goto tr376;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr375;
	goto st0;
st263:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof263;
case 263:
	if ( (*( state.p)) == 97 )
		goto st264;
	goto st0;
st264:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof264;
case 264:
	if ( (*( state.p)) == 110 )
		goto st265;
	goto st0;
st265:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof265;
case 265:
	if ( (*( state.p)) == 100 )
		goto st266;
	goto st0;
st266:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof266;
case 266:
	if ( (*( state.p)) == 111 )
		goto st267;
	goto st0;
st267:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof267;
case 267:
	if ( (*( state.p)) == 109 )
		goto st268;
	goto st0;
st268:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof268;
case 268:
	switch( (*( state.p)) ) {
		case 13: goto tr382;
		case 32: goto tr382;
		case 59: goto tr383;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr382;
	goto st0;
st269:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof269;
case 269:
	if ( (*( state.p)) == 101 )
		goto st270;
	goto st0;
st270:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof270;
case 270:
	if ( (*( state.p)) == 101 )
		goto st271;
	goto st0;
st271:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof271;
case 271:
	if ( (*( state.p)) == 107 )
		goto st272;
	goto st0;
st272:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof272;
case 272:
	if ( (*( state.p)) == 95 )
		goto st273;
	goto st0;
st273:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof273;
case 273:
	if ( (*( state.p)) == 112 )
		goto st274;
	goto st0;
st274:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof274;
case 274:
	if ( (*( state.p)) == 108 )
		goto st275;
	goto st0;
st275:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof275;
case 275:
	if ( (*( state.p)) == 97 )
		goto st276;
	goto st0;
st276:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof276;
case 276:
	if ( (*( state.p)) == 121 )
		goto st277;
	goto st0;
st277:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof277;
case 277:
	if ( (*( state.p)) == 101 )
		goto st278;
	goto st0;
st278:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof278;
case 278:
	if ( (*( state.p)) == 114 )
		goto st279;
	goto st0;
st279:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof279;
case 279:
	switch( (*( state.p)) ) {
		case 13: goto tr394;
		case 32: goto tr394;
		case 59: goto tr395;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr394;
	goto st0;
st280:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof280;
case 280:
	if ( (*( state.p)) == 116 )
		goto st281;
	goto st0;
st281:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof281;
case 281:
	if ( (*( state.p)) == 97 )
		goto st282;
	goto st0;
st282:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof282;
case 282:
	if ( (*( state.p)) == 99 )
		goto st283;
	goto st0;
st283:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof283;
case 283:
	if ( (*( state.p)) == 107 )
		goto st284;
	goto st0;
st284:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof284;
case 284:
	switch( (*( state.p)) ) {
		case 13: goto st285;
		case 32: goto st285;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st285;
	goto st0;
st285:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof285;
case 285:
	switch( (*( state.p)) ) {
		case 13: goto st285;
		case 32: goto st285;
		case 45: goto tr401;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr402;
	} else if ( (*( state.p)) >= 9 )
		goto st285;
	goto st0;
tr401:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st286;
st286:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof286;
case 286:
#line 4223 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr403;
	goto st0;
tr402:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st287;
tr403:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st287;
st287:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof287;
case 287:
#line 4247 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr404;
		case 32: goto tr404;
		case 46: goto tr405;
		case 59: goto tr406;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr403;
	} else if ( (*( state.p)) >= 9 )
		goto tr404;
	goto st0;
tr405:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st288;
st288:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof288;
case 288:
#line 4270 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr407;
	goto st0;
tr407:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st289;
st289:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof289;
case 289:
#line 4284 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr404;
		case 32: goto tr404;
		case 59: goto tr406;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr407;
	} else if ( (*( state.p)) >= 9 )
		goto tr404;
	goto st0;
st290:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof290;
case 290:
	switch( (*( state.p)) ) {
		case 13: goto st290;
		case 32: goto st290;
		case 97: goto st291;
		case 99: goto st301;
		case 100: goto st308;
		case 104: goto st326;
		case 110: goto st335;
		case 115: goto st342;
		case 116: goto st418;
		case 117: goto st430;
		case 125: goto st436;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st290;
	goto st0;
st291:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof291;
case 291:
	if ( (*( state.p)) == 116 )
		goto st292;
	goto st0;
st292:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof292;
case 292:
	if ( (*( state.p)) == 116 )
		goto st293;
	goto st0;
st293:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof293;
case 293:
	if ( (*( state.p)) == 97 )
		goto st294;
	goto st0;
st294:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof294;
case 294:
	if ( (*( state.p)) == 99 )
		goto st295;
	goto st0;
st295:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof295;
case 295:
	if ( (*( state.p)) == 107 )
		goto st296;
	goto st0;
st296:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof296;
case 296:
	switch( (*( state.p)) ) {
		case 13: goto st297;
		case 32: goto st297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st297;
	goto st0;
st297:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof297;
case 297:
	switch( (*( state.p)) ) {
		case 13: goto st297;
		case 32: goto st297;
		case 45: goto tr424;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr425;
	} else if ( (*( state.p)) >= 9 )
		goto st297;
	goto st0;
tr424:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st298;
st298:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof298;
case 298:
#line 4391 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr426;
	goto st0;
tr425:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st299;
tr426:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st299;
st299:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof299;
case 299:
#line 4415 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr427;
		case 32: goto tr427;
		case 46: goto tr428;
		case 59: goto tr429;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr426;
	} else if ( (*( state.p)) >= 9 )
		goto tr427;
	goto st0;
tr427:
#line 248 "configparser.rl"
	{ des.attack = ::atof(state.match.c_str()); }
	goto st300;
tr438:
#line 243 "configparser.rl"
	{ des.count = ::atoi(state.match.c_str()); }
	goto st300;
tr452:
#line 249 "configparser.rl"
	{ des.defense = ::atof(state.match.c_str()); }
	goto st300;
tr463:
#line 247 "configparser.rl"
	{ des.descr = state.match; }
	goto st300;
tr472:
#line 251 "configparser.rl"
	{ des.heal = ::atof(state.match.c_str()); }
	goto st300;
tr484:
#line 244 "configparser.rl"
	{ des.name = state.match; }
	goto st300;
tr528:
#line 245 "configparser.rl"
	{ des.skin = skin; }
	goto st300;
tr531:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 245 "configparser.rl"
	{ des.skin = skin; }
	goto st300;
tr536:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 245 "configparser.rl"
	{ des.skin = skin; }
	goto st300;
tr542:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 245 "configparser.rl"
	{ des.skin = skin; }
	goto st300;
tr550:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 245 "configparser.rl"
	{ des.skin = skin; }
	goto st300;
tr554:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 245 "configparser.rl"
	{ des.skin = skin; }
	goto st300;
tr560:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 245 "configparser.rl"
	{ des.skin = skin; }
	goto st300;
tr567:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 245 "configparser.rl"
	{ des.skin = skin; }
	goto st300;
tr589:
#line 246 "configparser.rl"
	{ des.slot = state.match; }
	goto st300;
tr601:
#line 250 "configparser.rl"
	{ des.stackrange = ::atoi(state.match.c_str()); }
	goto st300;
tr615:
#line 253 "configparser.rl"
	{ des.throwrange = ::atoi(state.match.c_str()); }
	goto st300;
tr623:
#line 252 "configparser.rl"
	{ des.usable = true; }
	goto st300;
tr625:
#line 260 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st300;
st300:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof300;
case 300:
#line 4522 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st300;
		case 32: goto st300;
		case 59: goto st444;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st300;
	goto st0;
tr429:
#line 248 "configparser.rl"
	{ des.attack = ::atof(state.match.c_str()); }
	goto st444;
tr440:
#line 243 "configparser.rl"
	{ des.count = ::atoi(state.match.c_str()); }
	goto st444;
tr454:
#line 249 "configparser.rl"
	{ des.defense = ::atof(state.match.c_str()); }
	goto st444;
tr464:
#line 247 "configparser.rl"
	{ des.descr = state.match; }
	goto st444;
tr474:
#line 251 "configparser.rl"
	{ des.heal = ::atof(state.match.c_str()); }
	goto st444;
tr485:
#line 244 "configparser.rl"
	{ des.name = state.match; }
	goto st444;
tr529:
#line 245 "configparser.rl"
	{ des.skin = skin; }
	goto st444;
tr532:
#line 154 "configparser.rl"
	{ add_color(skin.fore, 4); }
#line 245 "configparser.rl"
	{ des.skin = skin; }
	goto st444;
tr537:
#line 156 "configparser.rl"
	{ add_color(skin.fore, 6); }
#line 245 "configparser.rl"
	{ des.skin = skin; }
	goto st444;
tr543:
#line 152 "configparser.rl"
	{ add_color(skin.fore, 2); }
#line 245 "configparser.rl"
	{ des.skin = skin; }
	goto st444;
tr551:
#line 155 "configparser.rl"
	{ add_color(skin.fore, 5); }
#line 245 "configparser.rl"
	{ des.skin = skin; }
	goto st444;
tr555:
#line 151 "configparser.rl"
	{ add_color(skin.fore, 1); }
#line 245 "configparser.rl"
	{ des.skin = skin; }
	goto st444;
tr561:
#line 157 "configparser.rl"
	{ add_color(skin.fore, 7); }
#line 245 "configparser.rl"
	{ des.skin = skin; }
	goto st444;
tr568:
#line 153 "configparser.rl"
	{ add_color(skin.fore, 3); }
#line 245 "configparser.rl"
	{ des.skin = skin; }
	goto st444;
tr590:
#line 246 "configparser.rl"
	{ des.slot = state.match; }
	goto st444;
tr603:
#line 250 "configparser.rl"
	{ des.stackrange = ::atoi(state.match.c_str()); }
	goto st444;
tr617:
#line 253 "configparser.rl"
	{ des.throwrange = ::atoi(state.match.c_str()); }
	goto st444;
tr624:
#line 252 "configparser.rl"
	{ des.usable = true; }
	goto st444;
tr626:
#line 260 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st444;
st444:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof444;
case 444:
#line 4625 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st290;
		case 32: goto st290;
		case 97: goto st291;
		case 99: goto st301;
		case 100: goto st308;
		case 104: goto st326;
		case 110: goto st335;
		case 115: goto st342;
		case 116: goto st418;
		case 117: goto st430;
		case 125: goto st436;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st290;
	goto st0;
st301:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof301;
case 301:
	if ( (*( state.p)) == 111 )
		goto st302;
	goto st0;
st302:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof302;
case 302:
	if ( (*( state.p)) == 117 )
		goto st303;
	goto st0;
st303:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof303;
case 303:
	if ( (*( state.p)) == 110 )
		goto st304;
	goto st0;
st304:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof304;
case 304:
	if ( (*( state.p)) == 116 )
		goto st305;
	goto st0;
st305:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof305;
case 305:
	switch( (*( state.p)) ) {
		case 13: goto st306;
		case 32: goto st306;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st306;
	goto st0;
st306:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof306;
case 306:
	switch( (*( state.p)) ) {
		case 13: goto st306;
		case 32: goto st306;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr437;
	} else if ( (*( state.p)) >= 9 )
		goto st306;
	goto st0;
tr437:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st307;
tr439:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st307;
st307:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof307;
case 307:
#line 4715 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr438;
		case 32: goto tr438;
		case 59: goto tr440;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr439;
	} else if ( (*( state.p)) >= 9 )
		goto tr438;
	goto st0;
st308:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof308;
case 308:
	if ( (*( state.p)) == 101 )
		goto st309;
	goto st0;
st309:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof309;
case 309:
	switch( (*( state.p)) ) {
		case 102: goto st310;
		case 115: goto st320;
	}
	goto st0;
st310:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof310;
case 310:
	if ( (*( state.p)) == 101 )
		goto st311;
	goto st0;
st311:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof311;
case 311:
	if ( (*( state.p)) == 110 )
		goto st312;
	goto st0;
st312:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof312;
case 312:
	if ( (*( state.p)) == 115 )
		goto st313;
	goto st0;
st313:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof313;
case 313:
	if ( (*( state.p)) == 101 )
		goto st314;
	goto st0;
st314:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof314;
case 314:
	switch( (*( state.p)) ) {
		case 13: goto st315;
		case 32: goto st315;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st315;
	goto st0;
st315:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof315;
case 315:
	switch( (*( state.p)) ) {
		case 13: goto st315;
		case 32: goto st315;
		case 45: goto tr449;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr450;
	} else if ( (*( state.p)) >= 9 )
		goto st315;
	goto st0;
tr449:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st316;
st316:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof316;
case 316:
#line 4811 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr451;
	goto st0;
tr450:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st317;
tr451:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st317;
st317:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof317;
case 317:
#line 4835 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr452;
		case 32: goto tr452;
		case 46: goto tr453;
		case 59: goto tr454;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr451;
	} else if ( (*( state.p)) >= 9 )
		goto tr452;
	goto st0;
tr453:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st318;
st318:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof318;
case 318:
#line 4858 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr455;
	goto st0;
tr455:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st319;
st319:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof319;
case 319:
#line 4872 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr452;
		case 32: goto tr452;
		case 59: goto tr454;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr455;
	} else if ( (*( state.p)) >= 9 )
		goto tr452;
	goto st0;
st320:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof320;
case 320:
	if ( (*( state.p)) == 99 )
		goto st321;
	goto st0;
st321:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof321;
case 321:
	if ( (*( state.p)) == 114 )
		goto st322;
	goto st0;
st322:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof322;
case 322:
	switch( (*( state.p)) ) {
		case 13: goto st323;
		case 32: goto st323;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st323;
	goto st0;
st323:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof323;
case 323:
	switch( (*( state.p)) ) {
		case 13: goto st323;
		case 32: goto st323;
		case 34: goto tr459;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st323;
	goto st0;
tr460:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st324;
tr459:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st324;
tr462:
#line 142 "configparser.rl"
	{{ state.stack[ state.top++] = 324; goto st25;}}
	goto st324;
st324:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof324;
case 324:
#line 4941 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr462;
	}
	goto tr460;
st325:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof325;
case 325:
	switch( (*( state.p)) ) {
		case 13: goto tr463;
		case 32: goto tr463;
		case 59: goto tr464;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr463;
	goto st0;
st326:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof326;
case 326:
	if ( (*( state.p)) == 101 )
		goto st327;
	goto st0;
st327:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof327;
case 327:
	if ( (*( state.p)) == 97 )
		goto st328;
	goto st0;
st328:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof328;
case 328:
	if ( (*( state.p)) == 108 )
		goto st329;
	goto st0;
st329:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof329;
case 329:
	switch( (*( state.p)) ) {
		case 13: goto st330;
		case 32: goto st330;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st330;
	goto st0;
st330:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof330;
case 330:
	switch( (*( state.p)) ) {
		case 13: goto st330;
		case 32: goto st330;
		case 45: goto tr469;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr470;
	} else if ( (*( state.p)) >= 9 )
		goto st330;
	goto st0;
tr469:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st331;
st331:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof331;
case 331:
#line 5020 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr471;
	goto st0;
tr470:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st332;
tr471:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st332;
st332:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof332;
case 332:
#line 5044 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr472;
		case 32: goto tr472;
		case 46: goto tr473;
		case 59: goto tr474;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr471;
	} else if ( (*( state.p)) >= 9 )
		goto tr472;
	goto st0;
tr473:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st333;
st333:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof333;
case 333:
#line 5067 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr475;
	goto st0;
tr475:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st334;
st334:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof334;
case 334:
#line 5081 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr472;
		case 32: goto tr472;
		case 59: goto tr474;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr475;
	} else if ( (*( state.p)) >= 9 )
		goto tr472;
	goto st0;
st335:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof335;
case 335:
	if ( (*( state.p)) == 97 )
		goto st336;
	goto st0;
st336:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof336;
case 336:
	if ( (*( state.p)) == 109 )
		goto st337;
	goto st0;
st337:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof337;
case 337:
	if ( (*( state.p)) == 101 )
		goto st338;
	goto st0;
st338:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof338;
case 338:
	switch( (*( state.p)) ) {
		case 13: goto st339;
		case 32: goto st339;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st339;
	goto st0;
st339:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof339;
case 339:
	switch( (*( state.p)) ) {
		case 13: goto st339;
		case 32: goto st339;
		case 34: goto tr480;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st339;
	goto st0;
tr481:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st340;
tr480:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st340;
tr483:
#line 142 "configparser.rl"
	{{ state.stack[ state.top++] = 340; goto st25;}}
	goto st340;
st340:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof340;
case 340:
#line 5157 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st341;
		case 92: goto tr483;
	}
	goto tr481;
st341:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof341;
case 341:
	switch( (*( state.p)) ) {
		case 13: goto tr484;
		case 32: goto tr484;
		case 59: goto tr485;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr484;
	goto st0;
st342:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof342;
case 342:
	switch( (*( state.p)) ) {
		case 107: goto st343;
		case 108: goto st401;
		case 116: goto st407;
	}
	goto st0;
st343:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof343;
case 343:
	if ( (*( state.p)) == 105 )
		goto st344;
	goto st0;
st344:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof344;
case 344:
	if ( (*( state.p)) == 110 )
		goto st345;
	goto st0;
st345:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof345;
case 345:
	switch( (*( state.p)) ) {
		case 13: goto st346;
		case 32: goto st346;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st346;
	goto st0;
st346:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof346;
case 346:
	switch( (*( state.p)) ) {
		case 13: goto st346;
		case 32: goto st346;
		case 34: goto tr492;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st346;
	goto st0;
tr493:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st347;
tr492:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st347;
tr495:
#line 142 "configparser.rl"
	{{ state.stack[ state.top++] = 347; goto st25;}}
	goto st347;
st347:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof347;
case 347:
#line 5242 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st348;
		case 92: goto tr495;
	}
	goto tr493;
st348:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof348;
case 348:
	switch( (*( state.p)) ) {
		case 13: goto tr496;
		case 32: goto tr496;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr496;
	goto st0;
tr496:
#line 164 "configparser.rl"
	{ skin.text = state.match; }
	goto st349;
st349:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof349;
case 349:
#line 5267 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st349;
		case 32: goto st349;
		case 98: goto st350;
		case 100: goto st395;
		case 110: goto st398;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st349;
	goto st0;
st350:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof350;
case 350:
	if ( (*( state.p)) == 114 )
		goto st351;
	goto st0;
st351:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof351;
case 351:
	if ( (*( state.p)) == 105 )
		goto st352;
	goto st0;
st352:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof352;
case 352:
	if ( (*( state.p)) == 103 )
		goto st353;
	goto st0;
st353:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof353;
case 353:
	if ( (*( state.p)) == 104 )
		goto st354;
	goto st0;
st354:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof354;
case 354:
	if ( (*( state.p)) == 116 )
		goto st355;
	goto st0;
st355:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof355;
case 355:
	switch( (*( state.p)) ) {
		case 13: goto tr506;
		case 32: goto tr506;
		case 95: goto tr507;
		case 98: goto tr508;
		case 99: goto tr509;
		case 103: goto tr510;
		case 109: goto tr511;
		case 114: goto tr512;
		case 119: goto tr513;
		case 121: goto tr514;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr506;
	goto st0;
tr506:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st356;
tr571:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st356;
st356:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof356;
case 356:
#line 5344 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st356;
		case 32: goto st356;
		case 98: goto st357;
		case 99: goto st364;
		case 103: goto st368;
		case 109: goto st373;
		case 114: goto st380;
		case 119: goto st383;
		case 121: goto st388;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st356;
	goto st0;
tr508:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st357;
tr573:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st357;
st357:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof357;
case 357:
#line 5371 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st358;
	goto st0;
st358:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof358;
case 358:
	switch( (*( state.p)) ) {
		case 97: goto st359;
		case 117: goto st362;
	}
	goto st0;
st359:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof359;
case 359:
	if ( (*( state.p)) == 99 )
		goto st360;
	goto st0;
st360:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof360;
case 360:
	if ( (*( state.p)) == 107 )
		goto st361;
	goto st0;
st361:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof361;
case 361:
	switch( (*( state.p)) ) {
		case 13: goto tr528;
		case 32: goto tr528;
		case 59: goto tr529;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr528;
	goto st0;
st362:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof362;
case 362:
	if ( (*( state.p)) == 101 )
		goto st363;
	goto st0;
st363:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof363;
case 363:
	switch( (*( state.p)) ) {
		case 13: goto tr531;
		case 32: goto tr531;
		case 59: goto tr532;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr531;
	goto st0;
tr509:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st364;
tr574:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st364;
st364:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof364;
case 364:
#line 5441 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st365;
	goto st0;
st365:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof365;
case 365:
	if ( (*( state.p)) == 97 )
		goto st366;
	goto st0;
st366:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof366;
case 366:
	if ( (*( state.p)) == 110 )
		goto st367;
	goto st0;
st367:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof367;
case 367:
	switch( (*( state.p)) ) {
		case 13: goto tr536;
		case 32: goto tr536;
		case 59: goto tr537;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr536;
	goto st0;
tr510:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st368;
tr575:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st368;
st368:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof368;
case 368:
#line 5483 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st369;
	goto st0;
st369:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof369;
case 369:
	if ( (*( state.p)) == 101 )
		goto st370;
	goto st0;
st370:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof370;
case 370:
	if ( (*( state.p)) == 101 )
		goto st371;
	goto st0;
st371:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof371;
case 371:
	if ( (*( state.p)) == 110 )
		goto st372;
	goto st0;
st372:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof372;
case 372:
	switch( (*( state.p)) ) {
		case 13: goto tr542;
		case 32: goto tr542;
		case 59: goto tr543;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr542;
	goto st0;
tr511:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st373;
tr576:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st373;
st373:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof373;
case 373:
#line 5532 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st374;
	goto st0;
st374:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof374;
case 374:
	if ( (*( state.p)) == 103 )
		goto st375;
	goto st0;
st375:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof375;
case 375:
	if ( (*( state.p)) == 101 )
		goto st376;
	goto st0;
st376:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof376;
case 376:
	if ( (*( state.p)) == 110 )
		goto st377;
	goto st0;
st377:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof377;
case 377:
	if ( (*( state.p)) == 116 )
		goto st378;
	goto st0;
st378:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof378;
case 378:
	if ( (*( state.p)) == 97 )
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
tr512:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st380;
tr577:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st380;
st380:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof380;
case 380:
#line 5595 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st381;
	goto st0;
st381:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof381;
case 381:
	if ( (*( state.p)) == 100 )
		goto st382;
	goto st0;
st382:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof382;
case 382:
	switch( (*( state.p)) ) {
		case 13: goto tr554;
		case 32: goto tr554;
		case 59: goto tr555;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr554;
	goto st0;
tr513:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st383;
tr578:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st383;
st383:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof383;
case 383:
#line 5630 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st384;
	goto st0;
st384:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof384;
case 384:
	if ( (*( state.p)) == 105 )
		goto st385;
	goto st0;
st385:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof385;
case 385:
	if ( (*( state.p)) == 116 )
		goto st386;
	goto st0;
st386:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof386;
case 386:
	if ( (*( state.p)) == 101 )
		goto st387;
	goto st0;
st387:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof387;
case 387:
	switch( (*( state.p)) ) {
		case 13: goto tr560;
		case 32: goto tr560;
		case 59: goto tr561;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr560;
	goto st0;
tr514:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st388;
tr579:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st388;
st388:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof388;
case 388:
#line 5679 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st389;
	goto st0;
st389:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof389;
case 389:
	if ( (*( state.p)) == 108 )
		goto st390;
	goto st0;
st390:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof390;
case 390:
	if ( (*( state.p)) == 108 )
		goto st391;
	goto st0;
st391:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof391;
case 391:
	if ( (*( state.p)) == 111 )
		goto st392;
	goto st0;
st392:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof392;
case 392:
	if ( (*( state.p)) == 119 )
		goto st393;
	goto st0;
st393:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof393;
case 393:
	switch( (*( state.p)) ) {
		case 13: goto tr567;
		case 32: goto tr567;
		case 59: goto tr568;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr567;
	goto st0;
tr507:
#line 162 "configparser.rl"
	{ skin.fore = maudit::color::bright_black; }
	goto st394;
tr572:
#line 161 "configparser.rl"
	{ skin.fore = maudit::color::dim_black; }
	goto st394;
st394:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof394;
case 394:
#line 5735 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st357;
		case 99: goto st364;
		case 103: goto st368;
		case 109: goto st373;
		case 114: goto st380;
		case 119: goto st383;
		case 121: goto st388;
	}
	goto st0;
st395:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof395;
case 395:
	if ( (*( state.p)) == 105 )
		goto st396;
	goto st0;
st396:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof396;
case 396:
	if ( (*( state.p)) == 109 )
		goto st397;
	goto st0;
st397:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof397;
case 397:
	switch( (*( state.p)) ) {
		case 13: goto tr571;
		case 32: goto tr571;
		case 95: goto tr572;
		case 98: goto tr573;
		case 99: goto tr574;
		case 103: goto tr575;
		case 109: goto tr576;
		case 114: goto tr577;
		case 119: goto tr578;
		case 121: goto tr579;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr571;
	goto st0;
st398:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof398;
case 398:
	if ( (*( state.p)) == 111 )
		goto st399;
	goto st0;
st399:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof399;
case 399:
	if ( (*( state.p)) == 110 )
		goto st400;
	goto st0;
st400:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof400;
case 400:
	if ( (*( state.p)) == 101 )
		goto st361;
	goto st0;
st401:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof401;
case 401:
	if ( (*( state.p)) == 111 )
		goto st402;
	goto st0;
st402:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof402;
case 402:
	if ( (*( state.p)) == 116 )
		goto st403;
	goto st0;
st403:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof403;
case 403:
	switch( (*( state.p)) ) {
		case 13: goto st404;
		case 32: goto st404;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st404;
	goto st0;
st404:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof404;
case 404:
	switch( (*( state.p)) ) {
		case 13: goto st404;
		case 32: goto st404;
		case 34: goto tr585;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st404;
	goto st0;
tr586:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st405;
tr585:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
	goto st405;
tr588:
#line 142 "configparser.rl"
	{{ state.stack[ state.top++] = 405; goto st25;}}
	goto st405;
st405:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof405;
case 405:
#line 5857 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st406;
		case 92: goto tr588;
	}
	goto tr586;
st406:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof406;
case 406:
	switch( (*( state.p)) ) {
		case 13: goto tr589;
		case 32: goto tr589;
		case 59: goto tr590;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr589;
	goto st0;
st407:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof407;
case 407:
	if ( (*( state.p)) == 97 )
		goto st408;
	goto st0;
st408:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof408;
case 408:
	if ( (*( state.p)) == 99 )
		goto st409;
	goto st0;
st409:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof409;
case 409:
	if ( (*( state.p)) == 107 )
		goto st410;
	goto st0;
st410:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof410;
case 410:
	if ( (*( state.p)) == 114 )
		goto st411;
	goto st0;
st411:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof411;
case 411:
	if ( (*( state.p)) == 97 )
		goto st412;
	goto st0;
st412:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof412;
case 412:
	if ( (*( state.p)) == 110 )
		goto st413;
	goto st0;
st413:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof413;
case 413:
	if ( (*( state.p)) == 103 )
		goto st414;
	goto st0;
st414:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof414;
case 414:
	if ( (*( state.p)) == 101 )
		goto st415;
	goto st0;
st415:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof415;
case 415:
	switch( (*( state.p)) ) {
		case 13: goto st416;
		case 32: goto st416;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st416;
	goto st0;
st416:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof416;
case 416:
	switch( (*( state.p)) ) {
		case 13: goto st416;
		case 32: goto st416;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr600;
	} else if ( (*( state.p)) >= 9 )
		goto st416;
	goto st0;
tr600:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st417;
tr602:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st417;
st417:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof417;
case 417:
#line 5976 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr601;
		case 32: goto tr601;
		case 59: goto tr603;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr602;
	} else if ( (*( state.p)) >= 9 )
		goto tr601;
	goto st0;
st418:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof418;
case 418:
	if ( (*( state.p)) == 104 )
		goto st419;
	goto st0;
st419:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof419;
case 419:
	if ( (*( state.p)) == 114 )
		goto st420;
	goto st0;
st420:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof420;
case 420:
	if ( (*( state.p)) == 111 )
		goto st421;
	goto st0;
st421:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof421;
case 421:
	if ( (*( state.p)) == 119 )
		goto st422;
	goto st0;
st422:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof422;
case 422:
	if ( (*( state.p)) == 114 )
		goto st423;
	goto st0;
st423:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof423;
case 423:
	if ( (*( state.p)) == 97 )
		goto st424;
	goto st0;
st424:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof424;
case 424:
	if ( (*( state.p)) == 110 )
		goto st425;
	goto st0;
st425:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof425;
case 425:
	if ( (*( state.p)) == 103 )
		goto st426;
	goto st0;
st426:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof426;
case 426:
	if ( (*( state.p)) == 101 )
		goto st427;
	goto st0;
st427:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof427;
case 427:
	switch( (*( state.p)) ) {
		case 13: goto st428;
		case 32: goto st428;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st428;
	goto st0;
st428:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof428;
case 428:
	switch( (*( state.p)) ) {
		case 13: goto st428;
		case 32: goto st428;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr614;
	} else if ( (*( state.p)) >= 9 )
		goto st428;
	goto st0;
tr614:
#line 110 "configparser.rl"
	{
            state.match.clear();
        }
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st429;
tr616:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st429;
st429:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof429;
case 429:
#line 6096 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr615;
		case 32: goto tr615;
		case 59: goto tr617;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr616;
	} else if ( (*( state.p)) >= 9 )
		goto tr615;
	goto st0;
st430:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof430;
case 430:
	if ( (*( state.p)) == 115 )
		goto st431;
	goto st0;
st431:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof431;
case 431:
	if ( (*( state.p)) == 97 )
		goto st432;
	goto st0;
st432:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof432;
case 432:
	if ( (*( state.p)) == 98 )
		goto st433;
	goto st0;
st433:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof433;
case 433:
	if ( (*( state.p)) == 108 )
		goto st434;
	goto st0;
st434:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof434;
case 434:
	if ( (*( state.p)) == 101 )
		goto st435;
	goto st0;
st435:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof435;
case 435:
	switch( (*( state.p)) ) {
		case 13: goto tr623;
		case 32: goto tr623;
		case 59: goto tr624;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr623;
	goto st0;
st436:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof436;
case 436:
	switch( (*( state.p)) ) {
		case 13: goto tr625;
		case 32: goto tr625;
		case 59: goto tr626;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr625;
	goto st0;
tr428:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st437;
st437:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof437;
case 437:
#line 6177 "configparser.h"
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr627;
	goto st0;
tr627:
#line 114 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st438;
st438:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof438;
case 438:
#line 6191 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr427;
		case 32: goto tr427;
		case 59: goto tr429;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr627;
	} else if ( (*( state.p)) >= 9 )
		goto tr427;
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
	_test_eof439:  state.cs = 439; goto _test_eof; 
	_test_eof440:  state.cs = 440; goto _test_eof; 
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
	_test_eof441:  state.cs = 441; goto _test_eof; 
	_test_eof25:  state.cs = 25; goto _test_eof; 
	_test_eof442:  state.cs = 442; goto _test_eof; 
	_test_eof26:  state.cs = 26; goto _test_eof; 
	_test_eof27:  state.cs = 27; goto _test_eof; 
	_test_eof28:  state.cs = 28; goto _test_eof; 
	_test_eof29:  state.cs = 29; goto _test_eof; 
	_test_eof30:  state.cs = 30; goto _test_eof; 
	_test_eof31:  state.cs = 31; goto _test_eof; 
	_test_eof32:  state.cs = 32; goto _test_eof; 
	_test_eof33:  state.cs = 33; goto _test_eof; 
	_test_eof34:  state.cs = 34; goto _test_eof; 
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
	_test_eof443:  state.cs = 443; goto _test_eof; 
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
	_test_eof444:  state.cs = 444; goto _test_eof; 
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
	_test_eof413:  state.cs = 413; goto _test_eof; 
	_test_eof414:  state.cs = 414; goto _test_eof; 
	_test_eof415:  state.cs = 415; goto _test_eof; 
	_test_eof416:  state.cs = 416; goto _test_eof; 
	_test_eof417:  state.cs = 417; goto _test_eof; 
	_test_eof418:  state.cs = 418; goto _test_eof; 
	_test_eof419:  state.cs = 419; goto _test_eof; 
	_test_eof420:  state.cs = 420; goto _test_eof; 
	_test_eof421:  state.cs = 421; goto _test_eof; 
	_test_eof422:  state.cs = 422; goto _test_eof; 
	_test_eof423:  state.cs = 423; goto _test_eof; 
	_test_eof424:  state.cs = 424; goto _test_eof; 
	_test_eof425:  state.cs = 425; goto _test_eof; 
	_test_eof426:  state.cs = 426; goto _test_eof; 
	_test_eof427:  state.cs = 427; goto _test_eof; 
	_test_eof428:  state.cs = 428; goto _test_eof; 
	_test_eof429:  state.cs = 429; goto _test_eof; 
	_test_eof430:  state.cs = 430; goto _test_eof; 
	_test_eof431:  state.cs = 431; goto _test_eof; 
	_test_eof432:  state.cs = 432; goto _test_eof; 
	_test_eof433:  state.cs = 433; goto _test_eof; 
	_test_eof434:  state.cs = 434; goto _test_eof; 
	_test_eof435:  state.cs = 435; goto _test_eof; 
	_test_eof436:  state.cs = 436; goto _test_eof; 
	_test_eof437:  state.cs = 437; goto _test_eof; 
	_test_eof438:  state.cs = 438; goto _test_eof; 

	_test_eof: {}
	if ( ( state.p) == ( state.eof) )
	{
	switch (  state.cs ) {
	case 441: 
#line 238 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
	break;
	case 439: 
#line 276 "configparser.rl"
	{ std::cout << "design done: " << std::endl; print_design(des); }
	break;
#line 6661 "configparser.h"
	}
	}

	_out: {}
	}

#line 312 "configparser.rl"

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
