#define MAX_MSM5205 (4)  // maximum number of adpcm channels
int MSM5205Init(int nChip, int nSamplerate, float fMaxVolume, bool bAddSignal);
void MSM5205Reset(int nChip);
void MSM5205Exit(int nChip);
int MSM5205Render(int nChip, short* pSoundBuf, int nSegmentLength);
int MSM5205Scan(int nChip, int nAction);
void MSM5205Play(unsigned int nStart, unsigned int nEnd, int channel);

inline static unsigned int adpcmReadStatus()
{
	extern unsigned int nadpcmStatus;
	return nadpcmStatus;
}

extern unsigned char* MSM5205ROM;

extern unsigned char* MSM5205SampleInfo[MAX_MSM5205];
extern unsigned char* MSM5205SampleData[MAX_MSM5205];

