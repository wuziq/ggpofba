// Audio Output
#include "burner.h"

int nAudSampleRate = 22050;			// sample rate
int nAudVolume = 10000;				// Sound volume (% * 100)
int nAudSegCount = 6;				// Segs in the pdsbLoop buffer
int nAudSegLen = 0;					// Seg length in samples (calculated from Rate/Fps)
unsigned char bAudOkay = 0;			// True if DSound was initted okay
unsigned char bAudPlaying = 0;		// True if the Loop buffer is playing

int nAudDSPModule = 0;				// DSP module to use: 0 = none, 1 = low-pass filter

short* nAudNextSound = NULL;		// The next sound seg we will add to the sample loop

unsigned int nAudSelect = 0;		// Which audio plugin is selected

#if 1
#if defined (BUILD_WIN32)
	extern struct AudOut AudOutDx;
#elif defined (BUILD_SDL)
	extern struct AudOut AudOutSDL;
#endif

static struct AudOut *pAudOut[]=
{
#if defined (BUILD_WIN32)
	&AudOutDx,
#elif defined (BUILD_SDL)
	&AudOutSDL,
#endif
};
#else
	extern struct AudOut AudOutSDL;
	extern struct AudOut AudOutDx;

static struct AudOut *pAudOut[]=
{
	&AudOutSDL,
	&AudOutDx,
};
#endif

#define AUD_LEN (sizeof(pAudOut)/sizeof(pAudOut[0]))

static InterfaceInfo AudInfo = { NULL, NULL, NULL };

int AudBlankSound()
{
	if (!bAudOkay || nAudSelect >= AUD_LEN) {
		return 1;
	}
	return pAudOut[nAudSelect]->BlankSound();
}

// This function checks the Sound loop, and if necessary gets some more sound
int AudSoundCheck()
{
	if (!bAudOkay || nAudSelect >= AUD_LEN) {
		return 1;
	}
	return pAudOut[nAudSelect]->SoundCheck();
}

int AudSoundInit()
{
	int nRet;

	if (nAudSelect >= AUD_LEN) {
		return 1;
	}

	if ((nRet = pAudOut[nAudSelect]->SoundInit()) == 0) {
		bAudOkay = true;
	}

	return nRet;
}

int AudSetCallback(int (*pCallback)(int))
{
	if (!bAudOkay || nAudSelect >= AUD_LEN) {
		return 1;
	}
	return pAudOut[nAudSelect]->SetCallback(pCallback);
}

int AudSoundPlay()
{
	if (!bAudOkay || nAudSelect >= AUD_LEN) {
		return 1;
	}
	return pAudOut[nAudSelect]->SoundPlay();
}

int AudSoundStop()
{
	if (nAudSelect >= AUD_LEN) {
		return 1;
	}
	return pAudOut[nAudSelect]->SoundStop();
}

int AudSoundExit()
{
	IntInfoFree(&AudInfo);

	if (!bAudOkay || nAudSelect >= AUD_LEN) {
		return 1;
	}
	bAudOkay = false;

	return pAudOut[nAudSelect]->SoundExit();
}

int AudSoundSetVolume()
{
	if (!bAudOkay || nAudSelect >= AUD_LEN) {
		return 1;
	}
	return pAudOut[nAudSelect]->SoundSetVolume();
}

InterfaceInfo* AudGetInfo()
{
	if (IntInfoInit(&AudInfo)) {
		IntInfoFree(&AudInfo);
		return NULL;
	}

	if (bAudOkay) {
		TCHAR szString[MAX_PATH] = _T("");

		AudInfo.pszModuleName = pAudOut[nAudSelect]->szModuleName;

		_sntprintf(szString, MAX_PATH, _T("Playback at %iHz, %i%% volume"), nAudSampleRate, nAudVolume / 100);
		IntInfoAddStringInterface(&AudInfo, szString);

		if (nAudDSPModule) {
			IntInfoAddStringInterface(&AudInfo, _T("Applying low-pass filter"));
		}

	 	if (pAudOut[nAudSelect]->GetPluginSettings) {
			pAudOut[nAudSelect]->GetPluginSettings(&AudInfo);
		}
	} else {
		IntInfoAddStringInterface(&AudInfo, _T("Audio plugin not initialised"));
	}

	return &AudInfo;
}
