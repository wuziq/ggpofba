/*
 Teenage Mutant Ninja Turtles

 Original driver from Final Burn written by Dave
 A lot of improvements by KEV
 FB Alpha Convertion by FerchogtX

 This is a preliminary driver, bassed on the Final Burn sources so, the game has some bugs,
 the sprites aren't rendered at 100% and lacks sound.
*/

#include "burnint.h"
#include "burn_ym2151.h"

unsigned char bTmntRecalcPal=0;
unsigned char *TmntRam08,*TmntRam10,*TmntTile,*TmntZ80Ram,*PriRam,*K051960Ram;

static unsigned char *TmntSampleROM01=NULL,*TmntSampleROM02=NULL,*TmntSampleROM03=NULL;
static unsigned char *Tmnt68KROM01,*TmntRam06,*TmntSprite,*TmntZ80Rom,*TmntSpriteTemp/*,*Ram14*/;
static unsigned char *Mem=NULL,*MemEnd=NULL;
static unsigned char *RamStart=NULL,*RamEnd=NULL;
static unsigned char bInt5=0; // 1 if we are doing int 5
static int tmnt_soundlatch;

struct K051960Sprite {int h,w,x,y,number,pal_offset,zoomy,flipx,flipy,zoomx;} sprite;

static int nCyclesDone[2], nCyclesTotal[2];
static int nCyclesSegment;

unsigned char DrvReset=0;
inline static int CheckSleep(int)
{
	return 0;
}

// Pallete
unsigned int TmntPal[0x400];
static unsigned char bAnyDirt,Dirt[0x80];

// Tiles
static unsigned int nPageBase[4]={0,0,0,0};
static short nScrollX[3]={12*8,0,0},nScrollY[3]={2*8,0,0};
int count=0;

// Input
unsigned char TmntAoo[0x10]; // values to return from A0000
unsigned char TmntCoin[4],TmntService[4],TmntStart[4],TmntAttack[4],TmntJump[4],TmntUp[4],TmntDown[4],TmntLeft[4],TmntRight[4],Tmnt2pStart[2];
static unsigned char *pPlay[4]={TmntAoo+1,TmntAoo+2,TmntAoo+3,TmntAoo+0x0a};
static unsigned char TmntDip[3]={0,0,0};

//----------------------------------------------------------
// Input list
static struct BurnInputInfo TmntInputList[] = {
	{"P1 Coin"   , BIT_DIGITAL  , TmntCoin+0,"p1 coin"},
	{"P1 Start"  , BIT_DIGITAL  , TmntStart+0,"p1 start"},
	{"P1 Attack" , BIT_DIGITAL  , TmntAttack+0,"p1 fire 1"},
	{"P1 Jump"   , BIT_DIGITAL  , TmntJump+0,"p1 fire 2"},
	{"P1 Up"     , BIT_DIGITAL  , TmntUp+0,"p1 up"},
	{"P1 Down"   , BIT_DIGITAL  , TmntDown+0,"p1 down"},
	{"P1 Left"   , BIT_DIGITAL  , TmntLeft+0,"p1 left"},
	{"P1 Right"  , BIT_DIGITAL  , TmntRight+0,"p1 right"},
	{"Service 1" , BIT_DIGITAL  , TmntService+0,"service"},

	{"P2 Coin"   , BIT_DIGITAL  , TmntCoin+1,"p2 coin"},
	{"P2 Start"  , BIT_DIGITAL  , TmntStart+1,"p2 start"},
	{"P2 Attack" , BIT_DIGITAL  , TmntAttack+1,"p2 fire 1"},
	{"P2 Jump"   , BIT_DIGITAL  , TmntJump+1,"p2 fire 2"},
	{"P2 Up"     , BIT_DIGITAL  , TmntUp+1,"p2 up"},
	{"P2 Down"   , BIT_DIGITAL  , TmntDown+1,"p2 down"},
	{"P2 Left"   , BIT_DIGITAL  , TmntLeft+1,"p2 left"},
	{"P2 Right"  , BIT_DIGITAL  , TmntRight+1,"p2 right"},
	{"Service 2" , BIT_DIGITAL  , TmntService+1,""},

	{"P3 Coin"   , BIT_DIGITAL  , TmntCoin+2,"p3 coin"},
	{"P3 Start"  , BIT_DIGITAL  , TmntStart+2,"p3 start"},
	{"P3 Attack" , BIT_DIGITAL  , TmntAttack+2,"p3 fire 1"},
	{"P3 Jump"   , BIT_DIGITAL  , TmntJump+2,"p3 fire 2"},
	{"P3 Up"     , BIT_DIGITAL  , TmntUp+2,"p3 up"},
	{"P3 Down"   , BIT_DIGITAL  , TmntDown+2,"p3 down"},
	{"P3 Left"   , BIT_DIGITAL  , TmntLeft+2,"p3 left"},
	{"P3 Right"  , BIT_DIGITAL  , TmntRight+2,"p3 right"},
	{"Service 3" , BIT_DIGITAL  , TmntService+2,""},

	{"P4 Coin"   , BIT_DIGITAL  , TmntCoin+3,"p4 coin"},
	{"P4 Start"  , BIT_DIGITAL  , TmntStart+3,"p4 start"},
	{"P4 Attack" , BIT_DIGITAL  , TmntAttack+3,"p4 fire 1"},
	{"P4 Jump"   , BIT_DIGITAL  , TmntJump+3,"p4 fire 2"},
	{"P4 Up"     , BIT_DIGITAL  , TmntUp+3,"p4 up"},
	{"P4 Down"   , BIT_DIGITAL  , TmntDown+3,"p4 down"},
	{"P4 Left"   , BIT_DIGITAL  , TmntLeft+3,"p4 left"},
	{"P4 Right"  , BIT_DIGITAL  , TmntRight+3,"p4 right"},
	{"Service 4" , BIT_DIGITAL  , TmntService+3,""},

	{"Reset"     , BIT_DIGITAL  , &DrvReset	 ,"reset"},

	{"Dip 1"     , BIT_DIPSWITCH, TmntDip+0  ,"dip"},
	{"Dip 2"     , BIT_DIPSWITCH, TmntDip+1  ,"dip"},
	{"Dip 3"     , BIT_DIPSWITCH, TmntDip+2  ,"dip"},
};

static struct BurnInputInfo Tmnt2pInputList[] = {
	{"P1 Coin"   , BIT_DIGITAL  , TmntCoin+0,"p1 coin"},
	{"P1 Start"  , BIT_DIGITAL  , Tmnt2pStart+0,"p1 start"},
	{"P1 Attack" , BIT_DIGITAL  , TmntAttack+0,"p1 fire 1"},
	{"P1 Jump"   , BIT_DIGITAL  , TmntJump+0,"p1 fire 2"},
	{"P1 Up"     , BIT_DIGITAL  , TmntUp+0,"p1 up"},
	{"P1 Down"   , BIT_DIGITAL  , TmntDown+0,"p1 down"},
	{"P1 Left"   , BIT_DIGITAL  , TmntLeft+0,"p1 left"},
	{"P1 Right"  , BIT_DIGITAL  , TmntRight+0,"p1 right"},
	{"Service 1" , BIT_DIGITAL  , TmntService+0,"service"},

	{"P2 Coin"   , BIT_DIGITAL  , TmntCoin+1,"p2 coin"},
	{"P2 Start"  , BIT_DIGITAL  , Tmnt2pStart+1,"p2 start"},
	{"P2 Attack" , BIT_DIGITAL  , TmntAttack+1,"p2 fire 1"},
	{"P2 Jump"   , BIT_DIGITAL  , TmntJump+1,"p2 fire 2"},
	{"P2 Up"     , BIT_DIGITAL  , TmntUp+1,"p2 up"},
	{"P2 Down"   , BIT_DIGITAL  , TmntDown+1,"p2 down"},
	{"P2 Left"   , BIT_DIGITAL  , TmntLeft+1,"p2 left"},
	{"P2 Right"  , BIT_DIGITAL  , TmntRight+1	,"p2 right"},
	{"Service 2" , BIT_DIGITAL  , TmntService+1,""},

	{"Reset"     , BIT_DIGITAL  , &DrvReset	 ,"reset"},

	{"Dip 1"     , BIT_DIPSWITCH, TmntDip+0  ,"dip"},
	{"Dip 2"     , BIT_DIPSWITCH, TmntDip+1  ,"dip"},
	{"Dip 3"     , BIT_DIPSWITCH, TmntDip+2  ,"dip"},
};

STDINPUTINFO(Tmnt);
STDINPUTINFO(Tmnt2p);

static struct BurnDIPInfo TmntDIPList[]= {
	// Default Values
	{0x25, 0xff, 0xff, 0x00, NULL},
	{0x26, 0xff, 0xff, 0x20, NULL},
	{0x27, 0xff, 0xff, 0x00, NULL},

	// Dip 1
	{0   , 0xfe, 0   , 16  , "Coin 1"},
	{0x25, 0x01, 0x0f, 0x00, "1 coin 1 play"},
	{0x25, 0x01, 0x0f, 0x01, "1 coin 2 plays"},
	{0x25, 0x01, 0x0f, 0x02, "1 coin 3 plays"},
	{0x25, 0x01, 0x0f, 0x03, "1 coin 4 plays"},
	{0x25, 0x01, 0x0f, 0x04, "1 coin 5 plays"},
	{0x25, 0x01, 0x0f, 0x05, "1 coin 6 plays"},
	{0x25, 0x01, 0x0f, 0x06, "1 coin 7 plays"},
	{0x25, 0x01, 0x0f, 0x07, "2 coins 1 play"},
	{0x25, 0x01, 0x0f, 0x08, "2 coins 3 plays"},
	{0x25, 0x01, 0x0f, 0x09, "2 coins 5 plays"},
	{0x25, 0x01, 0x0f, 0x0a, "3 coins 1 play"},
	{0x25, 0x01, 0x0f, 0x0b, "3 coins 2 plays"},
	{0x25, 0x01, 0x0f, 0x0c, "3 coins 4 plays"},
	{0x25, 0x01, 0x0f, 0x0d, "4 coins 1 play"},
  {0x25, 0x01, 0x0f, 0x0e, "4 coins 3 plays"},
	{0x25, 0x01, 0x0f, 0x0f, "5 coins 1 play"},

	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"},
	{0x26, 0x01, 0x60, 0x00, "Easy"},
	{0x26, 0x01, 0x60, 0x20, "Normal"},
	{0x26, 0x01, 0x60, 0x40, "Difficult"},
	{0x26, 0x01, 0x60, 0x60, "Very difficult"},

	{0   , 0xfe, 0   , 4   , "Players"},
	{0x26, 0x01, 0x03, 0x00, "1"},
	{0x26, 0x01, 0x03, 0x01, "2"},
	{0x26, 0x01, 0x03, 0x02, "3"},
	{0x26, 0x01, 0x03, 0x03, "5"},

	{0   , 0xfe, 0   , 2   , "Demo sound"},
	{0x26, 0x01, 0x80, 0x00, "Off"},
	{0x26, 0x01, 0x80, 0x80, "On"},

	// Dip 3
	{0   , 0xfe, 0   , 2   , "Screen"},
	{0x27, 0x01, 0x01, 0x00, "Normal"},
	{0x27, 0x01, 0x01, 0x01, "Upside down"},

	{0   , 0xfe, 0   , 2   , NULL},
	{0x27, 0x01, 0x04, 0x00, "Game mode"},
	{0x27, 0x01, 0x04, 0x04, "Test mode"},
};

static struct BurnDIPInfo Tmnt2pDIPList[]= {
	// Default Values
	{0x13, 0xff, 0xff, 0x00, NULL},
	{0x14, 0xff, 0xff, 0x20, NULL},
	{0x15, 0xff, 0xff, 0x00, NULL},

	// Dip 1
	{0   , 0xfe, 0   , 16  , "Coin 1"},
	{0x13, 0x01, 0x0f, 0x00, "1 coin 1 play"},
	{0x13, 0x01, 0x0f, 0x01, "1 coin 2 plays"},
	{0x13, 0x01, 0x0f, 0x02, "1 coin 3 plays"},
	{0x13, 0x01, 0x0f, 0x03, "1 coin 4 plays"},
	{0x13, 0x01, 0x0f, 0x04, "1 coin 5 plays"},
	{0x13, 0x01, 0x0f, 0x05, "1 coin 6 plays"},
	{0x13, 0x01, 0x0f, 0x06, "1 coin 7 plays"},
	{0x13, 0x01, 0x0f, 0x07, "2 coins 1 play"},
	{0x13, 0x01, 0x0f, 0x08, "2 coins 3 plays"},
	{0x13, 0x01, 0x0f, 0x09, "2 coins 5 plays"},
	{0x13, 0x01, 0x0f, 0x0a, "3 coins 1 play"},
	{0x13, 0x01, 0x0f, 0x0b, "3 coins 2 plays"},
	{0x13, 0x01, 0x0f, 0x0c, "3 coins 4 plays"},
	{0x13, 0x01, 0x0f, 0x0d, "4 coins 1 play"},
  {0x13, 0x01, 0x0f, 0x0e, "4 coins 3 plays"},
	{0x13, 0x01, 0x0f, 0x0f, "Free play"},

	{0   , 0xfe, 0   , 15  , "Coin 2"},
	{0x13, 0x82, 0xf0, 0x00, "1 coin 1 play"},
	{0x13, 0x00, 0x0f, 0x0f, NULL},
	{0x13, 0x82, 0xf0, 0x10, "1 coin 2 plays"},
	{0x13, 0x00, 0x0f, 0x0f, NULL},
	{0x13, 0x82, 0xf0, 0x20, "1 coin 3 plays"},
	{0x13, 0x00, 0x0f, 0x0f, NULL},
	{0x13, 0x82, 0xf0, 0x30, "1 coin 4 plays"},
	{0x13, 0x00, 0x0f, 0x0f, NULL},
	{0x13, 0x82, 0xf0, 0x40, "1 coin 5 plays"},
	{0x13, 0x00, 0x0f, 0x0f, NULL},
	{0x13, 0x82, 0xf0, 0x50, "1 coin 6 plays"},
	{0x13, 0x00, 0x0f, 0x0f, NULL},
	{0x13, 0x82, 0xf0, 0x60, "1 coin 7 plays"},
	{0x13, 0x00, 0x0f, 0x0f, NULL},
	{0x13, 0x82, 0xf0, 0x70, "2 coins 1 play"},
	{0x13, 0x00, 0x0f, 0x0f, NULL},
	{0x13, 0x82, 0xf0, 0x80, "2 coins 3 plays"},
	{0x13, 0x00, 0x0f, 0x0f, NULL},
	{0x13, 0x82, 0xf0, 0x90, "2 coins 5 plays"},
	{0x13, 0x00, 0x0f, 0x0f, NULL},
	{0x13, 0x82, 0xf0, 0xa0, "3 coins 1 play"},
	{0x13, 0x00, 0x0f, 0x0f, NULL},
	{0x13, 0x82, 0xf0, 0xb0, "3 coins 2 plays"},
	{0x13, 0x00, 0x0f, 0x0f, NULL},
	{0x13, 0x82, 0xf0, 0xc0, "3 coins 4 plays"},
	{0x13, 0x00, 0x0f, 0x0f, NULL},
	{0x13, 0x82, 0xf0, 0xd0, "4 coins 1 play"},
	{0x13, 0x00, 0x0f, 0x0f, NULL},
	{0x13, 0x82, 0xf0, 0xe0, "4 coins 3 plays"},
	{0x13, 0x00, 0x0f, 0x0f, NULL},
//	{0x13, 0x82, 0xf0, 0xf0, "Invalid"},
//	{0x13, 0x00, 0x0f, 0x0f, NULL},

	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"},
	{0x14, 0x01, 0x60, 0x00, "Easy"},
	{0x14, 0x01, 0x60, 0x20, "Normal"},
	{0x14, 0x01, 0x60, 0x40, "Difficult"},
	{0x14, 0x01, 0x60, 0x60, "Very difficult"},

	{0   , 0xfe, 0   , 4   , "Players"},
	{0x14, 0x01, 0x03, 0x00, "1"},
	{0x14, 0x01, 0x03, 0x01, "2"},
	{0x14, 0x01, 0x03, 0x02, "3"},
	{0x14, 0x01, 0x03, 0x03, "5"},

	{0   , 0xfe, 0   , 2   , "Demo sound"},
	{0x14, 0x01, 0x80, 0x00, "Off"},
	{0x14, 0x01, 0x80, 0x80, "On"},

	// Dip 3
	{0   , 0xfe, 0   , 2   , "Screen"},
	{0x15, 0x01, 0x01, 0x00, "Normal"},
	{0x15, 0x01, 0x01, 0x01, "Upside down"},

	{0   , 0xfe, 0   , 2   , NULL},
	{0x15, 0x01, 0x04, 0x00, "Game mode"},
	{0x15, 0x01, 0x04, 0x04, "Test mode"},
};

STDDIPINFO(Tmnt);
STDDIPINFO(Tmnt2p);

// Rom information
// ==============================================
// Teenage Mutant Ninja Turtles (World 4 Players)
// ==============================================
static struct BurnRomInfo TmntRomDesc[] = {
	{ "963-x23.j17", 0x20000, 0xa9549004, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "963-x24.k17", 0x20000, 0xe5cc9067, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "963-x21.j15", 0x10000, 0x5789cf92, BRF_ESS | BRF_PRG }, //  2            (even)
	{ "963-x22.k15", 0x10000, 0x0a74e277, BRF_ESS | BRF_PRG }, //  3            (odd)

	{ "963a28.h27",  0x80000, 0xdb4769a8, BRF_GRA }, //  4 tile bitmaps
	{ "963a29.k27",  0x80000, 0x8069cd2e, BRF_GRA }, //  5

	{ "963a16.k6",   0x80000, 0xd4bd9984, BRF_GRA }, //  6 sprites
	{ "963a18.h6",   0x80000, 0xdd51adef, BRF_GRA }, //  7
	{ "963a15.k4",   0x80000, 0x1f324eed, BRF_GRA }, //  8
	{ "963a17.h4",   0x80000, 0xb5239a44, BRF_GRA }, //  9

	{ "963e20.g13",  0x08000, 0x1692a6d6, BRF_SND | BRF_PRG }, //  10 Z80 rom

	{ "963a26.c13",  0x20000, 0xe2ac3063, BRF_SND }, //  11 samples (K007232)
	{ "963a27.d18",  0x20000, 0x2dfd674b, BRF_SND }, //  12 samples (UPD7759C)
	{ "963a25.d5",   0x80000, 0xfca078c7, BRF_SND }, //  13 title music sample

	{ "963a30.g7",   0x0100,  0xabd82680, BRF_GRA }, //  14 sprite address decoder
	{ "963a31.g19",  0x0100,  0xf8004a1c, BRF_GRA }, //  15 priority encoder (not used)	
};

STD_ROM_PICK(Tmnt);
STD_ROM_FN(Tmnt);

// ==================================================
// Teenage Mutant Ninja Turtles (US 4 Players, set 1)
// ==================================================
static struct BurnRomInfo TmntuRomDesc[] = {
	{ "963-r23.j17", 0x20000, 0xa7f61195, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "963-r24.k17", 0x20000, 0x661e056a, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "963-r21.j15", 0x10000, 0xde047bb6, BRF_ESS | BRF_PRG }, //  2            (even)
	{ "963-r22.k15", 0x10000, 0xd86a0888, BRF_ESS | BRF_PRG }, //  3            (odd)

	{ "963a28.h27",  0x80000, 0xdb4769a8, BRF_GRA }, //  4 tile bitmaps
	{ "963a29.k27",  0x80000, 0x8069cd2e, BRF_GRA }, //  5

	{ "963a16.k6",   0x80000, 0xd4bd9984, BRF_GRA }, //  6 sprites
	{ "963a18.h6",   0x80000, 0xdd51adef, BRF_GRA }, //  7
	{ "963a15.k4",   0x80000, 0x1f324eed, BRF_GRA }, //  8
	{ "963a17.h4",   0x80000, 0xb5239a44, BRF_GRA }, //  9

	{ "963e20.g13",  0x08000, 0x1692a6d6, BRF_SND | BRF_PRG }, //  10 Z80 rom

	{ "963a26.c13",  0x20000, 0xe2ac3063, BRF_SND }, //  11 samples (K007232)
	{ "963a27.d18",  0x20000, 0x2dfd674b, BRF_SND }, //  12 samples (UPD7759C)
	{ "963a25.d5",   0x80000, 0xfca078c7, BRF_SND }, //  13 title music sample

	{ "963a30.g7",   0x0100,  0xabd82680, BRF_GRA }, //  14 sprite address decoder
	{ "963a31.g19",  0x0100,  0xf8004a1c, BRF_GRA }, //  15 priority encoder (not used)	
};

STD_ROM_PICK(Tmntu);
STD_ROM_FN(Tmntu);

// ==================================================
// Teenage Mutant Ninja Turtles (US 4 Players, set 2)
// ==================================================
static struct BurnRomInfo TmntuaRomDesc[] = {
	{ "963-j23.j17", 0x20000, 0xf77314e2, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "963-j24.k17", 0x20000, 0x47f662d3, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "963-j21.j15", 0x10000, 0x7bee9fe8, BRF_ESS | BRF_PRG }, //  2            (even)
	{ "963-j22.k15", 0x10000, 0x2efed09f, BRF_ESS | BRF_PRG }, //  3            (odd)

	{ "963a28.h27",  0x80000, 0xdb4769a8, BRF_GRA }, //  4 tile bitmaps
	{ "963a29.k27",  0x80000, 0x8069cd2e, BRF_GRA }, //  5

	{ "963a16.k6",   0x80000, 0xd4bd9984, BRF_GRA }, //  6 sprites
	{ "963a18.h6",   0x80000, 0xdd51adef, BRF_GRA }, //  7
	{ "963a15.k4",   0x80000, 0x1f324eed, BRF_GRA }, //  8
	{ "963a17.h4",   0x80000, 0xb5239a44, BRF_GRA }, //  9

	{ "963e20.g13",  0x08000, 0x1692a6d6, BRF_SND | BRF_PRG }, //  10 Z80 rom

	{ "963a26.c13",  0x20000, 0xe2ac3063, BRF_SND }, //  11 samples (K007232)
	{ "963a27.d18",  0x20000, 0x2dfd674b, BRF_SND }, //  12 samples (UPD7759C)
	{ "963a25.d5",   0x80000, 0xfca078c7, BRF_SND }, //  13 title music sample

	{ "963a30.g7",   0x0100,  0xabd82680, BRF_GRA }, //  14 sprite address decoder
	{ "963a31.g19",  0x0100,  0xf8004a1c, BRF_GRA }, //  15 priority encoder (not used)	
};

STD_ROM_PICK(Tmntua);
STD_ROM_FN(Tmntua);

// ==========================================
// Teenage Mutant Hero Turtles (UK 4 Players)
// ==========================================
static struct BurnRomInfo TmhtRomDesc[] = {
	{ "963-f23.j17", 0x20000, 0x9cb5e461, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "963-f24.k17", 0x20000, 0x2d902fab, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "963-f21.j15", 0x10000, 0x9fa25378, BRF_ESS | BRF_PRG }, //  2            (even)
	{ "963-f22.k15", 0x10000, 0x2127ee53, BRF_ESS | BRF_PRG }, //  3            (odd)

	{ "963a28.h27",  0x80000, 0xdb4769a8, BRF_GRA }, //  4 tile bitmaps
	{ "963a29.k27",  0x80000, 0x8069cd2e, BRF_GRA }, //  5

	{ "963a16.k6",   0x80000, 0xd4bd9984, BRF_GRA }, //  6 sprites
	{ "963a18.h6",   0x80000, 0xdd51adef, BRF_GRA }, //  7
	{ "963a15.k4",   0x80000, 0x1f324eed, BRF_GRA }, //  8
	{ "963a17.h4",   0x80000, 0xb5239a44, BRF_GRA }, //  9

	{ "963e20.g13",  0x08000, 0x1692a6d6, BRF_SND | BRF_PRG }, //  10 Z80 rom

	{ "963a26.c13",  0x20000, 0xe2ac3063, BRF_SND }, //  11 samples (K007232)
	{ "963a27.d18",  0x20000, 0x2dfd674b, BRF_SND }, //  12 samples (UPD7759C)
	{ "963a25.d5",   0x80000, 0xfca078c7, BRF_SND }, //  13 title music sample

	{ "963a30.g7",   0x0100,  0xabd82680, BRF_GRA }, //  14 sprite address decoder
	{ "963a31.g19",  0x0100,  0xf8004a1c, BRF_GRA }, //  15 priority encoder (not used)	
};

STD_ROM_PICK(Tmht);
STD_ROM_FN(Tmht);

// ==============================================
// Teenage Mutant Ninja Turtles (Japan 4 Players)
// ==============================================
static struct BurnRomInfo TmntjRomDesc[] = {
	{ "963_223.j17", 0x20000, 0x0d34a5ff, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "963_224.k17", 0x20000, 0x2fd453f2, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "963_221.j15", 0x10000, 0xfa8e25fd, BRF_ESS | BRF_PRG }, //  2            (even)
	{ "963_222.k15", 0x10000, 0xca437a4f, BRF_ESS | BRF_PRG }, //  3            (odd)

	{ "963a28.h27",  0x80000, 0xdb4769a8, BRF_GRA }, //  4 tile bitmaps
	{ "963a29.k27",  0x80000, 0x8069cd2e, BRF_GRA }, //  5

	{ "963a16.k6",   0x80000, 0xd4bd9984, BRF_GRA }, //  6 sprites
	{ "963a18.h6",   0x80000, 0xdd51adef, BRF_GRA }, //  7
	{ "963a15.k4",   0x80000, 0x1f324eed, BRF_GRA }, //  8
	{ "963a17.h4",   0x80000, 0xb5239a44, BRF_GRA }, //  9

	{ "963e20.g13",  0x08000, 0x1692a6d6, BRF_SND | BRF_PRG }, //  10 Z80 rom

	{ "963a26.c13",  0x20000, 0xe2ac3063, BRF_SND }, //  11 samples (K007232)
	{ "963a27.d18",  0x20000, 0x2dfd674b, BRF_SND }, //  12 samples (UPD7759C)
	{ "963a25.d5",   0x80000, 0xfca078c7, BRF_SND }, //  13 title music sample

	{ "963a30.g7",   0x0100,  0xabd82680, BRF_GRA }, //  14 sprite address decoder
	{ "963a31.g19",  0x0100,  0xf8004a1c, BRF_GRA }, //  15 priority encoder (not used)	
};

STD_ROM_PICK(Tmntj);
STD_ROM_FN(Tmntj);

// =================================================
// Teenage Mutant Hero Turtles (UK 2 Players, set 1)
// =================================================
static struct BurnRomInfo Tmht2pRomDesc[] = {
	{ "963-u23.j17", 0x20000, 0x58bec748, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "963-u24.k17", 0x20000, 0xdce87c8d, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "963-u21.j15", 0x10000, 0xabce5ead, BRF_ESS | BRF_PRG }, //  2            (even)
	{ "963-u22.k15", 0x10000, 0x4ecc8d6b, BRF_ESS | BRF_PRG }, //  3            (odd)

	{ "963a28.h27",  0x80000, 0xdb4769a8, BRF_GRA }, //  4 tile bitmaps
	{ "963a29.k27",  0x80000, 0x8069cd2e, BRF_GRA }, //  5

	{ "963a16.k6",   0x80000, 0xd4bd9984, BRF_GRA }, //  6 sprites
	{ "963a18.h6",   0x80000, 0xdd51adef, BRF_GRA }, //  7
	{ "963a15.k4",   0x80000, 0x1f324eed, BRF_GRA }, //  8
	{ "963a17.h4",   0x80000, 0xb5239a44, BRF_GRA }, //  9

	{ "963e20.g13",  0x08000, 0x1692a6d6, BRF_SND | BRF_PRG }, //  10 Z80 rom

	{ "963a26.c13",  0x20000, 0xe2ac3063, BRF_SND }, //  11 samples (K007232)
	{ "963a27.d18",  0x20000, 0x2dfd674b, BRF_SND }, //  12 samples (UPD7759C)
	{ "963a25.d5",   0x80000, 0xfca078c7, BRF_SND }, //  13 title music sample

	{ "963a30.g7",   0x0100,  0xabd82680, BRF_GRA }, //  14 sprite address decoder
	{ "963a31.g19",  0x0100,  0xf8004a1c, BRF_GRA }, //  15 priority encoder (not used)	
};

STD_ROM_PICK(Tmht2p);
STD_ROM_FN(Tmht2p);

// =================================================
// Teenage Mutant Hero Turtles (UK 2 Players, set 2)
// =================================================
static struct BurnRomInfo Tmht2paRomDesc[] = {
	{ "963-_23.j17", 0x20000, 0x8698061a, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "963-_24.k17", 0x20000, 0x4036c075, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "963-_21.j15", 0x10000, 0xddcc979c, BRF_ESS | BRF_PRG }, //  2            (even)
	{ "963-_22.k15", 0x10000, 0x71a38d27, BRF_ESS | BRF_PRG }, //  3            (odd)

	{ "963a28.h27",  0x80000, 0xdb4769a8, BRF_GRA }, //  4 tile bitmaps
	{ "963a29.k27",  0x80000, 0x8069cd2e, BRF_GRA }, //  5

	{ "963a16.k6",   0x80000, 0xd4bd9984, BRF_GRA }, //  6 sprites
	{ "963a18.h6",   0x80000, 0xdd51adef, BRF_GRA }, //  7
	{ "963a15.k4",   0x80000, 0x1f324eed, BRF_GRA }, //  8
	{ "963a17.h4",   0x80000, 0xb5239a44, BRF_GRA }, //  9

	{ "963e20.g13",  0x08000, 0x1692a6d6, BRF_SND | BRF_PRG }, //  10 Z80 rom

	{ "963a26.c13",  0x20000, 0xe2ac3063, BRF_SND }, //  11 samples (K007232)
	{ "963a27.d18",  0x20000, 0x2dfd674b, BRF_SND }, //  12 samples (UPD7759C)
	{ "963a25.d5",   0x80000, 0xfca078c7, BRF_SND }, //  13 title music sample

	{ "963a30.g7",   0x0100,  0xabd82680, BRF_GRA }, //  14 sprite address decoder
	{ "963a31.g19",  0x0100,  0xf8004a1c, BRF_GRA }, //  15 priority encoder (not used)	
};

STD_ROM_PICK(Tmht2pa);
STD_ROM_FN(Tmht2pa);

// ==============================================
// Teenage Mutant Ninja Turtles (Japan 2 Players)
// ==============================================
static struct BurnRomInfo Tmnt2pjRomDesc[] = {
	{ "963-123.j17", 0x20000, 0x6a3527c9, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "963-124.k17", 0x20000, 0x2c4bfa15, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "963-121.j15", 0x10000, 0x4181b733, BRF_ESS | BRF_PRG }, //  2            (even)
	{ "963-122.k15", 0x10000, 0xc64eb5ff, BRF_ESS | BRF_PRG }, //  3            (odd)

	{ "963a28.h27",  0x80000, 0xdb4769a8, BRF_GRA }, //  4 tile bitmaps
	{ "963a29.k27",  0x80000, 0x8069cd2e, BRF_GRA }, //  5

	{ "963a16.k6",   0x80000, 0xd4bd9984, BRF_GRA }, //  6 sprites
	{ "963a18.h6",   0x80000, 0xdd51adef, BRF_GRA }, //  7
	{ "963a15.k4",   0x80000, 0x1f324eed, BRF_GRA }, //  8
	{ "963a17.h4",   0x80000, 0xb5239a44, BRF_GRA }, //  9

	{ "963e20.g13",  0x08000, 0x1692a6d6, BRF_SND | BRF_PRG }, //  10 Z80 rom

	{ "963a26.c13",  0x20000, 0xe2ac3063, BRF_SND }, //  11 samples (K007232)
	{ "963a27.d18",  0x20000, 0x2dfd674b, BRF_SND }, //  12 samples (UPD7759C)
	{ "963a25.d5",   0x80000, 0xfca078c7, BRF_SND }, //  13 title music sample

	{ "963a30.g7",   0x0100,  0xabd82680, BRF_GRA }, //  14 sprite address decoder
	{ "963a31.g19",  0x0100,  0xf8004a1c, BRF_GRA }, //  15 priority encoder (not used)	
};

STD_ROM_PICK(Tmnt2pj);
STD_ROM_FN(Tmnt2pj);

// ================================================
// Teenage Mutant Ninja Turtles (Oceania 2 Players)
// ================================================
static struct BurnRomInfo Tmnt2poRomDesc[] = {
	{ "tmnt123.j17", 0x20000, 0x2d905183, BRF_ESS | BRF_PRG }, //  0 68000 code (even)
	{ "tmnt124.k17", 0x20000, 0xe0125352, BRF_ESS | BRF_PRG }, //  1            (odd)
	{ "tmnt21.j15",  0x10000, 0x12deeafb, BRF_ESS | BRF_PRG }, //  2            (even)
	{ "tmnt22.k15",  0x10000, 0xaec4f1c3, BRF_ESS | BRF_PRG }, //  3            (odd)

	{ "963a28.h27",  0x80000, 0xdb4769a8, BRF_GRA }, //  4 tile bitmaps
	{ "963a29.k27",  0x80000, 0x8069cd2e, BRF_GRA }, //  5

	{ "963a16.k6",   0x80000, 0xd4bd9984, BRF_GRA }, //  6 sprites
	{ "963a18.h6",   0x80000, 0xdd51adef, BRF_GRA }, //  7
	{ "963a15.k4",   0x80000, 0x1f324eed, BRF_GRA }, //  8
	{ "963a17.h4",   0x80000, 0xb5239a44, BRF_GRA }, //  9

	{ "963e20.g13",  0x08000, 0x1692a6d6, BRF_SND | BRF_PRG }, //  10 Z80 rom

	{ "963a26.c13",  0x20000, 0xe2ac3063, BRF_SND }, //  11 samples (K007232)
	{ "963a27.d18",  0x20000, 0x2dfd674b, BRF_SND }, //  12 samples (UPD7759C)
	{ "963a25.d5",   0x80000, 0xfca078c7, BRF_SND }, //  13 title music sample

	{ "963a30.g7",   0x0100,  0xabd82680, BRF_GRA }, //  14 sprite address decoder
	{ "963a31.g19",  0x0100,  0xf8004a1c, BRF_GRA }, //  15 priority encoder (not used)	
};

STD_ROM_PICK(Tmnt2po);
STD_ROM_FN(Tmnt2po);

int TmntInpMake()
{
	int i=0;
	memset(&TmntAoo,0,sizeof(TmntAoo));

	for (i=0;i<4;i++)
	{
		if (TmntCoin[i]) TmntAoo[0]|=0x01<<i;
		if (TmntService[i]) TmntAoo[0]|=0x10<<i;
		if (TmntStart[i]) *(pPlay[i])|=0x20;
		if (TmntAttack[i]) *(pPlay[i])|=0x20;
		if (TmntJump[i]) *(pPlay[i])|=0x10;
		if (TmntUp[i]) *(pPlay[i])|=0x04;
		if (TmntDown[i]) *(pPlay[i])|=0x08;
		if (TmntLeft[i]) *(pPlay[i])|=0x01;
		if (TmntRight[i])*(pPlay[i])|=0x02;
		if (Tmnt2pStart[i])*(pPlay[i])|=0x80;
	}

	return 0;
}

// This routine is called first to determine how much memory is needed (MemEnd-(unsigned char *)0),
// and then to set up all the pointers
static int MemIndex()
{
	unsigned char *Next; Next=Mem;
	Tmnt68KROM01 = Next;	Next+=0x060000; // 68000 program
	TmntZ80Rom = Next; Next += 0x08000;
	TmntSampleROM01 = Next; Next += 0x020000;
	TmntSampleROM02 = Next; Next += 0x020000;
	TmntSampleROM03 = Next; Next += 0x080000;

	RamStart = Next;
	K051960Ram = Next;	Next+=0x000800; // spr ram
	TmntRam10 = Next;	Next+=0x008000; // tile ram
	TmntRam08 = Next;	Next+=0x001000; // palette
	PriRam = Next;		Next+=0x0100;
  TmntRam06 = Next;	Next+=0x004000;
  TmntZ80Ram = Next; Next += 0x00800;
	RamEnd = Next;

	TmntTile = Next;	Next+=0x100000; // Tile bitmaps
	TmntSprite = Next;	Next+=0x400000; // Tile bitmaps
	MemEnd = Next;
	return 0;
}

static int Interleve2(unsigned char *pd,int i,int nLen)
{
	unsigned char *pt;
	unsigned short *pts,*ptd;
	int a;

	pt=(unsigned char *)malloc(nLen); if (pt==NULL) return 1;
	memset(pt,0,nLen);
	BurnLoadRom(pt,i,1);

	nLen>>=1; pts=(unsigned short *)pt;
	ptd=(unsigned short *)pd;
	for (a=0;a<nLen; a++, pts++, ptd+=2)
		*ptd=*pts;
	free(pt);
	return 0;
}

static int LoadRoms()
{
	int nRet=0;
	// Load program roms and byteswap
	nRet=BurnLoadRom(Tmnt68KROM01+0x00001,0,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(Tmnt68KROM01+0x00000,1,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(Tmnt68KROM01+0x40001,2,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(Tmnt68KROM01+0x40000,3,2); if (nRet!=0) return 1;

	// Load Z80 Program Rom
	nRet=BurnLoadRom(TmntZ80Rom,10,1); if (nRet!=0) return 1;

	// Load tile bitmaps
	Interleve2(TmntTile+0x000000,4,0x80000);
	Interleve2(TmntTile+0x000002,5,0x80000);

	// Load sprites
	TmntSpriteTemp=(unsigned char *)malloc(0x200000);

	Interleve2(TmntSpriteTemp+0x000000,6,0x80000);
	Interleve2(TmntSpriteTemp+0x000002,7,0x80000);
	Interleve2(TmntSpriteTemp+0x100000,8,0x80000);
	Interleve2(TmntSpriteTemp+0x100002,9,0x80000);

	for (int i = 0; i<0x200000;i++)
	{
		TmntSprite[i*2]=(TmntSpriteTemp[i^1] & 0x0F);//((TmntSpriteTemp[i] & 0xF0) >> 4);
		TmntSprite[(i*2)+1]=((TmntSpriteTemp[i^1] & 0xF0) >> 4);//(TmntSpriteTemp[i] & 0x0F);

	}

	free(TmntSpriteTemp);

	// Load samples
	nRet=BurnLoadRom(TmntSampleROM01,11,1); if (nRet!=0) return 1; // K007232
	nRet=BurnLoadRom(TmntSampleROM02,12,1); if (nRet!=0) return 1; // UPD7759C
	nRet=BurnLoadRom(TmntSampleROM03,13,1); if (nRet!=0) return 1;

	return 0;
}

int TmntPalExit()
{
	bAnyDirt=0;
	memset(Dirt   ,0,sizeof(Dirt));    // Mark all colors as clean
	memset(TmntPal,0,sizeof(TmntPal)); // All colors black
	return 0;
}

int TmntPalInit()
{
	TmntPalExit();
	return 0;
}

inline static unsigned int CalcCol(unsigned short *ps,int i)
{
	unsigned int a0,a1; int r,g,b;
	a0=ps[0]; 
	a1=ps[1];
	r =(a1&0x1f)<<3;
	g =(a0&0x03)<<6;
	g|=(a1&0xe0)>>2;
	b =(a0&0x7c)<<1;
	return BurnHighCol(r,g,b,i);
}

int TmntPalUpdate(int bRecalc)
{
	// If any colors have changed, convert them from TmntRam08 into the High palette
	int a; unsigned short *ps; unsigned int *ph; unsigned char *pd;
	if (bRecalc)
	{
		bAnyDirt=1;
		memset(Dirt,0xff,sizeof(Dirt)); // Mark all colors as dirty
	}
	if (!bAnyDirt) 
	{
		return 0; // All the same
	}

	ps=(unsigned short *)TmntRam08; 
	ph=TmntPal; 
	pd=Dirt;
	for (a=0;a<0x80; a++,pd++)
	{
		int b; unsigned char d; unsigned char m; // dirt info and mask
		d=*pd;
		if (d==0) 
		{ 
			ps+=16; 
			ph+=8; 
			continue; 
		} // Not changed

		for (b=0,m=1; b<8; b++,m<<=1, ps+=2,ph++)
		{
		if (d&m) 
			*ph=CalcCol(ps,(a<<3)|b); // If dirty recalculate
		}
		Dirt[a]=0; // Clean now
	}
	bAnyDirt=0; // Clean now
	return 0;
}

// Write a byte to the palette
void TmntPalWrite(unsigned int a,unsigned char d)
{
	a^=1; 
	a&=0xfff; // Clip to palette length
	if (TmntRam08[a]==d) 
		return; // No change
	TmntRam08[a]=d; // write byte

	a>>=2; 
	Dirt[a>>3]|=1<<(a&7);  
	bAnyDirt=1; // Mark this color as changed
}

// Functions for Tiles
// All the code is pretty much stolen from DTMNT and MAME, then hacked till it worked. 
// Thanks to Dave for releasing the source to DMNT and the MAME team
/* Todo:
   Black garbage on the title screen of tmnt 
   add support for zoom
   Rewrite the slow drawing stuff
   Add a bit more flexability to the code to allow other games to work.
   Fix the shadows
   -Kev											*/

void RawTileClip(unsigned int nTile,unsigned int nPal, int xpos, int ypos)
// Draw a background layer with a primitive form of clipping. A pretty slow and rubish function really :)
{
	unsigned int *ps; 
	int y,x;
	unsigned int s;  
	unsigned char *pPix;
	unsigned int *Pal;
	bool draw;
	nPal<<=4; 
	nPal&=0x3f0; 
	Pal=TmntPal+nPal;
	nTile<<=5;  
	if (nTile>=0x300000-0x20) 
		return;

	ps=(unsigned int *)(TmntTile+nTile); 

	for (y=0;y<8; y++,ps++)
	{
		s=*ps;
		pPix=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
		for (x=0; x<8; xpos++ ,x++,pPix+=nBurnBpp,s<<=4)
		{
			draw=1;
			unsigned char p;
			p=(unsigned char)((s>>28)&15);
			if (p)
			{
				if ((xpos>=0)&&(ypos>=0)&&(ypos<224)&&(xpos<304)) {
					*((unsigned int *)pPix)=Pal[p];
				}
			}
		}
		xpos-=8;
		ypos++;
	}
}

// Work out and draw the Fixed/A/B layers
void TmntTileLayer(int nLayer)
{
	unsigned char PalBase[3]={0,0x20,0x28};
	int sx,sy;
	unsigned char *pSrc;
	int nTile;
	int xoff=nScrollX[nLayer];
	int yoff=nScrollY[nLayer];
	int nPal;	
	int p;
	
	int x=0; 
	int y=0;
	for ( y=0; y<29; y++ )
	{
		for ( x=1; x<40; x++ )
		{
			pSrc=TmntRam10+(nLayer<<13);
			sx=x+(xoff>>3); 
			sy=y+(yoff>>3);
			sx&=63; 
			sy&=31;
			pSrc+=(sy<<7)+(sx<<1);
			nTile=*((unsigned short *)pSrc);
			// Get palette
			nPal=(nTile>>13)&7;		
			nPal+=PalBase[nLayer];

			// Get tile page (0-3)
			p=(nTile>>10)&3; 
			nTile=((nTile&0x1000)>>2) | (nTile&0x03ff);
			if (p) 
				nTile+=nPageBase[p];
			if (nTile!=0x10) // blank tile?
				RawTileClip(nTile,nPal,((x-1)*8)-(xoff&7),(y*8)-(yoff&7));
		}
	}
}

int K051960Draw() {
	// Draw the selected sprite. Very Slooooowly.
	unsigned char *temp;
	int x,y;
	int xpos,ypos;
	int TempPix;

	sprite.pal_offset<<=4; 
	sprite.pal_offset&=0x3f0; 

	if (sprite.zoomx == 0x10000 && sprite.zoomy == 0x10000)
	{

		if (sprite.flipx && sprite.flipy)
		{
			for (y=sprite.h-1;y>=0;y--)
			{
   				ypos=sprite.y+y;
				for (x=0;x<(sprite.w);x++)
				{
					xpos=-x+(sprite.x+(sprite.w)-1);
					temp=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
					TempPix=TmntSprite[sprite.number^1];
					sprite.number++;
					if ((xpos>=0)&&(ypos>=0)&&(ypos<224)&&(xpos<304)) 
					{
						if (TempPix) 
						{
							if (TempPix < 15)
							{
								*((unsigned int *)temp)=TmntPal[TempPix+sprite.pal_offset];
							}
							else
							{
								if (*temp==0)
								{
									*((unsigned int *)temp)=TmntPal[TempPix+sprite.pal_offset];
								}
								else
								{
							 		*((unsigned int *)temp)=(*temp & 0x00FEFEFE)>>1;
								}
							}
						}
					}
				}
			}
		}

		else if (sprite.flipy)
		{
			for (y=sprite.h-1;y>=0;y--)
			{
				ypos=sprite.y+y;
				for (x=0;x<(sprite.w);x++)
				{
					xpos=sprite.x+x+1;
					temp=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
					TempPix=TmntSprite[sprite.number^1];
					sprite.number++;
					if ((xpos>=0)&&(ypos>=0)&&(ypos<224)&&(xpos<304)) 
					{
						if (TempPix) 
						{
							if (TempPix < 15)
							{
								*((unsigned int *)temp)=TmntPal[TempPix+sprite.pal_offset];
							}
							else
							{
								if (*temp==0)
								{
									*((unsigned int *)temp)=TmntPal[TempPix+sprite.pal_offset];
								}
								else
								{
							 		*((unsigned int *)temp)=(*temp & 0x00FEFEFE)>>1;
								}
							}
						}
					}
				}
			}
		}

		else if (sprite.flipx)
		{
			for (y=0;y<sprite.h;y++) 
			{
				ypos=sprite.y+y;
				for (x=0;x<(sprite.w);x++)
				{
					xpos=-x+(sprite.x+(sprite.w)-1);
					temp=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
					TempPix=TmntSprite[sprite.number^1];
					sprite.number++;
					if ((xpos>=0)&&(ypos>=0)&&(ypos<224)&&(xpos<304)) 
					{
						if (TempPix) 
						{
							if (TempPix < 15)
							{
								*((unsigned int *)temp)=TmntPal[TempPix+sprite.pal_offset];
							}
							else
							{
								if (*temp==0)
								{
									*((unsigned int *)temp)=TmntPal[TempPix+sprite.pal_offset];
								}
								else
								{
							 		*((unsigned int *)temp)=(*temp & 0x00FEFEFE)>>1;
								}
							}
						}
					}
				}
			}
		}
		else for (y=0;y<sprite.h;y++) 
		{
			for (x=0;x<sprite.w;x++)
			{
				xpos=sprite.x+x;
				ypos=sprite.y+y;
				temp=pBurnDraw + (nBurnPitch * ypos)+(nBurnBpp * xpos);
				TempPix=TmntSprite[sprite.number^1];
				sprite.number++;
				if ((xpos>=0)&&(ypos>=0)&&(ypos<224)&&(xpos<304)) 
				{
					if (TempPix) 
					{
						if (TempPix < 15)
						{
							*((unsigned int *)temp)=TmntPal[TempPix+sprite.pal_offset];
						}
						else
						{
							if (*temp==0)
							{
								*((unsigned int *)temp)=TmntPal[TempPix+sprite.pal_offset];
							}
							else
							{
						 		*((unsigned int *)temp)=(*temp & 0x00FEFEFE)>>1;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

void K051960Decode(int i)
{
  // Decodes a sprite and returns a sprite structure. Partally taken from MAME, DMNT and my imagination
	static int size_table[16] = {16,16,32,16,16,32,32,32,64,32,32,64,64,64,128,128};
	int sproff=0x000000;
	int c=0,offset=0;

	sproff+=i*8;

	if ((K051960Ram[(sproff+0)^1]&0x80)==0) 
		return;   //sprite is not enabled

	sprite.x=(( 256* K051960Ram[(sproff+6)^1] + K051960Ram[(sproff+7)^1]) & 0x01ff)-110;
	sprite.y=240- (( 256* K051960Ram[(sproff+4)^1] + K051960Ram[(sproff+5)^1]) & 0x01ff);

	sprite.zoomx = (K051960Ram[(sproff+6)^1] & 0xfc) >> 2;
	sprite.zoomy = (K051960Ram[(sproff+4)^1] & 0xfc) >> 2;
	sprite.zoomx = 0x10000 / 128 * (128 - sprite.zoomx);
	sprite.zoomy = 0x10000 / 128 * (128 - sprite.zoomy);

	sprite.flipx=(K051960Ram[(sproff+6)^1]&2)?1:0; 
	sprite.flipy=(K051960Ram[(sproff+4)^1]&2)?1:0;  

	// c is the code for the sprite size
	c=(K051960Ram[(sproff+1)^1]>>4)&0xE;  
	sprite.w=size_table[c];
	sprite.h=size_table[c+1];

	offset=(K051960Ram[(sproff+1)^1]&0x1f); 
	offset<<=15;
	offset|=(K051960Ram[(sproff+2)^1]<<7);  

	if (((offset&0x00700)==0x00200)&&(c==0x0a)) offset+=0x200;
	if (((offset&0x001e0)==0x00080)&&(c==0x04)) offset+=0x080;

	offset*=2;

	if (K051960Ram[(sproff+3)^1]&0x10)
		sprite.number=offset;
	else
		sprite.number=0x200000+offset;
	
	sprite.pal_offset=(K051960Ram[(sproff+3)^1]&0x0F)+0x10;  


	if (sprite.number < 0x3FFFC0) // if not a valid sprite so save on the function call.
		K051960Draw();
}

int K051960DrawSprites()
// Maximum of 128 sprites a frame (TMNT only uses 64)
{
	for (int i=128;i>=0;i--){
		K051960Decode(i);
	}
	return 0;
}

int TmntTileDraw()
// This needs a lot of work but basically works out and draws all the graphics for TMNT
{
	int priority;
	unsigned char da,db;
	short s;

	// Get the two tile page decoders
	da=TmntRam10[0x6b00^1];
	db=TmntRam10[0x6e00^1];

	// Find the tile page base for each
                              
	nPageBase[1]=(da&0xf0)<<7;
	nPageBase[2]=(db&0x0f)<<11; 
	nPageBase[3]=(db&0xf0)<<7;


	// Get the scroll-x values
	s =TmntRam10[0x6402^1]; 
	s<<=8;
	s|=TmntRam10[0x6400^1]; 
	s+=12*8; 
	nScrollX[1]=s;
	
	s =TmntRam10[0x6403^1]; 
	s<<=8;
	s|=TmntRam10[0x6401^1]; 
	s+=12*8; 
	nScrollX[2]=s;
	
	// Get the scroll-y values
	s=TmntRam10[0x6018^1];  // ==  vpage[n].offy=MEMB(vidmem,0x006018+n-1); 
	s+=16; 
	nScrollY[1]=s;
	s=TmntRam10[0x6019^1]; 
	s+=16; 
	nScrollY[2]=s;

	count++;

	// Figure out which order to draw everything . . . .
	priority=PriRam[0x00000]&0x04;
	if (!priority)	
	{
		TmntTileLayer(2);
		TmntTileLayer(1);
		K051960DrawSprites();
		TmntTileLayer(0);
	}
	else 	
	{
		TmntTileLayer(2);
		K051960DrawSprites();
		TmntTileLayer(1);
		TmntTileLayer(0);
	}

  return 0;
}

// Z80 accesses
unsigned char __fastcall tmntZ80In(unsigned short wordValue)
{
	printf("\nZ80: read from port %x",wordValue);
	return 0;
}

void __fastcall tmntZ80Out(unsigned short wordValue,unsigned char val)
{
	printf("\nZ80: Write %x to port %x",val,wordValue);
}

unsigned char __fastcall tmntZ80Read(unsigned short wordValue)
{
	if (wordValue==0x9000)
	{
		//printf("\nZ80: tmnt_sres_r");
	}
	if (wordValue==0xa000)
	{
		//ZetRaiseIrq(1);
		return tmnt_soundlatch;
	//	printf("\nZ80: read from soundlatch");
	}
	if ((wordValue>=0xb000) && (wordValue<=0xb00d))
	{
	//	printf("\nZ80: read from K007232 %d",0xb000 - wordValue);
	}
	if (wordValue==0xc001)
	{
		return BurnYM2151ReadStatus();
	//	printf("\nZ80: YM2151 status read");
	}
	if (wordValue==0xf000)
	{
	//	printf("\nZ80: UDP7759 busy read");
	}
	return 0;
}


void tmntYM2151IRQHandler(int irq)
{
	//if (irq)
	{
		ZetSetIRQLine(1, ZET_IRQSTATUS_AUTO);
	}
//	else
	{
//		ZetSetIRQLine(1, ZET_IRQSTATUS_ACK);
	}

}


void __fastcall tmntZ80Write(unsigned short wordValue,unsigned char val)
{
	if (wordValue==0x9000)
	{
		tmnt_soundlatch = val;
	}
	if ((wordValue>=0xb000) && (wordValue<=0xb00d))
	{
//		printf("\nZ80: write %d to K007232 %d",val,0xb000 - wordValue);
		//ZetNmi();
	//	ZetLowerIrq();
	}
	if (wordValue==0xc000)
	{
		BurnYM2151SelectRegister(val);
	}
	if (wordValue==0xc001)
	{
		BurnYM2151WriteRegister(val);
	}
	if (wordValue==0xd000)
	{
//		printf("\nZ80: write %d to UPD7759_0_message", val);
	}
	if (wordValue==0xe000)
	{
//		printf("\nZ80: write %d to UPD7759_0_start", val);
	}
}
// end of z80 accesses

unsigned short __fastcall TmntReadWord(unsigned int sekAddress)
{
	return 0;
}

void __fastcall TmntWriteWord(unsigned int sekAddress, unsigned short wordValue)
{
	switch (sekAddress) {
		default: {
			bprintf(PRINT_NORMAL, _T("TmntWriteWord: value %x to location %x\n"), wordValue, sekAddress);
		}
	}
}


unsigned char __fastcall TmntReadByte(unsigned int a)
{
	if (a>=0x0a0010 && a<0x0a0012)
	{
		return 0xff - TmntDip[0]; // Dip 1
	}
	if (a>=0x0a0012 && a<0x0a0014)
	{
		return 0xff - TmntDip[1]; // Dip 2
	}
	if (a>=0xa0000 && a<0xa0016)
	{
		return (unsigned char)(~TmntAoo[(a>>1)&0xf]);
	}
	if (a>=0x0a0018 && a<0x0a0020)
	{
		return 0xff - TmntDip[2]; // Dip 3
	}
		return 0;
}
/*
static ADDRESS_MAP_START( tmnt_writemem, ADDRESS_SPACE_PROGRAM, 16 )

	AM_RANGE(0x0a0000, 0x0a0001) AM_WRITE(tmnt_0a0000_w)
	AM_RANGE(0x0a0008, 0x0a0009) AM_WRITE(tmnt_sound_command_w)
	AM_RANGE(0x0a0010, 0x0a0011) AM_WRITE(watchdog_reset16_w)
//  AM_RANGE(0x10e800, 0x10e801) AM_WRITE(MWA16_NOP) ???
	AM_RANGE(0x140000, 0x140007) AM_WRITE(K051937_word_w)
ADDRESS_MAP_END
*/
void __fastcall TmntWriteByte(unsigned int a,unsigned char d)
{
	unsigned int ab;
	ab=(a>>16)&0xff;
	if (ab==0x08)
	{
		TmntPalWrite(a,d);
		return;
	} // Palette write

	switch (a)
	{
	case 0xa0001:
		{
		if (d&0x20) 
		{
			bInt5=1;
		}
		else 
		{
			bInt5=0;
		}
		return;
		}
	case 0x0a0011:  // watchdog reset
		return;
	case 0x0a0009: // sound code
		tmnt_soundlatch = d&0xFF;
		return;
	default:
		bprintf(PRINT_NORMAL, _T("TmntWriteByte: value %x to location %x\n"), d, a);
		break;

	}

}

static int TmntDraw()
{
	TmntPalUpdate(bTmntRecalcPal); // Recalc whole pal if needed
	bTmntRecalcPal=0;
	BurnClearScreen();
	TmntTileDraw();

	return 0;
}

void TmntReset()
{
	bInt5=0;
	tmnt_soundlatch = 0;
	BurnYM2151Reset();
	SekOpen(0);
	SekReset();
	SekClose();

	ZetOpen(0);
	ZetReset();
	ZetClose();
}

int TmntFrame()
{
	int nInterleave = 16;
	if (DrvReset)
	{
		TmntReset();
	}
	TmntInpMake();

	nCyclesTotal[0] = 8000000/60;							
	nCyclesTotal[1] = 3579545/60;
	nCyclesDone[0] = nCyclesDone[1] = 0;
	int nSoundBufferPos = 0;

	SekOpen(0);
	ZetOpen(0);
	if (bInt5)
	{
		SekSetIRQLine(5, SEK_IRQSTATUS_AUTO);
	}
	for (int i = 0; i < nInterleave; i++) {
    	int nCurrentCPU;
		int nNext;
		// Run 68000
		nCurrentCPU = 0;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;

		nCyclesSegment = nNext - nCyclesDone[nCurrentCPU];
		if (!CheckSleep(nCurrentCPU)) {					// See if this CPU is busywaiting
			nCyclesDone[nCurrentCPU] += SekRun(nCyclesSegment);
		} else {
			nCyclesDone[nCurrentCPU] += nCyclesSegment;
		}
		// Run Z80
		nCurrentCPU = 1;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nCyclesDone[nCurrentCPU];
		nCyclesSegment = ZetRun(nCyclesSegment);
		nCyclesDone[nCurrentCPU] += nCyclesSegment;

		{
			// Render sound segment
			if (pBurnSoundOut) {
				int nSegmentLength = nBurnSoundLen / nInterleave;
				short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);
				BurnYM2151Render(pSoundBuf, nSegmentLength);
				nSoundBufferPos += nSegmentLength;
			}
		}
	}

	{
		// Make sure the buffer is entirely filled.
		if (pBurnSoundOut) {
			int nSegmentLength = nBurnSoundLen - nSoundBufferPos;
			short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);
			if (nSegmentLength) {
				BurnYM2151Render(pSoundBuf, nSegmentLength);
			}
		}
	}

	ZetClose();
	SekClose();

	if (pBurnDraw) {
		TmntDraw();														// Draw screen if needed
	}

	return 0;
}

static int TmntScan(int nAction,int *pnMin)
{
	struct BurnArea ba;

	if (pnMin) {						// Return minimum compatible version
		*pnMin = 0x029521;
	}

	if (nAction & ACB_MEMORY_RAM) {		// Scan volatile ram

		memset(&ba,0,sizeof(ba));
		ba.Data=RamStart;
		ba.nLen=RamEnd-RamStart;
		ba.szName="All Ram";
		BurnAcb(&ba);
	}

	if (nAction & ACB_DRIVER_DATA) {
		SekScan(nAction);  // scan 68000 states
//		ZetScan(nAction);	 // Scan Z80

		BurnYM2151Scan(nAction);

		SCAN_VAR(tmnt_soundlatch);
		SCAN_VAR(bInt5);
		SCAN_VAR(nCyclesDone);
		SCAN_VAR(nCyclesTotal);
		SCAN_VAR(nCyclesSegment);
		SCAN_VAR(TmntPal);		
	}
	return 0;
}

int TmntInit()
{
	int nRet=0; int nLen=0;

	// Find out how much memory is needed
	Mem=NULL;
	MemIndex();
	nLen=MemEnd-(unsigned char *)0;
	Mem=(unsigned char *)malloc(nLen);
	if (Mem==NULL)
		return 1;
	memset(Mem,0,nLen); // blank all memory
	MemIndex(); // Index the allocated memory

	nRet=LoadRoms();
	if (nRet!=0)
		return 1; // Load the roms into memory

  SekInit(0,0x68000);	// Allocate 68000
	SekOpen(0);

	// Map in memory:
	// ----------------- Cpu 1 ------------------------
	SekMapMemory(Tmnt68KROM01, 0x000000,0x05ffff, SM_ROM); // 68000 Rom
	SekMapMemory(TmntRam06,    0x060000,0x063fff, SM_RAM);
	SekMapMemory(TmntRam08,    0x080000,0x080fff, SM_ROM); // Write goes through handler
	SekMapMemory(PriRam,       0x0c0000,0x0c00ff, SM_RAM);
	SekMapMemory(TmntRam10,    0x100000,0x107fff, SM_RAM);
	SekMapMemory(K051960Ram,   0x140400,0x1407ff, SM_RAM);

	SekSetReadWordHandler(0,TmntReadWord);
	SekSetWriteWordHandler(0,TmntWriteWord);
	SekSetReadByteHandler(0,TmntReadByte);
	SekSetWriteByteHandler(0,TmntWriteByte);
	// ------------------------------------------------
	SekReset();
	SekClose();

	// Setup the Z80 emulation
	ZetInit(1);
	ZetOpen(0);
	ZetMapArea(0x0000, 0x7fff, 0, TmntZ80Rom);
	ZetMapArea(0x0000, 0x7fff, 2, TmntZ80Rom);
	ZetMapArea(0x8000, 0x87ff, 0, TmntZ80Ram);
	ZetMapArea(0x8000, 0x87ff, 1, TmntZ80Ram);
	ZetMapArea(0x8000, 0x87ff, 2, TmntZ80Ram);
	ZetMemEnd();
	ZetSetInHandler(tmntZ80In);
	ZetSetOutHandler(tmntZ80Out);
	ZetSetReadHandler(tmntZ80Read);
	ZetSetWriteHandler(tmntZ80Write);
	ZetReset();
	ZetClose();

	// sound stuff
	// ym2151
  BurnYM2151Init(3579545, 50.0);
	BurnYM2151SetIrqHandler(&tmntYM2151IRQHandler);
	BurnYM2151Reset();

	bInt5=0;
	TmntPalInit();
	return 0;
}

int TmntExit()
{
	TmntPalExit();
	BurnYM2151Exit();
	SekExit(); // Deallocate 68000
	ZetExit();
	// Deallocate all used memory
	free(Mem);
	Mem = NULL;

	return 0;
}

struct BurnDriverD BurnDrvTmnt={
	"tmnt",NULL,NULL,"1989",
	"Teenage Mutant Ninja Turtles (World 4 Players)\0","Preliminary driver","Konami","Konami 68000 bassed",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,4,HARDWARE_MISC_MISC,
	NULL,TmntRomInfo,TmntRomName,TmntInputInfo, TmntDIPInfo,
	TmntInit,TmntExit,TmntFrame,NULL,TmntScan,
	&bTmntRecalcPal,304,224,4,3
};

struct BurnDriverD BurnDrvTmntu={
	"tmntu","tmnt",NULL,"1989",
	"Teenage Mutant Ninja Turtles (US 4 Players, set 1)\0","Preliminary driver","Konami","Konami 68000 bassed",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_MISC_MISC,
	NULL,TmntuRomInfo,TmntuRomName,TmntInputInfo, TmntDIPInfo,
	TmntInit,TmntExit,TmntFrame,NULL,TmntScan,
	&bTmntRecalcPal,304,224,4,3
};

struct BurnDriverD BurnDrvTmntua={
	"tmntua","tmnt",NULL,"1989",
	"Teenage Mutant Ninja Turtles (US 4 Players, set 2)\0","Preliminary driver","Konami","Konami 68000 bassed",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_MISC_MISC,
	NULL,TmntuaRomInfo,TmntuaRomName,TmntInputInfo, TmntDIPInfo,
	TmntInit,TmntExit,TmntFrame,NULL,TmntScan,
	&bTmntRecalcPal,304,224,4,3
};

struct BurnDriverD BurnDrvTmht={
	"tmht","tmnt",NULL,"1989",
	"Teenage Mutant Hero Turtles (UK 4 Players)\0","Preliminary driver","Konami","Konami 68000 bassed",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_MISC_MISC,
	NULL,TmhtRomInfo,TmhtRomName,TmntInputInfo, TmntDIPInfo,
	TmntInit,TmntExit,TmntFrame,NULL,TmntScan,
	&bTmntRecalcPal,304,224,4,3
};

struct BurnDriverD BurnDrvTmntj={
	"tmntj","tmnt",NULL,"1990",
	"Teenage Mutant Ninja Turtles (Japan 4 Players) \0","Preliminary driver","Konami","Konami 68000 bassed",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_MISC_MISC,
	NULL,TmntjRomInfo,TmntjRomName,TmntInputInfo, TmntDIPInfo,
	TmntInit,TmntExit,TmntFrame,NULL,TmntScan,
	&bTmntRecalcPal,304,224,4,3
};

struct BurnDriverD BurnDrvTmht2p={
	"tmht2p","tmnt",NULL,"1989",
	"Teenage Mutant Hero Turtles (UK 2 Players, set 1)\0","Preliminary driver","Konami","Konami 68000 bassed",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_MISC_MISC,
	NULL,Tmht2pRomInfo,Tmht2pRomName,Tmnt2pInputInfo, Tmnt2pDIPInfo,
	TmntInit,TmntExit,TmntFrame,NULL,TmntScan,
	&bTmntRecalcPal,304,224,4,3
};

struct BurnDriverD BurnDrvTmht2pa={
	"tmht2pa","tmnt",NULL,"1989",
	"Teenage Mutant Hero Turtles (UK 2 Players, set 2)\0","Preliminary driver","Konami","Konami 68000 bassed",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_MISC_MISC,
	NULL,Tmht2paRomInfo,Tmht2paRomName,Tmnt2pInputInfo, Tmnt2pDIPInfo,
	TmntInit,TmntExit,TmntFrame,NULL,TmntScan,
	&bTmntRecalcPal,304,224,4,3
};

struct BurnDriverD BurnDrvTmnt2pj={
	"tmnt2pj","tmnt",NULL,"1990",
	"Teenage Mutant Ninja Turtles (Japan 2 Players)\0","Preliminary driver","Konami","Konami 68000 bassed",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_MISC_MISC,
	NULL,Tmnt2pjRomInfo,Tmnt2pjRomName,Tmnt2pInputInfo, Tmnt2pDIPInfo,
	TmntInit,TmntExit,TmntFrame,NULL,TmntScan,
	&bTmntRecalcPal,304,224,4,3
};

struct BurnDriverD BurnDrvTmnt2po={
	"tmnt2po","tmnt",NULL,"1989",
	"Teenage Mutant Ninja Turtles (Oceania 2 Players)\0","Preliminary driver","Konami","Konami 68000 bassed",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_MISC_MISC,
	NULL,Tmnt2poRomInfo,Tmnt2poRomName,Tmnt2pInputInfo, Tmnt2pDIPInfo,
	TmntInit,TmntExit,TmntFrame,NULL,TmntScan,
	&bTmntRecalcPal,304,224,4,3
};
