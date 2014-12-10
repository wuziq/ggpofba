// Doze - Dave's optimized Z80 emulator
// Code Maker - misc
#include "dam.h"

char *DamLoc8(int r,int Ext)
{
  if (r==0) return "byte [DozeBC+1]";
  if (r==1) return "byte [DozeBC]";
  if (r==2) return "byte [DozeDE+1]";
  if (r==3) return "byte [DozeDE]";
  if (r==4)
  {
    if (Ext==0xdd) return "byte [DozeIX+1]";
    if (Ext==0xfd) return "byte [DozeIY+1]";
    return "ch";
  }
  if (r==5)
  {
    if (Ext==0xdd) return "byte [DozeIX]";
    if (Ext==0xfd) return "byte [DozeIY]";
    return "cl";
  }
  if (r==7) return "al";
  return "";
}

// Return 1 if the emulated version is a register like cl
int DamLoc8IsReg(int r,int Ext)
{
  if (r==4 && Ext==0) return 1; // ch
  if (r==5 && Ext==0) return 1; // cl
  if (r==7) return 1; // al
  return 0;
}

int DamGet8(char *To  ,int r,int Ext)
{
  // Get register r into To   (must be dl for reg 6)
  if (r==6) { ot("  DAM_READ8\n"); return 0; }
  ot("  mov %s,%s\n",To,DamLoc8(r,Ext));
  return 0;
}

int DamPut8(char *From,int r,int Ext)
{
  // Put register r from From (must be dl for reg 6)
  if (r==6) { ot("  DAM_WRITE8\n"); return 0; }
  ot("  mov %s,%s\n",DamLoc8(r,Ext),From);
  return 0;
}

char *DamLoc16(int r,int Ext)
{
  if (r==0) return "word [DozeBC]";
  if (r==1) return "word [DozeDE]";
  if (r==2)
  {
    if (Ext==0xdd) return "word [DozeIX]";
    if (Ext==0xfd) return "word [DozeIY]";
    return "cx";
  }
  if (r==3) return "word [DozeSP]";
  return "";
}

int DamGet16(char *To  ,int r,int Ext)
{
  // Get register r into To
  ot("  mov %s,%s\n",To,DamLoc16(r,Ext));
  return 0;
}

int DamPut16(char *From,int r,int Ext)
{
  // Put register r from
  ot("  mov %s,%s\n",DamLoc16(r,Ext),From);
  return 0;
}

void DamIxIyOffset(int nRel)
{
  // Get IX/IY offset from PC+nRel
  ot("  ; Get IX/IY offset into di\n");
  DamFetch(nRel,1);
  ot("  xor dh,dh\n");
  ot("  xor dl,0x80\n");
  ot("  sub dx,0x80\n");
  ot("  mov di,dx\n");
}

void DamGetHL(int Ext)
{
  // Get the HL pointer, or if extended the IX/IY pointer
  if (Ext!=0xdd && Ext!=0xfd) Ext=0;
  if (Ext==0) DamGet16("di",2,Ext);
  else ot("  add di,%s\n",DamLoc16(2,Ext));
}

int DamMacros()
{
  ot(
  "%%macro SAVE_REGS 0\n"
  "  push ebx\n  push ecx\n  push edx\n  push esi\n  push edi\n  push ebp\n"
  "%%endmacro\n\n"

  "%%macro RESTORE_REGS 0\n"
  "  pop ebp\n  pop edi\n  pop esi\n  pop edx\n  pop ecx\n  pop ebx\n"
  "%%endmacro\n\n"
  );

  ot(
  "%%macro DOZE_TO_REG 0\n"
  "  ; Load a into al, f into ah\n"
  "  mov ax,word [DozeAF]\n"
  "  ror ax,8\n"
  "  ; Load hl into cx\n"
  "  mov cx,word [DozeHL]\n"
  "  mov bl,byte [DozeIR] ; Load bl <- R counter\n"
  "  rol bl,1 ; bl <-- R register bits (65432107)\n"
  "  xor esi,esi\n"
  "  mov si,word [DozePC] ; Load si <- PC\n"
  "%%endmacro\n\n"

  "%%macro REG_BLANK 0\n"
  "  xor edx,edx ; High 16 bits of edx kept clear\n"
  "  xor edi,edi ; High 16 bits of edi kept clear\n"
  "%%endmacro\n\n"

  "%%macro REG_TO_DOZE 0\n"
  "  ; Save a from al, f from ah\n"
  "  ror ax,8\n"
  "  mov word [DozeAF],ax\n"
  "  ; Save hl from cx\n"
  "  mov word [DozeHL],cx\n"
  "  ror bl,1 ; bl --> R register bits 76543210\n"
  "  mov byte [DozeIR],bl ; Save bl -> R counter\n"
  "  mov word [DozePC],si ; Save si -> PC\n"
  "%%endmacro\n\n"
  );

  // Memory access based on _DozeMemFetch/Read/Write:
  ot(
  "%%macro DAM_FETCH8 0\n"
  "; Fetch byte (esi) ==> dl\n"
  "  mov edx,esi\n"
  "  shr edx,8\n"
  "  mov ebp,[DozeMemFetch]\n"
  "  mov ebp,dword[ebp+edx*4]\n"
  "  mov dl,byte [ebp+esi]\n"
  "%%endmacro\n\n"

   "%%macro DAM_FETCH8D 0\n"
  "; Fetch byte (esi) ==> dl\n"
  "  mov edx,esi\n"
  "  shr edx,8\n"
  "  mov ebp,[DozeMemFetchData]\n"
  "  mov ebp,dword[ebp+edx*4]\n"
  "  mov dl,byte [ebp+esi]\n"
  "%%endmacro\n\n"

  "%%macro DAM_FETCH16D 0\n"
  "; Fetch word  (esi) ==> dx\n"
  "  mov edx,esi\n"
  "  shr edx,8\n"
  "  mov ebp,[DozeMemFetchData]\n"
  "  mov ebp,dword[ebp+edx*4]\n"
  "  mov dx,word [ebp+esi]\n"
  "%%endmacro\n\n"

  "%%macro DAM_READ8 0\n"
  "; Read byte   (edi) ==> dl\n"
  "  mov edx,edi\n"
  "  shr edx,8\n"
  "  mov ebp,[DozeMemRead]\n"
  "  mov ebp,dword[ebp+edx*4]\n"
  "  test ebp,ebp\n"
  "  jnz %%%%Direct\n"
  "  call Read\n"
  "  jmp %%%%Done\n"
  "%%%%Direct:\n"
  "  mov dl,byte [ebp+edi]\n"
  "%%%%Done:\n"
  "%%endmacro\n\n"

  "%%macro DAM_WRITE8 0\n"
  "; Write byte  dl ==> (edi)\n"
  "  mov ebp,edi\n"
  "  shr ebp,8\n"
  "  shl ebp,2\n"
  "  add ebp,[DozeMemWrite]\n"
  "  mov ebp,dword[ebp]\n"
  "  test ebp,ebp\n"
  "  jnz %%%%Direct\n"
  "  call Write\n"
  "  jmp %%%%Done\n"
  "%%%%Direct:\n"
  "  mov byte [ebp+edi],dl\n"
  "%%%%Done:\n"
  "%%endmacro\n\n"

  "%%macro DAM_READ16 0\n"
  "; Read word   (edi) ==> dx\n"
  "  mov edx,edi\n"
  "  shr edx,8\n"
  "  mov ebp,[DozeMemRead]\n"
  "  mov ebp,dword[ebp+edx*4]\n"
  "  test ebp,ebp\n"
  "  jnz %%%%Direct\n"
  "  inc di\n"
  "  call Read\n"
  "  dec di\n"
  "  mov dh,dl\n"
  "  jmp %%%%Done\n"
  "  call Read\n"
  "%%%%Direct:\n"
  "  mov dx,word [ebp+edi]\n"
  "%%%%Done:\n"
  "%%endmacro\n\n"

  "%%macro DAM_WRITE16 0\n"
  "; Write word  dx ==> (edi)\n"
  "  mov ebp,edi\n"
  "  shr ebp,8\n"
  "  shl ebp,2\n"
  "  add ebp,[DozeMemWrite]\n"
  "  mov ebp,dword[ebp]\n"
  "  test ebp,ebp\n"
  "  jnz %%%%Direct\n"
  "  inc di\n"
  "  ror dx,8\n"
  "  call Write\n"
  "  dec di\n"
  "  ror dx,8\n"
  "  call Write\n"
  "  jmp %%%%Done\n"
  "%%%%Direct:\n"
  "  mov word [ebp+edi],dx\n"
  "%%%%Done:\n"
  "%%endmacro\n\n"
  );

  ot(
  "%%macro FETCH_OP 0\n"
  "  ; Fetch next normal opcode\n"
  );

  DamFetch(0,3); DamAddPc(1);
  ot(
  "  xor dh,dh\n"
  "  jmp [JumpTab+edx*4]\n"
  "%%endmacro\n\n"
  );

  ot(
  "%%macro INC_R 0\n"
  "  add bl,2 ; Increase instruction counter R (bit 7 never modified)\n"
  "%%endmacro\n\n"
  );
  return 0;
}

int DamAddPc(int n)
{
  // Increase the PC by n
       if (n== 1) ot("  inc %s\n",DamPc);
  else if (n==-1) ot("  dec %s\n",DamPc);
  else if (n > 0) ot("  add %s,%d\n",DamPc, n);
  else if (n < 0) ot("  sub %s,%d\n",DamPc,-n);
  return 0;
}

int DamFetch(int nRel,int nSize)
{
  // Fetch PC+nRel into dl (edx clobbered)

       if (nRel== 1) ot("  inc si\n");
  else if (nRel==-1) ot("  dec si\n");
  else if (nRel > 0) ot("  add si,%d\n", nRel);
  else if (nRel < 0) ot("  sub si,%d\n",-nRel);

       if (nSize==2)  ot("  DAM_FETCH16D\n");
  else if (nSize==1)  ot("  DAM_FETCH8D\n");
  else if (nSize==3)  ot("  DAM_FETCH8\n");
  else return 1;

  nRel=-nRel;
       if (nRel== 1) ot("  inc si\n");
  else if (nRel==-1) ot("  dec si\n");
  else if (nRel > 0) ot("  add si,%d\n", nRel);
  else if (nRel < 0) ot("  sub si,%d\n",-nRel);

  return 0;
}
