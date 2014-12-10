#include "cps.h"
// Carrier Air Wing

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

static struct BurnInputInfo CawingbInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp008+0, "p1 coin"},
  {"P1 Start"      , BIT_DIGITAL, CpsInp008+4, "p1 start"},
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Shot"       , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Special"    , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Fire 3"     , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp008+1, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp008+5, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Shot"       , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Special"    , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Fire 3"     , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp008+6, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp008+2, "service"},
  {"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"},
  {"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Cawingb);

static struct BurnDIPInfo cawingDIPList[]=
{
	// Defaults
	{0x15, 0xff, 0xff, 0x00, NULL                },
	{0x16, 0xff, 0xff, 0x00, NULL                },
	{0x17, 0xff, 0xff, 0x00, NULL                },

	// Dip A
	{0   , 0xfe, 0   , 8   , "Coin 1"                 },
	{0x15, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x15, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x15, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x15, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x15, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x15, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x15, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x15, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 8   , "Coin 2"                 },
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
	{0   , 0xfe, 0   , 5   , "Game Level"             },
	{0x16, 0x01, 0x07, 0x00, "Very Easy"              },
	{0x16, 0x01, 0x07, 0x02, "Easy"                   },
	{0x16, 0x01, 0x07, 0x03, "Normal"                 },
	{0x16, 0x01, 0x07, 0x04, "Difficult"              },
	{0x16, 0x01, 0x07, 0x07, "Very Difficult"         },

	{0   , 0xfe, 0   , 4   , "Nando Vital"            },
	{0x16, 0x01, 0x18, 0x08, "Easy"                   },
	{0x16, 0x01, 0x18, 0x00, "Normal"                 },
	{0x16, 0x01, 0x18, 0x10, "Difficult"              },
	{0x16, 0x01, 0x18, 0x18, "Very Difficult"         },

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
//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x17, 0x01, 0x01, 0x00, "Off"                    },
//	{0x17, 0x01, 0x01, 0x01, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x17, 0x01, 0x02, 0x00, "Off"                    },
//	{0x17, 0x01, 0x02, 0x02, "On"                     },

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

STDDIPINFO(cawing);


static int DrvExit()
{


  CpsRunExit();
  CpsExit();
  nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0; Cawingb=0;
  return 0;
}


//========================
//Carrier Air Wing (World)
//========================

static int CawingInit()
{
  int nRet=0;
  Cps=1;
  nCpsRomLen =  0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen =4*0x080000;
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

  nCpsLcReg=0x4c; // Layer control register is at 0x4c
  CpsLayEn[1]=0x10;
  CpsLayEn[2]=0x0a;
  CpsLayEn[3]=0x0a;

  // Start of Board ID improvments by KEV. 0x40,0x0406
  CpsBID[0]=0x40;
  CpsBID[1]=0x04;
  CpsBID[2]=0x06;

  MaskAddr[0]=0x4a;
  MaskAddr[1]=0x48;
  MaskAddr[2]=0x46;
  MaskAddr[3]=0x44;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,9,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,10,1);
  nRet=BurnLoadRom(CpsAd+0x20000,11,1);

  nRet=CpsRunInit();

  if (nRet!=0) return 1;
  // Ready to go
  return 0;
}


static struct BurnRomInfo CawingRomDesc[] = {
	{ "cae_30a.rom",   0x20000, 0x91fceacd, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "cae_35a.rom",   0x20000, 0x3ef03083, BRF_ESS | BRF_PRG }, //  1
	{ "cae_31a.rom",   0x20000, 0xe5b75caf, BRF_ESS | BRF_PRG }, //  2 68000 code
	{ "cae_36a.rom",   0x20000, 0xc73fd713, BRF_ESS | BRF_PRG }, //  3
	{ "ca_32.rom",     0x80000, 0x0c4837d4, BRF_ESS | BRF_PRG }, //  4

// 5
	{ "ca_gfx5.rom",   0x80000, 0x66d4cc37, BRF_GRA },
	{ "ca_gfx7.rom",   0x80000, 0xb6f896f2, BRF_GRA },
	{ "ca_gfx1.rom",   0x80000, 0x4d0620fd, BRF_GRA },
	{ "ca_gfx3.rom",   0x80000, 0x0b0341c3, BRF_GRA },

// 9
// z80 program
	{ "ca_9.rom",      0x10000, 0x96fe7485, BRF_SND },
// adpcm samples
	{ "ca_18.rom",     0x20000, 0x4a613a2c, BRF_SND },
	{ "ca_19.rom",     0x20000, 0x74584493, BRF_SND },
// 18
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Cawing) STD_ROM_FN(Cawing)

static struct BurnRomInfo Cawingr1RomDesc[] = {
	{ "cae_30.11f",    0x20000, 0x23305cd5, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "cae_35.11h",    0x20000, 0x69419113, BRF_ESS | BRF_PRG }, //  1
	{ "cae_31.12f",    0x20000, 0x9008dfb3, BRF_ESS | BRF_PRG }, //  2 68000 code
	{ "cae_36.12h",    0x20000, 0x4dbf6f8e, BRF_ESS | BRF_PRG }, //  3
	{ "ca_32.rom",     0x80000, 0x0c4837d4, BRF_ESS | BRF_PRG }, //  4

// 5
	{ "ca_gfx5.rom",   0x80000, 0x66d4cc37, BRF_GRA },
	{ "ca_gfx7.rom",   0x80000, 0xb6f896f2, BRF_GRA },
	{ "ca_gfx1.rom",   0x80000, 0x4d0620fd, BRF_GRA },
	{ "ca_gfx3.rom",   0x80000, 0x0b0341c3, BRF_GRA },

// 9
// z80 program
	{ "ca_9.rom",      0x10000, 0x96fe7485, BRF_SND },
// adpcm samples
	{ "ca_18.rom",     0x20000, 0x4a613a2c, BRF_SND },
	{ "ca_19.rom",     0x20000, 0x74584493, BRF_SND },
// 18
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Cawingr1) STD_ROM_FN(Cawingr1)

struct BurnDriver BurnDrvCpsCawing = {
	"cawing", NULL, NULL, "1990",
	"Carrier Air Wing (U.S. navy 901012 etc)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,CawingRomInfo,CawingRomName,DrvInputInfo, cawingDIPInfo,
	CawingInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsCawingr1 = {
	"cawingr1", "cawing", NULL, "1990",
	"Carrier Air Wing (U.S. navy 901009 etc)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2,HARDWARE_CAPCOM_CPS1,
	NULL,Cawingr1RomInfo,Cawingr1RomName,DrvInputInfo, cawingDIPInfo,
	CawingInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=====================
//Carrier Air Wing (US)
//=====================

static struct BurnRomInfo CawinguRomDesc[] = {
	{ "cae_30a.rom",   0x20000, 0x91fceacd, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "cau_35a.rom",   0x20000, 0xf090d9b2, BRF_ESS | BRF_PRG }, //  1
	{ "cae_31a.rom",   0x20000, 0xe5b75caf, BRF_ESS | BRF_PRG }, //  2 68000 code
	{ "cae_36a.rom",   0x20000, 0xc73fd713, BRF_ESS | BRF_PRG }, //  3
	{ "ca_32.rom",     0x80000, 0x0c4837d4, BRF_ESS | BRF_PRG }, //  4

// 5
	{ "ca_gfx5.rom",   0x80000, 0x66d4cc37, BRF_GRA },
	{ "ca_gfx7.rom",   0x80000, 0xb6f896f2, BRF_GRA },
	{ "ca_gfx1.rom",   0x80000, 0x4d0620fd, BRF_GRA },
	{ "ca_gfx3.rom",   0x80000, 0x0b0341c3, BRF_GRA },

// 9
// z80 program
	{ "ca_9.rom",      0x10000, 0x96fe7485, BRF_SND },
// adpcm samples
	{ "ca_18.rom",     0x20000, 0x4a613a2c, BRF_SND },
	{ "ca_19.rom",     0x20000, 0x74584493, BRF_SND },
// 18
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Cawingu) STD_ROM_FN(Cawingu)

struct BurnDriver BurnDrvCpsCawingu = {
	"cawingu", "cawing", NULL, "1990",
	"Carrier Air Wing (U.S. navy 901012 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,CawinguRomInfo,CawinguRomName,DrvInputInfo, cawingDIPInfo,
	CawingInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=================
//U.S. Navy (Japan)
//=================

static int CawingjInit()
{
  int nRet=0;
  Cps=1;
  nCpsRomLen =  0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen =4*0x080000;
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
  CpsLoadTilesByte(CpsGfx, 8);
  CpsLoadTilesByte(CpsGfx+(8*0x020000), 8+8);

  nCpsLcReg=0x4c; // Layer control register is at 0x4c
  CpsLayEn[1]=0x10;
  CpsLayEn[2]=0x0a;
  CpsLayEn[3]=0x0a;

  // Start of Board ID improvments by KEV. 0x40,0x0406
  CpsBID[0]=0x40;
  CpsBID[1]=0x04;
  CpsBID[2]=0x06;

  MaskAddr[0]=0x4a;
  MaskAddr[1]=0x48;
  MaskAddr[2]=0x46;
  MaskAddr[3]=0x44;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,24,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,25,1);
  nRet=BurnLoadRom(CpsAd+0x20000,26,1);


  nRet=CpsRunInit();

  if (nRet!=0) return 1;
  // Ready to go
  return 0;
}


static struct BurnRomInfo CawingjRomDesc[] = {
	{ "cae_30a.rom",   0x20000, 0x91fceacd, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "caj42a.bin",    0x20000, 0x039f8362, BRF_ESS | BRF_PRG }, //  1
	{ "cae_31a.rom",   0x20000, 0xe5b75caf, BRF_ESS | BRF_PRG }, //  2 68000 code
	{ "cae_36a.rom",   0x20000, 0xc73fd713, BRF_ESS | BRF_PRG }, //  3
	{ "caj34.bin",     0x20000, 0x51ea57f4, BRF_ESS | BRF_PRG }, //  4 68000 code
	{ "caj40.bin",     0x20000, 0x2ab71ae1, BRF_ESS | BRF_PRG }, //  5
	{ "caj35.bin",     0x20000, 0x01d71973, BRF_ESS | BRF_PRG }, //  6 68000 code
	{ "caj41.bin",     0x20000, 0x3a43b538, BRF_ESS | BRF_PRG }, //  7

// 8
	{ "caj09.bin",     0x20000, 0x41b0f9a6, BRF_GRA },
	{ "caj01.bin",     0x20000, 0x1002d0b8, BRF_GRA },
	{ "caj13.bin",     0x20000, 0x6f3948b2, BRF_GRA },
	{ "caj05.bin",     0x20000, 0x207373d7, BRF_GRA },
// 12
	{ "caj24.bin",     0x20000, 0xe356aad7, BRF_GRA },
	{ "caj17.bin",     0x20000, 0x540f2fd8, BRF_GRA },
	{ "caj38.bin",     0x20000, 0x2464d4ab, BRF_GRA },
	{ "caj32.bin",     0x20000, 0x9b5836b3, BRF_GRA },
// 16
	{ "caj10.bin",     0x20000, 0xbf8a5f52, BRF_GRA },
	{ "caj02.bin",     0x20000, 0x125b018d, BRF_GRA },
	{ "caj14.bin",     0x20000, 0x8458e7d7, BRF_GRA },
	{ "caj06.bin",     0x20000, 0xcf80e164, BRF_GRA },
// 20
	{ "caj25.bin",     0x20000, 0xcdd0204d, BRF_GRA },
	{ "caj18.bin",     0x20000, 0x29c1d4b1, BRF_GRA },
	{ "caj39.bin",     0x20000, 0xeea23b67, BRF_GRA },
	{ "caj33.bin",     0x20000, 0xdde3891f, BRF_GRA },
// 24
// z80 program
	{ "ca_9.rom",      0x10000, 0x96fe7485, BRF_SND },
// adpcm samples
	{ "ca_18.rom",     0x20000, 0x4a613a2c, BRF_SND },
	{ "ca_19.rom",     0x20000, 0x74584493, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Cawingj) STD_ROM_FN(Cawingj)

struct BurnDriver BurnDrvCpsCawingj = {
	"cawingj", "cawing", NULL, "1990",
	"U.S. Navy (901012 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,CawingjRomInfo,CawingjRomName,DrvInputInfo, cawingDIPInfo,
	CawingjInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

/*
//============================
// Carrier Air Wing (Bootleg)
//============================

static int CawingbInit()
{
  int nRet=0;
  Cps=1; Cawingb=1;
  nCpsRomLen =  0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen =4*0x080000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  nRet=BurnLoadRom(CpsRom+0x000001,0,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x000000,1,2); if (nRet!=0) return 1;

  CpsLoadTiles(CpsGfx, 2);

  nCpsLcReg=0x4c;
  CpsLayEn[1]=0x10;
  CpsLayEn[2]=0x0a;
  CpsLayEn[3]=0x0a;

  CpsBID[0]=0x40;
  CpsBID[1]=0x04;
  CpsBID[2]=0x06;

  MaskAddr[0]=0x4a;
  MaskAddr[1]=0x48;
  MaskAddr[2]=0x46;
  MaskAddr[3]=0x44;

  nRet=BurnLoadRom(CpsZRom,6,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,7,1);
  nRet=BurnLoadRom(CpsAd+0x20000,8,1);


  nRet=CpsRunInit();

  if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

static struct BurnRomInfo CawingbRomDesc[] = {
	{ "2.16d",         0x80000, 0x8125d3f0, BRF_ESS | BRF_PRG }, //  1
	{ "1.19d",         0x80000, 0xb19b10ce, BRF_ESS | BRF_PRG }, //  0

//  {"5.5j"        , 0x80000, 0x30dd78db,    1}, //  3
//  {"4.7j"        , 0x80000, 0x4937fc41,    1}, //  2
//  {"7.2j"        , 0x80000, 0xa045c689,    1}, //  5
//  {"6.3j"        , 0x80000, 0x61192f7c,    1}, //  4
	{ "ca_gfx5.rom",   0x80000, 0x66d4cc37, BRF_GRA },
	{ "ca_gfx7.rom",   0x80000, 0xb6f896f2, BRF_GRA },
	{ "ca_gfx1.rom",   0x80000, 0x4d0620fd, BRF_GRA },
	{ "ca_gfx3.rom",   0x80000, 0x0b0341c3, BRF_GRA },

//  {"3.4d"        , 0x20000, 0xffe16cdc,    2}, //  6
	{ "ca_9.rom",      0x10000, 0x96fe7485, BRF_SND },

	{ "ca_18.rom",     0x20000, 0x4a613a2c, BRF_SND },			 //  7
	{ "ca_19.rom",     0x20000, 0x74584493, BRF_SND },			 //  8
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Cawingb) STD_ROM_FN(Cawingb)

struct BurnDriverD BurnDrvCpsCawingb = {
	"cawingb", "cawing", NULL, "1990",
	"Carrier Air Wing\0", "Missing GFX", "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,2,HARDWARE_CAPCOM_CPS1,
	NULL,CawingbRomInfo,CawingbRomName,CawingbInputInfo, cawingDIPInfo,
	CawingbInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
*/
