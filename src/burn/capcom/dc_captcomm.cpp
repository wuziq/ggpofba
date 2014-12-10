#include "cps.h"
// Captain Commando

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

  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"  },
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start" },
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"    },
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"  },
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"  },
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right" },
  {"P2 Attack"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Jump"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},

  {"P3 Coin"       , BIT_DIGITAL, CpsInp177+6, "p3 coin"  },
  {"P3 Start"      , BIT_DIGITAL, CpsInp177+7, "p3 start" },
  {"P3 Up"         , BIT_DIGITAL, CpsInp177+3, "p3 up"    },
  {"P3 Down"       , BIT_DIGITAL, CpsInp177+2, "p3 down"  },
  {"P3 Left"       , BIT_DIGITAL, CpsInp177+1, "p3 left"  },
  {"P3 Right"      , BIT_DIGITAL, CpsInp177+0, "p3 right" },
  {"P3 Attack"     , BIT_DIGITAL, CpsInp177+4, "p3 fire 1"},
  {"P3 Jump"       , BIT_DIGITAL, CpsInp177+5, "p3 fire 2"},

  {"P4 Coin"       , BIT_DIGITAL, CpsInp179+6, "p4 coin"  },
  {"P4 Start"      , BIT_DIGITAL, CpsInp179+7, "p4 start" },
  {"P4 Up"         , BIT_DIGITAL, CpsInp179+3, "p4 up"    },
  {"P4 Down"       , BIT_DIGITAL, CpsInp179+2, "p4 down"  },
  {"P4 Left"       , BIT_DIGITAL, CpsInp179+1, "p4 left"  },
  {"P4 Right"      , BIT_DIGITAL, CpsInp179+0, "p4 right" },
  {"P4 Attack"     , BIT_DIGITAL, CpsInp179+4, "p4 fire 1"},
  {"P4 Jump"       , BIT_DIGITAL, CpsInp179+5, "p4 fire 2"},

  {"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"    },
  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"     },
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"  },
  {"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"      },
  {"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"      },
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"      },
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo captcommDIPList[]=
{
	// Defaults
	{0x23, 0xff, 0xff, 0x00, NULL                     },
	{0x24, 0xff, 0xff, 0x00, NULL                     },
	{0x25, 0xff, 0xff, 0x00, NULL                     },

	// Dip A
	{0   , 0xfe, 0   , 8   , "Coin 1"                 },
	{0x23, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x23, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x23, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x23, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x23, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x23, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x23, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x23, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 8   , "Coin 2"                 },
	{0x23, 0x01, 0x38, 0x38, "4 Coins 1 Credit"       },
	{0x23, 0x01, 0x38, 0x30, "3 Coins 1 Credit"       },
	{0x23, 0x01, 0x38, 0x28, "2 Coins 1 Credit"       },
	{0x23, 0x01, 0x38, 0x00, "1 Coin 1 Credit"        },
	{0x23, 0x01, 0x38, 0x08, "1 Coin 2 Credits"       },
	{0x23, 0x01, 0x38, 0x10, "1 Coin 3 Credits"       },
	{0x23, 0x01, 0x38, 0x18, "1 Coin 4 Credits"       },
	{0x23, 0x01, 0x38, 0x20, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 2   , "2C to Start, 1 to Cont" },
	{0x23, 0x01, 0x40, 0x00, "Off"                    },
	{0x23, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x23, 0x01, 0x80, 0x00, "Off"                    },
//	{0x23, 0x01, 0x80, 0x80, "On"                     },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Difficulty 1"           },
	{0x24, 0x01, 0x07, 0x00, "Very Easy"              },
	{0x24, 0x01, 0x07, 0x01, "Easy 1"                 },
	{0x24, 0x01, 0x07, 0x02, "Easy 2"                 },
	{0x24, 0x01, 0x07, 0x03, "Normal"              },
	{0x24, 0x01, 0x07, 0x04, "Difficult"            },
	{0x24, 0x01, 0x07, 0x05, "Very Difficult"            },
	{0x24, 0x01, 0x07, 0x06, "Hard"            },
	{0x24, 0x01, 0x07, 0x07, "Hardest"         },

	{0   , 0xfe, 0   , 4   , "Difficulty 2"           },
	{0x24, 0x01, 0x18, 0x00, "1"                      },
	{0x24, 0x01, 0x18, 0x08, "2"                      },
	{0x24, 0x01, 0x18, 0x10, "3"                      },
	{0x24, 0x01, 0x18, 0x18, "4"                      },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x24, 0x01, 0x20, 0x00, "Off"                    },
//	{0x24, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 4   , "Max Players"            },
	{0x24, 0x01, 0xc0, 0x80, "1"                      },
	{0x24, 0x01, 0xc0, 0x00, "2"                      },
	{0x24, 0x01, 0xc0, 0x40, "3"                      },
	{0x24, 0x01, 0xc0, 0xc0, "4"                      },

	// Dip C
	{0   , 0xfe, 0   , 4   , "Lives"                  },
	{0x25, 0x01, 0x03, 0x03, "1"                      },
	{0x25, 0x01, 0x03, 0x00, "2"                      },
	{0x25, 0x01, 0x03, 0x01, "3"                      },
	{0x25, 0x01, 0x03, 0x02, "4"                      },

	{0   , 0xfe, 0   , 2   , "Free Play"              },
	{0x25, 0x01, 0x04, 0x00, "Off"                    },
	{0x25, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Freeze"                 },
	{0x25, 0x01, 0x08, 0x00, "Off"                    },
	{0x25, 0x01, 0x08, 0x08, "On"                     },

	{0   , 0xfe, 0   , 2   , "Flip"                   },
	{0x25, 0x01, 0x10, 0x00, "Off"                    },
	{0x25, 0x01, 0x10, 0x10, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sound"             },
	{0x25, 0x01, 0x20, 0x00, "Off"                    },
	{0x25, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 2   , "Continue"               },
	{0x25, 0x01, 0x40, 0x00, "Off"                    },
	{0x25, 0x01, 0x40, 0x40, "On"                     },
};

STDDIPINFO(captcomm);


static int DrvInit()
{
  int nRet=0;
  Cps=1;
  nCpsRomLen=   0x140000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 8*0x080000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000000,0,1); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,1,1); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x100001,2,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x100000,3,2); if (nRet!=0) return 1;

  // Load graphics roms
  CpsLoadTiles(CpsGfx+0x000000,4+0*4);
  CpsLoadTiles(CpsGfx+0x200000,4+1*4);

  nCpsLcReg=0x60; // Layer control register is at 0x60
  CpsLayEn[1]=0x20;
  CpsLayEn[2]=0x12;
  CpsLayEn[3]=0x12;

  // Protection enable code by KEV
  CpsMProt[0]=0x46;
  CpsMProt[1]=0x44;
  CpsMProt[2]=0x42;
  CpsMProt[3]=0x40;

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

static int DrvExit()
{
  CpsRunExit();

  CpsExit();
  nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0;
  return 0;
}


//========================
//Captain Commando (World)
//========================

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo CaptcommRomDesc[] = {
	{ "cce_23d.rom",   0x80000, 0x19c58ece, BRF_ESS | BRF_PRG }, // 0 swapped
	{ "cc_22d.rom",    0x80000, 0xa91949b7, BRF_ESS | BRF_PRG }, // 1 swapped
	{ "cc_24d.rom",    0x20000, 0x680e543f, BRF_ESS | BRF_PRG }, // 2 even
	{ "cc_28d.rom",    0x20000, 0x8820039f, BRF_ESS | BRF_PRG }, // 3 odd

  // graphics:
	{ "gfx_01.rom",    0x80000, 0x7261d8ba, BRF_GRA },
	{ "gfx_03.rom",    0x80000, 0x6a60f949, BRF_GRA },
	{ "gfx_02.rom",    0x80000, 0x00637302, BRF_GRA },			 // 4
	{ "gfx_04.rom",    0x80000, 0xcc87cf61, BRF_GRA },			 // 8
	{ "gfx_05.rom",    0x80000, 0x28718bed, BRF_GRA },
	{ "gfx_07.rom",    0x80000, 0xd4acc53a, BRF_GRA },
	{ "gfx_06.rom",    0x80000, 0x0c69f151, BRF_GRA },
	{ "gfx_08.rom",    0x80000, 0x1f9ebb97, BRF_GRA },

  // z80 rom
	{ "cc_09.rom",     0x10000, 0x698e8b58, BRF_GRA },			 // 12
  // samples
	{ "cc_18.rom",     0x20000, 0x6de2c2db, BRF_GRA },
	{ "cc_19.rom",     0x20000, 0xb99091ae, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Captcomm) STD_ROM_FN(Captcomm)

struct BurnDriver BurnDrvCpsCaptcomm = {
	"captcomm", NULL, NULL, "1991",
	"Captain Commando (911014 other country)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,4,HARDWARE_CAPCOM_CPS1,
	NULL,CaptcommRomInfo,CaptcommRomName,DrvInputInfo, captcommDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//======================
//Captain Commando (USA)
//======================

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo CaptcomuRomDesc[] = {
	{ "23b",           0x80000, 0x03da44fd, BRF_ESS | BRF_PRG }, // 0 swapped
	{ "22c",           0x80000, 0x9b82a052, BRF_ESS | BRF_PRG }, // 1 swapped
	{ "24b",           0x20000, 0x84ff99b2, BRF_ESS | BRF_PRG }, // 2 even
	{ "28b",           0x20000, 0xfbcec223, BRF_ESS | BRF_PRG }, // 3 odd

  // graphics:
	{ "gfx_01.rom",    0x80000, 0x7261d8ba, BRF_GRA },
	{ "gfx_03.rom",    0x80000, 0x6a60f949, BRF_GRA },
	{ "gfx_02.rom",    0x80000, 0x00637302, BRF_GRA },			 // 4
	{ "gfx_04.rom",    0x80000, 0xcc87cf61, BRF_GRA },			 // 8
	{ "gfx_05.rom",    0x80000, 0x28718bed, BRF_GRA },
	{ "gfx_07.rom",    0x80000, 0xd4acc53a, BRF_GRA },
	{ "gfx_06.rom",    0x80000, 0x0c69f151, BRF_GRA },
	{ "gfx_08.rom",    0x80000, 0x1f9ebb97, BRF_GRA },

  // z80 rom
	{ "cc_09.rom",     0x10000, 0x698e8b58, BRF_GRA },			 // 12
  // samples
	{ "cc_18.rom",     0x20000, 0x6de2c2db, BRF_GRA },
	{ "cc_19.rom",     0x20000, 0xb99091ae, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Captcomu) STD_ROM_FN(Captcomu)

struct BurnDriver BurnDrvCpsCaptcomu = {
	"captcomu", "captcomm", NULL, "1991",
	"Captain Commando (910928 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS1,
	NULL,CaptcomuRomInfo,CaptcomuRomName,DrvInputInfo, captcommDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//========================
//Captain Commando (Japan)
//========================

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo CaptcomjRomDesc[] = {
	{ "cc23.bin",      0x80000, 0x5b482b62, BRF_ESS | BRF_PRG }, // 0 swapped
	{ "cc22.bin",      0x80000, 0x0fd34195, BRF_ESS | BRF_PRG }, // 1 swapped
	{ "cc24.bin",      0x20000, 0x3a794f25, BRF_ESS | BRF_PRG }, // 2 even
	{ "cc28.bin",      0x20000, 0xfc3c2906, BRF_ESS | BRF_PRG }, // 3 odd

  // graphics:
	{ "gfx_01.rom",    0x80000, 0x7261d8ba, BRF_GRA },
	{ "gfx_03.rom",    0x80000, 0x6a60f949, BRF_GRA },
	{ "gfx_02.rom",    0x80000, 0x00637302, BRF_GRA },			 // 4
	{ "gfx_04.rom",    0x80000, 0xcc87cf61, BRF_GRA },			 // 8
	{ "gfx_05.rom",    0x80000, 0x28718bed, BRF_GRA },
	{ "gfx_07.rom",    0x80000, 0xd4acc53a, BRF_GRA },
	{ "gfx_06.rom",    0x80000, 0x0c69f151, BRF_GRA },
	{ "gfx_08.rom",    0x80000, 0x1f9ebb97, BRF_GRA },

  // z80 rom
	{ "cc_09.rom",     0x10000, 0x698e8b58, BRF_GRA },			 // 12
  // samples
	{ "cc_18.rom",     0x20000, 0x6de2c2db, BRF_GRA },
	{ "cc_19.rom",     0x20000, 0xb99091ae, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Captcomj) STD_ROM_FN(Captcomj)

struct BurnDriver BurnDrvCpsCaptcomj = {
	"captcomj", "captcomm", NULL, "1991",
	"Captain Commando (911202 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS1,
	NULL,CaptcomjRomInfo,CaptcomjRomName,DrvInputInfo, captcommDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
