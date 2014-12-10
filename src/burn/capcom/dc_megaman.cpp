// Mega Man - the power battle

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp018+0, "p1 coin"},
  {"P1 Start"      , BIT_DIGITAL, CpsInp018+4, "p1 start"},
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Fire"       , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Jump"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Select"     , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Fire"       , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Jump"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Select"     , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"},
  {"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo megamanDIPList[]=
{
	// Defaults
	{0x15, 0xff, 0xff, 0x00, NULL                },
	{0x16, 0xff, 0xff, 0x05, NULL                },
	{0x17, 0xff, 0xff, 0x00, NULL                },

	// Dip A
	{0   , 0xfe, 0   , 19  , "Coin Mode"         },
	{0x15, 0x01, 0x1f, 0x00, "1 Coin  1 Credit"  },
	{0x15, 0x01, 0x1f, 0x01, "1 Coin  2 Credits" },
	{0x15, 0x01, 0x1f, 0x02, "1 Coin  3 Credits" },
	{0x15, 0x01, 0x1f, 0x03, "1 Coin  4 Credits" },
	{0x15, 0x01, 0x1f, 0x04, "1 Coin  5 Credits" },
	{0x15, 0x01, 0x1f, 0x05, "1 Coin  6 Credits" },
	{0x15, 0x01, 0x1f, 0x06, "1 Coin  7 Credits" },
	{0x15, 0x01, 0x1f, 0x07, "1 Coin  8 Credits" },
	{0x15, 0x01, 0x1f, 0x08, "1 Coin  9 Credits" },
	{0x15, 0x01, 0x1f, 0x09, "2 Coins 1 Credit"  },
	{0x15, 0x01, 0x1f, 0x0a, "3 Coins 1 Credit"  },
	{0x15, 0x01, 0x1f, 0x0b, "4 Coins 1 Credit"  },
	{0x15, 0x01, 0x1f, 0x0c, "5 Coins 1 Credit"  },
	{0x15, 0x01, 0x1f, 0x0d, "6 Coins 1 Credit"  },
	{0x15, 0x01, 0x1f, 0x0e, "7 Coins 1 Credit"  },
	{0x15, 0x01, 0x1f, 0x0f, "8 Coins 1 Credit"  },
	{0x15, 0x01, 0x1f, 0x10, "9 Coins 1 Credit"  },
	{0x15, 0x01, 0x1f, 0x11, "2 Coins Start 1 Coin Continue"},
	{0x15, 0x01, 0x1f, 0x12, "Free Play"         },

	{0   , 0xfe, 0   , 4   , "Chute Type"        },
	{0x15, 0x01, 0x60, 0x40, "1 Chute Single"    },
	{0x15, 0x01, 0x60, 0x00, "2 Chutes Single"   },
	{0x15, 0x01, 0x60, 0x20, "2 Chutes Multi"    },

	// Dip C
	{0   , 0xfe, 0   , 2   , "Continue"          },
	{0x17, 0x01, 0x04, 0x04, "Off"               },
	{0x17, 0x01, 0x04, 0x00, "On"                },

	{0   , 0xfe, 0   , 2   , "Monitor"           },
	{0x17, 0x01, 0x01, 0x00, "Normal"            },
	{0x17, 0x01, 0x01, 0x01, "Flip"              },

	{0   , 0xfe, 0   , 2   , "Demo Sounds"       },
	{0x17, 0x01, 0x20, 0x20, "Off"               },
	{0x17, 0x01, 0x20, 0x00, "On"                },

	// Dip B
	{0   , 0xfe, 0   , 4   , "Difficulty"        },
	{0x16, 0x01, 0x03, 0x00, "1 Easy"            },
	{0x16, 0x01, 0x03, 0x01, "2 Normal"          },
	{0x16, 0x01, 0x03, 0x02, "3 Hard"            },
	{0x16, 0x01, 0x03, 0x03, "4 Very Hard"       },

	{0   , 0xfe, 0   , 4   , "Start Time"        },
	{0x16, 0x01, 0x0c, 0x00, "1 Easy"            },
	{0x16, 0x01, 0x0c, 0x04, "2 Normal"          },
	{0x16, 0x01, 0x0c, 0x08, "3 Hard"            },
	{0x16, 0x01, 0x0c, 0x0c, "4 Very Hard"       },

	{0   , 0xfe, 0   , 2   , "Voice"             },
	{0x16, 0x01, 0x40, 0x00, "Off"               },
	{0x16, 0x01, 0x40, 0x40, "Normal"            },
};

STDDIPINFO(megaman);

static int DrvInit()
{
  int nRet=0; int i=0;
  Cps=1;
  nCpsRomLen= 3*0x080000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen=16*0x080000;
  nCpsZRomLen=  0x020000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms (they are already byteswapped)
  for (i=0;i<3;i++)
  { nRet=BurnLoadRom(CpsRom+0x080000*i,0+i,1); if (nRet!=0) return 1; }

  // Load graphics roms
  for (i=0;i<4;i++)
  {
    // Load up and interleve each set of 4 roms to make the 16x16 tiles
    CpsLoadTiles(CpsGfx+0x200000*i,3+i*4);
  }

  MaskAddr[0]=0x68;
  MaskAddr[1]=0x6a;
  MaskAddr[2]=0x6c;
  MaskAddr[3]=0x6e;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,19,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,20,1);
  nRet=BurnLoadRom(CpsAd+0x20000,21,1);

  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

static int DrvExit()
{

  CpsRunExit();
  CpsExit();
  nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0;
  return 0;
}

//==================================
//Mega Man - the power battle (Asia)
//==================================

// Rom information
static struct BurnRomInfo DrvRomDesc[] = {
	{ "rcma_23b.rom",  0x80000, 0x61e4a397, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "rcma_22b.rom",  0x80000, 0x708268c4, BRF_ESS | BRF_PRG }, //  1
	{ "rcma_21a.rom",  0x80000, 0x4376ea95, BRF_ESS | BRF_PRG }, //  2

//4
  // graphics:
	{ "rcm_01.rom",    0x80000, 0x6ecdf13f, BRF_GRA },
	{ "rcm_02.rom",    0x80000, 0x944d4f0f, BRF_GRA },
	{ "rcm_03.rom",    0x80000, 0x36f3073c, BRF_GRA },
	{ "rcm_04.rom",    0x80000, 0x54e622ff, BRF_GRA },

	{ "rcm_05.rom",    0x80000, 0x5dd131fd, BRF_GRA },
	{ "rcm_06.rom",    0x80000, 0xf0faf813, BRF_GRA },
	{ "rcm_07.rom",    0x80000, 0x826de013, BRF_GRA },
	{ "rcm_08.rom",    0x80000, 0xfbff64cf, BRF_GRA },

	{ "rcm_10.rom",    0x80000, 0x4dc8ada9, BRF_GRA },
	{ "rcm_11.rom",    0x80000, 0xf2b9ee06, BRF_GRA },
	{ "rcm_12.rom",    0x80000, 0xfed5f203, BRF_GRA },
	{ "rcm_13.rom",    0x80000, 0x5069d4a9, BRF_GRA },

	{ "rcm_14.rom",    0x80000, 0x303be3bd, BRF_GRA },
	{ "rcm_15.rom",    0x80000, 0x4f2d372f, BRF_GRA },
	{ "rcm_16.rom",    0x80000, 0x93d97fde, BRF_GRA },
	{ "rcm_17.rom",    0x80000, 0x92371042, BRF_GRA },

//20
	{ "rcm_09.rom",    0x20000, 0x9632d6ef, BRF_SND },
	{ "rcm_18.rom",    0x20000, 0x80f1f8aa, BRF_SND },
	{ "rcm_19.rom",    0x20000, 0xf257dbe1, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Drv) STD_ROM_FN(Drv)


struct BurnDriver BurnDrvCpsMegaman = {
	"megaman", NULL, NULL, "1995",
	"Mega Man - the power battle (951006 Asia)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,DrvRomInfo,DrvRomName,DrvInputInfo, megamanDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================================
//Rockman - the power battle (Japan)
//==================================


static struct BurnRomInfo RockmanjRomDesc[] = {
	{ "rcm23a.bin",    0x80000, 0xefd96cb2, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "rcm22a.bin",    0x80000, 0x8729a689, BRF_ESS | BRF_PRG }, //  1
	{ "rcm21a.bin",    0x80000, 0x517ccde2, BRF_ESS | BRF_PRG }, //  2

  // graphics:
	{ "rcm_01.rom",    0x80000, 0x6ecdf13f, BRF_GRA },
	{ "rcm_02.rom",    0x80000, 0x944d4f0f, BRF_GRA },
	{ "rcm_03.rom",    0x80000, 0x36f3073c, BRF_GRA },
	{ "rcm_04.rom",    0x80000, 0x54e622ff, BRF_GRA },

	{ "rcm_05.rom",    0x80000, 0x5dd131fd, BRF_GRA },
	{ "rcm_06.rom",    0x80000, 0xf0faf813, BRF_GRA },
	{ "rcm_07.rom",    0x80000, 0x826de013, BRF_GRA },
	{ "rcm_08.rom",    0x80000, 0xfbff64cf, BRF_GRA },

	{ "rcm_10.rom",    0x80000, 0x4dc8ada9, BRF_GRA },
	{ "rcm_11.rom",    0x80000, 0xf2b9ee06, BRF_GRA },
	{ "rcm_12.rom",    0x80000, 0xfed5f203, BRF_GRA },
	{ "rcm_13.rom",    0x80000, 0x5069d4a9, BRF_GRA },

	{ "rcm_14.rom",    0x80000, 0x303be3bd, BRF_GRA },
	{ "rcm_15.rom",    0x80000, 0x4f2d372f, BRF_GRA },
	{ "rcm_16.rom",    0x80000, 0x93d97fde, BRF_GRA },
	{ "rcm_17.rom",    0x80000, 0x92371042, BRF_GRA },

	{ "rcm_09.rom",    0x20000, 0x9632d6ef, BRF_SND },
	{ "rcm_18.rom",    0x20000, 0x80f1f8aa, BRF_SND },
	{ "rcm_19.rom",    0x20000, 0xf257dbe1, BRF_SND },
};


STD_ROM_PICK(Rockmanj) STD_ROM_FN(Rockmanj)

struct BurnDriver BurnDrvCpsRockmanj = {
	"rockmanj", "megaman", NULL, "1995",
	"Rockman - the power battle (950922 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,RockmanjRomInfo,RockmanjRomName,DrvInputInfo, megamanDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
