#include "sys16.h"
// Sega PCM chip emulator

#define CHAN_COUNT (16) // must be a power of 2
#define FRAC_SHIFT (14) // accuracy of render

int PcmRate=22050; // sample rate to render at
unsigned char *PcmRom=NULL; // Pointer to the Pcm banks
int PcmBankCount=0; // Count of the number of banks
int PcmBankSize=0; // Bank length is 1<<PcmBankSize bytes
static int PcmSpeed=15700;
static int IncVal=0; // Amount to increment ChanPos each sample (* Reg[co+7])

static unsigned char Reg[0x100];
static int ChanPos[CHAN_COUNT]; // Position in the sample <<FRAC_SHIFT
static unsigned char ChanBank[CHAN_COUNT];

#define SET_START { ChanPos[c]=((Reg[co+5]<<8)|Reg[co+4])<<FRAC_SHIFT; }

int PcmInit()
{
  memset(Reg,0,sizeof(Reg));
  memset(&ChanPos,0,sizeof(ChanPos));
  memset(&ChanBank,0,sizeof(ChanBank));
  
  if (BurnDrvGetHardwareCode() & HARDWARE_SEGA_YM2203) {
  	PcmSpeed *= 2;
  }

  if (PcmRate>0)
  {
    // Make the ChanPos increment value
    IncVal=(PcmSpeed<<FRAC_SHIFT)/PcmRate;
  }
  return 0;
}

int PcmExit()
{
  IncVal=0;
  PcmSpeed = 15700;
  return 0;
}

int PcmScan()
{
  SCAN_VAR(Reg);
  SCAN_VAR(ChanPos);
  SCAN_VAR(ChanBank);
  return 0;
}

int (*PcmGetBank) (int Reg86)=NULL;

// pcm update for one channel
static int ChannelUpdate(short *Dest,int Len,int c)
{
  int co;
  int StopAt=0;
  unsigned char *PcmBank=NULL;
  short *pd=NULL,*pEnd=NULL;
  c&=15; co=c<<3;

 // channel has reached the end/overflowed - stop or loop
#define CHECK_END \
  if (ChanPos[c] >= StopAt) { if (Reg[co+0x86]&2) Reg[co+0x86]|=1; else SET_START  }

#define RET_IF_STOPPED \
  if (Reg[co+0x86]&1) { ChanPos[c]=0; return 0; }

  RET_IF_STOPPED // channel is stopped

  StopAt=Reg[co+6]<<8; StopAt&=(1<<PcmBankSize)-1; // find stop position but make sure clipped
  StopAt<<=FRAC_SHIFT; // convert to fractional value

  CHECK_END  RET_IF_STOPPED

  PcmBank=PcmRom+ChanBank[c]*(1<<PcmBankSize);
  
  if (Len<0) return 1;
  pd=Dest; pEnd=pd+(Len<<1); // make pointers to the start and end of the area to render
  do
  {
    int p,sl,sr,l,r;
    p=ChanPos[c]>>FRAC_SHIFT; // Find the current sample position

    sl=PcmBank[p]-0x80; // Get the sample
    sl*=3; sl>>=1;
    sr=sl;
    
    sl*=Reg[co+2]&0x3f;
    sr*=Reg[co+3]&0x3f;

    // Add to the sound currently in the buffer
    l=pd[0]; r=pd[1];
    l+=sl; r+=sr;
#define CLIP(x) if (x<-0x8000) x=-0x8000;  if (x>0x7fff) x=0x7fff;
    CLIP(l) CLIP(r)
    pd[0]=(short)l; pd[1]=(short)r;
    pd+=2;

    ChanPos[c]+=IncVal*Reg[co+7]/128; // increment sample position based on pitch
    CHECK_END  RET_IF_STOPPED // Quit if we reached the end of the sample
  }
  while (pd<pEnd);

  return 0;
}

int PcmUpdate(short *Dest,int Len) // Add Len*2 16-bit samples (stereo interleved) into Dest
{
  int i=0;
  if (PcmRom==NULL) return 1;

  for (i=0;i<CHAN_COUNT;i++) ChannelUpdate(Dest,Len,i);
  return 0;
}

unsigned char PcmRead(unsigned short a)
{
  a&=0xff;
  return Reg[a];
}

void PcmWrite(unsigned short a,unsigned char d)
{
  int c=0; // Channel number 0-15
  int f=0; // function
  int co=0; // channel offset

  a&=0xff;

  // a=FCCC CFFF  channel number and function

  c=(a>>3)&15;
#if CHAN_COUNT<16
  c&=CHAN_COUNT-1;
#endif
  co=c<<3;
  f=a&0x87;

  // 86 &2 means don't loop
  // 86 &1 means stopped

  if (f==4 || f==5) SET_START
  if (f==0x86)
  {
    if ((Reg[a]&3)==0) ; // Looping already
    else
    {
      int b=0;
      // Find out the bank of this channel
      if (PcmGetBank!=NULL) b=PcmGetBank(d);
      
      if (b>=PcmBankCount) b=0;
      ChanBank[c]=(unsigned char)b;
      
      SET_START
    }
  }

  Reg[a]=(unsigned char)d; // set register
}
