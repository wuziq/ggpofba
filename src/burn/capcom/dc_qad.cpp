// Quiz & Dragons

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp018+0, "p1 coin"},
  {"P1 Start"      , BIT_DIGITAL, CpsInp018+4, "p1 start"},
  {"P1 Answer 1"   , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Answer 2"   , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Answer 3"   , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},
  {"P1 Answer 4"   , BIT_DIGITAL, CpsInp001+7, "p1 fire 4"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start"},
  {"P2 Answer 1"   , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Answer 2"   , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Answer 3"   , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},
  {"P2 Answer 4"   , BIT_DIGITAL, CpsInp000+7, "p2 fire 4"},
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"},
  {"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo qadDIPList[]=
{
	// Defaults
	{0x0f, 0xff, 0xff, 0x00, NULL                },
	{0x10, 0xff, 0xff, 0x00, NULL                },
	{0x11, 0xff, 0xff, 0x00, NULL                },

	// Dip A
	{0   , 0xfe, 0   , 8   , "Coin"                   },
	{0x0f, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x0f, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x0f, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x0f, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x0f, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x0f, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x0f, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x0f, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x0f, 0x01, 0x08, 0x00, "Off"               },
//	{0x0f, 0x01, 0x08, 0x08, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x0f, 0x01, 0x10, 0x00, "Off"               },
//	{0x0f, 0x01, 0x10, 0x10, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x0f, 0x01, 0x20, 0x00, "Off"               },
//	{0x0f, 0x01, 0x20, 0x20, "On"                },

	{0   , 0xfe, 0   , 2   , "Continue Coin"          },
	{0x0f, 0x01, 0x40, 0x00, "Off"                    },
	{0x0f, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x0f, 0x01, 0x80, 0x00, "Off"               },
//	{0x0f, 0x01, 0x80, 0x80, "On"                },

	// Dip B
	{0   , 0xfe, 0   , 5   , "Difficulty"        },
	{0x10, 0x01, 0x07, 0x00, "Very Easy"            },
//	{0x10, 0x01, 0x07, 0x01, "Very Easy"            },
	{0x10, 0x01, 0x07, 0x02, "Easy"            },
	{0x10, 0x01, 0x07, 0x03, "Normal"         },
	{0x10, 0x01, 0x07, 0x04, "Hard"       },
	{0x10, 0x01, 0x07, 0x05, "Very Hard"       },
//	{0x10, 0x01, 0x07, 0x06, "Very Hard"       },
//	{0x10, 0x01, 0x07, 0x07, "Very Hard"    },

	{0   , 0xfe, 0   , 4   , "Wisdom of Enemy"            },
	{0x10, 0x01, 0x18, 0x00, "Low"               },
	{0x10, 0x01, 0x18, 0x08, "Normal"            },
	{0x10, 0x01, 0x18, 0x10, "High"              },
	{0x10, 0x01, 0x18, 0x18, "Brilliant"         },

	{0   , 0xfe, 0   , 3   , "Initial Vitality"  },
	{0x10, 0x01, 0xe0, 0x80, "1"                 },
//	{0x10, 0x01, 0xe0, 0xa0, "1"                 },
//	{0x10, 0x01, 0xe0, 0xc0, "1"                 },
//	{0x10, 0x01, 0xe0, 0xe0, "1"                 },
	{0x10, 0x01, 0xe0, 0x60, "2"                 },
	{0x10, 0x01, 0xe0, 0x00, "5"                 },

	// Dip C
	{0   , 0xfe, 0   , 2   , "Free Play"         },
	{0x11, 0x01, 0x04, 0x00, "Off"               },
	{0x11, 0x01, 0x04, 0x04, "On"                },

	{0   , 0xfe, 0   , 2   , "Stop"              },
	{0x11, 0x01, 0x08, 0x00, "Off"               },
	{0x11, 0x01, 0x08, 0x08, "On"                },

	{0   , 0xfe, 0   , 2   , "Flip"              },
	{0x11, 0x01, 0x10, 0x00, "Off"               },
	{0x11, 0x01, 0x10, 0x10, "On"                },

	{0   , 0xfe, 0   , 2   , "Demo Sound"        },
	{0x11, 0x01, 0x20, 0x20, "Off"               },
	{0x11, 0x01, 0x20, 0x00, "On"                },

	{0   , 0xfe, 0   , 2   , "Continue"          },
	{0x11, 0x01, 0x40, 0x40, "Off"               },
	{0x11, 0x01, 0x40, 0x00, "On"                },
};

STDDIPINFO(qad);

static struct BurnDIPInfo qadjDIPList[]=
{
	// Defaults
	{0x0f, 0xff, 0xff, 0x00, NULL                },
	{0x10, 0xff, 0xff, 0x00, NULL                },
	{0x11, 0xff, 0xff, 0x00, NULL                },

	// Dip A
	{0   , 0xfe, 0   , 8   , "Coin"                   },
	{0x0f, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x0f, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x0f, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x0f, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x0f, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x0f, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x0f, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x0f, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x0f, 0x01, 0x08, 0x00, "Off"               },
//	{0x0f, 0x01, 0x08, 0x08, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x0f, 0x01, 0x10, 0x00, "Off"               },
//	{0x0f, 0x01, 0x10, 0x10, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x0f, 0x01, 0x20, 0x00, "Off"               },
//	{0x0f, 0x01, 0x20, 0x20, "On"                },

	{0   , 0xfe, 0   , 2   , "Continue Coin"          },
	{0x0f, 0x01, 0x40, 0x00, "Off"                    },
	{0x0f, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x0f, 0x01, 0x80, 0x00, "Off"               },
//	{0x0f, 0x01, 0x80, 0x80, "On"                },

	// Dip B
	{0   , 0xfe, 0   , 5   , "Difficulty"        },
	{0x10, 0x01, 0x07, 0x00, "Very Easy"            },
//	{0x10, 0x01, 0x07, 0x01, "Very Easy"            },
	{0x10, 0x01, 0x07, 0x02, "Easy"            },
	{0x10, 0x01, 0x07, 0x03, "Normal"         },
	{0x10, 0x01, 0x07, 0x04, "Hard"       },
	{0x10, 0x01, 0x07, 0x05, "Very Hard"       },
//	{0x10, 0x01, 0x07, 0x06, "Very Hard"       },
//	{0x10, 0x01, 0x07, 0x07, "Very Hard"    },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x10, 0x01, 0x08, 0x00, "Off"               },
//	{0x10, 0x01, 0x08, 0x08, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x10, 0x01, 0x10, 0x00, "Off"               },
//	{0x10, 0x01, 0x10, 0x10, "On"                },

	{0   , 0xfe, 0   , 3   , "Initial Vitality"  },
//	{0x10, 0x01, 0xe0, 0xc0, "1"                 },
//	{0x10, 0x01, 0xe0, 0xe0, "1"                 },
	{0x10, 0x01, 0xe0, 0x60, "1"                 },
	{0x10, 0x01, 0xe0, 0xa0, "2"                 },
//	{0x10, 0x01, 0xe0, 0x80, "3"                 },
	{0x10, 0x01, 0xe0, 0x00, "3"                 },

	// Dip C
//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x11, 0x01, 0x01, 0x00, "Off"               },
//	{0x11, 0x01, 0x01, 0x01, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x11, 0x01, 0x02, 0x00, "Off"               },
//	{0x11, 0x01, 0x02, 0x02, "On"                },

	{0   , 0xfe, 0   , 2   , "Free Play"         },
	{0x11, 0x01, 0x04, 0x00, "Off"               },
	{0x11, 0x01, 0x04, 0x04, "On"                },

	{0   , 0xfe, 0   , 2   , "Stop"              },
	{0x11, 0x01, 0x08, 0x00, "Off"               },
	{0x11, 0x01, 0x08, 0x08, "On"                },

	{0   , 0xfe, 0   , 2   , "Flip"              },
	{0x11, 0x01, 0x10, 0x00, "Off"               },
	{0x11, 0x01, 0x10, 0x10, "On"                },

	{0   , 0xfe, 0   , 2   , "Demo Sound"        },
	{0x11, 0x01, 0x20, 0x00, "Off"               },
	{0x11, 0x01, 0x20, 0x20, "On"                },

	{0   , 0xfe, 0   , 2   , "Continue"          },
	{0x11, 0x01, 0x40, 0x40, "Off"               },
	{0x11, 0x01, 0x40, 0x00, "On"                },
};

STDDIPINFO(qadj);


static int DrvExit()
{


  CpsRunExit();

  CpsExit();
  nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0; Qad=0;
  return 0;
}


//====================
//Quiz & Dragons (USA)
//====================

static int QadInit()
{
  int nRet=0;
  Cps=1; Qad=1;
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

  // Load graphics roms
  CpsLoadTilesByte(CpsGfx, 4);

  nCpsLcReg=0x6c; // Layer control register is at 0x6c
  CpsLayEn[1]=0x14;
  CpsLayEn[2]=0x02;
  CpsLayEn[3]=0x14;

  // Protection enable code by KEV
  CpsMProt[0]=0x00;
  CpsMProt[1]=0x00;
  CpsMProt[2]=0x00;
  CpsMProt[3]=0x00;

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
static struct BurnRomInfo QadRomDesc[] = {
	{ "qdu_36a.rom",   0x20000, 0xde9c24a0, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "qdu_42a.rom",   0x20000, 0xcfe36f0c, BRF_ESS | BRF_PRG }, // 1 odd
	{ "qdu_37a.rom",   0x20000, 0x10d22320, BRF_ESS | BRF_PRG }, // 2 even 68000 code
	{ "qdu_43a.rom",   0x20000, 0x15e6beb9, BRF_ESS | BRF_PRG }, // 3 odd

  // graphics:
	{ "qdu_09.rom",    0x20000, 0x8c3f9f44, BRF_GRA },			 // 4
	{ "qdu_01.rom",    0x20000, 0xf688cf8f, BRF_GRA },
	{ "qdu_13.rom",    0x20000, 0xafbd551b, BRF_GRA },
	{ "qdu_05.rom",    0x20000, 0xc3db0910, BRF_GRA },
	{ "qdu_24.rom",    0x20000, 0x2f1bd0ec, BRF_GRA },			 // 8
	{ "qdu_17.rom",    0x20000, 0xa812f9e2, BRF_GRA },
	{ "qdu_38.rom",    0x20000, 0xccdddd1f, BRF_GRA },
	{ "qdu_32.rom",    0x20000, 0xa8d295d3, BRF_GRA },

  // z80 rom
	{ "qdu_23.rom",    0x10000, 0xcfb5264b, BRF_GRA },			 // 12
  // samples
	{ "qdu_30.rom",    0x20000, 0xf190da84, BRF_GRA },
	{ "qdu_31.rom",    0x20000, 0xb7583f73, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Qad) STD_ROM_FN(Qad)

struct BurnDriver BurnDrvCpsQad = {
	"qad", NULL, NULL, "1992",
	"Quiz & Dragons (capcom quiz game 920701 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,QadRomInfo,QadRomName,DrvInputInfo, qadDIPInfo,
	QadInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//======================
//Quiz & Dragons (Japan)
//======================

static int QadjInit()
{
  int nRet=0;
  Cps=1; Qad=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 4*0x080000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000000,0,1); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,1,1); if (nRet!=0) return 1;

  // Load graphics roms
  CpsLoadTiles(CpsGfx         ,2);

  nCpsLcReg=0x66; // Layer control register is at 0x66
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x08;

  // Protection enable code by KEV
  CpsMProt[0]=0x40;
  CpsMProt[1]=0x42;
  CpsMProt[2]=0x44;
  CpsMProt[3]=0x46;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,6,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,7,1);
  nRet=BurnLoadRom(CpsAd+0x20000,8,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

// Rom information
static struct BurnRomInfo QadjRomDesc[] = {
	{ "qad23a.bin",    0x80000, 0x4d3553de, BRF_ESS | BRF_PRG }, // 0 both 68000 code
	{ "qad22a.bin",    0x80000, 0x3191ddd0, BRF_ESS | BRF_PRG }, // 1 both

  // graphics:
	{ "qad01.bin",     0x80000, 0x9d853b57, BRF_GRA },			 // 2
	{ "qad02.bin",     0x80000, 0xb35976c4, BRF_GRA },
	{ "qad03.bin",     0x80000, 0xcea4ca8c, BRF_GRA },
	{ "qad04.bin",     0x80000, 0x41b74d1b, BRF_GRA },

  // z80 rom
	{ "qad09.bin",     0x10000, 0x733161cc, BRF_GRA },			 // 6
  // samples
	{ "qad18.bin",     0x20000, 0x2bfe6f6a, BRF_GRA },
	{ "qad19.bin",     0x20000, 0x13d3236b, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Qadj) STD_ROM_FN(Qadj)

struct BurnDriver BurnDrvCpsQadj = {
	"qadj", "qad", NULL, "1992",
	"Quiz & Dragons (940921 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,QadjRomInfo,QadjRomName,DrvInputInfo, qadjDIPInfo,
	QadjInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

