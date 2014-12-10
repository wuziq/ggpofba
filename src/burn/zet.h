// Z80 (Zed Eight-Ty) Interface
#define EMU_DOZE					// Use Dave's 'Doze' Assembler Z80 emulator

#ifdef EMU_DOZE
 #include "doze.h"
#endif

int ZetInit(int nCount);
void ZetExit();
void ZetNewFrame();
int ZetOpen(int nCPU);
void ZetClose();
int ZetMemCallback(int nStart,int nEnd,int nMode);
int ZetMemEnd();
int ZetMapArea(int nStart, int nEnd, int nMode, unsigned char *Mem);
int ZetMapArea(int nStart, int nEnd, int nMode, unsigned char *Mem01, unsigned char *Mem02);
int ZetReset();
int ZetPc(int n);
int ZetScan(int nAction);

#define ZET_IRQSTATUS_NONE DOZE_IRQSTATUS_NONE
#define ZET_IRQSTATUS_AUTO DOZE_IRQSTATUS_AUTO
#define ZET_IRQSTATUS_ACK  DOZE_IRQSTATUS_ACK

inline static void ZetSetIRQLine(const int line, const int status)
{
#ifdef EMU_DOZE
	Doze.nInterruptLatch = line | status;
#endif
}

#define ZetRaiseIrq(n) ZetSetIRQLine(n, ZET_IRQSTATUS_AUTO)
#define ZetLowerIrq() ZetSetIRQLine(0, ZET_IRQSTATUS_NONE)

inline static int ZetNmi()
{
#ifdef EMU_DOZE
	int nCycles = DozeNmi();
#else
	// Taking an NMI requires 12 cycles
	int nCycles = 12
#endif

	Doze.nCyclesTotal += nCycles;

	return nCycles;
}

int ZetRun(int nCycles);
void ZetRunEnd();

inline static int ZetIdle(int nCycles)
{
#ifdef EMU_DOZE
	Doze.nCyclesTotal += nCycles;
#endif

	return nCycles;
}

inline static int ZetSegmentCycles()
{
#ifdef EMU_DOZE
	return Doze.nCyclesSegment - Doze.nCyclesLeft;
#else
	return 0;
#endif
}

inline static int ZetTotalCycles()
{
#ifdef EMU_DOZE
	return Doze.nCyclesTotal - Doze.nCyclesLeft;
#else
	return 0;
#endif
}

void ZetSetReadHandler(unsigned char (__fastcall *pHandler)(unsigned short));
void ZetSetWriteHandler(void (__fastcall *pHandler)(unsigned short, unsigned char));
void ZetSetInHandler(unsigned char (__fastcall *pHandler)(unsigned short));
void ZetSetOutHandler(void (__fastcall *pHandler)(unsigned short, unsigned char));
