// Willow

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp018+0, "p1 coin"},
  {"P1 Start"      , BIT_DIGITAL, CpsInp018+4, "p1 start"},
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Attack"     , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Jump"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Fire 3"     , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Attack"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Jump"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Fire 3"     , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"},
  {"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo willowDIPList[]=
{
	// Defaults
	{0x15, 0xff, 0xff, 0x00, NULL                },
	{0x16, 0xff, 0xff, 0x00, NULL                },
	{0x17, 0xff, 0xff, 0x00, NULL                },

	// Dip A
        {0   , 0xfe, 0   , 7   , "A Side"            },
	{0x15, 0x01, 0x07, 0x06, "4 Coins 1 Credit"  },
	{0x15, 0x01, 0x07, 0x05, "3 Coins 1 Credit"  },
	{0x15, 0x01, 0x07, 0x04, "2 Coins 1 Credit"  },
	{0x15, 0x01, 0x07, 0x00, "1 Coin 1 Credit"   },
	{0x15, 0x01, 0x07, 0x01, "1 Coin 2 Credits"  },
	{0x15, 0x01, 0x07, 0x02, "1 Coin 3 Credits"  },
	{0x15, 0x01, 0x07, 0x03, "1 Coin 4 Credits"  },

        {0   , 0xfe, 0   , 7   , "B Side"            },
	{0x15, 0x01, 0x38, 0x30, "4 Coins 1 Credit"  },
	{0x15, 0x01, 0x38, 0x28, "3 Coins 1 Credit"  },
	{0x15, 0x01, 0x38, 0x20, "2 Coins 1 Credit"  },
	{0x15, 0x01, 0x38, 0x00, "1 Coin 1 Credit"   },
	{0x15, 0x01, 0x38, 0x08, "1 Coin 2 Credits"  },
	{0x15, 0x01, 0x38, 0x10, "1 Coin 3 Credits"  },
	{0x15, 0x01, 0x38, 0x18, "1 Coin 4 Credits"  },

        {0   , 0xfe, 0   , 3   , "Table Type"        },
	{0x15, 0x01, 0xc0, 0x00, "Upright 1P"        },
	{0x15, 0x01, 0xc0, 0x40, "Upright 2P"        },
	{0x15, 0x01, 0xc0, 0xc0, "Cocktail"          },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Game Level"        },
	{0x16, 0x01, 0x07, 0x03, "Very Easy"         },
	{0x16, 0x01, 0x07, 0x02, "Easy 2"            },
	{0x16, 0x01, 0x07, 0x01, "Easy 1"            },
	{0x16, 0x01, 0x07, 0x00, "Normal"            },
	{0x16, 0x01, 0x07, 0x04, "Difficult 1"       },
	{0x16, 0x01, 0x07, 0x05, "Difficult 2"       },
	{0x16, 0x01, 0x07, 0x06, "Difficult 3"       },
	{0x16, 0x01, 0x07, 0x07, "Very Difficult"    },

	{0   , 0xfe, 0   , 4   , "Nando Speed"       },
	{0x16, 0x01, 0x18, 0x00, "Normal"            },
	{0x16, 0x01, 0x18, 0x08, "Slow"              },
	{0x16, 0x01, 0x18, 0x10, "Fast"              },
	{0x16, 0x01, 0x18, 0x18, "Very Fast"         },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x16, 0x01, 0x20, 0x00, "Off"               },
//	{0x16, 0x01, 0x20, 0x20, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x16, 0x01, 0x40, 0x00, "Off"               },
//	{0x16, 0x01, 0x40, 0x40, "On"                },

	{0   , 0xfe, 0   , 2   , "Stage Magic Continue"},
	{0x16, 0x01, 0x80, 0x00, "Off"               },
	{0x16, 0x01, 0x80, 0x80, "On"                },

	// Dip C
	{0   , 0xfe, 0   , 4   , "Player"            },
	{0x17, 0x01, 0x03, 0x01, "1 Player"          },
	{0x17, 0x01, 0x03, 0x00, "2 Players"         },
	{0x17, 0x01, 0x03, 0x02, "3 Players"         },
	{0x17, 0x01, 0x03, 0x03, "4 Players"         },

	{0   , 0xfe, 0   , 4   , "Life"              },
	{0x17, 0x01, 0x0c, 0x0c, "2"                 },
	{0x17, 0x01, 0x0c, 0x00, "3"                 },
	{0x17, 0x01, 0x0c, 0x04, "4"                 },
	{0x17, 0x01, 0x0c, 0x08, "5"                 },

	{0   , 0xfe, 0   , 2   , "Screen"            },
	{0x17, 0x01, 0x10, 0x00, "Off"               },
	{0x17, 0x01, 0x10, 0x10, "On"                },

	{0   , 0xfe, 0   , 2   , "Sound"             },
	{0x17, 0x01, 0x20, 0x20, "Off"               },
	{0x17, 0x01, 0x20, 0x00, "On"                },

	{0   , 0xfe, 0   , 2   , "Continue"          },
	{0x17, 0x01, 0x40, 0x40, "Off"               },
	{0x17, 0x01, 0x40, 0x00, "On"                },
};

STDDIPINFO(willow);


static int DrvInit()
{
  int nRet=0;
  Cps=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 6*0x080000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000001,0,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x000000,1,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040001,2,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040000,3,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,4,1); if (nRet!=0) return 1;

  // Load graphics roms
  CpsLoadTiles(CpsGfx         ,5);
  CpsLoadTilesByte(CpsGfx+0x200000,9);

  nCpsGfxScroll[2]=0x200000;

  nCpsLcReg=0x70; // Layer control register is at 0x70
  CpsLayEn[1]=0x20;
  CpsLayEn[2]=0x10;
  CpsLayEn[3]=0x08;

  MaskAddr[0]=0x6e;
  MaskAddr[1]=0x6c;
  MaskAddr[2]=0x6a;
  MaskAddr[3]=0x68;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,17,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,18,1);
  nRet=BurnLoadRom(CpsAd+0x20000,19,1);


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

//=======================
//Willow (US)
//=======================

// Rom information
static struct BurnRomInfo WillowRomDesc[] = {
	{ "wlu_30.rom",    0x20000, 0xd604dbb1, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "willow-u.35",   0x20000, 0x7a791e77, BRF_ESS | BRF_PRG }, // 1 odd
	{ "wlu_31.rom",    0x20000, 0x0eb48a83, BRF_ESS | BRF_PRG }, // 2 even
	{ "wlu_36.rom",    0x20000, 0x36100209, BRF_ESS | BRF_PRG }, // 3 odd
	{ "wl_32.rom",     0x80000, 0xdfd9f643, BRF_ESS | BRF_PRG }, // 4 swapped

  // graphics:
	{ "wl_gfx5.rom",   0x80000, 0xafa74b73, BRF_GRA },			 // 5
	{ "wl_gfx7.rom",   0x80000, 0x12a0dc0b, BRF_GRA },
	{ "wl_gfx1.rom",   0x80000, 0xc6f2abce, BRF_GRA },
	{ "wl_gfx3.rom",   0x80000, 0x4aa4c6d3, BRF_GRA },

	{ "wl_24.rom",     0x20000, 0x6f0adee5, BRF_GRA },			 // 9
	{ "wl_14.rom",     0x20000, 0x9cf3027d, BRF_GRA },
	{ "wl_26.rom",     0x20000, 0xf09c8ecf, BRF_GRA },
	{ "wl_16.rom",     0x20000, 0xe35407aa, BRF_GRA },

	{ "wl_20.rom",     0x20000, 0x84992350, BRF_GRA },			 // 13
	{ "wl_10.rom",     0x20000, 0xb87b5a36, BRF_GRA },
	{ "wl_22.rom",     0x20000, 0xfd3f89f0, BRF_GRA },
	{ "wl_12.rom",     0x20000, 0x7da49d69, BRF_GRA },

  // z80 rom
	{ "wl_09.rom",     0x10000, 0xf6b3d060, BRF_GRA },			 // 17
  // samples
	{ "wl_18.rom",     0x20000, 0xbde23d4d, BRF_GRA },
	{ "wl_19.rom",     0x20000, 0x683898f5, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Willow); STD_ROM_FN(Willow);

struct BurnDriver BurnDrvCpsWillow = {
	"willow", NULL, NULL, "1989",
	"Willow (US)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,WillowRomInfo,WillowRomName,DrvInputInfo, willowDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=======================
//Willow (Japan, English)
//=======================

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo WillowjeRomDesc[] = {
	{ "wlu_30.rom",    0x20000, 0xd604dbb1, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "wlu_35.rom",    0x20000, 0xdaee72fe, BRF_ESS | BRF_PRG }, // 1 odd
	{ "wlu_31.rom",    0x20000, 0x0eb48a83, BRF_ESS | BRF_PRG }, // 2 even
	{ "wlu_36.rom",    0x20000, 0x36100209, BRF_ESS | BRF_PRG }, // 3 odd
	{ "wl_32.rom",     0x80000, 0xdfd9f643, BRF_ESS | BRF_PRG }, // 4 swapped

  // graphics:
	{ "wl_gfx5.rom",   0x80000, 0xafa74b73, BRF_GRA },			 // 5
	{ "wl_gfx7.rom",   0x80000, 0x12a0dc0b, BRF_GRA },
	{ "wl_gfx1.rom",   0x80000, 0xc6f2abce, BRF_GRA },
	{ "wl_gfx3.rom",   0x80000, 0x4aa4c6d3, BRF_GRA },

	{ "wl_24.rom",     0x20000, 0x6f0adee5, BRF_GRA },			 // 9
	{ "wl_14.rom",     0x20000, 0x9cf3027d, BRF_GRA },
	{ "wl_26.rom",     0x20000, 0xf09c8ecf, BRF_GRA },
	{ "wl_16.rom",     0x20000, 0xe35407aa, BRF_GRA },

	{ "wl_20.rom",     0x20000, 0x84992350, BRF_GRA },			 // 13
	{ "wl_10.rom",     0x20000, 0xb87b5a36, BRF_GRA },
	{ "wl_22.rom",     0x20000, 0xfd3f89f0, BRF_GRA },
	{ "wl_12.rom",     0x20000, 0x7da49d69, BRF_GRA },

  // z80 rom
	{ "wl_09.rom",     0x10000, 0xf6b3d060, BRF_GRA },			 // 17
  // samples
	{ "wl_18.rom",     0x20000, 0xbde23d4d, BRF_GRA },
	{ "wl_19.rom",     0x20000, 0x683898f5, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Willowje); STD_ROM_FN(Willowje);

struct BurnDriver BurnDrvCpsWillowje = {
	"willowje", "willow", NULL, "1989",
	"Willow (Japan, English)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,WillowjeRomInfo,WillowjeRomName,DrvInputInfo, willowDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//========================
//Willow (Japan, Japanese)
//========================

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo WillowjRomDesc[] = {
	{ "wl36.bin",      0x20000, 0x2b0d7cbc, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "wl42.bin",      0x20000, 0x1ac39615, BRF_ESS | BRF_PRG }, // 1 odd
	{ "wl37.bin",      0x20000, 0x30a717fa, BRF_ESS | BRF_PRG }, // 2 even
	{ "wl43.bin",      0x20000, 0xd0dddc9e, BRF_ESS | BRF_PRG }, // 3 odd
	{ "wl_32.rom",     0x80000, 0xdfd9f643, BRF_ESS | BRF_PRG }, // 4 swapped

  // graphics:
	{ "wl_gfx5.rom",   0x80000, 0xafa74b73, BRF_GRA },			 // 5
	{ "wl_gfx7.rom",   0x80000, 0x12a0dc0b, BRF_GRA },
	{ "wl_gfx1.rom",   0x80000, 0xc6f2abce, BRF_GRA },
	{ "wl_gfx3.rom",   0x80000, 0x4aa4c6d3, BRF_GRA },

	{ "wl_24.rom",     0x20000, 0x6f0adee5, BRF_GRA },			 // 9
	{ "wl_14.rom",     0x20000, 0x9cf3027d, BRF_GRA },
	{ "wl_26.rom",     0x20000, 0xf09c8ecf, BRF_GRA },
	{ "wl_16.rom",     0x20000, 0xe35407aa, BRF_GRA },

	{ "wl_20.rom",     0x20000, 0x84992350, BRF_GRA },			 // 13
	{ "wl_10.rom",     0x20000, 0xb87b5a36, BRF_GRA },
	{ "wl_22.rom",     0x20000, 0xfd3f89f0, BRF_GRA },
	{ "wl_12.rom",     0x20000, 0x7da49d69, BRF_GRA },

  // z80 rom
	{ "wl_09.rom",     0x10000, 0xf6b3d060, BRF_GRA },			 // 17
  // samples
	{ "wl_18.rom",     0x20000, 0xbde23d4d, BRF_GRA },
	{ "wl_19.rom",     0x20000, 0x683898f5, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Willowj); STD_ROM_FN(Willowj);

struct BurnDriver BurnDrvCpsWillowj = {
	"willowj", "willow", NULL, "1989",
	"Willow (Japan, Japanese)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,WillowjRomInfo,WillowjRomName,DrvInputInfo, willowDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
