#include "sys16.h"

unsigned char  System16InputPort0[8]  = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char  System16InputPort1[8]  = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char  System16InputPort2[8]  = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char  System16InputPort3[8]  = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char  System16InputPort4[8]  = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char  System16InputPort5[8]  = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char  System16InputPort6[8]  = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char  System16Gear           = 0;
int            System16AnalogPort0    = 0;
int            System16AnalogPort1    = 0;
int            System16AnalogPort2    = 0;
int            System16AnalogPort3    = 0;
int            System16AnalogSelect   = 0;
unsigned char  System16Dip[3]         = {0, 0, 0};
unsigned char  System16Input[7]       = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char  System16Reset          = 0;

unsigned char  *Mem                   = NULL;
unsigned char  *MemEnd                = NULL;
unsigned char  *RamStart              = NULL;
unsigned char  *RamEnd                = NULL;
unsigned char  *System16Rom           = NULL;
unsigned char  *System16Code          = NULL;
unsigned char  *System16Rom2          = NULL;
unsigned char  *System16Rom3          = NULL;
unsigned char  *System16Z80Rom        = NULL;
unsigned char  *System16Z80Rom2       = NULL;
unsigned char  *System16Z80Rom3       = NULL;
unsigned char  *System16Z80Rom4       = NULL;
unsigned char  *System167751Prog      = NULL;
unsigned char  *System167751Data      = NULL;
unsigned char  *System16UPD7759Data   = NULL;
unsigned char  *System16PCMData       = NULL;
unsigned char  *System16PCM2Data      = NULL;
unsigned char  *System16Prom          = NULL;
unsigned char  *System16Key           = NULL;
unsigned char  *System16Ram           = NULL;
unsigned char  *System16ExtraRam      = NULL;
unsigned char  *System16ExtraRam2     = NULL;
unsigned char  *System16ExtraRam3     = NULL;
unsigned char  *System16BackupRam     = NULL;
unsigned char  *System16BackupRam2    = NULL;
unsigned char  *System16Z80Ram        = NULL;
unsigned char  *System16TileRam       = NULL;
unsigned char  *System16TextRam       = NULL;
unsigned char  *System16SpriteRam     = NULL;
unsigned char  *System16SpriteRamBuff = NULL;
unsigned char  *System16SpriteRam2    = NULL;
unsigned char  *System16RotateRam     = NULL;
unsigned char  *System16RotateRamBuff = NULL;
unsigned char  *System16PaletteRam    = NULL;
unsigned char  *System16RoadRam       = NULL;
unsigned char  *System16RoadRamBuff   = NULL;
unsigned char  *System16Tiles         = NULL;
unsigned char  *System16Sprites       = NULL;
unsigned char  *System16Sprites2      = NULL;
unsigned char  *System16Roads         = NULL;
unsigned int   *System16Palette       = NULL;
unsigned char  *System16TempGfx       = NULL;

unsigned int System16RomSize = 0;
unsigned int System16RomNum = 0;
unsigned int System16Rom2Size = 0;
unsigned int System16Rom2Num = 0;
unsigned int System16Rom3Size = 0;
unsigned int System16Rom3Num = 0;
unsigned int System16TileRomSize = 0;
unsigned int System16TileRomNum = 0;
unsigned int System16NumTiles = 0;
unsigned int System16SpriteRomSize = 0;
unsigned int System16SpriteRomNum = 0;
unsigned int System16Sprite2RomSize = 0;
unsigned int System16Sprite2RomNum = 0;
unsigned int System16RoadRomSize = 0;
unsigned int System16RoadRomNum = 0;
unsigned int System16Z80RomSize = 0;
unsigned int System16Z80RomNum = 0;
unsigned int System16Z80Rom2Size = 0;
unsigned int System16Z80Rom2Num = 0;
unsigned int System16Z80Rom3Size = 0;
unsigned int System16Z80Rom3Num = 0;
unsigned int System16Z80Rom4Size = 0;
unsigned int System16Z80Rom4Num = 0;
unsigned int System167751ProgSize = 0;
unsigned int System167751ProgNum = 0;
unsigned int System167751DataSize = 0;
unsigned int System167751DataNum = 0;
unsigned int System16UPD7759DataSize = 0;
unsigned int System16UPD7759DataNum = 0;
unsigned int System16PCMDataSize = 0;
unsigned int System16PCMDataNum = 0;
unsigned int System16PCM2DataSize = 0;
unsigned int System16PCM2DataNum = 0;
unsigned int System16PromSize = 0;
unsigned int System16PromNum = 0;
unsigned int System16KeySize = 0;
unsigned int System16RamSize = 0;
unsigned int System16ExtraRamSize = 0;
unsigned int System16ExtraRam2Size = 0;
unsigned int System16ExtraRam3Size = 0;
unsigned int System16SpriteRamSize = 0;
unsigned int System16SpriteRam2Size = 0;
unsigned int System16RotateRamSize = 0;
unsigned int System16BackupRamSize = 0;
unsigned int System16BackupRam2Size = 0;

static int System16LastGear;
bool System16HasGears = false;

unsigned char System16VideoControl;
int System16SoundLatch;
bool System16BTileAlt = false;
bool Shangon = false;
bool Hangon = false;

bool System16Gun = false;
int System16Gun1X = 160 << 8, System16Gun1Y = 112 << 8;
int System16Gun2X = 160 << 8, System16Gun2Y = 112 << 8;

int nSystem16CyclesDone[4];
static int nCyclesTotal[4];
static int nCyclesSegment;
unsigned int System16ClockSpeed = 0;

int YBoardIrq2Scanline = 0;

static bool bUseAsm68KCoreOldValue = false;

Sim8751 Simulate8751;
System16Map68K System16Map68KDo;
System16CustomLoadRom System16CustomLoadRomDo;
System16CustomDecryptOpCode System16CustomDecryptOpCodeDo;
System16ProcessAnalogControls System16ProcessAnalogControlsDo;
System16MakeAnalogInputs System16MakeAnalogInputsDo;

/*====================================================
Inputs
====================================================*/

inline static void System16ClearOpposites(unsigned char* nJoystickInputs)
{
	if ((*nJoystickInputs & 0x30) == 0x30) {
		*nJoystickInputs &= ~0x30;
	}
	if ((*nJoystickInputs & 0xc0) == 0xc0) {
		*nJoystickInputs &= ~0xc0;
	}
}

inline static void System16MakeInputs()
{
	// Reset Inputs
	System16Input[0] = System16Input[1] = System16Input[2] = System16Input[3] = System16Input[4] = System16Input[5] = System16Input[6] = 0;

	// Compile Digital Inputs
	for (int i = 0; i < 8; i++) {
		System16Input[0] |= (System16InputPort0[i] & 1) << i;
		System16Input[1] |= (System16InputPort1[i] & 1) << i;
		System16Input[2] |= (System16InputPort2[i] & 1) << i;
		System16Input[3] |= (System16InputPort3[i] & 1) << i;
		System16Input[4] |= (System16InputPort4[i] & 1) << i;
		System16Input[5] |= (System16InputPort5[i] & 1) << i;
		System16Input[6] |= (System16InputPort6[i] & 1) << i;
	}
	
	if (System16MakeAnalogInputsDo) System16MakeAnalogInputsDo();
}

inline static void OutrunMakeInputs()
{
	// Reset Inputs
	System16Input[0] = 0;
	
	if (System16Gear && System16LastGear == 0) System16InputPort0[4] ^= 1;

	// Compile Digital Inputs
	for (int i = 0; i < 8; i++) {
		System16Input[0] |= (System16InputPort0[i] & 1) << i;
	}
	
	System16LastGear = System16Gear;
}

inline static void PdriftMakeInputs()
{
	// Reset Inputs
	System16Input[0] = 0;
	
	if (System16Gear && System16LastGear == 0) System16InputPort0[5] ^= 1;

	// Compile Digital Inputs
	for (int i = 0; i < 8; i++) {
		System16Input[0] |= (System16InputPort0[i] & 1) << i;
	}
	
	System16LastGear = System16Gear;
}

static void System16GunMakeInputs()
{
	// Reset Inputs
	System16Input[0] = System16Input[1] = 0;
	
	// Compile Digital Inputs
	for (int i = 0; i < 8; i++) {
		System16Input[0] |= (System16InputPort0[i] & 1) << i;
		System16Input[1] |= (System16InputPort1[i] & 1) << i;
	}
	
	// Gun
	const int GunMinX = -8 * 0x100;
	const int GunMinY = -8 * 0x100;
	System16Gun1X += (short)System16AnalogPort0;
	System16Gun1Y += (short)System16AnalogPort1;
	System16Gun2X += (short)System16AnalogPort2;
	System16Gun2Y += (short)System16AnalogPort3;
	
	if (System16Gun1X < GunMinX)
		System16Gun1X = GunMinX;
	if (System16Gun1X > GunMinX + 320 * 0x100)
		System16Gun1X = GunMinX + 320 * 0x100;
	if (System16Gun1Y < GunMinY)
		System16Gun1Y = GunMinY;
	if (System16Gun1Y > GunMinY + 224 * 0x100)
		System16Gun1Y = GunMinY + 224 * 0x100;
		
	if (System16Gun2X < GunMinX)
		System16Gun2X = GunMinX;
	if (System16Gun2X > GunMinX + 320 * 0x100)
		System16Gun2X = GunMinX + 320 * 0x100;
	if (System16Gun2Y < GunMinY)
		System16Gun2Y = GunMinY;
	if (System16Gun2Y > GunMinY + 224 * 0x100)
		System16Gun2Y = GunMinY + 224 * 0x100;
}

/*====================================================
Reset Driver
====================================================*/

static int System16DoReset()
{
	int i;
	
	if (BurnDrvGetHardwareCode() & HARDWARE_SEGA_FD1094_ENC) {
		fd1094_machine_init();
	}
	
	SekOpen(0);
	SekReset();
	SekClose();
	
	if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_OUTRUN || (BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEMX || (BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_HANGON || (BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEMY) {
		SekOpen(1);
		SekReset();
		SekClose();
		
		System16LastGear = 0;
		System16RoadControl = 0;
		System16AnalogSelect = 0;
		
		if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_OUTRUN) {
			// Start in low gear
			if (System16HasGears) System16InputPort0[4] = 1;
		}
	}
	
	if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEMY) {
		SekOpen(2);
		SekReset();
		SekClose();
		
		// Start in low gear
		if (System16HasGears) System16InputPort0[5] = 1;
	}
	
	ZetReset();
	
	if (BurnDrvGetHardwareCode() & HARDWARE_SEGA_YM2203) {
		BurnYM2203Reset();
	} else {
		BurnYM2151Reset();
	}
	
	// Reset Variables
	for (i = 0; i < 4; i++) {
		System16Page[i] = 0;
		System16ScrollX[i] = 0;
		System16ScrollY[i] = 0;
	}
	
	if (BurnDrvGetHardwareCode() & HARDWARE_SEGA_5358) {
		System16SpriteBanks[ 0] = 0;
		System16SpriteBanks[ 1] = 255;
		System16SpriteBanks[ 2] = 255;
		System16SpriteBanks[ 3] = 255;
		System16SpriteBanks[ 4] = 255;
		System16SpriteBanks[ 5] = 255;
		System16SpriteBanks[ 6] = 255;
		System16SpriteBanks[ 7] = 3;
		System16SpriteBanks[ 8] = 255;
		System16SpriteBanks[ 9] = 255;
		System16SpriteBanks[10] = 255;
		System16SpriteBanks[11] = 2;
		System16SpriteBanks[12] = 255;
		System16SpriteBanks[13] = 1;
		System16SpriteBanks[14] = 0;
		System16SpriteBanks[15] = 255;
	} else {
		for (i = 0; i < 16; i++) {
			System16SpriteBanks[i] = i;
		}
	}
	
	if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEM16B || (BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_OUTRUN || (BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEMX) {
		for (i = 0; i < 2; i++) {
			System16TileBanks[i] = i;
		}
	}
	
	System16VideoEnable = 0;
	System16VideoControl = 0;
	System16ScreenFlip = 0;
	System16SoundLatch = 0;
	System16ColScroll = 0;
	System16RowScroll = 0;
	
	return 0;
}

int __fastcall OutrunResetCallback()
{
	int nLastCPU = nSekActive;
	SekClose();
	
	SekOpen(1);
	SekReset();
	SekClose();
	
	SekOpen(nLastCPU);

	return 0;
}

/*====================================================
Z80 Memory Handlers
====================================================*/

unsigned char __fastcall System16Z80PortRead(unsigned short a)
{
	a &= 0xff;
	
	switch (a) {
		case 0x01: {
			return BurnYM2151ReadStatus();
		}
		
		case 0x40:
		case 0xc0: {
			return System16SoundLatch;
		}
	}

#if 1 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("Z80 Read Port -> %02X\n"), a);
#endif

	return 0;
}

unsigned char __fastcall System16PPIZ80PortRead(unsigned short a)
{
	a &= 0xff;
	
	switch (a) {
		case 0x01: {
			return BurnYM2151ReadStatus();
		}
		
		case 0x40:
		case 0xc0: {
			ppi8255_set_portC(0, 0x00);
			return System16SoundLatch;
		}
	}

#if 0 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("Z80 Read Port -> %02X\n"), a);
#endif

	return 0;
}

void __fastcall System16Z80PortWrite(unsigned short a, unsigned char d)
{
	a &= 0xff;
	d &= 0xff;
	
	switch (a) {
		case 0x00: {
			BurnYM2151SelectRegister(d);
			return;
		}
		
		case 0x01: {
			BurnYM2151WriteRegister(d);
			return;
		}
	}

#if 1 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("Z80 Write Port -> %02X, %02X\n"), a, d);
#endif
}

unsigned char __fastcall System16Z80Read(unsigned short a)
{
#if 1 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("Z80 Read -> %04X\n"), a);
#endif

	return 0;
}

void __fastcall System16Z80Write(unsigned short a, unsigned char d)
{
#if 1 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("Z80 Write -> %04X, %02X\n"), a, d);
#endif
}

unsigned char __fastcall System16Z80PCMRead(unsigned short a)
{
	if (a >= 0xf000 && a <= 0xf0ff) {
		return PcmRead(a - 0xf000);
	}

#if 0 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("Z80 Read -> %04X\n"), a);
#endif

	return 0;
}

void __fastcall System16Z80PCMWrite(unsigned short a, unsigned char d)
{
	if (a >= 0xf000 && a <= 0xf0ff) {
		PcmWrite(a - 0xf000, d);
		return;
	}
	
#if 0 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("Z80 Write -> %04X, %02X\n"), a, d);
#endif
}

unsigned char __fastcall System16Z802203PortRead(unsigned short a)
{
	a &= 0xff;
	
	switch (a) {
		case 0x40: {
			ppi8255_set_portC(0, 0x00);
			return System16SoundLatch;
		}
	}

#if 0 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("Z80 Read Port -> %02X\n"), a);
#endif

	return 0;
}

unsigned char __fastcall System16Z802203Read(unsigned short a)
{
	if (a >= 0xe000 && a <= 0xe0ff) {
		return PcmRead(a - 0xe000);
	}
	
	switch (a) {
		case 0xd000: {
			return BurnYM2203Read(0);
		}
	}

#if 0 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("Z80 Read -> %04X\n"), a);
#endif

	return 0;
}

void __fastcall System16Z802203Write(unsigned short a, unsigned char d)
{
	if (a >= 0xe000 && a <= 0xe0ff) {
		PcmWrite(a - 0xe000, d);
		return;
	}
	
	switch (a) {
		case 0xd000: {
			BurnYM2203Write(0, d);
			return;
		}
		
		case 0xd001: {
			BurnYM2203Write(1, d);
			return;
		}
	}

#if 0 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("Z80 Write -> %04X, %02X\n"), a, d);
#endif
}

/*====================================================
Allocate Memory
====================================================*/

static int System16MemIndex()
{
	unsigned char *Next; Next = Mem;
	
	System16PaletteEntries = 0x800;
	System16RamSize = 0x4000;
	System16ExtraRamSize = 0;
	System16ExtraRam2Size = 0;
	System16ExtraRam3Size = 0;
	System16SpriteRamSize = 0x800;
	System16SpriteRam2Size = 0;
	System16RotateRamSize = 0;
	System16BackupRamSize = 0;
	System16BackupRam2Size = 0;
	bool SpriteBuffer = false;
	bool HasRoad = false;
	bool UseTempDraw = false;
	
	if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_HANGON) {
		System16ExtraRamSize = 0x4000;
		if (!strcmp(BurnDrvGetTextA(DRV_NAME), "hangon") || !strcmp(BurnDrvGetTextA(DRV_NAME), "shangupb")) {
			System16RamSize = 0x10000;
		} else {
			System16SpriteRamSize = 0x1000;
		}
		HasRoad = true;
	}
	
	if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_OUTRUN) {
		System16PaletteEntries = 0x1000;
		System16RamSize = 0x8000;
		System16ExtraRamSize = 0x8000;
		System16SpriteRamSize = 0x1000;
		SpriteBuffer = true;
		HasRoad = true;
	}
	
	if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEMX) {
		System16PaletteEntries = 0x2000;
		System16RamSize = 0x8000;
		System16SpriteRamSize = 0x1000;
		System16BackupRamSize = 0x4000;
		System16BackupRam2Size = 0x4000;
		SpriteBuffer = true;
		HasRoad = true;
	}
	
	if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEMY) {
		System16PaletteEntries = 0x2000;
		System16RamSize = 0x10000;
		System16ExtraRamSize = 0x10000;
		System16ExtraRam2Size = 0x10000;
		System16ExtraRam3Size = 0x10000;
		System16SpriteRamSize = 0x1000;
		System16BackupRamSize = 0x4000;
		System16SpriteRam2Size = 0x10000;
		System16RotateRamSize = 0x800;
		UseTempDraw = true;
	}
	
	System16Rom          = Next; Next += 0x100000;
	System16Code         = Next; Next += 0x100000;
	System16Rom2         = Next; (System16Rom2Size) ? Next += 0x080000 : Next += 0;
	System16Rom3         = Next; (System16Rom3Size) ? Next += 0x080000 : Next += 0;
	System16Z80Rom       = Next; Next += 0x010000;
	System16Z80Rom2      = Next; Next += System16Z80Rom2Size;
	System16Z80Rom3      = Next; Next += System16Z80Rom3Size;
	System16Z80Rom4      = Next; Next += System16Z80Rom4Size;
	System167751Prog     = Next; Next += System167751ProgSize;
	System167751Data     = Next; Next += System167751DataSize;
	System16UPD7759Data  = Next; Next += System16UPD7759DataSize;
	System16PCMData      = Next; Next += System16PCMDataSize;
	System16PCM2Data     = Next; Next += System16PCM2DataSize;
	System16Key          = Next; Next += System16KeySize;
	System16Prom         = Next; Next += System16PromSize;
	
	RamStart = Next;

	System16Ram          = Next; Next += System16RamSize;
	System16ExtraRam     = Next; Next += System16ExtraRamSize;
	System16ExtraRam2    = Next; Next += System16ExtraRam2Size;
	System16ExtraRam3    = Next; Next += System16ExtraRam3Size;
	System16TileRam      = Next; (System16TileRomSize) ? Next += 0x10000 : Next += 0;
	System16TextRam      = Next; (System16TileRomSize) ? Next += 0x01000 : Next += 0;
	System16SpriteRam    = Next; Next += System16SpriteRamSize;
	System16SpriteRam2   = Next; Next += System16SpriteRam2Size;
	System16RotateRam    = Next; Next += System16RotateRamSize;
	System16RotateRamBuff= Next; Next += System16RotateRamSize;
	if (SpriteBuffer) System16SpriteRamBuff = Next; Next += System16SpriteRamSize;
	System16PaletteRam   = Next; Next += System16PaletteEntries * 2;

	if (HasRoad) {
		System16RoadRam       = Next; Next += 0x01000;
		System16RoadRamBuff   = Next; Next += 0x01000;
	}
	
	System16BackupRam    = Next; Next += System16BackupRamSize;
	System16BackupRam2   = Next; Next += System16BackupRam2Size;
	
	System16Z80Ram       = Next; Next += 0x00800;

	RamEnd = Next;

	System16Tiles        = Next; Next += (System16NumTiles * 8 * 8);
	System16Sprites      = Next; Next += System16SpriteRomSize;
	System16Sprites2     = Next; Next += System16Sprite2RomSize;
	
	if (HasRoad) {
		System16Roads        = Next; Next += 0x40000;
	}
	
	System16Palette      = (unsigned int*)Next; Next += System16PaletteEntries * 3 * sizeof(unsigned int);
	
	if (UseTempDraw) pTempDraw = (unsigned short*)Next; Next += (512 * 512 * sizeof(unsigned short));
	
	MemEnd = Next;

	return 0;
}

/*====================================================
Rom Loading
====================================================*/

static int System16LoadRoms(bool bLoad)
{
	struct BurnRomInfo ri;
	ri.nType = 0;
	ri.nLen = 0;
	int nOffset = -1;
	unsigned int i;
	int nRet = 0;
	
	if (!bLoad) {
		do {
			ri.nLen = 0;
			ri.nType = 0;
			BurnDrvGetRomInfo(&ri, ++nOffset);
			if (ri.nType & SYS16_ROM_PROG) {
				System16RomSize += ri.nLen;
				System16RomNum++;
			}
			if (ri.nType & SYS16_ROM_PROG2) {
				System16Rom2Size += ri.nLen;
				System16Rom2Num++;
			}
			if (ri.nType & SYS16_ROM_PROG3) {
				System16Rom3Size += ri.nLen;
				System16Rom3Num++;
			}
			if (ri.nType & SYS16_ROM_TILES) {
				System16TileRomSize += ri.nLen;
				System16TileRomNum++;
			}
			if (ri.nType & SYS16_ROM_SPRITES) {
				System16SpriteRomSize += ri.nLen;
				System16SpriteRomNum++;
			}
			if (ri.nType & SYS16_ROM_SPRITES2) {
				System16Sprite2RomSize += ri.nLen;
				System16Sprite2RomNum++;
			}
			if (ri.nType & SYS16_ROM_ROAD) {
				System16RoadRomSize += ri.nLen;
				System16RoadRomNum++;
			}
			if (ri.nType & SYS16_ROM_Z80PROG) {
				System16Z80RomSize += ri.nLen;
				System16Z80RomNum++;
			}
			if (ri.nType & SYS16_ROM_Z80PROG2) {
				System16Z80Rom2Size += ri.nLen;
				System16Z80Rom2Num++;
			}
			if (ri.nType & SYS16_ROM_Z80PROG3) {
				System16Z80Rom3Size += ri.nLen;
				System16Z80Rom3Num++;
			}
			if (ri.nType & SYS16_ROM_Z80PROG4) {
				System16Z80Rom4Size += ri.nLen;
				System16Z80Rom4Num++;
			}
			if (ri.nType & SYS16_ROM_7751PROG) {
				System167751ProgSize += ri.nLen;
				System167751ProgNum++;
			}
			if (ri.nType & SYS16_ROM_7751DATA) {
				System167751DataSize += ri.nLen;
				System167751DataNum++;
			}
			if (ri.nType & SYS16_ROM_UPD7759DATA) {
				System16UPD7759DataSize += ri.nLen;
				System16UPD7759DataNum++;
			}
			if (ri.nType & SYS16_ROM_PCMDATA) {
				System16PCMDataSize += ri.nLen;
				System16PCMDataNum++;
			}
			if (ri.nType & SYS16_ROM_PCM2DATA) {
				System16PCM2DataSize += ri.nLen;
				System16PCM2DataNum++;
			}
			if (ri.nType & SYS16_ROM_PROM) {
				System16PromSize += ri.nLen;
				System16PromNum++;
			}
			if (ri.nType & SYS16_ROM_KEY) {
				System16KeySize += ri.nLen;
			}
		} while (ri.nLen);
		
		System16NumTiles = System16TileRomSize / 24;
		
#if 1 && defined FBA_DEBUG	
		bprintf(PRINT_NORMAL, _T("68K Rom Size: 0x%X (%i roms)\n"), System16RomSize, System16RomNum);
		if (System16Rom2Size) bprintf(PRINT_NORMAL, _T("68K #2 Rom Size: 0x%X (%i roms)\n"), System16Rom2Size, System16Rom2Num);
		if (System16Rom3Size) bprintf(PRINT_NORMAL, _T("68K #3 Rom Size: 0x%X (%i roms)\n"), System16Rom3Size, System16Rom3Num);
		bprintf(PRINT_NORMAL, _T("Tile Rom Size: 0x%X (%i roms, 0x%X Tiles)\n"), System16TileRomSize, System16TileRomNum, System16NumTiles);
		bprintf(PRINT_NORMAL, _T("Sprite Rom Size: 0x%X (%i roms)\n"), System16SpriteRomSize, System16SpriteRomNum);
		if (System16Sprite2RomSize) bprintf(PRINT_NORMAL, _T("Sprite Rom 2 Size: 0x%X (%i roms)\n"), System16Sprite2RomSize, System16Sprite2RomNum);
		bprintf(PRINT_NORMAL, _T("Z80 Rom Size: 0x%X (%i roms)\n"), System16Z80RomSize, System16Z80RomNum);
		if (System16Z80Rom2Size) bprintf(PRINT_NORMAL, _T("Z80 #2 Rom Size: 0x%X (%i roms)\n"), System16Z80Rom2Size, System16Z80Rom2Num);
		if (System16Z80Rom3Size) bprintf(PRINT_NORMAL, _T("Z80 #3 Rom Size: 0x%X (%i roms)\n"), System16Z80Rom3Size, System16Z80Rom3Num);
		if (System16Z80Rom4Size) bprintf(PRINT_NORMAL, _T("Z80 #4 Rom Size: 0x%X (%i roms)\n"), System16Z80Rom4Size, System16Z80Rom4Num);
		if (System16RoadRomSize) bprintf(PRINT_NORMAL, _T("Road Rom Size: 0x%X (%i roms)\n"), System16RoadRomSize, System16RoadRomNum);
		if (System167751ProgSize) bprintf(PRINT_NORMAL, _T("7751 Prog Size: 0x%X (%i roms)\n"), System167751ProgSize, System167751ProgNum);
		if (System167751DataSize) bprintf(PRINT_NORMAL, _T("7751 Data Size: 0x%X (%i roms)\n"), System167751DataSize, System167751DataNum);
		if (System16UPD7759DataSize) bprintf(PRINT_NORMAL, _T("UPD7759 Data Size: 0x%X (%i roms)\n"), System16UPD7759DataSize, System16UPD7759DataNum);
		if (System16PCMDataSize) bprintf(PRINT_NORMAL, _T("PCM Data Size: 0x%X (%i roms)\n"), System16PCMDataSize, System16PCMDataNum);
		if (System16PCM2DataSize) bprintf(PRINT_NORMAL, _T("PCM Data #2 Size: 0x%X (%i roms)\n"), System16PCM2DataSize, System16PCM2DataNum);
		if (System16PromSize) bprintf(PRINT_NORMAL, _T("PROM Rom Size: 0x%X (%i roms)\n"), System16PromSize, System16PromNum);
		if (System16KeySize) bprintf(PRINT_NORMAL, _T("Encryption Key Size: 0x%X\n"), System16KeySize);
#endif
	}
	
	if (bLoad) {
		int Offset;
		
		// 68000 Program Roms
		Offset = 0;
		for (i = 0; i < System16RomNum; i += 2) {
			nRet = BurnLoadRom(System16Rom + Offset + 1, i + 0, 2); if (nRet) return 1;
			nRet = BurnLoadRom(System16Rom + Offset + 0, i + 1, 2); if (nRet) return 1;
			
			BurnDrvGetRomInfo(&ri, i + 0);
			Offset += ri.nLen;
			BurnDrvGetRomInfo(&ri, i + 1);
			Offset += ri.nLen;
		}
		
		// 68000 #2 Program Roms
		if (System16Rom2Size) {
			Offset = 0;
			for (i = System16RomNum; i < System16RomNum + System16Rom2Num; i += 2) {
				nRet = BurnLoadRom(System16Rom2 + Offset + 1, i + 0, 2); if (nRet) return 1;
				nRet = BurnLoadRom(System16Rom2 + Offset + 0, i + 1, 2); if (nRet) return 1;
			
				BurnDrvGetRomInfo(&ri, i + 0);
				Offset += ri.nLen;
				BurnDrvGetRomInfo(&ri, i + 1);
				Offset += ri.nLen;
			}
		}
		
		// 68000 #3 Program Roms
		if (System16Rom3Size) {
			Offset = 0;
			for (i = System16RomNum + System16Rom2Num; i < System16RomNum + System16Rom2Num + System16Rom3Num; i += 2) {
				nRet = BurnLoadRom(System16Rom3 + Offset + 1, i + 0, 2); if (nRet) return 1;
				nRet = BurnLoadRom(System16Rom3 + Offset + 0, i + 1, 2); if (nRet) return 1;
			
				BurnDrvGetRomInfo(&ri, i + 0);
				Offset += ri.nLen;
				BurnDrvGetRomInfo(&ri, i + 1);
				Offset += ri.nLen;
			}
		}

		// Tile Roms
		Offset = 0;
		System16TempGfx = (unsigned char*)malloc(System16TileRomSize);
		for (i = System16RomNum + System16Rom2Num + System16Rom3Num; i < System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum; i++) {
			nRet = BurnLoadRom(System16TempGfx + Offset, i, 1); if (nRet) return 1;
			
			BurnDrvGetRomInfo(&ri, i + 0);
			Offset += ri.nLen;
		}
		System16Decode8x8Tiles(System16Tiles, System16NumTiles, System16TileRomSize * 2 / 3, System16TileRomSize * 1 / 3, 0);
		free(System16TempGfx);
		
		// Sprite Roms
		Offset = 0;
		
		if (BurnDrvGetHardwareCode() & HARDWARE_SEGA_SPRITE_LOAD32) {
			for (i = System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum; i < System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum; i += 4) {
				nRet = BurnLoadRom(System16Sprites + Offset + 0, i + 0, 4); if (nRet) return 1;
				nRet = BurnLoadRom(System16Sprites + Offset + 1, i + 1, 4); if (nRet) return 1;
				nRet = BurnLoadRom(System16Sprites + Offset + 2, i + 2, 4); if (nRet) return 1;
				nRet = BurnLoadRom(System16Sprites + Offset + 3, i + 3, 4); if (nRet) return 1;
				
				BurnDrvGetRomInfo(&ri, i + 0);
				Offset += ri.nLen;
				BurnDrvGetRomInfo(&ri, i + 1);
				Offset += ri.nLen;
				BurnDrvGetRomInfo(&ri, i + 2);
				Offset += ri.nLen;
				BurnDrvGetRomInfo(&ri, i + 3);
				Offset += ri.nLen;
			}
		} else {
			for (i = System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum; i < System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum; i += 2) {
				nRet = BurnLoadRom(System16Sprites + Offset + 0, i + 0, 2); if (nRet) return 1;
				nRet = BurnLoadRom(System16Sprites + Offset + 1, i + 1, 2); if (nRet) return 1;
				
				BurnDrvGetRomInfo(&ri, i + 0);
				Offset += ri.nLen;
				BurnDrvGetRomInfo(&ri, i + 1);
				Offset += ri.nLen;
			}
		}
		
		// Sprite 2 Roms
		if (System16Sprite2RomSize) {
			Offset = 0;
			for (i = System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum; i < System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum; i += 8) {
				nRet = BurnLoadRom(System16Sprites2 + Offset + 7, i + 0, 8); if (nRet) return 1;
				nRet = BurnLoadRom(System16Sprites2 + Offset + 6, i + 1, 8); if (nRet) return 1;
				nRet = BurnLoadRom(System16Sprites2 + Offset + 5, i + 2, 8); if (nRet) return 1;
				nRet = BurnLoadRom(System16Sprites2 + Offset + 4, i + 3, 8); if (nRet) return 1;
				nRet = BurnLoadRom(System16Sprites2 + Offset + 3, i + 4, 8); if (nRet) return 1;
				nRet = BurnLoadRom(System16Sprites2 + Offset + 2, i + 5, 8); if (nRet) return 1;
				nRet = BurnLoadRom(System16Sprites2 + Offset + 1, i + 6, 8); if (nRet) return 1;
				nRet = BurnLoadRom(System16Sprites2 + Offset + 0, i + 7, 8); if (nRet) return 1;
				
				BurnDrvGetRomInfo(&ri, i + 0);
				Offset += ri.nLen;
				BurnDrvGetRomInfo(&ri, i + 1);
				Offset += ri.nLen;
				BurnDrvGetRomInfo(&ri, i + 2);
				Offset += ri.nLen;
				BurnDrvGetRomInfo(&ri, i + 3);
				Offset += ri.nLen;
				BurnDrvGetRomInfo(&ri, i + 4);
				Offset += ri.nLen;
				BurnDrvGetRomInfo(&ri, i + 5);
				Offset += ri.nLen;
				BurnDrvGetRomInfo(&ri, i + 6);
				Offset += ri.nLen;
				BurnDrvGetRomInfo(&ri, i + 7);
				Offset += ri.nLen;
			}
		}
		
		// Road Roms
		if (System16RoadRomSize) {
			Offset = 0;
			System16TempGfx = (unsigned char*)malloc(System16RoadRomSize);
			for (i = System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum; i < System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum; i++) {
				nRet = BurnLoadRom(System16TempGfx + Offset, i, 1); if (nRet) return 1;
			
				BurnDrvGetRomInfo(&ri, i + 0);
				Offset += ri.nLen;
			}
			if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_OUTRUN || (BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEMX) OutrunDecodeRoad();
			if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_HANGON) HangonDecodeRoad();
			free(System16TempGfx);
		}
		
		// Z80 Program Roms
		Offset = 0;
		for (i = System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum; i < System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum; i++) {
			nRet = BurnLoadRom(System16Z80Rom + Offset, i, 1);
			if (nRet) {
				// Fill with 0xff
				for (int j = 0; j < 0x8000; j++) {
					System16Z80Rom[j] = 0xff;
				}
				
				nRet = 0;
			}
			
			BurnDrvGetRomInfo(&ri, i + 0);
			Offset += ri.nLen;
		}
		
		// Z80 #2 Program Roms
		if (System16Z80Rom2Size) {
			Offset = 0;
			for (i = System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum+ System16Z80RomNum; i < System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num; i++) {
				nRet = BurnLoadRom(System16Z80Rom2 + Offset, i, 1); if (nRet) return 1;
			
				BurnDrvGetRomInfo(&ri, i + 0);
				Offset += ri.nLen;
			}
		}
		
		// Z80 #3 Program Roms
		if (System16Z80Rom3Size) {
			Offset = 0;
			for (i = System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num; i < System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num + System16Z80Rom3Num; i++) {
				nRet = BurnLoadRom(System16Z80Rom3 + Offset, i, 1); if (nRet) return 1;
			
				BurnDrvGetRomInfo(&ri, i + 0);
				Offset += ri.nLen;
			}
		}
		
		// Z80 #4 Program Roms
		if (System16Z80Rom4Size) {
			Offset = 0;
			for (i = System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num + System16Z80Rom3Num; i < System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num + System16Z80Rom3Num + System16Z80Rom4Num; i++) {
				nRet = BurnLoadRom(System16Z80Rom4 + Offset, i, 1); if (nRet) return 1;
			
				BurnDrvGetRomInfo(&ri, i + 0);
				Offset += ri.nLen;
			}
		}
		
		// 7751 Program Roms
		if (System167751ProgSize) {
			Offset = 0;
			for (i = System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num + System16Z80Rom3Num + System16Z80Rom4Num; i < System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num + System16Z80Rom3Num + System16Z80Rom4Num + System167751ProgNum; i++) {
				nRet = BurnLoadRom(System167751Prog + Offset, i, 1); if (nRet) return 1;
				
				BurnDrvGetRomInfo(&ri, i + 0);
				Offset += ri.nLen;
			}
		}
		
		// 7751 Data Roms
		if (System167751DataSize) {
			Offset = 0;
			for (i = System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num + System16Z80Rom3Num + System16Z80Rom4Num + System167751ProgNum; i < System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num + System16Z80Rom3Num + System16Z80Rom4Num + System167751ProgNum + System167751DataNum; i++) {
				nRet = BurnLoadRom(System167751Data + Offset, i, 1); if (nRet) return 1;
				
				BurnDrvGetRomInfo(&ri, i + 0);
				Offset += ri.nLen;
			}
		}
		
		// UPD7759 Data Roms
		if (System16UPD7759DataSize) {
			Offset = 0;
			for (i = System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num + System16Z80Rom3Num + System16Z80Rom4Num + System167751ProgNum + System167751DataNum; i < System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num + System16Z80Rom3Num + System16Z80Rom4Num + System167751ProgNum + System167751DataNum + System16UPD7759DataNum; i++) {
				nRet = BurnLoadRom(System16UPD7759Data + Offset, i, 1); if (nRet) return 1;
				
				BurnDrvGetRomInfo(&ri, i + 0);
				Offset += ri.nLen;
			}
		}
		
		// PCM Data Roms
		if (System16PCMDataSize) {
			Offset = 0;
			for (i = System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num + System16Z80Rom3Num + System16Z80Rom4Num + System167751ProgNum + System167751DataNum + System16UPD7759DataNum; i < System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num + System16Z80Rom3Num + System16Z80Rom4Num + System167751ProgNum + System167751DataNum + System16UPD7759DataNum + System16PCMDataNum; i++) {
				nRet = BurnLoadRom(System16PCMData + Offset, i, 1); if (nRet) return 1;
				
				BurnDrvGetRomInfo(&ri, i + 0);
				Offset += ri.nLen;
			}
		}
		
		// PCM2 Data Roms
		if (System16PCM2DataSize) {
			Offset = 0;
			for (i = System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num + System16Z80Rom3Num + System16Z80Rom4Num + System167751ProgNum + System167751DataNum + System16UPD7759DataNum + System16PCMDataNum; i < System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num + System16Z80Rom3Num + System16Z80Rom4Num + System167751ProgNum + System167751DataNum + System16UPD7759DataNum + System16PCMDataNum + System16PCM2DataNum; i++) {
				nRet = BurnLoadRom(System16PCM2Data + Offset, i, 1); if (nRet) return 1;
				
				BurnDrvGetRomInfo(&ri, i + 0);
				Offset += ri.nLen;
			}
		}
		
		// PROMs
		if (System16PromSize) {
			Offset = 0;
			for (i = System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num + System16Z80Rom3Num + System16Z80Rom4Num + System167751ProgNum + System167751DataNum + System16UPD7759DataNum + System16PCMDataNum + System16PCM2DataNum; i < System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num + System16Z80Rom3Num + System16Z80Rom4Num + System167751ProgNum + System167751DataNum + System16UPD7759DataNum + System16PCMDataNum + System16PCM2DataNum + System16PromNum; i++) {
				nRet = BurnLoadRom(System16Prom + Offset, i, 1); if (nRet) return 1;
				
				BurnDrvGetRomInfo(&ri, i + 0);
				Offset += ri.nLen;
			}
		}
		
		// Encryption Key
		if (System16KeySize) {
			Offset = System16RomNum + System16Rom2Num + System16Rom3Num + System16TileRomNum + System16SpriteRomNum + System16Sprite2RomNum + System16RoadRomNum + System16Z80RomNum + System16Z80Rom2Num + System16Z80Rom3Num + System16Z80Rom4Num + System167751ProgNum + System167751DataNum + System16UPD7759DataNum + System16PCMDataNum + System16PCM2DataNum + System16PromNum;
			nRet = BurnLoadRom(System16Key, Offset, 1); if (nRet) return 1;
		}
	}
	
	return nRet;
}

int CustomLoadRom20000()
{
	int nRet = 1;
	unsigned char *pTemp = (unsigned char*)malloc(0xc0000);
	
	if (pTemp) {
		memcpy(pTemp, System16Rom, 0xc0000);
		memset(System16Rom, 0, 0xc0000);
		memcpy(System16Rom + 0x00000, pTemp + 0x00000, 0x20000);
		memcpy(System16Rom + 0x80000, pTemp + 0x20000, 0x40000);
		free(pTemp);
		nRet = 0;
	}
		
	return nRet;
}

int CustomLoadRom40000()
{
	int nRet = 1;
	unsigned char *pTemp = (unsigned char*)malloc(0xc0000);
	
	if (pTemp) {
		memcpy(pTemp, System16Rom, 0xc0000);
		memset(System16Rom, 0, 0xc0000);
		memcpy(System16Rom + 0x00000, pTemp + 0x00000, 0x40000);
		memcpy(System16Rom + 0x80000, pTemp + 0x40000, 0x40000);
		free(pTemp);
		nRet = 0;
	}
		
	return nRet;
}

/*====================================================
Sound Support Functions
====================================================*/

inline static int System16SndGetBank(int Reg86)
{
	return (Reg86>>4)&7;
}

inline static int PdriftSndGetBank(int Reg86)
{
	return (Reg86>>3)&0x1f;
}

inline void System16YM2151IRQHandler(int Irq)
{
	if (Irq) {
		ZetSetIRQLine(0xff, ZET_IRQSTATUS_ACK);
	} else {
		ZetSetIRQLine(0,    ZET_IRQSTATUS_NONE);
	}
}

inline static void System16YM2203IRQHandler(int, int nStatus)
{
	if (nStatus & 1) {
		ZetSetIRQLine(0xFF, ZET_IRQSTATUS_ACK);
	} else {
		ZetSetIRQLine(0,    ZET_IRQSTATUS_NONE);
	}
}

inline static int System16SynchroniseStream(int nSoundRate)
{
	return (long long)ZetTotalCycles() * nSoundRate / 4000000;
}

inline static double System16GetTime()
{
	return (double)ZetTotalCycles() / 4000000;
}

/*====================================================
Multiply Protection Chip Emulation
====================================================*/

struct multiply_chip
{
	UINT16	regs[4];
};

static struct multiply_chip multiply[3];

UINT16 System16MultiplyChipRead(int which, int offset)
{
	offset &= 3;
	switch (offset) {
		case 0:	{
			return multiply[which].regs[0];
		}
		
		case 1:	{
			return multiply[which].regs[1];
		}
		
		case 2:	{
			return ((INT16)multiply[which].regs[0] * (INT16)multiply[which].regs[1]) >> 16;
		}
		
		case 3:	{
			return ((INT16)multiply[which].regs[0] * (INT16)multiply[which].regs[1]) & 0xffff;
		}
	}
	
	return 0xffff;
}

void System16MultiplyChipWrite(int which, int offset, UINT16 data)
{
	offset &= 3;
	switch (offset) {
		case 0: {
			multiply[which].regs[0] = data;
			return;
		}
		
		case 1: {
			multiply[which].regs[1] = data;
			return;
		}
		
		case 2: {
			multiply[which].regs[0] = data;
			return;
		}
		
		case 3: {
			multiply[which].regs[1] = data;
			return;
		}
	}
}

/*====================================================
Divide Protection Chip Emulation
====================================================*/

struct divide_chip
{
	UINT16 	regs[8];
};

static struct divide_chip divide[3];

static void update_divide(int which, int mode)
{
	/* clear the flags by default */
	divide[which].regs[6] = 0;

	/* if mode 0, store quotient/remainder */
	if (mode == 0)
	{
		INT32 dividend = (INT32)((divide[which].regs[0] << 16) | divide[which].regs[1]);
		INT32 divisor = (INT16)divide[which].regs[2];
		INT32 quotient, remainder;

		/* perform signed divide */
		if (divisor == 0)
		{
			quotient = dividend;//((INT32)(dividend ^ divisor) < 0) ? 0x8000 : 0x7fff;
			divide[which].regs[6] |= 0x4000;
		}
		else
			quotient = dividend / divisor;
		remainder = dividend - quotient * divisor;

		/* clamp to 16-bit signed */
		if (quotient < -32768)
		{
			quotient = -32768;
			divide[which].regs[6] |= 0x8000;
		}
		else if (quotient > 32767)
		{
			quotient = 32767;
			divide[which].regs[6] |= 0x8000;
		}

		/* store quotient and remainder */
		divide[which].regs[4] = quotient;
		divide[which].regs[5] = remainder;
	}

	/* if mode 1, store 32-bit quotient */
	else
	{
		UINT32 dividend = (UINT32)((divide[which].regs[0] << 16) | divide[which].regs[1]);
		UINT32 divisor = (UINT16)divide[which].regs[2];
		UINT32 quotient;

		/* perform unsigned divide */
		if (divisor == 0)
		{
			quotient = dividend;//0x7fffffff;
			divide[which].regs[6] |= 0x4000;
		}
		else
			quotient = dividend / divisor;

		/* store 32-bit quotient */
		divide[which].regs[4] = quotient >> 16;
		divide[which].regs[5] = quotient & 0xffff;
	}
}

UINT16 System16DivideChipRead(int which, int offset)
{
	offset &= 7;
	switch (offset) {
		case 0:	{
			return divide[which].regs[0];
		}
		
		case 1:	{
			return divide[which].regs[1];
		}
		
		case 2:	{
			return divide[which].regs[2];
		}
		
		case 4:	{
			return divide[which].regs[4];
		}
		
		case 5:	{
			return divide[which].regs[5];
		}
		
		case 6:	{
			return divide[which].regs[6];
		}
	}
	
	return 0xffff;
}

void System16DivideChipWrite(int which, int offset, UINT16 data)
{
	int a4 = offset & 8;
	int a3 = offset & 4;
	
	offset &= 3;
	switch (offset) {
		case 0: {
			divide[which].regs[0] = data;
			break;
		}
		
		case 1: {
			divide[which].regs[1] = data;
			break;
		}
		
		case 2: {
			divide[which].regs[2] = data;
			break;
		}
		
		case 3: {
			break;
		}
	}
	
	if (a4) update_divide(which, a3);
}

/*====================================================
Compare Timer Protection Chip Emulation
====================================================*/

struct compare_timer_chip
{
	UINT16	regs[16];
	UINT16	counter;
	UINT8	bit;
//	void	(*sound_w)(UINT8);
//	void	(*timer_ack)(void);
};

static struct compare_timer_chip compare_timer[2];

inline static int segaic16_compare_timer_clock(int which)
{
	int old_counter = compare_timer[which].counter;
	int result = 0;

	/* if we're enabled, clock the upcounter */
	if (compare_timer[which].regs[10] & 1)
		compare_timer[which].counter++;

	/* regardless of the enable, a value of 0xfff will generate the IRQ */
	if (old_counter == 0xfff)
	{
		result = 1;
		compare_timer[which].counter = compare_timer[which].regs[8] & 0xfff;
	}
	return result;
}

inline static void update_compare(int which, int update_history)
{
	int bound1 = (INT16)compare_timer[which].regs[0];
	int bound2 = (INT16)compare_timer[which].regs[1];
	int value = (INT16)compare_timer[which].regs[2];
	int min = (bound1 < bound2) ? bound1 : bound2;
	int max = (bound1 > bound2) ? bound1 : bound2;

	if (value < min)
	{
		compare_timer[which].regs[7] = min;
		compare_timer[which].regs[3] = 0x8000;
	}
	else if (value > max)
	{
		compare_timer[which].regs[7] = max;
		compare_timer[which].regs[3] = 0x4000;
	}
	else
	{
		compare_timer[which].regs[7] = value;
		compare_timer[which].regs[3] = 0x0000;
	}

	if (update_history)
		compare_timer[which].regs[4] |= (compare_timer[which].regs[3] == 0) << compare_timer[which].bit++;
}

UINT16 System16CompareTimerChipRead(int which, int offset)
{
	offset &= 0xf;
	switch (offset) {
		case 0x0:	return compare_timer[which].regs[0];
		case 0x1:	return compare_timer[which].regs[1];
		case 0x2:	return compare_timer[which].regs[2];
		case 0x3:	return compare_timer[which].regs[3];
		case 0x4:	return compare_timer[which].regs[4];
		case 0x5:	return compare_timer[which].regs[1];
		case 0x6:	return compare_timer[which].regs[2];
		case 0x7:	return compare_timer[which].regs[7];
//		case 0x9:
//		case 0xd:	bprintf(PRINT_IMPORTANT, _T("timer_int_ack(%x)\n"), which); /*timer_interrupt_ack(which);*/ break;
	}
	
	return 0xffff;
}

void System16CompareTimerChipWrite(int which, int offset, UINT16 data)
{
	offset &= 0xf;
	switch (offset) {
		case 0x0:	compare_timer[which].regs[0] = data; update_compare(which, 0); break;
		case 0x1:	compare_timer[which].regs[1] = data; update_compare(which, 0); break;
		case 0x2:	compare_timer[which].regs[2] = data; update_compare(which, 1); break;
		case 0x4:	compare_timer[which].regs[4] = 0; compare_timer[which].bit = 0; break;
		case 0x6:	compare_timer[which].regs[2] = data; update_compare(which, 0); break;
		case 0x8:
		case 0xc:	compare_timer[which].regs[8] = data; break;
//		case 0x9:
//		case 0xd:	bprintf(PRINT_IMPORTANT, _T("timer_int_ack(%x)\n"), which); /*timer_interrupt_ack(which);*/ break;
		case 0xa:
		case 0xe:	compare_timer[which].regs[10] = data; break;
		case 0xb:
		case 0xf:
			compare_timer[which].regs[11] = data;
//			if (compare_timer[which].sound_w)
//				(*compare_timer[which].sound_w)(compare_timer[which].regs[11]);
			break;
	}
}

/*====================================================
Main Driver Init function
====================================================*/

int System16Init()
{
	int nRet = 0, nLen;
	
	// Allocate and Blank all required memory
	Mem = NULL;
	System16LoadRoms(0); // Get required rom sizes
	System16MemIndex();
	nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) return 1;
	memset(Mem, 0, nLen);
	System16MemIndex();
	
	// Load Roms
	nRet = System16LoadRoms(1); if (nRet) return 1;
	if (System16CustomLoadRomDo) { nRet = System16CustomLoadRomDo(); if (nRet) return 1; }
	
	// Copy the first 68000 rom to code (FETCH)
	memcpy(System16Code, System16Rom, 0x100000);
	
	// Handle any op-code decryption
	if (System16CustomDecryptOpCodeDo) { nRet = System16CustomDecryptOpCodeDo(); if (nRet) return 1; }
	
	if (BurnDrvGetHardwareCode() & HARDWARE_SEGA_FD1089A_ENC || BurnDrvGetHardwareCode() & HARDWARE_SEGA_FD1089B_ENC) {
		FD1089_Decrypt();
	}
	
	if (BurnDrvGetHardwareCode() & HARDWARE_SEGA_FD1094_ENC) {
		// Make sure we use Musashi
		if (bBurnUseASMCPUEmulation) {
#if 1 && defined FBA_DEBUG
			bprintf(PRINT_NORMAL, _T("Switching to Musashi 68000 core\n"));
#endif
			bUseAsm68KCoreOldValue = bBurnUseASMCPUEmulation;
			bBurnUseASMCPUEmulation = false;
		}
		
		fd1094_driver_init();
	}
	
	// Setup the 68000 emulation
	if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEM16A || (BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEM16B) {
		if (System16Map68KDo) {
			System16Map68KDo();
		} else {
			SekInit(0, 0x68000);
			SekOpen(0);
			SekMapMemory(System16Rom           , 0x000000, 0x0fffff, SM_READ);
			SekMapMemory(System16Code          , 0x000000, 0x0fffff, SM_FETCH);
			SekMapMemory(System16TileRam       , 0x400000, 0x40ffff, SM_RAM);
			SekMapMemory(System16TextRam       , 0x410000, 0x410fff, SM_RAM);
			SekMapMemory(System16SpriteRam     , 0x440000, 0x4407ff, SM_RAM);
			SekMapMemory(System16PaletteRam    , 0x840000, 0x840fff, SM_RAM);
			SekMapMemory(System16Ram           , 0xffc000, 0xffffff, SM_RAM);
		
			if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEM16A) {
				SekSetReadWordHandler(0, System16AReadWord);
				SekSetWriteWordHandler(0, System16AWriteWord);
				SekSetReadByteHandler(0, System16AReadByte);
				SekSetWriteByteHandler(0, System16AWriteByte);
				SekClose();
			}
	
			if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEM16B) {
				SekSetReadWordHandler(0, System16BReadWord);
				SekSetWriteWordHandler(0, System16BWriteWord);
				SekSetReadByteHandler(0, System16BReadByte);
				SekSetWriteByteHandler(0, System16BWriteByte);
				SekClose();
			}
		}
	}
	
	if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_HANGON) {
		if (System16Map68KDo) {
			System16Map68KDo();
		} else {
			SekInit(0, 0x68000);
			SekOpen(0);
			SekMapMemory(System16Rom             , 0x000000, 0x03ffff, SM_READ);
			SekMapMemory(System16Code            , 0x000000, 0x03ffff, SM_FETCH);
			SekMapMemory(System16Ram             , 0x200000, 0x20ffff, SM_RAM);
			SekMapMemory(System16TileRam         , 0x400000, 0x403fff, SM_RAM);
			SekMapMemory(System16TextRam         , 0x410000, 0x410fff, SM_RAM);
			SekMapMemory(System16SpriteRam       , 0x600000, 0x607fff, SM_RAM);
			SekMapMemory(System16PaletteRam      , 0xa00000, 0xa00fff, SM_RAM);
			SekMapMemory(System16Rom2            , 0xc00000, 0xc3ffff, SM_READ);
			SekMapMemory(System16RoadRam         , 0xc68000, 0xc68fff, SM_RAM);
			SekMapMemory(System16ExtraRam        , 0xc7c000, 0xc7ffff, SM_RAM);
			
			SekSetReadByteHandler(0, HangonReadByte);
			SekSetWriteByteHandler(0, HangonWriteByte);
			SekClose();
		}
		
		SekInit(1, 0x68000);
		SekOpen(1);
		SekMapMemory(System16Rom2            , 0x000000, 0x03ffff, SM_READ);
		SekMapMemory(System16Rom2            , 0x000000, 0x03ffff, SM_FETCH);
		SekMapMemory(System16RoadRam         , 0xc68000, 0xc68fff, SM_RAM);
		SekMapMemory(System16ExtraRam        , 0xc7c000, 0xc7ffff, SM_RAM);
		SekClose();
	}
	
	if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_OUTRUN) {
		SekInit(0, 0x68000);
		SekOpen(0);
		SekMapMemory(System16Rom           , 0x000000, 0x05ffff, SM_READ);
		SekMapMemory(System16Code          , 0x000000, 0x05ffff, SM_FETCH);
		SekMapMemory(System16ExtraRam      , 0x060000, 0x067fff, SM_RAM);
		SekMapMemory(System16TileRam       , 0x100000, 0x10ffff, SM_RAM);
		SekMapMemory(System16TextRam       , 0x110000, 0x110fff, SM_RAM);
		SekMapMemory(System16PaletteRam    , 0x120000, 0x121fff, SM_RAM);
		SekMapMemory(System16SpriteRam     , 0x130000, 0x130fff, SM_RAM);
		SekMapMemory(System16Rom2          , 0x200000, 0x23ffff, SM_READ);
		SekMapMemory(System16Ram           , 0x260000, 0x267fff, SM_RAM);
		SekMapMemory(System16RoadRam       , 0x280000, 0x280fff, SM_RAM);
		SekSetResetCallback(OutrunResetCallback);
		SekSetReadWordHandler(0, OutrunReadWord);
		SekSetWriteWordHandler(0, OutrunWriteWord);
		SekSetReadByteHandler(0, OutrunReadByte);
		SekSetWriteByteHandler(0, OutrunWriteByte);
		SekClose();
		
		SekInit(1, 0x68000);
		SekOpen(1);
		SekMapMemory(System16Rom2          , 0x000000, 0x03ffff, SM_READ);
		SekMapMemory(System16Rom2          , 0x000000, 0x03ffff, SM_FETCH);
		SekMapMemory(System16Ram           , 0x060000, 0x067fff, SM_RAM);
		SekMapMemory(System16RoadRam       , 0x080000, 0x080fff, SM_RAM);
		SekSetReadWordHandler(0, Outrun2ReadWord);
		SekSetWriteWordHandler(0, Outrun2WriteWord);
		SekSetReadByteHandler(0, Outrun2ReadByte);
		SekSetWriteByteHandler(0, Outrun2WriteByte);
		SekClose();
		
		System16RoadColorOffset1 = 0x400;
		System16RoadColorOffset2 = 0x420;
		System16RoadColorOffset3 = 0x780;
	}
	
	if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEMX) {
		SekInit(0, 0x68000);
		SekOpen(0);
		SekMapMemory(System16Rom           , 0x000000, 0x07ffff, SM_READ);
		SekMapMemory(System16Code          , 0x000000, 0x07ffff, SM_FETCH);
		SekMapMemory(System16TileRam       , 0x0c0000, 0x0cffff, SM_RAM);
		SekMapMemory(System16TextRam       , 0x0d0000, 0x0d0fff, SM_RAM);
		SekMapMemory(System16SpriteRam     , 0x100000, 0x100fff, SM_RAM);
		SekMapMemory(System16SpriteRam     , 0x101000, 0x101fff, SM_RAM); // Tests past Sprite RAM in mem tests (mirror?)
		SekMapMemory(System16SpriteRam     , 0x102000, 0x102fff, SM_RAM); // Tests past Sprite RAM in mem tests (mirror?)
		SekMapMemory(System16SpriteRam     , 0x103000, 0x103fff, SM_RAM); // Tests past Sprite RAM in mem tests (mirror?)
		SekMapMemory(System16SpriteRam     , 0x104000, 0x104fff, SM_RAM); // Tests past Sprite RAM in mem tests (mirror?)
		SekMapMemory(System16SpriteRam     , 0x105000, 0x105fff, SM_RAM); // Tests past Sprite RAM in mem tests (mirror?)
		SekMapMemory(System16SpriteRam     , 0x106000, 0x106fff, SM_RAM); // Tests past Sprite RAM in mem tests (mirror?)
		SekMapMemory(System16SpriteRam     , 0x107000, 0x107fff, SM_RAM); // Tests past Sprite RAM in mem tests (mirror?)
		SekMapMemory(System16SpriteRam     , 0x108000, 0x108fff, SM_RAM); // Tests past Sprite RAM in mem tests (mirror?)
		SekMapMemory(System16SpriteRam     , 0x109000, 0x109fff, SM_RAM); // Tests past Sprite RAM in mem tests (mirror?)
		SekMapMemory(System16SpriteRam     , 0x10a000, 0x10afff, SM_RAM); // Tests past Sprite RAM in mem tests (mirror?)
		SekMapMemory(System16SpriteRam     , 0x10b000, 0x10bfff, SM_RAM); // Tests past Sprite RAM in mem tests (mirror?)
		SekMapMemory(System16SpriteRam     , 0x10c000, 0x10cfff, SM_RAM); // Tests past Sprite RAM in mem tests (mirror?)
		SekMapMemory(System16SpriteRam     , 0x10d000, 0x10dfff, SM_RAM); // Tests past Sprite RAM in mem tests (mirror?)
		SekMapMemory(System16SpriteRam     , 0x10e000, 0x10efff, SM_RAM); // Tests past Sprite RAM in mem tests (mirror?)
		SekMapMemory(System16SpriteRam     , 0x10f000, 0x10ffff, SM_RAM); // Tests past Sprite RAM in mem tests (mirror?)
		SekMapMemory(System16PaletteRam    , 0x120000, 0x123fff, SM_RAM);
		SekMapMemory(System16Rom2          , 0x200000, 0x27ffff, SM_READ);
		SekMapMemory(System16Ram           , 0x29c000, 0x2a3fff, SM_RAM);
		SekMapMemory(System16RoadRam       , 0x2ec000, 0x2ecfff, SM_RAM);
		SekMapMemory(System16RoadRam       , 0x2ed000, 0x2edfff, SM_RAM); // Tests past Road RAM in mem tests (mirror?)
		SekMapMemory(System16BackupRam2    , 0xff4000, 0xff7fff, SM_RAM);
		SekMapMemory(System16BackupRam     , 0xff8000, 0xffffff, SM_RAM);
		SekMapMemory(System16BackupRam2    , 0xffc000, 0xffffff, SM_RAM);
		SekSetResetCallback(OutrunResetCallback);
		SekSetReadWordHandler(0, XBoardReadWord);
		SekSetWriteWordHandler(0, XBoardWriteWord);
		SekSetReadByteHandler(0, XBoardReadByte);
		SekSetWriteByteHandler(0, XBoardWriteByte);
		SekClose();
		
		SekInit(1, 0x68000);
		SekOpen(1);
		SekMapMemory(System16Rom2          , 0x000000, 0x07ffff, SM_ROM);
		SekMapMemory(System16Ram           , 0x09c000, 0x0a3fff, SM_RAM);
		SekMapMemory(System16RoadRam       , 0x0ec000, 0x0ecfff, SM_RAM);
		SekMapMemory(System16Rom2          , 0x200000, 0x27ffff, SM_ROM);
		SekMapMemory(System16Ram           , 0x29c000, 0x2a3fff, SM_RAM);
		SekMapMemory(System16RoadRam       , 0x2ec000, 0x2ecfff, SM_RAM);
		SekSetReadWordHandler(0, XBoard2ReadWord);
		SekSetWriteWordHandler(0, XBoard2WriteWord);
		SekSetReadByteHandler(0, XBoard2ReadByte);
		SekSetWriteByteHandler(0, XBoard2WriteByte);
		SekClose();
		
		System16RoadColorOffset1 = 0x1700;
		System16RoadColorOffset2 = 0x1720;
		System16RoadColorOffset3 = 0x1780;
		System16RoadXOffset = -166;
		System16RoadPriority = 1;
		System16TilemapColorOffset = 0x1c00;
	}
	
	if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEMY) {
		SekInit(0, 0x68000);
		SekOpen(0);
		SekMapMemory(System16Rom           , 0x000000, 0x07ffff, SM_READ);
		SekMapMemory(System16Code          , 0x000000, 0x07ffff, SM_FETCH);
		SekMapMemory(System16Ram           , 0x0c0000, 0x0cffff, SM_RAM);
		SekMapMemory(System16ExtraRam      , 0xff0000, 0xffffff, SM_RAM);
		SekSetReadWordHandler(0, YBoardReadWord);
		SekSetWriteWordHandler(0, YBoardWriteWord);
		SekSetReadByteHandler(0, YBoardReadByte);
		SekSetWriteByteHandler(0, YBoardWriteByte);
		SekClose();
		
		SekInit(1, 0x68000);
		SekOpen(1);
		SekMapMemory(System16Rom2          , 0x000000, 0x03ffff, SM_ROM);
		SekMapMemory(System16Ram           , 0x0c0000, 0x0cffff, SM_RAM);
		SekMapMemory(System16SpriteRam2    , 0x180000, 0x18ffff, SM_RAM);
		SekMapMemory(System16ExtraRam2     , 0xff0000, 0xffbfff, SM_RAM);
		SekMapMemory(System16BackupRam     , 0xffc000, 0xffffff, SM_RAM);
		SekSetReadWordHandler(0, YBoard2ReadWord);
		SekSetWriteWordHandler(0, YBoard2WriteWord);
		SekSetReadByteHandler(0, YBoard2ReadByte);
		SekSetWriteByteHandler(0, YBoard2WriteByte);
		SekClose();
		
		SekInit(2, 0x68000);
		SekOpen(2);
		SekMapMemory(System16Rom3          , 0x000000, 0x03ffff, SM_ROM);
		SekMapMemory(System16Ram           , 0x0c0000, 0x0cffff, SM_RAM);
		SekMapMemory(System16RotateRam     , 0x180000, 0x1807ff, SM_RAM);
		SekMapMemory(System16SpriteRam     , 0x188000, 0x188fff, SM_RAM);
		SekMapMemory(System16PaletteRam    , 0x190000, 0x193fff, SM_RAM);
		SekMapMemory(System16PaletteRam    , 0x194000, 0x197fff, SM_RAM);
		SekMapMemory(System16ExtraRam3     , 0xff0000, 0xffffff, SM_RAM);
		SekSetReadWordHandler(0, YBoard3ReadWord);
		SekSetWriteWordHandler(0, YBoard3WriteWord);
		SekSetReadByteHandler(0, YBoard3ReadByte);
		SekSetWriteByteHandler(0, YBoard3WriteByte);
		SekClose();
		
		YBoardIrq2Scanline = 170;
	}
	
	if (BurnDrvGetHardwareCode() & HARDWARE_SEGA_MC8123_ENC) {
		mc8123_decrypt_rom(1, System16Key, 0, 0);
	}
	
	// Setup the Z80 emulation
	ZetInit(1);
	if (BurnDrvGetHardwareCode() & HARDWARE_SEGA_YM2203) {
		ZetMapArea(0x0000, 0x7fff, 0, System16Z80Rom);
		ZetMapArea(0x0000, 0x7fff, 2, System16Z80Rom);
	
		ZetMapArea(0xc000, 0xc7ff, 0, System16Z80Ram);
		ZetMapArea(0xc000, 0xc7ff, 1, System16Z80Ram);
		ZetMapArea(0xc000, 0xc7ff, 2, System16Z80Ram);
		ZetMemEnd();
		
		ZetSetReadHandler(System16Z802203Read);
		ZetSetWriteHandler(System16Z802203Write);
		ZetSetInHandler(System16Z802203PortRead);
	} else {
		ZetMapArea(0x0000, 0xefff, 0, System16Z80Rom);
		ZetMapArea(0x0000, 0xefff, 2, System16Z80Rom);
	
		ZetMapArea(0xf800, 0xffff, 0, System16Z80Ram);
		ZetMapArea(0xf800, 0xffff, 1, System16Z80Ram);
		ZetMapArea(0xf800, 0xffff, 2, System16Z80Ram);
		ZetMemEnd();
		
		if (System16PCMDataSize) {
			ZetSetReadHandler(System16Z80PCMRead);
			ZetSetWriteHandler(System16Z80PCMWrite);
		} else {
			ZetSetReadHandler(System16Z80Read);
			ZetSetWriteHandler(System16Z80Write);
		}		
		ZetSetInHandler(System16Z80PortRead);
		ZetSetOutHandler(System16Z80PortWrite);
	}
		
	ZetClose();
	
	// Setup the FM emulation
	if (BurnDrvGetHardwareCode() & HARDWARE_SEGA_YM2203) {
		BurnYM2203Init(4000000, &System16YM2203IRQHandler, System16SynchroniseStream, System16GetTime);
		BurnTimerAttachZet(4000000);
	} else {
		BurnYM2151Init(4000000, 25.0);
		if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_HANGON || (BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEMY) {
			BurnYM2151SetIrqHandler(&System16YM2151IRQHandler);
		}
	}
	
	if (System16PCMDataSize) {
		PcmRate = nBurnSoundRate;
		PcmRom = System16PCMData;
		if (System16PCMDataSize == 0x10000) { PcmBankSize = 16; PcmBankCount = 1; }
		if (System16PCMDataSize == 0x20000) { PcmBankSize = 15; PcmBankCount = 4; }
		if (System16PCMDataSize == 0x30000) { PcmBankSize = 15; PcmBankCount = 6; }
		if (System16PCMDataSize == 0x60000) { PcmBankSize = 16; PcmBankCount = 6; }
		
		PcmGetBank = System16SndGetBank;
		
		if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEMY) {
			PcmBankSize = 16;
			PcmBankCount = System16PCMDataSize >> 16;
			PcmGetBank = PdriftSndGetBank;
		}
		
		PcmInit();
	}
	
	if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEM16A) {
		if (PPI0PortWriteA == NULL) PPI0PortWriteA = System16APPI0WritePortA;
		if (PPI0PortWriteB == NULL) PPI0PortWriteB = System16APPI0WritePortB;
		if (PPI0PortWriteC == NULL) PPI0PortWriteC = System16APPI0WritePortC;
		
		ZetOpen(0);
		ZetSetInHandler(System16PPIZ80PortRead);
		ZetClose();
		
		ppi8255_init(1);
	}
	
	if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_OUTRUN) {
		if (PPI0PortWriteC == NULL) PPI0PortWriteC = OutrunPPI0WritePortC;
		
		ppi8255_init(1);
	}
	
	if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_HANGON) {
		if (PPI0PortWriteA == NULL) PPI0PortWriteA = HangonPPI0WritePortA;
		if (PPI0PortWriteB == NULL) PPI0PortWriteB = HangonPPI0WritePortB;
		if (PPI0PortWriteC == NULL) PPI0PortWriteC = HangonPPI0WritePortC;
		if (PPI1PortReadC == NULL) PPI1PortReadC = HangonPPI1ReadPortC;
		if (PPI1PortWriteA == NULL) PPI1PortWriteA = HangonPPI1WritePortA;
		
		if (!(BurnDrvGetHardwareCode() & HARDWARE_SEGA_YM2203)) {
			ZetOpen(0);
			ZetSetInHandler(System16PPIZ80PortRead);
			ZetClose();
		}
		
		ppi8255_init(2);
	}
	
	GenericTilesInit();
	
	// Reset the driver
	System16DoReset();
	
	return 0;
}

/*====================================================
Exit Function
====================================================*/

int System16Exit()
{
	int i;
	
	if (BurnDrvGetHardwareCode() & HARDWARE_SEGA_YM2203) {
		BurnYM2203Exit();
	} else {
		BurnYM2151Exit();
	}
	
	SekExit();
	ZetExit();
	
	PcmExit();
	
	ppi8255_exit();
	
	GenericTilesExit();

	free(Mem);
	Mem = NULL;
	
	// Reset Variables
	for (i = 0; i < 4; i++) {
		System16Page[i] = 0;
		System16ScrollX[i] = 0;
		System16ScrollY[i] = 0;
	}
	
	for (i = 0; i < 16; i++) {
		System16SpriteBanks[i] = 0;
	}
	
	for (i = 0; i < 2; i++) {
		System16TileBanks[i] = 0;
	}
	
	System16VideoEnable = 0;
	System16ScreenFlip = 0;
	System16SpriteShadow = 0;
	System16VideoControl = 0;
	System16SoundLatch = 0;
	System16ColScroll = 0;
	System16RowScroll = 0;
	
	System16LastGear = 0;
	System16HasGears = false;

 	System16RoadControl = 0;
 	System16RoadColorOffset1 = 0;
 	System16RoadColorOffset2 = 0;
 	System16RoadColorOffset3 = 0;
 	System16RoadXOffset = 0;
 	System16RoadPriority = 0;
 	System16AnalogSelect = 0;
 	
 	System16ClockSpeed = 0;
 	
 	System16PaletteEntries = 0;
 	System16RamSize = 0;
 	System16ExtraRamSize = 0;
 	System16ExtraRam2Size = 0;
 	System16ExtraRam3Size = 0;
 	System16SpriteRamSize = 0;
 	System16SpriteRam2Size = 0;
 	System16RotateRamSize = 0;
 	System16TilemapColorOffset = 0;
	
	System16BTileAlt = false;
	Shangon = false;
	Hangon = false;
	System16Gun = false;
	
	System16Gun1X = 160 << 8;
 	System16Gun1Y = 112 << 8;
 	System16Gun2X = 160 << 8;
 	System16Gun2Y = 112 << 8;
 	
 	YBoardIrq2Scanline = 0;
	
	System16RomSize = 0;
	System16RomNum = 0;
	System16Rom2Size = 0;
	System16Rom2Num = 0;
	System16Rom3Size = 0;
	System16Rom3Num = 0;
	System16TileRomSize = 0;
 	System16TileRomNum = 0;
 	System16NumTiles = 0;
 	System16SpriteRomSize = 0;
 	System16SpriteRomNum = 0;
 	System16Sprite2RomSize = 0;
 	System16Sprite2RomNum = 0;
 	System16RoadRomSize = 0;
 	System16RoadRomNum = 0;
 	System16Z80RomSize = 0;
 	System16Z80RomNum = 0;
 	System16Z80Rom2Size = 0;
 	System16Z80Rom2Num = 0;
 	System16Z80Rom3Size = 0;
 	System16Z80Rom3Num = 0;
 	System16Z80Rom4Size = 0;
 	System16Z80Rom4Num = 0;
 	System167751ProgSize = 0;
 	System167751ProgNum = 0;
 	System167751DataSize = 0;
 	System167751DataNum = 0;
 	System16UPD7759DataSize = 0;
 	System16UPD7759DataNum = 0;
 	System16PCMDataSize = 0;
 	System16PCMDataNum = 0;
 	System16PCM2DataSize = 0;
 	System16PCM2DataNum = 0;
 	System16PromSize = 0;
	System16PromNum = 0;
 	System16KeySize = 0;
 	
 	Simulate8751 = NULL;
 	System16Map68KDo = NULL;
 	System16CustomLoadRomDo = NULL;
 	System16CustomDecryptOpCodeDo = NULL;
 	System16ProcessAnalogControlsDo = NULL;
 	System16MakeAnalogInputsDo = NULL;
 	FD1089_Decrypt = NULL;
 	
 	memset(multiply, 0, sizeof(multiply));
 	memset(divide, 0, sizeof(divide));
 	memset(compare_timer, 0, sizeof(compare_timer));
 	
 	if (BurnDrvGetHardwareCode() & HARDWARE_SEGA_FD1094_ENC) {
		// Switch back CPU core if needed
		if (bUseAsm68KCoreOldValue) {
#if 1 && defined FBA_DEBUG
			bprintf(PRINT_NORMAL, _T("Switching back to A68K core\n"));
#endif
			bUseAsm68KCoreOldValue = false;
			bBurnUseASMCPUEmulation = true;
		}
	}
 	
	return 0;
}

/*====================================================
Frame Functions
====================================================*/

int System16AFrame()
{
	int nInterleave = 10;

	if (System16Reset) System16DoReset();

	System16MakeInputs();
	
	nCyclesTotal[0] = 10000000 / 60;
	nCyclesTotal[1] = 4000000 / 60;
	nSystem16CyclesDone[0] = nSystem16CyclesDone[1] = 0;

	int nSoundBufferPos = 0;

	SekNewFrame();

	SekOpen(0);
	for (int i = 0; i < nInterleave; i++) {
		int nCurrentCPU, nNext;

		// Run 68000
		nCurrentCPU = 0;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nSystem16CyclesDone[nCurrentCPU] += SekRun(nCyclesSegment);

		// Run Z80
		nCurrentCPU = 1;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nCyclesSegment = ZetRun(nCyclesSegment);
		nSystem16CyclesDone[nCurrentCPU] += nCyclesSegment;

		if (pBurnSoundOut) {
			int nSegmentLength = nBurnSoundLen / nInterleave;
			short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);

			BurnYM2151Render(pSoundBuf, nSegmentLength);
			nSoundBufferPos += nSegmentLength;
		}
	}

	SekSetIRQLine(4, SEK_IRQSTATUS_AUTO);
	SekClose();
	
	if (Simulate8751) Simulate8751();

	// Make sure the buffer is entirely filled.
	if (pBurnSoundOut) {
		int nSegmentLength = nBurnSoundLen - nSoundBufferPos;
		short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);

		if (nSegmentLength) {
			BurnYM2151Render(pSoundBuf, nSegmentLength);
		}
	}

	if (pBurnDraw) System16ARender();

	return 0;
}

int System16BFrame()
{
	int nInterleave = 10;

	if (System16Reset) System16DoReset();

	System16MakeInputs();
	
	nCyclesTotal[0] = 10000000 / 60;
	nCyclesTotal[1] = 5000000 / 60;
	nSystem16CyclesDone[0] = nSystem16CyclesDone[1] = 0;

	int nSoundBufferPos = 0;
	
	SekNewFrame();
	ZetNewFrame();

	SekOpen(0);
	for (int i = 0; i < nInterleave; i++) {
		int nCurrentCPU, nNext;

		// Run 68000
		nCurrentCPU = 0;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nSystem16CyclesDone[nCurrentCPU] += SekRun(nCyclesSegment);

		// Run Z80
		nCurrentCPU = 1;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nCyclesSegment = ZetRun(nCyclesSegment);
		nSystem16CyclesDone[nCurrentCPU] += nCyclesSegment;

		if (pBurnSoundOut) {
			int nSegmentLength = nBurnSoundLen / nInterleave;
			short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);

			BurnYM2151Render(pSoundBuf, nSegmentLength);
			nSoundBufferPos += nSegmentLength;
		}
	}

	// Make sure the buffer is entirely filled.
	if (pBurnSoundOut) {
		int nSegmentLength = nBurnSoundLen - nSoundBufferPos;
		short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);

		if (nSegmentLength) {
			BurnYM2151Render(pSoundBuf, nSegmentLength);
		}
	}
	
	SekSetIRQLine(4, SEK_IRQSTATUS_AUTO);
	SekClose();
	
	if (Simulate8751) Simulate8751();

	if (pBurnDraw) {
		if (System16BTileAlt) {
			System16BAltRender();
		} else {
			System16BRender();
		}
	}

	return 0;
}

int HangonFrame()
{
	int nInterleave = 10, i;

	if (System16Reset) System16DoReset();

	System16MakeInputs();
	
	nCyclesTotal[0] = System16ClockSpeed / 60;
	nCyclesTotal[1] = System16ClockSpeed / 60;
	nCyclesTotal[2] = 4000000 / 60;
	nSystem16CyclesDone[0] = nSystem16CyclesDone[1] = nSystem16CyclesDone[2] = 0;

	int nSoundBufferPos = 0;
	
	SekNewFrame();
	ZetNewFrame();

	for (i = 0; i < nInterleave; i++) {
		int nCurrentCPU, nNext;

		// Run 68000 #1
		nCurrentCPU = 0;
		SekOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nSystem16CyclesDone[nCurrentCPU] += SekRun(nCyclesSegment);
		SekClose();
		
		// Run 68000 #2
		nCurrentCPU = 1;
		SekOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nCyclesSegment = SekRun(nCyclesSegment);
		nSystem16CyclesDone[nCurrentCPU] += nCyclesSegment;
		SekClose();

		// Run Z80
		nCurrentCPU = 2;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nCyclesSegment = ZetRun(nCyclesSegment);
		nSystem16CyclesDone[nCurrentCPU] += nCyclesSegment;

		if (pBurnSoundOut) {
			int nSegmentLength = nBurnSoundLen / nInterleave;
			short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);

			BurnYM2151Render(pSoundBuf, nSegmentLength);
			PcmUpdate(pSoundBuf, nSegmentLength);
			nSoundBufferPos += nSegmentLength;
		}
	}

	// Make sure the buffer is entirely filled.
	if (pBurnSoundOut) {
		int nSegmentLength = nBurnSoundLen - nSoundBufferPos;
		short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);

		if (nSegmentLength) {
			BurnYM2151Render(pSoundBuf, nSegmentLength);
			PcmUpdate(pSoundBuf, nSegmentLength);
		}
	}

	SekOpen(0);
	SekSetIRQLine(4, SEK_IRQSTATUS_AUTO);
	SekClose();
	
	if (Simulate8751) Simulate8751();	

	if (pBurnDraw) {
		HangonRender();
	}

	return 0;
}

int HangonYM2203Frame()
{
	int nInterleave = 10, i;

	if (System16Reset) System16DoReset();

	System16MakeInputs();
	
	nCyclesTotal[0] = System16ClockSpeed / 60;
	nCyclesTotal[1] = System16ClockSpeed / 60;
	nCyclesTotal[2] = 4000000 / 60;
	nSystem16CyclesDone[0] = nSystem16CyclesDone[1] = nSystem16CyclesDone[2] = 0;

	SekNewFrame();
	ZetNewFrame();

	for (i = 0; i < nInterleave; i++) {
		int nCurrentCPU, nNext;

		// Run 68000 #1
		nCurrentCPU = 0;
		SekOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nSystem16CyclesDone[nCurrentCPU] += SekRun(nCyclesSegment);
		SekClose();
		
		// Run 68000 #2
		nCurrentCPU = 1;
		SekOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nCyclesSegment = SekRun(nCyclesSegment);
		nSystem16CyclesDone[nCurrentCPU] += nCyclesSegment;
		SekClose();
	}

	SekOpen(0);
	SekSetIRQLine(4, SEK_IRQSTATUS_AUTO);
	SekClose();
	
	BurnTimerEndFrame(nCyclesTotal[2]);
	BurnYM2203Update(nBurnSoundLen);
	PcmUpdate(pBurnSoundOut, nBurnSoundLen);
	nSystem16CyclesDone[2] = ZetTotalCycles() - nCyclesTotal[2];
	
	if (Simulate8751) Simulate8751();	

	if (pBurnDraw) {
		if (Hangon) {
			HangonAltRender();
		} else {
			HangonRender();
		}
	}

	return 0;
}

int OutrunFrame()
{
	int nInterleave = 10, i;

	if (System16Reset) System16DoReset();

	if (System16HasGears) {
		OutrunMakeInputs();
	} else {
		System16MakeInputs();
	}
	
	nCyclesTotal[0] = (50000000 / 4) / 60;
	nCyclesTotal[1] = (50000000 / 4) / 60;
	nCyclesTotal[2] = (16000000 / 4) / 60;
	nSystem16CyclesDone[0] = nSystem16CyclesDone[1] = nSystem16CyclesDone[2] = 0;

	int nSoundBufferPos = 0;
	
	SekNewFrame();

	for (i = 0; i < nInterleave; i++) {
		int nCurrentCPU, nNext;

		// Run 68000 #1
		nCurrentCPU = 0;
		SekOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nSystem16CyclesDone[nCurrentCPU] += SekRun(nCyclesSegment);
		if (i == 2 || i == 6 || i == 8) SekSetIRQLine(2, SEK_IRQSTATUS_AUTO);
		SekClose();
		
		// Run 68000 #2
		nCurrentCPU = 1;
		SekOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nCyclesSegment = SekRun(nCyclesSegment);
		nSystem16CyclesDone[nCurrentCPU] += nCyclesSegment;
		SekClose();

		// Run Z80
		nCurrentCPU = 2;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nCyclesSegment = ZetRun(nCyclesSegment);
		nSystem16CyclesDone[nCurrentCPU] += nCyclesSegment;

		if (pBurnSoundOut) {
			int nSegmentLength = nBurnSoundLen / nInterleave;
			short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);

			BurnYM2151Render(pSoundBuf, nSegmentLength);
			PcmUpdate(pSoundBuf, nSegmentLength);
			nSoundBufferPos += nSegmentLength;
		}
	}

	// Make sure the buffer is entirely filled.
	if (pBurnSoundOut) {
		int nSegmentLength = nBurnSoundLen - nSoundBufferPos;
		short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);

		if (nSegmentLength) {
			BurnYM2151Render(pSoundBuf, nSegmentLength);
			PcmUpdate(pSoundBuf, nSegmentLength);
		}
	}

	for (i = 0; i < 2; i++) {
		SekOpen(i);
		SekSetIRQLine(4, SEK_IRQSTATUS_AUTO);
		SekClose();
	}	
	
	if (pBurnDraw) {
		if (!Shangon) {
			OutrunRender();
		} else {
			ShangonRender();
		}
	}

	return 0;
}

int XBoardFrame()
{
	int nInterleave = 64, i;

	if (System16Reset) System16DoReset();

	if (System16Gun) {
		System16GunMakeInputs();
	} else {
		System16MakeInputs();
	}
	
	nCyclesTotal[0] = (50000000 / 4) / 60;
	nCyclesTotal[1] = (50000000 / 4) / 60;
	nCyclesTotal[2] = (16000000 / 4) / 60;
	nSystem16CyclesDone[0] = nSystem16CyclesDone[1] = nSystem16CyclesDone[2] = 0;

	int nSoundBufferPos = 0;
	
	SekNewFrame();

	for (i = 0; i < nInterleave; i++) {
		int nCurrentCPU, nNext;

		// Run 68000 #1
		nCurrentCPU = 0;
		SekOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nSystem16CyclesDone[nCurrentCPU] += SekRun(nCyclesSegment);
		if (i == 15 || i == 30 || i == 45 || i == 60) SekSetIRQLine(2, SEK_IRQSTATUS_AUTO);
		if (i == 63) SekSetIRQLine(4, SEK_IRQSTATUS_AUTO);
		SekClose();
		
		// Run 68000 #2
		nCurrentCPU = 1;
		SekOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nCyclesSegment = SekRun(nCyclesSegment);
		nSystem16CyclesDone[nCurrentCPU] += nCyclesSegment;
		if (i == 63) SekSetIRQLine(4, SEK_IRQSTATUS_AUTO);
		SekClose();

		// Run Z80
		nCurrentCPU = 2;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nCyclesSegment = ZetRun(nCyclesSegment);
		nSystem16CyclesDone[nCurrentCPU] += nCyclesSegment;

		if (pBurnSoundOut) {
			int nSegmentLength = nBurnSoundLen / nInterleave;
			short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);

			BurnYM2151Render(pSoundBuf, nSegmentLength);
			PcmUpdate(pSoundBuf, nSegmentLength);
			nSoundBufferPos += nSegmentLength;
		}
	}

	// Make sure the buffer is entirely filled.
	if (pBurnSoundOut) {
		int nSegmentLength = nBurnSoundLen - nSoundBufferPos;
		short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);

		if (nSegmentLength) {
			BurnYM2151Render(pSoundBuf, nSegmentLength);
			PcmUpdate(pSoundBuf, nSegmentLength);
		}
	}

	if (pBurnDraw) {
		XBoardRender();
	}

	return 0;
}

int YBoardFrame()
{
	int nInterleave = 224, i;

	if (System16Reset) System16DoReset();
	
	if (System16HasGears) {
		PdriftMakeInputs();
	} else {
		if (System16Gun) {
			System16GunMakeInputs();
		} else {
			System16MakeInputs();
		}
	}

	nCyclesTotal[0] = (50000000 / 4) / 60;
	nCyclesTotal[1] = (50000000 / 4) / 60;
	nCyclesTotal[2] = (50000000 / 4) / 60;
	nCyclesTotal[3] = (16000000 / 4) / 60;
	nSystem16CyclesDone[0] = nSystem16CyclesDone[1] = nSystem16CyclesDone[2] = nSystem16CyclesDone[3] = 0;

	int nSoundBufferPos = 0;
	
	SekNewFrame();

	for (i = 0; i < nInterleave; i++) {
		int nCurrentCPU, nNext;
		
		// Run 68000 #1
		nCurrentCPU = 0;
		SekOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nSystem16CyclesDone[nCurrentCPU] += SekRun(nCyclesSegment);
		if (i == YBoardIrq2Scanline) SekSetIRQLine(2, SEK_IRQSTATUS_AUTO);
		SekClose();
		
		// Run 68000 #2
		nCurrentCPU = 1;
		SekOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nCyclesSegment = SekRun(nCyclesSegment);
		nSystem16CyclesDone[nCurrentCPU] += nCyclesSegment;
		if (i == YBoardIrq2Scanline) SekSetIRQLine(2, SEK_IRQSTATUS_AUTO);
		SekClose();
		
		// Run 68000 #3
		nCurrentCPU = 2;
		SekOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nCyclesSegment = SekRun(nCyclesSegment);
		nSystem16CyclesDone[nCurrentCPU] += nCyclesSegment;
		if (i == YBoardIrq2Scanline) SekSetIRQLine(2, SEK_IRQSTATUS_AUTO);
		SekClose();

		// Run Z80
		nCurrentCPU = 3;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nSystem16CyclesDone[nCurrentCPU];
		nCyclesSegment = ZetRun(nCyclesSegment);
		nSystem16CyclesDone[nCurrentCPU] += nCyclesSegment;

		if (pBurnSoundOut) {
			int nSegmentLength = nBurnSoundLen / nInterleave;
			short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);

			BurnYM2151Render(pSoundBuf, nSegmentLength);
			PcmUpdate(pSoundBuf, nSegmentLength);
			nSoundBufferPos += nSegmentLength;
		}
	}

	// Make sure the buffer is entirely filled.
	if (pBurnSoundOut) {
		int nSegmentLength = nBurnSoundLen - nSoundBufferPos;
		short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);

		if (nSegmentLength) {
			BurnYM2151Render(pSoundBuf, nSegmentLength);
			PcmUpdate(pSoundBuf, nSegmentLength);
		}
	}
	
	for (i = 0; i < 3; i++) {
		SekOpen(i);
		SekSetIRQLine(4, SEK_IRQSTATUS_AUTO);
		SekClose();
	}

	if (pBurnDraw) {
		YBoardRender();
	}

	return 0;
}

/*====================================================
Driver Scan
====================================================*/

int System16Scan(int nAction,int *pnMin)
{
	struct BurnArea ba;

	if (pnMin != NULL) {					// Return minimum compatible version
		*pnMin =  0x029660;
	}

	if (nAction & ACB_NVRAM) {
		if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEMX || (BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEMY) {
			if (System16BackupRamSize) {
				memset(&ba, 0, sizeof(ba));
				ba.Data = System16BackupRam;
				ba.nLen = System16BackupRamSize;
				ba.szName = "Backup Ram 1";
				BurnAcb(&ba);
			}
		
			if (System16BackupRam2Size) {
				memset(&ba, 0, sizeof(ba));
				ba.Data = System16BackupRam2;
				ba.nLen = System16BackupRam2Size;
				ba.szName = "Backup Ram 2";
				BurnAcb(&ba);
			}
		}
		
		if ((BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_OUTRUN || (BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEM16B || (BurnDrvGetHardwareCode() & HARDWARE_PUBLIC_MASK) == HARDWARE_SEGA_SYSTEM16A) {
			memset(&ba, 0, sizeof(ba));
			ba.Data = System16Ram;
			ba.nLen = System16RamSize;
			ba.szName = "Work Ram";
			BurnAcb(&ba);
		}
	}

	if (nAction & ACB_MEMORY_RAM) {								// Scan all memory, devices & variables
		memset(&ba, 0, sizeof(ba));
    		ba.Data	  = RamStart;
		ba.nLen	  = RamEnd-RamStart;
		ba.szName = "All Ram";
		BurnAcb(&ba);
	}

	if (nAction & ACB_DRIVER_DATA) {
		SekScan(nAction);					// Scan 68000
		ZetScan(nAction);					// Scan Z80
		ppi8255_scan();

		if (BurnDrvGetHardwareCode() & HARDWARE_SEGA_YM2203) {
			BurnYM2203Scan(nAction, pnMin);
		} else {
			BurnYM2151Scan(nAction);
		}

		// Scan critical driver variables
		SCAN_VAR(System16SoundLatch);
		SCAN_VAR(System16Input);
		SCAN_VAR(System16Dip);
		SCAN_VAR(System16VideoEnable);
		SCAN_VAR(System16ScreenFlip);
		SCAN_VAR(System16ScrollX);
		SCAN_VAR(System16ScrollY);
		SCAN_VAR(System16ColScroll);
		SCAN_VAR(System16RowScroll);
		SCAN_VAR(System16SpriteBanks);
		SCAN_VAR(System16TileBanks);
		SCAN_VAR(System16Page);
		SCAN_VAR(System16AnalogSelect);
		SCAN_VAR(System16LastGear);
		SCAN_VAR(nSystem16CyclesDone);
		SCAN_VAR(nCyclesSegment);
		SCAN_VAR(System16RoadControl);
		SCAN_VAR(System16Gun1X);
		SCAN_VAR(System16Gun1Y);
		SCAN_VAR(System16Gun2X);
		SCAN_VAR(System16Gun2Y);
		SCAN_VAR(multiply);
		SCAN_VAR(divide);
		SCAN_VAR(compare_timer);
	}

	return 0;
}
