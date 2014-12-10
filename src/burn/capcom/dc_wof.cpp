// Warriors of Fate

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

  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Attack"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Jump"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},

  {"P3 Coin"       , BIT_DIGITAL, CpsInpc001+6, "p3 coin"  },
  {"P3 Start"      , BIT_DIGITAL, CpsInpc001+7, "p3 start" },
  {"P3 Up"         , BIT_DIGITAL, CpsInpc001+3, "p3 up"    },
  {"P3 Down"       , BIT_DIGITAL, CpsInpc001+2, "p3 down"  },
  {"P3 Left"       , BIT_DIGITAL, CpsInpc001+1, "p3 left"  },
  {"P3 Right"      , BIT_DIGITAL, CpsInpc001+0, "p3 right" },
  {"P3 Attack"     , BIT_DIGITAL, CpsInpc001+4, "p3 fire 1"},
  {"P3 Jump"       , BIT_DIGITAL, CpsInpc001+5, "p3 fire 2"},

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnInputInfo WofhInputList[]=
{
	{"P1 Coin"       , 0,  CpsInp006+0, "p1 coin"   },
	{"P1 Start"      , 0,  CpsInp006+4, "p1 start"  },
	{"P1 Up"         , 0,  CpsInp001+3, "p1 up"     },
	{"P1 Down"       , 0,  CpsInp001+2, "p1 down"   },
	{"P1 Left"       , 0,  CpsInp001+1, "p1 left"   },
	{"P1 Right"      , 0,  CpsInp001+0, "p1 right"  },
	{"P1 Attack"     , 0,  CpsInp001+4, "p1 fire 1" },
	{"P1 Jump"       , 0,  CpsInp001+5, "p1 fire 2" },

	{"P2 Coin"       , 0,  CpsInp006+1, "p2 coin"   },
	{"P2 Start"      , 0,  CpsInp006+5, "p2 start"  },
	{"P2 Up"         , 0,  CpsInp000+3, "p2 up"     },
	{"P2 Down"       , 0,  CpsInp000+2, "p2 down"   },
	{"P2 Left"       , 0,  CpsInp000+1, "p2 left"   },
	{"P2 Right"      , 0,  CpsInp000+0, "p2 right"  },
	{"P2 Attack"     , 0,  CpsInp000+4, "p2 fire 1" },
	{"P2 Jump"       , 0,  CpsInp000+5, "p2 fire 2" },

	{"P3 Coin"       , BIT_DIGITAL, CpsInp007+6, "p3 coin"   }, // doesn't work
	{"P3 Start"      , BIT_DIGITAL, CpsInp007+7, "p3 start"  },
	{"P3 Up"         , BIT_DIGITAL, CpsInp007+3, "p3 up"     },
	{"P3 Down"       , BIT_DIGITAL, CpsInp007+2, "p3 down"   },
	{"P3 Left"       , BIT_DIGITAL, CpsInp007+1, "p3 left"   },
	{"P3 Right"      , BIT_DIGITAL, CpsInp007+0, "p3 right"  },
	{"P3 Attack"     , BIT_DIGITAL, CpsInp007+4, "p3 fire 1" },
	{"P3 Jump"       , BIT_DIGITAL, CpsInp007+5, "p3 fire 2" },

	{"Reset"         , BIT_DIGITAL, &CpsReset   , "reset"     },
	{"Diagnostic"    , BIT_DIGITAL, CpsInp006+6 , "diag"      },
	{"Service"       , BIT_DIGITAL, CpsInp006+2 , "service"   },
	{"Dip C"         , BIT_DIPSWITCH, &Cpi01E     , "dip"       },
};

STDINPUTINFO(Wofh);

static struct BurnDIPInfo wofDIPList[]=
{
	// Defaults
	{0x1b, 0xff, 0xff, 0x00, NULL                },

	// Dip C
	{0   , 0xfe, 0   , 2   , "Freeze"                 },
	{0x1b, 0x01, 0x08, 0x08, "Off"                    },
	{0x1b, 0x01, 0x08, 0x00, "On"                     },
};

STDDIPINFO(wof);


static int DrvExit()
{

  CpsRunExit();

  CpsExit();
  nCpsQSamLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0; Cps1Qs=0; Wofh=0;
  return 0;
}

//==============================
//Warriors of Fate Init CPS_B_01
//==============================

static int Drvb1Init()
{
  int nRet=0; unsigned char *pqs=NULL;
  Cps=1; Cps1Qs=1;
  nCpsRomLen= 2*0x080000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 8*0x080000;
  nCpsZRomLen= 2*0x020000;
  nCpsQSamLen= 4*0x080000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000000,0,1); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,1,1); if (nRet!=0) return 1;

  // Load graphics roms
  CpsLoadTiles(CpsGfx         , 2);
  CpsLoadTiles(CpsGfx+0x200000, 6);

  nCpsLcReg=0x66; // Layer control register is at 0x66
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x08;

  // Start of Board ID improvments by KEV. 0x00,0x0000
  CpsBID[0]=0x00;
  CpsBID[1]=0x00;
  CpsBID[2]=0x00;
  //end

  MaskAddr[0]=0x68;
  MaskAddr[1]=0x6a;
  MaskAddr[2]=0x6c;
  MaskAddr[3]=0x6e;

  nRet=BurnLoadRom(CpsZRom,10,1);
  wof_decode();

  pqs=(unsigned char *)CpsQSam;
  nRet=BurnLoadRom(pqs         ,11,1);
  nRet=BurnLoadRom(pqs+0x080000,12,1);
  nRet=BurnLoadRom(pqs+0x100000,13,1);
  nRet=BurnLoadRom(pqs+0x180000,14,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//==============================
//Warriors of Fate Init QSOUND_1
//==============================

static int Drvq1Init()
{
  int nRet=0; unsigned char *pqs=NULL;
  Cps=1; Cps1Qs=1;
  nCpsRomLen= 2*0x080000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 8*0x080000;
  nCpsZRomLen= 2*0x020000;
  nCpsQSamLen= 4*0x080000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000000,0,1); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,1,1); if (nRet!=0) return 1;

  // Load graphics roms
  CpsLoadTiles(CpsGfx         , 2);
  CpsLoadTiles(CpsGfx+0x200000, 6);

  nCpsLcReg=0x62; // Layer control register is at 0x62
  CpsLayEn[1]=0x10;
  CpsLayEn[2]=0x08;
  CpsLayEn[3]=0x04;

  // Protection enable code by KEV
  CpsMProt[0]=0x00;
  CpsMProt[1]=0x00;
  CpsMProt[2]=0x00;
  CpsMProt[3]=0x00;

  // Start of Board ID improvments by KEV. 0x00,0x0000
  CpsBID[0]=0x00;
  CpsBID[1]=0x00;
  CpsBID[2]=0x00;
  //end

  MaskAddr[0]=0x64;
  MaskAddr[1]=0x66;
  MaskAddr[2]=0x68;
  MaskAddr[3]=0x6a;

  nRet=BurnLoadRom(CpsZRom,10,1);
  wof_decode();

  pqs=(unsigned char *)CpsQSam;
  nRet=BurnLoadRom(pqs         ,11,1);
  nRet=BurnLoadRom(pqs+0x080000,12,1);
  nRet=BurnLoadRom(pqs+0x100000,13,1);
  nRet=BurnLoadRom(pqs+0x180000,14,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//========================
//Warriors of Fate (World)
//========================

// Rom information
static struct BurnRomInfo WofRomDesc[] = {
	{ "tk2e_23b.rom",  0x80000, 0x11fb2ed1, BRF_ESS | BRF_PRG }, // 0 swapped 68000 code
	{ "tk2e_22b.rom",  0x80000, 0x479b3f24, BRF_ESS | BRF_PRG }, // 1 swapped

  // graphics:
	{ "tk2_gfx1.rom",  0x80000, 0x0d9cb9bf, BRF_GRA },			 // 2
	{ "tk2_gfx3.rom",  0x80000, 0x45227027, BRF_GRA },
	{ "tk2_gfx2.rom",  0x80000, 0xc5ca2460, BRF_GRA },
	{ "tk2_gfx4.rom",  0x80000, 0xe349551c, BRF_GRA },
	{ "tk2_gfx5.rom",  0x80000, 0x291f0f0b, BRF_GRA },			 // 6
	{ "tk2_gfx7.rom",  0x80000, 0x3edeb949, BRF_GRA },
	{ "tk2_gfx6.rom",  0x80000, 0x1abd14d6, BRF_GRA },
	{ "tk2_gfx8.rom",  0x80000, 0xb27948e3, BRF_GRA },

  // z80 rom
	{ "tk2_qa.rom",    0x20000, 0xc9183a0d, BRF_SND },			 // 10
  // samples
	{ "tk2_q1.rom",    0x80000, 0x611268cf, BRF_SND },
	{ "tk2_q2.rom",    0x80000, 0x20f55ca9, BRF_SND },
	{ "tk2_q3.rom",    0x80000, 0xbfcf6f52, BRF_SND },
	{ "tk2_q4.rom",    0x80000, 0x36642e88, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Wof) STD_ROM_FN(Wof)


struct BurnDriver BurnDrvCpsWof = {
	"wof", NULL, NULL, "1992",
	"Warriors of Fate (921002 etc)\0", NULL, "Capcom", "CPS1 / QSound",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,3,HARDWARE_CAPCOM_CPS1_QSOUND,
	NULL,WofRomInfo,WofRomName,DrvInputInfo, wofDIPInfo,
	Drvb1Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//====================
//Sangokushi II (Asia)
//====================

// Rom information
static struct BurnRomInfo WofaRomDesc[] = {
	{ "tk2a_23b.rom",  0x80000, 0x2e024628, BRF_ESS | BRF_PRG }, // 0 swapped 68000 code
	{ "tk2a_22b.rom",  0x80000, 0x900ad4cd, BRF_ESS | BRF_PRG }, // 1 swapped

  // graphics:
	{ "tk2_gfx1.rom",  0x80000, 0x0d9cb9bf, BRF_GRA },			 // 2
	{ "tk2_gfx3.rom",  0x80000, 0x45227027, BRF_GRA },
	{ "tk2_gfx2.rom",  0x80000, 0xc5ca2460, BRF_GRA },
	{ "tk2_gfx4.rom",  0x80000, 0xe349551c, BRF_GRA },
	{ "tk2_gfx5.rom",  0x80000, 0x291f0f0b, BRF_GRA },			 // 6
	{ "tk2_gfx7.rom",  0x80000, 0x3edeb949, BRF_GRA },
	{ "tk2_gfx6.rom",  0x80000, 0x1abd14d6, BRF_GRA },
	{ "tk2_gfx8.rom",  0x80000, 0xb27948e3, BRF_GRA },

  // z80 rom
	{ "tk2_qa.rom",    0x20000, 0xc9183a0d, BRF_SND },			 // 10
  // samples
	{ "tk2_q1.rom",    0x80000, 0x611268cf, BRF_SND },
	{ "tk2_q2.rom",    0x80000, 0x20f55ca9, BRF_SND },
	{ "tk2_q3.rom",    0x80000, 0xbfcf6f52, BRF_SND },
	{ "tk2_q4.rom",    0x80000, 0x36642e88, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Wofa) STD_ROM_FN(Wofa)


struct BurnDriver BurnDrvCpsWofa = {
	"wofa", "wof", NULL, "1992",
	"Sangokushi II (921005 Asia)\0", NULL, "Capcom", "CPS1 / QSound",
	L"\u4E09\u56FD\u5FD7II (Sangokushi 2 921005 Asia)\0Sangokushi II (921005 Asia)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,3,HARDWARE_CAPCOM_CPS1_QSOUND,
	NULL,WofaRomInfo,WofaRomName,DrvInputInfo, wofDIPInfo,
	Drvb1Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//======================
//Warriors of Fate (USA)
//======================

// Rom information
static struct BurnRomInfo WofuRomDesc[] = {
	{ "tk2u.23c",      0x80000, 0x29b89c12, BRF_ESS | BRF_PRG }, // 0 swapped 68000 code
	{ "tk2u.22c",      0x80000, 0xf5af4774, BRF_ESS | BRF_PRG }, // 1 swapped

  // graphics:
	{ "tk2_gfx1.rom",  0x80000, 0x0d9cb9bf, BRF_GRA },			 // 2
	{ "tk2_gfx3.rom",  0x80000, 0x45227027, BRF_GRA },
	{ "tk2_gfx2.rom",  0x80000, 0xc5ca2460, BRF_GRA },
	{ "tk2_gfx4.rom",  0x80000, 0xe349551c, BRF_GRA },
	{ "tk2_gfx5.rom",  0x80000, 0x291f0f0b, BRF_GRA },			 // 6
	{ "tk2_gfx7.rom",  0x80000, 0x3edeb949, BRF_GRA },
	{ "tk2_gfx6.rom",  0x80000, 0x1abd14d6, BRF_GRA },
	{ "tk2_gfx8.rom",  0x80000, 0xb27948e3, BRF_GRA },

  // z80 rom
	{ "tk2_qa.rom",    0x20000, 0xc9183a0d, BRF_SND },			 // 10
  // samples
	{ "tk2_q1.rom",    0x80000, 0x611268cf, BRF_SND },
	{ "tk2_q2.rom",    0x80000, 0x20f55ca9, BRF_SND },
	{ "tk2_q3.rom",    0x80000, 0xbfcf6f52, BRF_SND },
	{ "tk2_q4.rom",    0x80000, 0x36642e88, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Wofu) STD_ROM_FN(Wofu)


struct BurnDriver BurnDrvCpsWofu = {
	"wofu", "wof", NULL, "1992",
	"Warriors of Fate (921031 USA)\0", NULL, "Capcom", "CPS1 / QSound",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,3,HARDWARE_CAPCOM_CPS1_QSOUND,
	NULL,WofuRomInfo,WofuRomName,DrvInputInfo, wofDIPInfo,
	Drvq1Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//================================================
//Tenchi wo Kurau II - Sekiheki no Tatakai (Japan)
//================================================

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo WofjRomDesc[] = {
	{ "tk2j23c.bin",   0x80000, 0x9b215a68, BRF_ESS | BRF_PRG }, // 0 swapped 68000 code
	{ "tk2j22c.bin",   0x80000, 0xb74b09ac, BRF_ESS | BRF_PRG }, // 1 swapped

  // graphics:
	{ "tk2_gfx1.rom",  0x80000, 0x0d9cb9bf, BRF_GRA },			 // 2
	{ "tk2_gfx3.rom",  0x80000, 0x45227027, BRF_GRA },
	{ "tk2_gfx2.rom",  0x80000, 0xc5ca2460, BRF_GRA },
	{ "tk2_gfx4.rom",  0x80000, 0xe349551c, BRF_GRA },
	{ "tk205.bin",     0x80000, 0xe4a44d53, BRF_GRA },			 // 6
	{ "tk206.bin",     0x80000, 0x58066ba8, BRF_GRA },
	{ "tk207.bin",     0x80000, 0xd706568e, BRF_GRA },
	{ "tk208.bin",     0x80000, 0xd4a19a02, BRF_GRA },

  // z80 rom
	{ "tk2_qa.rom",    0x20000, 0xc9183a0d, BRF_SND },			 // 10
  // samples
	{ "tk2_q1.rom",    0x80000, 0x611268cf, BRF_SND },
	{ "tk2_q2.rom",    0x80000, 0x20f55ca9, BRF_SND },
	{ "tk2_q3.rom",    0x80000, 0xbfcf6f52, BRF_SND },
	{ "tk2_q4.rom",    0x80000, 0x36642e88, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Wofj) STD_ROM_FN(Wofj)


struct BurnDriver BurnDrvCpsWofj = {
	"wofj", "wof", NULL, "1992",
	"Tenchi wo Kurau II - Sekiheki no Tatakai (921031 Japan)\0", NULL, "Capcom", "CPS1 / QSound",
	L"\u8EE2\u5730\u3092\u55B0\u3089\u3046II - \u8D64\u58C1\u306E\u6226\u3044 (Tenchi wo Kurau 2 921031 Japan)\0Tenchi wo Kurau II - Sekiheki no Tatakai (921031 Japan)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,3,HARDWARE_CAPCOM_CPS1_QSOUND,
	NULL,WofjRomInfo,WofjRomName,DrvInputInfo, wofDIPInfo,
	Drvq1Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

/*
//================================================
// Warriors of Fate (Hack)
//================================================

static struct BurnRomInfo WofhRomDesc[] = {
	{ "tk2_23h.rom",  0x100000, 0x3703a650, BRF_ESS | BRF_PRG }, // 0

	{ "sgyx-1.160",   0x200000, 0xa60be9f6, BRF_GRA },			 // 1
	{ "sgyx-2.160",   0x200000, 0x6ad9d048, BRF_GRA },			 // 2

	{ "tk2_qa.rom",   0x020000, 0xc9183a0d, BRF_SND },			 // 3

	{ "tk2_q1.rom",   0x080000, 0x611268cf, BRF_SND },			 // 4
	{ "tk2_q2.rom",   0x080000, 0x20f55ca9, BRF_SND },			 // 5
	{ "tk2_q3.rom",   0x080000, 0xbfcf6f52, BRF_SND },			 // 6
	{ "tk2_q4.rom",   0x080000, 0x36642e88, BRF_SND },			 // 7
};


STD_ROM_PICK(Wofh) STD_ROM_FN(Wofh)

static int WofhInit()
{
  int nRet=0; unsigned char *pqs=NULL;
  Cps=1; Cps1Qs=1; Wofh=1;
  nCpsRomLen= 2*0x080000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 8*0x080000;
  nCpsZRomLen= 2*0x020000;
  nCpsQSamLen= 4*0x080000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000000,0,1); if (nRet!=0) return 1;

  // Patch protection? check
  CpsRom[0xf11ed] = 0x4e;
  CpsRom[0xf11ec] = 0x71;
  CpsRom[0xf11ef] = 0x4e;
  CpsRom[0xf11ee] = 0x71;

  // Disable Sprite Recoding
  CpsRom[0x5d891] = 0x0c;
  CpsRom[0x5d890] = 0x6d;
  CpsRom[0x5d893] = 0x90;
  CpsRom[0x5d892] = 0x00;
  CpsRom[0x5d895] = 0xe3;
  CpsRom[0x5d894] = 0xd2;
  CpsRom[0x5d8e9] = 0x00;
  CpsRom[0x5d8e8] = 0x90;
  CpsRom[0x5d8eb] = 0x00;
  CpsRom[0x5d8ea] = 0x00;
  CpsRom[0x5d8f9] = 0x00;
  CpsRom[0x5d8f8] = 0x90;
  CpsRom[0x5d8fb] = 0x40;
  CpsRom[0x5d8fa] = 0x00;
  CpsRom[0x5d859] = 0x61;
  CpsRom[0x5d858] = 0x00;
  CpsRom[0x5d85b] = 0x01;
  CpsRom[0x5d85a] = 0xe6;

  // Load graphics roms
  CpsLoadTilesHack160(CpsGfx, 1);

  nCpsLcReg=0x60;
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x08;

  CpsBID[0]=0x00;
  CpsBID[1]=0x00;
  CpsBID[2]=0x00;

  MaskAddr[0]=0x68;
  MaskAddr[1]=0x6a;
  MaskAddr[2]=0x6c;
  MaskAddr[3]=0x6e;

  nRet=BurnLoadRom(CpsZRom,3,1);
  wof_decode();

  pqs=(unsigned char *)CpsQSam;
  nRet=BurnLoadRom(pqs         ,4,1);
  nRet=BurnLoadRom(pqs+0x080000,5,1);
  nRet=BurnLoadRom(pqs+0x100000,6,1);
  nRet=BurnLoadRom(pqs+0x180000,7,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

struct BurnDriverD BurnDrvCpsWofh = {
	"wofh", "wof", NULL, "1992",
	"Warriors of Fate (Hack)\0", "Missing GFX, No Sound, Game crashes", "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_CLONE | BDF_BOOTLEG,3,HARDWARE_CAPCOM_CPS1_QSOUND,
	NULL,WofhRomInfo,WofhRomName,WofhInputInfo, wofDIPInfo,
	WofhInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
*/
