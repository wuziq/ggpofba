// Final Fight

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp018+0, "p1 coin"   },
  {"P1 Start"      , BIT_DIGITAL, CpsInp018+4, "p1 start"  },
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"     },
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"   },
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"   },
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"  },
  {"P1 Attack"     , BIT_DIGITAL, CpsInp001+4, "p1 fire 1" },
  {"P1 Jump"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2" },
  {"P1 Special"    , BIT_DIGITAL, CpsInp001+6, "p1 fire 3" },

  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"   },
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start"  },
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"     },
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"   },
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"   },
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"  },
  {"P2 Attack"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1" },
  {"P2 Jump"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2" },
  {"P2 Special"    , BIT_DIGITAL, CpsInp000+6, "p2 fire 3" },

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"},
  {"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo ffightDIPList[]=
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

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x15, 0x01, 0x80, 0x00, "Off"               },
//	{0x15, 0x01, 0x80, 0x80, "On"                },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Difficulty"        },
	{0x16, 0x01, 0x07, 0x00, "01"            },
	{0x16, 0x01, 0x07, 0x01, "02"            },
	{0x16, 0x01, 0x07, 0x02, "03"            },
	{0x16, 0x01, 0x07, 0x03, "04"         },
	{0x16, 0x01, 0x07, 0x04, "05"       },
	{0x16, 0x01, 0x07, 0x05, "06"       },
	{0x16, 0x01, 0x07, 0x06, "07"       },
	{0x16, 0x01, 0x07, 0x07, "08"    },

	{0   , 0xfe, 0   , 4   , "Difficulty 2"      },
	{0x16, 0x01, 0x18, 0x00, "01"              },
	{0x16, 0x01, 0x18, 0x08, "02"            },
	{0x16, 0x01, 0x18, 0x10, "03"              },
	{0x16, 0x01, 0x18, 0x18, "04"           },

	{0   , 0xfe, 0   , 4   , "Bonus Life"        },
	{0x16, 0x01, 0x60, 0x00, "100k"              },
	{0x16, 0x01, 0x60, 0x20, "200k"              },
	{0x16, 0x01, 0x60, 0x40, "100k and every 200k"},
	{0x16, 0x01, 0x60, 0x60, "None"              },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x16, 0x01, 0x80, 0x00, "Off"               },
//	{0x16, 0x01, 0x80, 0x80, "On"                },

	// Dip C
	{0   , 0xfe, 0   , 4   , "Lives"             },
	{0x17, 0x01, 0x03, 0x03, "1"                 },
	{0x17, 0x01, 0x03, 0x00, "2"                 },
	{0x17, 0x01, 0x03, 0x01, "3"                 },
	{0x17, 0x01, 0x03, 0x02, "4"                 },

	{0   , 0xfe, 0   , 2   , "Free Play"         },
	{0x17, 0x01, 0x04, 0x00, "Off"               },
	{0x17, 0x01, 0x04, 0x04, "On"                },

	{0   , 0xfe, 0   , 2   , "Freeze"            },
	{0x17, 0x01, 0x08, 0x00, "Off"               },
	{0x17, 0x01, 0x08, 0x08, "On"                },

	{0   , 0xfe, 0   , 2   , "Flip"              },
	{0x17, 0x01, 0x10, 0x00, "Off"               },
	{0x17, 0x01, 0x10, 0x10, "On"                },

	{0   , 0xfe, 0   , 2   , "Demo Sound"        },
	{0x17, 0x01, 0x20, 0x00, "Off"               },
	{0x17, 0x01, 0x20, 0x20, "On"                },

	{0   , 0xfe, 0   , 2   , "Continue"          },
	{0x17, 0x01, 0x40, 0x00, "Off"               },
	{0x17, 0x01, 0x40, 0x40, "On"                },
};

STDDIPINFO(ffight);


static int DrvExit()
{


  CpsRunExit();

  StartScroll[SCROLL_2]=0;
  StartScroll[SCROLL_3]=0;

  CpsExit();
  nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0;
  return 0;
}


//===================
//Final Fight (World)
//===================

static int FfightInit()
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

  nCpsLcReg=0x6e; // Layer control register is at 0x6e
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x0c;
  CpsLayEn[3]=0x0c;

  MaskAddr[0]=0x66;
  MaskAddr[1]=0x70;
  MaskAddr[2]=0x68;
  MaskAddr[3]=0x72;

  StartScroll[SCROLL_2]=1;
  StartScroll[SCROLL_3]=1;

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
static struct BurnRomInfo FfightRomDesc[] = {
	{ "ff30-36.bin",   0x20000, 0xf9a5ce83, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "ff35-42.bin",   0x20000, 0x65f11215, BRF_ESS | BRF_PRG }, // 1 odd
	{ "ff31-37.bin",   0x20000, 0xe1033784, BRF_ESS | BRF_PRG }, // 2 even
	{ "ff36-43.bin",   0x20000, 0x995e968a, BRF_ESS | BRF_PRG }, // 3 odd
	{ "ff32-32m.bin",  0x80000, 0xc747696e, BRF_ESS | BRF_PRG }, // 4 both

  // graphics:
	{ "ff05-05m.bin",  0x80000, 0x9c284108, BRF_GRA },			 // 5
	{ "ff07-07m.bin",  0x80000, 0xa7584dfb, BRF_GRA },
	{ "ff01-01m.bin",  0x80000, 0x0b605e44, BRF_GRA },
	{ "ff03-03m.bin",  0x80000, 0x52291cd2, BRF_GRA },

  // z80 rom
	{ "ff09-09.bin",   0x10000, 0xb8367eb5, BRF_GRA },			 // 9
  // samples
	{ "ff18-18.bin",   0x20000, 0x375c66e7, BRF_GRA },
	{ "ff19-19.bin",   0x20000, 0x1ef137f9, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Ffight) STD_ROM_FN(Ffight)

struct BurnDriver BurnDrvCpsFfight = {
	"ffight", NULL, NULL, "1989",
	"Final Fight (World)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,FfightRomInfo,FfightRomName,DrvInputInfo, ffightDIPInfo,
	FfightInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=================
//Final Fight (USA)
//=================

static int FfightuInit()
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

  nCpsLcReg=0x66; // Layer control register is at 0x66
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x08;

  MaskAddr[0]=0x68;
  MaskAddr[1]=0x6a;
  MaskAddr[2]=0x6c;
  MaskAddr[3]=0x6e;

  StartScroll[SCROLL_2]=1;
  StartScroll[SCROLL_3]=1;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,9,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,10,1);
  nRet=BurnLoadRom(CpsAd+0x20000,11,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

static int FfightuaInit()
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

  nCpsLcReg=0x68; // Layer control register is at 0x66
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x08;
  CpsLayEn[3]=0x20;

  MaskAddr[0]=0x6a;
  MaskAddr[1]=0x6c;
  MaskAddr[2]=0x6e;
  MaskAddr[3]=0x70;
  
  CpsBID[0]=0x60;
  CpsBID[1]=0x00;
  CpsBID[2]=0x05;

  StartScroll[SCROLL_2]=1;
  StartScroll[SCROLL_3]=1;

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
static struct BurnRomInfo FfightuRomDesc[] = {
	{ "36",            0x20000, 0xe2a48af9, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "42",            0x20000, 0xf4bb480e, BRF_ESS | BRF_PRG }, // 1 odd
	{ "37",            0x20000, 0xc371c667, BRF_ESS | BRF_PRG }, // 2 even
	{ "43",            0x20000, 0x2f5771f9, BRF_ESS | BRF_PRG }, // 3 odd
	{ "ff32-32m.bin",  0x80000, 0xc747696e, BRF_ESS | BRF_PRG }, // 4 both

  // graphics:
	{ "ff05-05m.bin",  0x80000, 0x9c284108, BRF_GRA },			 // 5
	{ "ff07-07m.bin",  0x80000, 0xa7584dfb, BRF_GRA },
	{ "ff01-01m.bin",  0x80000, 0x0b605e44, BRF_GRA },
	{ "ff03-03m.bin",  0x80000, 0x52291cd2, BRF_GRA },

  // z80 rom
	{ "ff09-09.bin",   0x10000, 0xb8367eb5, BRF_GRA },			 // 9
  // samples
	{ "ff18-18.bin",   0x20000, 0x375c66e7, BRF_GRA },
	{ "ff19-19.bin",   0x20000, 0x1ef137f9, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Ffightu) STD_ROM_FN(Ffightu)

static struct BurnRomInfo FfightuaRomDesc[] = {
	{ "30_2da0.010",   0x20000, 0xed988977, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "35_46ff.010",   0x20000, 0x07bf1c21, BRF_ESS | BRF_PRG }, // 1 odd
	{ "31_c933.010",   0x20000, 0xdba5a476, BRF_ESS | BRF_PRG }, // 2 even
	{ "36_0ace.010",   0x20000, 0x4d89f542, BRF_ESS | BRF_PRG }, // 3 odd
	{ "ff32-32m.bin",  0x80000, 0xc747696e, BRF_ESS | BRF_PRG }, // 4 both

  // graphics:
	{ "ff05-05m.bin",  0x80000, 0x9c284108, BRF_GRA },			 // 5
	{ "ff07-07m.bin",  0x80000, 0xa7584dfb, BRF_GRA },
	{ "ff01-01m.bin",  0x80000, 0x0b605e44, BRF_GRA },
	{ "ff03-03m.bin",  0x80000, 0x52291cd2, BRF_GRA },

  // z80 rom
	{ "23_ceb1.512",   0x10000, 0xb8367eb5, BRF_GRA },			 // 9
  // samples
	{ "18_ccb5.010",   0x20000, 0x375c66e7, BRF_GRA },
	{ "19_476d.010",   0x20000, 0x1ef137f9, BRF_GRA },
};

// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Ffightua) STD_ROM_FN(Ffightua)

struct BurnDriver BurnDrvCpsFfightu = {
	"ffightu", "ffight", NULL, "1989",
	"Final Fight (900112 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,FfightuRomInfo,FfightuRomName,DrvInputInfo, ffightDIPInfo,
	FfightuInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsFfightua = {
	"ffightua", "ffight", NULL, "1989",
	"Final Fight (900613 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,FfightuaRomInfo,FfightuaRomName,DrvInputInfo, ffightDIPInfo,
	FfightuaInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//===================
//Final Fight (Japan)
//===================

static int FfightjInit()
{
  int nRet=0;
  Cps=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 16*0x020000;
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
  CpsLoadTilesByte(CpsGfx, 5);
  CpsLoadTilesByte(CpsGfx+(8*0x020000), 5+8);

  nCpsLcReg=0x6e; // Layer control register is at 0x6e
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x0c;
  CpsLayEn[3]=0x0c;

  MaskAddr[0]=0x66;
  MaskAddr[1]=0x70;
  MaskAddr[2]=0x68;
  MaskAddr[3]=0x72;

  StartScroll[SCROLL_2]=1;
  StartScroll[SCROLL_3]=1;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,21,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,22,1);
  nRet=BurnLoadRom(CpsAd+0x20000,23,1);

  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

// Rom information
static struct BurnRomInfo FfightjRomDesc[] = {
	{ "ff30-36.bin",   0x20000, 0xf9a5ce83, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "ff35-42.bin",   0x20000, 0x65f11215, BRF_ESS | BRF_PRG }, // 1 odd
	{ "ff31-37.bin",   0x20000, 0xe1033784, BRF_ESS | BRF_PRG }, // 2 even
	{ "ff43.bin",      0x20000, 0xb6dee1c3, BRF_ESS | BRF_PRG }, // 3 odd
	{ "ff32-32m.bin",  0x80000, 0xc747696e, BRF_ESS | BRF_PRG }, // 4 both

  // graphics:
	{ "ff09.bin",      0x20000, 0x5b116d0d, BRF_GRA },			 // 5
	{ "ff01.bin",      0x20000, 0x815b1797, BRF_GRA },
	{ "ff13.bin",      0x20000, 0x8721a7da, BRF_GRA },
	{ "ff05.bin",      0x20000, 0xd0fcd4b5, BRF_GRA },
	{ "ff24.bin",      0x20000, 0xa1ab607a, BRF_GRA },			 // 9
	{ "ff17.bin",      0x20000, 0x2dc18cf4, BRF_GRA },
	{ "ff38.bin",      0x20000, 0x6535a57f, BRF_GRA },
	{ "ff32.bin",      0x20000, 0xc8bc4a57, BRF_GRA },
	{ "ff10.bin",      0x20000, 0x624a924a, BRF_GRA },			 // 13
	{ "ff02.bin",      0x20000, 0x5d91f694, BRF_GRA },
	{ "ff14.bin",      0x20000, 0x0a2e9101, BRF_GRA },
	{ "ff06.bin",      0x20000, 0x1c18f042, BRF_GRA },
	{ "ff25.bin",      0x20000, 0x6e8181ea, BRF_GRA },			 // 17
	{ "ff18.bin",      0x20000, 0xb19ede59, BRF_GRA },
	{ "ff39.bin",      0x20000, 0x9416b477, BRF_GRA },
	{ "ff33.bin",      0x20000, 0x7369fa07, BRF_GRA },

  // z80 rom
	{ "ff09-09.bin",   0x10000, 0xb8367eb5, BRF_GRA },			 // 21
  // samples
	{ "ff18-18.bin",   0x20000, 0x375c66e7, BRF_GRA },
	{ "ff19-19.bin",   0x20000, 0x1ef137f9, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Ffightj) STD_ROM_FN(Ffightj)

struct BurnDriver BurnDrvCpsFfightj = {
	"ffightj", "ffight", NULL, "1989",
	"Final Fight (Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,FfightjRomInfo,FfightjRomName,DrvInputInfo, ffightDIPInfo,
	FfightjInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//ffightj1

static int Ffightj1Init()
{
  int nRet=0;
  Cps=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 16*0x020000;
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
  CpsLoadTilesByte(CpsGfx, 5);
  CpsLoadTilesByte(CpsGfx+(8*0x020000), 5+8);

  nCpsLcReg=0x6c; // Layer control register is at 0x6c
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x08;

  MaskAddr[0]=0x6a;
  MaskAddr[1]=0x68;
  MaskAddr[2]=0x66;
  MaskAddr[3]=0x64;

  CpsBID[0]=0x60;
  CpsBID[1]=0x00;
  CpsBID[2]=0x02;

  StartScroll[SCROLL_2]=1;
  StartScroll[SCROLL_3]=1;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,21,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,22,1);
  nRet=BurnLoadRom(CpsAd+0x20000,23,1);

  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

// Rom information
static struct BurnRomInfo Ffightj1RomDesc[] = {
	{ "ff30-36.rom",   0x20000, 0x088ed1c9, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "ff35-42.rom",   0x20000, 0xc4c491e6, BRF_ESS | BRF_PRG }, // 1 odd
	{ "ff31-37.rom",   0x20000, 0x708557ff, BRF_ESS | BRF_PRG }, // 2 even
	{ "ff36-43.rom",   0x20000, 0xc004004a, BRF_ESS | BRF_PRG }, // 3 odd
	{ "ff32-32m.bin",  0x80000, 0xc747696e, BRF_ESS | BRF_PRG }, // 4 both

  // graphics:
	{ "ff09.bin",      0x20000, 0x5b116d0d, BRF_GRA },			 // 5
	{ "ff01.bin",      0x20000, 0x815b1797, BRF_GRA },
	{ "ff13.bin",      0x20000, 0x8721a7da, BRF_GRA },
	{ "ff05.bin",      0x20000, 0xd0fcd4b5, BRF_GRA },
	{ "ff24.bin",      0x20000, 0xa1ab607a, BRF_GRA },			 // 9
	{ "ff17.bin",      0x20000, 0x2dc18cf4, BRF_GRA },
	{ "ff38.bin",      0x20000, 0x6535a57f, BRF_GRA },
	{ "ff32.bin",      0x20000, 0xc8bc4a57, BRF_GRA },
	{ "ff10.bin",      0x20000, 0x624a924a, BRF_GRA },			 // 13
	{ "ff02.bin",      0x20000, 0x5d91f694, BRF_GRA },
	{ "ff14.bin",      0x20000, 0x0a2e9101, BRF_GRA },
	{ "ff06.bin",      0x20000, 0x1c18f042, BRF_GRA },
	{ "ff25.bin",      0x20000, 0x6e8181ea, BRF_GRA },			 // 17
	{ "ff18.bin",      0x20000, 0xb19ede59, BRF_GRA },
	{ "ff39.bin",      0x20000, 0x9416b477, BRF_GRA },
	{ "ff33.bin",      0x20000, 0x7369fa07, BRF_GRA },

  // z80 rom
	{ "ff09-09.bin",   0x10000, 0xb8367eb5, BRF_GRA },			 // 21
  // samples
	{ "ff18-18.bin",   0x20000, 0x375c66e7, BRF_GRA },
	{ "ff19-19.bin",   0x20000, 0x1ef137f9, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Ffightj1) STD_ROM_FN(Ffightj1)

struct BurnDriver BurnDrvCpsFfightj1 = {
	"ffightj1", "ffight", NULL, "1989",
	"Final Fight (900305 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Ffightj1RomInfo,Ffightj1RomName,DrvInputInfo, ffightDIPInfo,
	Ffightj1Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};



