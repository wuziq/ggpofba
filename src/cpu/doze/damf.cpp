// Doze - Dave's optimized Z80 emulator
// Code Maker - damf
#include "dam.h"

int Damf_ED_101x_x00x(unsigned int op)
{
//     ED 101r s000    Transfer bytes from (hl) to (de)
//     ED 101r s001    compare bytes at (hl)
//   r -> once/repeat   s -> ++/--

// e.g ED 1011 0000  ldir

  DamOpStart(op);
  ot("  ; cp/ld/i/d/r\n");
  DamGet16("di",2,0);
  ot("  DAM_READ8\n");

  if (op&1)
  {
    // cp
    ot("  mov dh,ah\n");
    ot("  and dh,0x01\n");
    ot("  cmp al,dl\n");
    ot("  lahf\n");
    ot("  and ah,0xd0 ; SZ-H ----\n");
    ot("  or  ah,0x02 ; SZ-H --N-\n");
    ot("  or  ah,dh   ; SZ-H --NC\n");
    ot("  ; Now work out A-(HL)-H: for bits 5 and 3\n");
    ot("  sub dl,al\n");
    ot("  neg dl ; A-(HL)\n");
    ot("  mov dh,ah\n");
    ot("  ror dh,4\n");
    ot("  and dh,0x01\n");
    ot("  sub dl,dh ; A-(HL)-H\n");
  }
  else
  {
    // ld
    DamGet16("di",1,0);
    ot("  DAM_WRITE8\n");
    ot("  and ah,0xc1 ; SZ-H --NC  (SZC preserved, H=0, N=0)\n");
    ot("  ; Now work out A+(HL): for bits 5 and 3\n");
    ot("  add dl,al\n");
  }

  ot("  xor dh,dh\n");
  ot("  test dl,0x02 ; Bit 5 is copied from bit 1\n");
  ot("  setnz dh\n");
  ot("  rol dh,5\n");
  ot("  or ah,dh ; SZ5H --NC\n");

  ot("  mov dh,dl\n");
  ot("  and dh,0x08\n");
  ot("  or ah,dh ; SZ5H 3-NC\n");

  if ((op&1)==0)
  {
    ot("  ; Update DE\n");
    if (op&8) ot("  dec "); else ot("  inc ");
    ot("%s\n",DamLoc16(1,0));
  }

  ot("  ; Update HL\n");
  if (op&8) ot("  dec "); else ot("  inc ");
  ot("%s\n",DamLoc16(2,0));

  ot("  ; Update BC\n");
  ot("  dec %s\n",DamLoc16(0,0));

  ot("; Check if BC==0\n");
  ot("  xor dh,dh\n");
  ot("  test %s,0xffff\n",DamLoc16(0,0));
  ot("  setnz dh\n");
  ot("  rol dh,2\n");
  ot("  or ah,dh ; SZ5H 3VNC\n");

  if (op&0x10)
  {
    static int Lab=0;
    ot("; Stop repeating if BC==0\n");
    ot("  test ah,0x04 ; ---- -V--\n");
    ot("  jz Done%d\n",Lab);

    if (op&1)
    {
      ot("; Stop repeating if a-(HL) == 0\n");
      ot("  test ah,0x40 ; -Z-- ----\n");
      ot("  jnz Done%d\n",Lab);
    }

    ot("  ; Repeat instruction\n");
    ot("  INC_R\n");
    DamAddPc(-2);

    DamOpDone(17,0);
    ot("Done%d:\n",Lab++);
  }

  DamOpDone(12,0);
  return op;
}

int Damf_ED_101x_x11x(unsigned int op)
{
  static int Lab=0;
//     ED 101r s000    ini /r/d
//     ED 101r s001    outi/r/d
  DamOpStart(op);
  ot("; Repeating I/O\n");

  if ((op&1)==0)
  {
    ot("  ; Read port (bc)\n");
    DamGet16("di",0,0);
    ot("  call PortIn ; Read port dl <-- di\n");
    ot("  mov bh,dl ; Remember port byte\n");
    ot("  ; Write to (hl)\n");
    DamGet16("di",2,0);
    ot("  DAM_WRITE8\n");
  }
  else
  {
    ot("  ; Read from (hl)\n");
    DamGet16("di",2,0);
    ot("  DAM_READ8\n");
    ot("  mov bh,dl ; Remember port byte\n");
  }

  if (op&8) ot("  dec di ; Decrement hl\n");
  else      ot("  inc di ; Increment hl\n");
  DamPut16("di",2,0);

  if (op&1)
  {
    ot("  ; Write to port (bc)\n");
    DamGet16("di",0,0);
    ot("  call PortOut ; Write port dl --> di\n");
  }

  ot("  ; Decrease b\n");
  DamGet8("dl",0,0);
  ot("  dec dl\n");
  DamPut8("dl",0,0);

  ot("  xor dh,dh\n");
  ot("  mov ah,byte [DecFlag+edx] ; flags based on dec b\n");
  ot("  and ah,0xe8 ; SZ5- 3---\n");

  ot("  ; Get negative bit from the port byte\n");
  ot("  mov dh,bh\n");
  ot("  rol dh,2\n");
  ot("  and dh,2\n");
  ot("  or  ah,dh   ; SZ5- 3-N-\n");

  ot("  ; Get H and C based on c + byte\n");
  DamGet8("dl",1,0);
  if (op&1) ot("  dec dl\n"); else  ot("  inc dl\n");
  ot("  add dl,bh\n");
  ot("  setc dl\n");
  ot("  and dl,1\n");
  ot("  mov dh,dl\n");
  ot("  rol dh,4\n");
  ot("  or dl,dh\n");
  ot("  or ah,dl ; SZ5H 3-NC\n");

  if (op&0x10)
  {
    ot("; Stop repeating if B==0\n");
    ot("  test ah,0x40\n");
    ot("  jnz IoStop%d\n",Lab);
    ot("  ; Repeat instruction\n");
    ot("  INC_R\n");

    DamAddPc(-2);
    DamOpDone(17,0);
    ot("IoStop%d:\n",Lab++);
    ot("  or ah,0x04 ; SZ5H 3VNC\n");
  }

  DamOpDone(12,0);
  return op;
}
