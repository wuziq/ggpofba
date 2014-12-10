// Doze - Dave's optimized Z80 emulator
// Code Maker - jump table
#include "dam.h"

int DamJump[0x700];

int DamJumpTab()
{
  unsigned int i=0;
  ot("\n\n");

  // Output the Jump table
  for (i=0;i< (sizeof(DamJump)/sizeof(DamJump[0]));i++)
  {
    int t=0,op=0;
    int nTarget=0;

    nTarget=DamJump[i];
    t=i>>8;
    op=i&0xff;
    if (op==0)
    {
      // Label the table
      if (t==0) ot("JumpTab:     ; Normal   opcodes:\n");
      if (t==1) ot("JumpTabCB:   ; CBxx     opcodes:\n");
      if (t==2) ot("JumpTabED:   ; EDxx     opcodes:\n");
      if (t==3) ot("JumpTabDD:   ; DDxx     opcodes:\n");
      if (t==4) ot("JumpTabFD:   ; FDxx     opcodes:\n");
      if (t==5) ot("JumpTabDDCB: ; DDCB__xx opcodes:\n");
      if (t==6) ot("JumpTabFDCB: ; FDCB__xx opcodes:\n");
    }

    if (((i+0)&0x0f)==0) ot("dd ");

    ot("Op%.2X",nTarget);

    if (((i+1)&0x0f)==0) ot("\n");
    else                 ot(",");

    if (op==0xff) ot("\n");
  }
  ot("\n");
  return 0;
}

