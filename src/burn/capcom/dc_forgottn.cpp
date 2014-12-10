// Forgotten Worlds

#include "cps.h"

#define A(a, b, c, d) {a, b, (unsigned char*)(c), d}

static struct BurnInputInfo DrvInputList[] =
{
	{"P1 Coin"       , BIT_DIGITAL,		CpsInp018+0, "p1 coin"},
	{"P1 Start"      , BIT_DIGITAL,		CpsInp018+4, "p1 start"},
	{"P1 Up"         , BIT_DIGITAL,		CpsInp001+3, "p1 up"},
	{"P1 Down"       , BIT_DIGITAL,		CpsInp001+2, "p1 down"},
	{"P1 Left"       , BIT_DIGITAL,		CpsInp001+1, "p1 left"},
	{"P1 Right"      , BIT_DIGITAL,		CpsInp001+0, "p1 right"},
	{"P1 Attack"     , BIT_DIGITAL,		CpsInp001+4, "p1 fire 1"},
   A("P1 Turn"       , BIT_ANALOG_REL,	&CpsInp055,	 "p1 z-axis"),

	{"P2 Coin"       , BIT_DIGITAL,		CpsInp018+1, "p2 coin"},
	{"P2 Start"      , BIT_DIGITAL,		CpsInp018+5, "p2 start"},
	{"P2 Up"         , BIT_DIGITAL,		CpsInp000+3, "p2 up"},
	{"P2 Down"       , BIT_DIGITAL,		CpsInp000+2, "p2 down"},
	{"P2 Left"       , BIT_DIGITAL,		CpsInp000+1, "p2 left"},
	{"P2 Right"      , BIT_DIGITAL,		CpsInp000+0, "p2 right"},
	{"P2 Attack"     , BIT_DIGITAL,		CpsInp000+4, "p2 fire 1"},
   A("P2 Turn"       , BIT_ANALOG_REL,	&CpsInp05d,	 "p2 z-axis"),

	{"Reset"         , BIT_DIGITAL,		&CpsReset,   "reset"},
	{"Diagnostic"    , BIT_DIGITAL,		CpsInp018+6, "diag"},
	{"Service"       , BIT_DIGITAL,		CpsInp018+2, "service"},

	{"Dip A"         , BIT_DIPSWITCH,	&Cpi01A    , "dip"       },
	{"Dip B"         , BIT_DIPSWITCH,	&Cpi01C    , "dip"       },
	{"Dip C"         , BIT_DIPSWITCH,	&Cpi01E    , "dip"       },
};

#undef A

STDINPUTINFO(Drv);

static struct BurnDIPInfo forgottnDIPList[]=
{
	// Defaults
	{0x19, 0xff, 0xff, 0x00, NULL                     },
	{0x1a, 0xff, 0xff, 0x00, NULL                     },
	{0x1b, 0xff, 0xff, 0x00, NULL                     },

	// Dip A
	{0   , 0xfe, 0   , 8   , "Coin 1"                 },
	{0x19, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x19, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x19, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x19, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x19, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x19, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x19, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x19, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 8   , "Coin 2"                 },
	{0x19, 0x01, 0x38, 0x38, "4 Coins 1 Credit"       },
	{0x19, 0x01, 0x38, 0x30, "3 Coins 1 Credit"       },
	{0x19, 0x01, 0x38, 0x28, "2 Coins 1 Credit"       },
	{0x19, 0x01, 0x38, 0x00, "1 Coin 1 Credit"        },
	{0x19, 0x01, 0x38, 0x08, "1 Coin 2 Credits"       },
	{0x19, 0x01, 0x38, 0x10, "1 Coin 3 Credits"       },
	{0x19, 0x01, 0x38, 0x18, "1 Coin 4 Credits"       },
	{0x19, 0x01, 0x38, 0x20, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 2   , "Demo Sound"             },
	{0x19, 0x01, 0x40, 0x00, "Off"                    },
	{0x19, 0x01, 0x40, 0x40, "On"                     },

	{0   , 0xfe, 0   , 2   , "Flip"                   },
	{0x19, 0x01, 0x80, 0x00, "Off"                    },
	{0x19, 0x01, 0x80, 0x80, "On"                     },

	// Dip B
//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1a, 0x01, 0x01, 0x00, "Off"                    },
//	{0x1a, 0x01, 0x01, 0x01, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1a, 0x01, 0x02, 0x00, "Off"                    },
//	{0x1a, 0x01, 0x02, 0x02, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1a, 0x01, 0x04, 0x00, "Off"                    },
//	{0x1a, 0x01, 0x04, 0x04, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1a, 0x01, 0x08, 0x00, "Off"                    },
//	{0x1a, 0x01, 0x08, 0x08, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1a, 0x01, 0x10, 0x00, "Off"                    },
//	{0x1a, 0x01, 0x10, 0x10, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1a, 0x01, 0x20, 0x00, "Off"                    },
//	{0x1a, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 2   , "Service Mode"           },
	{0x1a, 0x01, 0x40, 0x00, "Off"                    },
	{0x1a, 0x01, 0x40, 0x40, "On"                     },

	{0   , 0xfe, 0   , 2   , "Freeze"                 },
	{0x1a, 0x01, 0x80, 0x00, "Off"                    },
	{0x1a, 0x01, 0x80, 0x80, "On"                     },

	// Dip C
//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x01, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x01, 0x01, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x02, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x02, 0x02, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x04, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x04, 0x04, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x08, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x08, 0x08, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x10, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x10, 0x10, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x20, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x20, 0x20, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x40, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x80, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x80, 0x80, "On"                     },
};

STDDIPINFO(forgottn);


static int DrvInit()
{
   int nRet=0;
   Cps=1; Forgottn=1;
   nCpsRomLen=   0x100000;
   nCpsCodeLen=0; // not encrypted
   nCpsGfxLen =8*0x080000 + 0x2000;
   nCpsZRomLen=  0x010000;
   nCpsAdLen  =2*0x020000;
   nRet=CpsInit(); if (nRet!=0) return 1;
   CpsStar = CpsGfx + 8*0x080000;

   nRet=BurnLoadRom(CpsRom+0x000001,0,2); if (nRet!=0) return 1;
   nRet=BurnLoadRom(CpsRom+0x000000,1,2); if (nRet!=0) return 1;
   nRet=BurnLoadRom(CpsRom+0x040001,2,2); if (nRet!=0) return 1;
   nRet=BurnLoadRom(CpsRom+0x040000,3,2); if (nRet!=0) return 1;
   nRet=BurnLoadRom(CpsRom+0x080000,4,1); if (nRet!=0) return 1;

   // Load graphics roms
   CpsLoadTiles(CpsGfx         ,5);
   CpsLoadTiles(CpsGfx+0x200000,9);

   // Enable starfield layers
   CpsLayEn[4]=0x30;
   CpsLayEn[5]=0x30;

   CpsLoadStars(CpsStar, 5);

   MaskAddr[0]=0x68;
   MaskAddr[1]=0x6a;
   MaskAddr[2]=0x6c;
   MaskAddr[3]=0x6e;

   nRet=BurnLoadRom(CpsZRom,13,1); //changed to 13

   nRet=BurnLoadRom(CpsAd        ,14,1); //changed to 14
   nRet=BurnLoadRom(CpsAd+0x20000,15,1); //changed to 15


   nRet=CpsRunInit();

   if (nRet!=0) return 1;

   return 0;
}

static int DrvExit()
{


   CpsRunExit();
   CpsExit();
   nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
   Cps=0; Forgottn=0;
   return 0;
}


//======================
//Forgotten Worlds (USA)
//======================

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo ForgottnRomDesc[] = {
	{ "lwu11a",        0x20000, 0xddf78831, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "lwu15a",        0x20000, 0xf7ce2097, BRF_ESS | BRF_PRG }, // 1 odd
	{ "lwu10a",        0x20000, 0x8cb38c81, BRF_ESS | BRF_PRG }, // 2 even
	{ "lwu14a",        0x20000, 0xd70ef9fd, BRF_ESS | BRF_PRG }, // 3 odd
	{ "lw-07",         0x80000, 0xfd252a26, BRF_ESS | BRF_PRG }, // 4 both

  // graphics:
	{ "lw-02",         0x80000, 0x43e6c5c8, BRF_GRA },			 // 5
	{ "lw-09",         0x80000, 0x899cb4ad, BRF_GRA },
	{ "lw-06",         0x80000, 0x5b9edffc, BRF_GRA },
	{ "lw-13",         0x80000, 0x8e058ef5, BRF_GRA },
	{ "lw-01",         0x80000, 0x0318f298, BRF_GRA },			 // 9
	{ "lw-08",         0x80000, 0x25a8e43c, BRF_GRA },
	{ "lw-05",         0x80000, 0xe4552fd7, BRF_GRA },
	{ "lw-12",         0x80000, 0x8e6a832b, BRF_GRA },

  // z80 rom
	{ "lwu00",         0x10000, 0x59df2a63, BRF_GRA },			 // 13
  // samples
	{ "lw-03u",        0x20000, 0x807d051f, BRF_GRA },
	{ "lw-04u",        0x20000, 0xe6cd098e, BRF_GRA },
	
	{ "pal16l8.4a",    260,     0x00000000, BRF_NODUMP },
	{ "pal16l8.9j",    260,     0x00000000, BRF_NODUMP },
	{ "pal16l8.10f",   260,     0x00000000, BRF_NODUMP },
	{ "pal16l8.13j",   260,     0x00000000, BRF_NODUMP },
	{ "pal16l8.14j",   260,     0x00000000, BRF_NODUMP },
	{ "epl16p8.15e",   263,     0x00000000, BRF_NODUMP },
	{ "epl16p8.3a",    263,     0x00000000, BRF_NODUMP },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Forgottn) STD_ROM_FN(Forgottn)

struct BurnDriver BurnDrvCpsForgottn = {
	"forgottn", NULL, NULL, "1988",
	"Forgotten Worlds (US)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1_GENERIC,
	NULL,ForgottnRomInfo,ForgottnRomName,DrvInputInfo, forgottnDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//===================
//Lost Worlds (Japan)
//===================

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo LostwrldRomDesc[] = {
	{ "lw-11c.14f",    0x20000, 0x67e42546, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "lw-15c.14g",    0x20000, 0x402e2a46, BRF_ESS | BRF_PRG }, // 1 odd
	{ "lw-10c.13f",    0x20000, 0xc46479d7, BRF_ESS | BRF_PRG }, // 2 even
	{ "lw-14c.13g",    0x20000, 0x97670f4a, BRF_ESS | BRF_PRG }, // 3 odd
	{ "lw-07",         0x80000, 0xfd252a26, BRF_ESS | BRF_PRG }, // 4 both

 // graphics:
	{ "lw-02",         0x80000, 0x43e6c5c8, BRF_GRA },			 // 5
	{ "lw-09",         0x80000, 0x899cb4ad, BRF_GRA },
	{ "lw-06",         0x80000, 0x5b9edffc, BRF_GRA },
	{ "lw-13",         0x80000, 0x8e058ef5, BRF_GRA },
	{ "lw-01",         0x80000, 0x0318f298, BRF_GRA },			 // 9
	{ "lw-08",         0x80000, 0x25a8e43c, BRF_GRA },
	{ "lw-05",         0x80000, 0xe4552fd7, BRF_GRA },
	{ "lw-12",         0x80000, 0x8e6a832b, BRF_GRA },

  // z80 rom
	{ "lwu00",         0x10000, 0x59df2a63, BRF_GRA },			 // 13
  // samples
	{ "lw-03.14c",     0x20000, 0xce2159e7, BRF_GRA },
	{ "lw-04.13c",     0x20000, 0x39305536, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Lostwrld) STD_ROM_FN(Lostwrld)

struct BurnDriver BurnDrvCpsLostwrld = {
	"lostwrld", "forgottn", NULL, "1988",
	"Lost Worlds (Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1_GENERIC,
 NULL,LostwrldRomInfo,LostwrldRomName,DrvInputInfo, forgottnDIPInfo,
 DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
 &CpsRecalcPal,384,224,4,3
};
