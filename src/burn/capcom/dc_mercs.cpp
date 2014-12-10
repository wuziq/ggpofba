// Mercs

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

  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"  },
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Shot"       , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Special"    , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},

  {"P3 Coin"       , BIT_DIGITAL, CpsInp177+6, "p3 coin"},
  {"P3 Start"      , BIT_DIGITAL, CpsInp177+7, "p3 start" },
  {"P3 Up"         , BIT_DIGITAL, CpsInp177+3, "p3 up"    },
  {"P3 Down"       , BIT_DIGITAL, CpsInp177+2, "p3 down"  },
  {"P3 Left"       , BIT_DIGITAL, CpsInp177+1, "p3 left"  },
  {"P3 Right"      , BIT_DIGITAL, CpsInp177+0, "p3 right" },
  {"P3 Shot"       , BIT_DIGITAL, CpsInp177+4, "p3 fire 1"},
  {"P3 Special"    , BIT_DIGITAL, CpsInp177+5, "p3 fire 2"},

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"},
  {"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo mercsDIPList[]=
{
	// Defaults
	{0x1b, 0xff, 0xff, 0x00, NULL                },
	{0x1c, 0xff, 0xff, 0x00, NULL                },
	{0x1d, 0xff, 0xff, 0x00, NULL                },

	// Dip A
	{0   , 0xfe, 0   , 8   , "Coinage"                },
	{0x1b, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x1b, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x1b, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x1b, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x1b, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x1b, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x1b, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x1b, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

//	{0   , 0xfe, 0   , 8   , "Unknown"                },
//	{0x1b, 0x01, 0x38, 0x38, "0"                      },
//	{0x1b, 0x01, 0x38, 0x30, "1"                      },
//	{0x1b, 0x01, 0x38, 0x28, "2"                      },
//	{0x1b, 0x01, 0x38, 0x00, "3"                      },
//	{0x1b, 0x01, 0x38, 0x08, "4"                      },
//	{0x1b, 0x01, 0x38, 0x10, "5"                      },
//	{0x1b, 0x01, 0x38, 0x18, "6"                      },
//	{0x1b, 0x01, 0x38, 0x20, "7"                      },

	{0   , 0xfe, 0   , 2   , "2C to Start, 1 to Cont" },
	{0x1b, 0x01, 0x40, 0x00, "Off"                    },
	{0x1b, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x1b, 0x01, 0x80, 0x00, "Off"               },
//	{0x1b, 0x01, 0x80, 0x80, "On"                },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Game Level"            },
	{0x1c, 0x01, 0x07, 0x00, "1 (Easiest)"           },
	{0x1c, 0x01, 0x07, 0x01, "2"                     },
	{0x1c, 0x01, 0x07, 0x02, "3"                     },
	{0x1c, 0x01, 0x07, 0x03, "4"                     },
	{0x1c, 0x01, 0x07, 0x04, "5"                     },
	{0x1c, 0x01, 0x07, 0x05, "6"                     },
	{0x1c, 0x01, 0x07, 0x06, "7"                     },
	{0x1c, 0x01, 0x07, 0x07, "8 (Hardest)"           },

	{0   , 0xfe, 0   , 2   , "Coin Shooter"          },
	{0x1c, 0x01, 0x08, 0x08, "1 Shooter"             },
	{0x1c, 0x01, 0x08, 0x00, "3 Shooter"             },

	{0   , 0xfe, 0   , 2   , "Game Player"           },
	{0x1c, 0x01, 0x10, 0x10, "2 Player"              },
	{0x1c, 0x01, 0x10, 0x00, "3 Player"              },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x1c, 0x01, 0x20, 0x00, "Off"               },
//	{0x1c, 0x01, 0x20, 0x20, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x1c, 0x01, 0x40, 0x00, "Off"               },
//	{0x1c, 0x01, 0x40, 0x40, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x1c, 0x01, 0x80, 0x00, "Off"               },
//	{0x1c, 0x01, 0x80, 0x80, "On"                },

	// Dip C
//	{0   , 0xfe, 0   , 8   , "Unknown"                },
//	{0x1d, 0x01, 0x07, 0x07, "0"                      },
//	{0x1d, 0x01, 0x07, 0x06, "1"                      },
//	{0x1d, 0x01, 0x07, 0x05, "2"                      },
//	{0x1d, 0x01, 0x07, 0x00, "3"                      },
//	{0x1d, 0x01, 0x07, 0x01, "4"                      },
//	{0x1d, 0x01, 0x07, 0x02, "5"                      },
//	{0x1d, 0x01, 0x07, 0x03, "6"                      },
//	{0x1d, 0x01, 0x07, 0x04. "7"                      },

	{0   , 0xfe, 0   , 2   , "Freeze"            },
	{0x1d, 0x01, 0x08, 0x00, "Off"               },
	{0x1d, 0x01, 0x08, 0x08, "On"                },

	{0   , 0xfe, 0   , 2   , "Display FlipFlop"  },
	{0x1d, 0x01, 0x10, 0x00, "Off"               },
	{0x1d, 0x01, 0x10, 0x10, "On"                },

	{0   , 0xfe, 0   , 2   , "Demonstration Sound"},
	{0x1d, 0x01, 0x20, 0x00, "Off"               },
	{0x1d, 0x01, 0x20, 0x20, "On"                },

	{0   , 0xfe, 0   , 2   , "Continue Play"     },
	{0x1d, 0x01, 0x40, 0x00, "Off"               },
	{0x1d, 0x01, 0x40, 0x40, "On"                },
};

STDDIPINFO(mercs);


static int DrvInit()
{
  int nRet=0;

  Cps=1; Mercs=1;
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

  nCpsLcReg=0x6c; // Layer control register is at 0x70
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x08;

  // Start of Board ID improvments by KEV. 0x60,0x0402
  CpsBID[0]=0x60;
  CpsBID[1]=0x04;
  CpsBID[2]=0x02;

  StartScroll[SCROLL_2]=0x0600;
  EndScroll[SCROLL_2]=0x5bff;
  StartScroll[SCROLL_3]=0x0700;
  EndScroll[SCROLL_3]=0x17ff;

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

  StartScroll[SCROLL_2]=0;
  EndScroll[SCROLL_2]=0xffff;
  StartScroll[SCROLL_3]=0;
  EndScroll[SCROLL_3]=0xffff;

  CpsExit();
  nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0; Mercs=0;
  return 0;
}


//=============
//Mercs (World)
//=============

// Rom information
static struct BurnRomInfo MercsRomDesc[] = {
	{ "so2_30e.rom",   0x20000, 0xe17f9bf7, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "so2_35e.rom",   0x20000, 0x78e63575, BRF_ESS | BRF_PRG }, // 1 odd
	{ "so2_31e.rom",   0x20000, 0x51204d36, BRF_ESS | BRF_PRG }, // 2 even
	{ "so2_36e.rom",   0x20000, 0x9cfba8b4, BRF_ESS | BRF_PRG }, // 3 odd
	{ "so2_32.rom",    0x80000, 0x2eb5cf0c, BRF_ESS | BRF_PRG }, // 4 swapped

  // graphics:
	{ "so2_gfx6.rom",  0x80000, 0xaa6102af, BRF_GRA },			 // 5
	{ "so2_gfx8.rom",  0x80000, 0x839e6869, BRF_GRA },
	{ "so2_gfx2.rom",  0x80000, 0x597c2875, BRF_GRA },
	{ "so2_gfx4.rom",  0x80000, 0x912a9ca0, BRF_GRA },

	{ "so2_24.rom",    0x20000, 0x3f254efe, BRF_GRA },			 // 9
	{ "so2_14.rom",    0x20000, 0xf5a8905e, BRF_GRA },
	{ "so2_26.rom",    0x20000, 0xf3aa5a4a, BRF_GRA },
	{ "so2_16.rom",    0x20000, 0xb43cd1a8, BRF_GRA },

	{ "so2_20.rom",    0x20000, 0x8ca751a3, BRF_GRA },			 // 13
	{ "so2_10.rom",    0x20000, 0xe9f569fd, BRF_GRA },
	{ "so2_22.rom",    0x20000, 0xfce9a377, BRF_GRA },
	{ "so2_12.rom",    0x20000, 0xb7df8a06, BRF_GRA },

  // z80 rom
	{ "so2_09.rom",    0x10000, 0xd09d7c7a, BRF_GRA },			 // 17
  // samples
	{ "so2_18.rom",    0x20000, 0xbbea1643, BRF_GRA },
	{ "so2_19.rom",    0x20000, 0xac58aa71, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Mercs) STD_ROM_FN(Mercs)

struct BurnDriver BurnDrvCpsMercs = {
	"mercs", NULL, NULL, "1990",
	"Mercs (900302 etc)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL, 3, HARDWARE_CAPCOM_CPS1,
	NULL,MercsRomInfo,MercsRomName,DrvInputInfo, mercsDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};

//===========
//Mercs (USA)
//===========

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo MercsuRomDesc[] = {
	{ "so2_30e.rom",   0x20000, 0xe17f9bf7, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "s02-35",        0x20000, 0x4477df61, BRF_ESS | BRF_PRG }, // 1 odd
	{ "so2_31e.rom",   0x20000, 0x51204d36, BRF_ESS | BRF_PRG }, // 2 even
	{ "so2_36e.rom",   0x20000, 0x9cfba8b4, BRF_ESS | BRF_PRG }, // 3 odd
	{ "so2_32.rom",    0x80000, 0x2eb5cf0c, BRF_ESS | BRF_PRG }, // 4 swapped

  // graphics:
	{ "so2_gfx6.rom",  0x80000, 0xaa6102af, BRF_GRA },			 // 5
	{ "so2_gfx8.rom",  0x80000, 0x839e6869, BRF_GRA },
	{ "so2_gfx2.rom",  0x80000, 0x597c2875, BRF_GRA },
	{ "so2_gfx4.rom",  0x80000, 0x912a9ca0, BRF_GRA },

	{ "so2_24.rom",    0x20000, 0x3f254efe, BRF_GRA },			 // 9
	{ "so2_14.rom",    0x20000, 0xf5a8905e, BRF_GRA },
	{ "so2_26.rom",    0x20000, 0xf3aa5a4a, BRF_GRA },
	{ "so2_16.rom",    0x20000, 0xb43cd1a8, BRF_GRA },

	{ "so2_20.rom",    0x20000, 0x8ca751a3, BRF_GRA },			 // 13
	{ "so2_10.rom",    0x20000, 0xe9f569fd, BRF_GRA },
	{ "so2_22.rom",    0x20000, 0xfce9a377, BRF_GRA },
	{ "so2_12.rom",    0x20000, 0xb7df8a06, BRF_GRA },

  // z80 rom
	{ "so2_09.rom",    0x10000, 0xd09d7c7a, BRF_GRA },			 // 17
  // samples
	{ "so2_18.rom",    0x20000, 0xbbea1643, BRF_GRA },
	{ "so2_19.rom",    0x20000, 0xac58aa71, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Mercsu) STD_ROM_FN(Mercsu)

struct BurnDriver BurnDrvCpsMercsu = {
	"mercsu", "mercs", NULL, "1990",
	"Mercs (900302 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 3, HARDWARE_CAPCOM_CPS1,
	NULL,MercsuRomInfo,MercsuRomName,DrvInputInfo, mercsDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};



// Rom information
static struct BurnRomInfo MercsuaRomDesc[] = {
	{ "so2.30a",       0x20000, 0xe4e725d7, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "so2.35a",       0x20000, 0xe7843445, BRF_ESS | BRF_PRG }, // 1 odd
	{ "so2.31a",       0x20000, 0xc0b91dea, BRF_ESS | BRF_PRG }, // 2 even
	{ "so2.36a",       0x20000, 0x591edf6c, BRF_ESS | BRF_PRG }, // 3 odd
	{ "so2_32.rom",    0x80000, 0x2eb5cf0c, BRF_ESS | BRF_PRG }, // 4 swapped

  // graphics:
	{ "so2_gfx6.rom",  0x80000, 0xaa6102af, BRF_GRA },			 // 5
	{ "so2_gfx8.rom",  0x80000, 0x839e6869, BRF_GRA },
	{ "so2_gfx2.rom",  0x80000, 0x597c2875, BRF_GRA },
	{ "so2_gfx4.rom",  0x80000, 0x912a9ca0, BRF_GRA },

	{ "so2_24.rom",    0x20000, 0x3f254efe, BRF_GRA },			 // 9
	{ "so2_14.rom",    0x20000, 0xf5a8905e, BRF_GRA },
	{ "so2_26.rom",    0x20000, 0xf3aa5a4a, BRF_GRA },
	{ "so2_16.rom",    0x20000, 0xb43cd1a8, BRF_GRA },

	{ "so2_20.rom",    0x20000, 0x8ca751a3, BRF_GRA },			 // 13
	{ "so2_10.rom",    0x20000, 0xe9f569fd, BRF_GRA },
	{ "so2_22.rom",    0x20000, 0xfce9a377, BRF_GRA },
	{ "so2_12.rom",    0x20000, 0xb7df8a06, BRF_GRA },

  // z80 rom
	{ "so2_09.rom",    0x10000, 0xd09d7c7a, BRF_GRA },			 // 17
  // samples
	{ "so2_18.rom",    0x20000, 0xbbea1643, BRF_GRA },
	{ "so2_19.rom",    0x20000, 0xac58aa71, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Mercsua) STD_ROM_FN(Mercsua)


struct BurnDriver BurnDrvCpsMercsua = {
	"mercsua", "mercs", NULL, "1990",
	"Mercs (900608 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 3, HARDWARE_CAPCOM_CPS1,
	NULL,MercsuaRomInfo,MercsuaRomName,DrvInputInfo, mercsDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};

//=============
//Mercs (Japan)
//=============

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo MercsjRomDesc[] = {
	{ "so2_30e.rom",   0x20000, 0xe17f9bf7, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "so2_42.bin",    0x20000, 0x2c3884c6, BRF_ESS | BRF_PRG }, // 1 odd
	{ "so2_31e.rom",   0x20000, 0x51204d36, BRF_ESS | BRF_PRG }, // 2 even
	{ "so2_36e.rom",   0x20000, 0x9cfba8b4, BRF_ESS | BRF_PRG }, // 3 odd
	{ "so2_32.rom",    0x80000, 0x2eb5cf0c, BRF_ESS | BRF_PRG }, // 4 swapped

  // graphics:
	{ "so2_gfx6.rom",  0x80000, 0xaa6102af, BRF_GRA },			 // 5
	{ "so2_gfx8.rom",  0x80000, 0x839e6869, BRF_GRA },
	{ "so2_gfx2.rom",  0x80000, 0x597c2875, BRF_GRA },
	{ "so2_gfx4.rom",  0x80000, 0x912a9ca0, BRF_GRA },

	{ "so2_24.rom",    0x20000, 0x3f254efe, BRF_GRA },			 // 9
	{ "so2_14.rom",    0x20000, 0xf5a8905e, BRF_GRA },
	{ "so2_26.rom",    0x20000, 0xf3aa5a4a, BRF_GRA },
	{ "so2_16.rom",    0x20000, 0xb43cd1a8, BRF_GRA },

	{ "so2_20.rom",    0x20000, 0x8ca751a3, BRF_GRA },			 // 13
	{ "so2_10.rom",    0x20000, 0xe9f569fd, BRF_GRA },
	{ "so2_22.rom",    0x20000, 0xfce9a377, BRF_GRA },
	{ "so2_12.rom",    0x20000, 0xb7df8a06, BRF_GRA },

  // z80 rom
	{ "so2_09.rom",    0x10000, 0xd09d7c7a, BRF_GRA },			 // 17
  // samples
	{ "so2_18.rom",    0x20000, 0xbbea1643, BRF_GRA },
	{ "so2_19.rom",    0x20000, 0xac58aa71, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Mercsj) STD_ROM_FN(Mercsj)

struct BurnDriver BurnDrvCpsMercsj = {
	"mercsj", "mercs", NULL, "1990",
	"Senjo no Ookami II (Ookami 2 900302 Japan)\0", NULL, "Capcom", "CPS1",
	L"\u6226\u5834\u306E\u72FC II (Ookami 2 900302 Japan)\0Senjo no Ookami II (Ookami 2 900302 Japan)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 3, HARDWARE_CAPCOM_CPS1,
	NULL,MercsjRomInfo,MercsjRomName,DrvInputInfo, mercsDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};

