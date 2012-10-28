
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

    
#line 209 "configparser.rl"

/*

*/

    
#line 96 "configparser.h"
static const int ConfigParser_start = 1;
static const int ConfigParser_first_final = 898;
static const int ConfigParser_error = 0;

static const int ConfigParser_en_one_species = 14;
static const int ConfigParser_en_main = 1;


#line 215 "configparser.rl"
    
#line 107 "configparser.h"
	{
	 state.cs = ConfigParser_start;
	 state.top = 0;
	}

#line 216 "configparser.rl"

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
		case 898: goto st898;
		case 899: goto st899;
		case 14: goto st14;
		case 15: goto st15;
		case 16: goto st16;
		case 17: goto st17;
		case 18: goto st18;
		case 19: goto st19;
		case 20: goto st20;
		case 21: goto st21;
		case 22: goto st22;
		case 900: goto st900;
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
		case 901: goto st901;
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
		case 902: goto st902;
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
		case 903: goto st903;
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
		case 673: goto st673;
		case 674: goto st674;
		case 675: goto st675;
		case 676: goto st676;
		case 677: goto st677;
		case 678: goto st678;
		case 679: goto st679;
		case 680: goto st680;
		case 681: goto st681;
		case 682: goto st682;
		case 683: goto st683;
		case 684: goto st684;
		case 685: goto st685;
		case 686: goto st686;
		case 687: goto st687;
		case 688: goto st688;
		case 689: goto st689;
		case 690: goto st690;
		case 691: goto st691;
		case 692: goto st692;
		case 693: goto st693;
		case 694: goto st694;
		case 695: goto st695;
		case 696: goto st696;
		case 697: goto st697;
		case 698: goto st698;
		case 699: goto st699;
		case 700: goto st700;
		case 701: goto st701;
		case 702: goto st702;
		case 703: goto st703;
		case 704: goto st704;
		case 705: goto st705;
		case 706: goto st706;
		case 707: goto st707;
		case 708: goto st708;
		case 709: goto st709;
		case 710: goto st710;
		case 711: goto st711;
		case 712: goto st712;
		case 713: goto st713;
		case 714: goto st714;
		case 715: goto st715;
		case 716: goto st716;
		case 717: goto st717;
		case 718: goto st718;
		case 719: goto st719;
		case 720: goto st720;
		case 721: goto st721;
		case 722: goto st722;
		case 723: goto st723;
		case 724: goto st724;
		case 725: goto st725;
		case 726: goto st726;
		case 727: goto st727;
		case 728: goto st728;
		case 729: goto st729;
		case 730: goto st730;
		case 731: goto st731;
		case 732: goto st732;
		case 733: goto st733;
		case 734: goto st734;
		case 735: goto st735;
		case 736: goto st736;
		case 737: goto st737;
		case 738: goto st738;
		case 739: goto st739;
		case 740: goto st740;
		case 741: goto st741;
		case 742: goto st742;
		case 743: goto st743;
		case 744: goto st744;
		case 745: goto st745;
		case 746: goto st746;
		case 747: goto st747;
		case 748: goto st748;
		case 749: goto st749;
		case 750: goto st750;
		case 751: goto st751;
		case 752: goto st752;
		case 753: goto st753;
		case 754: goto st754;
		case 755: goto st755;
		case 756: goto st756;
		case 757: goto st757;
		case 758: goto st758;
		case 759: goto st759;
		case 760: goto st760;
		case 761: goto st761;
		case 762: goto st762;
		case 763: goto st763;
		case 764: goto st764;
		case 765: goto st765;
		case 766: goto st766;
		case 767: goto st767;
		case 768: goto st768;
		case 769: goto st769;
		case 770: goto st770;
		case 771: goto st771;
		case 772: goto st772;
		case 773: goto st773;
		case 774: goto st774;
		case 775: goto st775;
		case 776: goto st776;
		case 777: goto st777;
		case 778: goto st778;
		case 779: goto st779;
		case 780: goto st780;
		case 781: goto st781;
		case 782: goto st782;
		case 783: goto st783;
		case 784: goto st784;
		case 785: goto st785;
		case 786: goto st786;
		case 787: goto st787;
		case 788: goto st788;
		case 789: goto st789;
		case 790: goto st790;
		case 791: goto st791;
		case 792: goto st792;
		case 793: goto st793;
		case 794: goto st794;
		case 795: goto st795;
		case 796: goto st796;
		case 797: goto st797;
		case 798: goto st798;
		case 799: goto st799;
		case 800: goto st800;
		case 801: goto st801;
		case 802: goto st802;
		case 803: goto st803;
		case 804: goto st804;
		case 805: goto st805;
		case 806: goto st806;
		case 807: goto st807;
		case 808: goto st808;
		case 809: goto st809;
		case 810: goto st810;
		case 811: goto st811;
		case 812: goto st812;
		case 813: goto st813;
		case 814: goto st814;
		case 815: goto st815;
		case 816: goto st816;
		case 817: goto st817;
		case 818: goto st818;
		case 819: goto st819;
		case 820: goto st820;
		case 821: goto st821;
		case 822: goto st822;
		case 823: goto st823;
		case 824: goto st824;
		case 825: goto st825;
		case 826: goto st826;
		case 827: goto st827;
		case 828: goto st828;
		case 829: goto st829;
		case 830: goto st830;
		case 831: goto st831;
		case 832: goto st832;
		case 833: goto st833;
		case 834: goto st834;
		case 835: goto st835;
		case 836: goto st836;
		case 837: goto st837;
		case 838: goto st838;
		case 839: goto st839;
		case 840: goto st840;
		case 841: goto st841;
		case 842: goto st842;
		case 843: goto st843;
		case 844: goto st844;
		case 845: goto st845;
		case 846: goto st846;
		case 847: goto st847;
		case 848: goto st848;
		case 849: goto st849;
		case 850: goto st850;
		case 851: goto st851;
		case 852: goto st852;
		case 853: goto st853;
		case 854: goto st854;
		case 855: goto st855;
		case 856: goto st856;
		case 857: goto st857;
		case 858: goto st858;
		case 859: goto st859;
		case 860: goto st860;
		case 861: goto st861;
		case 862: goto st862;
		case 863: goto st863;
		case 864: goto st864;
		case 865: goto st865;
		case 866: goto st866;
		case 867: goto st867;
		case 868: goto st868;
		case 869: goto st869;
		case 870: goto st870;
		case 871: goto st871;
		case 872: goto st872;
		case 873: goto st873;
		case 874: goto st874;
		case 875: goto st875;
		case 876: goto st876;
		case 877: goto st877;
		case 878: goto st878;
		case 879: goto st879;
		case 880: goto st880;
		case 881: goto st881;
		case 882: goto st882;
		case 883: goto st883;
		case 884: goto st884;
		case 885: goto st885;
		case 886: goto st886;
		case 887: goto st887;
		case 888: goto st888;
		case 889: goto st889;
		case 890: goto st890;
		case 891: goto st891;
		case 892: goto st892;
		case 893: goto st893;
		case 894: goto st894;
		case 895: goto st895;
		case 896: goto st896;
		case 897: goto st897;
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
#line 201 "configparser.rl"
	{ spe = Species(); }
	goto st2;
tr1250:
#line 204 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
#line 201 "configparser.rl"
	{ spe = Species(); }
	goto st2;
st2:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof2;
case 2:
#line 1085 "configparser.h"
	if ( (*( state.p)) == 112 )
		goto tr3;
	goto st0;
tr3:
#line 201 "configparser.rl"
	{ spe = Species(); }
	goto st3;
st3:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof3;
case 3:
#line 1097 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr4;
	goto st0;
tr4:
#line 201 "configparser.rl"
	{ spe = Species(); }
	goto st4;
st4:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof4;
case 4:
#line 1109 "configparser.h"
	if ( (*( state.p)) == 99 )
		goto tr5;
	goto st0;
tr5:
#line 201 "configparser.rl"
	{ spe = Species(); }
	goto st5;
st5:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof5;
case 5:
#line 1121 "configparser.h"
	if ( (*( state.p)) == 105 )
		goto tr6;
	goto st0;
tr6:
#line 201 "configparser.rl"
	{ spe = Species(); }
	goto st6;
st6:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof6;
case 6:
#line 1133 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto tr7;
	goto st0;
tr7:
#line 201 "configparser.rl"
	{ spe = Species(); }
	goto st7;
st7:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof7;
case 7:
#line 1145 "configparser.h"
	if ( (*( state.p)) == 115 )
		goto tr8;
	goto st0;
tr8:
#line 201 "configparser.rl"
	{ spe = Species(); }
	goto st8;
st8:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof8;
case 8:
#line 1157 "configparser.h"
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
#line 1199 "configparser.h"
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
#line 194 "configparser.rl"
	{ spe.level = ::atoi(state.match.c_str()); }
	goto st11;
st11:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof11;
case 11:
#line 1218 "configparser.h"
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
#line 1256 "configparser.h"
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
#line 197 "configparser.rl"
	{ spe.tag = state.match; }
	goto st13;
st13:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof13;
case 13:
#line 1283 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st13;
		case 32: goto st13;
		case 123: goto tr19;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st13;
	goto st0;
tr17:
#line 197 "configparser.rl"
	{ spe.tag = state.match; }
#line 203 "configparser.rl"
	{{ state.stack[ state.top++] = 898; goto st14;}}
	goto st898;
tr19:
#line 203 "configparser.rl"
	{{ state.stack[ state.top++] = 898; goto st14;}}
	goto st898;
st898:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof898;
case 898:
#line 1306 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1249;
		case 32: goto tr1249;
		case 115: goto tr1250;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1249;
	goto st0;
tr1249:
#line 204 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
	goto st899;
st899:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof899;
case 899:
#line 1323 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st899;
		case 32: goto st899;
		case 115: goto tr2;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st899;
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
		case 100: goto st776;
		case 104: goto st787;
		case 105: goto st822;
		case 109: goto st840;
		case 110: goto st858;
		case 114: goto st864;
		case 115: goto st871;
		case 125: goto st877;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st14;
	goto st0;
st15:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof15;
case 15:
	switch( (*( state.p)) ) {
		case 105: goto st16;
		case 116: goto st889;
	}
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
		case 115: goto st878;
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
		case 13: goto tr39;
		case 32: goto tr39;
		case 59: goto tr40;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr39;
	goto st0;
tr39:
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st22;
tr59:
#line 175 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st22;
tr85:
#line 180 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st22;
tr298:
#line 163 "configparser.rl"
	{ spe.name = state.match; }
	goto st22;
tr553:
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st22;
tr558:
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st22;
tr564:
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st22;
tr572:
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st22;
tr576:
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st22;
tr582:
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st22;
tr589:
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st22;
tr1101:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
	goto st22;
tr1112:
#line 171 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st22;
tr1133:
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st22;
tr1139:
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st22;
tr1149:
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st22;
tr1155:
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st22;
tr1159:
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st22;
tr1173:
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st22;
tr1180:
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st22;
tr1191:
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st22;
tr1197:
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st22;
tr1203:
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st22;
tr1216:
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st22;
tr1224:
#line 188 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st22;
tr1236:
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st22;
tr1244:
#line 170 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st22;
st22:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof22;
case 22:
#line 1531 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st22;
		case 32: goto st22;
		case 59: goto st900;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st22;
	goto st0;
tr40:
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st900;
tr62:
#line 175 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st900;
tr88:
#line 180 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st900;
tr299:
#line 163 "configparser.rl"
	{ spe.name = state.match; }
	goto st900;
tr554:
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st900;
tr559:
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st900;
tr565:
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st900;
tr573:
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st900;
tr577:
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st900;
tr583:
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st900;
tr590:
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st900;
tr1103:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
	goto st900;
tr1115:
#line 171 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st900;
tr1134:
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st900;
tr1140:
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st900;
tr1150:
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st900;
tr1156:
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st900;
tr1160:
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st900;
tr1174:
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st900;
tr1181:
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st900;
tr1192:
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st900;
tr1198:
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st900;
tr1204:
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st900;
tr1218:
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st900;
tr1225:
#line 188 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st900;
tr1237:
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st900;
tr1247:
#line 170 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st900;
st900:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof900;
case 900:
#line 1652 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st14;
		case 32: goto st14;
		case 97: goto st15;
		case 99: goto st23;
		case 100: goto st776;
		case 104: goto st787;
		case 105: goto st822;
		case 109: goto st840;
		case 110: goto st858;
		case 114: goto st864;
		case 115: goto st871;
		case 125: goto st877;
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
			goto tr53;
	} else if ( (*( state.p)) >= 9 )
		goto st32;
	goto st0;
tr53:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st33;
tr56:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st33;
st33:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof33;
case 33:
#line 1773 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr54;
		case 32: goto tr54;
		case 46: goto st38;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr56;
	} else if ( (*( state.p)) >= 9 )
		goto tr54;
	goto st0;
tr54:
#line 174 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st34;
st34:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof34;
case 34:
#line 1793 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st34;
		case 32: goto st34;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr58;
	} else if ( (*( state.p)) >= 9 )
		goto st34;
	goto st0;
tr58:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st35;
tr61:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st35;
st35:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof35;
case 35:
#line 1824 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr59;
		case 32: goto tr59;
		case 46: goto st36;
		case 59: goto tr62;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr61;
	} else if ( (*( state.p)) >= 9 )
		goto tr59;
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
		case 13: goto tr59;
		case 32: goto tr59;
		case 59: goto tr62;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto st37;
	} else if ( (*( state.p)) >= 9 )
		goto tr59;
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
		case 13: goto tr54;
		case 32: goto tr54;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto st39;
	} else if ( (*( state.p)) >= 9 )
		goto tr54;
	goto st0;
st40:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof40;
case 40:
	switch( (*( state.p)) ) {
		case 109: goto st41;
		case 117: goto st771;
	}
	goto st0;
st41:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof41;
case 41:
	if ( (*( state.p)) == 112 )
		goto st42;
	goto st0;
st42:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof42;
case 42:
	if ( (*( state.p)) == 97 )
		goto st43;
	goto st0;
st43:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof43;
case 43:
	if ( (*( state.p)) == 110 )
		goto st44;
	goto st0;
st44:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof44;
case 44:
	if ( (*( state.p)) == 105 )
		goto st45;
	goto st0;
st45:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof45;
case 45:
	if ( (*( state.p)) == 111 )
		goto st46;
	goto st0;
st46:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof46;
case 46:
	if ( (*( state.p)) == 110 )
		goto st47;
	goto st0;
st47:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof47;
case 47:
	switch( (*( state.p)) ) {
		case 13: goto tr73;
		case 32: goto tr73;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr73;
	goto st0;
tr73:
#line 178 "configparser.rl"
	{ spe.companion.push_back(Species::companion_t()); }
	goto st48;
st48:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof48;
case 48:
#line 1950 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st48;
		case 32: goto st48;
		case 34: goto st49;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st48;
	goto st0;
st49:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof49;
case 49:
	switch( (*( state.p)) ) {
		case 34: goto tr77;
		case 92: goto tr78;
	}
	goto tr76;
tr76:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st50;
tr79:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st50;
st50:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof50;
case 50:
#line 1988 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
	}
	goto tr79;
tr77:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st51;
st51:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof51;
case 51:
#line 2004 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr82;
		case 32: goto tr82;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr82;
	goto st0;
tr82:
#line 179 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st52;
st52:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof52;
case 52:
#line 2020 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st52;
		case 32: goto st52;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr84;
	} else if ( (*( state.p)) >= 9 )
		goto st52;
	goto st0;
tr84:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st53;
tr87:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st53;
st53:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof53;
case 53:
#line 2051 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr85;
		case 32: goto tr85;
		case 46: goto st54;
		case 59: goto tr88;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr87;
	} else if ( (*( state.p)) >= 9 )
		goto tr85;
	goto st0;
st54:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof54;
case 54:
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto st55;
	goto st0;
st55:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof55;
case 55:
	switch( (*( state.p)) ) {
		case 13: goto tr85;
		case 32: goto tr85;
		case 59: goto tr88;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto st55;
	} else if ( (*( state.p)) >= 9 )
		goto tr85;
	goto st0;
tr78:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st56;
tr81:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st56;
st56:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof56;
case 56:
#line 2106 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr90;
		case 92: goto tr81;
	}
	goto tr79;
tr90:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st57;
st57:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof57;
case 57:
#line 2122 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr91;
		case 32: goto tr91;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr91;
	goto tr79;
tr92:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st58;
tr91:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 179 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st58;
tr177:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 179 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st58;
st58:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof58;
case 58:
#line 2162 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr92;
		case 32: goto tr92;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr93;
	} else if ( (*( state.p)) >= 9 )
		goto tr92;
	goto tr79;
tr96:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st59;
tr93:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st59;
st59:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof59;
case 59:
#line 2195 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr94;
		case 32: goto tr94;
		case 34: goto st51;
		case 46: goto tr95;
		case 59: goto tr97;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr96;
	} else if ( (*( state.p)) >= 9 )
		goto tr94;
	goto tr79;
tr98:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr94:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 180 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st60;
tr119:
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr131:
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr139:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 170 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st60;
tr160:
#line 175 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr182:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr193:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 171 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st60;
tr214:
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr220:
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr230:
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr236:
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr240:
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr254:
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr261:
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr272:
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr278:
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr284:
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr382:
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
	goto st60;
tr747:
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr752:
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr758:
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr766:
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr770:
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr776:
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr783:
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
tr1094:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 188 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st60;
tr1078:
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st60;
st60:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof60;
case 60:
#line 2440 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr98;
		case 32: goto tr98;
		case 34: goto st51;
		case 59: goto tr99;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr98;
	goto tr79;
tr99:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr97:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 180 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st901;
tr120:
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr132:
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr142:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 170 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st901;
tr163:
#line 175 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr184:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr196:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 171 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st901;
tr215:
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr221:
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr231:
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr237:
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr241:
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr255:
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr262:
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr273:
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr279:
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr285:
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr383:
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
	goto st901;
tr748:
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr753:
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr759:
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr767:
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr771:
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr777:
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr784:
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
tr1095:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 188 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st901;
tr1080:
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st901;
st901:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof901;
case 901:
#line 2681 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr100;
		case 32: goto tr100;
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr101;
		case 99: goto tr102;
		case 100: goto tr103;
		case 104: goto tr104;
		case 105: goto tr105;
		case 109: goto tr106;
		case 110: goto tr107;
		case 114: goto tr108;
		case 115: goto tr109;
		case 125: goto tr110;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr100;
	goto tr79;
tr100:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st61;
st61:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof61;
case 61:
#line 2711 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr100;
		case 32: goto tr100;
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr101;
		case 99: goto tr102;
		case 100: goto tr103;
		case 104: goto tr104;
		case 105: goto tr105;
		case 109: goto tr106;
		case 110: goto tr107;
		case 114: goto tr108;
		case 115: goto tr109;
		case 125: goto tr110;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr100;
	goto tr79;
tr101:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st62;
st62:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof62;
case 62:
#line 2741 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 105: goto tr111;
		case 116: goto tr112;
	}
	goto tr79;
tr111:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st63;
st63:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof63;
case 63:
#line 2759 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr113;
		case 32: goto tr113;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr113;
	goto tr79;
tr113:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st64;
st64:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof64;
case 64:
#line 2779 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr113;
		case 32: goto tr113;
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr114;
		case 115: goto tr115;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr113;
	goto tr79;
tr114:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st65;
st65:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof65;
case 65:
#line 2801 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 111: goto tr116;
	}
	goto tr79;
tr116:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st66;
st66:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof66;
case 66:
#line 2818 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr117;
	}
	goto tr79;
tr117:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st67;
st67:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof67;
case 67:
#line 2835 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr118;
	}
	goto tr79;
tr118:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st68;
st68:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof68;
case 68:
#line 2852 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr119;
		case 32: goto tr119;
		case 34: goto st51;
		case 59: goto tr120;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr119;
	goto tr79;
tr115:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st69;
st69:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof69;
case 69:
#line 2873 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr121;
	}
	goto tr79;
tr121:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st70;
st70:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof70;
case 70:
#line 2890 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr122;
	}
	goto tr79;
tr122:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st71;
st71:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof71;
case 71:
#line 2907 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 107: goto tr123;
	}
	goto tr79;
tr123:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st72;
st72:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof72;
case 72:
#line 2924 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 95: goto tr124;
	}
	goto tr79;
tr124:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st73;
st73:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof73;
case 73:
#line 2941 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 112: goto tr125;
	}
	goto tr79;
tr125:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st74;
st74:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof74;
case 74:
#line 2958 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 108: goto tr126;
	}
	goto tr79;
tr126:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st75;
st75:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof75;
case 75:
#line 2975 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr127;
	}
	goto tr79;
tr127:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st76;
st76:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof76;
case 76:
#line 2992 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 121: goto tr128;
	}
	goto tr79;
tr128:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st77;
st77:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof77;
case 77:
#line 3009 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr129;
	}
	goto tr79;
tr129:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st78;
st78:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof78;
case 78:
#line 3026 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 114: goto tr130;
	}
	goto tr79;
tr130:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st79;
st79:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof79;
case 79:
#line 3043 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr131;
		case 32: goto tr131;
		case 34: goto st51;
		case 59: goto tr132;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr131;
	goto tr79;
tr112:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st80;
st80:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof80;
case 80:
#line 3064 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 116: goto tr133;
	}
	goto tr79;
tr133:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st81;
st81:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof81;
case 81:
#line 3081 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr134;
	}
	goto tr79;
tr134:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st82;
st82:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof82;
case 82:
#line 3098 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 99: goto tr135;
	}
	goto tr79;
tr135:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st83;
st83:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof83;
case 83:
#line 3115 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 107: goto tr136;
	}
	goto tr79;
tr136:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st84;
st84:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof84;
case 84:
#line 3132 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr137;
		case 32: goto tr137;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr137;
	goto tr79;
tr137:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st85;
st85:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof85;
case 85:
#line 3152 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr137;
		case 32: goto tr137;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr138;
	} else if ( (*( state.p)) >= 9 )
		goto tr137;
	goto tr79;
tr141:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st86;
tr138:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st86;
st86:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof86;
case 86:
#line 3185 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr139;
		case 32: goto tr139;
		case 34: goto st51;
		case 46: goto tr140;
		case 59: goto tr142;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr141;
	} else if ( (*( state.p)) >= 9 )
		goto tr139;
	goto tr79;
tr140:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st87;
st87:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof87;
case 87:
#line 3210 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr143;
	goto tr79;
tr143:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st88;
st88:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof88;
case 88:
#line 3228 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr139;
		case 32: goto tr139;
		case 34: goto st51;
		case 59: goto tr142;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr143;
	} else if ( (*( state.p)) >= 9 )
		goto tr139;
	goto tr79;
tr102:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st89;
st89:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof89;
case 89:
#line 3252 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 108: goto tr144;
		case 111: goto tr145;
	}
	goto tr79;
tr144:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st90;
st90:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof90;
case 90:
#line 3270 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 117: goto tr146;
	}
	goto tr79;
tr146:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st91;
st91:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof91;
case 91:
#line 3287 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 109: goto tr147;
	}
	goto tr79;
tr147:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st92;
st92:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof92;
case 92:
#line 3304 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 112: goto tr148;
	}
	goto tr79;
tr148:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st93;
st93:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof93;
case 93:
#line 3321 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 115: goto tr149;
	}
	goto tr79;
tr149:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st94;
st94:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof94;
case 94:
#line 3338 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 105: goto tr150;
	}
	goto tr79;
tr150:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st95;
st95:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof95;
case 95:
#line 3355 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 122: goto tr151;
	}
	goto tr79;
tr151:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st96;
st96:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof96;
case 96:
#line 3372 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr152;
	}
	goto tr79;
tr152:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st97;
st97:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof97;
case 97:
#line 3389 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr153;
		case 32: goto tr153;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr153;
	goto tr79;
tr153:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st98;
st98:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof98;
case 98:
#line 3409 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr153;
		case 32: goto tr153;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr154;
	} else if ( (*( state.p)) >= 9 )
		goto tr153;
	goto tr79;
tr154:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st99;
tr157:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st99;
st99:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof99;
case 99:
#line 3442 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr155;
		case 32: goto tr155;
		case 34: goto st51;
		case 46: goto tr156;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr157;
	} else if ( (*( state.p)) >= 9 )
		goto tr155;
	goto tr79;
tr158:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st100;
tr155:
#line 174 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st100;
st100:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof100;
case 100:
#line 3474 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr158;
		case 32: goto tr158;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr159;
	} else if ( (*( state.p)) >= 9 )
		goto tr158;
	goto tr79;
tr159:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st101;
tr162:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st101;
st101:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof101;
case 101:
#line 3507 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr160;
		case 32: goto tr160;
		case 34: goto st51;
		case 46: goto tr161;
		case 59: goto tr163;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr162;
	} else if ( (*( state.p)) >= 9 )
		goto tr160;
	goto tr79;
tr161:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st102;
st102:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof102;
case 102:
#line 3532 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr164;
	goto tr79;
tr164:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st103;
st103:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof103;
case 103:
#line 3550 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr160;
		case 32: goto tr160;
		case 34: goto st51;
		case 59: goto tr163;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr164;
	} else if ( (*( state.p)) >= 9 )
		goto tr160;
	goto tr79;
tr156:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st104;
st104:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof104;
case 104:
#line 3574 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr165;
	goto tr79;
tr165:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st105;
st105:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof105;
case 105:
#line 3592 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr155;
		case 32: goto tr155;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr165;
	} else if ( (*( state.p)) >= 9 )
		goto tr155;
	goto tr79;
tr145:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st106;
st106:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof106;
case 106:
#line 3615 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 109: goto tr166;
		case 117: goto tr167;
	}
	goto tr79;
tr166:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st107;
st107:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof107;
case 107:
#line 3633 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 112: goto tr168;
	}
	goto tr79;
tr168:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st108;
st108:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof108;
case 108:
#line 3650 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr169;
	}
	goto tr79;
tr169:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st109;
st109:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof109;
case 109:
#line 3667 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr170;
	}
	goto tr79;
tr170:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st110;
st110:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof110;
case 110:
#line 3684 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 105: goto tr171;
	}
	goto tr79;
tr171:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st111;
st111:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof111;
case 111:
#line 3701 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 111: goto tr172;
	}
	goto tr79;
tr172:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st112;
st112:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof112;
case 112:
#line 3718 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr173;
	}
	goto tr79;
tr173:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st113;
st113:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof113;
case 113:
#line 3735 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr174;
		case 32: goto tr174;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr174;
	goto tr79;
tr175:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st114;
tr174:
#line 178 "configparser.rl"
	{ spe.companion.push_back(Species::companion_t()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st114;
st114:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof114;
case 114:
#line 3763 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr175;
		case 32: goto tr175;
		case 34: goto st115;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr175;
	goto tr79;
st115:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof115;
case 115:
	switch( (*( state.p)) ) {
		case 13: goto tr177;
		case 32: goto tr177;
		case 34: goto tr77;
		case 92: goto tr78;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr177;
	goto tr76;
tr167:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st116;
st116:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof116;
case 116:
#line 3796 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr178;
	}
	goto tr79;
tr178:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st117;
st117:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof117;
case 117:
#line 3813 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 116: goto tr179;
	}
	goto tr79;
tr179:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st118;
st118:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof118;
case 118:
#line 3830 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr180;
		case 32: goto tr180;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr180;
	goto tr79;
tr180:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st119;
st119:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof119;
case 119:
#line 3850 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr180;
		case 32: goto tr180;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr181;
	} else if ( (*( state.p)) >= 9 )
		goto tr180;
	goto tr79;
tr181:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st120;
tr183:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st120;
st120:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof120;
case 120:
#line 3883 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr182;
		case 32: goto tr182;
		case 34: goto st51;
		case 59: goto tr184;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr183;
	} else if ( (*( state.p)) >= 9 )
		goto tr182;
	goto tr79;
tr103:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st121;
st121:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof121;
case 121:
#line 3907 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr185;
	}
	goto tr79;
tr185:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st122;
st122:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof122;
case 122:
#line 3924 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 102: goto tr186;
	}
	goto tr79;
tr186:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st123;
st123:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof123;
case 123:
#line 3941 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr187;
	}
	goto tr79;
tr187:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st124;
st124:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof124;
case 124:
#line 3958 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr188;
	}
	goto tr79;
tr188:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st125;
st125:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof125;
case 125:
#line 3975 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 115: goto tr189;
	}
	goto tr79;
tr189:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st126;
st126:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof126;
case 126:
#line 3992 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr190;
	}
	goto tr79;
tr190:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st127;
st127:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof127;
case 127:
#line 4009 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr191;
		case 32: goto tr191;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr191;
	goto tr79;
tr191:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st128;
st128:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof128;
case 128:
#line 4029 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr191;
		case 32: goto tr191;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr192;
	} else if ( (*( state.p)) >= 9 )
		goto tr191;
	goto tr79;
tr195:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st129;
tr192:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st129;
st129:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof129;
case 129:
#line 4062 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr193;
		case 32: goto tr193;
		case 34: goto st51;
		case 46: goto tr194;
		case 59: goto tr196;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr195;
	} else if ( (*( state.p)) >= 9 )
		goto tr193;
	goto tr79;
tr194:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st130;
st130:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof130;
case 130:
#line 4087 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr197;
	goto tr79;
tr197:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st131;
st131:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof131;
case 131:
#line 4105 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr193;
		case 32: goto tr193;
		case 34: goto st51;
		case 59: goto tr196;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr197;
	} else if ( (*( state.p)) >= 9 )
		goto tr193;
	goto tr79;
tr104:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st132;
st132:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof132;
case 132:
#line 4129 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr198;
	}
	goto tr79;
tr198:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st133;
st133:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof133;
case 133:
#line 4146 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 98: goto tr199;
	}
	goto tr79;
tr199:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st134;
st134:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof134;
case 134:
#line 4163 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 105: goto tr200;
	}
	goto tr79;
tr200:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st135;
st135:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof135;
case 135:
#line 4180 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 116: goto tr201;
	}
	goto tr79;
tr201:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st136;
st136:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof136;
case 136:
#line 4197 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr202;
	}
	goto tr79;
tr202:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st137;
st137:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof137;
case 137:
#line 4214 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 116: goto tr203;
	}
	goto tr79;
tr203:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st138;
st138:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof138;
case 138:
#line 4231 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr204;
		case 32: goto tr204;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr204;
	goto tr79;
tr204:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st139;
st139:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof139;
case 139:
#line 4251 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr204;
		case 32: goto tr204;
		case 34: goto st51;
		case 92: goto tr81;
		case 99: goto tr205;
		case 102: goto tr206;
		case 115: goto tr207;
		case 119: goto tr208;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr204;
	goto tr79;
tr205:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st140;
st140:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof140;
case 140:
#line 4275 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 111: goto tr209;
	}
	goto tr79;
tr209:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st141;
st141:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof141;
case 141:
#line 4292 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 114: goto tr210;
	}
	goto tr79;
tr210:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st142;
st142:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof142;
case 142:
#line 4309 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr211;
	}
	goto tr79;
tr211:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st143;
st143:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof143;
case 143:
#line 4326 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr212;
	}
	goto tr79;
tr212:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st144;
st144:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof144;
case 144:
#line 4343 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 114: goto tr213;
	}
	goto tr79;
tr213:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st145;
st145:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof145;
case 145:
#line 4360 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr214;
		case 32: goto tr214;
		case 34: goto st51;
		case 59: goto tr215;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr214;
	goto tr79;
tr206:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st146;
st146:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof146;
case 146:
#line 4381 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 108: goto tr216;
	}
	goto tr79;
tr216:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st147;
st147:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof147;
case 147:
#line 4398 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 111: goto tr217;
	}
	goto tr79;
tr217:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st148;
st148:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof148;
case 148:
#line 4415 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 111: goto tr218;
	}
	goto tr79;
tr218:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st149;
st149:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof149;
case 149:
#line 4432 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 114: goto tr219;
	}
	goto tr79;
tr219:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st150;
st150:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof150;
case 150:
#line 4449 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr220;
		case 32: goto tr220;
		case 34: goto st51;
		case 59: goto tr221;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr220;
	goto tr79;
tr207:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st151;
st151:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof151;
case 151:
#line 4470 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 104: goto tr222;
	}
	goto tr79;
tr222:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st152;
st152:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof152;
case 152:
#line 4487 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 111: goto tr223;
	}
	goto tr79;
tr223:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st153;
st153:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof153;
case 153:
#line 4504 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 114: goto tr224;
	}
	goto tr79;
tr224:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st154;
st154:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof154;
case 154:
#line 4521 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr225;
	}
	goto tr79;
tr225:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st155;
st155:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof155;
case 155:
#line 4538 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 108: goto tr226;
	}
	goto tr79;
tr226:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st156;
st156:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof156;
case 156:
#line 4555 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 105: goto tr227;
	}
	goto tr79;
tr227:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st157;
st157:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof157;
case 157:
#line 4572 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr228;
	}
	goto tr79;
tr228:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st158;
st158:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof158;
case 158:
#line 4589 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr229;
	}
	goto tr79;
tr229:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st159;
st159:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof159;
case 159:
#line 4606 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr230;
		case 32: goto tr230;
		case 34: goto st51;
		case 59: goto tr231;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr230;
	goto tr79;
tr208:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st160;
st160:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof160;
case 160:
#line 4627 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr232;
	}
	goto tr79;
tr232:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st161;
st161:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof161;
case 161:
#line 4644 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 108: goto tr233;
		case 116: goto tr234;
	}
	goto tr79;
tr233:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st162;
st162:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof162;
case 162:
#line 4662 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 107: goto tr235;
	}
	goto tr79;
tr235:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st163;
st163:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof163;
case 163:
#line 4679 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr236;
		case 32: goto tr236;
		case 34: goto st51;
		case 59: goto tr237;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr236;
	goto tr79;
tr234:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st164;
st164:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof164;
case 164:
#line 4700 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr238;
	}
	goto tr79;
tr238:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st165;
st165:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof165;
case 165:
#line 4717 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 114: goto tr239;
	}
	goto tr79;
tr239:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st166;
st166:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof166;
case 166:
#line 4734 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr240;
		case 32: goto tr240;
		case 34: goto st51;
		case 59: goto tr241;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr240;
	goto tr79;
tr105:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st167;
st167:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof167;
case 167:
#line 4755 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 100: goto tr242;
	}
	goto tr79;
tr242:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st168;
st168:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof168;
case 168:
#line 4772 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 108: goto tr243;
	}
	goto tr79;
tr243:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st169;
st169:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof169;
case 169:
#line 4789 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr244;
	}
	goto tr79;
tr244:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st170;
st170:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof170;
case 170:
#line 4806 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 95: goto tr245;
	}
	goto tr79;
tr245:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st171;
st171:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof171;
case 171:
#line 4823 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr246;
	}
	goto tr79;
tr246:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st172;
st172:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof172;
case 172:
#line 4840 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 105: goto tr247;
	}
	goto tr79;
tr247:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st173;
st173:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof173;
case 173:
#line 4857 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr248;
		case 32: goto tr248;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr248;
	goto tr79;
tr248:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st174;
st174:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof174;
case 174:
#line 4877 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr248;
		case 32: goto tr248;
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr249;
		case 114: goto tr250;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr248;
	goto tr79;
tr249:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st175;
st175:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof175;
case 175:
#line 4899 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 111: goto tr251;
	}
	goto tr79;
tr251:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st176;
st176:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof176;
case 176:
#line 4916 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr252;
	}
	goto tr79;
tr252:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st177;
st177:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof177;
case 177:
#line 4933 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr253;
	}
	goto tr79;
tr253:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st178;
st178:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof178;
case 178:
#line 4950 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr254;
		case 32: goto tr254;
		case 34: goto st51;
		case 59: goto tr255;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr254;
	goto tr79;
tr250:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st179;
st179:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof179;
case 179:
#line 4971 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr256;
	}
	goto tr79;
tr256:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st180;
st180:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof180;
case 180:
#line 4988 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr257;
	}
	goto tr79;
tr257:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st181;
st181:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof181;
case 181:
#line 5005 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 100: goto tr258;
	}
	goto tr79;
tr258:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st182;
st182:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof182;
case 182:
#line 5022 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 111: goto tr259;
	}
	goto tr79;
tr259:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st183;
st183:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof183;
case 183:
#line 5039 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 109: goto tr260;
	}
	goto tr79;
tr260:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st184;
st184:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof184;
case 184:
#line 5056 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr261;
		case 32: goto tr261;
		case 34: goto st51;
		case 59: goto tr262;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr261;
	goto tr79;
tr106:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st185;
st185:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof185;
case 185:
#line 5077 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 111: goto tr263;
	}
	goto tr79;
tr263:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st186;
st186:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof186;
case 186:
#line 5094 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 118: goto tr264;
	}
	goto tr79;
tr264:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st187;
st187:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof187;
case 187:
#line 5111 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr265;
	}
	goto tr79;
tr265:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st188;
st188:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof188;
case 188:
#line 5128 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr266;
		case 32: goto tr266;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr266;
	goto tr79;
tr266:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st189;
st189:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof189;
case 189:
#line 5148 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr266;
		case 32: goto tr266;
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr267;
		case 102: goto tr268;
		case 119: goto tr269;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr266;
	goto tr79;
tr267:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st190;
st190:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof190;
case 190:
#line 5171 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr270;
	}
	goto tr79;
tr270:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st191;
st191:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof191;
case 191:
#line 5188 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 121: goto tr271;
	}
	goto tr79;
tr271:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st192;
st192:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof192;
case 192:
#line 5205 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr272;
		case 32: goto tr272;
		case 34: goto st51;
		case 59: goto tr273;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr272;
	goto tr79;
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
#line 5226 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 108: goto tr274;
	}
	goto tr79;
tr274:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st194;
st194:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof194;
case 194:
#line 5243 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 111: goto tr275;
	}
	goto tr79;
tr275:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st195;
st195:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof195;
case 195:
#line 5260 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 111: goto tr276;
	}
	goto tr79;
tr276:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st196;
st196:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof196;
case 196:
#line 5277 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 114: goto tr277;
	}
	goto tr79;
tr277:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st197;
st197:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof197;
case 197:
#line 5294 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr278;
		case 32: goto tr278;
		case 34: goto st51;
		case 59: goto tr279;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr278;
	goto tr79;
tr269:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st198;
st198:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof198;
case 198:
#line 5315 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr280;
	}
	goto tr79;
tr280:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st199;
st199:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof199;
case 199:
#line 5332 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 116: goto tr281;
	}
	goto tr79;
tr281:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st200;
st200:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof200;
case 200:
#line 5349 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr282;
	}
	goto tr79;
tr282:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st201;
st201:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof201;
case 201:
#line 5366 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 114: goto tr283;
	}
	goto tr79;
tr283:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st202;
st202:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof202;
case 202:
#line 5383 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr284;
		case 32: goto tr284;
		case 34: goto st51;
		case 59: goto tr285;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr284;
	goto tr79;
tr107:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st203;
st203:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof203;
case 203:
#line 5404 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr286;
	}
	goto tr79;
tr286:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st204;
st204:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof204;
case 204:
#line 5421 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 109: goto tr287;
	}
	goto tr79;
tr287:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st205;
st205:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof205;
case 205:
#line 5438 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr288;
	}
	goto tr79;
tr288:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st206;
st206:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof206;
case 206:
#line 5455 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr289;
		case 32: goto tr289;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr289;
	goto tr79;
tr289:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st207;
st207:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof207;
case 207:
#line 5475 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr289;
		case 32: goto tr289;
		case 34: goto st208;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr289;
	goto tr79;
st208:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof208;
case 208:
	switch( (*( state.p)) ) {
		case 13: goto tr292;
		case 32: goto tr292;
		case 34: goto tr293;
		case 92: goto tr294;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr292;
	goto tr291;
tr291:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st209;
tr295:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st209;
st209:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof209;
case 209:
#line 5518 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
	}
	goto tr295;
tr293:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st210;
st210:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof210;
case 210:
#line 5534 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr298;
		case 32: goto tr298;
		case 59: goto tr299;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr298;
	goto st0;
tr294:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st211;
tr297:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st211;
st211:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof211;
case 211:
#line 5563 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr300;
		case 92: goto tr297;
	}
	goto tr295;
tr300:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st212;
st212:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof212;
case 212:
#line 5579 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr301;
		case 32: goto tr301;
		case 34: goto st210;
		case 59: goto tr302;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr301;
	goto tr295;
tr303:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st213;
tr1067:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 180 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st213;
tr344:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 170 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st213;
tr388:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st213;
tr399:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 171 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st213;
tr301:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 163 "configparser.rl"
	{ spe.name = state.match; }
	goto st213;
tr324:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st213;
tr336:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st213;
tr365:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 175 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st213;
tr420:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st213;
tr426:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st213;
tr436:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st213;
tr442:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st213;
tr446:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st213;
tr460:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st213;
tr467:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st213;
tr478:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st213;
tr484:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st213;
tr490:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st213;
tr497:
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
	goto st213;
tr505:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st213;
tr943:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st213;
tr948:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st213;
tr954:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st213;
tr962:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st213;
tr966:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st213;
tr972:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st213;
tr979:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st213;
tr1063:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 188 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st213;
st213:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof213;
case 213:
#line 5828 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr303;
		case 32: goto tr303;
		case 34: goto st210;
		case 59: goto tr304;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr303;
	goto tr295;
tr304:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st902;
tr1070:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 180 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st902;
tr347:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 170 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st902;
tr390:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st902;
tr402:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 171 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st902;
tr302:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 163 "configparser.rl"
	{ spe.name = state.match; }
	goto st902;
tr325:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st902;
tr337:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st902;
tr368:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 175 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st902;
tr421:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st902;
tr427:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st902;
tr437:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st902;
tr443:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st902;
tr447:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st902;
tr461:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st902;
tr468:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st902;
tr479:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st902;
tr485:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st902;
tr491:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st902;
tr498:
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
	goto st902;
tr507:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st902;
tr944:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st902;
tr949:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st902;
tr955:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st902;
tr963:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st902;
tr967:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st902;
tr973:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st902;
tr980:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st902;
tr1064:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 188 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st902;
st902:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof902;
case 902:
#line 6077 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr305;
		case 32: goto tr305;
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr306;
		case 99: goto tr307;
		case 100: goto tr308;
		case 104: goto tr309;
		case 105: goto tr310;
		case 109: goto tr311;
		case 110: goto tr312;
		case 114: goto tr313;
		case 115: goto tr314;
		case 125: goto tr315;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr305;
	goto tr295;
tr305:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st214;
st214:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof214;
case 214:
#line 6107 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr305;
		case 32: goto tr305;
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr306;
		case 99: goto tr307;
		case 100: goto tr308;
		case 104: goto tr309;
		case 105: goto tr310;
		case 109: goto tr311;
		case 110: goto tr312;
		case 114: goto tr313;
		case 115: goto tr314;
		case 125: goto tr315;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr305;
	goto tr295;
tr306:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st215;
st215:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof215;
case 215:
#line 6137 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 105: goto tr316;
		case 116: goto tr317;
	}
	goto tr295;
tr316:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st216;
st216:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof216;
case 216:
#line 6155 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr318;
		case 32: goto tr318;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr318;
	goto tr295;
tr318:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st217;
st217:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof217;
case 217:
#line 6175 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr318;
		case 32: goto tr318;
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr319;
		case 115: goto tr320;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr318;
	goto tr295;
tr319:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st218;
st218:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof218;
case 218:
#line 6197 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 111: goto tr321;
	}
	goto tr295;
tr321:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st219;
st219:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof219;
case 219:
#line 6214 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr322;
	}
	goto tr295;
tr322:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st220;
st220:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof220;
case 220:
#line 6231 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr323;
	}
	goto tr295;
tr323:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st221;
st221:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof221;
case 221:
#line 6248 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr324;
		case 32: goto tr324;
		case 34: goto st210;
		case 59: goto tr325;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr324;
	goto tr295;
tr320:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st222;
st222:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof222;
case 222:
#line 6269 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr326;
	}
	goto tr295;
tr326:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st223;
st223:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof223;
case 223:
#line 6286 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr327;
	}
	goto tr295;
tr327:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st224;
st224:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof224;
case 224:
#line 6303 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 107: goto tr328;
	}
	goto tr295;
tr328:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st225;
st225:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof225;
case 225:
#line 6320 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 95: goto tr329;
	}
	goto tr295;
tr329:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st226;
st226:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof226;
case 226:
#line 6337 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 112: goto tr330;
	}
	goto tr295;
tr330:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st227;
st227:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof227;
case 227:
#line 6354 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 108: goto tr331;
	}
	goto tr295;
tr331:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st228;
st228:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof228;
case 228:
#line 6371 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr332;
	}
	goto tr295;
tr332:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st229;
st229:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof229;
case 229:
#line 6388 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 121: goto tr333;
	}
	goto tr295;
tr333:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st230;
st230:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof230;
case 230:
#line 6405 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr334;
	}
	goto tr295;
tr334:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st231;
st231:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof231;
case 231:
#line 6422 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 114: goto tr335;
	}
	goto tr295;
tr335:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st232;
st232:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof232;
case 232:
#line 6439 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr336;
		case 32: goto tr336;
		case 34: goto st210;
		case 59: goto tr337;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr336;
	goto tr295;
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
#line 6460 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 116: goto tr338;
	}
	goto tr295;
tr338:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st234;
st234:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof234;
case 234:
#line 6477 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr339;
	}
	goto tr295;
tr339:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st235;
st235:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof235;
case 235:
#line 6494 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 99: goto tr340;
	}
	goto tr295;
tr340:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st236;
st236:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof236;
case 236:
#line 6511 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 107: goto tr341;
	}
	goto tr295;
tr341:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st237;
st237:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof237;
case 237:
#line 6528 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr342;
		case 32: goto tr342;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr342;
	goto tr295;
tr342:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st238;
st238:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof238;
case 238:
#line 6548 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr342;
		case 32: goto tr342;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr343;
	} else if ( (*( state.p)) >= 9 )
		goto tr342;
	goto tr295;
tr346:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st239;
tr343:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st239;
st239:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof239;
case 239:
#line 6581 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr344;
		case 32: goto tr344;
		case 34: goto st210;
		case 46: goto tr345;
		case 59: goto tr347;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr346;
	} else if ( (*( state.p)) >= 9 )
		goto tr344;
	goto tr295;
tr345:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st240;
st240:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof240;
case 240:
#line 6606 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr348;
	goto tr295;
tr348:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st241;
st241:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof241;
case 241:
#line 6624 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr344;
		case 32: goto tr344;
		case 34: goto st210;
		case 59: goto tr347;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr348;
	} else if ( (*( state.p)) >= 9 )
		goto tr344;
	goto tr295;
tr307:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st242;
st242:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof242;
case 242:
#line 6648 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 108: goto tr349;
		case 111: goto tr350;
	}
	goto tr295;
tr349:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st243;
st243:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof243;
case 243:
#line 6666 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 117: goto tr351;
	}
	goto tr295;
tr351:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st244;
st244:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof244;
case 244:
#line 6683 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 109: goto tr352;
	}
	goto tr295;
tr352:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st245;
st245:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof245;
case 245:
#line 6700 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 112: goto tr353;
	}
	goto tr295;
tr353:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st246;
st246:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof246;
case 246:
#line 6717 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 115: goto tr354;
	}
	goto tr295;
tr354:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st247;
st247:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof247;
case 247:
#line 6734 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 105: goto tr355;
	}
	goto tr295;
tr355:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st248;
st248:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof248;
case 248:
#line 6751 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 122: goto tr356;
	}
	goto tr295;
tr356:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st249;
st249:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof249;
case 249:
#line 6768 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr357;
	}
	goto tr295;
tr357:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st250;
st250:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof250;
case 250:
#line 6785 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr358;
		case 32: goto tr358;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr358;
	goto tr295;
tr358:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st251;
st251:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof251;
case 251:
#line 6805 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr358;
		case 32: goto tr358;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr359;
	} else if ( (*( state.p)) >= 9 )
		goto tr358;
	goto tr295;
tr362:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st252;
tr359:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st252;
st252:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof252;
case 252:
#line 6838 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr360;
		case 32: goto tr360;
		case 34: goto st210;
		case 46: goto tr361;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr362;
	} else if ( (*( state.p)) >= 9 )
		goto tr360;
	goto tr295;
tr363:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st253;
tr360:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 174 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st253;
st253:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof253;
case 253:
#line 6870 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr363;
		case 32: goto tr363;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr364;
	} else if ( (*( state.p)) >= 9 )
		goto tr363;
	goto tr295;
tr367:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st254;
tr364:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st254;
st254:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof254;
case 254:
#line 6903 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr365;
		case 32: goto tr365;
		case 34: goto st210;
		case 46: goto tr366;
		case 59: goto tr368;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr367;
	} else if ( (*( state.p)) >= 9 )
		goto tr365;
	goto tr295;
tr366:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st255;
st255:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof255;
case 255:
#line 6928 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr369;
	goto tr295;
tr369:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st256;
st256:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof256;
case 256:
#line 6946 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr365;
		case 32: goto tr365;
		case 34: goto st210;
		case 59: goto tr368;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr369;
	} else if ( (*( state.p)) >= 9 )
		goto tr365;
	goto tr295;
tr361:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st257;
st257:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof257;
case 257:
#line 6970 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr370;
	goto tr295;
tr370:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st258;
st258:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof258;
case 258:
#line 6988 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr360;
		case 32: goto tr360;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr370;
	} else if ( (*( state.p)) >= 9 )
		goto tr360;
	goto tr295;
tr350:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st259;
st259:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof259;
case 259:
#line 7011 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 109: goto tr371;
		case 117: goto tr372;
	}
	goto tr295;
tr371:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st260;
st260:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof260;
case 260:
#line 7029 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 112: goto tr373;
	}
	goto tr295;
tr373:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st261;
st261:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof261;
case 261:
#line 7046 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr374;
	}
	goto tr295;
tr374:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st262;
st262:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof262;
case 262:
#line 7063 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr375;
	}
	goto tr295;
tr375:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st263;
st263:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof263;
case 263:
#line 7080 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 105: goto tr376;
	}
	goto tr295;
tr376:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st264;
st264:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof264;
case 264:
#line 7097 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 111: goto tr377;
	}
	goto tr295;
tr377:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st265;
st265:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof265;
case 265:
#line 7114 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr378;
	}
	goto tr295;
tr378:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st266;
st266:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof266;
case 266:
#line 7131 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr379;
		case 32: goto tr379;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr379;
	goto tr295;
tr380:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st267;
tr379:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 178 "configparser.rl"
	{ spe.companion.push_back(Species::companion_t()); }
	goto st267;
st267:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof267;
case 267:
#line 7159 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr380;
		case 32: goto tr380;
		case 34: goto st268;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr380;
	goto tr295;
st268:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof268;
case 268:
	switch( (*( state.p)) ) {
		case 13: goto tr382;
		case 32: goto tr382;
		case 34: goto tr77;
		case 59: goto tr383;
		case 92: goto tr78;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr382;
	goto tr76;
tr372:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st269;
st269:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof269;
case 269:
#line 7193 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr384;
	}
	goto tr295;
tr384:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st270;
st270:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof270;
case 270:
#line 7210 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 116: goto tr385;
	}
	goto tr295;
tr385:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st271;
st271:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof271;
case 271:
#line 7227 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr386;
		case 32: goto tr386;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr386;
	goto tr295;
tr386:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st272;
st272:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof272;
case 272:
#line 7247 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr386;
		case 32: goto tr386;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr387;
	} else if ( (*( state.p)) >= 9 )
		goto tr386;
	goto tr295;
tr387:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st273;
tr389:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st273;
st273:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof273;
case 273:
#line 7280 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr388;
		case 32: goto tr388;
		case 34: goto st210;
		case 59: goto tr390;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr389;
	} else if ( (*( state.p)) >= 9 )
		goto tr388;
	goto tr295;
tr308:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st274;
st274:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof274;
case 274:
#line 7304 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr391;
	}
	goto tr295;
tr391:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st275;
st275:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof275;
case 275:
#line 7321 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 102: goto tr392;
	}
	goto tr295;
tr392:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st276;
st276:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof276;
case 276:
#line 7338 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr393;
	}
	goto tr295;
tr393:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st277;
st277:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof277;
case 277:
#line 7355 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr394;
	}
	goto tr295;
tr394:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st278;
st278:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof278;
case 278:
#line 7372 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 115: goto tr395;
	}
	goto tr295;
tr395:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st279;
st279:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof279;
case 279:
#line 7389 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr396;
	}
	goto tr295;
tr396:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st280;
st280:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof280;
case 280:
#line 7406 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr397;
		case 32: goto tr397;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr397;
	goto tr295;
tr397:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st281;
st281:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof281;
case 281:
#line 7426 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr397;
		case 32: goto tr397;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr398;
	} else if ( (*( state.p)) >= 9 )
		goto tr397;
	goto tr295;
tr401:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st282;
tr398:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st282;
st282:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof282;
case 282:
#line 7459 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr399;
		case 32: goto tr399;
		case 34: goto st210;
		case 46: goto tr400;
		case 59: goto tr402;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr401;
	} else if ( (*( state.p)) >= 9 )
		goto tr399;
	goto tr295;
tr400:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st283;
st283:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof283;
case 283:
#line 7484 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr403;
	goto tr295;
tr403:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st284;
st284:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof284;
case 284:
#line 7502 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr399;
		case 32: goto tr399;
		case 34: goto st210;
		case 59: goto tr402;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr403;
	} else if ( (*( state.p)) >= 9 )
		goto tr399;
	goto tr295;
tr309:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st285;
st285:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof285;
case 285:
#line 7526 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr404;
	}
	goto tr295;
tr404:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st286;
st286:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof286;
case 286:
#line 7543 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 98: goto tr405;
	}
	goto tr295;
tr405:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st287;
st287:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof287;
case 287:
#line 7560 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 105: goto tr406;
	}
	goto tr295;
tr406:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st288;
st288:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof288;
case 288:
#line 7577 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 116: goto tr407;
	}
	goto tr295;
tr407:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st289;
st289:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof289;
case 289:
#line 7594 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr408;
	}
	goto tr295;
tr408:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st290;
st290:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof290;
case 290:
#line 7611 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 116: goto tr409;
	}
	goto tr295;
tr409:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st291;
st291:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof291;
case 291:
#line 7628 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr410;
		case 32: goto tr410;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr410;
	goto tr295;
tr410:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st292;
st292:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof292;
case 292:
#line 7648 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr410;
		case 32: goto tr410;
		case 34: goto st210;
		case 92: goto tr297;
		case 99: goto tr411;
		case 102: goto tr412;
		case 115: goto tr413;
		case 119: goto tr414;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr410;
	goto tr295;
tr411:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st293;
st293:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof293;
case 293:
#line 7672 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 111: goto tr415;
	}
	goto tr295;
tr415:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st294;
st294:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof294;
case 294:
#line 7689 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 114: goto tr416;
	}
	goto tr295;
tr416:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st295;
st295:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof295;
case 295:
#line 7706 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr417;
	}
	goto tr295;
tr417:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st296;
st296:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof296;
case 296:
#line 7723 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr418;
	}
	goto tr295;
tr418:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st297;
st297:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof297;
case 297:
#line 7740 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 114: goto tr419;
	}
	goto tr295;
tr419:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st298;
st298:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof298;
case 298:
#line 7757 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr420;
		case 32: goto tr420;
		case 34: goto st210;
		case 59: goto tr421;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr420;
	goto tr295;
tr412:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st299;
st299:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof299;
case 299:
#line 7778 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 108: goto tr422;
	}
	goto tr295;
tr422:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st300;
st300:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof300;
case 300:
#line 7795 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 111: goto tr423;
	}
	goto tr295;
tr423:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st301;
st301:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof301;
case 301:
#line 7812 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 111: goto tr424;
	}
	goto tr295;
tr424:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st302;
st302:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof302;
case 302:
#line 7829 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 114: goto tr425;
	}
	goto tr295;
tr425:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st303;
st303:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof303;
case 303:
#line 7846 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr426;
		case 32: goto tr426;
		case 34: goto st210;
		case 59: goto tr427;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr426;
	goto tr295;
tr413:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st304;
st304:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof304;
case 304:
#line 7867 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 104: goto tr428;
	}
	goto tr295;
tr428:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st305;
st305:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof305;
case 305:
#line 7884 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 111: goto tr429;
	}
	goto tr295;
tr429:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st306;
st306:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof306;
case 306:
#line 7901 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 114: goto tr430;
	}
	goto tr295;
tr430:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st307;
st307:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof307;
case 307:
#line 7918 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr431;
	}
	goto tr295;
tr431:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st308;
st308:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof308;
case 308:
#line 7935 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 108: goto tr432;
	}
	goto tr295;
tr432:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st309;
st309:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof309;
case 309:
#line 7952 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 105: goto tr433;
	}
	goto tr295;
tr433:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st310;
st310:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof310;
case 310:
#line 7969 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr434;
	}
	goto tr295;
tr434:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st311;
st311:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof311;
case 311:
#line 7986 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr435;
	}
	goto tr295;
tr435:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st312;
st312:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof312;
case 312:
#line 8003 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr436;
		case 32: goto tr436;
		case 34: goto st210;
		case 59: goto tr437;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr436;
	goto tr295;
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
#line 8024 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr438;
	}
	goto tr295;
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
#line 8041 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 108: goto tr439;
		case 116: goto tr440;
	}
	goto tr295;
tr439:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st315;
st315:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof315;
case 315:
#line 8059 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 107: goto tr441;
	}
	goto tr295;
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
#line 8076 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr442;
		case 32: goto tr442;
		case 34: goto st210;
		case 59: goto tr443;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr442;
	goto tr295;
tr440:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st317;
st317:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof317;
case 317:
#line 8097 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr444;
	}
	goto tr295;
tr444:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st318;
st318:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof318;
case 318:
#line 8114 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 114: goto tr445;
	}
	goto tr295;
tr445:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st319;
st319:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof319;
case 319:
#line 8131 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr446;
		case 32: goto tr446;
		case 34: goto st210;
		case 59: goto tr447;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr446;
	goto tr295;
tr310:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st320;
st320:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof320;
case 320:
#line 8152 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 100: goto tr448;
	}
	goto tr295;
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
#line 8169 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 108: goto tr449;
	}
	goto tr295;
tr449:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st322;
st322:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof322;
case 322:
#line 8186 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr450;
	}
	goto tr295;
tr450:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st323;
st323:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof323;
case 323:
#line 8203 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 95: goto tr451;
	}
	goto tr295;
tr451:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st324;
st324:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof324;
case 324:
#line 8220 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr452;
	}
	goto tr295;
tr452:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st325;
st325:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof325;
case 325:
#line 8237 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 105: goto tr453;
	}
	goto tr295;
tr453:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st326;
st326:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof326;
case 326:
#line 8254 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr454;
		case 32: goto tr454;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr454;
	goto tr295;
tr454:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st327;
st327:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof327;
case 327:
#line 8274 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr454;
		case 32: goto tr454;
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr455;
		case 114: goto tr456;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr454;
	goto tr295;
tr455:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st328;
st328:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof328;
case 328:
#line 8296 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 111: goto tr457;
	}
	goto tr295;
tr457:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st329;
st329:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof329;
case 329:
#line 8313 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr458;
	}
	goto tr295;
tr458:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st330;
st330:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof330;
case 330:
#line 8330 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr459;
	}
	goto tr295;
tr459:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st331;
st331:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof331;
case 331:
#line 8347 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr460;
		case 32: goto tr460;
		case 34: goto st210;
		case 59: goto tr461;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr460;
	goto tr295;
tr456:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st332;
st332:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof332;
case 332:
#line 8368 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr462;
	}
	goto tr295;
tr462:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st333;
st333:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof333;
case 333:
#line 8385 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr463;
	}
	goto tr295;
tr463:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st334;
st334:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof334;
case 334:
#line 8402 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 100: goto tr464;
	}
	goto tr295;
tr464:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st335;
st335:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof335;
case 335:
#line 8419 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 111: goto tr465;
	}
	goto tr295;
tr465:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st336;
st336:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof336;
case 336:
#line 8436 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 109: goto tr466;
	}
	goto tr295;
tr466:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st337;
st337:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof337;
case 337:
#line 8453 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr467;
		case 32: goto tr467;
		case 34: goto st210;
		case 59: goto tr468;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr467;
	goto tr295;
tr311:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st338;
st338:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof338;
case 338:
#line 8474 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 111: goto tr469;
	}
	goto tr295;
tr469:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st339;
st339:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof339;
case 339:
#line 8491 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 118: goto tr470;
	}
	goto tr295;
tr470:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st340;
st340:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof340;
case 340:
#line 8508 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr471;
	}
	goto tr295;
tr471:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st341;
st341:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof341;
case 341:
#line 8525 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr472;
		case 32: goto tr472;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr472;
	goto tr295;
tr472:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st342;
st342:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof342;
case 342:
#line 8545 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr472;
		case 32: goto tr472;
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr473;
		case 102: goto tr474;
		case 119: goto tr475;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr472;
	goto tr295;
tr473:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st343;
st343:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof343;
case 343:
#line 8568 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr476;
	}
	goto tr295;
tr476:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st344;
st344:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof344;
case 344:
#line 8585 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 121: goto tr477;
	}
	goto tr295;
tr477:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st345;
st345:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof345;
case 345:
#line 8602 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr478;
		case 32: goto tr478;
		case 34: goto st210;
		case 59: goto tr479;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr478;
	goto tr295;
tr474:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st346;
st346:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof346;
case 346:
#line 8623 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 108: goto tr480;
	}
	goto tr295;
tr480:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st347;
st347:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof347;
case 347:
#line 8640 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 111: goto tr481;
	}
	goto tr295;
tr481:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st348;
st348:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof348;
case 348:
#line 8657 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 111: goto tr482;
	}
	goto tr295;
tr482:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st349;
st349:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof349;
case 349:
#line 8674 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 114: goto tr483;
	}
	goto tr295;
tr483:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st350;
st350:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof350;
case 350:
#line 8691 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr484;
		case 32: goto tr484;
		case 34: goto st210;
		case 59: goto tr485;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr484;
	goto tr295;
tr475:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st351;
st351:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof351;
case 351:
#line 8712 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr486;
	}
	goto tr295;
tr486:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st352;
st352:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof352;
case 352:
#line 8729 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 116: goto tr487;
	}
	goto tr295;
tr487:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st353;
st353:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof353;
case 353:
#line 8746 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr488;
	}
	goto tr295;
tr488:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st354;
st354:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof354;
case 354:
#line 8763 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 114: goto tr489;
	}
	goto tr295;
tr489:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st355;
st355:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof355;
case 355:
#line 8780 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr490;
		case 32: goto tr490;
		case 34: goto st210;
		case 59: goto tr491;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr490;
	goto tr295;
tr312:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st356;
st356:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof356;
case 356:
#line 8801 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr492;
	}
	goto tr295;
tr492:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st357;
st357:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof357;
case 357:
#line 8818 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 109: goto tr493;
	}
	goto tr295;
tr493:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st358;
st358:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof358;
case 358:
#line 8835 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr494;
	}
	goto tr295;
tr494:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st359;
st359:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof359;
case 359:
#line 8852 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr495;
		case 32: goto tr495;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr495;
	goto tr295;
tr495:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st360;
st360:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof360;
case 360:
#line 8872 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr495;
		case 32: goto tr495;
		case 34: goto st361;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr495;
	goto tr295;
st361:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof361;
case 361:
	switch( (*( state.p)) ) {
		case 13: goto tr497;
		case 32: goto tr497;
		case 34: goto tr293;
		case 59: goto tr498;
		case 92: goto tr294;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr497;
	goto tr291;
tr313:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st362;
st362:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof362;
case 362:
#line 8906 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr499;
	}
	goto tr295;
tr499:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st363;
st363:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof363;
case 363:
#line 8923 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr500;
	}
	goto tr295;
tr500:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st364;
st364:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof364;
case 364:
#line 8940 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 103: goto tr501;
	}
	goto tr295;
tr501:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st365;
st365:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof365;
case 365:
#line 8957 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr502;
	}
	goto tr295;
tr502:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st366;
st366:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof366;
case 366:
#line 8974 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr503;
		case 32: goto tr503;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr503;
	goto tr295;
tr503:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st367;
st367:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof367;
case 367:
#line 8994 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr503;
		case 32: goto tr503;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr504;
	} else if ( (*( state.p)) >= 9 )
		goto tr503;
	goto tr295;
tr506:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st368;
tr504:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st368;
st368:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof368;
case 368:
#line 9027 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr505;
		case 32: goto tr505;
		case 34: goto st210;
		case 59: goto tr507;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr506;
	} else if ( (*( state.p)) >= 9 )
		goto tr505;
	goto tr295;
tr314:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st369;
st369:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof369;
case 369:
#line 9051 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 107: goto tr508;
	}
	goto tr295;
tr508:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st370;
st370:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof370;
case 370:
#line 9068 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 105: goto tr509;
	}
	goto tr295;
tr509:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st371;
st371:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof371;
case 371:
#line 9085 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr510;
	}
	goto tr295;
tr510:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st372;
st372:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof372;
case 372:
#line 9102 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr511;
		case 32: goto tr511;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr511;
	goto tr295;
tr511:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st373;
st373:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof373;
case 373:
#line 9122 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr511;
		case 32: goto tr511;
		case 34: goto st374;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr511;
	goto tr295;
st374:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof374;
case 374:
	switch( (*( state.p)) ) {
		case 13: goto tr514;
		case 32: goto tr514;
		case 34: goto tr515;
		case 59: goto tr516;
		case 92: goto tr517;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr514;
	goto tr513;
tr513:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st375;
tr518:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st375;
st375:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof375;
case 375:
#line 9166 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
	}
	goto tr518;
tr515:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st376;
st376:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof376;
case 376:
#line 9182 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr521;
		case 32: goto tr521;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr521;
	goto st0;
tr521:
#line 140 "configparser.rl"
	{ spe.skin.text = state.match; }
	goto st377;
st377:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof377;
case 377:
#line 9198 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st377;
		case 32: goto st377;
		case 98: goto st378;
		case 100: goto st422;
		case 110: goto st425;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st377;
	goto st0;
st378:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof378;
case 378:
	if ( (*( state.p)) == 114 )
		goto st379;
	goto st0;
st379:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof379;
case 379:
	if ( (*( state.p)) == 105 )
		goto st380;
	goto st0;
st380:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof380;
case 380:
	if ( (*( state.p)) == 103 )
		goto st381;
	goto st0;
st381:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof381;
case 381:
	if ( (*( state.p)) == 104 )
		goto st382;
	goto st0;
st382:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof382;
case 382:
	if ( (*( state.p)) == 116 )
		goto st383;
	goto st0;
st383:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof383;
case 383:
	switch( (*( state.p)) ) {
		case 13: goto tr531;
		case 32: goto tr531;
		case 95: goto tr532;
		case 98: goto tr533;
		case 99: goto tr534;
		case 103: goto tr535;
		case 109: goto tr536;
		case 114: goto tr537;
		case 119: goto tr538;
		case 121: goto tr539;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr531;
	goto st0;
tr531:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st384;
tr593:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st384;
st384:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof384;
case 384:
#line 9275 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto st384;
		case 32: goto st384;
		case 98: goto st385;
		case 99: goto st391;
		case 103: goto st395;
		case 109: goto st400;
		case 114: goto st407;
		case 119: goto st410;
		case 121: goto st415;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st384;
	goto st0;
tr533:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st385;
tr595:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st385;
st385:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof385;
case 385:
#line 9302 "configparser.h"
	if ( (*( state.p)) == 108 )
		goto st386;
	goto st0;
st386:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof386;
case 386:
	switch( (*( state.p)) ) {
		case 97: goto st387;
		case 117: goto st389;
	}
	goto st0;
st387:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof387;
case 387:
	if ( (*( state.p)) == 99 )
		goto st388;
	goto st0;
st388:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof388;
case 388:
	if ( (*( state.p)) == 107 )
		goto st22;
	goto st0;
st389:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof389;
case 389:
	if ( (*( state.p)) == 101 )
		goto st390;
	goto st0;
st390:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof390;
case 390:
	switch( (*( state.p)) ) {
		case 13: goto tr553;
		case 32: goto tr553;
		case 59: goto tr554;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr553;
	goto st0;
tr534:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st391;
tr596:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st391;
st391:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof391;
case 391:
#line 9360 "configparser.h"
	if ( (*( state.p)) == 121 )
		goto st392;
	goto st0;
st392:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof392;
case 392:
	if ( (*( state.p)) == 97 )
		goto st393;
	goto st0;
st393:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof393;
case 393:
	if ( (*( state.p)) == 110 )
		goto st394;
	goto st0;
st394:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof394;
case 394:
	switch( (*( state.p)) ) {
		case 13: goto tr558;
		case 32: goto tr558;
		case 59: goto tr559;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr558;
	goto st0;
tr535:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st395;
tr597:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st395;
st395:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof395;
case 395:
#line 9402 "configparser.h"
	if ( (*( state.p)) == 114 )
		goto st396;
	goto st0;
st396:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof396;
case 396:
	if ( (*( state.p)) == 101 )
		goto st397;
	goto st0;
st397:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof397;
case 397:
	if ( (*( state.p)) == 101 )
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
	switch( (*( state.p)) ) {
		case 13: goto tr564;
		case 32: goto tr564;
		case 59: goto tr565;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr564;
	goto st0;
tr536:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st400;
tr598:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st400;
st400:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof400;
case 400:
#line 9451 "configparser.h"
	if ( (*( state.p)) == 97 )
		goto st401;
	goto st0;
st401:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof401;
case 401:
	if ( (*( state.p)) == 103 )
		goto st402;
	goto st0;
st402:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof402;
case 402:
	if ( (*( state.p)) == 101 )
		goto st403;
	goto st0;
st403:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof403;
case 403:
	if ( (*( state.p)) == 110 )
		goto st404;
	goto st0;
st404:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof404;
case 404:
	if ( (*( state.p)) == 116 )
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
	switch( (*( state.p)) ) {
		case 13: goto tr572;
		case 32: goto tr572;
		case 59: goto tr573;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr572;
	goto st0;
tr537:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st407;
tr599:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st407;
st407:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof407;
case 407:
#line 9514 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st408;
	goto st0;
st408:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof408;
case 408:
	if ( (*( state.p)) == 100 )
		goto st409;
	goto st0;
st409:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof409;
case 409:
	switch( (*( state.p)) ) {
		case 13: goto tr576;
		case 32: goto tr576;
		case 59: goto tr577;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr576;
	goto st0;
tr538:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st410;
tr600:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st410;
st410:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof410;
case 410:
#line 9549 "configparser.h"
	if ( (*( state.p)) == 104 )
		goto st411;
	goto st0;
st411:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof411;
case 411:
	if ( (*( state.p)) == 105 )
		goto st412;
	goto st0;
st412:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof412;
case 412:
	if ( (*( state.p)) == 116 )
		goto st413;
	goto st0;
st413:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof413;
case 413:
	if ( (*( state.p)) == 101 )
		goto st414;
	goto st0;
st414:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof414;
case 414:
	switch( (*( state.p)) ) {
		case 13: goto tr582;
		case 32: goto tr582;
		case 59: goto tr583;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr582;
	goto st0;
tr539:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st415;
tr601:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st415;
st415:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof415;
case 415:
#line 9598 "configparser.h"
	if ( (*( state.p)) == 101 )
		goto st416;
	goto st0;
st416:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof416;
case 416:
	if ( (*( state.p)) == 108 )
		goto st417;
	goto st0;
st417:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof417;
case 417:
	if ( (*( state.p)) == 108 )
		goto st418;
	goto st0;
st418:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof418;
case 418:
	if ( (*( state.p)) == 111 )
		goto st419;
	goto st0;
st419:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof419;
case 419:
	if ( (*( state.p)) == 119 )
		goto st420;
	goto st0;
st420:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof420;
case 420:
	switch( (*( state.p)) ) {
		case 13: goto tr589;
		case 32: goto tr589;
		case 59: goto tr590;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr589;
	goto st0;
tr532:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st421;
tr594:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st421;
st421:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof421;
case 421:
#line 9654 "configparser.h"
	switch( (*( state.p)) ) {
		case 98: goto st385;
		case 99: goto st391;
		case 103: goto st395;
		case 109: goto st400;
		case 114: goto st407;
		case 119: goto st410;
		case 121: goto st415;
	}
	goto st0;
st422:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof422;
case 422:
	if ( (*( state.p)) == 105 )
		goto st423;
	goto st0;
st423:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof423;
case 423:
	if ( (*( state.p)) == 109 )
		goto st424;
	goto st0;
st424:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof424;
case 424:
	switch( (*( state.p)) ) {
		case 13: goto tr593;
		case 32: goto tr593;
		case 95: goto tr594;
		case 98: goto tr595;
		case 99: goto tr596;
		case 103: goto tr597;
		case 109: goto tr598;
		case 114: goto tr599;
		case 119: goto tr600;
		case 121: goto tr601;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr593;
	goto st0;
st425:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof425;
case 425:
	if ( (*( state.p)) == 111 )
		goto st426;
	goto st0;
st426:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof426;
case 426:
	if ( (*( state.p)) == 110 )
		goto st427;
	goto st0;
st427:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof427;
case 427:
	if ( (*( state.p)) == 101 )
		goto st22;
	goto st0;
tr517:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st428;
tr520:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st428;
st428:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof428;
case 428:
#line 9739 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto tr604;
		case 92: goto tr520;
	}
	goto tr518;
tr604:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st429;
st429:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof429;
case 429:
#line 9755 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr605;
		case 32: goto tr605;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr605;
	goto tr518;
tr606:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st430;
tr605:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 140 "configparser.rl"
	{ spe.skin.text = state.match; }
	goto st430;
tr1008:
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
	goto st430;
st430:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof430;
case 430:
#line 9795 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr606;
		case 32: goto tr606;
		case 34: goto st376;
		case 92: goto tr520;
		case 98: goto tr607;
		case 100: goto tr608;
		case 110: goto tr609;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr606;
	goto tr518;
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
#line 9818 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 114: goto tr610;
	}
	goto tr518;
tr610:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st432;
st432:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof432;
case 432:
#line 9835 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 105: goto tr611;
	}
	goto tr518;
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
#line 9852 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 103: goto tr612;
	}
	goto tr518;
tr612:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st434;
st434:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof434;
case 434:
#line 9869 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 104: goto tr613;
	}
	goto tr518;
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
#line 9886 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 116: goto tr614;
	}
	goto tr518;
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
#line 9903 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr615;
		case 32: goto tr615;
		case 34: goto st376;
		case 92: goto tr520;
		case 95: goto tr616;
		case 98: goto tr617;
		case 99: goto tr618;
		case 103: goto tr619;
		case 109: goto tr620;
		case 114: goto tr621;
		case 119: goto tr622;
		case 121: goto tr623;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr615;
	goto tr518;
tr624:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st437;
tr615:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st437;
tr1052:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st437;
st437:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof437;
case 437:
#line 9947 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr624;
		case 32: goto tr624;
		case 34: goto st376;
		case 92: goto tr520;
		case 98: goto tr625;
		case 99: goto tr626;
		case 103: goto tr627;
		case 109: goto tr628;
		case 114: goto tr629;
		case 119: goto tr630;
		case 121: goto tr631;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr624;
	goto tr518;
tr625:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st438;
tr617:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st438;
tr1054:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st438;
st438:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof438;
case 438:
#line 9990 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 108: goto tr632;
	}
	goto tr518;
tr632:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st439;
st439:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof439;
case 439:
#line 10007 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr633;
		case 117: goto tr634;
	}
	goto tr518;
tr633:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st440;
st440:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof440;
case 440:
#line 10025 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 99: goto tr635;
	}
	goto tr518;
tr635:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st441;
st441:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof441;
case 441:
#line 10042 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 107: goto tr636;
	}
	goto tr518;
tr636:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st442;
tr1089:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 180 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st442;
tr677:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 170 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st442;
tr802:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st442;
tr813:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 171 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st442;
tr657:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st442;
tr669:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st442;
tr698:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 175 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st442;
tr514:
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
	goto st442;
tr834:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st442;
tr840:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st442;
tr850:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st442;
tr856:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st442;
tr860:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st442;
tr874:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st442;
tr881:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st442;
tr892:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st442;
tr898:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st442;
tr904:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st442;
tr1000:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st442;
tr1012:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st442;
tr1017:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st442;
tr1023:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st442;
tr1031:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st442;
tr1035:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st442;
tr1041:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st442;
tr1048:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st442;
tr1009:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 188 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st442;
st442:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof442;
case 442:
#line 10279 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr636;
		case 32: goto tr636;
		case 34: goto st376;
		case 59: goto tr637;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr636;
	goto tr518;
tr637:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st903;
tr1092:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 180 "configparser.rl"
	{ spe.companion.back().chance = ::atof(state.match.c_str()); }
	goto st903;
tr680:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 170 "configparser.rl"
	{ spe.attack = ::atof(state.match.c_str()); }
	goto st903;
tr804:
#line 162 "configparser.rl"
	{ spe.count = ::atoi(state.match.c_str()); }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st903;
tr816:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 171 "configparser.rl"
	{ spe.defense = ::atof(state.match.c_str()); }
	goto st903;
tr658:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 150 "configparser.rl"
	{ spe.ai = Species::ai_t::none; }
	goto st903;
tr670:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 151 "configparser.rl"
	{ spe.ai = Species::ai_t::seek_player; }
	goto st903;
tr701:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 175 "configparser.rl"
	{ spe.clumpsize.deviation = ::atof(state.match.c_str()); }
	goto st903;
tr516:
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
	goto st903;
tr835:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 146 "configparser.rl"
	{ spe.habitat = Species::habitat_t::corner; }
	goto st903;
tr841:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 144 "configparser.rl"
	{ spe.habitat = Species::habitat_t::floor; }
	goto st903;
tr851:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 147 "configparser.rl"
	{ spe.habitat = Species::habitat_t::shoreline; }
	goto st903;
tr857:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 143 "configparser.rl"
	{ spe.habitat = Species::habitat_t::walk; }
	goto st903;
tr861:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 145 "configparser.rl"
	{ spe.habitat = Species::habitat_t::water; }
	goto st903;
tr875:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 154 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::none; }
	goto st903;
tr882:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 155 "configparser.rl"
	{ spe.idle_ai = Species::idle_ai_t::random; }
	goto st903;
tr893:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 158 "configparser.rl"
	{ spe.move = Species::move_t::any; }
	goto st903;
tr899:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 159 "configparser.rl"
	{ spe.move = Species::move_t::floor; }
	goto st903;
tr905:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 160 "configparser.rl"
	{ spe.move = Species::move_t::water; }
	goto st903;
tr1002:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 169 "configparser.rl"
	{ spe.range = ::atoi(state.match.c_str()); }
	goto st903;
tr1013:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 130 "configparser.rl"
	{ add_color(spe.skin.fore, 4); }
	goto st903;
tr1018:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 132 "configparser.rl"
	{ add_color(spe.skin.fore, 6); }
	goto st903;
tr1024:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 128 "configparser.rl"
	{ add_color(spe.skin.fore, 2); }
	goto st903;
tr1032:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 131 "configparser.rl"
	{ add_color(spe.skin.fore, 5); }
	goto st903;
tr1036:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 127 "configparser.rl"
	{ add_color(spe.skin.fore, 1); }
	goto st903;
tr1042:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 133 "configparser.rl"
	{ add_color(spe.skin.fore, 7); }
	goto st903;
tr1049:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 129 "configparser.rl"
	{ add_color(spe.skin.fore, 3); }
	goto st903;
tr1010:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 188 "configparser.rl"
	{ { state.cs =  state.stack[-- state.top];goto _again;} }
	goto st903;
st903:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof903;
case 903:
#line 10520 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr638;
		case 32: goto tr638;
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr639;
		case 99: goto tr640;
		case 100: goto tr641;
		case 104: goto tr642;
		case 105: goto tr643;
		case 109: goto tr644;
		case 110: goto tr645;
		case 114: goto tr646;
		case 115: goto tr647;
		case 125: goto tr648;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr638;
	goto tr518;
tr638:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st443;
st443:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof443;
case 443:
#line 10550 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr638;
		case 32: goto tr638;
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr639;
		case 99: goto tr640;
		case 100: goto tr641;
		case 104: goto tr642;
		case 105: goto tr643;
		case 109: goto tr644;
		case 110: goto tr645;
		case 114: goto tr646;
		case 115: goto tr647;
		case 125: goto tr648;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr638;
	goto tr518;
tr639:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st444;
st444:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof444;
case 444:
#line 10580 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 105: goto tr649;
		case 116: goto tr650;
	}
	goto tr518;
tr649:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st445;
st445:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof445;
case 445:
#line 10598 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr651;
		case 32: goto tr651;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr651;
	goto tr518;
tr651:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st446;
st446:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof446;
case 446:
#line 10618 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr651;
		case 32: goto tr651;
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr652;
		case 115: goto tr653;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr651;
	goto tr518;
tr652:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st447;
st447:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof447;
case 447:
#line 10640 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 111: goto tr654;
	}
	goto tr518;
tr654:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st448;
st448:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof448;
case 448:
#line 10657 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr655;
	}
	goto tr518;
tr655:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st449;
st449:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof449;
case 449:
#line 10674 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr656;
	}
	goto tr518;
tr656:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st450;
st450:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof450;
case 450:
#line 10691 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr657;
		case 32: goto tr657;
		case 34: goto st376;
		case 59: goto tr658;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr657;
	goto tr518;
tr653:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st451;
st451:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof451;
case 451:
#line 10712 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr659;
	}
	goto tr518;
tr659:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st452;
st452:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof452;
case 452:
#line 10729 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr660;
	}
	goto tr518;
tr660:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st453;
st453:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof453;
case 453:
#line 10746 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 107: goto tr661;
	}
	goto tr518;
tr661:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st454;
st454:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof454;
case 454:
#line 10763 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 95: goto tr662;
	}
	goto tr518;
tr662:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st455;
st455:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof455;
case 455:
#line 10780 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 112: goto tr663;
	}
	goto tr518;
tr663:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st456;
st456:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof456;
case 456:
#line 10797 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 108: goto tr664;
	}
	goto tr518;
tr664:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st457;
st457:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof457;
case 457:
#line 10814 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr665;
	}
	goto tr518;
tr665:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st458;
st458:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof458;
case 458:
#line 10831 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 121: goto tr666;
	}
	goto tr518;
tr666:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st459;
st459:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof459;
case 459:
#line 10848 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr667;
	}
	goto tr518;
tr667:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st460;
st460:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof460;
case 460:
#line 10865 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 114: goto tr668;
	}
	goto tr518;
tr668:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st461;
st461:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof461;
case 461:
#line 10882 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr669;
		case 32: goto tr669;
		case 34: goto st376;
		case 59: goto tr670;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr669;
	goto tr518;
tr650:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st462;
st462:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof462;
case 462:
#line 10903 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 116: goto tr671;
	}
	goto tr518;
tr671:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st463;
st463:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof463;
case 463:
#line 10920 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr672;
	}
	goto tr518;
tr672:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st464;
st464:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof464;
case 464:
#line 10937 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 99: goto tr673;
	}
	goto tr518;
tr673:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st465;
st465:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof465;
case 465:
#line 10954 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 107: goto tr674;
	}
	goto tr518;
tr674:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st466;
st466:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof466;
case 466:
#line 10971 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr675;
		case 32: goto tr675;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr675;
	goto tr518;
tr675:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st467;
st467:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof467;
case 467:
#line 10991 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr675;
		case 32: goto tr675;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr676;
	} else if ( (*( state.p)) >= 9 )
		goto tr675;
	goto tr518;
tr679:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st468;
tr676:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st468;
st468:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof468;
case 468:
#line 11024 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr677;
		case 32: goto tr677;
		case 34: goto st376;
		case 46: goto tr678;
		case 59: goto tr680;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr679;
	} else if ( (*( state.p)) >= 9 )
		goto tr677;
	goto tr518;
tr678:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st469;
st469:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof469;
case 469:
#line 11049 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr681;
	goto tr518;
tr681:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st470;
st470:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof470;
case 470:
#line 11067 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr677;
		case 32: goto tr677;
		case 34: goto st376;
		case 59: goto tr680;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr681;
	} else if ( (*( state.p)) >= 9 )
		goto tr677;
	goto tr518;
tr640:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st471;
st471:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof471;
case 471:
#line 11091 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 108: goto tr682;
		case 111: goto tr683;
	}
	goto tr518;
tr682:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st472;
st472:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof472;
case 472:
#line 11109 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 117: goto tr684;
	}
	goto tr518;
tr684:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st473;
st473:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof473;
case 473:
#line 11126 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 109: goto tr685;
	}
	goto tr518;
tr685:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st474;
st474:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof474;
case 474:
#line 11143 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 112: goto tr686;
	}
	goto tr518;
tr686:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st475;
st475:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof475;
case 475:
#line 11160 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 115: goto tr687;
	}
	goto tr518;
tr687:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st476;
st476:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof476;
case 476:
#line 11177 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 105: goto tr688;
	}
	goto tr518;
tr688:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st477;
st477:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof477;
case 477:
#line 11194 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 122: goto tr689;
	}
	goto tr518;
tr689:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st478;
st478:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof478;
case 478:
#line 11211 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr690;
	}
	goto tr518;
tr690:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st479;
st479:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof479;
case 479:
#line 11228 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr691;
		case 32: goto tr691;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr691;
	goto tr518;
tr691:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st480;
st480:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof480;
case 480:
#line 11248 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr691;
		case 32: goto tr691;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr692;
	} else if ( (*( state.p)) >= 9 )
		goto tr691;
	goto tr518;
tr695:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st481;
tr692:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st481;
st481:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof481;
case 481:
#line 11281 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr693;
		case 32: goto tr693;
		case 34: goto st376;
		case 46: goto tr694;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr695;
	} else if ( (*( state.p)) >= 9 )
		goto tr693;
	goto tr518;
tr696:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st482;
tr693:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 174 "configparser.rl"
	{ spe.clumpsize.mean = ::atof(state.match.c_str()); }
	goto st482;
st482:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof482;
case 482:
#line 11313 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr696;
		case 32: goto tr696;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr697;
	} else if ( (*( state.p)) >= 9 )
		goto tr696;
	goto tr518;
tr700:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st483;
tr697:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st483;
st483:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof483;
case 483:
#line 11346 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr698;
		case 32: goto tr698;
		case 34: goto st376;
		case 46: goto tr699;
		case 59: goto tr701;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr700;
	} else if ( (*( state.p)) >= 9 )
		goto tr698;
	goto tr518;
tr699:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st484;
st484:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof484;
case 484:
#line 11371 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr702;
	goto tr518;
tr702:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st485;
st485:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof485;
case 485:
#line 11389 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr698;
		case 32: goto tr698;
		case 34: goto st376;
		case 59: goto tr701;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr702;
	} else if ( (*( state.p)) >= 9 )
		goto tr698;
	goto tr518;
tr694:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st486;
st486:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof486;
case 486:
#line 11413 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr703;
	goto tr518;
tr703:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st487;
st487:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof487;
case 487:
#line 11431 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr693;
		case 32: goto tr693;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr703;
	} else if ( (*( state.p)) >= 9 )
		goto tr693;
	goto tr518;
tr683:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st488;
st488:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof488;
case 488:
#line 11454 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 109: goto tr704;
		case 117: goto tr705;
	}
	goto tr518;
tr704:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st489;
st489:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof489;
case 489:
#line 11472 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 112: goto tr706;
	}
	goto tr518;
tr706:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st490;
st490:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof490;
case 490:
#line 11489 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr707;
	}
	goto tr518;
tr707:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st491;
st491:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof491;
case 491:
#line 11506 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr708;
	}
	goto tr518;
tr708:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st492;
st492:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof492;
case 492:
#line 11523 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 105: goto tr709;
	}
	goto tr518;
tr709:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st493;
st493:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof493;
case 493:
#line 11540 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 111: goto tr710;
	}
	goto tr518;
tr710:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st494;
st494:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof494;
case 494:
#line 11557 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr711;
	}
	goto tr518;
tr711:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st495;
st495:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof495;
case 495:
#line 11574 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr712;
		case 32: goto tr712;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr712;
	goto tr518;
tr713:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st496;
tr712:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 178 "configparser.rl"
	{ spe.companion.push_back(Species::companion_t()); }
	goto st496;
st496:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof496;
case 496:
#line 11602 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr713;
		case 32: goto tr713;
		case 34: goto st497;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr713;
	goto tr518;
st497:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof497;
case 497:
	switch( (*( state.p)) ) {
		case 13: goto tr715;
		case 32: goto tr715;
		case 34: goto tr77;
		case 92: goto tr78;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr715;
	goto tr76;
tr716:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st498;
tr715:
#line 140 "configparser.rl"
	{ spe.skin.text = state.match; }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st498;
st498:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof498;
case 498:
#line 11647 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr716;
		case 32: goto tr716;
		case 34: goto st51;
		case 92: goto tr81;
		case 98: goto tr717;
		case 100: goto tr718;
		case 110: goto tr719;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr716;
	goto tr79;
tr717:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st499;
st499:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof499;
case 499:
#line 11670 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 114: goto tr720;
	}
	goto tr79;
tr720:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st500;
st500:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof500;
case 500:
#line 11687 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 105: goto tr721;
	}
	goto tr79;
tr721:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st501;
st501:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof501;
case 501:
#line 11704 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 103: goto tr722;
	}
	goto tr79;
tr722:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st502;
st502:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof502;
case 502:
#line 11721 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 104: goto tr723;
	}
	goto tr79;
tr723:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st503;
st503:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof503;
case 503:
#line 11738 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 116: goto tr724;
	}
	goto tr79;
tr724:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st504;
st504:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof504;
case 504:
#line 11755 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr725;
		case 32: goto tr725;
		case 34: goto st51;
		case 92: goto tr81;
		case 95: goto tr726;
		case 98: goto tr727;
		case 99: goto tr728;
		case 103: goto tr729;
		case 109: goto tr730;
		case 114: goto tr731;
		case 119: goto tr732;
		case 121: goto tr733;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr725;
	goto tr79;
tr734:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st505;
tr725:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st505;
tr787:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st505;
st505:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof505;
case 505:
#line 11799 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr734;
		case 32: goto tr734;
		case 34: goto st51;
		case 92: goto tr81;
		case 98: goto tr735;
		case 99: goto tr736;
		case 103: goto tr737;
		case 109: goto tr738;
		case 114: goto tr739;
		case 119: goto tr740;
		case 121: goto tr741;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr734;
	goto tr79;
tr735:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st506;
tr727:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st506;
tr789:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st506;
st506:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof506;
case 506:
#line 11842 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 108: goto tr742;
	}
	goto tr79;
tr742:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st507;
st507:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof507;
case 507:
#line 11859 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr743;
		case 117: goto tr744;
	}
	goto tr79;
tr743:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st508;
st508:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof508;
case 508:
#line 11877 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 99: goto tr745;
	}
	goto tr79;
tr745:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st509;
st509:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof509;
case 509:
#line 11894 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 107: goto tr98;
	}
	goto tr79;
tr744:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st510;
st510:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof510;
case 510:
#line 11911 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr746;
	}
	goto tr79;
tr746:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st511;
st511:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof511;
case 511:
#line 11928 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr747;
		case 32: goto tr747;
		case 34: goto st51;
		case 59: goto tr748;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr747;
	goto tr79;
tr736:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st512;
tr728:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st512;
tr790:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st512;
st512:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof512;
case 512:
#line 11965 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 121: goto tr749;
	}
	goto tr79;
tr749:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st513;
st513:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof513;
case 513:
#line 11982 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr750;
	}
	goto tr79;
tr750:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st514;
st514:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof514;
case 514:
#line 11999 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr751;
	}
	goto tr79;
tr751:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st515;
st515:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof515;
case 515:
#line 12016 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr752;
		case 32: goto tr752;
		case 34: goto st51;
		case 59: goto tr753;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr752;
	goto tr79;
tr737:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st516;
tr729:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st516;
tr791:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st516;
st516:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof516;
case 516:
#line 12053 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 114: goto tr754;
	}
	goto tr79;
tr754:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st517;
st517:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof517;
case 517:
#line 12070 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr755;
	}
	goto tr79;
tr755:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st518;
st518:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof518;
case 518:
#line 12087 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr756;
	}
	goto tr79;
tr756:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st519;
st519:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof519;
case 519:
#line 12104 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr757;
	}
	goto tr79;
tr757:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st520;
st520:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof520;
case 520:
#line 12121 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr758;
		case 32: goto tr758;
		case 34: goto st51;
		case 59: goto tr759;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr758;
	goto tr79;
tr738:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st521;
tr730:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st521;
tr792:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st521;
st521:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof521;
case 521:
#line 12158 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr760;
	}
	goto tr79;
tr760:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st522;
st522:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof522;
case 522:
#line 12175 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 103: goto tr761;
	}
	goto tr79;
tr761:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st523;
st523:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof523;
case 523:
#line 12192 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr762;
	}
	goto tr79;
tr762:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st524;
st524:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof524;
case 524:
#line 12209 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr763;
	}
	goto tr79;
tr763:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st525;
st525:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof525;
case 525:
#line 12226 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 116: goto tr764;
	}
	goto tr79;
tr764:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st526;
st526:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof526;
case 526:
#line 12243 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr765;
	}
	goto tr79;
tr765:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st527;
st527:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof527;
case 527:
#line 12260 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr766;
		case 32: goto tr766;
		case 34: goto st51;
		case 59: goto tr767;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr766;
	goto tr79;
tr739:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st528;
tr731:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st528;
tr793:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st528;
st528:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof528;
case 528:
#line 12297 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr768;
	}
	goto tr79;
tr768:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st529;
st529:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof529;
case 529:
#line 12314 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 100: goto tr769;
	}
	goto tr79;
tr769:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st530;
st530:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof530;
case 530:
#line 12331 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr770;
		case 32: goto tr770;
		case 34: goto st51;
		case 59: goto tr771;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr770;
	goto tr79;
tr740:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st531;
tr732:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st531;
tr794:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st531;
st531:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof531;
case 531:
#line 12368 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 104: goto tr772;
	}
	goto tr79;
tr772:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st532;
st532:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof532;
case 532:
#line 12385 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 105: goto tr773;
	}
	goto tr79;
tr773:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st533;
st533:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof533;
case 533:
#line 12402 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 116: goto tr774;
	}
	goto tr79;
tr774:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st534;
st534:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof534;
case 534:
#line 12419 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr775;
	}
	goto tr79;
tr775:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st535;
st535:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof535;
case 535:
#line 12436 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr776;
		case 32: goto tr776;
		case 34: goto st51;
		case 59: goto tr777;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr776;
	goto tr79;
tr741:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st536;
tr733:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st536;
tr795:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st536;
st536:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof536;
case 536:
#line 12473 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr778;
	}
	goto tr79;
tr778:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st537;
st537:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof537;
case 537:
#line 12490 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 108: goto tr779;
	}
	goto tr79;
tr779:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st538;
st538:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof538;
case 538:
#line 12507 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 108: goto tr780;
	}
	goto tr79;
tr780:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st539;
st539:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof539;
case 539:
#line 12524 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 111: goto tr781;
	}
	goto tr79;
tr781:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st540;
st540:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof540;
case 540:
#line 12541 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 119: goto tr782;
	}
	goto tr79;
tr782:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st541;
st541:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof541;
case 541:
#line 12558 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr783;
		case 32: goto tr783;
		case 34: goto st51;
		case 59: goto tr784;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr783;
	goto tr79;
tr726:
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st542;
tr788:
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st542;
st542:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof542;
case 542:
#line 12589 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 98: goto tr735;
		case 99: goto tr736;
		case 103: goto tr737;
		case 109: goto tr738;
		case 114: goto tr739;
		case 119: goto tr740;
		case 121: goto tr741;
	}
	goto tr79;
tr718:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st543;
st543:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof543;
case 543:
#line 12612 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 105: goto tr785;
	}
	goto tr79;
tr785:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st544;
st544:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof544;
case 544:
#line 12629 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 109: goto tr786;
	}
	goto tr79;
tr786:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st545;
st545:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof545;
case 545:
#line 12646 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr787;
		case 32: goto tr787;
		case 34: goto st51;
		case 92: goto tr81;
		case 95: goto tr788;
		case 98: goto tr789;
		case 99: goto tr790;
		case 103: goto tr791;
		case 109: goto tr792;
		case 114: goto tr793;
		case 119: goto tr794;
		case 121: goto tr795;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr787;
	goto tr79;
tr719:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st546;
st546:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof546;
case 546:
#line 12674 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 111: goto tr796;
	}
	goto tr79;
tr796:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st547;
st547:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof547;
case 547:
#line 12691 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr797;
	}
	goto tr79;
tr797:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st548;
st548:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof548;
case 548:
#line 12708 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr98;
	}
	goto tr79;
tr705:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st549;
st549:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof549;
case 549:
#line 12725 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr798;
	}
	goto tr518;
tr798:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st550;
st550:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof550;
case 550:
#line 12742 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 116: goto tr799;
	}
	goto tr518;
tr799:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st551;
st551:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof551;
case 551:
#line 12759 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr800;
		case 32: goto tr800;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr800;
	goto tr518;
tr800:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st552;
st552:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof552;
case 552:
#line 12779 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr800;
		case 32: goto tr800;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr801;
	} else if ( (*( state.p)) >= 9 )
		goto tr800;
	goto tr518;
tr801:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st553;
tr803:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st553;
st553:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof553;
case 553:
#line 12812 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr802;
		case 32: goto tr802;
		case 34: goto st376;
		case 59: goto tr804;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr803;
	} else if ( (*( state.p)) >= 9 )
		goto tr802;
	goto tr518;
tr641:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st554;
st554:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof554;
case 554:
#line 12836 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr805;
	}
	goto tr518;
tr805:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st555;
st555:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof555;
case 555:
#line 12853 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 102: goto tr806;
	}
	goto tr518;
tr806:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st556;
st556:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof556;
case 556:
#line 12870 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr807;
	}
	goto tr518;
tr807:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st557;
st557:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof557;
case 557:
#line 12887 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr808;
	}
	goto tr518;
tr808:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st558;
st558:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof558;
case 558:
#line 12904 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 115: goto tr809;
	}
	goto tr518;
tr809:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st559;
st559:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof559;
case 559:
#line 12921 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr810;
	}
	goto tr518;
tr810:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st560;
st560:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof560;
case 560:
#line 12938 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr811;
		case 32: goto tr811;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr811;
	goto tr518;
tr811:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st561;
st561:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof561;
case 561:
#line 12958 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr811;
		case 32: goto tr811;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr812;
	} else if ( (*( state.p)) >= 9 )
		goto tr811;
	goto tr518;
tr815:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st562;
tr812:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st562;
st562:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof562;
case 562:
#line 12991 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr813;
		case 32: goto tr813;
		case 34: goto st376;
		case 46: goto tr814;
		case 59: goto tr816;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr815;
	} else if ( (*( state.p)) >= 9 )
		goto tr813;
	goto tr518;
tr814:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st563;
st563:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof563;
case 563:
#line 13016 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr817;
	goto tr518;
tr817:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st564;
st564:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof564;
case 564:
#line 13034 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr813;
		case 32: goto tr813;
		case 34: goto st376;
		case 59: goto tr816;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr817;
	} else if ( (*( state.p)) >= 9 )
		goto tr813;
	goto tr518;
tr642:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st565;
st565:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof565;
case 565:
#line 13058 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr818;
	}
	goto tr518;
tr818:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st566;
st566:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof566;
case 566:
#line 13075 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 98: goto tr819;
	}
	goto tr518;
tr819:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st567;
st567:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof567;
case 567:
#line 13092 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 105: goto tr820;
	}
	goto tr518;
tr820:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st568;
st568:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof568;
case 568:
#line 13109 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 116: goto tr821;
	}
	goto tr518;
tr821:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st569;
st569:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof569;
case 569:
#line 13126 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr822;
	}
	goto tr518;
tr822:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st570;
st570:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof570;
case 570:
#line 13143 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 116: goto tr823;
	}
	goto tr518;
tr823:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st571;
st571:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof571;
case 571:
#line 13160 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr824;
		case 32: goto tr824;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr824;
	goto tr518;
tr824:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st572;
st572:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof572;
case 572:
#line 13180 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr824;
		case 32: goto tr824;
		case 34: goto st376;
		case 92: goto tr520;
		case 99: goto tr825;
		case 102: goto tr826;
		case 115: goto tr827;
		case 119: goto tr828;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr824;
	goto tr518;
tr825:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st573;
st573:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof573;
case 573:
#line 13204 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 111: goto tr829;
	}
	goto tr518;
tr829:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st574;
st574:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof574;
case 574:
#line 13221 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 114: goto tr830;
	}
	goto tr518;
tr830:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st575;
st575:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof575;
case 575:
#line 13238 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr831;
	}
	goto tr518;
tr831:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st576;
st576:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof576;
case 576:
#line 13255 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr832;
	}
	goto tr518;
tr832:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st577;
st577:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof577;
case 577:
#line 13272 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 114: goto tr833;
	}
	goto tr518;
tr833:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st578;
st578:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof578;
case 578:
#line 13289 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr834;
		case 32: goto tr834;
		case 34: goto st376;
		case 59: goto tr835;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr834;
	goto tr518;
tr826:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st579;
st579:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof579;
case 579:
#line 13310 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 108: goto tr836;
	}
	goto tr518;
tr836:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st580;
st580:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof580;
case 580:
#line 13327 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 111: goto tr837;
	}
	goto tr518;
tr837:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st581;
st581:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof581;
case 581:
#line 13344 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 111: goto tr838;
	}
	goto tr518;
tr838:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st582;
st582:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof582;
case 582:
#line 13361 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 114: goto tr839;
	}
	goto tr518;
tr839:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st583;
st583:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof583;
case 583:
#line 13378 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr840;
		case 32: goto tr840;
		case 34: goto st376;
		case 59: goto tr841;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr840;
	goto tr518;
tr827:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st584;
st584:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof584;
case 584:
#line 13399 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 104: goto tr842;
	}
	goto tr518;
tr842:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st585;
st585:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof585;
case 585:
#line 13416 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 111: goto tr843;
	}
	goto tr518;
tr843:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st586;
st586:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof586;
case 586:
#line 13433 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 114: goto tr844;
	}
	goto tr518;
tr844:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st587;
st587:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof587;
case 587:
#line 13450 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr845;
	}
	goto tr518;
tr845:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st588;
st588:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof588;
case 588:
#line 13467 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 108: goto tr846;
	}
	goto tr518;
tr846:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st589;
st589:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof589;
case 589:
#line 13484 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 105: goto tr847;
	}
	goto tr518;
tr847:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st590;
st590:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof590;
case 590:
#line 13501 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr848;
	}
	goto tr518;
tr848:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st591;
st591:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof591;
case 591:
#line 13518 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr849;
	}
	goto tr518;
tr849:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st592;
st592:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof592;
case 592:
#line 13535 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr850;
		case 32: goto tr850;
		case 34: goto st376;
		case 59: goto tr851;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr850;
	goto tr518;
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
#line 13556 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr852;
	}
	goto tr518;
tr852:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st594;
st594:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof594;
case 594:
#line 13573 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 108: goto tr853;
		case 116: goto tr854;
	}
	goto tr518;
tr853:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st595;
st595:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof595;
case 595:
#line 13591 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 107: goto tr855;
	}
	goto tr518;
tr855:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st596;
st596:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof596;
case 596:
#line 13608 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr856;
		case 32: goto tr856;
		case 34: goto st376;
		case 59: goto tr857;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr856;
	goto tr518;
tr854:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st597;
st597:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof597;
case 597:
#line 13629 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr858;
	}
	goto tr518;
tr858:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st598;
st598:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof598;
case 598:
#line 13646 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 114: goto tr859;
	}
	goto tr518;
tr859:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st599;
st599:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof599;
case 599:
#line 13663 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr860;
		case 32: goto tr860;
		case 34: goto st376;
		case 59: goto tr861;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr860;
	goto tr518;
tr643:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st600;
st600:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof600;
case 600:
#line 13684 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 100: goto tr862;
	}
	goto tr518;
tr862:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st601;
st601:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof601;
case 601:
#line 13701 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 108: goto tr863;
	}
	goto tr518;
tr863:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st602;
st602:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof602;
case 602:
#line 13718 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr864;
	}
	goto tr518;
tr864:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st603;
st603:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof603;
case 603:
#line 13735 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 95: goto tr865;
	}
	goto tr518;
tr865:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st604;
st604:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof604;
case 604:
#line 13752 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr866;
	}
	goto tr518;
tr866:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st605;
st605:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof605;
case 605:
#line 13769 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 105: goto tr867;
	}
	goto tr518;
tr867:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st606;
st606:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof606;
case 606:
#line 13786 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr868;
		case 32: goto tr868;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr868;
	goto tr518;
tr868:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st607;
st607:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof607;
case 607:
#line 13806 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr868;
		case 32: goto tr868;
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr869;
		case 114: goto tr870;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr868;
	goto tr518;
tr869:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st608;
st608:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof608;
case 608:
#line 13828 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 111: goto tr871;
	}
	goto tr518;
tr871:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st609;
st609:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof609;
case 609:
#line 13845 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr872;
	}
	goto tr518;
tr872:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st610;
st610:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof610;
case 610:
#line 13862 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr873;
	}
	goto tr518;
tr873:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st611;
st611:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof611;
case 611:
#line 13879 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr874;
		case 32: goto tr874;
		case 34: goto st376;
		case 59: goto tr875;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr874;
	goto tr518;
tr870:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st612;
st612:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof612;
case 612:
#line 13900 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr876;
	}
	goto tr518;
tr876:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st613;
st613:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof613;
case 613:
#line 13917 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr877;
	}
	goto tr518;
tr877:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st614;
st614:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof614;
case 614:
#line 13934 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 100: goto tr878;
	}
	goto tr518;
tr878:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st615;
st615:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof615;
case 615:
#line 13951 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 111: goto tr879;
	}
	goto tr518;
tr879:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st616;
st616:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof616;
case 616:
#line 13968 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 109: goto tr880;
	}
	goto tr518;
tr880:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st617;
st617:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof617;
case 617:
#line 13985 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr881;
		case 32: goto tr881;
		case 34: goto st376;
		case 59: goto tr882;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr881;
	goto tr518;
tr644:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st618;
st618:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof618;
case 618:
#line 14006 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 111: goto tr883;
	}
	goto tr518;
tr883:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st619;
st619:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof619;
case 619:
#line 14023 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 118: goto tr884;
	}
	goto tr518;
tr884:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st620;
st620:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof620;
case 620:
#line 14040 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr885;
	}
	goto tr518;
tr885:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st621;
st621:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof621;
case 621:
#line 14057 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr886;
		case 32: goto tr886;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr886;
	goto tr518;
tr886:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st622;
st622:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof622;
case 622:
#line 14077 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr886;
		case 32: goto tr886;
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr887;
		case 102: goto tr888;
		case 119: goto tr889;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr886;
	goto tr518;
tr887:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st623;
st623:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof623;
case 623:
#line 14100 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr890;
	}
	goto tr518;
tr890:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st624;
st624:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof624;
case 624:
#line 14117 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 121: goto tr891;
	}
	goto tr518;
tr891:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st625;
st625:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof625;
case 625:
#line 14134 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr892;
		case 32: goto tr892;
		case 34: goto st376;
		case 59: goto tr893;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr892;
	goto tr518;
tr888:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st626;
st626:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof626;
case 626:
#line 14155 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 108: goto tr894;
	}
	goto tr518;
tr894:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st627;
st627:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof627;
case 627:
#line 14172 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 111: goto tr895;
	}
	goto tr518;
tr895:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st628;
st628:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof628;
case 628:
#line 14189 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 111: goto tr896;
	}
	goto tr518;
tr896:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st629;
st629:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof629;
case 629:
#line 14206 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 114: goto tr897;
	}
	goto tr518;
tr897:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st630;
st630:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof630;
case 630:
#line 14223 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr898;
		case 32: goto tr898;
		case 34: goto st376;
		case 59: goto tr899;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr898;
	goto tr518;
tr889:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st631;
st631:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof631;
case 631:
#line 14244 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr900;
	}
	goto tr518;
tr900:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st632;
st632:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof632;
case 632:
#line 14261 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 116: goto tr901;
	}
	goto tr518;
tr901:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st633;
st633:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof633;
case 633:
#line 14278 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr902;
	}
	goto tr518;
tr902:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st634;
st634:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof634;
case 634:
#line 14295 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 114: goto tr903;
	}
	goto tr518;
tr903:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st635;
st635:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof635;
case 635:
#line 14312 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr904;
		case 32: goto tr904;
		case 34: goto st376;
		case 59: goto tr905;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr904;
	goto tr518;
tr645:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st636;
st636:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof636;
case 636:
#line 14333 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr906;
	}
	goto tr518;
tr906:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st637;
st637:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof637;
case 637:
#line 14350 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 109: goto tr907;
	}
	goto tr518;
tr907:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st638;
st638:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof638;
case 638:
#line 14367 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr908;
	}
	goto tr518;
tr908:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st639;
st639:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof639;
case 639:
#line 14384 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr909;
		case 32: goto tr909;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr909;
	goto tr518;
tr909:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st640;
st640:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof640;
case 640:
#line 14404 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr909;
		case 32: goto tr909;
		case 34: goto st641;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr909;
	goto tr518;
st641:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof641;
case 641:
	switch( (*( state.p)) ) {
		case 13: goto tr911;
		case 32: goto tr911;
		case 34: goto tr293;
		case 92: goto tr294;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr911;
	goto tr291;
tr912:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st642;
tr911:
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
	goto st642;
st642:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof642;
case 642:
#line 14449 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr912;
		case 32: goto tr912;
		case 34: goto st210;
		case 92: goto tr297;
		case 98: goto tr913;
		case 100: goto tr914;
		case 110: goto tr915;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr912;
	goto tr295;
tr913:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st643;
st643:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof643;
case 643:
#line 14472 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 114: goto tr916;
	}
	goto tr295;
tr916:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st644;
st644:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof644;
case 644:
#line 14489 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 105: goto tr917;
	}
	goto tr295;
tr917:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st645;
st645:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof645;
case 645:
#line 14506 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 103: goto tr918;
	}
	goto tr295;
tr918:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st646;
st646:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof646;
case 646:
#line 14523 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 104: goto tr919;
	}
	goto tr295;
tr919:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st647;
st647:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof647;
case 647:
#line 14540 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 116: goto tr920;
	}
	goto tr295;
tr920:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st648;
st648:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof648;
case 648:
#line 14557 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr921;
		case 32: goto tr921;
		case 34: goto st210;
		case 92: goto tr297;
		case 95: goto tr922;
		case 98: goto tr923;
		case 99: goto tr924;
		case 103: goto tr925;
		case 109: goto tr926;
		case 114: goto tr927;
		case 119: goto tr928;
		case 121: goto tr929;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr921;
	goto tr295;
tr930:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st649;
tr921:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st649;
tr983:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st649;
st649:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof649;
case 649:
#line 14601 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr930;
		case 32: goto tr930;
		case 34: goto st210;
		case 92: goto tr297;
		case 98: goto tr931;
		case 99: goto tr932;
		case 103: goto tr933;
		case 109: goto tr934;
		case 114: goto tr935;
		case 119: goto tr936;
		case 121: goto tr937;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr930;
	goto tr295;
tr931:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st650;
tr923:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st650;
tr985:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st650;
st650:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof650;
case 650:
#line 14644 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 108: goto tr938;
	}
	goto tr295;
tr938:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st651;
st651:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof651;
case 651:
#line 14661 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr939;
		case 117: goto tr940;
	}
	goto tr295;
tr939:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st652;
st652:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof652;
case 652:
#line 14679 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 99: goto tr941;
	}
	goto tr295;
tr941:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st653;
st653:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof653;
case 653:
#line 14696 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 107: goto tr303;
	}
	goto tr295;
tr940:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st654;
st654:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof654;
case 654:
#line 14713 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr942;
	}
	goto tr295;
tr942:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st655;
st655:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof655;
case 655:
#line 14730 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr943;
		case 32: goto tr943;
		case 34: goto st210;
		case 59: goto tr944;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr943;
	goto tr295;
tr932:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st656;
tr924:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st656;
tr986:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st656;
st656:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof656;
case 656:
#line 14767 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 121: goto tr945;
	}
	goto tr295;
tr945:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st657;
st657:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof657;
case 657:
#line 14784 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr946;
	}
	goto tr295;
tr946:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st658;
st658:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof658;
case 658:
#line 14801 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr947;
	}
	goto tr295;
tr947:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st659;
st659:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof659;
case 659:
#line 14818 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr948;
		case 32: goto tr948;
		case 34: goto st210;
		case 59: goto tr949;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr948;
	goto tr295;
tr933:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st660;
tr925:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st660;
tr987:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st660;
st660:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof660;
case 660:
#line 14855 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 114: goto tr950;
	}
	goto tr295;
tr950:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st661;
st661:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof661;
case 661:
#line 14872 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr951;
	}
	goto tr295;
tr951:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st662;
st662:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof662;
case 662:
#line 14889 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr952;
	}
	goto tr295;
tr952:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st663;
st663:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof663;
case 663:
#line 14906 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr953;
	}
	goto tr295;
tr953:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st664;
st664:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof664;
case 664:
#line 14923 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr954;
		case 32: goto tr954;
		case 34: goto st210;
		case 59: goto tr955;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr954;
	goto tr295;
tr934:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st665;
tr926:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st665;
tr988:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st665;
st665:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof665;
case 665:
#line 14960 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr956;
	}
	goto tr295;
tr956:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st666;
st666:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof666;
case 666:
#line 14977 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 103: goto tr957;
	}
	goto tr295;
tr957:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st667;
st667:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof667;
case 667:
#line 14994 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr958;
	}
	goto tr295;
tr958:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st668;
st668:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof668;
case 668:
#line 15011 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr959;
	}
	goto tr295;
tr959:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st669;
st669:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof669;
case 669:
#line 15028 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 116: goto tr960;
	}
	goto tr295;
tr960:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st670;
st670:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof670;
case 670:
#line 15045 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 97: goto tr961;
	}
	goto tr295;
tr961:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st671;
st671:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof671;
case 671:
#line 15062 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr962;
		case 32: goto tr962;
		case 34: goto st210;
		case 59: goto tr963;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr962;
	goto tr295;
tr935:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st672;
tr927:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st672;
tr989:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st672;
st672:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof672;
case 672:
#line 15099 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr964;
	}
	goto tr295;
tr964:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st673;
st673:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof673;
case 673:
#line 15116 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 100: goto tr965;
	}
	goto tr295;
tr965:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st674;
st674:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof674;
case 674:
#line 15133 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr966;
		case 32: goto tr966;
		case 34: goto st210;
		case 59: goto tr967;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr966;
	goto tr295;
tr936:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st675;
tr928:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st675;
tr990:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st675;
st675:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof675;
case 675:
#line 15170 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 104: goto tr968;
	}
	goto tr295;
tr968:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st676;
st676:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof676;
case 676:
#line 15187 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 105: goto tr969;
	}
	goto tr295;
tr969:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st677;
st677:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof677;
case 677:
#line 15204 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 116: goto tr970;
	}
	goto tr295;
tr970:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st678;
st678:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof678;
case 678:
#line 15221 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr971;
	}
	goto tr295;
tr971:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st679;
st679:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof679;
case 679:
#line 15238 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr972;
		case 32: goto tr972;
		case 34: goto st210;
		case 59: goto tr973;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr972;
	goto tr295;
tr937:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st680;
tr929:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st680;
tr991:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st680;
st680:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof680;
case 680:
#line 15275 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr974;
	}
	goto tr295;
tr974:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st681;
st681:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof681;
case 681:
#line 15292 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 108: goto tr975;
	}
	goto tr295;
tr975:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st682;
st682:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof682;
case 682:
#line 15309 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 108: goto tr976;
	}
	goto tr295;
tr976:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st683;
st683:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof683;
case 683:
#line 15326 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 111: goto tr977;
	}
	goto tr295;
tr977:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st684;
st684:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof684;
case 684:
#line 15343 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 119: goto tr978;
	}
	goto tr295;
tr978:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st685;
st685:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof685;
case 685:
#line 15360 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr979;
		case 32: goto tr979;
		case 34: goto st210;
		case 59: goto tr980;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr979;
	goto tr295;
tr922:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st686;
tr984:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st686;
st686:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof686;
case 686:
#line 15391 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 98: goto tr931;
		case 99: goto tr932;
		case 103: goto tr933;
		case 109: goto tr934;
		case 114: goto tr935;
		case 119: goto tr936;
		case 121: goto tr937;
	}
	goto tr295;
tr914:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st687;
st687:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof687;
case 687:
#line 15414 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 105: goto tr981;
	}
	goto tr295;
tr981:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st688;
st688:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof688;
case 688:
#line 15431 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 109: goto tr982;
	}
	goto tr295;
tr982:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st689;
st689:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof689;
case 689:
#line 15448 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr983;
		case 32: goto tr983;
		case 34: goto st210;
		case 92: goto tr297;
		case 95: goto tr984;
		case 98: goto tr985;
		case 99: goto tr986;
		case 103: goto tr987;
		case 109: goto tr988;
		case 114: goto tr989;
		case 119: goto tr990;
		case 121: goto tr991;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr983;
	goto tr295;
tr915:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st690;
st690:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof690;
case 690:
#line 15476 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 111: goto tr992;
	}
	goto tr295;
tr992:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st691;
st691:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof691;
case 691:
#line 15493 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 110: goto tr993;
	}
	goto tr295;
tr993:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st692;
st692:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof692;
case 692:
#line 15510 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
		case 101: goto tr303;
	}
	goto tr295;
tr646:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st693;
st693:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof693;
case 693:
#line 15527 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr994;
	}
	goto tr518;
tr994:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st694;
st694:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof694;
case 694:
#line 15544 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr995;
	}
	goto tr518;
tr995:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st695;
st695:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof695;
case 695:
#line 15561 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 103: goto tr996;
	}
	goto tr518;
tr996:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st696;
st696:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof696;
case 696:
#line 15578 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr997;
	}
	goto tr518;
tr997:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st697;
st697:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof697;
case 697:
#line 15595 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr998;
		case 32: goto tr998;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr998;
	goto tr518;
tr998:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st698;
st698:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof698;
case 698:
#line 15615 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr998;
		case 32: goto tr998;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr999;
	} else if ( (*( state.p)) >= 9 )
		goto tr998;
	goto tr518;
tr1001:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st699;
tr999:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st699;
st699:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof699;
case 699:
#line 15648 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1000;
		case 32: goto tr1000;
		case 34: goto st376;
		case 59: goto tr1002;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1001;
	} else if ( (*( state.p)) >= 9 )
		goto tr1000;
	goto tr518;
tr647:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st700;
st700:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof700;
case 700:
#line 15672 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 107: goto tr1003;
	}
	goto tr518;
tr1003:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st701;
st701:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof701;
case 701:
#line 15689 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 105: goto tr1004;
	}
	goto tr518;
tr1004:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st702;
st702:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof702;
case 702:
#line 15706 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr1005;
	}
	goto tr518;
tr1005:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st703;
st703:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof703;
case 703:
#line 15723 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1006;
		case 32: goto tr1006;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1006;
	goto tr518;
tr1006:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st704;
st704:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof704;
case 704:
#line 15743 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1006;
		case 32: goto tr1006;
		case 34: goto st705;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1006;
	goto tr518;
st705:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof705;
case 705:
	switch( (*( state.p)) ) {
		case 13: goto tr1008;
		case 32: goto tr1008;
		case 34: goto tr515;
		case 92: goto tr517;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1008;
	goto tr513;
tr648:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st706;
st706:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof706;
case 706:
#line 15776 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1009;
		case 32: goto tr1009;
		case 34: goto st376;
		case 59: goto tr1010;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1009;
	goto tr518;
tr634:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st707;
st707:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof707;
case 707:
#line 15797 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr1011;
	}
	goto tr518;
tr1011:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st708;
st708:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof708;
case 708:
#line 15814 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1012;
		case 32: goto tr1012;
		case 34: goto st376;
		case 59: goto tr1013;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1012;
	goto tr518;
tr626:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st709;
tr618:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st709;
tr1055:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st709;
st709:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof709;
case 709:
#line 15851 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 121: goto tr1014;
	}
	goto tr518;
tr1014:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st710;
st710:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof710;
case 710:
#line 15868 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr1015;
	}
	goto tr518;
tr1015:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st711;
st711:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof711;
case 711:
#line 15885 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr1016;
	}
	goto tr518;
tr1016:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st712;
st712:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof712;
case 712:
#line 15902 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1017;
		case 32: goto tr1017;
		case 34: goto st376;
		case 59: goto tr1018;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1017;
	goto tr518;
tr627:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st713;
tr619:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st713;
tr1056:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st713;
st713:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof713;
case 713:
#line 15939 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 114: goto tr1019;
	}
	goto tr518;
tr1019:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st714;
st714:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof714;
case 714:
#line 15956 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr1020;
	}
	goto tr518;
tr1020:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st715;
st715:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof715;
case 715:
#line 15973 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr1021;
	}
	goto tr518;
tr1021:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st716;
st716:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof716;
case 716:
#line 15990 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr1022;
	}
	goto tr518;
tr1022:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st717;
st717:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof717;
case 717:
#line 16007 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1023;
		case 32: goto tr1023;
		case 34: goto st376;
		case 59: goto tr1024;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1023;
	goto tr518;
tr628:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st718;
tr620:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st718;
tr1057:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st718;
st718:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof718;
case 718:
#line 16044 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr1025;
	}
	goto tr518;
tr1025:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st719;
st719:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof719;
case 719:
#line 16061 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 103: goto tr1026;
	}
	goto tr518;
tr1026:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st720;
st720:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof720;
case 720:
#line 16078 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr1027;
	}
	goto tr518;
tr1027:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st721;
st721:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof721;
case 721:
#line 16095 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr1028;
	}
	goto tr518;
tr1028:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st722;
st722:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof722;
case 722:
#line 16112 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 116: goto tr1029;
	}
	goto tr518;
tr1029:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st723;
st723:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof723;
case 723:
#line 16129 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 97: goto tr1030;
	}
	goto tr518;
tr1030:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st724;
st724:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof724;
case 724:
#line 16146 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1031;
		case 32: goto tr1031;
		case 34: goto st376;
		case 59: goto tr1032;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1031;
	goto tr518;
tr629:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st725;
tr621:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st725;
tr1058:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st725;
st725:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof725;
case 725:
#line 16183 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr1033;
	}
	goto tr518;
tr1033:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st726;
st726:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof726;
case 726:
#line 16200 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 100: goto tr1034;
	}
	goto tr518;
tr1034:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st727;
st727:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof727;
case 727:
#line 16217 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1035;
		case 32: goto tr1035;
		case 34: goto st376;
		case 59: goto tr1036;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1035;
	goto tr518;
tr630:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st728;
tr622:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st728;
tr1059:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st728;
st728:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof728;
case 728:
#line 16254 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 104: goto tr1037;
	}
	goto tr518;
tr1037:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st729;
st729:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof729;
case 729:
#line 16271 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 105: goto tr1038;
	}
	goto tr518;
tr1038:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st730;
st730:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof730;
case 730:
#line 16288 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 116: goto tr1039;
	}
	goto tr518;
tr1039:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st731;
st731:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof731;
case 731:
#line 16305 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr1040;
	}
	goto tr518;
tr1040:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st732;
st732:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof732;
case 732:
#line 16322 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1041;
		case 32: goto tr1041;
		case 34: goto st376;
		case 59: goto tr1042;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1041;
	goto tr518;
tr631:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st733;
tr623:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st733;
tr1060:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st733;
st733:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof733;
case 733:
#line 16359 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr1043;
	}
	goto tr518;
tr1043:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st734;
st734:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof734;
case 734:
#line 16376 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 108: goto tr1044;
	}
	goto tr518;
tr1044:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st735;
st735:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof735;
case 735:
#line 16393 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 108: goto tr1045;
	}
	goto tr518;
tr1045:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st736;
st736:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof736;
case 736:
#line 16410 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 111: goto tr1046;
	}
	goto tr518;
tr1046:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st737;
st737:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof737;
case 737:
#line 16427 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 119: goto tr1047;
	}
	goto tr518;
tr1047:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st738;
st738:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof738;
case 738:
#line 16444 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1048;
		case 32: goto tr1048;
		case 34: goto st376;
		case 59: goto tr1049;
		case 92: goto tr520;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1048;
	goto tr518;
tr616:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 138 "configparser.rl"
	{ spe.skin.fore = maudit::color::bright_black; }
	goto st739;
tr1053:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 137 "configparser.rl"
	{ spe.skin.fore = maudit::color::dim_black; }
	goto st739;
st739:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof739;
case 739:
#line 16475 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 98: goto tr625;
		case 99: goto tr626;
		case 103: goto tr627;
		case 109: goto tr628;
		case 114: goto tr629;
		case 119: goto tr630;
		case 121: goto tr631;
	}
	goto tr518;
tr608:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st740;
st740:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof740;
case 740:
#line 16498 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 105: goto tr1050;
	}
	goto tr518;
tr1050:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st741;
st741:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof741;
case 741:
#line 16515 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 109: goto tr1051;
	}
	goto tr518;
tr1051:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st742;
st742:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof742;
case 742:
#line 16532 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1052;
		case 32: goto tr1052;
		case 34: goto st376;
		case 92: goto tr520;
		case 95: goto tr1053;
		case 98: goto tr1054;
		case 99: goto tr1055;
		case 103: goto tr1056;
		case 109: goto tr1057;
		case 114: goto tr1058;
		case 119: goto tr1059;
		case 121: goto tr1060;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1052;
	goto tr518;
tr609:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st743;
st743:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof743;
case 743:
#line 16560 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 111: goto tr1061;
	}
	goto tr518;
tr1061:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st744;
st744:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof744;
case 744:
#line 16577 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 110: goto tr1062;
	}
	goto tr518;
tr1062:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st745;
st745:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof745;
case 745:
#line 16594 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
		case 101: goto tr636;
	}
	goto tr518;
tr315:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st746;
st746:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof746;
case 746:
#line 16611 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1063;
		case 32: goto tr1063;
		case 34: goto st210;
		case 59: goto tr1064;
		case 92: goto tr297;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1063;
	goto tr295;
tr1065:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st747;
tr292:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 179 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st747;
st747:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof747;
case 747:
#line 16644 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1065;
		case 32: goto tr1065;
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1066;
	} else if ( (*( state.p)) >= 9 )
		goto tr1065;
	goto tr295;
tr1069:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st748;
tr1066:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st748;
st748:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof748;
case 748:
#line 16677 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1067;
		case 32: goto tr1067;
		case 34: goto st210;
		case 46: goto tr1068;
		case 59: goto tr1070;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1069;
	} else if ( (*( state.p)) >= 9 )
		goto tr1067;
	goto tr295;
tr1068:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st749;
st749:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof749;
case 749:
#line 16702 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st210;
		case 92: goto tr297;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1071;
	goto tr295;
tr1071:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st750;
st750:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof750;
case 750:
#line 16720 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1067;
		case 32: goto tr1067;
		case 34: goto st210;
		case 59: goto tr1070;
		case 92: goto tr297;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1071;
	} else if ( (*( state.p)) >= 9 )
		goto tr1067;
	goto tr295;
tr108:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st751;
st751:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof751;
case 751:
#line 16744 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 97: goto tr1072;
	}
	goto tr79;
tr1072:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st752;
st752:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof752;
case 752:
#line 16761 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr1073;
	}
	goto tr79;
tr1073:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st753;
st753:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof753;
case 753:
#line 16778 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 103: goto tr1074;
	}
	goto tr79;
tr1074:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st754;
st754:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof754;
case 754:
#line 16795 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 101: goto tr1075;
	}
	goto tr79;
tr1075:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st755;
st755:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof755;
case 755:
#line 16812 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1076;
		case 32: goto tr1076;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1076;
	goto tr79;
tr1076:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st756;
st756:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof756;
case 756:
#line 16832 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1076;
		case 32: goto tr1076;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1077;
	} else if ( (*( state.p)) >= 9 )
		goto tr1076;
	goto tr79;
tr1077:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st757;
tr1079:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st757;
st757:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof757;
case 757:
#line 16865 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1078;
		case 32: goto tr1078;
		case 34: goto st51;
		case 59: goto tr1080;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1079;
	} else if ( (*( state.p)) >= 9 )
		goto tr1078;
	goto tr79;
tr109:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st758;
st758:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof758;
case 758:
#line 16889 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 107: goto tr1081;
	}
	goto tr79;
tr1081:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st759;
st759:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof759;
case 759:
#line 16906 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 105: goto tr1082;
	}
	goto tr79;
tr1082:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st760;
st760:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof760;
case 760:
#line 16923 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
		case 110: goto tr1083;
	}
	goto tr79;
tr1083:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st761;
st761:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof761;
case 761:
#line 16940 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1084;
		case 32: goto tr1084;
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1084;
	goto tr79;
tr1084:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st762;
st762:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof762;
case 762:
#line 16960 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1084;
		case 32: goto tr1084;
		case 34: goto st763;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1084;
	goto tr79;
st763:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof763;
case 763:
	switch( (*( state.p)) ) {
		case 13: goto tr1086;
		case 32: goto tr1086;
		case 34: goto tr515;
		case 92: goto tr517;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1086;
	goto tr513;
tr1087:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st764;
tr1086:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 179 "configparser.rl"
	{ spe.companion.back().tag = state.match; }
	goto st764;
st764:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof764;
case 764:
#line 17005 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1087;
		case 32: goto tr1087;
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1088;
	} else if ( (*( state.p)) >= 9 )
		goto tr1087;
	goto tr518;
tr1091:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st765;
tr1088:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
	goto st765;
st765:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof765;
case 765:
#line 17038 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1089;
		case 32: goto tr1089;
		case 34: goto st376;
		case 46: goto tr1090;
		case 59: goto tr1092;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1091;
	} else if ( (*( state.p)) >= 9 )
		goto tr1089;
	goto tr518;
tr1090:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st766;
st766:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof766;
case 766:
#line 17063 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st376;
		case 92: goto tr520;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1093;
	goto tr518;
tr1093:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st767;
st767:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof767;
case 767:
#line 17081 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1089;
		case 32: goto tr1089;
		case 34: goto st376;
		case 59: goto tr1092;
		case 92: goto tr520;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1093;
	} else if ( (*( state.p)) >= 9 )
		goto tr1089;
	goto tr518;
tr110:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st768;
st768:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof768;
case 768:
#line 17105 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1094;
		case 32: goto tr1094;
		case 34: goto st51;
		case 59: goto tr1095;
		case 92: goto tr81;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1094;
	goto tr79;
tr95:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st769;
st769:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof769;
case 769:
#line 17126 "configparser.h"
	switch( (*( state.p)) ) {
		case 34: goto st51;
		case 92: goto tr81;
	}
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto tr1096;
	goto tr79;
tr1096:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st770;
st770:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof770;
case 770:
#line 17144 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr94;
		case 32: goto tr94;
		case 34: goto st51;
		case 59: goto tr97;
		case 92: goto tr81;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1096;
	} else if ( (*( state.p)) >= 9 )
		goto tr94;
	goto tr79;
st771:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof771;
case 771:
	if ( (*( state.p)) == 110 )
		goto st772;
	goto st0;
st772:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof772;
case 772:
	if ( (*( state.p)) == 116 )
		goto st773;
	goto st0;
st773:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof773;
case 773:
	switch( (*( state.p)) ) {
		case 13: goto st774;
		case 32: goto st774;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st774;
	goto st0;
st774:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof774;
case 774:
	switch( (*( state.p)) ) {
		case 13: goto st774;
		case 32: goto st774;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1100;
	} else if ( (*( state.p)) >= 9 )
		goto st774;
	goto st0;
tr1100:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st775;
tr1102:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st775;
st775:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof775;
case 775:
#line 17217 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1101;
		case 32: goto tr1101;
		case 59: goto tr1103;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1102;
	} else if ( (*( state.p)) >= 9 )
		goto tr1101;
	goto st0;
st776:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof776;
case 776:
	if ( (*( state.p)) == 101 )
		goto st777;
	goto st0;
st777:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof777;
case 777:
	if ( (*( state.p)) == 102 )
		goto st778;
	goto st0;
st778:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof778;
case 778:
	if ( (*( state.p)) == 101 )
		goto st779;
	goto st0;
st779:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof779;
case 779:
	if ( (*( state.p)) == 110 )
		goto st780;
	goto st0;
st780:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof780;
case 780:
	if ( (*( state.p)) == 115 )
		goto st781;
	goto st0;
st781:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof781;
case 781:
	if ( (*( state.p)) == 101 )
		goto st782;
	goto st0;
st782:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof782;
case 782:
	switch( (*( state.p)) ) {
		case 13: goto st783;
		case 32: goto st783;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st783;
	goto st0;
st783:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof783;
case 783:
	switch( (*( state.p)) ) {
		case 13: goto st783;
		case 32: goto st783;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1111;
	} else if ( (*( state.p)) >= 9 )
		goto st783;
	goto st0;
tr1111:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st784;
tr1114:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st784;
st784:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof784;
case 784:
#line 17316 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1112;
		case 32: goto tr1112;
		case 46: goto st785;
		case 59: goto tr1115;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1114;
	} else if ( (*( state.p)) >= 9 )
		goto tr1112;
	goto st0;
st785:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof785;
case 785:
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto st786;
	goto st0;
st786:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof786;
case 786:
	switch( (*( state.p)) ) {
		case 13: goto tr1112;
		case 32: goto tr1112;
		case 59: goto tr1115;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto st786;
	} else if ( (*( state.p)) >= 9 )
		goto tr1112;
	goto st0;
st787:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof787;
case 787:
	if ( (*( state.p)) == 97 )
		goto st788;
	goto st0;
st788:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof788;
case 788:
	if ( (*( state.p)) == 98 )
		goto st789;
	goto st0;
st789:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof789;
case 789:
	if ( (*( state.p)) == 105 )
		goto st790;
	goto st0;
st790:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof790;
case 790:
	if ( (*( state.p)) == 116 )
		goto st791;
	goto st0;
st791:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof791;
case 791:
	if ( (*( state.p)) == 97 )
		goto st792;
	goto st0;
st792:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof792;
case 792:
	if ( (*( state.p)) == 116 )
		goto st793;
	goto st0;
st793:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof793;
case 793:
	switch( (*( state.p)) ) {
		case 13: goto st794;
		case 32: goto st794;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st794;
	goto st0;
st794:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof794;
case 794:
	switch( (*( state.p)) ) {
		case 13: goto st794;
		case 32: goto st794;
		case 99: goto st795;
		case 102: goto st801;
		case 115: goto st806;
		case 119: goto st815;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st794;
	goto st0;
st795:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof795;
case 795:
	if ( (*( state.p)) == 111 )
		goto st796;
	goto st0;
st796:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof796;
case 796:
	if ( (*( state.p)) == 114 )
		goto st797;
	goto st0;
st797:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof797;
case 797:
	if ( (*( state.p)) == 110 )
		goto st798;
	goto st0;
st798:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof798;
case 798:
	if ( (*( state.p)) == 101 )
		goto st799;
	goto st0;
st799:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof799;
case 799:
	if ( (*( state.p)) == 114 )
		goto st800;
	goto st0;
st800:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof800;
case 800:
	switch( (*( state.p)) ) {
		case 13: goto tr1133;
		case 32: goto tr1133;
		case 59: goto tr1134;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1133;
	goto st0;
st801:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof801;
case 801:
	if ( (*( state.p)) == 108 )
		goto st802;
	goto st0;
st802:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof802;
case 802:
	if ( (*( state.p)) == 111 )
		goto st803;
	goto st0;
st803:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof803;
case 803:
	if ( (*( state.p)) == 111 )
		goto st804;
	goto st0;
st804:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof804;
case 804:
	if ( (*( state.p)) == 114 )
		goto st805;
	goto st0;
st805:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof805;
case 805:
	switch( (*( state.p)) ) {
		case 13: goto tr1139;
		case 32: goto tr1139;
		case 59: goto tr1140;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1139;
	goto st0;
st806:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof806;
case 806:
	if ( (*( state.p)) == 104 )
		goto st807;
	goto st0;
st807:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof807;
case 807:
	if ( (*( state.p)) == 111 )
		goto st808;
	goto st0;
st808:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof808;
case 808:
	if ( (*( state.p)) == 114 )
		goto st809;
	goto st0;
st809:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof809;
case 809:
	if ( (*( state.p)) == 101 )
		goto st810;
	goto st0;
st810:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof810;
case 810:
	if ( (*( state.p)) == 108 )
		goto st811;
	goto st0;
st811:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof811;
case 811:
	if ( (*( state.p)) == 105 )
		goto st812;
	goto st0;
st812:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof812;
case 812:
	if ( (*( state.p)) == 110 )
		goto st813;
	goto st0;
st813:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof813;
case 813:
	if ( (*( state.p)) == 101 )
		goto st814;
	goto st0;
st814:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof814;
case 814:
	switch( (*( state.p)) ) {
		case 13: goto tr1149;
		case 32: goto tr1149;
		case 59: goto tr1150;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1149;
	goto st0;
st815:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof815;
case 815:
	if ( (*( state.p)) == 97 )
		goto st816;
	goto st0;
st816:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof816;
case 816:
	switch( (*( state.p)) ) {
		case 108: goto st817;
		case 116: goto st819;
	}
	goto st0;
st817:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof817;
case 817:
	if ( (*( state.p)) == 107 )
		goto st818;
	goto st0;
st818:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof818;
case 818:
	switch( (*( state.p)) ) {
		case 13: goto tr1155;
		case 32: goto tr1155;
		case 59: goto tr1156;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1155;
	goto st0;
st819:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof819;
case 819:
	if ( (*( state.p)) == 101 )
		goto st820;
	goto st0;
st820:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof820;
case 820:
	if ( (*( state.p)) == 114 )
		goto st821;
	goto st0;
st821:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof821;
case 821:
	switch( (*( state.p)) ) {
		case 13: goto tr1159;
		case 32: goto tr1159;
		case 59: goto tr1160;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1159;
	goto st0;
st822:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof822;
case 822:
	if ( (*( state.p)) == 100 )
		goto st823;
	goto st0;
st823:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof823;
case 823:
	if ( (*( state.p)) == 108 )
		goto st824;
	goto st0;
st824:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof824;
case 824:
	if ( (*( state.p)) == 101 )
		goto st825;
	goto st0;
st825:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof825;
case 825:
	if ( (*( state.p)) == 95 )
		goto st826;
	goto st0;
st826:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof826;
case 826:
	if ( (*( state.p)) == 97 )
		goto st827;
	goto st0;
st827:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof827;
case 827:
	if ( (*( state.p)) == 105 )
		goto st828;
	goto st0;
st828:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof828;
case 828:
	switch( (*( state.p)) ) {
		case 13: goto st829;
		case 32: goto st829;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st829;
	goto st0;
st829:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof829;
case 829:
	switch( (*( state.p)) ) {
		case 13: goto st829;
		case 32: goto st829;
		case 110: goto st830;
		case 114: goto st834;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st829;
	goto st0;
st830:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof830;
case 830:
	if ( (*( state.p)) == 111 )
		goto st831;
	goto st0;
st831:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof831;
case 831:
	if ( (*( state.p)) == 110 )
		goto st832;
	goto st0;
st832:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof832;
case 832:
	if ( (*( state.p)) == 101 )
		goto st833;
	goto st0;
st833:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof833;
case 833:
	switch( (*( state.p)) ) {
		case 13: goto tr1173;
		case 32: goto tr1173;
		case 59: goto tr1174;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1173;
	goto st0;
st834:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof834;
case 834:
	if ( (*( state.p)) == 97 )
		goto st835;
	goto st0;
st835:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof835;
case 835:
	if ( (*( state.p)) == 110 )
		goto st836;
	goto st0;
st836:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof836;
case 836:
	if ( (*( state.p)) == 100 )
		goto st837;
	goto st0;
st837:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof837;
case 837:
	if ( (*( state.p)) == 111 )
		goto st838;
	goto st0;
st838:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof838;
case 838:
	if ( (*( state.p)) == 109 )
		goto st839;
	goto st0;
st839:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof839;
case 839:
	switch( (*( state.p)) ) {
		case 13: goto tr1180;
		case 32: goto tr1180;
		case 59: goto tr1181;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1180;
	goto st0;
st840:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof840;
case 840:
	if ( (*( state.p)) == 111 )
		goto st841;
	goto st0;
st841:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof841;
case 841:
	if ( (*( state.p)) == 118 )
		goto st842;
	goto st0;
st842:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof842;
case 842:
	if ( (*( state.p)) == 101 )
		goto st843;
	goto st0;
st843:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof843;
case 843:
	switch( (*( state.p)) ) {
		case 13: goto st844;
		case 32: goto st844;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st844;
	goto st0;
st844:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof844;
case 844:
	switch( (*( state.p)) ) {
		case 13: goto st844;
		case 32: goto st844;
		case 97: goto st845;
		case 102: goto st848;
		case 119: goto st853;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st844;
	goto st0;
st845:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof845;
case 845:
	if ( (*( state.p)) == 110 )
		goto st846;
	goto st0;
st846:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof846;
case 846:
	if ( (*( state.p)) == 121 )
		goto st847;
	goto st0;
st847:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof847;
case 847:
	switch( (*( state.p)) ) {
		case 13: goto tr1191;
		case 32: goto tr1191;
		case 59: goto tr1192;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1191;
	goto st0;
st848:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof848;
case 848:
	if ( (*( state.p)) == 108 )
		goto st849;
	goto st0;
st849:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof849;
case 849:
	if ( (*( state.p)) == 111 )
		goto st850;
	goto st0;
st850:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof850;
case 850:
	if ( (*( state.p)) == 111 )
		goto st851;
	goto st0;
st851:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof851;
case 851:
	if ( (*( state.p)) == 114 )
		goto st852;
	goto st0;
st852:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof852;
case 852:
	switch( (*( state.p)) ) {
		case 13: goto tr1197;
		case 32: goto tr1197;
		case 59: goto tr1198;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1197;
	goto st0;
st853:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof853;
case 853:
	if ( (*( state.p)) == 97 )
		goto st854;
	goto st0;
st854:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof854;
case 854:
	if ( (*( state.p)) == 116 )
		goto st855;
	goto st0;
st855:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof855;
case 855:
	if ( (*( state.p)) == 101 )
		goto st856;
	goto st0;
st856:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof856;
case 856:
	if ( (*( state.p)) == 114 )
		goto st857;
	goto st0;
st857:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof857;
case 857:
	switch( (*( state.p)) ) {
		case 13: goto tr1203;
		case 32: goto tr1203;
		case 59: goto tr1204;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1203;
	goto st0;
st858:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof858;
case 858:
	if ( (*( state.p)) == 97 )
		goto st859;
	goto st0;
st859:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof859;
case 859:
	if ( (*( state.p)) == 109 )
		goto st860;
	goto st0;
st860:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof860;
case 860:
	if ( (*( state.p)) == 101 )
		goto st861;
	goto st0;
st861:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof861;
case 861:
	switch( (*( state.p)) ) {
		case 13: goto st862;
		case 32: goto st862;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st862;
	goto st0;
st862:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof862;
case 862:
	switch( (*( state.p)) ) {
		case 13: goto st862;
		case 32: goto st862;
		case 34: goto st863;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st862;
	goto st0;
st863:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof863;
case 863:
	switch( (*( state.p)) ) {
		case 34: goto tr293;
		case 92: goto tr294;
	}
	goto tr291;
st864:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof864;
case 864:
	if ( (*( state.p)) == 97 )
		goto st865;
	goto st0;
st865:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof865;
case 865:
	if ( (*( state.p)) == 110 )
		goto st866;
	goto st0;
st866:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof866;
case 866:
	if ( (*( state.p)) == 103 )
		goto st867;
	goto st0;
st867:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof867;
case 867:
	if ( (*( state.p)) == 101 )
		goto st868;
	goto st0;
st868:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof868;
case 868:
	switch( (*( state.p)) ) {
		case 13: goto st869;
		case 32: goto st869;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st869;
	goto st0;
st869:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof869;
case 869:
	switch( (*( state.p)) ) {
		case 13: goto st869;
		case 32: goto st869;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1215;
	} else if ( (*( state.p)) >= 9 )
		goto st869;
	goto st0;
tr1215:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st870;
tr1217:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st870;
st870:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof870;
case 870:
#line 18059 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1216;
		case 32: goto tr1216;
		case 59: goto tr1218;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1217;
	} else if ( (*( state.p)) >= 9 )
		goto tr1216;
	goto st0;
st871:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof871;
case 871:
	if ( (*( state.p)) == 107 )
		goto st872;
	goto st0;
st872:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof872;
case 872:
	if ( (*( state.p)) == 105 )
		goto st873;
	goto st0;
st873:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof873;
case 873:
	if ( (*( state.p)) == 110 )
		goto st874;
	goto st0;
st874:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof874;
case 874:
	switch( (*( state.p)) ) {
		case 13: goto st875;
		case 32: goto st875;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st875;
	goto st0;
st875:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof875;
case 875:
	switch( (*( state.p)) ) {
		case 13: goto st875;
		case 32: goto st875;
		case 34: goto st876;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st875;
	goto st0;
st876:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof876;
case 876:
	switch( (*( state.p)) ) {
		case 34: goto tr515;
		case 92: goto tr517;
	}
	goto tr513;
st877:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof877;
case 877:
	switch( (*( state.p)) ) {
		case 13: goto tr1224;
		case 32: goto tr1224;
		case 59: goto tr1225;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1224;
	goto st0;
st878:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof878;
case 878:
	if ( (*( state.p)) == 101 )
		goto st879;
	goto st0;
st879:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof879;
case 879:
	if ( (*( state.p)) == 101 )
		goto st880;
	goto st0;
st880:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof880;
case 880:
	if ( (*( state.p)) == 107 )
		goto st881;
	goto st0;
st881:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof881;
case 881:
	if ( (*( state.p)) == 95 )
		goto st882;
	goto st0;
st882:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof882;
case 882:
	if ( (*( state.p)) == 112 )
		goto st883;
	goto st0;
st883:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof883;
case 883:
	if ( (*( state.p)) == 108 )
		goto st884;
	goto st0;
st884:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof884;
case 884:
	if ( (*( state.p)) == 97 )
		goto st885;
	goto st0;
st885:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof885;
case 885:
	if ( (*( state.p)) == 121 )
		goto st886;
	goto st0;
st886:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof886;
case 886:
	if ( (*( state.p)) == 101 )
		goto st887;
	goto st0;
st887:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof887;
case 887:
	if ( (*( state.p)) == 114 )
		goto st888;
	goto st0;
st888:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof888;
case 888:
	switch( (*( state.p)) ) {
		case 13: goto tr1236;
		case 32: goto tr1236;
		case 59: goto tr1237;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto tr1236;
	goto st0;
st889:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof889;
case 889:
	if ( (*( state.p)) == 116 )
		goto st890;
	goto st0;
st890:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof890;
case 890:
	if ( (*( state.p)) == 97 )
		goto st891;
	goto st0;
st891:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof891;
case 891:
	if ( (*( state.p)) == 99 )
		goto st892;
	goto st0;
st892:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof892;
case 892:
	if ( (*( state.p)) == 107 )
		goto st893;
	goto st0;
st893:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof893;
case 893:
	switch( (*( state.p)) ) {
		case 13: goto st894;
		case 32: goto st894;
	}
	if ( 9 <= (*( state.p)) && (*( state.p)) <= 10 )
		goto st894;
	goto st0;
st894:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof894;
case 894:
	switch( (*( state.p)) ) {
		case 13: goto st894;
		case 32: goto st894;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1243;
	} else if ( (*( state.p)) >= 9 )
		goto st894;
	goto st0;
tr1243:
#line 94 "configparser.rl"
	{
            state.match.clear();
        }
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st895;
tr1246:
#line 98 "configparser.rl"
	{
            state.match += (*( state.p));
        }
	goto st895;
st895:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof895;
case 895:
#line 18291 "configparser.h"
	switch( (*( state.p)) ) {
		case 13: goto tr1244;
		case 32: goto tr1244;
		case 46: goto st896;
		case 59: goto tr1247;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto tr1246;
	} else if ( (*( state.p)) >= 9 )
		goto tr1244;
	goto st0;
st896:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof896;
case 896:
	if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
		goto st897;
	goto st0;
st897:
	if ( ++( state.p) == ( state.pe) )
		goto _test_eof897;
case 897:
	switch( (*( state.p)) ) {
		case 13: goto tr1244;
		case 32: goto tr1244;
		case 59: goto tr1247;
	}
	if ( (*( state.p)) > 10 ) {
		if ( 48 <= (*( state.p)) && (*( state.p)) <= 57 )
			goto st897;
	} else if ( (*( state.p)) >= 9 )
		goto tr1244;
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
	_test_eof898:  state.cs = 898; goto _test_eof; 
	_test_eof899:  state.cs = 899; goto _test_eof; 
	_test_eof14:  state.cs = 14; goto _test_eof; 
	_test_eof15:  state.cs = 15; goto _test_eof; 
	_test_eof16:  state.cs = 16; goto _test_eof; 
	_test_eof17:  state.cs = 17; goto _test_eof; 
	_test_eof18:  state.cs = 18; goto _test_eof; 
	_test_eof19:  state.cs = 19; goto _test_eof; 
	_test_eof20:  state.cs = 20; goto _test_eof; 
	_test_eof21:  state.cs = 21; goto _test_eof; 
	_test_eof22:  state.cs = 22; goto _test_eof; 
	_test_eof900:  state.cs = 900; goto _test_eof; 
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
	_test_eof901:  state.cs = 901; goto _test_eof; 
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
	_test_eof902:  state.cs = 902; goto _test_eof; 
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
	_test_eof903:  state.cs = 903; goto _test_eof; 
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
	_test_eof673:  state.cs = 673; goto _test_eof; 
	_test_eof674:  state.cs = 674; goto _test_eof; 
	_test_eof675:  state.cs = 675; goto _test_eof; 
	_test_eof676:  state.cs = 676; goto _test_eof; 
	_test_eof677:  state.cs = 677; goto _test_eof; 
	_test_eof678:  state.cs = 678; goto _test_eof; 
	_test_eof679:  state.cs = 679; goto _test_eof; 
	_test_eof680:  state.cs = 680; goto _test_eof; 
	_test_eof681:  state.cs = 681; goto _test_eof; 
	_test_eof682:  state.cs = 682; goto _test_eof; 
	_test_eof683:  state.cs = 683; goto _test_eof; 
	_test_eof684:  state.cs = 684; goto _test_eof; 
	_test_eof685:  state.cs = 685; goto _test_eof; 
	_test_eof686:  state.cs = 686; goto _test_eof; 
	_test_eof687:  state.cs = 687; goto _test_eof; 
	_test_eof688:  state.cs = 688; goto _test_eof; 
	_test_eof689:  state.cs = 689; goto _test_eof; 
	_test_eof690:  state.cs = 690; goto _test_eof; 
	_test_eof691:  state.cs = 691; goto _test_eof; 
	_test_eof692:  state.cs = 692; goto _test_eof; 
	_test_eof693:  state.cs = 693; goto _test_eof; 
	_test_eof694:  state.cs = 694; goto _test_eof; 
	_test_eof695:  state.cs = 695; goto _test_eof; 
	_test_eof696:  state.cs = 696; goto _test_eof; 
	_test_eof697:  state.cs = 697; goto _test_eof; 
	_test_eof698:  state.cs = 698; goto _test_eof; 
	_test_eof699:  state.cs = 699; goto _test_eof; 
	_test_eof700:  state.cs = 700; goto _test_eof; 
	_test_eof701:  state.cs = 701; goto _test_eof; 
	_test_eof702:  state.cs = 702; goto _test_eof; 
	_test_eof703:  state.cs = 703; goto _test_eof; 
	_test_eof704:  state.cs = 704; goto _test_eof; 
	_test_eof705:  state.cs = 705; goto _test_eof; 
	_test_eof706:  state.cs = 706; goto _test_eof; 
	_test_eof707:  state.cs = 707; goto _test_eof; 
	_test_eof708:  state.cs = 708; goto _test_eof; 
	_test_eof709:  state.cs = 709; goto _test_eof; 
	_test_eof710:  state.cs = 710; goto _test_eof; 
	_test_eof711:  state.cs = 711; goto _test_eof; 
	_test_eof712:  state.cs = 712; goto _test_eof; 
	_test_eof713:  state.cs = 713; goto _test_eof; 
	_test_eof714:  state.cs = 714; goto _test_eof; 
	_test_eof715:  state.cs = 715; goto _test_eof; 
	_test_eof716:  state.cs = 716; goto _test_eof; 
	_test_eof717:  state.cs = 717; goto _test_eof; 
	_test_eof718:  state.cs = 718; goto _test_eof; 
	_test_eof719:  state.cs = 719; goto _test_eof; 
	_test_eof720:  state.cs = 720; goto _test_eof; 
	_test_eof721:  state.cs = 721; goto _test_eof; 
	_test_eof722:  state.cs = 722; goto _test_eof; 
	_test_eof723:  state.cs = 723; goto _test_eof; 
	_test_eof724:  state.cs = 724; goto _test_eof; 
	_test_eof725:  state.cs = 725; goto _test_eof; 
	_test_eof726:  state.cs = 726; goto _test_eof; 
	_test_eof727:  state.cs = 727; goto _test_eof; 
	_test_eof728:  state.cs = 728; goto _test_eof; 
	_test_eof729:  state.cs = 729; goto _test_eof; 
	_test_eof730:  state.cs = 730; goto _test_eof; 
	_test_eof731:  state.cs = 731; goto _test_eof; 
	_test_eof732:  state.cs = 732; goto _test_eof; 
	_test_eof733:  state.cs = 733; goto _test_eof; 
	_test_eof734:  state.cs = 734; goto _test_eof; 
	_test_eof735:  state.cs = 735; goto _test_eof; 
	_test_eof736:  state.cs = 736; goto _test_eof; 
	_test_eof737:  state.cs = 737; goto _test_eof; 
	_test_eof738:  state.cs = 738; goto _test_eof; 
	_test_eof739:  state.cs = 739; goto _test_eof; 
	_test_eof740:  state.cs = 740; goto _test_eof; 
	_test_eof741:  state.cs = 741; goto _test_eof; 
	_test_eof742:  state.cs = 742; goto _test_eof; 
	_test_eof743:  state.cs = 743; goto _test_eof; 
	_test_eof744:  state.cs = 744; goto _test_eof; 
	_test_eof745:  state.cs = 745; goto _test_eof; 
	_test_eof746:  state.cs = 746; goto _test_eof; 
	_test_eof747:  state.cs = 747; goto _test_eof; 
	_test_eof748:  state.cs = 748; goto _test_eof; 
	_test_eof749:  state.cs = 749; goto _test_eof; 
	_test_eof750:  state.cs = 750; goto _test_eof; 
	_test_eof751:  state.cs = 751; goto _test_eof; 
	_test_eof752:  state.cs = 752; goto _test_eof; 
	_test_eof753:  state.cs = 753; goto _test_eof; 
	_test_eof754:  state.cs = 754; goto _test_eof; 
	_test_eof755:  state.cs = 755; goto _test_eof; 
	_test_eof756:  state.cs = 756; goto _test_eof; 
	_test_eof757:  state.cs = 757; goto _test_eof; 
	_test_eof758:  state.cs = 758; goto _test_eof; 
	_test_eof759:  state.cs = 759; goto _test_eof; 
	_test_eof760:  state.cs = 760; goto _test_eof; 
	_test_eof761:  state.cs = 761; goto _test_eof; 
	_test_eof762:  state.cs = 762; goto _test_eof; 
	_test_eof763:  state.cs = 763; goto _test_eof; 
	_test_eof764:  state.cs = 764; goto _test_eof; 
	_test_eof765:  state.cs = 765; goto _test_eof; 
	_test_eof766:  state.cs = 766; goto _test_eof; 
	_test_eof767:  state.cs = 767; goto _test_eof; 
	_test_eof768:  state.cs = 768; goto _test_eof; 
	_test_eof769:  state.cs = 769; goto _test_eof; 
	_test_eof770:  state.cs = 770; goto _test_eof; 
	_test_eof771:  state.cs = 771; goto _test_eof; 
	_test_eof772:  state.cs = 772; goto _test_eof; 
	_test_eof773:  state.cs = 773; goto _test_eof; 
	_test_eof774:  state.cs = 774; goto _test_eof; 
	_test_eof775:  state.cs = 775; goto _test_eof; 
	_test_eof776:  state.cs = 776; goto _test_eof; 
	_test_eof777:  state.cs = 777; goto _test_eof; 
	_test_eof778:  state.cs = 778; goto _test_eof; 
	_test_eof779:  state.cs = 779; goto _test_eof; 
	_test_eof780:  state.cs = 780; goto _test_eof; 
	_test_eof781:  state.cs = 781; goto _test_eof; 
	_test_eof782:  state.cs = 782; goto _test_eof; 
	_test_eof783:  state.cs = 783; goto _test_eof; 
	_test_eof784:  state.cs = 784; goto _test_eof; 
	_test_eof785:  state.cs = 785; goto _test_eof; 
	_test_eof786:  state.cs = 786; goto _test_eof; 
	_test_eof787:  state.cs = 787; goto _test_eof; 
	_test_eof788:  state.cs = 788; goto _test_eof; 
	_test_eof789:  state.cs = 789; goto _test_eof; 
	_test_eof790:  state.cs = 790; goto _test_eof; 
	_test_eof791:  state.cs = 791; goto _test_eof; 
	_test_eof792:  state.cs = 792; goto _test_eof; 
	_test_eof793:  state.cs = 793; goto _test_eof; 
	_test_eof794:  state.cs = 794; goto _test_eof; 
	_test_eof795:  state.cs = 795; goto _test_eof; 
	_test_eof796:  state.cs = 796; goto _test_eof; 
	_test_eof797:  state.cs = 797; goto _test_eof; 
	_test_eof798:  state.cs = 798; goto _test_eof; 
	_test_eof799:  state.cs = 799; goto _test_eof; 
	_test_eof800:  state.cs = 800; goto _test_eof; 
	_test_eof801:  state.cs = 801; goto _test_eof; 
	_test_eof802:  state.cs = 802; goto _test_eof; 
	_test_eof803:  state.cs = 803; goto _test_eof; 
	_test_eof804:  state.cs = 804; goto _test_eof; 
	_test_eof805:  state.cs = 805; goto _test_eof; 
	_test_eof806:  state.cs = 806; goto _test_eof; 
	_test_eof807:  state.cs = 807; goto _test_eof; 
	_test_eof808:  state.cs = 808; goto _test_eof; 
	_test_eof809:  state.cs = 809; goto _test_eof; 
	_test_eof810:  state.cs = 810; goto _test_eof; 
	_test_eof811:  state.cs = 811; goto _test_eof; 
	_test_eof812:  state.cs = 812; goto _test_eof; 
	_test_eof813:  state.cs = 813; goto _test_eof; 
	_test_eof814:  state.cs = 814; goto _test_eof; 
	_test_eof815:  state.cs = 815; goto _test_eof; 
	_test_eof816:  state.cs = 816; goto _test_eof; 
	_test_eof817:  state.cs = 817; goto _test_eof; 
	_test_eof818:  state.cs = 818; goto _test_eof; 
	_test_eof819:  state.cs = 819; goto _test_eof; 
	_test_eof820:  state.cs = 820; goto _test_eof; 
	_test_eof821:  state.cs = 821; goto _test_eof; 
	_test_eof822:  state.cs = 822; goto _test_eof; 
	_test_eof823:  state.cs = 823; goto _test_eof; 
	_test_eof824:  state.cs = 824; goto _test_eof; 
	_test_eof825:  state.cs = 825; goto _test_eof; 
	_test_eof826:  state.cs = 826; goto _test_eof; 
	_test_eof827:  state.cs = 827; goto _test_eof; 
	_test_eof828:  state.cs = 828; goto _test_eof; 
	_test_eof829:  state.cs = 829; goto _test_eof; 
	_test_eof830:  state.cs = 830; goto _test_eof; 
	_test_eof831:  state.cs = 831; goto _test_eof; 
	_test_eof832:  state.cs = 832; goto _test_eof; 
	_test_eof833:  state.cs = 833; goto _test_eof; 
	_test_eof834:  state.cs = 834; goto _test_eof; 
	_test_eof835:  state.cs = 835; goto _test_eof; 
	_test_eof836:  state.cs = 836; goto _test_eof; 
	_test_eof837:  state.cs = 837; goto _test_eof; 
	_test_eof838:  state.cs = 838; goto _test_eof; 
	_test_eof839:  state.cs = 839; goto _test_eof; 
	_test_eof840:  state.cs = 840; goto _test_eof; 
	_test_eof841:  state.cs = 841; goto _test_eof; 
	_test_eof842:  state.cs = 842; goto _test_eof; 
	_test_eof843:  state.cs = 843; goto _test_eof; 
	_test_eof844:  state.cs = 844; goto _test_eof; 
	_test_eof845:  state.cs = 845; goto _test_eof; 
	_test_eof846:  state.cs = 846; goto _test_eof; 
	_test_eof847:  state.cs = 847; goto _test_eof; 
	_test_eof848:  state.cs = 848; goto _test_eof; 
	_test_eof849:  state.cs = 849; goto _test_eof; 
	_test_eof850:  state.cs = 850; goto _test_eof; 
	_test_eof851:  state.cs = 851; goto _test_eof; 
	_test_eof852:  state.cs = 852; goto _test_eof; 
	_test_eof853:  state.cs = 853; goto _test_eof; 
	_test_eof854:  state.cs = 854; goto _test_eof; 
	_test_eof855:  state.cs = 855; goto _test_eof; 
	_test_eof856:  state.cs = 856; goto _test_eof; 
	_test_eof857:  state.cs = 857; goto _test_eof; 
	_test_eof858:  state.cs = 858; goto _test_eof; 
	_test_eof859:  state.cs = 859; goto _test_eof; 
	_test_eof860:  state.cs = 860; goto _test_eof; 
	_test_eof861:  state.cs = 861; goto _test_eof; 
	_test_eof862:  state.cs = 862; goto _test_eof; 
	_test_eof863:  state.cs = 863; goto _test_eof; 
	_test_eof864:  state.cs = 864; goto _test_eof; 
	_test_eof865:  state.cs = 865; goto _test_eof; 
	_test_eof866:  state.cs = 866; goto _test_eof; 
	_test_eof867:  state.cs = 867; goto _test_eof; 
	_test_eof868:  state.cs = 868; goto _test_eof; 
	_test_eof869:  state.cs = 869; goto _test_eof; 
	_test_eof870:  state.cs = 870; goto _test_eof; 
	_test_eof871:  state.cs = 871; goto _test_eof; 
	_test_eof872:  state.cs = 872; goto _test_eof; 
	_test_eof873:  state.cs = 873; goto _test_eof; 
	_test_eof874:  state.cs = 874; goto _test_eof; 
	_test_eof875:  state.cs = 875; goto _test_eof; 
	_test_eof876:  state.cs = 876; goto _test_eof; 
	_test_eof877:  state.cs = 877; goto _test_eof; 
	_test_eof878:  state.cs = 878; goto _test_eof; 
	_test_eof879:  state.cs = 879; goto _test_eof; 
	_test_eof880:  state.cs = 880; goto _test_eof; 
	_test_eof881:  state.cs = 881; goto _test_eof; 
	_test_eof882:  state.cs = 882; goto _test_eof; 
	_test_eof883:  state.cs = 883; goto _test_eof; 
	_test_eof884:  state.cs = 884; goto _test_eof; 
	_test_eof885:  state.cs = 885; goto _test_eof; 
	_test_eof886:  state.cs = 886; goto _test_eof; 
	_test_eof887:  state.cs = 887; goto _test_eof; 
	_test_eof888:  state.cs = 888; goto _test_eof; 
	_test_eof889:  state.cs = 889; goto _test_eof; 
	_test_eof890:  state.cs = 890; goto _test_eof; 
	_test_eof891:  state.cs = 891; goto _test_eof; 
	_test_eof892:  state.cs = 892; goto _test_eof; 
	_test_eof893:  state.cs = 893; goto _test_eof; 
	_test_eof894:  state.cs = 894; goto _test_eof; 
	_test_eof895:  state.cs = 895; goto _test_eof; 
	_test_eof896:  state.cs = 896; goto _test_eof; 
	_test_eof897:  state.cs = 897; goto _test_eof; 

	_test_eof: {}
	if ( ( state.p) == ( state.eof) )
	{
	switch (  state.cs ) {
	case 898: 
#line 204 "configparser.rl"
	{ std::cout << "species done: " << std::endl; print_species(spe); }
	break;
#line 19239 "configparser.h"
	}
	}

	_out: {}
	}

#line 238 "configparser.rl"

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
