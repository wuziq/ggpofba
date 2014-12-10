#include "cps.h"
// Saturday Night Slam Masters

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
  {"P1 Pin"        , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Attack"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Jump"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Pin"        , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

  {"P3 Coin"       , BIT_DIGITAL, CpsInpc001+6, "p3 coin"},
  {"P3 Start"      , BIT_DIGITAL, CpsInpc001+7, "p3 start"},
  {"P3 Up"         , BIT_DIGITAL, CpsInpc001+3, "p3 up"},
  {"P3 Down"       , BIT_DIGITAL, CpsInpc001+2, "p3 down"},
  {"P3 Left"       , BIT_DIGITAL, CpsInpc001+1, "p3 left"},
  {"P3 Right"      , BIT_DIGITAL, CpsInpc001+0, "p3 right"},
  {"P3 Attack"     , BIT_DIGITAL, CpsInpc001+4, "p3 fire 1"},
  {"P3 Jump"       , BIT_DIGITAL, CpsInpc001+5, "p3 fire 2"},
  {"P3 Pin"        , BIT_DIGITAL, CpsInp001+7 , "p3 fire 3"},

  {"P4 Coin"       , BIT_DIGITAL, CpsInpc003+6, "p4 coin"},
  {"P4 Start"      , BIT_DIGITAL, CpsInpc003+7, "p4 start"},
  {"P4 Up"         , BIT_DIGITAL, CpsInpc003+3, "p4 up"},
  {"P4 Down"       , BIT_DIGITAL, CpsInpc003+2, "p4 down"},
  {"P4 Left"       , BIT_DIGITAL, CpsInpc003+1, "p4 left"},
  {"P4 Right"      , BIT_DIGITAL, CpsInpc003+0, "p4 right"},
  {"P4 Attack"     , BIT_DIGITAL, CpsInpc003+4, "p4 fire 1"},
  {"P4 Jump"       , BIT_DIGITAL, CpsInpc003+5, "p4 fire 2"},
  {"P4 Pin"        , BIT_DIGITAL, CpsInp000+7 , "p4 fire 3"},

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo slammastDIPList[]=
{
	// Defaults
	{0x23, 0xff, 0xff, 0x00, NULL                },

	// Dip C
	{0   , 0xfe, 0   , 2   , "Freeze"                 },
	{0x23, 0x01, 0x08, 0x08, "Off"                    },
	{0x23, 0x01, 0x08, 0x00, "On"                     },
};

STDDIPINFO(slammast);


static int DrvExit()
{

  CpsRunExit();

  CpsExit();
  nCpsQSamLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0; Cps1Qs=0;
  return 0;
}

//================================
//Saturday Night Slam Masters Init
//================================

static int DrvInit()
{
  int nRet=0; unsigned char *pqs=NULL;
  Cps=1; Cps1Qs=1;
  nCpsRomLen= 4*0x080000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 12*0x080000;
  nCpsZRomLen= 2*0x020000;
  nCpsQSamLen= 8*0x080000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000000,0,1); if (nRet!=0) return 1; // Already byteswapped
  nRet=BurnLoadRom(CpsRom+0x080001,1,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,2,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x0c0001,3,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x0c0000,4,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x100000,5,1); if (nRet!=0) return 1; // Already byteswapped
  nRet=BurnLoadRom(CpsRom+0x180000,6,1); if (nRet!=0) return 1; // Already byteswapped

// Load graphics roms
  CpsLoadTiles(CpsGfx         , 7);
  CpsLoadTiles(CpsGfx+0x200000, 11);
  CpsLoadTiles(CpsGfx+0x400000, 15);

  nCpsLcReg=0x56; // Layer control register is at 0x56
  CpsLayEn[1]=0x04;
  CpsLayEn[2]=0x08;
  CpsLayEn[3]=0x10;

  // Protection enable code by KEV
  CpsMProt[0]=0x00;
  CpsMProt[1]=0x00;
  CpsMProt[2]=0x00;
  CpsMProt[3]=0x00;

  // Start of Board ID improvments by KEV. 0x6e,0x0c01
  CpsBID[0]=0x6e;
  CpsBID[1]=0x0c;
  CpsBID[2]=0x01;
  //end

  MaskAddr[0]=0x40;
  MaskAddr[1]=0x42;
  MaskAddr[2]=0x68;
  MaskAddr[3]=0x6a;

  nRet=BurnLoadRom(CpsZRom,19,1);
  slammast_decode();
  nRet=BurnLoadRom(CpsEncZRom,19,1);

  pqs=(unsigned char *)CpsQSam;
  nRet=BurnLoadRom(pqs         ,20,1);
  nRet=BurnLoadRom(pqs+0x080000,21,1);
  nRet=BurnLoadRom(pqs+0x100000,22,1);
  nRet=BurnLoadRom(pqs+0x180000,23,1);
  nRet=BurnLoadRom(pqs+0x200000,24,1);
  nRet=BurnLoadRom(pqs+0x280000,25,1);
  nRet=BurnLoadRom(pqs+0x300000,26,1);
  nRet=BurnLoadRom(pqs+0x380000,27,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//======================
//Muscle Bomber Duo Init
//======================

static int DuoInit()
{
  int nRet=0; unsigned char *pqs=NULL;
  Cps=1; Cps1Qs=1;
  nCpsRomLen= 4*0x080000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 12*0x080000;
  nCpsZRomLen= 2*0x020000;
  nCpsQSamLen= 8*0x080000;
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
  nRet=BurnLoadRom(CpsRom+0x100000,8,1); if (nRet!=0) return 1; // Already byteswapped
  nRet=BurnLoadRom(CpsRom+0x180000,9,1); if (nRet!=0) return 1; // Already byteswapped

  // Load graphics roms
  CpsLoadTiles(CpsGfx         , 10);
  CpsLoadTiles(CpsGfx+0x200000, 14);
  CpsLoadTiles(CpsGfx+0x400000, 18);

  nCpsLcReg=0x6a; // Layer control register is at 0x6a
  CpsLayEn[1]=0x04;
  CpsLayEn[2]=0x08;
  CpsLayEn[3]=0x10;

  // Protection enable code by KEV
  CpsMProt[0]=0x00;
  CpsMProt[1]=0x00;
  CpsMProt[2]=0x00;
  CpsMProt[3]=0x00;

  // Start of Board ID improvments by KEV. 0x5e,0x0c02
  CpsBID[0]=0x5e;
  CpsBID[1]=0x0c;
  CpsBID[2]=0x02;
  //end

  MaskAddr[0]=0x6c;
  MaskAddr[1]=0x6e;
  MaskAddr[2]=0x70;
  MaskAddr[3]=0x72;

  nRet=BurnLoadRom(CpsZRom,22,1);
  slammast_decode();
  nRet=BurnLoadRom(CpsEncZRom,22,1);

  pqs=(unsigned char *)CpsQSam;
  nRet=BurnLoadRom(pqs         ,23,1);
  nRet=BurnLoadRom(pqs+0x080000,24,1);
  nRet=BurnLoadRom(pqs+0x100000,25,1);
  nRet=BurnLoadRom(pqs+0x180000,26,1);
  nRet=BurnLoadRom(pqs+0x200000,27,1);
  nRet=BurnLoadRom(pqs+0x280000,28,1);
  nRet=BurnLoadRom(pqs+0x300000,29,1);
  nRet=BurnLoadRom(pqs+0x380000,30,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//===================================
//Saturday Night Slam Masters (World)
//===================================

// Rom information
static struct BurnRomInfo SlammastRomDesc[] = {
	{ "mbe_23e.rom",   0x80000, 0x5394057a, BRF_ESS | BRF_PRG }, // 0 swapped
	{ "mbe_24b.rom",   0x20000, 0x95d5e729, BRF_ESS | BRF_PRG }, // 1 even 68000 code
	{ "mbe_28b.rom",   0x20000, 0xb1c7cbcb, BRF_ESS | BRF_PRG }, // 2 odd
	{ "mbe_25b.rom",   0x20000, 0xa50d3fd4, BRF_ESS | BRF_PRG }, // 3 even 68000 code
	{ "mbe_29b.rom",   0x20000, 0x08e32e56, BRF_ESS | BRF_PRG }, // 4 odd
	{ "mbe_21a.rom",   0x80000, 0xd5007b05, BRF_ESS | BRF_PRG }, // 5 swapped
	{ "mbe_20a.rom",   0x80000, 0xaeb557b0, BRF_ESS | BRF_PRG }, // 6 swapped

  // graphics:
	{ "mb_gfx01.rom",  0x80000, 0x41468e06, BRF_GRA },			 // 7
	{ "mb_gfx03.rom",  0x80000, 0xf453aa9e, BRF_GRA },
	{ "mb_gfx02.rom",  0x80000, 0x2ffbfea8, BRF_GRA },
	{ "mb_gfx04.rom",  0x80000, 0x1eb9841d, BRF_GRA },
	{ "mb_05.bin",     0x80000, 0x506b9dc9, BRF_GRA },			 // 11
	{ "mb_07.bin",     0x80000, 0xaff8c2fb, BRF_GRA },
	{ "mb_06.bin",     0x80000, 0xb76c70e9, BRF_GRA },
	{ "mb_08.bin",     0x80000, 0xe60c9556, BRF_GRA },
	{ "mb_10.bin",     0x80000, 0x97976ff5, BRF_GRA },			 // 15
	{ "mb_12.bin",     0x80000, 0xb350a840, BRF_GRA },
	{ "mb_11.bin",     0x80000, 0x8fb94743, BRF_GRA },
	{ "mb_13.bin",     0x80000, 0xda810d5f, BRF_GRA },

  // z80 rom
	{ "mb_qa.rom",     0x20000, 0xe21a03c4, BRF_ESS | BRF_PRG }, // 19
  // samples
	{ "mb_q1.bin",     0x80000, 0x0630c3ce, BRF_SND },
	{ "mb_q2.bin",     0x80000, 0x354f9c21, BRF_SND },
	{ "mb_q3.bin",     0x80000, 0x7838487c, BRF_SND },
	{ "mb_q4.bin",     0x80000, 0xab66e087, BRF_SND },
	{ "mb_q5.bin",     0x80000, 0xc789fef2, BRF_SND },
	{ "mb_q6.bin",     0x80000, 0xecb81b61, BRF_SND },
	{ "mb_q7.bin",     0x80000, 0x041e49ba, BRF_SND },
	{ "mb_q8.bin",     0x80000, 0x59fe702a, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Slammast) STD_ROM_FN(Slammast)

struct BurnDriver BurnDrvCpsSlammast = {
	"slammast", NULL, NULL, "1993",
	"Saturday Night Slam Masters (Slam Masters 930713 etc)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,4,HARDWARE_CAPCOM_CPS1,
	NULL,SlammastRomInfo,SlammastRomName,DrvInputInfo, slammastDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=================================
//Saturday Night Slam Masters (USA)
//=================================

// Rom information
static struct BurnRomInfo SlammasuRomDesc[] = {
	{ "mbu-23e.rom",   0x80000, 0x224f0062, BRF_ESS | BRF_PRG }, // 0 swapped
	{ "mbe_24b.rom",   0x20000, 0x95d5e729, BRF_ESS | BRF_PRG }, // 1 even 68000 code
	{ "mbe_28b.rom",   0x20000, 0xb1c7cbcb, BRF_ESS | BRF_PRG }, // 2 odd
	{ "mbe_25b.rom",   0x20000, 0xa50d3fd4, BRF_ESS | BRF_PRG }, // 3 even 68000 code
	{ "mbe_29b.rom",   0x20000, 0x08e32e56, BRF_ESS | BRF_PRG }, // 4 odd
	{ "mbe_21a.rom",   0x80000, 0xd5007b05, BRF_ESS | BRF_PRG }, // 5 swapped
	{ "mbu-20a.rom",   0x80000, 0xfc848af5, BRF_ESS | BRF_PRG }, // 6 swapped

  // graphics:
	{ "mb_gfx01.rom",  0x80000, 0x41468e06, BRF_GRA },			 // 7
	{ "mb_gfx03.rom",  0x80000, 0xf453aa9e, BRF_GRA },
	{ "mb_gfx02.rom",  0x80000, 0x2ffbfea8, BRF_GRA },
	{ "mb_gfx04.rom",  0x80000, 0x1eb9841d, BRF_GRA },
	{ "mb_05.bin",     0x80000, 0x506b9dc9, BRF_GRA },			 // 11
	{ "mb_07.bin",     0x80000, 0xaff8c2fb, BRF_GRA },
	{ "mb_06.bin",     0x80000, 0xb76c70e9, BRF_GRA },
	{ "mb_08.bin",     0x80000, 0xe60c9556, BRF_GRA },
	{ "mb_10.bin",     0x80000, 0x97976ff5, BRF_GRA },			 // 15
	{ "mb_12.bin",     0x80000, 0xb350a840, BRF_GRA },
	{ "mb_11.bin",     0x80000, 0x8fb94743, BRF_GRA },
	{ "mb_13.bin",     0x80000, 0xda810d5f, BRF_GRA },

  // z80 rom
	{ "mb_qa.rom",     0x20000, 0xe21a03c4, BRF_ESS | BRF_PRG }, // 19
  // samples
	{ "mb_q1.bin",     0x80000, 0x0630c3ce, BRF_SND },
	{ "mb_q2.bin",     0x80000, 0x354f9c21, BRF_SND },
	{ "mb_q3.bin",     0x80000, 0x7838487c, BRF_SND },
	{ "mb_q4.bin",     0x80000, 0xab66e087, BRF_SND },
	{ "mb_q5.bin",     0x80000, 0xc789fef2, BRF_SND },
	{ "mb_q6.bin",     0x80000, 0xecb81b61, BRF_SND },
	{ "mb_q7.bin",     0x80000, 0x041e49ba, BRF_SND },
	{ "mb_q8.bin",     0x80000, 0x59fe702a, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Slammasu) STD_ROM_FN(Slammasu)

struct BurnDriver BurnDrvCpsSlammasu = {
	"slammasu", "slammast", NULL, "1993",
	"Saturday Night Slam Masters (slam masters 930713 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS1,
	NULL,SlammasuRomInfo,SlammasuRomName,DrvInputInfo, slammastDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==========================================
//Muscle Bomber - The Body Explosion (Japan)
//==========================================

// Rom information
static struct BurnRomInfo MbomberjRomDesc[] = {
	{ "mbj23e",        0x80000, 0x0d06036a, BRF_ESS | BRF_PRG }, // 0 swapped
	{ "mbe_24b.rom",   0x20000, 0x95d5e729, BRF_ESS | BRF_PRG }, // 1 even 68000 code
	{ "mbe_28b.rom",   0x20000, 0xb1c7cbcb, BRF_ESS | BRF_PRG }, // 2 odd
	{ "mbe_25b.rom",   0x20000, 0xa50d3fd4, BRF_ESS | BRF_PRG }, // 3 even 68000 code
	{ "mbe_29b.rom",   0x20000, 0x08e32e56, BRF_ESS | BRF_PRG }, // 4 odd
	{ "mbe_21a.rom",   0x80000, 0xd5007b05, BRF_ESS | BRF_PRG }, // 5 swapped
	{ "mbe_20a.rom",   0x80000, 0xaeb557b0, BRF_ESS | BRF_PRG }, // 6 swapped

  // graphics:
	{ "mbj_01.bin",    0x80000, 0xa53b1c81, BRF_GRA },			 // 7
	{ "mbj_03.bin",    0x80000, 0x23fe10f6, BRF_GRA },
	{ "mbj_02.bin",    0x80000, 0xcb866c2f, BRF_GRA },
	{ "mbj_04.bin",    0x80000, 0xc9143e75, BRF_GRA },
	{ "mb_05.bin",     0x80000, 0x506b9dc9, BRF_GRA },			 // 11
	{ "mb_07.bin",     0x80000, 0xaff8c2fb, BRF_GRA },
	{ "mb_06.bin",     0x80000, 0xb76c70e9, BRF_GRA },
	{ "mb_08.bin",     0x80000, 0xe60c9556, BRF_GRA },
	{ "mb_10.bin",     0x80000, 0x97976ff5, BRF_GRA },			 // 15
	{ "mb_12.bin",     0x80000, 0xb350a840, BRF_GRA },
	{ "mb_11.bin",     0x80000, 0x8fb94743, BRF_GRA },
	{ "mb_13.bin",     0x80000, 0xda810d5f, BRF_GRA },

  // z80 rom
	{ "mb_qa.rom",     0x20000, 0xe21a03c4, BRF_ESS | BRF_PRG }, // 19
  // samples
	{ "mb_q1.bin",     0x80000, 0x0630c3ce, BRF_SND },
	{ "mb_q2.bin",     0x80000, 0x354f9c21, BRF_SND },
	{ "mb_q3.bin",     0x80000, 0x7838487c, BRF_SND },
	{ "mb_q4.bin",     0x80000, 0xab66e087, BRF_SND },
	{ "mb_q5.bin",     0x80000, 0xc789fef2, BRF_SND },
	{ "mb_q6.bin",     0x80000, 0xecb81b61, BRF_SND },
	{ "mb_q7.bin",     0x80000, 0x041e49ba, BRF_SND },
	{ "mb_q8.bin",     0x80000, 0x59fe702a, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Mbomberj) STD_ROM_FN(Mbomberj)

struct BurnDriver BurnDrvCpsMbomberj = {
	"mbomberj", "slammast", NULL, "1993",
	"Muscle Bomber - the body explosion (930713 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS1,
	NULL,MbomberjRomInfo,MbomberjRomName,DrvInputInfo, slammastDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//================================================
//Muscle Bomber Duo - Ultimate Team Battle (World)
//================================================

// Rom information
static struct BurnRomInfo MbombrdRomDesc[] = {
	{ "mbd_26.bin",    0x20000, 0x72b7451c, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "mbde_30.rom",   0x20000, 0xa036dc16, BRF_ESS | BRF_PRG }, // 1 odd
	{ "mbd_27.bin",    0x20000, 0x4086f534, BRF_ESS | BRF_PRG }, // 2 even 68000 code
	{ "mbd_31.bin",    0x20000, 0x085f47f0, BRF_ESS | BRF_PRG }, // 3 odd
	{ "mbd_24.bin",    0x20000, 0xc20895a5, BRF_ESS | BRF_PRG }, // 4 even 68000 code
	{ "mbd_28.bin",    0x20000, 0x2618d5e1, BRF_ESS | BRF_PRG }, // 5 odd
	{ "mbd_25.bin",    0x20000, 0x9bdb6b11, BRF_ESS | BRF_PRG }, // 6 even 68000 code
	{ "mbd_29.bin",    0x20000, 0x3f52d5e5, BRF_ESS | BRF_PRG }, // 7 odd
	{ "mbd_21.bin",    0x80000, 0x690c026a, BRF_ESS | BRF_PRG }, // 8 swapped
	{ "mbd_20.bin",    0x80000, 0xb8b2139b, BRF_ESS | BRF_PRG }, // 9 swapped

  // graphics:
	{ "mb_gfx01.rom",  0x80000, 0x41468e06, BRF_GRA },			 // 10
	{ "mb_gfx03.rom",  0x80000, 0xf453aa9e, BRF_GRA },
	{ "mb_gfx02.rom",  0x80000, 0x2ffbfea8, BRF_GRA },
	{ "mb_gfx04.rom",  0x80000, 0x1eb9841d, BRF_GRA },
	{ "mb_05.bin",     0x80000, 0x506b9dc9, BRF_GRA },			 // 14
	{ "mb_07.bin",     0x80000, 0xaff8c2fb, BRF_GRA },
	{ "mb_06.bin",     0x80000, 0xb76c70e9, BRF_GRA },
	{ "mb_08.bin",     0x80000, 0xe60c9556, BRF_GRA },
	{ "mb_10.bin",     0x80000, 0x97976ff5, BRF_GRA },			 // 18
	{ "mb_12.bin",     0x80000, 0xb350a840, BRF_GRA },
	{ "mb_11.bin",     0x80000, 0x8fb94743, BRF_GRA },
	{ "mb_13.bin",     0x80000, 0xda810d5f, BRF_GRA },

  // z80 rom
	{ "mb_q.bin",      0x20000, 0xd6fa76d1, BRF_ESS | BRF_PRG }, // 22
  // samples
	{ "mb_q1.bin",     0x80000, 0x0630c3ce, BRF_SND },
	{ "mb_q2.bin",     0x80000, 0x354f9c21, BRF_SND },
	{ "mb_q3.bin",     0x80000, 0x7838487c, BRF_SND },
	{ "mb_q4.bin",     0x80000, 0xab66e087, BRF_SND },
	{ "mb_q5.bin",     0x80000, 0xc789fef2, BRF_SND },
	{ "mb_q6.bin",     0x80000, 0xecb81b61, BRF_SND },
	{ "mb_q7.bin",     0x80000, 0x041e49ba, BRF_SND },
	{ "mb_q8.bin",     0x80000, 0x59fe702a, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Mbombrd) STD_ROM_FN(Mbombrd)

struct BurnDriver BurnDrvCpsMbombrd = {
	"mbombrd", "slammast", NULL, "1993",
	"Muscle Bomber Duo - ultimate team battle (931206 etc)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS1,
	NULL,MbombrdRomInfo,MbombrdRomName,DrvInputInfo, slammastDIPInfo,
	DuoInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//============================================
//Muscle Bomber Duo - Heat Up Warriors (Japan)
//============================================

// Rom information
static struct BurnRomInfo MbombrdjRomDesc[] = {
	{ "mbd_26.bin",    0x20000, 0x72b7451c, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "mbdj_30.bin",   0x20000, 0xbeff31cf, BRF_ESS | BRF_PRG }, // 1 odd
	{ "mbd_27.bin",    0x20000, 0x4086f534, BRF_ESS | BRF_PRG }, // 2 even 68000 code
	{ "mbd_31.bin",    0x20000, 0x085f47f0, BRF_ESS | BRF_PRG }, // 3 odd
	{ "mbd_24.bin",    0x20000, 0xc20895a5, BRF_ESS | BRF_PRG }, // 4 even 68000 code
	{ "mbd_28.bin",    0x20000, 0x2618d5e1, BRF_ESS | BRF_PRG }, // 5 odd
	{ "mbd_25.bin",    0x20000, 0x9bdb6b11, BRF_ESS | BRF_PRG }, // 6 even 68000 code
	{ "mbd_29.bin",    0x20000, 0x3f52d5e5, BRF_ESS | BRF_PRG }, // 7 odd
	{ "mbd_21.bin",    0x80000, 0x690c026a, BRF_ESS | BRF_PRG }, // 8 swapped
	{ "mbd_20.bin",    0x80000, 0xb8b2139b, BRF_ESS | BRF_PRG }, // 9 swapped

  // graphics:
	{ "mbj_01.bin",    0x80000, 0xa53b1c81, BRF_GRA },			 // 10
	{ "mbj_03.bin",    0x80000, 0x23fe10f6, BRF_GRA },
	{ "mbj_02.bin",    0x80000, 0xcb866c2f, BRF_GRA },
	{ "mbj_04.bin",    0x80000, 0xc9143e75, BRF_GRA },
	{ "mb_05.bin",     0x80000, 0x506b9dc9, BRF_GRA },			 // 14
	{ "mb_07.bin",     0x80000, 0xaff8c2fb, BRF_GRA },
	{ "mb_06.bin",     0x80000, 0xb76c70e9, BRF_GRA },
	{ "mb_08.bin",     0x80000, 0xe60c9556, BRF_GRA },
	{ "mb_10.bin",     0x80000, 0x97976ff5, BRF_GRA },			 // 18
	{ "mb_12.bin",     0x80000, 0xb350a840, BRF_GRA },
	{ "mb_11.bin",     0x80000, 0x8fb94743, BRF_GRA },
	{ "mb_13.bin",     0x80000, 0xda810d5f, BRF_GRA },

  // z80 rom
	{ "mb_q.bin",      0x20000, 0xd6fa76d1, BRF_ESS | BRF_PRG }, // 22
  // samples
	{ "mb_q1.bin",     0x80000, 0x0630c3ce, BRF_SND },
	{ "mb_q2.bin",     0x80000, 0x354f9c21, BRF_SND },
	{ "mb_q3.bin",     0x80000, 0x7838487c, BRF_SND },
	{ "mb_q4.bin",     0x80000, 0xab66e087, BRF_SND },
	{ "mb_q5.bin",     0x80000, 0xc789fef2, BRF_SND },
	{ "mb_q6.bin",     0x80000, 0xecb81b61, BRF_SND },
	{ "mb_q7.bin",     0x80000, 0x041e49ba, BRF_SND },
	{ "mb_q8.bin",     0x80000, 0x59fe702a, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Mbombrdj) STD_ROM_FN(Mbombrdj)

struct BurnDriver BurnDrvCpsMbombrdj = {
	"mbombrdj", "slammast", NULL, "1993",
	"Muscle Bomber Duo - heat up warriors (931206 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS1,
	NULL,MbombrdjRomInfo,MbombrdjRomName,DrvInputInfo, slammastDIPInfo,
	DuoInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
