// Tenchi wo Kurau

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"         , BIT_DIGITAL, CpsInp018+0, "p1 coin"},
  {"P1 Start"        , BIT_DIGITAL, CpsInp018+4, "p1 start"},
  {"P1 Up"           , BIT_DIGITAL, CpsInp001+3, "p1 up"},
  {"P1 Down"         , BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left"         , BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right"        , BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Attack Left"  , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Attack Right" , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Special"      , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

  {"P2 Coin"         , BIT_DIGITAL, CpsInp018+1, "p2 coin"},
  {"P2 Start"        , BIT_DIGITAL, CpsInp018+5, "p2 start"},
  {"P2 Up"           , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"         , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"         , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"        , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Attack Left"  , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Attack Right" , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Special"      , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

  {"Reset"           , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"      , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Service"         , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip A"           , BIT_DIPSWITCH, &Cpi01A    , "dip"},
  {"Dip B"           , BIT_DIPSWITCH, &Cpi01C    , "dip"},
  {"Dip C"           , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo dwDIPList[]=
{
	// Defaults
	{0x15, 0xff, 0xff, 0x00, NULL                },
	{0x16, 0xff, 0xff, 0x00, NULL                },
	{0x17, 0xff, 0xff, 0x00, NULL                },

	// Dip A
        {0   , 0xfe, 0   , 7   , "Coin 1"            },
	{0x15, 0x01, 0x07, 0x06, "4 Coins 1 Credit"  },
	{0x15, 0x01, 0x07, 0x05, "3 Coins 1 Credit"  },
	{0x15, 0x01, 0x07, 0x04, "2 Coins 1 Credit"  },
	{0x15, 0x01, 0x07, 0x00, "1 Coin 1 Credit"   },
	{0x15, 0x01, 0x07, 0x01, "1 Coin 2 Credits"  },
	{0x15, 0x01, 0x07, 0x02, "1 Coin 3 Credits"  },
	{0x15, 0x01, 0x07, 0x03, "1 Coin 4 Credits"  },

        {0   , 0xfe, 0   , 7   , "Coin 2"            },
	{0x15, 0x01, 0x38, 0x30, "4 Coins 1 Credit"  },
	{0x15, 0x01, 0x38, 0x28, "3 Coins 1 Credit"  },
	{0x15, 0x01, 0x38, 0x20, "2 Coins 1 Credit"  },
	{0x15, 0x01, 0x38, 0x00, "1 Coin 1 Credit"   },
	{0x15, 0x01, 0x38, 0x08, "1 Coin 2 Credits"  },
	{0x15, 0x01, 0x38, 0x10, "1 Coin 3 Credits"  },
	{0x15, 0x01, 0x38, 0x18, "1 Coin 4 Credits"  },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x15, 0x01, 0x40, 0x00, "Off"               },
//	{0x15, 0x01, 0x40, 0x40, "On"                },

        {0   , 0xfe, 0   , 2   , "Free Play"         },
	{0x15, 0x01, 0x80, 0x00, "Off"               },
	{0x15, 0x01, 0x80, 0x80, "On"                },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Difficulty"        },
	{0x16, 0x01, 0x07, 0x03, "Very Easy"         },
	{0x16, 0x01, 0x07, 0x02, "Easy 2"            },
	{0x16, 0x01, 0x07, 0x01, "Easy 1"            },
	{0x16, 0x01, 0x07, 0x00, "Normal"            },
	{0x16, 0x01, 0x07, 0x04, "Difficult 1"       },
	{0x16, 0x01, 0x07, 0x05, "Difficult 2"       },
	{0x16, 0x01, 0x07, 0x06, "Difficult 3"       },
	{0x16, 0x01, 0x07, 0x07, "Very Difficult"    },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x16, 0x01, 0x08, 0x00, "Off"               },
//	{0x16, 0x01, 0x08, 0x08, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x16, 0x01, 0x10, 0x00, "Off"               },
//	{0x16, 0x01, 0x10, 0x10, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x16, 0x01, 0x20, 0x00, "Off"               },
//	{0x16, 0x01, 0x20, 0x20, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x16, 0x01, 0x40, 0x00, "Off"               },
//	{0x16, 0x01, 0x40, 0x40, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x16, 0x01, 0x80, 0x00, "Off"               },
//	{0x16, 0x01, 0x80, 0x80, "On"                },

	// Dip C
	{0   , 0xfe, 0   , 2   , "Freeze"            },
	{0x17, 0x01, 0x01, 0x00, "Off"               },
	{0x17, 0x01, 0x01, 0x01, "On"                },

	{0   , 0xfe, 0   , 2   , "Turbo Mode"        },
	{0x17, 0x01, 0x02, 0x00, "Off"               },
	{0x17, 0x01, 0x02, 0x02, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x17, 0x01, 0x04, 0x00, "Off"               },
//	{0x17, 0x01, 0x04, 0x04, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x17, 0x01, 0x08, 0x00, "Off"               },
//	{0x17, 0x01, 0x08, 0x08, "On"                },

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

STDDIPINFO(dw);


static int dwjInit()
{
  int nRet=0;
  Cps=1;
  nCpsRomLen=  0x100000;
  nCpsCodeLen= 0; // not encrypted
  nCpsGfxLen=  8*0x080000;
  nCpsZRomLen= 0x010000;
  nCpsAdLen=   2*0x020000;
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
  CpsLoadTilesByte(CpsGfx,             8);
  CpsLoadTilesByte(CpsGfx+(0x100000), 16);
  CpsLoadTilesByte(CpsGfx+(0x200000), 24);
  CpsLoadTilesByte(CpsGfx+(0x300000), 32);

  nCpsGfxScroll[2]=0x200000;
  nCpsGfxScroll[3]=0x200000;

  nCpsLcReg=0x6c; // Layer control register is at 0x6c
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x08;

  MaskAddr[0]=0x6a;
  MaskAddr[1]=0x68;
  MaskAddr[2]=0x66;
  MaskAddr[3]=0x64;


  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,40,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,41,1);
  nRet=BurnLoadRom(CpsAd+0x20000,42,1);


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


//=======================
//Tenchi wo Kurau (Japan)
//=======================

// Rom information
static struct BurnRomInfo DwjRomDesc[] = {
	{ "36.bin",        0x20000, 0x1a516657, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "42.bin",        0x20000, 0x12a290a0, BRF_ESS | BRF_PRG }, // 1 odd
	{ "37.bin",        0x20000, 0x932fc943, BRF_ESS | BRF_PRG }, // 2 even
	{ "43.bin",        0x20000, 0x872ad76d, BRF_ESS | BRF_PRG }, // 3 odd
	{ "34.bin",        0x20000, 0x8f663d00, BRF_ESS | BRF_PRG }, // 4 even 68000 code
	{ "40.bin",        0x20000, 0x1586dbf3, BRF_ESS | BRF_PRG }, // 5 odd
	{ "35.bin",        0x20000, 0x9db93d7a, BRF_ESS | BRF_PRG }, // 6 even
	{ "41.bin",        0x20000, 0x1aae69a4, BRF_ESS | BRF_PRG }, // 7 odd

    // graphics:
	{ "09.bin",        0x20000, 0xc3e83c69, BRF_GRA },			 // 8
	{ "01.bin",        0x20000, 0x187b2886, BRF_GRA },
	{ "13.bin",        0x20000, 0x0273d87d, BRF_GRA },
	{ "05.bin",        0x20000, 0x339378b8, BRF_GRA },
	{ "24.bin",        0x20000, 0xc6909b6f, BRF_GRA },			 // 12
	{ "17.bin",        0x20000, 0x2e2f8320, BRF_GRA },
	{ "38.bin",        0x20000, 0xcd7923ed, BRF_GRA },
	{ "32.bin",        0x20000, 0x21a0a453, BRF_GRA },
	{ "10.bin",        0x20000, 0xff28f8d0, BRF_GRA },			 // 16
	{ "02.bin",        0x20000, 0xcc83c02f, BRF_GRA },
	{ "14.bin",        0x20000, 0x18fb232c, BRF_GRA },
	{ "06.bin",        0x20000, 0x6f9edd75, BRF_GRA },
	{ "25.bin",        0x20000, 0x152ea74a, BRF_GRA },			 // 20
	{ "18.bin",        0x20000, 0x1833f932, BRF_GRA },
	{ "39.bin",        0x20000, 0xbc09b360, BRF_GRA },
	{ "33.bin",        0x20000, 0x89de1533, BRF_GRA },
	{ "11.bin",        0x20000, 0x29eaf490, BRF_GRA },			 // 24
	{ "03.bin",        0x20000, 0x7bf51337, BRF_GRA },
	{ "15.bin",        0x20000, 0xd36cdb91, BRF_GRA },
	{ "07.bin",        0x20000, 0xe04af054, BRF_GRA },
	{ "26.bin",        0x20000, 0x07fc714b, BRF_GRA },			 // 28
	{ "19.bin",        0x20000, 0x7114e5c6, BRF_GRA },
	{ "28.bin",        0x20000, 0xaf62bf07, BRF_GRA },
	{ "21.bin",        0x20000, 0x523f462a, BRF_GRA },
	{ "12.bin",        0x20000, 0x38652339, BRF_GRA },			 // 32
	{ "04.bin",        0x20000, 0x4951bc0f, BRF_GRA },
	{ "16.bin",        0x20000, 0x381608ae, BRF_GRA },
	{ "08.bin",        0x20000, 0xb475d4e9, BRF_GRA },
	{ "27.bin",        0x20000, 0xa27e81fa, BRF_GRA },			 // 36
	{ "20.bin",        0x20000, 0x002796dc, BRF_GRA },
	{ "29.bin",        0x20000, 0x6b41f82d, BRF_GRA },
	{ "22.bin",        0x20000, 0x52145369, BRF_GRA },

    // z80 rom
	{ "23.bin",        0x10000, 0xb3b79d4f, BRF_GRA },			 // 40
    // samples
	{ "30.bin",        0x20000, 0x7e5f6cb4, BRF_GRA },
	{ "31.bin",        0x20000, 0x4a30c737, BRF_GRA },
};

// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Dwj) STD_ROM_FN(Dwj)

struct BurnDriver BurnDrvCpsDwj = {
	"dynwarj", "dynwar", NULL, "1989",
	"Tenchi wo Kurau (Japan)\0", NULL, "Capcom", "CPS1",
	L"\u8EE2\u5730\u3092\u55B0\u3089\u3046 (Japan)\0Tenchi wo Kurau (Japan)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,DwjRomInfo,DwjRomName,DrvInputInfo, dwDIPInfo,
	dwjInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

static int dwInit()
{
  int nRet=0;
  Cps=1;
  nCpsRomLen=  0x100000;
  nCpsCodeLen= 0; // not encrypted
  nCpsGfxLen=  8*0x080000;
  nCpsZRomLen= 0x010000;
  nCpsAdLen=   2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000001,0,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x000000,1,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040001,2,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040000,3,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,4,1); if (nRet!=0) return 1;

  // Load graphics roms
  CpsLoadTiles(CpsGfx           ,5);
  CpsLoadTiles(CpsGfx+(0x200000),9);

  nCpsGfxScroll[2]=0x200000;
  nCpsGfxScroll[3]=0x200000;

  nCpsLcReg=0x6c; // Layer control register is at 0x6c
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x08;

  MaskAddr[0]=0x6a;
  MaskAddr[1]=0x68;
  MaskAddr[2]=0x66;
  MaskAddr[3]=0x64;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,13,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,14,1);
  nRet=BurnLoadRom(CpsAd+0x20000,15,1);

  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//====================
//Dynasty Wars (World)
//====================

// Rom information
static struct BurnRomInfo DwRomDesc[] = {
	{ "30.11f",        0x20000, 0xf9ec6d68, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "35.11h",        0x20000, 0xe41fff2f, BRF_ESS | BRF_PRG }, // 1 odd
	{ "31.12f",        0x20000, 0xe3de76ff, BRF_ESS | BRF_PRG }, // 2 even
	{ "36.12h",        0x20000, 0x7a13cfbf, BRF_ESS | BRF_PRG }, // 3 odd
	{ "tkm-9.8h",      0x80000, 0x93654bcf, BRF_ESS | BRF_PRG }, // 4

    // graphics:
	{ "tkm-5.7a",      0x80000, 0xf64bb6a0, BRF_GRA },
	{ "tkm-8.9a",      0x80000, 0x21fe6274, BRF_GRA },
	{ "tkm-6.3a",      0x80000, 0x0bf228cb, BRF_GRA },			 // 5
	{ "tkm-7.5a",      0x80000, 0x1255dfb1, BRF_GRA },
	{ "tkm-1.8a",      0x80000, 0x44f7661e, BRF_GRA },
	{ "tkm-4.10a",     0x80000, 0xa54c515d, BRF_GRA },
	{ "tkm-2.4a",      0x80000, 0xca5c687c, BRF_GRA },			 // 9
	{ "tkm-3.6a",      0x80000, 0xf9fe6591, BRF_GRA },

    // z80 rom
	{ "tke17.12b",     0x10000, 0xb3b79d4f, BRF_GRA },			 // 13
    // samples
	{ "tke18.11c",     0x20000, 0xac6e307d, BRF_GRA },
	{ "tke19.12c",     0x20000, 0x068741db, BRF_GRA },
};

// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Dw) STD_ROM_FN(Dw)

struct BurnDriver BurnDrvCpsDw = {
	"dynwar", NULL, NULL, "1989",
	"Dynasty Wars (World)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,DwRomInfo,DwRomName,DrvInputInfo, dwDIPInfo,
	dwInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
