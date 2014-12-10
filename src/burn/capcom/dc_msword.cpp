// Magic Sword

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , 0, CpsInp018+0, "p1 coin"},
  {"P1 Start"      , 0, CpsInp018+4, "p1 start"},
  {"P1 Up"         , 0, CpsInp001+3, "p1 up"},
  {"P1 Down"       , 0, CpsInp001+2, "p1 down"},
  {"P1 Left"       , 0, CpsInp001+1, "p1 left"},
  {"P1 Right"      , 0, CpsInp001+0, "p1 right"},
  {"P1 Attack"     , 0, CpsInp001+4, "p1 fire 1"},
  {"P1 Jump"       , 0, CpsInp001+5, "p1 fire 2"},
  {"P1 Fire 3"     , 0, CpsInp001+6, "p1 fire 3"},

  {"P2 Coin"       , 0, CpsInp018+1, "p2 coin"},
  {"P2 Start"      , 0, CpsInp018+5, "p2 start"},
  {"P2 Up"         , 0, CpsInp000+3, "p2 up"},
  {"P2 Down"       , 0, CpsInp000+2, "p2 down"},
  {"P2 Left"       , 0, CpsInp000+1, "p2 left"},
  {"P2 Right"      , 0, CpsInp000+0, "p2 right"},
  {"P2 Attack"     , 0, CpsInp000+4, "p2 fire 1"},
  {"P2 Jump"       , 0, CpsInp000+5, "p2 fire 2"},
  {"P2 Fire 3"     , 0, CpsInp000+6, "p2 fire 3"},

  {"Reset"         , 0, &CpsReset,   "reset"},
  {"Diagnostic"    , 0, CpsInp018+6, "diag"},
  {"Service"       , 0, CpsInp018+2, "service"},
  {"Dip A"         , 2, &Cpi01A    , "dip"},
  {"Dip B"         , 2, &Cpi01C    , "dip"},
  {"Dip C"         , 2, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo mswordDIPList[]=
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

	{0   , 0xfe, 0   , 2   , "2C to Start, 1 to Cont" },
	{0x15, 0x01, 0x40, 0x00, "Off"                    },
	{0x15, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x15, 0x01, 0x80, 0x00, "Off"                    },
//	{0x15, 0x01, 0x80, 0x80, "On"                     },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Level 1"                },
	{0x16, 0x01, 0x07, 0x00, "Easy 3"                 },
	{0x16, 0x01, 0x07, 0x01, "Easy 2"                 },
	{0x16, 0x01, 0x07, 0x02, "Easy 1"                 },
	{0x16, 0x01, 0x07, 0x03, "Normal"                 },
	{0x16, 0x01, 0x07, 0x04, "Difficult 1"            },
	{0x16, 0x01, 0x07, 0x05, "Difficult 2"            },
	{0x16, 0x01, 0x07, 0x06, "Difficult 3"            },
	{0x16, 0x01, 0x07, 0x07, "Difficult 4"            },

	{0   , 0xfe, 0   , 8   , "Level 2"                },
	{0x16, 0x01, 0x38, 0x18, "Easy 3"                 },
	{0x16, 0x01, 0x38, 0x10, "Easy 2"                 },
	{0x16, 0x01, 0x38, 0x08, "Easy 1"                 },
	{0x16, 0x01, 0x38, 0x00, "Normal"                 },
	{0x16, 0x01, 0x38, 0x20, "Difficult 1"            },
	{0x16, 0x01, 0x38, 0x28, "Difficult 2"            },
	{0x16, 0x01, 0x38, 0x30, "Difficult 3"            },
	{0x16, 0x01, 0x38, 0x38, "Difficult 4"            },

	{0   , 0xfe, 0   , 2   , "Stage Select"           },
	{0x16, 0x01, 0x40, 0x00, "Off"                    },
	{0x16, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x16, 0x01, 0x80, 0x00, "Off"                    },
//	{0x16, 0x01, 0x80, 0x80, "On"                     },

	// Dip C
	{0   , 0xfe, 0   , 4   , "Vitality"               },
	{0x17, 0x01, 0x03, 0x03, "1"                      },
	{0x17, 0x01, 0x03, 0x00, "2"                      },
	{0x17, 0x01, 0x03, 0x01, "3"                      },
	{0x17, 0x01, 0x03, 0x02, "4"                      },

	{0   , 0xfe, 0   , 2   , "Free Play"              },
	{0x17, 0x01, 0x04, 0x00, "Off"                    },
	{0x17, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Freeze"                 },
	{0x17, 0x01, 0x08, 0x00, "Off"                    },
	{0x17, 0x01, 0x08, 0x08, "On"                     },

	{0   , 0xfe, 0   , 2   , "Flip"                   },
	{0x17, 0x01, 0x10, 0x00, "Off"                    },
	{0x17, 0x01, 0x10, 0x10, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sound"             },
	{0x17, 0x01, 0x20, 0x00, "Off"                    },
	{0x17, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 2   , "Continue"               },
	{0x17, 0x01, 0x40, 0x00, "Off"                    },
	{0x17, 0x01, 0x40, 0x40, "On"                     },
};

STDDIPINFO(msword);


static int DrvInit()
{
  int nRet=0;
  Cps=1; Msword=1;
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

  nCpsLcReg=0x62; // Layer control register is at 0x62
  CpsLayEn[1]=0x20;
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x02;

  MaskAddr[0]=0x64;
  MaskAddr[1]=0x66;
  MaskAddr[2]=0x68;
  MaskAddr[3]=0x6a;

  StartScroll[SCROLL_2]=0x2800;
  EndScroll[SCROLL_2]=0x37ff;

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

static int DrvExit()
{


  StartScroll[SCROLL_2]=0;
  EndScroll[SCROLL_2]=0xffff;

  CpsRunExit();
  CpsExit();
  nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0; Msword=0;
  return 0;
}

//====================================
//Magic Sword - heroic fantasy (World)
//====================================


static struct BurnRomInfo MswordRomDesc[] = {
	{ "mse_30.rom",    0x20000, 0x03fc8dbc, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "mse_35.rom",    0x20000, 0xd5bf66cd, BRF_ESS | BRF_PRG }, //  1
	{ "mse_31.rom",    0x20000, 0x30332bcf, BRF_ESS | BRF_PRG }, //  2 68000 code
	{ "mse_36.rom",    0x20000, 0x8f7d6ce9, BRF_ESS | BRF_PRG }, //  3
	{ "ms_32.rom",     0x80000, 0x2475ddfc, BRF_ESS | BRF_PRG }, //  4

// 5
	{ "ms_gfx5.rom",   0x80000, 0xc00fe7e2, BRF_GRA },
	{ "ms_gfx7.rom",   0x80000, 0x4ccacac5, BRF_GRA },
	{ "ms_gfx1.rom",   0x80000, 0x0d2bbe00, BRF_GRA },
	{ "ms_gfx3.rom",   0x80000, 0x3a1a5bf4, BRF_GRA },

// 9
// z80 program
	{ "ms_9.rom",      0x10000, 0x57b29519, BRF_SND },
// adpcm samples
	{ "ms_18.rom",     0x20000, 0xfb64e90d, BRF_SND },
	{ "ms_19.rom",     0x20000, 0x74f892b9, BRF_SND },
// 18
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Msword) STD_ROM_FN(Msword)

struct BurnDriver BurnDrvCpsMsword = {
	"msword", NULL, NULL, "1990",
	"Magic Sword - heroic fantasy (25.07.1990 other country)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,MswordRomInfo,MswordRomName,DrvInputInfo, mswordDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=======================================
//Magic Sword - heroic fantasy (World r1)
//=======================================


static struct BurnRomInfo Mswordr1RomDesc[] = {
	{ "ms30.11f",      0x20000, 0x21c1f078, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "ms35.11h",      0x20000, 0xa540a73a, BRF_ESS | BRF_PRG }, //  1
	{ "ms31.12f",      0x20000, 0xd7e762b5, BRF_ESS | BRF_PRG }, //  2 68000 code
	{ "ms36.12h",      0x20000, 0x66f2dcdb, BRF_ESS | BRF_PRG }, //  3
	{ "ms_32.rom",     0x80000, 0x2475ddfc, BRF_ESS | BRF_PRG }, //  4

// 5
	{ "ms_gfx5.rom",   0x80000, 0xc00fe7e2, BRF_GRA },
	{ "ms_gfx7.rom",   0x80000, 0x4ccacac5, BRF_GRA },
	{ "ms_gfx1.rom",   0x80000, 0x0d2bbe00, BRF_GRA },
	{ "ms_gfx3.rom",   0x80000, 0x3a1a5bf4, BRF_GRA },

// 9
// z80 program
	{ "ms_9.rom",      0x10000, 0x57b29519, BRF_SND },
// adpcm samples
	{ "ms_18.rom",     0x20000, 0xfb64e90d, BRF_SND },
	{ "ms_19.rom",     0x20000, 0x74f892b9, BRF_SND },
// 18
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Mswordr1) STD_ROM_FN(Mswordr1)

struct BurnDriver BurnDrvCpsMswordr1 = {
	"mswordr1", "msword", NULL, "1990",
	"Magic Sword - heroic fantasy (90.06.23 other country)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Mswordr1RomInfo,Mswordr1RomName,DrvInputInfo, mswordDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//===================
//Magic Sword (Japan)
//===================


static struct BurnRomInfo MswordjRomDesc[] = {
	{ "msj_36.bin",    0x20000, 0x04f0ef50, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "msj_42.bin",    0x20000, 0x9fcbb9cd, BRF_ESS | BRF_PRG }, //  1
	{ "msj_37.bin",    0x20000, 0x6c060d70, BRF_ESS | BRF_PRG }, //  2 68000 code
	{ "msj_43.bin",    0x20000, 0xaec77787, BRF_ESS | BRF_PRG }, //  3
	{ "ms_32.rom",     0x80000, 0x2475ddfc, BRF_ESS | BRF_PRG }, //  4

// 5
	{ "ms_gfx5.rom",   0x80000, 0xc00fe7e2, BRF_GRA },
	{ "ms_gfx7.rom",   0x80000, 0x4ccacac5, BRF_GRA },
	{ "ms_gfx1.rom",   0x80000, 0x0d2bbe00, BRF_GRA },
	{ "ms_gfx3.rom",   0x80000, 0x3a1a5bf4, BRF_GRA },

// 9
// z80 program
	{ "ms_9.rom",      0x10000, 0x57b29519, BRF_SND },
// adpcm samples
	{ "ms_18.rom",     0x20000, 0xfb64e90d, BRF_SND },
	{ "ms_19.rom",     0x20000, 0x74f892b9, BRF_SND },
// 18
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Mswordj) STD_ROM_FN(Mswordj)

struct BurnDriver BurnDrvCpsMswordj = {
	"mswordj", "msword", NULL, "1990",
	"Magic Sword (23.06.1990 Japan)\0", NULL, "Capcom", "CPS1",
	L"Magic Sword (23.06.1990 Japan)\0Magic Sword\u30DE\u30B8\u30C3\u30AF\uFF65\u30BD\u30FC\u30C9\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,MswordjRomInfo,MswordjRomName,DrvInputInfo, mswordDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================================
//Magic Sword - heroic fantasy (USA)
//==================================


static struct BurnRomInfo MsworduRomDesc[] = {
	{ "msu30",         0x20000, 0xd963c816, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "msu35",         0x20000, 0x72f179b3, BRF_ESS | BRF_PRG }, //  1
	{ "msu31",         0x20000, 0x20cd7904, BRF_ESS | BRF_PRG }, //  2 68000 code
	{ "msu36",         0x20000, 0xbf88c080, BRF_ESS | BRF_PRG }, //  3
	{ "ms_32.rom",     0x80000, 0x2475ddfc, BRF_ESS | BRF_PRG }, //  4

// 5
	{ "ms_gfx5.rom",   0x80000, 0xc00fe7e2, BRF_GRA },
	{ "ms_gfx7.rom",   0x80000, 0x4ccacac5, BRF_GRA },
	{ "ms_gfx1.rom",   0x80000, 0x0d2bbe00, BRF_GRA },
	{ "ms_gfx3.rom",   0x80000, 0x3a1a5bf4, BRF_GRA },

// 9
// z80 program
	{ "ms_9.rom",      0x10000, 0x57b29519, BRF_SND },
// adpcm samples
	{ "ms_18.rom",     0x20000, 0xfb64e90d, BRF_SND },
	{ "ms_19.rom",     0x20000, 0x74f892b9, BRF_SND },
// 18
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Mswordu) STD_ROM_FN(Mswordu)

struct BurnDriver BurnDrvCpsMswordu = {
	"mswordu", "msword", NULL, "1990",
	"Magic Sword - heroic fantasy (25.07.1990 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,MsworduRomInfo,MsworduRomName,DrvInputInfo, mswordDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
