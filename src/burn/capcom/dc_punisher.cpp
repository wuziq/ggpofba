// The Punisher

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

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo punishDIPList[]=
{
	// Defaults
	{0x13, 0xff, 0xff, 0x00, NULL                },

	// Dip C
	{0   , 0xfe, 0   , 2   , "Freeze"                 },
	{0x13, 0x01, 0x08, 0x00, "Off"                    },
	{0x13, 0x01, 0x08, 0x08, "On"                     },
};

STDDIPINFO(punish);


static int DrvExit()
{

  CpsRunExit();

  CpsExit();
  nCpsQSamLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps=0; Cps1Qs=0;
  return 0;
}

//=============
//Punisher Init
//=============

static int PunisherInit()
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
  nRet=BurnLoadRom(CpsRom+0x000001,0,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x000000,1,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040001,2,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040000,3,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080001,4,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,5,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x0c0001,6,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x0c0000,7,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x100000,8,1); if (nRet!=0) return 1; // Already byteswapped

  // Load graphics roms
  CpsLoadTiles(CpsGfx         , 9);
  CpsLoadTiles(CpsGfx+0x200000, 13);

  nCpsLcReg=0x52; // Layer control register is at 0x52
  CpsLayEn[1]=0x04;
  CpsLayEn[2]=0x02;
  CpsLayEn[3]=0x20;

  // Protection enable code by KEV
  CpsMProt[0]=0x00;
  CpsMProt[1]=0x00;
  CpsMProt[2]=0x00;
  CpsMProt[3]=0x00;

  // Start of Board ID improvments by KEV. 0x4e,0x0c00
  CpsBID[0]=0x4e;
  CpsBID[1]=0x0c;
  CpsBID[2]=0x00;

  MaskAddr[0]=0x54;
  MaskAddr[1]=0x56;
  MaskAddr[2]=0x48;
  MaskAddr[3]=0x4a;

  nRet=BurnLoadRom(CpsZRom,17,1);
  punisher_decode();

  pqs=(unsigned char *)CpsQSam;
  nRet=BurnLoadRom(pqs         ,18,1);
  nRet=BurnLoadRom(pqs+0x080000,19,1);
  nRet=BurnLoadRom(pqs+0x100000,20,1);
  nRet=BurnLoadRom(pqs+0x180000,21,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//=====================
//Punisher (Japan) Init
//=====================

static int PunishrjInit()
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

  nCpsLcReg=0x52; // Layer control register is at 0x52
  CpsLayEn[1]=0x04;
  CpsLayEn[2]=0x02;
  CpsLayEn[3]=0x20;

  // Protection enable code by KEV
  CpsMProt[0]=0x00;
  CpsMProt[1]=0x00;
  CpsMProt[2]=0x00;
  CpsMProt[3]=0x00;

  // Start of Board ID improvments by KEV. 0x4e,0x0c00
  CpsBID[0]=0x4e;
  CpsBID[1]=0x0c;
  CpsBID[2]=0x00;

  MaskAddr[0]=0x54;
  MaskAddr[1]=0x56;
  MaskAddr[2]=0x48;
  MaskAddr[3]=0x4a;

  nRet=BurnLoadRom(CpsZRom,11,1);
  punisher_decode();

  pqs=(unsigned char *)CpsQSam;
  nRet=BurnLoadRom(pqs         ,12,1);
  nRet=BurnLoadRom(pqs+0x080000,13,1);
  nRet=BurnLoadRom(pqs+0x100000,14,1);
  nRet=BurnLoadRom(pqs+0x180000,15,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//====================
//The Punisher (World)
//====================

// Rom information
static struct BurnRomInfo PunisherRomDesc[] = {
	{ "pse_26.rom",    0x20000, 0x389a99d2, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "pse_30.rom",    0x20000, 0x68fb06ac, BRF_ESS | BRF_PRG }, // 1 odd
	{ "pse_27.rom",    0x20000, 0x3eb181c3, BRF_ESS | BRF_PRG }, // 2 even 68000 code
	{ "pse_31.rom",    0x20000, 0x37108e7b, BRF_ESS | BRF_PRG }, // 3 odd
	{ "pse_24.rom",    0x20000, 0x0f434414, BRF_ESS | BRF_PRG }, // 4 even 68000 code
	{ "pse_28.rom",    0x20000, 0xb732345d, BRF_ESS | BRF_PRG }, // 5 odd
	{ "pse_25.rom",    0x20000, 0xb77102e2, BRF_ESS | BRF_PRG }, // 6 even 68000 code
	{ "pse_29.rom",    0x20000, 0xec037bce, BRF_ESS | BRF_PRG }, // 7 odd
	{ "ps_21.rom",     0x80000, 0x8affa5a9, BRF_ESS | BRF_PRG }, // 8 swapped

  // graphics:
	{ "ps_gfx1.rom",   0x80000, 0x77b7ccab, BRF_GRA },			 // 9
	{ "ps_gfx3.rom",   0x80000, 0x0122720b, BRF_GRA },
	{ "ps_gfx2.rom",   0x80000, 0x64fa58d4, BRF_GRA },
	{ "ps_gfx4.rom",   0x80000, 0x60da42c8, BRF_GRA },
	{ "ps_gfx5.rom",   0x80000, 0xc54ea839, BRF_GRA },			 // 13
	{ "ps_gfx7.rom",   0x80000, 0x04c5acbd, BRF_GRA },
	{ "ps_gfx6.rom",   0x80000, 0xa544f4cc, BRF_GRA },
	{ "ps_gfx8.rom",   0x80000, 0x8f02f436, BRF_GRA },

  // z80 rom
	{ "ps_q.rom",      0x20000, 0x49ff4446, BRF_SND },			 // 17
  // samples
	{ "ps_q1.rom",     0x80000, 0x31fd8726, BRF_SND },
	{ "ps_q2.rom",     0x80000, 0x980a9eef, BRF_SND },
	{ "ps_q3.rom",     0x80000, 0x0dd44491, BRF_SND },
	{ "ps_q4.rom",     0x80000, 0xbed42f03, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Punisher) STD_ROM_FN(Punisher)

struct BurnDriver BurnDrvCpsPunisher = {
	"punisher", NULL, NULL, "1993",
	"The Punisher (930422 etc)\0", NULL, "Capcom", "CPS1 / QSound",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS1_QSOUND,
	NULL,PunisherRomInfo,PunisherRomName,DrvInputInfo, punishDIPInfo,
	PunisherInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==================
//The Punisher (USA)
//==================

// Rom information
static struct BurnRomInfo PunishruRomDesc[] = {
	{ "psu26.rom",     0x20000, 0x9236d121, BRF_ESS | BRF_PRG }, // 0 even 68000 code
	{ "psu30.rom",     0x20000, 0x8320e501, BRF_ESS | BRF_PRG }, // 1 odd
	{ "psu27.rom",     0x20000, 0x61c960a1, BRF_ESS | BRF_PRG }, // 2 even 68000 code
	{ "psu31.rom",     0x20000, 0x78d4c298, BRF_ESS | BRF_PRG }, // 3 odd
	{ "psu24.rom",     0x20000, 0x1cfecad7, BRF_ESS | BRF_PRG }, // 4 even 68000 code
	{ "psu28.rom",     0x20000, 0xbdf921c1, BRF_ESS | BRF_PRG }, // 5 odd
	{ "psu25.rom",     0x20000, 0xc51acc94, BRF_ESS | BRF_PRG }, // 6 even 68000 code
	{ "psu29.rom",     0x20000, 0x52dce1ca, BRF_ESS | BRF_PRG }, // 7 odd
	{ "ps_21.rom",     0x80000, 0x8affa5a9, BRF_ESS | BRF_PRG }, // 8 swapped

  // graphics:
	{ "ps_gfx1.rom",   0x80000, 0x77b7ccab, BRF_GRA },			 // 9
	{ "ps_gfx3.rom",   0x80000, 0x0122720b, BRF_GRA },
	{ "ps_gfx2.rom",   0x80000, 0x64fa58d4, BRF_GRA },
	{ "ps_gfx4.rom",   0x80000, 0x60da42c8, BRF_GRA },
	{ "ps_gfx5.rom",   0x80000, 0xc54ea839, BRF_GRA },			 // 13
	{ "ps_gfx7.rom",   0x80000, 0x04c5acbd, BRF_GRA },
	{ "ps_gfx6.rom",   0x80000, 0xa544f4cc, BRF_GRA },
	{ "ps_gfx8.rom",   0x80000, 0x8f02f436, BRF_GRA },

  // z80 rom
	{ "ps_q.rom",      0x20000, 0x49ff4446, BRF_SND },			 // 17
  // samples
	{ "ps_q1.rom",     0x80000, 0x31fd8726, BRF_SND },
	{ "ps_q2.rom",     0x80000, 0x980a9eef, BRF_SND },
	{ "ps_q3.rom",     0x80000, 0x0dd44491, BRF_SND },
	{ "ps_q4.rom",     0x80000, 0xbed42f03, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Punishru) STD_ROM_FN(Punishru)

struct BurnDriver BurnDrvCpsPunishru = {
	"punishru", "punisher", NULL, "1993",
	"The Punisher (930422 USA)\0", NULL, "Capcom", "CPS1 / QSound",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1_QSOUND,
	NULL,PunishruRomInfo,PunishruRomName,DrvInputInfo, punishDIPInfo,
	PunisherInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//====================
//The Punisher (Japan)
//====================

// Rom information
static struct BurnRomInfo PunishrjRomDesc[] = {
	{ "psj23.bin",     0x80000, 0x6b2fda52, BRF_ESS | BRF_PRG }, // 0 swapped 68000 code
	{ "psj22.bin",     0x80000, 0xe01036bc, BRF_ESS | BRF_PRG }, // 1 swapped
	{ "ps_21.rom",     0x80000, 0x8affa5a9, BRF_ESS | BRF_PRG }, // 2 swapped

  // graphics:
	{ "ps_gfx1.rom",   0x80000, 0x77b7ccab, BRF_GRA },			 // 3
	{ "ps_gfx3.rom",   0x80000, 0x0122720b, BRF_GRA },
	{ "ps_gfx2.rom",   0x80000, 0x64fa58d4, BRF_GRA },
	{ "ps_gfx4.rom",   0x80000, 0x60da42c8, BRF_GRA },
	{ "ps_gfx5.rom",   0x80000, 0xc54ea839, BRF_GRA },			 // 7
	{ "ps_gfx7.rom",   0x80000, 0x04c5acbd, BRF_GRA },
	{ "ps_gfx6.rom",   0x80000, 0xa544f4cc, BRF_GRA },
	{ "ps_gfx8.rom",   0x80000, 0x8f02f436, BRF_GRA },

  // z80 rom
	{ "ps_q.rom",      0x20000, 0x49ff4446, BRF_SND },			 // 11
  // samples
	{ "ps_q1.rom",     0x80000, 0x31fd8726, BRF_SND },
	{ "ps_q2.rom",     0x80000, 0x980a9eef, BRF_SND },
	{ "ps_q3.rom",     0x80000, 0x0dd44491, BRF_SND },
	{ "ps_q4.rom",     0x80000, 0xbed42f03, BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Punishrj) STD_ROM_FN(Punishrj)

struct BurnDriver BurnDrvCpsPunishrj = {
	"punishrj", "punisher", NULL, "1993",
	"The Punisher (930422 Japan)\0", NULL, "Capcom", "CPS1 / QSound",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS1_QSOUND,
	NULL,PunishrjRomInfo,PunishrjRomName,DrvInputInfo, punishDIPInfo,
	PunishrjInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
