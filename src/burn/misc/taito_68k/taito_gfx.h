/*
Part of FBAs Taito 68k hardware drivers
Credits: Mame team, Raine team
Coding by KEV, with help from Treble Winner and Jan_Klaassen
*/

#ifndef __TAITOGFX_H__
#define __TAITOGFX_H__

// Common Stuff
extern unsigned int *taito_pal;
extern int nLastTileBpp;
extern int nLastTileMaskBpp;
extern int nLastSpriteMaskBpp;
extern int nLastSpriteBpp;
extern unsigned char taitoRecalcPal;

extern unsigned char *tsprites; // Sprite buffer
extern unsigned char *ttiles; // Tile Buffer
void init_taito_gfx();

// PC090OJ - used for sprites in Rastan, Rainbow and OpWolf
extern unsigned char *PC090OJ_word_0;
extern unsigned char *PC090OJ_spritectrl;
void PC090OJ_draw_sprites();

// PC080SN - used for backgrounds in Rastan, Rainbow and OpWolf
// This will need to be redone as its not 100% accurate. :)
extern unsigned char *PC080SN_word_0,*PC080SN_yscroll_word_0;
extern unsigned char *PC080SN_xscroll_word_0,*PC080SN_ctrl_word_0;
void PC080SN_bg();
void PC080SN_fg();
void draw_gun(int x, int y);
void init_gun();
extern int p1scrollx,p2scrollx;
extern int p1scrolly,p2scrolly;

//tatio systemx
void SysXSprites();
void SysXBG();
extern unsigned char *sysbvidattr,*sysbvidram;
void SysXInit(int game);
extern unsigned char *SysxTempGfx;


#endif


