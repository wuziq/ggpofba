// Varth - Operation Thunderstorm

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
  {"P1 Bomb"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Fire 3"     , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Shot"       , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Bomb"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Fire 3"     , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"},
  {"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo varthDIPList[]=
{
	// Defaults
	{0x15, 0xff, 0xff, 0x00, NULL                },
	{0x16, 0xff, 0xff, 0x00, NULL                },
	{0x17, 0xff, 0xff, 0x00, NULL                },

	// Dip A
	{0   , 0xfe, 0   , 8   , "Coin A"                 },
	{0x15, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x15, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x15, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x15, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x15, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x15, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x15, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x15, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 8   , "Coin B"                 },
	{0x15, 0x01, 0x38, 0x38, "4 Coins 1 Credit"       },
	{0x15, 0x01, 0x38, 0x30, "3 Coins 1 Credit"       },
	{0x15, 0x01, 0x38, 0x28, "2 Coins 1 Credit"       },
	{0x15, 0x01, 0x38, 0x00, "1 Coin 1 Credit"        },
	{0x15, 0x01, 0x38, 0x08, "1 Coin 2 Credits"       },
	{0x15, 0x01, 0x38, 0x10, "1 Coin 3 Credits"       },
	{0x15, 0x01, 0x38, 0x18, "1 Coin 4 Credits"       },
	{0x15, 0x01, 0x38, 0x20, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 2   , "Continue Coin"          },
	{0x15, 0x01, 0x40, 0x00, "Off"                    },
	{0x15, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x15, 0x01, 0x80, 0x00, "Off"               },
//	{0x15, 0x01, 0x80, 0x80, "On"                },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Difficulty"             },
	{0x16, 0x01, 0x07, 0x00, "Easiest"                 },
	{0x16, 0x01, 0x07, 0x01, "Easy 1"                 },
	{0x16, 0x01, 0x07, 0x02, "Easy 2"                 },
	{0x16, 0x01, 0x07, 0x03, "Normal"              },
	{0x16, 0x01, 0x07, 0x04, "Difficult"            },
	{0x16, 0x01, 0x07, 0x05, "Very Difficult"            },
	{0x16, 0x01, 0x07, 0x06, "Hard"            },
	{0x16, 0x01, 0x07, 0x07, "Hardest"         },

	{0   , 0xfe, 0   , 4   , "Bonus Life"             },
	{0x16, 0x01, 0x18, 0x00, "600k and every 1400k"             },
	{0x16, 0x01, 0x18, 0x08, "600k, 2000k and every 4500k"           },
	{0x16, 0x01, 0x18, 0x10, "1200k, 3500k"},
	{0x16, 0x01, 0x18, 0x18, "2000k only"   },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x16, 0x01, 0x20, 0x00, "Off"                    },
//	{0x16, 0x01, 0x20, 0x20, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x16, 0x01, 0x40, 0x00, "Off"                    },
//	{0x16, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x16, 0x01, 0x80, 0x00, "Off"                    },
//	{0x16, 0x01, 0x80, 0x80, "On"                     },

	// Dip C
	{0   , 0xfe, 0   , 4   , "Lives"                  },
	{0x17, 0x01, 0x03, 0x01, "1"                      },
	{0x17, 0x01, 0x03, 0x02, "2"                      },
	{0x17, 0x01, 0x03, 0x00, "3"                      },
	{0x17, 0x01, 0x03, 0x03, "4"                      },

	{0   , 0xfe, 0   , 2   , "Free Play"              },
	{0x17, 0x01, 0x04, 0x00, "Off"                    },
	{0x17, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Stop"                   },
	{0x17, 0x01, 0x08, 0x00, "Off"                    },
	{0x17, 0x01, 0x08, 0x08, "On"                     },

	{0   , 0xfe, 0   , 2   , "Flip Screen"            },
	{0x17, 0x01, 0x10, 0x00, "Off"                    },
	{0x17, 0x01, 0x10, 0x10, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sound"             },
	{0x17, 0x01, 0x20, 0x00, "Off"                    },
	{0x17, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 2   , "Continue"               },
	{0x17, 0x01, 0x40, 0x00, "Off"                    },
	{0x17, 0x01, 0x40, 0x40, "On"                     },
};

STDDIPINFO(varth);


static int DrvExit()
{

  CpsRunExit();

  CpsExit();
  nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0; Varth=0;

  return 0;
}

// ======================================
// Varth - Operation Thunderstorm (World)
// ======================================

static int VarthInit()
{
  int nRet=0;

  Cps=1; Varth=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 4*0x080000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000001,0,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x000000,1,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040001,2,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040000,3,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080001,4,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,5,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x0c0001,6,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x0c0000,7,2); if (nRet!=0) return 1;

  // Load graphics roms
  CpsLoadTiles(CpsGfx,8);

  nCpsLcReg=0x6e; // Layer control register is at 0x6e
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x0c;
  CpsLayEn[3]=0x0c;

  MaskAddr[0]=0x66;
  MaskAddr[1]=0x70;
  MaskAddr[2]=0x68;
  MaskAddr[3]=0x62;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,12,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,13,1);
  nRet=BurnLoadRom(CpsAd+0x20000,14,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

// Rom information
static struct BurnRomInfo VarthRomDesc[] = {
	{ "vae_30b.rom",   0x20000, 0xadb8d391, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "vae_35b.rom",   0x20000, 0x44e5548f, BRF_ESS | BRF_PRG }, // 1 odd
	{ "vae_31b.rom",   0x20000, 0x1749a71c, BRF_ESS | BRF_PRG }, // 2 even
	{ "vae_36b.rom",   0x20000, 0x5f2e2450, BRF_ESS | BRF_PRG }, // 3 odd
	{ "vae_28b.rom",   0x20000, 0xe524ca50, BRF_ESS | BRF_PRG }, // 4 even 68000 code
	{ "vae_33b.rom",   0x20000, 0xc0bbf8c9, BRF_ESS | BRF_PRG }, // 5 odd
	{ "vae_29b.rom",   0x20000, 0x6640996a, BRF_ESS | BRF_PRG }, // 6 even
	{ "vae_34b.rom",   0x20000, 0xfa59be8a, BRF_ESS | BRF_PRG }, // 7 odd

  // graphics:
	{ "va_gfx5.rom",   0x80000, 0xb1fb726e, BRF_GRA },			 // 8
	{ "va_gfx7.rom",   0x80000, 0x4c6588cd, BRF_GRA },
	{ "va_gfx1.rom",   0x80000, 0x0b1ace37, BRF_GRA },
	{ "va_gfx3.rom",   0x80000, 0x44dfe706, BRF_GRA },

  // z80 rom
	{ "va_09.rom",     0x10000, 0x7a99446e, BRF_GRA },			 // 12
  // samples
	{ "va_18.rom",     0x20000, 0xde30510e, BRF_GRA },
	{ "va_19.rom",     0x20000, 0x0610a4ac, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Varth) STD_ROM_FN(Varth)

struct BurnDriver BurnDrvCpsVarth = {
	"varth", NULL, NULL, "1992",
	"Varth - operation thunderstorm (920714 etc)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_CAPCOM_CPS1,
	NULL,VarthRomInfo,VarthRomName,DrvInputInfo, varthDIPInfo,
	VarthInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};

static struct BurnRomInfo Varthr1RomDesc[] = {
	{ "vae_30a.rom",   0x20000, 0x7fcd0091, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "vae_35a.rom",   0x20000, 0x35cf9509, BRF_ESS | BRF_PRG }, // 1 odd
	{ "vae_31a.rom",   0x20000, 0x15e5ee81, BRF_ESS | BRF_PRG }, // 2 even
	{ "vae_36a.rom",   0x20000, 0x153a201e, BRF_ESS | BRF_PRG }, // 3 odd
	{ "vae_28a.rom",   0x20000, 0x7a0e0d25, BRF_ESS | BRF_PRG }, // 4 even 68000 code
	{ "vae_33a.rom",   0x20000, 0xf2365922, BRF_ESS | BRF_PRG }, // 5 odd
	{ "vae_29a.rom",   0x20000, 0x5e2cd2c3, BRF_ESS | BRF_PRG }, // 6 even
	{ "vae_34a.rom",   0x20000, 0x3d9bdf83, BRF_ESS | BRF_PRG }, // 7 odd

  // graphics:
	{ "va_gfx5.rom",   0x80000, 0xb1fb726e, BRF_GRA },			 // 8
	{ "va_gfx7.rom",   0x80000, 0x4c6588cd, BRF_GRA },
	{ "va_gfx1.rom",   0x80000, 0x0b1ace37, BRF_GRA },
	{ "va_gfx3.rom",   0x80000, 0x44dfe706, BRF_GRA },

  // z80 rom
	{ "va_09.rom",     0x10000, 0x7a99446e, BRF_GRA },			 // 12
  // samples
	{ "va_18.rom",     0x20000, 0xde30510e, BRF_GRA },
	{ "va_19.rom",     0x20000, 0x0610a4ac, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Varthr1) STD_ROM_FN(Varthr1)

struct BurnDriver BurnDrvCpsVarthr1 = {
	"varthr1", "varth", NULL, "1992",
	"Varth - operation thunderstorm (920612 etc)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_CAPCOM_CPS1,
	NULL,Varthr1RomInfo,Varthr1RomName,DrvInputInfo, varthDIPInfo,
	VarthInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};

// ======================================
// Varth - Operation Thunderstorm (Japan)
// ======================================

static int VarthjInit()
{
  int nRet=0;

  Cps=1; Varth=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 4*0x080000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000001,0,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x000000,1,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040001,2,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040000,3,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080001,4,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,5,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x0c0001,6,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x0c0000,7,2); if (nRet!=0) return 1;

  // Load graphics roms
  CpsLoadTiles(CpsGfx,8);

  nCpsLcReg=0x60; // Layer control register is at 0x60
  CpsLayEn[1]=0x20;
  CpsLayEn[2]=0x06;
  CpsLayEn[3]=0x06;

  // Protection enable code by KEV - Looks like only the JAP version uses this
  CpsMProt[0]=0x4e;
  CpsMProt[1]=0x4c;
  CpsMProt[2]=0x4a;
  CpsMProt[3]=0x48;

  MaskAddr[0]=0x6e;
  MaskAddr[1]=0x6c;
  MaskAddr[2]=0x6a;
  MaskAddr[3]=0x68;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,12,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,13,1);
  nRet=BurnLoadRom(CpsAd+0x20000,14,1);

  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

// Rom information
static struct BurnRomInfo VarthjRomDesc[] = {
	{ "vaj36b.bin",    0x20000, 0x1d798d6a, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "vaj42b.bin",    0x20000, 0x0f720233, BRF_ESS | BRF_PRG }, // 1 odd
	{ "vaj37b.bin",    0x20000, 0x24414b17, BRF_ESS | BRF_PRG }, // 2 even
	{ "vaj43b.bin",    0x20000, 0x34b4b06c, BRF_ESS | BRF_PRG }, // 3 odd
	{ "vaj34b.bin",    0x20000, 0x87c79aed, BRF_ESS | BRF_PRG }, // 4 even 68000 code
	{ "vaj40b.bin",    0x20000, 0x210b4bd0, BRF_ESS | BRF_PRG }, // 5 odd
	{ "vaj35b.bin",    0x20000, 0x6b0da69f, BRF_ESS | BRF_PRG }, // 6 even
	{ "vaj41b.bin",    0x20000, 0x6542c8a4, BRF_ESS | BRF_PRG }, // 7 odd

  // graphics:
	{ "va_gfx5.rom",   0x80000, 0xb1fb726e, BRF_GRA },			 // 8
	{ "va_gfx7.rom",   0x80000, 0x4c6588cd, BRF_GRA },
	{ "va_gfx1.rom",   0x80000, 0x0b1ace37, BRF_GRA },
	{ "va_gfx3.rom",   0x80000, 0x44dfe706, BRF_GRA },

  // z80 rom
	{ "va_09.rom",     0x10000, 0x7a99446e, BRF_GRA },			 // 12
  // samples
	{ "va_18.rom",     0x20000, 0xde30510e, BRF_GRA },
	{ "va_19.rom",     0x20000, 0x0610a4ac, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Varthj) STD_ROM_FN(Varthj)

struct BurnDriver BurnDrvCpsVarthj = {
	"varthj", "varth", NULL, "1992",
	"Varth - operation thunderstorm (920714 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 2 ,HARDWARE_CAPCOM_CPS1,
	NULL,VarthjRomInfo,VarthjRomName,DrvInputInfo, varthDIPInfo,
	VarthjInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};

// ====================================
// Varth - Operation Thunderstorm (USA)
// ====================================

static int VarthuInit()
{
  int nRet=0;

  Cps=1; Varth=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 4*0x080000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000000,0,1); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080001,1,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,2,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x0c0001,3,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x0c0000,4,2); if (nRet!=0) return 1;

  // Load graphics roms
  CpsLoadTiles(CpsGfx,5);

  nCpsLcReg=0x6e; // Layer control register is at 0x6e
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x0c;
  CpsLayEn[3]=0x0c;

  MaskAddr[0]=0x66;
  MaskAddr[1]=0x70;
  MaskAddr[2]=0x68;
  MaskAddr[3]=0x62;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,9,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,10,1);
  nRet=BurnLoadRom(CpsAd+0x20000,11,1);

  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

// Rom information
static struct BurnRomInfo VarthuRomDesc[] = {
	{ "vau23a.bin",    0x80000, 0xfbe68726, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "vae_28a.rom",   0x20000, 0x7a0e0d25, BRF_ESS | BRF_PRG }, // 1 even 68000 code
	{ "vae_33a.rom",   0x20000, 0xf2365922, BRF_ESS | BRF_PRG }, // 2 odd
	{ "vae_29a.rom",   0x20000, 0x5e2cd2c3, BRF_ESS | BRF_PRG }, // 3 even
	{ "vae_34a.rom",   0x20000, 0x3d9bdf83, BRF_ESS | BRF_PRG }, // 4 odd

  // graphics:
	{ "va_gfx5.rom",   0x80000, 0xb1fb726e, BRF_GRA },			 // 5
	{ "va_gfx7.rom",   0x80000, 0x4c6588cd, BRF_GRA },
	{ "va_gfx1.rom",   0x80000, 0x0b1ace37, BRF_GRA },
	{ "va_gfx3.rom",   0x80000, 0x44dfe706, BRF_GRA },

  // z80 rom
	{ "va_09.rom",     0x10000, 0x7a99446e, BRF_GRA },			 // 9
  // samples
	{ "va_18.rom",     0x20000, 0xde30510e, BRF_GRA },
	{ "va_19.rom",     0x20000, 0x0610a4ac, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Varthu) STD_ROM_FN(Varthu)

struct BurnDriver BurnDrvCpsVarthu = {
	"varthu", "varth", NULL, "1992",
	"Varth - operation thunderstorm (920612 USA)\0", NULL, "Capcom (Romstar license)", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_CAPCOM_CPS1,
	NULL,VarthuRomInfo,VarthuRomName,DrvInputInfo, varthDIPInfo,
	VarthuInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};
