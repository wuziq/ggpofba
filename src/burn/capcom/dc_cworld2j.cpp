#include "cps.h"
// Capcom World 2

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

static struct BurnDIPInfo cworld2jDIPList[]=
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

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x0f, 0x01, 0x38, 0x00, "Off"                    },
//	{0x0f, 0x01, 0x38, 0x38, "On"                     },

	{0   , 0xfe, 0   , 2   , "Continue Coin"          },
	{0x0f, 0x01, 0x40, 0x00, "Off"                    },
	{0x0f, 0x01, 0x40, 0x40, "On"                     },

	{0   , 0xfe, 0   , 2   , "Test"                   },
	{0x0f, 0x01, 0x80, 0x00, "Off"                    },
	{0x0f, 0x01, 0x80, 0x80, "On"                     },

	// Dip B
	{0   , 0xfe, 0   , 4   , "Game Level"             },
	{0x10, 0x01, 0x07, 0x00, "0"                      },
	{0x10, 0x01, 0x07, 0x02, "1"                      },
	{0x10, 0x01, 0x07, 0x03, "2"                      },
	{0x10, 0x01, 0x07, 0x04, "3"                      },

	{0   , 0xfe, 0   , 3   , "Extend"                 },
	{0x10, 0x01, 0x18, 0x18, "D"                      },
	{0x10, 0x01, 0x18, 0x08, "E"                      },
	{0x10, 0x01, 0x18, 0x00, "N"                      },

	{0   , 0xfe, 0   , 5   , "Players Life"           },
	{0x10, 0x01, 0xe0, 0x80, "1"                      },
	{0x10, 0x01, 0xe0, 0x60, "2"                      },
	{0x10, 0x01, 0xe0, 0x00, "3"                      },
	{0x10, 0x01, 0xe0, 0x40, "4"                      },
	{0x10, 0x01, 0xe0, 0x20, "5"                      },

	// Dip C
//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x11, 0x01, 0x01, 0x00, "Off                     },
//	{0x11, 0x01, 0x01, 0x01, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x11, 0x01, 0x02, 0x00, "Off                     },
//	{0x11, 0x01, 0x02, 0x02, "On"                     },

	{0   , 0xfe, 0   , 2   , "Free Play"              },
	{0x11, 0x01, 0x04, 0x00, "Off"                    },
	{0x11, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Stop"                   },
	{0x11, 0x01, 0x08, 0x00, "Off"                    },
	{0x11, 0x01, 0x08, 0x08, "On"                     },

	{0   , 0xfe, 0   , 2   , "Flip"                   },
	{0x11, 0x01, 0x10, 0x00, "Off"                    },
	{0x11, 0x01, 0x10, 0x10, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sound"             },
	{0x11, 0x01, 0x20, 0x00, "Off"                    },
	{0x11, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 2   , "Continue"               },
	{0x11, 0x01, 0x40, 0x00, "Off"                    },
	{0x11, 0x01, 0x40, 0x40, "On"                     },
};

STDDIPINFO(cworld2j);


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
  nRet=BurnLoadRom(CpsRom+0x080001,4,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,5,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x0c0001,6,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x0c0000,7,2); if (nRet!=0) return 1;

  // Load graphics roms
  CpsLoadTilesByte(CpsGfx, 8);
  CpsLoadTilesByte(CpsGfx+(8*0x020000), 8+8);

  nCpsLcReg=0x60; // Layer control register is at 0x60
  CpsLayEn[1]=0x20;
  CpsLayEn[2]=0x14;
  CpsLayEn[3]=0x14;

  // Protection enable code by KEV
  CpsMProt[0]=0x00;
  CpsMProt[1]=0x00;
  CpsMProt[2]=0x00;
  CpsMProt[3]=0x00;

  MaskAddr[0]=0x6e;
  MaskAddr[1]=0x6c;
  MaskAddr[2]=0x6a;
  MaskAddr[3]=0x68;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,24,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,25,1);
  nRet=BurnLoadRom(CpsAd+0x20000,26,1);


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


//======================
//Capcom World 2 (Japan)
//======================

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo Cworld2jRomDesc[] = {
	{ "q536.bin",      0x20000, 0x38a08099, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "q542.bin",      0x20000, 0x4d29b3a4, BRF_ESS | BRF_PRG }, // 1 odd
	{ "q537.bin",      0x20000, 0xeb547ebc, BRF_ESS | BRF_PRG }, // 2 even
	{ "q543.bin",      0x20000, 0x3ef65ea8, BRF_ESS | BRF_PRG }, // 3 odd
	{ "q534.bin",      0x20000, 0x7fcc1317, BRF_ESS | BRF_PRG }, // 4 even 68000 code
	{ "q540.bin",      0x20000, 0x7f14b7b4, BRF_ESS | BRF_PRG }, // 5 odd
	{ "q535.bin",      0x20000, 0xabacee26, BRF_ESS | BRF_PRG }, // 6 even
	{ "q541.bin",      0x20000, 0xd3654067, BRF_ESS | BRF_PRG }, // 7 odd

  // graphics:
	{ "q509.bin",      0x20000, 0x48496d80, BRF_GRA },			 // 8
	{ "q501.bin",      0x20000, 0xc5453f56, BRF_GRA },
	{ "q513.bin",      0x20000, 0xc741ac52, BRF_GRA },
	{ "q505.bin",      0x20000, 0x143e068f, BRF_GRA },
	{ "q524.bin",      0x20000, 0xb419d139, BRF_GRA },			 // 12
	{ "q517.bin",      0x20000, 0xbd3b4d11, BRF_GRA },
	{ "q538.bin",      0x20000, 0x9c24670c, BRF_GRA },
	{ "q532.bin",      0x20000, 0x3ef9c7c2, BRF_GRA },
	{ "q510.bin",      0x20000, 0x119e5e93, BRF_GRA },			 // 16
	{ "q502.bin",      0x20000, 0xa2cadcbe, BRF_GRA },
	{ "q514.bin",      0x20000, 0xa8755f82, BRF_GRA },
	{ "q506.bin",      0x20000, 0xc92a91fc, BRF_GRA },
	{ "q525.bin",      0x20000, 0x979237cb, BRF_GRA },			 // 20
	{ "q518.bin",      0x20000, 0xc57da03c, BRF_GRA },
	{ "q539.bin",      0x20000, 0xa5839b25, BRF_GRA },
	{ "q533.bin",      0x20000, 0x04d03930, BRF_GRA },

  // z80 rom
	{ "q523.bin",      0x10000, 0xe14dc524, BRF_GRA },			 // 24
  // samples
	{ "q530.bin",      0x20000, 0xd10c1b68, BRF_GRA },
	{ "q531.bin",      0x20000, 0x7d17e496, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Cworld2j) STD_ROM_FN(Cworld2j)

struct BurnDriver BurnDrvCpsCworld2j = {
	"cworld2j", NULL, NULL, "1992",
	"Capcom World 2 (920611 Japan)\0", NULL, "Capcom", "CPS1",
	L"Capcom World 2 (\u30AF\u30A4\u30BA\uFF15 \u3042\u3069\u3079\u3093\u3061\u3083\u30FC\u304F\u3044\u305A \u304B\u3077\u3053\u3093\u308F\u30FC\u308B\u3069\uFF12 920611 Japan)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,Cworld2jRomInfo,Cworld2jRomName,DrvInputInfo, cworld2jDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
