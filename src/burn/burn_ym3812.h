#include "driver.h"
extern "C" {
 #include "fmopl.h"
}
#include "timer.h"

extern "C" void BurnYM3812UpdateRequest();

int BurnYM3812Init(int nClockFrequency, OPL_IRQHANDLER IRQCallback, int (*StreamCallback)(int));
void BurnYM3812Reset();
void BurnYM3812Exit();
extern void (*BurnYM3812Update)(int nSegmentEnd);
void BurnYM3812Scan(int nAction, int* pnMin);

#define BurnYM3812Write(a, n) YM3812Write(0, a, n)
#define BurnYM3812Read(a) YM3812Read(0, a)
