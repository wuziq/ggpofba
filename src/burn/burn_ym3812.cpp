#include "burnint.h"
#include "burn_sound.h"
#include "burn_ym3812.h"

void (*BurnYM3812Update)(int nSegmentEnd);

static int (*BurnYM3812StreamCallback)(int nSoundRate);

static int nBurnYM3812SoundRate;

static short* pBuffer;
static short* pYM3812Buffer;

static int nYM3812Position;

static unsigned int nSampleSize;
static unsigned int nFractionalPosition;

// ----------------------------------------------------------------------------
// Dummy functions

static void YM3812UpdateDummy(int /* nSegmentEnd */)
{
	return;
}

static int YM3812StreamCallbackDummy(int /* nSoundRate */)
{
	return 0;
}

// ----------------------------------------------------------------------------
// Execute YM3812 for part of a frame

static void YM3812Render(int nSegmentLength)
{
	if (nYM3812Position >= nSegmentLength) {
		return;
	}

//	bprintf(PRINT_NORMAL, _T("    YM3812 render %6i -> %6i\n", nYM3812Position, nSegmentLength));

	nSegmentLength -= nYM3812Position;

	YM3812UpdateOne(0, pBuffer + 0 * 4096 + 4 + nYM3812Position, nSegmentLength);

	nYM3812Position += nSegmentLength;
}

// ----------------------------------------------------------------------------
// Update the sound buffer

static void YM3812UpdateResample(int nSegmentEnd)
{
	short* pSoundBuf = pBurnSoundOut;
	int nSegmentLength = nSegmentEnd;
	int nSamplesNeeded = nSegmentEnd * nBurnYM3812SoundRate / nBurnSoundRate + 1;

//	bprintf(PRINT_NORMAL, _T("    YM3812 update        -> %6i\n", nSegmentLength));

	if (nSamplesNeeded < nYM3812Position) {
		nSamplesNeeded = nYM3812Position;
	}

	if (nSegmentLength > nBurnSoundLen) {
		nSegmentLength = nBurnSoundLen;
	}
	nSegmentLength <<= 1;

	YM3812Render(nSamplesNeeded);

	pYM3812Buffer = pBuffer + 0 * 4096 + 4;

	for (int i = (nFractionalPosition & 0xFFFF0000) >> 15; i < nSegmentLength; i += 2, nFractionalPosition += nSampleSize) {
		pSoundBuf[i + 0] = INTERPOLATE4PS_16BIT((nFractionalPosition >> 4) & 0x0FFF,
												pYM3812Buffer[(nFractionalPosition >> 16) - 3],
												pYM3812Buffer[(nFractionalPosition >> 16) - 2],
												pYM3812Buffer[(nFractionalPosition >> 16) - 1],
												pYM3812Buffer[(nFractionalPosition >> 16) - 0]);
		pSoundBuf[i + 1] = pSoundBuf[i + 0];
	}

	if (nSegmentEnd >= nBurnSoundLen) {
		int nExtraSamples = nSamplesNeeded - (nFractionalPosition >> 16);

//		bprintf(PRINT_NORMAL, _T("   %6i rendered, %i extra, %i <- %i\n"), nSamplesNeeded, nExtraSamples, nExtraSamples, (nFractionalPosition >> 16) + nExtraSamples - 1);

		for (int i = -4; i < nExtraSamples; i++) {
			pYM3812Buffer[i] = pYM3812Buffer[(nFractionalPosition >> 16) + i];
		}

		nFractionalPosition &= 0xFFFF;

		nYM3812Position = nExtraSamples;
	}
}

static void YM3812UpdateNormal(int nSegmentEnd)
{
	short* pSoundBuf = pBurnSoundOut;
	int nSegmentLength = nSegmentEnd;

//	bprintf(PRINT_NORMAL, _T("    YM3812 render %6i -> %6i\n"), nYM3812Position, nSegmentEnd);

	if (nSegmentEnd < nYM3812Position) {
		nSegmentEnd = nYM3812Position;
	}

	if (nSegmentLength > nBurnSoundLen) {
		nSegmentLength = nBurnSoundLen;
	}

	YM3812Render(nSegmentEnd);

	pYM3812Buffer = pBuffer + 4 + 0 * 4096;

	for (int i = nFractionalPosition; i < nSegmentLength; i++) {
		pSoundBuf[(i << 1) + 0] = pYM3812Buffer[i];
		pSoundBuf[(i << 1) + 1] = pYM3812Buffer[i];
	}

	nFractionalPosition = nSegmentLength;

	if (nSegmentEnd >= nBurnSoundLen) {
		int nExtraSamples = nSegmentEnd - nBurnSoundLen;

		for (int i = 0; i < nExtraSamples; i++) {
			pYM3812Buffer[i] = pYM3812Buffer[nBurnSoundLen + i];
		}

		nFractionalPosition = 0;

		nYM3812Position = nExtraSamples;

	}
}

// ----------------------------------------------------------------------------
// Callbacks for YM3812 core

void BurnYM3812UpdateRequest(int, int)
{
	YM3812Render(BurnYM3812StreamCallback(nBurnYM3812SoundRate));
}

// ----------------------------------------------------------------------------
// Initialisation, etc.

void BurnYM3812Reset()
{
	BurnTimerReset();

	YM3812ResetChip(0);
}

void BurnYM3812Exit()
{
	YM3812Shutdown();

	BurnTimerExit();

	free(pBuffer);
}

int BurnYM3812Init(int nClockFrequency, OPL_IRQHANDLER IRQCallback, int (*StreamCallback)(int))
{
	BurnTimerInit(&YM3812TimerOver, NULL);

	if (nBurnSoundRate <= 0) {
		BurnYM3812StreamCallback = YM3812StreamCallbackDummy;

		BurnYM3812Update = YM3812UpdateDummy;

		YM3812Init(1, nClockFrequency, 11025);
		return 0;
	}

	BurnYM3812StreamCallback = StreamCallback;

	if (nFMInterpolation == 3) {
		// Set YM3812 core samplerate to match the hardware
		nBurnYM3812SoundRate = nClockFrequency / 72;
		// Bring YM3812 core samplerate within usable range
		while (nBurnYM3812SoundRate > nBurnSoundRate * 3) {
			nBurnYM3812SoundRate >>= 1;
		}

		BurnYM3812Update = YM3812UpdateResample;

		nSampleSize = (unsigned int)nBurnYM3812SoundRate * (1 << 16) / nBurnSoundRate;
		nFractionalPosition = 0;
	} else {
		nBurnYM3812SoundRate = nBurnSoundRate;

		BurnYM3812Update = YM3812UpdateNormal;
	}

	YM3812Init(1, nClockFrequency, nBurnYM3812SoundRate);
	YM3812SetIRQHandler(0, IRQCallback, 0);
	YM3812SetTimerHandler(0, &BurnOPLTimerCallback, 0);
	YM3812SetUpdateHandler(0, &BurnYM3812UpdateRequest, 0);

	pBuffer = (short*)malloc(4096 * sizeof(short));
	memset(pBuffer, 0, 4096 * sizeof(short));

	nYM3812Position = 0;

	nFractionalPosition = 0;

	return 0;
}

void BurnYM3812Scan(int nAction, int* pnMin)
{
	BurnTimerScan(nAction, pnMin);
}
