
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

    
#line 205 "configparser.rl"

/*

*/

    
#line 96 "configparser.h"
static const int ConfigParser_start = 1;
static const int ConfigParser_first_final = 673;
static const int ConfigParser_error = 0;

static const int ConfigParser_en_one_species = 14;
static const int ConfigParser_en_main = 1;


#line 211 "configparser.rl"
    
#line 107 "configparser.h"
	{
	 state.cs = ConfigParser_start;
	 state.top = 0;
	}

#line 212 "configparser.rl"

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
		case 673: goto st673;
		case 674: goto st674;
		case 14: goto st14;
		case 15: goto st15;
		case 16: goto st16;
		case 17: goto st17;
		case 18: goto st18;
		case 19: goto st19;
		case 20: goto st20;
		case 21: goto st21;
		case 22: goto st22;
		case 675: goto st675;
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
		case 676: goto st676;
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
		case 677: goto st677;
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
		case 577: goto st577;
		case 578: goto st578;
		case 579: goto st579;
		case 580: goto st580;
		case 581: goto st581;
		case 582: goto st582;
		case 583: goto st583;
		case 584: goto st584;
		case 585: goto st585;
		case 586: goto st586;
		case 587: goto st587;
		case 588: goto st588;
		case 589: goto st589;
		case 590: goto st590;
		case 591: goto st591;
		case 592: goto st592;
		case 593: goto st593;
		case 594: goto st594;
		case 595: goto st595;
		case 596: goto st596;
		case 597: goto st597;
		case 598: goto st598;
		case 599: goto st599;
		case 600: goto st600;
		case 601: goto st601;
		case 602: goto st602;
		case 603: goto st603;
		case 604: goto st604;
		case 605: goto st605;
		case 606: goto st606;
		case 607: goto st607;
		case 608: goto st608;
		case 609: goto st609;
		case 610: goto st610;
		case 611: goto st611;
		case 612: goto st612;
		case 613: goto st613;
		case 614: goto st614;
		case 615: goto st615;
		case 616: goto st616;
		case 617: goto st617;
		case 618: goto st618;
		case 619: goto st619;
		case 620: goto st620;
		case 621: goto st621;
		case 622: goto st622;
		case 623: goto st623;
		case 624: goto st624;
		case 625: goto st625;
		case 626: goto st626;
		case 627: goto st627;
		case 628: goto st628;
		case 629: goto st629;
		case 630: goto st630;
		case 631: goto st631;
		case 632: goto st632;
		case 633: goto st633;
		case 634: goto st634;
		case 635: goto st635;
		case 636: goto st636;
		case 637: goto st637;
		case 638: goto st638;
		case 639: goto st639;
		case 640: goto st640;
		case 641: goto st641;
		case 642: goto st642;
		case 643: goto st643;
		case 644: goto st644;
		case 645: goto st645;
		case 646: goto st646;
		case 647: goto st647;
		case 648: goto st648;
		case 649: goto st649;
		case 650: goto st650;
		case 651: goto st651;
		case 652: goto st652;
		case 653: goto st653;
		case 654: goto st654;
		case 655: goto st655;
		case 656: goto st656;
		case 657: goto st657;
		case 658: goto st658;
		case 659: goto st659;
		case 660: goto st660;
		case 661: goto st661;
		case 662: goto st662;
		case 663: goto st663;
		case 664: goto st664;
		case 665: goto st665;
		case 666: goto st666;
		case 667: goto st667;
		case 668: goto st668;
		case 669: goto st669;
		case 670: goto st670;
		case 671: goto st671;
		case 672: goto st672;
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
#line 197 "configparser.rl"
	{ spe = Species(); }
	goto st2;
tr929:
#line 200 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
#line 197 "configparser.rl"
	{ spe = Species(); }
	goto st2;
st2:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof2;
case 2:
#line 859 "configparser.h"
	if ( (*( state.p)) == 112 )
		goto tr3;
	goto st0;
tr3:
#line 197 "configparser.rl"
	{ spe = Species(); }
	goto st3;
st3:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof3;
case 3:
#line 871 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr4;
	goto st0;
tr4:
#line 197 "configparser.rl"
	{ spe = Species(); }
	goto st4;
st4:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof4;
case 4:
#line 883 "configparser.h"
	if ( (*( state.p)) == 99 )
		goto tr5;
	goto st0;
tr5:
#line 197 "configparser.rl"
	{ spe = Species(); }
	goto st5;
st5:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof5;
case 5:
#line 895 "configparser.h"
	if ( (*( state.p)) == 105 )
		goto tr6;
	goto st0;
tr6:
#line 197 "configparser.rl"
	{ spe = Species(); }
	goto st6;
st6:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof6;
case 6:
#line 907 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr7;
	goto st0;
tr7:
#line 197 "configparser.rl"
	{ spe = Species(); }
	goto st7;
st7:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof7;
case 7:
#line 919 "configparser.h"
	if ( (*( state.p)) == 115 )
		goto tr8;
	goto st0;
tr8:
#line 197 "configparser.rl"
	{ spe = Species(); }
	goto st8;
st8:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof8;
case 8:
#line 931 "configparser.h"
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
#line 973 "configparser.h"
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
#line 190 "configparser.rl"
	{ spe.level = ::atoi(state.match.c_str()); }
	goto st11;
st11:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof11;
case 11:
#line 992 "configparser.h"
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
#line 1030 "configparser.h"
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
#line 193 "configparser.rl"
	{ spe.tag = state.match; }
	goto st13;
st13:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof13;
case 13:
#line 1057 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st13;
		case 32: goto st13;
		case 123: goto tr19;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st13;
	goto st0;
tr17:
#line 193 "configparser.rl"
	{ spe.tag = state.match; }
#line 199 "configparser.rl"
	{{ state.stack[ state.top++] = 673; goto st14;}}
	goto st673;
tr19:
#line 199 "configparser.rl"
	{{ state.stack[ state.top++] = 673; goto st14;}}
	goto st673;
st673:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof673;
case 673:
#line 1080 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr928;
		case 32: goto tr928;
		case 115: goto tr929;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr928;
	goto st0;
tr928:
#line 200 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
	goto st674;
st674:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof674;
case 674:
#line 1097 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st674;
		case 32: goto st674;
		case 115: goto tr2;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st674;
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
		case 105: goto st113;
		case 109: goto st131;
		case 110: goto st149;
		case 114: goto st648;
		case 115: goto st655;
		case 125: goto st661;
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
		case 115: goto st662;
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
#line 154 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st22;
tr57:
#line 177 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st22;
tr68:
#line 166 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
	goto st22;
tr99:
#line 150 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_corner; }
	goto st22;
tr105:
#line 148 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_floor; }
	goto st22;
tr115:
#line 151 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_shoreline; }
	goto st22;
tr121:
#line 149 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_water; }
	goto st22;
tr127:
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st22;
tr133:
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st22;
tr143:
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st22;
tr149:
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st22;
tr153:
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st22;
tr167:
#line 158 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st22;
tr174:
#line 159 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st22;
tr185:
#line 162 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st22;
tr191:
#line 163 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st22;
tr197:
#line 164 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st22;
tr210:
#line 167 "configparser.rl"
	{ spe.name = state.match; }
	goto st22;
tr467:
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st22;
tr472:
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st22;
tr478:
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st22;
tr486:
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st22;
tr490:
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st22;
tr496:
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st22;
tr503:
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st22;
tr906:
#line 173 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st22;
tr914:
#line 184 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st22;
tr926:
#line 155 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st22;
st22:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof22;
case 22:
#line 1306 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st22;
		case 32: goto st22;
		case 59: goto st675;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st22;
	goto st0;
tr38:
#line 154 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st675;
tr60:
#line 177 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st675;
tr70:
#line 166 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
	goto st675;
tr100:
#line 150 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_corner; }
	goto st675;
tr106:
#line 148 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_floor; }
	goto st675;
tr116:
#line 151 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_shoreline; }
	goto st675;
tr122:
#line 149 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_water; }
	goto st675;
tr128:
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st675;
tr134:
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st675;
tr144:
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st675;
tr150:
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st675;
tr154:
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st675;
tr168:
#line 158 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st675;
tr175:
#line 159 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st675;
tr186:
#line 162 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st675;
tr192:
#line 163 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st675;
tr198:
#line 164 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st675;
tr211:
#line 167 "configparser.rl"
	{ spe.name = state.match; }
	goto st675;
tr468:
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st675;
tr473:
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st675;
tr479:
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st675;
tr487:
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st675;
tr491:
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st675;
tr497:
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st675;
tr504:
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st675;
tr908:
#line 173 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st675;
tr915:
#line 184 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st675;
tr927:
#line 155 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st675;
st675:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof675;
case 675:
#line 1431 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st14;
		case 32: goto st14;
		case 97: goto st15;
		case 99: goto st23;
		case 104: goto st46;
		case 105: goto st113;
		case 109: goto st131;
		case 110: goto st149;
		case 114: goto st648;
		case 115: goto st655;
		case 125: goto st661;
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
#line 1551 "configparser.h"
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
#line 176 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st34;
st34:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof34;
case 34:
#line 1571 "configparser.h"
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
#line 1602 "configparser.h"
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
#line 1724 "configparser.h"
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
		case 102: goto st92;
		case 115: goto st97;
		case 119: goto st106;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st53;
	goto st0;
st54:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof54;
case 54:
	switch( (*( state.p)) ) {
		case 108: goto st55;
		case 111: goto st87;
	}
	goto st0;
st55:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof55;
case 55:
	if ( (*( state.p)) == 117 )
		goto st56;
	goto st0;
st56:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof56;
case 56:
	if ( (*( state.p)) == 109 )
		goto st57;
	goto st0;
st57:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof57;
case 57:
	if ( (*( state.p)) == 112 )
		goto st58;
	goto st0;
st58:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof58;
case 58:
	if ( (*( state.p)) == 101 )
		goto st59;
	goto st0;
st59:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof59;
case 59:
	if ( (*( state.p)) == 100 )
		goto st60;
	goto st0;
st60:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof60;
case 60:
	if ( (*( state.p)) == 95 )
		goto st61;
	goto st0;
st61:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof61;
case 61:
	switch( (*( state.p)) ) {
		case 99: goto st62;
		case 102: goto st68;
		case 115: goto st73;
		case 119: goto st82;
	}
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
	if ( (*( state.p)) == 110 )
		goto st65;
	goto st0;
st65:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof65;
case 65:
	if ( (*( state.p)) == 101 )
		goto st66;
	goto st0;
st66:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof66;
case 66:
	if ( (*( state.p)) == 114 )
		goto st67;
	goto st0;
st67:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof67;
case 67:
	switch( (*( state.p)) ) {
		case 13: goto tr99;
		case 32: goto tr99;
		case 59: goto tr100;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr99;
	goto st0;
st68:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof68;
case 68:
	if ( (*( state.p)) == 108 )
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
	if ( (*( state.p)) == 111 )
		goto st71;
	goto st0;
st71:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof71;
case 71:
	if ( (*( state.p)) == 114 )
		goto st72;
	goto st0;
st72:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof72;
case 72:
	switch( (*( state.p)) ) {
		case 13: goto tr105;
		case 32: goto tr105;
		case 59: goto tr106;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr105;
	goto st0;
st73:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof73;
case 73:
	if ( (*( state.p)) == 104 )
		goto st74;
	goto st0;
st74:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof74;
case 74:
	if ( (*( state.p)) == 111 )
		goto st75;
	goto st0;
st75:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof75;
case 75:
	if ( (*( state.p)) == 114 )
		goto st76;
	goto st0;
st76:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof76;
case 76:
	if ( (*( state.p)) == 101 )
		goto st77;
	goto st0;
st77:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof77;
case 77:
	if ( (*( state.p)) == 108 )
		goto st78;
	goto st0;
st78:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof78;
case 78:
	if ( (*( state.p)) == 105 )
		goto st79;
	goto st0;
st79:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof79;
case 79:
	if ( (*( state.p)) == 110 )
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
		case 13: goto tr115;
		case 32: goto tr115;
		case 59: goto tr116;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr115;
	goto st0;
st82:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof82;
case 82:
	if ( (*( state.p)) == 97 )
		goto st83;
	goto st0;
st83:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof83;
case 83:
	if ( (*( state.p)) == 116 )
		goto st84;
	goto st0;
st84:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof84;
case 84:
	if ( (*( state.p)) == 101 )
		goto st85;
	goto st0;
st85:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof85;
case 85:
	if ( (*( state.p)) == 114 )
		goto st86;
	goto st0;
st86:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof86;
case 86:
	switch( (*( state.p)) ) {
		case 13: goto tr121;
		case 32: goto tr121;
		case 59: goto tr122;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr121;
	goto st0;
st87:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof87;
case 87:
	if ( (*( state.p)) == 114 )
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
	if ( (*( state.p)) == 101 )
		goto st90;
	goto st0;
st90:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof90;
case 90:
	if ( (*( state.p)) == 114 )
		goto st91;
	goto st0;
st91:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof91;
case 91:
	switch( (*( state.p)) ) {
		case 13: goto tr127;
		case 32: goto tr127;
		case 59: goto tr128;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr127;
	goto st0;
st92:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof92;
case 92:
	if ( (*( state.p)) == 108 )
		goto st93;
	goto st0;
st93:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof93;
case 93:
	if ( (*( state.p)) == 111 )
		goto st94;
	goto st0;
st94:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof94;
case 94:
	if ( (*( state.p)) == 111 )
		goto st95;
	goto st0;
st95:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof95;
case 95:
	if ( (*( state.p)) == 114 )
		goto st96;
	goto st0;
st96:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof96;
case 96:
	switch( (*( state.p)) ) {
		case 13: goto tr133;
		case 32: goto tr133;
		case 59: goto tr134;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr133;
	goto st0;
st97:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof97;
case 97:
	if ( (*( state.p)) == 104 )
		goto st98;
	goto st0;
st98:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof98;
case 98:
	if ( (*( state.p)) == 111 )
		goto st99;
	goto st0;
st99:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof99;
case 99:
	if ( (*( state.p)) == 114 )
		goto st100;
	goto st0;
st100:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof100;
case 100:
	if ( (*( state.p)) == 101 )
		goto st101;
	goto st0;
st101:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof101;
case 101:
	if ( (*( state.p)) == 108 )
		goto st102;
	goto st0;
st102:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof102;
case 102:
	if ( (*( state.p)) == 105 )
		goto st103;
	goto st0;
st103:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof103;
case 103:
	if ( (*( state.p)) == 110 )
		goto st104;
	goto st0;
st104:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof104;
case 104:
	if ( (*( state.p)) == 101 )
		goto st105;
	goto st0;
st105:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof105;
case 105:
	switch( (*( state.p)) ) {
		case 13: goto tr143;
		case 32: goto tr143;
		case 59: goto tr144;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr143;
	goto st0;
st106:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof106;
case 106:
	if ( (*( state.p)) == 97 )
		goto st107;
	goto st0;
st107:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof107;
case 107:
	switch( (*( state.p)) ) {
		case 108: goto st108;
		case 116: goto st110;
	}
	goto st0;
st108:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof108;
case 108:
	if ( (*( state.p)) == 107 )
		goto st109;
	goto st0;
st109:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof109;
case 109:
	switch( (*( state.p)) ) {
		case 13: goto tr149;
		case 32: goto tr149;
		case 59: goto tr150;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr149;
	goto st0;
st110:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof110;
case 110:
	if ( (*( state.p)) == 101 )
		goto st111;
	goto st0;
st111:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof111;
case 111:
	if ( (*( state.p)) == 114 )
		goto st112;
	goto st0;
st112:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof112;
case 112:
	switch( (*( state.p)) ) {
		case 13: goto tr153;
		case 32: goto tr153;
		case 59: goto tr154;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr153;
	goto st0;
st113:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof113;
case 113:
	if ( (*( state.p)) == 100 )
		goto st114;
	goto st0;
st114:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof114;
case 114:
	if ( (*( state.p)) == 108 )
		goto st115;
	goto st0;
st115:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof115;
case 115:
	if ( (*( state.p)) == 101 )
		goto st116;
	goto st0;
st116:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof116;
case 116:
	if ( (*( state.p)) == 95 )
		goto st117;
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
	if ( (*( state.p)) == 105 )
		goto st119;
	goto st0;
st119:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof119;
case 119:
	switch( (*( state.p)) ) {
		case 13: goto st120;
		case 32: goto st120;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st120;
	goto st0;
st120:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof120;
case 120:
	switch( (*( state.p)) ) {
		case 13: goto st120;
		case 32: goto st120;
		case 110: goto st121;
		case 114: goto st125;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st120;
	goto st0;
st121:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof121;
case 121:
	if ( (*( state.p)) == 111 )
		goto st122;
	goto st0;
st122:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof122;
case 122:
	if ( (*( state.p)) == 110 )
		goto st123;
	goto st0;
st123:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof123;
case 123:
	if ( (*( state.p)) == 101 )
		goto st124;
	goto st0;
st124:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof124;
case 124:
	switch( (*( state.p)) ) {
		case 13: goto tr167;
		case 32: goto tr167;
		case 59: goto tr168;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr167;
	goto st0;
st125:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof125;
case 125:
	if ( (*( state.p)) == 97 )
		goto st126;
	goto st0;
st126:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof126;
case 126:
	if ( (*( state.p)) == 110 )
		goto st127;
	goto st0;
st127:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof127;
case 127:
	if ( (*( state.p)) == 100 )
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
	if ( (*( state.p)) == 109 )
		goto st130;
	goto st0;
st130:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof130;
case 130:
	switch( (*( state.p)) ) {
		case 13: goto tr174;
		case 32: goto tr174;
		case 59: goto tr175;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr174;
	goto st0;
st131:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof131;
case 131:
	if ( (*( state.p)) == 111 )
		goto st132;
	goto st0;
st132:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof132;
case 132:
	if ( (*( state.p)) == 118 )
		goto st133;
	goto st0;
st133:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof133;
case 133:
	if ( (*( state.p)) == 101 )
		goto st134;
	goto st0;
st134:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof134;
case 134:
	switch( (*( state.p)) ) {
		case 13: goto st135;
		case 32: goto st135;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st135;
	goto st0;
st135:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof135;
case 135:
	switch( (*( state.p)) ) {
		case 13: goto st135;
		case 32: goto st135;
		case 97: goto st136;
		case 102: goto st139;
		case 119: goto st144;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st135;
	goto st0;
st136:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof136;
case 136:
	if ( (*( state.p)) == 110 )
		goto st137;
	goto st0;
st137:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof137;
case 137:
	if ( (*( state.p)) == 121 )
		goto st138;
	goto st0;
st138:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof138;
case 138:
	switch( (*( state.p)) ) {
		case 13: goto tr185;
		case 32: goto tr185;
		case 59: goto tr186;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr185;
	goto st0;
st139:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof139;
case 139:
	if ( (*( state.p)) == 108 )
		goto st140;
	goto st0;
st140:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof140;
case 140:
	if ( (*( state.p)) == 111 )
		goto st141;
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
	if ( (*( state.p)) == 114 )
		goto st143;
	goto st0;
st143:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof143;
case 143:
	switch( (*( state.p)) ) {
		case 13: goto tr191;
		case 32: goto tr191;
		case 59: goto tr192;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr191;
	goto st0;
st144:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof144;
case 144:
	if ( (*( state.p)) == 97 )
		goto st145;
	goto st0;
st145:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof145;
case 145:
	if ( (*( state.p)) == 116 )
		goto st146;
	goto st0;
st146:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof146;
case 146:
	if ( (*( state.p)) == 101 )
		goto st147;
	goto st0;
st147:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof147;
case 147:
	if ( (*( state.p)) == 114 )
		goto st148;
	goto st0;
st148:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof148;
case 148:
	switch( (*( state.p)) ) {
		case 13: goto tr197;
		case 32: goto tr197;
		case 59: goto tr198;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr197;
	goto st0;
st149:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof149;
case 149:
	if ( (*( state.p)) == 97 )
		goto st150;
	goto st0;
st150:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof150;
case 150:
	if ( (*( state.p)) == 109 )
		goto st151;
	goto st0;
st151:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof151;
case 151:
	if ( (*( state.p)) == 101 )
		goto st152;
	goto st0;
st152:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof152;
case 152:
	switch( (*( state.p)) ) {
		case 13: goto st153;
		case 32: goto st153;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st153;
	goto st0;
st153:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof153;
case 153:
	switch( (*( state.p)) ) {
		case 13: goto st153;
		case 32: goto st153;
		case 34: goto st154;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st153;
	goto st0;
st154:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof154;
case 154:
	switch( (*( state.p)) ) {
		case 34: goto tr205;
		case 92: goto tr206;
	}
	goto tr204;
tr204:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st155;
tr207:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st155;
st155:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof155;
case 155:
#line 2641 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
	}
	goto tr207;
tr205:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st156;
st156:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof156;
case 156:
#line 2657 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr210;
		case 32: goto tr210;
		case 59: goto tr211;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr210;
	goto st0;
tr206:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st157;
tr209:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st157;
st157:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof157;
case 157:
#line 2686 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr212;
		case 92: goto tr209;
	}
	goto tr207;
tr212:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st158;
st158:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof158;
case 158:
#line 2702 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr213;
		case 32: goto tr213;
		case 34: goto st156;
		case 59: goto tr214;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr213;
	goto tr207;
tr215:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st159;
tr213:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 167 "configparser.rl"
	{ spe.name = state.match; }
	goto st159;
tr234:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st159;
tr246:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 155 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st159;
tr264:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 177 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st159;
tr275:
#line 166 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st159;
tr306:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_corner; }
	goto st159;
tr312:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 148 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_floor; }
	goto st159;
tr322:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_shoreline; }
	goto st159;
tr328:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 149 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_water; }
	goto st159;
tr334:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st159;
tr340:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st159;
tr350:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st159;
tr356:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st159;
tr360:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st159;
tr374:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st159;
tr381:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st159;
tr392:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 162 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st159;
tr398:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 163 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st159;
tr404:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 164 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st159;
tr411:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 167 "configparser.rl"
	{ spe.name = state.match; }
	goto st159;
tr419:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 173 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st159;
tr778:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st159;
tr783:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st159;
tr789:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st159;
tr797:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st159;
tr801:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st159;
tr807:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st159;
tr814:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st159;
tr898:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 184 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st159;
st159:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof159;
case 159:
#line 2959 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr215;
		case 32: goto tr215;
		case 34: goto st156;
		case 59: goto tr216;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr215;
	goto tr207;
tr216:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st676;
tr214:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 167 "configparser.rl"
	{ spe.name = state.match; }
	goto st676;
tr235:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st676;
tr247:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 155 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st676;
tr267:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 177 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st676;
tr277:
#line 166 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st676;
tr307:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_corner; }
	goto st676;
tr313:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 148 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_floor; }
	goto st676;
tr323:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_shoreline; }
	goto st676;
tr329:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 149 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_water; }
	goto st676;
tr335:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st676;
tr341:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st676;
tr351:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st676;
tr357:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st676;
tr361:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st676;
tr375:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st676;
tr382:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st676;
tr393:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 162 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st676;
tr399:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 163 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st676;
tr405:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 164 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st676;
tr412:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 167 "configparser.rl"
	{ spe.name = state.match; }
	goto st676;
tr421:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 173 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st676;
tr779:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st676;
tr784:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st676;
tr790:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st676;
tr798:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st676;
tr802:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st676;
tr808:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st676;
tr815:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st676;
tr899:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 184 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st676;
st676:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof676;
case 676:
#line 3216 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr217;
		case 32: goto tr217;
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr218;
		case 99: goto tr219;
		case 104: goto tr220;
		case 105: goto tr221;
		case 109: goto tr222;
		case 110: goto tr223;
		case 114: goto tr224;
		case 115: goto tr225;
		case 125: goto tr226;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr217;
	goto tr207;
tr217:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st160;
st160:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof160;
case 160:
#line 3245 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr217;
		case 32: goto tr217;
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr218;
		case 99: goto tr219;
		case 104: goto tr220;
		case 105: goto tr221;
		case 109: goto tr222;
		case 110: goto tr223;
		case 114: goto tr224;
		case 115: goto tr225;
		case 125: goto tr226;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr217;
	goto tr207;
tr218:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st161;
st161:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof161;
case 161:
#line 3274 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 105: goto tr227;
	}
	goto tr207;
tr227:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st162;
st162:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof162;
case 162:
#line 3291 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr228;
		case 32: goto tr228;
		case 34: goto st156;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr228;
	goto tr207;
tr228:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st163;
st163:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof163;
case 163:
#line 3311 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr228;
		case 32: goto tr228;
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr229;
		case 115: goto tr230;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr228;
	goto tr207;
tr229:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st164;
st164:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof164;
case 164:
#line 3333 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 111: goto tr231;
	}
	goto tr207;
tr231:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st165;
st165:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof165;
case 165:
#line 3350 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr232;
	}
	goto tr207;
tr232:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st166;
st166:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof166;
case 166:
#line 3367 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr233;
	}
	goto tr207;
tr233:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st167;
st167:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof167;
case 167:
#line 3384 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr234;
		case 32: goto tr234;
		case 34: goto st156;
		case 59: goto tr235;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr234;
	goto tr207;
tr230:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st168;
st168:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof168;
case 168:
#line 3405 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr236;
	}
	goto tr207;
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
#line 3422 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr237;
	}
	goto tr207;
tr237:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st170;
st170:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof170;
case 170:
#line 3439 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 107: goto tr238;
	}
	goto tr207;
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
#line 3456 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 95: goto tr239;
	}
	goto tr207;
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
#line 3473 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 112: goto tr240;
	}
	goto tr207;
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
#line 3490 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 108: goto tr241;
	}
	goto tr207;
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
#line 3507 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr242;
	}
	goto tr207;
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
#line 3524 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 121: goto tr243;
	}
	goto tr207;
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
#line 3541 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr244;
	}
	goto tr207;
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
#line 3558 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 114: goto tr245;
	}
	goto tr207;
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
#line 3575 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr246;
		case 32: goto tr246;
		case 34: goto st156;
		case 59: goto tr247;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr246;
	goto tr207;
tr219:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st179;
st179:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof179;
case 179:
#line 3596 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 108: goto tr248;
		case 111: goto tr249;
	}
	goto tr207;
tr248:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st180;
st180:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof180;
case 180:
#line 3614 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 117: goto tr250;
	}
	goto tr207;
tr250:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st181;
st181:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof181;
case 181:
#line 3631 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 109: goto tr251;
	}
	goto tr207;
tr251:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st182;
st182:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof182;
case 182:
#line 3648 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 112: goto tr252;
	}
	goto tr207;
tr252:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st183;
st183:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof183;
case 183:
#line 3665 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 115: goto tr253;
	}
	goto tr207;
tr253:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st184;
st184:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof184;
case 184:
#line 3682 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 105: goto tr254;
	}
	goto tr207;
tr254:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st185;
st185:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof185;
case 185:
#line 3699 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 122: goto tr255;
	}
	goto tr207;
tr255:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st186;
st186:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof186;
case 186:
#line 3716 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr256;
	}
	goto tr207;
tr256:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st187;
st187:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof187;
case 187:
#line 3733 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr257;
		case 32: goto tr257;
		case 34: goto st156;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr257;
	goto tr207;
tr257:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st188;
st188:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof188;
case 188:
#line 3753 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr257;
		case 32: goto tr257;
		case 34: goto st156;
		case 92: goto tr209;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr258;
	} else if ( (*( state.p)) >= 9 )
		goto tr257;
	goto tr207;
tr261:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st189;
tr258:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st189;
st189:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof189;
case 189:
#line 3786 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr259;
		case 32: goto tr259;
		case 34: goto st156;
		case 46: goto tr260;
		case 92: goto tr209;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr261;
	} else if ( (*( state.p)) >= 9 )
		goto tr259;
	goto tr207;
tr262:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st190;
tr259:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 176 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st190;
st190:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof190;
case 190:
#line 3818 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr262;
		case 32: goto tr262;
		case 34: goto st156;
		case 92: goto tr209;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr263;
	} else if ( (*( state.p)) >= 9 )
		goto tr262;
	goto tr207;
tr266:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st191;
tr263:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st191;
st191:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof191;
case 191:
#line 3851 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr264;
		case 32: goto tr264;
		case 34: goto st156;
		case 46: goto tr265;
		case 59: goto tr267;
		case 92: goto tr209;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr266;
	} else if ( (*( state.p)) >= 9 )
		goto tr264;
	goto tr207;
tr265:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st192;
st192:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof192;
case 192:
#line 3876 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr268;
	goto tr207;
tr268:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st193;
st193:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof193;
case 193:
#line 3894 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr264;
		case 32: goto tr264;
		case 34: goto st156;
		case 59: goto tr267;
		case 92: goto tr209;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr268;
	} else if ( (*( state.p)) >= 9 )
		goto tr264;
	goto tr207;
tr260:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st194;
st194:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof194;
case 194:
#line 3918 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr269;
	goto tr207;
tr269:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st195;
st195:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof195;
case 195:
#line 3936 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr259;
		case 32: goto tr259;
		case 34: goto st156;
		case 92: goto tr209;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr269;
	} else if ( (*( state.p)) >= 9 )
		goto tr259;
	goto tr207;
tr249:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st196;
st196:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof196;
case 196:
#line 3959 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 117: goto tr270;
	}
	goto tr207;
tr270:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st197;
st197:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof197;
case 197:
#line 3976 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr271;
	}
	goto tr207;
tr271:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st198;
st198:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof198;
case 198:
#line 3993 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 116: goto tr272;
	}
	goto tr207;
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
#line 4010 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr273;
		case 32: goto tr273;
		case 34: goto st156;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr273;
	goto tr207;
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
#line 4030 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr273;
		case 32: goto tr273;
		case 34: goto st156;
		case 92: goto tr209;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr274;
	} else if ( (*( state.p)) >= 9 )
		goto tr273;
	goto tr207;
tr274:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st201;
tr276:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st201;
st201:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof201;
case 201:
#line 4063 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr275;
		case 32: goto tr275;
		case 34: goto st156;
		case 59: goto tr277;
		case 92: goto tr209;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr276;
	} else if ( (*( state.p)) >= 9 )
		goto tr275;
	goto tr207;
tr220:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st202;
st202:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof202;
case 202:
#line 4087 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr278;
	}
	goto tr207;
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
#line 4104 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 98: goto tr279;
	}
	goto tr207;
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
#line 4121 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 105: goto tr280;
	}
	goto tr207;
tr280:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st205;
st205:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof205;
case 205:
#line 4138 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 116: goto tr281;
	}
	goto tr207;
tr281:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st206;
st206:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof206;
case 206:
#line 4155 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr282;
	}
	goto tr207;
tr282:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st207;
st207:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof207;
case 207:
#line 4172 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 116: goto tr283;
	}
	goto tr207;
tr283:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st208;
st208:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof208;
case 208:
#line 4189 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr284;
		case 32: goto tr284;
		case 34: goto st156;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr284;
	goto tr207;
tr284:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st209;
st209:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof209;
case 209:
#line 4209 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr284;
		case 32: goto tr284;
		case 34: goto st156;
		case 92: goto tr209;
		case 99: goto tr285;
		case 102: goto tr286;
		case 115: goto tr287;
		case 119: goto tr288;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr284;
	goto tr207;
tr285:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st210;
st210:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof210;
case 210:
#line 4233 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 108: goto tr289;
		case 111: goto tr290;
	}
	goto tr207;
tr289:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st211;
st211:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof211;
case 211:
#line 4251 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 117: goto tr291;
	}
	goto tr207;
tr291:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st212;
st212:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof212;
case 212:
#line 4268 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 109: goto tr292;
	}
	goto tr207;
tr292:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st213;
st213:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof213;
case 213:
#line 4285 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 112: goto tr293;
	}
	goto tr207;
tr293:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st214;
st214:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof214;
case 214:
#line 4302 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr294;
	}
	goto tr207;
tr294:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st215;
st215:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof215;
case 215:
#line 4319 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 100: goto tr295;
	}
	goto tr207;
tr295:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st216;
st216:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof216;
case 216:
#line 4336 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 95: goto tr296;
	}
	goto tr207;
tr296:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st217;
st217:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof217;
case 217:
#line 4353 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 99: goto tr297;
		case 102: goto tr298;
		case 115: goto tr299;
		case 119: goto tr300;
	}
	goto tr207;
tr297:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st218;
st218:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof218;
case 218:
#line 4373 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 111: goto tr301;
	}
	goto tr207;
tr301:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st219;
st219:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof219;
case 219:
#line 4390 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 114: goto tr302;
	}
	goto tr207;
tr302:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st220;
st220:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof220;
case 220:
#line 4407 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr303;
	}
	goto tr207;
tr303:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st221;
st221:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof221;
case 221:
#line 4424 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr304;
	}
	goto tr207;
tr304:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st222;
st222:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof222;
case 222:
#line 4441 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 114: goto tr305;
	}
	goto tr207;
tr305:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st223;
st223:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof223;
case 223:
#line 4458 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr306;
		case 32: goto tr306;
		case 34: goto st156;
		case 59: goto tr307;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr306;
	goto tr207;
tr298:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st224;
st224:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof224;
case 224:
#line 4479 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 108: goto tr308;
	}
	goto tr207;
tr308:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st225;
st225:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof225;
case 225:
#line 4496 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 111: goto tr309;
	}
	goto tr207;
tr309:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st226;
st226:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof226;
case 226:
#line 4513 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 111: goto tr310;
	}
	goto tr207;
tr310:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st227;
st227:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof227;
case 227:
#line 4530 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 114: goto tr311;
	}
	goto tr207;
tr311:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st228;
st228:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof228;
case 228:
#line 4547 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr312;
		case 32: goto tr312;
		case 34: goto st156;
		case 59: goto tr313;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr312;
	goto tr207;
tr299:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st229;
st229:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof229;
case 229:
#line 4568 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 104: goto tr314;
	}
	goto tr207;
tr314:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st230;
st230:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof230;
case 230:
#line 4585 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 111: goto tr315;
	}
	goto tr207;
tr315:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st231;
st231:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof231;
case 231:
#line 4602 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 114: goto tr316;
	}
	goto tr207;
tr316:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st232;
st232:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof232;
case 232:
#line 4619 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr317;
	}
	goto tr207;
tr317:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st233;
st233:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof233;
case 233:
#line 4636 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 108: goto tr318;
	}
	goto tr207;
tr318:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st234;
st234:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof234;
case 234:
#line 4653 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 105: goto tr319;
	}
	goto tr207;
tr319:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st235;
st235:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof235;
case 235:
#line 4670 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr320;
	}
	goto tr207;
tr320:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st236;
st236:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof236;
case 236:
#line 4687 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr321;
	}
	goto tr207;
tr321:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st237;
st237:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof237;
case 237:
#line 4704 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr322;
		case 32: goto tr322;
		case 34: goto st156;
		case 59: goto tr323;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr322;
	goto tr207;
tr300:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st238;
st238:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof238;
case 238:
#line 4725 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr324;
	}
	goto tr207;
tr324:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st239;
st239:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof239;
case 239:
#line 4742 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 116: goto tr325;
	}
	goto tr207;
tr325:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st240;
st240:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof240;
case 240:
#line 4759 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr326;
	}
	goto tr207;
tr326:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st241;
st241:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof241;
case 241:
#line 4776 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 114: goto tr327;
	}
	goto tr207;
tr327:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st242;
st242:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof242;
case 242:
#line 4793 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr328;
		case 32: goto tr328;
		case 34: goto st156;
		case 59: goto tr329;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr328;
	goto tr207;
tr290:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st243;
st243:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof243;
case 243:
#line 4814 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 114: goto tr330;
	}
	goto tr207;
tr330:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st244;
st244:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof244;
case 244:
#line 4831 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr331;
	}
	goto tr207;
tr331:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st245;
st245:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof245;
case 245:
#line 4848 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr332;
	}
	goto tr207;
tr332:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st246;
st246:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof246;
case 246:
#line 4865 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 114: goto tr333;
	}
	goto tr207;
tr333:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st247;
st247:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof247;
case 247:
#line 4882 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr334;
		case 32: goto tr334;
		case 34: goto st156;
		case 59: goto tr335;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr334;
	goto tr207;
tr286:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st248;
st248:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof248;
case 248:
#line 4903 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 108: goto tr336;
	}
	goto tr207;
tr336:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st249;
st249:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof249;
case 249:
#line 4920 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 111: goto tr337;
	}
	goto tr207;
tr337:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st250;
st250:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof250;
case 250:
#line 4937 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 111: goto tr338;
	}
	goto tr207;
tr338:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st251;
st251:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof251;
case 251:
#line 4954 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 114: goto tr339;
	}
	goto tr207;
tr339:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st252;
st252:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof252;
case 252:
#line 4971 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr340;
		case 32: goto tr340;
		case 34: goto st156;
		case 59: goto tr341;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr340;
	goto tr207;
tr287:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st253;
st253:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof253;
case 253:
#line 4992 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 104: goto tr342;
	}
	goto tr207;
tr342:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st254;
st254:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof254;
case 254:
#line 5009 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 111: goto tr343;
	}
	goto tr207;
tr343:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st255;
st255:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof255;
case 255:
#line 5026 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 114: goto tr344;
	}
	goto tr207;
tr344:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st256;
st256:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof256;
case 256:
#line 5043 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr345;
	}
	goto tr207;
tr345:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st257;
st257:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof257;
case 257:
#line 5060 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 108: goto tr346;
	}
	goto tr207;
tr346:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st258;
st258:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof258;
case 258:
#line 5077 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 105: goto tr347;
	}
	goto tr207;
tr347:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st259;
st259:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof259;
case 259:
#line 5094 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr348;
	}
	goto tr207;
tr348:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st260;
st260:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof260;
case 260:
#line 5111 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr349;
	}
	goto tr207;
tr349:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st261;
st261:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof261;
case 261:
#line 5128 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr350;
		case 32: goto tr350;
		case 34: goto st156;
		case 59: goto tr351;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr350;
	goto tr207;
tr288:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st262;
st262:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof262;
case 262:
#line 5149 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr352;
	}
	goto tr207;
tr352:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st263;
st263:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof263;
case 263:
#line 5166 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 108: goto tr353;
		case 116: goto tr354;
	}
	goto tr207;
tr353:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st264;
st264:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof264;
case 264:
#line 5184 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 107: goto tr355;
	}
	goto tr207;
tr355:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st265;
st265:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof265;
case 265:
#line 5201 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr356;
		case 32: goto tr356;
		case 34: goto st156;
		case 59: goto tr357;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr356;
	goto tr207;
tr354:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st266;
st266:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof266;
case 266:
#line 5222 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr358;
	}
	goto tr207;
tr358:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st267;
st267:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof267;
case 267:
#line 5239 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 114: goto tr359;
	}
	goto tr207;
tr359:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st268;
st268:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof268;
case 268:
#line 5256 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr360;
		case 32: goto tr360;
		case 34: goto st156;
		case 59: goto tr361;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr360;
	goto tr207;
tr221:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st269;
st269:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof269;
case 269:
#line 5277 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 100: goto tr362;
	}
	goto tr207;
tr362:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st270;
st270:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof270;
case 270:
#line 5294 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 108: goto tr363;
	}
	goto tr207;
tr363:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st271;
st271:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof271;
case 271:
#line 5311 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr364;
	}
	goto tr207;
tr364:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st272;
st272:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof272;
case 272:
#line 5328 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 95: goto tr365;
	}
	goto tr207;
tr365:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st273;
st273:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof273;
case 273:
#line 5345 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr366;
	}
	goto tr207;
tr366:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st274;
st274:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof274;
case 274:
#line 5362 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 105: goto tr367;
	}
	goto tr207;
tr367:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st275;
st275:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof275;
case 275:
#line 5379 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr368;
		case 32: goto tr368;
		case 34: goto st156;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr368;
	goto tr207;
tr368:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st276;
st276:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof276;
case 276:
#line 5399 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr368;
		case 32: goto tr368;
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr369;
		case 114: goto tr370;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr368;
	goto tr207;
tr369:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st277;
st277:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof277;
case 277:
#line 5421 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 111: goto tr371;
	}
	goto tr207;
tr371:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st278;
st278:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof278;
case 278:
#line 5438 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr372;
	}
	goto tr207;
tr372:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st279;
st279:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof279;
case 279:
#line 5455 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr373;
	}
	goto tr207;
tr373:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st280;
st280:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof280;
case 280:
#line 5472 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr374;
		case 32: goto tr374;
		case 34: goto st156;
		case 59: goto tr375;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr374;
	goto tr207;
tr370:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st281;
st281:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof281;
case 281:
#line 5493 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr376;
	}
	goto tr207;
tr376:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st282;
st282:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof282;
case 282:
#line 5510 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr377;
	}
	goto tr207;
tr377:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st283;
st283:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof283;
case 283:
#line 5527 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 100: goto tr378;
	}
	goto tr207;
tr378:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st284;
st284:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof284;
case 284:
#line 5544 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 111: goto tr379;
	}
	goto tr207;
tr379:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st285;
st285:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof285;
case 285:
#line 5561 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 109: goto tr380;
	}
	goto tr207;
tr380:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st286;
st286:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof286;
case 286:
#line 5578 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr381;
		case 32: goto tr381;
		case 34: goto st156;
		case 59: goto tr382;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr381;
	goto tr207;
tr222:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st287;
st287:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof287;
case 287:
#line 5599 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 111: goto tr383;
	}
	goto tr207;
tr383:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st288;
st288:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof288;
case 288:
#line 5616 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 118: goto tr384;
	}
	goto tr207;
tr384:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st289;
st289:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof289;
case 289:
#line 5633 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr385;
	}
	goto tr207;
tr385:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st290;
st290:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof290;
case 290:
#line 5650 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr386;
		case 32: goto tr386;
		case 34: goto st156;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr386;
	goto tr207;
tr386:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st291;
st291:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof291;
case 291:
#line 5670 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr386;
		case 32: goto tr386;
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr387;
		case 102: goto tr388;
		case 119: goto tr389;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr386;
	goto tr207;
tr387:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st292;
st292:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof292;
case 292:
#line 5693 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr390;
	}
	goto tr207;
tr390:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st293;
st293:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof293;
case 293:
#line 5710 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 121: goto tr391;
	}
	goto tr207;
tr391:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st294;
st294:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof294;
case 294:
#line 5727 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr392;
		case 32: goto tr392;
		case 34: goto st156;
		case 59: goto tr393;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr392;
	goto tr207;
tr388:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st295;
st295:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof295;
case 295:
#line 5748 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 108: goto tr394;
	}
	goto tr207;
tr394:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st296;
st296:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof296;
case 296:
#line 5765 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 111: goto tr395;
	}
	goto tr207;
tr395:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st297;
st297:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof297;
case 297:
#line 5782 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 111: goto tr396;
	}
	goto tr207;
tr396:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st298;
st298:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof298;
case 298:
#line 5799 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 114: goto tr397;
	}
	goto tr207;
tr397:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st299;
st299:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof299;
case 299:
#line 5816 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr398;
		case 32: goto tr398;
		case 34: goto st156;
		case 59: goto tr399;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr398;
	goto tr207;
tr389:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st300;
st300:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof300;
case 300:
#line 5837 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr400;
	}
	goto tr207;
tr400:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st301;
st301:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof301;
case 301:
#line 5854 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 116: goto tr401;
	}
	goto tr207;
tr401:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st302;
st302:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof302;
case 302:
#line 5871 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr402;
	}
	goto tr207;
tr402:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st303;
st303:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof303;
case 303:
#line 5888 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 114: goto tr403;
	}
	goto tr207;
tr403:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st304;
st304:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof304;
case 304:
#line 5905 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr404;
		case 32: goto tr404;
		case 34: goto st156;
		case 59: goto tr405;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr404;
	goto tr207;
tr223:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st305;
st305:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof305;
case 305:
#line 5926 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr406;
	}
	goto tr207;
tr406:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st306;
st306:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof306;
case 306:
#line 5943 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 109: goto tr407;
	}
	goto tr207;
tr407:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st307;
st307:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof307;
case 307:
#line 5960 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr408;
	}
	goto tr207;
tr408:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st308;
st308:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof308;
case 308:
#line 5977 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr409;
		case 32: goto tr409;
		case 34: goto st156;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr409;
	goto tr207;
tr409:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st309;
st309:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof309;
case 309:
#line 5997 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr409;
		case 32: goto tr409;
		case 34: goto st310;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr409;
	goto tr207;
st310:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof310;
case 310:
	switch( (*( state.p)) ) {
		case 13: goto tr411;
		case 32: goto tr411;
		case 34: goto tr205;
		case 59: goto tr412;
		case 92: goto tr206;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr411;
	goto tr204;
tr224:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st311;
st311:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof311;
case 311:
#line 6031 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr413;
	}
	goto tr207;
tr413:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st312;
st312:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof312;
case 312:
#line 6048 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr414;
	}
	goto tr207;
tr414:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st313;
st313:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof313;
case 313:
#line 6065 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 103: goto tr415;
	}
	goto tr207;
tr415:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st314;
st314:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof314;
case 314:
#line 6082 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr416;
	}
	goto tr207;
tr416:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st315;
st315:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof315;
case 315:
#line 6099 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr417;
		case 32: goto tr417;
		case 34: goto st156;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr417;
	goto tr207;
tr417:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st316;
st316:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof316;
case 316:
#line 6119 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr417;
		case 32: goto tr417;
		case 34: goto st156;
		case 92: goto tr209;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr418;
	} else if ( (*( state.p)) >= 9 )
		goto tr417;
	goto tr207;
tr420:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st317;
tr418:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st317;
st317:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof317;
case 317:
#line 6152 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr419;
		case 32: goto tr419;
		case 34: goto st156;
		case 59: goto tr421;
		case 92: goto tr209;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr420;
	} else if ( (*( state.p)) >= 9 )
		goto tr419;
	goto tr207;
tr225:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st318;
st318:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof318;
case 318:
#line 6176 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 107: goto tr422;
	}
	goto tr207;
tr422:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st319;
st319:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof319;
case 319:
#line 6193 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 105: goto tr423;
	}
	goto tr207;
tr423:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st320;
st320:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof320;
case 320:
#line 6210 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr424;
	}
	goto tr207;
tr424:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st321;
st321:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof321;
case 321:
#line 6227 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr425;
		case 32: goto tr425;
		case 34: goto st156;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr425;
	goto tr207;
tr425:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st322;
st322:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof322;
case 322:
#line 6247 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr425;
		case 32: goto tr425;
		case 34: goto st323;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr425;
	goto tr207;
st323:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof323;
case 323:
	switch( (*( state.p)) ) {
		case 13: goto tr428;
		case 32: goto tr428;
		case 34: goto tr429;
		case 59: goto tr430;
		case 92: goto tr431;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr428;
	goto tr427;
tr427:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st324;
tr432:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st324;
st324:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof324;
case 324:
#line 6291 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
	}
	goto tr432;
tr429:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st325;
st325:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof325;
case 325:
#line 6307 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr435;
		case 32: goto tr435;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr435;
	goto st0;
tr435:
#line 140 "configparser.rl"
	{ spe.skin.text = state.match; }
	goto st326;
st326:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof326;
case 326:
#line 6323 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st326;
		case 32: goto st326;
		case 98: goto st327;
		case 100: goto st371;
		case 110: goto st374;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st326;
	goto st0;
st327:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof327;
case 327:
	if ( (*( state.p)) == 114 )
		goto st328;
	goto st0;
st328:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof328;
case 328:
	if ( (*( state.p)) == 105 )
		goto st329;
	goto st0;
st329:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof329;
case 329:
	if ( (*( state.p)) == 103 )
		goto st330;
	goto st0;
st330:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof330;
case 330:
	if ( (*( state.p)) == 104 )
		goto st331;
	goto st0;
st331:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof331;
case 331:
	if ( (*( state.p)) == 116 )
		goto st332;
	goto st0;
st332:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof332;
case 332:
	switch( (*( state.p)) ) {
		case 13: goto tr445;
		case 32: goto tr445;
		case 95: goto tr446;
		case 98: goto tr447;
		case 99: goto tr448;
		case 103: goto tr449;
		case 109: goto tr450;
		case 114: goto tr451;
		case 119: goto tr452;
		case 121: goto tr453;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr445;
	goto st0;
tr445:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st333;
tr507:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st333;
st333:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof333;
case 333:
#line 6400 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st333;
		case 32: goto st333;
		case 98: goto st334;
		case 99: goto st340;
		case 103: goto st344;
		case 109: goto st349;
		case 114: goto st356;
		case 119: goto st359;
		case 121: goto st364;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st333;
	goto st0;
tr447:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st334;
tr509:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st334;
st334:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof334;
case 334:
#line 6427 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st335;
	goto st0;
st335:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof335;
case 335:
	switch( (*( state.p)) ) {
		case 97: goto st336;
		case 117: goto st338;
	}
	goto st0;
st336:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof336;
case 336:
	if ( (*( state.p)) == 99 )
		goto st337;
	goto st0;
st337:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof337;
case 337:
	if ( (*( state.p)) == 107 )
		goto st22;
	goto st0;
st338:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof338;
case 338:
	if ( (*( state.p)) == 101 )
		goto st339;
	goto st0;
st339:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof339;
case 339:
	switch( (*( state.p)) ) {
		case 13: goto tr467;
		case 32: goto tr467;
		case 59: goto tr468;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr467;
	goto st0;
tr448:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st340;
tr510:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st340;
st340:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof340;
case 340:
#line 6485 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st341;
	goto st0;
st341:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof341;
case 341:
	if ( (*( state.p)) == 97 )
		goto st342;
	goto st0;
st342:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof342;
case 342:
	if ( (*( state.p)) == 110 )
		goto st343;
	goto st0;
st343:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof343;
case 343:
	switch( (*( state.p)) ) {
		case 13: goto tr472;
		case 32: goto tr472;
		case 59: goto tr473;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr472;
	goto st0;
tr449:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st344;
tr511:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st344;
st344:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof344;
case 344:
#line 6527 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st345;
	goto st0;
st345:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof345;
case 345:
	if ( (*( state.p)) == 101 )
		goto st346;
	goto st0;
st346:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof346;
case 346:
	if ( (*( state.p)) == 101 )
		goto st347;
	goto st0;
st347:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof347;
case 347:
	if ( (*( state.p)) == 110 )
		goto st348;
	goto st0;
st348:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof348;
case 348:
	switch( (*( state.p)) ) {
		case 13: goto tr478;
		case 32: goto tr478;
		case 59: goto tr479;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr478;
	goto st0;
tr450:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st349;
tr512:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st349;
st349:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof349;
case 349:
#line 6576 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st350;
	goto st0;
st350:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof350;
case 350:
	if ( (*( state.p)) == 103 )
		goto st351;
	goto st0;
st351:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof351;
case 351:
	if ( (*( state.p)) == 101 )
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
	if ( (*( state.p)) == 116 )
		goto st354;
	goto st0;
st354:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof354;
case 354:
	if ( (*( state.p)) == 97 )
		goto st355;
	goto st0;
st355:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof355;
case 355:
	switch( (*( state.p)) ) {
		case 13: goto tr486;
		case 32: goto tr486;
		case 59: goto tr487;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr486;
	goto st0;
tr451:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st356;
tr513:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st356;
st356:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof356;
case 356:
#line 6639 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st357;
	goto st0;
st357:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof357;
case 357:
	if ( (*( state.p)) == 100 )
		goto st358;
	goto st0;
st358:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof358;
case 358:
	switch( (*( state.p)) ) {
		case 13: goto tr490;
		case 32: goto tr490;
		case 59: goto tr491;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr490;
	goto st0;
tr452:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st359;
tr514:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st359;
st359:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof359;
case 359:
#line 6674 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st360;
	goto st0;
st360:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof360;
case 360:
	if ( (*( state.p)) == 105 )
		goto st361;
	goto st0;
st361:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof361;
case 361:
	if ( (*( state.p)) == 116 )
		goto st362;
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
		case 13: goto tr496;
		case 32: goto tr496;
		case 59: goto tr497;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr496;
	goto st0;
tr453:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st364;
tr515:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st364;
st364:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof364;
case 364:
#line 6723 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st365;
	goto st0;
st365:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof365;
case 365:
	if ( (*( state.p)) == 108 )
		goto st366;
	goto st0;
st366:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof366;
case 366:
	if ( (*( state.p)) == 108 )
		goto st367;
	goto st0;
st367:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof367;
case 367:
	if ( (*( state.p)) == 111 )
		goto st368;
	goto st0;
st368:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof368;
case 368:
	if ( (*( state.p)) == 119 )
		goto st369;
	goto st0;
st369:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof369;
case 369:
	switch( (*( state.p)) ) {
		case 13: goto tr503;
		case 32: goto tr503;
		case 59: goto tr504;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr503;
	goto st0;
tr446:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st370;
tr508:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st370;
st370:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof370;
case 370:
#line 6779 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st334;
		case 99: goto st340;
		case 103: goto st344;
		case 109: goto st349;
		case 114: goto st356;
		case 119: goto st359;
		case 121: goto st364;
	}
	goto st0;
st371:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof371;
case 371:
	if ( (*( state.p)) == 105 )
		goto st372;
	goto st0;
st372:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof372;
case 372:
	if ( (*( state.p)) == 109 )
		goto st373;
	goto st0;
st373:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof373;
case 373:
	switch( (*( state.p)) ) {
		case 13: goto tr507;
		case 32: goto tr507;
		case 95: goto tr508;
		case 98: goto tr509;
		case 99: goto tr510;
		case 103: goto tr511;
		case 109: goto tr512;
		case 114: goto tr513;
		case 119: goto tr514;
		case 121: goto tr515;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr507;
	goto st0;
st374:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof374;
case 374:
	if ( (*( state.p)) == 111 )
		goto st375;
	goto st0;
st375:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof375;
case 375:
	if ( (*( state.p)) == 110 )
		goto st376;
	goto st0;
st376:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof376;
case 376:
	if ( (*( state.p)) == 101 )
		goto st22;
	goto st0;
tr431:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st377;
tr434:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st377;
st377:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof377;
case 377:
#line 6864 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr518;
		case 92: goto tr434;
	}
	goto tr432;
tr518:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st378;
st378:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof378;
case 378:
#line 6880 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr519;
		case 32: goto tr519;
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr519;
	goto tr432;
tr520:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st379;
tr519:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 140 "configparser.rl"
	{ spe.skin.text = state.match; }
	goto st379;
tr843:
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
	goto st379;
st379:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof379;
case 379:
#line 6920 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr520;
		case 32: goto tr520;
		case 34: goto st325;
		case 92: goto tr434;
		case 98: goto tr521;
		case 100: goto tr522;
		case 110: goto tr523;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr520;
	goto tr432;
tr521:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st380;
st380:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof380;
case 380:
#line 6943 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 114: goto tr524;
	}
	goto tr432;
tr524:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st381;
st381:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof381;
case 381:
#line 6960 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 105: goto tr525;
	}
	goto tr432;
tr525:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st382;
st382:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof382;
case 382:
#line 6977 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 103: goto tr526;
	}
	goto tr432;
tr526:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st383;
st383:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof383;
case 383:
#line 6994 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 104: goto tr527;
	}
	goto tr432;
tr527:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st384;
st384:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof384;
case 384:
#line 7011 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 116: goto tr528;
	}
	goto tr432;
tr528:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st385;
st385:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof385;
case 385:
#line 7028 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr529;
		case 32: goto tr529;
		case 34: goto st325;
		case 92: goto tr434;
		case 95: goto tr530;
		case 98: goto tr531;
		case 99: goto tr532;
		case 103: goto tr533;
		case 109: goto tr534;
		case 114: goto tr535;
		case 119: goto tr536;
		case 121: goto tr537;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr529;
	goto tr432;
tr538:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st386;
tr529:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st386;
tr887:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st386;
st386:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof386;
case 386:
#line 7072 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr538;
		case 32: goto tr538;
		case 34: goto st325;
		case 92: goto tr434;
		case 98: goto tr539;
		case 99: goto tr540;
		case 103: goto tr541;
		case 109: goto tr542;
		case 114: goto tr543;
		case 119: goto tr544;
		case 121: goto tr545;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr538;
	goto tr432;
tr539:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st387;
tr531:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st387;
tr889:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st387;
st387:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof387;
case 387:
#line 7115 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 108: goto tr546;
	}
	goto tr432;
tr546:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st388;
st388:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof388;
case 388:
#line 7132 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr547;
		case 117: goto tr548;
	}
	goto tr432;
tr547:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st389;
st389:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof389;
case 389:
#line 7150 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 99: goto tr549;
	}
	goto tr432;
tr549:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st390;
st390:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof390;
case 390:
#line 7167 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 107: goto tr550;
	}
	goto tr432;
tr550:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st391;
tr569:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st391;
tr581:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 155 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st391;
tr599:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 177 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st391;
tr610:
#line 166 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st391;
tr641:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_corner; }
	goto st391;
tr647:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 148 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_floor; }
	goto st391;
tr657:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_shoreline; }
	goto st391;
tr663:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 149 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_water; }
	goto st391;
tr669:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st391;
tr675:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st391;
tr685:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st391;
tr691:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st391;
tr695:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st391;
tr709:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st391;
tr716:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st391;
tr727:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 162 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st391;
tr733:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 163 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st391;
tr739:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 164 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st391;
tr835:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 173 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st391;
tr428:
#line 167 "configparser.rl"
	{ spe.name = state.match; }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st391;
tr847:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st391;
tr852:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st391;
tr858:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st391;
tr866:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st391;
tr870:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st391;
tr876:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st391;
tr883:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st391;
tr844:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 184 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st391;
st391:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof391;
case 391:
#line 7412 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr550;
		case 32: goto tr550;
		case 34: goto st325;
		case 59: goto tr551;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr550;
	goto tr432;
tr551:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st677;
tr570:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st677;
tr582:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 155 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st677;
tr602:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 177 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st677;
tr612:
#line 166 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st677;
tr642:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_corner; }
	goto st677;
tr648:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 148 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_floor; }
	goto st677;
tr658:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_shoreline; }
	goto st677;
tr664:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 149 "configparser.rl"
	{ spe.habitat = Species::habitat_t::clumped_water; }
	goto st677;
tr670:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st677;
tr676:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st677;
tr686:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st677;
tr692:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st677;
tr696:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st677;
tr710:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st677;
tr717:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st677;
tr728:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 162 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st677;
tr734:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 163 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st677;
tr740:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 164 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st677;
tr837:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 173 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st677;
tr430:
#line 167 "configparser.rl"
	{ spe.name = state.match; }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st677;
tr848:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st677;
tr853:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st677;
tr859:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st677;
tr867:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st677;
tr871:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st677;
tr877:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st677;
tr884:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st677;
tr845:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 184 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st677;
st677:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof677;
case 677:
#line 7661 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr552;
		case 32: goto tr552;
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr553;
		case 99: goto tr554;
		case 104: goto tr555;
		case 105: goto tr556;
		case 109: goto tr557;
		case 110: goto tr558;
		case 114: goto tr559;
		case 115: goto tr560;
		case 125: goto tr561;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr552;
	goto tr432;
tr552:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st392;
st392:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof392;
case 392:
#line 7690 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr552;
		case 32: goto tr552;
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr553;
		case 99: goto tr554;
		case 104: goto tr555;
		case 105: goto tr556;
		case 109: goto tr557;
		case 110: goto tr558;
		case 114: goto tr559;
		case 115: goto tr560;
		case 125: goto tr561;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr552;
	goto tr432;
tr553:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st393;
st393:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof393;
case 393:
#line 7719 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 105: goto tr562;
	}
	goto tr432;
tr562:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st394;
st394:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof394;
case 394:
#line 7736 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr563;
		case 32: goto tr563;
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr563;
	goto tr432;
tr563:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st395;
st395:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof395;
case 395:
#line 7756 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr563;
		case 32: goto tr563;
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr564;
		case 115: goto tr565;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr563;
	goto tr432;
tr564:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st396;
st396:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof396;
case 396:
#line 7778 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 111: goto tr566;
	}
	goto tr432;
tr566:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st397;
st397:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof397;
case 397:
#line 7795 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr567;
	}
	goto tr432;
tr567:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st398;
st398:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof398;
case 398:
#line 7812 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr568;
	}
	goto tr432;
tr568:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st399;
st399:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof399;
case 399:
#line 7829 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr569;
		case 32: goto tr569;
		case 34: goto st325;
		case 59: goto tr570;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr569;
	goto tr432;
tr565:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st400;
st400:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof400;
case 400:
#line 7850 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr571;
	}
	goto tr432;
tr571:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st401;
st401:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof401;
case 401:
#line 7867 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr572;
	}
	goto tr432;
tr572:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st402;
st402:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof402;
case 402:
#line 7884 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 107: goto tr573;
	}
	goto tr432;
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
#line 7901 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 95: goto tr574;
	}
	goto tr432;
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
#line 7918 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 112: goto tr575;
	}
	goto tr432;
tr575:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st405;
st405:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof405;
case 405:
#line 7935 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 108: goto tr576;
	}
	goto tr432;
tr576:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st406;
st406:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof406;
case 406:
#line 7952 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr577;
	}
	goto tr432;
tr577:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st407;
st407:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof407;
case 407:
#line 7969 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 121: goto tr578;
	}
	goto tr432;
tr578:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st408;
st408:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof408;
case 408:
#line 7986 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr579;
	}
	goto tr432;
tr579:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st409;
st409:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof409;
case 409:
#line 8003 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 114: goto tr580;
	}
	goto tr432;
tr580:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st410;
st410:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof410;
case 410:
#line 8020 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr581;
		case 32: goto tr581;
		case 34: goto st325;
		case 59: goto tr582;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr581;
	goto tr432;
tr554:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st411;
st411:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof411;
case 411:
#line 8041 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 108: goto tr583;
		case 111: goto tr584;
	}
	goto tr432;
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
#line 8059 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 117: goto tr585;
	}
	goto tr432;
tr585:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st413;
st413:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof413;
case 413:
#line 8076 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 109: goto tr586;
	}
	goto tr432;
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
#line 8093 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 112: goto tr587;
	}
	goto tr432;
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
#line 8110 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 115: goto tr588;
	}
	goto tr432;
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
#line 8127 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 105: goto tr589;
	}
	goto tr432;
tr589:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st417;
st417:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof417;
case 417:
#line 8144 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 122: goto tr590;
	}
	goto tr432;
tr590:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st418;
st418:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof418;
case 418:
#line 8161 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr591;
	}
	goto tr432;
tr591:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st419;
st419:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof419;
case 419:
#line 8178 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr592;
		case 32: goto tr592;
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr592;
	goto tr432;
tr592:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st420;
st420:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof420;
case 420:
#line 8198 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr592;
		case 32: goto tr592;
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr593;
	} else if ( (*( state.p)) >= 9 )
		goto tr592;
	goto tr432;
tr596:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st421;
tr593:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st421;
st421:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof421;
case 421:
#line 8231 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr594;
		case 32: goto tr594;
		case 34: goto st325;
		case 46: goto tr595;
		case 92: goto tr434;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr596;
	} else if ( (*( state.p)) >= 9 )
		goto tr594;
	goto tr432;
tr597:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st422;
tr594:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 176 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st422;
st422:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof422;
case 422:
#line 8263 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr597;
		case 32: goto tr597;
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr598;
	} else if ( (*( state.p)) >= 9 )
		goto tr597;
	goto tr432;
tr601:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st423;
tr598:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st423;
st423:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof423;
case 423:
#line 8296 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr599;
		case 32: goto tr599;
		case 34: goto st325;
		case 46: goto tr600;
		case 59: goto tr602;
		case 92: goto tr434;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr601;
	} else if ( (*( state.p)) >= 9 )
		goto tr599;
	goto tr432;
tr600:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st424;
st424:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof424;
case 424:
#line 8321 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr603;
	goto tr432;
tr603:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st425;
st425:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof425;
case 425:
#line 8339 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr599;
		case 32: goto tr599;
		case 34: goto st325;
		case 59: goto tr602;
		case 92: goto tr434;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr603;
	} else if ( (*( state.p)) >= 9 )
		goto tr599;
	goto tr432;
tr595:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st426;
st426:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof426;
case 426:
#line 8363 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr604;
	goto tr432;
tr604:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st427;
st427:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof427;
case 427:
#line 8381 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr594;
		case 32: goto tr594;
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr604;
	} else if ( (*( state.p)) >= 9 )
		goto tr594;
	goto tr432;
tr584:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st428;
st428:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof428;
case 428:
#line 8404 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 117: goto tr605;
	}
	goto tr432;
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
#line 8421 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr606;
	}
	goto tr432;
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
#line 8438 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 116: goto tr607;
	}
	goto tr432;
tr607:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st431;
st431:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof431;
case 431:
#line 8455 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr608;
		case 32: goto tr608;
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr608;
	goto tr432;
tr608:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st432;
st432:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof432;
case 432:
#line 8475 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr608;
		case 32: goto tr608;
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr609;
	} else if ( (*( state.p)) >= 9 )
		goto tr608;
	goto tr432;
tr609:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st433;
tr611:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st433;
st433:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof433;
case 433:
#line 8508 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr610;
		case 32: goto tr610;
		case 34: goto st325;
		case 59: goto tr612;
		case 92: goto tr434;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr611;
	} else if ( (*( state.p)) >= 9 )
		goto tr610;
	goto tr432;
tr555:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st434;
st434:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof434;
case 434:
#line 8532 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr613;
	}
	goto tr432;
tr613:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st435;
st435:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof435;
case 435:
#line 8549 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 98: goto tr614;
	}
	goto tr432;
tr614:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st436;
st436:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof436;
case 436:
#line 8566 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 105: goto tr615;
	}
	goto tr432;
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
#line 8583 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 116: goto tr616;
	}
	goto tr432;
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
#line 8600 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr617;
	}
	goto tr432;
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
#line 8617 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 116: goto tr618;
	}
	goto tr432;
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
#line 8634 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr619;
		case 32: goto tr619;
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr619;
	goto tr432;
tr619:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st441;
st441:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof441;
case 441:
#line 8654 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr619;
		case 32: goto tr619;
		case 34: goto st325;
		case 92: goto tr434;
		case 99: goto tr620;
		case 102: goto tr621;
		case 115: goto tr622;
		case 119: goto tr623;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr619;
	goto tr432;
tr620:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st442;
st442:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof442;
case 442:
#line 8678 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 108: goto tr624;
		case 111: goto tr625;
	}
	goto tr432;
tr624:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st443;
st443:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof443;
case 443:
#line 8696 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 117: goto tr626;
	}
	goto tr432;
tr626:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st444;
st444:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof444;
case 444:
#line 8713 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 109: goto tr627;
	}
	goto tr432;
tr627:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st445;
st445:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof445;
case 445:
#line 8730 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 112: goto tr628;
	}
	goto tr432;
tr628:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st446;
st446:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof446;
case 446:
#line 8747 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr629;
	}
	goto tr432;
tr629:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st447;
st447:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof447;
case 447:
#line 8764 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 100: goto tr630;
	}
	goto tr432;
tr630:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st448;
st448:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof448;
case 448:
#line 8781 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 95: goto tr631;
	}
	goto tr432;
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
#line 8798 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 99: goto tr632;
		case 102: goto tr633;
		case 115: goto tr634;
		case 119: goto tr635;
	}
	goto tr432;
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
#line 8818 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 111: goto tr636;
	}
	goto tr432;
tr636:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st451;
st451:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof451;
case 451:
#line 8835 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 114: goto tr637;
	}
	goto tr432;
tr637:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st452;
st452:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof452;
case 452:
#line 8852 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr638;
	}
	goto tr432;
tr638:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st453;
st453:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof453;
case 453:
#line 8869 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr639;
	}
	goto tr432;
tr639:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st454;
st454:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof454;
case 454:
#line 8886 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 114: goto tr640;
	}
	goto tr432;
tr640:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st455;
st455:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof455;
case 455:
#line 8903 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr641;
		case 32: goto tr641;
		case 34: goto st325;
		case 59: goto tr642;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr641;
	goto tr432;
tr633:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st456;
st456:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof456;
case 456:
#line 8924 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 108: goto tr643;
	}
	goto tr432;
tr643:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st457;
st457:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof457;
case 457:
#line 8941 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 111: goto tr644;
	}
	goto tr432;
tr644:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st458;
st458:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof458;
case 458:
#line 8958 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 111: goto tr645;
	}
	goto tr432;
tr645:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st459;
st459:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof459;
case 459:
#line 8975 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 114: goto tr646;
	}
	goto tr432;
tr646:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st460;
st460:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof460;
case 460:
#line 8992 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr647;
		case 32: goto tr647;
		case 34: goto st325;
		case 59: goto tr648;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr647;
	goto tr432;
tr634:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st461;
st461:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof461;
case 461:
#line 9013 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 104: goto tr649;
	}
	goto tr432;
tr649:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st462;
st462:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof462;
case 462:
#line 9030 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 111: goto tr650;
	}
	goto tr432;
tr650:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st463;
st463:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof463;
case 463:
#line 9047 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 114: goto tr651;
	}
	goto tr432;
tr651:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st464;
st464:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof464;
case 464:
#line 9064 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr652;
	}
	goto tr432;
tr652:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st465;
st465:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof465;
case 465:
#line 9081 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 108: goto tr653;
	}
	goto tr432;
tr653:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st466;
st466:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof466;
case 466:
#line 9098 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 105: goto tr654;
	}
	goto tr432;
tr654:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st467;
st467:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof467;
case 467:
#line 9115 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr655;
	}
	goto tr432;
tr655:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st468;
st468:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof468;
case 468:
#line 9132 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr656;
	}
	goto tr432;
tr656:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st469;
st469:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof469;
case 469:
#line 9149 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr657;
		case 32: goto tr657;
		case 34: goto st325;
		case 59: goto tr658;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr657;
	goto tr432;
tr635:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st470;
st470:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof470;
case 470:
#line 9170 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr659;
	}
	goto tr432;
tr659:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st471;
st471:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof471;
case 471:
#line 9187 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 116: goto tr660;
	}
	goto tr432;
tr660:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st472;
st472:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof472;
case 472:
#line 9204 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr661;
	}
	goto tr432;
tr661:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st473;
st473:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof473;
case 473:
#line 9221 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 114: goto tr662;
	}
	goto tr432;
tr662:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st474;
st474:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof474;
case 474:
#line 9238 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr663;
		case 32: goto tr663;
		case 34: goto st325;
		case 59: goto tr664;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr663;
	goto tr432;
tr625:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st475;
st475:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof475;
case 475:
#line 9259 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 114: goto tr665;
	}
	goto tr432;
tr665:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st476;
st476:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof476;
case 476:
#line 9276 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr666;
	}
	goto tr432;
tr666:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st477;
st477:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof477;
case 477:
#line 9293 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr667;
	}
	goto tr432;
tr667:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st478;
st478:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof478;
case 478:
#line 9310 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 114: goto tr668;
	}
	goto tr432;
tr668:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st479;
st479:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof479;
case 479:
#line 9327 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr669;
		case 32: goto tr669;
		case 34: goto st325;
		case 59: goto tr670;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr669;
	goto tr432;
tr621:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st480;
st480:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof480;
case 480:
#line 9348 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 108: goto tr671;
	}
	goto tr432;
tr671:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st481;
st481:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof481;
case 481:
#line 9365 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 111: goto tr672;
	}
	goto tr432;
tr672:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st482;
st482:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof482;
case 482:
#line 9382 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 111: goto tr673;
	}
	goto tr432;
tr673:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st483;
st483:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof483;
case 483:
#line 9399 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 114: goto tr674;
	}
	goto tr432;
tr674:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st484;
st484:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof484;
case 484:
#line 9416 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr675;
		case 32: goto tr675;
		case 34: goto st325;
		case 59: goto tr676;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr675;
	goto tr432;
tr622:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st485;
st485:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof485;
case 485:
#line 9437 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 104: goto tr677;
	}
	goto tr432;
tr677:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st486;
st486:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof486;
case 486:
#line 9454 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 111: goto tr678;
	}
	goto tr432;
tr678:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st487;
st487:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof487;
case 487:
#line 9471 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 114: goto tr679;
	}
	goto tr432;
tr679:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st488;
st488:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof488;
case 488:
#line 9488 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr680;
	}
	goto tr432;
tr680:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st489;
st489:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof489;
case 489:
#line 9505 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 108: goto tr681;
	}
	goto tr432;
tr681:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st490;
st490:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof490;
case 490:
#line 9522 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 105: goto tr682;
	}
	goto tr432;
tr682:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st491;
st491:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof491;
case 491:
#line 9539 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr683;
	}
	goto tr432;
tr683:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st492;
st492:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof492;
case 492:
#line 9556 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr684;
	}
	goto tr432;
tr684:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st493;
st493:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof493;
case 493:
#line 9573 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr685;
		case 32: goto tr685;
		case 34: goto st325;
		case 59: goto tr686;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr685;
	goto tr432;
tr623:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st494;
st494:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof494;
case 494:
#line 9594 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr687;
	}
	goto tr432;
tr687:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st495;
st495:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof495;
case 495:
#line 9611 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 108: goto tr688;
		case 116: goto tr689;
	}
	goto tr432;
tr688:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st496;
st496:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof496;
case 496:
#line 9629 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 107: goto tr690;
	}
	goto tr432;
tr690:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st497;
st497:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof497;
case 497:
#line 9646 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr691;
		case 32: goto tr691;
		case 34: goto st325;
		case 59: goto tr692;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr691;
	goto tr432;
tr689:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st498;
st498:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof498;
case 498:
#line 9667 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr693;
	}
	goto tr432;
tr693:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st499;
st499:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof499;
case 499:
#line 9684 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 114: goto tr694;
	}
	goto tr432;
tr694:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st500;
st500:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof500;
case 500:
#line 9701 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr695;
		case 32: goto tr695;
		case 34: goto st325;
		case 59: goto tr696;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr695;
	goto tr432;
tr556:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st501;
st501:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof501;
case 501:
#line 9722 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 100: goto tr697;
	}
	goto tr432;
tr697:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st502;
st502:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof502;
case 502:
#line 9739 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 108: goto tr698;
	}
	goto tr432;
tr698:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st503;
st503:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof503;
case 503:
#line 9756 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr699;
	}
	goto tr432;
tr699:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st504;
st504:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof504;
case 504:
#line 9773 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 95: goto tr700;
	}
	goto tr432;
tr700:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st505;
st505:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof505;
case 505:
#line 9790 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr701;
	}
	goto tr432;
tr701:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st506;
st506:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof506;
case 506:
#line 9807 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 105: goto tr702;
	}
	goto tr432;
tr702:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st507;
st507:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof507;
case 507:
#line 9824 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr703;
		case 32: goto tr703;
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr703;
	goto tr432;
tr703:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st508;
st508:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof508;
case 508:
#line 9844 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr703;
		case 32: goto tr703;
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr704;
		case 114: goto tr705;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr703;
	goto tr432;
tr704:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st509;
st509:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof509;
case 509:
#line 9866 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 111: goto tr706;
	}
	goto tr432;
tr706:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st510;
st510:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof510;
case 510:
#line 9883 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr707;
	}
	goto tr432;
tr707:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st511;
st511:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof511;
case 511:
#line 9900 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr708;
	}
	goto tr432;
tr708:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st512;
st512:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof512;
case 512:
#line 9917 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr709;
		case 32: goto tr709;
		case 34: goto st325;
		case 59: goto tr710;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr709;
	goto tr432;
tr705:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st513;
st513:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof513;
case 513:
#line 9938 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr711;
	}
	goto tr432;
tr711:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st514;
st514:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof514;
case 514:
#line 9955 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr712;
	}
	goto tr432;
tr712:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st515;
st515:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof515;
case 515:
#line 9972 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 100: goto tr713;
	}
	goto tr432;
tr713:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st516;
st516:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof516;
case 516:
#line 9989 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 111: goto tr714;
	}
	goto tr432;
tr714:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st517;
st517:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof517;
case 517:
#line 10006 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 109: goto tr715;
	}
	goto tr432;
tr715:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st518;
st518:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof518;
case 518:
#line 10023 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr716;
		case 32: goto tr716;
		case 34: goto st325;
		case 59: goto tr717;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr716;
	goto tr432;
tr557:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st519;
st519:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof519;
case 519:
#line 10044 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 111: goto tr718;
	}
	goto tr432;
tr718:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st520;
st520:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof520;
case 520:
#line 10061 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 118: goto tr719;
	}
	goto tr432;
tr719:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st521;
st521:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof521;
case 521:
#line 10078 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr720;
	}
	goto tr432;
tr720:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st522;
st522:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof522;
case 522:
#line 10095 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr721;
		case 32: goto tr721;
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr721;
	goto tr432;
tr721:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st523;
st523:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof523;
case 523:
#line 10115 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr721;
		case 32: goto tr721;
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr722;
		case 102: goto tr723;
		case 119: goto tr724;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr721;
	goto tr432;
tr722:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st524;
st524:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof524;
case 524:
#line 10138 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr725;
	}
	goto tr432;
tr725:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st525;
st525:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof525;
case 525:
#line 10155 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 121: goto tr726;
	}
	goto tr432;
tr726:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st526;
st526:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof526;
case 526:
#line 10172 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr727;
		case 32: goto tr727;
		case 34: goto st325;
		case 59: goto tr728;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr727;
	goto tr432;
tr723:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st527;
st527:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof527;
case 527:
#line 10193 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 108: goto tr729;
	}
	goto tr432;
tr729:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st528;
st528:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof528;
case 528:
#line 10210 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 111: goto tr730;
	}
	goto tr432;
tr730:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st529;
st529:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof529;
case 529:
#line 10227 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 111: goto tr731;
	}
	goto tr432;
tr731:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st530;
st530:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof530;
case 530:
#line 10244 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 114: goto tr732;
	}
	goto tr432;
tr732:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st531;
st531:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof531;
case 531:
#line 10261 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr733;
		case 32: goto tr733;
		case 34: goto st325;
		case 59: goto tr734;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr733;
	goto tr432;
tr724:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st532;
st532:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof532;
case 532:
#line 10282 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr735;
	}
	goto tr432;
tr735:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st533;
st533:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof533;
case 533:
#line 10299 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 116: goto tr736;
	}
	goto tr432;
tr736:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st534;
st534:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof534;
case 534:
#line 10316 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr737;
	}
	goto tr432;
tr737:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st535;
st535:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof535;
case 535:
#line 10333 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 114: goto tr738;
	}
	goto tr432;
tr738:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st536;
st536:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof536;
case 536:
#line 10350 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr739;
		case 32: goto tr739;
		case 34: goto st325;
		case 59: goto tr740;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr739;
	goto tr432;
tr558:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st537;
st537:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof537;
case 537:
#line 10371 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr741;
	}
	goto tr432;
tr741:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st538;
st538:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof538;
case 538:
#line 10388 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 109: goto tr742;
	}
	goto tr432;
tr742:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st539;
st539:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof539;
case 539:
#line 10405 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr743;
	}
	goto tr432;
tr743:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st540;
st540:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof540;
case 540:
#line 10422 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr744;
		case 32: goto tr744;
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr744;
	goto tr432;
tr744:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st541;
st541:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof541;
case 541:
#line 10442 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr744;
		case 32: goto tr744;
		case 34: goto st542;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr744;
	goto tr432;
st542:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof542;
case 542:
	switch( (*( state.p)) ) {
		case 13: goto tr746;
		case 32: goto tr746;
		case 34: goto tr205;
		case 92: goto tr206;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr746;
	goto tr204;
tr747:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st543;
tr746:
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
	goto st543;
st543:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof543;
case 543:
#line 10487 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr747;
		case 32: goto tr747;
		case 34: goto st156;
		case 92: goto tr209;
		case 98: goto tr748;
		case 100: goto tr749;
		case 110: goto tr750;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr747;
	goto tr207;
tr748:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st544;
st544:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof544;
case 544:
#line 10510 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 114: goto tr751;
	}
	goto tr207;
tr751:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st545;
st545:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof545;
case 545:
#line 10527 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 105: goto tr752;
	}
	goto tr207;
tr752:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st546;
st546:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof546;
case 546:
#line 10544 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 103: goto tr753;
	}
	goto tr207;
tr753:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st547;
st547:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof547;
case 547:
#line 10561 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 104: goto tr754;
	}
	goto tr207;
tr754:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st548;
st548:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof548;
case 548:
#line 10578 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 116: goto tr755;
	}
	goto tr207;
tr755:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st549;
st549:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof549;
case 549:
#line 10595 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr756;
		case 32: goto tr756;
		case 34: goto st156;
		case 92: goto tr209;
		case 95: goto tr757;
		case 98: goto tr758;
		case 99: goto tr759;
		case 103: goto tr760;
		case 109: goto tr761;
		case 114: goto tr762;
		case 119: goto tr763;
		case 121: goto tr764;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr756;
	goto tr207;
tr765:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st550;
tr756:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st550;
tr818:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st550;
st550:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof550;
case 550:
#line 10639 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr765;
		case 32: goto tr765;
		case 34: goto st156;
		case 92: goto tr209;
		case 98: goto tr766;
		case 99: goto tr767;
		case 103: goto tr768;
		case 109: goto tr769;
		case 114: goto tr770;
		case 119: goto tr771;
		case 121: goto tr772;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr765;
	goto tr207;
tr766:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st551;
tr758:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st551;
tr820:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st551;
st551:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof551;
case 551:
#line 10682 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 108: goto tr773;
	}
	goto tr207;
tr773:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st552;
st552:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof552;
case 552:
#line 10699 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr774;
		case 117: goto tr775;
	}
	goto tr207;
tr774:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st553;
st553:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof553;
case 553:
#line 10717 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 99: goto tr776;
	}
	goto tr207;
tr776:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st554;
st554:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof554;
case 554:
#line 10734 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 107: goto tr215;
	}
	goto tr207;
tr775:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st555;
st555:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof555;
case 555:
#line 10751 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr777;
	}
	goto tr207;
tr777:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st556;
st556:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof556;
case 556:
#line 10768 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr778;
		case 32: goto tr778;
		case 34: goto st156;
		case 59: goto tr779;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr778;
	goto tr207;
tr767:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st557;
tr759:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st557;
tr821:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st557;
st557:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof557;
case 557:
#line 10805 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 121: goto tr780;
	}
	goto tr207;
tr780:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st558;
st558:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof558;
case 558:
#line 10822 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr781;
	}
	goto tr207;
tr781:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st559;
st559:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof559;
case 559:
#line 10839 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr782;
	}
	goto tr207;
tr782:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st560;
st560:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof560;
case 560:
#line 10856 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr783;
		case 32: goto tr783;
		case 34: goto st156;
		case 59: goto tr784;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr783;
	goto tr207;
tr768:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st561;
tr760:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st561;
tr822:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st561;
st561:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof561;
case 561:
#line 10893 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 114: goto tr785;
	}
	goto tr207;
tr785:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st562;
st562:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof562;
case 562:
#line 10910 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr786;
	}
	goto tr207;
tr786:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st563;
st563:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof563;
case 563:
#line 10927 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr787;
	}
	goto tr207;
tr787:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st564;
st564:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof564;
case 564:
#line 10944 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr788;
	}
	goto tr207;
tr788:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st565;
st565:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof565;
case 565:
#line 10961 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr789;
		case 32: goto tr789;
		case 34: goto st156;
		case 59: goto tr790;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr789;
	goto tr207;
tr769:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st566;
tr761:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st566;
tr823:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st566;
st566:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof566;
case 566:
#line 10998 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr791;
	}
	goto tr207;
tr791:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st567;
st567:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof567;
case 567:
#line 11015 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 103: goto tr792;
	}
	goto tr207;
tr792:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st568;
st568:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof568;
case 568:
#line 11032 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr793;
	}
	goto tr207;
tr793:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st569;
st569:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof569;
case 569:
#line 11049 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr794;
	}
	goto tr207;
tr794:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st570;
st570:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof570;
case 570:
#line 11066 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 116: goto tr795;
	}
	goto tr207;
tr795:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st571;
st571:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof571;
case 571:
#line 11083 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 97: goto tr796;
	}
	goto tr207;
tr796:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st572;
st572:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof572;
case 572:
#line 11100 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr797;
		case 32: goto tr797;
		case 34: goto st156;
		case 59: goto tr798;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr797;
	goto tr207;
tr770:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st573;
tr762:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st573;
tr824:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st573;
st573:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof573;
case 573:
#line 11137 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr799;
	}
	goto tr207;
tr799:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st574;
st574:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof574;
case 574:
#line 11154 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 100: goto tr800;
	}
	goto tr207;
tr800:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st575;
st575:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof575;
case 575:
#line 11171 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr801;
		case 32: goto tr801;
		case 34: goto st156;
		case 59: goto tr802;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr801;
	goto tr207;
tr771:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st576;
tr763:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st576;
tr825:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st576;
st576:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof576;
case 576:
#line 11208 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 104: goto tr803;
	}
	goto tr207;
tr803:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st577;
st577:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof577;
case 577:
#line 11225 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 105: goto tr804;
	}
	goto tr207;
tr804:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st578;
st578:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof578;
case 578:
#line 11242 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 116: goto tr805;
	}
	goto tr207;
tr805:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st579;
st579:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof579;
case 579:
#line 11259 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr806;
	}
	goto tr207;
tr806:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st580;
st580:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof580;
case 580:
#line 11276 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr807;
		case 32: goto tr807;
		case 34: goto st156;
		case 59: goto tr808;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr807;
	goto tr207;
tr772:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st581;
tr764:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st581;
tr826:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st581;
st581:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof581;
case 581:
#line 11313 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr809;
	}
	goto tr207;
tr809:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st582;
st582:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof582;
case 582:
#line 11330 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 108: goto tr810;
	}
	goto tr207;
tr810:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st583;
st583:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof583;
case 583:
#line 11347 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 108: goto tr811;
	}
	goto tr207;
tr811:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st584;
st584:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof584;
case 584:
#line 11364 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 111: goto tr812;
	}
	goto tr207;
tr812:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st585;
st585:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof585;
case 585:
#line 11381 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 119: goto tr813;
	}
	goto tr207;
tr813:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st586;
st586:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof586;
case 586:
#line 11398 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr814;
		case 32: goto tr814;
		case 34: goto st156;
		case 59: goto tr815;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr814;
	goto tr207;
tr757:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st587;
tr819:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st587;
st587:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof587;
case 587:
#line 11429 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 98: goto tr766;
		case 99: goto tr767;
		case 103: goto tr768;
		case 109: goto tr769;
		case 114: goto tr770;
		case 119: goto tr771;
		case 121: goto tr772;
	}
	goto tr207;
tr749:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st588;
st588:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof588;
case 588:
#line 11452 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 105: goto tr816;
	}
	goto tr207;
tr816:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st589;
st589:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof589;
case 589:
#line 11469 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 109: goto tr817;
	}
	goto tr207;
tr817:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st590;
st590:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof590;
case 590:
#line 11486 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr818;
		case 32: goto tr818;
		case 34: goto st156;
		case 92: goto tr209;
		case 95: goto tr819;
		case 98: goto tr820;
		case 99: goto tr821;
		case 103: goto tr822;
		case 109: goto tr823;
		case 114: goto tr824;
		case 119: goto tr825;
		case 121: goto tr826;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr818;
	goto tr207;
tr750:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st591;
st591:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof591;
case 591:
#line 11514 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 111: goto tr827;
	}
	goto tr207;
tr827:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st592;
st592:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof592;
case 592:
#line 11531 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 110: goto tr828;
	}
	goto tr207;
tr828:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st593;
st593:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof593;
case 593:
#line 11548 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st156;
		case 92: goto tr209;
		case 101: goto tr215;
	}
	goto tr207;
tr559:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st594;
st594:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof594;
case 594:
#line 11565 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr829;
	}
	goto tr432;
tr829:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st595;
st595:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof595;
case 595:
#line 11582 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr830;
	}
	goto tr432;
tr830:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st596;
st596:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof596;
case 596:
#line 11599 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 103: goto tr831;
	}
	goto tr432;
tr831:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st597;
st597:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof597;
case 597:
#line 11616 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr832;
	}
	goto tr432;
tr832:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st598;
st598:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof598;
case 598:
#line 11633 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr833;
		case 32: goto tr833;
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr833;
	goto tr432;
tr833:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st599;
st599:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof599;
case 599:
#line 11653 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr833;
		case 32: goto tr833;
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr834;
	} else if ( (*( state.p)) >= 9 )
		goto tr833;
	goto tr432;
tr836:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st600;
tr834:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st600;
st600:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof600;
case 600:
#line 11686 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr835;
		case 32: goto tr835;
		case 34: goto st325;
		case 59: goto tr837;
		case 92: goto tr434;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr836;
	} else if ( (*( state.p)) >= 9 )
		goto tr835;
	goto tr432;
tr560:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st601;
st601:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof601;
case 601:
#line 11710 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 107: goto tr838;
	}
	goto tr432;
tr838:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st602;
st602:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof602;
case 602:
#line 11727 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 105: goto tr839;
	}
	goto tr432;
tr839:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st603;
st603:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof603;
case 603:
#line 11744 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr840;
	}
	goto tr432;
tr840:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st604;
st604:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof604;
case 604:
#line 11761 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr841;
		case 32: goto tr841;
		case 34: goto st325;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr841;
	goto tr432;
tr841:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st605;
st605:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof605;
case 605:
#line 11781 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr841;
		case 32: goto tr841;
		case 34: goto st606;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr841;
	goto tr432;
st606:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof606;
case 606:
	switch( (*( state.p)) ) {
		case 13: goto tr843;
		case 32: goto tr843;
		case 34: goto tr429;
		case 92: goto tr431;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr843;
	goto tr427;
tr561:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st607;
st607:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof607;
case 607:
#line 11814 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr844;
		case 32: goto tr844;
		case 34: goto st325;
		case 59: goto tr845;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr844;
	goto tr432;
tr548:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st608;
st608:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof608;
case 608:
#line 11835 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr846;
	}
	goto tr432;
tr846:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st609;
st609:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof609;
case 609:
#line 11852 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr847;
		case 32: goto tr847;
		case 34: goto st325;
		case 59: goto tr848;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr847;
	goto tr432;
tr540:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st610;
tr532:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st610;
tr890:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st610;
st610:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof610;
case 610:
#line 11889 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 121: goto tr849;
	}
	goto tr432;
tr849:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st611;
st611:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof611;
case 611:
#line 11906 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr850;
	}
	goto tr432;
tr850:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st612;
st612:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof612;
case 612:
#line 11923 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr851;
	}
	goto tr432;
tr851:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st613;
st613:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof613;
case 613:
#line 11940 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr852;
		case 32: goto tr852;
		case 34: goto st325;
		case 59: goto tr853;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr852;
	goto tr432;
tr541:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st614;
tr533:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st614;
tr891:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st614;
st614:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof614;
case 614:
#line 11977 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 114: goto tr854;
	}
	goto tr432;
tr854:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st615;
st615:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof615;
case 615:
#line 11994 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr855;
	}
	goto tr432;
tr855:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st616;
st616:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof616;
case 616:
#line 12011 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr856;
	}
	goto tr432;
tr856:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st617;
st617:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof617;
case 617:
#line 12028 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr857;
	}
	goto tr432;
tr857:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st618;
st618:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof618;
case 618:
#line 12045 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr858;
		case 32: goto tr858;
		case 34: goto st325;
		case 59: goto tr859;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr858;
	goto tr432;
tr542:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st619;
tr534:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st619;
tr892:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st619;
st619:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof619;
case 619:
#line 12082 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr860;
	}
	goto tr432;
tr860:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st620;
st620:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof620;
case 620:
#line 12099 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 103: goto tr861;
	}
	goto tr432;
tr861:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st621;
st621:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof621;
case 621:
#line 12116 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr862;
	}
	goto tr432;
tr862:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st622;
st622:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof622;
case 622:
#line 12133 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr863;
	}
	goto tr432;
tr863:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st623;
st623:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof623;
case 623:
#line 12150 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 116: goto tr864;
	}
	goto tr432;
tr864:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st624;
st624:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof624;
case 624:
#line 12167 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 97: goto tr865;
	}
	goto tr432;
tr865:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st625;
st625:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof625;
case 625:
#line 12184 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr866;
		case 32: goto tr866;
		case 34: goto st325;
		case 59: goto tr867;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr866;
	goto tr432;
tr543:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st626;
tr535:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st626;
tr893:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st626;
st626:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof626;
case 626:
#line 12221 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr868;
	}
	goto tr432;
tr868:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st627;
st627:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof627;
case 627:
#line 12238 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 100: goto tr869;
	}
	goto tr432;
tr869:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st628;
st628:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof628;
case 628:
#line 12255 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr870;
		case 32: goto tr870;
		case 34: goto st325;
		case 59: goto tr871;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr870;
	goto tr432;
tr544:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st629;
tr536:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st629;
tr894:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st629;
st629:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof629;
case 629:
#line 12292 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 104: goto tr872;
	}
	goto tr432;
tr872:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st630;
st630:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof630;
case 630:
#line 12309 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 105: goto tr873;
	}
	goto tr432;
tr873:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st631;
st631:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof631;
case 631:
#line 12326 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 116: goto tr874;
	}
	goto tr432;
tr874:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st632;
st632:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof632;
case 632:
#line 12343 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr875;
	}
	goto tr432;
tr875:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st633;
st633:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof633;
case 633:
#line 12360 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr876;
		case 32: goto tr876;
		case 34: goto st325;
		case 59: goto tr877;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr876;
	goto tr432;
tr545:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st634;
tr537:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st634;
tr895:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st634;
st634:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof634;
case 634:
#line 12397 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr878;
	}
	goto tr432;
tr878:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st635;
st635:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof635;
case 635:
#line 12414 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 108: goto tr879;
	}
	goto tr432;
tr879:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st636;
st636:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof636;
case 636:
#line 12431 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 108: goto tr880;
	}
	goto tr432;
tr880:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st637;
st637:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof637;
case 637:
#line 12448 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 111: goto tr881;
	}
	goto tr432;
tr881:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st638;
st638:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof638;
case 638:
#line 12465 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 119: goto tr882;
	}
	goto tr432;
tr882:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st639;
st639:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof639;
case 639:
#line 12482 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr883;
		case 32: goto tr883;
		case 34: goto st325;
		case 59: goto tr884;
		case 92: goto tr434;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr883;
	goto tr432;
tr530:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st640;
tr888:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st640;
st640:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof640;
case 640:
#line 12513 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 98: goto tr539;
		case 99: goto tr540;
		case 103: goto tr541;
		case 109: goto tr542;
		case 114: goto tr543;
		case 119: goto tr544;
		case 121: goto tr545;
	}
	goto tr432;
tr522:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st641;
st641:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof641;
case 641:
#line 12536 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 105: goto tr885;
	}
	goto tr432;
tr885:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st642;
st642:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof642;
case 642:
#line 12553 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 109: goto tr886;
	}
	goto tr432;
tr886:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st643;
st643:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof643;
case 643:
#line 12570 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr887;
		case 32: goto tr887;
		case 34: goto st325;
		case 92: goto tr434;
		case 95: goto tr888;
		case 98: goto tr889;
		case 99: goto tr890;
		case 103: goto tr891;
		case 109: goto tr892;
		case 114: goto tr893;
		case 119: goto tr894;
		case 121: goto tr895;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr887;
	goto tr432;
tr523:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st644;
st644:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof644;
case 644:
#line 12598 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 111: goto tr896;
	}
	goto tr432;
tr896:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st645;
st645:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof645;
case 645:
#line 12615 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 110: goto tr897;
	}
	goto tr432;
tr897:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st646;
st646:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof646;
case 646:
#line 12632 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st325;
		case 92: goto tr434;
		case 101: goto tr550;
	}
	goto tr432;
tr226:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st647;
st647:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof647;
case 647:
#line 12649 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr898;
		case 32: goto tr898;
		case 34: goto st156;
		case 59: goto tr899;
		case 92: goto tr209;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr898;
	goto tr207;
st648:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof648;
case 648:
	if ( (*( state.p)) == 97 )
		goto st649;
	goto st0;
st649:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof649;
case 649:
	if ( (*( state.p)) == 110 )
		goto st650;
	goto st0;
st650:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof650;
case 650:
	if ( (*( state.p)) == 103 )
		goto st651;
	goto st0;
st651:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof651;
case 651:
	if ( (*( state.p)) == 101 )
		goto st652;
	goto st0;
st652:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof652;
case 652:
	switch( (*( state.p)) ) {
		case 13: goto st653;
		case 32: goto st653;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st653;
	goto st0;
st653:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof653;
case 653:
	switch( (*( state.p)) ) {
		case 13: goto st653;
		case 32: goto st653;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr905;
	} else if ( (*( state.p)) >= 9 )
		goto st653;
	goto st0;
tr905:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st654;
tr907:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st654;
st654:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof654;
case 654:
#line 12733 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr906;
		case 32: goto tr906;
		case 59: goto tr908;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr907;
	} else if ( (*( state.p)) >= 9 )
		goto tr906;
	goto st0;
st655:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof655;
case 655:
	if ( (*( state.p)) == 107 )
		goto st656;
	goto st0;
st656:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof656;
case 656:
	if ( (*( state.p)) == 105 )
		goto st657;
	goto st0;
st657:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof657;
case 657:
	if ( (*( state.p)) == 110 )
		goto st658;
	goto st0;
st658:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof658;
case 658:
	switch( (*( state.p)) ) {
		case 13: goto st659;
		case 32: goto st659;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st659;
	goto st0;
st659:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof659;
case 659:
	switch( (*( state.p)) ) {
		case 13: goto st659;
		case 32: goto st659;
		case 34: goto st660;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st659;
	goto st0;
st660:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof660;
case 660:
	switch( (*( state.p)) ) {
		case 34: goto tr429;
		case 92: goto tr431;
	}
	goto tr427;
st661:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof661;
case 661:
	switch( (*( state.p)) ) {
		case 13: goto tr914;
		case 32: goto tr914;
		case 59: goto tr915;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr914;
	goto st0;
st662:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof662;
case 662:
	if ( (*( state.p)) == 101 )
		goto st663;
	goto st0;
st663:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof663;
case 663:
	if ( (*( state.p)) == 101 )
		goto st664;
	goto st0;
st664:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof664;
case 664:
	if ( (*( state.p)) == 107 )
		goto st665;
	goto st0;
st665:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof665;
case 665:
	if ( (*( state.p)) == 95 )
		goto st666;
	goto st0;
st666:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof666;
case 666:
	if ( (*( state.p)) == 112 )
		goto st667;
	goto st0;
st667:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof667;
case 667:
	if ( (*( state.p)) == 108 )
		goto st668;
	goto st0;
st668:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof668;
case 668:
	if ( (*( state.p)) == 97 )
		goto st669;
	goto st0;
st669:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof669;
case 669:
	if ( (*( state.p)) == 121 )
		goto st670;
	goto st0;
st670:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof670;
case 670:
	if ( (*( state.p)) == 101 )
		goto st671;
	goto st0;
st671:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof671;
case 671:
	if ( (*( state.p)) == 114 )
		goto st672;
	goto st0;
st672:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof672;
case 672:
	switch( (*( state.p)) ) {
		case 13: goto tr926;
		case 32: goto tr926;
		case 59: goto tr927;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr926;
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
	_test_eof673:  state.cs = 673; goto _test_eof; 
	_test_eof674:  state.cs = 674; goto _test_eof; 
	_test_eof14:  state.cs = 14; goto _test_eof; 
	_test_eof15:  state.cs = 15; goto _test_eof; 
	_test_eof16:  state.cs = 16; goto _test_eof; 
	_test_eof17:  state.cs = 17; goto _test_eof; 
	_test_eof18:  state.cs = 18; goto _test_eof; 
	_test_eof19:  state.cs = 19; goto _test_eof; 
	_test_eof20:  state.cs = 20; goto _test_eof; 
	_test_eof21:  state.cs = 21; goto _test_eof; 
	_test_eof22:  state.cs = 22; goto _test_eof; 
	_test_eof675:  state.cs = 675; goto _test_eof; 
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
	_test_eof676:  state.cs = 676; goto _test_eof; 
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
	_test_eof677:  state.cs = 677; goto _test_eof; 
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
	_test_eof577:  state.cs = 577; goto _test_eof; 
	_test_eof578:  state.cs = 578; goto _test_eof; 
	_test_eof579:  state.cs = 579; goto _test_eof; 
	_test_eof580:  state.cs = 580; goto _test_eof; 
	_test_eof581:  state.cs = 581; goto _test_eof; 
	_test_eof582:  state.cs = 582; goto _test_eof; 
	_test_eof583:  state.cs = 583; goto _test_eof; 
	_test_eof584:  state.cs = 584; goto _test_eof; 
	_test_eof585:  state.cs = 585; goto _test_eof; 
	_test_eof586:  state.cs = 586; goto _test_eof; 
	_test_eof587:  state.cs = 587; goto _test_eof; 
	_test_eof588:  state.cs = 588; goto _test_eof; 
	_test_eof589:  state.cs = 589; goto _test_eof; 
	_test_eof590:  state.cs = 590; goto _test_eof; 
	_test_eof591:  state.cs = 591; goto _test_eof; 
	_test_eof592:  state.cs = 592; goto _test_eof; 
	_test_eof593:  state.cs = 593; goto _test_eof; 
	_test_eof594:  state.cs = 594; goto _test_eof; 
	_test_eof595:  state.cs = 595; goto _test_eof; 
	_test_eof596:  state.cs = 596; goto _test_eof; 
	_test_eof597:  state.cs = 597; goto _test_eof; 
	_test_eof598:  state.cs = 598; goto _test_eof; 
	_test_eof599:  state.cs = 599; goto _test_eof; 
	_test_eof600:  state.cs = 600; goto _test_eof; 
	_test_eof601:  state.cs = 601; goto _test_eof; 
	_test_eof602:  state.cs = 602; goto _test_eof; 
	_test_eof603:  state.cs = 603; goto _test_eof; 
	_test_eof604:  state.cs = 604; goto _test_eof; 
	_test_eof605:  state.cs = 605; goto _test_eof; 
	_test_eof606:  state.cs = 606; goto _test_eof; 
	_test_eof607:  state.cs = 607; goto _test_eof; 
	_test_eof608:  state.cs = 608; goto _test_eof; 
	_test_eof609:  state.cs = 609; goto _test_eof; 
	_test_eof610:  state.cs = 610; goto _test_eof; 
	_test_eof611:  state.cs = 611; goto _test_eof; 
	_test_eof612:  state.cs = 612; goto _test_eof; 
	_test_eof613:  state.cs = 613; goto _test_eof; 
	_test_eof614:  state.cs = 614; goto _test_eof; 
	_test_eof615:  state.cs = 615; goto _test_eof; 
	_test_eof616:  state.cs = 616; goto _test_eof; 
	_test_eof617:  state.cs = 617; goto _test_eof; 
	_test_eof618:  state.cs = 618; goto _test_eof; 
	_test_eof619:  state.cs = 619; goto _test_eof; 
	_test_eof620:  state.cs = 620; goto _test_eof; 
	_test_eof621:  state.cs = 621; goto _test_eof; 
	_test_eof622:  state.cs = 622; goto _test_eof; 
	_test_eof623:  state.cs = 623; goto _test_eof; 
	_test_eof624:  state.cs = 624; goto _test_eof; 
	_test_eof625:  state.cs = 625; goto _test_eof; 
	_test_eof626:  state.cs = 626; goto _test_eof; 
	_test_eof627:  state.cs = 627; goto _test_eof; 
	_test_eof628:  state.cs = 628; goto _test_eof; 
	_test_eof629:  state.cs = 629; goto _test_eof; 
	_test_eof630:  state.cs = 630; goto _test_eof; 
	_test_eof631:  state.cs = 631; goto _test_eof; 
	_test_eof632:  state.cs = 632; goto _test_eof; 
	_test_eof633:  state.cs = 633; goto _test_eof; 
	_test_eof634:  state.cs = 634; goto _test_eof; 
	_test_eof635:  state.cs = 635; goto _test_eof; 
	_test_eof636:  state.cs = 636; goto _test_eof; 
	_test_eof637:  state.cs = 637; goto _test_eof; 
	_test_eof638:  state.cs = 638; goto _test_eof; 
	_test_eof639:  state.cs = 639; goto _test_eof; 
	_test_eof640:  state.cs = 640; goto _test_eof; 
	_test_eof641:  state.cs = 641; goto _test_eof; 
	_test_eof642:  state.cs = 642; goto _test_eof; 
	_test_eof643:  state.cs = 643; goto _test_eof; 
	_test_eof644:  state.cs = 644; goto _test_eof; 
	_test_eof645:  state.cs = 645; goto _test_eof; 
	_test_eof646:  state.cs = 646; goto _test_eof; 
	_test_eof647:  state.cs = 647; goto _test_eof; 
	_test_eof648:  state.cs = 648; goto _test_eof; 
	_test_eof649:  state.cs = 649; goto _test_eof; 
	_test_eof650:  state.cs = 650; goto _test_eof; 
	_test_eof651:  state.cs = 651; goto _test_eof; 
	_test_eof652:  state.cs = 652; goto _test_eof; 
	_test_eof653:  state.cs = 653; goto _test_eof; 
	_test_eof654:  state.cs = 654; goto _test_eof; 
	_test_eof655:  state.cs = 655; goto _test_eof; 
	_test_eof656:  state.cs = 656; goto _test_eof; 
	_test_eof657:  state.cs = 657; goto _test_eof; 
	_test_eof658:  state.cs = 658; goto _test_eof; 
	_test_eof659:  state.cs = 659; goto _test_eof; 
	_test_eof660:  state.cs = 660; goto _test_eof; 
	_test_eof661:  state.cs = 661; goto _test_eof; 
	_test_eof662:  state.cs = 662; goto _test_eof; 
	_test_eof663:  state.cs = 663; goto _test_eof; 
	_test_eof664:  state.cs = 664; goto _test_eof; 
	_test_eof665:  state.cs = 665; goto _test_eof; 
	_test_eof666:  state.cs = 666; goto _test_eof; 
	_test_eof667:  state.cs = 667; goto _test_eof; 
	_test_eof668:  state.cs = 668; goto _test_eof; 
	_test_eof669:  state.cs = 669; goto _test_eof; 
	_test_eof670:  state.cs = 670; goto _test_eof; 
	_test_eof671:  state.cs = 671; goto _test_eof; 
	_test_eof672:  state.cs = 672; goto _test_eof; 

	_test_eof: {}
	if ( ( state.p) == ( state.eof) )
	{
	switch (  state.cs ) {
	case 673: 
#line 200 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
	break;
#line 13579 "configparser.h"
	}
	}

	_out: {}
	}

#line 234 "configparser.rl"

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
