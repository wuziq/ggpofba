// Pnickies

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp018+0, "p1 coin"},
  {"P1 Start"      , BIT_DIGITAL, CpsInp018+4, "p1 start"},
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Turn 1"     , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Turn 2"     , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Turn 1"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Turn 2"     , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"},
  {"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo pnickjDIPList[]=
{
	// Defaults
	{0x13, 0xff, 0xff, 0x00, NULL                },
	{0x14, 0xff, 0xff, 0x00, NULL                },
	{0x15, 0xff, 0xff, 0x00, NULL                },

	// Dip A
	{0   , 0xfe, 0   , 8   , "Coin"                   },
	{0x13, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x13, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x13, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x13, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x13, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x13, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x13, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x13, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 2   , "Chuter Mode"            },
	{0x13, 0x01, 0x08, 0x00, "1 Chuter"               },
	{0x13, 0x01, 0x08, 0x08, "2 Chuter"               },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x13, 0x01, 0x10, 0x00, "Off"               },
//	{0x13, 0x01, 0x10, 0x10, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x13, 0x01, 0x20, 0x00, "Off"               },
//	{0x13, 0x01, 0x20, 0x20, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x13, 0x01, 0x40, 0x00, "Off"               },
//	{0x13, 0x01, 0x40, 0x40, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x13, 0x01, 0x80, 0x00, "Off"               },
//	{0x13, 0x01, 0x80, 0x80, "On"                },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Difficulty"        },
	{0x14, 0x01, 0x07, 0x00, "Easiest"           },
	{0x14, 0x01, 0x07, 0x01, "Very Easy"         },
	{0x14, 0x01, 0x07, 0x02, "Easy"              },
	{0x14, 0x01, 0x07, 0x03, "Normal"            },
	{0x14, 0x01, 0x07, 0x04, "Hard"              },
	{0x14, 0x01, 0x07, 0x05, "Very Hard"         },
	{0x14, 0x01, 0x07, 0x06, "Hardest"           },
	{0x14, 0x01, 0x07, 0x07, "Master Level"      },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x14, 0x01, 0x08, 0x00, "Off"               },
//	{0x14, 0x01, 0x08, 0x08, "On"                },

//	{0   , 0xfe, 0   , 4   , "Unknown"           },
//	{0x14, 0x01, 0x30, 0x00, "1"                 },
//	{0x14, 0x01, 0x30, 0x10, "2"                 },
//	{0x14, 0x01, 0x30, 0x20, "3"                 },
//	{0x14, 0x01, 0x30, 0x30, "4"                 },

	{0   , 0xfe, 0   , 4   , "Vs. Play Mode"     },
	{0x14, 0x01, 0xc0, 0x00, "1 Game  Match"     },
	{0x14, 0x01, 0xc0, 0x40, "3 Games Match"     },
	{0x14, 0x01, 0xc0, 0x80, "5 Games Match"     },
	{0x14, 0x01, 0xc0, 0xc0, "7 Games Match"     },

	// Dip C
//	{0   , 0xfe, 0   , 4   , "Unknown"                },
//	{0x15, 0x01, 0x03, 0x00, "1"                      },
//	{0x15, 0x01, 0x03, 0x01, "2"                      },
//	{0x15, 0x01, 0x03, 0x02, "3"                      },
//	{0x15, 0x01, 0x03, 0x03, "4"                      },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x15, 0x01, 0x04, 0x00, "Off"               },
//	{0x15, 0x01, 0x04, 0x04, "On"                },

	{0   , 0xfe, 0   , 2   , "Stop Mode"         },
	{0x15, 0x01, 0x08, 0x00, "Off"               },
	{0x15, 0x01, 0x08, 0x08, "On"                },

	{0   , 0xfe, 0   , 2   , "Flip"              },
	{0x15, 0x01, 0x10, 0x00, "Off"               },
	{0x15, 0x01, 0x10, 0x10, "On"                },

	{0   , 0xfe, 0   , 2   , "Demo Sound"        },
	{0x15, 0x01, 0x20, 0x00, "Off"               },
	{0x15, 0x01, 0x20, 0x20, "On"                },

	{0   , 0xfe, 0   , 2   , "Continue"          },
	{0x15, 0x01, 0x40, 0x00, "Off"               },
	{0x15, 0x01, 0x40, 0x40, "On"                },
};

STDDIPINFO(pnickj);


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

  // Load graphics roms
  CpsLoadTilesByte(CpsGfx, 2);
  CpsLoadTilesByte(CpsGfx+(8*0x020000), 2+8);

  nCpsLcReg=0x66; // Layer control register is at 0x66
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x08;

  MaskAddr[0]=0x68;
  MaskAddr[1]=0x6a;
  MaskAddr[2]=0x6c;
  MaskAddr[3]=0x6e;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,18,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,19,1);
  nRet=BurnLoadRom(CpsAd+0x20000,20,1);


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

//================
//Pnickies (Japan)
//================

// Rom information
static struct BurnRomInfo PnickjRomDesc[] = {
	{ "pnij36.bin",    0x20000, 0x2d4ffb2b, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "pnij42.bin",    0x20000, 0xc085dfaf, BRF_ESS | BRF_PRG }, // 1 odd

  // graphics:
	{ "pnij09.bin",    0x20000, 0x48177b0a, BRF_GRA },			 // 2
	{ "pnij01.bin",    0x20000, 0x01a0f311, BRF_GRA },
	{ "pnij13.bin",    0x20000, 0x406451b0, BRF_GRA },
	{ "pnij05.bin",    0x20000, 0x8c515dc0, BRF_GRA },
	{ "pnij26.bin",    0x20000, 0xe2af981e, BRF_GRA },			 // 6
	{ "pnij18.bin",    0x20000, 0xf17a0e56, BRF_GRA },
	{ "pnij38.bin",    0x20000, 0xeb75bd8c, BRF_GRA },
	{ "pnij32.bin",    0x20000, 0x84560bef, BRF_GRA },
	{ "pnij10.bin",    0x20000, 0xc2acc171, BRF_GRA },			 // 10
	{ "pnij02.bin",    0x20000, 0x0e21fc33, BRF_GRA },
	{ "pnij14.bin",    0x20000, 0x7fe59b19, BRF_GRA },
	{ "pnij06.bin",    0x20000, 0x79f4bfe3, BRF_GRA },
	{ "pnij27.bin",    0x20000, 0x83d5cb0e, BRF_GRA },			 // 14
	{ "pnij19.bin",    0x20000, 0xaf08b230, BRF_GRA },
	{ "pnij39.bin",    0x20000, 0x70fbe579, BRF_GRA },
	{ "pnij33.bin",    0x20000, 0x3ed2c680, BRF_GRA },

  // z80 rom
	{ "pnij17.bin",    0x10000, 0xe86f787a, BRF_GRA },			 // 18
  // samples
	{ "pnij24.bin",    0x20000, 0x5092257d, BRF_GRA },
	{ "pnij25.bin",    0x20000, 0x22109aaa, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Pnickj) STD_ROM_FN(Pnickj)

struct BurnDriver BurnDrvCpsPnickj = {
	"pnickj", NULL, NULL, "1994",
	"Pnickies (940608 Japan)\0", NULL, "Compile (Capcom license)", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,PnickjRomInfo,PnickjRomName,DrvInputInfo, pnickjDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
