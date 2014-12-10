// Inputs common to all Cps2 Fighter Style games (3 x Punch,3 x Kick)

#include "cps.h"

struct BurnInputInfo CpsFsi[] = {
  {"P1 Coin",			BIT_DIGITAL, CpsInp020+4, "p1 coin"},	// 0x00
  {"P1 Start",			BIT_DIGITAL, CpsInp020+0, "p1 start"},

  {"P1 Up",				BIT_DIGITAL, CpsInp001+3, "p1 up"},		// 0x02
  {"P1 Down",			BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left",			BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right",			BIT_DIGITAL, CpsInp001+0, "p1 right"},

  {"P1 Weak punch",		BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},	// 0x06
  {"P1 Medium punch",	BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Strong punch",	BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},
  {"P1 Weak kick",		BIT_DIGITAL, CpsInp011+0, "p1 fire 4"},
  {"P1 Medium kick",	BIT_DIGITAL, CpsInp011+1, "p1 fire 5"},
  {"P1 Strong kick",	BIT_DIGITAL, CpsInp011+2, "p1 fire 6"},

  {"P2 Coin",			BIT_DIGITAL, CpsInp020+5, "p2 coin"},	// 0x0C
  {"P2 Start",			BIT_DIGITAL, CpsInp020+1, "p2 start"},

  {"P2 Up",				BIT_DIGITAL, CpsInp000+3, "p2 up"},		// 0x0E
  {"P2 Down",			BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left",			BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right",			BIT_DIGITAL, CpsInp000+0, "p2 right"},

  {"P2 Weak punch",		BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},	// 0x12
  {"P2 Medium punch",	BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Strong Punch",	BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},
  {"P2 Weak kick",		BIT_DIGITAL, CpsInp011+4, "p2 fire 4"},
  {"P2 Medium kick",	BIT_DIGITAL, CpsInp011+5, "p2 fire 5"},
  {"P2 Strong kick",	BIT_DIGITAL, CpsInp020+6, "p2 fire 6"},

  {"Reset",				BIT_DIGITAL, &CpsReset  , "reset"},		// 0x18
  {"Diagnostic",		BIT_DIGITAL, CpsInp021+1, "diag"},
  {"Service",			BIT_DIGITAL, CpsInp021+2, "service"},
};

