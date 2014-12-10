#include "tiles_generic.h"
#include "burn_ym2151.h"
#include "burn_ym2203.h"
#include "bitswap.h"

#define SYS16_ROM_PROG		0x00001
#define SYS16_ROM_TILES		0x00002
#define SYS16_ROM_SPRITES	0x00004
#define SYS16_ROM_Z80PROG	0x00008
#define SYS16_ROM_KEY		0x00010
#define SYS16_ROM_7751PROG	0x00020
#define SYS16_ROM_7751DATA	0x00040
#define SYS16_ROM_UPD7759DATA	0x00080
#define SYS16_ROM_PROG2		0x00100
#define SYS16_ROM_ROAD		0x00200
#define SYS16_ROM_PCMDATA	0x00400
#define SYS16_ROM_Z80PROG2	0x00800
#define SYS16_ROM_Z80PROG3	0x01000
#define SYS16_ROM_Z80PROG4	0x02000
#define SYS16_ROM_PCM2DATA	0x04000
#define SYS16_ROM_PROM 		0x08000
#define SYS16_ROM_PROG3		0x10000
#define SYS16_ROM_SPRITES2	0x20000

// sys16_run.cpp
extern unsigned char  System16InputPort0[8];
extern unsigned char  System16InputPort1[8];
extern unsigned char  System16InputPort2[8];
extern unsigned char  System16InputPort3[8];
extern unsigned char  System16InputPort4[8];
extern unsigned char  System16InputPort5[8];
extern unsigned char  System16InputPort6[8];
extern unsigned char  System16Gear;
extern int            System16AnalogPort0;
extern int            System16AnalogPort1;
extern int            System16AnalogPort2;
extern int            System16AnalogPort3;
extern int            System16AnalogSelect;
extern unsigned char  System16Dip[3];
extern unsigned char  System16Input[7];
extern unsigned char  System16Reset;
extern unsigned char *System16Rom;
extern unsigned char *System16Code;
extern unsigned char *System16Rom2;
extern unsigned char *System16Z80Rom;
extern unsigned char *System16PCMData;
extern unsigned char *System16Prom;
extern unsigned char *System16Key;
extern unsigned char *System16Ram;
extern unsigned char *System16ExtraRam;
extern unsigned char *System16TempGfx;
extern unsigned char *System16TileRam;
extern unsigned char *System16TextRam;
extern unsigned char *System16TextRam;
extern unsigned char *System16SpriteRam;
extern unsigned char *System16SpriteRamBuff;
extern unsigned char *System16SpriteRam2;
extern unsigned char *System16RotateRam;
extern unsigned char *System16RotateRamBuff;
extern unsigned char *System16PaletteRam;
extern unsigned char *System16RoadRam;
extern unsigned char *System16RoadRamBuff;
extern unsigned int  *System16Palette;
extern unsigned char *System16Tiles;
extern unsigned char *System16Sprites;
extern unsigned char *System16Sprites2;
extern unsigned char *System16Roads;
extern unsigned int System16NumTiles;
extern unsigned int System16RomSize;
extern unsigned int System16Rom2Size;
extern unsigned int System16SpriteRomSize;
extern unsigned int System16Sprite2RomSize;
extern unsigned int System16RoadRomSize;
extern unsigned int System16Z80RomSize;
extern unsigned int System16PCMDataSize;
extern unsigned int System16SpriteRamSize;
extern unsigned int System16SpriteRam2Size;
extern unsigned int System16RotateRamSize;

extern unsigned char System16VideoControl;
extern int System16SoundLatch;
extern bool System16BTileAlt;
extern bool Shangon;
extern bool Hangon;

extern int YBoardIrq2Scanline;

extern bool System16HasGears;

extern bool System16Gun;
extern int System16Gun1X, System16Gun1Y;
extern int System16Gun2X, System16Gun2Y;

extern int nSystem16CyclesDone[4]; 
extern unsigned int System16ClockSpeed;

typedef void (*Sim8751)();
extern Sim8751 Simulate8751;

typedef void (*System16Map68K)();
extern System16Map68K System16Map68KDo;

typedef int (*System16CustomLoadRom)();
extern System16CustomLoadRom System16CustomLoadRomDo;

typedef int (*System16CustomDecryptOpCode)();
extern System16CustomDecryptOpCode System16CustomDecryptOpCodeDo;

typedef unsigned char (*System16ProcessAnalogControls)(UINT16 value);
extern System16ProcessAnalogControls System16ProcessAnalogControlsDo;

typedef void (*System16MakeAnalogInputs)();
extern System16MakeAnalogInputs System16MakeAnalogInputsDo;

int CustomLoadRom20000();
int CustomLoadRom40000();

UINT16 System16MultiplyChipRead(int which, int offset);
void System16MultiplyChipWrite(int which, int offset, UINT16 data);
UINT16 System16CompareTimerChipRead(int which, int offset);
void System16CompareTimerChipWrite(int which, int offset, UINT16 data);
UINT16 System16DivideChipRead(int which, int offset);
void System16DivideChipWrite(int which, int offset, UINT16 data);

int System16Init();
int System16Exit();
int System16AFrame();
int System16BFrame();
int HangonFrame();
int HangonYM2203Frame();
int OutrunFrame();
int XBoardFrame();
int YBoardFrame();
int System16Scan(int nAction,int *pnMin);

// d_sys16a.cpp
void System16APPI0WritePortA(UINT8 data);
void System16APPI0WritePortB(UINT8 data);
void System16APPI0WritePortC(UINT8 data);
extern unsigned short __fastcall System16AReadWord(unsigned int a);
extern unsigned char __fastcall System16AReadByte(unsigned int a);
void __fastcall System16AWriteWord(unsigned int a, unsigned short d);
void __fastcall System16AWriteByte(unsigned int a, unsigned char d);

// d_sys16b.cpp
extern unsigned short __fastcall System16BReadWord(unsigned int a);
extern unsigned char __fastcall System16BReadByte(unsigned int a);
void __fastcall System16BWriteWord(unsigned int a, unsigned short d);
void __fastcall System16BWriteByte(unsigned int a, unsigned char d);

// d_hangon.cpp
void HangonPPI0WritePortA(UINT8 data);
void HangonPPI0WritePortB(UINT8 data);
void HangonPPI0WritePortC(UINT8 data);
UINT8 HangonPPI1ReadPortC();
void HangonPPI1WritePortA(UINT8 data);
extern unsigned short __fastcall HangonReadWord(unsigned int a);
extern unsigned char __fastcall HangonReadByte(unsigned int a);
void __fastcall HangonWriteWord(unsigned int a, unsigned short d);
void __fastcall HangonWriteByte(unsigned int a, unsigned char d);

// d_outrun.cpp
void OutrunPPI0WritePortC(UINT8 data);
extern unsigned short __fastcall OutrunReadWord(unsigned int a);
extern unsigned char __fastcall OutrunReadByte(unsigned int a);
void __fastcall OutrunWriteWord(unsigned int a, unsigned short d);
void __fastcall OutrunWriteByte(unsigned int a, unsigned char d);
extern unsigned short __fastcall Outrun2ReadWord(unsigned int a);
extern unsigned char __fastcall Outrun2ReadByte(unsigned int a);
void __fastcall Outrun2WriteWord(unsigned int a, unsigned short d);
void __fastcall Outrun2WriteByte(unsigned int a, unsigned char d);

// d_xbrd.cpp
extern unsigned short __fastcall XBoardReadWord(unsigned int a);
extern unsigned char __fastcall XBoardReadByte(unsigned int a);
void __fastcall XBoardWriteWord(unsigned int a, unsigned short d);
void __fastcall XBoardWriteByte(unsigned int a, unsigned char d);
extern unsigned short __fastcall XBoard2ReadWord(unsigned int a);
extern unsigned char __fastcall XBoard2ReadByte(unsigned int a);
void __fastcall XBoard2WriteWord(unsigned int a, unsigned short d);
void __fastcall XBoard2WriteByte(unsigned int a, unsigned char d);

// d_ybrd.cpp
extern unsigned short __fastcall YBoardReadWord(unsigned int a);
extern unsigned char __fastcall YBoardReadByte(unsigned int a);
void __fastcall YBoardWriteWord(unsigned int a, unsigned short d);
void __fastcall YBoardWriteByte(unsigned int a, unsigned char d);
extern unsigned short __fastcall YBoard2ReadWord(unsigned int a);
extern unsigned char __fastcall YBoard2ReadByte(unsigned int a);
void __fastcall YBoard2WriteWord(unsigned int a, unsigned short d);
void __fastcall YBoard2WriteByte(unsigned int a, unsigned char d);
extern unsigned short __fastcall YBoard3ReadWord(unsigned int a);
extern unsigned char __fastcall YBoard3ReadByte(unsigned int a);
void __fastcall YBoard3WriteWord(unsigned int a, unsigned short d);
void __fastcall YBoard3WriteByte(unsigned int a, unsigned char d);

// sys16_gfx.cpp
extern int System16VideoEnable;
extern int System16ScreenFlip;
extern int System16SpriteShadow;
extern int System16SpriteBanks[16];
extern int System16TileBanks[2];
extern int System16Page[4];
extern int System16ScrollX[4];
extern int System16ScrollY[4];
extern int System16ColScroll;
extern int System16RowScroll;
extern int System16RoadControl;
extern int System16RoadColorOffset1;
extern int System16RoadColorOffset2;
extern int System16RoadColorOffset3;
extern int System16RoadXOffset;
extern int System16RoadPriority;
extern int System16PaletteEntries;
extern int System16TilemapColorOffset;

extern unsigned short *pTempDraw;

void System16Decode8x8Tiles(unsigned char *pTile, int Num, int offs1, int offs2, int offs3);
void OutrunDecodeRoad();
void HangonDecodeRoad();
void System16ARender();
void System16BRender();
void System16BAltRender();
void HangonRender();
void HangonAltRender();
void OutrunRender();
void ShangonRender();
void XBoardRender();
void YBoardRender();

// fd1089.cpp
typedef void (*FD1089Decrypt)();
extern FD1089Decrypt FD1089_Decrypt;

void fd1089_decrypt_alexkidd(void);
void fd1089_decrypt_0013A(void);
void fd1089_decrypt_0018(void);
void fd1089_decrypt_0022(void);
void fd1089_decrypt_0024(void);
void fd1089_decrypt_0027(void);
void fd1089_decrypt_0028(void);
void fd1089_decrypt_0033(void);
void fd1089_decrypt_0034(void);
void fd1089_decrypt_0167(void);
void fd1089_decrypt_0168(void);
void fd1089_decrypt_5021(void);

// mc8123.cpp
void mc8123_decrypt_rom(int cpunum, const UINT8* key, int banknum, int numbanks);

// sys16_fd1094.cpp
void fd1094_driver_init();
void fd1094_machine_init();

// sys16_pcm.cpp
unsigned char PcmRead(unsigned short a);
void PcmWrite(unsigned short a,unsigned char d);
int PcmInit();
int PcmExit();
int PcmUpdate(short *Dest,int Len);
extern int (*PcmGetBank) (int Reg86);
extern int PcmRate;
extern unsigned char *PcmRom;
extern int PcmBankCount;
extern int PcmBankSize;

// sys16_ppi.cpp
typedef UINT8 (*PPIPortRead)();
typedef void (*PPIPortWrite)(UINT8 data);
extern PPIPortRead PPI0PortReadA;
extern PPIPortRead PPI0PortReadB;
extern PPIPortRead PPI0PortReadC;
extern PPIPortWrite PPI0PortWriteA;
extern PPIPortWrite PPI0PortWriteB;
extern PPIPortWrite PPI0PortWriteC;
extern PPIPortRead PPI1PortReadA;
extern PPIPortRead PPI1PortReadB;
extern PPIPortRead PPI1PortReadC;
extern PPIPortWrite PPI1PortWriteA;
extern PPIPortWrite PPI1PortWriteB;
extern PPIPortWrite PPI1PortWriteC;

void ppi8255_init(int num);
void ppi8255_exit();
void ppi8255_scan();
UINT8 ppi8255_r(int which, int offset);
void ppi8255_w(int which, int offset, UINT8 data);
void ppi8255_set_portC( int which, UINT8 data );
