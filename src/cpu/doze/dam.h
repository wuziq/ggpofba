// Doze - Dave's optimized Z80 emulator
// Code maker -------------------------------------------------
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __ELF__
 #define PREFIX ""
#else
 #define PREFIX "_"
#endif

// dam.cpp
extern char DamPc[];
extern char DamCycles[];
int ot(char *Format,...);
void DamAlign();
void DamVarToReg();
void DamRegToVar();
int DamOpStart(unsigned int op);
int DamOpDone(int nCycles,int bDontEnd);

// dama.cpp
int DamaFlags(int bOverflow,char *Bits35);
int DamaOp(unsigned int op);

// damc.cpp
int DamcRotate(unsigned int op);
int DamcOpCb(unsigned int op);

// dame.cpp
int Dame_00xx_0001(unsigned int op);
int Dame_00xx_x011(unsigned int op);
int Dame_00xx_1001(unsigned int op);
int Dame_11xx_0x01(unsigned int op);
int DameExHL(unsigned int op);
int DameDirectMem16(unsigned int op);
int DameOpEd(unsigned int op);

// damf.cpp
int Damf_ED_101x_x00x(unsigned int op);
int Damf_ED_101x_x11x(unsigned int op);

// damj.cpp
extern int DamJump[0x700];
int DamJumpTab();

// damm.cpp
char *DamLoc8(int r,int Ext);
int DamLoc8IsReg(int r,int Ext);
int DamGet8 (char *To  ,int r,int Ext);
int DamPut8 (char *From,int r,int Ext);
char *DamLoc16(int r,int Ext);
int DamGet16(char *To  ,int r,int Ext);
int DamPut16(char *From,int r,int Ext);
void DamIxIyOffset(int nRel);
void DamGetHL(int Ext);
int DamMacros();
int DamAddPc(int n);
int DamFetch(int nRel,int nSize);

// damo.cpp
int DamoOp(unsigned int op);

// damt.cpp
int DamTables();
