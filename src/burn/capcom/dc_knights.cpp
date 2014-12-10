// Knights of the Round

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

{"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"   },
{"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start"  },
{"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"     },
{"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"   },
{"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"   },
{"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"  },
{"P2 Attack"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1" },
{"P2 Jump"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2" },

{"P3 Coin"       , BIT_DIGITAL, CpsInp177+6, "p3 coin"   },
{"P3 Start"      , BIT_DIGITAL, CpsInp177+7, "p3 start"  },
{"P3 Up"         , BIT_DIGITAL, CpsInp177+3, "p3 up"     },
{"P3 Down"       , BIT_DIGITAL, CpsInp177+2, "p3 down"   },
{"P3 Left"       , BIT_DIGITAL, CpsInp177+1, "p3 left"   },
{"P3 Right"      , BIT_DIGITAL, CpsInp177+0, "p3 right"  },
{"P3 Attack"     , BIT_DIGITAL, CpsInp177+4, "p3 fire 1" },
{"P3 Jump"       , BIT_DIGITAL, CpsInp177+5, "p3 fire 2" },

{"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"     },
{"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"      },
{"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
{"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"},
{"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"},
{"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo knightsDIPList[]=
{
	// Defaults
	{0x1b, 0xff, 0xff, 0x00, NULL                },
	{0x1c, 0xff, 0xff, 0x00, NULL                },
	{0x1d, 0xff, 0xff, 0x00, NULL                },

	// Dip A
	{0   , 0xfe, 0   , 8   , "Coin"                   },
	{0x1b, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x1b, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x1b, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x1b, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x1b, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x1b, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x1b, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x1b, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x08, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x08, 0x08, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x10, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x10, 0x10, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x20, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 2   , "2C to Start, 1 to Cont" },
	{0x1b, 0x01, 0x40, 0x00, "Off"                    },
	{0x1b, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x80, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x80, 0x80, "On"                     },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Level 1"                },
	{0x1c, 0x01, 0x07, 0x02, "Easy 1"                 },
	{0x1c, 0x01, 0x07, 0x01, "Easy 2"                 },
	{0x1c, 0x01, 0x07, 0x00, "Easy 3"                 },
	{0x1c, 0x01, 0x07, 0x03, "Normal"                 },
	{0x1c, 0x01, 0x07, 0x04, "Difficult 1"            },
	{0x1c, 0x01, 0x07, 0x05, "Difficult 2"            },
	{0x1c, 0x01, 0x07, 0x06, "Difficult 3"            },
	{0x1c, 0x01, 0x07, 0x07, "Difficult 4"            },

	{0   , 0xfe, 0   , 8   , "Level 2"                },
	{0x1c, 0x01, 0x38, 0x28, "Easy 1"                 },
	{0x1c, 0x01, 0x38, 0x30, "Easy 2"                 },
	{0x1c, 0x01, 0x38, 0x38, "Easy 3"                 },
	{0x1c, 0x01, 0x38, 0x00, "Normal"                 },
	{0x1c, 0x01, 0x38, 0x08, "Difficult 1"            },
	{0x1c, 0x01, 0x38, 0x10, "Difficult 2"            },
	{0x1c, 0x01, 0x38, 0x18, "Difficult 3"            },
	{0x1c, 0x01, 0x38, 0x20, "Difficult 4"            },

	{0   , 0xfe, 0   , 2   , "Coin Shooter"           },
	{0x1c, 0x01, 0x40, 0x40, "1 Shooter"              },
	{0x1c, 0x01, 0x40, 0x00, "3 Shooter"              },

	{0   , 0xfe, 0   , 2   , "Play Type"              },
	{0x1c, 0x01, 0x80, 0x80, "2P"                     },
	{0x1c, 0x01, 0x80, 0x00, "3P"                     },

	// Dip C
	{0   , 0xfe, 0   , 4   , "Lives (varies by Diff)" },
	{0x1d, 0x01, 0x03, 0x03, "Least"                  },
	{0x1d, 0x01, 0x03, 0x00, "Less"                   },
	{0x1d, 0x01, 0x03, 0x01, "More"                   },
	{0x1d, 0x01, 0x03, 0x02, "Most"                   },

	{0   , 0xfe, 0   , 2   , "Free Play"              },
	{0x1d, 0x01, 0x04, 0x00, "Off"                    },
	{0x1d, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Freeze"                 },
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

STDDIPINFO(knights);


static int DrvInit()
{
   int nRet=0;
   Cps=1; Knights=1;
   nCpsRomLen =  0x100000;
   nCpsCodeLen=0;
   nCpsGfxLen =8*0x080000;
   nCpsZRomLen=  0x010000;
   nCpsAdLen  =2*0x020000;
   nRet=CpsInit(); if (nRet!=0) return 1;

   nRet=BurnLoadRom(CpsRom,0,1); if (nRet!=0) return 1;
   nRet=BurnLoadRom(CpsRom+0x080000,1,1); if (nRet!=0) return 1;

   CpsLoadTiles(CpsGfx+0x000000,2);
   CpsLoadTiles(CpsGfx+0x200000,6);

   nCpsLcReg=0x68;
   CpsLayEn[1]=0x20;
   CpsLayEn[2]=0x10;
   CpsLayEn[3]=0x02;

   CpsMProt[0]=0x46;
   CpsMProt[1]=0x44;
   CpsMProt[2]=0x42;
   CpsMProt[3]=0x40;

   MaskAddr[0]=0x66;
   MaskAddr[1]=0x64;
   MaskAddr[2]=0x62;
   MaskAddr[3]=0x60;

   nRet=BurnLoadRom(CpsZRom,10,1); //changed to 13

   nRet=BurnLoadRom(CpsAd        ,11,1); //changed to 14
   nRet=BurnLoadRom(CpsAd+0x20000,12,1); //changed to 15


   nRet=CpsRunInit();

   if (nRet!=0) return 1;

   return 0;
}

static int DrvExit()
{


   CpsRunExit();
   CpsExit();
   nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
   Cps=0; Knights=0;
   return 0;
}


// Knights of the Round ()

static struct BurnRomInfo KnightsRomDesc[] = {
	{ "kr_23e.rom",    0x80000, 0x1b3997eb, BRF_ESS | BRF_PRG },
	{ "kr_22.rom",     0x80000, 0xd0b671a9, BRF_ESS | BRF_PRG },

	{ "kr_gfx1.rom",   0x80000, 0x9e36c1a4, BRF_GRA },
	{ "kr_gfx3.rom",   0x80000, 0xc5832cae, BRF_GRA },
	{ "kr_gfx2.rom",   0x80000, 0xf095be2d, BRF_GRA },
	{ "kr_gfx4.rom",   0x80000, 0x179dfd96, BRF_GRA },
	{ "kr_gfx5.rom",   0x80000, 0x1f4298d2, BRF_GRA },
	{ "kr_gfx7.rom",   0x80000, 0x37fa8751, BRF_GRA },
	{ "kr_gfx6.rom",   0x80000, 0x0200bc3d, BRF_GRA },
	{ "kr_gfx8.rom",   0x80000, 0x0bb2b4e7, BRF_GRA },

	{ "kr_09.rom",     0x10000, 0x5e44d9ee, BRF_SND },

	{ "kr_18.rom",     0x20000, 0xda69d15f, BRF_SND },
	{ "kr_19.rom",     0x20000, 0xbfc654e9, BRF_SND },
};


STD_ROM_PICK(Knights) STD_ROM_FN(Knights)

struct BurnDriver BurnDrvCpsKnights = {
	"knights", NULL, NULL, "1991",
	"Knights of the Round (911127 etc)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,3,HARDWARE_CAPCOM_CPS1,
NULL,KnightsRomInfo,KnightsRomName,DrvInputInfo, knightsDIPInfo,
DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
&CpsRecalcPal,384,224,4,3
};

// Knights of the Round (USA)


static struct BurnRomInfo KnightsuRomDesc[] = {
	{ "kru23.rom",     0x80000, 0x252bc2ba, BRF_ESS | BRF_PRG },
	{ "kr_22.rom",     0x80000, 0xd0b671a9, BRF_ESS | BRF_PRG },

	{ "kr_gfx1.rom",   0x80000, 0x9e36c1a4, BRF_GRA },
	{ "kr_gfx3.rom",   0x80000, 0xc5832cae, BRF_GRA },
	{ "kr_gfx2.rom",   0x80000, 0xf095be2d, BRF_GRA },
	{ "kr_gfx4.rom",   0x80000, 0x179dfd96, BRF_GRA },
	{ "kr_gfx5.rom",   0x80000, 0x1f4298d2, BRF_GRA },
	{ "kr_gfx7.rom",   0x80000, 0x37fa8751, BRF_GRA },
	{ "kr_gfx6.rom",   0x80000, 0x0200bc3d, BRF_GRA },
	{ "kr_gfx8.rom",   0x80000, 0x0bb2b4e7, BRF_GRA },

	{ "kr_09.rom",     0x10000, 0x5e44d9ee, BRF_SND },

	{ "kr_18.rom",     0x20000, 0xda69d15f, BRF_SND },
	{ "kr_19.rom",     0x20000, 0xbfc654e9, BRF_SND },
};


STD_ROM_PICK(Knightsu) STD_ROM_FN(Knightsu)

struct BurnDriver BurnDrvCpsKnightsu = {
	"knightsu", "knights", NULL, "1991",
	"Knights of the Round (911127 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,3,HARDWARE_CAPCOM_CPS1,
NULL,KnightsuRomInfo,KnightsuRomName,DrvInputInfo, knightsDIPInfo,
DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
&CpsRecalcPal,384,224,4,3
};

////////////////////
// Knights of the Round (Japan)

static int KnightsjInit()
{
   int nRet=0;
   Cps=1; Knights=1;
   nCpsRomLen =  0x100000;
   nCpsCodeLen=0;
   nCpsGfxLen =8*0x080000;
   nCpsZRomLen=  0x010000;
   nCpsAdLen  =2*0x020000;
   nRet=CpsInit(); if (nRet!=0) return 1;

   nRet=BurnLoadRom(CpsRom+0x000001,0,2); if (nRet!=0) return 1;
   nRet=BurnLoadRom(CpsRom+0x000000,1,2); if (nRet!=0) return 1;
   nRet=BurnLoadRom(CpsRom+0x040001,2,2); if (nRet!=0) return 1;
   nRet=BurnLoadRom(CpsRom+0x040000,3,2); if (nRet!=0) return 1;
   nRet=BurnLoadRom(CpsRom+0x080000,4,1); if (nRet!=0) return 1;

   // Set dip switches
//   SETUP_DIPSW_3(Cpi01A,Cpi01C,Cpi01E,0x00,0x03,0x60);

   CpsLoadTiles(CpsGfx+0x000000,5+0*4);
   CpsLoadTiles(CpsGfx+0x200000,5+1*4);

   nCpsLcReg=0x68;
   CpsLayEn[1]=0x20;
   CpsLayEn[2]=0x10;
   CpsLayEn[3]=0x02;

   CpsMProt[0]=0x46;
   CpsMProt[1]=0x44;
   CpsMProt[2]=0x42;
   CpsMProt[3]=0x40;

   MaskAddr[0]=0x66;
   MaskAddr[1]=0x64;
   MaskAddr[2]=0x62;
   MaskAddr[3]=0x60;

   nRet=BurnLoadRom(CpsZRom,13,1); //changed to 13

   nRet=BurnLoadRom(CpsAd        ,14,1); //changed to 14
   nRet=BurnLoadRom(CpsAd+0x20000,15,1); //changed to 15

   nRet=CpsRunInit();

   if (nRet!=0) return 1;

   return 0;
}


static struct BurnRomInfo KnightsjRomDesc[] = {
	{ "krj30.bin",     0x20000, 0xad3d1a8e, BRF_ESS | BRF_PRG },
	{ "krj37.bin",     0x20000, 0xe694a491, BRF_ESS | BRF_PRG },
	{ "krj31.bin",     0x20000, 0x85596094, BRF_ESS | BRF_PRG },
	{ "krj38.bin",     0x20000, 0x9198bf8f, BRF_ESS | BRF_PRG },
	{ "kr_22.rom",     0x80000, 0xd0b671a9, BRF_ESS | BRF_PRG }, //added

	{ "kr_gfx1.rom",   0x80000, 0x9e36c1a4, BRF_GRA },			 // 2
	{ "kr_gfx3.rom",   0x80000, 0xc5832cae, BRF_GRA },
	{ "kr_gfx2.rom",   0x80000, 0xf095be2d, BRF_GRA },
	{ "kr_gfx4.rom",   0x80000, 0x179dfd96, BRF_GRA },
	{ "kr_gfx5.rom",   0x80000, 0x1f4298d2, BRF_GRA },			 // 6
	{ "kr_gfx7.rom",   0x80000, 0x37fa8751, BRF_GRA },
	{ "kr_gfx6.rom",   0x80000, 0x0200bc3d, BRF_GRA },
	{ "kr_gfx8.rom",   0x80000, 0x0bb2b4e7, BRF_GRA },

	{ "kr_09.rom",     0x10000, 0x5e44d9ee, BRF_SND },

	{ "kr_18.rom",     0x20000, 0xda69d15f, BRF_SND },
	{ "kr_19.rom",     0x20000, 0xbfc654e9, BRF_SND },
};


STD_ROM_PICK(Knightsj) STD_ROM_FN(Knightsj)

struct BurnDriver BurnDrvCpsKnightsj = {
	"knightsj", "knights", NULL, "1991",
	"Knights of the Round (911127 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,3,HARDWARE_CAPCOM_CPS1,
NULL,KnightsjRomInfo,KnightsjRomName,DrvInputInfo, knightsDIPInfo,
KnightsjInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
&CpsRecalcPal,384,224,4,3
};

//////////////////////////

static int KnightshInit()
{
   int nRet=0;
   Cps=1; Knights=1;
   nCpsRomLen =  0x100000;
   nCpsCodeLen=0;
   nCpsGfxLen =8*0x080000;
   nCpsZRomLen=  0x010000;
   nCpsAdLen  =2*0x020000;
   nRet=CpsInit(); if (nRet!=0) return 1;

   nRet=BurnLoadRom(CpsRom,0,1); if (nRet!=0) return 1;
   nRet=BurnLoadRom(CpsRom+0x080000,1,1); if (nRet!=0) return 1;

   CpsLoadTiles(CpsGfx+0x000000,2);
   CpsLoadTiles(CpsGfx+0x200000,6);

   nCpsLcReg=0x66;
   CpsLayEn[1]=0x02;
   CpsLayEn[2]=0x04;
   CpsLayEn[3]=0x08;

   // it works without CpsMProt - we can probably disable this
   CpsMProt[0]=0x00;
   CpsMProt[1]=0x00;
   CpsMProt[2]=0x00;
   CpsMProt[3]=0x00;

   MaskAddr[0]=0x68;
   MaskAddr[1]=0x6a;
   MaskAddr[2]=0x6c;
   MaskAddr[3]=0x6e;

   nRet=BurnLoadRom(CpsZRom,10,1); //changed to 13

   nRet=BurnLoadRom(CpsAd        ,11,1); //changed to 14
   nRet=BurnLoadRom(CpsAd+0x20000,12,1); //changed to 15


   nRet=CpsRunInit();

   if (nRet!=0) return 1;

   return 0;
}

// Knights of the Round (Hack)
/*
static struct BurnRomInfo KnightshRomDesc[] = {
	{ "krh23.rom",     0x80000, 0xfa2ff63d, BRF_ESS | BRF_PRG },
	{ "krh22.rom",     0x80000, 0x1438d070, BRF_ESS | BRF_PRG },

	{ "kr_gfx1.rom",   0x80000, 0x9e36c1a4, BRF_GRA },
	{ "kr_gfx3.rom",   0x80000, 0xc5832cae, BRF_GRA },
	{ "kr_gfx2.rom",   0x80000, 0xf095be2d, BRF_GRA },
	{ "kr_gfx4.rom",   0x80000, 0x179dfd96, BRF_GRA },
	{ "kr_gfx5.rom",   0x80000, 0x1f4298d2, BRF_GRA },
	{ "kr_gfx7.rom",   0x80000, 0x37fa8751, BRF_GRA },
	{ "kr_gfx6.rom",   0x80000, 0x0200bc3d, BRF_GRA },
	{ "kr_gfx8.rom",   0x80000, 0x0bb2b4e7, BRF_GRA },

	{ "kr_09.rom",     0x10000, 0x5e44d9ee, BRF_SND },

	{ "kr_18.rom",     0x20000, 0xda69d15f, BRF_SND },
	{ "kr_19.rom",     0x20000, 0xbfc654e9, BRF_SND },
};


STD_ROM_PICK(Knightsh) STD_ROM_FN(Knightsh)

struct BurnDriver BurnDrvCpsKnightsh = {
	"knightsh", "knights", NULL, "1991",
	"Knights of the Round\0", "Hack", "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,3,HARDWARE_CAPCOM_CPS1,
NULL,KnightshRomInfo,KnightshRomName,DrvInputInfo, knightsDIPInfo,
KnightshInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
&CpsRecalcPal,384,224,4,3
};*/
