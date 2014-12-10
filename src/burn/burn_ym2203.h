// burn_ym2203.h
#include "driver.h"
extern "C" {
 #include "ay8910.h"
 #include "fm.h"
}
#include "timer.h"

extern "C" void BurnYM2203UpdateRequest();

int BurnYM2203Init(int nClockFrequency, FM_IRQHANDLER IRQCallback, int (*StreamCallback)(int), double (*GetTimeCallback)());
void BurnYM2203Reset();
void BurnYM2203Exit();
extern void (*BurnYM2203Update)(int nSegmentEnd);
void BurnYM2203Scan(int nAction, int* pnMin);

#define BurnYM2203Write(a, n) YM2203Write(0, a, n)
#define BurnYM2203Read(a) YM2203Read(0, a)

