// Strider (Hiryu)

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
  {"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"       },
  {"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"       },
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"       },
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo striderDIPList[]=
{
	// Defaults
	{0x15, 0xff, 0xff, 0x00, NULL                     },
	{0x16, 0xff, 0xff, 0x00, NULL                     },
	{0x17, 0xff, 0xff, 0x00, NULL                     },

	// Dip A
	{0   , 0xfe, 0   , 8   , "A Side"                 },
	{0x15, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x15, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x15, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x15, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x15, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x15, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x15, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x15, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 8   , "B Side"                 },
	{0x15, 0x01, 0x38, 0x38, "4 Coins 1 Credit"       },
	{0x15, 0x01, 0x38, 0x30, "3 Coins 1 Credit"       },
	{0x15, 0x01, 0x38, 0x28, "2 Coins 1 Credit"       },
	{0x15, 0x01, 0x38, 0x00, "1 Coin 1 Credit"        },
	{0x15, 0x01, 0x38, 0x08, "1 Coin 2 Credits"       },
	{0x15, 0x01, 0x38, 0x10, "1 Coin 3 Credits"       },
	{0x15, 0x01, 0x38, 0x18, "1 Coin 4 Credits"       },
	{0x15, 0x01, 0x38, 0x20, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 3   , "Table Type"             },
	{0x15, 0x01, 0xc0, 0x00, "Upright 1P"            },
	{0x15, 0x01, 0xc0, 0x40, "Upright 2P"            },
	{0x15, 0x01, 0xc0, 0x80, "Cocktail"               },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Game Level"             },
	{0x16, 0x01, 0x07, 0x03, "1"                 },
	{0x16, 0x01, 0x07, 0x02, "2"                 },
	{0x16, 0x01, 0x07, 0x01, "3"              },
	{0x16, 0x01, 0x07, 0x00, "4"                 },
	{0x16, 0x01, 0x07, 0x04, "5"            },
	{0x16, 0x01, 0x07, 0x05, "6"            },
	{0x16, 0x01, 0x07, 0x06, "7"            },
	{0x16, 0x01, 0x07, 0x07, "8"         },

//	{0   , 0xfe, 0   , 2   , "Continue Coinage?"      },
//	{0x16, 0x01, 0x08, 0x00, "1 Coin"                 },
//	{0x16, 0x01, 0x08, 0x08, "2 Coins"                },

	{0   , 0xfe, 0   , 4   , "Bonus"                  },
	{0x16, 0x01, 0x30, 0x20, "20k, 60k"               },
	{0x16, 0x01, 0x30, 0x30, "30k, 60k"               },
	{0x16, 0x01, 0x30, 0x00, "20k, 40k, 60k"          },
	{0x16, 0x01, 0x30, 0x10, "30k, 50k, 70k"          },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x16, 0x01, 0x40, 0x00, "Off"                    },
//	{0x16, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x16, 0x01, 0x80, 0x00, "Off"                    },
//	{0x16, 0x01, 0x80, 0x80, "On"                     },

	// Dip C
	{0   , 0xfe, 0   , 4   , "Player"                 },
	{0x17, 0x01, 0x03, 0x00, "3"                      },
	{0x17, 0x01, 0x03, 0x01, "4"                      },
	{0x17, 0x01, 0x03, 0x02, "5"                      },
	{0x17, 0x01, 0x03, 0x03, "6"                      },

	{0   , 0xfe, 0   , 2   , "Freeze"                 },
	{0x17, 0x01, 0x04, 0x00, "Off"                    },
	{0x17, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Free Play"              },
	{0x17, 0x01, 0x08, 0x00, "Off"                    },
	{0x17, 0x01, 0x08, 0x08, "On"                     },

	{0   , 0xfe, 0   , 2   , "Flip"                   },
	{0x17, 0x01, 0x10, 0x00, "Off"                    },
	{0x17, 0x01, 0x10, 0x10, "On"                     },

	{0   , 0xfe, 0   , 2   , "Sound"                  },
	{0x17, 0x01, 0x20, 0x20, "Off"                    },
	{0x17, 0x01, 0x20, 0x00, "On"                     },

	{0   , 0xfe, 0   , 2   , "Continue"               },
	{0x17, 0x01, 0x40, 0x40, "Off"                    },
	{0x17, 0x01, 0x40, 0x00, "On"                     },
};

STDDIPINFO(strider);


static int DrvExit()
{
  CpsRunExit();

  CpsExit();
  nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0;
  return 0;
}

// ===========================
// Strider (USA + Japan Set 2)
// ===========================

static int StriderInit()
{
  int nRet=0;
  Cps=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen=   0x400000 + 0x2000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;
  CpsStar = CpsGfx + 0x400000;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000001,0,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x000000,1,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040001,2,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040000,3,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,4,1); if (nRet!=0) return 1; // Already byteswapped

  // Load graphics roms
  CpsLoadTiles(CpsGfx         ,5);
  CpsLoadTiles(CpsGfx+0x200000,9);

  nCpsLcReg=0x66;		// Layer control register is at 0x66
  CpsLayEn[1]=0x02;		// Layer enable 1 is different
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x08;		// Layer enable is different
  // Enable starfield layers
  CpsLayEn[4]=0x10;
  CpsLayEn[5]=0x20;

  CpsLoadStars(CpsStar, 5);

  // Offset to Scroll tiles
  nCpsGfxScroll[1]=0x200000;
  nCpsGfxScroll[3]=0x200000;

  MaskAddr[0]=0x68;
  MaskAddr[1]=0x6a;
  MaskAddr[2]=0x6c;
  MaskAddr[3]=0x6e;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,13,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,14,1);
  nRet=BurnLoadRom(CpsAd+0x20000,15,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

// =============
// Strider (USA)
// =============

// Rom information
static struct BurnRomInfo StriderRomDesc[] = {
	{ "strider.30",    0x20000, 0xda997474, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "strider.35",    0x20000, 0x5463aaa3, BRF_ESS | BRF_PRG }, // 1 odd
	{ "strider.31",    0x20000, 0xd20786db, BRF_ESS | BRF_PRG }, // 2 even
	{ "strider.36",    0x20000, 0x21aa2863, BRF_ESS | BRF_PRG }, // 3 odd
	{ "strider.32",    0x80000, 0x9b3cfc08, BRF_ESS | BRF_PRG }, // 4 both

  // graphics:
	{ "strider.06",    0x80000, 0x4eee9aea, BRF_GRA },			 // 5
	{ "strider.08",    0x80000, 0x2d7f21e4, BRF_GRA },
	{ "strider.02",    0x80000, 0x7705aa46, BRF_GRA },
	{ "strider.04",    0x80000, 0x5b18b722, BRF_GRA },
	{ "strider.05",    0x80000, 0x005f000b, BRF_GRA },			 // 9
	{ "strider.07",    0x80000, 0xb9441519, BRF_GRA },
	{ "strider.01",    0x80000, 0xb7d04e8b, BRF_GRA },
	{ "strider.03",    0x80000, 0x6b4713b4, BRF_GRA },

  // z80 rom
	{ "strider.09",    0x10000, 0x2ed403bc, BRF_GRA },			 // 13
  // samples
	{ "strider.18",    0x20000, 0x4386bc80, BRF_GRA },
	{ "strider.19",    0x20000, 0x444536d7, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Strider); STD_ROM_FN(Strider);

struct BurnDriver BurnDrvCpsStrider = {
	"strider", NULL, NULL, "1989",
	"Strider (US set 1)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,StriderRomInfo,StriderRomName,DrvInputInfo, striderDIPInfo,
	StriderInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

// Rom information
static struct BurnRomInfo StridruaRomDesc[] = {
	{ "strid.30",      0x20000, 0x66aec273, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "strid.35",      0x20000, 0x50e0e865, BRF_ESS | BRF_PRG }, // 1 odd
	{ "strid.31",      0x20000, 0xeae93bd1, BRF_ESS | BRF_PRG }, // 2 even
	{ "strid.36",      0x20000, 0xb904a31d, BRF_ESS | BRF_PRG }, // 3 odd
	{ "strider.32",    0x80000, 0x9b3cfc08, BRF_ESS | BRF_PRG }, // 4 both

  // graphics:
	{ "strider.06",    0x80000, 0x4eee9aea, BRF_GRA },			 // 5
	{ "strider.08",    0x80000, 0x2d7f21e4, BRF_GRA },
	{ "strider.02",    0x80000, 0x7705aa46, BRF_GRA },
	{ "strider.04",    0x80000, 0x5b18b722, BRF_GRA },
	{ "strider.05",    0x80000, 0x005f000b, BRF_GRA },			 // 9
	{ "strider.07",    0x80000, 0xb9441519, BRF_GRA },
	{ "strider.01",    0x80000, 0xb7d04e8b, BRF_GRA },
	{ "strider.03",    0x80000, 0x6b4713b4, BRF_GRA },
  // z80 rom
	{ "strid.09",      0x10000, 0x08d63519, BRF_GRA },			 // 13
  // samples
	{ "strider.18",    0x20000, 0x4386bc80, BRF_GRA },
	{ "strider.19",    0x20000, 0x444536d7, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Stridrua); STD_ROM_FN(Stridrua);
struct BurnDriver BurnDrvCpsStridrua = {
	"stridrua", "strider", NULL, "1989",
	"Strider (US set 2)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,StridruaRomInfo,StridruaRomName,DrvInputInfo, striderDIPInfo,
	StriderInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};


// ===========================
// Strider Hiryu (Japan Set 1)
// ===========================

static int StriderjInit()
{
  int nRet=0;
  Cps=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen=   0x400000 + 0x8000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;
  CpsStar = CpsGfx + 0x400000;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000000,0,1); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,1,1); if (nRet!=0) return 1; // Already byteswapped

  // Load graphics roms
  CpsLoadTiles(CpsGfx         ,2);
  CpsLoadTiles(CpsGfx+0x200000,6);

  // Offset to Scroll tiles
  nCpsGfxScroll[1]=0x200000;
  nCpsGfxScroll[3]=0x200000;

  // Enable starfield layers
  CpsLayEn[4]=0x10;
  CpsLayEn[5]=0x20;

  CpsLoadStars(CpsStar, 2);

  MaskAddr[0]=0x68;
  MaskAddr[1]=0x6a;
  MaskAddr[2]=0x6c;
  MaskAddr[3]=0x6e;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,10,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,11,1);
  nRet=BurnLoadRom(CpsAd+0x20000,12,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo StriderjRomDesc[] = {
	{ "sthj23.bin",    0x80000, 0x046e7b12, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "strider.32",    0x80000, 0x9b3cfc08, BRF_ESS | BRF_PRG }, // 1 both

  // graphics:
	{ "strider.06",    0x80000, 0x4eee9aea, BRF_GRA },			 // 2
	{ "strider.08",    0x80000, 0x2d7f21e4, BRF_GRA },
	{ "strider.02",    0x80000, 0x7705aa46, BRF_GRA },
	{ "strider.04",    0x80000, 0x5b18b722, BRF_GRA },
	{ "strider.05",    0x80000, 0x005f000b, BRF_GRA },			 // 6
	{ "strider.07",    0x80000, 0xb9441519, BRF_GRA },
	{ "strider.01",    0x80000, 0xb7d04e8b, BRF_GRA },
	{ "strider.03",    0x80000, 0x6b4713b4, BRF_GRA },

  // z80 rom
	{ "strider.09",    0x10000, 0x2ed403bc, BRF_GRA },			 // 10
  // samples
	{ "strider.18",    0x20000, 0x4386bc80, BRF_GRA },
	{ "strider.19",    0x20000, 0x444536d7, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Striderj) STD_ROM_FN(Striderj)

struct BurnDriver BurnDrvCpsStriderj = {
	"striderj", "strider", NULL, "1989",
	"Strider Hiryu (Japan set 1)\0", NULL, "Capcom", "CPS1",
	L"\u30B9\u30C8\u30E9\u30A4\u30C0\u30FC\u98DB\u7ADC (Japan set 1)\0Strider Hiryu (Japan set 1)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,StriderjRomInfo,StriderjRomName,DrvInputInfo, striderDIPInfo,
	StriderjInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

// ===========================
// Strider Hiryu (Japan Set 2)
// ===========================

// Rom information
static struct BurnRomInfo StridrjaRomDesc[] = {
	{ "sth36.bin",     0x20000, 0x53c7b006, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "sth42.bin",     0x20000, 0x4037f65f, BRF_ESS | BRF_PRG }, // 1 odd
	{ "sth37.bin",     0x20000, 0x80e8877d, BRF_ESS | BRF_PRG }, // 2 even
	{ "sth43.bin",     0x20000, 0x6b3fa466, BRF_ESS | BRF_PRG }, // 3 odd
	{ "strider.32",    0x80000, 0x9b3cfc08, BRF_ESS | BRF_PRG }, // 4 both

  // graphics:
	{ "strider.06",    0x80000, 0x4eee9aea, BRF_GRA },			 // 5
	{ "strider.08",    0x80000, 0x2d7f21e4, BRF_GRA },
	{ "strider.02",    0x80000, 0x7705aa46, BRF_GRA },
	{ "strider.04",    0x80000, 0x5b18b722, BRF_GRA },
	{ "strider.05",    0x80000, 0x005f000b, BRF_GRA },			 // 9
	{ "strider.07",    0x80000, 0xb9441519, BRF_GRA },
	{ "strider.01",    0x80000, 0xb7d04e8b, BRF_GRA },
	{ "strider.03",    0x80000, 0x6b4713b4, BRF_GRA },

  // z80 rom
	{ "strider.09",    0x10000, 0x2ed403bc, BRF_GRA },			 // 13
  // samples
	{ "strider.18",    0x20000, 0x4386bc80, BRF_GRA },
	{ "strider.19",    0x20000, 0x444536d7, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Stridrja); STD_ROM_FN(Stridrja);

struct BurnDriver BurnDrvCpsStridrja = {
	"stridrja", "strider", NULL, "1989",
	"Strider Hiryu (Japan set 2)\0", NULL, "Capcom", "CPS1",
	L"\u30B9\u30C8\u30E9\u30A4\u30C0\u30FC\u98DB\u7ADC (Japan set 2)\0Strider Hiryu (Japan set 2)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,StridrjaRomInfo,StridrjaRomName,DrvInputInfo, striderDIPInfo,
	StriderInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
