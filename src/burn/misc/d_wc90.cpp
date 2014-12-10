// FB Alpha - World Cup '90 driver

#include "tiles_generic.h"
#include "burn_ym2608.h"

static unsigned char Wc90InputPort0[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char Wc90InputPort1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char Wc90InputPort2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char Wc90Dip[2]        = {0, 0};
static unsigned char Wc90Input[3]      = {0x00, 0x00, 0x00};
static unsigned char Wc90Reset         = 0;

static unsigned char *Mem              = NULL;
static unsigned char *MemEnd           = NULL;
static unsigned char *RamStart         = NULL;
static unsigned char *RamEnd           = NULL;
static unsigned char *Wc90Z80Rom1      = NULL;
static unsigned char *Wc90Z80Rom2      = NULL;
static unsigned char *Wc90Z80Rom3      = NULL;
static unsigned char *Wc90Z80Ram1      = NULL;
static unsigned char *Wc90Z80Ram2      = NULL;
static unsigned char *Wc90Z80Ram3      = NULL;
static unsigned char *Wc90FgVideoRam   = NULL;
static unsigned char *Wc90BgVideoRam   = NULL;
static unsigned char *Wc90TextVideoRam = NULL;
static unsigned char *Wc90SpriteRam    = NULL;
static unsigned char *Wc90PaletteRam   = NULL;
static unsigned char *Wc90SharedRam    = NULL;
static unsigned int  *Wc90Palette      = NULL;
static unsigned char *Wc90CharTiles    = NULL;
static unsigned char *Wc90BgTiles      = NULL;
static unsigned char *Wc90FgTiles      = NULL;
static unsigned char *Wc90Sprites      = NULL;
static unsigned char *Wc90TempGfx      = NULL;
static unsigned char *Wc90YM2608Rom    = NULL;

static int Wc90Scroll0YLo;
static int Wc90Scroll0YHi;
static int Wc90Scroll0XLo;
static int Wc90Scroll0XHi;
static int Wc90Scroll1YLo;
static int Wc90Scroll1YHi;
static int Wc90Scroll1XLo;
static int Wc90Scroll1XHi;
static int Wc90Scroll2YLo;
static int Wc90Scroll2YHi;
static int Wc90Scroll2XLo;
static int Wc90Scroll2XHi;

static int Wc90SoundLatch = 0;

static int nCyclesDone[3], nCyclesTotal[3];
static int nCyclesSegment;

static int nTileType;

// Input definitions and functions
static struct BurnInputInfo Wc90InputList[] =
{
	{"Coin 1"            , BIT_DIGITAL  , Wc90InputPort2 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , Wc90InputPort2 + 2, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL  , Wc90InputPort2 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , Wc90InputPort2 + 3, "p2 start"  },

	{"P1 Up"             , BIT_DIGITAL  , Wc90InputPort0 + 0, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , Wc90InputPort0 + 1, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , Wc90InputPort0 + 2, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , Wc90InputPort0 + 3, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , Wc90InputPort0 + 4, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL  , Wc90InputPort0 + 5, "p1 fire 2" },

	{"P2 Up"             , BIT_DIGITAL  , Wc90InputPort1 + 0, "p2 up"     },
	{"P2 Down"           , BIT_DIGITAL  , Wc90InputPort1 + 1, "p2 down"   },
	{"P2 Left"           , BIT_DIGITAL  , Wc90InputPort1 + 2, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL  , Wc90InputPort1 + 3, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , Wc90InputPort1 + 4, "p2 fire 1" },
	{"P2 Fire 2"         , BIT_DIGITAL  , Wc90InputPort1 + 5, "p2 fire 2" },

	{"Reset"             , BIT_DIGITAL  , &Wc90Reset        , "reset"     },
	{"Dip 1"             , BIT_DIPSWITCH, Wc90Dip + 0       , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH, Wc90Dip + 1       , "dip"       },
};

STDINPUTINFO(Wc90);

inline void Wc90ClearOpposites(unsigned char* nJoystickInputs)
{
	if ((*nJoystickInputs & 0x03) == 0x03) {
		*nJoystickInputs &= ~0x03;
	}
	if ((*nJoystickInputs & 0x0c) == 0x0c) {
		*nJoystickInputs &= ~0x0c;
	}
}

inline void Wc90MakeInputs()
{
	// Reset Inputs
	Wc90Input[0] = Wc90Input[1] = Wc90Input[2] = 0x00;

	// Compile Digital Inputs
	for (int i = 0; i < 8; i++) {
		Wc90Input[0] |= (Wc90InputPort0[i] & 1) << i;
		Wc90Input[1] |= (Wc90InputPort1[i] & 1) << i;
		Wc90Input[2] |= (Wc90InputPort2[i] & 1) << i;
	}

	// Clear Opposites
	Wc90ClearOpposites(&Wc90Input[0]);
	Wc90ClearOpposites(&Wc90Input[1]);
}

// Dip Switch definitions
static struct BurnDIPInfo Wc90DIPList[]=
{
	// Default Values
	{0x11, 0xff, 0xff, 0xff, NULL                     },
	{0x12, 0xff, 0xff, 0x7f, NULL                     },

	// Dip 1
	{0   , 0xfe, 0   , 16  , "Coinage"                },
	{0x11, 0x01, 0x0f, 0x00, "10 Coins 1 Credit"      },
	{0x11, 0x01, 0x0f, 0x08, " 9 Coins 1 Credit"      },
	{0x11, 0x01, 0x0f, 0x04, " 8 Coins 1 Credit"      },
	{0x11, 0x01, 0x0f, 0x0c, " 7 Coins 1 Credit"      },
	{0x11, 0x01, 0x0f, 0x02, " 6 Coins 1 Credit"      },
	{0x11, 0x01, 0x0f, 0x0a, " 5 Coins 1 Credit"      },
	{0x11, 0x01, 0x0f, 0x06, " 4 Coins 1 Credit"      },
	{0x11, 0x01, 0x0f, 0x0e, " 3 Coins 1 Credit"      },
	{0x11, 0x01, 0x0f, 0x01, " 2 Coins 3 Credits"     },
	{0x11, 0x01, 0x0f, 0x09, " 2 Coins 1 Credit"      },
	{0x11, 0x01, 0x0f, 0x0f, " 1 Coin  1 Credit"      },
	{0x11, 0x01, 0x0f, 0x07, " 1 Coin  2 Credits"     },
	{0x11, 0x01, 0x0f, 0x0b, " 1 Coin  3 Credits"     },
	{0x11, 0x01, 0x0f, 0x03, " 1 Coin  4 Credits"     },
	{0x11, 0x01, 0x0f, 0x0d, " 1 Coin  5 Credits"     },
	{0x11, 0x01, 0x0f, 0x05, " 1 Coin  6 Credits"     },

	{0   , 0xfe, 0   , 4   , "Difficulty"             },
	{0x11, 0x01, 0x30, 0x30, "Easy"                   },
	{0x11, 0x01, 0x30, 0x10, "Normal"                 },
	{0x11, 0x01, 0x30, 0x20, "Hard"                   },
	{0x11, 0x01, 0x30, 0x00, "Hardest"                },

	{0   , 0xfe, 0   , 2   , "Countdown Speed"        },
	{0x11, 0x01, 0x40, 0x40, "Normal"                 },
	{0x11, 0x01, 0x40, 0x00, "Fast"                   },

	{0   , 0xfe, 0   , 2   , "Demo Sounds"            },
	{0x11, 0x01, 0x80, 0x00, "Off"                    },
	{0x11, 0x01, 0x80, 0x80, "On"                     },

	// Dip 2
	{0   , 0xfe, 0   , 4   , "1 Player Game Time"     },
	{0x12, 0x01, 0x03, 0x01, "1:00"                   },
	{0x12, 0x01, 0x03, 0x02, "1:30"                   },
	{0x12, 0x01, 0x03, 0x03, "2:00"                   },
	{0x12, 0x01, 0x03, 0x00, "2:30"                   },

	{0   , 0xfe, 0   , 8   , "2 Players Game Time"    },
	{0x12, 0x01, 0x1c, 0x0c, "1:00"                   },
	{0x12, 0x01, 0x1c, 0x14, "1:30"                   },
	{0x12, 0x01, 0x1c, 0x04, "2:00"                   },
	{0x12, 0x01, 0x1c, 0x18, "2:30"                   },
	{0x12, 0x01, 0x1c, 0x1c, "3:00"                   },
	{0x12, 0x01, 0x1c, 0x08, "3:30"                   },
	{0x12, 0x01, 0x1c, 0x10, "4:00"                   },
	{0x12, 0x01, 0x1c, 0x00, "5:00"                   },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x12, 0x01, 0x20, 0x20, "Off"                    },
//	{0x12, 0x01, 0x20, 0x00, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x12, 0x01, 0x40, 0x40, "Off"                    },
//	{0x12, 0x01, 0x40, 0x00, "On"                     },

	{0   , 0xfe, 0   , 2   , "Language"               },
	{0x12, 0x01, 0x80, 0x00, "English"                },
	{0x12, 0x01, 0x80, 0x80, "Japanese"               },
};

STDDIPINFO(Wc90);

// Rom definitions
static struct BurnRomInfo Wc90RomDesc[] = {
	{ "ic87_01.bin",   0x08000, 0x4a1affbc, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "ic95_02.bin",   0x10000, 0x847d439c, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code

	{ "ic67_04.bin",   0x10000, 0xdc6eaf00, BRF_ESS | BRF_PRG }, //  2	Z80 #2 Program Code
	{ "ic56_03.bin",   0x10000, 0x1ac02b3b, BRF_ESS | BRF_PRG }, //  3	Z80 #2 Program Code

	{ "ic54_05.bin",   0x10000, 0x27c348b3, BRF_ESS | BRF_PRG }, //  4	Z80 #3 Program Code

	{ "ic85_07v.bin",  0x10000, 0xc5219426, BRF_GRA },			 //  5	Characters
	{ "ic86_08v.bin",  0x20000, 0x8fa1a1ff, BRF_GRA },			 //  6	Fg Tiles
	{ "ic90_09v.bin",  0x20000, 0x99f8841c, BRF_GRA },			 //  7	Fg Tiles
	{ "ic87_10v.bin",  0x20000, 0x8232093d, BRF_GRA },			 //  8	Bg Tiles
	{ "ic91_11v.bin",  0x20000, 0x188d3789, BRF_GRA },			 //  9	Bg Tiles
	{ "ic50_12v.bin",  0x20000, 0xda1fe922, BRF_GRA },			 //  10	Sprites
	{ "ic54_13v.bin",  0x20000, 0x9ad03c2c, BRF_GRA },			 //  11	Sprites
	{ "ic60_14v.bin",  0x20000, 0x499dfb1b, BRF_GRA },			 //  12	Sprites
	{ "ic65_15v.bin",  0x20000, 0xd8ea5c81, BRF_GRA },			 //  13	Sprites

	{ "ic82_06.bin",   0x20000, 0x2fd692ed, BRF_SND },			 //  14	ADPCM Samples
};


STD_ROM_PICK(Wc90);
STD_ROM_FN(Wc90);

static struct BurnRomInfo Wc90aRomDesc[] = {
	{ "wc90-1.bin",    0x08000, 0xd1804e1a, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "ic95_02.bin",   0x10000, 0x847d439c, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code

	{ "ic67_04.bin",   0x10000, 0xdc6eaf00, BRF_ESS | BRF_PRG }, //  2	Z80 #2 Program Code
	{ "ic56_03.bin",   0x10000, 0x1ac02b3b, BRF_ESS | BRF_PRG }, //  3	Z80 #2 Program Code

	{ "ic54_05.bin",   0x10000, 0x27c348b3, BRF_ESS | BRF_PRG }, //  4	Z80 #3 Program Code

	{ "ic85_07v.bin",  0x10000, 0xc5219426, BRF_GRA },			 //  5	Characters
	{ "ic86_08v.bin",  0x20000, 0x8fa1a1ff, BRF_GRA },			 //  6	Fg Tiles
	{ "ic90_09v.bin",  0x20000, 0x99f8841c, BRF_GRA },			 //  7	Fg Tiles
	{ "ic87_10v.bin",  0x20000, 0x8232093d, BRF_GRA },			 //  8	Bg Tiles
	{ "ic91_11v.bin",  0x20000, 0x188d3789, BRF_GRA },			 //  9	Bg Tiles
	{ "ic50_12v.bin",  0x20000, 0xda1fe922, BRF_GRA },			 //  10	Sprites
	{ "ic54_13v.bin",  0x20000, 0x9ad03c2c, BRF_GRA },			 //  11	Sprites
	{ "ic60_14v.bin",  0x20000, 0x499dfb1b, BRF_GRA },			 //  12	Sprites
	{ "ic65_15v.bin",  0x20000, 0xd8ea5c81, BRF_GRA },			 //  13	Sprites

	{ "ic82_06.bin",   0x20000, 0x2fd692ed, BRF_SND },			 //  14	ADPCM Samples
};


STD_ROM_PICK(Wc90a);
STD_ROM_FN(Wc90a);

static struct BurnRomInfo Wc90tRomDesc[] = {
	{ "wc90a-1.bin",   0x08000, 0xb6f51a68, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "wc90a-2.bin",   0x10000, 0xc50f2a98, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code

	{ "ic67_04.bin",   0x10000, 0xdc6eaf00, BRF_ESS | BRF_PRG }, //  2	Z80 #2 Program Code
	{ "wc90a-3.bin",   0x10000, 0x8c7a9542, BRF_ESS | BRF_PRG }, //  3	Z80 #2 Program Code

	{ "ic54_05.bin",   0x10000, 0x27c348b3, BRF_ESS | BRF_PRG }, //  4	Z80 #3 Program Code

	{ "ic85_07v.bin",  0x10000, 0xc5219426, BRF_GRA },			 //  5	Characters
	{ "ic86_08v.bin",  0x20000, 0x8fa1a1ff, BRF_GRA },			 //  6	Fg Tiles
	{ "ic90_09v.bin",  0x20000, 0x99f8841c, BRF_GRA },			 //  7	Fg Tiles
	{ "ic87_10v.bin",  0x20000, 0x8232093d, BRF_GRA },			 //  8	Bg Tiles
	{ "ic91_11v.bin",  0x20000, 0x188d3789, BRF_GRA },			 //  9	Bg Tiles
	{ "ic50_12v.bin",  0x20000, 0xda1fe922, BRF_GRA },			 //  10	Sprites
	{ "ic54_13v.bin",  0x20000, 0x9ad03c2c, BRF_GRA },			 //  11	Sprites
	{ "ic60_14v.bin",  0x20000, 0x499dfb1b, BRF_GRA },			 //  12	Sprites
	{ "ic65_15v.bin",  0x20000, 0xd8ea5c81, BRF_GRA },			 //  13	Sprites

	{ "ic82_06.bin",   0x20000, 0x2fd692ed, BRF_SND },			 //  14	ADPCM Samples
};


STD_ROM_PICK(Wc90t);
STD_ROM_FN(Wc90t);

// Gfx decode functions
void Wc90Decode8x8Tiles(unsigned char *pTile, int Num)
{
	int c, y;

	for (c= 0; c < Num; c++) {
		for (y = 0; y < 8; y++) {
			pTile[(c * 64) + (y * 8) + 0] = Wc90TempGfx[0x00000 + (y * 4) + (c * 32)] >> 4;
			pTile[(c * 64) + (y * 8) + 1] = Wc90TempGfx[0x00000 + (y * 4) + (c * 32)] & 0x0f;
			pTile[(c * 64) + (y * 8) + 2] = Wc90TempGfx[0x00001 + (y * 4) + (c * 32)] >> 4;
			pTile[(c * 64) + (y * 8) + 3] = Wc90TempGfx[0x00001 + (y * 4) + (c * 32)] & 0x0f;
			pTile[(c * 64) + (y * 8) + 4] = Wc90TempGfx[0x00002 + (y * 4) + (c * 32)] >> 4;
			pTile[(c * 64) + (y * 8) + 5] = Wc90TempGfx[0x00002 + (y * 4) + (c * 32)] & 0x0f;
			pTile[(c * 64) + (y * 8) + 6] = Wc90TempGfx[0x00003 + (y * 4) + (c * 32)] >> 4;
			pTile[(c * 64) + (y * 8) + 7] = Wc90TempGfx[0x00003 + (y * 4) + (c * 32)] & 0x0f;
		}
	}
}

void Wc90Decode16x16Tiles(unsigned char *pTile, int Num)
{
	int c, y;

	for (c = 0; c < Num; c++) {
		for (y = 0; y < 8; y++) {
			pTile[(c * 256) + (y * 16) +  0] = Wc90TempGfx[0x00000 + (y * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  1] = Wc90TempGfx[0x00000 + (y * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  2] = Wc90TempGfx[0x00001 + (y * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  3] = Wc90TempGfx[0x00001 + (y * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  4] = Wc90TempGfx[0x00002 + (y * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  5] = Wc90TempGfx[0x00002 + (y * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  6] = Wc90TempGfx[0x00003 + (y * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  7] = Wc90TempGfx[0x00003 + (y * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  8] = Wc90TempGfx[0x00020 + (y * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  9] = Wc90TempGfx[0x00020 + (y * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 10] = Wc90TempGfx[0x00021 + (y * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) + 11] = Wc90TempGfx[0x00021 + (y * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 12] = Wc90TempGfx[0x00022 + (y * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) + 13] = Wc90TempGfx[0x00022 + (y * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 14] = Wc90TempGfx[0x00023 + (y * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) + 15] = Wc90TempGfx[0x00023 + (y * 4) + (c * 128)] & 0x0f;
		}

		for (y = 8; y < 16; y++) {
			pTile[(c * 256) + (y * 16) +  0] = Wc90TempGfx[0x00000 + ((y + 8) * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  1] = Wc90TempGfx[0x00000 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  2] = Wc90TempGfx[0x00001 + ((y + 8) * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  3] = Wc90TempGfx[0x00001 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  4] = Wc90TempGfx[0x00002 + ((y + 8) * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  5] = Wc90TempGfx[0x00002 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  6] = Wc90TempGfx[0x00003 + ((y + 8) * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  7] = Wc90TempGfx[0x00003 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  8] = Wc90TempGfx[0x00020 + ((y + 8) * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  9] = Wc90TempGfx[0x00020 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 10] = Wc90TempGfx[0x00021 + ((y + 8) * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) + 11] = Wc90TempGfx[0x00021 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 12] = Wc90TempGfx[0x00022 + ((y + 8) * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) + 13] = Wc90TempGfx[0x00022 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 14] = Wc90TempGfx[0x00023 + ((y + 8) * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) + 15] = Wc90TempGfx[0x00023 + ((y + 8) * 4) + (c * 128)] & 0x0f;
		}
	}
}

void Wc90DecodeSprites(unsigned char *pTile, int Num)
{
	int c, y;

	for (c = 0; c < Num; c++) {
		for (y = 0; y < 8; y++) {
			pTile[(c * 256) + (y * 16) +  0] = Wc90TempGfx[0x00000 + (y * 2) + (c * 64)] >> 4;
			pTile[(c * 256) + (y * 16) +  1] = Wc90TempGfx[0x00000 + (y * 2) + (c * 64)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  2] = Wc90TempGfx[0x40000 + (y * 2) + (c * 64)] >> 4;
			pTile[(c * 256) + (y * 16) +  3] = Wc90TempGfx[0x40000 + (y * 2) + (c * 64)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  4] = Wc90TempGfx[0x00001 + (y * 2) + (c * 64)] >> 4;
			pTile[(c * 256) + (y * 16) +  5] = Wc90TempGfx[0x00001 + (y * 2) + (c * 64)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  6] = Wc90TempGfx[0x40001 + (y * 2) + (c * 64)] >> 4;
			pTile[(c * 256) + (y * 16) +  7] = Wc90TempGfx[0x40001 + (y * 2) + (c * 64)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  8] = Wc90TempGfx[0x00010 + (y * 2) + (c * 64)] >> 4;
			pTile[(c * 256) + (y * 16) +  9] = Wc90TempGfx[0x00010 + (y * 2) + (c * 64)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 10] = Wc90TempGfx[0x40010 + (y * 2) + (c * 64)] >> 4;
			pTile[(c * 256) + (y * 16) + 11] = Wc90TempGfx[0x40010 + (y * 2) + (c * 64)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 12] = Wc90TempGfx[0x00011 + (y * 2) + (c * 64)] >> 4;
			pTile[(c * 256) + (y * 16) + 13] = Wc90TempGfx[0x00011 + (y * 2) + (c * 64)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 14] = Wc90TempGfx[0x40011 + (y * 2) + (c * 64)] >> 4;
			pTile[(c * 256) + (y * 16) + 15] = Wc90TempGfx[0x40011 + (y * 2) + (c * 64)] & 0x0f;
		}

		for (y = 8; y < 16; y++) {
			pTile[(c * 256) + (y * 16) +  0] = Wc90TempGfx[0x00000 + ((y + 8) * 2) + (c * 64)] >> 4;
			pTile[(c * 256) + (y * 16) +  1] = Wc90TempGfx[0x00000 + ((y + 8) * 2) + (c * 64)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  2] = Wc90TempGfx[0x40000 + ((y + 8) * 2) + (c * 64)] >> 4;
			pTile[(c * 256) + (y * 16) +  3] = Wc90TempGfx[0x40000 + ((y + 8) * 2) + (c * 64)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  4] = Wc90TempGfx[0x00001 + ((y + 8) * 2) + (c * 64)] >> 4;
			pTile[(c * 256) + (y * 16) +  5] = Wc90TempGfx[0x00001 + ((y + 8) * 2) + (c * 64)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  6] = Wc90TempGfx[0x40001 + ((y + 8) * 2) + (c * 64)] >> 4;
			pTile[(c * 256) + (y * 16) +  7] = Wc90TempGfx[0x40001 + ((y + 8) * 2) + (c * 64)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  8] = Wc90TempGfx[0x00010 + ((y + 8) * 2) + (c * 64)] >> 4;
			pTile[(c * 256) + (y * 16) +  9] = Wc90TempGfx[0x00010 + ((y + 8) * 2) + (c * 64)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 10] = Wc90TempGfx[0x40010 + ((y + 8) * 2) + (c * 64)] >> 4;
			pTile[(c * 256) + (y * 16) + 11] = Wc90TempGfx[0x40010 + ((y + 8) * 2) + (c * 64)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 12] = Wc90TempGfx[0x00011 + ((y + 8) * 2) + (c * 64)] >> 4;
			pTile[(c * 256) + (y * 16) + 13] = Wc90TempGfx[0x00011 + ((y + 8) * 2) + (c * 64)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 14] = Wc90TempGfx[0x40011 + ((y + 8) * 2) + (c * 64)] >> 4;
			pTile[(c * 256) + (y * 16) + 15] = Wc90TempGfx[0x40011 + ((y + 8) * 2) + (c * 64)] & 0x0f;
		}
	}
}

// Driver reset
int Wc90DoReset()
{
	Wc90Scroll0XLo = Wc90Scroll0XHi = Wc90Scroll0YLo = Wc90Scroll0YHi = 0;
	Wc90Scroll1XLo = Wc90Scroll1XHi = Wc90Scroll1YLo = Wc90Scroll1YHi = 0;
	Wc90Scroll2XLo = Wc90Scroll2XHi = Wc90Scroll2YLo = Wc90Scroll2YHi = 0;

	Wc90SoundLatch = 0;

	for (int i = 0; i < 3; i++) {
		ZetOpen(i);
		ZetReset();
		ZetClose();
	}

	BurnYM2608Reset();

	return 0;
}

// YM2608 IRQ Handler
static void wc90FMIRQHandler(int, int nStatus)
{
//	bprintf(PRINT_NORMAL, _T("    YM2608 IRQ status: 0x%02X (%6i cycles)\n"), nStatus, ZetTotalCycles());

	if (nStatus & 1) {
		ZetSetIRQLine(0xFF, ZET_IRQSTATUS_ACK);
	} else {
		ZetSetIRQLine(0,    ZET_IRQSTATUS_NONE);
	}
}

// CPU synchronisation
static inline void wc90SendSoundCommand(int nCommand)
{
	int nCycles = ZetTotalCycles() * 2 / 3;

//	bprintf(PRINT_NORMAL, _T("    Sync Sound CPU %i -> %i\n"), ZetTotalCycles(), nCycles);

	Wc90SoundLatch = nCommand;

	ZetClose();
	ZetOpen(2);

	if (nCycles > ZetTotalCycles()) {
		BurnTimerUpdate(nCycles);
	}

	ZetNmi();

	ZetClose();
	ZetOpen(0);
}

static int wc90SynchroniseStream(int nSoundRate)
{
	return (long long)ZetTotalCycles() * nSoundRate / 4000000;
}

static double wc90GetTime()
{
	return (double)ZetTotalCycles() / 4000000;
}

// Unmapped Memory reads and writes
unsigned char __fastcall Wc90Read1(unsigned short a)
{
	switch (a) {
		case 0xfc00: {
			return 0xff - Wc90Input[0];
		}

		case 0xfc02: {
			return 0xff - Wc90Input[1];
		}

		case 0xfc05: {
			return 0xff - Wc90Input[2];
		}

		case 0xfc06: {
			return Wc90Dip[0];
		}

		case 0xfc07: {
			return Wc90Dip[1];
		}
	}

	return 0;
}

void __fastcall Wc90Write1(unsigned short a, unsigned char d)
{
	switch (a) {
		case 0xfc02: {
			Wc90Scroll0YLo = d;
			return;
		}

		case 0xfc03: {
			Wc90Scroll0YHi = d;
			return;
		}

		case 0xfc06: {
			Wc90Scroll0XLo = d;
			return;
		}

		case 0xfc07: {
			Wc90Scroll0XHi = d;
			return;
		}

		case 0xfc22: {
			Wc90Scroll1YLo = d;
			return;
		}

		case 0xfc23: {
			Wc90Scroll1YHi = d;
			return;
		}

		case 0xfc26: {
			Wc90Scroll1XLo = d;
			return;
		}

		case 0xfc27: {
			Wc90Scroll1XHi = d;
			return;
		}

		case 0xfc42: {
			Wc90Scroll2YLo = d;
			return;
		}

		case 0xfc43: {
			Wc90Scroll2YHi = d;
			return;
		}

		case 0xfc46: {
			Wc90Scroll2XLo = d;
			return;
		}

		case 0xfc47: {
			Wc90Scroll2XHi = d;
			return;
		}

		case 0xfcc0: {
			wc90SendSoundCommand(d);
			return;
		}

		case 0xfce0: {
			int BankAddress;

			BankAddress = 0x10000 + ((d & 0xf8) << 8);
			ZetMapArea(0xf000, 0xf7ff, 0, Wc90Z80Rom1 + BankAddress);
			ZetMapArea(0xf000, 0xf7ff, 2, Wc90Z80Rom1 + BankAddress);
			return;
		}
	}
}

void __fastcall Wc90Write2(unsigned short a, unsigned char d)
{
	switch (a) {
		case 0xfc00: {
			int BankAddress;

			BankAddress = 0x10000 + ((d & 0xf8) << 8);
			ZetMapArea(0xf000, 0xf7ff, 0, Wc90Z80Rom2 + BankAddress);
			ZetMapArea(0xf000, 0xf7ff, 2, Wc90Z80Rom2 + BankAddress);
			return;
		}
	}
}

unsigned char __fastcall Wc90Read3(unsigned short a)
{
	switch (a) {
		case 0xf800: {
			return BurnYM2608Read(0);
		}

		case 0xf802: {
			return BurnYM2608Read(2);
		}

		case 0xfc10: {
			return Wc90SoundLatch;
		}
	}

	return 0;
}

void __fastcall Wc90Write3(unsigned short a, unsigned char d)
{
	switch (a) {
		case 0xf800: {
			BurnYM2608Write(0, d);
			return;
		}

		case 0xf801: {
			BurnYM2608Write(1, d);
			return;
		}

		case 0xf802: {
			BurnYM2608Write(2, d);
			return;
		}

		case 0xf803: {
			BurnYM2608Write(3, d);
			return;
		}
	}
}

// Function to allocate memory and set up pointers
static int MemIndex()
{
	unsigned char *Next; Next = Mem;

	Wc90Z80Rom1            = Next; Next += 0x20000;
	Wc90Z80Rom2            = Next; Next += 0x20000;
	Wc90Z80Rom3            = Next; Next += 0x10000;
	Wc90YM2608Rom          = Next; Next += 0x20000;

	RamStart               = Next;

	Wc90Z80Ram1            = Next; Next += 0x04000;
	Wc90Z80Ram2            = Next; Next += 0x01800;
	Wc90Z80Ram3            = Next; Next += 0x00800;
	Wc90FgVideoRam         = Next; Next += 0x01000;
	Wc90BgVideoRam         = Next; Next += 0x01000;
	Wc90TextVideoRam       = Next; Next += 0x01000;
	Wc90SpriteRam          = Next; Next += 0x00800;
	Wc90PaletteRam         = Next; Next += 0x00800;
	Wc90SharedRam          = Next; Next += 0x00400;

	RamEnd                 = Next;

	Wc90CharTiles          = Next; Next += (2048 *  8 *  8);
	Wc90BgTiles            = Next; Next += (2048 * 16 * 16);
	Wc90FgTiles            = Next; Next += (2048 * 16 * 16);
	Wc90Sprites            = Next; Next += (4096 * 16 * 16);
	Wc90Palette            = (unsigned int*)Next; Next += 0x00800 * sizeof(unsigned int);

	MemEnd                 = Next;

	return 0;
}

// Background Layer emulation
void Wc90RenderBgLayer()
{
	int mx, my, Attr, Code, Colour, x, y, TileIndex = 0;

	for (my = 0; my < 32; my++) {
		for (mx = 0; mx < 64; mx++) {
			Attr = Wc90BgVideoRam[TileIndex];
			Code = Wc90BgVideoRam[TileIndex + 0x800] + 256 * ((Attr & 3) + ((Attr >> 1) & 4));
			Colour = Attr >> 4;

			x = 16 * mx;
			y = 16 * my;

			x -= Wc90Scroll2XLo + 256 * Wc90Scroll2XHi;
			y -= Wc90Scroll2YLo + 256 * Wc90Scroll2YHi;

			x &= 0x3ff;
			y &= 0x1ff;

			y -= 16;
			if (x > 968) x -= 1024;

			if (x > 15 && x < 240 && y > 15 && y < 208) {
				Render16x16Tile(Code, x, y, Colour, 4, 768, Wc90BgTiles);
			} else {
				Render16x16Tile_Clip(Code, x, y, Colour, 4, 768, Wc90BgTiles);
			}

			TileIndex++;
		}
	}
}

void Wc90tRenderBgLayer()
{
	int mx, my, Attr, Code, Colour, x, y, TileIndex = 0;

	for (my = 0; my < 32; my++) {
		for (mx = 0; mx < 64; mx++) {
			Attr = Wc90BgVideoRam[TileIndex];
			Code = Wc90BgVideoRam[TileIndex + 0x800] + 256 * (Attr & 7);
			Colour = Attr >> 4;

			x = 16 * mx;
			y = 16 * my;

			x -= Wc90Scroll2XLo + 256 * Wc90Scroll2XHi;
			y -= Wc90Scroll2YLo + 256 * Wc90Scroll2YHi;

			x &= 0x3ff;
			y &= 0x1ff;

			y -= 16;
			if (x > 968) x -= 1024;

			if (x > 15 && x < 240 && y > 15 && y < 208) {
				Render16x16Tile(Code, x, y, Colour, 4, 768, Wc90BgTiles);
			} else {
				Render16x16Tile_Clip(Code, x, y, Colour, 4, 768, Wc90BgTiles);
			}

			TileIndex++;
		}
	}
}

// Foreground Layer emulation
void Wc90RenderFgLayer()
{
	int mx, my, Attr, Code, Colour, x, y, TileIndex = 0;

	for (my = 0; my < 32; my++) {
		for (mx = 0; mx < 64; mx++) {
			Attr = Wc90FgVideoRam[TileIndex];
			Code = Wc90FgVideoRam[TileIndex + 0x800] + 256 * ((Attr & 3) + ((Attr >> 1) & 4));
			Colour = Attr >> 4;

			x = 16 * mx;
			y = 16 * my;

			x -= Wc90Scroll1XLo + 256 * Wc90Scroll1XHi;
			y -= Wc90Scroll1YLo + 256 * Wc90Scroll1YHi;

			x &= 0x3ff;
			y &= 0x1ff;

			y -= 16;
			if (x > 968) x -= 1024;

			if (x > 15 && x < 240 && y > 15 && y < 208) {
				Render16x16Tile_Mask(Code, x, y, Colour, 4, 0, 512, Wc90FgTiles);
			} else {
				Render16x16Tile_Mask_Clip(Code, x, y, Colour, 4, 0, 512, Wc90FgTiles);
			}

			TileIndex++;
		}
	}
}

void Wc90tRenderFgLayer()
{
	int mx, my, Attr, Code, Colour, x, y, TileIndex = 0;

	for (my = 0; my < 32; my++) {
		for (mx = 0; mx < 64; mx++) {
			Attr = Wc90FgVideoRam[TileIndex];
			Code = Wc90FgVideoRam[TileIndex + 0x800] + 256 * (Attr & 7);
			Colour = Attr >> 4;

			x = 16 * mx;
			y = 16 * my;

			x -= Wc90Scroll1XLo + 256 * Wc90Scroll1XHi;
			y -= Wc90Scroll1YLo + 256 * Wc90Scroll1YHi;

			x &= 0x3ff;
			y &= 0x1ff;

			y -= 16;
			if (x > 968) x -= 1024;

			if (x > 15 && x < 240 && y > 15 && y < 208) {
				Render16x16Tile_Mask(Code, x, y, Colour, 4, 0, 512, Wc90FgTiles);
			} else {
				Render16x16Tile_Mask_Clip(Code, x, y, Colour, 4, 0, 512, Wc90FgTiles);
			}

			TileIndex++;
		}
	}
}

// Character Layer emulation
void Wc90RenderCharLayer()
{
	int mx, my, Code, Colour, x, y, TileIndex = 0;

	for (my = 0; my < 32; my++) {
		for (mx = 0; mx < 64; mx++) {
			Code = Wc90TextVideoRam[TileIndex + 0x800] + ((Wc90TextVideoRam[TileIndex] & 0x07) << 8);
			Colour = Wc90TextVideoRam[TileIndex] >> 4;

			x = 8 * mx;
			y = 8 * my;

			x -= Wc90Scroll0XLo + 256 * Wc90Scroll0XHi;
			y -= Wc90Scroll0YLo + 256 * Wc90Scroll0YHi;

			x &= 0x1ff;
			y &= 0x0ff;

			y -= 16;

			if (x > 7 && x < 248 && y > 7 && y < 216) {
				Render8x8Tile_Mask(Code, x, y, Colour, 4, 0, 256, Wc90CharTiles);
			} else {
				Render8x8Tile_Mask_Clip(Code, x, y, Colour, 4, 0, 256, Wc90CharTiles);
			}

			TileIndex++;
		}
	}
}

// Sprite Layers emulation
void Wc90RenderSprite(int Code, int Colour, int FlipX, int FlipY, int x, int y)
{
	if (x > 15 && x < 240 && y > 15 && y < 208) {
		if (!FlipY) {
			if (!FlipX) {
				Render16x16Tile_Mask(Code, x, y, Colour, 4, 0, 0, Wc90Sprites);
			} else {
				Render16x16Tile_Mask_FlipX(Code, x, y, Colour, 4, 0, 0, Wc90Sprites);
			}
		} else {
			if (!FlipX) {
				Render16x16Tile_Mask_FlipY(Code, x, y, Colour, 4, 0, 0, Wc90Sprites);
			} else {
				Render16x16Tile_Mask_FlipXY(Code, x, y, Colour, 4, 0, 0, Wc90Sprites);
			}
		}
	} else {
		if (!FlipY) {
			if (!FlipX) {
				Render16x16Tile_Mask_Clip(Code, x, y, Colour, 4, 0, 0, Wc90Sprites);
			} else {
				Render16x16Tile_Mask_FlipX_Clip(Code, x, y, Colour, 4, 0, 0, Wc90Sprites);
			}
		} else {
			if (!FlipX) {
				Render16x16Tile_Mask_FlipY_Clip(Code, x, y, Colour, 4, 0, 0, Wc90Sprites);
			} else {
				Render16x16Tile_Mask_FlipXY_Clip(Code, x, y, Colour, 4, 0, 0, Wc90Sprites);
			}
		}
	}
}

static char pos32x32[] = { 0, 1, 2, 3 };
static char pos32x32x[] = { 1, 0, 3, 2 };
static char pos32x32y[] = { 2, 3, 0, 1 };
static char pos32x32xy[] = { 3, 2, 1, 0 };

static char pos32x64[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
static char pos32x64x[] = { 5, 4, 7, 6, 1, 0, 3, 2 };
static char pos32x64y[] = { 2, 3, 0, 1,	6, 7, 4, 5 };
static char pos32x64xy[] = { 7, 6, 5, 4, 3, 2, 1, 0 };

static char pos64x32[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
static char pos64x32x[] = { 1, 0, 3, 2, 5, 4, 7, 6 };
static char pos64x32y[] = { 6, 7, 4, 5, 2, 3, 0, 1 };
static char pos64x32xy[] = { 7, 6, 5, 4, 3, 2, 1, 0 };

static char pos64x64[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
static char pos64x64x[] = { 5, 4, 7, 6, 1, 0, 3, 2, 13, 12, 15, 14, 9, 8, 11, 10 };
static char pos64x64y[] = { 10, 11, 8, 9, 14, 15, 12, 13, 2, 3, 0, 1, 6, 7, 4, 5 };
static char pos64x64xy[] = { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

static char* p32x32[4] = {
	pos32x32,
	pos32x32x,
	pos32x32y,
	pos32x32xy
};

static char* p32x64[4] = {
	pos32x64,
	pos32x64x,
	pos32x64y,
	pos32x64xy
};

static char* p64x32[4] = {
	pos64x32,
	pos64x32x,
	pos64x32y,
	pos64x32xy
};

static char* p64x64[4] = {
	pos64x64,
	pos64x64x,
	pos64x64y,
	pos64x64xy
};

static void drawsprite_16x16(int Code, int x, int y, int Bank, int Attr) {
	Wc90RenderSprite(Code, Attr >> 4, Bank & 1, Bank & 2, x, y);
}

static void drawsprite_16x32(int Code, int x, int y, int Bank, int Attr) {
	if (Bank & 2) {
		Wc90RenderSprite(Code + 1, Attr >> 4, Bank & 1, Bank & 2, x, y + 16);
		Wc90RenderSprite(Code + 0, Attr >> 4, Bank & 1, Bank & 2, x, y +  0);
	} else {
		Wc90RenderSprite(Code + 0, Attr >> 4, Bank & 1, Bank & 2, x, y +  0);
		Wc90RenderSprite(Code + 1, Attr >> 4, Bank & 1, Bank & 2, x, y + 16);
	}
}

static void drawsprite_16x64(int Code, int x, int y, int Bank, int Attr) {
	if (Bank & 2) {
		Wc90RenderSprite(Code + 3, Attr >> 4, Bank & 1, Bank & 2, x, y + 48);
		Wc90RenderSprite(Code + 2, Attr >> 4, Bank & 1, Bank & 2, x, y + 32);
		Wc90RenderSprite(Code + 1, Attr >> 4, Bank & 1, Bank & 2, x, y + 16);
		Wc90RenderSprite(Code + 0, Attr >> 4, Bank & 1, Bank & 2, x, y +  0);
	} else {
		Wc90RenderSprite(Code + 0, Attr >> 4, Bank & 1, Bank & 2, x, y +  0);
		Wc90RenderSprite(Code + 1, Attr >> 4, Bank & 1, Bank & 2, x, y + 16);
		Wc90RenderSprite(Code + 2, Attr >> 4, Bank & 1, Bank & 2, x, y + 32);
		Wc90RenderSprite(Code + 3, Attr >> 4, Bank & 1, Bank & 2, x, y + 48);
	}
}

static void drawsprite_32x16(int Code, int x, int y, int Bank, int Attr) {
	if (Bank & 1) {
		Wc90RenderSprite(Code + 1, Attr >> 4, Bank & 1, Bank & 2, x + 16, y);
		Wc90RenderSprite(Code + 0, Attr >> 4, Bank & 1, Bank & 2, x +  0, y);
	} else {
		Wc90RenderSprite(Code + 0, Attr >> 4, Bank & 1, Bank & 2, x +  0, y);
		Wc90RenderSprite(Code + 1, Attr >> 4, Bank & 1, Bank & 2, x + 16, y);
	}
}

static void drawsprite_32x32(int Code, int x, int y, int Bank, int Attr) {
	char *p = p32x32[Bank & 3];

	Wc90RenderSprite(Code + p[0], Attr >> 4, Bank & 1, Bank & 2, x +  0, y +  0);
	Wc90RenderSprite(Code + p[1], Attr >> 4, Bank & 1, Bank & 2, x + 16, y +  0);
	Wc90RenderSprite(Code + p[2], Attr >> 4, Bank & 1, Bank & 2, x +  0, y + 16);
	Wc90RenderSprite(Code + p[3], Attr >> 4, Bank & 1, Bank & 2, x + 16, y + 16);
}

static void drawsprite_32x64(int Code, int x, int y, int Bank, int Attr) {
	char *p = p32x64[Bank & 3];

	Wc90RenderSprite(Code + p[0], Attr >> 4, Bank & 1, Bank & 2, x +  0, y +  0);
	Wc90RenderSprite(Code + p[1], Attr >> 4, Bank & 1, Bank & 2, x + 16, y +  0);
	Wc90RenderSprite(Code + p[2], Attr >> 4, Bank & 1, Bank & 2, x +  0, y + 16);
	Wc90RenderSprite(Code + p[3], Attr >> 4, Bank & 1, Bank & 2, x + 16, y + 16);
	Wc90RenderSprite(Code + p[4], Attr >> 4, Bank & 1, Bank & 2, x +  0, y + 32);
	Wc90RenderSprite(Code + p[5], Attr >> 4, Bank & 1, Bank & 2, x + 16, y + 32);
	Wc90RenderSprite(Code + p[6], Attr >> 4, Bank & 1, Bank & 2, x +  0, y + 48);
	Wc90RenderSprite(Code + p[7], Attr >> 4, Bank & 1, Bank & 2, x + 16, y + 48);
}

static void drawsprite_64x16(int Code, int x, int y, int Bank, int Attr) {
	if (Bank & 1) {
		Wc90RenderSprite(Code + 3, Attr >> 4, Bank & 1, Bank & 2, x + 48, y);
		Wc90RenderSprite(Code + 2, Attr >> 4, Bank & 1, Bank & 2, x + 32, y);
		Wc90RenderSprite(Code + 1, Attr >> 4, Bank & 1, Bank & 2, x + 16, y);
		Wc90RenderSprite(Code + 0, Attr >> 4, Bank & 1, Bank & 2, x +  0, y);
	} else {
		Wc90RenderSprite(Code + 0, Attr >> 4, Bank & 1, Bank & 2, x +  0, y);
		Wc90RenderSprite(Code + 1, Attr >> 4, Bank & 1, Bank & 2, x + 16, y);
		Wc90RenderSprite(Code + 2, Attr >> 4, Bank & 1, Bank & 2, x + 32, y);
		Wc90RenderSprite(Code + 3, Attr >> 4, Bank & 1, Bank & 2, x + 48, y);
	}
}

static void drawsprite_64x32(int Code, int x, int y, int Bank, int Attr) {
	char *p = p64x32[Bank & 3];

	Wc90RenderSprite(Code + p[0], Attr >> 4, Bank & 1, Bank & 2, x +  0, y +  0);
	Wc90RenderSprite(Code + p[1], Attr >> 4, Bank & 1, Bank & 2, x + 16, y +  0);
	Wc90RenderSprite(Code + p[2], Attr >> 4, Bank & 1, Bank & 2, x +  0, y + 16);
	Wc90RenderSprite(Code + p[3], Attr >> 4, Bank & 1, Bank & 2, x + 16, y + 16);
	Wc90RenderSprite(Code + p[4], Attr >> 4, Bank & 1, Bank & 2, x + 32 ,y +  0);
	Wc90RenderSprite(Code + p[5], Attr >> 4, Bank & 1, Bank & 2, x + 48, y +  0);
	Wc90RenderSprite(Code + p[6], Attr >> 4, Bank & 1, Bank & 2, x + 32, y + 16);
	Wc90RenderSprite(Code + p[7], Attr >> 4, Bank & 1, Bank & 2, x + 48, y + 16);
}

static void drawsprite_64x64(int Code, int x, int y, int Bank, int Attr) {
	char *p = p64x64[Bank & 3];

	Wc90RenderSprite(Code + p[ 0], Attr >> 4, Bank & 1, Bank & 2, x +  0, y +  0);
	Wc90RenderSprite(Code + p[ 1], Attr >> 4, Bank & 1, Bank & 2, x + 16, y +  0);
	Wc90RenderSprite(Code + p[ 2], Attr >> 4, Bank & 1, Bank & 2, x +  0, y + 16);
	Wc90RenderSprite(Code + p[ 3], Attr >> 4, Bank & 1, Bank & 2, x + 16, y + 16);
	Wc90RenderSprite(Code + p[ 4], Attr >> 4, Bank & 1, Bank & 2, x + 32 ,y +  0);
	Wc90RenderSprite(Code + p[ 5], Attr >> 4, Bank & 1, Bank & 2, x + 48, y +  0);
	Wc90RenderSprite(Code + p[ 6], Attr >> 4, Bank & 1, Bank & 2, x + 32, y + 16);
	Wc90RenderSprite(Code + p[ 7], Attr >> 4, Bank & 1, Bank & 2, x + 48, y + 16);
	Wc90RenderSprite(Code + p[ 8], Attr >> 4, Bank & 1, Bank & 2, x +  0, y + 32);
	Wc90RenderSprite(Code + p[ 9], Attr >> 4, Bank & 1, Bank & 2, x + 16, y + 32);
	Wc90RenderSprite(Code + p[10], Attr >> 4, Bank & 1, Bank & 2, x +  0, y + 48);
	Wc90RenderSprite(Code + p[11], Attr >> 4, Bank & 1, Bank & 2, x + 16, y + 48);
	Wc90RenderSprite(Code + p[12], Attr >> 4, Bank & 1, Bank & 2, x + 32, y + 32);
	Wc90RenderSprite(Code + p[13], Attr >> 4, Bank & 1, Bank & 2, x + 48, y + 32);
	Wc90RenderSprite(Code + p[14], Attr >> 4, Bank & 1, Bank & 2, x + 32, y + 48);
	Wc90RenderSprite(Code + p[15], Attr >> 4, Bank & 1, Bank & 2, x + 48, y + 48);
}

static void drawsprite_invalid(int Code, int x, int y, int Bank, int Attr) {
#ifdef FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("8 Pixel Size not Supported! %X, %d, %d, %X, %X\n"), Code, x, y, Bank, Attr);
#else
	(void)Code; (void)x; (void)y; (void)Bank; (void)Attr;
#endif
}

typedef void (*drawsprites_procdef)(int, int, int, int, int);

static drawsprites_procdef drawsprites_proc[16] = {
	drawsprite_invalid,		/* 0000 = 08x08 */
	drawsprite_invalid,		/* 0001 = 16x08 */
	drawsprite_invalid,		/* 0010 = 32x08 */
	drawsprite_invalid,		/* 0011 = 64x08 */
	drawsprite_invalid,		/* 0100 = 08x16 */
	drawsprite_16x16,		/* 0101 = 16x16 */
	drawsprite_32x16,		/* 0110 = 32x16 */
	drawsprite_64x16,		/* 0111 = 64x16 */
	drawsprite_invalid,		/* 1000 = 08x32 */
	drawsprite_16x32,		/* 1001 = 16x32 */
	drawsprite_32x32,		/* 1010 = 32x32 */
	drawsprite_64x32,		/* 1011 = 64x32 */
	drawsprite_invalid,		/* 1100 = 08x64 */
	drawsprite_16x64,		/* 1101 = 16x64 */
	drawsprite_32x64,		/* 1110 = 32x64 */
	drawsprite_64x64		/* 1111 = 64x64 */
};

void Wc90RenderSprites(int Priority)
{
	int Code, Attr, x, y;

	for (int Offs = 0; Offs < 0x800; Offs += 16) {
		int Bank = Wc90SpriteRam[Offs + 0];

		if ((Bank >> 4) == Priority) {
			if (Bank & 4) {
				Code = (Wc90SpriteRam[Offs + 2] >> 2) + (Wc90SpriteRam[Offs + 3] << 6);

				x = Wc90SpriteRam[Offs + 8] + ((Wc90SpriteRam[Offs + 9] & 1) << 8);
				y = Wc90SpriteRam[Offs + 6] + ((Wc90SpriteRam[Offs + 7] & 1) << 8);

				y -= 16;

				Attr = Wc90SpriteRam[Offs + 4];
				(*(drawsprites_proc[Attr & 0x0f]))(Code, x, y, Bank, Attr);
			}
		}
	}
}

// Palette handling functions
inline static unsigned int CalcCol(unsigned short nColour)
{
	int r, g, b;

	r = (nColour >> 4) & 0x0f;
	g = (nColour >> 0) & 0x0f;
	b = (nColour >> 8) & 0x0f;

	r = (r << 4) | r;
	g = (g << 4) | g;
	b = (b << 4) | b;

	return BurnHighCol(r, g, b, 0);
}

int Wc90CalcPalette()
{
	int i;

	for (i = 0; i < 0x800; i++) {
		Wc90Palette[i / 2] = CalcCol(Wc90PaletteRam[i | 1] | (Wc90PaletteRam[i & ~1] << 8));
	}

	return 0;
}

// Draw Screen functions
void Wc90Draw()
{
	Wc90CalcPalette();
	Wc90RenderBgLayer();
	Wc90RenderSprites(2);
	Wc90RenderFgLayer();
	Wc90RenderSprites(1);
	Wc90RenderCharLayer();
	Wc90RenderSprites(0);
	BurnTransferCopy(Wc90Palette);
}

void Wc90tDraw()
{
	Wc90CalcPalette();
	Wc90tRenderBgLayer();
	Wc90RenderSprites(2);
	Wc90tRenderFgLayer();
	Wc90RenderSprites(1);
	Wc90RenderCharLayer();
	Wc90RenderSprites(0);
	BurnTransferCopy(Wc90Palette);
}

typedef void (*drawscreen_procdef)(void);

static drawscreen_procdef drawscreen_proc[2] = {
	Wc90Draw,
	Wc90tDraw,
};

// Frame function
int Wc90Frame()
{
	int nInterleave = 16;
	int nCurrentCPU;

	if (Wc90Reset) Wc90DoReset();

	Wc90MakeInputs();

	ZetNewFrame();

	// Compensate for extra cycles executed
	for (int i = 0; i < 3; i++) {
		ZetOpen(i);
		ZetIdle(nCyclesDone[i]);
		ZetClose();
	}

	nCyclesTotal[0] = 6000000 / 60;
	nCyclesTotal[1] = 6000000 / 60;
	nCyclesTotal[2] = 4000000 / 60;

	for (int i = 0; i < nInterleave; i++) {
		int nNext;

		// Run Z80 #1
		nCurrentCPU = 0;
		ZetOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - ZetTotalCycles();
		ZetRun(nCyclesSegment);
		ZetClose();

		// Run Z80 #2
		nCurrentCPU = 1;
		ZetOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - ZetTotalCycles();
		ZetRun(nCyclesSegment);
		ZetClose();
	}

	for (int i = 0; i < 2; i++) {
		ZetOpen(i);
		ZetRaiseIrq(0);
		nCyclesDone[i] = ZetTotalCycles() - nCyclesTotal[i];
		ZetClose();
	}

	ZetOpen(2);
	BurnTimerEndFrame(nCyclesTotal[2]);
	BurnYM2608Update(nBurnSoundLen);
	nCyclesDone[2] = ZetTotalCycles() - nCyclesTotal[2];
	ZetClose();

//	bprintf(PRINT_NORMAL, _T("    %i %i %i\n"), nCyclesDone[0], nCyclesDone[1], nCyclesDone[2]);

	if (pBurnDraw) (*(drawscreen_proc[nTileType]))();

	return 0;
}

// Driver Init function
int Wc90Init()
{
	int nRet = 0, nLen;

	// Allocate and Blank all required memory
	Mem = NULL;
	MemIndex();
	nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) return 1;
	memset(Mem, 0, nLen);
	MemIndex();

	Wc90TempGfx = (unsigned char*)malloc(0x80000);
	if (Wc90TempGfx == NULL) return 1;

	// Load Z80 #1 Program Roms
	nRet = BurnLoadRom(Wc90Z80Rom1 + 0x00000,  0, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Wc90Z80Rom1 + 0x10000,  1, 1); if (nRet != 0) return 1;

	// Load Z80 #2 Program Roms
	nRet = BurnLoadRom(Wc90Z80Rom2 + 0x00000,  2, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Wc90Z80Rom2 + 0x10000,  3, 1); if (nRet != 0) return 1;

	// Load Z80 #3 Program Rom
	nRet = BurnLoadRom(Wc90Z80Rom3 + 0x00000,  4, 1); if (nRet != 0) return 1;

	// Load and Decode Char Tile Rom
	memset(Wc90TempGfx, 0, 0x80000);
	nRet = BurnLoadRom(Wc90TempGfx + 0x00000,  5, 1); if (nRet != 0) return 1;
	Wc90Decode8x8Tiles(Wc90CharTiles, 2048);

	// Load and Decode Fg Tile Roms
	memset(Wc90TempGfx, 0, 0x80000);
	nRet = BurnLoadRom(Wc90TempGfx + 0x00000,  6, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Wc90TempGfx + 0x20000,  7, 1); if (nRet != 0) return 1;
	Wc90Decode16x16Tiles(Wc90FgTiles, 2048);

	// Load and Decode Bg Tile Roms
	memset(Wc90TempGfx, 0, 0x80000);
	nRet = BurnLoadRom(Wc90TempGfx + 0x00000,  8, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Wc90TempGfx + 0x20000,  9, 1); if (nRet != 0) return 1;
	Wc90Decode16x16Tiles(Wc90BgTiles, 2048);

	// Load and Decode Sprite Roms
	memset(Wc90TempGfx, 0, 0x80000);
	nRet = BurnLoadRom(Wc90TempGfx + 0x00000, 10, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Wc90TempGfx + 0x20000, 11, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Wc90TempGfx + 0x40000, 12, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Wc90TempGfx + 0x60000, 13, 1); if (nRet != 0) return 1;
	Wc90DecodeSprites(Wc90Sprites, 4096);

	free(Wc90TempGfx);

	// Load ADPCM Rom
	nRet = BurnLoadRom(Wc90YM2608Rom, 14, 1); if (nRet !=0) return 1;

	// Setup the Z80 emulation
	ZetInit(3);
	ZetOpen(0);
	ZetSetReadHandler(Wc90Read1);
	ZetSetWriteHandler(Wc90Write1);
	ZetMapArea(0x0000, 0x7fff, 0, Wc90Z80Rom1          );
	ZetMapArea(0x0000, 0x7fff, 2, Wc90Z80Rom1          );
	ZetMapArea(0x8000, 0x9fff, 0, Wc90Z80Ram1 + 0x00000);
	ZetMapArea(0x8000, 0x9fff, 1, Wc90Z80Ram1 + 0x00000);
	ZetMapArea(0x8000, 0x9fff, 2, Wc90Z80Ram1 + 0x00000);
	ZetMapArea(0xa000, 0xafff, 0, Wc90FgVideoRam       );
	ZetMapArea(0xa000, 0xafff, 1, Wc90FgVideoRam       );
	ZetMapArea(0xa000, 0xafff, 2, Wc90FgVideoRam       );
	ZetMapArea(0xb000, 0xbfff, 0, Wc90Z80Ram1 + 0x02000);
	ZetMapArea(0xb000, 0xbfff, 1, Wc90Z80Ram1 + 0x02000);
	ZetMapArea(0xb000, 0xbfff, 2, Wc90Z80Ram1 + 0x02000);
	ZetMapArea(0xc000, 0xcfff, 0, Wc90BgVideoRam       );
	ZetMapArea(0xc000, 0xcfff, 1, Wc90BgVideoRam       );
	ZetMapArea(0xc000, 0xcfff, 2, Wc90BgVideoRam       );
	ZetMapArea(0xd000, 0xdfff, 0, Wc90Z80Ram1 + 0x03000);
	ZetMapArea(0xd000, 0xdfff, 1, Wc90Z80Ram1 + 0x03000);
	ZetMapArea(0xd000, 0xdfff, 2, Wc90Z80Ram1 + 0x03000);
	ZetMapArea(0xe000, 0xefff, 0, Wc90TextVideoRam     );
	ZetMapArea(0xe000, 0xefff, 1, Wc90TextVideoRam     );
	ZetMapArea(0xe000, 0xefff, 2, Wc90TextVideoRam     );
	ZetMapArea(0xf000, 0xf7ff, 0, Wc90Z80Rom1 + 0x10000);
	ZetMapArea(0xf000, 0xf7ff, 2, Wc90Z80Rom1 + 0x10000);
	ZetMapArea(0xf800, 0xfbff, 0, Wc90SharedRam        );
	ZetMapArea(0xf800, 0xfbff, 1, Wc90SharedRam        );
	ZetMapArea(0xf800, 0xfbff, 2, Wc90SharedRam        );
	ZetMemEnd();
	ZetClose();

	ZetOpen(1);
	ZetSetWriteHandler(Wc90Write2);
	ZetMapArea(0x0000, 0xbfff, 0, Wc90Z80Rom2          );
	ZetMapArea(0x0000, 0xbfff, 2, Wc90Z80Rom2          );
	ZetMapArea(0xc000, 0xcfff, 0, Wc90Z80Ram2 + 0x00000);
	ZetMapArea(0xc000, 0xcfff, 1, Wc90Z80Ram2 + 0x00000);
	ZetMapArea(0xc000, 0xcfff, 2, Wc90Z80Ram2 + 0x00000);
	ZetMapArea(0xd000, 0xd7ff, 0, Wc90SpriteRam        );
	ZetMapArea(0xd000, 0xd7ff, 1, Wc90SpriteRam        );
	ZetMapArea(0xd000, 0xd7ff, 2, Wc90SpriteRam        );
	ZetMapArea(0xd800, 0xdfff, 0, Wc90Z80Ram2 + 0x01000);
	ZetMapArea(0xd800, 0xdfff, 1, Wc90Z80Ram2 + 0x01000);
	ZetMapArea(0xd800, 0xdfff, 2, Wc90Z80Ram2 + 0x01000);
	ZetMapArea(0xe000, 0xe7ff, 0, Wc90PaletteRam       );
	ZetMapArea(0xe000, 0xe7ff, 1, Wc90PaletteRam       );
	ZetMapArea(0xe000, 0xe7ff, 2, Wc90PaletteRam       );
	ZetMapArea(0xf000, 0xf7ff, 0, Wc90Z80Rom2 + 0x10000);
	ZetMapArea(0xf000, 0xf7ff, 2, Wc90Z80Rom2 + 0x10000);
	ZetMapArea(0xf800, 0xfbff, 0, Wc90SharedRam        );
	ZetMapArea(0xf800, 0xfbff, 1, Wc90SharedRam        );
	ZetMapArea(0xf800, 0xfbff, 2, Wc90SharedRam        );
	ZetMemEnd();
	ZetClose();

	ZetOpen(2);
	ZetSetReadHandler(Wc90Read3);
	ZetSetWriteHandler(Wc90Write3);
	ZetMapArea(0x0000, 0xbfff, 0, Wc90Z80Rom3          );
	ZetMapArea(0x0000, 0xbfff, 2, Wc90Z80Rom3          );
	ZetMapArea(0xf000, 0xf7ff, 0, Wc90Z80Ram3          );
	ZetMapArea(0xf000, 0xf7ff, 1, Wc90Z80Ram3          );
	ZetMapArea(0xf000, 0xf7ff, 2, Wc90Z80Ram3          );
	ZetMemEnd();
	ZetClose();

	GenericTilesInit();

	if (!strcmp(BurnDrvGetTextA(DRV_NAME), "wc90t")) {
		nTileType = 1;
	} else {
		nTileType = 0;
	}

	int Wc90YM2608RomSize = 0x20000;
	BurnYM2608Init(8000000, Wc90YM2608Rom, &Wc90YM2608RomSize, &wc90FMIRQHandler, wc90SynchroniseStream, wc90GetTime);
	BurnTimerAttachZet(4000000);

	// Reset the driver
	Wc90DoReset();

	return 0;
}

// Driver Exit function
int Wc90Exit()
{
	ZetExit();
	GenericTilesExit();
	BurnYM2608Exit();

	free(Mem);
	Mem = NULL;

	return 0;
}

// Scan Ram function
static int Wc90Scan(int nAction,int *pnMin)
{
	struct BurnArea ba;

	if (pnMin != NULL) {			// Return minimum compatible version
		*pnMin = 0x029521;
	}

	if (nAction & ACB_MEMORY_RAM) {
		memset(&ba, 0, sizeof(ba));
		ba.Data	  = RamStart;
		ba.nLen	  = RamEnd-RamStart;
		ba.szName = "All Ram";
		BurnAcb(&ba);
	}

	if (nAction & ACB_DRIVER_DATA) {
		ZetScan(nAction);			// Scan Z80

		BurnYM2608Scan(nAction, pnMin);	// Scan YM2608

		// Scan critical driver variables
		SCAN_VAR(Wc90SoundLatch);
		SCAN_VAR(Wc90Input);
		SCAN_VAR(Wc90Dip);
		SCAN_VAR(Wc90Scroll0YLo);
		SCAN_VAR(Wc90Scroll0YHi);
		SCAN_VAR(Wc90Scroll0XLo);
		SCAN_VAR(Wc90Scroll0XHi);
		SCAN_VAR(Wc90Scroll1YLo);
		SCAN_VAR(Wc90Scroll1YHi);
		SCAN_VAR(Wc90Scroll1XLo);
		SCAN_VAR(Wc90Scroll1XHi);
		SCAN_VAR(Wc90Scroll2YLo);
		SCAN_VAR(Wc90Scroll2YHi);
		SCAN_VAR(Wc90Scroll2XLo);
		SCAN_VAR(Wc90Scroll2XHi);
	}

	return 0;
}

// Driver definitions
struct BurnDriver BurnDrvWc90 = {
	"wc90", NULL, NULL, "1989",
	"World Cup '90 (set 1)\0", NULL, "Tecmo", "Miscellaneous",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_MISC_MISC,
	NULL, Wc90RomInfo, Wc90RomName, Wc90InputInfo, Wc90DIPInfo,
	Wc90Init, Wc90Exit, Wc90Frame, NULL, Wc90Scan,
	NULL, 256, 224, 4, 3
};

struct BurnDriver BurnDrvWc90a = {
	"wc90a", "wc90", NULL, "1989",
	"World Cup '90 (set 2)\0", NULL, "Tecmo", "Miscellaneous",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_MISC_MISC,
	NULL, Wc90aRomInfo, Wc90aRomName, Wc90InputInfo, Wc90DIPInfo,
	Wc90Init, Wc90Exit, Wc90Frame, NULL, Wc90Scan,
	NULL, 256, 224, 4, 3
};

struct BurnDriver BurnDrvWc90t = {
	"wc90t", "wc90", NULL, "1989",
	"World Cup '90 (trackball)\0", NULL, "Tecmo", "Miscellaneous",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_MISC_MISC,
	NULL, Wc90tRomInfo, Wc90tRomName, Wc90InputInfo, Wc90DIPInfo,
	Wc90Init, Wc90Exit, Wc90Frame, NULL, Wc90Scan,
	NULL, 256, 224, 4, 3
};
