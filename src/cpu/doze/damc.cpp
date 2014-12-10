// Doze - Dave's optimized Z80 emulator
// Code Maker - CB opcodes
#include "dam.h"

int DamcRotate(unsigned int op)
{
  int t=4,a=0,r=0;
  unsigned int Ext=0; // Extend code (00, dd or fd)
  static char Opco[8][4]={"rol","ror","rcl","rcr","sal","sar","sal","shr"};

  Ext=op>>8; if ((Ext&0xff)==0xcb) Ext=op>>16; // Get dd/fd extend code
  a=(op>>3)&7; r=op&7;

  DamOpStart(op);
  if (Ext)
  {
    // Get IX/IY offset (it's 2 bytes back because of the FD CB nn C6 opcode format)
    DamIxIyOffset(-2);
    t+=4;
  }
  if (Ext || r==6)
  {
    DamGetHL(Ext);
    t+=7;
  }
  DamGet8("dl",r,Ext);

  ot("\n");
  ot("  sahf\n");
  ot("  %s dl,1\n",Opco[a]);
  ot("  setc dh     ; ---- ---C\n");
  if (op>>8)
  {
    // One of the CB opcodes
    ot("  test dl,dl\n");
    ot("  lahf\n");
    ot("  and ah,0xc4 ; SZ-- -P--\n");
    ot("  or  ah,dh   ; SZ-- -P-C\n");
    ot("\n");
  }
  else
  {
    // One of the normal rotates
    ot("  and ah,0xc4 ; ..00 0.00\n");
    ot("  or  ah,dh   ; ..00 0.0C\n");
    ot("\n");
  }

  if (Ext || r==6) DamPut8("dl",6,Ext); // Put to memory
  if (r!=6) DamPut8("dl",r,0); // Put to register
  // (both of the above happen in the undocumented opcodes)
  DamOpDone(t,0);
  return op;
}

static int DamcBit(unsigned int op)
{
  int b=0,r=0,t=4;
  unsigned int Ext=0; // Extend code (00, dd or fd)

  Ext=op>>16; b=(op>>3)&7; r=op&7;

  DamOpStart(op);

  if (Ext)
  {
    // Get IX/IY offset (it's 2 bytes back because of the FD CB nn C6 opcode format)
    DamIxIyOffset(-2);
    t+=8;
  }
  if (Ext || r==6)
  {
    DamGetHL(Ext);
    t+=4;
  }

  DamGet8("dl",r,Ext);
  ot("  mov dh,ah\n");
  ot("  and dl,0x%.2x\n",1<<b);
  ot("  lahf\n");
  ot("  and dh,0x01 ; Preserve ---- ---C\n");
  ot("  and ah,0xc4 ;          SZ-- -P--\n");
  ot("  or  ah,dh   ;          SZ-- -P0C\n");
  ot("  or  ah,0x10 ;          SZ-1 -P0C\n");
  DamOpDone(t,0);
  return op;
}

static int DamcSet(unsigned int op)
{
  int b=0,r=0,t=4,s=0;
  unsigned int Ext=0; // Extend code (00, dd or fd)
  char *Targ="";

  Ext=op>>16; b=(op>>3)&7; r=op&7; s=(op>>6)&1;

  DamOpStart(op);

  if (Ext)
  {
    // Get IX/IY offset (it's 2 bytes back because of the FD CB nn C6 opcode format)
    DamIxIyOffset(-2);
    t+=4;
  }
  if (Ext || r==6)
  {
    DamGetHL(Ext);
    t+=7;
  }

  if (Ext || r==6)
  {
    // Get to dl, then change it
    DamGet8("dl",6,Ext);
    Targ="dl";
  }
  else
  {
    // Do it direct
    Targ=DamLoc8(r,Ext);
  }

  if (s) ot("  or  %s,0x%.2x\n",Targ,1<<b);
  else   ot("  and %s,0x%.2x\n",Targ,0xff^(1<<b));

  if (Ext || r==6)
  {
    DamPut8("dl",6,Ext); // Put to memory
    if (r!=6) DamPut8("dl",r,0); // (undocumented opcodes also put to register)
  }

  DamOpDone(t,0);
  return op;
}

int DamcOpCb(unsigned int op)
{
  if ((op&0xc0)==0x00) return DamcRotate(op);
  if ((op&0xc0)==0x40) return DamcBit(op);
  if ((op&0x80)==0x80) return DamcSet(op);
  return 0x00; // nop
}
