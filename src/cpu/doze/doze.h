//---------------------------------------------------------------------------
// Doze - Dave's optimized Z80 emulator
// Copyright (c) 2001 Dave (www.finalburn.com), all rights reserved.

// You can use, modify and redistribute this code freely as long as you
// don't do so commercially. This copyright notice must remain with the code.
// You must state if your program uses this code.

// Dave
// Homepage: www.finalburn.com
// E-mail:  dave@finalburn.com
// -------------------------------------------------------------------------------------------

// Change log
// 1.001 : Fixed mistake in timing of ini/r/d/outi/r/d  (4+16 cycles should have
//         been 4+12 cycles)
// 1.002 : Implemented seperate fetch mechanisms for opcodes and data (ayeye)
//		   Modified the interface to allow for multiple emulated Z80's
//		   Added support for using the __fastcall calling convention for handlers
// 1.003 : Minor change to the .asm file to prevent problems with a recent (buggy)
//         version of Gnu binutils
// 1.004 : Improved IRQ support
//

// (external) Header

#ifdef __cplusplus
 extern "C" {
#endif

#if !defined (_WIN32)
 #define __cdecl
#endif

#define DOZE_IRQSTATUS_NONE (0x8000)
#define DOZE_IRQSTATUS_AUTO (0x2000)
#define DOZE_IRQSTATUS_ACK  (0x1000)

struct DozeContext {
	// Registers
	unsigned short af,  bc,  de,  hl,  ix, iy, pc, sp;
	unsigned short af2, bc2, de2, hl2, ir;
	unsigned short iff;								  // iff.h = IFF2, iff.l = IFF1
	unsigned char im;

	// Variables
	int nCyclesTotal;
	int nCyclesSegment;
	int nCyclesLeft;
	int nEI;
	int nInterruptLatch;

	// Memory access
	unsigned char** ppMemFetch;
	unsigned char** ppMemFetchData;
	unsigned char** ppMemRead;
	unsigned char** ppMemWrite;

	// Handlers
 #ifdef FASTCALL
	unsigned char (__fastcall *ReadHandler)(unsigned short a);
	void (__fastcall *WriteHandler)(unsigned short a, unsigned char d);
	unsigned char (__fastcall *InHandler)(unsigned short a);
	void (__fastcall *OutHandler)(unsigned short a, unsigned char d);
 #else
	unsigned char (__cdecl *ReadHandler)(unsigned short a);
	void (__cdecl *WriteHandler)(unsigned short a, unsigned char d);
	unsigned char (__cdecl *InHandler)(unsigned short a);
	void (__cdecl *OutHandler)(unsigned short a, unsigned char d);
 #endif
};

// Interface to the assembly code
extern struct DozeContext Doze;

void __cdecl DozeAsmRun();
void __cdecl DozeAsmCall(unsigned short nAddr);
unsigned char __cdecl DozeAsmRead(unsigned short nAddr);

// doze.cpp
extern int nDozeVer;					// Version number of the library
void __cdecl DozeRun();
int __cdecl DozeNmi();
int __cdecl DozeReset();

#ifdef __cplusplus
 } // End of extern "C"
#endif
