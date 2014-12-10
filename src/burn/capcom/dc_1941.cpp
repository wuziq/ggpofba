// 1941 - Counter Attack

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
	{"P1 Coin"    , BIT_DIGITAL, CpsInp018+0, "p1 coin"   },
	{"P1 Start"   , BIT_DIGITAL, CpsInp018+4, "p1 start"  },
	{"P1 Up"      , BIT_DIGITAL, CpsInp001+3, "p1 up"     },
	{"P1 Down"    , BIT_DIGITAL, CpsInp001+2, "p1 down"   },
	{"P1 Left"    , BIT_DIGITAL, CpsInp001+1, "p1 left"   },
	{"P1 Right"   , BIT_DIGITAL, CpsInp001+0, "p1 right"  },
	{"P1 Shot"    , BIT_DIGITAL, CpsInp001+4, "p1 fire 1" },
	{"P1 Special" , BIT_DIGITAL, CpsInp001+5, "p1 fire 2" },

	{"P2 Coin"    , BIT_DIGITAL, CpsInp018+1, "p2 coin"   },
	{"P2 Start"   , BIT_DIGITAL, CpsInp018+5, "p2 start"  },
	{"P2 Up"      , BIT_DIGITAL, CpsInp000+3, "p2 up"     },
	{"P2 Down"    , BIT_DIGITAL, CpsInp000+2, "p2 down"   },
	{"P2 Left"    , BIT_DIGITAL, CpsInp000+1, "p2 left"   },
	{"P2 Right"   , BIT_DIGITAL, CpsInp000+0, "p2 right"  },
	{"P2 Shot"    , BIT_DIGITAL, CpsInp000+4, "p2 fire 1" },
	{"P2 Special" , BIT_DIGITAL, CpsInp000+5, "p2 fire 2" },

	{"Reset"      , BIT_DIGITAL, &CpsReset,   "reset"     },
	{"Diagnostic" , BIT_DIGITAL, CpsInp018+6, "diag"      },
	{"Service"    , BIT_DIGITAL, CpsInp018+2, "service"   },
	{"Dip A"      , BIT_DIPSWITCH, &Cpi01A    , "dip"       },
	{"Dip B"      , BIT_DIPSWITCH, &Cpi01C    , "dip"       },
	{"Dip C"      , BIT_DIPSWITCH, &Cpi01E    , "dip"       },
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo NTFODIPList[]=
{
	// Defaults
	{0x13, 0xff, 0xff, 0x00, NULL                     },
	{0x14, 0xff, 0xff, 0x2B, NULL                     },
	{0x15, 0xff, 0xff, 0x60, NULL                     },

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

	{0   , 0xfe, 0   , 2   , "2C to Start, 1 to Cont" },
	{0x13, 0x01, 0x40, 0x00, "Off"                    },
	{0x13, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown" },
//	{0x13, 0x01, 0x80, 0x00, "Off"                    },
//	{0x13, 0x01, 0x80, 0x80, "On"                     },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Difficulty"             },
	{0x14, 0x01, 0x07, 0x00, "00 (Easier)"            },
	{0x14, 0x01, 0x07, 0x01, "01"                     },
	{0x14, 0x01, 0x07, 0x02, "02"                     },
	{0x14, 0x01, 0x07, 0x03, "03"                     },
	{0x14, 0x01, 0x07, 0x04, "04"                     },
	{0x14, 0x01, 0x07, 0x05, "05"                     },
	{0x14, 0x01, 0x07, 0x06, "06"                     },
	{0x14, 0x01, 0x07, 0x07, "07 (Harder)"            },

	{0   , 0xfe, 0   , 4   , "Level Up Timer"         },
	{0x14, 0x01, 0x18, 0x00, "More Slowly"            },
	{0x14, 0x01, 0x18, 0x08, "Slowly"                 },
	{0x14, 0x01, 0x18, 0x10, "Quickly"                },
	{0x14, 0x01, 0x18, 0x18, "More Quickly"           },

	{0   , 0xfe, 0   , 4   , "Bullet's Speed"         },
	{0x14, 0x01, 0x60, 0x00, "Very Slow"              },
	{0x14, 0x01, 0x60, 0x20, "Slow"                   },
	{0x14, 0x01, 0x60, 0x40, "Fast"                   },
	{0x14, 0x01, 0x60, 0x60, "Very Fast"              },

	{0   , 0xfe, 0   , 2   , "Initital Vitality"      },
	{0x14, 0x01, 0x80, 0x00, "3 bars"                 },
	{0x14, 0x01, 0x80, 0x80, "4 bars"                 },

	// Dip C
//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x15, 0x01, 0x01, 0x00, "Off"                    },
//	{0x15, 0x01, 0x01, 0x01, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x15, 0x01, 0x02, 0x00, "Off"                    },
//	{0x15, 0x01, 0x02, 0x02, "On"                     },

	{0   , 0xfe, 0   , 2   , "Free Play"              },
	{0x15, 0x01, 0x04, 0x00, "Off"                    },
	{0x15, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Freeze"                 },
	{0x15, 0x01, 0x08, 0x00, "Off"                    },
	{0x15, 0x01, 0x08, 0x08, "On"                     },

	{0   , 0xfe, 0   , 2   , "Flip"                   },
	{0x15, 0x01, 0x10, 0x00, "Off"                    },
	{0x15, 0x01, 0x10, 0x10, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sound"             },
	{0x15, 0x01, 0x20, 0x00, "Off"                    },
	{0x15, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 2   , "Continue"               },
	{0x15, 0x01, 0x40, 0x00, "Off"                    },
	{0x15, 0x01, 0x40, 0x40, "On"                     },
};

STDDIPINFO(NTFO);


static int DrvInit()
{
    int nRet=0;
	Cps=1;
	nCpsRomLen= 0x100000;
	nCpsCodeLen=0; // not encrypted
	nCpsGfxLen= 4*0x080000;
	nCpsZRomLen= 0x010000;
	nCpsAdLen =2*0x020000;
	nRet=CpsInit(); if (nRet!=0) return 1;

    // Load program roms
	nRet=BurnLoadRom(CpsRom+0x000001,0,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom+0x000000,1,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom+0x040001,2,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom+0x040000,3,2); if (nRet!=0) return 1;
	nRet=BurnLoadRom(CpsRom+0x080000,4,1); if (nRet!=0) return 1; // Already byteswapped

    // Load graphics roms
	CpsLoadTiles(CpsGfx,5);

	nCpsLcReg=0x68;   // Layer control register is at 0x6e
    CpsLayEn[1]=0x02; //layer enable 1 is different
    CpsLayEn[2]=0x08;
    CpsLayEn[3]=0x20; // Layer enable is different

    // Board ID improvments by KEV. 0x60,0x0005
    CpsBID[0]=0x60;
    CpsBID[1]=0x00;
    CpsBID[2]=0x05;

	MaskAddr[0]=0x6a;
    MaskAddr[1]=0x6c;
    MaskAddr[2]=0x6e;
    MaskAddr[3]=0x70;

    StartScroll[SCROLL_3]=0x0400;
	EndScroll[SCROLL_3]=0x07ff;

    // Load Z80 Rom
	nRet=BurnLoadRom(CpsZRom,9,1);

    // Load ADPCM data
	nRet=BurnLoadRom(CpsAd ,10,1);
	nRet=BurnLoadRom(CpsAd+0x20000,11,1);
	nRet=CpsRunInit(); if (nRet!=0) return 1;

	// Ready to go
	return 0;
}

static int DrvExit()
{

	CpsRunExit();

	StartScroll[SCROLL_3]=0;
	EndScroll[SCROLL_3]=0xffff;

	CpsExit();
	nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
	Cps=0;
	return 0;
}


/////////////////////////////////
// Variations and clones
///////////////////////////////

///////////////
//1941 (World)
///////////////

// Rom information
static struct BurnRomInfo NTFODrvRomDesc[] = {
	{ "41e_30.rom",    0x20000, 0x9deb1e75, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "41e_35.rom",    0x20000, 0xd63942b3, BRF_ESS | BRF_PRG }, // 1 odd
	{ "41e_31.rom",    0x20000, 0xdf201112, BRF_ESS | BRF_PRG }, // 2 even
	{ "41e_36.rom",    0x20000, 0x816a818f, BRF_ESS | BRF_PRG }, // 3 odd
	{ "41_32.rom",     0x80000, 0x4e9648ca, BRF_ESS | BRF_PRG }, // 4 both

// graphics:
	{ "41_gfx5.rom",   0x80000, 0x01d1cb11, BRF_GRA },			 // 5
	{ "41_gfx7.rom",   0x80000, 0xaeaa3509, BRF_GRA },
	{ "41_gfx1.rom",   0x80000, 0xff77985a, BRF_GRA },
	{ "41_gfx3.rom",   0x80000, 0x983be58f, BRF_GRA },

// z80 rom
	{ "41_09.rom",     0x10000, 0x0f9d8527, BRF_GRA },			 // 9
// samples
	{ "41_18.rom",     0x20000, 0xd1f15aeb, BRF_GRA },
	{ "41_19.rom",     0x20000, 0x15aec3a6, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(NTFODrv);
STD_ROM_FN(NTFODrv);

struct BurnDriver BurnDrvCps1941 = {
	"1941", NULL, NULL, "1990",
	"1941 - Counter Attack (World)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_CAPCOM_CPS1,
	NULL,NTFODrvRomInfo,NTFODrvRomName,DrvInputInfo, NTFODIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};

////////////
// 1941 Jap
///////////

// Rom information
static struct BurnRomInfo NTFOJDrvRomDesc[] = {
	{ "4136.bin",      0x20000, 0x7fbd42ab, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "4142.bin",      0x20000, 0xc7781f89, BRF_ESS | BRF_PRG }, // 1 odd
	{ "4137.bin",      0x20000, 0xc6464b0b, BRF_ESS | BRF_PRG }, // 2 even
	{ "4143.bin",      0x20000, 0x440fc0b5, BRF_ESS | BRF_PRG }, // 3 odd
	{ "41_32.rom",     0x80000, 0x4e9648ca, BRF_ESS | BRF_PRG }, // 4 both

// graphics:
	{ "41_gfx5.rom",   0x80000, 0x01d1cb11, BRF_GRA },			 // 5
	{ "41_gfx7.rom",   0x80000, 0xaeaa3509, BRF_GRA },
	{ "41_gfx1.rom",   0x80000, 0xff77985a, BRF_GRA },
	{ "41_gfx3.rom",   0x80000, 0x983be58f, BRF_GRA },

// z80 rom
	{ "41_09.rom",     0x10000, 0x0f9d8527, BRF_GRA },			 // 9
// samples
	{ "41_18.rom",     0x20000, 0xd1f15aeb, BRF_GRA },
	{ "41_19.rom",     0x20000, 0x15aec3a6, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(NTFOJDrv);
STD_ROM_FN(NTFOJDrv);

struct BurnDriver BurnDrvCps1941j = {
	"1941j", "1941", NULL, "1990",
	"1941 - Counter Attack (Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_CAPCOM_CPS1,
	NULL,NTFOJDrvRomInfo,NTFOJDrvRomName,DrvInputInfo, NTFODIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};
