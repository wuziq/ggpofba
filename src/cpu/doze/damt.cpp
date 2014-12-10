// Doze - Dave's optimized Z80 emulator
// Code Maker - tables
#include "dam.h"

int DamTables()
{
  int r=0;
  ot("IncFlag:\n");
  for (r=0;r<0x100;r++)
  {
    int i=0; int f=0;
    // If a value is increased to 'r', find out the flags
    i=(r-1)&0xff; // Find start value
    if (i==0x7f)    f|=0x04;   // ---- -V-- overflow
                    f|=r&0xa8; // S-5- 3V-- Sign, 5 and 3
    if (r==0)       f|=0x40;   // SZ5- 3V-- Zero
    if ((i&15)==15) f|=0x10;   // SZ5H 3V-- Half carry (low nibble overflows)

    if ((r&15)== 0) ot("db ");
    ot("0x%.2x",f);
    if ((r&15)< 15) ot(","); else ot("\n");
  }
  ot("\n");

  ot("DecFlag:\n");
  for (r=0;r<0x100;r++)
  {
    int i=0; int f=2; // negative
    // If a value is decreased to 'r', find out the flags
    i=(r+1)&0xff; // Find start value
    if (i==0x80)    f|=0x04;   // ---- -V-- overflow
                    f|=r&0xa8; // S-5- 3V-- Sign, 5 and 3
    if (r==0)       f|=0x40;   // SZ5- 3V-- Zero
    if ((i&15)== 0) f|=0x10;   // SZ5H 3V-- Half carry (low nibble overflows)

    if ((r&15)== 0) ot("db ");
    ot("0x%.2x",f);
    if ((r&15)< 15) ot(","); else ot("\n");
  }
  ot("\n");

  {
    int d=0;
    ot("DaaTable: ;(HNC nnnn nnnn)\n");
    for (d=0x0;d<0x800;d++)
    {
      int e=0,f=0;

      e=d&0x1ff; // include carry bit

      if (d&0x400) // Was a half-carry
      {
        if (d&0x200) // After subtraction
        {
          e-=6;
          f|=0x02; // N
          if (e>0x99-6) { e-=0x60; f|=0x01; } // Carry
          if ((e&15)>9) {          f|=0x10; } // Half-carry
        }
        else
        {
          e+=6;
          if (e>0x99+6) { e+=0x60; f|=0x01; } // Carry
          if ((e&15)<6) {          f|=0x10; } // Half-carry
        }
      }
      else
      {
        if (d&0x200) // After subtraction
        {
          f|=0x02; // N
          if (e>0x99)   { e-=0x60; f|=0x01; } // Carry
          if ((e&15)>9) { e-=0x06; f|=0x10; } // Half-carry
        }
        else // After addition
        {
          if (e>0x99)   { e+=0x60; f|=0x01; } // Carry
          if ((e&15)>9) { e+=0x06; f|=0x10; } // Half-carry
        }
      }

      e&=0xff;

      f|=e&0xa8; // S,5,3


      if (e==0) f|=0x40; // Z

      {
        int p;
        p=e^(e>>4); p&=15;
        p=p^(p>>2); p&=3;
        p=p^(p>>1); p&=1;
        if (p==0) f|=0x04; // parity
      }

      if ((d&15)== 0) ot("dw ");
      ot("0x%.4x",(f<<8)|e);
      if ((d&15)<15) ot(","); else ot(" ; %.3x\n",d-15);
    }
    ot("\n");
  }

  return 0;
}

