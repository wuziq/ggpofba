#include "cps.h"
// Three wonders

static struct BurnInputInfo DrvInputList[] =
{
	{"P1 Coin"       , BIT_DIGITAL, CpsInp018+0, "p1 coin"   },
	{"P1 Start"      , BIT_DIGITAL, CpsInp018+4, "p1 start"  },
	{"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"     },
	{"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"   },
	{"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"   },
	{"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"  },
	{"P1 Button 1"   , BIT_DIGITAL, CpsInp001+4, "p1 fire 1" },
	{"P1 Button 2"   , BIT_DIGITAL, CpsInp001+5, "p1 fire 2" },

	{"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"   },
	{"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start"  },
	{"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"     },
	{"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"   },
	{"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"   },
	{"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"  },
	{"P2 Button 1"   , BIT_DIGITAL, CpsInp000+4, "p2 fire 1" },
	{"P2 Button 2"   , BIT_DIGITAL, CpsInp000+5, "p2 fire 2" },

	{"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"     },
	{"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"      },
	{"Service"       , BIT_DIGITAL, CpsInp018+2, "service"   },
	{"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"       },
	{"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"       },
	{"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"       },
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo threewondersDIPList[]=
{
	// Defaults
	{0x13, 0xff, 0xff, 0x00, NULL                     },
	{0x14, 0xff, 0xff, 0x00, NULL                     },
	{0x15, 0xff, 0xff, 0x00, NULL                     },

	// Dip A
	{0   , 0xfe, 0   , 8   , "Coin 1"                 },
	{0x13, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x13, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x13, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x13, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x13, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x13, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x13, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x13, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 8   , "Coin 2"                 },
	{0x13, 0x01, 0x38, 0x38, "4 Coins 1 Credit"       },
	{0x13, 0x01, 0x38, 0x30, "3 Coins 1 Credit"       },
	{0x13, 0x01, 0x38, 0x28, "2 Coins 1 Credit"       },
	{0x13, 0x01, 0x38, 0x00, "1 Coin 1 Credit"        },
	{0x13, 0x01, 0x38, 0x08, "1 Coin 2 Credits"       },
	{0x13, 0x01, 0x38, 0x10, "1 Coin 3 Credits"       },
	{0x13, 0x01, 0x38, 0x18, "1 Coin 4 Credits"       },
	{0x13, 0x01, 0x38, 0x20, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 2   , "2C to Start, 1 to Cont" },
	{0x13, 0x01, 0x40, 0x00, "Off"                    },
	{0x13, 0x01, 0x40, 0x40, "On"                     },

	{0   , 0xfe, 0   , 2   , "Freeze"                 },
	{0x13, 0x01, 0x80, 0x00, "Off"                    },
	{0x13, 0x01, 0x80, 0x80, "On"                     },

	// Dip B
	{0   , 0xfe, 0   , 4   , "Action Lives"           },
	{0x14, 0x01, 0x03, 0x00, "1"                      },
	{0x14, 0x01, 0x03, 0x01, "2"                      },
	{0x14, 0x01, 0x03, 0x02, "3"                      },
	{0x14, 0x01, 0x03, 0x03, "5"                      },

	{0   , 0xfe, 0   , 4   , "Action Game Level"      },
	{0x14, 0x01, 0x0c, 0x00, "Easy"                   },
	{0x14, 0x01, 0x0c, 0x04, "Normal"                 },
	{0x14, 0x01, 0x0c, 0x08, "Hard"                   },
	{0x14, 0x01, 0x0c, 0x0c, "Hardest"                },

	{0   , 0xfe, 0   , 4   , "Shooting Lives"         },
	{0x14, 0x01, 0x30, 0x00, "1"                      },
	{0x14, 0x01, 0x30, 0x10, "2"                      },
	{0x14, 0x01, 0x30, 0x20, "3"                      },
	{0x14, 0x01, 0x30, 0x30, "5"                      },

	{0   , 0xfe, 0   , 4   , "Shooting Game Level"    },
	{0x14, 0x01, 0xc0, 0x00, "Easy"                   },
	{0x14, 0x01, 0xc0, 0x40, "Normal"                 },
	{0x14, 0x01, 0xc0, 0x80, "Hard"                   },
	{0x14, 0x01, 0xc0, 0xc0, "Hardest"                },

	// Dip C
	{0   , 0xfe, 0   , 4   , "Puzzle Lives"           },
	{0x15, 0x01, 0x03, 0x00, "1"                      },
	{0x15, 0x01, 0x03, 0x01, "2"                      },
	{0x15, 0x01, 0x03, 0x02, "3"                      },
	{0x15, 0x01, 0x03, 0x03, "5"                      },

	{0   , 0xfe, 0   , 4   , "Puzzle Game Level"      },
	{0x15, 0x01, 0x0c, 0x00, "Easy"                   },
	{0x15, 0x01, 0x0c, 0x04, "Normal"                 },
	{0x15, 0x01, 0x0c, 0x08, "Hard"                   },
	{0x15, 0x01, 0x0c, 0x0c, "Hardest"                },

	{0   , 0xfe, 0   , 2   , "Flip"                   },
	{0x15, 0x01, 0x10, 0x00, "Off"                    },
	{0x15, 0x01, 0x10, 0x10, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sound"             },
	{0x15, 0x01, 0x20, 0x00, "Off"                    },
	{0x15, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 2   , "Continue"               },
	{0x15, 0x01, 0x40, 0x00, "Off"                    },
	{0x15, 0x01, 0x40, 0x40, "On"                     },
};

STDDIPINFO(threewonders);


static int DrvInit()
{
  int nRet=0;
  Cps=1; Wonders3=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 8*0x080000;
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
  CpsLoadTiles(CpsGfx         ,8);
  CpsLoadTiles(CpsGfx+0x200000,12);

  nCpsGfxScroll[2]=0x200000;

  nCpsLcReg=0x68; // Layer control register is at 0x68
  CpsLayEn[1]=0x20;
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x08;

  // Board ID improvments by KEV. 0x72,0x0800
  CpsBID[0]=0x72;
  CpsBID[1]=0x08;
  CpsBID[2]=0x00;

  // Protection enable code by KEV
  CpsMProt[0]=0x4e;
  CpsMProt[1]=0x4c;
  CpsMProt[2]=0x4a;
  CpsMProt[3]=0x48;

  MaskAddr[0]=0x66;
  MaskAddr[1]=0x64;
  MaskAddr[2]=0x62;
  MaskAddr[3]=0x60;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,16,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,17,1);
  nRet=BurnLoadRom(CpsAd+0x20000,18,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

static int DrvExit()
{


  CpsRunExit();

  CpsExit();
  nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0; Wonders3=0;
  return 0;
}


//=====================
//Three Wonders (World)
//=====================

// Rom information
static struct BurnRomInfo Wonder3wRomDesc[] = {
	{ "rte.30a",       0x20000, 0xef5b8b33, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "rte.35a",       0x20000, 0x7d705529, BRF_ESS | BRF_PRG }, // 1 odd
	{ "rte.31a",       0x20000, 0x32835e5e, BRF_ESS | BRF_PRG }, // 2 even
	{ "rte.36a",       0x20000, 0x7637975f, BRF_ESS | BRF_PRG }, // 3 odd
	{ "3wonders.28",   0x20000, 0x054137c8, BRF_ESS | BRF_PRG }, // 4 even
	{ "3wonders.33",   0x20000, 0x7264cb1b, BRF_ESS | BRF_PRG }, // 5 odd
	{ "rte.29a",       0x20000, 0xcddaa919, BRF_ESS | BRF_PRG }, // 6 even
	{ "rte.34a",       0x20000, 0xed52e7e5, BRF_ESS | BRF_PRG }, // 7 odd

  // graphics:
	{ "3wonders.05",   0x80000, 0x86aef804, BRF_GRA },			 // 8
	{ "3wonders.07",   0x80000, 0x4f057110, BRF_GRA },
	{ "3wonders.01",   0x80000, 0x902489d0, BRF_GRA },
	{ "3wonders.03",   0x80000, 0xe35ce720, BRF_GRA },
	{ "3wonders.06",   0x80000, 0x13cb0e7c, BRF_GRA },			 // 12
	{ "3wonders.08",   0x80000, 0x1f055014, BRF_GRA },
	{ "3wonders.02",   0x80000, 0xe9a034f4, BRF_GRA },
	{ "3wonders.04",   0x80000, 0xdf0eea8b, BRF_GRA },

  // z80 rom
	{ "3wonders.09",   0x10000, 0xabfca165, BRF_GRA },			 // 16
  // samples
	{ "3wonders.18",   0x20000, 0x26b211ab, BRF_GRA },
	{ "3wonders.19",   0x20000, 0xdbe64ad0, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Wonder3w) STD_ROM_FN(Wonder3w)

struct BurnDriver BurnDrvCps3wonders = {
	"3wonders", NULL, NULL, "1991",
	"Three Wonders (wonder 3 910520 etc)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,Wonder3wRomInfo,Wonder3wRomName,DrvInputInfo, threewondersDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//===================
//Three Wonders (USA)
//===================

// Rom information
static struct BurnRomInfo Wonder3uRomDesc[] = {
	{ "3wonders.30",   0x20000, 0x0b156fd8, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "3wonders.35",   0x20000, 0x57350bf4, BRF_ESS | BRF_PRG }, // 1 odd
	{ "3wonders.31",   0x20000, 0x0e723fcc, BRF_ESS | BRF_PRG }, // 2 even
	{ "3wonders.36",   0x20000, 0x523a45dc, BRF_ESS | BRF_PRG }, // 3 odd
	{ "3wonders.28",   0x20000, 0x054137c8, BRF_ESS | BRF_PRG }, // 4 even
	{ "3wonders.33",   0x20000, 0x7264cb1b, BRF_ESS | BRF_PRG }, // 5 odd
	{ "3wonders.29",   0x20000, 0x37ba3e20, BRF_ESS | BRF_PRG }, // 6 even
	{ "3wonders.34",   0x20000, 0xf99f46c0, BRF_ESS | BRF_PRG }, // 7 odd

  // graphics:
	{ "3wonders.05",   0x80000, 0x86aef804, BRF_GRA },			 // 8
	{ "3wonders.07",   0x80000, 0x4f057110, BRF_GRA },
	{ "3wonders.01",   0x80000, 0x902489d0, BRF_GRA },
	{ "3wonders.03",   0x80000, 0xe35ce720, BRF_GRA },
	{ "3wonders.06",   0x80000, 0x13cb0e7c, BRF_GRA },			 // 12
	{ "3wonders.08",   0x80000, 0x1f055014, BRF_GRA },
	{ "3wonders.02",   0x80000, 0xe9a034f4, BRF_GRA },
	{ "3wonders.04",   0x80000, 0xdf0eea8b, BRF_GRA },

  // z80 rom
	{ "3wonders.09",   0x10000, 0xabfca165, BRF_GRA },			 // 16
  // samples
	{ "3wonders.18",   0x20000, 0x26b211ab, BRF_GRA },
	{ "3wonders.19",   0x20000, 0xdbe64ad0, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Wonder3u) STD_ROM_FN(Wonder3u)

struct BurnDriver BurnDrvCps3wonderu = {
	"3wonderu", "3wonders", NULL, "1991",
	"Three Wonders (wonder 3 910520 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Wonder3uRomInfo,Wonder3uRomName,DrvInputInfo, threewondersDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//================
//Wonder 3 (Japan)
//================

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo Wonder3RomDesc[] = {
	{ "rtj36.bin",     0x20000, 0xe3741247, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "rtj42.bin",     0x20000, 0xb4baa117, BRF_ESS | BRF_PRG }, // 1 odd
	{ "rtj37.bin",     0x20000, 0xa1f677b0, BRF_ESS | BRF_PRG }, // 2 even
	{ "rtj43.bin",     0x20000, 0x85337a47, BRF_ESS | BRF_PRG }, // 3 odd
	{ "3wonders.28",   0x20000, 0x054137c8, BRF_ESS | BRF_PRG }, // 4 even
	{ "3wonders.33",   0x20000, 0x7264cb1b, BRF_ESS | BRF_PRG }, // 5 odd
	{ "rtj35.bin",     0x20000, 0xe72f9ea3, BRF_ESS | BRF_PRG }, // 6 even
	{ "rtj41.bin",     0x20000, 0xa11ee998, BRF_ESS | BRF_PRG }, // 7 odd

  // graphics:
	{ "3wonders.05",   0x80000, 0x86aef804, BRF_GRA },			 // 8
	{ "3wonders.07",   0x80000, 0x4f057110, BRF_GRA },
	{ "3wonders.01",   0x80000, 0x902489d0, BRF_GRA },
	{ "3wonders.03",   0x80000, 0xe35ce720, BRF_GRA },
	{ "3wonders.06",   0x80000, 0x13cb0e7c, BRF_GRA },			 // 12
	{ "3wonders.08",   0x80000, 0x1f055014, BRF_GRA },
	{ "3wonders.02",   0x80000, 0xe9a034f4, BRF_GRA },
	{ "3wonders.04",   0x80000, 0xdf0eea8b, BRF_GRA },

  // z80 rom
	{ "rt23.bin",      0x10000, 0x7d5a77a7, BRF_GRA },			 // 16
  // samples
	{ "3wonders.18",   0x20000, 0x26b211ab, BRF_GRA },
	{ "3wonders.19",   0x20000, 0xdbe64ad0, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Wonder3) STD_ROM_FN(Wonder3)

struct BurnDriver BurnDrvCpsWonder3 = {
	"wonder3", "3wonders", NULL, "1991",
	"Wonder 3 (910520 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Wonder3RomInfo,Wonder3RomName,DrvInputInfo, threewondersDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
