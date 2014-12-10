//Street Fighter II - the world warrior

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
  {"Service",			BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip A",				BIT_DIPSWITCH, &Cpi01A,   "dip"},
  {"Dip B",				BIT_DIPSWITCH, &Cpi01C,   "dip"},
  {"Dip C",				BIT_DIPSWITCH, &Cpi01E,   "dip"},
};


// Treble Winner - Input for sf2ue
static struct BurnInputInfo Sf2ueInputList[]=
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
  {"P1 Weak kick",		BIT_DIGITAL, CpsInp1fd+0, "p1 fire 4"},
  {"P1 Medium kick",	BIT_DIGITAL, CpsInp1fd+1, "p1 fire 5"},
  {"P1 Strong kick",	BIT_DIGITAL, CpsInp1fd+2, "p1 fire 6"},
  {"P2 Coin",			BIT_DIGITAL, CpsInp018+1, "p2 coin"},	// 0x0C
  {"P2 Start",			BIT_DIGITAL, CpsInp018+5, "p2 start"},
  {"P2 Up",				BIT_DIGITAL, CpsInp000+3, "p2 up"},		// 0x0E
  {"P2 Down",			BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left",			BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right",			BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Weak punch",		BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},	// 0x12
  {"P2 Medium punch",	BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Strong Punch",	BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},
  {"P2 Weak kick",		BIT_DIGITAL, CpsInp1fd+4, "p2 fire 4"},
  {"P2 Medium kick",	BIT_DIGITAL, CpsInp1fd+5, "p2 fire 5"},
  {"P2 Strong kick",	BIT_DIGITAL, CpsInp1fd+6, "p2 fire 6"},
  {"Diagnostic",		BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Reset",				BIT_DIGITAL, &CpsReset,	  "reset"},
  {"Dip A",				BIT_DIPSWITCH, &Cpi01A,   "dip"},
  {"Dip B",				BIT_DIPSWITCH, &Cpi01C,   "dip"},
  {"Dip C",				BIT_DIPSWITCH, &Cpi01E,   "dip"},
};

STDINPUTINFO(Sf2ue);

STDINPUTINFO(Drv);

static struct BurnDIPInfo sf2DIPList[]=
{
	// Defaults
	{0x1b, 0xff, 0xff, 0x00, NULL                },
	{0x1c, 0xff, 0xff, 0x00, NULL                },
	{0x1d, 0xff, 0xff, 0x00, NULL                },

	// Dip A
	{0   , 0xfe, 0   , 8   , "A Side"                 },
	{0x1b, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x1b, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x1b, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x1b, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x1b, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x1b, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x1b, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x1b, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 8   , "B Side"                 },
	{0x1b, 0x01, 0x38, 0x38, "4 Coins 1 Credit"       },
	{0x1b, 0x01, 0x38, 0x30, "3 Coins 1 Credit"       },
	{0x1b, 0x01, 0x38, 0x28, "2 Coins 1 Credit"       },
	{0x1b, 0x01, 0x38, 0x00, "1 Coin 1 Credit"        },
	{0x1b, 0x01, 0x38, 0x08, "1 Coin 2 Credits"       },
	{0x1b, 0x01, 0x38, 0x10, "1 Coin 3 Credits"       },
	{0x1b, 0x01, 0x38, 0x18, "1 Coin 4 Credits"       },
	{0x1b, 0x01, 0x38, 0x20, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 2   , "Continue Coin"          },
	{0x1b, 0x01, 0x40, 0x00, "Off"                    },
	{0x1b, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x80, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x80, 0x80, "On"                     },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Game Level"             },
	{0x1c, 0x01, 0x07, 0x00, "0"                 },
	{0x1c, 0x01, 0x07, 0x01, "1"                 },
	{0x1c, 0x01, 0x07, 0x02, "2"                 },
	{0x1c, 0x01, 0x07, 0x03, "3"              },
	{0x1c, 0x01, 0x07, 0x04, "4"            },
	{0x1c, 0x01, 0x07, 0x05, "5"            },
	{0x1c, 0x01, 0x07, 0x06, "6"            },
	{0x1c, 0x01, 0x07, 0x07, "7"         },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1c, 0x01, 0x08, 0x00, "Off"                    },
//	{0x1c, 0x01, 0x08, 0x08, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//      {0x1c, 0x01, 0x10, 0x00, "Off"                    },
//      {0x1c, 0x01, 0x10, 0x10, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1c, 0x01, 0x20, 0x00, "Off"                    },
//	{0x1c, 0x01, 0x20, 0x20, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//      {0x1c, 0x01, 0x40, 0x00, "Off"                    },
//      {0x1c, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//      {0x1c, 0x01, 0x80, 0x00, "Off"                    },
//      {0x1c, 0x01, 0x80, 0x80, "On"                     },

	// Dip C
//	{0   , 0xfe, 0   , 4   , "Unknown"                },
//      {0x1d, 0x01, 0x03, 0x00, "1"                      },
//      {0x1d, 0x01, 0x03, 0x01, "2"                      },
//      {0x1d, 0x01, 0x03, 0x02, "3"                      },
//      {0x1d, 0x01, 0x03, 0x03, "4"                      },

	{0   , 0xfe, 0   , 2   , "Free Play"              },
        {0x1d, 0x01, 0x04, 0x00, "Off"                    },
        {0x1d, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Stop"                   },
        {0x1d, 0x01, 0x08, 0x00, "Off"                    },
        {0x1d, 0x01, 0x08, 0x08, "On"                     },

	{0   , 0xfe, 0   , 2   , "Flip"                   },
        {0x1d, 0x01, 0x10, 0x00, "Off"                    },
        {0x1d, 0x01, 0x10, 0x10, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sound"             },
        {0x1d, 0x01, 0x20, 0x00, "Off"                    },
        {0x1d, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 2   , "Continue"               },
        {0x1d, 0x01, 0x40, 0x00, "Off"                    },
        {0x1d, 0x01, 0x40, 0x40, "On"                     },
};

STDDIPINFO(sf2);

static struct BurnDIPInfo sf2jDIPList[]=
{
	// Defaults
	{0x1b, 0xff, 0xff, 0x00, NULL                },
	{0x1c, 0xff, 0xff, 0x00, NULL                },
	{0x1d, 0xff, 0xff, 0x00, NULL                },

	// Dip A
	{0   , 0xfe, 0   , 8   , "A Side"                 },
	{0x1b, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x1b, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x1b, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x1b, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x1b, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x1b, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x1b, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x1b, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 8   , "B Side"                 },
	{0x1b, 0x01, 0x38, 0x38, "4 Coins 1 Credit"       },
	{0x1b, 0x01, 0x38, 0x30, "3 Coins 1 Credit"       },
	{0x1b, 0x01, 0x38, 0x28, "2 Coins 1 Credit"       },
	{0x1b, 0x01, 0x38, 0x00, "1 Coin 1 Credit"        },
	{0x1b, 0x01, 0x38, 0x08, "1 Coin 2 Credits"       },
	{0x1b, 0x01, 0x38, 0x10, "1 Coin 3 Credits"       },
	{0x1b, 0x01, 0x38, 0x18, "1 Coin 4 Credits"       },
	{0x1b, 0x01, 0x38, 0x20, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 2   , "Continue Coin"          },
	{0x1b, 0x01, 0x40, 0x00, "Off"                    },
	{0x1b, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x80, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x80, 0x80, "On"                     },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Game Level"             },
	{0x1c, 0x01, 0x07, 0x00, "0"                 },
	{0x1c, 0x01, 0x07, 0x01, "1"                 },
	{0x1c, 0x01, 0x07, 0x02, "2"                 },
	{0x1c, 0x01, 0x07, 0x03, "3"              },
	{0x1c, 0x01, 0x07, 0x04, "4"            },
	{0x1c, 0x01, 0x07, 0x05, "5"            },
	{0x1c, 0x01, 0x07, 0x06, "6"            },
	{0x1c, 0x01, 0x07, 0x07, "7"         },

	{0   , 0xfe, 0   , 2   , "2 Players Game"         },
	{0x1c, 0x01, 0x08, 0x00, "1 Credit/No Continue"   },
	{0x1c, 0x01, 0x08, 0x08, "2 Credits/Winner Continue"},

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//      {0x1c, 0x01, 0x10, 0x00, "Off"                    },
//      {0x1c, 0x01, 0x10, 0x10, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1c, 0x01, 0x20, 0x00, "Off"                    },
//	{0x1c, 0x01, 0x20, 0x20, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//      {0x1c, 0x01, 0x40, 0x00, "Off"                    },
//      {0x1c, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//      {0x1c, 0x01, 0x80, 0x00, "Off"                    },
//      {0x1c, 0x01, 0x80, 0x80, "On"                     },

	// Dip C
//	{0   , 0xfe, 0   , 4   , "Unknown"                },
//      {0x1d, 0x01, 0x03, 0x00, "1"                      },
//      {0x1d, 0x01, 0x03, 0x01, "2"                      },
//      {0x1d, 0x01, 0x03, 0x02, "3"                      },
//      {0x1d, 0x01, 0x03, 0x03, "4"                      },

	{0   , 0xfe, 0   , 2   , "Free Play"              },
        {0x1d, 0x01, 0x04, 0x00, "Off"                    },
        {0x1d, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Stop"                   },
        {0x1d, 0x01, 0x08, 0x00, "Off"                    },
        {0x1d, 0x01, 0x08, 0x08, "On"                     },

	{0   , 0xfe, 0   , 2   , "Flip"                   },
        {0x1d, 0x01, 0x10, 0x00, "Off"                    },
        {0x1d, 0x01, 0x10, 0x10, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sound"             },
        {0x1d, 0x01, 0x20, 0x00, "Off"                    },
        {0x1d, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 2   , "Continue"               },
        {0x1d, 0x01, 0x40, 0x00, "Off"                    },
        {0x1d, 0x01, 0x40, 0x40, "On"                     },
};

STDDIPINFO(sf2j);


static int DrvExit()
{

  CpsRunExit();
  CpsExit();
  nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0; Sf2jc=0;
  return 0;
}

//============================================
//Street Fighter II - the world warrior Init05
//============================================

static int Drv05Init()
{
  int nRet=0; int i=0;
  Cps=1;
  nCpsRomLen =  0x100000;
  nCpsGfxLen =3*0x200000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  for (i=0;i<8;i++)
  {
    int a; a=(i>>1)*0x40000; a+=(i&1); a^=1;
    nRet=BurnLoadRom(CpsRom+a,i,2); if (nRet!=0) return 1;
  }

  // Load up and interleve each set of 4 roms to make the 16x16 tiles
  for (i=0;i<3;i++) CpsLoadTiles(CpsGfx+i*0x200000,8+i*4);

  nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

  nCpsLcReg=0x68; // Layer control register is at 0x52
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x08;
  CpsLayEn[3]=0x20; // Layer enable is different

  // Start of Board ID improvments by KEV. 0x5E,0x0404
  CpsBID[0]=0x60;
  CpsBID[1]=0x00;
  CpsBID[2]=0x05;

  MaskAddr[0]=0x6a;
  MaskAddr[1]=0x6c;
  MaskAddr[2]=0x6e;
  MaskAddr[3]=0x70;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,20,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,21,1);
  nRet=BurnLoadRom(CpsAd+0x20000,22,1);


  nRet=CpsRunInit();

  if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//============================================
//Street Fighter II - the world warrior Init11
//============================================

static int Drv11Init()
{
  int nRet=0; int i=0;
  Cps=1;
  nCpsRomLen =  0x100000;
  nCpsGfxLen =3*0x200000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  for (i=0;i<8;i++)
  {
    int a; a=(i>>1)*0x40000; a+=(i&1); a^=1;
    nRet=BurnLoadRom(CpsRom+a,i,2); if (nRet!=0) return 1;
  }

  // Load up and interleve each set of 4 roms to make the 16x16 tiles
  for (i=0;i<3;i++) CpsLoadTiles(CpsGfx+i*0x200000,8+i*4);

  nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

  nCpsLcReg=0x66; // Layer control register is at 0x54
  CpsLayEn[1]=0x20;
  CpsLayEn[2]=0x10;
  CpsLayEn[3]=0x08; // Layer enable is different

  // Start of Board ID improvments by KEV. 0x48,0x0407
  CpsBID[0]=0x72;
  CpsBID[1]=0x04;
  CpsBID[2]=0x01;

  MaskAddr[0]=0x68;
  MaskAddr[1]=0x6a;
  MaskAddr[2]=0x6c;
  MaskAddr[3]=0x6e;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,20,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,21,1);
  nRet=BurnLoadRom(CpsAd+0x20000,22,1);


  nRet=CpsRunInit();

  if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//============================================
//Street Fighter II - the world warrior Init12
//============================================

static int Drv12Init()
{
  int nRet=0; int i=0;
  Cps=1; Sf2jc=1;
  nCpsRomLen =  0x100000;
  nCpsGfxLen =3*0x200000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  for (i=0;i<8;i++)
  {
    int a; a=(i>>1)*0x40000; a+=(i&1); a^=1;
    nRet=BurnLoadRom(CpsRom+a,i,2); if (nRet!=0) return 1;
  }

  // Load up and interleve each set of 4 roms to make the 16x16 tiles
  for (i=0;i<3;i++) CpsLoadTiles(CpsGfx+i*0x200000,8+i*4);

  nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

  nCpsLcReg=0x6c; // Layer control register is at 0x6c
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x08; // Layer enable is different

  // Start of Board ID improvments by KEV. 0x60,0x0402
  CpsBID[0]=0x60;
  CpsBID[1]=0x04;
  CpsBID[2]=0x02;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,20,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,21,1);
  nRet=BurnLoadRom(CpsAd+0x20000,22,1);


  nRet=CpsRunInit();

  if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//============================================
//Street Fighter II - the world warrior Init13
//============================================

static int Drv13Init()
{
  int nRet=0; int i=0;
  Cps=1;
  nCpsRomLen =  0x100000;
  nCpsGfxLen =3*0x200000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  for (i=0;i<8;i++)
  {
    int a; a=(i>>1)*0x40000; a+=(i&1); a^=1;
    nRet=BurnLoadRom(CpsRom+a,i,2); if (nRet!=0) return 1;
  }

  // Load up and interleve each set of 4 roms to make the 16x16 tiles
  for (i=0;i<3;i++) CpsLoadTiles(CpsGfx+i*0x200000,8+i*4);

  nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

  nCpsLcReg=0x62; // Layer control register is at 0x62
  CpsLayEn[1]=0x20;
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x02; // Layer enable is different

  // Start of Board ID improvments by KEV. 0x6e,0x0403
  CpsBID[0]=0x6e;
  CpsBID[1]=0x04;
  CpsBID[2]=0x03;

  MaskAddr[0]=0x64;
  MaskAddr[1]=0x66;
  MaskAddr[2]=0x68;
  MaskAddr[3]=0x6a;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,20,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,21,1);
  nRet=BurnLoadRom(CpsAd+0x20000,22,1);


  nRet=CpsRunInit();

  if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//============================================
//Street Fighter II - the world warrior Init14
//============================================

static int Drv14Init()
{
  int nRet=0; int i=0;
  Cps=1;
  nCpsRomLen =  0x100000;
  nCpsGfxLen =3*0x200000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  for (i=0;i<8;i++)
  {
    int a; a=(i>>1)*0x40000; a+=(i&1); a^=1;
    nRet=BurnLoadRom(CpsRom+a,i,2); if (nRet!=0) return 1;
  }

  // Load up and interleve each set of 4 roms to make the 16x16 tiles
  for (i=0;i<3;i++) CpsLoadTiles(CpsGfx+i*0x200000,8+i*4);

  nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

  nCpsLcReg=0x52; // Layer control register is at 0x52
  CpsLayEn[1]=0x08;
  CpsLayEn[2]=0x30;
  CpsLayEn[3]=0x30; // Layer enable is different

  // Start of Board ID improvments by KEV. 0x5E,0x0404
  CpsBID[0]=0x5E;
  CpsBID[1]=0x04;
  CpsBID[2]=0x04;

  MaskAddr[0]=0x54;
  MaskAddr[1]=0x56;
  MaskAddr[2]=0x58;
  MaskAddr[3]=0x5a;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,20,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,21,1);
  nRet=BurnLoadRom(CpsAd+0x20000,22,1);


  nRet=CpsRunInit();

  if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//============================================
//Street Fighter II - the world warrior Init15
//============================================

static int Drv15Init()
{
  int nRet=0; int i=0;
  Cps=1;
  nCpsRomLen =  0x100000;
  nCpsGfxLen =3*0x200000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  for (i=0;i<8;i++)
  {
    int a; a=(i>>1)*0x40000; a+=(i&1); a^=1;
    nRet=BurnLoadRom(CpsRom+a,i,2); if (nRet!=0) return 1;
  }

  // Load up and interleve each set of 4 roms to make the 16x16 tiles
  for (i=0;i<3;i++) CpsLoadTiles(CpsGfx+i*0x200000,8+i*4);

  nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

  nCpsLcReg=0x42; // Layer control register is at 0x52
  CpsLayEn[1]=0x04;
  CpsLayEn[2]=0x22;
  CpsLayEn[3]=0x22; // Layer enable is different

  // Start of Board ID improvments by KEV. 0x5E,0x0404
  CpsBID[0]=0x4E;
  CpsBID[1]=0x04;
  CpsBID[2]=0x05;

  MaskAddr[0]=0x44;
  MaskAddr[1]=0x46;
  MaskAddr[2]=0x48;
  MaskAddr[3]=0x4A;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,20,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,21,1);
  nRet=BurnLoadRom(CpsAd+0x20000,22,1);


  nRet=CpsRunInit();

  if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//============================================
//Street Fighter II - the world warrior Init17
//============================================

static int Drv17Init()
{
  int nRet=0; int i=0;
  Cps=1;
  nCpsRomLen =  0x100000;
  nCpsGfxLen =3*0x200000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  for (i=0;i<8;i++)
  {
    int a; a=(i>>1)*0x40000; a+=(i&1); a^=1;
    nRet=BurnLoadRom(CpsRom+a,i,2); if (nRet!=0) return 1;
  }

  // Load up and interleve each set of 4 roms to make the 16x16 tiles
  for (i=0;i<3;i++) CpsLoadTiles(CpsGfx+i*0x200000,8+i*4);

  nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

  nCpsLcReg=0x54; // Layer control register is at 0x54
  CpsLayEn[1]=0x08;
  CpsLayEn[2]=0x10;
  CpsLayEn[3]=0x02; // Layer enable is different

  // Start of Board ID improvments by KEV. 0x48,0x0407
  CpsBID[0]=0x48;
  CpsBID[1]=0x04;
  CpsBID[2]=0x07;

  MaskAddr[0]=0x52;
  MaskAddr[1]=0x50;
  MaskAddr[2]=0x4e;
  MaskAddr[3]=0x4c;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,20,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,21,1);
  nRet=BurnLoadRom(CpsAd+0x20000,22,1);


  nRet=CpsRunInit();

  if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//============================================
//Street Fighter II - the world warrior Init18
//============================================

static int Drv18Init()
{
  int nRet=0; int i=0;
  Cps=1;
  nCpsRomLen =  0x100000;
  nCpsGfxLen =3*0x200000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  for (i=0;i<8;i++)
  {
    int a; a=(i>>1)*0x40000; a+=(i&1); a^=1;
    nRet=BurnLoadRom(CpsRom+a,i,2); if (nRet!=0) return 1;
  }

  // Load up and interleve each set of 4 roms to make the 16x16 tiles
  for (i=0;i<3;i++) CpsLoadTiles(CpsGfx+i*0x200000,8+i*4);

  nCpsGfxScroll[1]=nCpsGfxScroll[2]=nCpsGfxScroll[3]=0x400000; // Offset to Scroll tiles

  nCpsLcReg=0xdc; // Layer control register is at 0xdc
  CpsLayEn[1]=0x10;
  CpsLayEn[2]=0x0a;
  CpsLayEn[3]=0x0a; // Layer enable is different

  // Start of Board ID improvments by KEV. 0xd0,0x0408
  CpsBID[0]=0xd0;
  CpsBID[1]=0x04;
  CpsBID[2]=0x08;

  MaskAddr[0]=0xda;
  MaskAddr[1]=0xd8;
  MaskAddr[2]=0xd6;
  MaskAddr[3]=0xd4;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,20,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,21,1);
  nRet=BurnLoadRom(CpsAd+0x20000,22,1);


  nRet=CpsRunInit();

  if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//=============================================
//Street Fighter II - the world warrior (World)
//=============================================


static struct BurnRomInfo Sf2RomDesc[] = {
// 0
	{ "sf2e.30g",      0x20000, 0xfe39ee33, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2e.37g",      0x20000, 0xfb92cd74, BRF_ESS | BRF_PRG },
	{ "sf2e.31g",      0x20000, 0x69a0a301, BRF_ESS | BRF_PRG },
	{ "sf2e.38g",      0x20000, 0x5e22db70, BRF_ESS | BRF_PRG },
	{ "sf2e.28g",      0x20000, 0x8bf9f1e5, BRF_ESS | BRF_PRG },
	{ "sf2e.35g",      0x20000, 0x626ef934, BRF_ESS | BRF_PRG },
	{ "sf2_29a.bin",   0x20000, 0xbb4af315, BRF_ESS | BRF_PRG },
	{ "sf2_36a.bin",   0x20000, 0xc02a13eb, BRF_ESS | BRF_PRG },

// 8
	{ "sf2_06.bin",    0x80000, 0x22c9cc8e, BRF_GRA },
	{ "sf2_08.bin",    0x80000, 0x57213be8, BRF_GRA },
	{ "sf2_05.bin",    0x80000, 0xba529b4f, BRF_GRA },
	{ "sf2_07.bin",    0x80000, 0x4b1b33a8, BRF_GRA },
	{ "sf2_15.bin",    0x80000, 0x2c7e2229, BRF_GRA },
	{ "sf2_17.bin",    0x80000, 0xb5548f17, BRF_GRA },
	{ "sf2_14.bin",    0x80000, 0x14b84312, BRF_GRA },
	{ "sf2_16.bin",    0x80000, 0x5e9cd89a, BRF_GRA },
	{ "sf2_25.bin",    0x80000, 0x994bfa58, BRF_GRA },
	{ "sf2_27.bin",    0x80000, 0x3e66ad9d, BRF_GRA },
	{ "sf2_24.bin",    0x80000, 0xc1befaa8, BRF_GRA },
	{ "sf2_26.bin",    0x80000, 0x0627c831, BRF_GRA },

// 20
// z80 program
	{ "sf2_09.bin",    0x10000, 0xa4823a1b, BRF_SND },
// adpcm samples
	{ "sf2_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "sf2_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2) STD_ROM_FN(Sf2)

struct BurnDriver BurnDrvCpsSf2 = {
	"sf2", NULL, NULL, "1991",
	"Street Fighter II - the world warrior (910522 etc)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2RomInfo,Sf2RomName,DrvInputInfo, sf2DIPInfo,
	Drv11Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=============================================
//Street Fighter II - the world warrior (World 910214)
//=============================================


static struct BurnRomInfo Sf2ebRomDesc[] = {
	{ "sf2_30a.bin",   0x20000, 0x57bd7051, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2e_37b.rom",  0x20000, 0x62691cdd, BRF_ESS | BRF_PRG },
	{ "sf2_31a.bin",   0x20000, 0xa673143d, BRF_ESS | BRF_PRG },
	{ "sf2_38a.bin",   0x20000, 0x4c2ccef7, BRF_ESS | BRF_PRG },
	{ "sf2_28a.bin",   0x20000, 0x4009955e, BRF_ESS | BRF_PRG },
	{ "sf2_35a.bin",   0x20000, 0x8c1f3994, BRF_ESS | BRF_PRG },
	{ "sf2_29a.bin",   0x20000, 0xbb4af315, BRF_ESS | BRF_PRG },
	{ "sf2_36a.bin",   0x20000, 0xc02a13eb, BRF_ESS | BRF_PRG },

// 8
	{ "sf2_06.bin",    0x80000, 0x22c9cc8e, BRF_GRA },
	{ "sf2_08.bin",    0x80000, 0x57213be8, BRF_GRA },
	{ "sf2_05.bin",    0x80000, 0xba529b4f, BRF_GRA },
	{ "sf2_07.bin",    0x80000, 0x4b1b33a8, BRF_GRA },
	{ "sf2_15.bin",    0x80000, 0x2c7e2229, BRF_GRA },
	{ "sf2_17.bin",    0x80000, 0xb5548f17, BRF_GRA },
	{ "sf2_14.bin",    0x80000, 0x14b84312, BRF_GRA },
	{ "sf2_16.bin",    0x80000, 0x5e9cd89a, BRF_GRA },
	{ "sf2_25.bin",    0x80000, 0x994bfa58, BRF_GRA },
	{ "sf2_27.bin",    0x80000, 0x3e66ad9d, BRF_GRA },
	{ "sf2_24.bin",    0x80000, 0xc1befaa8, BRF_GRA },
	{ "sf2_26.bin",    0x80000, 0x0627c831, BRF_GRA },

// 20
// z80 program
	{ "sf2_09.bin",    0x10000, 0xa4823a1b, BRF_SND },
// adpcm samples
	{ "sf2_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "sf2_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2eb) STD_ROM_FN(Sf2eb)

struct BurnDriver BurnDrvCpsSf2eb = {
	"sf2eb", "sf2", NULL, "1991",
	"Street Fighter II - the world warrior (910214 etc)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2ebRomInfo,Sf2ebRomName,DrvInputInfo, sf2DIPInfo,
	Drv17Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================================================
//Street Fighter II - the world warrior (USA Rev. A)
//==================================================


static struct BurnRomInfo Sf2uaRomDesc[] = {
// 0
	{ "sf2u.30a",      0x20000, 0x08beb861, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2u.37a",      0x20000, 0xb7638d69, BRF_ESS | BRF_PRG },
	{ "sf2u.31a",      0x20000, 0x0d5394e0, BRF_ESS | BRF_PRG },
	{ "sf2u.38a",      0x20000, 0x42d6a79e, BRF_ESS | BRF_PRG },
	{ "sf2u.28a",      0x20000, 0x387a175c, BRF_ESS | BRF_PRG },
	{ "sf2u.35a",      0x20000, 0xa1a5adcc, BRF_ESS | BRF_PRG },
	{ "sf2_29a.bin",   0x20000, 0xbb4af315, BRF_ESS | BRF_PRG },
	{ "sf2_36a.bin",   0x20000, 0xc02a13eb, BRF_ESS | BRF_PRG },

// 8
	{ "sf2_06.bin",    0x80000, 0x22c9cc8e, BRF_GRA },
	{ "sf2_08.bin",    0x80000, 0x57213be8, BRF_GRA },
	{ "sf2_05.bin",    0x80000, 0xba529b4f, BRF_GRA },
	{ "sf2_07.bin",    0x80000, 0x4b1b33a8, BRF_GRA },
	{ "sf2_15.bin",    0x80000, 0x2c7e2229, BRF_GRA },
	{ "sf2_17.bin",    0x80000, 0xb5548f17, BRF_GRA },
	{ "sf2_14.bin",    0x80000, 0x14b84312, BRF_GRA },
	{ "sf2_16.bin",    0x80000, 0x5e9cd89a, BRF_GRA },
	{ "sf2_25.bin",    0x80000, 0x994bfa58, BRF_GRA },
	{ "sf2_27.bin",    0x80000, 0x3e66ad9d, BRF_GRA },
	{ "sf2_24.bin",    0x80000, 0xc1befaa8, BRF_GRA },
	{ "sf2_26.bin",    0x80000, 0x0627c831, BRF_GRA },

// 20
// z80 program
	{ "sf2_09.bin",    0x10000, 0xa4823a1b, BRF_SND },
// adpcm samples
	{ "sf2_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "sf2_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2ua) STD_ROM_FN(Sf2ua)

struct BurnDriver BurnDrvCpsSf2ua = {
	"sf2ua", "sf2", NULL, "1991",
	"Street Fighter II - the world warrior (910206 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2uaRomInfo,Sf2uaRomName,DrvInputInfo, sf2DIPInfo,
	Drv17Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================================================
//Street Fighter II - the world warrior (USA Rev. B)
//==================================================


static struct BurnRomInfo Sf2ubRomDesc[] = {
// 0
	{ "sf2_30a.bin",   0x20000, 0x57bd7051, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2u.37b",      0x20000, 0x4a54d479, BRF_ESS | BRF_PRG },
	{ "sf2_31a.bin",   0x20000, 0xa673143d, BRF_ESS | BRF_PRG },
	{ "sf2_38a.bin",   0x20000, 0x4c2ccef7, BRF_ESS | BRF_PRG },
	{ "sf2_28a.bin",   0x20000, 0x4009955e, BRF_ESS | BRF_PRG },
	{ "sf2_35a.bin",   0x20000, 0x8c1f3994, BRF_ESS | BRF_PRG },
	{ "sf2_29a.bin",   0x20000, 0xbb4af315, BRF_ESS | BRF_PRG },
	{ "sf2_36a.bin",   0x20000, 0xc02a13eb, BRF_ESS | BRF_PRG },

// 8
	{ "sf2_06.bin",    0x80000, 0x22c9cc8e, BRF_GRA },
	{ "sf2_08.bin",    0x80000, 0x57213be8, BRF_GRA },
	{ "sf2_05.bin",    0x80000, 0xba529b4f, BRF_GRA },
	{ "sf2_07.bin",    0x80000, 0x4b1b33a8, BRF_GRA },
	{ "sf2_15.bin",    0x80000, 0x2c7e2229, BRF_GRA },
	{ "sf2_17.bin",    0x80000, 0xb5548f17, BRF_GRA },
	{ "sf2_14.bin",    0x80000, 0x14b84312, BRF_GRA },
	{ "sf2_16.bin",    0x80000, 0x5e9cd89a, BRF_GRA },
	{ "sf2_25.bin",    0x80000, 0x994bfa58, BRF_GRA },
	{ "sf2_27.bin",    0x80000, 0x3e66ad9d, BRF_GRA },
	{ "sf2_24.bin",    0x80000, 0xc1befaa8, BRF_GRA },
	{ "sf2_26.bin",    0x80000, 0x0627c831, BRF_GRA },

// 20
// z80 program
	{ "sf2_09.bin",    0x10000, 0xa4823a1b, BRF_SND },
// adpcm samples
	{ "sf2_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "sf2_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2ub) STD_ROM_FN(Sf2ub)

struct BurnDriver BurnDrvCpsSf2ub = {
	"sf2ub", "sf2", NULL, "1991",
	"Street Fighter II - the world warrior (910214 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2ubRomInfo,Sf2ubRomName,DrvInputInfo, sf2DIPInfo,
	Drv17Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================================================
//Street Fighter II - the world warrior (USA Rev. D)
//==================================================


static struct BurnRomInfo Sf2udRomDesc[] = {
// 0
	{ "sf2u.30d",      0x20000, 0x4bb2657c, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2u.37d",      0x20000, 0xb33b42f2, BRF_ESS | BRF_PRG },
	{ "sf2u.31d",      0x20000, 0xd57b67d7, BRF_ESS | BRF_PRG },
	{ "sf2u.38d",      0x20000, 0x9c8916ef, BRF_ESS | BRF_PRG },
	{ "sf2u.28d",      0x20000, 0x175819d1, BRF_ESS | BRF_PRG },
	{ "sf2u.35d",      0x20000, 0x82060da4, BRF_ESS | BRF_PRG },
	{ "sf2_29a.bin",   0x20000, 0xbb4af315, BRF_ESS | BRF_PRG },
	{ "sf2_36a.bin",   0x20000, 0xc02a13eb, BRF_ESS | BRF_PRG },

// 8
	{ "sf2_06.bin",    0x80000, 0x22c9cc8e, BRF_GRA },
	{ "sf2_08.bin",    0x80000, 0x57213be8, BRF_GRA },
	{ "sf2_05.bin",    0x80000, 0xba529b4f, BRF_GRA },
	{ "sf2_07.bin",    0x80000, 0x4b1b33a8, BRF_GRA },
	{ "sf2_15.bin",    0x80000, 0x2c7e2229, BRF_GRA },
	{ "sf2_17.bin",    0x80000, 0xb5548f17, BRF_GRA },
	{ "sf2_14.bin",    0x80000, 0x14b84312, BRF_GRA },
	{ "sf2_16.bin",    0x80000, 0x5e9cd89a, BRF_GRA },
	{ "sf2_25.bin",    0x80000, 0x994bfa58, BRF_GRA },
	{ "sf2_27.bin",    0x80000, 0x3e66ad9d, BRF_GRA },
	{ "sf2_24.bin",    0x80000, 0xc1befaa8, BRF_GRA },
	{ "sf2_26.bin",    0x80000, 0x0627c831, BRF_GRA },

// 20
// z80 program
	{ "sf2_09.bin",    0x10000, 0xa4823a1b, BRF_SND },
// adpcm samples
	{ "sf2_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "sf2_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2ud) STD_ROM_FN(Sf2ud)

struct BurnDriver BurnDrvCpsSf2ud = {
	"sf2ud", "sf2", NULL, "1991",
	"Street Fighter II - the world warrior (910318 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2udRomInfo,Sf2udRomName,DrvInputInfo, sf2DIPInfo,
	Drv05Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================================================
//Street Fighter II - the world warrior (USA Rev. E)
//==================================================


static struct BurnRomInfo Sf2ueRomDesc[] = {
// 0
	{ "sf2u.30e",      0x20000, 0xf37cd088, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2u.37e",      0x20000, 0x6c61a513, BRF_ESS | BRF_PRG },
	{ "sf2u.31e",      0x20000, 0x7c4771b4, BRF_ESS | BRF_PRG },
	{ "sf2u.38e",      0x20000, 0xa4bd0cd9, BRF_ESS | BRF_PRG },
	{ "sf2u.28e",      0x20000, 0xe3b95625, BRF_ESS | BRF_PRG },
	{ "sf2u.35e",      0x20000, 0x3648769a, BRF_ESS | BRF_PRG },
	{ "sf2_29a.bin",   0x20000, 0xbb4af315, BRF_ESS | BRF_PRG },
	{ "sf2_36a.bin",   0x20000, 0xc02a13eb, BRF_ESS | BRF_PRG },

// 8
	{ "sf2_06.bin",    0x80000, 0x22c9cc8e, BRF_GRA },
	{ "sf2_08.bin",    0x80000, 0x57213be8, BRF_GRA },
	{ "sf2_05.bin",    0x80000, 0xba529b4f, BRF_GRA },
	{ "sf2_07.bin",    0x80000, 0x4b1b33a8, BRF_GRA },
	{ "sf2_15.bin",    0x80000, 0x2c7e2229, BRF_GRA },
	{ "sf2_17.bin",    0x80000, 0xb5548f17, BRF_GRA },
	{ "sf2_14.bin",    0x80000, 0x14b84312, BRF_GRA },
	{ "sf2_16.bin",    0x80000, 0x5e9cd89a, BRF_GRA },
	{ "sf2_25.bin",    0x80000, 0x994bfa58, BRF_GRA },
	{ "sf2_27.bin",    0x80000, 0x3e66ad9d, BRF_GRA },
	{ "sf2_24.bin",    0x80000, 0xc1befaa8, BRF_GRA },
	{ "sf2_26.bin",    0x80000, 0x0627c831, BRF_GRA },

// 20
// z80 program
	{ "sf2_09.bin",    0x10000, 0xa4823a1b, BRF_SND },
// adpcm samples
	{ "sf2_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "sf2_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2ue) STD_ROM_FN(Sf2ue)

struct BurnDriver BurnDrvCpsSf2ue = {
	"sf2ue", "sf2", NULL, "1991",
	"Street Fighter II - the world warrior (910228 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2ueRomInfo,Sf2ueRomName,Sf2ueInputInfo, sf2DIPInfo,
	Drv18Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================================================
//Street Fighter II - the world warrior (USA Rev. F)
//==================================================


static struct BurnRomInfo Sf2ufRomDesc[] = {
// 0
	{ "sf2e.30g",      0x20000, 0xfe39ee33, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2u.37f",      0x20000, 0x169e7388, BRF_ESS | BRF_PRG },
	{ "sf2e.31g",      0x20000, 0x69a0a301, BRF_ESS | BRF_PRG },
	{ "sf2u.38f",      0x20000, 0x1510e4e2, BRF_ESS | BRF_PRG },
	{ "sf2u.28f",      0x20000, 0xacd8175b, BRF_ESS | BRF_PRG },
	{ "sf2u.35f",      0x20000, 0xc0a80bd1, BRF_ESS | BRF_PRG },
	{ "sf2_29a.bin",   0x20000, 0xbb4af315, BRF_ESS | BRF_PRG },
	{ "sf2_36a.bin",   0x20000, 0xc02a13eb, BRF_ESS | BRF_PRG },

// 8
	{ "sf2_06.bin",    0x80000, 0x22c9cc8e, BRF_GRA },
	{ "sf2_08.bin",    0x80000, 0x57213be8, BRF_GRA },
	{ "sf2_05.bin",    0x80000, 0xba529b4f, BRF_GRA },
	{ "sf2_07.bin",    0x80000, 0x4b1b33a8, BRF_GRA },
	{ "sf2_15.bin",    0x80000, 0x2c7e2229, BRF_GRA },
	{ "sf2_17.bin",    0x80000, 0xb5548f17, BRF_GRA },
	{ "sf2_14.bin",    0x80000, 0x14b84312, BRF_GRA },
	{ "sf2_16.bin",    0x80000, 0x5e9cd89a, BRF_GRA },
	{ "sf2_25.bin",    0x80000, 0x994bfa58, BRF_GRA },
	{ "sf2_27.bin",    0x80000, 0x3e66ad9d, BRF_GRA },
	{ "sf2_24.bin",    0x80000, 0xc1befaa8, BRF_GRA },
	{ "sf2_26.bin",    0x80000, 0x0627c831, BRF_GRA },

// 20
// z80 program
	{ "sf2_09.bin",    0x10000, 0xa4823a1b, BRF_SND },
// adpcm samples
	{ "sf2_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "sf2_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2uf) STD_ROM_FN(Sf2uf)

struct BurnDriver BurnDrvCpsSf2uf = {
	"sf2uf", "sf2", NULL, "1991",
	"Street Fighter II - the world warrior (910411 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2ufRomInfo,Sf2ufRomName,DrvInputInfo, sf2DIPInfo,
	Drv15Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================================================
//Street Fighter II - the world warrior (USA Rev. I)
//==================================================


static struct BurnRomInfo Sf2uiRomDesc[] = {
// 0
	{ "sf2e.30g",      0x20000, 0xfe39ee33, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2u.37i",      0x20000, 0x9df707dd, BRF_ESS | BRF_PRG },
	{ "sf2e.31g",      0x20000, 0x69a0a301, BRF_ESS | BRF_PRG },
	{ "sf2u.38i",      0x20000, 0x4cb46daf, BRF_ESS | BRF_PRG },
	{ "sf2u.28i",      0x20000, 0x1580be4c, BRF_ESS | BRF_PRG },
	{ "sf2u.35i",      0x20000, 0x1468d185, BRF_ESS | BRF_PRG },
	{ "sf2_29a.bin",   0x20000, 0xbb4af315, BRF_ESS | BRF_PRG },
	{ "sf2_36a.bin",   0x20000, 0xc02a13eb, BRF_ESS | BRF_PRG },

// 8
	{ "sf2_06.bin",    0x80000, 0x22c9cc8e, BRF_GRA },
	{ "sf2_08.bin",    0x80000, 0x57213be8, BRF_GRA },
	{ "sf2_05.bin",    0x80000, 0xba529b4f, BRF_GRA },
	{ "sf2_07.bin",    0x80000, 0x4b1b33a8, BRF_GRA },
	{ "sf2_15.bin",    0x80000, 0x2c7e2229, BRF_GRA },
	{ "sf2_17.bin",    0x80000, 0xb5548f17, BRF_GRA },
	{ "sf2_14.bin",    0x80000, 0x14b84312, BRF_GRA },
	{ "sf2_16.bin",    0x80000, 0x5e9cd89a, BRF_GRA },
	{ "sf2_25.bin",    0x80000, 0x994bfa58, BRF_GRA },
	{ "sf2_27.bin",    0x80000, 0x3e66ad9d, BRF_GRA },
	{ "sf2_24.bin",    0x80000, 0xc1befaa8, BRF_GRA },
	{ "sf2_26.bin",    0x80000, 0x0627c831, BRF_GRA },

// 20
// z80 program
	{ "sf2_09.bin",    0x10000, 0xa4823a1b, BRF_SND },
// adpcm samples
	{ "sf2_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "sf2_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2ui) STD_ROM_FN(Sf2ui)

struct BurnDriver BurnDrvCpsSf2ui = {
	"sf2ui", "sf2", NULL, "1991",
	"Street Fighter II - the world warrior (910522 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2uiRomInfo,Sf2uiRomName,DrvInputInfo, sf2DIPInfo,
	Drv14Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

static struct BurnRomInfo Sf2ukRomDesc[] = {
// 0
	{ "sf2u.30k",      0x20000, 0x8f66076c, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2u.37k",      0x20000, 0x4e1f6a83, BRF_ESS | BRF_PRG },
	{ "sf2u.31k",      0x20000, 0xf9f89f60, BRF_ESS | BRF_PRG },
	{ "sf2u.38k",      0x20000, 0x6ce0a85a, BRF_ESS | BRF_PRG },
	{ "sf2u.28k",      0x20000, 0x8e958f31, BRF_ESS | BRF_PRG },
	{ "sf2u.35k",      0x20000, 0xfce76fad, BRF_ESS | BRF_PRG },
	{ "sf2_29a.bin",   0x20000, 0xbb4af315, BRF_ESS | BRF_PRG },
	{ "sf2_36a.bin",   0x20000, 0xc02a13eb, BRF_ESS | BRF_PRG },

// 8
	{ "sf2_06.bin",    0x80000, 0x22c9cc8e, BRF_GRA },
	{ "sf2_08.bin",    0x80000, 0x57213be8, BRF_GRA },
	{ "sf2_05.bin",    0x80000, 0xba529b4f, BRF_GRA },
	{ "sf2_07.bin",    0x80000, 0x4b1b33a8, BRF_GRA },
	{ "sf2_15.bin",    0x80000, 0x2c7e2229, BRF_GRA },
	{ "sf2_17.bin",    0x80000, 0xb5548f17, BRF_GRA },
	{ "sf2_14.bin",    0x80000, 0x14b84312, BRF_GRA },
	{ "sf2_16.bin",    0x80000, 0x5e9cd89a, BRF_GRA },
	{ "sf2_25.bin",    0x80000, 0x994bfa58, BRF_GRA },
	{ "sf2_27.bin",    0x80000, 0x3e66ad9d, BRF_GRA },
	{ "sf2_24.bin",    0x80000, 0xc1befaa8, BRF_GRA },
	{ "sf2_26.bin",    0x80000, 0x0627c831, BRF_GRA },

// 20
// z80 program
	{ "sf2_09.bin",    0x10000, 0xa4823a1b, BRF_SND },
// adpcm samples
	{ "sf2_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "sf2_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2uk) STD_ROM_FN(Sf2uk)

struct BurnDriver BurnDrvCpsSf2uk = {
	"sf2uk", "sf2", NULL, "1991",
	"Street Fighter II - the world warrior (911101 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2ukRomInfo,Sf2ukRomName,DrvInputInfo, sf2DIPInfo,
	Drv17Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=============================================
//Street Fighter II - the world warrior (Japan)
//=============================================


static struct BurnRomInfo Sf2jRomDesc[] = {
// 0
	{ "sf2j30.bin",    0x20000, 0x79022b31, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2j37.bin",    0x20000, 0x516776ec, BRF_ESS | BRF_PRG },
	{ "sf2j31.bin",    0x20000, 0xfe15cb39, BRF_ESS | BRF_PRG },
	{ "sf2j38.bin",    0x20000, 0x38614d70, BRF_ESS | BRF_PRG },
	{ "sf2j28.bin",    0x20000, 0xd283187a, BRF_ESS | BRF_PRG },
	{ "sf2j35.bin",    0x20000, 0xd28158e4, BRF_ESS | BRF_PRG },
	{ "sf2_29a.bin",   0x20000, 0xbb4af315, BRF_ESS | BRF_PRG },
	{ "sf2_36a.bin",   0x20000, 0xc02a13eb, BRF_ESS | BRF_PRG },

// 8
	{ "sf2_06.bin",    0x80000, 0x22c9cc8e, BRF_GRA },
	{ "sf2_08.bin",    0x80000, 0x57213be8, BRF_GRA },
	{ "sf2_05.bin",    0x80000, 0xba529b4f, BRF_GRA },
	{ "sf2_07.bin",    0x80000, 0x4b1b33a8, BRF_GRA },
	{ "sf2_15.bin",    0x80000, 0x2c7e2229, BRF_GRA },
	{ "sf2_17.bin",    0x80000, 0xb5548f17, BRF_GRA },
	{ "sf2_14.bin",    0x80000, 0x14b84312, BRF_GRA },
	{ "sf2_16.bin",    0x80000, 0x5e9cd89a, BRF_GRA },
	{ "sf2_25.bin",    0x80000, 0x994bfa58, BRF_GRA },
	{ "sf2_27.bin",    0x80000, 0x3e66ad9d, BRF_GRA },
	{ "sf2_24.bin",    0x80000, 0xc1befaa8, BRF_GRA },
	{ "sf2_26.bin",    0x80000, 0x0627c831, BRF_GRA },

// 20
// z80 program
	{ "sf2_09.bin",    0x10000, 0xa4823a1b, BRF_SND },
// adpcm samples
	{ "sf2_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "sf2_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2j) STD_ROM_FN(Sf2j)

struct BurnDriver BurnDrvCpsSf2j = {
	"sf2j", "sf2", NULL, "1991",
	"Street Fighter II - the world warrior (911210 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2jRomInfo,Sf2jRomName,DrvInputInfo, sf2jDIPInfo,
	Drv13Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//====================================================
//Street Fighter II - the world warrior (Japan Rev. A)
//====================================================


static struct BurnRomInfo Sf2jaRomDesc[] = {
// 0
	{ "sf2_30a.bin",   0x20000, 0x57bd7051, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2j_37a.bin",  0x20000, 0x1e1f6844, BRF_ESS | BRF_PRG },
	{ "sf2_31a.bin",   0x20000, 0xa673143d, BRF_ESS | BRF_PRG },
	{ "sf2_38a.bin",   0x20000, 0x4c2ccef7, BRF_ESS | BRF_PRG },
	{ "sf2_28a.bin",   0x20000, 0x4009955e, BRF_ESS | BRF_PRG },
	{ "sf2_35a.bin",   0x20000, 0x8c1f3994, BRF_ESS | BRF_PRG },
	{ "sf2_29a.bin",   0x20000, 0xbb4af315, BRF_ESS | BRF_PRG },
	{ "sf2_36a.bin",   0x20000, 0xc02a13eb, BRF_ESS | BRF_PRG },

// 8
	{ "sf2_06.bin",    0x80000, 0x22c9cc8e, BRF_GRA },
	{ "sf2_08.bin",    0x80000, 0x57213be8, BRF_GRA },
	{ "sf2_05.bin",    0x80000, 0xba529b4f, BRF_GRA },
	{ "sf2_07.bin",    0x80000, 0x4b1b33a8, BRF_GRA },
	{ "sf2_15.bin",    0x80000, 0x2c7e2229, BRF_GRA },
	{ "sf2_17.bin",    0x80000, 0xb5548f17, BRF_GRA },
	{ "sf2_14.bin",    0x80000, 0x14b84312, BRF_GRA },
	{ "sf2_16.bin",    0x80000, 0x5e9cd89a, BRF_GRA },
	{ "sf2_25.bin",    0x80000, 0x994bfa58, BRF_GRA },
	{ "sf2_27.bin",    0x80000, 0x3e66ad9d, BRF_GRA },
	{ "sf2_24.bin",    0x80000, 0xc1befaa8, BRF_GRA },
	{ "sf2_26.bin",    0x80000, 0x0627c831, BRF_GRA },

// 20
// z80 program
	{ "sf2_09.bin",    0x10000, 0xa4823a1b, BRF_SND },
// adpcm samples
	{ "sf2_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "sf2_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2ja) STD_ROM_FN(Sf2ja)

struct BurnDriver BurnDrvCpsSf2ja = {
	"sf2ja", "sf2", NULL, "1991",
	"Street Fighter II - the world warrior (910214 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2jaRomInfo,Sf2jaRomName,DrvInputInfo, sf2jDIPInfo,
	Drv17Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//====================================================
//Street Fighter II - the world warrior (Japan Rev. C)
//====================================================


static struct BurnRomInfo Sf2jcRomDesc[] = {
// 0
	{ "sf2_30c.bin",   0x20000, 0x8add35ec, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "sf2j_37c.bin",  0x20000, 0x0d74a256, BRF_ESS | BRF_PRG },
	{ "sf2_31c.bin",   0x20000, 0xc4fff4a9, BRF_ESS | BRF_PRG },
	{ "sf2_38c.bin",   0x20000, 0x8210fc0e, BRF_ESS | BRF_PRG },
	{ "sf2_28c.bin",   0x20000, 0x6eddd5e8, BRF_ESS | BRF_PRG },
	{ "sf2_35c.bin",   0x20000, 0x6bcb404c, BRF_ESS | BRF_PRG },
	{ "sf2_29a.bin",   0x20000, 0xbb4af315, BRF_ESS | BRF_PRG },
	{ "sf2_36a.bin",   0x20000, 0xc02a13eb, BRF_ESS | BRF_PRG },

// 8
	{ "sf2_06.bin",    0x80000, 0x22c9cc8e, BRF_GRA },
	{ "sf2_08.bin",    0x80000, 0x57213be8, BRF_GRA },
	{ "sf2_05.bin",    0x80000, 0xba529b4f, BRF_GRA },
	{ "sf2_07.bin",    0x80000, 0x4b1b33a8, BRF_GRA },
	{ "sf2_15.bin",    0x80000, 0x2c7e2229, BRF_GRA },
	{ "sf2_17.bin",    0x80000, 0xb5548f17, BRF_GRA },
	{ "sf2_14.bin",    0x80000, 0x14b84312, BRF_GRA },
	{ "sf2_16.bin",    0x80000, 0x5e9cd89a, BRF_GRA },
	{ "sf2_25.bin",    0x80000, 0x994bfa58, BRF_GRA },
	{ "sf2_27.bin",    0x80000, 0x3e66ad9d, BRF_GRA },
	{ "sf2_24.bin",    0x80000, 0xc1befaa8, BRF_GRA },
	{ "sf2_26.bin",    0x80000, 0x0627c831, BRF_GRA },

// 20
// z80 program
	{ "sf2_09.bin",    0x10000, 0xa4823a1b, BRF_SND },
// adpcm samples
	{ "sf2_18.bin",    0x20000, 0x7f162009, BRF_SND },
	{ "sf2_19.bin",    0x20000, 0xbeade53f, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Sf2jc) STD_ROM_FN(Sf2jc)

struct BurnDriver BurnDrvCpsSf2jc = {
	"sf2jc", "sf2", NULL, "1991",
	"Street Fighter II - the world warrior (910306 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,Sf2jcRomInfo,Sf2jcRomName,DrvInputInfo, sf2jDIPInfo,
	Drv12Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
