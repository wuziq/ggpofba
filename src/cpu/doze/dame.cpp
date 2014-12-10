// Doze - Dave's optimized Z80 emulator
// Code Maker - dame: mostly 16-bit opcodes
#include "dam.h"

int Dame_00xx_0001(unsigned int op)
{
//       00dd 0001 nnnn
//    dd -> bc,de,hl,sp
// Load the immediate value into 16-bit register. Can be extended with DD or FD

//e.g    0011 0001 nnnn   ld sp,$nnnn
//e.g DD 0010 0001 nnnn   ld ix,$nnnn

  int d=0; int Ext=0;
  d=(op>>4)&3; Ext=op>>8;
  if ((op>>8) && d!=2) return op&0xff; // No such DD/FD opcode

  DamOpStart(op);
  ot("; Load Immediate 16-bit\n");
  DamFetch(0,2); DamAddPc(2);
  DamPut16("dx",d,Ext);
  DamOpDone(10,0);
  return op;
}

int Dame_00xx_x011(unsigned int op)
{
//       00dd s011     Inc/dec a 16-bit register. Can be extended with DD or FD.
//    dd -> bc,de,hl,sp     s -> inc,dec

// e.g   0000 0011  inc bc

  int d=0,t=6; int Ext=0;
  d=(op>>4)&3; Ext=op>>8;
  if ((op>>8) && d!=2) return op&0xff; // No such DD/FD opcode
  DamOpStart(op);

//TEST:
  if (op&8) ot("  dec "); else ot("  inc ");
  ot("%s\n",DamLoc16(d,Ext));
/* TEST

  DamGet16("dx",d,Ext);
  if (op&8) ot("  dec dx\n"); else ot("  inc dx\n");
  DamPut16("dx",d,Ext);
*/
  ot("  ; (With 16-bit inc, flags aren't changed)\n");
  DamOpDone(t,0);
  return op;
}

int Dame_00xx_1001(unsigned int op)
{
//       00dd 1001  -  Add a register to hl. Can be extended with DD or FD.
//    dd -> bc,de,hl,sp

//e.g    0000 1001   add hl,bc
//e.g DD 0000 1001   add ix,bc
//e.g DD 0010 1001   add ix,ix

  int s=0; int Ext=0;
  s=(op>>4)&3; Ext=op>>8;

  DamOpStart(op);
  ot("  mov bh,ah\n");
  ot("  and bh,0xc4 ; Remember SZ---P--\n");
  DamGet16("dx",s,Ext);
  ot("  ror ebx,16 ; Get access to a spare bit of ebx\n");
  ot("  mov bx,dx\n");
  DamGet16("dx",2,Ext);

  ot("  ; Do operation in two bytes to get the correct z80 flags (for the msb)\n");
  ot("  add dl,bl\n");
  ot("  adc dh,bh\n");
  ot("  lahf\n");

  DamPut16("dx",2,Ext);
  ot("  ror ebx,16 ; Done with ebx\n");

  ot("  and ah,0x11 ; ---H---C get flags.\n");

  ot("  and dh,0x28\n");
  ot("  or  ah,dh   ; --5H3--C\n");

  ot("  or  ah,bh\n");
  DamOpDone(11,0);
  return op;
}

int Dame_11xx_0x01(unsigned int op)
{
//       11rr 0p01     Push/Pop a register. Can be extended with DD or FD
//    dd -> bc,de,hl,af     s -> pop,push
  int r=0,p=0,t=10; int Ext=0;
  r=(op>>4)&3; p=(op>>2)&1; Ext=op>>8;
  if (Ext && r!=2) return op&0xff; // No such DD/FD opcode
  if (p) t++; // Push takes longer

  DamOpStart(op);
  if (p)
  {
    // Push
    ot("  sub word [DozeSP],2\n");
    ot("  mov di,word [DozeSP]\n");
    if (r==3) ot("  mov dx,ax\n  ror dx,8\n");      // AF
    else      DamGet16("dx",r,Ext);
    ot("  DAM_WRITE16\n");
  }
  else
  {
    // Pop
    ot("  mov di,word [DozeSP]\n");
    ot("  DAM_READ16\n");
    if (r==3) ot("  mov ax,dx\n  ror ax,8\n");      // AF
    else      DamPut16("dx",r,Ext);
    ot("  add word [DozeSP],2\n");
  }

  DamOpDone(t,0);
  return op;
}

int DameExHL(unsigned int op)
{
  int t=19; int Ext=0;
  Ext=op>>8;
  DamOpStart(op);
  ot("  ; Find the memory location:\n");
  ot("  mov di,word [DozeSP]\n");
  ot("  ; Swap HL with it:\n");
  ot("  DAM_READ16\n");
  ot("  mov word [Tmp16],dx\n");
  DamGet16("dx",2,Ext);
  ot("  DAM_WRITE16\n");
  ot("  mov dx,word [Tmp16]\n");
  DamPut16("dx",2,Ext);
  DamOpDone(t,0);
  return op;
}

int DameDirectMem16(unsigned int op)
{
//        0010 s010 nn nn   Move hl to/from (nnnn). Can be extended with DD or FD.
//and  ED 01rr s011 nn nn   Move 16-bit register to/from (nnnn)

//    rr -> bc,de,hl,sp     s -> To mem, From mem

// e.g    0010 0010 nn nn  ld ($nnnn),hl
// e.g DD 0010 0010 nn nn  ld ($nnnn),ix
// e.g ED 0100 0011 nn nn  ld ($nnnn),bc

  int r=0; int Ext=0;
  r=(op>>4)&3; Ext=op>>8;
  if (Ext!=0xdd && Ext!=0xfd) Ext=0;
  if (Ext==0xdd && r!=2) return op&0xff; // No such DD opcode
  if (Ext==0xfd && r!=2) return op&0xff; // No such FD opcode
  DamOpStart(op);

  ot("; Direct access to a memory location\n");
  DamFetch(0,2); DamAddPc(2);
  ot("  mov di,dx\n");
  if (op&8)
  {
    ot("  DAM_READ16\n");
    DamPut16("dx",r,Ext);
  }
  else
  {
    DamGet16("dx",r,Ext);
    ot("  DAM_WRITE16\n");
  }

  DamOpDone(16,0);
  return op;
}

static int DameAdcSbc16(unsigned int op)
{
//     ED 01dd s010      Add/sub a register from hl (with carry)
//    dd -> bc,de,hl,sp     s -> sbc,adc

// e.g ED 0100 0010  sbc hl,bc

  int s=0;
  s=(op>>4)&3;
  DamOpStart(op);
  DamGet16("dx",2,0);
  ot("  mov word[Tmp16],dx\n");
  DamGet16("dx",s,0);

  ot("  sahf ; Get the carry flag\n");
  ot("  ; Do operation in two bytes to get the correct z80 flags (for the msb)\n");
  if (op&8)
  {
    ot("  adc byte [Tmp16]  ,dl\n");
    ot("  setz dl\n");
    ot("  adc byte [Tmp16+1],dh\n");
  }
  else
  {
    ot("  sbb byte [Tmp16]  ,dl\n");
    ot("  setz dl\n");
    ot("  sbb byte [Tmp16+1],dh\n");
  }

  DamaFlags(1,"byte [Tmp16+1]"); // Get flags with overflow
  if ((op&8)==0) ot("  or ah,0x02 ; Set bit 1 - last operation was a subtraction\n");
  ot("  or  dl,0xfe ; 1111 1110 if high byte not zero\n");
  ot("  rol dl,6    ; 1011 1111\n");
  ot("  and ah,dl   ; Correct zero flag\n");

  ot("  mov dx,word[Tmp16]\n");
  DamPut16("dx",2,0);

  DamOpDone(11,0);
  return op;
}

static int Dame_ED_01xx_x110(unsigned int op)
{
  int nn=0,i=0;
//     ED 01xn n110   Set Interrupt mode
// nn -> 0,?,1,2
  nn=(op>>3)&3;

  if (op&0x20) return op&(~0x20); // aka opcode

  if (nn==0) i=0;
  if (nn==1) i=0;
  if (nn==2) i=1;
  if (nn==3) i=2;

  DamOpStart(op);
  ot(";  im %d\n",i);
  ot("  mov byte[DozeIM],%d\n",i);
  DamOpDone(4,0);
  return op;
}

static int Dame_ED_01xx_x00x(unsigned int op)
{
//              ED 01dd d00s - port i/o from (c) or (bc)
  int d=0,s=0;
  d=(op>>3)&7; s=op&1;

  DamOpStart(op);
  DamGet16("di",0,0);

  if (s==0)
  {
    // Input
    ot("  and ah,0x01 ; Remember carry\n");
    ot("  mov dh,ah\n");
    ot("  xor ah,ah\n");
    ot("  call PortIn ; Read port dl <-- di\n");
    ot("  test dl,dl\n");
    ot("  lahf\n");
    ot("  and ah,0xc4 ; SZ-- -P--\n");
    ot("  or ah,dh    ; SZ-- -P-C\n");

    if (d!=6) DamPut8("dl",d,0);
  }
  else
  {
    // Output
    if (d==6) ot("xor dl,dl\n"); else DamGet8("dl",d,0);
    ot("  call PortOut ; Write port dl --> di\n");
  }

  DamOpDone(8,0);
  return op;
}

static int Dame_ED_01xx_x101(unsigned int op)
{
//              ED 01xx x101 - retn/reti
  if (op!=0xed45) return 0xed45; // Use same instruction

  DamOpStart(op);
  ot("  ; retn/i\n");
  ot("  mov di,word [DozeSP]\n");
  ot("  DAM_READ16\n");
  ot("  mov %s,dx\n",DamPc);
  ot("  add word [DozeSP],2\n");
  ot("  mov dl,byte [DozeIFF+1]\n");
  ot("  mov byte [DozeIFF],dl ; iff1 <-- iff2\n");

  DamOpDone(10,0);
  return op;
}

static int Dame_ED_0110_x111(unsigned int op)
{
//              ED 0110 d111 - rld/rrd
  int d=0;
  d=(op>>3)&1;

  DamOpStart(op);
  DamGetHL(0);
  DamGet8("dl",6,0);

  if (d==1)
  {
    ot("  ; aaaa DDDD dddd, rotate <---\n");
    ot("  rol dx,8    ; DDDD dddd ---- ----\n");
    ot("  ror al,4\n");
    ot("  mov dl,al\n");
    ot("  ror al,4\n");
    ot("  and dl,0xf0 ; DDDD dddd aaaa ----\n");
    ot("  rol dx,4    ; dddd aaaa ---- DDDD\n");
    ot("  and al,0xf0\n");
    ot("  or  al,dl   ; GOT aaaa=DDDD\n");
    ot("  mov dl,dh   ; dddd aaaa dddd aaaa\n");
    ot("  xor dh,dh   ; ---- ---- dddd aaaa  GOT new d\n");
  }
  else
  {
    ot("  ; aaaa DDDD dddd, rotate --->\n");
    ot("  rol dl,4    ; ---- ---- dddd DDDD\n");
    ot("  rol dx,8    ; dddd DDDD ---- ----\n");
    ot("  ror al,4\n");
    ot("  mov dl,al\n");
    ot("  ror al,4\n");
    ot("  and dl,0xf0 ; dddd DDDD aaaa ----\n");
    ot("  rol dx,4    ; DDDD aaaa ---- dddd\n");
    ot("  and al,0xf0\n");
    ot("  or  al,dl   ; GOT aaaa=dddd\n");
    ot("  mov dl,dh   ; DDDD aaaa DDDD aaaa\n");
    ot("  xor dh,dh   ; ---- ---- DDDD aaaa\n");
    ot("  rol dl,4    ; ---- ---- aaaa DDDD  GOT new d\n");
  }

  DamPut8("dl",6,0);

  ot("  mov dh,ah\n");
  ot("  and dh,0x01 ; Preserve Carry\n");
  ot("  test al,al\n");
  ot("  lahf\n");
  ot("  and ah,0xc4 ; SZ-- -P--\n");
  ot("  or  ah,dh   ; SZ-- -P-C\n");

  DamOpDone(14,0);
  return op;
}

int DameOpEd(unsigned int op)
{
  if ((op&0xc6)==0x40) return Dame_ED_01xx_x00x(op);
  if ((op&0xc7)==0x42) return DameAdcSbc16(op);
  if ((op&0xc7)==0x43) return DameDirectMem16(op);
  if ((op&0xc7)==0x44)
  {
    if (op!=0xed44) return 0xed44; // aka opcode
    DamOpStart(op);
    ot("  ; ed 44 (and others) - neg\n");
    ot("  and ah,0x01 ; Remember carry\n");
    ot("  mov dh,ah\n");
    ot("  neg al\n");
    DamaFlags(1,"al");
    ot("  or  ah,0x02\n");
    DamOpDone(4,0);
    return op;
  }

  if ((op&0xc7)==0x45) return Dame_ED_01xx_x101(op);
  if ((op&0xc7)==0x46) return Dame_ED_01xx_x110(op);
  if ((op&0xf7)==0x47)
  {
    DamOpStart(op);
    if (op&0x08)
    {
      ot("  mov bl,al   ; ld r,a\n");
      ot("  rol bl,1\n");
    }
    else         ot("  mov byte [DozeIR+1],al ; ld i,a\n");
    DamOpDone(5,0);
    return op;
  }

  if ((op&0xf7)==0x57)
  {
    DamOpStart(op);
    ot("  mov dh,ah\n");
    ot("  and dh,0x01 ; ---- ---C\n");

    if (op&0x08)
    {
      ot("  mov al,bl\n");
      ot("  ror al,1 ; ld a,r\n");
    }
    else ot("  mov al,byte [DozeIR+1] ; ld a,i\n");

    ot("  test al,al\n");
    ot("  lahf\n");
    ot("  and ah,0xc0 ; SZ-- ----\n");
    ot("  or ah,dh    ; SZ-- ---C\n");
    ot("  mov dh,al\n");
    ot("  and dh,0x28\n");
    ot("  or ah,dh    ; SZ5- 3--C\n");
    ot("  mov dh,byte [DozeIFF+1] ; get iff2\n");
    ot("  rol dh,2\n");
    ot("  and dh,0x04\n");
    ot("  or ah,dh    ; SZ5- 3V-C\n");
    DamOpDone(5,0);
    return op;
  }
  if ((op&0xf7)==0x67) return Dame_ED_0110_x111(op);

  if ((op&0xe6)==0xa0) return Damf_ED_101x_x00x(op);
  if ((op&0xe6)==0xa2) return Damf_ED_101x_x11x(op);

  return 0;
}
