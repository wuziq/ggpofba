/*
Part of FBAs Taito 68k hardware drivers
Credits: Mame team, Raine team
Driver by Treble Winner
*/

//#include "taito.h"
#include "burnint.h"
#include "taito_gfx.h"
#include "snd_tc0140.h"
#include "burn_ym2610.h"

static unsigned char *Mem = NULL, *MemEnd = NULL;
static unsigned char *RamStart =NULL, *RamEnd = NULL;
static unsigned char *Rom = NULL;
static unsigned char *Superman_ram = NULL, *Superman_src_pal = NULL;
static unsigned char SupermanReset = 0;
static unsigned char *z80_rom = NULL, *z80_ram = NULL;
static unsigned char *SupermanYM2610Rom = NULL;
static unsigned int *Superman_pal = NULL;

// Z80 ROM bank
static int Z80Bank = 0;
static int nCurrentBank = 0;

static int nCyclesTotal[2];
static int nCyclesDone[2];
static int nCycles68KSync;

static unsigned char SupermanInputPort0[8], SupermanInputPort1[8], SupermanInputPort2[8];
unsigned char SupermanInput[3] = {0, 0, 0};
static unsigned char SupermanDip[2] = {0, 0};

static struct BurnInputInfo SupermanInputList[] =
{
	{"P1 Coin"     , BIT_DIGITAL, SupermanInputPort2 + 0, "p1 coin"     },
	{"P1 Start"    , BIT_DIGITAL, SupermanInputPort0 + 7, "p1 start"    },
	{"P1 Up"       , BIT_DIGITAL, SupermanInputPort0 + 0, "p1 up"       },
	{"P1 Down"     , BIT_DIGITAL, SupermanInputPort0 + 1, "p1 down"     },
	{"P1 Left"     , BIT_DIGITAL, SupermanInputPort0 + 2, "p1 left"     },
	{"P1 Right"    , BIT_DIGITAL, SupermanInputPort0 + 3, "p1 right"    },
	{"P1 Button 1" , BIT_DIGITAL, SupermanInputPort0 + 4, "p1 fire 1"   },
	{"P1 Button 2" , BIT_DIGITAL, SupermanInputPort0 + 5, "p1 fire 2"   },

	{"P2 Coin"     , BIT_DIGITAL, SupermanInputPort2 + 1, "p2 coin"     },
	{"P2 Start"    , BIT_DIGITAL, SupermanInputPort1 + 7, "p2 start"    },
	{"P2 Up"       , BIT_DIGITAL, SupermanInputPort1 + 0, "p2 up"       },
	{"P2 Down"     , BIT_DIGITAL, SupermanInputPort1 + 1, "p2 down"     },
	{"P2 Left"     , BIT_DIGITAL, SupermanInputPort1 + 2, "p2 left"     },
	{"P2 Right"    , BIT_DIGITAL, SupermanInputPort1 + 3, "p2 right"    },
	{"P2 Button 1" , BIT_DIGITAL, SupermanInputPort1 + 4, "p2 fire 1"   },
	{"P2 Button 2" , BIT_DIGITAL, SupermanInputPort1 + 5, "p2 fire 2"   },

	{"Reset"       , BIT_DIGITAL, &SupermanReset        , "reset"       },
	{"Service"     , BIT_DIGITAL, SupermanInputPort2 + 2, "service"     },
	{"Tilt"        , BIT_DIGITAL, SupermanInputPort2 + 3, "tilt"        },
	{"Dip 1"       , BIT_DIPSWITCH, SupermanDip + 0     , "dip"         },
	{"Dip 2"       , BIT_DIPSWITCH, SupermanDip + 1     , "dip"         },
};

STDINPUTINFO(Superman);

static struct BurnDIPInfo SupermanCoinageDIPList[] =
{
	// Taito Coinage World
	{0   , 0xfe, 0   , 4   , "Coin A"                 },
	{0x13, 0x01, 0x30, 0x30, "4 Coins 1 Credit"       },
	{0x13, 0x01, 0x30, 0x20, "3 Coins 1 Credit"       },
	{0x13, 0x01, 0x30, 0x10, "2 Coins 1 Credit"       },
	{0x13, 0x01, 0x30, 0x00, "1 Coin 1 Credit"        },

	{0   , 0xfe, 0   , 4   , "Coin B"                 },
	{0x13, 0x01, 0xc0, 0xc0, "1 Coin 6 Credits"       },
	{0x13, 0x01, 0xc0, 0x80, "1 Coin 4 Credits"       },
	{0x13, 0x01, 0xc0, 0x40, "1 Coin 3 Credits"       },
	{0x13, 0x01, 0xc0, 0x00, "1 Coin 2 Credits"       },
};

static struct BurnDIPInfo SuprmanjCoinageDIPList[] =
{
	// Taito Coinage Japan
	{0   , 0xfe, 0   , 4   , "Coin A"                 },
	{0x13, 0x01, 0x30, 0x30, "2 Coins 3 Credits"      },
	{0x13, 0x01, 0x30, 0x20, "2 Coins 1 Credit"       },
	{0x13, 0x01, 0x30, 0x10, "1 Coin 2 Credits"       },
	{0x13, 0x01, 0x30, 0x00, "1 Coin 1 Credit"        },

	{0   , 0xfe, 0   , 4   , "Coin B"                 },
	{0x13, 0x01, 0xc0, 0xc0, "2 Coins 3 Credits"      },
	{0x13, 0x01, 0xc0, 0x80, "2 Coins 1 Credit"       },
	{0x13, 0x01, 0xc0, 0x40, "1 Coin 2 Credits"       },
	{0x13, 0x01, 0xc0, 0x00, "1 Coin 1 Credit"        },
};

static struct BurnDIPInfo SupermanDIPList[]=
{
	// Default Values
	{0x13, 0xff, 0xff, 0x00, NULL                     },
	{0x14, 0xff, 0xff, 0x00, NULL                     },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Flip Screen"            },
	{0x13, 0x01, 0x02, 0x00, "Off"                    },
	{0x13, 0x01, 0x02, 0x02, "On"                     },

	{0   , 0xfe, 0   , 2   , "Service Mode"           },
	{0x13, 0x01, 0x04, 0x00, "Off"                    },
	{0x13, 0x01, 0x04, 0x04, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Demo Sounds"            },	// No Effect?
//	{0x13, 0x01, 0x08, 0x00, "Off"                    },
//	{0x13, 0x01, 0x08, 0x08, "On"                     },

	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"             },
	{0x14, 0x01, 0x03, 0x01, "Easy"                   },
	{0x14, 0x01, 0x03, 0x00, "Normal"                 },
	{0x14, 0x01, 0x03, 0x02, "Hard"                   },
	{0x14, 0x01, 0x03, 0x03, "Hardest"                },

	{0   , 0xfe, 0   , 4   , "Lives"                  },
	{0x14, 0x01, 0x30, 0x10, "2"                      },
	{0x14, 0x01, 0x30, 0x00, "3"                      },
	{0x14, 0x01, 0x30, 0x20, "4"                      },
	{0x14, 0x01, 0x30, 0x30, "5"                      },
};

STDDIPINFOEXT(Superman, SupermanCoinage, Superman);
STDDIPINFOEXT(Suprmanj, SuprmanjCoinage, Superman);


void SupermanBankSwitch(unsigned int data)
{
	Z80Bank = (data - 1) & 0x03;
	unsigned char* nStartAddress = z80_rom + 0x4000 + (Z80Bank * 0x4000);
	nCurrentBank = Z80Bank;
	ZetMapArea(0x4000, 0x7fff, 0, nStartAddress);
	ZetMapArea(0x4000, 0x7fff, 2, nStartAddress);
}

int SupermanInpMake()
{
	SupermanInput[0] = SupermanInput[1] =  SupermanInput[2] = 0xff;

	for (int i = 0; i < 8; i++) {
		SupermanInput[0] -= (SupermanInputPort0[i] & 1) << i;
		SupermanInput[1] -= (SupermanInputPort1[i] & 1) << i;
		SupermanInput[2] -= (SupermanInputPort2[i] & 1) << i;

	}
	return 0;
}


// ----------------------------------------------------------------------------
// CPU synchronisation

static inline void SupermanSynchroniseZ80(int nExtraCycles)
{
	int nCycles = ((long long)SekTotalCycles() * nCyclesTotal[1] / nCyclesTotal[0]) + nExtraCycles;

	if (nCycles <= ZetTotalCycles()) {
		return;
	}

	nCycles68KSync = nCycles - nExtraCycles;

	BurnTimerUpdate(nCycles);
}

// Callbacks for the FM chip

static void SupermanFMIRQHandler(int, int nStatus)
{
	if (nStatus) {
		ZetSetIRQLine(0xFF, ZET_IRQSTATUS_ACK);
	} else {
		ZetSetIRQLine(0,    ZET_IRQSTATUS_NONE);
	}
}

static int SupermanSynchroniseStream(int nSoundRate)
{
	return (long long)ZetTotalCycles() * nSoundRate / 4000000;
}

static double SupermanGetTime()
{
	return (double)ZetTotalCycles() / 4000000.0;
}

// ----------------------------------------------------------------------------

inline static unsigned int CalcCol(unsigned short nColour)
{
	int r, g, b;

	r = (nColour & 0x001f) << 3;	// Red
	r |= r >> 5;
	g = (nColour & 0x03e0) >> 2;  	// Green
	g |= g >> 5;
	b = (nColour & 0x7c00) >> 7;	// Blue
	b |= b >> 5;

	return BurnHighCol(b, g, r, 0);
}

int SupermanPalUpdate()
{
	int i;
	unsigned short* ps;
	unsigned int* pd;

	for (i = 0, ps = (unsigned short*)Superman_src_pal, pd = Superman_pal; i < 0x400; i++, ps++, pd++) {
		*pd = CalcCol(*ps);
	}
	return 0;
}

// This routine is called first to determine how much memory is needed (MemEnd-(unsigned char *)0),
// and then to set up all the pointers

static int MemIndex()
{
	unsigned char *Next; Next=Mem;

	Rom              = Next; Next += 0x80000; // 68000 program
	z80_rom          = Next; Next += 0x1c000;
	SupermanYM2610Rom= Next; Next += 0x80000;

        RamStart         = Next;

	Superman_ram     = Next; Next += 0x4000;
	sysbvidattr      = Next; Next += 0x1000;
	sysbvidram       = Next; Next += 0x4000;
	Superman_src_pal = Next; Next += 0x1000;
	Superman_pal     = (unsigned int*)Next; Next += 0x800 * sizeof(unsigned int);
	z80_ram          = Next; Next += 0x2000;

	RamEnd           = Next;

	MemEnd           = Next;

	return 0;
}

static int LoadRoms()
{
	int nRet=0;
	// Load program roms and byteswap
	nRet = BurnLoadRom(Rom + 0x00001, 0, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Rom + 0x00000, 1, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Rom + 0x40001, 2, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(Rom + 0x40000, 3, 2); if (nRet != 0) return 1;

	nRet = BurnLoadRom(z80_rom, 4, 1); // load z80 code rom

	ttiles = (unsigned char *)malloc(0x400000);
	memset(ttiles, 0, 16384 * 256);

	SysxTempGfx = (unsigned char *)malloc(0x200000);

	nRet = BurnLoadRom(SysxTempGfx + 0x000000, 5, 1);
	nRet = BurnLoadRom(SysxTempGfx + 0x080000, 6, 1);
	nRet = BurnLoadRom(SysxTempGfx + 0x100000, 7, 1);
	nRet = BurnLoadRom(SysxTempGfx + 0x180000, 8, 1);

	nRet = BurnLoadRom(SupermanYM2610Rom, 9, 1);

	return nRet;
}

// C-Chip Stuff (Taken from MAME)

static int CChip_CurrentBank = 0;
static int CChip_Port = 0;
static int superman_code[40] =
{
	0x48, 0xe7, 0x80, 0x80,	            /* MOVEM.L  D0/A0,-(A7)   ( Preserve Regs ) */
	0x20, 0x6d, 0x1c, 0x40,             /* MOVEA.L  ($1C40,A5),A0 ( Load sound pointer in A0 ) */
	0x30, 0x2f, 0x00, 0x0c,             /* MOVE.W   ($0C,A7),D0   ( Fetch sound number ) */
	0x10, 0x80,                         /* MOVE.B   D0,(A0)       ( Store it on sound pointer ) */
	0x52, 0x88,                         /* ADDQ.W   #1,A0         ( Increment sound pointer ) */
	0x20, 0x3c, 0x00, 0xf0, 0x1c, 0x40, /* MOVE.L   #$F01C40,D0   ( Load top of buffer in D0 ) */
	0xb1, 0xc0,                         /* CMPA.L   D0,A0         ( Are we there yet? ) */
	0x66, 0x04,                         /* BNE.S    *+$6          ( No, we arent, skip next line ) */
	0x41, 0xed, 0x1c, 0x20,             /* LEA      ($1C20,A5),A0 ( Point to the start of the buffer ) */
	0x2b, 0x48, 0x1c, 0x40,	            /* MOVE.L   A0,($1C40,A5) ( Store new sound pointer ) */
	0x4c, 0xdf, 0x01, 0x01,	            /* MOVEM.L  (A7)+, D0/A0  ( Restore Regs ) */
	0x4e, 0x75                          /* RTS                    ( Return ) */
};

static unsigned char CChip_Read(int Offset)
{
	if (Offset == 0x401) {
		// C-Chip ID
		return 0x01;
	}

	if (CChip_CurrentBank == 0) {
		switch (Offset) {
			case 0x000: return SupermanInput[0];	// input port 1
			case 0x001: return SupermanInput[1];	// input port 2
			case 0x002: return SupermanInput[2];	// input port 3
			case 0x003: return CChip_Port;
		}
	}

	if (CChip_CurrentBank == 1 && Offset <= 0xff) {
//		bprintf(PRINT_NORMAL, "C-Chip: Attempt to read sound commands\n");
		if (Offset < 40) {
			return superman_code[Offset];
		} else {
			return 0x00;
		}
	}

	if (CChip_CurrentBank == 2) {
		switch (Offset) {
			case 0x000: return 0x47;
			case 0x001: return 0x57;
			case 0x002: return 0x4b;
		}
	}

	return 0;
}

static void CChip_Write(int Offset, unsigned short Data)
{
	if (Offset == 0x600) {
		CChip_CurrentBank = Data;
		return;
	}

	if (CChip_CurrentBank == 0 && Offset == 0x003) {
		CChip_Port = Data;
		return;
	}
}

unsigned char __fastcall SupermanZ80Read(unsigned short a)
{
	switch (a) {
		case (0xe000):
			return BurnYM2610Read(0);;
		case (0xe001):
			return BurnYM2610Read(1);
		case (0xe002):
			return BurnYM2610Read(2);
		case (0xe201):
			return tc0140_slave_comm_r();
	}

	return 0;
}

void __fastcall SupermanZ80Write(unsigned short a, unsigned char d)
{
	switch (a) {
		case 0xe000:
		case 0xe001:
		case 0xe002:
		case 0xe003:
			BurnYM2610Write(a & 3, d);
			return;
		case 0xe200:
			tc0140_slave_port_w(d);
			return;
		case 0xe201:
			tc0140_slave_comm_w(d);
			return;
		case 0xf200:
			SupermanBankSwitch(d);
			return;
	}
}

unsigned short __fastcall SupermanReadWord(unsigned int a)
{
	switch (a) {
		case 0x500000:
		case 0x500002:
		case 0x500004:
		case 0x500006:
		case 0x800002:
			SEK_DEF_READ_WORD(0, a);
	}

//	bprintf(PRINT_NORMAL, "68000: Read Word %06X\n",a);
	return 0;
}

unsigned char __fastcall SupermanReadByte(unsigned int a)
{
	if (a >= 0x900000 && a <= 0x900fff) {
		return CChip_Read((a - 0x900000) / 2);
	}

	switch (a) {
		case 0x500001: return (0xff - SupermanDip[0]) & 0x0f;
		case 0x500003: return ((0xff - SupermanDip[0]) & 0xf0) >> 4;
		case 0x500005: return (0xff - SupermanDip[1]) & 0x0f;
		case 0x500007: return ((0xff - SupermanDip[1]) & 0xf0) >> 4;
		case 0x800002: return 0xff;
		case 0x800003: return tc0140_comm_r();
	}

//	bprintf(PRINT_NORMAL, "68000: Read Byte %06X\n", a);
	return 0;
}

void __fastcall SupermanWriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0x300000:
		case 0x400000:
		case 0x600000:
		case 0x700000:
		case 0xc00000:
			return;

		case 0x800000:
		case 0x800002:
			SEK_DEF_WRITE_WORD(0, a, d);
			return;
	}

//	bprintf(PRINT_NORMAL, "68000: Write Word %06X %04X\n", a, d);
	return;
}

void __fastcall SupermanWriteByte(unsigned int a, unsigned char d)
{
	if (a >= 0x900000 && a <= 0x900fff) {
		CChip_Write((a - 0x900000) / 2, d);
		return;
	}

	switch (a) {
		case 0x800001:
			tc0140_port_w(d);
			return;
		case 0x800003:
			SupermanSynchroniseZ80(0);
			tc0140_comm_w(d);
			return;
	}

//	bprintf(PRINT_NORMAL, "68000: Write Byte %06X %02X\n", a, d);
	return;
}

static int SupermanDoReset()
{
	SekOpen(0);
	SekReset();
	SekClose();

	ZetOpen(0);
	ZetReset();
	Z80Bank = 0;
	nCurrentBank = 0;
	SupermanBankSwitch(0);
	ZetClose();

	BurnYM2610Reset();

	nCyclesDone[0] = nCyclesDone[1] = 0;

	return 0;
}

int SupermanInit()
{
	int nRet= 0; int nLen = 0;

	//--------------Allocate Memory-----------------
	Mem = NULL;
	MemIndex();
	nLen = MemEnd - (unsigned char *)0;
	Mem = (unsigned char *)malloc(nLen);
	if (Mem == NULL)
		return 1;
	memset(Mem, 0, nLen); // blank all memory
	MemIndex(); // Index the allocated memory

	//--------------- Load Roms -------------------
	nRet = LoadRoms();
	if (nRet != 0)
		return 1; // Load the roms into memory

	// Map in memory:
	// ----------------- Cpu 1 68k ------------------------
	SekInit(0, 0x68000); // Allocate 1 68000
	SekOpen(0);
	SekMapMemory(Rom             , 0x000000, 0x07ffff ,SM_ROM);
	SekMapMemory(Superman_src_pal, 0xb00000, 0xb00fff, SM_RAM);
	SekMapMemory(sysbvidattr     , 0xd00000, 0xd00fff, SM_RAM);
	SekMapMemory(sysbvidram      , 0xe00000, 0xe03fff, SM_RAM);
	SekMapMemory(Superman_ram    , 0xf00000, 0xf03fff ,SM_RAM);

	SekSetWriteWordHandler(0, SupermanWriteWord);
	SekSetReadWordHandler(0, SupermanReadWord);
	SekSetReadByteHandler(0, SupermanReadByte);
	SekSetWriteByteHandler(0, SupermanWriteByte);
	SekClose();

	// ----------------- Cpu 2 Z80 ------------------------
	ZetInit(1);
	ZetSetReadHandler(SupermanZ80Read);
	ZetSetWriteHandler(SupermanZ80Write);
	ZetMapArea(0x0000, 0x3fff, 0, z80_rom);
	ZetMapArea(0x0000, 0x3fff, 2, z80_rom);
	ZetMapArea(0xc000, 0xdfff, 0, z80_ram);
	ZetMapArea(0xc000, 0xdfff, 2, z80_ram);
	ZetMapArea(0xc000, 0xdfff, 1, z80_ram);
	ZetMemCallback(0xe000, 0xffff, 0);
	ZetMemCallback(0xe000, 0xffff, 1);
	ZetMemEnd();
	ZetClose();
	//-------------------------------------------------

	//-------- sound stuff ----------------------------
	nCurrentBank = -1;

	int SupermanYM2610RomSize = 0x80000;
	BurnYM2610Init(8000000, SupermanYM2610Rom, &SupermanYM2610RomSize, SupermanYM2610Rom, &SupermanYM2610RomSize, &SupermanFMIRQHandler, SupermanSynchroniseStream, SupermanGetTime);
	BurnTimerAttachZet(4000000);

	// ------- GFX Init -------------------
	taito_pal=Superman_pal;
	SysXInit(1);

	SupermanDoReset();
	return 0;
}

int SupermanExit()
{
	free(ttiles);
	SekExit();
	ZetExit();
	BurnYM2610Exit();
	if (Mem != NULL)
		free(Mem);
	Mem = NULL;
	return 0;
}

static int SupermanDraw()
{
	SupermanPalUpdate();
	SysXBG();
	SysXSprites();
	return 0;
}

int SupermanFrame()
{
	if (SupermanReset) {	// Reset machine
		SupermanDoReset();
	}

	SupermanInpMake();

	SekNewFrame();
	ZetNewFrame();

	SekOpen(0);
	ZetOpen(0);

	SekIdle(nCyclesDone[0]);
	ZetIdle(nCyclesDone[1]);

	nCyclesTotal[0] = 8000000 / 60;
	nCyclesTotal[1] = 4000000 / 60;

	SekRun(nCyclesTotal[0] - SekTotalCycles());

	SekSetIRQLine(6, SEK_IRQSTATUS_AUTO);

	nCycles68KSync = SekTotalCycles();
	BurnTimerEndFrame(nCyclesTotal[1]);
	BurnYM2610Update(nBurnSoundLen);

	nCyclesDone[0] = SekTotalCycles() - nCyclesTotal[0];
	nCyclesDone[1] = ZetTotalCycles() - nCyclesTotal[1];

	ZetClose();
	SekClose();

	if (pBurnDraw) {
		SupermanDraw();														// Draw screen if needed
	}

	return 0;
}

// Scan RAM
static int SupermanScan(int nAction,int *pnMin)
{
	struct BurnArea ba;

	if (pnMin) {						// Return minimum compatible version
		*pnMin = 0x029521;
	}

	if (nAction & ACB_VOLATILE) {		// Scan volatile ram

		memset(&ba, 0, sizeof(ba));
    ba.Data	  = RamStart;
		ba.nLen	  = RamEnd-RamStart;
		ba.szName = "All Ram";
		BurnAcb(&ba);
	}

	if (nAction & ACB_DRIVER_DATA) {
		SekScan(nAction);			// Scan 68000
		ZetScan(nAction);			// Scan Z80

		BurnYM2610Scan(nAction, pnMin);

		// Scan critical driver variables
		SCAN_VAR(SupermanInput);
		SCAN_VAR(SupermanDip);
		SCAN_VAR(Z80Bank);
		SCAN_VAR(nCurrentBank);
		SCAN_VAR(nCycles68KSync);
	}

	return 0;
}

/// Rom information
static struct BurnRomInfo SupermanRomDesc[] = {
	{ "a10_09.bin",    0x20000, 0x640f1d58, BRF_ESS | BRF_PRG }, //  0 68000 Code
	{ "a05_07.bin",    0x20000, 0xfddb9953, BRF_ESS | BRF_PRG }, //  1
	{ "a08_08.bin",    0x20000, 0x79fc028e, BRF_ESS | BRF_PRG }, //  2
	{ "a03_13.bin",    0x20000, 0x9f446a44, BRF_ESS | BRF_PRG }, //  3

	{ "d18_10.bin",    0x10000, 0x6efe79e8, BRF_ESS | BRF_PRG }, //  4 Z80 Code

	{ "f01_14.bin",    0x80000, 0x89368c3e, BRF_GRA },			 //  5 Tiles
	{ "j01_16.bin",    0x80000, 0x3622ed2f, BRF_GRA },			 //  7
	{ "h01_15.bin",    0x80000, 0x910cc4f9, BRF_GRA },			 //  6
	{ "k01_17.bin",    0x80000, 0xc34f27e0, BRF_GRA },			 //  8

	{ "e18_01.bin",    0x80000, 0x3cf99786, BRF_SND },			 //  9 ADPCM Samples
};


STD_ROM_PICK(Superman);
STD_ROM_FN(Superman);

static struct BurnRomInfo SuprmanjRomDesc[] = {
	{ "a10_09.bin",    0x20000, 0x640f1d58, BRF_ESS | BRF_PRG }, //  0 68000 Code
	{ "a05_07.bin",    0x20000, 0xfddb9953, BRF_ESS | BRF_PRG }, //  1
	{ "a08_08.bin",    0x20000, 0x79fc028e, BRF_ESS | BRF_PRG }, //  2
	{ "b61-06.a3",     0x20000, 0x714a0b68, BRF_ESS | BRF_PRG }, //  3

	{ "d18_10.bin",    0x10000, 0x6efe79e8, BRF_ESS | BRF_PRG }, //  4 Z80 Code

	{ "f01_14.bin",    0x80000, 0x89368c3e, BRF_GRA },			 //  5 Tiles
	{ "j01_16.bin",    0x80000, 0x3622ed2f, BRF_GRA },			 //  7
	{ "h01_15.bin",    0x80000, 0x910cc4f9, BRF_GRA },			 //  6
	{ "k01_17.bin",    0x80000, 0xc34f27e0, BRF_GRA },			 //  8

	{ "e18_01.bin",    0x80000, 0x3cf99786, BRF_SND },			 //  9 ADPCM Samples
};


STD_ROM_PICK(Suprmanj);
STD_ROM_FN(Suprmanj);

struct BurnDriver BurnDrvSuperman = {
	"superman", NULL, NULL, "1988",
	"Superman\0", NULL, "Taito", "Taito X System",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_MISC_MISC,
	NULL, SupermanRomInfo, SupermanRomName, SupermanInputInfo, SupermanDIPInfo,
	SupermanInit, SupermanExit, SupermanFrame, NULL, SupermanScan,
	&taitoRecalcPal, 384, 240, 4, 3
};

struct BurnDriver BurnDrvSuprmanj = {
	"suprmanj", "superman", NULL, "1988",
	"Superman (Japan)\0", NULL, "Taito", "Taito X System",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_MISC_MISC,
	NULL, SuprmanjRomInfo, SuprmanjRomName, SupermanInputInfo, SuprmanjDIPInfo,
	SupermanInit, SupermanExit, SupermanFrame, NULL, SupermanScan,
	&taitoRecalcPal, 384, 240, 4, 3
};
