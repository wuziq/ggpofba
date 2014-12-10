// Nemo

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp018+0, "p1 coin"  },
  {"P1 Start"      , BIT_DIGITAL, CpsInp018+4, "p1 start" },
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"    },
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"  },
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"  },
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right" },
  {"P1 Attack"     , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Jump"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Fire 3"     , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"  },
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start" },
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"    },
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"  },
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"  },
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right" },
  {"P2 Attack"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Jump"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Fire 3"     , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"    },
  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"     },
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"},
  {"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo nemoDIPList[]=
{
	// Defaults
	{0x15, 0xff, 0xff, 0x00, NULL                },
	{0x16, 0xff, 0xff, 0x00, NULL                },
	{0x17, 0xff, 0xff, 0x00, NULL                },

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

	{0   , 0xfe, 0   , 2   , "Continue Coin"          },
	{0x15, 0x01, 0x40, 0x00, "Off"                    },
	{0x15, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x15, 0x01, 0x80, 0x00, "Off"                    },
//	{0x15, 0x01, 0x80, 0x80, "On"                     },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Game Level"             },
	{0x16, 0x01, 0x07, 0x00, "Very Easy (3)"          },
	{0x16, 0x01, 0x07, 0x01, "Easy (4)"               },
	{0x16, 0x01, 0x07, 0x02, "Easy (5)"               },
	{0x16, 0x01, 0x07, 0x03, "Normal (6)"             },
	{0x16, 0x01, 0x07, 0x04, "Difficult (7)"          },
	{0x16, 0x01, 0x07, 0x05, "Difficult (8)"          },
	{0x16, 0x01, 0x07, 0x06, "Difficult (9)"          },
	{0x16, 0x01, 0x07, 0x07, "Very Difficult (a)"     },

	{0   , 0xfe, 0   , 3   , "Life"                   },
	{0x16, 0x01, 0x18, 0x18, "Minimum"                },
	{0x16, 0x01, 0x18, 0x00, "Medium"                 },
	{0x16, 0x01, 0x18, 0x10, "Maximum"                },

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
//	{0   , 0xfe, 0   , 4   , "Unknown"                },
//	{0x17, 0x01, 0x03, 0x00, "1"                      },
//	{0x17, 0x01, 0x03, 0x01, "2"                      },
//	{0x17, 0x01, 0x03, 0x02, "3"                      },
//	{0x17, 0x01, 0x03, 0x03, "4"                      },

	{0   , 0xfe, 0   , 2   , "Free Play"              },
	{0x17, 0x01, 0x04, 0x00, "Off"                    },
	{0x17, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Freeze"                 },
	{0x17, 0x01, 0x08, 0x00, "Off"                    },
	{0x17, 0x01, 0x08, 0x08, "On"                     },

	{0   , 0xfe, 0   , 2   , "Flip"                   },
	{0x17, 0x01, 0x10, 0x00, "Off"                    },
	{0x17, 0x01, 0x10, 0x10, "On"                     },

	{0   , 0xfe, 0   , 2   , "Sound"                  },
	{0x17, 0x01, 0x20, 0x00, "Off"                    },
	{0x17, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 2   , "Continue"               },
	{0x17, 0x01, 0x40, 0x00, "Off"                    },
	{0x17, 0x01, 0x40, 0x40, "On"                     },
};

STDDIPINFO(nemo);


static int DrvInit()
{
  int nRet=0;
  Cps=1;
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
  nRet=BurnLoadRom(CpsRom+0x080000,4,1); if (nRet!=0) return 1; // Already byteswapped

  // Load graphics roms
  CpsLoadTiles(CpsGfx,5);

  nCpsLcReg=0x42; // Layer control register is at 0x42
  CpsLayEn[1]=0x04;
  CpsLayEn[2]=0x22;
  CpsLayEn[3]=0x22;

  // Start of Board ID improvments by KEV. 0x4e,0x0405
  CpsBID[0]=0x4e;
  CpsBID[1]=0x04;
  CpsBID[2]=0x05;

  MaskAddr[0]=0x44;
  MaskAddr[1]=0x46;
  MaskAddr[2]=0x48;
  MaskAddr[3]=0x4a;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,9,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,10,1);
  nRet=BurnLoadRom(CpsAd+0x20000,11,1);


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

//============
//Nemo (World)
//============

// Rom information
static struct BurnRomInfo NemoRomDesc[] = {
	{ "nme_30a.rom",   0x20000, 0xd2c03e56, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "nme_35a.rom",   0x20000, 0x5fd31661, BRF_ESS | BRF_PRG }, // 1 odd
	{ "nme_31a.rom",   0x20000, 0xb2bd4f6f, BRF_ESS | BRF_PRG }, // 2 even
	{ "nme_36a.rom",   0x20000, 0xee9450e3, BRF_ESS | BRF_PRG }, // 3 odd
	{ "nm_32.rom",     0x80000, 0xd6d1add3, BRF_ESS | BRF_PRG }, // 4 both

  // graphics:
	{ "nm_gfx5.rom",   0x80000, 0x487b8747, BRF_GRA },			 // 5
	{ "nm_gfx7.rom",   0x80000, 0x203dc8c6, BRF_GRA },
	{ "nm_gfx1.rom",   0x80000, 0x9e878024, BRF_GRA },
	{ "nm_gfx3.rom",   0x80000, 0xbb01e6b6, BRF_GRA },

  // z80 rom
	{ "nm_09.rom",     0x10000, 0x0f4b0581, BRF_GRA },			 // 9
  // samples
	{ "nm_18.rom",     0x20000, 0xbab333d4, BRF_GRA },
	{ "nm_19.rom",     0x20000, 0x2650a0a8, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Nemo) STD_ROM_FN(Nemo)

struct BurnDriver BurnDrvCpsNemo = {
	"nemo", NULL, NULL, "1990",
	"Nemo (90 11 30 etc)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,NemoRomInfo,NemoRomName,DrvInputInfo, nemoDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//============
//Nemo (Japan)
//============

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo NemojRomDesc[] = {
	{ "nm36.bin",      0x20000, 0xdaeceabb, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "nm42.bin",      0x20000, 0x55024740, BRF_ESS | BRF_PRG }, // 1 odd
	{ "nm37.bin",      0x20000, 0x619068b6, BRF_ESS | BRF_PRG }, // 2 even
	{ "nm43.bin",      0x20000, 0xa948a53b, BRF_ESS | BRF_PRG }, // 3 odd
	{ "nm_32.rom",     0x80000, 0xd6d1add3, BRF_ESS | BRF_PRG }, // 4 both

  // graphics:
	{ "nm_gfx5.rom",   0x80000, 0x487b8747, BRF_GRA },			 // 5
	{ "nm_gfx7.rom",   0x80000, 0x203dc8c6, BRF_GRA },
	{ "nm_gfx1.rom",   0x80000, 0x9e878024, BRF_GRA },
	{ "nm_gfx3.rom",   0x80000, 0xbb01e6b6, BRF_GRA },

  // z80 rom
	{ "nm_09.rom",     0x10000, 0x0f4b0581, BRF_GRA },			 // 9
  // samples
	{ "nm_18.rom",     0x20000, 0xbab333d4, BRF_GRA },
	{ "nm_19.rom",     0x20000, 0x2650a0a8, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Nemoj) STD_ROM_FN(Nemoj)

struct BurnDriver BurnDrvCpsNemoj = {
	"nemoj", "nemo", NULL, "1990",
	"Nemo (90 11 20 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,NemojRomInfo,NemojRomName,DrvInputInfo, nemoDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
