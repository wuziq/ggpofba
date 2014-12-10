// Street Fighter II' CE/Turbo
// Some sf2yyc and kouryu information from El-Semi - thanks El

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin",			BIT_DIGITAL, CpsInp018+0, "p1 coin"},	// 0x00
  {"P1 Start",			BIT_DIGITAL, CpsInp018+4, "p1 start"},
  {"P1 Up",				BIT_DIGITAL, CpsInp001+3, "p1 up"},		// 0x02
  {"P1 Down",			BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left",			BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right",			BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Weak punch",		BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},	// 0x06
  {"P1 Medium punch",	BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Strong punch",	BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},
  {"P1 Weak kick",		BIT_DIGITAL, CpsInp177+0, "p1 fire 4"},
  {"P1 Medium kick",	BIT_DIGITAL, CpsInp177+1, "p1 fire 5"},
  {"P1 Strong kick",	BIT_DIGITAL, CpsInp177+2, "p1 fire 6"},
  {"P2 Coin",			BIT_DIGITAL, CpsInp018+1, "p2 coin"},	// 0x0C
  {"P2 Start",			BIT_DIGITAL, CpsInp018+5, "p2 start"},
  {"P2 Up",				BIT_DIGITAL, CpsInp000+3, "p2 up"},		// 0x0E
  {"P2 Down",			BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left",			BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right",			BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Weak punch",		BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},	// 0x12
  {"P2 Medium punch",	BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Strong Punch",	BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},
  {"P2 Weak kick",		BIT_DIGITAL, CpsInp177+4, "p2 fire 4"},
  {"P2 Medium kick",	BIT_DIGITAL, CpsInp177+5, "p2 fire 5"},
  {"P2 Strong kick",	BIT_DIGITAL, CpsInp177+6, "p2 fire 6"},
  {"Diagnostic",		BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Reset",				BIT_DIGITAL, &CpsReset,	  "reset"},
  {"Dip A",				BIT_DIPSWITCH, &Cpi01A,   "dip"},
  {"Dip B",				BIT_DIPSWITCH, &Cpi01C,   "dip"},
  {"Dip C",				BIT_DIPSWITCH, &Cpi01E,   "dip"},
};

STDINPUTINFO(Drv);

static struct BurnInputInfo Sf2yycInputList[]=
{
  {"P1 Coin",			BIT_DIGITAL, CpsInp019+0, "p1 coin"},	// 0x00
  {"P1 Start",			BIT_DIGITAL, CpsInp019+4, "p1 start"},
  {"P1 Up",				BIT_DIGITAL, CpsInp001+3, "p1 up"},		// 0x02
  {"P1 Down",			BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left",			BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right",			BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Weak punch",		BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},	// 0x06
  {"P1 Medium punch",	BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Strong punch",	BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},
  {"P1 Weak kick",		BIT_DIGITAL, CpsInp176+0, "p1 fire 4"},
  {"P1 Medium kick",	BIT_DIGITAL, CpsInp176+1, "p1 fire 5"},
  {"P1 Strong kick",	BIT_DIGITAL, CpsInp176+2, "p1 fire 6"},
  {"P2 Coin",			BIT_DIGITAL, CpsInp019+1, "p2 coin"},	// 0x0C
  {"P2 Start",			BIT_DIGITAL, CpsInp019+5, "p2 start"},
  {"P2 Up",				BIT_DIGITAL, CpsInp000+3, "p2 up"},		// 0x0E
  {"P2 Down",			BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left",			BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right",			BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Weak punch",		BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},	// 0x12
  {"P2 Medium punch",	BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Strong Punch",	BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},
  {"P2 Weak kick",		BIT_DIGITAL, CpsInp176+4, "p2 fire 4"},
  {"P2 Medium kick",	BIT_DIGITAL, CpsInp176+5, "p2 fire 5"},
  {"P2 Strong kick",	BIT_DIGITAL, CpsInp176+6, "p2 fire 6"},
  {"Diagnostic",		BIT_DIGITAL, CpsInp019+6, "diag"},
  {"Reset",				BIT_DIGITAL, &CpsReset,	  "reset"},
  {"Service",			BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip A",				BIT_DIPSWITCH, &Cpi01A,   "dip"},
  {"Dip B",				BIT_DIPSWITCH, &Cpi01C,   "dip"},
  {"Dip C",				BIT_DIPSWITCH, &Cpi01E,   "dip"},
};

STDINPUTINFO(Sf2yyc);

static struct BurnDIPInfo sf2ceDIPList[]=
{
	// Defaults
	{0x1a, 0xff, 0xff, 0x00, NULL                },
	{0x1b, 0xff, 0xff, 0x00, NULL                },
	{0x1c, 0xff, 0xff, 0x00, NULL                },

	// Dip A
	{0   , 0xfe, 0   , 8   , "A Side"                 },
	{0x1a, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x1a, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x1a, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x1a, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x1a, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x1a, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x1a, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x1a, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 8   , "B Side"                 },
	{0x1a, 0x01, 0x38, 0x38, "4 Coins 1 Credit"       },
	{0x1a, 0x01, 0x38, 0x30, "3 Coins 1 Credit"       },
	{0x1a, 0x01, 0x38, 0x28, "2 Coins 1 Credit"       },
	{0x1a, 0x01, 0x38, 0x00, "1 Coin 1 Credit"        },
	{0x1a, 0x01, 0x38, 0x08, "1 Coin 2 Credits"       },
	{0x1a, 0x01, 0x38, 0x10, "1 Coin 3 Credits"       },
	{0x1a, 0x01, 0x38, 0x18, "1 Coin 4 Credits"       },
	{0x1a, 0x01, 0x38, 0x20, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 2   , "Continue Coin"          },
	{0x1a, 0x01, 0x40, 0x00, "Off"                    },
	{0x1a, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1a, 0x01, 0x80, 0x00, "Off"                    },
//	{0x1a, 0x01, 0x80, 0x80, "On"                     },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Game Level"             },
	{0x1b, 0x01, 0x07, 0x00, "0"                 },
	{0x1b, 0x01, 0x07, 0x01, "1"                 },
	{0x1b, 0x01, 0x07, 0x02, "2"                 },
	{0x1b, 0x01, 0x07, 0x03, "3"              },
	{0x1b, 0x01, 0x07, 0x04, "4"            },
	{0x1b, 0x01, 0x07, 0x05, "5"            },
	{0x1b, 0x01, 0x07, 0x06, "6"            },
	{0x1b, 0x01, 0x07, 0x07, "7"         },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x08, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x08, 0x08, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//      {0x1b, 0x01, 0x10, 0x00, "Off"                    },
//      {0x1b, 0x01, 0x10, 0x10, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x20, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x20, 0x20, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//      {0x1b, 0x01, 0x40, 0x00, "Off"                    },
//      {0x1b, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//      {0x1b, 0x01, 0x80, 0x00, "Off"                    },
//      {0x1b, 0x01, 0x80, 0x80, "On"                     },

	// Dip C
//	{0   , 0xfe, 0   , 4   , "Unknown"                },
//      {0x1c, 0x01, 0x03, 0x00, "1"                      },
//      {0x1c, 0x01, 0x03, 0x01, "2"                      },
//      {0x1c, 0x01, 0x03, 0x02, "3"                      },
//      {0x1c, 0x01, 0x03, 0x03, "4"                      },

	{0   , 0xfe, 0   , 2   , "Free Play"              },
        {0x1c, 0x01, 0x04, 0x00, "Off"                    },
        {0x1c, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Stop"                   },
        {0x1c, 0x01, 0x08, 0x00, "Off"                    },
        {0x1c, 0x01, 0x08, 0x08, "On"                     },

	{0   , 0xfe, 0   , 2   , "Flip"                   },
        {0x1c, 0x01, 0x10, 0x00, "Off"                    },
        {0x1c, 0x01, 0x10, 0x10, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sound"             },
        {0x1c, 0x01, 0x20, 0x00, "Off"                    },
        {0x1c, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 2   , "Continue"               },
        {0x1c, 0x01, 0x40, 0x00, "Off"                    },
        {0x1c, 0x01, 0x40, 0x40, "On"                     },
};

STDDIPINFO(sf2ce);

static struct BurnDIPInfo sf2cejDIPList[]=
{
	// Defaults
	{0x1a, 0xff, 0xff, 0x00, NULL                },
	{0x1b, 0xff, 0xff, 0x00, NULL                },
	{0x1c, 0xff, 0xff, 0x00, NULL                },

	// Dip A
	{0   , 0xfe, 0   , 8   , "A Side"                 },
	{0x1a, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x1a, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x1a, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x1a, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x1a, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x1a, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x1a, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x1a, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 8   , "B Side"                 },
	{0x1a, 0x01, 0x38, 0x38, "4 Coins 1 Credit"       },
	{0x1a, 0x01, 0x38, 0x30, "3 Coins 1 Credit"       },
	{0x1a, 0x01, 0x38, 0x28, "2 Coins 1 Credit"       },
	{0x1a, 0x01, 0x38, 0x00, "1 Coin 1 Credit"        },
	{0x1a, 0x01, 0x38, 0x08, "1 Coin 2 Credits"       },
	{0x1a, 0x01, 0x38, 0x10, "1 Coin 3 Credits"       },
	{0x1a, 0x01, 0x38, 0x18, "1 Coin 4 Credits"       },
	{0x1a, 0x01, 0x38, 0x20, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 2   , "Continue Coin"          },
	{0x1a, 0x01, 0x40, 0x00, "Off"                    },
	{0x1a, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1a, 0x01, 0x80, 0x00, "Off"                    },
//	{0x1a, 0x01, 0x80, 0x80, "On"                     },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Game Level"             },
	{0x1b, 0x01, 0x07, 0x00, "0"                 },
	{0x1b, 0x01, 0x07, 0x01, "1"                 },
	{0x1b, 0x01, 0x07, 0x02, "2"                 },
	{0x1b, 0x01, 0x07, 0x03, "3"              },
	{0x1b, 0x01, 0x07, 0x04, "4"            },
	{0x1b, 0x01, 0x07, 0x05, "5"            },
	{0x1b, 0x01, 0x07, 0x06, "6"            },
	{0x1b, 0x01, 0x07, 0x07, "7"         },

	{0   , 0xfe, 0   , 2   , "2 Players Game"         },
	{0x1b, 0x01, 0x08, 0x00, "1 Credit/No Continue"   },
	{0x1b, 0x01, 0x08, 0x08, "2 Credits/Winner Continue"},

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//      {0x1b, 0x01, 0x10, 0x00, "Off"                    },
//      {0x1b, 0x01, 0x10, 0x10, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x20, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x20, 0x20, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//      {0x1b, 0x01, 0x40, 0x00, "Off"                    },
//      {0x1b, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//      {0x1b, 0x01, 0x80, 0x00, "Off"                    },
//      {0x1b, 0x01, 0x80, 0x80, "On"                     },

	// Dip C
//	{0   , 0xfe, 0   , 4   , "Unknown"                },
//      {0x1c, 0x01, 0x03, 0x00, "1"                      },
//      {0x1c, 0x01, 0x03, 0x01, "2"                      },
//      {0x1c, 0x01, 0x03, 0x02, "3"                      },
//      {0x1c, 0x01, 0x03, 0x03, "4"                      },

	{0   , 0xfe, 0   , 2   , "Free Play"              },
        {0x1c, 0x01, 0x04, 0x00, "Off"                    },
        {0x1c, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Stop"                   },
        {0x1c, 0x01, 0x08, 0x00, "Off"                    },
        {0x1c, 0x01, 0x08, 0x08, "On"                     },

	{0   , 0xfe, 0   , 2   , "Flip"                   },
        {0x1c, 0x01, 0x10, 0x00, "Off"                    },
        {0x1c, 0x01, 0x10, 0x10, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sound"             },
        {0x1c, 0x01, 0x20, 0x00, "Off"                    },
        {0x1c, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 2   , "Continue"               },
        {0x1c, 0x01, 0x40, 0x00, "Off"                    },
        {0x1c, 0x01, 0x40, 0x40, "On"                     },
};

STDDIPINFO(sf2cej);


static int DrvExit()
{

	CpsRunExit();
	CpsExit();
	nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
	Cps=0;
	Sf2Hack=0;
	return 0;
}

//==========================================
//Street Fighter II' C.E./Turbo Regular Init
//==========================================

static int DrvInit()
{
	int nRet=0; int i=0;
	Cps=1;
	nCpsRomLen =3*0x080000;
	nCpsGfxLen =3*0x200000;
	nCpsZRomLen=  0x010000;
	nCpsAdLen  =2*0x020000;

	nCPS68KClockspeed = 7000000;
	nRet=CpsInit(); if (nRet!=0) return 1;

	// Load program roms (they are already byteswapped)
	for (i=0;i<3;i++)
		{ nRet=BurnLoadRom(CpsRom+0x080000*i,0+i,1); if (nRet!=0) return 1; }

	// Load up and interleve each set of 4 roms to make the 16x16 tiles
	CpsLoadTiles(CpsGfx+0x000000,3+0*4);
	CpsLoadTiles(CpsGfx+0x200000,3+1*4);
	CpsLoadTiles(CpsGfx+0x400000,3+2*4);

	nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

	MaskAddr[0]=0x68;
	MaskAddr[1]=0x6a;
	MaskAddr[2]=0x6c;
	MaskAddr[3]=0x6e;

	// Load Z80 Rom
	nRet=BurnLoadRom(CpsZRom,15,1);

	// Load ADPCM data
	nRet=BurnLoadRom(CpsAd        ,16,1);
	nRet=BurnLoadRom(CpsAd+0x20000,17,1);

	// Start of Board ID improvments by KEV. 0x48,0x0407
	CpsBID[0]=0x48;
	CpsBID[1]=0x04;
	CpsBID[2]=0x07;

	nRet=CpsRunInit();
	if (nRet!=0) return 1;

	// Ready to go
	return 0;
}

//==============================================================
//Street Fighter II' - champion edition (Accelerator Pt.II) Init
//==============================================================

static int Sf2accp2Init()
{
	int nRet=0; int i=0;
	Cps=1;
	nCpsRomLen =3*0x080000;
	nCpsGfxLen =3*0x200000;
	nCpsZRomLen=  0x010000;
	nCpsAdLen  =2*0x020000;

	nCPS68KClockspeed = 7000000;
	nRet=CpsInit(); if (nRet!=0) return 1;

	// Load program roms (they are already byteswapped)
	for (i=0;i<3;i++)
		{ nRet=BurnLoadRom(CpsRom+0x080000*i,0+i,1); if (nRet!=0) return 1; }

	// patch out the "odd branch"
	CpsRom[0x11755]=0x4e;
	CpsRom[0x11756]=0x71;

	// Load up and interleve each set of 4 roms to make the 16x16 tiles
	CpsLoadTiles(CpsGfx+0x000000,3+0*4);
	CpsLoadTiles(CpsGfx+0x200000,3+1*4);
	CpsLoadTiles(CpsGfx+0x400000,3+2*4);

	nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

	MaskAddr[0]=0x68;
	MaskAddr[1]=0x6a;
	MaskAddr[2]=0x6c;
	MaskAddr[3]=0x6e;

	// Load Z80 Rom
	nRet=BurnLoadRom(CpsZRom,15,1);

	// Load ADPCM data
	nRet=BurnLoadRom(CpsAd        ,16,1);
	nRet=BurnLoadRom(CpsAd+0x20000,17,1);

	// Start of Board ID improvments by KEV. 0x48,0x0407
	CpsBID[0]=0x48;
	CpsBID[1]=0x04;
	CpsBID[2]=0x07;

	nRet=CpsRunInit();
	if (nRet!=0) return 1;

	// Ready to go
	return 0;
}

//==========================================================
//Street Fighter II' - champion edition (Rainbow Set 1) Init
//==========================================================

static int Sf2rbInit()
{
	int nRet=0; int i=0;
	Cps=1;
	nCpsRomLen =3*0x080000;
	nCpsGfxLen =3*0x200000;
	nCpsZRomLen=  0x010000;
	nCpsAdLen  =2*0x020000;

	nCPS68KClockspeed = 7000000;
	nRet=CpsInit(); if (nRet!=0) return 1;

	// Load program roms (they are already byteswapped)
	for (i=0;i<3;i++)
		{ nRet=BurnLoadRom(CpsRom+0x080000*i,0+i,1); if (nRet!=0) return 1; }

	// patch the copy protection
	BurnByteswap(CpsRom,0x080000*2);
	CpsRom[0xe5465]=0x60;
	CpsRom[0xe5464]=0x12;

	// Load up and interleve each set of 4 roms to make the 16x16 tiles
	CpsLoadTiles(CpsGfx+0x000000,3+0*4);
	CpsLoadTiles(CpsGfx+0x200000,3+1*4);
	CpsLoadTiles(CpsGfx+0x400000,3+2*4);

	nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

	MaskAddr[0]=0x68;
	MaskAddr[1]=0x6a;
	MaskAddr[2]=0x6c;
	MaskAddr[3]=0x6e;

	// Load Z80 Rom
	nRet=BurnLoadRom(CpsZRom,15,1);

	// Load ADPCM data
	nRet=BurnLoadRom(CpsAd        ,16,1);
	nRet=BurnLoadRom(CpsAd+0x20000,17,1);

	// Start of Board ID improvments by KEV. 0x48,0x0407
	CpsBID[0]=0x48;
	CpsBID[1]=0x04;
	CpsBID[2]=0x07;

	nRet=CpsRunInit();
	if (nRet!=0) return 1;

	// Ready to go
	return 0;
}

//==========================================================
//Street Fighter II' - champion edition (Rainbow Set 2) Init
//==========================================================

static int Sf2rb2Init()
{
	int nRet=0; int i=0;
	Cps=1;
	nCpsRomLen =8*0x20000+0x80000;
	nCpsGfxLen =3*0x200000;
	nCpsZRomLen=  0x010000;
	nCpsAdLen  =2*0x020000;

	nCPS68KClockspeed = 7000000;
	nRet=CpsInit(); if (nRet!=0) return 1;

	// Load program roms
	nRet=BurnLoadRom(CpsRom+0x000000,0,2); if (nRet!=0) return 1;//ROM_LOAD16_BYTE
	nRet=BurnLoadRom(CpsRom+0x000001,1,2); if (nRet!=0) return 1;//ROM_LOAD16_BYTE
	nRet=BurnLoadRom(CpsRom+0x040000,2,2); if (nRet!=0) return 1;//ROM_LOAD16_BYTE
	nRet=BurnLoadRom(CpsRom+0x040001,3,2); if (nRet!=0) return 1;//ROM_LOAD16_BYTE
	nRet=BurnLoadRom(CpsRom+0x080000,4,2); if (nRet!=0) return 1;//ROM_LOAD16_BYTE
	nRet=BurnLoadRom(CpsRom+0x080001,5,2); if (nRet!=0) return 1;//ROM_LOAD16_BYTE
	nRet=BurnLoadRom(CpsRom+0x0c0000,6,2); if (nRet!=0) return 1;//ROM_LOAD16_BYTE
	nRet=BurnLoadRom(CpsRom+0x0c0001,7,2); if (nRet!=0) return 1;//ROM_LOAD16_BYTE
	nRet=BurnLoadRom(CpsRom+0x100000,8,1); if (nRet!=0) return 1;//ROM_LOAD16_WORD_SWAP

	// patch the copy protection
	BurnByteswap(CpsRom,0x080000*2);
	CpsRom[0xe5333]=0x60;
	CpsRom[0xe5332]=0x14;

	// Load up and interleve each set of 4 roms to make the 16x16 tiles
	for (i=0;i<3;i++) CpsLoadTiles(CpsGfx+i*0x200000,9+i*4);

	nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

	MaskAddr[0]=0x68;
	MaskAddr[1]=0x6a;
	MaskAddr[2]=0x6c;
	MaskAddr[3]=0x6e;

	// Load Z80 Rom
	nRet=BurnLoadRom(CpsZRom,21,1);

	// Load ADPCM data
	nRet=BurnLoadRom(CpsAd        ,22,1);
	nRet=BurnLoadRom(CpsAd+0x20000,23,1);

	// Start of Board ID improvments by KEV. 0x48,0x0407
	CpsBID[0]=0x48;
	CpsBID[1]=0x04;
	CpsBID[2]=0x07;

	nRet=CpsRunInit();
	if (nRet!=0) return 1;

	// Ready to go
	return 0;
}

//==================================
//Street Fighter II' C.E. (YYC) Init
//==================================

static int Sf2yycInit()
{
	int nRet=0;
	Cps=1; Sf2Hack=1;
	nCpsRomLen =2*0x080000 + 4*0x020000;
	nCpsGfxLen =3*0x200000;
	nCpsZRomLen=  0x010000;
	nCpsAdLen  =2*0x020000;

	nCPS68KClockspeed = 7000000;
	nRet=CpsInit(); if (nRet!=0) return 1;

	// Load program roms
	nRet=BurnLoadRom(CpsRom + 0x000001, 0, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x000000, 1, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x100001, 2, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x100000, 3, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x140001, 2, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x140000, 3, 2); if (nRet!=0) return 1;

        // Patch invalid opcode (protection?)
        CpsRom[0xe55cb]=0x4e;
        CpsRom[0xe55ca]=0x71;
        CpsRom[0xe55cd]=0x4e;
        CpsRom[0xe55cc]=0x71;
        CpsRom[0xe55cf]=0x4e;
        CpsRom[0xe55ce]=0x71;
        CpsRom[0xe55d1]=0x4e;
        CpsRom[0xe55d0]=0x71;
        CpsRom[0xe55d7]=0x4e;
        CpsRom[0xe55d6]=0x71;
        CpsRom[0xe55d9]=0x4e;
        CpsRom[0xe55d8]=0x71;
        CpsRom[0xe55db]=0x4e;
        CpsRom[0xe55da]=0x71;
        CpsRom[0xe55df]=0x4e;
        CpsRom[0xe55de]=0x71;
        CpsRom[0xe55e3]=0x4e;
        CpsRom[0xe55e2]=0x71;
        CpsRom[0xe55e5]=0x4e;
        CpsRom[0xe55e4]=0x71;
        CpsRom[0xe55e7]=0x4e;
        CpsRom[0xe55e6]=0x71;
        CpsRom[0xe55e9]=0x4e;
        CpsRom[0xe55e8]=0x71;
        CpsRom[0xe55bf]=0x4e;
        CpsRom[0xe55be]=0x71;
        CpsRom[0xe55d1]=0x4e;
        CpsRom[0xe55d0]=0x71;
        CpsRom[0xe55d3]=0x4e;
        CpsRom[0xe55d2]=0x71;
        CpsRom[0xe55d5]=0x4e;
        CpsRom[0xe55d4]=0x71;

	// Load up and interleve each set of 4 roms to make the 16x16 tiles
	CpsLoadTiles(CpsGfx+0x000000, 4+0*4);
	CpsLoadTiles(CpsGfx+0x200000, 4+1*4);
	CpsLoadTiles(CpsGfx+0x400000, 4+2*4);

        nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

        nCpsLcReg=0x66;
	CpsLayEn[1]=0x02;
	CpsLayEn[2]=0x04;
	CpsLayEn[3]=0x08;

	CpsMProt[0]=0x40;
	CpsMProt[1]=0x42;
	CpsMProt[2]=0x44;
	CpsMProt[3]=0x46;

	CpsBID[0]=0x00;
	CpsBID[1]=0x00;
	CpsBID[2]=0x00;

	MaskAddr[0]=0x68;
	MaskAddr[1]=0x6a;
	MaskAddr[2]=0x6c;
	MaskAddr[3]=0x6e;

	// Load Z80 Rom
	nRet=BurnLoadRom(CpsZRom      , 16, 1);

	// Load ADPCM data
	nRet=BurnLoadRom(CpsAd        , 17, 1);
	nRet=BurnLoadRom(CpsAd+0x20000, 18, 1);

	nRet=CpsRunInit();
	if (nRet!=0) return 1;

	// Ready to go
	return 0;
}

//=====================================
//Street Fighter II' C.E. (Kouryu) Init
//=====================================

static int KouryuInit()
{
	int nRet=0;
	Cps=1; Sf2Hack=1;
        nCpsRomLen =2*0x080000 + 2*0x020000;
	nCpsGfxLen =3*0x200000;
	nCpsZRomLen=  0x010000;
	nCpsAdLen  =2*0x020000;

	nCPS68KClockspeed = 7000000;
	nRet=CpsInit(); if (nRet!=0) return 1;

	// Load program roms
	nRet=BurnLoadRom(CpsRom + 0x000000, 0, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x000001, 1, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x100000, 2, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x100001, 3, 2); if (nRet!=0) return 1;

	BurnByteswap(CpsRom, 2*0x080000 + 2*0x020000);

	// Load up and interleve each set of 4 roms to make the 16x16 tiles
	CpsLoadTiles(CpsGfx+0x000000, 4+0*4);
	CpsLoadTiles(CpsGfx+0x200000, 4+1*4);
	CpsLoadTiles(CpsGfx+0x400000, 4+2*4);

	nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

	nCpsLcReg=0x66;
	CpsLayEn[1]=0x02;
	CpsLayEn[2]=0x04;
	CpsLayEn[3]=0x08;

	CpsMProt[0]=0x40;
	CpsMProt[1]=0x42;
	CpsMProt[2]=0x44;
	CpsMProt[3]=0x46;

	CpsBID[0]=0x00;
	CpsBID[1]=0x00;
	CpsBID[2]=0x00;

	MaskAddr[0]=0x68;
	MaskAddr[1]=0x6a;
	MaskAddr[2]=0x6c;
	MaskAddr[3]=0x6e;

	// Load Z80 Rom
	nRet=BurnLoadRom(CpsZRom      , 16, 1);

	// Load ADPCM data
	nRet=BurnLoadRom(CpsAd        , 17, 1);
	nRet=BurnLoadRom(CpsAd+0x20000, 18, 1);

	nRet=CpsRunInit();
	if (nRet!=0) return 1;

	// Ready to go
	return 0;
}


//=============================================
//Street Fighter II' - champion edition (World)
//=============================================


static struct BurnRomInfo Sf2ceRomDesc[] = {
	{ "sf2ce.23",      0x80000, 0x3f846b74, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2ce.22",      0x80000, 0x99f1cca4, BRF_ESS | BRF_PRG }, //  1
	{ "s92_21a.bin",   0x80000, 0x925a7877, BRF_ESS | BRF_PRG }, //  2

	{ "s92_01.bin",    0x80000, 0x03b0d852, BRF_GRA },
	{ "s92_02.bin",    0x80000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",    0x80000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",    0x80000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",    0x80000, 0xba8a2761, BRF_GRA },
	{ "s92_06.bin",    0x80000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",    0x80000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",    0x80000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",    0x80000, 0x960687d5, BRF_GRA },
	{ "s92_11.bin",    0x80000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",    0x80000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",    0x80000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",    0x10000, 0x08f6b60e, BRF_SND },

	{ "s92_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "s92_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2ce) STD_ROM_FN(Sf2ce)

struct BurnDriver BurnDrvCpsSf2ce = {
	"sf2ce", NULL, NULL, "1992",
	"Street Fighter II' - champion edition (street fighter 2' 920313 etc)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2ceRomInfo,Sf2ceRomName,DrvInputInfo, sf2ceDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=============================================
//Street Fighter II' - champion edition (Japan)
//=============================================


static struct BurnRomInfo Sf2cejRomDesc[] = {
	{ "s92j_23b.bin",  0x80000, 0x140876c5, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "s92j_22b.bin",  0x80000, 0x2fbb3bfe, BRF_ESS | BRF_PRG }, //  1
	{ "s92_21a.bin",   0x80000, 0x925a7877, BRF_ESS | BRF_PRG }, //  2

	{ "s92_01.bin",    0x80000, 0x03b0d852, BRF_GRA },
	{ "s92_02.bin",    0x80000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",    0x80000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",    0x80000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",    0x80000, 0xba8a2761, BRF_GRA },
	{ "s92_06.bin",    0x80000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",    0x80000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",    0x80000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",    0x80000, 0x960687d5, BRF_GRA },
	{ "s92_11.bin",    0x80000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",    0x80000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",    0x80000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",    0x10000, 0x08f6b60e, BRF_SND },

	{ "s92_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "s92_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2cej) STD_ROM_FN(Sf2cej)

struct BurnDriver BurnDrvCpsSf2cej = {
	"sf2cej", "sf2ce", NULL, "1992",
	"Street Fighter II' - champion edition (street fighter 2' 920513 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2cejRomInfo,Sf2cejRomName,DrvInputInfo, sf2cejDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================================================
//Street Fighter II' - champion edition (USA Rev. A)
//==================================================


static struct BurnRomInfo Sf2ceuaRomDesc[] = {
	{ "s92u-23a",      0x80000, 0xac44415b, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2ce.22",      0x80000, 0x99f1cca4, BRF_ESS | BRF_PRG }, //  1
	{ "s92_21a.bin",   0x80000, 0x925a7877, BRF_ESS | BRF_PRG }, //  2

	{ "s92_01.bin",    0x80000, 0x03b0d852, BRF_GRA },
	{ "s92_02.bin",    0x80000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",    0x80000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",    0x80000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",    0x80000, 0xba8a2761, BRF_GRA },
	{ "s92_06.bin",    0x80000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",    0x80000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",    0x80000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",    0x80000, 0x960687d5, BRF_GRA },
	{ "s92_11.bin",    0x80000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",    0x80000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",    0x80000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",    0x10000, 0x08f6b60e, BRF_SND },

	{ "s92_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "s92_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2ceua) STD_ROM_FN(Sf2ceua)

struct BurnDriver BurnDrvCpsSf2ceua = {
	"sf2ceua", "sf2ce", NULL, "1992",
	"Street Fighter II' - champion edition (street fighter 2' 920313 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2ceuaRomInfo,Sf2ceuaRomName,DrvInputInfo, sf2ceDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================================================
//Street Fighter II' - champion edition (USA Rev. B)
//==================================================


static struct BurnRomInfo Sf2ceubRomDesc[] = {
	{ "s92-23b",       0x80000, 0x996a3015, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "s92-22b",       0x80000, 0x2bbe15ed, BRF_ESS | BRF_PRG }, //  1
	{ "s92-21b",       0x80000, 0xb383cb1c, BRF_ESS | BRF_PRG }, //  2

	{ "s92_01.bin",    0x80000, 0x03b0d852, BRF_GRA },
	{ "s92_02.bin",    0x80000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",    0x80000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",    0x80000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",    0x80000, 0xba8a2761, BRF_GRA },
	{ "s92_06.bin",    0x80000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",    0x80000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",    0x80000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",    0x80000, 0x960687d5, BRF_GRA },
	{ "s92_11.bin",    0x80000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",    0x80000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",    0x80000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",    0x10000, 0x08f6b60e, BRF_SND },

	{ "s92_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "s92_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2ceub) STD_ROM_FN(Sf2ceub)

struct BurnDriver BurnDrvCpsSf2ceub = {
	"sf2ceub", "sf2ce", NULL, "1992",
	"Street Fighter II' - champion edition (street fighter 2' 920513 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2ceubRomInfo,Sf2ceubRomName,DrvInputInfo, sf2ceDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================================================
//Street Fighter II' - champion edition (USA Rev. C)
//==================================================


static struct BurnRomInfo Sf2ceucRomDesc[] = {
	{ "s92-23c",       0x80000, 0x0a8b6aa2, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "s92-22c",       0x80000, 0x5fd8630b, BRF_ESS | BRF_PRG }, //  1
	{ "s92-21b",       0x80000, 0xb383cb1c, BRF_ESS | BRF_PRG }, //  2

	{ "s92_01.bin",    0x80000, 0x03b0d852, BRF_GRA },
	{ "s92_02.bin",    0x80000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",    0x80000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",    0x80000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",    0x80000, 0xba8a2761, BRF_GRA },
	{ "s92_06.bin",    0x80000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",    0x80000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",    0x80000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",    0x80000, 0x960687d5, BRF_GRA },
	{ "s92_11.bin",    0x80000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",    0x80000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",    0x80000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",    0x10000, 0x08f6b60e, BRF_SND },

	{ "s92_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "s92_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2ceuc) STD_ROM_FN(Sf2ceuc)

struct BurnDriver BurnDrvCpsSf2ceuc = {
	"sf2ceuc", "sf2ce", NULL, "1992",
	"Street Fighter II' - champion edition (street fighter 2' 920803 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2ceucRomInfo,Sf2ceucRomName,DrvInputInfo, sf2ceDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=========================================================
//Street Fighter II' - champion edition (Accelerator Pt.II)
//=========================================================


static struct BurnRomInfo Sf2accp2RomDesc[] = {
	{ "sf2ca-23.bin",  0x80000, 0x36c3ba2f, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2ca-22.bin",  0x80000, 0x0550453d, BRF_ESS | BRF_PRG }, //  1
	{ "sf2ca-21.bin",  0x40000, 0x4c1c43ba, BRF_ESS | BRF_PRG }, //  2

	{ "s92_01.bin",    0x80000, 0x03b0d852, BRF_GRA },
	{ "s92_02.bin",    0x80000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",    0x80000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",    0x80000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",    0x80000, 0xba8a2761, BRF_GRA },
	{ "s92_06.bin",    0x80000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",    0x80000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",    0x80000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",    0x80000, 0x960687d5, BRF_GRA },
	{ "s92_11.bin",    0x80000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",    0x80000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",    0x80000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",    0x10000, 0x08f6b60e, BRF_SND },

	{ "s92_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "s92_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2accp2) STD_ROM_FN(Sf2accp2)

struct BurnDriver BurnDrvCpsSf2accp2 = {
	"sf2accp2", "sf2ce", NULL, "1992",
	"Street Fighter II' - champion edition (Hack - Accelerator Pt.II)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2accp2RomInfo,Sf2accp2RomName,DrvInputInfo, sf2ceDIPInfo,
	Sf2accp2Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=====================================================
//Street Fighter II' - champion edition (Rainbow Set 1)
//=====================================================



static struct BurnRomInfo Sf2rbRomDesc[] = {
	{ "sf2d__23.rom",  0x80000, 0x450532b0, BRF_ESS | BRF_PRG },
	{ "sf2d__22.rom",  0x80000, 0xfe9d9cf5, BRF_ESS | BRF_PRG },
	{ "s92_21a.bin",   0x80000, 0x925a7877, BRF_ESS | BRF_PRG },

	{ "s92_01.bin",    0x80000, 0x03b0d852, BRF_GRA },
	{ "s92_02.bin",    0x80000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",    0x80000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",    0x80000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",    0x80000, 0xba8a2761, BRF_GRA },
	{ "s92_06.bin",    0x80000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",    0x80000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",    0x80000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",    0x80000, 0x960687d5, BRF_GRA },
	{ "s92_11.bin",    0x80000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",    0x80000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",    0x80000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",    0x10000, 0x08f6b60e, BRF_SND },

	{ "s92_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "s92_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2rb) STD_ROM_FN(Sf2rb)

struct BurnDriver BurnDrvCpsSf2rb = {
	"sf2rb", "sf2ce", NULL, "1992",
	"Street Fighter II' - champion edition (Hack - Rainbow set 1)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2rbRomInfo,Sf2rbRomName,DrvInputInfo, sf2ceDIPInfo,
	Sf2rbInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=====================================================
//Street Fighter II' - champion edition (Rainbow Set 2)
//=====================================================


static struct BurnRomInfo Sf2rb2RomDesc[] = {
	{ "27.bin",        0x20000, 0x40296ecd, BRF_ESS | BRF_PRG },
	{ "31.bin",        0x20000, 0x87954a41, BRF_ESS | BRF_PRG },
	{ "26.bin",        0x20000, 0xa6974195, BRF_ESS | BRF_PRG },
	{ "30.bin",        0x20000, 0x8141fe32, BRF_ESS | BRF_PRG },
	{ "25.bin",        0x20000, 0x9ef8f772, BRF_ESS | BRF_PRG },
	{ "29.bin",        0x20000, 0x7d9c479c, BRF_ESS | BRF_PRG },
	{ "24.bin",        0x20000, 0x93579684, BRF_ESS | BRF_PRG },
	{ "28.bin",        0x20000, 0xff728865, BRF_ESS | BRF_PRG },
	{ "s92_21a.bin",   0x80000, 0x925a7877, BRF_ESS | BRF_PRG },

	{ "s92_01.bin",    0x80000, 0x03b0d852, BRF_GRA },
	{ "s92_02.bin",    0x80000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",    0x80000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",    0x80000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",    0x80000, 0xba8a2761, BRF_GRA },
	{ "s92_06.bin",    0x80000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",    0x80000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",    0x80000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",    0x80000, 0x960687d5, BRF_GRA },
	{ "s92_11.bin",    0x80000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",    0x80000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",    0x80000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",    0x10000, 0x08f6b60e, BRF_SND },

	{ "s92_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "s92_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2rb2) STD_ROM_FN(Sf2rb2)

struct BurnDriver BurnDrvCpsSf2rb2 = {
	"sf2rb2", "sf2ce", NULL, "1992",
	"Street Fighter II' - champion edition (Hack - Rainbow set 2)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2rb2RomInfo,Sf2rb2RomName,DrvInputInfo, sf2ceDIPInfo,
	Sf2rb2Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//================================================
//Street Fighter II' - champion edition (Red Wave)
//================================================


static struct BurnRomInfo Sf2redRomDesc[] = {
	{ "sf2red.23",     0x80000, 0x40276abb, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2red.22",     0x80000, 0x18daf387, BRF_ESS | BRF_PRG }, //  1
	{ "sf2red.21",     0x80000, 0x52c486bb, BRF_ESS | BRF_PRG }, //  2

	{ "s92_01.bin",    0x80000, 0x03b0d852, BRF_GRA },
	{ "s92_02.bin",    0x80000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",    0x80000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",    0x80000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",    0x80000, 0xba8a2761, BRF_GRA },
	{ "s92_06.bin",    0x80000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",    0x80000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",    0x80000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",    0x80000, 0x960687d5, BRF_GRA },
	{ "s92_11.bin",    0x80000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",    0x80000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",    0x80000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",    0x10000, 0x08f6b60e, BRF_SND },

	{ "s92_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "s92_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2red) STD_ROM_FN(Sf2red)

struct BurnDriver BurnDrvCpsSf2red = {
	"sf2red", "sf2ce", NULL, "1992",
	"Street Fighter II' - champion edition (Hack - Red Wave)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2redRomInfo,Sf2redRomName,DrvInputInfo, sf2ceDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//============================================
//Street Fighter II' - champion edition (V004)
//============================================


static struct BurnRomInfo Sf2v004RomDesc[] = {
	{ "sf2v004.23",    0x80000, 0x52d19f2c, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2v004.22",    0x80000, 0x4b26fde7, BRF_ESS | BRF_PRG }, //  1
	{ "sf2red.21",     0x80000, 0x52c486bb, BRF_ESS | BRF_PRG }, //  2

	{ "s92_01.bin",    0x80000, 0x03b0d852, BRF_GRA },
	{ "s92_02.bin",    0x80000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",    0x80000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",    0x80000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",    0x80000, 0xba8a2761, BRF_GRA },
	{ "s92_06.bin",    0x80000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",    0x80000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",    0x80000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",    0x80000, 0x960687d5, BRF_GRA },
	{ "s92_11.bin",    0x80000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",    0x80000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",    0x80000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",    0x10000, 0x08f6b60e, BRF_SND },

	{ "s92_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "s92_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2v004) STD_ROM_FN(Sf2v004)

struct BurnDriver BurnDrvCpsSf2v004 = {
	"sf2v004", "sf2ce", NULL, "1992",
	"Street Fighter II' - champion edition (Hack - V004)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2v004RomInfo,Sf2v004RomName,DrvInputInfo, sf2ceDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=========================================
//Street Fighter II' - hyper fighting (USA)
//=========================================

static struct BurnRomInfo Sf2hfRomDesc[] = {
	{ "s92e_23a.bin",  0x80000, 0x2DD72514, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2_22.bin",    0x80000, 0xaea6e035, BRF_ESS | BRF_PRG }, //  1
	{ "sf2_21.bin",    0x80000, 0xfd200288, BRF_ESS | BRF_PRG }, //  2

	{ "s92_01.bin",    0x80000, 0x03b0d852, BRF_GRA },
	{ "s92_02.bin",    0x80000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",    0x80000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",    0x80000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",    0x80000, 0xba8a2761, BRF_GRA },
	{ "s92_06.bin",    0x80000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",    0x80000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",    0x80000, 0xbefc47df, BRF_GRA },

	{ "s2t_10.bin",    0x80000, 0x3c042686, BRF_GRA },
	{ "s2t_11.bin",    0x80000, 0x8b7e7183, BRF_GRA },
	{ "s2t_12.bin",    0x80000, 0x293c888c, BRF_GRA },
	{ "s2t_13.bin",    0x80000, 0x842b35a4, BRF_GRA },

	{ "s92_09.bin",    0x10000, 0x08f6b60e, BRF_SND },

	{ "s92_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "s92_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


STD_ROM_PICK(Sf2hf) STD_ROM_FN(Sf2hf)

struct BurnDriver BurnDrvCpsSf2hf = {
	"sf2hf", "sf2ce", NULL, "1992",
	"Street Fighter II' - hyper fighting (street fighter 2' T 921209 ETC)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2hfRomInfo,Sf2hfRomName,DrvInputInfo, sf2ceDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

static struct BurnRomInfo Sf2tRomDesc[] = {
	{ "sf2.23",        0x80000, 0x89a1fc38, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2_22.bin",    0x80000, 0xaea6e035, BRF_ESS | BRF_PRG }, //  1
	{ "sf2_21.bin",    0x80000, 0xfd200288, BRF_ESS | BRF_PRG }, //  2

	{ "s92_01.bin",    0x80000, 0x03b0d852, BRF_GRA },
	{ "s92_02.bin",    0x80000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",    0x80000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",    0x80000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",    0x80000, 0xba8a2761, BRF_GRA },
	{ "s92_06.bin",    0x80000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",    0x80000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",    0x80000, 0xbefc47df, BRF_GRA },

	{ "s2t_10.bin",    0x80000, 0x3c042686, BRF_GRA },
	{ "s2t_11.bin",    0x80000, 0x8b7e7183, BRF_GRA },
	{ "s2t_12.bin",    0x80000, 0x293c888c, BRF_GRA },
	{ "s2t_13.bin",    0x80000, 0x842b35a4, BRF_GRA },

	{ "s92_09.bin",    0x10000, 0x08f6b60e, BRF_SND },

	{ "s92_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "s92_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


STD_ROM_PICK(Sf2t) STD_ROM_FN(Sf2t)

struct BurnDriver BurnDrvCpsSf2t = {
	"sf2t", "sf2hf", NULL, "1992",
	"Street Fighter II' - hyper fighting (street fighter 2' T 921209 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2tRomInfo,Sf2tRomName,DrvInputInfo, sf2ceDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=================================================
//Street Fighter II' Turbo - hyper fighting (Japan)
//=================================================


static struct BurnRomInfo Sf2tjRomDesc[] = {
	{ "s2tj_23.bin",   0x80000, 0xea73b4dc, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "s2t_22.bin",    0x80000, 0xaea6e035, BRF_ESS | BRF_PRG }, //  1
	{ "s2t_21.bin",    0x80000, 0xfd200288, BRF_ESS | BRF_PRG }, //  2

	{ "s92_01.bin",    0x80000, 0x03b0d852, BRF_GRA },
	{ "s92_02.bin",    0x80000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",    0x80000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",    0x80000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",    0x80000, 0xba8a2761, BRF_GRA },
	{ "s92_06.bin",    0x80000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",    0x80000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",    0x80000, 0xbefc47df, BRF_GRA },

	{ "s2t_10.bin",    0x80000, 0x3c042686, BRF_GRA },
	{ "s2t_11.bin",    0x80000, 0x8b7e7183, BRF_GRA },
	{ "s2t_12.bin",    0x80000, 0x293c888c, BRF_GRA },
	{ "s2t_13.bin",    0x80000, 0x842b35a4, BRF_GRA },

	{ "s92_09.bin",    0x10000, 0x08f6b60e, BRF_SND },

	{ "s92_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "s92_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


STD_ROM_PICK(Sf2tj) STD_ROM_FN(Sf2tj)

struct BurnDriver BurnDrvCpsSf2tj = {
	"sf2tj", "sf2hf", NULL, "1992",
	"Street Fighter II' Turbo - hyper fighting (street fighter 2' T 921209 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2tjRomInfo,Sf2tjRomName,DrvInputInfo, sf2cejDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//============================================
//Street Fighter II' - champion edition (YYC)
//============================================


static struct BurnRomInfo Sf2yycRomDesc[] = {
	{ "b12.rom",      0x080000, 0x8f742fd5, BRF_ESS | BRF_PRG }, // 0
	{ "b14.rom",      0x080000, 0x8831ec7f, BRF_ESS | BRF_PRG }, // 1
	{ "b11.rom",      0x020000, 0x94a46525, BRF_ESS | BRF_PRG }, // 2
	{ "b13.rom",      0x020000, 0x8fb3dd47, BRF_ESS | BRF_PRG }, // 3

	{ "s92_01.bin",   0x080000, 0x03b0d852, BRF_GRA },			 // 4
	{ "s92_02.bin",   0x080000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",   0x080000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",   0x080000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",   0x080000, 0xba8a2761, BRF_GRA },			 // 8
	{ "s92_06.bin",   0x080000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",   0x080000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",   0x080000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",   0x080000, 0x960687d5, BRF_GRA },			 // 12
	{ "s92_11.bin",   0x080000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",   0x080000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",   0x080000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",   0x010000, 0x08f6b60e, BRF_SND },			 // 16

	{ "s92_18.bin",   0x020000, 0x7f162009, BRF_SND },			 // 17
	{ "s92_19.bin",   0x020000, 0xbeade53f, BRF_SND },			 // 18
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2yyc) STD_ROM_FN(Sf2yyc)

struct BurnDriver BurnDrvCpsSf2yyc = {
	"sf2yyc", "sf2ce", NULL, "1992",
	"Street Fighter II' - champion edition (Hack - YYC)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,2,HARDWARE_CAPCOM_CPS1,
	      NULL,Sf2yycRomInfo,Sf2yycRomName,Sf2yycInputInfo, sf2ceDIPInfo,
	Sf2yycInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==============================================
//Street Fighter II' - champion edition (kouryu)
//==============================================


static struct BurnRomInfo KouryuRomDesc[] = {
	{ "u222.rom",     0x080000, 0x9236a79a, BRF_ESS | BRF_PRG }, // 0
	{ "u196.rom",     0x080000, 0xb23a869d, BRF_ESS | BRF_PRG }, // 1
	{ "u221.rom",     0x020000, 0x64e6e091, BRF_ESS | BRF_PRG }, // 2
	{ "u195.rom",     0x020000, 0xc95e4443, BRF_ESS | BRF_PRG }, // 3

	{ "s92_01.bin",   0x080000, 0x03b0d852, BRF_GRA },			 // 4
	{ "s92_02.bin",   0x080000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",   0x080000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",   0x080000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",   0x080000, 0xba8a2761, BRF_GRA },			 // 8
	{ "s92_06.bin",   0x080000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",   0x080000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",   0x080000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",   0x080000, 0x960687d5, BRF_GRA },			 // 12
	{ "s92_11.bin",   0x080000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",   0x080000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",   0x080000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",   0x010000, 0x08f6b60e, BRF_SND },			 // 16

	{ "s92_18.bin",   0x020000, 0x7f162009, BRF_SND },			 // 17
	{ "s92_19.bin",   0x020000, 0xbeade53f, BRF_SND },			 // 18
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Kouryu) STD_ROM_FN(Kouryu)

struct BurnDriver BurnDrvCpsKouryu = {
	"sf2koryu", "sf2ce", NULL, "1992",
	"Street Fighter II' - champion edition (Hack - kouryu)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,2,HARDWARE_CAPCOM_CPS1,
	      NULL,KouryuRomInfo,KouryuRomName,Sf2yycInputInfo, sf2ceDIPInfo,
	KouryuInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================================================
//Street Fighter II' - champion edition (M-4 [Hack])
//==================================================

static int Sf2m4Init()
{
	int nRet=0;
	Cps=1; Sf2Hack=1;
        nCpsRomLen =3*0x080000;
	nCpsGfxLen =3*0x200000;
	nCpsZRomLen=  0x010000;
	nCpsAdLen  =2*0x020000;

	nCPS68KClockspeed = 7000000;
	nRet=CpsInit(); if (nRet!=0) return 1;

	// Load program roms
	nRet=BurnLoadRom(CpsRom + 0x000001, 0, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x000000, 1, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x100000, 2, 1); if (nRet!=0) return 1;

	// Load up and interleve each set of 4 roms to make the 16x16 tiles
	CpsLoadTiles(CpsGfx+0x000000, 3+0*4);
	CpsLoadTiles(CpsGfx+0x200000, 3+1*4);
	CpsLoadTiles(CpsGfx+0x400000, 3+2*4);

	nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

	nCpsLcReg=0x54;
	CpsLayEn[1]=0xff;
	CpsLayEn[2]=0xff;
	CpsLayEn[3]=0xff;

	CpsMProt[0]=0x40;
	CpsMProt[1]=0x42;
	CpsMProt[2]=0x44;
	CpsMProt[3]=0x46;

	CpsBID[0]=0x00;
	CpsBID[1]=0x00;
	CpsBID[2]=0x00;

	MaskAddr[0]=0x52;
	MaskAddr[1]=0x50;
	MaskAddr[2]=0x4e;
	MaskAddr[3]=0x4c;

	// Load Z80 Rom
	nRet=BurnLoadRom(CpsZRom      , 15, 1);

	// Load ADPCM data
	nRet=BurnLoadRom(CpsAd        , 16, 1);
	nRet=BurnLoadRom(CpsAd+0x20000, 17, 1);

	nRet=CpsRunInit();
	if (nRet!=0) return 1;

	// Ready to go
	return 0;
}

static struct BurnRomInfo Sf2m4RomDesc[] = {
	{ "u222ne",       0x080000, 0x7133489e, BRF_ESS | BRF_PRG }, // 0
	{ "u196ne",       0x080000, 0xb07a4f90, BRF_ESS | BRF_PRG }, // 1
	{ "s92_21a.bin",  0x080000, 0x925a7877, BRF_ESS | BRF_PRG }, // 2

	{ "s92_01.bin",   0x080000, 0x03b0d852, BRF_GRA },			 // 3
	{ "s92_02.bin",   0x080000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",   0x080000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",   0x080000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",   0x080000, 0xba8a2761, BRF_GRA },			 // 7
	{ "s92_06.bin",   0x080000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",   0x080000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",   0x080000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",   0x080000, 0x960687d5, BRF_GRA },			 // 11
	{ "s92_11.bin",   0x080000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",   0x080000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",   0x080000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",   0x010000, 0x08f6b60e, BRF_SND },			 // 15

	{ "s92_18.bin",   0x020000, 0x7f162009, BRF_SND },			 // 16
	{ "s92_19.bin",   0x020000, 0xbeade53f, BRF_SND },			 // 17
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2m4) STD_ROM_FN(Sf2m4)

struct BurnDriver BurnDrvCpsSf2m4 = {
	"sf2m4", "sf2ce", NULL, "1992",
	"Street Fighter II' - champion edition (Hack - M-4)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,2,HARDWARE_CAPCOM_CPS1,
	      NULL,Sf2m4RomInfo,Sf2m4RomName,Sf2yycInputInfo, sf2cejDIPInfo,
	Sf2m4Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================================================
//Street Fighter II' - champion edition (M-5 [Hack])
//==================================================

static int Sf2m5Init()
{
	int nRet=0;
	Cps=1; Sf2Hack=1;
        nCpsRomLen =3*0x080000;
	nCpsGfxLen =3*0x200000;
	nCpsZRomLen=  0x010000;
	nCpsAdLen  =2*0x020000;

	nCPS68KClockspeed = 7000000;
	nRet=CpsInit(); if (nRet!=0) return 1;

	// Load program roms
	nRet=BurnLoadRom(CpsRom + 0x000001, 0, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x000000, 1, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x100000, 2, 1); if (nRet!=0) return 1;

	// Load up and interleve each set of 4 roms to make the 16x16 tiles
	CpsLoadTiles(CpsGfx+0x000000, 3+0*4);
	CpsLoadTiles(CpsGfx+0x200000, 3+1*4);
	CpsLoadTiles(CpsGfx+0x400000, 3+2*4);

	nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

	nCpsLcReg=0x66;
	CpsLayEn[1]=0x02;
	CpsLayEn[2]=0x04;
	CpsLayEn[3]=0x08;

	CpsMProt[0]=0x40;
	CpsMProt[1]=0x42;
	CpsMProt[2]=0x44;
	CpsMProt[3]=0x46;

	CpsBID[0]=0x00;
	CpsBID[1]=0x00;
	CpsBID[2]=0x00;

	MaskAddr[0]=0x68;
	MaskAddr[1]=0x6a;
	MaskAddr[2]=0x6c;
	MaskAddr[3]=0x6e;

	// Load Z80 Rom
	nRet=BurnLoadRom(CpsZRom      , 15, 1);

	// Load ADPCM data
	nRet=BurnLoadRom(CpsAd        , 16, 1);
	nRet=BurnLoadRom(CpsAd+0x20000, 17, 1);

	nRet=CpsRunInit();
	if (nRet!=0) return 1;

	// Ready to go
	return 0;
}

static struct BurnRomInfo Sf2m5RomDesc[] = {
	{ "u222",         0x080000, 0x03991fba, BRF_ESS | BRF_PRG }, // 0
	{ "u196",         0x080000, 0x39f15a1e, BRF_ESS | BRF_PRG }, // 1
	{ "s92_21a.bin",  0x080000, 0x925a7877, BRF_ESS | BRF_PRG }, // 2

	{ "s92_01.bin",   0x080000, 0x03b0d852, BRF_GRA },			 // 3
	{ "s92_02.bin",   0x080000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",   0x080000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",   0x080000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",   0x080000, 0xba8a2761, BRF_GRA },			 // 7
	{ "s92_06.bin",   0x080000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",   0x080000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",   0x080000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",   0x080000, 0x960687d5, BRF_GRA },			 // 11
	{ "s92_11.bin",   0x080000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",   0x080000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",   0x080000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",   0x010000, 0x08f6b60e, BRF_SND },			 // 15

	{ "s92_18.bin",   0x020000, 0x7f162009, BRF_SND },			 // 16
	{ "s92_19.bin",   0x020000, 0xbeade53f, BRF_SND },			 // 17
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2m5) STD_ROM_FN(Sf2m5)

struct BurnDriver BurnDrvCpsSf2m5 = {
	"sf2m5", "sf2ce", NULL, "1992",
	"Street Fighter II' - champion edition (Hack - M-5)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,2,HARDWARE_CAPCOM_CPS1,
	      NULL,Sf2m5RomInfo,Sf2m5RomName,Sf2yycInputInfo, sf2ceDIPInfo,
	Sf2m5Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================================================
//Street Fighter II' - champion edition (M-6 [Hack])
//==================================================

static struct BurnRomInfo Sf2m6RomDesc[] = {
	{ "u222-6b",      0x080000, 0x0a3692be, BRF_ESS | BRF_PRG }, // 0
	{ "u196-6b",      0x080000, 0x80454da7, BRF_ESS | BRF_PRG }, // 1
	{ "s92_21a.bin",  0x080000, 0x925a7877, BRF_ESS | BRF_PRG }, // 2

	{ "s92_01.bin",   0x080000, 0x03b0d852, BRF_GRA },			 // 3
	{ "s92_02.bin",   0x080000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",   0x080000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",   0x080000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",   0x080000, 0xba8a2761, BRF_GRA },			 // 7
	{ "s92_06.bin",   0x080000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",   0x080000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",   0x080000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",   0x080000, 0x960687d5, BRF_GRA },			 // 11
	{ "s92_11.bin",   0x080000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",   0x080000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",   0x080000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",   0x010000, 0x08f6b60e, BRF_SND },			 // 15

	{ "s92_18.bin",   0x020000, 0x7f162009, BRF_SND },			 // 16
	{ "s92_19.bin",   0x020000, 0xbeade53f, BRF_SND },			 // 17
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2m6) STD_ROM_FN(Sf2m6)

struct BurnDriver BurnDrvCpsSf2m6 = {
	"sf2m6", "sf2ce", NULL, "1992",
	"Street Fighter II' - champion edition (Hack - M-6)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,2,HARDWARE_CAPCOM_CPS1,
	      NULL,Sf2m6RomInfo,Sf2m6RomName,Sf2yycInputInfo, sf2ceDIPInfo,
	Sf2m5Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================================================
//Street Fighter II' - champion edition (M-7 [Hack])
//==================================================

static int Sf2m7Init()
{
	int nRet=0;
	Cps=1; Sf2Hack=1;
        nCpsRomLen =3*0x080000;
	nCpsGfxLen =3*0x200000;
	nCpsZRomLen=  0x010000;
	nCpsAdLen  =2*0x020000;

	nCPS68KClockspeed = 7000000;
	nRet=CpsInit(); if (nRet!=0) return 1;

	// Load program roms
	nRet=BurnLoadRom(CpsRom + 0x000001, 0, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x000000, 1, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x080001, 2, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x080000, 3, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x100000, 4, 1); if (nRet!=0) return 1;

	// Load up and interleve each set of 4 roms to make the 16x16 tiles
	CpsLoadTiles(CpsGfx+0x000000, 5+0*4);
	CpsLoadTiles(CpsGfx+0x200000, 5+1*4);
	CpsLoadTiles(CpsGfx+0x400000, 5+2*4);

	nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

	nCpsLcReg=0x66;
	CpsLayEn[1]=0x02;
	CpsLayEn[2]=0x04;
	CpsLayEn[3]=0x08;

	CpsMProt[0]=0x40;
	CpsMProt[1]=0x42;
	CpsMProt[2]=0x44;
	CpsMProt[3]=0x46;

	CpsBID[0]=0x00;
	CpsBID[1]=0x00;
	CpsBID[2]=0x00;

	MaskAddr[0]=0x68;
	MaskAddr[1]=0x6a;
	MaskAddr[2]=0x6c;
	MaskAddr[3]=0x6e;

	// Load Z80 Rom
	nRet=BurnLoadRom(CpsZRom      , 17, 1);

	// Load ADPCM data
	nRet=BurnLoadRom(CpsAd        , 18, 1);
	nRet=BurnLoadRom(CpsAd+0x20000, 19, 1);

	nRet=CpsRunInit();
	if (nRet!=0) return 1;

	// Ready to go
	return 0;
}

static struct BurnRomInfo Sf2m7RomDesc[] = {
	{ "u222-2i",      0x040000, 0x1ca7adbd, BRF_ESS | BRF_PRG }, // 0
	{ "u196-2i",      0x040000, 0xf758408c, BRF_ESS | BRF_PRG }, // 1
	{ "u222-2s",      0x040000, 0x720cea3e, BRF_ESS | BRF_PRG }, // 2
	{ "u196-2s",      0x040000, 0x9932832c, BRF_ESS | BRF_PRG }, // 3
	{ "s92_21a.bin",  0x080000, 0x925a7877, BRF_ESS | BRF_PRG }, // 4

	{ "s92_01.bin",   0x080000, 0x03b0d852, BRF_GRA },			 // 5
	{ "s92_02.bin",   0x080000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",   0x080000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",   0x080000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",   0x080000, 0xba8a2761, BRF_GRA },			 // 9
	{ "s92_06.bin",   0x080000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",   0x080000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",   0x080000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",   0x080000, 0x960687d5, BRF_GRA },			 // 13
	{ "s92_11.bin",   0x080000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",   0x080000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",   0x080000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",   0x010000, 0x08f6b60e, BRF_SND },			 // 17

	{ "s92_18.bin",   0x020000, 0x7f162009, BRF_SND },			 // 18
	{ "s92_19.bin",   0x020000, 0xbeade53f, BRF_SND },			 // 19
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2m7) STD_ROM_FN(Sf2m7)

struct BurnDriver BurnDrvCpsSf2m7 = {
	"sf2m7", "sf2ce", NULL, "1992",
	"Street Fighter II' - champion edition (Hack - M-7)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,2,HARDWARE_CAPCOM_CPS1,
	      NULL,Sf2m7RomInfo,Sf2m7RomName,Sf2yycInputInfo, sf2ceDIPInfo,
	Sf2m7Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================================================
//Street Fighter II' - champion edition (M-2 [Hack])
//==================================================

static int Sf2m2Init()
{
	int nRet=0;
	Cps=1; Sf2Hack=1;
        nCpsRomLen =3*0x080000;
	nCpsGfxLen =3*0x200000;
	nCpsZRomLen=  0x010000;
	nCpsAdLen  =2*0x020000;

	nCPS68KClockspeed = 7000000;
	nRet=CpsInit(); if (nRet!=0) return 1;

	// Load program roms
	nRet=BurnLoadRom(CpsRom + 0x000001, 0, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x000000, 1, 2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom + 0x100000, 2, 1); if (nRet!=0) return 1;
	
	*((unsigned short*)(CpsRom + 0xC0680)) = 0x4E71;
	*((unsigned short*)(CpsRom + 0xC0682)) = 0x4E71;
	*((unsigned short*)(CpsRom + 0xC0684)) = 0x4E71;

	// Load up and interleve each set of 4 roms to make the 16x16 tiles
	CpsLoadTiles(CpsGfx+0x000000, 3+0*4);
	CpsLoadTiles(CpsGfx+0x200000, 3+1*4);
	CpsLoadTiles(CpsGfx+0x400000, 3+2*4);

	nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

	nCpsLcReg=0x66;
	CpsLayEn[1]=0x02;
	CpsLayEn[2]=0x04;
	CpsLayEn[3]=0x08;

	CpsMProt[0]=0x40;
	CpsMProt[1]=0x42;
	CpsMProt[2]=0x44;
	CpsMProt[3]=0x46;

	CpsBID[0]=0x00;
	CpsBID[1]=0x00;
	CpsBID[2]=0x00;

	MaskAddr[0]=0x68;
	MaskAddr[1]=0x6a;
	MaskAddr[2]=0x6c;
	MaskAddr[3]=0x6e;

	// Load Z80 Rom
	nRet=BurnLoadRom(CpsZRom      , 15, 1);

	// Load ADPCM data
	nRet=BurnLoadRom(CpsAd        , 16, 1);
	nRet=BurnLoadRom(CpsAd+0x20000, 17, 1);

	nRet=CpsRunInit();
	if (nRet!=0) return 1;

	// Ready to go
	return 0;
}

static struct BurnRomInfo Sf2m2RomDesc[] = {
	{ "ch222esp",     0x080000, 0x9e6d058a, BRF_ESS | BRF_PRG }, // 0
	{ "ch196esp",     0x080000, 0xed2ff437, BRF_ESS | BRF_PRG }, // 1
	{ "s92_21a.bin",  0x080000, 0x925a7877, BRF_ESS | BRF_PRG }, // 4

	{ "s92_01.bin",   0x080000, 0x03b0d852, BRF_GRA },			 // 5
	{ "s92_02.bin",   0x080000, 0x840289ec, BRF_GRA },
	{ "s92_03.bin",   0x080000, 0xcdb5f027, BRF_GRA },
	{ "s92_04.bin",   0x080000, 0xe2799472, BRF_GRA },

	{ "s92_05.bin",   0x080000, 0xba8a2761, BRF_GRA },			 // 9
	{ "s92_06.bin",   0x080000, 0xe584bfb5, BRF_GRA },
	{ "s92_07.bin",   0x080000, 0x21e3f87d, BRF_GRA },
	{ "s92_08.bin",   0x080000, 0xbefc47df, BRF_GRA },

	{ "s92_10.bin",   0x080000, 0x960687d5, BRF_GRA },			 // 13
	{ "s92_11.bin",   0x080000, 0x978ecd18, BRF_GRA },
	{ "s92_12.bin",   0x080000, 0xd6ec9a0a, BRF_GRA },
	{ "s92_13.bin",   0x080000, 0xed2c67f6, BRF_GRA },

	{ "s92_09.bin",   0x010000, 0x08f6b60e, BRF_SND },			 // 17

	{ "s92_18.bin",   0x020000, 0x7f162009, BRF_SND },			 // 18
	{ "s92_19.bin",   0x020000, 0xbeade53f, BRF_SND },			 // 19
};

// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2m2) STD_ROM_FN(Sf2m2)

struct BurnDriver BurnDrvCpsSf2m2 = {
	"sf2m2", "sf2ce", NULL, "1992",
	"Street Fighter II' - champion edition (Hack - M-2)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,2,HARDWARE_CAPCOM_CPS1,
	      NULL,Sf2m2RomInfo,Sf2m2RomName,Sf2yycInputInfo, sf2ceDIPInfo,
	Sf2m2Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
