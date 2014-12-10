// Ghouls and Ghosts

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp018+0, "p1 coin"},
  {"P1 Start"      , BIT_DIGITAL, CpsInp018+4, "p1 start"},
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Fire"       , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Jump"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Fire"       , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Jump"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},

  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"},
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"       },
  {"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"       },
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"       },
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo ghoulsDIPList[]=
{
	// Defaults
	{0x13, 0xff, 0xff, 0x00, NULL                     },
	{0x14, 0xff, 0xff, 0x00, NULL                     },
	{0x15, 0xff, 0xff, 0x00, NULL                     },

	// Dip A
	{0   , 0xfe, 0   , 8   , "Coin 1"                 },
	{0x13, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x13, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x13, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x13, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x13, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x13, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x13, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x13, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 8   , "Coin 2"                 },
	{0x13, 0x01, 0x38, 0x38, "4 Coins 1 Credit"       },
	{0x13, 0x01, 0x38, 0x30, "3 Coins 1 Credit"       },
	{0x13, 0x01, 0x38, 0x28, "2 Coins 1 Credit"       },
	{0x13, 0x01, 0x38, 0x00, "1 Coin 1 Credit"        },
	{0x13, 0x01, 0x38, 0x08, "1 Coin 2 Credits"       },
	{0x13, 0x01, 0x38, 0x10, "1 Coin 3 Credits"       },
	{0x13, 0x01, 0x38, 0x18, "1 Coin 4 Credits"       },
	{0x13, 0x01, 0x38, 0x20, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 3   , "Cabinet"                },
	{0x13, 0x01, 0xc0, 0x00, "Upright 1 Player"       },
	{0x13, 0x01, 0xc0, 0x40, "Upright 2 Players"      },
	{0x13, 0x01, 0xc0, 0x80, "Cocktail"               },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Difficulty"             },
	{0x14, 0x01, 0x07, 0x03, "Easier"              },
	{0x14, 0x01, 0x07, 0x02, "Very Easy"                 },
	{0x14, 0x01, 0x07, 0x01, "Easy"                 },
	{0x14, 0x01, 0x07, 0x00, "Normal"                 },
	{0x14, 0x01, 0x07, 0x04, "Difficult"            },
	{0x14, 0x01, 0x07, 0x05, "Hard"            },
	{0x14, 0x01, 0x07, 0x06, "Very Hard"            },
	{0x14, 0x01, 0x07, 0x07, "Hardest"         },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x14, 0x01, 0x08, 0x00, "Off"                    },
//	{0x14, 0x01, 0x08, 0x08, "On"                     },

	{0   , 0xfe, 0   , 4   , "Bonus Life"             },
	{0x14, 0x01, 0x30, 0x10, "10k, 30k and every 30k" },
	{0x14, 0x01, 0x30, 0x20, "20k, 50k and every 70k" },
	{0x14, 0x01, 0x30, 0x00, "30k, 60k and every 70k" },
	{0x14, 0x01, 0x30, 0x30, "40k, 70k and every 80k" },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x14, 0x01, 0x40, 0x00, "Off"                    },
//	{0x14, 0x01, 0x40, 0x40, "On"                     },

	{0   , 0xfe, 0   , 2   , "Freeze"                 },
	{0x14, 0x01, 0x80, 0x00, "Off"                    },
	{0x14, 0x01, 0x80, 0x80, "On"                     },

	// Dip C
	{0   , 0xfe, 0   , 4   , "Lives"                  },
	{0x15, 0x01, 0x03, 0x00, "3"                      },
	{0x15, 0x01, 0x03, 0x01, "4"                      },
	{0x15, 0x01, 0x03, 0x02, "5"                      },
	{0x15, 0x01, 0x03, 0x03, "6"                      },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x15, 0x01, 0x04, 0x00, "Off"                    },
//	{0x15, 0x01, 0x04, 0x04, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x15, 0x01, 0x08, 0x00, "Off"                    },
//	{0x15, 0x01, 0x08, 0x08, "On"                     },

	{0   , 0xfe, 0   , 2   , "Flip"                   },
	{0x15, 0x01, 0x10, 0x00, "Off"                    },
	{0x15, 0x01, 0x10, 0x10, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sound"             },
	{0x15, 0x01, 0x20, 0x20, "Off"                    },
	{0x15, 0x01, 0x20, 0x00, "On"                     },

	{0   , 0xfe, 0   , 2   , "Continue"               },
	{0x15, 0x01, 0x40, 0x40, "Off"                    },
	{0x15, 0x01, 0x40, 0x00, "On"                     },
};

STDDIPINFO(ghouls);


static int DrvInit()
{
  int nRet=0;
  Cps=1; Ghouls=1;
  nCpsRomLen=  0x100000;
  nCpsGfxLen=  0x300000;
  nCpsZRomLen= 0x010000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000001,0,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x000000,1,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040001,2,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040000,3,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,4,1); if (nRet!=0) return 1;
  BurnByteswap(CpsRom+0x080000,0x080000);

  // Load graphics roms
  CpsLoadTiles    (CpsGfx         ,  5);
  CpsLoadTilesByte(CpsGfx+0x200000,  9);
  CpsLoadTilesByte(CpsGfx+0x280000, 17);

  MaskAddr[0]=0x68;
  MaskAddr[1]=0x6a;
  MaskAddr[2]=0x6c;
  MaskAddr[3]=0x6e;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,25,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

static int DrvExit()
{

  CpsRunExit();
  CpsExit();
  nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0; Ghouls=0;
  return 0;
}


///////
// Drivers
/////////////////////
// Ghouls 'N Ghosts - Driver

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo GhoulsRomDesc[] = {
	{ "ghl29.bin",     0x20000, 0x166a58a2, BRF_ESS | BRF_PRG }, //  0 even 68000 code
	{ "ghl30.bin",     0x20000, 0x7ac8407a, BRF_ESS | BRF_PRG }, //  1 odd
	{ "ghl27.bin",     0x20000, 0xf734b2be, BRF_ESS | BRF_PRG }, //  2 even
	{ "ghl28.bin",     0x20000, 0x03d3e714, BRF_ESS | BRF_PRG }, //  3 odd
	{ "ghl17.bin",     0x80000, 0x3ea1b0f2, BRF_ESS | BRF_PRG }, //  4 both

  // graphics:
  // 5
	{ "ghl5.bin",      0x80000, 0x0ba9c0b0, BRF_GRA },
	{ "ghl7.bin",      0x80000, 0x5d760ab9, BRF_GRA },
	{ "ghl6.bin",      0x80000, 0x4ba90b59, BRF_GRA },
	{ "ghl8.bin",      0x80000, 0x4bdee9de, BRF_GRA },

  // 9
	{ "ghl09.bin",     0x10000, 0xae24bb19, BRF_GRA },
	{ "ghl18.bin",     0x10000, 0xd34e271a, BRF_GRA },
	{ "ghl13.bin",     0x10000, 0x3f70dd37, BRF_GRA },
	{ "ghl22.bin",     0x10000, 0x7e69e2e6, BRF_GRA },
	{ "ghl11.bin",     0x10000, 0x37c9b6c6, BRF_GRA },
	{ "ghl20.bin",     0x10000, 0x2f1345b4, BRF_GRA },
	{ "ghl15.bin",     0x10000, 0x3c2a212a, BRF_GRA },
	{ "ghl24.bin",     0x10000, 0x889aac05, BRF_GRA },
	{ "ghl10.bin",     0x10000, 0xbcc0f28c, BRF_GRA },
	{ "ghl19.bin",     0x10000, 0x2a40166a, BRF_GRA },
	{ "ghl14.bin",     0x10000, 0x20f85c03, BRF_GRA },
	{ "ghl23.bin",     0x10000, 0x8426144b, BRF_GRA },
	{ "ghl12.bin",     0x10000, 0xda088d61, BRF_GRA },
	{ "ghl21.bin",     0x10000, 0x17e11df0, BRF_GRA },
	{ "ghl16.bin",     0x10000, 0xf187ba1c, BRF_GRA },
	{ "ghl25.bin",     0x10000, 0x29f79c78, BRF_GRA },

  // 25
	{ "ghl26.bin",     0x10000, 0x3692f6e5, BRF_SND },
};


STD_ROM_PICK(Ghouls); STD_ROM_FN(Ghouls);

struct BurnDriver BurnDrvCpsGhouls = {
	"ghouls", NULL, NULL, "1988",
	"Ghouls'n Ghosts (World)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
	NULL,GhoulsRomInfo,GhoulsRomName,DrvInputInfo, ghoulsDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};


// Ghouls'N Ghosts USA - Driver by Mike_Haggar_99@hotmail.com

// Rom information
static struct BurnRomInfo GhoulsuRomDesc[] = {
	{ "dmu29",         0x20000, 0x334d85b2, BRF_ESS | BRF_PRG }, //  0 even 68000 code
	{ "dmu30",         0x20000, 0xcee8ceb5, BRF_ESS | BRF_PRG }, //  1 odd
	{ "dmu27",         0x20000, 0x4a524140, BRF_ESS | BRF_PRG }, //  2 even
	{ "dmu28",         0x20000, 0x94aae205, BRF_ESS | BRF_PRG }, //  3 odd
	{ "ghl17.bin",     0x80000, 0x3ea1b0f2, BRF_ESS | BRF_PRG }, //  4 both

  // graphics:
  // 5
	{ "ghl5.bin",      0x80000, 0x0ba9c0b0, BRF_GRA },
	{ "ghl7.bin",      0x80000, 0x5d760ab9, BRF_GRA },
	{ "ghl6.bin",      0x80000, 0x4ba90b59, BRF_GRA },
	{ "ghl8.bin",      0x80000, 0x4bdee9de, BRF_GRA },

  // 9
	{ "ghl09.bin",     0x10000, 0xae24bb19, BRF_GRA },
	{ "ghl18.bin",     0x10000, 0xd34e271a, BRF_GRA },
	{ "ghl13.bin",     0x10000, 0x3f70dd37, BRF_GRA },
	{ "ghl22.bin",     0x10000, 0x7e69e2e6, BRF_GRA },
	{ "ghl11.bin",     0x10000, 0x37c9b6c6, BRF_GRA },
	{ "ghl20.bin",     0x10000, 0x2f1345b4, BRF_GRA },
	{ "ghl15.bin",     0x10000, 0x3c2a212a, BRF_GRA },
	{ "ghl24.bin",     0x10000, 0x889aac05, BRF_GRA },
	{ "ghl10.bin",     0x10000, 0xbcc0f28c, BRF_GRA },
	{ "ghl19.bin",     0x10000, 0x2a40166a, BRF_GRA },
	{ "ghl14.bin",     0x10000, 0x20f85c03, BRF_GRA },
	{ "ghl23.bin",     0x10000, 0x8426144b, BRF_GRA },
	{ "ghl12.bin",     0x10000, 0xda088d61, BRF_GRA },
	{ "ghl21.bin",     0x10000, 0x17e11df0, BRF_GRA },
	{ "ghl16.bin",     0x10000, 0xf187ba1c, BRF_GRA },
	{ "ghl25.bin",     0x10000, 0x29f79c78, BRF_GRA },

  // 25
	{ "ghl26.bin",     0x10000, 0x3692f6e5, BRF_SND },
};


STD_ROM_PICK(Ghoulsu); STD_ROM_FN(Ghoulsu);
struct BurnDriver BurnDrvCpsGhoulsu = {
	"ghoulsu", "ghouls", NULL, "1988",
	"Ghouls'n Ghosts (US)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,GhoulsuRomInfo,GhoulsuRomName,DrvInputInfo, ghoulsDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

/////////////////////////////
// Dai Makai-Mura (Ghouls'N Ghosts) Japan - Driver by Mike_Haggar_99@hotmail.com

// Rom information
static struct BurnRomInfo daimakaiRomDesc[] = {
	{ "dmj_38.bin",    0x20000, 0x82fd1798, BRF_ESS | BRF_PRG }, //  0 even 68000 code
	{ "dmj_39.bin",    0x20000, 0x35366ccc, BRF_ESS | BRF_PRG }, //  1 odd
	{ "dmj_40.bin",    0x20000, 0xa17c170a, BRF_ESS | BRF_PRG }, //  2 even
	{ "dmj_41.bin",    0x20000, 0x6af0b391, BRF_ESS | BRF_PRG }, //  3 odd
	{ "ghl17.bin",     0x80000, 0x3ea1b0f2, BRF_ESS | BRF_PRG }, //  4 both

  // graphics:
  // 5
	{ "ghl5.bin",      0x80000, 0x0ba9c0b0, BRF_GRA },
	{ "ghl7.bin",      0x80000, 0x5d760ab9, BRF_GRA },
	{ "ghl6.bin",      0x80000, 0x4ba90b59, BRF_GRA },
	{ "ghl8.bin",      0x80000, 0x4bdee9de, BRF_GRA },

  // 9
	{ "ghl09.bin",     0x10000, 0xae24bb19, BRF_GRA },
	{ "ghl18.bin",     0x10000, 0xd34e271a, BRF_GRA },
	{ "ghl13.bin",     0x10000, 0x3f70dd37, BRF_GRA },
	{ "ghl22.bin",     0x10000, 0x7e69e2e6, BRF_GRA },
	{ "ghl11.bin",     0x10000, 0x37c9b6c6, BRF_GRA },
	{ "ghl20.bin",     0x10000, 0x2f1345b4, BRF_GRA },
	{ "ghl15.bin",     0x10000, 0x3c2a212a, BRF_GRA },
	{ "ghl24.bin",     0x10000, 0x889aac05, BRF_GRA },
	{ "ghl10.bin",     0x10000, 0xbcc0f28c, BRF_GRA },
	{ "ghl19.bin",     0x10000, 0x2a40166a, BRF_GRA },
	{ "ghl14.bin",     0x10000, 0x20f85c03, BRF_GRA },
	{ "ghl23.bin",     0x10000, 0x8426144b, BRF_GRA },
	{ "ghl12.bin",     0x10000, 0xda088d61, BRF_GRA },
	{ "ghl21.bin",     0x10000, 0x17e11df0, BRF_GRA },
	{ "ghl16.bin",     0x10000, 0xf187ba1c, BRF_GRA },
	{ "ghl25.bin",     0x10000, 0x29f79c78, BRF_GRA },

  // 25
	{ "ghl26.bin",     0x10000, 0x3692f6e5, BRF_SND },
};


STD_ROM_PICK(daimakai); STD_ROM_FN(daimakai);

struct BurnDriver BurnDrvCpsDaimakai = {
	"daimakai", "ghouls", NULL, "1988",
	"Dai Makai-Mura (Japan)\0", NULL, "Capcom", "CPS1",
	L"\u5927\u9B54\u754C\u6751 (Japan)\0Dai Makai-Mura (Japan)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,daimakaiRomInfo,daimakaiRomName,DrvInputInfo, ghoulsDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
