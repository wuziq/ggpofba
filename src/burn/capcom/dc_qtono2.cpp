// Quiz Tonosama no Yabou 2 Zenkoku-ban

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

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"},
  {"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo qtono2DIPList[]=
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
	{0   , 0xfe, 0   , 8   , "Difficulty"        },
	{0x10, 0x01, 0x07, 0x03, "Very Easy"         },
	{0x10, 0x01, 0x07, 0x02, "Easy 2"            },
	{0x10, 0x01, 0x07, 0x01, "Easy 1"            },
	{0x10, 0x01, 0x07, 0x00, "Normal"            },
	{0x10, 0x01, 0x07, 0x04, "Difficult 1"       },
	{0x10, 0x01, 0x07, 0x05, "Difficult 2"       },
	{0x10, 0x01, 0x07, 0x06, "Difficult 3"       },
	{0x10, 0x01, 0x07, 0x07, "Very Difficult"    },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x10, 0x01, 0x08, 0x00, "Off"               },
//	{0x10, 0x01, 0x08, 0x08, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x10, 0x01, 0x10, 0x00, "Off"               },
//	{0x10, 0x01, 0x10, 0x10, "On"                },

	{0   , 0xfe, 0   , 6   , "Initital Vitality" },
	{0x10, 0x01, 0xe0, 0x60, "1"                 },
	{0x10, 0x01, 0xe0, 0x80, "2"                 },
	{0x10, 0x01, 0xe0, 0xa0, "3"                 },
	{0x10, 0x01, 0xe0, 0xc0, "4"                 },
	{0x10, 0x01, 0xe0, 0xe0, "5"                 },
	{0x10, 0x01, 0xe0, 0x00, "6"                 },

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
	{0x11, 0x01, 0x40, 0x00, "Off"               },
	{0x11, 0x01, 0x40, 0x40, "On"                },
};

STDDIPINFO(qtono2);


static int DrvInit()
{
  int nRet=0;
  Cps=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 8*0x080000;
  nCpsZRomLen=  0x008000;
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

  nCpsLcReg=0x66; // Layer control register is at 0x66
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x08;

  // Protection enable code by KEV
  CpsMProt[0]=0x40;
  CpsMProt[1]=0x42;
  CpsMProt[2]=0x44;
  CpsMProt[3]=0x46;

  MaskAddr[0]=0x68;
  MaskAddr[1]=0x6a;
  MaskAddr[2]=0x6c;
  MaskAddr[3]=0x6e;

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
  Cps=0;
  return 0;
}


//============================================
//Quiz Tonosama no Yabou 2 Zenkoku-ban (Japan)
//============================================

// Rom information
static struct BurnRomInfo Qtono2RomDesc[] = {
	{ "tn2j-30.11e",   0x20000, 0x9226eb5e, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "tn2j-37.11f",   0x20000, 0xd1d30da1, BRF_ESS | BRF_PRG }, // 1 odd
	{ "tn2j-31.12e",   0x20000, 0x015e6a8a, BRF_ESS | BRF_PRG }, // 2 even 68000 code
	{ "tn2j-38.12f",   0x20000, 0x1f139bcc, BRF_ESS | BRF_PRG }, // 3 odd
	{ "tn2j-28.9e",    0x20000, 0x86d27f71, BRF_ESS | BRF_PRG }, // 4 even 68000 code
	{ "tn2j-35.9f",    0x20000, 0x7a1ab87d, BRF_ESS | BRF_PRG }, // 5 odd
	{ "tn2j-29.10e",   0x20000, 0x9c384e99, BRF_ESS | BRF_PRG }, // 6 even 68000 code
	{ "tn2j-36.10f",   0x20000, 0x4c4b2a0a, BRF_ESS | BRF_PRG }, // 7 odd

  // graphics:
	{ "tn2-02m.4a",    0x80000, 0xf2016a34, BRF_GRA },			 // 8
	{ "tn2-04m.6a",    0x80000, 0x094e0fb1, BRF_GRA },
	{ "tn2-01m.3a",    0x80000, 0xcb950cf9, BRF_GRA },
	{ "tn2-03m.5a",    0x80000, 0x18a5bf59, BRF_GRA },
	{ "tn2-11m.4c",    0x80000, 0xd0edd30b, BRF_GRA },			 // 12
	{ "tn2-13m.6c",    0x80000, 0x426621c3, BRF_GRA },
	{ "tn2-10m.3c",    0x80000, 0xa34ece70, BRF_GRA },
	{ "tn2-12m.5c",    0x80000, 0xe04ff2f4, BRF_GRA },

  // z80 rom
	{ "tn2j-09.12a",   0x08000, 0x6d8edcef, BRF_GRA },			 // 16
  // samples
	{ "tn2j-18.11c",   0x20000, 0xa40bf9a7, BRF_GRA },
	{ "tn2j-19.12c",   0x20000, 0x5b3b931e, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Qtono2) STD_ROM_FN(Qtono2)

struct BurnDriver BurnDrvCpsQtono2 = {
	"qtono2", NULL, NULL, "1995",
	"Quiz Tonosama no Yabou 2 Zenkoku-ban (tonosama 2 950123 Japan)\0", NULL, "Capcom", "CPS1",
	L"\u30AF\u30A4\u30BA\u6BBF\u69D8\u306E\u91CE\u671B\uFF12 (\u3068\u306E\u3055\u307E\u306E\u3084\u307C\u3046 2 950123 Japan)\0Quiz Tonosama no Yabou 2 Zenkoku-ban (tonosama 2 950123 Japan)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,Qtono2RomInfo,Qtono2RomName,DrvInputInfo, qtono2DIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
