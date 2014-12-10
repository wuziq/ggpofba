// U.N. Squadron (Area 88)

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp018+0, "p1 coin"},
  {"P1 Start"      , BIT_DIGITAL, CpsInp018+4, "p1 start"},
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Shot"       , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Special"    , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Fire 3"     , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Shot"       , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Special"    , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Fire 3"     , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"},
  {"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},

};

STDINPUTINFO(Drv);

static struct BurnDIPInfo unsquadDIPList[]=
{
	// Defaults
	{0x15, 0xff, 0xff, 0x00, NULL                },
	{0x16, 0xff, 0xff, 0x00, NULL                },
	{0x17, 0xff, 0xff, 0x00, NULL                },

	// Dip A
        {0   , 0xfe, 0   , 7   , "Coin A"            },
	{0x15, 0x01, 0x07, 0x06, "4 Coins 1 Credit"  },
	{0x15, 0x01, 0x07, 0x05, "3 Coins 1 Credit"  },
	{0x15, 0x01, 0x07, 0x04, "2 Coins 1 Credit"  },
	{0x15, 0x01, 0x07, 0x00, "1 Coin 1 Credit"   },
	{0x15, 0x01, 0x07, 0x01, "1 Coin 2 Credits"  },
	{0x15, 0x01, 0x07, 0x02, "1 Coin 3 Credits"  },
	{0x15, 0x01, 0x07, 0x03, "1 Coin 4 Credits"  },

        {0   , 0xfe, 0   , 7   , "Coin B"            },
	{0x15, 0x01, 0x38, 0x30, "4 Coins 1 Credit"  },
	{0x15, 0x01, 0x38, 0x28, "3 Coins 1 Credit"  },
	{0x15, 0x01, 0x38, 0x20, "2 Coins 1 Credit"  },
	{0x15, 0x01, 0x38, 0x00, "1 Coin 1 Credit"   },
	{0x15, 0x01, 0x38, 0x08, "1 Coin 2 Credits"  },
	{0x15, 0x01, 0x38, 0x10, "1 Coin 3 Credits"  },
	{0x15, 0x01, 0x38, 0x18, "1 Coin 4 Credits"  },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x15, 0x01, 0x40, 0x00, "Off"               },
//	{0x15, 0x01, 0x40, 0x40, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x15, 0x01, 0x80, 0x00, "Off"               },
//	{0x15, 0x01, 0x80, 0x80, "On"                },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Difficulty"        },
	{0x16, 0x01, 0x07, 0x00, "Super Easy"            },
	{0x16, 0x01, 0x07, 0x01, "Very Easy"            },
	{0x16, 0x01, 0x07, 0x02, "Easy"            },
	{0x16, 0x01, 0x07, 0x03, "Normal"         },
	{0x16, 0x01, 0x07, 0x04, "Difficult"       },
	{0x16, 0x01, 0x07, 0x05, "Very Difficult"       },
	{0x16, 0x01, 0x07, 0x06, "Super Difficult"       },
	{0x16, 0x01, 0x07, 0x07, "Ultra Super Difficult"    },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x16, 0x01, 0x08, 0x00, "Off"               },
//	{0x16, 0x01, 0x08, 0x08, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x16, 0x01, 0x10, 0x00, "Off"               },
//	{0x16, 0x01, 0x10, 0x10, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x16, 0x01, 0x20, 0x00, "Off"               },
//	{0x16, 0x01, 0x20, 0x20, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x16, 0x01, 0x40, 0x00, "Off"               },
//	{0x16, 0x01, 0x40, 0x40, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x16, 0x01, 0x80, 0x00, "Off"               },
//	{0x16, 0x01, 0x80, 0x80, "On"                },

	// Dip C
//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x17, 0x01, 0x01, 0x00, "Off"               },
//	{0x17, 0x01, 0x01, 0x01, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x17, 0x01, 0x02, 0x00, "Off"               },
//	{0x17, 0x01, 0x02, 0x02, "On"                },

	{0   , 0xfe, 0   , 2   , "Free Play"         },
	{0x17, 0x01, 0x04, 0x00, "Off"               },
	{0x17, 0x01, 0x04, 0x04, "On"                },

	{0   , 0xfe, 0   , 2   , "Stop"              },
	{0x17, 0x01, 0x08, 0x00, "Off"               },
	{0x17, 0x01, 0x08, 0x08, "On"                },

	{0   , 0xfe, 0   , 2   , "Flip"              },
	{0x17, 0x01, 0x10, 0x00, "Off"               },
	{0x17, 0x01, 0x10, 0x10, "On"                },

	{0   , 0xfe, 0   , 2   , "Demo Sound"        },
	{0x17, 0x01, 0x20, 0x00, "Off"               },
	{0x17, 0x01, 0x20, 0x20, "On"                },

	{0   , 0xfe, 0   , 2   , "Continue"          },
	{0x17, 0x01, 0x40, 0x00, "No"                },
	{0x17, 0x01, 0x40, 0x40, "Yes"               },
};

STDDIPINFO(unsquad);


static int DrvInit()
{
  int nRet=0;
  Cps=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 4*0x080000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =  0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000001,0,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x000000,1,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040001,2,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040000,3,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,4,1); if (nRet!=0) return 1; // Already byteswapped
  // Load graphics roms
  CpsLoadTiles(CpsGfx,5);

  nCpsLcReg=0x66;		// Layer control register is at 0x66
  CpsLayEn[1]=0x20;		// Layer enable 1 is different
  CpsLayEn[2]=0x10;
  CpsLayEn[3]=0x08;		// Layer enable is different

  MaskAddr[0]=0x68;
  MaskAddr[1]=0x6a;
  MaskAddr[2]=0x6c;
  MaskAddr[3]=0x6e;

  StartScroll[SCROLL_3]=1;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,9,1);
  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd,10,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

static int DrvExit()
{
  CpsRunExit();

  StartScroll[SCROLL_3]=0;

  CpsExit();
  nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0;
  return 0;
}

// ===================
// U.N. Squadron (USA)
// ===================

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo UnsquadRomDesc[] = {
	{ "unsquad.30",    0x20000, 0x24d8f88d, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "unsquad.35",    0x20000, 0x8b954b59, BRF_ESS | BRF_PRG }, // 1 odd
	{ "unsquad.31",    0x20000, 0x33e9694b, BRF_ESS | BRF_PRG }, // 2 even
	{ "unsquad.36",    0x20000, 0x7cc8fb9e, BRF_ESS | BRF_PRG }, // 3 odd
	{ "unsquad.32",    0x80000, 0xae1d7fb0, BRF_ESS | BRF_PRG }, // 4 both

  // graphics:
	{ "unsquad.05",    0x80000, 0xbf4575d8, BRF_GRA },			 // 5
	{ "unsquad.07",    0x80000, 0xa02945f4, BRF_GRA },
	{ "unsquad.01",    0x80000, 0x5965ca8d, BRF_GRA },
	{ "unsquad.03",    0x80000, 0xac6db17d, BRF_GRA },

  // z80 rom
	{ "unsquad.09",    0x10000, 0xf3dd1367, BRF_GRA },			 // 9
  // samples
	{ "unsquad.18",    0x20000, 0x584b43a9, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Unsquad); STD_ROM_FN(Unsquad);

struct BurnDriver BurnDrvCpsUnsquad = {
	"unsquad", NULL, NULL, "1989",
	"U.N. Squadron (US)\0", NULL, "Daipro / Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,UnsquadRomInfo,UnsquadRomName,DrvInputInfo, unsquadDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

// ===============
// Area 88 (Japan)
// ===============

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo Area88RomDesc[] = {
	{ "ar36.bin",      0x20000, 0x65030392, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "ar42.bin",      0x20000, 0xc48170de, BRF_ESS | BRF_PRG }, // 1 odd
	{ "unsquad.31",    0x20000, 0x33e9694b, BRF_ESS | BRF_PRG }, // 2 even
	{ "unsquad.36",    0x20000, 0x7cc8fb9e, BRF_ESS | BRF_PRG }, // 3 odd
	{ "unsquad.32",    0x80000, 0xae1d7fb0, BRF_ESS | BRF_PRG }, // 4 both

  // graphics:
	{ "unsquad.05",    0x80000, 0xbf4575d8, BRF_GRA },			 // 5
	{ "unsquad.07",    0x80000, 0xa02945f4, BRF_GRA },
	{ "unsquad.01",    0x80000, 0x5965ca8d, BRF_GRA },
	{ "unsquad.03",    0x80000, 0xac6db17d, BRF_GRA },


  // z80 rom
	{ "unsquad.09",    0x10000, 0xf3dd1367, BRF_GRA },			 // 9
  // samples
	{ "unsquad.18",    0x20000, 0x584b43a9, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Area88); STD_ROM_FN(Area88);

struct BurnDriver BurnDrvCpsArea88 = {
	"area88", "unsquad", NULL, "1989",
	"Area 88 (Japan)\0", NULL, "Daipro / Capcom", "CPS1",
	L"\u30A8\u30EA\u30A2\uFF18\uFF18 (Japan)\0Area 88 (Japan)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Area88RomInfo,Area88RomName,DrvInputInfo, unsquadDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
