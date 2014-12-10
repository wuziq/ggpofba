// Cadillacs & Dinosaurs

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp018+0, "p1 coin"  },
  {"P1 Start"      , BIT_DIGITAL, CpsInp018+4, "p1 start" },
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"    },
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"  },
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"  },
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right" },
  {"P1 Attack"     , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Jump"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"  },
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start" },
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"    },
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"  },
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"  },
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right" },
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

static struct BurnDIPInfo dinoDIPList[]=
{
	// Defaults
	{0x1b, 0xff, 0xff, 0x00, NULL                },

	// Dip C
	{0   , 0xfe, 0   , 2   , "Freeze"                 },
	{0x1b, 0x01, 0x08, 0x00, "Off"                    },
	{0x1b, 0x01, 0x08, 0x08, "On"                     },
};

STDDIPINFO(dino);

static int DrvInit()
{
  int nRet=0; unsigned char *pqs=NULL;
  Cps=1; Cps1Qs=1;
  nCpsRomLen= 3*0x080000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 8*0x080000;
  nCpsZRomLen= 2*0x020000;
  nCpsQSamLen= 4*0x080000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000000,0,1); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,1,1); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x100000,2,1); if (nRet!=0) return 1; // Already byteswapped

  // Load graphics roms
  CpsLoadTiles(CpsGfx         , 3);
  CpsLoadTiles(CpsGfx+0x200000, 7);

  nCpsLcReg=0x4a; // Layer control register is at 0x4a
  CpsLayEn[1]=0x16;
  CpsLayEn[2]=0x16;
  CpsLayEn[3]=0x16;

  // Protection enable code by KEV
  CpsMProt[0]=0x00;
  CpsMProt[1]=0x00;
  CpsMProt[2]=0x00;
  CpsMProt[3]=0x00;

  // Board ID improvments by KEV. 0x00,0x0000
  CpsBID[0]=0x00;
  CpsBID[1]=0x00;
  CpsBID[2]=0x00;

  MaskAddr[0]=0x4c;
  MaskAddr[1]=0x4e;
  MaskAddr[2]=0x40;
  MaskAddr[3]=0x42;

  nRet=BurnLoadRom(CpsZRom,11,1);
  dino_decode();

  pqs=(unsigned char *)CpsQSam;
  nRet=BurnLoadRom(pqs         ,12,1);
  nRet=BurnLoadRom(pqs+0x080000,13,1);
  nRet=BurnLoadRom(pqs+0x100000,14,1);
  nRet=BurnLoadRom(pqs+0x180000,15,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

static int DinohInit()
{
  int nRet=0; unsigned char *pqs=NULL;
  Cps=1; Cps1Qs=1; Cps1QsHack=1;
  nCpsRomLen= 4*0x080000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 8*0x080000;
  nCpsZRomLen= 2*0x020000;
  nCpsQSamLen= 4*0x080000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000000,0,1); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,1,1); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x100000,2,1); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x180000,3,1); if (nRet!=0) return 1;

  // Patch Q-Sound Test
  CpsRom[0xaacf5]=0x4e;
  CpsRom[0xaacf4]=0x71;

  // Load graphics roms
  CpsLoadTiles(CpsGfx         , 4);
  CpsLoadTiles(CpsGfx+0x200000, 8);

  nCpsLcReg=0x66;
  CpsLayEn[1]=0x02;
  CpsLayEn[2]=0x04;
  CpsLayEn[3]=0x08;

  // Protection enable code by KEV
  CpsMProt[0]=0x00;
  CpsMProt[1]=0x00;
  CpsMProt[2]=0x00;
  CpsMProt[3]=0x00;

  // Board ID improvments by KEV. 0x00,0x0000
  CpsBID[0]=0x00;
  CpsBID[1]=0x00;
  CpsBID[2]=0x00;

  MaskAddr[0]=0x68;
  MaskAddr[1]=0x6a;
  MaskAddr[2]=0x6c;
  MaskAddr[3]=0x6e;

  nRet=BurnLoadRom(CpsZRom,12,1);
  dino_decode();

  pqs=(unsigned char *)CpsQSam;
  nRet=BurnLoadRom(pqs         ,13,1);
  nRet=BurnLoadRom(pqs+0x080000,14,1);
  nRet=BurnLoadRom(pqs+0x100000,15,1);
  nRet=BurnLoadRom(pqs+0x180000,16,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

static int DrvExit()
{
  CpsRunExit();

  CpsExit();
  nCpsQSamLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0; Cps1Qs=0; Cps1QsHack=0;
  return 0;
}

//===============================
//Cadillacs and Dinosaurs (World)
//===============================

// Rom information
static struct BurnRomInfo DinoRomDesc[] = {
	{ "cde_23a.rom",   0x80000, 0x8f4e585e, BRF_ESS | BRF_PRG }, // 0 swapped 68000 code
	{ "cde_22a.rom",   0x80000, 0x9278aa12, BRF_ESS | BRF_PRG }, // 1 swapped
	{ "cde_21a.rom",   0x80000, 0x66d23de2, BRF_ESS | BRF_PRG }, // 2 swapped

  // graphics:
	{ "cd_gfx01.rom",  0x80000, 0x8da4f917, BRF_GRA },			 // 3
	{ "cd_gfx03.rom",  0x80000, 0x6c40f603, BRF_GRA },
	{ "cd_gfx02.rom",  0x80000, 0x09c8fc2d, BRF_GRA },
	{ "cd_gfx04.rom",  0x80000, 0x637ff38f, BRF_GRA },
	{ "cd_gfx05.rom",  0x80000, 0x470befee, BRF_GRA },			 // 7
	{ "cd_gfx07.rom",  0x80000, 0x22bfb7a3, BRF_GRA },
	{ "cd_gfx06.rom",  0x80000, 0xe7599ac4, BRF_GRA },
	{ "cd_gfx08.rom",  0x80000, 0x211b4b15, BRF_GRA },

  // z80 rom
	{ "cd_q.rom",      0x20000, 0x605fdb0b, BRF_SND },			 // 11
  // samples
	{ "cd_q1.rom",     0x80000, 0x60927775, BRF_SND },
	{ "cd_q2.rom",     0x80000, 0x770f4c47, BRF_SND },
	{ "cd_q3.rom",     0x80000, 0x2f273ffc, BRF_SND },
	{ "cd_q4.rom",     0x80000, 0x2c67821d, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Dino) STD_ROM_FN(Dino)


struct BurnDriver BurnDrvCpsDino = {
	"dino", NULL, NULL, "1993",
	"Cadillacs & Dinosaurs (930201 etc)\0", NULL, "Capcom", "CPS1 / QSound",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,3,HARDWARE_CAPCOM_CPS1_QSOUND,
	NULL,DinoRomInfo,DinoRomName,DrvInputInfo, dinoDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//====================================
//Cadillacs Kyouryuu-Shinseiki (Japan)
//====================================

// Rom information
static struct BurnRomInfo DinojRomDesc[] = {
	{ "cdj-23a.8f",    0x80000, 0x5f3ece96, BRF_ESS | BRF_PRG }, // 0 swapped 68000 code
	{ "cdj-22a.7f",    0x80000, 0xa0d8de29, BRF_ESS | BRF_PRG }, // 1 swapped
	{ "cde_21a.rom",   0x80000, 0x66d23de2, BRF_ESS | BRF_PRG }, // 2 swapped

  // graphics:
	{ "cd_gfx01.rom",  0x80000, 0x8da4f917, BRF_GRA },			 // 3
	{ "cd_gfx03.rom",  0x80000, 0x6c40f603, BRF_GRA },
	{ "cd_gfx02.rom",  0x80000, 0x09c8fc2d, BRF_GRA },
	{ "cd_gfx04.rom",  0x80000, 0x637ff38f, BRF_GRA },
	{ "cd_gfx05.rom",  0x80000, 0x470befee, BRF_GRA },			 // 7
	{ "cd_gfx07.rom",  0x80000, 0x22bfb7a3, BRF_GRA },
	{ "cd_gfx06.rom",  0x80000, 0xe7599ac4, BRF_GRA },
	{ "cd_gfx08.rom",  0x80000, 0x211b4b15, BRF_GRA },

  // z80 rom
	{ "cd_q.rom",      0x20000, 0x605fdb0b, BRF_SND },			 // 11
  // samples
	{ "cd_q1.rom",     0x80000, 0x60927775, BRF_SND },
	{ "cd_q2.rom",     0x80000, 0x770f4c47, BRF_SND },
	{ "cd_q3.rom",     0x80000, 0x2f273ffc, BRF_SND },
	{ "cd_q4.rom",     0x80000, 0x2c67821d, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Dinoj) STD_ROM_FN(Dinoj)


struct BurnDriver BurnDrvCpsDinoj = {
	"dinoj", "dino", NULL, "1993",
	"Cadillacs Kyouryuu-Shinseiki (Cadillacs 930201 Japan)\0", NULL, "Capcom", "CPS1, QSound",
	L"Cadillacs \u6050\u7ADC\u65B0\u4E16\u7D00 (Cadillacs 930201 Japan)\0Cadillacs Kyouryuu-Shinseiki (Cadillacs 930201 Japan)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,3,HARDWARE_CAPCOM_CPS1_QSOUND,
	NULL,DinojRomInfo,DinojRomName,DrvInputInfo, dinoDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//====================================
//Cadillacs Kyouryuu-Shinseiki (US)
//====================================

// Rom information
static struct BurnRomInfo DinouRomDesc[] = {
	{ "cdu.23a",       0x80000, 0x7c2543cd, BRF_ESS | BRF_PRG }, // 0 swapped 68000 code
	{ "cdu.22a",       0x80000, 0xfab740a9, BRF_ESS | BRF_PRG }, // 1 swapped
	{ "cde_21a.rom",   0x80000, 0x66d23de2, BRF_ESS | BRF_PRG }, // 2 swapped

  // graphics:
	{ "cd_gfx01.rom",  0x80000, 0x8da4f917, BRF_GRA },			 // 3
	{ "cd_gfx03.rom",  0x80000, 0x6c40f603, BRF_GRA },
	{ "cd_gfx02.rom",  0x80000, 0x09c8fc2d, BRF_GRA },
	{ "cd_gfx04.rom",  0x80000, 0x637ff38f, BRF_GRA },
	{ "cd_gfx05.rom",  0x80000, 0x470befee, BRF_GRA },			 // 7
	{ "cd_gfx07.rom",  0x80000, 0x22bfb7a3, BRF_GRA },
	{ "cd_gfx06.rom",  0x80000, 0xe7599ac4, BRF_GRA },
	{ "cd_gfx08.rom",  0x80000, 0x211b4b15, BRF_GRA },

  // z80 rom
	{ "cd_q.rom",      0x20000, 0x605fdb0b, BRF_SND },			 // 11
  // samples
	{ "cd_q1.rom",     0x80000, 0x60927775, BRF_SND },
	{ "cd_q2.rom",     0x80000, 0x770f4c47, BRF_SND },
	{ "cd_q3.rom",     0x80000, 0x2f273ffc, BRF_SND },
	{ "cd_q4.rom",     0x80000, 0x2c67821d, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Dinou) STD_ROM_FN(Dinou)


struct BurnDriver BurnDrvCpsDinou = {
	"dinou", "dino", NULL, "1993",
	"Cadillacs & Dinosaurs (930201 USA)\0", NULL, "Capcom", "CPS1 / QSound",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,3,HARDWARE_CAPCOM_CPS1_QSOUND,
	NULL,DinouRomInfo,DinouRomName,DrvInputInfo, dinoDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

/*

static struct BurnInputInfo DinohInputList[]=
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp018+0, "p1 coin"  },
  {"P1 Start"      , BIT_DIGITAL, CpsInp018+4, "p1 start" },
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"    },
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"  },
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"  },
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right" },
  {"P1 Attack"     , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Jump"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"  },
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start" },
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"    },
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"  },
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"  },
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right" },
  {"P2 Attack"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Jump"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},

  {"P3 Coin"       , BIT_DIGITAL, CpsInp177+6, "p3 coin"  },
  {"P3 Start"      , BIT_DIGITAL, CpsInp177+7, "p3 start" },
  {"P3 Up"         , BIT_DIGITAL, CpsInp177+3, "p3 up"    },
  {"P3 Down"       , BIT_DIGITAL, CpsInp177+2, "p3 down"  },
  {"P3 Left"       , BIT_DIGITAL, CpsInp177+1, "p3 left"  },
  {"P3 Right"      , BIT_DIGITAL, CpsInp177+0, "p3 right" },
  {"P3 Attack"     , BIT_DIGITAL, CpsInp177+4, "p3 fire 1"},
  {"P3 Jump"       , BIT_DIGITAL, CpsInp177+5, "p3 fire 2"},

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Dinoh);

//==============================
//Cadillacs and Dinosaurs (Hack)
//==============================

// Rom information
static struct BurnRomInfo DinohRomDesc[] = {
	{ "cda_23h.rom",   0x80000, 0x8e2a9cf0, BRF_ESS | BRF_PRG }, // 0
	{ "cda_22h.rom",   0x80000, 0xf72cd219, BRF_ESS | BRF_PRG }, // 1
	{ "cda_21h.rom",   0x80000, 0xbc275b76, BRF_ESS | BRF_PRG }, // 2
	{ "cda_20h.rom",   0x80000, 0x8987c975, BRF_ESS | BRF_PRG }, // 3

	{ "cd_gfx01.rom",  0x80000, 0x8da4f917, BRF_GRA },			 // 4
	{ "cd_gfx03.rom",  0x80000, 0x6c40f603, BRF_GRA },
	{ "cd_gfx02.rom",  0x80000, 0x09c8fc2d, BRF_GRA },
	{ "cd_gfx04.rom",  0x80000, 0x637ff38f, BRF_GRA },
	{ "cd_gfx05.rom",  0x80000, 0x470befee, BRF_GRA },			 // 8
	{ "cd_gfx07.rom",  0x80000, 0x22bfb7a3, BRF_GRA },
	{ "cd_gfx06.rom",  0x80000, 0xe7599ac4, BRF_GRA },
	{ "cd_gfx08.rom",  0x80000, 0x211b4b15, BRF_GRA },

	{ "cd_q.rom",      0x20000, 0x605fdb0b, BRF_SND },			 // 12

	{ "cd_q1.rom",     0x80000, 0x60927775, BRF_SND },			 // 13
	{ "cd_q2.rom",     0x80000, 0x770f4c47, BRF_SND },			 // 14
	{ "cd_q3.rom",     0x80000, 0x2f273ffc, BRF_SND },			 // 15
	{ "cd_q4.rom",     0x80000, 0x2c67821d, BRF_SND },			 // 16
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Dinoh) STD_ROM_FN(Dinoh)


struct BurnDriver BurnDrvCpsDinoh = {
	"dinoh", "dino", NULL, "1993",
	"Cadillacs and Dinosaurs (Hack)\0", NULL, "Capcom", "CPS1 / QSound",
	NULL, NULL, NULL, NULL,
	BDF_CLONE | BDF_BOOTLEG,3,HARDWARE_CAPCOM_CPS1_QSOUND,
	NULL,DinohRomInfo,DinohRomName,DinohInputInfo, dinoDIPInfo,
	DinohInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==============================
//Cadillacs and Dinosaurs (Hack II)
//==============================

// Rom information
static struct BurnRomInfo Dinoh2RomDesc[] = {
	{ "kl2-l2.800",   0x100000, 0xC6AE7338, BRF_ESS | BRF_PRG }, // 0
	{ "kl2-r1.800",   0x100000, 0x4C70DCA7, BRF_ESS | BRF_PRG }, // 1

	{ "cd-a.160",     0x200000, 0x7e4F9FB3, BRF_GRA },			 // 2
	{ "cd-b.160",     0x200000, 0x89532d85, BRF_GRA },			 // 3

	{ "cd_q.rom",     0x020000, 0x605fdb0b, BRF_SND },			 // 4

	{ "cd_q1.rom",    0x080000, 0x60927775, BRF_SND },			 // 5
	{ "cd_q2.rom",    0x080000, 0x770f4c47, BRF_SND },			 // 6
	{ "cd_q3.rom",    0x080000, 0x2f273ffc, BRF_SND },			 // 7
	{ "cd_q4.rom",    0x080000, 0x2c67821d, BRF_SND },			 // 8
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Dinoh2);
STD_ROM_FN(Dinoh2);

static int Dinoh2Init()
{
  int nRet=0; unsigned char *pqs=NULL;
  Cps=1; Cps1Qs=1;
  nCpsRomLen= 4*0x080000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 8*0x080000;
  nCpsZRomLen= 2*0x020000;
  nCpsQSamLen= 4*0x080000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000000,0,1); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x100000,1,1); if (nRet!=0) return 1;

  // Load graphics roms
  CpsLoadTilesHack160(CpsGfx, 2);

  nCpsLcReg=0x4a; // Layer control register is at 0x4a
  CpsLayEn[1]=0x16;
  CpsLayEn[2]=0x16;
  CpsLayEn[3]=0x16;

  CpsMProt[0]=0x00;
  CpsMProt[1]=0x00;
  CpsMProt[2]=0x00;
  CpsMProt[3]=0x00;

  CpsBID[0]=0x00;
  CpsBID[1]=0x00;
  CpsBID[2]=0x00;

  MaskAddr[0]=0x4c;
  MaskAddr[1]=0x4e;
  MaskAddr[2]=0x40;
  MaskAddr[3]=0x42;

  nRet=BurnLoadRom(CpsZRom,4,1);
  dino_decode();

  pqs=(unsigned char *)CpsQSam;
  nRet=BurnLoadRom(pqs         ,5,1);
  nRet=BurnLoadRom(pqs+0x080000,6,1);
  nRet=BurnLoadRom(pqs+0x100000,7,1);
  nRet=BurnLoadRom(pqs+0x180000,8,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

struct BurnDriverD BurnDrvCpsDinoh2 = {
	"kl2d", "dino", NULL, "1993",
	"Cadillacs and Dinosaurs (Hack2)\0", "Missing GFX, No Sound", "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_CLONE | BDF_BOOTLEG,3,HARDWARE_CAPCOM_CPS1_QSOUND,
	NULL,Dinoh2RomInfo,Dinoh2RomName,DrvInputInfo, dinoDIPInfo,
	Dinoh2Init,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

*/

