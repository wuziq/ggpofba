// Mega Twins

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
{"P1 Coin"       , BIT_DIGITAL, CpsInp018+0, "p1 coin"},
{"P1 Start"      , BIT_DIGITAL, CpsInp018+4, "p1 start"},
{"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
{"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
{"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
{"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
{"P1 Attack"     , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
{"P1 Jump"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
{"P1 Special"    , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

{"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"},
{"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start"},
{"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
{"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
{"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
{"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
{"P2 Attack"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
{"P2 Jump"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
{"P2 Special"    , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

{"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
{"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
{"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
{"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"},
{"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"},
{"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo mtwinsDIPList[]=
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
	{0x16, 0x01, 0x07, 0x00, "0 (Easiest)"       },
	{0x16, 0x01, 0x07, 0x01, "1"                 },
	{0x16, 0x01, 0x07, 0x02, "2"                 },
	{0x16, 0x01, 0x07, 0x03, "3"                 },
	{0x16, 0x01, 0x07, 0x04, "4"                 },
	{0x16, 0x01, 0x07, 0x05, "5"                 },
	{0x16, 0x01, 0x07, 0x06, "6"                 },
	{0x16, 0x01, 0x07, 0x07, "7"                 },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x16, 0x01, 0x08, 0x00, "Off"               },
//	{0x16, 0x01, 0x08, 0x08, "On"                },

	{0   , 0xfe, 0   , 3   , "Lives"             },
	{0x16, 0x01, 0x30, 0x00, "1"                 },
	{0x16, 0x01, 0x30, 0x20, "2"                 },
	{0x16, 0x01, 0x30, 0x30, "3"                 },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x16, 0x01, 0x40, 0x00, "Off"               },
//	{0x16, 0x01, 0x40, 0x40, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x16, 0x01, 0x80, 0x00, "Off"               },
//	{0x16, 0x01, 0x80, 0x80, "On"                },

	// Dip C
//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x17, 0x01, 0x01, 0x00, "Off"               },
//	{0x17, 0x01, 0x01, 0x01, "On"                },

//	{0   , 0xfe, 0   , 2   , "Unknown"           },
//	{0x17, 0x01, 0x02, 0x00, "Off"               },
//	{0x17, 0x01, 0x02, 0x02, "On"                },

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

STDDIPINFO(mtwins);


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
   nRet=BurnLoadRom(CpsRom+0x080000,4,1); if (nRet!=0) return 1; // Already byteswapped

   // Load graphics roms
   CpsLoadTiles(CpsGfx,5);

   //-----------------------------------------------------
   nCpsLcReg =0x52;
   CpsLayEn[1]=0x08;
   CpsLayEn[2]=0x30;
   CpsLayEn[3]=0x30;

   //-----------------------------------------------------
   CpsBID[0]=0x5e;
   CpsBID[1]=0x04;
   CpsBID[2]=0x04;
   //-----------------------------------------------------

   MaskAddr[0]=0x54;
   MaskAddr[1]=0x56;
   MaskAddr[2]=0x58;
   MaskAddr[3]=0x5a;

   EndScroll[SCROLL_2]=0x3fff;
   StartScroll[SCROLL_3]=0x0e00;

   // Load Z80 Rom
   nRet=BurnLoadRom(CpsZRom,9,1);

   // Load ADPCM data
   nRet=BurnLoadRom(CpsAd        ,10,1);
   nRet=BurnLoadRom(CpsAd+0x20000,11,1);


   nRet=CpsRunInit(); if (nRet!=0) return 1;
   // Ready to go
   return 0;
}

static int DrvExit()
{

   CpsRunExit();

   EndScroll[SCROLL_2]=0xffff;
   StartScroll[SCROLL_3]=0;

   CpsExit();
   nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
   Cps=0;
   return 0;
}

//==================
//Mega Twins (World)
//==================

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo MtwinsRomDesc[] = {
	{ "che_30.rom",    0x20000, 0x9a2a2db1, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "che_35.rom",    0x20000, 0xa7f96b02, BRF_ESS | BRF_PRG }, // 1 odd
	{ "che_31.rom",    0x20000, 0xbbff8a99, BRF_ESS | BRF_PRG }, // 2 even
	{ "che_36.rom",    0x20000, 0x0fa00c39, BRF_ESS | BRF_PRG }, // 3 odd
	{ "ch_32.rom",     0x80000, 0x9b70bd41, BRF_ESS | BRF_PRG }, // 4 both

// graphics:
	{ "ch_gfx5.rom",   0x80000, 0x4ec75f15, BRF_GRA },			 // 5
	{ "ch_gfx7.rom",   0x80000, 0xd85d00d6, BRF_GRA },
	{ "ch_gfx1.rom",   0x80000, 0xf33ca9d4, BRF_GRA },
	{ "ch_gfx3.rom",   0x80000, 0x0ba2047f, BRF_GRA },

// z80 rom
	{ "ch_09.rom",     0x10000, 0x4d4255b7, BRF_GRA },			 // 9
// samples
	{ "ch_18.rom",     0x20000, 0xf909e8de, BRF_GRA },
	{ "ch_19.rom",     0x20000, 0xfc158cf7, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Mtwins) STD_ROM_FN(Mtwins)

struct BurnDriver BurnDrvCpsMtwins = {
	"mtwins", NULL, NULL, "1990",
	"Mega Twins (chiki chiki boys 900619 etc)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1,
NULL,MtwinsRomInfo,MtwinsRomName,DrvInputInfo, mtwinsDIPInfo,
DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
&CpsRecalcPal,384,224,4,3
};

//========================
//Chiki Chiki Boys (Japan)
//========================


static struct BurnRomInfo ChikijRomDesc[] = {
	{ "chj36a.bin",    0x20000, 0xec1328d8, BRF_ESS | BRF_PRG }, //  0 68000 code
	{ "chj42a.bin",    0x20000, 0x4ae13503, BRF_ESS | BRF_PRG }, //  1
	{ "chj37a.bin",    0x20000, 0x46d2cf7b, BRF_ESS | BRF_PRG }, //  2 68000 code
	{ "chj43a.bin",    0x20000, 0x8d387fe8, BRF_ESS | BRF_PRG }, //  3
	{ "ch_32.rom",     0x80000, 0x9b70bd41, BRF_ESS | BRF_PRG }, //  4

// 5
	{ "ch_gfx5.rom",   0x80000, 0x4ec75f15, BRF_GRA },
	{ "ch_gfx7.rom",   0x80000, 0xd85d00d6, BRF_GRA },
	{ "ch_gfx1.rom",   0x80000, 0xf33ca9d4, BRF_GRA },
	{ "ch_gfx3.rom",   0x80000, 0x0ba2047f, BRF_GRA },

// 9
// z80 program
	{ "ch_09.rom",     0x10000, 0x4d4255b7, BRF_SND },
// adpcm samples
	{ "ch_18.rom",     0x20000, 0xf909e8de, BRF_SND },
	{ "ch_19.rom",     0x20000, 0xfc158cf7, BRF_SND },
// 18
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Chikij) STD_ROM_FN(Chikij)

struct BurnDriver BurnDrvCpsChikij = {
	"chikij", "mtwins", NULL, "1990",
	"Chiki Chiki Boys (900619 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1,
	NULL,ChikijRomInfo,ChikijRomName,DrvInputInfo, mtwinsDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
