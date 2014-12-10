// Z80 (Zed Eight-Ty) Interface
#include "burnint.h"

#define QUARK_LOG_MODULE "ZET"
#include "ggpo_log.h"

#ifdef EMU_DOZE
 static DozeContext* ZetCPUContext = NULL;
#endif // EMU_DOZE

static int nOpenedCPU = -1;
static int nCPUCount = 0;

unsigned char __fastcall ZetDummyReadHandler(unsigned short) { return 0; }
void __fastcall ZetDummyWriteHandler(unsigned short, unsigned char) { }
unsigned char __fastcall ZetDummyInHandler(unsigned short) { return 0; }
void __fastcall ZetDummyOutHandler(unsigned short, unsigned char) { }

void ZetSetReadHandler(unsigned char (__fastcall *pHandler)(unsigned short))
{
	Doze.ReadHandler = pHandler;
}

void ZetSetWriteHandler(void (__fastcall *pHandler)(unsigned short, unsigned char))
{
	Doze.WriteHandler = pHandler;
}

void ZetSetInHandler(unsigned char (__fastcall *pHandler)(unsigned short))
{
	Doze.InHandler = pHandler;
}

void ZetSetOutHandler(void (__fastcall *pHandler)(unsigned short, unsigned char))
{
	Doze.OutHandler = pHandler;
}

void ZetNewFrame()
{
	for (int i = 0; i < nCPUCount; i++) {
		ZetCPUContext[i].nCyclesTotal = 0;
	}
	Doze.nCyclesTotal = 0;
}

int ZetInit(int nCount)
{
#ifdef EMU_DOZE
	ZetCPUContext = (DozeContext*)malloc(nCount * sizeof(DozeContext));
	if (ZetCPUContext == NULL) {
		return 1;
	}

	memset(ZetCPUContext, 0, nCount * sizeof(DozeContext));

	for (int i = 0; i < nCount; i++) {
		ZetCPUContext[i].nInterruptLatch = -1;

		ZetCPUContext[i].ReadHandler = ZetDummyReadHandler;
		ZetCPUContext[i].WriteHandler = ZetDummyWriteHandler;
		ZetCPUContext[i].InHandler = ZetDummyInHandler;
		ZetCPUContext[i].OutHandler = ZetDummyOutHandler;

		ZetCPUContext[i].ppMemFetch = (unsigned char**)malloc(0x0100 * sizeof(char*));
		ZetCPUContext[i].ppMemFetchData = (unsigned char**)malloc(0x0100 * sizeof(char*));
		ZetCPUContext[i].ppMemRead = (unsigned char**)malloc(0x0100 * sizeof(char*));
		ZetCPUContext[i].ppMemWrite = (unsigned char**)malloc(0x0100 * sizeof(char*));

		if (ZetCPUContext[i].ppMemFetch == NULL || ZetCPUContext[i].ppMemFetchData == NULL || ZetCPUContext[i].ppMemRead == NULL || ZetCPUContext[i].ppMemWrite == NULL) {
			ZetExit();
			return 1;
		}

		for (int j = 0; j < 0x0100; j++) {
			ZetCPUContext[i].ppMemFetch[j] = NULL;
			ZetCPUContext[i].ppMemFetchData[j] = NULL;
			ZetCPUContext[i].ppMemRead[j] = NULL;
			ZetCPUContext[i].ppMemWrite[j] = NULL;
		}
	}

	ZetOpen(0);

	nCPUCount = nCount;
#endif

	return 0;
}

void ZetClose()
{
#ifdef EMU_DOZE
	ZetCPUContext[nOpenedCPU] = Doze;
#endif
	nOpenedCPU = -1;
}

int ZetOpen(int nCPU)
{
#ifdef EMU_DOZE
	Doze = ZetCPUContext[nCPU];

	nOpenedCPU = nCPU;
#endif

	return 0;
}

int ZetRun(int nCycles)
{
#ifdef EMU_DOZE

	if (nCycles <= 0) {
		return 0;
	}

   QUARK_LOG_VAR(nCycles);
   QUARK_LOG_VAR(Doze.nCyclesTotal);
   QUARK_LOG_VAR(Doze.nCyclesSegment);
   QUARK_LOG_VAR(Doze.nCyclesLeft);

	Doze.nCyclesTotal += nCycles;
	Doze.nCyclesSegment = nCycles;
	Doze.nCyclesLeft = nCycles;

	DozeRun();
	nCycles = Doze.nCyclesSegment - Doze.nCyclesLeft;

   QUARK_LOG_VAR(nCycles);
   QUARK_LOG_VAR(Doze.nCyclesTotal);
   QUARK_LOG_VAR(Doze.nCyclesSegment);
   QUARK_LOG_VAR(Doze.nCyclesLeft);

   Doze.nCyclesTotal -= Doze.nCyclesLeft;
	Doze.nCyclesLeft = 0;
	Doze.nCyclesSegment = 0;

	return nCycles;
#else
	return 0;
#endif
}

void ZetRunAdjust(int nCycles)
{
#ifdef EMU_DOZE
	if (nCycles < 0 && Doze.nCyclesLeft < -nCycles) {
		nCycles = 0;
	}

	Doze.nCyclesTotal += nCycles;
	Doze.nCyclesSegment += nCycles;
	Doze.nCyclesLeft += nCycles;
#endif
}

void ZetRunEnd()
{
#ifdef EMU_DOZE
	Doze.nCyclesTotal -= Doze.nCyclesLeft;
	Doze.nCyclesSegment -= Doze.nCyclesLeft;
	Doze.nCyclesLeft = 0;
#endif
}

// This function will make an area callback ZetRead/ZetWrite
int ZetMemCallback(int nStart, int nEnd, int nMode)
{
#ifdef EMU_DOZE
	nStart >>= 8;
	nEnd += 0xff;
	nEnd >>= 8;

	// Leave the section out of the memory map, so the Doze* callback with be used
	for (int i = nStart; i < nEnd; i++) {
		switch (nMode) {
			case 0:
				Doze.ppMemRead[i] = NULL;
				break;
			case 1:
				Doze.ppMemWrite[i] = NULL;
				break;
			case 2:
				Doze.ppMemFetch[i] = NULL;
				break;
		}
	}

#endif

	return 0;
}

int ZetMemEnd()
{
	return 0;
}

void ZetExit()
{
#ifdef EMU_DOZE
	for (int i = 0; i < nCPUCount; i++) {
		free(ZetCPUContext[i].ppMemFetch);
		ZetCPUContext[i].ppMemFetch = NULL;
		free(ZetCPUContext[i].ppMemFetchData);
		ZetCPUContext[i].ppMemFetchData = NULL;
		free(ZetCPUContext[i].ppMemRead);
		ZetCPUContext[i].ppMemRead = NULL;
		free(ZetCPUContext[i].ppMemWrite);
		ZetCPUContext[i].ppMemWrite = NULL;
	}

	free(ZetCPUContext);
	ZetCPUContext = NULL;
#endif

	nCPUCount = 0;
}


int ZetMapArea(int nStart, int nEnd, int nMode, unsigned char *Mem)
{
#ifdef EMU_DOZE
	int s = nStart >> 8;
	int e = (nEnd + 0xFF) >> 8;

	// Put this section in the memory map, giving the offset from Z80 memory to PC memory
	for (int i = s; i < e; i++) {
		switch (nMode) {
			case 0:
				Doze.ppMemRead[i] = Mem - nStart;
				break;
			case 1:
				Doze.ppMemWrite[i] = Mem - nStart;
				break;
			case 2:
				Doze.ppMemFetch[i] = Mem - nStart;
				Doze.ppMemFetchData[i] = Mem - nStart;
				break;
		}
	}
#endif

	return 0;
}

int ZetMapArea(int nStart, int nEnd, int nMode, unsigned char *Mem01, unsigned char *Mem02)
{
#ifdef EMU_DOZE
	int s = nStart >> 8;
	int e = (nEnd + 0xFF) >> 8;

	if (nMode != 2) {
		return 1;
	}

	// Put this section in the memory map, giving the offset from Z80 memory to PC memory
	for (int i = s; i < e; i++) {
		Doze.ppMemFetch[i] = Mem01 - nStart;
		Doze.ppMemFetchData[i] = Mem02 - nStart;
	}
#endif

	return 0;
}

int ZetReset()
{
#ifdef EMU_DOZE
	DozeReset();
#endif

	return 0;
}

int ZetPc(int n)
{
#ifdef EMU_DOZE
	if (n < 0) {
		return Doze.pc;
	} else {
		return ZetCPUContext[n].pc;
	}
#else
	return 0;
#endif
}

int ZetScan(int nAction)
{
	if ((nAction & ACB_DRIVER_DATA) == 0) {
		return 0;
	}

#ifdef EMU_DOZE
	char szText[] = "Z80 #0";
   char szAreaText[512];

	for (int i = 0; i < nCPUCount; i++) {
		szText[5] = '1' + i;

      int len = ((char *)&ZetCPUContext[i].ppMemFetch) - ((char*)&ZetCPUContext[i]);
		ScanVar(&ZetCPUContext[i], len, szText);
	}
#endif

	return 0;
}
