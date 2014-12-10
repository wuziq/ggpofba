/*
Part of FBAs Taito 68k hardware drivers
Credits: Mame team, Raine team
Coding by KEV, with help from Treble Winner and Jan_Klaassen
*/
#include "taito.h"
int nLastTileBpp=-1;
int nLastTileMaskBpp=-1;
int nLastSpriteMaskBpp=-1;
int nLastSpriteBpp=-1;
unsigned char taitoRecalcPal = 0;

unsigned char *tsprites=NULL;
unsigned char *ttiles=NULL;


void init_taito_gfx()
{
	nLastTileBpp=-1;
	nLastTileMaskBpp=-1;
	nLastSpriteMaskBpp=-1;
	nLastSpriteBpp=-1;

}


