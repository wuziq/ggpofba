// Doze - Dave's optimized Z80 emulator
// Code Maker
#include "dam.h"

static char *OutName="dozea.asm";
static FILE *Out=NULL;
char DamPc[]="si";
char DamCycles[]="dword [nDozeCyclesLeft]";

int ot(char *Format,...)
{
  va_list Arg; va_start(Arg,Format);
  if (Out!=NULL) vfprintf(Out,Format,Arg);
  va_end(Arg);
  return 0;
}

void DamAlign() { ot("times ($$-$) & 3 db 0\n\n"); }

static int DamVariables()
{

  // Global variables
  DamAlign();
  ot("global %sDoze\n", PREFIX);
  ot("%sDoze:\n", PREFIX);
  ot("\n");
  ot("; Z80 Registers\n");
  ot("DozeAF  dw 0\n");
  ot("DozeBC  dw 0\n");
  ot("DozeDE  dw 0\n");
  ot("DozeHL  dw 0\n");
  ot("DozeIX  dw 0\n");
  ot("DozeIY  dw 0\n");
  ot("DozePC  dw 0\n");
  ot("DozeSP  dw 0\n");
  ot("DozeAF2 dw 0\n");
  ot("DozeBC2 dw 0\n");
  ot("DozeDE2 dw 0\n");
  ot("DozeHL2 dw 0\n");
  ot("DozeIR  dw 0\n");
  ot("DozeIFF dw 0\n");
  ot("DozeIM  db 0\n");
  ot("\n");
  DamAlign();
  ot("nDozeCyclesTotal: dd 0 ; Total number of cycles in this frame (in T-states)\n");
  ot("nDozeCyclesSegment: dd 0 ; Total number of cycles in this segment (in T-states)\n");
  ot("nDozeCyclesLeft: dd 0 ; Cycles left (in T-states)\n");
  ot("nDozeEi: dd 0 ; 1 = assembler quit on EI, 2 = assembler did quit on EI\n");
  ot("nDozeInterruptLatch: dd -1\n");
  ot("\n");
  DamAlign();
  ot("DozeMemFetch: dd 0\n");
  ot("DozeMemFetchData: dd 0\n");
  ot("DozeMemRead: dd 0\n");
  ot("DozeMemWrite: dd 0\n");
  ot("\n");
  DamAlign();
  ot("DozeRead: dd 0\n");
  ot("DozeWrite: dd 0\n");
  ot("DozeIn: dd 0\n");
  ot("DozeOut: dd 0\n");
  ot("\n");

  // Private variables
  DamAlign();
  ot("Tmp16: dw 0\n");
  ot("TmpFlag: db 0\n");

  return 0;
}

int DamOpStart(unsigned int op)
{
  ot(";****************************************************************\n");

  DamAlign();

  ot("Op%-6.2X: INC_R\n\n",op);
  return 0;
}

int DamOpDone(int nCycles,int bDontEnd)
{
  ot("\n  sub %s,%d\n",DamCycles,nCycles);
  if (bDontEnd==0)
  {
    ot("  jle near DozeRunEnd\n");
    ot("  FETCH_OP\n\n");
  }
  return 0;
}

static int DamCall()
{
  DamAlign();
  ot(
  "Read:\n"
  "  REG_TO_DOZE\n"
  "  push edx\n  push edi\n"
#ifdef FASTCALL
  "  mov ecx,edi\n"
#else
  "  push edi\n"
#endif
  "  call [DozeRead]\n"
#ifndef FASTCALL
  "  add esp,4\n"
#endif
  "  pop edi\n  pop edx\n\n"
  "  mov dl,al\n"
  "  DOZE_TO_REG\n"
  "  ret\n\n"
  );

  DamAlign();
  ot(
  "Write:\n"
  "  REG_TO_DOZE\n"
  "  push edx\n  push edi\n"
#ifdef FASTCALL
  "  mov ecx,edi\n"
#else
  "  push edx\n"
  "  push edi\n"
#endif
  "  call [DozeWrite]\n"
#ifndef FASTCALL
  "  add esp,8\n"
#endif
  "  pop edi\n  pop edx\n\n"
  "  DOZE_TO_REG\n"
  "  ret\n\n"
  );

  DamAlign();
  ot(
  "PortIn:\n"
  "  REG_TO_DOZE\n"
  "  push edx\n  push edi\n"
#ifdef FASTCALL
  "  mov ecx,edi\n"
#else
  "  push edi\n"
#endif
  "  call [DozeIn]\n"
#ifndef FASTCALL
  "  add esp,4\n"
#endif
  "  pop edi\n  pop edx\n\n"
  "  mov dl,al\n"
  "  DOZE_TO_REG\n"
  "  ret\n\n"
  );

  DamAlign();
  ot(
  "PortOut:\n"
  "  REG_TO_DOZE\n"
  "  push edx\n  push edi\n"
#ifdef FASTCALL
  "  mov ecx,edi\n"
#else
  "  push edx\n"
  "  push edi\n"
#endif
  "  call [DozeOut]\n"
#ifndef FASTCALL
  "  add esp,8\n"
#endif
  "  pop edi\n  pop edx\n\n"
  "  DOZE_TO_REG\n"
  "  ret\n\n"
  );

  DamAlign();
  ot(
  "; Call a routine\n"
  "global %sDozeAsmCall\n"
  "%sDozeAsmCall:\n"
  "  mov ax,word[esp+4] ; Get address\n"
  "  mov word[Tmp16],ax\n"
  "  SAVE_REGS\n"
  "  REG_BLANK\n"
  "  DOZE_TO_REG\n"
  "  INC_R\n"
  "  sub word [DozeSP],2\n"
  "  mov dx,si\n"
  "  mov di,word [DozeSP]\n"
  "  DAM_WRITE16\n"
  "  mov dx,word[Tmp16]\n"
  "  mov si,dx\n"
  "  REG_TO_DOZE\n"
  "  RESTORE_REGS\n"
  "  ret\n\n"

  , PREFIX, PREFIX
  );

  DamAlign();
  ot(
  "; Read a byte from memory\n"
  "global %sDozeAsmRead\n"
  "%sDozeAsmRead:\n"
  "  mov ax,word[esp+4] ; Get address\n"
  "  mov word[Tmp16],ax\n"
  "  SAVE_REGS\n"
  "  REG_BLANK\n"
  "  DOZE_TO_REG\n"
  "  mov di,word [Tmp16]\n"
  "  DAM_READ8\n"
  "  REG_TO_DOZE\n"
  "  xor eax,eax\n"
  "  mov al,dl\n"
  "  RESTORE_REGS\n"
  "  ret\n\n"

  , PREFIX, PREFIX
  );

  return 0;
}

static int DamMain()
{
  int i=0;
  ot("; Doze - Dave's Z80 Emulator - Assembler output\n");
  ot("bits 32\n\n");

  ot("section .text\n\n");
  DamMacros(); // make macros
  DamCall();

  DamAlign();
  ot("global %sDozeAsmRun\n", PREFIX);
  ot("%sDozeAsmRun:\n", PREFIX);
  ot("\n");
  ot("  SAVE_REGS\n");
  ot("  REG_BLANK\n");
  ot("  DOZE_TO_REG\n");

  ot("  FETCH_OP ; Fetch first opcode\n\n");

  ot("DozeRunEnd: ; After cycles have run out, we come back here\n\n");
  ot("  REG_TO_DOZE\n");
  ot("  RESTORE_REGS\n");
  ot("  ret\n\n\n");

  memset(DamJump  ,0,sizeof(DamJump));

  // Fill in jump table if the instruction is available
  for (i=0x00;i<0x100;i++) DamJump[      i]=DamaOp  (         i);
  for (i=0x00;i<0x100;i++) DamJump[0x100+i]=DamcOpCb(  0xCB00+i);
  for (i=0x00;i<0x100;i++) DamJump[0x200+i]=DameOpEd(  0xED00+i);
  for (i=0x00;i<0x100;i++) DamJump[0x300+i]=DamaOp  (  0xDD00+i);
  for (i=0x00;i<0x100;i++) DamJump[0x400+i]=DamaOp  (  0xFD00+i);
  // Note that DDCB__xx is represented as DDCBxx here
  for (i=0x00;i<0x100;i++) DamJump[0x500+i]=DamcOpCb(0xDDCB00+i);
  for (i=0x00;i<0x100;i++) DamJump[0x600+i]=DamcOpCb(0xFDCB00+i);

  DamJumpTab(); // Jump table
  DamTables();  // Other tables

  ot("section .data\n\n");
  DamVariables();

  return 0;
}

int main(int argc, char **argv)
{
	switch (argc) {
		case 1:
			Out=fopen(OutName,"wt");
			break;
		case 2:
			Out=fopen(argv[1],"wt");
			break;
		default:
			printf ("Usage: %s [outfile]\n", argv[0]);
	}

	if (Out==NULL) return 1;

	printf ("Doze building Z80...\n");
	DamMain();
	fclose(Out); Out=NULL;
	return 0;
}

