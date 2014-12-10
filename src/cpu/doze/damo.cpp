// Doze - Dave's optimized Z80 emulator
// Code Maker - other misc. opcodes
#include "dam.h"

int DamoOp(unsigned int op)
{
  if (op==0x00)
  {
    ot("  ; 00 - nop\n");
    DamOpStart(op);
    DamOpDone(4,0);
    return op;
  }

  if (op==0x02)
  {
    DamOpStart(op);
    ot("  ; 02 - ld (bc),a\n");
    ot("  ; Get Save address:\n");
    DamGet16("di",0,0);
    ot("  mov dl,al\n");
    ot("  DAM_WRITE8 ; Save to address\n");
    DamOpDone(7,0);
    return op;
  }

  if (op==0x08)
  {
    DamOpStart(op);
    ot("  ; 08 - ex af,af'\n");
    ot("  rol ax,8\n");
    ot("  mov dx,ax\n");
    ot("  mov ax,word [DozeAF2]\n");
    ot("  mov word [DozeAF2],dx\n");
    ot("  rol ax,8\n");
    DamOpDone(4,0);
    return op;
  }

  if (op==0x0a)
  {
    DamOpStart(op);
    ot("  ; 0a - ld a,(bc)\n");
    ot("  ; Get Load address:\n");
    DamGet16("di",0,0);
    ot("  DAM_READ8 ; Load from address\n");
    ot("  mov al,dl\n");
    DamOpDone(7,0);
    return op;
  }

  if (op==0x10)
  {
    static int Lab=0;
    DamOpStart(op);
    DamAddPc(1);
    ot("  ; 10 nn - djnz +nn\n");

    DamGet8("dl",0,0);
    ot("  dec dl\n");
    ot("  jnz BNotZero%d\n",Lab);
    DamPut8("dl",0,0);
    DamOpDone( 8,0);

    ot("BNotZero%d:\n",Lab++);
    DamPut8("dl",0,0);
    ot("  ; Get Jump offset:\n");
    DamFetch(-1,1);
    ot("  xor dh,dh\n");
    ot("  xor dl,0x80\n");
    ot("  sub dx,0x80\n");
    ot("  add %s,dx\n",DamPc);
    DamOpDone(13,0);
    return op;
  }

  if (op==0x12)
  {
    DamOpStart(op);
    ot("  ; 02 - ld (de),a\n");
    ot("  ; Get Save address:\n");
    DamGet16("di",1,0);
    ot("  mov dl,al\n");
    ot("  DAM_WRITE8 ; Save to address\n");
    DamOpDone(7,0);
    return op;
  }

  if (op==0x18)
  {
    ot("  ; 18 nn - jr +nn\n");
    DamOpStart(op);
    ot("  ; Get Jump offset:\n");
    DamFetch(0,1); DamAddPc(1);
    ot("  xor dh,dh\n");
    ot("  xor dl,0x80\n");
    ot("  sub dx,0x80\n");
    ot("  add %s,dx\n",DamPc);
    DamOpDone(12,0);
    return op;
  }

  if (op==0x1a)
  {
    DamOpStart(op);
    ot("  ; 0a - ld a,(de)\n");
    ot("  ; Get Load address:\n");
    DamGet16("di",1,0);
    ot("  DAM_READ8 ; Load from address\n");
    ot("  mov al,dl\n");
    DamOpDone(7,0);
    return op;
  }

  if (op==0x27)
  {
    DamOpStart(op);
    ot("  ; 27 - daa\n");
    ot("  mov dh,ah\n");
    ot("  ror dh,2   ;H-- ---- ----\n");
    ot("  and dx,0x400\n");
    ot("  and ax,0x3ff\n");
    ot("  or  dx,ax ; HNC nnnn nnnn\n");
    ot("  mov ax,word[DaaTable+edx*2] ; Get flags and value in one go\n");
    DamOpDone(4,0);
    return op;
  }

  if (op==0x2f)
  {
    DamOpStart(op);
    ot("  ; 2f - cpl\n");
    ot("  and ah,0xc5 ; SZ-- -P-C\n");
    ot("  not al\n");
    ot("  or  ah,0x12 ; SZ-H -PNC\n");
    ot("  mov dh,al\n");
    ot("  and dh,0x28\n");
    ot("  or  ah,dh   ; SZ5H 3PNC\n");
    DamOpDone(4,0);
    return op;
  }

  if (op==0x32)
  {
    DamOpStart(op);
    ot("  ; 32 nn nn - ld ($nnnn),a\n");
    ot("  ; Get Save address:\n");
    DamFetch(0,2); DamAddPc(2);
    ot("  mov di,dx\n");
    ot("  mov dl,al\n");
    ot("  DAM_WRITE8 ; Save to address\n");
    DamOpDone(13,0);
    return op;
  }

  if (op==0x37)
  {
    DamOpStart(op);
    ot("  ; 37 - scf - set carry flag\n");
    ot("  and ah,0xc4\n");
    ot("  or  ah,0x01\n");
    DamOpDone(4,0);
    return op;
  }

  if (op==0x3a)
  {
    DamOpStart(op);
    ot("  ; 3a nn nn - ld a,($nnnn)\n");
    ot("  ; Get Load address:\n");
    DamFetch(0,2); DamAddPc(2);
    ot("  mov di,dx\n");
    ot("  DAM_READ8 ; Load from address\n");
    ot("  mov al,dl\n");
    DamOpDone(13,0);
    return op;
  }

  if (op==0x3f)
  {
    DamOpStart(op);
    ot("  ; 3f - ccf - complement carry flag\n");
    ot("  mov dh,ah\n");
    ot("  and ah,0xc5\n");
    ot("  rol dh,4\n");
    ot("  xor ah,0x01\n");
    ot("  and dh,0x10\n");
    ot("  or  ah,dh ; H is last Carry value\n");
    DamOpDone(4,0);
    return op;
  }

  if (op==0xc3)
  {
    DamOpStart(op);
    ot("  ; c3 nn nn - jp $nnnn\n");
    DamFetch(0,2);
    ot("  mov %s,dx\n",DamPc);
    DamOpDone(10,0);
    return op;
  }

  if (op==0xc9)
  {
    DamOpStart(op);
    ot("  ; c9 - ret\n");
    ot("  mov di,word [DozeSP]\n");
    ot("  DAM_READ16\n");
    ot("  mov %s,dx\n",DamPc);
    ot("  add word [DozeSP],2\n");
    DamOpDone(10,0);
    return op;
  }

  if (op==0xcb)
  {
    DamOpStart(op);
    ot("  ; %x - extend opcode, take 4 cycles\n",op);
    DamOpDone(4,1);
    DamFetch(0,3); DamAddPc(1);
    ot("  xor dh,dh\n");
    ot("  jmp [JumpTabCB+edx*4]\n\n");
    return op;
  }

  if (op==0xcd)
  {
    DamOpStart(op);
    ot("  ; cd nn nn - call $nnnn\n");
    ot("  sub word [DozeSP],2\n");
    ot("  mov di,word [DozeSP]\n");
    DamAddPc(2);
    ot("  mov dx,%s\n",DamPc);
    ot("  DAM_WRITE16\n");
    DamFetch(-2,2);
    ot("  mov %s,dx\n",DamPc);
    DamOpDone(17,0);
    return op;
  }

  if (op==0xddcb || op==0xfdcb)
  {
    DamOpStart(op);
    ot("  ; %x - extend opcode, take another 4 cycles\n",op);
    DamOpDone(4,1);
    ot("  ; Fetch op, and skip the I?+nn byte:\n");
    DamFetch(1,1); DamAddPc(2);
    ot("  xor dh,dh\n");
    if (op==0xfdcb) ot("  jmp [JumpTabFDCB+edx*4]\n");
    else            ot("  jmp [JumpTabDDCB+edx*4]\n");
    return op;
  }

  if (op==0xd3)
  {
    DamOpStart(op);
    ot("  ; d3 nn - out ($nn),a\n");
    DamFetch(0,1); DamAddPc(1);
    ot("  mov dh,al ; Fill high port byte with a\n");
    ot("  mov di,dx\n");
    ot("  mov dl,al\n");
    ot("  call PortOut ; Write port dl --> di\n");
    DamOpDone(11,0);
    return op;
  }

  if (op==0xdb)
  {
    DamOpStart(op);
    ot("  ; db nn - in a,($nn)\n");
    DamFetch(0,1); DamAddPc(1);
    ot("  mov dh,al ; Fill high port byte with a\n");
    ot("  mov di,dx\n");
    ot("  call PortIn ; Read port dl <-- di\n");
    ot("  mov al,dl\n");
    DamOpDone(11,0);
    return op;
  }

  if (op==0xd9)
  {
    DamOpStart(op);
    ot("  ; exx - flip registers BC,DE and HL with prime registers\n");

    DamGet16("dx",0,0);
    ot("  mov di,word[DozeBC2]\n");
    ot("  mov word[DozeBC2],dx\n");
    DamPut16("di",0,0);

    DamGet16("dx",1,0);
    ot("  mov di,word[DozeDE2]\n");
    ot("  mov word[DozeDE2],dx\n");
    DamPut16("di",1,0);

    DamGet16("dx",2,0);
    ot("  mov di,word[DozeHL2]\n");
    ot("  mov word[DozeHL2],dx\n");
    DamPut16("di",2,0);
    DamOpDone(4,0);
    return op;
  }

  if (op==0xdd)
  {
    DamOpStart(op);
    ot("  ; dd - extend opcode, take 4 cycles\n");
    DamOpDone(4,1);
    DamFetch(0,3); DamAddPc(1);
    ot("  xor dh,dh\n");
    ot("  jmp [JumpTabDD+edx*4]\n\n");
    return op;
  }

  if ((op&0xff)==0xe9)
  {
    int Ext=0;
    Ext=op>>8;
    DamOpStart(op);
    ot("  ; e9 - jp (hl) - PC <- HL/IX/IY\n");
    DamGet16("dx",2,Ext);
    ot("  mov %s,dx\n",DamPc);
    DamOpDone(4,0);
    return op;
  }

  if (op==0xed)
  {
    DamOpStart(op);
    ot("  ; ed - extend opcode, take 4 cycles\n");
    DamOpDone(4,1);
    DamFetch(0,3); DamAddPc(1);
    ot("  xor dh,dh\n");
    ot("  jmp [JumpTabED+edx*4]\n\n");
    return op;
  }

  if (op==0xeb)
  {
    DamOpStart(op);
    ot("  ; ex de,hl  (DE <==> HL)\n");
    DamGet16("dx",1,0);
    DamGet16("di",2,0);
    DamPut16("dx",2,0);
    DamPut16("di",1,0);
    DamOpDone(4,0);
    return op;
  }

  if (op==0xf3)
  {
    DamOpStart(op);
    ot("  ; di - Disable Interrupts\n");
    ot("  mov word [DozeIFF],0x0000\n");
    DamOpDone(4, 0);
    return op;
  }

  if ((op&0xff)==0xf9)
  {
    int Ext=0;
    Ext=op>>8;
    ot("  ; f9 - ld sp,HL/IX/IY\n");
    DamOpStart(op);
    DamGet16("dx",2,Ext);
    ot("  mov word [DozeSP],dx\n");
    DamOpDone(6,0);
    return op;
  }

  if (op==0xfb)
  {
    DamOpStart(op);
    ot("  ; ei - Enable Interrupts\n");

    ot("  ; See if we need to quit after enabling interrupts\n");
    ot("  test word [nDozeEi],1\n");
    ot("  jz EiContinue\n");

    ot("  cmp word [DozeIFF],0x0101\n");
    ot("  jz EiContinue ; Interrupts are already enabled\n");

    ot("  ; Yes: need to quit now\n");
    ot("  mov word [DozeIFF],0x0101\n");
    ot("  mov word [nDozeEi],2\n");
    ot("  sub %s,4\n",DamCycles);
    ot("  jmp DozeRunEnd\n\n");
    ot("EiContinue:\n");
    ot("  mov word [DozeIFF],0x0101\n");
    ot("  sub %s,4\n",DamCycles);
    ot("  FETCH_OP\n\n");
    return op;
  }

  if (op==0xfd)
  {
    DamOpStart(op);
    ot("  ; fd - extend opcode, take 4 cycles\n");
    DamOpDone(4,1);
    DamFetch(0,3); DamAddPc(1);
    ot("  xor dh,dh\n");
    ot("  jmp [JumpTabFD+edx*4]\n");
    return op;
  }

  return 0x00; // nop
}
