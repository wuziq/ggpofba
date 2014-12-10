// Doze - Dave's optimized Z80 emulator
// Code Maker - normal opcodes
#include "dam.h"

int DamaFlags(int bOverflow,char *Bits35)
{
  ot("  ; Get the correct flags ----\n");
  ot("  lahf ; Flag bits -> AH\n");

  if (bOverflow)
  {
    ot("  seto dh ; dh=1 or 0\n");
    ot("  and ah,0xd1 ; SZ-A ---C\n");
    ot("  rol dh,2\n");
    ot("  or ah,dh ; Get overflow flag\n");
  }
  else
    ot("  and ah,0xd5 ; SZ-A -P-C\n");

  ot("  mov dh,%s\n",Bits35);
  ot("  and dh,0x28 ; S-5- 3---\n");
  ot("  or  ah,dh   ; SZ5A 3P-C\n");

  ot("  ; End of get the correct flags ----\n");
  return 1;
}

static int Dama_00xx_x10x(unsigned int op)
{
  //            00dd d10s
  // s -> inc/dec

  // e.g 0000 0100     inc b
  // e.g 0011 0100     inc (hl)

  // If it uses hl, it can be extended with dd and fd
  // If (hl) is extended becomes (ix/iy + offset)

  int d=0,t=4; int Ext=0;
  d=(op>>3)&7; Ext=op>>8;
  if (Ext) { if (d<4 || d==7) return op&0xff; } // No such DD/FD opcode

  DamOpStart(op);

  if (Ext && d==6)
  {
    // Get IX/IY offset
    DamIxIyOffset(0); DamAddPc(1);
    t+=8; // Takes longer with offsett
  }

  if (d==6)
  {
    DamGetHL(Ext); // Get the value of HL/IX/IY
    t+=7; ot ("; Takes more cycles from memory\n");
  }


  ot("  and ah,0x01 ; Keep carry flag\n");

  if (d!=6)
  {
    // Do it direct
    if (op&1) ot("  dec "); else ot("  inc ");
    ot("%s\n",DamLoc8(d,Ext));
    ot("  mov dl,%s\n",DamLoc8(d,Ext));
  }
  else
  {
    // Do it via dl
    DamGet8("dl",d,Ext);
    if (op&1) ot("  dec dl\n"); else ot("  inc dl\n");
    DamPut8("dl",d,Ext);
  }

  ot("  xor dh,dh\n");
  if (op&1) { ot("  or ah,byte [DecFlag+edx]\n"); }
  else      { ot("  or ah,byte [IncFlag+edx]\n"); }

  DamOpDone(t,0);
  return op;
}

static int Dama_00xx_x110(unsigned int op)
{
  //            00dd d110 nn
  // ddd -> b,c,d,e,h,l,(hl),a

  // e.g. 0000 0110 nn    ld b   ,$nn
  // e.g. 0011 0110 nn    ld (hl),$nn

  // If it uses hl, it can be extended with dd and fd
  // If (hl) is extended becomes (ix/iy + signed offset)

  int d=0,t=7;
  d=(op>>3)&7;

  if (op>>8) { if (d<4 || d==7) return op&0xff; } // No such DD/FD opcode

  DamOpStart(op);

  ot("; Load Value 8-bit\n");
  if ((op>>8) && d==6)
  {
    // Get IX/IY offset from PC+0
    DamIxIyOffset(0); DamAddPc(1);
    t+=5;
  }

  DamFetch(0,1); DamAddPc(1); // Get Value

  if (d==6)
  {
    DamGetHL(op>>8); // Get the value of HL/IX/IY
    t+=3; // takes longer to memory
  }

  DamPut8("dl",d,op>>8);

  DamOpDone(t,0);
  return op;
}

static int Dama_001x_x000(unsigned int op)
{
  //            001c c000 nn
  //  cc -> nz,z,nc,c   nn=signed offset

  // e.g 0010 0000 nn   jr nz, next statement+nn

  int c=0; static int Lab=0;
  c=(op>>3)&3;
  if (op>>8) return op&0xff; // Can't be an extended opcode

  DamOpStart(op);

  DamAddPc(1);

  // jr nz
  ot("  sahf ; Get flags so we can test for the condition\n");
       if (c==0) ot("  jz "); else if (c==1) ot("  jnz ");
  else if (c==2) ot("  jc "); else           ot("  jnc ");
  ot("ConditionFalse%d\n",Lab);

  ot("  ; Get Jump offset:\n");
  DamFetch(-1,1);
  ot("  xor dl,0x80\n");
  ot("  xor dh,dh\n");
  ot("  sub dx,0x80\n");
  ot("  add %s,dx\n",DamPc);
  DamOpDone(12,0);

  ot("ConditionFalse%d:\n",Lab++);
  DamOpDone(7,0);
  return op;
}

static int DamaHalt(unsigned int op)
{
  if (op>>8) return op&0xff; // not extended
  ot("  ; 76 - halt\n");
  DamOpStart(op);

  ot("  ; Reduce cycle counter to 1,2,3 or 4\n");
  ot("  dec si ; Stay on halt instruction\n");
  ot("  and %s,3\n",DamCycles);
  ot("  ; todo - add R counter by cycles/4\n");

  DamOpDone(4,0);
  return op;
}

static int Dama_01xx_xxxx(unsigned int op)
{
  int se=0,de=0;
  //            01dd dsss
  // ddd/sss -> b,c,d,e,h,l,(hl),a

  // e.g. 0100 0001     ld b,c
  // e.g. 0100 0110     ld b,(hl)

  // If it uses hl, it can be extended with dd and fd
  // If (hl) is extended becomes (ix/iy + signed offset)

  int s=0,d=0,t=4; int Ext=0;
  s=op&7; d=(op>>3)&7;
  Ext=op>>8;

  if ((op&0xff)==0x76) return DamaHalt(op);
  if (Ext) { if ( (s<4 || s==7) && (d<4 || d==7) ) return op&0xff; } // No such DD/FD opcode

  se=de=Ext; // Copy extension to source and dest

  if (d==6) se=0; // If to   (hl)/(ix)/(iy), source register is not extended
  if (s==6) de=0; // If from (hl)/(ix)/(iy), dest register is not extended

  DamOpStart(op);

  ot("; Load 8-bit\n");

  if (s==6 || d==6)
  {
    if (Ext)
    {
      // Get IX/IY offset
      DamIxIyOffset(0); DamAddPc(1);
      t+=8; // Takes longer with offset
    }

    DamGetHL(Ext); // Get the value of HL/IX/IY
    t+=3; // takes longer to memory
  }

  if (d==s && de==se)
  {
    // Same register (e.g. Op49)
  }
  else
  {
    if (d!=6 && s!=6 && (DamLoc8IsReg(d,de) || DamLoc8IsReg(s,se)) )
    {
      // Can do it direct
      ot("  mov %s,%s\n",DamLoc8(d,de),DamLoc8(s,se));
    }
    else
    {
      // (hl)/(ix)/(iy), register is not extended
      ot("; Copy to dl, then to destination\n");
      DamGet8("dl",s,se); DamPut8("dl",d,de);
    }
  }

  DamOpDone(t,0);
  return op;
}

static int DoArith(int a)
{
  static char Opco[8][4]={"add","adc","sub","sbb","and","xor","or","cmp"};
  char *Bits35="";
  // Do arithmetic on al and dl
  if (a==1 || a==3) { ot("  sahf ; Get the carry flag\n"); }
  else { ot("  xor ah,ah ; Start with blank flags\n"); }

  if (a==7) Bits35="dl"; // bits copied from argument
  else      Bits35="al"; // bits copied from result

  ot("  %s al,dl ; DO ARITHMETIC OPERATION\n",Opco[a]);
  if (a<4 || a==7) DamaFlags(1,Bits35); // Get flags with overflow
  else             DamaFlags(0,Bits35); // Get flags with parity

  if (a==2 || a==3 || a==7)  ot("  or ah,0x02 ; Set bit 1 - last operation was a subtraction\n");
  if (a==4)                  ot("  or ah,0x10 ; Set bit 4 to 1 (AND operation)\n");
  return 0;
}

static int Dama_10xx_xxxx(unsigned int op)
{
  //            10aa addd - Arithmetic
  // ddd -> b,c,d,e,h,l,(hl),a
  // aaa -> add,adc,sub,sbc,and,xor,or,cp

  // e.g. 1000 0000     add a,b
  // e.g. 1000 0110     add a,(hl)
  // e.g. 1010 1000     xor b

  // If it uses hl, it can be extended with dd and fd
  // If (hl) is extended becomes (ix/iy + signed offset)

  int a=0,s=0,t=4; int Ext=0;
  a=(op>>3)&7; s=op&7;
  Ext=op>>8;

  if (Ext) { if (s<4 || s==7) return op&0xff; } // No such DD/FD opcode
  DamOpStart(op);
  ot("  ; Arithmetic\n");

  if (s==6)
  {
    if (Ext)
    {
      // Get IX/IY offset
      DamIxIyOffset(0); DamAddPc(1);
      t+=8; // Takes longer with offset
    }

    DamGetHL(Ext); // Get the value of HL/IX/IY
    t+=3; // takes longer to memory
  }

  DamGet8("dl",s,Ext);
  DoArith(a);
  DamOpDone(t,0);
  return op;
}

static int DamaJumpOnCond(unsigned int c)
{
  // Jump on condition code ccc to Label
  // ccc -> nz,z,nc,c,po (parity=0),pe (parity=1), p (N=0), m (N=1)
  static unsigned char nAnd[4]={0x40,0x01,0x04,0x80}; // Bits to check for
  c&=7;
  ot("  test ah,0x%.2x\n",nAnd[c>>1]);
  if (c&1) ot("  jnz "); else ot("  jz ");
  return 0;
}

static int Dama_11xx_x000(unsigned int op)
{
  //            11cc c000 - Return on condition code

  // e.g. 1100 0000     ret nz

  static int Lab=0; int c=0;
  c=(op>>3)&7;
  if (op>>8) return op&0xff; // Not extended
  DamOpStart(op);
  DamaJumpOnCond(c); ot("DoRet%d\n",Lab);
  DamOpDone(5,0);

  ot("DoRet%d:\n",Lab++);
  ot("  mov di,word [DozeSP]\n");
  ot("  DAM_READ16\n");
  ot("  mov %s,dx\n",DamPc);
  ot("  add word [DozeSP],2\n");
  DamOpDone(11,0);
  return op;
}

static int Dama_11xx_x010(unsigned int op)
{
  //            11cc c010 nn nn - Jump (absolute) on condition code
  // e.g. 1100 0010 nn nn    jp nz,$nnnn

  static int Lab=0; int c=0;
  c=(op>>3)&7;
  if (op>>8) return op&0xff; // Can't be an extended opcode
  DamOpStart(op);
  DamAddPc(2);
  DamaJumpOnCond(c); ot("DoJump%d\n",Lab);
  DamOpDone(10,0);

  ot("DoJump%d:\n",Lab++);
  DamFetch(-2,2);
  ot("  mov %s,dx\n",DamPc);

  DamOpDone(10,0);
  return op;
}

static int Dama_11xx_x100(unsigned int op)
{
  //            11cc c100 nn nn - Call nnnn on condition code
  // e.g. 1100 0100 nn nn    call nz,$nnnn

  static int Lab=0; int c=0;
  c=(op>>3)&7;
  if (op>>8) return op&0xff; // Can't be an extended opcode
  DamOpStart(op);
  DamAddPc(2);
  DamaJumpOnCond(c); ot("DoCall%d\n",Lab);
  DamOpDone(10,0);

  ot("DoCall%d:\n",Lab++);

  ot("  sub word [DozeSP],2\n");
  ot("  mov di,word [DozeSP]\n");
  ot("  mov dx,%s\n",DamPc);
  ot("  DAM_WRITE16\n");

  DamFetch(-2,2);
  ot("  mov %s,dx\n",DamPc);

  DamOpDone(17,0);
  return op;
}

static int Dama_11xx_x110(unsigned int op)
{
  //      11aa a110 nn
  // aaa -> add,adc,sub,sbc,and,xor,or,cp

  // e.g. 1100 0110 nn    add a,$nn
  int a=0,s=0,t=8;
  if (op>>8) return op&0xff;  // Can't be extended

  a=(op>>3)&7; s=op&7;
  DamOpStart(op);
  ot("  ; Arithmetic (Immediate value)\n");

  ot("  ; Get value:\n");
  DamFetch(0,1); DamAddPc(1);
  DoArith(a);
  DamOpDone(t,0);
  return op;
}

static int Dama_11xx_x111(unsigned int op)
{
  //            rst nn
  int nNewPc=0;
  nNewPc=op&0x38;
  if (op>>8) return op&0xff;

  DamOpStart(op);
  ot("  sub word [DozeSP],2\n");
  ot("  mov di,word [DozeSP]\n");
  ot("  mov dx,%s\n",DamPc);
  ot("  DAM_WRITE16\n");
  ot("  mov %s,0x%.2x\n",DamPc,nNewPc);
  DamOpDone(11,0);
  return op;
}

int DamaOp(unsigned int op)
{
  if ((op&0xcf)==0x01) return Dame_00xx_0001(op);
  if ((op&0xc7)==0x03) return Dame_00xx_x011(op);
  if ((op&0xc6)==0x04) return Dama_00xx_x10x(op);
  if ((op&0xc7)==0x06) return Dama_00xx_x110(op);
  if ((op&0xcf)==0x09) return Dame_00xx_1001(op);
  if ((op&0xe7)==0x20) return Dama_001x_x000(op);
  if ((op&0xc0)==0x40) return Dama_01xx_xxxx(op);
  if ((op&0xc0)==0x80) return Dama_10xx_xxxx(op);
  if ((op&0xc7)==0xc0) return Dama_11xx_x000(op);
  if ((op&0xcb)==0xc1) return Dame_11xx_0x01(op);
  if ((op&0xc7)==0xc2) return Dama_11xx_x010(op);
  if ((op&0xc7)==0xc4) return Dama_11xx_x100(op);
  if ((op&0xc7)==0xc6) return Dama_11xx_x110(op);
  if ((op&0xc7)==0xc7) return Dama_11xx_x111(op);

  if ((op&0xe7)==0x07 && (op>>8)==0) return DamcRotate(op); // Simple, unextended rotate
  if ((op&0xf7)==0x22) return DameDirectMem16(op);
  if ((op&0xff)==0xe3) return DameExHL(op);
  return DamoOp(op); // Other opcodes
}
