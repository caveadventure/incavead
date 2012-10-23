
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

    
#line 201 "configparser.rl"

/*

*/

    
#line 96 "configparser.h"
static const int ConfigParser_start = 1;
static const int ConfigParser_first_final = 577;
static const int ConfigParser_error = 0;

static const int ConfigParser_en_one_species = 14;
static const int ConfigParser_en_main = 1;


#line 207 "configparser.rl"
    
#line 107 "configparser.h"
	{
	 state.cs = ConfigParser_start;
	 state.top = 0;
	}

#line 208 "configparser.rl"

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

        
#line 136 "configparser.h"
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
		case 13: goto st13;
		case 577: goto st577;
		case 578: goto st578;
		case 14: goto st14;
		case 15: goto st15;
		case 16: goto st16;
		case 17: goto st17;
		case 18: goto st18;
		case 19: goto st19;
		case 20: goto st20;
		case 21: goto st21;
		case 22: goto st22;
		case 579: goto st579;
		case 23: goto st23;
		case 24: goto st24;
		case 25: goto st25;
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
		case 580: goto st580;
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
		case 581: goto st581;
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
		case 439: goto st439;
		case 440: goto st440;
		case 441: goto st441;
		case 442: goto st442;
		case 443: goto st443;
		case 444: goto st444;
		case 445: goto st445;
		case 446: goto st446;
		case 447: goto st447;
		case 448: goto st448;
		case 449: goto st449;
		case 450: goto st450;
		case 451: goto st451;
		case 452: goto st452;
		case 453: goto st453;
		case 454: goto st454;
		case 455: goto st455;
		case 456: goto st456;
		case 457: goto st457;
		case 458: goto st458;
		case 459: goto st459;
		case 460: goto st460;
		case 461: goto st461;
		case 462: goto st462;
		case 463: goto st463;
		case 464: goto st464;
		case 465: goto st465;
		case 466: goto st466;
		case 467: goto st467;
		case 468: goto st468;
		case 469: goto st469;
		case 470: goto st470;
		case 471: goto st471;
		case 472: goto st472;
		case 473: goto st473;
		case 474: goto st474;
		case 475: goto st475;
		case 476: goto st476;
		case 477: goto st477;
		case 478: goto st478;
		case 479: goto st479;
		case 480: goto st480;
		case 481: goto st481;
		case 482: goto st482;
		case 483: goto st483;
		case 484: goto st484;
		case 485: goto st485;
		case 486: goto st486;
		case 487: goto st487;
		case 488: goto st488;
		case 489: goto st489;
		case 490: goto st490;
		case 491: goto st491;
		case 492: goto st492;
		case 493: goto st493;
		case 494: goto st494;
		case 495: goto st495;
		case 496: goto st496;
		case 497: goto st497;
		case 498: goto st498;
		case 499: goto st499;
		case 500: goto st500;
		case 501: goto st501;
		case 502: goto st502;
		case 503: goto st503;
		case 504: goto st504;
		case 505: goto st505;
		case 506: goto st506;
		case 507: goto st507;
		case 508: goto st508;
		case 509: goto st509;
		case 510: goto st510;
		case 511: goto st511;
		case 512: goto st512;
		case 513: goto st513;
		case 514: goto st514;
		case 515: goto st515;
		case 516: goto st516;
		case 517: goto st517;
		case 518: goto st518;
		case 519: goto st519;
		case 520: goto st520;
		case 521: goto st521;
		case 522: goto st522;
		case 523: goto st523;
		case 524: goto st524;
		case 525: goto st525;
		case 526: goto st526;
		case 527: goto st527;
		case 528: goto st528;
		case 529: goto st529;
		case 530: goto st530;
		case 531: goto st531;
		case 532: goto st532;
		case 533: goto st533;
		case 534: goto st534;
		case 535: goto st535;
		case 536: goto st536;
		case 537: goto st537;
		case 538: goto st538;
		case 539: goto st539;
		case 540: goto st540;
		case 541: goto st541;
		case 542: goto st542;
		case 543: goto st543;
		case 544: goto st544;
		case 545: goto st545;
		case 546: goto st546;
		case 547: goto st547;
		case 548: goto st548;
		case 549: goto st549;
		case 550: goto st550;
		case 551: goto st551;
		case 552: goto st552;
		case 553: goto st553;
		case 554: goto st554;
		case 555: goto st555;
		case 556: goto st556;
		case 557: goto st557;
		case 558: goto st558;
		case 559: goto st559;
		case 560: goto st560;
		case 561: goto st561;
		case 562: goto st562;
		case 563: goto st563;
		case 564: goto st564;
		case 565: goto st565;
		case 566: goto st566;
		case 567: goto st567;
		case 568: goto st568;
		case 569: goto st569;
		case 570: goto st570;
		case 571: goto st571;
		case 572: goto st572;
		case 573: goto st573;
		case 574: goto st574;
		case 575: goto st575;
		case 576: goto st576;
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
		case 115: goto tr2;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st1;
	goto st0;
st0:
 state.cs = 0;
	goto _out;
tr2:
#line 193 "configparser.rl"
	{ spe = Species(); }
	goto st2;
tr809:
#line 196 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
#line 193 "configparser.rl"
	{ spe = Species(); }
	goto st2;
st2:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof2;
case 2:
#line 763 "configparser.h"
	if ( (*( state.p)) == 112 )
		goto tr3;
	goto st0;
tr3:
#line 193 "configparser.rl"
	{ spe = Species(); }
	goto st3;
st3:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof3;
case 3:
#line 775 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr4;
	goto st0;
tr4:
#line 193 "configparser.rl"
	{ spe = Species(); }
	goto st4;
st4:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof4;
case 4:
#line 787 "configparser.h"
	if ( (*( state.p)) == 99 )
		goto tr5;
	goto st0;
tr5:
#line 193 "configparser.rl"
	{ spe = Species(); }
	goto st5;
st5:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof5;
case 5:
#line 799 "configparser.h"
	if ( (*( state.p)) == 105 )
		goto tr6;
	goto st0;
tr6:
#line 193 "configparser.rl"
	{ spe = Species(); }
	goto st6;
st6:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof6;
case 6:
#line 811 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr7;
	goto st0;
tr7:
#line 193 "configparser.rl"
	{ spe = Species(); }
	goto st7;
st7:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof7;
case 7:
#line 823 "configparser.h"
	if ( (*( state.p)) == 115 )
		goto tr8;
	goto st0;
tr8:
#line 193 "configparser.rl"
	{ spe = Species(); }
	goto st8;
st8:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof8;
case 8:
#line 835 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st9;
		case 32: goto st9;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st9;
	goto st0;
st9:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof9;
case 9:
	switch( (*( state.p)) ) {
		case 13: goto st9;
		case 32: goto st9;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr10;
	} else if ( (*( state.p)) >= 9 )
		goto st9;
	goto st0;
tr10:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st10;
tr12:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st10;
st10:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof10;
case 10:
#line 877 "configparser.h"
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
#line 186 "configparser.rl"
	{ spe.level = ::atoi(state.match.c_str()); }
	goto st11;
st11:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof11;
case 11:
#line 896 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st11;
		case 32: goto st11;
		case 95: goto tr14;
	}
	if ( (*( state.p)) < 48 ) {
		if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
			goto st11;
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
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st12;
tr16:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st12;
st12:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof12;
case 12:
#line 934 "configparser.h"
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
#line 189 "configparser.rl"
	{ spe.tag = state.match; }
	goto st13;
st13:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof13;
case 13:
#line 961 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st13;
		case 32: goto st13;
		case 123: goto tr19;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st13;
	goto st0;
tr17:
#line 189 "configparser.rl"
	{ spe.tag = state.match; }
#line 195 "configparser.rl"
	{{ state.stack[ state.top++] = 577; goto st14;}}
	goto st577;
tr19:
#line 195 "configparser.rl"
	{{ state.stack[ state.top++] = 577; goto st14;}}
	goto st577;
st577:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof577;
case 577:
#line 984 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr808;
		case 32: goto tr808;
		case 115: goto tr809;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr808;
	goto st0;
tr808:
#line 196 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
	goto st578;
st578:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof578;
case 578:
#line 1001 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st578;
		case 32: goto st578;
		case 115: goto tr2;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st578;
	goto st0;
st14:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof14;
case 14:
	switch( (*( state.p)) ) {
		case 13: goto st14;
		case 32: goto st14;
		case 97: goto st15;
		case 99: goto st23;
		case 104: goto st46;
		case 105: goto st81;
		case 109: goto st99;
		case 110: goto st117;
		case 114: goto st552;
		case 115: goto st559;
		case 125: goto st565;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st14;
	goto st0;
st15:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof15;
case 15:
	if ( (*( state.p)) == 105 )
		goto st16;
	goto st0;
st16:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof16;
case 16:
	switch( (*( state.p)) ) {
		case 13: goto st17;
		case 32: goto st17;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st17;
	goto st0;
st17:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof17;
case 17:
	switch( (*( state.p)) ) {
		case 13: goto st17;
		case 32: goto st17;
		case 110: goto st18;
		case 115: goto st566;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st17;
	goto st0;
st18:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof18;
case 18:
	if ( (*( state.p)) == 111 )
		goto st19;
	goto st0;
st19:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof19;
case 19:
	if ( (*( state.p)) == 110 )
		goto st20;
	goto st0;
st20:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof20;
case 20:
	if ( (*( state.p)) == 101 )
		goto st21;
	goto st0;
st21:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof21;
case 21:
	switch( (*( state.p)) ) {
		case 13: goto tr37;
		case 32: goto tr37;
		case 59: goto tr38;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr37;
	goto st0;
tr37:
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st22;
tr57:
#line 173 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st22;
tr68:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
	goto st22;
tr87:
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st22;
tr93:
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st22;
tr103:
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st22;
tr109:
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st22;
tr113:
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st22;
tr127:
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st22;
tr134:
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st22;
tr145:
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st22;
tr151:
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st22;
tr157:
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st22;
tr170:
#line 163 "configparser.rl"
	{ spe.name = state.match; }
	goto st22;
tr387:
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st22;
tr392:
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st22;
tr398:
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st22;
tr406:
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st22;
tr410:
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st22;
tr416:
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st22;
tr423:
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st22;
tr786:
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st22;
tr794:
#line 180 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st22;
tr806:
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st22;
st22:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof22;
case 22:
#line 1194 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st22;
		case 32: goto st22;
		case 59: goto st579;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st22;
	goto st0;
tr38:
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st579;
tr60:
#line 173 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st579;
tr70:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
	goto st579;
tr88:
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st579;
tr94:
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st579;
tr104:
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st579;
tr110:
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st579;
tr114:
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st579;
tr128:
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st579;
tr135:
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st579;
tr146:
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st579;
tr152:
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st579;
tr158:
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st579;
tr171:
#line 163 "configparser.rl"
	{ spe.name = state.match; }
	goto st579;
tr388:
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st579;
tr393:
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st579;
tr399:
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st579;
tr407:
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st579;
tr411:
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st579;
tr417:
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st579;
tr424:
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st579;
tr788:
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st579;
tr795:
#line 180 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st579;
tr807:
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st579;
st579:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof579;
case 579:
#line 1303 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st14;
		case 32: goto st14;
		case 97: goto st15;
		case 99: goto st23;
		case 104: goto st46;
		case 105: goto st81;
		case 109: goto st99;
		case 110: goto st117;
		case 114: goto st552;
		case 115: goto st559;
		case 125: goto st565;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st14;
	goto st0;
st23:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof23;
case 23:
	switch( (*( state.p)) ) {
		case 108: goto st24;
		case 111: goto st40;
	}
	goto st0;
st24:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof24;
case 24:
	if ( (*( state.p)) == 117 )
		goto st25;
	goto st0;
st25:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof25;
case 25:
	if ( (*( state.p)) == 109 )
		goto st26;
	goto st0;
st26:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof26;
case 26:
	if ( (*( state.p)) == 112 )
		goto st27;
	goto st0;
st27:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof27;
case 27:
	if ( (*( state.p)) == 115 )
		goto st28;
	goto st0;
st28:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof28;
case 28:
	if ( (*( state.p)) == 105 )
		goto st29;
	goto st0;
st29:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof29;
case 29:
	if ( (*( state.p)) == 122 )
		goto st30;
	goto st0;
st30:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof30;
case 30:
	if ( (*( state.p)) == 101 )
		goto st31;
	goto st0;
st31:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof31;
case 31:
	switch( (*( state.p)) ) {
		case 13: goto st32;
		case 32: goto st32;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st32;
	goto st0;
st32:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof32;
case 32:
	switch( (*( state.p)) ) {
		case 13: goto st32;
		case 32: goto st32;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr51;
	} else if ( (*( state.p)) >= 9 )
		goto st32;
	goto st0;
tr51:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st33;
tr54:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st33;
st33:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof33;
case 33:
#line 1423 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr52;
		case 32: goto tr52;
		case 46: goto st38;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr54;
	} else if ( (*( state.p)) >= 9 )
		goto tr52;
	goto st0;
tr52:
#line 172 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st34;
st34:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof34;
case 34:
#line 1443 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st34;
		case 32: goto st34;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr56;
	} else if ( (*( state.p)) >= 9 )
		goto st34;
	goto st0;
tr56:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st35;
tr59:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st35;
st35:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof35;
case 35:
#line 1474 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr57;
		case 32: goto tr57;
		case 46: goto st36;
		case 59: goto tr60;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr59;
	} else if ( (*( state.p)) >= 9 )
		goto tr57;
	goto st0;
st36:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof36;
case 36:
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto st37;
	goto st0;
st37:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof37;
case 37:
	switch( (*( state.p)) ) {
		case 13: goto tr57;
		case 32: goto tr57;
		case 59: goto tr60;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto st37;
	} else if ( (*( state.p)) >= 9 )
		goto tr57;
	goto st0;
st38:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof38;
case 38:
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto st39;
	goto st0;
st39:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof39;
case 39:
	switch( (*( state.p)) ) {
		case 13: goto tr52;
		case 32: goto tr52;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto st39;
	} else if ( (*( state.p)) >= 9 )
		goto tr52;
	goto st0;
st40:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof40;
case 40:
	if ( (*( state.p)) == 117 )
		goto st41;
	goto st0;
st41:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof41;
case 41:
	if ( (*( state.p)) == 110 )
		goto st42;
	goto st0;
st42:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof42;
case 42:
	if ( (*( state.p)) == 116 )
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
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr67;
	} else if ( (*( state.p)) >= 9 )
		goto st44;
	goto st0;
tr67:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st45;
tr69:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st45;
st45:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof45;
case 45:
#line 1596 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr68;
		case 32: goto tr68;
		case 59: goto tr70;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr69;
	} else if ( (*( state.p)) >= 9 )
		goto tr68;
	goto st0;
st46:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof46;
case 46:
	if ( (*( state.p)) == 97 )
		goto st47;
	goto st0;
st47:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof47;
case 47:
	if ( (*( state.p)) == 98 )
		goto st48;
	goto st0;
st48:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof48;
case 48:
	if ( (*( state.p)) == 105 )
		goto st49;
	goto st0;
st49:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof49;
case 49:
	if ( (*( state.p)) == 116 )
		goto st50;
	goto st0;
st50:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof50;
case 50:
	if ( (*( state.p)) == 97 )
		goto st51;
	goto st0;
st51:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof51;
case 51:
	if ( (*( state.p)) == 116 )
		goto st52;
	goto st0;
st52:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof52;
case 52:
	switch( (*( state.p)) ) {
		case 13: goto st53;
		case 32: goto st53;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st53;
	goto st0;
st53:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof53;
case 53:
	switch( (*( state.p)) ) {
		case 13: goto st53;
		case 32: goto st53;
		case 99: goto st54;
		case 102: goto st60;
		case 115: goto st65;
		case 119: goto st74;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st53;
	goto st0;
st54:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof54;
case 54:
	if ( (*( state.p)) == 111 )
		goto st55;
	goto st0;
st55:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof55;
case 55:
	if ( (*( state.p)) == 114 )
		goto st56;
	goto st0;
st56:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof56;
case 56:
	if ( (*( state.p)) == 110 )
		goto st57;
	goto st0;
st57:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof57;
case 57:
	if ( (*( state.p)) == 101 )
		goto st58;
	goto st0;
st58:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof58;
case 58:
	if ( (*( state.p)) == 114 )
		goto st59;
	goto st0;
st59:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof59;
case 59:
	switch( (*( state.p)) ) {
		case 13: goto tr87;
		case 32: goto tr87;
		case 59: goto tr88;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr87;
	goto st0;
st60:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof60;
case 60:
	if ( (*( state.p)) == 108 )
		goto st61;
	goto st0;
st61:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof61;
case 61:
	if ( (*( state.p)) == 111 )
		goto st62;
	goto st0;
st62:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof62;
case 62:
	if ( (*( state.p)) == 111 )
		goto st63;
	goto st0;
st63:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof63;
case 63:
	if ( (*( state.p)) == 114 )
		goto st64;
	goto st0;
st64:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof64;
case 64:
	switch( (*( state.p)) ) {
		case 13: goto tr93;
		case 32: goto tr93;
		case 59: goto tr94;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr93;
	goto st0;
st65:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof65;
case 65:
	if ( (*( state.p)) == 104 )
		goto st66;
	goto st0;
st66:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof66;
case 66:
	if ( (*( state.p)) == 111 )
		goto st67;
	goto st0;
st67:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof67;
case 67:
	if ( (*( state.p)) == 114 )
		goto st68;
	goto st0;
st68:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof68;
case 68:
	if ( (*( state.p)) == 101 )
		goto st69;
	goto st0;
st69:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof69;
case 69:
	if ( (*( state.p)) == 108 )
		goto st70;
	goto st0;
st70:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof70;
case 70:
	if ( (*( state.p)) == 105 )
		goto st71;
	goto st0;
st71:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof71;
case 71:
	if ( (*( state.p)) == 110 )
		goto st72;
	goto st0;
st72:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof72;
case 72:
	if ( (*( state.p)) == 101 )
		goto st73;
	goto st0;
st73:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof73;
case 73:
	switch( (*( state.p)) ) {
		case 13: goto tr103;
		case 32: goto tr103;
		case 59: goto tr104;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr103;
	goto st0;
st74:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof74;
case 74:
	if ( (*( state.p)) == 97 )
		goto st75;
	goto st0;
st75:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof75;
case 75:
	switch( (*( state.p)) ) {
		case 108: goto st76;
		case 116: goto st78;
	}
	goto st0;
st76:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof76;
case 76:
	if ( (*( state.p)) == 107 )
		goto st77;
	goto st0;
st77:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof77;
case 77:
	switch( (*( state.p)) ) {
		case 13: goto tr109;
		case 32: goto tr109;
		case 59: goto tr110;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr109;
	goto st0;
st78:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof78;
case 78:
	if ( (*( state.p)) == 101 )
		goto st79;
	goto st0;
st79:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof79;
case 79:
	if ( (*( state.p)) == 114 )
		goto st80;
	goto st0;
st80:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof80;
case 80:
	switch( (*( state.p)) ) {
		case 13: goto tr113;
		case 32: goto tr113;
		case 59: goto tr114;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr113;
	goto st0;
st81:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof81;
case 81:
	if ( (*( state.p)) == 100 )
		goto st82;
	goto st0;
st82:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof82;
case 82:
	if ( (*( state.p)) == 108 )
		goto st83;
	goto st0;
st83:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof83;
case 83:
	if ( (*( state.p)) == 101 )
		goto st84;
	goto st0;
st84:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof84;
case 84:
	if ( (*( state.p)) == 95 )
		goto st85;
	goto st0;
st85:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof85;
case 85:
	if ( (*( state.p)) == 97 )
		goto st86;
	goto st0;
st86:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof86;
case 86:
	if ( (*( state.p)) == 105 )
		goto st87;
	goto st0;
st87:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof87;
case 87:
	switch( (*( state.p)) ) {
		case 13: goto st88;
		case 32: goto st88;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st88;
	goto st0;
st88:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof88;
case 88:
	switch( (*( state.p)) ) {
		case 13: goto st88;
		case 32: goto st88;
		case 110: goto st89;
		case 114: goto st93;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st88;
	goto st0;
st89:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof89;
case 89:
	if ( (*( state.p)) == 111 )
		goto st90;
	goto st0;
st90:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof90;
case 90:
	if ( (*( state.p)) == 110 )
		goto st91;
	goto st0;
st91:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof91;
case 91:
	if ( (*( state.p)) == 101 )
		goto st92;
	goto st0;
st92:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof92;
case 92:
	switch( (*( state.p)) ) {
		case 13: goto tr127;
		case 32: goto tr127;
		case 59: goto tr128;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr127;
	goto st0;
st93:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof93;
case 93:
	if ( (*( state.p)) == 97 )
		goto st94;
	goto st0;
st94:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof94;
case 94:
	if ( (*( state.p)) == 110 )
		goto st95;
	goto st0;
st95:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof95;
case 95:
	if ( (*( state.p)) == 100 )
		goto st96;
	goto st0;
st96:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof96;
case 96:
	if ( (*( state.p)) == 111 )
		goto st97;
	goto st0;
st97:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof97;
case 97:
	if ( (*( state.p)) == 109 )
		goto st98;
	goto st0;
st98:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof98;
case 98:
	switch( (*( state.p)) ) {
		case 13: goto tr134;
		case 32: goto tr134;
		case 59: goto tr135;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr134;
	goto st0;
st99:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof99;
case 99:
	if ( (*( state.p)) == 111 )
		goto st100;
	goto st0;
st100:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof100;
case 100:
	if ( (*( state.p)) == 118 )
		goto st101;
	goto st0;
st101:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof101;
case 101:
	if ( (*( state.p)) == 101 )
		goto st102;
	goto st0;
st102:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof102;
case 102:
	switch( (*( state.p)) ) {
		case 13: goto st103;
		case 32: goto st103;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st103;
	goto st0;
st103:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof103;
case 103:
	switch( (*( state.p)) ) {
		case 13: goto st103;
		case 32: goto st103;
		case 97: goto st104;
		case 102: goto st107;
		case 119: goto st112;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st103;
	goto st0;
st104:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof104;
case 104:
	if ( (*( state.p)) == 110 )
		goto st105;
	goto st0;
st105:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof105;
case 105:
	if ( (*( state.p)) == 121 )
		goto st106;
	goto st0;
st106:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof106;
case 106:
	switch( (*( state.p)) ) {
		case 13: goto tr145;
		case 32: goto tr145;
		case 59: goto tr146;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr145;
	goto st0;
st107:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof107;
case 107:
	if ( (*( state.p)) == 108 )
		goto st108;
	goto st0;
st108:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof108;
case 108:
	if ( (*( state.p)) == 111 )
		goto st109;
	goto st0;
st109:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof109;
case 109:
	if ( (*( state.p)) == 111 )
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
		case 13: goto tr151;
		case 32: goto tr151;
		case 59: goto tr152;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr151;
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
	if ( (*( state.p)) == 101 )
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
		case 13: goto tr157;
		case 32: goto tr157;
		case 59: goto tr158;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr157;
	goto st0;
st117:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof117;
case 117:
	if ( (*( state.p)) == 97 )
		goto st118;
	goto st0;
st118:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof118;
case 118:
	if ( (*( state.p)) == 109 )
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
	switch( (*( state.p)) ) {
		case 13: goto st121;
		case 32: goto st121;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st121;
	goto st0;
st121:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof121;
case 121:
	switch( (*( state.p)) ) {
		case 13: goto st121;
		case 32: goto st121;
		case 34: goto st122;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st121;
	goto st0;
st122:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof122;
case 122:
	switch( (*( state.p)) ) {
		case 34: goto tr165;
		case 92: goto tr166;
	}
	goto tr164;
tr164:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st123;
tr167:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st123;
st123:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof123;
case 123:
#line 2263 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
	}
	goto tr167;
tr165:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st124;
st124:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof124;
case 124:
#line 2279 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr170;
		case 32: goto tr170;
		case 59: goto tr171;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr170;
	goto st0;
tr166:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st125;
tr169:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st125;
st125:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof125;
case 125:
#line 2308 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr172;
		case 92: goto tr169;
	}
	goto tr167;
tr172:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st126;
st126:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof126;
case 126:
#line 2324 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr173;
		case 32: goto tr173;
		case 34: goto st124;
		case 59: goto tr174;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr173;
	goto tr167;
tr175:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st127;
tr173:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 163 "configparser.rl"
	{ spe.name = state.match; }
	goto st127;
tr194:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st127;
tr206:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st127;
tr224:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 173 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st127;
tr235:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st127;
tr254:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st127;
tr260:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st127;
tr270:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st127;
tr276:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st127;
tr280:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st127;
tr294:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st127;
tr301:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st127;
tr312:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st127;
tr318:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st127;
tr324:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st127;
tr331:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 163 "configparser.rl"
	{ spe.name = state.match; }
	goto st127;
tr339:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st127;
tr658:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st127;
tr663:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st127;
tr669:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st127;
tr677:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st127;
tr681:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st127;
tr687:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st127;
tr694:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st127;
tr778:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 180 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st127;
st127:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof127;
case 127:
#line 2549 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr175;
		case 32: goto tr175;
		case 34: goto st124;
		case 59: goto tr176;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr175;
	goto tr167;
tr176:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st580;
tr174:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 163 "configparser.rl"
	{ spe.name = state.match; }
	goto st580;
tr195:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st580;
tr207:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st580;
tr227:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 173 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st580;
tr237:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st580;
tr255:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st580;
tr261:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st580;
tr271:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st580;
tr277:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st580;
tr281:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st580;
tr295:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st580;
tr302:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st580;
tr313:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st580;
tr319:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st580;
tr325:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st580;
tr332:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 163 "configparser.rl"
	{ spe.name = state.match; }
	goto st580;
tr341:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st580;
tr659:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st580;
tr664:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st580;
tr670:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st580;
tr678:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st580;
tr682:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st580;
tr688:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st580;
tr695:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st580;
tr779:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 180 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st580;
st580:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof580;
case 580:
#line 2774 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr177;
		case 32: goto tr177;
		case 34: goto st124;
		case 92: goto tr169;
		case 97: goto tr178;
		case 99: goto tr179;
		case 104: goto tr180;
		case 105: goto tr181;
		case 109: goto tr182;
		case 110: goto tr183;
		case 114: goto tr184;
		case 115: goto tr185;
		case 125: goto tr186;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr177;
	goto tr167;
tr177:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st128;
st128:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof128;
case 128:
#line 2803 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr177;
		case 32: goto tr177;
		case 34: goto st124;
		case 92: goto tr169;
		case 97: goto tr178;
		case 99: goto tr179;
		case 104: goto tr180;
		case 105: goto tr181;
		case 109: goto tr182;
		case 110: goto tr183;
		case 114: goto tr184;
		case 115: goto tr185;
		case 125: goto tr186;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr177;
	goto tr167;
tr178:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st129;
st129:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof129;
case 129:
#line 2832 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 105: goto tr187;
	}
	goto tr167;
tr187:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st130;
st130:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof130;
case 130:
#line 2849 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr188;
		case 32: goto tr188;
		case 34: goto st124;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr188;
	goto tr167;
tr188:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st131;
st131:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof131;
case 131:
#line 2869 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr188;
		case 32: goto tr188;
		case 34: goto st124;
		case 92: goto tr169;
		case 110: goto tr189;
		case 115: goto tr190;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr188;
	goto tr167;
tr189:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st132;
st132:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof132;
case 132:
#line 2891 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 111: goto tr191;
	}
	goto tr167;
tr191:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st133;
st133:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof133;
case 133:
#line 2908 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 110: goto tr192;
	}
	goto tr167;
tr192:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st134;
st134:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof134;
case 134:
#line 2925 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr193;
	}
	goto tr167;
tr193:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st135;
st135:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof135;
case 135:
#line 2942 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr194;
		case 32: goto tr194;
		case 34: goto st124;
		case 59: goto tr195;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr194;
	goto tr167;
tr190:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st136;
st136:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof136;
case 136:
#line 2963 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr196;
	}
	goto tr167;
tr196:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st137;
st137:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof137;
case 137:
#line 2980 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr197;
	}
	goto tr167;
tr197:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st138;
st138:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof138;
case 138:
#line 2997 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 107: goto tr198;
	}
	goto tr167;
tr198:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st139;
st139:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof139;
case 139:
#line 3014 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 95: goto tr199;
	}
	goto tr167;
tr199:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st140;
st140:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof140;
case 140:
#line 3031 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 112: goto tr200;
	}
	goto tr167;
tr200:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st141;
st141:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof141;
case 141:
#line 3048 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 108: goto tr201;
	}
	goto tr167;
tr201:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st142;
st142:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof142;
case 142:
#line 3065 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 97: goto tr202;
	}
	goto tr167;
tr202:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st143;
st143:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof143;
case 143:
#line 3082 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 121: goto tr203;
	}
	goto tr167;
tr203:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st144;
st144:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof144;
case 144:
#line 3099 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr204;
	}
	goto tr167;
tr204:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st145;
st145:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof145;
case 145:
#line 3116 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 114: goto tr205;
	}
	goto tr167;
tr205:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st146;
st146:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof146;
case 146:
#line 3133 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr206;
		case 32: goto tr206;
		case 34: goto st124;
		case 59: goto tr207;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr206;
	goto tr167;
tr179:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st147;
st147:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof147;
case 147:
#line 3154 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 108: goto tr208;
		case 111: goto tr209;
	}
	goto tr167;
tr208:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st148;
st148:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof148;
case 148:
#line 3172 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 117: goto tr210;
	}
	goto tr167;
tr210:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st149;
st149:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof149;
case 149:
#line 3189 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 109: goto tr211;
	}
	goto tr167;
tr211:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st150;
st150:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof150;
case 150:
#line 3206 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 112: goto tr212;
	}
	goto tr167;
tr212:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st151;
st151:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof151;
case 151:
#line 3223 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 115: goto tr213;
	}
	goto tr167;
tr213:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st152;
st152:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof152;
case 152:
#line 3240 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 105: goto tr214;
	}
	goto tr167;
tr214:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st153;
st153:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof153;
case 153:
#line 3257 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 122: goto tr215;
	}
	goto tr167;
tr215:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st154;
st154:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof154;
case 154:
#line 3274 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr216;
	}
	goto tr167;
tr216:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st155;
st155:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof155;
case 155:
#line 3291 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr217;
		case 32: goto tr217;
		case 34: goto st124;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr217;
	goto tr167;
tr217:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st156;
st156:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof156;
case 156:
#line 3311 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr217;
		case 32: goto tr217;
		case 34: goto st124;
		case 92: goto tr169;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr218;
	} else if ( (*( state.p)) >= 9 )
		goto tr217;
	goto tr167;
tr221:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st157;
tr218:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st157;
st157:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof157;
case 157:
#line 3344 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr219;
		case 32: goto tr219;
		case 34: goto st124;
		case 46: goto tr220;
		case 92: goto tr169;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr221;
	} else if ( (*( state.p)) >= 9 )
		goto tr219;
	goto tr167;
tr222:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st158;
tr219:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 172 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st158;
st158:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof158;
case 158:
#line 3376 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr222;
		case 32: goto tr222;
		case 34: goto st124;
		case 92: goto tr169;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr223;
	} else if ( (*( state.p)) >= 9 )
		goto tr222;
	goto tr167;
tr226:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st159;
tr223:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st159;
st159:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof159;
case 159:
#line 3409 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr224;
		case 32: goto tr224;
		case 34: goto st124;
		case 46: goto tr225;
		case 59: goto tr227;
		case 92: goto tr169;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr226;
	} else if ( (*( state.p)) >= 9 )
		goto tr224;
	goto tr167;
tr225:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st160;
st160:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof160;
case 160:
#line 3434 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr228;
	goto tr167;
tr228:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st161;
st161:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof161;
case 161:
#line 3452 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr224;
		case 32: goto tr224;
		case 34: goto st124;
		case 59: goto tr227;
		case 92: goto tr169;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr228;
	} else if ( (*( state.p)) >= 9 )
		goto tr224;
	goto tr167;
tr220:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st162;
st162:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof162;
case 162:
#line 3476 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr229;
	goto tr167;
tr229:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st163;
st163:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof163;
case 163:
#line 3494 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr219;
		case 32: goto tr219;
		case 34: goto st124;
		case 92: goto tr169;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr229;
	} else if ( (*( state.p)) >= 9 )
		goto tr219;
	goto tr167;
tr209:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st164;
st164:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof164;
case 164:
#line 3517 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 117: goto tr230;
	}
	goto tr167;
tr230:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st165;
st165:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof165;
case 165:
#line 3534 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 110: goto tr231;
	}
	goto tr167;
tr231:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st166;
st166:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof166;
case 166:
#line 3551 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 116: goto tr232;
	}
	goto tr167;
tr232:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st167;
st167:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof167;
case 167:
#line 3568 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr233;
		case 32: goto tr233;
		case 34: goto st124;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr233;
	goto tr167;
tr233:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st168;
st168:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof168;
case 168:
#line 3588 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr233;
		case 32: goto tr233;
		case 34: goto st124;
		case 92: goto tr169;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr234;
	} else if ( (*( state.p)) >= 9 )
		goto tr233;
	goto tr167;
tr234:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st169;
tr236:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st169;
st169:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof169;
case 169:
#line 3621 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr235;
		case 32: goto tr235;
		case 34: goto st124;
		case 59: goto tr237;
		case 92: goto tr169;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr236;
	} else if ( (*( state.p)) >= 9 )
		goto tr235;
	goto tr167;
tr180:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st170;
st170:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof170;
case 170:
#line 3645 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 97: goto tr238;
	}
	goto tr167;
tr238:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st171;
st171:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof171;
case 171:
#line 3662 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 98: goto tr239;
	}
	goto tr167;
tr239:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st172;
st172:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof172;
case 172:
#line 3679 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 105: goto tr240;
	}
	goto tr167;
tr240:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st173;
st173:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof173;
case 173:
#line 3696 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 116: goto tr241;
	}
	goto tr167;
tr241:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st174;
st174:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof174;
case 174:
#line 3713 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 97: goto tr242;
	}
	goto tr167;
tr242:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st175;
st175:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof175;
case 175:
#line 3730 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 116: goto tr243;
	}
	goto tr167;
tr243:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st176;
st176:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof176;
case 176:
#line 3747 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr244;
		case 32: goto tr244;
		case 34: goto st124;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr244;
	goto tr167;
tr244:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st177;
st177:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof177;
case 177:
#line 3767 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr244;
		case 32: goto tr244;
		case 34: goto st124;
		case 92: goto tr169;
		case 99: goto tr245;
		case 102: goto tr246;
		case 115: goto tr247;
		case 119: goto tr248;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr244;
	goto tr167;
tr245:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st178;
st178:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof178;
case 178:
#line 3791 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 111: goto tr249;
	}
	goto tr167;
tr249:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st179;
st179:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof179;
case 179:
#line 3808 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 114: goto tr250;
	}
	goto tr167;
tr250:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st180;
st180:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof180;
case 180:
#line 3825 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 110: goto tr251;
	}
	goto tr167;
tr251:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st181;
st181:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof181;
case 181:
#line 3842 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr252;
	}
	goto tr167;
tr252:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st182;
st182:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof182;
case 182:
#line 3859 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 114: goto tr253;
	}
	goto tr167;
tr253:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st183;
st183:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof183;
case 183:
#line 3876 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr254;
		case 32: goto tr254;
		case 34: goto st124;
		case 59: goto tr255;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr254;
	goto tr167;
tr246:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st184;
st184:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof184;
case 184:
#line 3897 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 108: goto tr256;
	}
	goto tr167;
tr256:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st185;
st185:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof185;
case 185:
#line 3914 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 111: goto tr257;
	}
	goto tr167;
tr257:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st186;
st186:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof186;
case 186:
#line 3931 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 111: goto tr258;
	}
	goto tr167;
tr258:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st187;
st187:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof187;
case 187:
#line 3948 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 114: goto tr259;
	}
	goto tr167;
tr259:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st188;
st188:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof188;
case 188:
#line 3965 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr260;
		case 32: goto tr260;
		case 34: goto st124;
		case 59: goto tr261;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr260;
	goto tr167;
tr247:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st189;
st189:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof189;
case 189:
#line 3986 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 104: goto tr262;
	}
	goto tr167;
tr262:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st190;
st190:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof190;
case 190:
#line 4003 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 111: goto tr263;
	}
	goto tr167;
tr263:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st191;
st191:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof191;
case 191:
#line 4020 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 114: goto tr264;
	}
	goto tr167;
tr264:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st192;
st192:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof192;
case 192:
#line 4037 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr265;
	}
	goto tr167;
tr265:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st193;
st193:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof193;
case 193:
#line 4054 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 108: goto tr266;
	}
	goto tr167;
tr266:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st194;
st194:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof194;
case 194:
#line 4071 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 105: goto tr267;
	}
	goto tr167;
tr267:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st195;
st195:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof195;
case 195:
#line 4088 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 110: goto tr268;
	}
	goto tr167;
tr268:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st196;
st196:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof196;
case 196:
#line 4105 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr269;
	}
	goto tr167;
tr269:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st197;
st197:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof197;
case 197:
#line 4122 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr270;
		case 32: goto tr270;
		case 34: goto st124;
		case 59: goto tr271;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr270;
	goto tr167;
tr248:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st198;
st198:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof198;
case 198:
#line 4143 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 97: goto tr272;
	}
	goto tr167;
tr272:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st199;
st199:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof199;
case 199:
#line 4160 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 108: goto tr273;
		case 116: goto tr274;
	}
	goto tr167;
tr273:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st200;
st200:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof200;
case 200:
#line 4178 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 107: goto tr275;
	}
	goto tr167;
tr275:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st201;
st201:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof201;
case 201:
#line 4195 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr276;
		case 32: goto tr276;
		case 34: goto st124;
		case 59: goto tr277;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr276;
	goto tr167;
tr274:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st202;
st202:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof202;
case 202:
#line 4216 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr278;
	}
	goto tr167;
tr278:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st203;
st203:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof203;
case 203:
#line 4233 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 114: goto tr279;
	}
	goto tr167;
tr279:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st204;
st204:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof204;
case 204:
#line 4250 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr280;
		case 32: goto tr280;
		case 34: goto st124;
		case 59: goto tr281;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr280;
	goto tr167;
tr181:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st205;
st205:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof205;
case 205:
#line 4271 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 100: goto tr282;
	}
	goto tr167;
tr282:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st206;
st206:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof206;
case 206:
#line 4288 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 108: goto tr283;
	}
	goto tr167;
tr283:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st207;
st207:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof207;
case 207:
#line 4305 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr284;
	}
	goto tr167;
tr284:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st208;
st208:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof208;
case 208:
#line 4322 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 95: goto tr285;
	}
	goto tr167;
tr285:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st209;
st209:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof209;
case 209:
#line 4339 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 97: goto tr286;
	}
	goto tr167;
tr286:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st210;
st210:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof210;
case 210:
#line 4356 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 105: goto tr287;
	}
	goto tr167;
tr287:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st211;
st211:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof211;
case 211:
#line 4373 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr288;
		case 32: goto tr288;
		case 34: goto st124;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr288;
	goto tr167;
tr288:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st212;
st212:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof212;
case 212:
#line 4393 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr288;
		case 32: goto tr288;
		case 34: goto st124;
		case 92: goto tr169;
		case 110: goto tr289;
		case 114: goto tr290;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr288;
	goto tr167;
tr289:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st213;
st213:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof213;
case 213:
#line 4415 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 111: goto tr291;
	}
	goto tr167;
tr291:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st214;
st214:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof214;
case 214:
#line 4432 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 110: goto tr292;
	}
	goto tr167;
tr292:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st215;
st215:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof215;
case 215:
#line 4449 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr293;
	}
	goto tr167;
tr293:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st216;
st216:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof216;
case 216:
#line 4466 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr294;
		case 32: goto tr294;
		case 34: goto st124;
		case 59: goto tr295;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr294;
	goto tr167;
tr290:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st217;
st217:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof217;
case 217:
#line 4487 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 97: goto tr296;
	}
	goto tr167;
tr296:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st218;
st218:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof218;
case 218:
#line 4504 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 110: goto tr297;
	}
	goto tr167;
tr297:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st219;
st219:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof219;
case 219:
#line 4521 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 100: goto tr298;
	}
	goto tr167;
tr298:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st220;
st220:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof220;
case 220:
#line 4538 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 111: goto tr299;
	}
	goto tr167;
tr299:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st221;
st221:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof221;
case 221:
#line 4555 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 109: goto tr300;
	}
	goto tr167;
tr300:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st222;
st222:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof222;
case 222:
#line 4572 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr301;
		case 32: goto tr301;
		case 34: goto st124;
		case 59: goto tr302;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr301;
	goto tr167;
tr182:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st223;
st223:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof223;
case 223:
#line 4593 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 111: goto tr303;
	}
	goto tr167;
tr303:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st224;
st224:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof224;
case 224:
#line 4610 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 118: goto tr304;
	}
	goto tr167;
tr304:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st225;
st225:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof225;
case 225:
#line 4627 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr305;
	}
	goto tr167;
tr305:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st226;
st226:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof226;
case 226:
#line 4644 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr306;
		case 32: goto tr306;
		case 34: goto st124;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr306;
	goto tr167;
tr306:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st227;
st227:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof227;
case 227:
#line 4664 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr306;
		case 32: goto tr306;
		case 34: goto st124;
		case 92: goto tr169;
		case 97: goto tr307;
		case 102: goto tr308;
		case 119: goto tr309;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr306;
	goto tr167;
tr307:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st228;
st228:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof228;
case 228:
#line 4687 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 110: goto tr310;
	}
	goto tr167;
tr310:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st229;
st229:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof229;
case 229:
#line 4704 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 121: goto tr311;
	}
	goto tr167;
tr311:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st230;
st230:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof230;
case 230:
#line 4721 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr312;
		case 32: goto tr312;
		case 34: goto st124;
		case 59: goto tr313;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr312;
	goto tr167;
tr308:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st231;
st231:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof231;
case 231:
#line 4742 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 108: goto tr314;
	}
	goto tr167;
tr314:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st232;
st232:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof232;
case 232:
#line 4759 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 111: goto tr315;
	}
	goto tr167;
tr315:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st233;
st233:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof233;
case 233:
#line 4776 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 111: goto tr316;
	}
	goto tr167;
tr316:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st234;
st234:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof234;
case 234:
#line 4793 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 114: goto tr317;
	}
	goto tr167;
tr317:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st235;
st235:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof235;
case 235:
#line 4810 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr318;
		case 32: goto tr318;
		case 34: goto st124;
		case 59: goto tr319;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr318;
	goto tr167;
tr309:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st236;
st236:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof236;
case 236:
#line 4831 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 97: goto tr320;
	}
	goto tr167;
tr320:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st237;
st237:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof237;
case 237:
#line 4848 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 116: goto tr321;
	}
	goto tr167;
tr321:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st238;
st238:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof238;
case 238:
#line 4865 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr322;
	}
	goto tr167;
tr322:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st239;
st239:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof239;
case 239:
#line 4882 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 114: goto tr323;
	}
	goto tr167;
tr323:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st240;
st240:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof240;
case 240:
#line 4899 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr324;
		case 32: goto tr324;
		case 34: goto st124;
		case 59: goto tr325;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr324;
	goto tr167;
tr183:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st241;
st241:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof241;
case 241:
#line 4920 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 97: goto tr326;
	}
	goto tr167;
tr326:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st242;
st242:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof242;
case 242:
#line 4937 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 109: goto tr327;
	}
	goto tr167;
tr327:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st243;
st243:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof243;
case 243:
#line 4954 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr328;
	}
	goto tr167;
tr328:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st244;
st244:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof244;
case 244:
#line 4971 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr329;
		case 32: goto tr329;
		case 34: goto st124;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr329;
	goto tr167;
tr329:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st245;
st245:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof245;
case 245:
#line 4991 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr329;
		case 32: goto tr329;
		case 34: goto st246;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr329;
	goto tr167;
st246:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof246;
case 246:
	switch( (*( state.p)) ) {
		case 13: goto tr331;
		case 32: goto tr331;
		case 34: goto tr165;
		case 59: goto tr332;
		case 92: goto tr166;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr331;
	goto tr164;
tr184:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st247;
st247:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof247;
case 247:
#line 5025 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 97: goto tr333;
	}
	goto tr167;
tr333:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st248;
st248:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof248;
case 248:
#line 5042 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 110: goto tr334;
	}
	goto tr167;
tr334:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st249;
st249:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof249;
case 249:
#line 5059 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 103: goto tr335;
	}
	goto tr167;
tr335:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st250;
st250:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof250;
case 250:
#line 5076 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr336;
	}
	goto tr167;
tr336:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st251;
st251:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof251;
case 251:
#line 5093 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr337;
		case 32: goto tr337;
		case 34: goto st124;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr337;
	goto tr167;
tr337:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st252;
st252:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof252;
case 252:
#line 5113 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr337;
		case 32: goto tr337;
		case 34: goto st124;
		case 92: goto tr169;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr338;
	} else if ( (*( state.p)) >= 9 )
		goto tr337;
	goto tr167;
tr340:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st253;
tr338:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st253;
st253:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof253;
case 253:
#line 5146 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr339;
		case 32: goto tr339;
		case 34: goto st124;
		case 59: goto tr341;
		case 92: goto tr169;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr340;
	} else if ( (*( state.p)) >= 9 )
		goto tr339;
	goto tr167;
tr185:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st254;
st254:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof254;
case 254:
#line 5170 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 107: goto tr342;
	}
	goto tr167;
tr342:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st255;
st255:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof255;
case 255:
#line 5187 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 105: goto tr343;
	}
	goto tr167;
tr343:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st256;
st256:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof256;
case 256:
#line 5204 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 110: goto tr344;
	}
	goto tr167;
tr344:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st257;
st257:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof257;
case 257:
#line 5221 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr345;
		case 32: goto tr345;
		case 34: goto st124;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr345;
	goto tr167;
tr345:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st258;
st258:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof258;
case 258:
#line 5241 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr345;
		case 32: goto tr345;
		case 34: goto st259;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr345;
	goto tr167;
st259:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof259;
case 259:
	switch( (*( state.p)) ) {
		case 13: goto tr348;
		case 32: goto tr348;
		case 34: goto tr349;
		case 59: goto tr350;
		case 92: goto tr351;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr348;
	goto tr347;
tr347:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st260;
tr352:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st260;
st260:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof260;
case 260:
#line 5285 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
	}
	goto tr352;
tr349:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st261;
st261:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof261;
case 261:
#line 5301 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr355;
		case 32: goto tr355;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr355;
	goto st0;
tr355:
#line 140 "configparser.rl"
	{ spe.skin.text = state.match; }
	goto st262;
st262:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof262;
case 262:
#line 5317 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st262;
		case 32: goto st262;
		case 98: goto st263;
		case 100: goto st307;
		case 110: goto st310;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st262;
	goto st0;
st263:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof263;
case 263:
	if ( (*( state.p)) == 114 )
		goto st264;
	goto st0;
st264:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof264;
case 264:
	if ( (*( state.p)) == 105 )
		goto st265;
	goto st0;
st265:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof265;
case 265:
	if ( (*( state.p)) == 103 )
		goto st266;
	goto st0;
st266:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof266;
case 266:
	if ( (*( state.p)) == 104 )
		goto st267;
	goto st0;
st267:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof267;
case 267:
	if ( (*( state.p)) == 116 )
		goto st268;
	goto st0;
st268:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof268;
case 268:
	switch( (*( state.p)) ) {
		case 13: goto tr365;
		case 32: goto tr365;
		case 95: goto tr366;
		case 98: goto tr367;
		case 99: goto tr368;
		case 103: goto tr369;
		case 109: goto tr370;
		case 114: goto tr371;
		case 119: goto tr372;
		case 121: goto tr373;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr365;
	goto st0;
tr365:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st269;
tr427:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st269;
st269:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof269;
case 269:
#line 5394 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st269;
		case 32: goto st269;
		case 98: goto st270;
		case 99: goto st276;
		case 103: goto st280;
		case 109: goto st285;
		case 114: goto st292;
		case 119: goto st295;
		case 121: goto st300;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st269;
	goto st0;
tr367:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st270;
tr429:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st270;
st270:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof270;
case 270:
#line 5421 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st271;
	goto st0;
st271:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof271;
case 271:
	switch( (*( state.p)) ) {
		case 97: goto st272;
		case 117: goto st274;
	}
	goto st0;
st272:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof272;
case 272:
	if ( (*( state.p)) == 99 )
		goto st273;
	goto st0;
st273:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof273;
case 273:
	if ( (*( state.p)) == 107 )
		goto st22;
	goto st0;
st274:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof274;
case 274:
	if ( (*( state.p)) == 101 )
		goto st275;
	goto st0;
st275:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof275;
case 275:
	switch( (*( state.p)) ) {
		case 13: goto tr387;
		case 32: goto tr387;
		case 59: goto tr388;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr387;
	goto st0;
tr368:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st276;
tr430:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st276;
st276:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof276;
case 276:
#line 5479 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st277;
	goto st0;
st277:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof277;
case 277:
	if ( (*( state.p)) == 97 )
		goto st278;
	goto st0;
st278:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof278;
case 278:
	if ( (*( state.p)) == 110 )
		goto st279;
	goto st0;
st279:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof279;
case 279:
	switch( (*( state.p)) ) {
		case 13: goto tr392;
		case 32: goto tr392;
		case 59: goto tr393;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr392;
	goto st0;
tr369:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st280;
tr431:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st280;
st280:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof280;
case 280:
#line 5521 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st281;
	goto st0;
st281:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof281;
case 281:
	if ( (*( state.p)) == 101 )
		goto st282;
	goto st0;
st282:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof282;
case 282:
	if ( (*( state.p)) == 101 )
		goto st283;
	goto st0;
st283:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof283;
case 283:
	if ( (*( state.p)) == 110 )
		goto st284;
	goto st0;
st284:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof284;
case 284:
	switch( (*( state.p)) ) {
		case 13: goto tr398;
		case 32: goto tr398;
		case 59: goto tr399;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr398;
	goto st0;
tr370:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st285;
tr432:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st285;
st285:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof285;
case 285:
#line 5570 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st286;
	goto st0;
st286:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof286;
case 286:
	if ( (*( state.p)) == 103 )
		goto st287;
	goto st0;
st287:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof287;
case 287:
	if ( (*( state.p)) == 101 )
		goto st288;
	goto st0;
st288:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof288;
case 288:
	if ( (*( state.p)) == 110 )
		goto st289;
	goto st0;
st289:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof289;
case 289:
	if ( (*( state.p)) == 116 )
		goto st290;
	goto st0;
st290:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof290;
case 290:
	if ( (*( state.p)) == 97 )
		goto st291;
	goto st0;
st291:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof291;
case 291:
	switch( (*( state.p)) ) {
		case 13: goto tr406;
		case 32: goto tr406;
		case 59: goto tr407;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr406;
	goto st0;
tr371:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st292;
tr433:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st292;
st292:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof292;
case 292:
#line 5633 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st293;
	goto st0;
st293:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof293;
case 293:
	if ( (*( state.p)) == 100 )
		goto st294;
	goto st0;
st294:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof294;
case 294:
	switch( (*( state.p)) ) {
		case 13: goto tr410;
		case 32: goto tr410;
		case 59: goto tr411;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr410;
	goto st0;
tr372:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st295;
tr434:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st295;
st295:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof295;
case 295:
#line 5668 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st296;
	goto st0;
st296:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof296;
case 296:
	if ( (*( state.p)) == 105 )
		goto st297;
	goto st0;
st297:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof297;
case 297:
	if ( (*( state.p)) == 116 )
		goto st298;
	goto st0;
st298:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof298;
case 298:
	if ( (*( state.p)) == 101 )
		goto st299;
	goto st0;
st299:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof299;
case 299:
	switch( (*( state.p)) ) {
		case 13: goto tr416;
		case 32: goto tr416;
		case 59: goto tr417;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr416;
	goto st0;
tr373:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st300;
tr435:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st300;
st300:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof300;
case 300:
#line 5717 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st301;
	goto st0;
st301:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof301;
case 301:
	if ( (*( state.p)) == 108 )
		goto st302;
	goto st0;
st302:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof302;
case 302:
	if ( (*( state.p)) == 108 )
		goto st303;
	goto st0;
st303:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof303;
case 303:
	if ( (*( state.p)) == 111 )
		goto st304;
	goto st0;
st304:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof304;
case 304:
	if ( (*( state.p)) == 119 )
		goto st305;
	goto st0;
st305:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof305;
case 305:
	switch( (*( state.p)) ) {
		case 13: goto tr423;
		case 32: goto tr423;
		case 59: goto tr424;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr423;
	goto st0;
tr366:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st306;
tr428:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st306;
st306:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof306;
case 306:
#line 5773 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st270;
		case 99: goto st276;
		case 103: goto st280;
		case 109: goto st285;
		case 114: goto st292;
		case 119: goto st295;
		case 121: goto st300;
	}
	goto st0;
st307:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof307;
case 307:
	if ( (*( state.p)) == 105 )
		goto st308;
	goto st0;
st308:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof308;
case 308:
	if ( (*( state.p)) == 109 )
		goto st309;
	goto st0;
st309:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof309;
case 309:
	switch( (*( state.p)) ) {
		case 13: goto tr427;
		case 32: goto tr427;
		case 95: goto tr428;
		case 98: goto tr429;
		case 99: goto tr430;
		case 103: goto tr431;
		case 109: goto tr432;
		case 114: goto tr433;
		case 119: goto tr434;
		case 121: goto tr435;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr427;
	goto st0;
st310:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof310;
case 310:
	if ( (*( state.p)) == 111 )
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
	if ( (*( state.p)) == 101 )
		goto st22;
	goto st0;
tr351:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st313;
tr354:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st313;
st313:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof313;
case 313:
#line 5858 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr438;
		case 92: goto tr354;
	}
	goto tr352;
tr438:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st314;
st314:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof314;
case 314:
#line 5874 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr439;
		case 32: goto tr439;
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr439;
	goto tr352;
tr440:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st315;
tr439:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 140 "configparser.rl"
	{ spe.skin.text = state.match; }
	goto st315;
tr723:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 140 "configparser.rl"
	{ spe.skin.text = state.match; }
	goto st315;
st315:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof315;
case 315:
#line 5914 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr440;
		case 32: goto tr440;
		case 34: goto st261;
		case 92: goto tr354;
		case 98: goto tr441;
		case 100: goto tr442;
		case 110: goto tr443;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr440;
	goto tr352;
tr441:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st316;
st316:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof316;
case 316:
#line 5937 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 114: goto tr444;
	}
	goto tr352;
tr444:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st317;
st317:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof317;
case 317:
#line 5954 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 105: goto tr445;
	}
	goto tr352;
tr445:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st318;
st318:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof318;
case 318:
#line 5971 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 103: goto tr446;
	}
	goto tr352;
tr446:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st319;
st319:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof319;
case 319:
#line 5988 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 104: goto tr447;
	}
	goto tr352;
tr447:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st320;
st320:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof320;
case 320:
#line 6005 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 116: goto tr448;
	}
	goto tr352;
tr448:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st321;
st321:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof321;
case 321:
#line 6022 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr449;
		case 32: goto tr449;
		case 34: goto st261;
		case 92: goto tr354;
		case 95: goto tr450;
		case 98: goto tr451;
		case 99: goto tr452;
		case 103: goto tr453;
		case 109: goto tr454;
		case 114: goto tr455;
		case 119: goto tr456;
		case 121: goto tr457;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr449;
	goto tr352;
tr458:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st322;
tr449:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st322;
tr767:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st322;
st322:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof322;
case 322:
#line 6066 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr458;
		case 32: goto tr458;
		case 34: goto st261;
		case 92: goto tr354;
		case 98: goto tr459;
		case 99: goto tr460;
		case 103: goto tr461;
		case 109: goto tr462;
		case 114: goto tr463;
		case 119: goto tr464;
		case 121: goto tr465;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr458;
	goto tr352;
tr459:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st323;
tr451:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st323;
tr769:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st323;
st323:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof323;
case 323:
#line 6109 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 108: goto tr466;
	}
	goto tr352;
tr466:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st324;
st324:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof324;
case 324:
#line 6126 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 97: goto tr467;
		case 117: goto tr468;
	}
	goto tr352;
tr467:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st325;
st325:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof325;
case 325:
#line 6144 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 99: goto tr469;
	}
	goto tr352;
tr469:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st326;
st326:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof326;
case 326:
#line 6161 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 107: goto tr470;
	}
	goto tr352;
tr470:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st327;
tr489:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st327;
tr501:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st327;
tr519:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 173 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st327;
tr530:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st327;
tr549:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st327;
tr555:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st327;
tr565:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st327;
tr571:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st327;
tr575:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st327;
tr589:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st327;
tr596:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st327;
tr607:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st327;
tr613:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st327;
tr619:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st327;
tr715:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st327;
tr348:
#line 163 "configparser.rl"
	{ spe.name = state.match; }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st327;
tr727:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st327;
tr732:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st327;
tr738:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st327;
tr746:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st327;
tr750:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st327;
tr756:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st327;
tr763:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st327;
tr724:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 180 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st327;
st327:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof327;
case 327:
#line 6374 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr470;
		case 32: goto tr470;
		case 34: goto st261;
		case 59: goto tr471;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr470;
	goto tr352;
tr471:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st581;
tr490:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st581;
tr502:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st581;
tr522:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 173 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st581;
tr532:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st581;
tr550:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st581;
tr556:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st581;
tr566:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st581;
tr572:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st581;
tr576:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st581;
tr590:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st581;
tr597:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st581;
tr608:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st581;
tr614:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st581;
tr620:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st581;
tr717:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st581;
tr350:
#line 163 "configparser.rl"
	{ spe.name = state.match; }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st581;
tr728:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st581;
tr733:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st581;
tr739:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st581;
tr747:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st581;
tr751:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st581;
tr757:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st581;
tr764:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st581;
tr725:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 180 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st581;
st581:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof581;
case 581:
#line 6591 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr472;
		case 32: goto tr472;
		case 34: goto st261;
		case 92: goto tr354;
		case 97: goto tr473;
		case 99: goto tr474;
		case 104: goto tr475;
		case 105: goto tr476;
		case 109: goto tr477;
		case 110: goto tr478;
		case 114: goto tr479;
		case 115: goto tr480;
		case 125: goto tr481;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr472;
	goto tr352;
tr472:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st328;
st328:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof328;
case 328:
#line 6620 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr472;
		case 32: goto tr472;
		case 34: goto st261;
		case 92: goto tr354;
		case 97: goto tr473;
		case 99: goto tr474;
		case 104: goto tr475;
		case 105: goto tr476;
		case 109: goto tr477;
		case 110: goto tr478;
		case 114: goto tr479;
		case 115: goto tr480;
		case 125: goto tr481;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr472;
	goto tr352;
tr473:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st329;
st329:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof329;
case 329:
#line 6649 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 105: goto tr482;
	}
	goto tr352;
tr482:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st330;
st330:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof330;
case 330:
#line 6666 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr483;
		case 32: goto tr483;
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr483;
	goto tr352;
tr483:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st331;
st331:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof331;
case 331:
#line 6686 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr483;
		case 32: goto tr483;
		case 34: goto st261;
		case 92: goto tr354;
		case 110: goto tr484;
		case 115: goto tr485;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr483;
	goto tr352;
tr484:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st332;
st332:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof332;
case 332:
#line 6708 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 111: goto tr486;
	}
	goto tr352;
tr486:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st333;
st333:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof333;
case 333:
#line 6725 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 110: goto tr487;
	}
	goto tr352;
tr487:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st334;
st334:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof334;
case 334:
#line 6742 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr488;
	}
	goto tr352;
tr488:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st335;
st335:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof335;
case 335:
#line 6759 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr489;
		case 32: goto tr489;
		case 34: goto st261;
		case 59: goto tr490;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr489;
	goto tr352;
tr485:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st336;
st336:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof336;
case 336:
#line 6780 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr491;
	}
	goto tr352;
tr491:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st337;
st337:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof337;
case 337:
#line 6797 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr492;
	}
	goto tr352;
tr492:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st338;
st338:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof338;
case 338:
#line 6814 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 107: goto tr493;
	}
	goto tr352;
tr493:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st339;
st339:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof339;
case 339:
#line 6831 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 95: goto tr494;
	}
	goto tr352;
tr494:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st340;
st340:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof340;
case 340:
#line 6848 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 112: goto tr495;
	}
	goto tr352;
tr495:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st341;
st341:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof341;
case 341:
#line 6865 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 108: goto tr496;
	}
	goto tr352;
tr496:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st342;
st342:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof342;
case 342:
#line 6882 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 97: goto tr497;
	}
	goto tr352;
tr497:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st343;
st343:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof343;
case 343:
#line 6899 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 121: goto tr498;
	}
	goto tr352;
tr498:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st344;
st344:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof344;
case 344:
#line 6916 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr499;
	}
	goto tr352;
tr499:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st345;
st345:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof345;
case 345:
#line 6933 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 114: goto tr500;
	}
	goto tr352;
tr500:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st346;
st346:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof346;
case 346:
#line 6950 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr501;
		case 32: goto tr501;
		case 34: goto st261;
		case 59: goto tr502;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr501;
	goto tr352;
tr474:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st347;
st347:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof347;
case 347:
#line 6971 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 108: goto tr503;
		case 111: goto tr504;
	}
	goto tr352;
tr503:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st348;
st348:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof348;
case 348:
#line 6989 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 117: goto tr505;
	}
	goto tr352;
tr505:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st349;
st349:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof349;
case 349:
#line 7006 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 109: goto tr506;
	}
	goto tr352;
tr506:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st350;
st350:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof350;
case 350:
#line 7023 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 112: goto tr507;
	}
	goto tr352;
tr507:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st351;
st351:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof351;
case 351:
#line 7040 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 115: goto tr508;
	}
	goto tr352;
tr508:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st352;
st352:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof352;
case 352:
#line 7057 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 105: goto tr509;
	}
	goto tr352;
tr509:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st353;
st353:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof353;
case 353:
#line 7074 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 122: goto tr510;
	}
	goto tr352;
tr510:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st354;
st354:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof354;
case 354:
#line 7091 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr511;
	}
	goto tr352;
tr511:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st355;
st355:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof355;
case 355:
#line 7108 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr512;
		case 32: goto tr512;
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr512;
	goto tr352;
tr512:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st356;
st356:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof356;
case 356:
#line 7128 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr512;
		case 32: goto tr512;
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr513;
	} else if ( (*( state.p)) >= 9 )
		goto tr512;
	goto tr352;
tr516:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st357;
tr513:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st357;
st357:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof357;
case 357:
#line 7161 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr514;
		case 32: goto tr514;
		case 34: goto st261;
		case 46: goto tr515;
		case 92: goto tr354;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr516;
	} else if ( (*( state.p)) >= 9 )
		goto tr514;
	goto tr352;
tr517:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st358;
tr514:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 172 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st358;
st358:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof358;
case 358:
#line 7193 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr517;
		case 32: goto tr517;
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr518;
	} else if ( (*( state.p)) >= 9 )
		goto tr517;
	goto tr352;
tr521:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st359;
tr518:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st359;
st359:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof359;
case 359:
#line 7226 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr519;
		case 32: goto tr519;
		case 34: goto st261;
		case 46: goto tr520;
		case 59: goto tr522;
		case 92: goto tr354;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr521;
	} else if ( (*( state.p)) >= 9 )
		goto tr519;
	goto tr352;
tr520:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st360;
st360:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof360;
case 360:
#line 7251 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr523;
	goto tr352;
tr523:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st361;
st361:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof361;
case 361:
#line 7269 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr519;
		case 32: goto tr519;
		case 34: goto st261;
		case 59: goto tr522;
		case 92: goto tr354;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr523;
	} else if ( (*( state.p)) >= 9 )
		goto tr519;
	goto tr352;
tr515:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st362;
st362:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof362;
case 362:
#line 7293 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr524;
	goto tr352;
tr524:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st363;
st363:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof363;
case 363:
#line 7311 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr514;
		case 32: goto tr514;
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr524;
	} else if ( (*( state.p)) >= 9 )
		goto tr514;
	goto tr352;
tr504:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st364;
st364:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof364;
case 364:
#line 7334 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 117: goto tr525;
	}
	goto tr352;
tr525:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st365;
st365:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof365;
case 365:
#line 7351 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 110: goto tr526;
	}
	goto tr352;
tr526:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st366;
st366:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof366;
case 366:
#line 7368 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 116: goto tr527;
	}
	goto tr352;
tr527:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st367;
st367:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof367;
case 367:
#line 7385 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr528;
		case 32: goto tr528;
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr528;
	goto tr352;
tr528:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st368;
st368:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof368;
case 368:
#line 7405 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr528;
		case 32: goto tr528;
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr529;
	} else if ( (*( state.p)) >= 9 )
		goto tr528;
	goto tr352;
tr529:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st369;
tr531:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st369;
st369:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof369;
case 369:
#line 7438 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr530;
		case 32: goto tr530;
		case 34: goto st261;
		case 59: goto tr532;
		case 92: goto tr354;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr531;
	} else if ( (*( state.p)) >= 9 )
		goto tr530;
	goto tr352;
tr475:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st370;
st370:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof370;
case 370:
#line 7462 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 97: goto tr533;
	}
	goto tr352;
tr533:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st371;
st371:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof371;
case 371:
#line 7479 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 98: goto tr534;
	}
	goto tr352;
tr534:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st372;
st372:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof372;
case 372:
#line 7496 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 105: goto tr535;
	}
	goto tr352;
tr535:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st373;
st373:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof373;
case 373:
#line 7513 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 116: goto tr536;
	}
	goto tr352;
tr536:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st374;
st374:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof374;
case 374:
#line 7530 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 97: goto tr537;
	}
	goto tr352;
tr537:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st375;
st375:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof375;
case 375:
#line 7547 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 116: goto tr538;
	}
	goto tr352;
tr538:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st376;
st376:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof376;
case 376:
#line 7564 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr539;
		case 32: goto tr539;
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr539;
	goto tr352;
tr539:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st377;
st377:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof377;
case 377:
#line 7584 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr539;
		case 32: goto tr539;
		case 34: goto st261;
		case 92: goto tr354;
		case 99: goto tr540;
		case 102: goto tr541;
		case 115: goto tr542;
		case 119: goto tr543;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr539;
	goto tr352;
tr540:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st378;
st378:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof378;
case 378:
#line 7608 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 111: goto tr544;
	}
	goto tr352;
tr544:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st379;
st379:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof379;
case 379:
#line 7625 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 114: goto tr545;
	}
	goto tr352;
tr545:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st380;
st380:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof380;
case 380:
#line 7642 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 110: goto tr546;
	}
	goto tr352;
tr546:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st381;
st381:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof381;
case 381:
#line 7659 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr547;
	}
	goto tr352;
tr547:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st382;
st382:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof382;
case 382:
#line 7676 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 114: goto tr548;
	}
	goto tr352;
tr548:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st383;
st383:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof383;
case 383:
#line 7693 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr549;
		case 32: goto tr549;
		case 34: goto st261;
		case 59: goto tr550;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr549;
	goto tr352;
tr541:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st384;
st384:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof384;
case 384:
#line 7714 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 108: goto tr551;
	}
	goto tr352;
tr551:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st385;
st385:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof385;
case 385:
#line 7731 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 111: goto tr552;
	}
	goto tr352;
tr552:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st386;
st386:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof386;
case 386:
#line 7748 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 111: goto tr553;
	}
	goto tr352;
tr553:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st387;
st387:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof387;
case 387:
#line 7765 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 114: goto tr554;
	}
	goto tr352;
tr554:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st388;
st388:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof388;
case 388:
#line 7782 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr555;
		case 32: goto tr555;
		case 34: goto st261;
		case 59: goto tr556;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr555;
	goto tr352;
tr542:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st389;
st389:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof389;
case 389:
#line 7803 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 104: goto tr557;
	}
	goto tr352;
tr557:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st390;
st390:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof390;
case 390:
#line 7820 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 111: goto tr558;
	}
	goto tr352;
tr558:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st391;
st391:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof391;
case 391:
#line 7837 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 114: goto tr559;
	}
	goto tr352;
tr559:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st392;
st392:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof392;
case 392:
#line 7854 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr560;
	}
	goto tr352;
tr560:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st393;
st393:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof393;
case 393:
#line 7871 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 108: goto tr561;
	}
	goto tr352;
tr561:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st394;
st394:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof394;
case 394:
#line 7888 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 105: goto tr562;
	}
	goto tr352;
tr562:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st395;
st395:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof395;
case 395:
#line 7905 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 110: goto tr563;
	}
	goto tr352;
tr563:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st396;
st396:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof396;
case 396:
#line 7922 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr564;
	}
	goto tr352;
tr564:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st397;
st397:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof397;
case 397:
#line 7939 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr565;
		case 32: goto tr565;
		case 34: goto st261;
		case 59: goto tr566;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr565;
	goto tr352;
tr543:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st398;
st398:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof398;
case 398:
#line 7960 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 97: goto tr567;
	}
	goto tr352;
tr567:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st399;
st399:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof399;
case 399:
#line 7977 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 108: goto tr568;
		case 116: goto tr569;
	}
	goto tr352;
tr568:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st400;
st400:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof400;
case 400:
#line 7995 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 107: goto tr570;
	}
	goto tr352;
tr570:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st401;
st401:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof401;
case 401:
#line 8012 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr571;
		case 32: goto tr571;
		case 34: goto st261;
		case 59: goto tr572;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr571;
	goto tr352;
tr569:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st402;
st402:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof402;
case 402:
#line 8033 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr573;
	}
	goto tr352;
tr573:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st403;
st403:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof403;
case 403:
#line 8050 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 114: goto tr574;
	}
	goto tr352;
tr574:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st404;
st404:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof404;
case 404:
#line 8067 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr575;
		case 32: goto tr575;
		case 34: goto st261;
		case 59: goto tr576;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr575;
	goto tr352;
tr476:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st405;
st405:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof405;
case 405:
#line 8088 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 100: goto tr577;
	}
	goto tr352;
tr577:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st406;
st406:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof406;
case 406:
#line 8105 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 108: goto tr578;
	}
	goto tr352;
tr578:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st407;
st407:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof407;
case 407:
#line 8122 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr579;
	}
	goto tr352;
tr579:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st408;
st408:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof408;
case 408:
#line 8139 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 95: goto tr580;
	}
	goto tr352;
tr580:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st409;
st409:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof409;
case 409:
#line 8156 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 97: goto tr581;
	}
	goto tr352;
tr581:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st410;
st410:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof410;
case 410:
#line 8173 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 105: goto tr582;
	}
	goto tr352;
tr582:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st411;
st411:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof411;
case 411:
#line 8190 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr583;
		case 32: goto tr583;
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr583;
	goto tr352;
tr583:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st412;
st412:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof412;
case 412:
#line 8210 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr583;
		case 32: goto tr583;
		case 34: goto st261;
		case 92: goto tr354;
		case 110: goto tr584;
		case 114: goto tr585;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr583;
	goto tr352;
tr584:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st413;
st413:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof413;
case 413:
#line 8232 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 111: goto tr586;
	}
	goto tr352;
tr586:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st414;
st414:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof414;
case 414:
#line 8249 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 110: goto tr587;
	}
	goto tr352;
tr587:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st415;
st415:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof415;
case 415:
#line 8266 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr588;
	}
	goto tr352;
tr588:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st416;
st416:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof416;
case 416:
#line 8283 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr589;
		case 32: goto tr589;
		case 34: goto st261;
		case 59: goto tr590;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr589;
	goto tr352;
tr585:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st417;
st417:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof417;
case 417:
#line 8304 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 97: goto tr591;
	}
	goto tr352;
tr591:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st418;
st418:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof418;
case 418:
#line 8321 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 110: goto tr592;
	}
	goto tr352;
tr592:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st419;
st419:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof419;
case 419:
#line 8338 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 100: goto tr593;
	}
	goto tr352;
tr593:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st420;
st420:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof420;
case 420:
#line 8355 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 111: goto tr594;
	}
	goto tr352;
tr594:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st421;
st421:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof421;
case 421:
#line 8372 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 109: goto tr595;
	}
	goto tr352;
tr595:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st422;
st422:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof422;
case 422:
#line 8389 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr596;
		case 32: goto tr596;
		case 34: goto st261;
		case 59: goto tr597;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr596;
	goto tr352;
tr477:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st423;
st423:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof423;
case 423:
#line 8410 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 111: goto tr598;
	}
	goto tr352;
tr598:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st424;
st424:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof424;
case 424:
#line 8427 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 118: goto tr599;
	}
	goto tr352;
tr599:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st425;
st425:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof425;
case 425:
#line 8444 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr600;
	}
	goto tr352;
tr600:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st426;
st426:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof426;
case 426:
#line 8461 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr601;
		case 32: goto tr601;
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr601;
	goto tr352;
tr601:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st427;
st427:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof427;
case 427:
#line 8481 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr601;
		case 32: goto tr601;
		case 34: goto st261;
		case 92: goto tr354;
		case 97: goto tr602;
		case 102: goto tr603;
		case 119: goto tr604;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr601;
	goto tr352;
tr602:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st428;
st428:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof428;
case 428:
#line 8504 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 110: goto tr605;
	}
	goto tr352;
tr605:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st429;
st429:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof429;
case 429:
#line 8521 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 121: goto tr606;
	}
	goto tr352;
tr606:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st430;
st430:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof430;
case 430:
#line 8538 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr607;
		case 32: goto tr607;
		case 34: goto st261;
		case 59: goto tr608;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr607;
	goto tr352;
tr603:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st431;
st431:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof431;
case 431:
#line 8559 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 108: goto tr609;
	}
	goto tr352;
tr609:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st432;
st432:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof432;
case 432:
#line 8576 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 111: goto tr610;
	}
	goto tr352;
tr610:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st433;
st433:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof433;
case 433:
#line 8593 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 111: goto tr611;
	}
	goto tr352;
tr611:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st434;
st434:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof434;
case 434:
#line 8610 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 114: goto tr612;
	}
	goto tr352;
tr612:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st435;
st435:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof435;
case 435:
#line 8627 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr613;
		case 32: goto tr613;
		case 34: goto st261;
		case 59: goto tr614;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr613;
	goto tr352;
tr604:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st436;
st436:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof436;
case 436:
#line 8648 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 97: goto tr615;
	}
	goto tr352;
tr615:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st437;
st437:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof437;
case 437:
#line 8665 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 116: goto tr616;
	}
	goto tr352;
tr616:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st438;
st438:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof438;
case 438:
#line 8682 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr617;
	}
	goto tr352;
tr617:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st439;
st439:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof439;
case 439:
#line 8699 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 114: goto tr618;
	}
	goto tr352;
tr618:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st440;
st440:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof440;
case 440:
#line 8716 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr619;
		case 32: goto tr619;
		case 34: goto st261;
		case 59: goto tr620;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr619;
	goto tr352;
tr478:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st441;
st441:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof441;
case 441:
#line 8737 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 97: goto tr621;
	}
	goto tr352;
tr621:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st442;
st442:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof442;
case 442:
#line 8754 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 109: goto tr622;
	}
	goto tr352;
tr622:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st443;
st443:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof443;
case 443:
#line 8771 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr623;
	}
	goto tr352;
tr623:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st444;
st444:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof444;
case 444:
#line 8788 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr624;
		case 32: goto tr624;
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr624;
	goto tr352;
tr624:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st445;
st445:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof445;
case 445:
#line 8808 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr624;
		case 32: goto tr624;
		case 34: goto st446;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr624;
	goto tr352;
st446:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof446;
case 446:
	switch( (*( state.p)) ) {
		case 13: goto tr626;
		case 32: goto tr626;
		case 34: goto tr165;
		case 92: goto tr166;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr626;
	goto tr164;
tr627:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st447;
tr626:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 140 "configparser.rl"
	{ spe.skin.text = state.match; }
	goto st447;
st447:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof447;
case 447:
#line 8853 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr627;
		case 32: goto tr627;
		case 34: goto st124;
		case 92: goto tr169;
		case 98: goto tr628;
		case 100: goto tr629;
		case 110: goto tr630;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr627;
	goto tr167;
tr628:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st448;
st448:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof448;
case 448:
#line 8876 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 114: goto tr631;
	}
	goto tr167;
tr631:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st449;
st449:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof449;
case 449:
#line 8893 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 105: goto tr632;
	}
	goto tr167;
tr632:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st450;
st450:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof450;
case 450:
#line 8910 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 103: goto tr633;
	}
	goto tr167;
tr633:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st451;
st451:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof451;
case 451:
#line 8927 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 104: goto tr634;
	}
	goto tr167;
tr634:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st452;
st452:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof452;
case 452:
#line 8944 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 116: goto tr635;
	}
	goto tr167;
tr635:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st453;
st453:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof453;
case 453:
#line 8961 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr636;
		case 32: goto tr636;
		case 34: goto st124;
		case 92: goto tr169;
		case 95: goto tr637;
		case 98: goto tr638;
		case 99: goto tr639;
		case 103: goto tr640;
		case 109: goto tr641;
		case 114: goto tr642;
		case 119: goto tr643;
		case 121: goto tr644;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr636;
	goto tr167;
tr645:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st454;
tr636:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st454;
tr698:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st454;
st454:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof454;
case 454:
#line 9005 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr645;
		case 32: goto tr645;
		case 34: goto st124;
		case 92: goto tr169;
		case 98: goto tr646;
		case 99: goto tr647;
		case 103: goto tr648;
		case 109: goto tr649;
		case 114: goto tr650;
		case 119: goto tr651;
		case 121: goto tr652;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr645;
	goto tr167;
tr646:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st455;
tr638:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st455;
tr700:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st455;
st455:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof455;
case 455:
#line 9048 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 108: goto tr653;
	}
	goto tr167;
tr653:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st456;
st456:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof456;
case 456:
#line 9065 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 97: goto tr654;
		case 117: goto tr655;
	}
	goto tr167;
tr654:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st457;
st457:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof457;
case 457:
#line 9083 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 99: goto tr656;
	}
	goto tr167;
tr656:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st458;
st458:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof458;
case 458:
#line 9100 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 107: goto tr175;
	}
	goto tr167;
tr655:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st459;
st459:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof459;
case 459:
#line 9117 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr657;
	}
	goto tr167;
tr657:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st460;
st460:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof460;
case 460:
#line 9134 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr658;
		case 32: goto tr658;
		case 34: goto st124;
		case 59: goto tr659;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr658;
	goto tr167;
tr647:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st461;
tr639:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st461;
tr701:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st461;
st461:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof461;
case 461:
#line 9171 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 121: goto tr660;
	}
	goto tr167;
tr660:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st462;
st462:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof462;
case 462:
#line 9188 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 97: goto tr661;
	}
	goto tr167;
tr661:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st463;
st463:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof463;
case 463:
#line 9205 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 110: goto tr662;
	}
	goto tr167;
tr662:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st464;
st464:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof464;
case 464:
#line 9222 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr663;
		case 32: goto tr663;
		case 34: goto st124;
		case 59: goto tr664;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr663;
	goto tr167;
tr648:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st465;
tr640:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st465;
tr702:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st465;
st465:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof465;
case 465:
#line 9259 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 114: goto tr665;
	}
	goto tr167;
tr665:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st466;
st466:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof466;
case 466:
#line 9276 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr666;
	}
	goto tr167;
tr666:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st467;
st467:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof467;
case 467:
#line 9293 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr667;
	}
	goto tr167;
tr667:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st468;
st468:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof468;
case 468:
#line 9310 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 110: goto tr668;
	}
	goto tr167;
tr668:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st469;
st469:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof469;
case 469:
#line 9327 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr669;
		case 32: goto tr669;
		case 34: goto st124;
		case 59: goto tr670;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr669;
	goto tr167;
tr649:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st470;
tr641:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st470;
tr703:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st470;
st470:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof470;
case 470:
#line 9364 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 97: goto tr671;
	}
	goto tr167;
tr671:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st471;
st471:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof471;
case 471:
#line 9381 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 103: goto tr672;
	}
	goto tr167;
tr672:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st472;
st472:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof472;
case 472:
#line 9398 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr673;
	}
	goto tr167;
tr673:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st473;
st473:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof473;
case 473:
#line 9415 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 110: goto tr674;
	}
	goto tr167;
tr674:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st474;
st474:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof474;
case 474:
#line 9432 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 116: goto tr675;
	}
	goto tr167;
tr675:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st475;
st475:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof475;
case 475:
#line 9449 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 97: goto tr676;
	}
	goto tr167;
tr676:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st476;
st476:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof476;
case 476:
#line 9466 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr677;
		case 32: goto tr677;
		case 34: goto st124;
		case 59: goto tr678;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr677;
	goto tr167;
tr650:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st477;
tr642:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st477;
tr704:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st477;
st477:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof477;
case 477:
#line 9503 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr679;
	}
	goto tr167;
tr679:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st478;
st478:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof478;
case 478:
#line 9520 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 100: goto tr680;
	}
	goto tr167;
tr680:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st479;
st479:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof479;
case 479:
#line 9537 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr681;
		case 32: goto tr681;
		case 34: goto st124;
		case 59: goto tr682;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr681;
	goto tr167;
tr651:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st480;
tr643:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st480;
tr705:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st480;
st480:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof480;
case 480:
#line 9574 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 104: goto tr683;
	}
	goto tr167;
tr683:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st481;
st481:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof481;
case 481:
#line 9591 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 105: goto tr684;
	}
	goto tr167;
tr684:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st482;
st482:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof482;
case 482:
#line 9608 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 116: goto tr685;
	}
	goto tr167;
tr685:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st483;
st483:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof483;
case 483:
#line 9625 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr686;
	}
	goto tr167;
tr686:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st484;
st484:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof484;
case 484:
#line 9642 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr687;
		case 32: goto tr687;
		case 34: goto st124;
		case 59: goto tr688;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr687;
	goto tr167;
tr652:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st485;
tr644:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st485;
tr706:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st485;
st485:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof485;
case 485:
#line 9679 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr689;
	}
	goto tr167;
tr689:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st486;
st486:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof486;
case 486:
#line 9696 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 108: goto tr690;
	}
	goto tr167;
tr690:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st487;
st487:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof487;
case 487:
#line 9713 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 108: goto tr691;
	}
	goto tr167;
tr691:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st488;
st488:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof488;
case 488:
#line 9730 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 111: goto tr692;
	}
	goto tr167;
tr692:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st489;
st489:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof489;
case 489:
#line 9747 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 119: goto tr693;
	}
	goto tr167;
tr693:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st490;
st490:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof490;
case 490:
#line 9764 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr694;
		case 32: goto tr694;
		case 34: goto st124;
		case 59: goto tr695;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr694;
	goto tr167;
tr637:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st491;
tr699:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st491;
st491:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof491;
case 491:
#line 9795 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 98: goto tr646;
		case 99: goto tr647;
		case 103: goto tr648;
		case 109: goto tr649;
		case 114: goto tr650;
		case 119: goto tr651;
		case 121: goto tr652;
	}
	goto tr167;
tr629:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st492;
st492:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof492;
case 492:
#line 9818 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 105: goto tr696;
	}
	goto tr167;
tr696:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st493;
st493:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof493;
case 493:
#line 9835 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 109: goto tr697;
	}
	goto tr167;
tr697:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st494;
st494:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof494;
case 494:
#line 9852 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr698;
		case 32: goto tr698;
		case 34: goto st124;
		case 92: goto tr169;
		case 95: goto tr699;
		case 98: goto tr700;
		case 99: goto tr701;
		case 103: goto tr702;
		case 109: goto tr703;
		case 114: goto tr704;
		case 119: goto tr705;
		case 121: goto tr706;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr698;
	goto tr167;
tr630:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st495;
st495:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof495;
case 495:
#line 9880 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 111: goto tr707;
	}
	goto tr167;
tr707:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st496;
st496:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof496;
case 496:
#line 9897 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 110: goto tr708;
	}
	goto tr167;
tr708:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st497;
st497:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof497;
case 497:
#line 9914 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st124;
		case 92: goto tr169;
		case 101: goto tr175;
	}
	goto tr167;
tr479:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st498;
st498:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof498;
case 498:
#line 9931 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 97: goto tr709;
	}
	goto tr352;
tr709:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st499;
st499:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof499;
case 499:
#line 9948 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 110: goto tr710;
	}
	goto tr352;
tr710:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st500;
st500:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof500;
case 500:
#line 9965 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 103: goto tr711;
	}
	goto tr352;
tr711:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st501;
st501:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof501;
case 501:
#line 9982 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr712;
	}
	goto tr352;
tr712:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st502;
st502:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof502;
case 502:
#line 9999 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr713;
		case 32: goto tr713;
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr713;
	goto tr352;
tr713:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st503;
st503:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof503;
case 503:
#line 10019 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr713;
		case 32: goto tr713;
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr714;
	} else if ( (*( state.p)) >= 9 )
		goto tr713;
	goto tr352;
tr716:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st504;
tr714:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st504;
st504:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof504;
case 504:
#line 10052 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr715;
		case 32: goto tr715;
		case 34: goto st261;
		case 59: goto tr717;
		case 92: goto tr354;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr716;
	} else if ( (*( state.p)) >= 9 )
		goto tr715;
	goto tr352;
tr480:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st505;
st505:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof505;
case 505:
#line 10076 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 107: goto tr718;
	}
	goto tr352;
tr718:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st506;
st506:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof506;
case 506:
#line 10093 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 105: goto tr719;
	}
	goto tr352;
tr719:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st507;
st507:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof507;
case 507:
#line 10110 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 110: goto tr720;
	}
	goto tr352;
tr720:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st508;
st508:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof508;
case 508:
#line 10127 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr721;
		case 32: goto tr721;
		case 34: goto st261;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr721;
	goto tr352;
tr721:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st509;
st509:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof509;
case 509:
#line 10147 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr721;
		case 32: goto tr721;
		case 34: goto st510;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr721;
	goto tr352;
st510:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof510;
case 510:
	switch( (*( state.p)) ) {
		case 13: goto tr723;
		case 32: goto tr723;
		case 34: goto tr349;
		case 92: goto tr351;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr723;
	goto tr347;
tr481:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st511;
st511:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof511;
case 511:
#line 10180 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr724;
		case 32: goto tr724;
		case 34: goto st261;
		case 59: goto tr725;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr724;
	goto tr352;
tr468:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st512;
st512:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof512;
case 512:
#line 10201 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr726;
	}
	goto tr352;
tr726:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st513;
st513:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof513;
case 513:
#line 10218 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr727;
		case 32: goto tr727;
		case 34: goto st261;
		case 59: goto tr728;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr727;
	goto tr352;
tr460:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st514;
tr452:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st514;
tr770:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st514;
st514:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof514;
case 514:
#line 10255 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 121: goto tr729;
	}
	goto tr352;
tr729:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st515;
st515:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof515;
case 515:
#line 10272 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 97: goto tr730;
	}
	goto tr352;
tr730:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st516;
st516:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof516;
case 516:
#line 10289 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 110: goto tr731;
	}
	goto tr352;
tr731:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st517;
st517:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof517;
case 517:
#line 10306 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr732;
		case 32: goto tr732;
		case 34: goto st261;
		case 59: goto tr733;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr732;
	goto tr352;
tr461:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st518;
tr453:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st518;
tr771:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st518;
st518:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof518;
case 518:
#line 10343 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 114: goto tr734;
	}
	goto tr352;
tr734:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st519;
st519:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof519;
case 519:
#line 10360 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr735;
	}
	goto tr352;
tr735:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st520;
st520:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof520;
case 520:
#line 10377 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr736;
	}
	goto tr352;
tr736:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st521;
st521:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof521;
case 521:
#line 10394 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 110: goto tr737;
	}
	goto tr352;
tr737:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st522;
st522:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof522;
case 522:
#line 10411 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr738;
		case 32: goto tr738;
		case 34: goto st261;
		case 59: goto tr739;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr738;
	goto tr352;
tr462:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st523;
tr454:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st523;
tr772:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st523;
st523:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof523;
case 523:
#line 10448 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 97: goto tr740;
	}
	goto tr352;
tr740:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st524;
st524:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof524;
case 524:
#line 10465 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 103: goto tr741;
	}
	goto tr352;
tr741:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st525;
st525:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof525;
case 525:
#line 10482 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr742;
	}
	goto tr352;
tr742:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st526;
st526:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof526;
case 526:
#line 10499 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 110: goto tr743;
	}
	goto tr352;
tr743:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st527;
st527:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof527;
case 527:
#line 10516 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 116: goto tr744;
	}
	goto tr352;
tr744:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st528;
st528:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof528;
case 528:
#line 10533 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 97: goto tr745;
	}
	goto tr352;
tr745:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st529;
st529:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof529;
case 529:
#line 10550 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr746;
		case 32: goto tr746;
		case 34: goto st261;
		case 59: goto tr747;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr746;
	goto tr352;
tr463:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st530;
tr455:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st530;
tr773:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st530;
st530:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof530;
case 530:
#line 10587 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr748;
	}
	goto tr352;
tr748:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st531;
st531:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof531;
case 531:
#line 10604 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 100: goto tr749;
	}
	goto tr352;
tr749:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st532;
st532:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof532;
case 532:
#line 10621 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr750;
		case 32: goto tr750;
		case 34: goto st261;
		case 59: goto tr751;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr750;
	goto tr352;
tr464:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st533;
tr456:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st533;
tr774:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st533;
st533:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof533;
case 533:
#line 10658 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 104: goto tr752;
	}
	goto tr352;
tr752:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st534;
st534:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof534;
case 534:
#line 10675 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 105: goto tr753;
	}
	goto tr352;
tr753:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st535;
st535:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof535;
case 535:
#line 10692 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 116: goto tr754;
	}
	goto tr352;
tr754:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st536;
st536:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof536;
case 536:
#line 10709 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr755;
	}
	goto tr352;
tr755:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st537;
st537:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof537;
case 537:
#line 10726 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr756;
		case 32: goto tr756;
		case 34: goto st261;
		case 59: goto tr757;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr756;
	goto tr352;
tr465:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st538;
tr457:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st538;
tr775:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st538;
st538:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof538;
case 538:
#line 10763 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr758;
	}
	goto tr352;
tr758:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st539;
st539:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof539;
case 539:
#line 10780 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 108: goto tr759;
	}
	goto tr352;
tr759:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st540;
st540:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof540;
case 540:
#line 10797 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 108: goto tr760;
	}
	goto tr352;
tr760:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st541;
st541:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof541;
case 541:
#line 10814 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 111: goto tr761;
	}
	goto tr352;
tr761:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st542;
st542:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof542;
case 542:
#line 10831 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 119: goto tr762;
	}
	goto tr352;
tr762:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st543;
st543:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof543;
case 543:
#line 10848 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr763;
		case 32: goto tr763;
		case 34: goto st261;
		case 59: goto tr764;
		case 92: goto tr354;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr763;
	goto tr352;
tr450:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st544;
tr768:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st544;
st544:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof544;
case 544:
#line 10879 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 98: goto tr459;
		case 99: goto tr460;
		case 103: goto tr461;
		case 109: goto tr462;
		case 114: goto tr463;
		case 119: goto tr464;
		case 121: goto tr465;
	}
	goto tr352;
tr442:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st545;
st545:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof545;
case 545:
#line 10902 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 105: goto tr765;
	}
	goto tr352;
tr765:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st546;
st546:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof546;
case 546:
#line 10919 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 109: goto tr766;
	}
	goto tr352;
tr766:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st547;
st547:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof547;
case 547:
#line 10936 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr767;
		case 32: goto tr767;
		case 34: goto st261;
		case 92: goto tr354;
		case 95: goto tr768;
		case 98: goto tr769;
		case 99: goto tr770;
		case 103: goto tr771;
		case 109: goto tr772;
		case 114: goto tr773;
		case 119: goto tr774;
		case 121: goto tr775;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr767;
	goto tr352;
tr443:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st548;
st548:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof548;
case 548:
#line 10964 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 111: goto tr776;
	}
	goto tr352;
tr776:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st549;
st549:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof549;
case 549:
#line 10981 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 110: goto tr777;
	}
	goto tr352;
tr777:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st550;
st550:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof550;
case 550:
#line 10998 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st261;
		case 92: goto tr354;
		case 101: goto tr470;
	}
	goto tr352;
tr186:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st551;
st551:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof551;
case 551:
#line 11015 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr778;
		case 32: goto tr778;
		case 34: goto st124;
		case 59: goto tr779;
		case 92: goto tr169;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr778;
	goto tr167;
st552:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof552;
case 552:
	if ( (*( state.p)) == 97 )
		goto st553;
	goto st0;
st553:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof553;
case 553:
	if ( (*( state.p)) == 110 )
		goto st554;
	goto st0;
st554:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof554;
case 554:
	if ( (*( state.p)) == 103 )
		goto st555;
	goto st0;
st555:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof555;
case 555:
	if ( (*( state.p)) == 101 )
		goto st556;
	goto st0;
st556:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof556;
case 556:
	switch( (*( state.p)) ) {
		case 13: goto st557;
		case 32: goto st557;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st557;
	goto st0;
st557:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof557;
case 557:
	switch( (*( state.p)) ) {
		case 13: goto st557;
		case 32: goto st557;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr785;
	} else if ( (*( state.p)) >= 9 )
		goto st557;
	goto st0;
tr785:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st558;
tr787:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st558;
st558:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof558;
case 558:
#line 11099 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr786;
		case 32: goto tr786;
		case 59: goto tr788;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr787;
	} else if ( (*( state.p)) >= 9 )
		goto tr786;
	goto st0;
st559:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof559;
case 559:
	if ( (*( state.p)) == 107 )
		goto st560;
	goto st0;
st560:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof560;
case 560:
	if ( (*( state.p)) == 105 )
		goto st561;
	goto st0;
st561:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof561;
case 561:
	if ( (*( state.p)) == 110 )
		goto st562;
	goto st0;
st562:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof562;
case 562:
	switch( (*( state.p)) ) {
		case 13: goto st563;
		case 32: goto st563;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st563;
	goto st0;
st563:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof563;
case 563:
	switch( (*( state.p)) ) {
		case 13: goto st563;
		case 32: goto st563;
		case 34: goto st564;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st563;
	goto st0;
st564:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof564;
case 564:
	switch( (*( state.p)) ) {
		case 34: goto tr349;
		case 92: goto tr351;
	}
	goto tr347;
st565:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof565;
case 565:
	switch( (*( state.p)) ) {
		case 13: goto tr794;
		case 32: goto tr794;
		case 59: goto tr795;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr794;
	goto st0;
st566:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof566;
case 566:
	if ( (*( state.p)) == 101 )
		goto st567;
	goto st0;
st567:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof567;
case 567:
	if ( (*( state.p)) == 101 )
		goto st568;
	goto st0;
st568:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof568;
case 568:
	if ( (*( state.p)) == 107 )
		goto st569;
	goto st0;
st569:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof569;
case 569:
	if ( (*( state.p)) == 95 )
		goto st570;
	goto st0;
st570:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof570;
case 570:
	if ( (*( state.p)) == 112 )
		goto st571;
	goto st0;
st571:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof571;
case 571:
	if ( (*( state.p)) == 108 )
		goto st572;
	goto st0;
st572:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof572;
case 572:
	if ( (*( state.p)) == 97 )
		goto st573;
	goto st0;
st573:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof573;
case 573:
	if ( (*( state.p)) == 121 )
		goto st574;
	goto st0;
st574:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof574;
case 574:
	if ( (*( state.p)) == 101 )
		goto st575;
	goto st0;
st575:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof575;
case 575:
	if ( (*( state.p)) == 114 )
		goto st576;
	goto st0;
st576:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof576;
case 576:
	switch( (*( state.p)) ) {
		case 13: goto tr806;
		case 32: goto tr806;
		case 59: goto tr807;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr806;
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
	_test_eof13:  state.cs = 13; goto _test_eof; 
	_test_eof577:  state.cs = 577; goto _test_eof; 
	_test_eof578:  state.cs = 578; goto _test_eof; 
	_test_eof14:  state.cs = 14; goto _test_eof; 
	_test_eof15:  state.cs = 15; goto _test_eof; 
	_test_eof16:  state.cs = 16; goto _test_eof; 
	_test_eof17:  state.cs = 17; goto _test_eof; 
	_test_eof18:  state.cs = 18; goto _test_eof; 
	_test_eof19:  state.cs = 19; goto _test_eof; 
	_test_eof20:  state.cs = 20; goto _test_eof; 
	_test_eof21:  state.cs = 21; goto _test_eof; 
	_test_eof22:  state.cs = 22; goto _test_eof; 
	_test_eof579:  state.cs = 579; goto _test_eof; 
	_test_eof23:  state.cs = 23; goto _test_eof; 
	_test_eof24:  state.cs = 24; goto _test_eof; 
	_test_eof25:  state.cs = 25; goto _test_eof; 
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
	_test_eof580:  state.cs = 580; goto _test_eof; 
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
	_test_eof581:  state.cs = 581; goto _test_eof; 
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
	_test_eof439:  state.cs = 439; goto _test_eof; 
	_test_eof440:  state.cs = 440; goto _test_eof; 
	_test_eof441:  state.cs = 441; goto _test_eof; 
	_test_eof442:  state.cs = 442; goto _test_eof; 
	_test_eof443:  state.cs = 443; goto _test_eof; 
	_test_eof444:  state.cs = 444; goto _test_eof; 
	_test_eof445:  state.cs = 445; goto _test_eof; 
	_test_eof446:  state.cs = 446; goto _test_eof; 
	_test_eof447:  state.cs = 447; goto _test_eof; 
	_test_eof448:  state.cs = 448; goto _test_eof; 
	_test_eof449:  state.cs = 449; goto _test_eof; 
	_test_eof450:  state.cs = 450; goto _test_eof; 
	_test_eof451:  state.cs = 451; goto _test_eof; 
	_test_eof452:  state.cs = 452; goto _test_eof; 
	_test_eof453:  state.cs = 453; goto _test_eof; 
	_test_eof454:  state.cs = 454; goto _test_eof; 
	_test_eof455:  state.cs = 455; goto _test_eof; 
	_test_eof456:  state.cs = 456; goto _test_eof; 
	_test_eof457:  state.cs = 457; goto _test_eof; 
	_test_eof458:  state.cs = 458; goto _test_eof; 
	_test_eof459:  state.cs = 459; goto _test_eof; 
	_test_eof460:  state.cs = 460; goto _test_eof; 
	_test_eof461:  state.cs = 461; goto _test_eof; 
	_test_eof462:  state.cs = 462; goto _test_eof; 
	_test_eof463:  state.cs = 463; goto _test_eof; 
	_test_eof464:  state.cs = 464; goto _test_eof; 
	_test_eof465:  state.cs = 465; goto _test_eof; 
	_test_eof466:  state.cs = 466; goto _test_eof; 
	_test_eof467:  state.cs = 467; goto _test_eof; 
	_test_eof468:  state.cs = 468; goto _test_eof; 
	_test_eof469:  state.cs = 469; goto _test_eof; 
	_test_eof470:  state.cs = 470; goto _test_eof; 
	_test_eof471:  state.cs = 471; goto _test_eof; 
	_test_eof472:  state.cs = 472; goto _test_eof; 
	_test_eof473:  state.cs = 473; goto _test_eof; 
	_test_eof474:  state.cs = 474; goto _test_eof; 
	_test_eof475:  state.cs = 475; goto _test_eof; 
	_test_eof476:  state.cs = 476; goto _test_eof; 
	_test_eof477:  state.cs = 477; goto _test_eof; 
	_test_eof478:  state.cs = 478; goto _test_eof; 
	_test_eof479:  state.cs = 479; goto _test_eof; 
	_test_eof480:  state.cs = 480; goto _test_eof; 
	_test_eof481:  state.cs = 481; goto _test_eof; 
	_test_eof482:  state.cs = 482; goto _test_eof; 
	_test_eof483:  state.cs = 483; goto _test_eof; 
	_test_eof484:  state.cs = 484; goto _test_eof; 
	_test_eof485:  state.cs = 485; goto _test_eof; 
	_test_eof486:  state.cs = 486; goto _test_eof; 
	_test_eof487:  state.cs = 487; goto _test_eof; 
	_test_eof488:  state.cs = 488; goto _test_eof; 
	_test_eof489:  state.cs = 489; goto _test_eof; 
	_test_eof490:  state.cs = 490; goto _test_eof; 
	_test_eof491:  state.cs = 491; goto _test_eof; 
	_test_eof492:  state.cs = 492; goto _test_eof; 
	_test_eof493:  state.cs = 493; goto _test_eof; 
	_test_eof494:  state.cs = 494; goto _test_eof; 
	_test_eof495:  state.cs = 495; goto _test_eof; 
	_test_eof496:  state.cs = 496; goto _test_eof; 
	_test_eof497:  state.cs = 497; goto _test_eof; 
	_test_eof498:  state.cs = 498; goto _test_eof; 
	_test_eof499:  state.cs = 499; goto _test_eof; 
	_test_eof500:  state.cs = 500; goto _test_eof; 
	_test_eof501:  state.cs = 501; goto _test_eof; 
	_test_eof502:  state.cs = 502; goto _test_eof; 
	_test_eof503:  state.cs = 503; goto _test_eof; 
	_test_eof504:  state.cs = 504; goto _test_eof; 
	_test_eof505:  state.cs = 505; goto _test_eof; 
	_test_eof506:  state.cs = 506; goto _test_eof; 
	_test_eof507:  state.cs = 507; goto _test_eof; 
	_test_eof508:  state.cs = 508; goto _test_eof; 
	_test_eof509:  state.cs = 509; goto _test_eof; 
	_test_eof510:  state.cs = 510; goto _test_eof; 
	_test_eof511:  state.cs = 511; goto _test_eof; 
	_test_eof512:  state.cs = 512; goto _test_eof; 
	_test_eof513:  state.cs = 513; goto _test_eof; 
	_test_eof514:  state.cs = 514; goto _test_eof; 
	_test_eof515:  state.cs = 515; goto _test_eof; 
	_test_eof516:  state.cs = 516; goto _test_eof; 
	_test_eof517:  state.cs = 517; goto _test_eof; 
	_test_eof518:  state.cs = 518; goto _test_eof; 
	_test_eof519:  state.cs = 519; goto _test_eof; 
	_test_eof520:  state.cs = 520; goto _test_eof; 
	_test_eof521:  state.cs = 521; goto _test_eof; 
	_test_eof522:  state.cs = 522; goto _test_eof; 
	_test_eof523:  state.cs = 523; goto _test_eof; 
	_test_eof524:  state.cs = 524; goto _test_eof; 
	_test_eof525:  state.cs = 525; goto _test_eof; 
	_test_eof526:  state.cs = 526; goto _test_eof; 
	_test_eof527:  state.cs = 527; goto _test_eof; 
	_test_eof528:  state.cs = 528; goto _test_eof; 
	_test_eof529:  state.cs = 529; goto _test_eof; 
	_test_eof530:  state.cs = 530; goto _test_eof; 
	_test_eof531:  state.cs = 531; goto _test_eof; 
	_test_eof532:  state.cs = 532; goto _test_eof; 
	_test_eof533:  state.cs = 533; goto _test_eof; 
	_test_eof534:  state.cs = 534; goto _test_eof; 
	_test_eof535:  state.cs = 535; goto _test_eof; 
	_test_eof536:  state.cs = 536; goto _test_eof; 
	_test_eof537:  state.cs = 537; goto _test_eof; 
	_test_eof538:  state.cs = 538; goto _test_eof; 
	_test_eof539:  state.cs = 539; goto _test_eof; 
	_test_eof540:  state.cs = 540; goto _test_eof; 
	_test_eof541:  state.cs = 541; goto _test_eof; 
	_test_eof542:  state.cs = 542; goto _test_eof; 
	_test_eof543:  state.cs = 543; goto _test_eof; 
	_test_eof544:  state.cs = 544; goto _test_eof; 
	_test_eof545:  state.cs = 545; goto _test_eof; 
	_test_eof546:  state.cs = 546; goto _test_eof; 
	_test_eof547:  state.cs = 547; goto _test_eof; 
	_test_eof548:  state.cs = 548; goto _test_eof; 
	_test_eof549:  state.cs = 549; goto _test_eof; 
	_test_eof550:  state.cs = 550; goto _test_eof; 
	_test_eof551:  state.cs = 551; goto _test_eof; 
	_test_eof552:  state.cs = 552; goto _test_eof; 
	_test_eof553:  state.cs = 553; goto _test_eof; 
	_test_eof554:  state.cs = 554; goto _test_eof; 
	_test_eof555:  state.cs = 555; goto _test_eof; 
	_test_eof556:  state.cs = 556; goto _test_eof; 
	_test_eof557:  state.cs = 557; goto _test_eof; 
	_test_eof558:  state.cs = 558; goto _test_eof; 
	_test_eof559:  state.cs = 559; goto _test_eof; 
	_test_eof560:  state.cs = 560; goto _test_eof; 
	_test_eof561:  state.cs = 561; goto _test_eof; 
	_test_eof562:  state.cs = 562; goto _test_eof; 
	_test_eof563:  state.cs = 563; goto _test_eof; 
	_test_eof564:  state.cs = 564; goto _test_eof; 
	_test_eof565:  state.cs = 565; goto _test_eof; 
	_test_eof566:  state.cs = 566; goto _test_eof; 
	_test_eof567:  state.cs = 567; goto _test_eof; 
	_test_eof568:  state.cs = 568; goto _test_eof; 
	_test_eof569:  state.cs = 569; goto _test_eof; 
	_test_eof570:  state.cs = 570; goto _test_eof; 
	_test_eof571:  state.cs = 571; goto _test_eof; 
	_test_eof572:  state.cs = 572; goto _test_eof; 
	_test_eof573:  state.cs = 573; goto _test_eof; 
	_test_eof574:  state.cs = 574; goto _test_eof; 
	_test_eof575:  state.cs = 575; goto _test_eof; 
	_test_eof576:  state.cs = 576; goto _test_eof; 

	_test_eof: {}
	if ( ( state.p) == ( state.eof) )
	{
	switch (  state.cs ) {
	case 577: 
#line 196 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
	break;
#line 11849 "configparser.h"
	}
	}

	_out: {}
	}

#line 230 "configparser.rl"

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
