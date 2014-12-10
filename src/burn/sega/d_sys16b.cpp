#include "sys16.h"

/*====================================================
Input defs
====================================================*/

#define A(a, b, c, d) {a, b, (unsigned char*)(c), d}

static struct BurnInputInfo System16bInputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , System16InputPort0 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , System16InputPort0 + 4, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL  , System16InputPort0 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , System16InputPort0 + 5, "p2 start"  },

	{"P1 Up"             , BIT_DIGITAL  , System16InputPort1 + 5, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , System16InputPort1 + 4, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , System16InputPort1 + 7, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , System16InputPort1 + 6, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , System16InputPort1 + 1, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL  , System16InputPort1 + 2, "p1 fire 2" },

	{"P2 Up"             , BIT_DIGITAL  , System16InputPort2 + 5, "p2 up"     },
	{"P2 Down"           , BIT_DIGITAL  , System16InputPort2 + 4, "p2 down"   },
	{"P2 Left"           , BIT_DIGITAL  , System16InputPort2 + 7, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL  , System16InputPort2 + 6, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , System16InputPort2 + 1, "p2 fire 1" },
	{"P2 Fire 2"         , BIT_DIGITAL  , System16InputPort2 + 2, "p2 fire 2" },

	{"Service"           , BIT_DIGITAL  , System16InputPort0 + 3 , "service"  },
	{"Diagnostics"       , BIT_DIGITAL  , System16InputPort0 + 2 , "diag"     },
	{"Reset"             , BIT_DIGITAL  , &System16Reset         , "reset"    },
	{"Dip 1"             , BIT_DIPSWITCH, System16Dip + 0        , "dip"      },
	{"Dip 2"             , BIT_DIPSWITCH, System16Dip + 1        , "dip"      },
};

STDINPUTINFO(System16b);

static struct BurnInputInfo System16bfire1InputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , System16InputPort0 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , System16InputPort0 + 4, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL  , System16InputPort0 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , System16InputPort0 + 5, "p2 start"  },

	{"P1 Up"             , BIT_DIGITAL  , System16InputPort1 + 5, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , System16InputPort1 + 4, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , System16InputPort1 + 7, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , System16InputPort1 + 6, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , System16InputPort1 + 1, "p1 fire 1" },

	{"P2 Up"             , BIT_DIGITAL  , System16InputPort2 + 5, "p2 up"     },
	{"P2 Down"           , BIT_DIGITAL  , System16InputPort2 + 4, "p2 down"   },
	{"P2 Left"           , BIT_DIGITAL  , System16InputPort2 + 7, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL  , System16InputPort2 + 6, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , System16InputPort2 + 1, "p2 fire 1" },

	{"Service"           , BIT_DIGITAL  , System16InputPort0 + 3 , "service"  },
	{"Diagnostics"       , BIT_DIGITAL  , System16InputPort0 + 2 , "diag"     },
	{"Reset"             , BIT_DIGITAL  , &System16Reset         , "reset"    },
	{"Dip 1"             , BIT_DIPSWITCH, System16Dip + 0        , "dip"      },
	{"Dip 2"             , BIT_DIPSWITCH, System16Dip + 1        , "dip"      },
};

STDINPUTINFO(System16bfire1);

static struct BurnInputInfo System16bfire3InputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , System16InputPort0 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , System16InputPort0 + 4, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL  , System16InputPort0 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , System16InputPort0 + 5, "p2 start"  },

	{"P1 Up"             , BIT_DIGITAL  , System16InputPort1 + 5, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , System16InputPort1 + 4, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , System16InputPort1 + 7, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , System16InputPort1 + 6, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , System16InputPort1 + 0, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL  , System16InputPort1 + 1, "p1 fire 2" },
	{"P1 Fire 3"         , BIT_DIGITAL  , System16InputPort1 + 2, "p1 fire 3" },

	{"P2 Up"             , BIT_DIGITAL  , System16InputPort2 + 5, "p2 up"     },
	{"P2 Down"           , BIT_DIGITAL  , System16InputPort2 + 4, "p2 down"   },
	{"P2 Left"           , BIT_DIGITAL  , System16InputPort2 + 7, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL  , System16InputPort2 + 6, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , System16InputPort2 + 0, "p2 fire 1" },
	{"P2 Fire 2"         , BIT_DIGITAL  , System16InputPort2 + 1, "p2 fire 2" },
	{"P2 Fire 3"         , BIT_DIGITAL  , System16InputPort2 + 2, "p2 fire 3" },

	{"Service"           , BIT_DIGITAL  , System16InputPort0 + 3 , "service"  },
	{"Diagnostics"       , BIT_DIGITAL  , System16InputPort0 + 2 , "diag"     },
	{"Reset"             , BIT_DIGITAL  , &System16Reset         , "reset"    },
	{"Dip 1"             , BIT_DIPSWITCH, System16Dip + 0        , "dip"      },
	{"Dip 2"             , BIT_DIPSWITCH, System16Dip + 1        , "dip"      },
};

STDINPUTINFO(System16bfire3);

static struct BurnInputInfo System16bfire4InputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , System16InputPort0 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , System16InputPort0 + 4, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL  , System16InputPort0 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , System16InputPort0 + 5, "p2 start"  },

	{"P1 Up"             , BIT_DIGITAL  , System16InputPort1 + 5, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , System16InputPort1 + 4, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , System16InputPort1 + 7, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , System16InputPort1 + 6, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , System16InputPort1 + 0, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL  , System16InputPort1 + 1, "p1 fire 2" },
	{"P1 Fire 3"         , BIT_DIGITAL  , System16InputPort1 + 2, "p1 fire 3" },
	{"P1 Fire 4"         , BIT_DIGITAL  , System16InputPort1 + 3, "p1 fire 4" },

	{"P2 Up"             , BIT_DIGITAL  , System16InputPort2 + 5, "p2 up"     },
	{"P2 Down"           , BIT_DIGITAL  , System16InputPort2 + 4, "p2 down"   },
	{"P2 Left"           , BIT_DIGITAL  , System16InputPort2 + 7, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL  , System16InputPort2 + 6, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , System16InputPort2 + 0, "p2 fire 1" },
	{"P2 Fire 2"         , BIT_DIGITAL  , System16InputPort2 + 1, "p2 fire 2" },
	{"P2 Fire 3"         , BIT_DIGITAL  , System16InputPort2 + 2, "p2 fire 3" },
	{"P2 Fire 4"         , BIT_DIGITAL  , System16InputPort2 + 3, "p2 fire 4" },

	{"Service"           , BIT_DIGITAL  , System16InputPort0 + 3 , "service"  },
	{"Diagnostics"       , BIT_DIGITAL  , System16InputPort0 + 2 , "diag"     },
	{"Reset"             , BIT_DIGITAL  , &System16Reset         , "reset"    },
	{"Dip 1"             , BIT_DIPSWITCH, System16Dip + 0        , "dip"      },
	{"Dip 2"             , BIT_DIPSWITCH, System16Dip + 1        , "dip"      },
};

STDINPUTINFO(System16bfire4);

static struct BurnInputInfo System16bDip3InputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , System16InputPort0 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , System16InputPort0 + 4, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL  , System16InputPort0 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , System16InputPort0 + 5, "p2 start"  },

	{"P1 Up"             , BIT_DIGITAL  , System16InputPort1 + 5, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , System16InputPort1 + 4, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , System16InputPort1 + 7, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , System16InputPort1 + 6, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , System16InputPort1 + 1, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL  , System16InputPort1 + 2, "p1 fire 2" },

	{"P2 Up"             , BIT_DIGITAL  , System16InputPort2 + 5, "p2 up"     },
	{"P2 Down"           , BIT_DIGITAL  , System16InputPort2 + 4, "p2 down"   },
	{"P2 Left"           , BIT_DIGITAL  , System16InputPort2 + 7, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL  , System16InputPort2 + 6, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , System16InputPort2 + 1, "p2 fire 1" },
	{"P2 Fire 2"         , BIT_DIGITAL  , System16InputPort2 + 2, "p2 fire 2" },

	{"Service"           , BIT_DIGITAL  , System16InputPort0 + 3 , "service"  },
	{"Diagnostics"       , BIT_DIGITAL  , System16InputPort0 + 2 , "diag"     },
	{"Reset"             , BIT_DIGITAL  , &System16Reset         , "reset"    },
	{"Dip 1"             , BIT_DIPSWITCH, System16Dip + 0        , "dip"      },
	{"Dip 2"             , BIT_DIPSWITCH, System16Dip + 1        , "dip"      },
	{"Dip 3"             , BIT_DIPSWITCH, System16Dip + 2        , "dip"      },
};

STDINPUTINFO(System16bDip3);

static struct BurnInputInfo BulletInputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , System16InputPort0 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , System16InputPort0 + 4, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL  , System16InputPort0 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , System16InputPort0 + 5, "p2 start"  },
	{"Coin 3"            , BIT_DIGITAL  , System16InputPort0 + 7, "p3 coin"   },
	{"Start 3"           , BIT_DIGITAL  , System16InputPort0 + 6, "p3 start"  },

	{"P1 Up 1"           , BIT_DIGITAL  , System16InputPort1 + 1, "p1 up"     },
	{"P1 Down 1"         , BIT_DIGITAL  , System16InputPort1 + 0, "p1 down"   },
	{"P1 Left 1"         , BIT_DIGITAL  , System16InputPort1 + 3, "p1 left"   },
	{"P1 Right 1"        , BIT_DIGITAL  , System16InputPort1 + 2, "p1 right"  },
	{"P1 Up 2"           , BIT_DIGITAL  , System16InputPort1 + 5, "p1 up 2"   },
	{"P1 Down 2"         , BIT_DIGITAL  , System16InputPort1 + 4, "p1 down 2" },
	{"P1 Left 2"         , BIT_DIGITAL  , System16InputPort1 + 7, "p1 left 2" },
	{"P1 Right 2"        , BIT_DIGITAL  , System16InputPort1 + 6, "p1 right 2"},	

	{"P2 Up 1"           , BIT_DIGITAL  , System16InputPort2 + 1, "p2 up"     },
	{"P2 Down 1"         , BIT_DIGITAL  , System16InputPort2 + 0, "p2 down"   },
	{"P2 Left 1"         , BIT_DIGITAL  , System16InputPort2 + 3, "p2 left"   },
	{"P2 Right 1"        , BIT_DIGITAL  , System16InputPort2 + 2, "p2 right"  },
	{"P2 Up 2"           , BIT_DIGITAL  , System16InputPort2 + 5, "p2 up 2"   },
	{"P2 Down 2"         , BIT_DIGITAL  , System16InputPort2 + 4, "p2 down 2" },
	{"P2 Left 2"         , BIT_DIGITAL  , System16InputPort2 + 7, "p2 left 2" },
	{"P2 Right 2"        , BIT_DIGITAL  , System16InputPort2 + 6, "p2 right 2"},	
	
	{"P3 Up 1"           , BIT_DIGITAL  , System16InputPort3 + 1, "p3 up"     },
	{"P3 Down 1"         , BIT_DIGITAL  , System16InputPort3 + 0, "p3 down"   },
	{"P3 Left 1"         , BIT_DIGITAL  , System16InputPort3 + 3, "p3 left"   },
	{"P3 Right 1"        , BIT_DIGITAL  , System16InputPort3 + 2, "p3 right"  },
	{"P3 Up 2"           , BIT_DIGITAL  , System16InputPort3 + 5, "p3 up 2"   },
	{"P3 Down 2"         , BIT_DIGITAL  , System16InputPort3 + 4, "p3 down 2" },
	{"P3 Left 2"         , BIT_DIGITAL  , System16InputPort3 + 7, "p3 left 2" },
	{"P3 Right 2"        , BIT_DIGITAL  , System16InputPort3 + 6, "p3 right 2"},

	{"Service"           , BIT_DIGITAL  , System16InputPort0 + 3 , "service"  },
	{"Diagnostics"       , BIT_DIGITAL  , System16InputPort0 + 2 , "diag"     },
	{"Reset"             , BIT_DIGITAL  , &System16Reset         , "reset"    },
	{"Dip 1"             , BIT_DIPSWITCH, System16Dip + 0        , "dip"      },
	{"Dip 2"             , BIT_DIPSWITCH, System16Dip + 1        , "dip"      },
};

STDINPUTINFO(Bullet);

static struct BurnInputInfo DunkshotInputList[] = {
	{"Coin 1"            , BIT_DIGITAL   , System16InputPort0 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL   , System16InputPort0 + 4, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL   , System16InputPort0 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL   , System16InputPort0 + 5, "p2 start"  },
	{"Start 3"           , BIT_DIGITAL   , System16InputPort0 + 6, "p3 start"  },
	{"Start 4"           , BIT_DIGITAL   , System16InputPort0 + 7, "p4 start"  },

	{"P1 Up"             , BIT_DIGITAL   , System16InputPort2 + 2, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL   , System16InputPort2 + 3, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL   , System16InputPort2 + 0, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL   , System16InputPort2 + 1, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL   , System16InputPort1 + 0, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL   , System16InputPort1 + 1, "p1 fire 2" },

	{"P2 Up"             , BIT_DIGITAL   , System16InputPort2 + 6, "p2 up"     },
	{"P2 Down"           , BIT_DIGITAL   , System16InputPort2 + 7, "p2 down"   },
	{"P2 Left"           , BIT_DIGITAL   , System16InputPort2 + 4, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL   , System16InputPort2 + 5, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL   , System16InputPort1 + 2, "p2 fire 1" },
	{"P2 Fire 2"         , BIT_DIGITAL   , System16InputPort1 + 3, "p2 fire 2" },
	
	{"P3 Up"             , BIT_DIGITAL   , System16InputPort3 + 2, "p3 up"     },
	{"P3 Down"           , BIT_DIGITAL   , System16InputPort3 + 3, "p3 down"   },
	{"P3 Left"           , BIT_DIGITAL   , System16InputPort3 + 0, "p3 left"   },
	{"P3 Right"          , BIT_DIGITAL   , System16InputPort3 + 1, "p3 right"  },
	{"P3 Fire 1"         , BIT_DIGITAL   , System16InputPort1 + 4, "p3 fire 1" },
	{"P3 Fire 2"         , BIT_DIGITAL   , System16InputPort1 + 5, "p3 fire 2" },

	{"P4 Up"             , BIT_DIGITAL   , System16InputPort3 + 6, "p4 up"     },
	{"P4 Down"           , BIT_DIGITAL   , System16InputPort3 + 7, "p4 down"   },
	{"P4 Left"           , BIT_DIGITAL   , System16InputPort3 + 4, "p4 left"   },
	{"P4 Right"          , BIT_DIGITAL   , System16InputPort3 + 5, "p4 right"  },
	{"P4 Fire 1"         , BIT_DIGITAL   , System16InputPort1 + 6, "p4 fire 1" },
	{"P4 Fire 2"         , BIT_DIGITAL   , System16InputPort1 + 7, "p4 fire 2" },

	{"Service"           , BIT_DIGITAL   , System16InputPort0 + 3 , "service"  },
	{"Diagnostics"       , BIT_DIGITAL   , System16InputPort0 + 2 , "diag"     },
	{"Reset"             , BIT_DIGITAL   , &System16Reset         , "reset"    },
	{"Dip 1"             , BIT_DIPSWITCH , System16Dip + 0        , "dip"      },
	{"Dip 2"             , BIT_DIPSWITCH , System16Dip + 1        , "dip"      },
};

STDINPUTINFO(Dunkshot);

static struct BurnInputInfo HwchampInputList[] = {
	{"Coin 1"            , BIT_DIGITAL   , System16InputPort0 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL   , System16InputPort0 + 4, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL   , System16InputPort0 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL   , System16InputPort0 + 5, "p2 start"  },

	A("Left/Right"       , BIT_ANALOG_REL, &System16AnalogPort0,   "p1 x-axis"  ),
	A("Left"             , BIT_ANALOG_REL, &System16AnalogPort1,   "p1 fire 1"  ),
	A("Right"            , BIT_ANALOG_REL, &System16AnalogPort2,   "p1 fire 2"  ),
	
	{"Service"           , BIT_DIGITAL   , System16InputPort0 + 3 , "service"   },
	{"Diagnostics"       , BIT_DIGITAL   , System16InputPort0 + 2 , "diag"      },
	{"Reset"             , BIT_DIGITAL   , &System16Reset         , "reset"     },
	{"Dip 1"             , BIT_DIPSWITCH , System16Dip + 0        , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH , System16Dip + 1        , "dip"       },
};

STDINPUTINFO(Hwchamp);

static struct BurnInputInfo PassshtInputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , System16InputPort0 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , System16InputPort0 + 4, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL  , System16InputPort0 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , System16InputPort0 + 5, "p2 start"  },
	{"Start 3"           , BIT_DIGITAL  , System16InputPort0 + 6, "p3 start"  },
	{"Start 4"           , BIT_DIGITAL  , System16InputPort0 + 7, "p4 start"  },

	{"P1 Up"             , BIT_DIGITAL  , System16InputPort1 + 1, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , System16InputPort1 + 0, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , System16InputPort1 + 3, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , System16InputPort1 + 2, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , System16InputPort1 + 4, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL  , System16InputPort1 + 5, "p1 fire 2" },
	{"P1 Fire 3"         , BIT_DIGITAL  , System16InputPort1 + 6, "p1 fire 3" },
	{"P1 Fire 4"         , BIT_DIGITAL  , System16InputPort1 + 7, "p1 fire 4" },

	{"P2 Up"             , BIT_DIGITAL  , System16InputPort2 + 1, "p2 up"     },
	{"P2 Down"           , BIT_DIGITAL  , System16InputPort2 + 0, "p2 down"   },
	{"P2 Left"           , BIT_DIGITAL  , System16InputPort2 + 3, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL  , System16InputPort2 + 2, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , System16InputPort2 + 4, "p2 fire 1" },
	{"P2 Fire 2"         , BIT_DIGITAL  , System16InputPort2 + 5, "p2 fire 2" },
	{"P2 Fire 3"         , BIT_DIGITAL  , System16InputPort2 + 6, "p2 fire 3" },
	{"P2 Fire 4"         , BIT_DIGITAL  , System16InputPort2 + 7, "p2 fire 4" },
	
	{"P3 Up"             , BIT_DIGITAL  , System16InputPort3 + 1, "p3 up"     },
	{"P3 Down"           , BIT_DIGITAL  , System16InputPort3 + 0, "p3 down"   },
	{"P3 Left"           , BIT_DIGITAL  , System16InputPort3 + 3, "p3 left"   },
	{"P3 Right"          , BIT_DIGITAL  , System16InputPort3 + 2, "p3 right"  },
	{"P3 Fire 1"         , BIT_DIGITAL  , System16InputPort3 + 4, "p3 fire 1" },
	{"P3 Fire 2"         , BIT_DIGITAL  , System16InputPort3 + 5, "p3 fire 2" },
	{"P3 Fire 3"         , BIT_DIGITAL  , System16InputPort3 + 6, "p3 fire 3" },
	{"P3 Fire 4"         , BIT_DIGITAL  , System16InputPort3 + 7, "p3 fire 4" },

	{"P4 Up"             , BIT_DIGITAL  , System16InputPort4 + 1, "p4 up"     },
	{"P4 Down"           , BIT_DIGITAL  , System16InputPort4 + 0, "p4 down"   },
	{"P4 Left"           , BIT_DIGITAL  , System16InputPort4 + 3, "p4 left"   },
	{"P4 Right"          , BIT_DIGITAL  , System16InputPort4 + 2, "p4 right"  },
	{"P4 Fire 1"         , BIT_DIGITAL  , System16InputPort4 + 4, "p4 fire 1" },
	{"P4 Fire 2"         , BIT_DIGITAL  , System16InputPort4 + 5, "p4 fire 2" },
	{"P4 Fire 3"         , BIT_DIGITAL  , System16InputPort4 + 6, "p4 fire 3" },
	{"P4 Fire 4"         , BIT_DIGITAL  , System16InputPort4 + 7, "p4 fire 4" },

	{"Service"           , BIT_DIGITAL  , System16InputPort0 + 3 , "service"  },
	{"Diagnostics"       , BIT_DIGITAL  , System16InputPort0 + 2 , "diag"     },
	{"Reset"             , BIT_DIGITAL  , &System16Reset         , "reset"    },
	{"Dip 1"             , BIT_DIPSWITCH, System16Dip + 0        , "dip"      },
	{"Dip 2"             , BIT_DIPSWITCH, System16Dip + 1        , "dip"      },
};

STDINPUTINFO(Passsht);

static struct BurnInputInfo RyukyuInputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , System16InputPort0 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , System16InputPort0 + 4, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL  , System16InputPort0 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , System16InputPort0 + 5, "p2 start"  },
	
	{"P1 Up"             , BIT_DIGITAL  , System16InputPort1 + 5, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , System16InputPort1 + 4, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , System16InputPort1 + 7, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , System16InputPort1 + 6, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , System16InputPort1 + 1, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL  , System16InputPort1 + 2, "p1 fire 2" },

	{"Service"           , BIT_DIGITAL  , System16InputPort0 + 3 , "service"  },
	{"Diagnostics"       , BIT_DIGITAL  , System16InputPort0 + 2 , "diag"     },
	{"Reset"             , BIT_DIGITAL  , &System16Reset         , "reset"    },
	{"Dip 1"             , BIT_DIPSWITCH, System16Dip + 0        , "dip"      },
	{"Dip 2"             , BIT_DIPSWITCH, System16Dip + 1        , "dip"      },
};

STDINPUTINFO(Ryukyu);

static struct BurnInputInfo SdiInputList[] = {
	{"Coin 1"            , BIT_DIGITAL   , System16InputPort0 + 0, "p1 coin"      },
	{"Start 1"           , BIT_DIGITAL   , System16InputPort0 + 4, "p1 start"     },
	{"Coin 2"            , BIT_DIGITAL   , System16InputPort0 + 1, "p2 coin"      },
	{"Start 2"           , BIT_DIGITAL   , System16InputPort0 + 5, "p2 start"     },

	{"P1 Up"             , BIT_DIGITAL   , System16InputPort1 + 1, "p1 up"        },
	{"P1 Down"           , BIT_DIGITAL   , System16InputPort1 + 0, "p1 down"      },
	{"P1 Left"           , BIT_DIGITAL   , System16InputPort1 + 3, "p1 left"      },
	{"P1 Right"          , BIT_DIGITAL   , System16InputPort1 + 2, "p1 right"     },
	A("Target Left/Right", BIT_ANALOG_REL, &System16AnalogPort0,   "mouse x-axis" ),
	A("Target Up/Down"   , BIT_ANALOG_REL, &System16AnalogPort1,   "mouse y-axis" ),
	{"P1 Fire 1"         , BIT_DIGITAL   , System16InputPort0 + 6, "mouse button 1"},

	{"P2 Up"             , BIT_DIGITAL   , System16InputPort1 + 5, "p2 up"        },
	{"P2 Down"           , BIT_DIGITAL   , System16InputPort1 + 4, "p2 down"      },
	{"P2 Left"           , BIT_DIGITAL   , System16InputPort1 + 7, "p2 left"      },
	{"P2 Right"          , BIT_DIGITAL   , System16InputPort1 + 6, "p2 right"     },
	A("Target Left/Right", BIT_ANALOG_REL, &System16AnalogPort2,   "p2 x-axis"    ),
	A("Target Up/Down"   , BIT_ANALOG_REL, &System16AnalogPort3,   "p2 y-axis"    ),
	{"P2 Fire 1"         , BIT_DIGITAL   , System16InputPort0 + 7, "p2 fire 1"    },

	{"Service"           , BIT_DIGITAL  , System16InputPort0 + 3 , "service"      },
	{"Diagnostics"       , BIT_DIGITAL  , System16InputPort0 + 2 , "diag"         },
	{"Reset"             , BIT_DIGITAL  , &System16Reset         , "reset"        },
	{"Dip 1"             , BIT_DIPSWITCH, System16Dip + 0        , "dip"          },
	{"Dip 2"             , BIT_DIPSWITCH, System16Dip + 1        , "dip"          },
};

STDINPUTINFO(Sdi);

static struct BurnInputInfo SjryukoInputList[] = {
	{"Coin 1"             , BIT_DIGITAL  , System16InputPort0 + 0, "p1 coin"   },
	{"Coin 2"             , BIT_DIGITAL  , System16InputPort0 + 1, "p2 coin"   },
	
	{"Mahjong A"          , BIT_DIGITAL  , System16InputPort1 + 0, "mah a"     },
	{"Mahjong B"          , BIT_DIGITAL  , System16InputPort1 + 1, "mah b"     },
	{"Mahjong C"          , BIT_DIGITAL  , System16InputPort1 + 2, "mah c"     },
	{"Mahjong D"          , BIT_DIGITAL  , System16InputPort1 + 3, "mah d"     },
	{"Mahjong E"          , BIT_DIGITAL  , System16InputPort2 + 0, "mah e"     },
	{"Mahjong F"          , BIT_DIGITAL  , System16InputPort2 + 1, "mah f"     },
	{"Mahjong G"          , BIT_DIGITAL  , System16InputPort2 + 2, "mah g"     },
	{"Mahjong H"          , BIT_DIGITAL  , System16InputPort2 + 3, "mah h"     },
	{"Mahjong I"          , BIT_DIGITAL  , System16InputPort3 + 0, "mah i"     },
	{"Mahjong J"          , BIT_DIGITAL  , System16InputPort3 + 1, "mah j"     },
	{"Mahjong K"          , BIT_DIGITAL  , System16InputPort3 + 2, "mah k"     },
	{"Mahjong L"          , BIT_DIGITAL  , System16InputPort3 + 3, "mah l"     },
	{"Mahjong M"          , BIT_DIGITAL  , System16InputPort4 + 0, "mah m"     },
	{"Mahjong N"          , BIT_DIGITAL  , System16InputPort4 + 1, "mah n"     },
	{"Mahjong Kan"        , BIT_DIGITAL  , System16InputPort6 + 0, "mah kan"   },
	{"Mahjong Pon"        , BIT_DIGITAL  , System16InputPort4 + 3, "mah pon"   },
	{"Mahjong Chi"        , BIT_DIGITAL  , System16InputPort4 + 2, "mah chi"   },
	{"Mahjong Reach"      , BIT_DIGITAL  , System16InputPort6 + 1, "mah reach" },
	{"Mahjong Ron"        , BIT_DIGITAL  , System16InputPort6 + 2, "mah ron"   },
	{"Mahjong Bet"        , BIT_DIGITAL  , System16InputPort5 + 1, "mah bet"   },
	{"Mahjong Last Chance", BIT_DIGITAL  , System16InputPort1 + 4, "mah lc"    },
	{"Mahjong Score"      , BIT_DIGITAL  , System16InputPort5 + 0, "mah score" },
	{"Mahjong Flip Flop"  , BIT_DIGITAL  , System16InputPort4 + 4, "mah ff"    },
		
	{"Service"           , BIT_DIGITAL  , System16InputPort0 + 3 , "service"   },
	{"Diagnostics"       , BIT_DIGITAL  , System16InputPort0 + 2 , "diag"      },
	{"Reset"             , BIT_DIGITAL  , &System16Reset         , "reset"     },
	{"Dip 1"             , BIT_DIPSWITCH, System16Dip + 0        , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH, System16Dip + 1        , "dip"       },
};

STDINPUTINFO(Sjryuko);

#undef A

/*====================================================
Dip defs
====================================================*/

#define SYSTEM16B_COINAGE(dipval)								\
	{0   , 0xfe, 0   , 16  , "Coin A"                               },			\
	{dipval, 0x01, 0x0f, 0x07, "4 Coins 1 Credit"                   },			\
	{dipval, 0x01, 0x0f, 0x08, "3 Coins 1 Credit"                   },			\
	{dipval, 0x01, 0x0f, 0x09, "2 Coins 1 Credit"                   },			\
	{dipval, 0x01, 0x0f, 0x05, "2 Coins 1 Credit 5/3 6/4"           },			\
	{dipval, 0x01, 0x0f, 0x04, "2 Coins 1 Credit 4/3"               },			\
	{dipval, 0x01, 0x0f, 0x0f, "1 Coin  1 Credit"                   },			\
	{dipval, 0x01, 0x0f, 0x01, "1 Coin  1 Credit 2/3"               },			\
	{dipval, 0x01, 0x0f, 0x02, "1 Coin  1 Credit 4/5"               },			\
	{dipval, 0x01, 0x0f, 0x03, "1 Coin  1 Credit 5/6"               },			\
	{dipval, 0x01, 0x0f, 0x06, "2 Coins 3 Credits"                  },			\
	{dipval, 0x01, 0x0f, 0x0e, "1 Coin  2 Credits"                  },			\
	{dipval, 0x01, 0x0f, 0x0d, "1 Coin  3 Credits"                  },			\
	{dipval, 0x01, 0x0f, 0x0c, "1 Coin  4 Credits"                  },			\
	{dipval, 0x01, 0x0f, 0x0b, "1 Coin  5 Credits"                  },			\
	{dipval, 0x01, 0x0f, 0x0a, "1 Coin  6 Credits"                  },			\
	{dipval, 0x01, 0x0f, 0x00, "Free Play (if coin B too) or 1C/1C" },			\
												\
	{0   , 0xfe, 0   , 16  , "Coin B"                               },			\
	{dipval, 0x01, 0xf0, 0x70, "4 Coins 1 Credit"                   },			\
	{dipval, 0x01, 0xf0, 0x80, "3 Coins 1 Credit"                   },			\
	{dipval, 0x01, 0xf0, 0x90, "2 Coins 1 Credit"                   },			\
	{dipval, 0x01, 0xf0, 0x50, "2 Coins 1 Credit 5/3 6/4"           },			\
	{dipval, 0x01, 0xf0, 0x40, "2 Coins 1 Credit 4/3"               },			\
	{dipval, 0x01, 0xf0, 0xf0, "1 Coin  1 Credit"                   },			\
	{dipval, 0x01, 0xf0, 0x10, "1 Coin  1 Credit 2/3"               },			\
	{dipval, 0x01, 0xf0, 0x20, "1 Coin  1 Credit 4/5"               },			\
	{dipval, 0x01, 0xf0, 0x30, "1 Coin  1 Credit 5/6"               },			\
	{dipval, 0x01, 0xf0, 0x60, "2 Coins 3 Credits"                  },			\
	{dipval, 0x01, 0xf0, 0xe0, "1 Coin  2 Credits"                  },			\
	{dipval, 0x01, 0xf0, 0xd0, "1 Coin  3 Credits"                  },			\
	{dipval, 0x01, 0xf0, 0xc0, "1 Coin  4 Credits"                  },			\
	{dipval, 0x01, 0xf0, 0xb0, "1 Coin  5 Credits"                  },			\
	{dipval, 0x01, 0xf0, 0xa0, "1 Coin  6 Credits"                  },			\
	{dipval, 0x01, 0xf0, 0x00, "Free Play (if coin A too) or 1C/1C" },

static struct BurnDIPInfo AliensynDIPList[]=
{
	// Default Values
	{0x11, 0xff, 0xff, 0xfd, NULL                                 },
	{0x12, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x11, 0x01, 0x02, 0x02, "Off"                                },
	{0x11, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x11, 0x01, 0x0c, 0x08, "2"                                  },
	{0x11, 0x01, 0x0c, 0x0c, "3"                                  },
	{0x11, 0x01, 0x0c, 0x04, "4"                                  },
	{0x11, 0x01, 0x0c, 0x00, "127"                                },
	
	{0   , 0xfe, 0   , 4   , "Timer"                              },
	{0x11, 0x01, 0x30, 0x00, "120"                                },
	{0x11, 0x01, 0x30, 0x10, "130"                                },
	{0x11, 0x01, 0x30, 0x20, "140"                                },
	{0x11, 0x01, 0x30, 0x30, "150"                                },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x11, 0x01, 0xc0, 0x80, "Easy"                               },
	{0x11, 0x01, 0xc0, 0xc0, "Normal"                             },
	{0x11, 0x01, 0xc0, 0x40, "Hard"                               },
	{0x11, 0x01, 0xc0, 0x00, "Hardest"                            },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x12)
};

STDDIPINFO(Aliensyn);

static struct BurnDIPInfo AltbeastDIPList[]=
{
	// Default Values
	{0x15, 0xff, 0xff, 0xfd, NULL                                 },
	{0x16, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Credits needed"                     },
	{0x15, 0x01, 0x01, 0x01, "1 to start, 1 to continue"          },
	{0x15, 0x01, 0x01, 0x00, "2 to start, 1 to continue"          },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x15, 0x01, 0x02, 0x02, "Off"                                },
	{0x15, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x15, 0x01, 0x0c, 0x08, "2"                                  },
	{0x15, 0x01, 0x0c, 0x0c, "3"                                  },
	{0x15, 0x01, 0x0c, 0x04, "4"                                  },
	{0x15, 0x01, 0x0c, 0x00, "240"                                },
	
	{0   , 0xfe, 0   , 4   , "Energy Meter"                       },
	{0x15, 0x01, 0x30, 0x20, "2"                                  },
	{0x15, 0x01, 0x30, 0x30, "3"                                  },
	{0x15, 0x01, 0x30, 0x10, "4"                                  },
	{0x15, 0x01, 0x30, 0x00, "5"                                  },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x15, 0x01, 0xc0, 0x80, "Easy"                               },
	{0x15, 0x01, 0xc0, 0xc0, "Normal"                             },
	{0x15, 0x01, 0xc0, 0x40, "Hard"                               },
	{0x15, 0x01, 0xc0, 0x00, "Hardest"                            },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x16)
};

STDDIPINFO(Altbeast);

static struct BurnDIPInfo AurailDIPList[]=
{
	// Default Values
	{0x15, 0xff, 0xff, 0xfd, NULL                                 },
	{0x16, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Cabinet"                            },
	{0x15, 0x01, 0x01, 0x01, "Upright"                            },
	{0x15, 0x01, 0x01, 0x00, "Cocktail"                           },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x15, 0x01, 0x02, 0x02, "Off"                                },
	{0x15, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x15, 0x01, 0x0c, 0x00, "2"                                  },
	{0x15, 0x01, 0x0c, 0x0c, "3"                                  },
	{0x15, 0x01, 0x0c, 0x08, "4"                                  },
	{0x15, 0x01, 0x0c, 0x04, "5"                                  },
	
	{0   , 0xfe, 0   , 2   , "Bonus Life"                         },
	{0x15, 0x01, 0x10, 0x10, "80k, 200k, 500k, 1000k"             },
	{0x15, 0x01, 0x10, 0x00, "100k, 300k, 700k, 1000k"            },
	
	{0   , 0xfe, 0   , 2   , "Difficulty"                         },
	{0x15, 0x01, 0x20, 0x20, "Normal"                             },
	{0x15, 0x01, 0x20, 0x00, "Hard"                               },
	
	{0   , 0xfe, 0   , 2   , "Controller Select"                  },
	{0x15, 0x01, 0x40, 0x40, "1 Player Side"                      },
	{0x15, 0x01, 0x40, 0x00, "2 Players Side"                     },
	
	{0   , 0xfe, 0   , 2   , "Special Function Mode"              },
	{0x15, 0x01, 0x80, 0x80, "Off"                                },
	{0x15, 0x01, 0x80, 0x00, "On"                                 },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x16)
};

STDDIPINFO(Aurail);

static struct BurnDIPInfo BayrouteDIPList[]=
{
	// Default Values
	{0x15, 0xff, 0xff, 0xfd, NULL                                 },
	{0x16, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Allow Continue"                     },
	{0x15, 0x01, 0x01, 0x00, "Off"                                },
	{0x15, 0x01, 0x01, 0x01, "On"                                 },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x15, 0x01, 0x02, 0x02, "Off"                                },
	{0x15, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x15, 0x01, 0x0c, 0x04, "1"                                  },
	{0x15, 0x01, 0x0c, 0x0c, "3"                                  },
	{0x15, 0x01, 0x0c, 0x08, "5"                                  },
	{0x15, 0x01, 0x0c, 0x00, "Unlimited"                          },
	
	{0   , 0xfe, 0   , 4   , "Bonus Life"                         },
	{0x15, 0x01, 0x30, 0x30, "100000"                             },
	{0x15, 0x01, 0x30, 0x20, "150000"                             },
	{0x15, 0x01, 0x30, 0x10, "200000"                             },
	{0x15, 0x01, 0x30, 0x00, "None"                               },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x15, 0x01, 0xc0, 0xc0, "Easy"                               },
	{0x15, 0x01, 0xc0, 0x80, "Normal"                             },
	{0x15, 0x01, 0xc0, 0x40, "Hard"                               },
	{0x15, 0x01, 0xc0, 0x00, "Hardest"                            },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x16)
};

STDDIPINFO(Bayroute);

static struct BurnDIPInfo BulletDIPList[]=
{
	// Default Values
	{0x21, 0xff, 0xff, 0xff, NULL                                 },
	{0x22, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	
	// Dip 2
	SYSTEM16B_COINAGE(0x22)
};

STDDIPINFO(Bullet);

static struct BurnDIPInfo CottonDIPList[]=
{
	// Default Values
	{0x13, 0xff, 0xff, 0xfe, NULL                                 },
	{0x14, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x13, 0x01, 0x01, 0x01, "Off"                                },
	{0x13, 0x01, 0x01, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x13, 0x01, 0x06, 0x04, "2"                                  },
	{0x13, 0x01, 0x06, 0x06, "3"                                  },
	{0x13, 0x01, 0x06, 0x02, "4"                                  },
	{0x13, 0x01, 0x06, 0x00, "5"                                  },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x13, 0x01, 0x18, 0x10, "Easy"                               },
	{0x13, 0x01, 0x18, 0x18, "Normal"                             },
	{0x13, 0x01, 0x18, 0x08, "Hard"                               },
	{0x13, 0x01, 0x18, 0x00, "Hardest"                            },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x14)
};

STDDIPINFO(Cotton);

static struct BurnDIPInfo DduxDIPList[]=
{
	// Default Values
	{0x13, 0xff, 0xff, 0xfe, NULL                                 },
	{0x14, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x13, 0x01, 0x01, 0x01, "Off"                                },
	{0x13, 0x01, 0x01, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x13, 0x01, 0x06, 0x04, "Easy"                               },
	{0x13, 0x01, 0x06, 0x06, "Normal"                             },
	{0x13, 0x01, 0x06, 0x02, "Hard"                               },
	{0x13, 0x01, 0x06, 0x00, "Hardest"                            },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x13, 0x01, 0x18, 0x10, "2"                                  },
	{0x13, 0x01, 0x18, 0x18, "3"                                  },
	{0x13, 0x01, 0x18, 0x08, "4"                                  },
	{0x13, 0x01, 0x18, 0x00, "5"                                  },
	
	{0   , 0xfe, 0   , 4   , "Bonus Life"                         },
	{0x13, 0x01, 0x60, 0x40, "150000"                             },
	{0x13, 0x01, 0x60, 0x60, "200000"                             },
	{0x13, 0x01, 0x60, 0x20, "300000"                             },
	{0x13, 0x01, 0x60, 0x00, "400000"                             },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x14)
};

STDDIPINFO(Ddux);

static struct BurnDIPInfo DunkshotDIPList[]=
{
	// Default Values
	{0x21, 0xff, 0xff, 0xfd, NULL                                 },
	{0x22, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x21, 0x01, 0x02, 0x02, "Off"                                },
	{0x21, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "VS Time"                            },
	{0x21, 0x01, 0x0c, 0x08, "2P 1:30 | 3P 2:00 | 4P 2:30"        },
	{0x21, 0x01, 0x0c, 0x0c, "2P 2:00 | 3P 2:30 | 4P 3:00"        },
	{0x21, 0x01, 0x0c, 0x04, "2P 2:30 | 3P 3:00 | 4P 3:30"        },
	{0x21, 0x01, 0x0c, 0x00, "2P 3:00 | 3P 3:30 | 4P 4:00"        },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x21, 0x01, 0x30, 0x20, "Easy"                               },
	{0x21, 0x01, 0x30, 0x30, "Normal"                             },
	{0x21, 0x01, 0x30, 0x10, "Hard"                               },
	{0x21, 0x01, 0x30, 0x00, "Hardest"                            },
	
	{0   , 0xfe, 0   , 2   , "CPU starts with +6 pts"             },
	{0x21, 0x01, 0x40, 0x40, "Off"                                },
	{0x21, 0x01, 0x40, 0x00, "On"                                 },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x22)
};

STDDIPINFO(Dunkshot);

static struct BurnDIPInfo EswatDIPList[]=
{
	// Default Values
	{0x15, 0xff, 0xff, 0xfd, NULL                                 },
	{0x16, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "2 Credits to Start"                 },
	{0x15, 0x01, 0x01, 0x01, "Off"                                },
	{0x15, 0x01, 0x01, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x15, 0x01, 0x02, 0x02, "Off"                                },
	{0x15, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 2   , "Flip Screen"                        },
	{0x15, 0x01, 0x04, 0x04, "Off"                                },
	{0x15, 0x01, 0x04, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 2   , "Time"                               },
	{0x15, 0x01, 0x08, 0x08, "Normal"                             },
	{0x15, 0x01, 0x08, 0x00, "Hard"                               },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x15, 0x01, 0x30, 0x20, "Easy"                               },
	{0x15, 0x01, 0x30, 0x30, "Normal"                             },
	{0x15, 0x01, 0x30, 0x10, "Hard"                               },
	{0x15, 0x01, 0x30, 0x00, "Hardest"                            },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x15, 0x01, 0xc0, 0x00, "1"                                  },
	{0x15, 0x01, 0xc0, 0x40, "2"                                  },
	{0x15, 0x01, 0xc0, 0xc0, "3"                                  },
	{0x15, 0x01, 0xc0, 0x80, "4"                                  },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x16)
};

STDDIPINFO(Eswat);

static struct BurnDIPInfo FpointDIPList[]=
{
	// Default Values
	{0x11, 0xff, 0xff, 0xfd, NULL                                 },
	{0x12, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x11, 0x01, 0x02, 0x02, "Off"                                },
	{0x11, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x11, 0x01, 0x30, 0x20, "Easy"                               },
	{0x11, 0x01, 0x30, 0x30, "Normal"                             },
	{0x11, 0x01, 0x30, 0x10, "Hard"                               },
	{0x11, 0x01, 0x30, 0x00, "Hardest"                            },

	{0   , 0xfe, 0   , 2   , "Clear Round Allowed"                },
	{0x11, 0x01, 0x40, 0x00, "1"                                  },
	{0x11, 0x01, 0x40, 0x40, "2"                                  },
	
	{0   , 0xfe, 0   , 2   , "Cell Move"                          },
	{0x11, 0x01, 0x80, 0x00, "Off"                                },
	{0x11, 0x01, 0x80, 0x80, "On"                                 },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x12)
};

STDDIPINFO(Fpoint);

static struct BurnDIPInfo GoldnaxeDIPList[]=
{
	// Default Values
	{0x15, 0xff, 0xff, 0xfd, NULL                                 },
	{0x16, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Credits needed"                     },
	{0x15, 0x01, 0x01, 0x01, "1 to start, 1 to continue"          },
	{0x15, 0x01, 0x01, 0x00, "2 to start, 1 to continue"          },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x15, 0x01, 0x02, 0x02, "Off"                                },
	{0x15, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x15, 0x01, 0x0c, 0x08, "1"                                  },
	{0x15, 0x01, 0x0c, 0x0c, "2"                                  },
	{0x15, 0x01, 0x0c, 0x04, "3"                                  },
	{0x15, 0x01, 0x0c, 0x00, "5"                                  },
	
	{0   , 0xfe, 0   , 4   , "Energy Meter"                       },
	{0x15, 0x01, 0x30, 0x20, "2"                                  },
	{0x15, 0x01, 0x30, 0x30, "3"                                  },
	{0x15, 0x01, 0x30, 0x10, "4"                                  },
	{0x15, 0x01, 0x30, 0x00, "5"                                  },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x16)
};

STDDIPINFO(Goldnaxe);

static struct BurnDIPInfo HwchampDIPList[]=
{
	// Default Values
	{0x0a, 0xff, 0xff, 0xf9, NULL                                 },
	{0x0b, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x0a, 0x01, 0x02, 0x02, "Off"                                },
	{0x0a, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 2   , "Start Level Select"                 },
	{0x0a, 0x01, 0x04, 0x04, "Off"                                },
	{0x0a, 0x01, 0x04, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 2   , "Allow Continue"                     },
	{0x0a, 0x01, 0x08, 0x08, "Off"                                },
	{0x0a, 0x01, 0x08, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x0a, 0x01, 0x30, 0x20, "Easy"                               },
	{0x0a, 0x01, 0x30, 0x30, "Normal"                             },
	{0x0a, 0x01, 0x30, 0x10, "Hard"                               },
	{0x0a, 0x01, 0x30, 0x00, "Hardest"                            },
	
	{0   , 0xfe, 0   , 4   , "Time Adjust"                        },
	{0x0a, 0x01, 0xc0, 0x80, "Easy"                               },
	{0x0a, 0x01, 0xc0, 0xc0, "Normal"                             },
	{0x0a, 0x01, 0xc0, 0x40, "Hard"                               },
	{0x0a, 0x01, 0xc0, 0x00, "Hardest"                            },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x0b)
};

STDDIPINFO(Hwchamp);

static struct BurnDIPInfo MvpDIPList[]=
{
	// Default Values
	{0x15, 0xff, 0xff, 0xfd, NULL                                 },
	{0x16, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Credits Needed"                     },
	{0x15, 0x01, 0x01, 0x01, "1 to start, 1 to continue"          },
	{0x15, 0x01, 0x01, 0x00, "2 to start, 1 to continue"          },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x15, 0x01, 0x02, 0x02, "Off"                                },
	{0x15, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 2   , "Innings"                            },
	{0x15, 0x01, 0x04, 0x04, "1 Credit 1 Inning Only"             },
	{0x15, 0x01, 0x04, 0x0c, "+2 Credits 3 Innings"               },
	
	{0   , 0xfe, 0   , 8   , "Time Limits"                        },
	{0x15, 0x01, 0x38, 0x18, "Easy"                               },
	{0x15, 0x01, 0x38, 0x28, "Easy 2"                             },
	{0x15, 0x01, 0x38, 0x08, "Easy 3"                             },
	{0x15, 0x01, 0x38, 0x38, "Normal"                             },
	{0x15, 0x01, 0x38, 0x30, "Hard"                               },
	{0x15, 0x01, 0x38, 0x10, "Hard 2"                             },
	{0x15, 0x01, 0x38, 0x20, "Hard 3"                             },
	{0x15, 0x01, 0x38, 0x00, "Hardest"                            },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x15, 0x01, 0xc0, 0x80, "Easy"                               },
	{0x15, 0x01, 0xc0, 0x40, "Easy 2"                             },
	{0x15, 0x01, 0xc0, 0xc0, "Normal"                             },
	{0x15, 0x01, 0xc0, 0x30, "Hard"                               },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x16)
};

STDDIPINFO(Mvp);

static struct BurnDIPInfo PassshtDIPList[]=
{
	// Default Values
	{0x17, 0xff, 0xff, 0xf0, NULL                                 },
	{0x18, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x17, 0x01, 0x01, 0x01, "Off"                                },
	{0x17, 0x01, 0x01, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 8   , "Initial Point"                      },
	{0x17, 0x01, 0x0e, 0x06, "2000"                               },
	{0x17, 0x01, 0x0e, 0x0a, "3000"                               },
	{0x17, 0x01, 0x0e, 0x0c, "4000"                               },
	{0x17, 0x01, 0x0e, 0x0e, "5000"                               },
	{0x17, 0x01, 0x0e, 0x08, "6000"                               },
	{0x17, 0x01, 0x0e, 0x04, "7000"                               },
	{0x17, 0x01, 0x0e, 0x02, "8000"                               },
	{0x17, 0x01, 0x0e, 0x00, "9000"                               },
	
	{0   , 0xfe, 0   , 4   , "Point Table"                        },
	{0x17, 0x01, 0x30, 0x20, "Easy"                               },
	{0x17, 0x01, 0x30, 0x30, "Normal"                             },
	{0x17, 0x01, 0x30, 0x10, "Hard"                               },
	{0x17, 0x01, 0x30, 0x00, "Hardest"                            },	
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x17, 0x01, 0xc0, 0x80, "Easy"                               },
	{0x17, 0x01, 0xc0, 0xc0, "Normal"                             },
	{0x17, 0x01, 0xc0, 0x40, "Hard"                               },
	{0x17, 0x01, 0xc0, 0x00, "Hardest"                            },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x18)
};

STDDIPINFO(Passsht);


static struct BurnDIPInfo PassshtaDIPList[]=
{
	// Default Values
	{0x29, 0xff, 0xff, 0xf0, NULL                                 },
	{0x2a, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x29, 0x01, 0x01, 0x01, "Off"                                },
	{0x29, 0x01, 0x01, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 8   , "Initial Point"                      },
	{0x29, 0x01, 0x0e, 0x06, "2000"                               },
	{0x29, 0x01, 0x0e, 0x0a, "3000"                               },
	{0x29, 0x01, 0x0e, 0x0c, "4000"                               },
	{0x29, 0x01, 0x0e, 0x0e, "5000"                               },
	{0x29, 0x01, 0x0e, 0x08, "6000"                               },
	{0x29, 0x01, 0x0e, 0x04, "7000"                               },
	{0x29, 0x01, 0x0e, 0x02, "8000"                               },
	{0x29, 0x01, 0x0e, 0x00, "9000"                               },
	
	{0   , 0xfe, 0   , 4   , "Point Table"                        },
	{0x29, 0x01, 0x30, 0x20, "Easy"                               },
	{0x29, 0x01, 0x30, 0x30, "Normal"                             },
	{0x29, 0x01, 0x30, 0x10, "Hard"                               },
	{0x29, 0x01, 0x30, 0x00, "Hardest"                            },	
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x29, 0x01, 0xc0, 0x80, "Easy"                               },
	{0x29, 0x01, 0xc0, 0xc0, "Normal"                             },
	{0x29, 0x01, 0xc0, 0x40, "Hard"                               },
	{0x29, 0x01, 0xc0, 0x00, "Hardest"                            },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x2a)
};

STDDIPINFO(Passshta);

static struct BurnDIPInfo RiotcityDIPList[]=
{
	// Default Values
	{0x13, 0xff, 0xff, 0xfd, NULL                                 },
	{0x14, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "2 Credits to Start"                 },
	{0x13, 0x01, 0x01, 0x01, "Off"                                },
	{0x13, 0x01, 0x01, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x13, 0x01, 0x02, 0x02, "Off"                                },
	{0x13, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x13, 0x01, 0x0c, 0x00, "1"                                  },
	{0x13, 0x01, 0x0c, 0x0c, "2"                                  },
	{0x13, 0x01, 0x0c, 0x08, "3"                                  },
	{0x13, 0x01, 0x0c, 0x04, "4"                                  },
	
	{0   , 0xfe, 0   , 4   , "Bonus Life"                         },
	{0x13, 0x01, 0x30, 0x20, "Easy"                               },
	{0x13, 0x01, 0x30, 0x30, "Normal"                             },
	{0x13, 0x01, 0x30, 0x10, "Hard"                               },
	{0x13, 0x01, 0x30, 0x00, "Hardest"                            },
	
	{0   , 0xfe, 0   , 2   , "Difficulty"                         },
	{0x13, 0x01, 0x40, 0x40, "Normal"                             },
	{0x13, 0x01, 0x40, 0x00, "Hard"                               },
	
	{0   , 0xfe, 0   , 2   , "Attack button to start"             },
	{0x13, 0x01, 0x80, 0x80, "Off"                                },
	{0x13, 0x01, 0x80, 0x00, "On"                                 },
		
	// Dip 2
	SYSTEM16B_COINAGE(0x14)
};

STDDIPINFO(Riotcity);

static struct BurnDIPInfo RyukyuDIPList[]=
{
	// Default Values
	{0x0d, 0xff, 0xff, 0xf8, NULL                                 },
	{0x0e, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x0d, 0x01, 0x01, 0x01, "Off"                                },
	{0x0d, 0x01, 0x01, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 2   , "Cancel per credit"                  },
	{0x0d, 0x01, 0x02, 0x00, "2"                                  },
	{0x0d, 0x01, 0x02, 0x02, "3"                                  },
	
	{0   , 0xfe, 0   , 2   , "Timer Speed"                        },
	{0x0d, 0x01, 0x04, 0x04, "20 seconds"                         },
	{0x0d, 0x01, 0x04, 0x00, "30 seconds"                         },
	
	{0   , 0xfe, 0   , 2   , "PCM Voice"                          },
	{0x0d, 0x01, 0x08, 0x00, "Off"                                },
	{0x0d, 0x01, 0x08, 0x08, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Omikuji Difficulty"                 },
	{0x0d, 0x01, 0x30, 0x20, "Easy"                               },
	{0x0d, 0x01, 0x30, 0x30, "Normal"                             },
	{0x0d, 0x01, 0x30, 0x10, "Hard"                               },
	{0x0d, 0x01, 0x30, 0x00, "Hardest"                            },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x0d, 0x01, 0xc0, 0x80, "Easy"                               },
	{0x0d, 0x01, 0xc0, 0xc0, "Normal"                             },
	{0x0d, 0x01, 0xc0, 0x40, "Hard"                               },
	{0x0d, 0x01, 0xc0, 0x00, "Hardest"                            },
		
	// Dip 2
	SYSTEM16B_COINAGE(0x0e)
};

STDDIPINFO(Ryukyu);

static struct BurnDIPInfo SdibDIPList[]=
{
	// Default Values
	{0x15, 0xff, 0xff, 0xfd, NULL                                 },
	{0x16, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Allow Continue"                     },
	{0x15, 0x01, 0x01, 0x01, "No"                                 },
	{0x15, 0x01, 0x01, 0x00, "Yes"                                },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x15, 0x01, 0x02, 0x02, "Off"                                },
	{0x15, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x15, 0x01, 0x0c, 0x08, "2"                                  },
	{0x15, 0x01, 0x0c, 0x0c, "3"                                  },
	{0x15, 0x01, 0x0c, 0x04, "4"                                  },
	{0x15, 0x01, 0x0c, 0x00, "Free"                               },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x15, 0x01, 0x30, 0x20, "Easy"                               },
	{0x15, 0x01, 0x30, 0x30, "Normal"                             },
	{0x15, 0x01, 0x30, 0x10, "Hard"                               },
	{0x15, 0x01, 0x30, 0x00, "Hardest"                            },
	
	{0   , 0xfe, 0   , 4   , "Bonus Life"                         },
	{0x15, 0x01, 0xc0, 0x80, "Every 50000"                        },
	{0x15, 0x01, 0xc0, 0xc0, "50000"                              },
	{0x15, 0x01, 0xc0, 0x40, "100000"                             },
	{0x15, 0x01, 0xc0, 0x00, "None"                               },
	
	// Dip 1
	SYSTEM16B_COINAGE(0x16)
};

STDDIPINFO(Sdib);

static struct BurnDIPInfo ShinobiDIPList[]=
{
	// Default Values
	{0x15, 0xff, 0xff, 0xfc, NULL                                 },
	{0x16, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Cabinet"                            },
	{0x15, 0x01, 0x01, 0x00, "Upright"                            },
	{0x15, 0x01, 0x01, 0x01, "Cocktail"                           },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x15, 0x01, 0x02, 0x02, "Off"                                },
	{0x15, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x15, 0x01, 0x0c, 0x08, "2"                                  },
	{0x15, 0x01, 0x0c, 0x0c, "3"                                  },
	{0x15, 0x01, 0x0c, 0x04, "5"                                  },
	{0x15, 0x01, 0x0c, 0x00, "240"                                },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x15, 0x01, 0x30, 0x20, "Easy"                               },
	{0x15, 0x01, 0x30, 0x30, "Normal"                             },
	{0x15, 0x01, 0x30, 0x10, "Hard"                               },
	{0x15, 0x01, 0x30, 0x00, "Hardest"                            },
	
	{0   , 0xfe, 0   , 2   , "Enemy Bullet Speed"                 },
	{0x15, 0x01, 0x40, 0x40, "Slow"                               },
	{0x15, 0x01, 0x40, 0x00, "Fast"                               },
	
	{0   , 0xfe, 0   , 2   , "Language"                           },
	{0x15, 0x01, 0x80, 0x80, "Japanese"                           },
	{0x15, 0x01, 0x80, 0x00, "English"                            },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x16)
};

STDDIPINFO(Shinobi);

static struct BurnDIPInfo SonicbomDIPList[]=
{
	// Default Values
	{0x13, 0xff, 0xff, 0x7f, NULL                                 },
	{0x14, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 8   , "Difficulty"                         },
	{0x13, 0x01, 0x07, 0x06, "Easy"                               },
	{0x13, 0x01, 0x07, 0x07, "Normal"                             },
	{0x13, 0x01, 0x07, 0x05, "Hard 1"                             },
	{0x13, 0x01, 0x07, 0x04, "Hard 2"                             },
	{0x13, 0x01, 0x07, 0x03, "Hard 3"                             },
	{0x13, 0x01, 0x07, 0x02, "Hard 4"                             },
	{0x13, 0x01, 0x07, 0x01, "Hard 5"                             },
	{0x13, 0x01, 0x07, 0x00, "Hardest"                            },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x13, 0x01, 0x18, 0x10, "2"                                  },
	{0x13, 0x01, 0x18, 0x18, "3"                                  },
	{0x13, 0x01, 0x18, 0x08, "4"                                  },
	{0x13, 0x01, 0x18, 0x00, "5"                                  },
	
	{0   , 0xfe, 0   , 4   , "Bonus Life"                         },
	{0x13, 0x01, 0x60, 0x40, "30000"                              },
	{0x13, 0x01, 0x60, 0x60, "40000"                              },
	{0x13, 0x01, 0x60, 0x20, "50000"                              },
	{0x13, 0x01, 0x60, 0x00, "60000"                              },
	
	{0   , 0xfe, 0   , 2   , "Cabinet"                            },
	{0x13, 0x01, 0x80, 0x00, "Upright"                            },
	{0x13, 0x01, 0x80, 0x80, "Cocktail"                           },
		
	// Dip 2
	SYSTEM16B_COINAGE(0x14)
};

STDDIPINFO(Sonicbom);

static struct BurnDIPInfo SjryukoDIPList[]=
{
	// Default Values
	{0x1c, 0xff, 0xff, 0xff, NULL                                 },
	{0x1d, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	
	
	// Dip 2
	SYSTEM16B_COINAGE(0x1d)
};

STDDIPINFO(Sjryuko);

static struct BurnDIPInfo TetrisDIPList[]=
{
	// Default Values
	{0x11, 0xff, 0xff, 0xfd, NULL                                 },
	{0x12, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x11, 0x01, 0x02, 0x02, "Off"                                },
	{0x11, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x11, 0x01, 0x30, 0x20, "Easy"                               },
	{0x11, 0x01, 0x30, 0x30, "Normal"                             },
	{0x11, 0x01, 0x30, 0x10, "Hard"                               },
	{0x11, 0x01, 0x30, 0x00, "Hardest"                            },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x12)
};

STDDIPINFO(Tetris);

static struct BurnDIPInfo TimescanDIPList[]=
{
	// Default Values
	{0x13, 0xff, 0xff, 0xf5, NULL                                 },
	{0x14, 0xff, 0xff, 0xff, NULL                                 },
	{0x15, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Cabinet"                            },
	{0x13, 0x01, 0x01, 0x00, "Cocktail"                           },
	{0x13, 0x01, 0x01, 0x01, "Upright"                            },
	
	{0   , 0xfe, 0   , 16  , "Bonus"                              },
	{0x13, 0x01, 0x1e, 0x16, "Replay 1000000/2000000"             },
	{0x13, 0x01, 0x1e, 0x14, "Replay 1200000/2500000"             },
	{0x13, 0x01, 0x1e, 0x12, "Replay 1500000/3000000"             },
	{0x13, 0x01, 0x1e, 0x10, "Replay 2000000/4000000"             },
	{0x13, 0x01, 0x1e, 0x1c, "Replay 1000000"                     },
	{0x13, 0x01, 0x1e, 0x1e, "Replay 1200000"                     },
	{0x13, 0x01, 0x1e, 0x1a, "Replay 1500000"                     },
	{0x13, 0x01, 0x1e, 0x18, "Replay 1800000"                     },
	{0x13, 0x01, 0x1e, 0x0e, "Extra Ball 100000"                  },
	{0x13, 0x01, 0x1e, 0x0c, "Extra Ball 200000"                  },
	{0x13, 0x01, 0x1e, 0x0a, "Extra Ball 300000"                  },
	{0x13, 0x01, 0x1e, 0x08, "Extra Ball 400000"                  },
	{0x13, 0x01, 0x1e, 0x06, "Extra Ball 500000"                  },
	{0x13, 0x01, 0x1e, 0x04, "Extra Ball 600000"                  },
	{0x13, 0x01, 0x1e, 0x02, "Extra Ball 700000"                  },
	{0x13, 0x01, 0x1e, 0x00, "None"                               },
	
	{0   , 0xfe, 0   , 2   , "Match"                              },
	{0x13, 0x01, 0x20, 0x00, "Off"                                },
	{0x13, 0x01, 0x20, 0x20, "On"                                 },
	
	{0   , 0xfe, 0   , 2   , "Pin Rebound"                        },
	{0x13, 0x01, 0x40, 0x40, "Well"                               },
	{0x13, 0x01, 0x40, 0x00, "A Little"                           },
	
	{0   , 0xfe, 0   , 2   , "Lives"                              },
	{0x13, 0x01, 0x80, 0x80, "3"                                  },
	{0x13, 0x01, 0x80, 0x00, "5"                                  },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x14)
	
	// Dip 3
	{0   , 0xfe, 0   , 2   , "Flip Screen"                        },
	{0x15, 0x01, 0x01, 0x01, "Off"                                },
	{0x15, 0x01, 0x01, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 2   , "Out Lane Pin"                       },
	{0x15, 0x01, 0x02, 0x02, "Near"                               },
	{0x15, 0x01, 0x02, 0x00, "Far"                                },
	
	{0   , 0xfe, 0   , 4   , "Special"                            },
	{0x15, 0x01, 0x0c, 0x08, "7 Credits"                          },
	{0x15, 0x01, 0x0c, 0x0c, "3 Credits"                          },
	{0x15, 0x01, 0x0c, 0x04, "1 Credit"                           },
	{0x15, 0x01, 0x0c, 0x00, "2000000 Points"                     },
	
	{0   , 0xfe, 0   , 2   , "Allow Continue"                     },
	{0x15, 0x01, 0x10, 0x00, "No"                                 },
	{0x15, 0x01, 0x10, 0x10, "Yes"                                },
};

STDDIPINFO(Timescan);

static struct BurnDIPInfo ToryumonDIPList[]=
{
	// Default Values
	{0x11, 0xff, 0xff, 0xfe, NULL                                 },
	{0x12, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x11, 0x01, 0x01, 0x01, "Off"                                },
	{0x11, 0x01, 0x01, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 2   , "VS-Mode Battle"                     },
	{0x11, 0x01, 0x10, 0x10, "1"                                  },
	{0x11, 0x01, 0x10, 0x00, "3"                                  },
	
	{0   , 0xfe, 0   , 8   , "Difficulty"                         },
	{0x11, 0x01, 0xe0, 0xc0, "Easy"                               },
	{0x11, 0x01, 0xe0, 0xe0, "Normal"                             },
	{0x11, 0x01, 0xe0, 0xa0, "Hard"                               },
	{0x11, 0x01, 0xe0, 0x80, "Hard+1"                             },
	{0x11, 0x01, 0xe0, 0x60, "Hard+2"                             },
	{0x11, 0x01, 0xe0, 0x40, "Hard+3"                             },
	{0x11, 0x01, 0xe0, 0x20, "Hard+4"                             },
	{0x11, 0x01, 0xe0, 0x00, "Hard+5"                             },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x12)
};

STDDIPINFO(Toryumon);

static struct BurnDIPInfo TturfDIPList[]=
{
	// Default Values
	{0x15, 0xff, 0xff, 0x2c, NULL                                 },
	{0x16, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 4   , "Continues"                          },
	{0x15, 0x01, 0x03, 0x00, "None"                               },
	{0x15, 0x01, 0x03, 0x01, "3"                                  },
	{0x15, 0x01, 0x03, 0x02, "Unlimited"                          },
	{0x15, 0x01, 0x03, 0x03, "Unlimited"                          },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x15, 0x01, 0x0c, 0x08, "Easy"                               },
	{0x15, 0x01, 0x0c, 0x0c, "Normal"                             },
	{0x15, 0x01, 0x0c, 0x04, "Hard"                               },
	{0x15, 0x01, 0x0c, 0x00, "Hardest"                            },
	
	{0   , 0xfe, 0   , 4   , "Starting Energy"                    },
	{0x15, 0x01, 0x30, 0x00, "3"                                  },
	{0x15, 0x01, 0x30, 0x10, "4"                                  },
	{0x15, 0x01, 0x30, 0x20, "6"                                  },
	{0x15, 0x01, 0x30, 0x30, "8"                                  },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x15, 0x01, 0x40, 0x40, "Off"                                },
	{0x15, 0x01, 0x40, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 2   , "Bonus Energy"                       },
	{0x15, 0x01, 0x80, 0x80, "1"                                  },
	{0x15, 0x01, 0x80, 0x00, "2"                                  },
	
	// Dip 2
	SYSTEM16B_COINAGE(0x16)
};

STDDIPINFO(Tturf);

static struct BurnDIPInfo Wb3DIPList[]=
{
	// Default Values
	{0x13, 0xff, 0xff, 0xfd, NULL                                 },
	{0x14, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x13, 0x01, 0x02, 0x02, "Off"                                },
	{0x13, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x13, 0x01, 0x0c, 0x00, "2"                                  },
	{0x13, 0x01, 0x0c, 0x0c, "3"                                  },
	{0x13, 0x01, 0x0c, 0x08, "4"                                  },
	{0x13, 0x01, 0x0c, 0x04, "5"                                  },
	
	{0   , 0xfe, 0   , 2   , "Bonus Life"                         },
	{0x13, 0x01, 0x10, 0x10, "5k, 10k, 18k, 30k"                  },
	{0x13, 0x01, 0x10, 0x00, "5k, 15k, 30k"                       },
	
	{0   , 0xfe, 0   , 2   , "Difficulty"                         },
	{0x13, 0x01, 0x20, 0x20, "Normal"                             },
	{0x13, 0x01, 0x20, 0x00, "Hard"                               },
	
	{0   , 0xfe, 0   , 2   , "Invincible Mode"                    },
	{0x13, 0x01, 0x40, 0x40, "No"                                 },
	{0x13, 0x01, 0x40, 0x00, "Yes"                                },
		
	// Dip 2
	SYSTEM16B_COINAGE(0x14)
};

STDDIPINFO(Wb3);

static struct BurnDIPInfo WrestwarDIPList[]=
{
	// Default Values
	{0x13, 0xff, 0xff, 0xfd, NULL                                 },
	{0x14, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x13, 0x01, 0x02, 0x02, "Off"                                },
	{0x13, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Round Time"                         },
	{0x13, 0x01, 0x0c, 0x00, "100"                                },
	{0x13, 0x01, 0x0c, 0x0c, "110"                                },
	{0x13, 0x01, 0x0c, 0x08, "120"                                },
	{0x13, 0x01, 0x0c, 0x04, "130"                                },
	
	{0   , 0xfe, 0   , 2   , "Allow Continue"                     },
	{0x13, 0x01, 0x20, 0x00, "No"                                 },
	{0x13, 0x01, 0x20, 0x20, "Yes"                                },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x13, 0x01, 0xc0, 0x80, "Easy"                               },
	{0x13, 0x01, 0xc0, 0xc0, "Normal"                             },
	{0x13, 0x01, 0xc0, 0x40, "Hard"                               },
	{0x13, 0x01, 0xc0, 0x00, "Hardest"                            },
		
	// Dip 2
	SYSTEM16B_COINAGE(0x14)
};

STDDIPINFO(Wrestwar);
	
#undef SYSTEM16B_COINAGE

/*====================================================
Rom defs
====================================================*/

static struct BurnRomInfo AliensynRomDesc[] = {
	{ "epr11083.a4",   0x08000, 0xcb2ad9b3, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11080.a1",   0x08000, 0xfe7378d9, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11084.a5",   0x08000, 0x2e1ec7b1, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11081.a2",   0x08000, 0x1308ee63, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11085.a6",   0x08000, 0xcff78f39, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11082.a3",   0x08000, 0x9cdc2a14, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr10702.b9",   0x10000, 0x393bc813, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10703.b10",  0x10000, 0x6b6dd9f5, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10704.b11",  0x10000, 0x911e7ebc, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr10709.b1",   0x10000, 0xaddf0a90, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10713.b5",   0x10000, 0xececde3a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10710.b2",   0x10000, 0x992369eb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10714.b6",   0x10000, 0x91bf42fb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10711.b3",   0x10000, 0x29166ef6, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10715.b7",   0x10000, 0xa7c57384, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10712.b4",   0x10000, 0x876ad019, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10716.b8",   0x10000, 0x40ba1d48, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr10723.a7",   0x08000, 0x99953526, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr10724.a8",   0x08000, 0xf971a817, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr10725.a9",   0x08000, 0x6a50e08f, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr10726.a10",  0x08000, 0xd50b7736, SYS16_ROM_UPD7759DATA | BRF_SND },
};


STD_ROM_PICK(Aliensyn);
STD_ROM_FN(Aliensyn);

static struct BurnRomInfo Aliensy3RomDesc[] = {
	{ "epr10816.a4",   0x08000, 0x17bf5304, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10814.a1",   0x08000, 0x4cd134df, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10817.a5",   0x08000, 0xc8b791b0, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10815.a2",   0x08000, 0xbdcf4a30, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10822a.a6",  0x08000, 0x1d0790aa, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10819a.a3",  0x08000, 0x1e7586b7, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr10702.b9",   0x10000, 0x393bc813, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10703.b10",  0x10000, 0x6b6dd9f5, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10704.b11",  0x10000, 0x911e7ebc, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr10709.b1",   0x10000, 0xaddf0a90, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10713.b5",   0x10000, 0xececde3a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10710.b2",   0x10000, 0x992369eb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10714.b6",   0x10000, 0x91bf42fb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10711.b3",   0x10000, 0x29166ef6, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10715.b7",   0x10000, 0xa7c57384, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10712.b4",   0x10000, 0x876ad019, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10716.b8",   0x10000, 0x40ba1d48, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr10723.a7",   0x08000, 0x99953526, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr10724.a8",   0x08000, 0xf971a817, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr10725.a9",   0x08000, 0x6a50e08f, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr10726.a10",  0x08000, 0xd50b7736, SYS16_ROM_UPD7759DATA | BRF_SND },
};


STD_ROM_PICK(Aliensy3);
STD_ROM_FN(Aliensy3);

static struct BurnRomInfo AltbeastRomDesc[] = {
	{ "epr-11907.a7",   0x20000, 0x29e0c3ad, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-11906.a5",   0x20000, 0x4c9e9cd8, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "opr-11674.a14",  0x20000, 0xa57a66d5, SYS16_ROM_TILES | BRF_GRA },
	{ "opr-11675.a15",  0x20000, 0x2ef2f144, SYS16_ROM_TILES | BRF_GRA },
	{ "opr-11676.a16",  0x20000, 0x0c04acac, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr-11677.b1",   0x20000, 0xa01425cd, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11681.b5",   0x20000, 0xd9e03363, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11678.b2",   0x20000, 0x17a9fc53, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11682.b6",   0x20000, 0xe3f77c5e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11679.b3",   0x20000, 0x14dcc245, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11683.b7",   0x20000, 0xf9a60f06, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11680.b4",   0x20000, 0xf43dcdec, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11684.b8",   0x20000, 0xb20c0edb, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr-11671.a10",  0x08000, 0x2b71343b, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "opr-11672.a11",  0x20000, 0xbbd7f460, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "opr-11673.a12",  0x20000, 0x400c4a36, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0078.mcu",   0x01000, 0x00000000, BRF_NODUMP },
};


STD_ROM_PICK(Altbeast);
STD_ROM_FN(Altbeast);

static struct BurnRomInfo AltbeasjRomDesc[] = {
	{ "epr-11885.a7",   0x20000, 0x5bb715aa, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-11884.a5",   0x20000, 0xe1707090, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr-11722.a14",  0x10000, 0xadaa8db5, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11736.b14",  0x10000, 0xe9ad5e89, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11723.a15",  0x10000, 0x131a3f9a, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11737.b15",  0x10000, 0x2e420023, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11724.a16",  0x10000, 0x6f2ed50a, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11738.b16",  0x10000, 0xde3d6d02, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr-11725.b1",   0x10000, 0xf8b3684e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11729.b5",   0x10000, 0xae3c2793, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11726.b2",   0x10000, 0x3cce5419, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11730.b6",   0x10000, 0x3af62b55, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11727.b3",   0x10000, 0xb0390078, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11731.b7",   0x10000, 0x2a87744a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11728.b4",   0x10000, 0xf3a43fd8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11732.b8",   0x10000, 0x2fb3e355, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11717.a1",   0x10000, 0x676be0cb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11733.b10",  0x10000, 0x802cac94, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11718.a2",   0x10000, 0x882864c2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11734.b11",  0x10000, 0x76c704d2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11719.a3",   0x10000, 0x339987f7, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11735.b12",  0x10000, 0x4fe406aa, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr-11671.a10",  0x08000, 0x2b71343b, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "opr-11672.a11",  0x20000, 0xbbd7f460, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "opr-11673.a12",  0x20000, 0x400c4a36, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0077.mcu",   0x01000, 0x00000000, BRF_NODUMP },
};


STD_ROM_PICK(Altbeasj);
STD_ROM_FN(Altbeasj);

static struct BurnRomInfo Altbeas2RomDesc[] = {
	{ "epr-11705.a7",   0x20000, 0x57dc5c7a, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-11704.a5",   0x20000, 0x33bbcf07, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "opr-11674.a14",  0x20000, 0xa57a66d5, SYS16_ROM_TILES | BRF_GRA },
	{ "opr-11675.a15",  0x20000, 0x2ef2f144, SYS16_ROM_TILES | BRF_GRA },
	{ "opr-11676.a16",  0x20000, 0x0c04acac, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr-11677.b1",   0x20000, 0xa01425cd, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11681.b5",   0x20000, 0xd9e03363, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11678.b2",   0x20000, 0x17a9fc53, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11682.b6",   0x20000, 0xe3f77c5e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11679.b3",   0x20000, 0x14dcc245, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11683.b7",   0x20000, 0xf9a60f06, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11680.b4",   0x20000, 0xf43dcdec, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11684.b8",   0x20000, 0xb20c0edb, SYS16_ROM_SPRITES | BRF_GRA },
	
	{ "epr-11686.a10",  0x08000, 0x828a45b3, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "opr-11672.a11",  0x20000, 0xbbd7f460, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "opr-11673.a12",  0x20000, 0x400c4a36, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0066.key",   0x02000, 0xed85a054, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Altbeas2);
STD_ROM_FN(Altbeas2);

static struct BurnRomInfo Altbeaj3RomDesc[] = {
	{ "epr-11721.a7",   0x20000, 0x1c5d11de, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-11720.a5",   0x20000, 0x735350cf, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr-11722.a14",  0x10000, 0xadaa8db5, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11736.b14",  0x10000, 0xe9ad5e89, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11723.a15",  0x10000, 0x131a3f9a, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11737.b15",  0x10000, 0x2e420023, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11724.a16",  0x10000, 0x6f2ed50a, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11738.b16",  0x10000, 0xde3d6d02, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr-11725.b1",   0x10000, 0xf8b3684e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11729.b5",   0x10000, 0xae3c2793, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11726.b2",   0x10000, 0x3cce5419, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11730.b6",   0x10000, 0x3af62b55, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11727.b3",   0x10000, 0xb0390078, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11731.b7",   0x10000, 0x2a87744a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11728.b4",   0x10000, 0xf3a43fd8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11732.b8",   0x10000, 0x2fb3e355, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11717.a1",   0x10000, 0x676be0cb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11733.b10",  0x10000, 0x802cac94, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11718.a2",   0x10000, 0x882864c2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11734.b11",  0x10000, 0x76c704d2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11719.a3",   0x10000, 0x339987f7, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11735.b12",  0x10000, 0x4fe406aa, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr-11671.a10",  0x08000, 0x2b71343b, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "opr-11672.a11",  0x20000, 0xbbd7f460, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "opr-11673.a12",  0x20000, 0x400c4a36, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0068.key",   0x02000, 0xc1ed4310, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Altbeaj3);
STD_ROM_FN(Altbeaj3);

static struct BurnRomInfo Altbeas4RomDesc[] = {
	{ "epr-11740.a7",   0x20000, 0xce227542, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-11739.a5",   0x20000, 0xe466eb65, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr-11722.a14",  0x10000, 0xadaa8db5, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11736.b14",  0x10000, 0xe9ad5e89, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11723.a15",  0x10000, 0x131a3f9a, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11737.b15",  0x10000, 0x2e420023, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11724.a16",  0x10000, 0x6f2ed50a, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11738.b16",  0x10000, 0xde3d6d02, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr-11725.b1",   0x10000, 0xf8b3684e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11729.b5",   0x10000, 0xae3c2793, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11726.b2",   0x10000, 0x3cce5419, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11730.b6",   0x10000, 0x3af62b55, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11727.b3",   0x10000, 0xb0390078, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11731.b7",   0x10000, 0x2a87744a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11728.b4",   0x10000, 0xf3a43fd8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11732.b8",   0x10000, 0x2fb3e355, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11717.a1",   0x10000, 0x676be0cb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11733.b10",  0x10000, 0x802cac94, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11718.a2",   0x10000, 0x882864c2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11734.b11",  0x10000, 0x76c704d2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11719.a3",   0x10000, 0x339987f7, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11735.b12",  0x10000, 0x4fe406aa, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr-11686.a10",  0x08000, 0x828a45b3, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "opr-11672.a11",  0x20000, 0xbbd7f460, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "opr-11673.a12",  0x20000, 0x400c4a36, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0066.key",   0x02000, 0xed85a054, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Altbeas4);
STD_ROM_FN(Altbeas4);

static struct BurnRomInfo Altbeas5RomDesc[] = {
	{ "epr-11883.a7",   0x20000, 0xc5b3e8f7, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-11882.a5",   0x20000, 0x9c01170b, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr-11722.a14",  0x10000, 0xadaa8db5, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11736.b14",  0x10000, 0xe9ad5e89, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11723.a15",  0x10000, 0x131a3f9a, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11737.b15",  0x10000, 0x2e420023, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11724.a16",  0x10000, 0x6f2ed50a, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-11738.b16",  0x10000, 0xde3d6d02, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr-11725.b1",   0x10000, 0xf8b3684e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11729.b5",   0x10000, 0xae3c2793, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11726.b2",   0x10000, 0x3cce5419, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11730.b6",   0x10000, 0x3af62b55, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11727.b3",   0x10000, 0xb0390078, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11731.b7",   0x10000, 0x2a87744a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11728.b4",   0x10000, 0xf3a43fd8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11732.b8",   0x10000, 0x2fb3e355, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11717.a1",   0x10000, 0x676be0cb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11733.b10",  0x10000, 0x802cac94, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11718.a2",   0x10000, 0x882864c2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11734.b11",  0x10000, 0x76c704d2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11719.a3",   0x10000, 0x339987f7, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-11735.b12",  0x10000, 0x4fe406aa, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr-11671.a10",  0x08000, 0x2b71343b, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "opr-11672.a11",  0x20000, 0xbbd7f460, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "opr-11673.a12",  0x20000, 0x400c4a36, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0076.mcu",   0x01000, 0x00000000, BRF_NODUMP },
};


STD_ROM_PICK(Altbeas5);
STD_ROM_FN(Altbeas5);

static struct BurnRomInfo AurailRomDesc[] = {
	{ "epr13577.a7",   0x20000, 0x6701b686, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr13576.a5",   0x20000, 0x1e428d94, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr13447.a8",   0x20000, 0x70a52167, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr13445.a6",   0x20000, 0x28dfc3dd, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "mpr13450.a14",  0x20000, 0x0fc4a7a8, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr13465.b14",  0x20000, 0xe08135e0, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr13451.a15",  0x20000, 0x1c49852f, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr13466.b15",  0x20000, 0xe14c6684, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr13452.a16",  0x20000, 0x047bde5e, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr13467.b16",  0x20000, 0x6309fec4, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr13453.b1",   0x20000, 0x5fa0a9f8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13457.b5",   0x20000, 0x0d1b54da, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13454.b2",   0x20000, 0x5f6b33b1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13458.b6",   0x20000, 0xbad340c3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13455.b3",   0x20000, 0x4e80520b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13459.b7",   0x20000, 0x7e9165ac, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13456.b4",   0x20000, 0x5733c428, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13460.b8",   0x20000, 0x66b8f9b3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13440.a1",   0x20000, 0x4f370b2b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13461.b10",  0x20000, 0xf76014bf, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13441.a2",   0x20000, 0x37cf9cb4, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13462.b11",  0x20000, 0x1061e7da, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13442.a3",   0x20000, 0x049698ef, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13463.b12",  0x20000, 0x7dbcfbf1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13443.a4",   0x20000, 0x77a8989e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13464.b13",  0x20000, 0x551df422, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr13448.a10",  0x08000, 0xb5183fb9, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr13449.a11",  0x20000, 0xd3d9aaf9, SYS16_ROM_UPD7759DATA | BRF_SND },
};


STD_ROM_PICK(Aurail);
STD_ROM_FN(Aurail);

static struct BurnRomInfo Aurail1RomDesc[] = {
	{ "epr13469.a7",   0x20000, 0xc628b69d, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr13468.a5",   0x20000, 0xce092218, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr13447.a8",   0x20000, 0x70a52167, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr13445.a6",   0x20000, 0x28dfc3dd, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "mpr13450.a14",  0x20000, 0x0fc4a7a8, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr13465.b14",  0x20000, 0xe08135e0, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr13451.a15",  0x20000, 0x1c49852f, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr13466.b15",  0x20000, 0xe14c6684, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr13452.a16",  0x20000, 0x047bde5e, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr13467.b16",  0x20000, 0x6309fec4, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr13453.b1",   0x20000, 0x5fa0a9f8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13457.b5",   0x20000, 0x0d1b54da, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13454.b2",   0x20000, 0x5f6b33b1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13458.b6",   0x20000, 0xbad340c3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13455.b3",   0x20000, 0x4e80520b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13459.b7",   0x20000, 0x7e9165ac, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13456.b4",   0x20000, 0x5733c428, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13460.b8",   0x20000, 0x66b8f9b3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13440.a1",   0x20000, 0x4f370b2b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13461.b10",  0x20000, 0xf76014bf, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13441.a2",   0x20000, 0x37cf9cb4, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13462.b11",  0x20000, 0x1061e7da, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13442.a3",   0x20000, 0x049698ef, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13463.b12",  0x20000, 0x7dbcfbf1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13443.a4",   0x20000, 0x77a8989e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13464.b13",  0x20000, 0x551df422, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr13448.a10",  0x08000, 0xb5183fb9, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr13449.a11",  0x20000, 0xd3d9aaf9, SYS16_ROM_UPD7759DATA | BRF_SND },
};


STD_ROM_PICK(Aurail1);
STD_ROM_FN(Aurail1);

static struct BurnRomInfo AurailjRomDesc[] = {
	{ "epr13446.a7",   0x20000, 0xd1f57b2a, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr13444.a5",   0x20000, 0x7a2b045f, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr13447.a8",   0x20000, 0x70a52167, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr13445.a6",   0x20000, 0x28dfc3dd, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr13450.a14",  0x20000, 0x0fc4a7a8, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr13465.b14",  0x20000, 0xe08135e0, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr13451.a15",  0x20000, 0x1c49852f, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr13466.b15",  0x20000, 0xe14c6684, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr13452.a16",  0x20000, 0x047bde5e, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr13467.b16",  0x20000, 0x6309fec4, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr13453.b1",   0x20000, 0x5fa0a9f8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13457.b5",   0x20000, 0x0d1b54da, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13454.b2",   0x20000, 0x5f6b33b1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13458.b6",   0x20000, 0xbad340c3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13455.b3",   0x20000, 0x4e80520b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13459.b7",   0x20000, 0x7e9165ac, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13456.b4",   0x20000, 0x5733c428, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13460.b8",   0x20000, 0x66b8f9b3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13440.a1",   0x20000, 0x4f370b2b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13461.b10",  0x20000, 0xf76014bf, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13441.a2",   0x20000, 0x37cf9cb4, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13462.b11",  0x20000, 0x1061e7da, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13442.a3",   0x20000, 0x049698ef, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13463.b12",  0x20000, 0x7dbcfbf1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13443.a4",   0x20000, 0x77a8989e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr13464.b13",  0x20000, 0x551df422, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr13448.a10",  0x08000, 0xb5183fb9, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr13449.a11",  0x20000, 0xd3d9aaf9, SYS16_ROM_UPD7759DATA | BRF_SND },
};


STD_ROM_PICK(Aurailj);
STD_ROM_FN(Aurailj);

static struct BurnRomInfo BayrouteRomDesc[] = {
	{ "epr12517.a7",   0x20000, 0x436728a9, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12516.a5",   0x20000, 0x4ff0353f, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12458.a8",   0x20000, 0xe7c7476a, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12456.a6",   0x20000, 0x25dc2eaf, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "opr12462.a14",  0x10000, 0xa19943b5, SYS16_ROM_TILES | BRF_GRA },
	{ "opr12463.a15",  0x10000, 0x62f8200d, SYS16_ROM_TILES | BRF_GRA },
	{ "opr12464.a16",  0x10000, 0xc8c59703, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr12465.b1",   0x20000, 0x11d61b45, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12467.b5",   0x20000, 0xc3b4e4c0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12466.b2",   0x20000, 0xa57f236f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12468.b6",   0x20000, 0xd89c77de, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12459.a10",  0x08000, 0x3e1d29d0, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12460.a11",  0x20000, 0x0bae570d, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "mpr12461.a12",  0x20000, 0xb03b8b46, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0116.key",  0x02000, 0x8778ee49, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Bayroute);
STD_ROM_FN(Bayroute);

static struct BurnRomInfo BayroutjRomDesc[] = {
	{ "epr12457.a7",   0x20000, 0xbc726255, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12455.a5",   0x20000, 0xb6a722eb, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12458.a8",   0x20000, 0xe7c7476a, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12456.a6",   0x20000, 0x25dc2eaf, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "opr12462.a14",  0x10000, 0xa19943b5, SYS16_ROM_TILES | BRF_GRA },
	{ "opr12463.a15",  0x10000, 0x62f8200d, SYS16_ROM_TILES | BRF_GRA },
	{ "opr12464.a16",  0x10000, 0xc8c59703, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr12465.b1",   0x20000, 0x11d61b45, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12467.b5",   0x20000, 0xc3b4e4c0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12466.b2",   0x20000, 0xa57f236f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12468.b6",   0x20000, 0xd89c77de, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12459.a10",  0x08000, 0x3e1d29d0, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12460.a11",  0x20000, 0x0bae570d, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "mpr12461.a12",  0x20000, 0xb03b8b46, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0115.key",  0x02000, 0x75a55614, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Bayroutj);
STD_ROM_FN(Bayroutj);

static struct BurnRomInfo Bayrout1RomDesc[] = {
	{ "br.a4",         0x10000, 0x91c6424b, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "br.a1",         0x10000, 0x76954bf3, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "br.a5",         0x10000, 0x9d6fd183, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "br.a2",         0x10000, 0x5ca1e3d2, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "br.a6",         0x10000, 0xed97ad4c, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "br.a3",         0x10000, 0x0d362905, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "opr12462.a14",  0x10000, 0xa19943b5, SYS16_ROM_TILES | BRF_GRA },
	{ "opr12463.a15",  0x10000, 0x62f8200d, SYS16_ROM_TILES | BRF_GRA },
	{ "opr12464.a16",  0x10000, 0xc8c59703, SYS16_ROM_TILES | BRF_GRA },
	
	{ "br_obj0o.b1",   0x10000, 0x098a5e82, SYS16_ROM_SPRITES | BRF_GRA },
	{ "br_obj0e.b5",   0x10000, 0x85238af9, SYS16_ROM_SPRITES | BRF_GRA },
	{ "br_obj1o.b2",   0x10000, 0xcc641da1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "br_obj1e.b6",   0x10000, 0xd3123315, SYS16_ROM_SPRITES | BRF_GRA },
	{ "br_obj2o.b3",   0x10000, 0x84efac1f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "br_obj2e.b7",   0x10000, 0xb73b12cb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "br_obj3o.b4",   0x10000, 0xa2e238ac, SYS16_ROM_SPRITES | BRF_GRA },
	{ "br.b8",         0x10000, 0xd8de78ff, SYS16_ROM_SPRITES | BRF_GRA },

	{ "sound.a7",      0x08000, 0x00000000, SYS16_ROM_Z80PROG | BRF_NODUMP | BRF_PRG },
	
	{ "sound.a8",      0x10000, 0x00000000, SYS16_ROM_UPD7759DATA | BRF_NODUMP | BRF_SND },
	{ "sound.a9",      0x10000, 0x00000000, SYS16_ROM_UPD7759DATA | BRF_NODUMP | BRF_SND },
	{ "sound.a10",     0x10000, 0x00000000, SYS16_ROM_UPD7759DATA | BRF_NODUMP | BRF_SND },
	{ "sound.a11",     0x10000, 0x00000000, SYS16_ROM_UPD7759DATA | BRF_NODUMP | BRF_SND },
};


STD_ROM_PICK(Bayrout1);
STD_ROM_FN(Bayrout1);

static struct BurnRomInfo BulletRomDesc[] = {
	{ "epr11010.a4",   0x08000, 0xdd9001de, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11007.a1",   0x08000, 0xd9e08110, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11011.a5",   0x08000, 0x7f446b9f, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11008.a2",   0x08000, 0x34824d3b, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11012.a6",   0x08000, 0x3992f159, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11009.a3",   0x08000, 0xdf199999, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "epr10994.b9",   0x10000, 0x3035468a, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10995.b10",  0x10000, 0x6b97aff1, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10996.b11",  0x10000, 0x501bddd6, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr10999.b1",   0x10000, 0x119f0008, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11003.b5",   0x10000, 0x2f429089, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11000.b2",   0x10000, 0xf5482bbe, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11004.b6",   0x10000, 0x8c886df0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11001.b3",   0x10000, 0x65ea71e0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11005.b7",   0x10000, 0xea2f9d50, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11002.b4",   0x10000, 0x9e25042b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11006.b8",   0x10000, 0x6b7384f2, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr10997.a7",   0x08000, 0x5dd9cab5, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr10998.a8",   0x08000, 0xf971a817, SYS16_ROM_UPD7759DATA | BRF_SND },
		
	{ "317-0041.key",  0x02000, 0xa30ae46c, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Bullet);
STD_ROM_FN(Bullet);

static struct BurnRomInfo CottonRomDesc[] = {
	{ "epr13921a.a7",  0x20000, 0xf047a037, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr13919a.a5",  0x20000, 0x651108b1, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr13922a.a8",  0x20000, 0x1ca248c5, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr13920a.a6",  0x20000, 0xfa3610f9, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "opr13862.a14",  0x20000, 0xa47354b6, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13877.b14",  0x20000, 0xd38424b5, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13863.a15",  0x20000, 0x8c990026, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13878.b15",  0x20000, 0x21c15b8a, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13864.a16",  0x20000, 0xd2b175bf, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13879.b16",  0x20000, 0xb9d62531, SYS16_ROM_TILES | BRF_GRA },
	
	{ "opr13865.b1",   0x20000, 0x7024f404, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13869.b5",   0x20000, 0xab4b3468, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13866.b2",   0x20000, 0x6169bba4, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13870.b6",   0x20000, 0x69b41ac3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13867.b3",   0x20000, 0xb014f02d, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13871.b7",   0x20000, 0x0801cf02, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13868.b4",   0x20000, 0xe62a7cd6, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13872.b8",   0x20000, 0xf066f315, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13852.a1",   0x20000, 0x943aba8b, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13873.b10",  0x20000, 0x1bd145f3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13853.a2",   0x20000, 0x7ea93200, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13874.b11",  0x20000, 0x4fd59bff, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13891.a3",   0x20000, 0xc6b3c414, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13894.b12",  0x20000, 0xe3d0bee2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13855.a4",   0x20000, 0x856f3ee2, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13876.b13",  0x20000, 0x1c5ffad8, SYS16_ROM_SPRITES | BRF_GRA },
	
	{ "epr13892.a10",  0x08000, 0xfdfbe6ad, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "opr13893.a11",  0x20000, 0x384233df, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0181a.key", 0x02000, 0x5c419b36, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Cotton);
STD_ROM_FN(Cotton);

static struct BurnRomInfo CottonuRomDesc[] = {
	{ "cotton.a7",     0x20000, 0xe7ef7d10, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "cotton.a5",     0x20000, 0xabe4f83e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "cotton.a8",     0x20000, 0xfc0f4401, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "cotton.a6",     0x20000, 0xf50f1ea2, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "opr13862.a14",  0x20000, 0xa47354b6, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13877.b14",  0x20000, 0xd38424b5, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13863.a15",  0x20000, 0x8c990026, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13878.b15",  0x20000, 0x21c15b8a, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13864.a16",  0x20000, 0xd2b175bf, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13879.b16",  0x20000, 0xb9d62531, SYS16_ROM_TILES | BRF_GRA },
	
	{ "opr13865.b1",   0x20000, 0x7024f404, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13869.b5",   0x20000, 0xab4b3468, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13866.b2",   0x20000, 0x6169bba4, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13870.b6",   0x20000, 0x69b41ac3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13867.b3",   0x20000, 0xb014f02d, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13871.b7",   0x20000, 0x0801cf02, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13868.b4",   0x20000, 0xe62a7cd6, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13872.b8",   0x20000, 0xf066f315, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13852.a1",   0x20000, 0x943aba8b, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13873.b10",  0x20000, 0x1bd145f3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13853.a2",   0x20000, 0x7ea93200, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13874.b11",  0x20000, 0x4fd59bff, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13891.a3",   0x20000, 0xc6b3c414, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13894.b12",  0x20000, 0xe3d0bee2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13855.a4",   0x20000, 0x856f3ee2, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13876.b13",  0x20000, 0x1c5ffad8, SYS16_ROM_SPRITES | BRF_GRA },
	
	{ "epr13892.a10",  0x08000, 0xfdfbe6ad, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "opr13893.a11",  0x20000, 0x384233df, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0180.key",  0x02000, 0xa236b915, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Cottonu);
STD_ROM_FN(Cottonu);

static struct BurnRomInfo CottonjRomDesc[] = {
	{ "epr13858.a7",   0x20000, 0x276f42fe, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr13856.a5",   0x20000, 0x14e6b5e7, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr13859.a8",   0x20000, 0x4703ef9d, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr13857.a6",   0x20000, 0xde37e527, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "opr13862.a14",  0x20000, 0xa47354b6, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13877.b14",  0x20000, 0xd38424b5, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13863.a15",  0x20000, 0x8c990026, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13878.b15",  0x20000, 0x21c15b8a, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13864.a16",  0x20000, 0xd2b175bf, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13879.b16",  0x20000, 0xb9d62531, SYS16_ROM_TILES | BRF_GRA },
	
	{ "opr13865.b1",   0x20000, 0x7024f404, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13869.b5",   0x20000, 0xab4b3468, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13866.b2",   0x20000, 0x6169bba4, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13870.b6",   0x20000, 0x69b41ac3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13867.b3",   0x20000, 0xb014f02d, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13871.b7",   0x20000, 0x0801cf02, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13868.b4",   0x20000, 0xe62a7cd6, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13872.b8",   0x20000, 0xf066f315, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13852.a1",   0x20000, 0x943aba8b, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13873.b10",  0x20000, 0x1bd145f3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13853.a2",   0x20000, 0x7ea93200, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13874.b11",  0x20000, 0x4fd59bff, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13854.a3",   0x20000, 0x1c942190, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13875.b12",  0x20000, 0x6a66868d, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13855.a4",   0x20000, 0x856f3ee2, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "opr13876.b13",  0x20000, 0x1c5ffad8, SYS16_ROM_SPRITES | BRF_GRA },
	
	{ "epr13860.a10",  0x08000, 0x6a57b027, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "opr13061.a11",  0x20000, 0x4d21153f, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0179a.key", 0x02000, 0x488096d3, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Cottonj);
STD_ROM_FN(Cottonj);

static struct BurnRomInfo DduxRomDesc[] = {
	{ "epr11191.a7",   0x20000, 0x500e400a, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11190.a5",   0x20000, 0x2a698308, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11915.a8",   0x20000, 0xd8ed3132, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11913.a6",   0x20000, 0x30c6cb92, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr11917.a14",  0x10000, 0x6f772190, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr11918.a15",  0x10000, 0xc731db95, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr11919.a16",  0x10000, 0x64d5a491, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr11920.b1",   0x20000, 0xe5d1e3cd, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr11922.b5",   0x20000, 0x70b0c4dd, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr11921.b2",   0x20000, 0x61d2358c, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr11923.b6",   0x20000, 0xc9ffe47d, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr11916.a10",  0x08000, 0x7ab541cf, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "317-0096.key",  0x02000, 0x6fd7d26e, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Ddux);
STD_ROM_FN(Ddux);

static struct BurnRomInfo Ddux1RomDesc[] = {
	{ "epr12189.a7",   0x20000, 0x558e9b5d, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12188.a5",   0x20000, 0x802a240f, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11915.a8",   0x20000, 0xd8ed3132, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11913.a6",   0x20000, 0x30c6cb92, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr11917.a14",  0x10000, 0x6f772190, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr11918.a15",  0x10000, 0xc731db95, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr11919.a16",  0x10000, 0x64d5a491, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr11920.b1",   0x20000, 0xe5d1e3cd, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr11922.b5",   0x20000, 0x70b0c4dd, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr11921.b2",   0x20000, 0x61d2358c, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr11923.b6",   0x20000, 0xc9ffe47d, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr11916.a10",  0x08000, 0x7ab541cf, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "317-0095.bin",  0x01000, 0x00000000, BRF_NODUMP },
};


STD_ROM_PICK(Ddux1);
STD_ROM_FN(Ddux1);

static struct BurnRomInfo DunkshotRomDesc[] = {
	{ "epr10470.a4",   0x08000, 0x8c60761f, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10467.a1",   0x08000, 0x29774114, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10471.a5",   0x08000, 0x22777314, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10468.a2",   0x08000, 0xe2d5f97a, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10472.a6",   0x08000, 0x206027a6, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10469.a3",   0x08000, 0xaa442b81, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
		
	{ "epr10485.b9",   0x08000, 0xf16dda29, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10486.b10",  0x08000, 0x311d973c, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10487.b11",  0x08000, 0xa8fb179f, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr10477.b1",   0x08000, 0xf9d3b2cb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10481.b5",   0x08000, 0xfeb04bc9, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10478.b2",   0x08000, 0x5b5c5c92, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "epr10482.b6",   0x08000, 0x5bc07618, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10479.b3",   0x08000, 0xe84190a0, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "epr10483.b7",   0x08000, 0x7cab4f9e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10480.b4",   0x08000, 0x5dffd9dd, SYS16_ROM_SPRITES | BRF_GRA },	
	{ "epr10484.b8",   0x08000, 0xbcb5fcc9, SYS16_ROM_SPRITES | BRF_GRA },	
	
	{ "epr10473.a7",   0x08000, 0x7f1f5a27, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr10474.a8",   0x08000, 0x419a656e, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr10475.a9",   0x08000, 0x17d55e85, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr10476.a10",  0x08000, 0xa6be0956, SYS16_ROM_UPD7759DATA | BRF_SND },
};


STD_ROM_PICK(Dunkshot);
STD_ROM_FN(Dunkshot);

static struct BurnRomInfo EswatRomDesc[] = {
	{ "epr12659.bin",  0x40000, 0xc5ab2db9, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12658.bin",  0x40000, 0xaf40bd71, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12624.b11",  0x40000, 0x375a5ec4, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr12625.b12",  0x40000, 0x3b8c757e, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr12626.b13",  0x40000, 0x3efca25c, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr12618.b1",   0x40000, 0x0d1530bf, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12621.b4",   0x40000, 0x18ff0799, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12619.b2",   0x40000, 0x32069246, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12622.b5",   0x40000, 0xa3dfe436, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12620.b3",   0x40000, 0xf6b096e0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12623.b6",   0x40000, 0x6773fef6, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12617.a13",  0x08000, 0x7efecf23, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12616.a11",  0x40000, 0x254347c2, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0130.key",  0x02000, 0xba7b717b, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Eswat);
STD_ROM_FN(Eswat);

static struct BurnRomInfo EswatjRomDesc[] = {
	{ "epr12615.a2",   0x40000, 0x388c2ea7, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12614.a1",   0x40000, 0xd5f0fb47, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12624.b11",  0x40000, 0x375a5ec4, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr12625.b12",  0x40000, 0x3b8c757e, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr12626.b13",  0x40000, 0x3efca25c, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr12618.b1",   0x40000, 0x0d1530bf, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12621.b4",   0x40000, 0x18ff0799, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12619.b2",   0x40000, 0x32069246, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12622.b5",   0x40000, 0xa3dfe436, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12620.b3",   0x40000, 0xf6b096e0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12623.b6",   0x40000, 0x6773fef6, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12617.a13",  0x08000, 0x7efecf23, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12616.a11",  0x40000, 0x254347c2, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0128.key",  0x02000, 0x95f96277, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Eswatj);
STD_ROM_FN(Eswatj);

static struct BurnRomInfo EswatuRomDesc[] = {
	{ "epr12657.a2",   0x40000, 0x43ca72aa, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12656.a1",   0x40000, 0x5f018967, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12624.b11",  0x40000, 0x375a5ec4, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr12625.b12",  0x40000, 0x3b8c757e, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr12626.b13",  0x40000, 0x3efca25c, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr12618.b1",   0x40000, 0x0d1530bf, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12621.b4",   0x40000, 0x18ff0799, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12619.b2",   0x40000, 0x32069246, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12622.b5",   0x40000, 0xa3dfe436, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12620.b3",   0x40000, 0xf6b096e0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12623.b6",   0x40000, 0x6773fef6, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12617.a13",  0x08000, 0x7efecf23, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12616.a11",  0x40000, 0x254347c2, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0129.key",  0x02000, 0x128302c7, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Eswatu);
STD_ROM_FN(Eswatu);

static struct BurnRomInfo FpointRomDesc[] = {
	{ "epr12599b.a4",  0x10000, 0x26e3f354, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12598b.a1",  0x10000, 0xc0f2c97d, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "opr12593.a14",  0x10000, 0xcc0582d8, SYS16_ROM_TILES | BRF_GRA },
	{ "opr12594.a15",  0x10000, 0x8bfc4815, SYS16_ROM_TILES | BRF_GRA },
	{ "opr12595.a16",  0x10000, 0x5b18d60b, SYS16_ROM_TILES | BRF_GRA },
	
	{ "opr12596.b1",   0x10000, 0x4a4041f3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12597.b5",   0x10000, 0x6961e676, SYS16_ROM_SPRITES | BRF_GRA },
	
	{ "epr12592.a10",  0x08000, 0x9a8c11bb, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "317-0127a.key", 0x02000, 0x5adb0042, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Fpoint);
STD_ROM_FN(Fpoint);

static struct BurnRomInfo Fpoint1RomDesc[] = {
	{ "epr12591b.a7",  0x10000, 0x248b3e1b, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12590b.a5",  0x10000, 0x75256e3d, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "opr12593.a14",  0x10000, 0xcc0582d8, SYS16_ROM_TILES | BRF_GRA },
	{ "opr12594.a15",  0x10000, 0x8bfc4815, SYS16_ROM_TILES | BRF_GRA },
	{ "opr12595.a16",  0x10000, 0x5b18d60b, SYS16_ROM_TILES | BRF_GRA },
	
	{ "opr12596.b1",   0x10000, 0x4a4041f3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12597.b5",   0x10000, 0x6961e676, SYS16_ROM_SPRITES | BRF_GRA },
	
	{ "epr12592.a10",  0x08000, 0x9a8c11bb, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "317-0127a.key", 0x02000, 0x5adb0042, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Fpoint1);
STD_ROM_FN(Fpoint1);

static struct BurnRomInfo GoldnaxeRomDesc[] = {
	{ "epr12545.a2",   0x40000, 0xa97c4e4d, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12544.a1",   0x40000, 0x5e38f668, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr12385",      0x20000, 0xb8a4e7e0, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12386",      0x20000, 0x25d7d779, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12387",      0x20000, 0xc7fcadf3, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr12378.b1",   0x40000, 0x119e5a82, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12379.b4",   0x40000, 0x1a0e8c57, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12380.b2",   0x40000, 0xbb2c0853, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12381.b5",   0x40000, 0x81ba6ecc, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12382.b3",   0x40000, 0x81601c6f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12383.b6",   0x40000, 0x5dbacf7a, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12390",      0x08000, 0x399fc5f5, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12384.a11",  0x20000, 0x6218d8e7, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0123a.bin", 0x01000, 0x00000000, BRF_NODUMP },
};


STD_ROM_PICK(Goldnaxe);
STD_ROM_FN(Goldnaxe);

static struct BurnRomInfo Goldnax1RomDesc[] = {
	{ "epr12389.a2",   0x40000, 0x35d5fa77, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12388.a1",   0x40000, 0x72952a93, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr12385",      0x20000, 0xb8a4e7e0, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12386",      0x20000, 0x25d7d779, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12387",      0x20000, 0xc7fcadf3, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr12378.b1",   0x40000, 0x119e5a82, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12379.b4",   0x40000, 0x1a0e8c57, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12380.b2",   0x40000, 0xbb2c0853, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12381.b5",   0x40000, 0x81ba6ecc, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12382.b3",   0x40000, 0x81601c6f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12383.b6",   0x40000, 0x5dbacf7a, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12390",      0x08000, 0x399fc5f5, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12384.a11",  0x20000, 0x6218d8e7, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0110.key",  0x02000, 0xcd517dc6, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Goldnax1);
STD_ROM_FN(Goldnax1);

static struct BurnRomInfo Goldnax2RomDesc[] = {
	{ "epr12523.a7",   0x20000, 0x8e6128d7, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12522.a5",   0x20000, 0xb6c35160, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12521.a8",   0x20000, 0x5001d713, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12519.a6",   0x20000, 0x4438ca8e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr12385",      0x20000, 0xb8a4e7e0, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12386",      0x20000, 0x25d7d779, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12387",      0x20000, 0xc7fcadf3, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr12378.b1",   0x40000, 0x119e5a82, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12379.b4",   0x40000, 0x1a0e8c57, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12380.b2",   0x40000, 0xbb2c0853, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12381.b5",   0x40000, 0x81ba6ecc, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12382.b3",   0x40000, 0x81601c6f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12383.b6",   0x40000, 0x5dbacf7a, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12390",      0x08000, 0x399fc5f5, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12384.a11",  0x20000, 0x6218d8e7, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0112.bin",  0x01000, 0x00000000, BRF_NODUMP },
};


STD_ROM_PICK(Goldnax2);
STD_ROM_FN(Goldnax2);

static struct BurnRomInfo Goldnax3RomDesc[] = {
	{ "7.bin",         0x20000, 0x48332c76, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "5.bin",         0x20000, 0x8e58f342, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12521.a8",   0x20000, 0x5001d713, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12519.a6",   0x20000, 0x4438ca8e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr12385",      0x20000, 0xb8a4e7e0, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12386",      0x20000, 0x25d7d779, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12387",      0x20000, 0xc7fcadf3, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr12378.b1",   0x40000, 0x119e5a82, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12379.b4",   0x40000, 0x1a0e8c57, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12380.b2",   0x40000, 0xbb2c0853, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12381.b5",   0x40000, 0x81ba6ecc, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12382.b3",   0x40000, 0x81601c6f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12383.b6",   0x40000, 0x5dbacf7a, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12390",      0x08000, 0x399fc5f5, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12384.a11",  0x20000, 0x6218d8e7, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0120.key",  0x02000, 0x946e9fa6, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Goldnax3);
STD_ROM_FN(Goldnax3);

static struct BurnRomInfo GoldnaxjRomDesc[] = {
	{ "epr12540.a7",   0x20000, 0x0c7ccc6d, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12539.a5",   0x20000, 0x1f24f7d0, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12521.a8",   0x20000, 0x5001d713, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12519.a6",   0x20000, 0x4438ca8e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr12385",      0x20000, 0xb8a4e7e0, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12386",      0x20000, 0x25d7d779, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12387",      0x20000, 0xc7fcadf3, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr12378.b1",   0x40000, 0x119e5a82, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12379.b4",   0x40000, 0x1a0e8c57, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12380.b2",   0x40000, 0xbb2c0853, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12381.b5",   0x40000, 0x81ba6ecc, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12382.b3",   0x40000, 0x81601c6f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12383.b6",   0x40000, 0x5dbacf7a, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12390",      0x08000, 0x399fc5f5, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12384.a11",  0x20000, 0x6218d8e7, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0121.key",  0x02000, 0x72afed01, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Goldnaxj);
STD_ROM_FN(Goldnaxj);

static struct BurnRomInfo GoldnaxuRomDesc[] = {
	{ "epr12543.a2",   0x40000, 0xb0df9ca4, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12542.a1",   0x40000, 0xb7994d3c, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr12385",      0x20000, 0xb8a4e7e0, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12386",      0x20000, 0x25d7d779, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12387",      0x20000, 0xc7fcadf3, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr12378.b1",   0x40000, 0x119e5a82, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12379.b4",   0x40000, 0x1a0e8c57, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12380.b2",   0x40000, 0xbb2c0853, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12381.b5",   0x40000, 0x81ba6ecc, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12382.b3",   0x40000, 0x81601c6f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12383.b6",   0x40000, 0x5dbacf7a, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12390",      0x08000, 0x399fc5f5, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12384.a11",  0x20000, 0x6218d8e7, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0122.key",  0x02000, 0xf123c2fb, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Goldnaxu);
STD_ROM_FN(Goldnaxu);

static struct BurnRomInfo HwchampRomDesc[] = {
	{ "rom0-e.bin",    0x20000, 0xe5abfed7, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "rom0-o.bin",    0x20000, 0x25180124, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "scr01.bin",     0x20000, 0xfc586a86, SYS16_ROM_TILES | BRF_GRA },
	{ "scr11.bin",     0x20000, 0xaeaaa9d8, SYS16_ROM_TILES | BRF_GRA },
	{ "scr02.bin",     0x20000, 0x7715a742, SYS16_ROM_TILES | BRF_GRA },
	{ "scr12.bin",     0x20000, 0x63a82afa, SYS16_ROM_TILES | BRF_GRA },
	{ "scr03.bin",     0x20000, 0xf30cd5fd, SYS16_ROM_TILES | BRF_GRA },
	{ "scr13.bin",     0x20000, 0x5b8494a8, SYS16_ROM_TILES | BRF_GRA },
	
	{ "obj0-o.bin",    0x20000, 0xfc098a13, SYS16_ROM_SPRITES | BRF_GRA },
	{ "obj0-e.bin",    0x20000, 0x5db934a8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "obj1-o.bin",    0x20000, 0x1f27ee74, SYS16_ROM_SPRITES | BRF_GRA },
	{ "obj1-e.bin",    0x20000, 0x8a6a5cf1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "obj2-o.bin",    0x20000, 0xc0b2ba82, SYS16_ROM_SPRITES | BRF_GRA },
	{ "obj2-e.bin",    0x20000, 0xd6c7917b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "obj3-o.bin",    0x20000, 0x52fa3a49, SYS16_ROM_SPRITES | BRF_GRA },
	{ "obj3-e.bin",    0x20000, 0x57e8f9d2, SYS16_ROM_SPRITES | BRF_GRA },
	
	{ "s-prog.bin",    0x08000, 0x96a12d9d, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "speech0.bin",   0x20000, 0x4191c03d, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "speech1.bin",   0x20000, 0xa4d53f7b, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "pls153.bin",    0x000eb, 0x39b47212, BRF_OPT }, // PLD
};


STD_ROM_PICK(Hwchamp);
STD_ROM_FN(Hwchamp);

static struct BurnRomInfo MvpRomDesc[] = {
	{ "13000.rom",     0x40000, 0x2e0e21ec, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "12999.rom",     0x40000, 0xfd213d28, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "13011.rom",     0x40000, 0x1cb871fc, SYS16_ROM_TILES | BRF_GRA },
	{ "13012.rom",     0x40000, 0xb75e6821, SYS16_ROM_TILES | BRF_GRA },
	{ "13013.rom",     0x40000, 0xf1944a3c, SYS16_ROM_TILES | BRF_GRA },
	
	{ "13003.rom",     0x40000, 0x21424151, SYS16_ROM_SPRITES | BRF_GRA },
	{ "13006.rom",     0x40000, 0x2e9afd2f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "13004.rom",     0x40000, 0x0aa09dd3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "13007.rom",     0x40000, 0x55c8605b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "13005.rom",     0x40000, 0xc899c810, SYS16_ROM_SPRITES | BRF_GRA },
	{ "13008.rom",     0x40000, 0xb3d46dfc, SYS16_ROM_SPRITES | BRF_GRA },
	{ "13009.rom",     0x40000, 0x126d2e37, SYS16_ROM_SPRITES | BRF_GRA },
	{ "13010.rom",     0x40000, 0xdf37c567, SYS16_ROM_SPRITES | BRF_GRA },

	{ "13002.rom",     0x08000, 0x1b6e1515, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "13001.rom",     0x40000, 0xe8cace8c, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0143.key",  0x02000, 0xfba2e8da, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Mvp);
STD_ROM_FN(Mvp);

static struct BurnRomInfo MvpjRomDesc[] = {
	{ "epr12967.a7",   0x20000, 0xe53ac137, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12965.a5",   0x20000, 0x4266cb9e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12968.a8",   0x20000, 0x91c772ac, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12966.a6",   0x20000, 0x39365a79, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr12971.a14",  0x20000, 0x245dcd1f, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12983.b14",  0x20000, 0xf3570fc9, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12972.a15",  0x20000, 0xff7c4278, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12984.b15",  0x20000, 0xd37d1876, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12973.a16",  0x20000, 0x8dc9b9ea, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12985.b16",  0x20000, 0xe3f33a8a, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr12974.b1",   0x20000, 0xe1da5597, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12977.b5",   0x20000, 0xb9eb9762, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12975.b2",   0x20000, 0x364d51d1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12978.b6",   0x20000, 0x014b5442, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12976.b3",   0x20000, 0x43b549c0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12979.b7",   0x20000, 0x20f603f8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12962.a1",   0x20000, 0x9b678da3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12980.b10",  0x20000, 0x883b792a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12963.a2",   0x20000, 0x8870f95a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12981.b11",  0x20000, 0x48636cb0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12964.a3",   0x20000, 0xf9148c5d, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12982.b12",  0x20000, 0xc4453292, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12969.a10",  0x08000, 0xec621893, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr12970.a11",  0x20000, 0x8f7d7657, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0142.key",  0x02000, 0x90468045, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Mvpj);
STD_ROM_FN(Mvpj);

static struct BurnRomInfo PassshtRomDesc[] = {
	{ "epr11871.a4",   0x10000, 0x0f9ccea5, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11870.a1",   0x10000, 0xdf43ebcf, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "opr11854.b9",   0x10000, 0xd31c0b6c, SYS16_ROM_TILES | BRF_GRA },
	{ "opr11855.b10",  0x10000, 0xb78762b4, SYS16_ROM_TILES | BRF_GRA },
	{ "opr11856.b11",  0x10000, 0xea49f666, SYS16_ROM_TILES | BRF_GRA },
	
	{ "opr11862.b1",   0x10000, 0xb6e94727, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11865.b5",   0x10000, 0x17e8d5d5, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11863.b2",   0x10000, 0x3e670098, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11866.b6",   0x10000, 0x50eb71cc, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11864.b3",   0x10000, 0x05733ca8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11867.b7",   0x10000, 0x81e49697, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr11857.a7",   0x08000, 0x789edc06, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr11858.a8",   0x08000, 0x08ab0018, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr11859.a9",   0x08000, 0x8673e01b, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr11860.a10",  0x08000, 0x10263746, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr11861.a11",  0x08000, 0x38b54a71, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0080.key",  0x02000, 0x222d016f, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Passsht);
STD_ROM_FN(Passsht);

static struct BurnRomInfo PassshtaRomDesc[] = {
	{ "8.4a",          0x10000, 0xb84dc139, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "5.1a",          0x10000, 0xeffe29df, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "opr11854.b9",   0x10000, 0xd31c0b6c, SYS16_ROM_TILES | BRF_GRA },
	{ "opr11855.b10",  0x10000, 0xb78762b4, SYS16_ROM_TILES | BRF_GRA },
	{ "opr11856.b11",  0x10000, 0xea49f666, SYS16_ROM_TILES | BRF_GRA },
	
	{ "opr11862.b1",   0x10000, 0xb6e94727, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11865.b5",   0x10000, 0x17e8d5d5, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11863.b2",   0x10000, 0x3e670098, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11866.b6",   0x10000, 0x50eb71cc, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11864.b3",   0x10000, 0x05733ca8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11867.b7",   0x10000, 0x81e49697, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr11857.a7",   0x08000, 0x789edc06, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr11858.a8",   0x08000, 0x08ab0018, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr11859.a9",   0x08000, 0x8673e01b, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr11860.a10",  0x08000, 0x10263746, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr11861.a11",  0x08000, 0x38b54a71, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0074.key",  0x02000, 0x71bd232d, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Passshta);
STD_ROM_FN(Passshta);

static struct BurnRomInfo PassshtjRomDesc[] = {
	{ "epr11853.a4",   0x10000, 0xfab337e7, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11852.a1",   0x10000, 0x892a81fc, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "opr11854.b9",   0x10000, 0xd31c0b6c, SYS16_ROM_TILES | BRF_GRA },
	{ "opr11855.b10",  0x10000, 0xb78762b4, SYS16_ROM_TILES | BRF_GRA },
	{ "opr11856.b11",  0x10000, 0xea49f666, SYS16_ROM_TILES | BRF_GRA },
	
	{ "opr11862.b1",   0x10000, 0xb6e94727, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11865.b5",   0x10000, 0x17e8d5d5, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11863.b2",   0x10000, 0x3e670098, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11866.b6",   0x10000, 0x50eb71cc, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11864.b3",   0x10000, 0x05733ca8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11867.b7",   0x10000, 0x81e49697, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr11857.a7",   0x08000, 0x789edc06, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr11858.a8",   0x08000, 0x08ab0018, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr11859.a9",   0x08000, 0x8673e01b, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr11860.a10",  0x08000, 0x10263746, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr11861.a11",  0x08000, 0x38b54a71, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0070.key",  0x02000, 0x5d0308aa, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Passshtj);
STD_ROM_FN(Passshtj);

static struct BurnRomInfo RiotcityRomDesc[] = {
	{ "epr14612.bin",  0x20000, 0xa1b331ec, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr14610.bin",  0x20000, 0xcd4f2c50, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr14613.bin",  0x20000, 0x0659df4c, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr14611.bin",  0x20000, 0xd9e6f80b, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "epr14616.bin",  0x20000, 0x46d30368, SYS16_ROM_TILES | BRF_GRA },
	{ "epr14625.bin",  0x20000, 0xabfb80fe, SYS16_ROM_TILES | BRF_GRA },
	{ "epr14617.bin",  0x20000, 0x884e40f9, SYS16_ROM_TILES | BRF_GRA },
	{ "epr14626.bin",  0x20000, 0x4ef55846, SYS16_ROM_TILES | BRF_GRA },
	{ "epr14618.bin",  0x20000, 0x00eb260e, SYS16_ROM_TILES | BRF_GRA },
	{ "epr14627.bin",  0x20000, 0x961e5f82, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr14619.bin",  0x40000, 0x6f2b5ef7, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr14622.bin",  0x40000, 0x7ca7e40d, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr14620.bin",  0x40000, 0x66183333, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr14623.bin",  0x40000, 0x98630049, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr14621.bin",  0x40000, 0xc0f2820e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr14624.bin",  0x40000, 0xd1a68448, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr14614.bin",  0x10000, 0xc65cc69a, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr14615.bin",  0x20000, 0x46653db1, SYS16_ROM_UPD7759DATA | BRF_SND },
};


STD_ROM_PICK(Riotcity);
STD_ROM_FN(Riotcity);

static struct BurnRomInfo RyukyuRomDesc[] = {
	{ "epr13348.a7",    0x10000, 0x5f0e0c86, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr13347.a5",    0x10000, 0x398031fa, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "opr13351.a14",   0x20000, 0xa68a4e6d, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13352.a15",   0x20000, 0x5e5531e4, SYS16_ROM_TILES | BRF_GRA },
	{ "opr13353.a16",   0x20000, 0x6d23dfd8, SYS16_ROM_TILES | BRF_GRA },
	
	{ "opr13354.b1",    0x20000, 0xf07aad99, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13356.b5",    0x20000, 0x5498290b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13355.b2",    0x20000, 0x67890019, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr13357.b6",    0x20000, 0xf9e7cf03, SYS16_ROM_SPRITES | BRF_GRA },
		
	{ "epr13349.a10",   0x08000, 0xb83183f8, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "opr13350.a11",   0x20000, 0x3c59a658, SYS16_ROM_UPD7759DATA | BRF_SND },
		
	{ "317-5023.key",   0x02000, 0x43704331, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Ryukyu);
STD_ROM_FN(Ryukyu);

static struct BurnRomInfo SdibRomDesc[] = {
	{ "epr10986a.a4",  0x08000, 0x3e136215, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10984a.a1",  0x08000, 0x44bf3cf5, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10987a.a5",  0x08000, 0xcfd79404, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10985a.a2",  0x08000, 0x1c21a03f, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10829.a6",   0x08000, 0xa431ab08, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10826.a3",   0x08000, 0x2ed8e4b7, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr10772.b9",   0x10000, 0x182b6301, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10773.b10",  0x10000, 0x8f7129a2, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10774.b11",  0x10000, 0x4409411f, SYS16_ROM_TILES | BRF_GRA },
	
	{ "10760.b1",      0x10000, 0x70de327b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10763.b5",      0x10000, 0x99ec5cb5, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10761.b2",      0x10000, 0x4e80f80d, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10764.b6",      0x10000, 0x602da5d5, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10762.b3",      0x10000, 0x464b5f78, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10765.b7",      0x10000, 0x0a73a057, SYS16_ROM_SPRITES | BRF_GRA },

	{ "10775.a7",      0x08000, 0x4cbd55a8, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Sdib);
STD_ROM_FN(Sdib);

static struct BurnRomInfo SdiblRomDesc[] = {
	{ "a4.rom",        0x08000, 0xf2c41dd6, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "a1.rom",        0x08000, 0xa9f816ef, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "a5.rom",        0x08000, 0x7952e27e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "a2.rom",        0x08000, 0x369af326, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "a6.rom",        0x08000, 0x8ee2c287, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "a3.rom",        0x08000, 0x193e4231, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr10772.b9",   0x10000, 0x182b6301, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10773.b10",  0x10000, 0x8f7129a2, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10774.b11",  0x10000, 0x4409411f, SYS16_ROM_TILES | BRF_GRA },
	
	{ "b1.rom",        0x10000, 0x30e2c50a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "b5.rom",        0x10000, 0x794e3e8b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "b2.rom",        0x10000, 0x6a8b3fd0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10764.b6",      0x10000, 0x602da5d5, SYS16_ROM_SPRITES | BRF_GRA },
	{ "b3.rom",        0x10000, 0xb9de3aeb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10765.b7",      0x10000, 0x0a73a057, SYS16_ROM_SPRITES | BRF_GRA },

	{ "a7.rom",        0x08000, 0x793f9f7f, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Sdibl);
STD_ROM_FN(Sdibl);

static struct BurnRomInfo DefenseRomDesc[] = {
	{ "epr10917a.a4",  0x08000, 0xd91ac47c, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10915.a1",   0x08000, 0x7344c510, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10918a.a5",  0x08000, 0xe41befcd, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10916a.a2",  0x08000, 0x7f58ba12, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10829.a6",   0x08000, 0xa431ab08, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10826.a3",   0x08000, 0x2ed8e4b7, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "10919.b9",      0x10000, 0x23b88f82, SYS16_ROM_TILES | BRF_GRA },
	{ "10920.b10",     0x10000, 0x22b1fb4c, SYS16_ROM_TILES | BRF_GRA },
	{ "10921.b11",     0x10000, 0x7788f55d, SYS16_ROM_TILES | BRF_GRA },
	
	{ "10760.b1",      0x10000, 0x70de327b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10763.b5",      0x10000, 0x99ec5cb5, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10761.b2",      0x10000, 0x4e80f80d, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10764.b6",      0x10000, 0x602da5d5, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10762.b3",      0x10000, 0x464b5f78, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10765.b7",      0x10000, 0x0a73a057, SYS16_ROM_SPRITES | BRF_GRA },

	{ "10775.a7",      0x08000, 0x4cbd55a8, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Defense);
STD_ROM_FN(Defense);

static struct BurnRomInfo Shinobi2RomDesc[] = {
	{ "epr11282.a4",   0x10000, 0x5f2e5524, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11280.a1",   0x10000, 0xbdfe5c38, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11283.a5",   0x10000, 0x9d46e707, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11281.a2",   0x10000, 0x7961d07e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr11284.b9",   0x10000, 0x5f62e163, SYS16_ROM_TILES | BRF_GRA },
	{ "epr11285.b10",  0x10000, 0x75f8fbc9, SYS16_ROM_TILES | BRF_GRA },
	{ "epr11286.b11",  0x10000, 0x06508bb9, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr11290.10",   0x10000, 0x611f413a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11294.11",   0x10000, 0x5eb00fc1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11291.17",   0x10000, 0x3c0797c0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11295.18",   0x10000, 0x25307ef8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11292.23",   0x10000, 0xc29ac34e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11296.24",   0x10000, 0x04a437f8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11293.29",   0x10000, 0x41f41063, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11297.30",   0x10000, 0xb6e1fd72, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr11287.a7",   0x08000, 0xe8cccd42, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr11288.a8",   0x08000, 0xc8df8460, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr11289.a9",   0x08000, 0xe5a4cf30, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0049.key",  0x02000, 0x8fac824f, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Shinobi2);
STD_ROM_FN(Shinobi2);

static struct BurnRomInfo Shinobi3RomDesc[] = {
	{ "epr11299.a4",   0x10000, 0xb930399d, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11298.a1",   0x10000, 0x343f4c46, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11283.a5",   0x10000, 0x9d46e707, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11281.a2",   0x10000, 0x7961d07e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr11284.b9",   0x10000, 0x5f62e163, SYS16_ROM_TILES | BRF_GRA },
	{ "epr11285.b10",  0x10000, 0x75f8fbc9, SYS16_ROM_TILES | BRF_GRA },
	{ "epr11286.b11",  0x10000, 0x06508bb9, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr11290.10",   0x10000, 0x611f413a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11294.11",   0x10000, 0x5eb00fc1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11291.17",   0x10000, 0x3c0797c0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11295.18",   0x10000, 0x25307ef8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11292.23",   0x10000, 0xc29ac34e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11296.24",   0x10000, 0x04a437f8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11293.29",   0x10000, 0x41f41063, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11297.30",   0x10000, 0xb6e1fd72, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr11372.a7",   0x08000, 0x0824269a, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr11288.a8",   0x08000, 0xc8df8460, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr11289.a9",   0x08000, 0xe5a4cf30, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0054.key",  0x02000, 0x39fd4535, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Shinobi3);
STD_ROM_FN(Shinobi3);

static struct BurnRomInfo Shinobi4RomDesc[] = {
	{ "epr11360.a7",   0x20000, 0xb1f67ab9, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11359.a6",   0x20000, 0x0f0306e1, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr11284.b9",   0x10000, 0x5f62e163, SYS16_ROM_TILES | BRF_GRA },
	{ "epr11285.b10",  0x10000, 0x75f8fbc9, SYS16_ROM_TILES | BRF_GRA },
	{ "epr11286.b11",  0x10000, 0x06508bb9, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr11290.10",   0x10000, 0x611f413a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11294.11",   0x10000, 0x5eb00fc1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11291.17",   0x10000, 0x3c0797c0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11295.18",   0x10000, 0x25307ef8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11292.23",   0x10000, 0xc29ac34e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11296.24",   0x10000, 0x04a437f8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11293.29",   0x10000, 0x41f41063, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11297.30",   0x10000, 0xb6e1fd72, SYS16_ROM_SPRITES | BRF_GRA },

	{ "eprxxxxx.a10",  0x08000, 0x1f47ebcb, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr11288.a8",   0x08000, 0xc8df8460, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr11289.a9",   0x08000, 0xe5a4cf30, SYS16_ROM_UPD7759DATA | BRF_SND },
};


STD_ROM_PICK(Shinobi4);
STD_ROM_FN(Shinobi4);

static struct BurnRomInfo SjryukoRomDesc[] = {
	{ "epr12256.a4",   0x08000, 0x5987ee1b, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12253.a1",   0x08000, 0x26a822df, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12257.a5",   0x08000, 0x3a2acc3f, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12254.a2",   0x08000, 0x7e908217, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "12224-95.b9",   0x08000, 0xeac17ba1, SYS16_ROM_TILES | BRF_GRA },
	{ "12225-94.b10",  0x08000, 0x2310fc98, SYS16_ROM_TILES | BRF_GRA },
	{ "12226-93.b11",  0x08000, 0x210e6999, SYS16_ROM_TILES | BRF_GRA },
	
	{ "12232-10.b1",   0x10000, 0x0adec62b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12236-11.b5",   0x10000, 0x286b9af8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12233-17.b2",   0x10000, 0x3e45969c, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12237-18.b6",   0x10000, 0xe5058e96, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12234-23.b3",   0x10000, 0x8c8d54ef, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12238-24.b7",   0x10000, 0x7ada3304, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12235-29.b4",   0x10000, 0xfa45d511, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12239-30.b8",   0x10000, 0x91f70c8b, SYS16_ROM_SPRITES | BRF_GRA },
	
	{ "epr12244.a7",   0x08000, 0xcb2a47e5, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr12245.a8",   0x08000, 0x66164134, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr12246.a9",   0x08000, 0xf1242582, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr12247.a10",  0x08000, 0xef8a64c6, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr12248.a11",  0x08000, 0xd1eabdab, SYS16_ROM_UPD7759DATA | BRF_SND },
};


STD_ROM_PICK(Sjryuko);
STD_ROM_FN(Sjryuko);

static struct BurnRomInfo SonicbomRomDesc[] = {
	{ "epr11342.a4",   0x10000, 0x454693f1, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11340.a1",   0x10000, 0x03ba3fed, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11343.a5",   0x10000, 0xedfeb7d4, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11341.a2",   0x10000, 0x0338f771, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "opr11344.b9",   0x10000, 0x59a9f940, SYS16_ROM_TILES | BRF_GRA },
	{ "opr11345.b10",  0x10000, 0xb44c068b, SYS16_ROM_TILES | BRF_GRA },
	{ "opr11346.b11",  0x10000, 0xe5ada66c, SYS16_ROM_TILES | BRF_GRA },
	
	{ "opr11350.b1",   0x10000, 0x525ba1df, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11354.b5",   0x10000, 0x793fa3ac, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11351.b2",   0x10000, 0x63b1f1ca, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11355.b6",   0x10000, 0xfe0fa332, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11352.b3",   0x10000, 0x047fa4b0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11356.b7",   0x10000, 0xaea3c39d, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11353.b4",   0x10000, 0x4e0791f8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr11357.b8",   0x10000, 0xa7c5ea41, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr11347.a7",   0x08000, 0xb41f0ced, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr11348.a8",   0x08000, 0x89924588, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr11349.a9",   0x08000, 0x8e4b6204, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0053.key",  0x02000, 0x91c80c88, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Sonicbom);
STD_ROM_FN(Sonicbom);

static struct BurnRomInfo Tetris1RomDesc[] = {
	{ "epr12164.a4",   0x08000, 0xb329cd6f, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12163.a1",   0x08000, 0xd372d3f3, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
		
	{ "epr12165.b9",   0x10000, 0x62640221, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12166.b10",  0x10000, 0x9abd183b, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12167.b11",  0x10000, 0x2495fd4e, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr12169.b1",   0x08000, 0xdacc6165, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12170.b5",   0x08000, 0x87354e42, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12168.a7",   0x08000, 0xbd9ba01b, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "317-0091.key",  0x02000, 0xa7937661, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Tetris1);
STD_ROM_FN(Tetris1);

static struct BurnRomInfo Tetris2RomDesc[] = {
	{ "epr12193.rom",  0x10000, 0x9ce15ac9, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12192.rom",  0x10000, 0x98d590ca, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
		
	{ "epr12165.b9",   0x10000, 0x62640221, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12166.b10",  0x10000, 0x9abd183b, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12167.b11",  0x10000, 0x2495fd4e, SYS16_ROM_TILES | BRF_GRA },
	
	{ "obj0-o.rom",    0x10000, 0x2fb38880, SYS16_ROM_SPRITES | BRF_GRA },
	{ "obj0-e.rom",    0x10000, 0xd6a02cba, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12168.a7",   0x08000, 0xbd9ba01b, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "317-0092.key",  0x02000, 0xd10e1ad9, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Tetris2);
STD_ROM_FN(Tetris2);

static struct BurnRomInfo TimescanRomDesc[] = {
	{ "epr10853.a4",   0x08000, 0x24d7c5fb, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10850.a1",   0x08000, 0xf1575732, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10854.a5",   0x08000, 0x82d0b237, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10851.a2",   0x08000, 0xf5ce271b, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10855.a6",   0x08000, 0x63e95a53, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10852.a3",   0x08000, 0x7cd1382b, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr10543.b9",   0x08000, 0x07dccc37, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10544.b10",  0x08000, 0x84fb9a3a, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10545.b11",  0x08000, 0xc8694bc0, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr10548.b1",   0x08000, 0xaa150735, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10552.b5",   0x08000, 0x6fcbb9f7, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10549.b2",   0x08000, 0x2f59f067, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10553.b6",   0x08000, 0x8a220a9f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10550.b3",   0x08000, 0xf05069ff, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10554.b7",   0x08000, 0xdc64f809, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10551.b4",   0x08000, 0x435d811f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10555.b8",   0x08000, 0x2143c471, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr10562.a7",   0x08000, 0x3f5028bf, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr10563.a8",   0x08000, 0x9db7eddf, SYS16_ROM_UPD7759DATA | BRF_SND },
};


STD_ROM_PICK(Timescan);
STD_ROM_FN(Timescan);

static struct BurnRomInfo ToryumonRomDesc[] = {
	{ "epr17689.a2",   0x20000, 0x4f0dee19, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr17688.a1",   0x20000, 0x717d81c7, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr17700.b11",  0x40000, 0x8f288b37, SYS16_ROM_TILES | BRF_GRA },
	{ "epr17701.b12",  0x40000, 0x6dfb025b, SYS16_ROM_TILES | BRF_GRA },
	{ "epr17702.b13",  0x40000, 0xae0b7eab, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr17692.b1",   0x20000, 0x543c4327, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr17695.b4",   0x20000, 0xee60f244, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr17693.b2",   0x20000, 0x4a350b3e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr17696.b5",   0x20000, 0x6edb54f1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr17694.b3",   0x20000, 0xb296d71d, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr17697.b6",   0x20000, 0x6ccb7b28, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr17698.b7",   0x20000, 0xcd4dfb82, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr17699.b8",   0x20000, 0x2694ecce, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr17691.a13",  0x08000, 0x14205388, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr17690.a11",  0x40000, 0x4f9ba4e4, SYS16_ROM_UPD7759DATA | BRF_SND },
};


STD_ROM_PICK(Toryumon);
STD_ROM_FN(Toryumon);

static struct BurnRomInfo TturfRomDesc[] = {
	{ "12327.a7",      0x20000, 0x0376c593, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "12326.a5",      0x20000, 0xf998862b, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "12268.a14",     0x10000, 0xe0dac07f, SYS16_ROM_TILES | BRF_GRA },
	{ "12269.a15",     0x10000, 0x457a8790, SYS16_ROM_TILES | BRF_GRA },
	{ "12270.a16",     0x10000, 0x69fc025b, SYS16_ROM_TILES | BRF_GRA },
	
	{ "12279.b1",      0x10000, 0x7a169fb1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12283.b5",      0x10000, 0xae0fa085, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12278.b2",      0x10000, 0x961d06b7, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12282.b6",      0x10000, 0xe8671ee1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12277.b3",      0x10000, 0xf16b6ba2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12281.b7",      0x10000, 0x1ef1077f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12276.b4",      0x10000, 0x838bd71f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12280.b8",      0x10000, 0x639a57cb, SYS16_ROM_SPRITES | BRF_GRA },

	{ "12328.a10",     0x08000, 0x00000000, SYS16_ROM_Z80PROG | BRF_NODUMP | BRF_PRG },
	
	{ "12329.a11",     0x10000, 0xed9a686d, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "12330.a12",     0x10000, 0xfb762bca, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0104.bin",  0x01000, 0x00000000, BRF_NODUMP },
};


STD_ROM_PICK(Tturf);
STD_ROM_FN(Tturf);

static struct BurnRomInfo TturfuRomDesc[] = {
	{ "epr12266.bin",  0x10000, 0xf549def8, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12264.bin",  0x10000, 0xf7cdb289, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12267.bin",  0x10000, 0x3c3ce191, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12265.bin",  0x10000, 0x8cdadd9a, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "12268.a14",     0x10000, 0xe0dac07f, SYS16_ROM_TILES | BRF_GRA },
	{ "12269.a15",     0x10000, 0x457a8790, SYS16_ROM_TILES | BRF_GRA },
	{ "12270.a16",     0x10000, 0x69fc025b, SYS16_ROM_TILES | BRF_GRA },
	
	{ "12276.b4",      0x10000, 0x838bd71f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12280.b8",      0x10000, 0x639a57cb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12277.b3",      0x10000, 0xf16b6ba2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12281.b7",      0x10000, 0x1ef1077f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12278.b2",      0x10000, 0x961d06b7, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12282.b6",      0x10000, 0xe8671ee1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12279.b1",      0x10000, 0x7a169fb1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "12283.b5",      0x10000, 0xae0fa085, SYS16_ROM_SPRITES | BRF_GRA },
	
	{ "epr12271.a7",   0x08000, 0x99671e52, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "epr12272.a8",   0x08000, 0x7cf7e69f, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr12273.a9",   0x08000, 0x28f0bb8b, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr12274.a10",  0x08000, 0x8207f0c4, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "epr12275.a11",  0x08000, 0x182f3c3d, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0099.bin",  0x01000, 0x00000000, BRF_NODUMP },
};


STD_ROM_PICK(Tturfu);
STD_ROM_FN(Tturfu);

static struct BurnRomInfo Wb3RomDesc[] = {
	{ "epr12259.a7",   0x20000, 0x54927c7e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12258.a5",   0x20000, 0x01f5898c, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "epr12124.a14",  0x10000, 0xdacefb6f, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12125.a15",  0x10000, 0x9fc36df7, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12126.a16",  0x10000, 0xa693fd94, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr12090.b1",   0x10000, 0xaeeecfca, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12094.b5",   0x10000, 0x615e4927, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12091.b2",   0x10000, 0x8409a243, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12095.b6",   0x10000, 0xe774ec2c, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12092.b3",   0x10000, 0x5c2f0d90, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12096.b7",   0x10000, 0x0cd59d6e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12093.b4",   0x10000, 0x4891e7bb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12097.b8",   0x10000, 0xe645902c, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12127.a10",  0x08000, 0x0bb901bb, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "317-0098.bin",  0x01000, 0x00000000, BRF_NODUMP }
};


STD_ROM_PICK(Wb3);
STD_ROM_FN(Wb3);

static struct BurnRomInfo Wb32RomDesc[] = {
	{ "epr12100.a6",   0x10000, 0xf5ca4abc, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12098.a1",   0x10000, 0xd998e5e5, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12101.a5",   0x10000, 0x6146492b, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12099.a2",   0x10000, 0x3e243b45, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
		
	{ "epr12124.b9",   0x10000, 0xdacefb6f, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12125.b10",  0x10000, 0x9fc36df7, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12126.b11",  0x10000, 0xa693fd94, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr12090.b1",   0x10000, 0xaeeecfca, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12094.b5",   0x10000, 0x615e4927, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12091.b2",   0x10000, 0x8409a243, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12095.b6",   0x10000, 0xe774ec2c, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12092.b3",   0x10000, 0x5c2f0d90, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12096.b7",   0x10000, 0x0cd59d6e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12093.b4",   0x10000, 0x4891e7bb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12097.b8",   0x10000, 0xe645902c, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12127.a7",   0x08000, 0x0bb901bb, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "317-0085.key",  0x02000, 0x8150f38d, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Wb32);
STD_ROM_FN(Wb32);

static struct BurnRomInfo Wb33RomDesc[] = {
	{ "epr12137.a7",   0x20000, 0x6f81238e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12136.a5",   0x20000, 0x4cf05003, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
		
	{ "epr12124.a14",  0x10000, 0xdacefb6f, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12125.a15",  0x10000, 0x9fc36df7, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12126.a16",  0x10000, 0xa693fd94, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr12090.b1",   0x10000, 0xaeeecfca, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12094.b5",   0x10000, 0x615e4927, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12091.b2",   0x10000, 0x8409a243, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12095.b6",   0x10000, 0xe774ec2c, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12092.b3",   0x10000, 0x5c2f0d90, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12096.b7",   0x10000, 0x0cd59d6e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12093.b4",   0x10000, 0x4891e7bb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12097.b8",   0x10000, 0xe645902c, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12127.a10",  0x08000, 0x0bb901bb, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "317-0089.key",  0x02000, 0x597d30d3, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Wb33);
STD_ROM_FN(Wb33);

static struct BurnRomInfo Wb34RomDesc[] = {
	{ "epr12131.a7",   0x20000, 0xb95ecf88, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12128.a5",   0x20000, 0xb711372b, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
		
	{ "epr12124.a14",  0x10000, 0xdacefb6f, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12125.a15",  0x10000, 0x9fc36df7, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12126.a16",  0x10000, 0xa693fd94, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr12090.b1",   0x10000, 0xaeeecfca, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12094.b5",   0x10000, 0x615e4927, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12091.b2",   0x10000, 0x8409a243, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12095.b6",   0x10000, 0xe774ec2c, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12092.b3",   0x10000, 0x5c2f0d90, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12096.b7",   0x10000, 0x0cd59d6e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12093.b4",   0x10000, 0x4891e7bb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12097.b8",   0x10000, 0xe645902c, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12127.a10",  0x08000, 0x0bb901bb, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "317-0087.key",  0x02000, 0x162cb531, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Wb34);
STD_ROM_FN(Wb34);

static struct BurnRomInfo WrestwarRomDesc[] = {
	{ "epr12372.a7",   0x20000, 0xeeaba126, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12371.a5",   0x20000, 0x6714600a, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12146.a8",   0x20000, 0xb77ba665, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12144.a6",   0x20000, 0xddf075cb, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12150.a14",  0x20000, 0x6a821ab9, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr12151.a15",  0x20000, 0x2b1a0751, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr12152.a16",  0x20000, 0xf6e190fe, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr12153.b1",   0x20000, 0xffa7d368, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12157.b5",   0x20000, 0x8d7794c1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12154.b2",   0x20000, 0x0ed343f2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12158.b6",   0x20000, 0x99458d58, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12155.b3",   0x20000, 0x3087104d, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12159.b7",   0x20000, 0xabcf9bed, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12156.b4",   0x20000, 0x41b6068b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12160.b8",   0x20000, 0x97eac164, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12141.a1",   0x20000, 0x260311c5, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12161.b10",  0x20000, 0x35a4b1b1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12142.a2",   0x10000, 0x12e38a5c, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12162.b11",  0x10000, 0xfa06fd24, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12147.a10",  0x08000, 0xc3609607, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12148.a11",  0x20000, 0xfb9a7f29, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "mpr12149.a12",  0x20000, 0xd6617b19, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0103.bin",  0x01000, 0x00000000, BRF_NODUMP }
};


STD_ROM_PICK(Wrestwar);
STD_ROM_FN(Wrestwar);

static struct BurnRomInfo Wrestwa1RomDesc[] = {
	{ "epr12145.a7",   0x20000, 0x2af51e2e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12143.a5",   0x20000, 0x4131e345, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12146.a8",   0x20000, 0xb77ba665, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12144.a6",   0x20000, 0xddf075cb, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12150.a14",  0x20000, 0x6a821ab9, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr12151.a15",  0x20000, 0x2b1a0751, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr12152.a16",  0x20000, 0xf6e190fe, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr12153.b1",   0x20000, 0xffa7d368, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12157.b5",   0x20000, 0x8d7794c1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12154.b2",   0x20000, 0x0ed343f2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12158.b6",   0x20000, 0x99458d58, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12155.b3",   0x20000, 0x3087104d, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12159.b7",   0x20000, 0xabcf9bed, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12156.b4",   0x20000, 0x41b6068b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12160.b8",   0x20000, 0x97eac164, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12141.a1",   0x20000, 0x260311c5, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12161.b10",  0x20000, 0x35a4b1b1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12142.a2",   0x10000, 0x12e38a5c, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12162.b11",  0x10000, 0xfa06fd24, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12147.a10",  0x08000, 0xc3609607, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12148.a11",  0x20000, 0xfb9a7f29, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "mpr12149.a12",  0x20000, 0xd6617b19, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0090.key",  0x02000, 0xb7c24c4a, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Wrestwa1);
STD_ROM_FN(Wrestwa1);

static struct BurnRomInfo Wrestwa2RomDesc[] = {
	{ "epr12370.a7",   0x20000, 0xcb5dbb76, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12369.a5",   0x20000, 0x6f47dd2f, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12146.a8",   0x20000, 0xb77ba665, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12144.a6",   0x20000, 0xddf075cb, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12150.a14",  0x20000, 0x6a821ab9, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr12151.a15",  0x20000, 0x2b1a0751, SYS16_ROM_TILES | BRF_GRA },
	{ "mpr12152.a16",  0x20000, 0xf6e190fe, SYS16_ROM_TILES | BRF_GRA },
	
	{ "mpr12153.b1",   0x20000, 0xffa7d368, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12157.b5",   0x20000, 0x8d7794c1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12154.b2",   0x20000, 0x0ed343f2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12158.b6",   0x20000, 0x99458d58, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12155.b3",   0x20000, 0x3087104d, SYS16_ROM_SPRITES | BRF_GRA },
	{ "mpr12159.b7",   0x20000, 0xabcf9bed, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12156.b4",   0x20000, 0x41b6068b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12160.b8",   0x20000, 0x97eac164, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12141.a1",   0x20000, 0x260311c5, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12161.b10",  0x20000, 0x35a4b1b1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12142.a2",   0x10000, 0x12e38a5c, SYS16_ROM_SPRITES | BRF_GRA },
	{ "opr12162.b11",  0x10000, 0xfa06fd24, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12147.a10",  0x08000, 0xc3609607, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "mpr12148.a11",  0x20000, 0xfb9a7f29, SYS16_ROM_UPD7759DATA | BRF_SND },
	{ "mpr12149.a12",  0x20000, 0xd6617b19, SYS16_ROM_UPD7759DATA | BRF_SND },
	
	{ "317-0102.key",  0x02000, 0x28ba1bf0, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Wrestwa2);
STD_ROM_FN(Wrestwa2);

/*====================================================
Memory Handlers
====================================================*/

unsigned short __fastcall System16BReadWord(unsigned int a)
{
#if 0 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("68000 Read Word -> 0x%06X\n"), a);
#endif

	return 0xffff;
}

unsigned char __fastcall System16BReadByte(unsigned int a)
{
	switch (a) {
		case 0xc41001: {
			return 0xff - System16Input[0];
		}
		
		case 0xc41003: {
			return 0xff - System16Input[1];
		}
		
		case 0xc41005: {
			return System16Dip[2];
		}
		
		case 0xc41007: {
			return 0xff - System16Input[2];
		}
		
		case 0xc42001: {
			return System16Dip[0];
		}

		case 0xc42003: {
			return System16Dip[1];
		}
	}
	
#if 0 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("68000 Read Byte -> 0x%06X\n"), a);
#endif

	return 0xff;
}

void __fastcall System16BWriteWord(unsigned int a, unsigned short d)
{
#if 0 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("68000 Write Word -> 0x%06X, 0x%04X\n"), a, d);
#endif
}

void __fastcall System16BWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0xc40001: {
			System16VideoEnable = d & 0x20;
			System16ScreenFlip = d & 0x40;
			return;
		}
		
		case 0xfe0007: {
			System16SoundLatch = d & 0xff;
			ZetRaiseIrq(0);
			return;
		}
	}

#if 0 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("68000 Write Byte -> 0x%06X, 0x%02X\n"), a, d);
#endif
}

void __fastcall AliensynWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0xc00007: {
			System16SoundLatch = d & 0xff;
			ZetRaiseIrq(0);
			return;
		}
	}
}

void __fastcall AurailWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0xfc0001: {
			System16TileBanks[0] = d & 0x07;
			return;
		}
		
		case 0xfc0003: {
			System16TileBanks[1] = d & 0x07;
			return;
		}
	}
}

unsigned char __fastcall BayrouteReadByte(unsigned int a)
{
	switch (a) {
		case 0x901001: {
			return 0xff - System16Input[0];
		}
		
		case 0x901003: {
			return 0xff - System16Input[1];
		}
		
		case 0x901007: {
			return 0xff - System16Input[2];
		}
		
		case 0x902001: {
			return System16Dip[0];
		}

		case 0x902003: {
			return System16Dip[1];
		}
	}

	return 0xff;
}

void __fastcall BayrouteWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x900001: {
			System16VideoEnable = d & 0x20;
			System16ScreenFlip = d & 0x40;
			return;
		}
		
		case 0xff0007: {
			System16SoundLatch = d & 0xff;
			ZetRaiseIrq(0);
			return;
		}
	}
}

unsigned char __fastcall BulletReadByte(unsigned int a)
{
	switch (a) {
		case 0xc41001: {
			return 0xff - System16Input[0];
		}
		
		case 0xc41003: {
			return 0xff - System16Input[1];
		}
		
		case 0xc41005: {
			return 0xff - System16Input[3];
		}
		
		case 0xc41007: {
			return 0xff - System16Input[2];
		}
		
		case 0xc42001: {
			return System16Dip[0];
		}

		case 0xc42003: {
			return System16Dip[1];
		}
	}

	return 0xff;
}

void __fastcall BulletWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0xc00007: {
			System16SoundLatch = d & 0xff;
			ZetRaiseIrq(0);
			return;
		}
	}
}

unsigned char __fastcall CottonReadByte(unsigned int a)
{
	switch (a) {
		case 0x601001: {
			return 0xff - System16Input[0];
		}
		
		case 0x601003: {
			return 0xff - System16Input[1];
		}
		
		case 0x601005: {
			return 0xff;
		}
		
		case 0x601007: {
			return 0xff - System16Input[2];
		}
		
		case 0x602001: {
			return System16Dip[0];
		}

		case 0x602003: {
			return System16Dip[1];
		}
		
		case 0x7038f7: {
			return (System16Rom[SekGetPC(0) + 1] << 8) | System16Rom[SekGetPC(0) + 0];
		}
	}
	
#if 1 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("68000 Read Byte -> 0x%06X\n"), a);
#endif

	return 0xff;
}

void __fastcall CottonWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x100001: {
			System16TileBanks[0] = d & 0x07;
			return;
		}
		
		case 0x100003: {
			System16TileBanks[1] = d & 0x07;
			return;
		}
	
		case 0x600001: {
			System16VideoEnable = d & 0x20;
			System16ScreenFlip = d & 0x40;
			return;
		}
		
		case 0xff0007: {
			System16SoundLatch = d & 0xff;
			ZetRaiseIrq(0);
			return;
		}
	}

#if 0 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("68000 Write Byte -> 0x%06X, 0x%02X\n"), a, d);
#endif
}

void __fastcall DduxWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x3f0001: {
			System16TileBanks[0] = d & 0x07;
			return;
		}
		
		case 0x3f0003: {
			System16TileBanks[1] = d & 0x07;
			return;
		}
	}
}

static short DunkshotTrack1X = 0;
static short DunkshotTrack1Y = 0;
static short DunkshotTrack2X = 0;
static short DunkshotTrack2Y = 0;
static short DunkshotTrack3X = 0;
static short DunkshotTrack3Y = 0;
static short DunkshotTrack4X = 0;
static short DunkshotTrack4Y = 0;

void DunkshotMakeAnalogInputs()
{
	if (System16InputPort2[0]) DunkshotTrack1X += 0x40;
	if (System16InputPort2[1]) DunkshotTrack1X -= 0x40;
	if (DunkshotTrack1X >= 0x1000) DunkshotTrack1X = 0;
	if (DunkshotTrack1X < 0) DunkshotTrack1X = 0xfc0;
	
	if (System16InputPort2[2]) DunkshotTrack1Y -= 0x40;
	if (System16InputPort2[3]) DunkshotTrack1Y += 0x40;
	if (DunkshotTrack1Y >= 0x1000) DunkshotTrack1Y = 0;
	if (DunkshotTrack1Y < 0) DunkshotTrack1Y = 0xfc0;
	
	if (System16InputPort2[4]) DunkshotTrack2X += 0x40;
	if (System16InputPort2[5]) DunkshotTrack2X -= 0x40;
	if (DunkshotTrack2X >= 0x1000) DunkshotTrack2X = 0;
	if (DunkshotTrack2X < 0) DunkshotTrack2X = 0xfc0;
	
	if (System16InputPort2[6]) DunkshotTrack2Y -= 0x40;
	if (System16InputPort2[7]) DunkshotTrack2Y += 0x40;
	if (DunkshotTrack2Y >= 0x1000) DunkshotTrack2Y = 0;
	if (DunkshotTrack2Y < 0) DunkshotTrack2Y = 0xfc0;
	
	if (System16InputPort3[0]) DunkshotTrack3X += 0x40;
	if (System16InputPort3[1]) DunkshotTrack3X -= 0x40;
	if (DunkshotTrack3X >= 0x1000) DunkshotTrack3X = 0;
	if (DunkshotTrack3X < 0) DunkshotTrack3X = 0xfc0;
	
	if (System16InputPort3[2]) DunkshotTrack3Y -= 0x40;
	if (System16InputPort3[3]) DunkshotTrack3Y += 0x40;
	if (DunkshotTrack3Y >= 0x1000) DunkshotTrack3Y = 0;
	if (DunkshotTrack3Y < 0) DunkshotTrack3Y = 0xfc0;

	if (System16InputPort3[4]) DunkshotTrack4X += 0x40;
	if (System16InputPort3[5]) DunkshotTrack4X -= 0x40;
	if (DunkshotTrack4X >= 0x1000) DunkshotTrack4X = 0;
	if (DunkshotTrack4X < 0) DunkshotTrack4X = 0xfc0;
	
	if (System16InputPort3[6]) DunkshotTrack4Y -= 0x40;
	if (System16InputPort3[7]) DunkshotTrack4Y += 0x40;
	if (DunkshotTrack4Y >= 0x1000) DunkshotTrack4Y = 0;
	if (DunkshotTrack4Y < 0) DunkshotTrack4Y = 0xfc0;
}

unsigned char __fastcall DunkshotReadByte(unsigned int a)
{
	switch (a) {
		case 0xc43001: {
			return DunkshotTrack1X & 0xff;
		}

		case 0xc43003: {
			return DunkshotTrack1X >> 8;
		}
		
		case 0xc43005: {
			return DunkshotTrack1Y & 0xff;
		}

		case 0xc43007: {
			return DunkshotTrack1Y >> 8;
		}
		
		case 0xc43009: {
			return DunkshotTrack2X & 0xff;
		}

		case 0xc4300b: {
			return DunkshotTrack2X >> 8;
		}
		
		case 0xc4300d: {
			return DunkshotTrack2Y & 0xff;
		}

		case 0xc4300f: {
			return DunkshotTrack2Y >> 8;
		}
		
		case 0xc43011: {
			return DunkshotTrack3X & 0xff;
		}

		case 0xc43013: {
			return DunkshotTrack3X >> 8;
		}
		
		case 0xc43015: {
			return DunkshotTrack3Y & 0xff;
		}

		case 0xc43017: {
			return DunkshotTrack3Y >> 8;
		}
		
		case 0xc43019: {
			return DunkshotTrack4X & 0xff;
		}

		case 0xc4301b: {
			return DunkshotTrack4X >> 8;
		}
		
		case 0xc4301d: {
			return DunkshotTrack4Y & 0xff;
		}

		case 0xc4301f: {
			return DunkshotTrack4Y >> 8;
		}
	}

	return 0xff;
}

unsigned short __fastcall EswatMultiply0ReadWord(unsigned int a)
{
	return System16MultiplyChipRead(0, (a - 0x3e0000) >> 1);
}

void __fastcall EswatMultiply0WriteWord(unsigned int a, unsigned short d)
{
	System16MultiplyChipWrite(0, (a - 0x3e0000) >> 1, d);
}

unsigned short __fastcall EswatCompare0ReadWord(unsigned int a)
{
	return System16CompareTimerChipRead(0, (a - 0x3e1000) >> 1);
}

void __fastcall EswatCompare0WriteWord(unsigned int a, unsigned short d)
{
	System16CompareTimerChipWrite(0, (a - 0x3e1000) >> 1, d);
}

void __fastcall EswatSoundWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x123407: {
			System16SoundLatch = d & 0xff;
			ZetRaiseIrq(0);
			return;
		}
	}
}

void __fastcall EswatWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x3e2001: {
			System16TileBanks[0] = d & 7;
			return;
		}
		
		case 0x3e2003: {
			System16TileBanks[1] = d & 7;
			return;
		}
	}
}

unsigned short __fastcall GoldnaxeMultiply0ReadWord(unsigned int a)
{
	return System16MultiplyChipRead(0, (a - 0x1f0000) >> 1);
}

void __fastcall GoldnaxeMultiply0WriteWord(unsigned int a, unsigned short d)
{
	System16MultiplyChipWrite(0, (a - 0x1f0000) >> 1, d);
}

unsigned short __fastcall GoldnaxeCompare0ReadWord(unsigned int a)
{
	return System16CompareTimerChipRead(0, (a - 0x1f1000) >> 1);
}

void __fastcall GoldnaxeCompare0WriteWord(unsigned int a, unsigned short d)
{
	System16CompareTimerChipWrite(0, (a - 0x1f1000) >> 1, d);
}

unsigned short __fastcall GoldnaxeCompare1ReadWord(unsigned int a)
{
	return System16CompareTimerChipRead(1, (a - 0x1e0000) >> 1);
}

void __fastcall GoldnaxeCompare1WriteWord(unsigned int a, unsigned short d)
{
	System16CompareTimerChipWrite(1, (a - 0x1e0000) >> 1, d);
}

void __fastcall Goldnaxe1WriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x1f2001: {
			System16TileBanks[0] = d & 7;
			return;
		}
		
		case 0x1f2003: {
			System16TileBanks[1] = d & 7;
			return;
		}
	}
}

void __fastcall Goldnaxe3WriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x1f0001: {
			System16TileBanks[0] = d & 7;
			return;
		}
		
		case 0x1f0003: {
			System16TileBanks[1] = d & 7;
			return;
		}
	}
}

static UINT8 HwchampInputVal;

unsigned short __fastcall HwchampCtrlReadWord(unsigned int a)
{
	UINT16 result;
	
	switch (a) {
		case 0xc43020: 
		case 0xc43022: 
		case 0xc43024: {
			result = (HwchampInputVal & 0x80) >> 7;
			HwchampInputVal <<= 1;
			return result;
		}
	}

	return 0xffff;
}

void __fastcall HwchampCtrlWriteWord(unsigned int a, unsigned short d)
{
	unsigned char temp = 0;
	
	switch (a) {
		case 0xc43020: {
			temp = 0x80 + (System16AnalogPort0 >> 4);
			if (temp < 0x01) temp = 0x01;
			if (temp > 0xfe) temp = 0xfe;
			HwchampInputVal = temp;
			return;
		}
		
		case 0xc43022: {
			temp = 0x26;
			if (System16AnalogPort2 > 1) temp = 0xfe;
			HwchampInputVal = temp;
			return;
		}
		
		case 0xc43024: {
			temp = 0x26;
			if (System16AnalogPort1 > 1) temp = 0xfe;
			HwchampInputVal = temp;
			return;
		}
	}
}

void __fastcall HwchampWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x3f0001: {
			System16TileBanks[0] = d & 7;
			return;
		}
		
		case 0x3f0003: {
			System16TileBanks[1] = d & 7;
			return;
		}
	}
}

void __fastcall MvpWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x3f2001: {
			System16TileBanks[0] = d & 0x07;
			return;
		}
		
		case 0x3f2003: {
			System16TileBanks[1] = d & 0x07;
			return;
		}
	}
}

void __fastcall MvpjWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x3f0001: {
			System16TileBanks[0] = d & 0x07;
			return;
		}
		
		case 0x3f0003: {
			System16TileBanks[1] = d & 0x07;
			return;
		}
	}
}

void __fastcall PassshtWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0xc00007: {
			System16SoundLatch = d & 0xff;
			ZetRaiseIrq(0);
			return;
		}
	}
}

unsigned char __fastcall PassshtaReadByte(unsigned int a)
{
	switch (a) {
		case 0xc43001: {
			return 0xff - System16Input[1];
		}
		
		case 0xc43003: {
			return 0xff - System16Input[2];
		}
		
		case 0xc43005: {
			return 0xff - System16Input[3];
		}
		
		case 0xc43007: {
			return 0xff - System16Input[4];
		}
	}

	return 0xff;
}

unsigned char __fastcall RiotcityReadByte(unsigned int a)
{
	switch (a) {
		case 0xf81001: {
			return 0xff - System16Input[0];
		}
		
		case 0xf81003: {
			return 0xff - System16Input[1];
		}
		
		case 0xf81007: {
			return 0xff - System16Input[2];
		}
		
		case 0xf82001: {
			return System16Dip[0];
		}

		case 0xf82003: {
			return System16Dip[1];
		}
	}

	return 0xff;
}

void __fastcall RiotcityWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0xf00007: {
			System16SoundLatch = d & 0xff;
			ZetRaiseIrq(0);
			return;
		}
		
		case 0xf20001: {
			System16TileBanks[0] = d & 0x07;
			return;
		}
		
		case 0xf20003: {
			System16TileBanks[1] = d & 0x07;
			return;
		}

		case 0xf80001: {
			System16VideoEnable = d & 0x20;
			System16ScreenFlip = d & 0x40;
			return;
		}
	}
}

unsigned short __fastcall RyukyuReadWord(unsigned int a)
{
	switch (a) {
		case 0x601000: {
			return 0xff - System16Input[0];
		}
		
		case 0x601002: {
			return 0xff - System16Input[1];
		}
		
		case 0x602000: {
			return System16Dip[0];
		}
		
		case 0x602002: {
			return System16Dip[1];
		}
	}
	
	return 0xffff;
}

void __fastcall RyukyuWriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0x100000: {
			System16TileBanks[0] = d & 7;
			return;
		}
		
		case 0x100002: {
			System16TileBanks[1] = d & 7;
			return;
		}
		
		case 0x600000: {
			System16VideoEnable = d & 0x20;
			System16ScreenFlip = d & 0x40;
			return;
		}
	}
}

void __fastcall RyukyuWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0xff0007: {
			System16SoundLatch = d & 0xff;
			ZetRaiseIrq(0);
			return;
		}
	}
}

static short SdiTrack1X = 0;
static short SdiTrack1Y = 0;
static short SdiTrack2X = 0;
static short SdiTrack2Y = 0;

void SdibMakeAnalogInputs()
{
	SdiTrack1X -= (System16AnalogPort0 >> 8) & 0xff;
	SdiTrack1Y += (System16AnalogPort1 >> 8) & 0xff;
	
	SdiTrack2X -= (System16AnalogPort2 >> 8) & 0xff;
	SdiTrack2Y += (System16AnalogPort3 >> 8) & 0xff;
}

unsigned char __fastcall SdibReadByte(unsigned int a)
{
	switch (a) {
		case 0xc41001: {
			return 0xff - System16Input[0];
		}
		
		case 0xc41005: {
			return 0xff - System16Input[1];
		}
		
		case 0xc42003: {
			return System16Dip[1];
		}
		
		case 0xc42005: {
			return System16Dip[0];
		}
		
		case 0xc43001: {
			return SdiTrack1X;
		}
		
		case 0xc43005: {
			return SdiTrack1Y;
		}
		
		case 0xc43009: {
			return SdiTrack2X;
		}
		
		case 0xc4300d: {
			return SdiTrack2Y;
		}
	}
	
	return 0xff;
}

void __fastcall SdibSoundWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x123407: {
			System16SoundLatch = d & 0xff;
			ZetRaiseIrq(0);
			return;
		}
	}
}

static UINT8 MahjongInputNum;

unsigned short __fastcall SjryukoReadWord(unsigned int a)
{
	SEK_DEF_READ_WORD(0, a);
	
	return 0xffff;
}

unsigned char __fastcall SjryukoReadByte(unsigned int a)
{
	switch (a) {
		case 0xc41001: {
			return 0xff - System16Input[0];
		}
		
		case 0xc41003: {
			if (System16Input[MahjongInputNum + 1] != 0xff) return 0xff & ~(1 << MahjongInputNum);
			return 0xff;
		}
		
		case 0xc41005: {
			return 0xff - System16Input[MahjongInputNum + 1];
		}
		
		case 0xc42001: {
			return System16Dip[0];
		}

		case 0xc42003: {
			return System16Dip[1];
		}
	}
	
	return 0xff;
}

void __fastcall SjryukoWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0xc40003: {
			System16VideoEnable = d & 0x20;
			System16ScreenFlip = d & 0x40;
			if (d & 4) MahjongInputNum = (MahjongInputNum + 1) % 6;
			return;
		}
		
		case 0xc00007: {
			System16SoundLatch = d & 0xff;
			ZetRaiseIrq(0);
			return;
		}
	}
}

unsigned short __fastcall SonicbomReadWord(unsigned int a)
{
	switch (a) {
		case 0xc42000: {
			return (0xff << 8) | System16Dip[0];
		}
		
		case 0xc42002: {
			return (0xff << 8) | System16Dip[1];
		}
	}
	
	return 0xffff;
}

void __fastcall SonicbomWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x123407: {
			System16SoundLatch = d & 0xff;
			ZetRaiseIrq(0);
			return;
		}
	}
}

unsigned char __fastcall ToryumonReadByte(unsigned int a)
{
	switch (a) {
		case 0xe41001: {
			return 0xff - System16Input[0];
		}
		
		case 0xe41003: {
			return 0xff - System16Input[1];
		}
		
		case 0xe41005: {
			return 0;
		}
		
		case 0xe41007: {
			return 0xff - System16Input[2];
		}
		
		case 0xe42001: {
			return System16Dip[0];
		}

		case 0xe42003: {
			return System16Dip[1];
		}
	}

	return 0xff;
}

void __fastcall ToryumonWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x3e2001: {
			System16TileBanks[0] = d & 0x07;
			return;
		}
		
		case 0x3e2003: {
			System16TileBanks[1] = d & 0x07;
			return;
		}
		
		case 0xe40001: {
			System16VideoEnable = d & 0x20;
			System16ScreenFlip = d & 0x40;
			return;
		}
		
		case 0xfe0007: {
			System16SoundLatch = d & 0xff;
			ZetRaiseIrq(0);
			return;
		}
	}
}

unsigned char __fastcall TturfReadByte(unsigned int a)
{
	switch (a) {
		case 0x602001: {
			return System16Dip[0];
		}

		case 0x602003: {
			return System16Dip[1];
		}
	}

	return 0xff;
}

void __fastcall TturfWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x600001: {
			System16VideoEnable = d & 0x20;
			System16ScreenFlip = d & 0x40;
			return;
		}
	}
}

void __fastcall Wb3WriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0xdf0007: {
			System16SoundLatch = d & 0xff;
			ZetRaiseIrq(0);
			return;
		}
	}
}

void __fastcall WrestwarWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x400001: {
			System16TileBanks[0] = d & 0x07;
			return;
		}
		
		case 0x400003: {
			System16TileBanks[1] = d & 0x07;
			return;
		}
	}
}

/*====================================================
Driver Inits
====================================================*/

static int AliensynInit()
{
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0xc00006, 0xc00007, SM_WRITE);
		SekSetWriteByteHandler(1, AliensynWriteByte);
		SekClose();
	}
	
	return nRet;
}

static int Aliensy3Init()
{
	FD1089_Decrypt = fd1089_decrypt_0033;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0xc00006, 0xc00007, SM_WRITE);
		SekSetWriteByteHandler(1, AliensynWriteByte);
		SekClose();
	}
	
	return nRet;
}

void Altbeast_Sim8751()
{
	// System Inputs
	*((unsigned short*)(System16Ram + 0x30c2)) = (unsigned short)(System16Input[0] << 8);
	
	// Tile Banking
	System16TileBanks[1] = ((System16Ram[0x3094 + 1] << 8) | System16Ram[0x3094 + 0]) & 7;
	
	// Sound command
	unsigned short temp = (System16Ram[0x30c4 + 1] << 8) | System16Ram[0x30c4 + 0];
	if ((temp & 0xff00) != 0x0000) {
		System16SoundLatch = temp >> 8;
		ZetRaiseIrq(0);
		*((unsigned short*)(System16Ram + 0x30c4)) = (unsigned short)(temp & 0xff);
	}
}

void Altbeasj_Sim8751()
{
	// System Inputs
	*((unsigned short*)(System16Ram + 0x30d0)) = (unsigned short)(System16Input[0] << 8);
	
	// Tile Banking
	System16TileBanks[1] = ((System16Ram[0x3094 + 1] << 8) | System16Ram[0x3094 + 0]) & 7;
	
	// Sound command
	unsigned short temp = (System16Ram[0x30d4 + 1] << 8) | System16Ram[0x30d4 + 0];
	if ((temp & 0xff00) != 0x0000) {
		System16SoundLatch = temp >> 8;
		ZetRaiseIrq(0);
		*((unsigned short*)(System16Ram + 0x30d4)) = (unsigned short)(temp & 0xff);
	}
}

void Altbeas5_Sim8751()
{
	// System Inputs
	*((unsigned short*)(System16Ram + 0x3096)) = (unsigned short)(System16Input[0] << 8);
	
	// Tile Banking
	System16TileBanks[1] = ((System16Ram[0x3094 + 1] << 8) | System16Ram[0x3094 + 0]) & 7;
	
	// Sound command
	unsigned short temp = (System16Ram[0x3098 + 1] << 8) | System16Ram[0x3098 + 0];
	if ((temp & 0xff00) != 0x0000) {
		System16SoundLatch = temp >> 8;
		ZetRaiseIrq(0);
		*((unsigned short*)(System16Ram + 0x3098)) = (unsigned short)(temp & 0xff);
	}
}

static int AltbeastInit()
{
	Simulate8751 = Altbeast_Sim8751;

	int nRet = System16Init();
	
	return nRet;
}

static int AltbeasjInit()
{
	Simulate8751 = Altbeasj_Sim8751;
	
	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0x1a0000 - 0xe0000;

	int nRet = System16Init();
	
	if (!nRet) {
		unsigned char *pTemp = (unsigned char*)malloc(0xe0000);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, 0xe0000);
			memset(System16Sprites, 0, 0x1a0000);
			memcpy(System16Sprites + 0x000000, pTemp + 0x00000, 0x20000);
			memcpy(System16Sprites + 0x040000, pTemp + 0x20000, 0x20000);
			memcpy(System16Sprites + 0x080000, pTemp + 0x40000, 0x20000);
			memcpy(System16Sprites + 0x0c0000, pTemp + 0x60000, 0x20000);
			memcpy(System16Sprites + 0x100000, pTemp + 0x80000, 0x20000);
			memcpy(System16Sprites + 0x140000, pTemp + 0xa0000, 0x20000);
			memcpy(System16Sprites + 0x180000, pTemp + 0xc0000, 0x20000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}
	
	return nRet;
}

static int Altbeas5Init()
{
	Simulate8751 = Altbeas5_Sim8751;
	
	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0x1a0000 - 0xe0000;

	int nRet = System16Init();
	
	if (!nRet) {
		unsigned char *pTemp = (unsigned char*)malloc(0xe0000);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, 0xe0000);
			memset(System16Sprites, 0, 0x1a0000);
			memcpy(System16Sprites + 0x000000, pTemp + 0x00000, 0x20000);
			memcpy(System16Sprites + 0x040000, pTemp + 0x20000, 0x20000);
			memcpy(System16Sprites + 0x080000, pTemp + 0x40000, 0x20000);
			memcpy(System16Sprites + 0x0c0000, pTemp + 0x60000, 0x20000);
			memcpy(System16Sprites + 0x100000, pTemp + 0x80000, 0x20000);
			memcpy(System16Sprites + 0x140000, pTemp + 0xa0000, 0x20000);
			memcpy(System16Sprites + 0x180000, pTemp + 0xc0000, 0x20000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}
	
	return nRet;
}

static int Altbeaj3Init()
{
	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0x1a0000 - 0xe0000;

	int nRet = System16Init();
	
	if (!nRet) {
		unsigned char *pTemp = (unsigned char*)malloc(0xe0000);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, 0xe0000);
			memset(System16Sprites, 0, 0x1a0000);
			memcpy(System16Sprites + 0x000000, pTemp + 0x00000, 0x20000);
			memcpy(System16Sprites + 0x040000, pTemp + 0x20000, 0x20000);
			memcpy(System16Sprites + 0x080000, pTemp + 0x40000, 0x20000);
			memcpy(System16Sprites + 0x0c0000, pTemp + 0x60000, 0x20000);
			memcpy(System16Sprites + 0x100000, pTemp + 0x80000, 0x20000);
			memcpy(System16Sprites + 0x140000, pTemp + 0xa0000, 0x20000);
			memcpy(System16Sprites + 0x180000, pTemp + 0xc0000, 0x20000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}
	
	return nRet;
}

static int Altbeas4Init()
{
	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0x1a0000 - 0xe0000;

	int nRet = System16Init();
	
	if (!nRet) {
		unsigned char *pTemp = (unsigned char*)malloc(0xe0000);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, 0xe0000);
			memset(System16Sprites, 0, 0x1a0000);
			memcpy(System16Sprites + 0x000000, pTemp + 0x00000, 0x20000);
			memcpy(System16Sprites + 0x040000, pTemp + 0x20000, 0x20000);
			memcpy(System16Sprites + 0x080000, pTemp + 0x40000, 0x20000);
			memcpy(System16Sprites + 0x0c0000, pTemp + 0x60000, 0x20000);
			memcpy(System16Sprites + 0x100000, pTemp + 0x80000, 0x20000);
			memcpy(System16Sprites + 0x140000, pTemp + 0xa0000, 0x20000);
			memcpy(System16Sprites + 0x180000, pTemp + 0xc0000, 0x20000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}
	
	return nRet;
}

static int AurailInit()
{
	System16CustomLoadRomDo = CustomLoadRom40000;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0xfc0000, 0xfc0003, SM_WRITE);
		SekSetWriteByteHandler(1, AurailWriteByte);
		SekClose();
	}
	
	return nRet;
}

static int Aurail1Init()
{
	FD1089_Decrypt = fd1089_decrypt_0168;
	System16CustomLoadRomDo = CustomLoadRom40000;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0xfc0000, 0xfc0003, SM_WRITE);
		SekSetWriteByteHandler(1, AurailWriteByte);
		SekClose();
	}
	
	return nRet;
}

static int AurailjInit()
{
	FD1089_Decrypt = fd1089_decrypt_0167;
	System16CustomLoadRomDo = CustomLoadRom40000;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0xfc0000, 0xfc0003, SM_WRITE);
		SekSetWriteByteHandler(1, AurailWriteByte);
		SekClose();
	}
	
	return nRet;
}

void BayrouteMap68K()
{
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(System16Rom           , 0x000000, 0x0bffff, SM_READ);
	SekMapMemory(System16Code          , 0x000000, 0x0bffff, SM_FETCH);
	SekMapMemory(System16Ram           , 0x500000, 0x503fff, SM_RAM);
	SekMapMemory(System16SpriteRam     , 0x600000, 0x6007ff, SM_RAM);
	SekMapMemory(System16TileRam       , 0x700000, 0x70ffff, SM_RAM);
	SekMapMemory(System16TextRam       , 0x710000, 0x710fff, SM_RAM);
	SekMapMemory(System16PaletteRam    , 0x800000, 0x800fff, SM_RAM);
	SekSetReadWordHandler(0, System16BReadWord);
	SekSetWriteWordHandler(0, System16BWriteWord);
	SekSetReadByteHandler(0, BayrouteReadByte);
	SekSetWriteByteHandler(0, BayrouteWriteByte);
	SekClose();
}

static int BayrouteInit()
{
	System16Map68KDo = BayrouteMap68K;
	System16CustomLoadRomDo = CustomLoadRom40000;
	
	int nRet = System16Init();
	
	return nRet;
}

static int Bayrout1Init()
{
	System16Map68KDo = BayrouteMap68K;
	System16CustomLoadRomDo = CustomLoadRom20000;
	
	int nRet = System16Init();
	
	return nRet;
}

static int BulletInit()
{
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekSetReadByteHandler(0, BulletReadByte);
		SekMapHandler(1, 0xc00006, 0xc00007, SM_WRITE);
		SekSetWriteByteHandler(1, BulletWriteByte);
		SekClose();
	}
	return nRet;
}

void CottonMap68K()
{
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(System16Rom           , 0x000000, 0x0fffff, SM_READ);
	SekMapMemory(System16Code          , 0x000000, 0x0fffff, SM_FETCH);
	SekMapMemory(System16TileRam       , 0x400000, 0x40ffff, SM_RAM);
	SekMapMemory(System16TextRam       , 0x410000, 0x410fff, SM_RAM);
	SekMapMemory(System16SpriteRam     , 0x300000, 0x3007ff, SM_RAM);
	SekMapMemory(System16PaletteRam    , 0x500000, 0x500fff, SM_RAM);
	SekMapMemory(System16Ram           , 0x200000, 0x203fff, SM_RAM);
	SekSetReadWordHandler(0, System16BReadWord);
	SekSetWriteWordHandler(0, System16BWriteWord);
	SekSetReadByteHandler(0, CottonReadByte);
	SekSetWriteByteHandler(0, CottonWriteByte);
	SekClose();
}

static int CottonInit()
{
	System16Map68KDo = CottonMap68K;
	System16CustomLoadRomDo = CustomLoadRom40000;
	
	int nRet = System16Init();
	
	return nRet;
}

void Ddux_Sim8751()
{
	// Sound command
	unsigned short temp = (System16Ram[0x0bd0 + 1] << 8) | System16Ram[0x0bd0 + 0];
	if ((temp & 0xff00) != 0x0000) {
		System16SoundLatch = temp >> 8;
		ZetRaiseIrq(0);
		*((unsigned short*)(System16Ram + 0x0bd0)) = (unsigned short)(temp & 0xff);
	}
}

static int DduxInit()
{
	System16CustomLoadRomDo = CustomLoadRom40000;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0x3f0000, 0x3f0003, SM_WRITE);
		SekSetWriteByteHandler(1, DduxWriteByte);
		SekClose();
	}
	
	return nRet;
}

static int Ddux1Init()
{
	Simulate8751 = Ddux_Sim8751;
	System16CustomLoadRomDo = CustomLoadRom40000;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0x3f0000, 0x3f0003, SM_WRITE);
		SekSetWriteByteHandler(1, DduxWriteByte);
		SekClose();
	}
	
	return nRet;
}

static int DunkshotInit()
{
	FD1089_Decrypt = fd1089_decrypt_0022;
	
	System16MakeAnalogInputsDo = DunkshotMakeAnalogInputs;
	
	System16BTileAlt = true;
	
	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0x80000 - 0x40000;

	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0xc43000, 0xc4301f, SM_READ);
		SekSetReadByteHandler(1, DunkshotReadByte);
		SekClose();
		
		unsigned char *pTemp = (unsigned char*)malloc(0x80000);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, 0x80000);
			memset(System16Sprites, 0, 0x80000);
			memcpy(System16Sprites + 0x00000, pTemp + 0x00000, 0x10000);
			memcpy(System16Sprites + 0x10000, pTemp + 0x00000, 0x10000);
			memcpy(System16Sprites + 0x20000, pTemp + 0x10000, 0x10000);
			memcpy(System16Sprites + 0x30000, pTemp + 0x10000, 0x10000);
			memcpy(System16Sprites + 0x40000, pTemp + 0x20000, 0x10000);
			memcpy(System16Sprites + 0x50000, pTemp + 0x20000, 0x10000);
			memcpy(System16Sprites + 0x60000, pTemp + 0x30000, 0x10000);
			memcpy(System16Sprites + 0x70000, pTemp + 0x30000, 0x10000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}
	
	return nRet;
}

static int DunkshotExit()
{
	DunkshotTrack1X = 0;
	DunkshotTrack1Y = 0;
	DunkshotTrack2X = 0;
	DunkshotTrack2Y = 0;
	DunkshotTrack3X = 0;
	DunkshotTrack3Y = 0;
	DunkshotTrack4X = 0;
	DunkshotTrack4Y = 0;

	return System16Exit();
}

static int DunkshotScan(int nAction,int *pnMin)
{
	if (pnMin != NULL) {					// Return minimum compatible version
		*pnMin =  0x029660;
	}
	
	if (nAction & ACB_DRIVER_DATA) {
		SCAN_VAR(DunkshotTrack1X);
		SCAN_VAR(DunkshotTrack1Y);
		SCAN_VAR(DunkshotTrack2X);
		SCAN_VAR(DunkshotTrack2Y);
		SCAN_VAR(DunkshotTrack3X);
		SCAN_VAR(DunkshotTrack3Y);
		SCAN_VAR(DunkshotTrack4X);
		SCAN_VAR(DunkshotTrack4Y);
	}
	
	return System16Scan(nAction, pnMin);;
}

void EswatMap68K()
{
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(System16Rom           , 0x000000, 0x0bffff, SM_READ);
	SekMapMemory(System16Code          , 0x000000, 0x0bffff, SM_FETCH);
	SekMapMemory(System16TileRam       , 0x400000, 0x40ffff, SM_RAM);
	SekMapMemory(System16TextRam       , 0x410000, 0x410fff, SM_RAM);
	SekMapMemory(System16SpriteRam     , 0x440000, 0x4407ff, SM_RAM);
	SekMapMemory(System16PaletteRam    , 0x840000, 0x840fff, SM_RAM);
	SekMapMemory(System16Ram           , 0xffc000, 0xffffff, SM_RAM);
	SekSetReadWordHandler(0, System16BReadWord);
	SekSetWriteWordHandler(0, System16BWriteWord);
	SekSetReadByteHandler(0, System16BReadByte);
	SekSetWriteByteHandler(0, System16BWriteByte);
	SekClose();
}

static int EswatInit()
{
	System16Map68KDo = EswatMap68K;
	
	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0x1c0000 - 0x180000;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0x123406, 0x123407, SM_WRITE);
		SekSetWriteByteHandler(1, EswatSoundWriteByte);
		
		SekMapHandler(2, 0x3e0000, 0x3e0fff, SM_RAM);
		SekSetReadWordHandler(2, EswatMultiply0ReadWord);
		SekSetWriteWordHandler(2, EswatMultiply0WriteWord);
		
		SekMapHandler(3, 0x3e1000, 0x3e1fff, SM_RAM);
		SekSetReadWordHandler(3, EswatCompare0ReadWord);
		SekSetWriteWordHandler(3, EswatCompare0WriteWord);
		
		SekMapHandler(4, 0x3e2000, 0x3e2003, SM_WRITE);
		SekSetWriteByteHandler(4, EswatWriteByte);
		SekClose();
		
		unsigned char *pTemp = (unsigned char*)malloc(0x1c0000);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, 0x1c0000);
			memset(System16Sprites, 0, 0x1c0000);
			memcpy(System16Sprites + 0x000000, pTemp + 0x000000, 0x40000);
			memcpy(System16Sprites + 0x100000, pTemp + 0x040000, 0x40000);
			memcpy(System16Sprites + 0x040000, pTemp + 0x080000, 0x40000);
			memcpy(System16Sprites + 0x140000, pTemp + 0x0c0000, 0x40000);
			memcpy(System16Sprites + 0x080000, pTemp + 0x100000, 0x40000);
			memcpy(System16Sprites + 0x180000, pTemp + 0x140000, 0x40000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}
	
	return nRet;
}

void GoldnaxeMap68K()
{
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(System16Rom           , 0x000000, 0x0bffff, SM_READ);
	SekMapMemory(System16Code          , 0x000000, 0x0bffff, SM_FETCH);
	SekMapMemory(System16TileRam       , 0x100000, 0x10ffff, SM_RAM);
	SekMapMemory(System16TextRam       , 0x110000, 0x110fff, SM_RAM);
	SekMapMemory(System16SpriteRam     , 0x200000, 0x2007ff, SM_RAM);
	SekMapMemory(System16SpriteRam     , 0x300000, 0x3007ff, SM_RAM);
	SekMapMemory(System16SpriteRam     , 0x400000, 0x4007ff, SM_RAM);
	SekMapMemory(System16SpriteRam     , 0x500000, 0x5007ff, SM_RAM);
	SekMapMemory(System16SpriteRam     , 0x700000, 0x7007ff, SM_RAM);
	SekMapMemory(System16SpriteRam     , 0x800000, 0x8007ff, SM_RAM);
	SekMapMemory(System16SpriteRam     , 0x900000, 0x9007ff, SM_RAM);
	SekMapMemory(System16SpriteRam     , 0x600000, 0x6007ff, SM_RAM);
	SekMapMemory(System16PaletteRam    , 0x140000, 0x140fff, SM_RAM);
	SekMapMemory(System16Ram           , 0xffc000, 0xffffff, SM_RAM);
	SekSetReadWordHandler(0, System16BReadWord);
	SekSetWriteWordHandler(0, System16BWriteWord);
	SekSetReadByteHandler(0, System16BReadByte);
	SekSetWriteByteHandler(0, System16BWriteByte);
	SekClose();
}

void Goldnaxe_Sim8751()
{
	// Protection MCU
	unsigned short temp1 = (System16Ram[0x2cd8 + 1] << 8) | System16Ram[0x2cd8 + 0];
	unsigned short temp2 = (System16Ram[0x2cda + 1] << 8) | System16Ram[0x2cda + 0];
	unsigned short temp3 = (System16Ram[0x2cdc + 1] << 8) | System16Ram[0x2cdc + 0];
	unsigned short temp4 = (System16Ram[0x2cde + 1] << 8) | System16Ram[0x2cde + 0];
	if (temp1 == 0 && temp2 == 0 && temp3 == 0 && temp4 == 0) {
		*((unsigned short*)(System16Ram + 0x2cd8)) = 0x048c;
		*((unsigned short*)(System16Ram + 0x2cda)) = 0x159d;
		*((unsigned short*)(System16Ram + 0x2cdc)) = 0x26ae;
		*((unsigned short*)(System16Ram + 0x2cde)) = 0x37bf;
	}
	
	// Sound command
	unsigned short temp = (System16Ram[0x2cfc + 1] << 8) | System16Ram[0x2cfc + 0];
	if ((temp & 0xff00) != 0x0000) {
		System16SoundLatch = temp >> 8;
		ZetRaiseIrq(0);
		*((unsigned short*)(System16Ram + 0x2cfc)) = (unsigned short)(temp & 0xff);
	}
	
	// Inputs
	*((unsigned short*)(System16Ram + 0x2cd0)) = (unsigned short)(~((System16Input[1] << 8) | System16Input[2]));
	*((unsigned short*)(System16Ram + 0x2c96)) = (unsigned short)(~System16Input[0] << 8);
}

static int GoldnaxeInit()
{
	Simulate8751 = Goldnaxe_Sim8751;
	System16Map68KDo = GoldnaxeMap68K;
	
	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0x1c0000 - 0x180000;

	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0x1e0000, 0x1e0fff, SM_RAM);
		SekSetReadWordHandler(1, GoldnaxeCompare1ReadWord);
		SekSetWriteWordHandler(1, GoldnaxeCompare1WriteWord);
		
		SekMapHandler(2, 0x1f0000, 0x1f0fff, SM_RAM);
		SekSetReadWordHandler(2, GoldnaxeMultiply0ReadWord);
		SekSetWriteWordHandler(2, GoldnaxeMultiply0WriteWord);
		
		SekMapHandler(3, 0x1f1000, 0x1f1fff, SM_RAM);
		SekSetReadWordHandler(3, GoldnaxeCompare0ReadWord);
		SekSetWriteWordHandler(3, GoldnaxeCompare0WriteWord);
		
		SekMapHandler(4, 0x1f2000, 0x1f2003, SM_WRITE);
		SekSetWriteByteHandler(4, Goldnaxe1WriteByte);
		SekClose();
		
		unsigned char *pTemp = (unsigned char*)malloc(0x1c0000);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, 0x1c0000);
			memset(System16Sprites, 0, 0x1c0000);
			memcpy(System16Sprites + 0x000000, pTemp + 0x000000, 0x40000);
			memcpy(System16Sprites + 0x100000, pTemp + 0x040000, 0x40000);
			memcpy(System16Sprites + 0x040000, pTemp + 0x080000, 0x40000);
			memcpy(System16Sprites + 0x140000, pTemp + 0x0c0000, 0x40000);
			memcpy(System16Sprites + 0x080000, pTemp + 0x100000, 0x40000);
			memcpy(System16Sprites + 0x180000, pTemp + 0x140000, 0x40000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}
	
	return nRet;
}

static int Goldnax1Init()
{
	System16Map68KDo = GoldnaxeMap68K;
	
	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0x1c0000 - 0x180000;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0x1e0000, 0x1e0fff, SM_RAM);
		SekSetReadWordHandler(1, GoldnaxeCompare1ReadWord);
		SekSetWriteWordHandler(1, GoldnaxeCompare1WriteWord);
		
		SekMapHandler(2, 0x1f0000, 0x1f0fff, SM_RAM);
		SekSetReadWordHandler(2, GoldnaxeMultiply0ReadWord);
		SekSetWriteWordHandler(2, GoldnaxeMultiply0WriteWord);
		
		SekMapHandler(3, 0x1f1000, 0x1f1fff, SM_RAM);
		SekSetReadWordHandler(3, GoldnaxeCompare0ReadWord);
		SekSetWriteWordHandler(3, GoldnaxeCompare0WriteWord);
		
		SekMapHandler(4, 0x1f2000, 0x1f2003, SM_WRITE);
		SekSetWriteByteHandler(4, Goldnaxe1WriteByte);
		SekClose();
		
		unsigned char *pTemp = (unsigned char*)malloc(0x1c0000);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, 0x1c0000);
			memset(System16Sprites, 0, 0x1c0000);
			memcpy(System16Sprites + 0x000000, pTemp + 0x000000, 0x40000);
			memcpy(System16Sprites + 0x100000, pTemp + 0x040000, 0x40000);
			memcpy(System16Sprites + 0x040000, pTemp + 0x080000, 0x40000);
			memcpy(System16Sprites + 0x140000, pTemp + 0x0c0000, 0x40000);
			memcpy(System16Sprites + 0x080000, pTemp + 0x100000, 0x40000);
			memcpy(System16Sprites + 0x180000, pTemp + 0x140000, 0x40000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}
	
	return nRet;
}

static int Goldnax2Init()
{
	Simulate8751 = Goldnaxe_Sim8751;
	System16Map68KDo = GoldnaxeMap68K;
	System16CustomLoadRomDo = CustomLoadRom40000;
	
	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0x1c0000 - 0x180000;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0x1f0000, 0x1f0003, SM_WRITE);
		SekSetWriteByteHandler(1, Goldnaxe3WriteByte);
		SekClose();
	
		unsigned char *pTemp = (unsigned char*)malloc(0x1c0000);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, 0x1c0000);
			memset(System16Sprites, 0, 0x1c0000);
			memcpy(System16Sprites + 0x000000, pTemp + 0x000000, 0x40000);
			memcpy(System16Sprites + 0x100000, pTemp + 0x040000, 0x40000);
			memcpy(System16Sprites + 0x040000, pTemp + 0x080000, 0x40000);
			memcpy(System16Sprites + 0x140000, pTemp + 0x0c0000, 0x40000);
			memcpy(System16Sprites + 0x080000, pTemp + 0x100000, 0x40000);
			memcpy(System16Sprites + 0x180000, pTemp + 0x140000, 0x40000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}
	
	return nRet;
}

static int Goldnax3Init()
{
	System16Map68KDo = GoldnaxeMap68K;
	System16CustomLoadRomDo = CustomLoadRom40000;
	
	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0x1c0000 - 0x180000;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0x1f0000, 0x1f0003, SM_WRITE);
		SekSetWriteByteHandler(1, Goldnaxe3WriteByte);
		SekClose();
		
		unsigned char *pTemp = (unsigned char*)malloc(0x1c0000);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, 0x1c0000);
			memset(System16Sprites, 0, 0x1c0000);
			memcpy(System16Sprites + 0x000000, pTemp + 0x000000, 0x40000);
			memcpy(System16Sprites + 0x100000, pTemp + 0x040000, 0x40000);
			memcpy(System16Sprites + 0x040000, pTemp + 0x080000, 0x40000);
			memcpy(System16Sprites + 0x140000, pTemp + 0x0c0000, 0x40000);
			memcpy(System16Sprites + 0x080000, pTemp + 0x100000, 0x40000);
			memcpy(System16Sprites + 0x180000, pTemp + 0x140000, 0x40000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}
	
	return nRet;
}

static int HwchampInit()
{
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0x3f0000, 0x3f0003, SM_WRITE);
		SekSetWriteByteHandler(1, HwchampWriteByte);
		
		SekMapHandler(2, 0xc43020, 0xc43025, SM_RAM);
		SekSetReadWordHandler(2, HwchampCtrlReadWord);
		SekSetWriteWordHandler(2, HwchampCtrlWriteWord);
		SekClose();
	}
	
	return nRet;
}

static int HwchampExit()
{
	HwchampInputVal = 0;
	
	return System16Exit();
}

static int HwchampScan(int nAction,int *pnMin)
{
	if (pnMin != NULL) {					// Return minimum compatible version
		*pnMin =  0x029660;
	}
	
	if (nAction & ACB_DRIVER_DATA) {
		SCAN_VAR(HwchampInputVal);
	}
	
	return System16Scan(nAction, pnMin);;
}

static int MvpInit()
{
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0x3f2000, 0x3f2003, SM_WRITE);
		SekSetWriteByteHandler(1, MvpWriteByte);
		SekClose();
	
		unsigned char *pTemp = (unsigned char*)malloc(0x200000);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, 0x200000);
			memset(System16Sprites, 0, 0x200000);
			memcpy(System16Sprites + 0x000000, pTemp + 0x000000, 0x40000);
			memcpy(System16Sprites + 0x100000, pTemp + 0x040000, 0x40000);
			memcpy(System16Sprites + 0x040000, pTemp + 0x080000, 0x40000);
			memcpy(System16Sprites + 0x140000, pTemp + 0x0c0000, 0x40000);
			memcpy(System16Sprites + 0x080000, pTemp + 0x100000, 0x40000);
			memcpy(System16Sprites + 0x180000, pTemp + 0x140000, 0x40000);
			memcpy(System16Sprites + 0x0c0000, pTemp + 0x180000, 0x40000);
			memcpy(System16Sprites + 0x1c0000, pTemp + 0x1c0000, 0x40000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}

	return nRet;
}

static int MvpjInit()
{
	System16CustomLoadRomDo = CustomLoadRom40000;
	
	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0x200000 - 0x180000;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0x3f0000, 0x3f0003, SM_WRITE);
		SekSetWriteByteHandler(1, MvpjWriteByte);
		SekClose();
	
		unsigned char *pTemp = (unsigned char*)malloc(0x200000);
		if (pTemp) {
			memset(pTemp, 0, 0x200000);
			memcpy(pTemp, System16Sprites, 0x200000);
			memset(System16Sprites, 0, 0x200000);
			memcpy(System16Sprites + 0x000000, pTemp + 0x000000, 0xc0000);
			memcpy(System16Sprites + 0x100000, pTemp + 0x0c0000, 0xc0000);
		} else {
			nRet = 1;
		}		
		free(pTemp);
	}

	return nRet;
}

static int PassshtInit()
{
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0xc00006, 0xc00007, SM_WRITE);
		SekSetWriteByteHandler(1, PassshtWriteByte);
		SekClose();
	}
	
	return nRet;
}

static int PassshtaInit()
{
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0xc00006, 0xc00007, SM_WRITE);
		SekSetWriteByteHandler(1, PassshtWriteByte);
		SekMapHandler(2, 0xc43000, 0xc43007, SM_READ);
		SekSetReadByteHandler(2, PassshtaReadByte);
		SekClose();
	}
	
	return nRet;
}

void RiotcityMap68K()
{
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(System16Rom           , 0x000000, 0x0bffff, SM_READ);
	SekMapMemory(System16Code          , 0x000000, 0x0bffff, SM_FETCH);
	SekMapMemory(System16TileRam       , 0xfa0000, 0xfaffff, SM_RAM);
	SekMapMemory(System16TextRam       , 0xfb0000, 0xfb0fff, SM_RAM);
	SekMapMemory(System16SpriteRam     , 0xf40000, 0xf407ff, SM_RAM);
	SekMapMemory(System16PaletteRam    , 0xf60000, 0xf60fff, SM_RAM);
	SekMapMemory(System16Ram           , 0xffc000, 0xffffff, SM_RAM);
	SekSetReadWordHandler(0, System16BReadWord);
	SekSetWriteWordHandler(0, System16BWriteWord);
	SekSetReadByteHandler(0, RiotcityReadByte);
	SekSetWriteByteHandler(0, RiotcityWriteByte);
	SekClose();
}

static int RiotcityInit()
{
	System16Map68KDo = RiotcityMap68K;
	System16CustomLoadRomDo = CustomLoadRom40000;
	
	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0x1c0000 - 0x180000;

	int nRet = System16Init();
	
	if (!nRet) {
		unsigned char *pTemp = (unsigned char*)malloc(0x1c0000);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, 0x1c0000);
			memset(System16Sprites, 0, 0x1c0000);
			memcpy(System16Sprites + 0x000000, pTemp + 0x000000, 0x40000);
			memcpy(System16Sprites + 0x100000, pTemp + 0x040000, 0x40000);
			memcpy(System16Sprites + 0x040000, pTemp + 0x080000, 0x40000);
			memcpy(System16Sprites + 0x140000, pTemp + 0x0c0000, 0x40000);
			memcpy(System16Sprites + 0x080000, pTemp + 0x100000, 0x40000);
			memcpy(System16Sprites + 0x180000, pTemp + 0x140000, 0x40000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}
	
	return nRet;
}

void RyukyuMap68K()
{
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(System16Rom           , 0x000000, 0x0bffff, SM_READ);
	SekMapMemory(System16Code          , 0x000000, 0x0bffff, SM_FETCH);
	SekMapMemory(System16TileRam       , 0x400000, 0x40ffff, SM_RAM);
	SekMapMemory(System16TextRam       , 0x410000, 0x410fff, SM_RAM);
	SekMapMemory(System16SpriteRam     , 0x300000, 0x3007ff, SM_RAM);
	SekMapMemory(System16SpriteRam     , 0x300800, 0x300fff, SM_RAM);
	SekMapMemory(System16PaletteRam    , 0x500000, 0x500fff, SM_RAM);
	SekMapMemory(System16Ram           , 0x200000, 0x203fff, SM_RAM);
	SekSetReadWordHandler(0, RyukyuReadWord);
	SekSetWriteWordHandler(0, RyukyuWriteWord);
	SekSetReadByteHandler(0, System16BReadByte);
	SekSetWriteByteHandler(0, RyukyuWriteByte);
	SekClose();
}

static int RyukyuInit()
{
	System16Map68KDo = RyukyuMap68K;
	
	int nRet = System16Init();
	
	return nRet;
}

static int SdibInit()
{
	FD1089_Decrypt = fd1089_decrypt_0028;
	
	System16MakeAnalogInputsDo = SdibMakeAnalogInputs;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekSetReadByteHandler(0, SdibReadByte);
		SekMapHandler(1, 0x123406, 0x123407, SM_WRITE);
		SekSetWriteByteHandler(1, SdibSoundWriteByte);		
		SekClose();
	}
	
	return nRet;
}

static int SdiblInit()
{
	System16MakeAnalogInputsDo = SdibMakeAnalogInputs;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekSetReadByteHandler(0, SdibReadByte);
		SekMapHandler(1, 0x123406, 0x123407, SM_WRITE);
		SekSetWriteByteHandler(1, SdibSoundWriteByte);		
		SekClose();
	}
	
	return nRet;
}

static int SdibExit()
{
	SdiTrack1X = 0;
	SdiTrack1Y = 0;
	SdiTrack2X = 0;
	SdiTrack2Y = 0;

	return System16Exit();
}

static int SdibScan(int nAction,int *pnMin)
{
	if (pnMin != NULL) {					// Return minimum compatible version
		*pnMin =  0x029660;
	}
	
	if (nAction & ACB_DRIVER_DATA) {
		SCAN_VAR(SdiTrack1X);
		SCAN_VAR(SdiTrack1Y);
		SCAN_VAR(SdiTrack2X);
		SCAN_VAR(SdiTrack2Y);
	}
	
	return System16Scan(nAction, pnMin);;
}

static int SjryukoInit()
{
	FD1089_Decrypt = fd1089_decrypt_5021;
	
	System16BTileAlt = true;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekSetWriteByteHandler(0, SjryukoWriteByte);
		SekSetReadByteHandler(0, SjryukoReadByte);
		SekSetReadWordHandler(0, SjryukoReadWord);
		SekClose();
	}
	
	return nRet;
}

static int SjryukoExit()
{
	MahjongInputNum = 0;
	
	return System16Exit();
}

static int SjryukoScan(int nAction,int *pnMin)
{
	if (pnMin != NULL) {					// Return minimum compatible version
		*pnMin =  0x029660;
	}
	
	if (nAction & ACB_DRIVER_DATA) {
		SCAN_VAR(MahjongInputNum);
	}
	
	return System16Scan(nAction, pnMin);;
}

static int SonicbomInit()
{
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0x123406, 0x123407, SM_WRITE);
		SekSetWriteByteHandler(1, SonicbomWriteByte);
		SekMapHandler(2, 0xc42000, 0xc42003, SM_READ);
		SekSetReadWordHandler(2, SonicbomReadWord);
		SekClose();
	}

	return nRet;
}

static int TimescanInit()
{
	System16BTileAlt = true;

	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0x80000 - 0x40000;

	int nRet = System16Init();
	
	if (!nRet) {
		unsigned char *pTemp = (unsigned char*)malloc(0x80000);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, 0x40000);
			memset(System16Sprites, 0, 0x80000);
			memcpy(System16Sprites + 0x000000, pTemp + 0x00000, 0x20000);
			memcpy(System16Sprites + 0x020000, pTemp + 0x10000, 0x20000);
			memcpy(System16Sprites + 0x040000, pTemp + 0x20000, 0x20000);
			memcpy(System16Sprites + 0x060000, pTemp + 0x30000, 0x20000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}

	return nRet;
}

static int ToryumonInit()
{
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekSetReadByteHandler(0, ToryumonReadByte);
		SekSetWriteByteHandler(0, ToryumonWriteByte);
		SekMapMemory(System16Ram, 0xff0000, 0xff3fff, SM_RAM);
		SekMapMemory(System16Ram, 0xff4000, 0xff7fff, SM_RAM);
		SekMapMemory(System16Ram, 0xff8000, 0xffbfff, SM_RAM);
		SekClose();
	}

	return nRet;
}

void TturfMap68K()
{
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(System16Rom           , 0x000000, 0x0bffff, SM_READ);
	SekMapMemory(System16Code          , 0x000000, 0x0bffff, SM_FETCH);
	SekMapMemory(System16TileRam       , 0x400000, 0x40ffff, SM_RAM);
	SekMapMemory(System16TextRam       , 0x410000, 0x410fff, SM_RAM);
	SekMapMemory(System16SpriteRam     , 0x300000, 0x3007ff, SM_RAM);
	SekMapMemory(System16PaletteRam    , 0x500000, 0x500fff, SM_RAM);
	SekMapMemory(System16Ram           , 0x200000, 0x203fff, SM_RAM);
	SekSetReadWordHandler(0, System16BReadWord);
	SekSetWriteWordHandler(0, System16BWriteWord);
	SekSetReadByteHandler(0, TturfReadByte);
	SekSetWriteByteHandler(0, TturfWriteByte);
	SekClose();
}

void Tturf_Sim8751()
{
	// Inputs
	*((unsigned short*)(System16Ram + 0x01e6)) = (unsigned short)(~System16Input[0] << 8);
	*((unsigned short*)(System16Ram + 0x01e8)) = (unsigned short)(~System16Input[1] << 8);
	*((unsigned short*)(System16Ram + 0x01ea)) = (unsigned short)(~System16Input[2] << 8);
	
	// Sound command
	unsigned short temp = (System16Ram[0x01d0 + 1] << 8) | System16Ram[0x01d0 + 0];
	if ((temp & 0xff00) != 0x0000) {
		System16SoundLatch = temp & 0xff;
		ZetRaiseIrq(0);
		*((unsigned short*)(System16Ram + 0x01d0)) = (unsigned short)(temp & 0xff);
	}
}

static int TturfInit()
{
	Simulate8751 = Tturf_Sim8751;
	System16Map68KDo = TturfMap68K;
	
	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0xe0000 - 0x80000;

	int nRet = System16Init();
	
	if (!nRet) {
		unsigned char *pTemp = (unsigned char*)malloc(0xe0000);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, 0x80000);
			memset(System16Sprites, 0, 0xe0000);
			memcpy(System16Sprites + 0x000000, pTemp + 0x00000, 0x20000);
			memcpy(System16Sprites + 0x040000, pTemp + 0x20000, 0x20000);
			memcpy(System16Sprites + 0x080000, pTemp + 0x40000, 0x20000);
			memcpy(System16Sprites + 0x0c0000, pTemp + 0x60000, 0x20000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}

	return nRet;
}

static int TturfuInit()
{
	Simulate8751 = Tturf_Sim8751;
	System16Map68KDo = TturfMap68K;
	
	int nRet = System16Init();
	
	return nRet;
}

void Wb3_Sim8751()
{
	// Sound command
	unsigned short temp = (System16Ram[0x0008 + 1] << 8) | System16Ram[0x0008 + 0];
	if ((temp & 0xff00) != 0x0000) {
		System16SoundLatch = temp >> 8;
		ZetRaiseIrq(0);
		*((unsigned short*)(System16Ram + 0x0008)) = (unsigned short)(temp & 0xff);
	}
}

static int Wb3Init()
{
	Simulate8751 = Wb3_Sim8751;
	
	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0xe0000 - 0x80000;

	int nRet = System16Init();
	
	if (!nRet) {
		unsigned char *pTemp = (unsigned char*)malloc(0xe0000);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, 0x80000);
			memset(System16Sprites, 0, 0xe0000);
			memcpy(System16Sprites + 0x000000, pTemp + 0x00000, 0x20000);
			memcpy(System16Sprites + 0x040000, pTemp + 0x20000, 0x20000);
			memcpy(System16Sprites + 0x080000, pTemp + 0x40000, 0x20000);
			memcpy(System16Sprites + 0x0c0000, pTemp + 0x60000, 0x20000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}

	return nRet;
}

static int Wb32Init()
{
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0xdf0006, 0xdf0007, SM_WRITE);
		SekSetWriteByteHandler(1, Wb3WriteByte);
		SekClose();
	}

	return nRet;
}

static int Wb33Init()
{
	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0xe0000 - 0x80000;

	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekMapHandler(1, 0xdf0006, 0xdf0007, SM_WRITE);
		SekSetWriteByteHandler(1, Wb3WriteByte);
		SekClose();
	
		unsigned char *pTemp = (unsigned char*)malloc(0xe0000);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, 0x80000);
			memset(System16Sprites, 0, 0xe0000);
			memcpy(System16Sprites + 0x000000, pTemp + 0x00000, 0x20000);
			memcpy(System16Sprites + 0x040000, pTemp + 0x20000, 0x20000);
			memcpy(System16Sprites + 0x080000, pTemp + 0x40000, 0x20000);
			memcpy(System16Sprites + 0x0c0000, pTemp + 0x60000, 0x20000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}

	return nRet;
}

void WrestwarMap68K()
{
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(System16Rom           , 0x000000, 0x0bffff, SM_READ);
	SekMapMemory(System16Code          , 0x000000, 0x0bffff, SM_FETCH);
	SekMapMemory(System16TileRam       , 0x100000, 0x10ffff, SM_RAM);
	SekMapMemory(System16TextRam       , 0x110000, 0x110fff, SM_RAM);
	SekMapMemory(System16SpriteRam     , 0x200000, 0x2007ff, SM_RAM);
	SekMapMemory(System16PaletteRam    , 0x300000, 0x300fff, SM_RAM);
	SekMapMemory(System16Ram           , 0xffc000, 0xffffff, SM_RAM);
	SekSetReadWordHandler(0, System16BReadWord);
	SekSetWriteWordHandler(0, System16BWriteWord);
	SekSetReadByteHandler(0, System16BReadByte);
	SekSetWriteByteHandler(0, System16BWriteByte);
	SekMapHandler(1, 0x400000, 0x400003, SM_WRITE);
	SekSetWriteByteHandler(1, WrestwarWriteByte);
	SekClose();
}

void Wrestwar_Sim8751()
{
	// System Inputs
	*((unsigned short*)(System16Ram + 0x2082)) = (unsigned short)~System16Input[0];
	
	// Sound command
	unsigned short temp = (System16Ram[0x208e + 1] << 8) | System16Ram[0x208e + 0];
	if ((temp & 0xff00) != 0x0000) {
		System16SoundLatch = temp & 0xff;
		ZetRaiseIrq(0);
		*((unsigned short*)(System16Ram + 0x208e)) = (unsigned short)(temp & 0xff);
	}
}

static int WrestwarInit()
{
	Simulate8751 = Wrestwar_Sim8751;
	System16Map68KDo = WrestwarMap68K;
	System16CustomLoadRomDo = CustomLoadRom40000;
	
	int nRet = System16Init();

	return nRet;
}

static int Wrestwa1Init()
{
	System16Map68KDo = WrestwarMap68K;
	System16CustomLoadRomDo = CustomLoadRom40000;
	
	int nRet = System16Init();

	return nRet;
}

/*====================================================
Driver defs
====================================================*/

struct BurnDriver BurnDrvAliensyn = {
	"aliensyn", NULL, NULL, "1987",
	"Alien Syndrome (set 4, System 16B, unprotected)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_5358,
	NULL, AliensynRomInfo, AliensynRomName, System16bfire1InputInfo, AliensynDIPInfo,
	AliensynInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvAliensy3 = {
	"aliensy3", "aliensyn", NULL, "1987",
	"Alien Syndrome (set 3, System 16B, FD1089A 317-0033)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_5358 | HARDWARE_SEGA_FD1089A_ENC,
	NULL, Aliensy3RomInfo, Aliensy3RomName, System16bfire1InputInfo, AliensynDIPInfo,
	Aliensy3Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvAltbeast = {
	"altbeast", NULL, NULL, "1988",
	"Altered Beast (set 7, 8751 317-0078)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B,
	NULL, AltbeastRomInfo, AltbeastRomName, System16bfire3InputInfo, AltbeastDIPInfo,
	AltbeastInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvAltbeasj = {
	"altbeasj", "altbeast", NULL, "1988",
	"Juuouki (set 6, Japan, 8751 317-0077)\0", "Incomplete Sound", "Sega", "System 16B",
	L"Juuoki (set 6, Japan, 8751 317-0077)\0\u7363\u738B\u8A18\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B,
	NULL, AltbeasjRomInfo, AltbeasjRomName, System16bfire3InputInfo, AltbeastDIPInfo,
	AltbeasjInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvAltbeas2 = {
	"altbeas2", "altbeast", NULL, "1988",
	"Altered Beast (set 2, MC-8123B 317-0066)\0", "No Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_MC8123_ENC,
	NULL, Altbeas2RomInfo, Altbeas2RomName, System16bfire3InputInfo, AltbeastDIPInfo,
	System16Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvAltbeaj3 = {
	"altbeaj3", "altbeast", NULL, "1988",
	"Juuouki (set 3, Japan, FD1094 317-0068)\0", "Incomplete Sound", "Sega", "System 16B",
	L"Juuoki (set 3, Japan, FD1094 317-0068)\0\u7363\u738B\u8A18\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, Altbeaj3RomInfo, Altbeaj3RomName, System16bfire3InputInfo, AltbeastDIPInfo,
	Altbeaj3Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvAltbeas4 = {
	"altbeas4", "altbeast", NULL, "1988",
	"Altered Beast (set 4, MC-8123B 317-0066)\0", "No Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_MC8123_ENC,
	NULL, Altbeas4RomInfo, Altbeas4RomName, System16bfire3InputInfo, AltbeastDIPInfo,
	Altbeas4Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvAltbeas5 = {
	"altbeas5", "altbeast", NULL, "1988",
	"Altered Beast (set 5, 8751 317-0076)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B,
	NULL, Altbeas5RomInfo, Altbeas5RomName, System16bfire3InputInfo, AltbeastDIPInfo,
	Altbeas5Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvAurail = {
	"aurail", NULL, NULL, "1990",
	"Aurail (set 3, US, unprotected)\0", "Incomplete Sound", "Sega / Westone", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B,
	NULL, AurailRomInfo, AurailRomName, System16bfire3InputInfo, AurailDIPInfo,
	AurailInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvAurail1 = {
	"aurail1", "aurail", NULL, "1990",
	"Aurail (set 2, World, FD1089B 317-0168)\0", "Incomplete Sound", "Sega / Westone", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1089B_ENC,
	NULL, Aurail1RomInfo, Aurail1RomName, System16bfire3InputInfo, AurailDIPInfo,
	Aurail1Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvAurailj = {
	"aurailj", "aurail", NULL, "1990",
	"Aurail (set 1, Japan, FD1089A 317-0167)\0", "Incomplete Sound", "Sega / Westone", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1089A_ENC,
	NULL, AurailjRomInfo, AurailjRomName, System16bfire3InputInfo, AurailDIPInfo,
	AurailjInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvBayroute = {
	"bayroute", NULL, NULL, "1989",
	"Bay Route (set 3, World, FD1094 317-0116)\0", "Incomplete Sound", "Sunsoft / Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, BayrouteRomInfo, BayrouteRomName, System16bfire3InputInfo, BayrouteDIPInfo,
	BayrouteInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvBayroutj = {
	"bayroutj", "bayroute", NULL, "1989",
	"Bay Route (set 2, Japan, FD1094 317-0115)\0", "Incomplete Sound", "Sunsoft / Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, BayroutjRomInfo, BayroutjRomName, System16bfire3InputInfo, BayrouteDIPInfo,
	BayrouteInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvBayrout1 = {
	"bayrout1", "bayroute", NULL, "1989",
	"Bay Route (set 1, US, unprotected)\0", "No Sound, Missing Z80 Program ROM", "Sunsoft / Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_5358,
	NULL, Bayrout1RomInfo, Bayrout1RomName, System16bfire3InputInfo, BayrouteDIPInfo,
	Bayrout1Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriverD BurnDrvBullet = {
	"bullet", NULL, NULL, "1987",
	"Bullet (FD1094 317-0041)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 3, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC | HARDWARE_SEGA_5358,
	NULL, BulletRomInfo, BulletRomName, BulletInputInfo, BulletDIPInfo,
	BulletInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvCotton = {
	"cotton", NULL, NULL, "1991",
	"Cotton (set 3, World, FD1094 317-0181a)\0", "No Sound", "Sega / Success", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, CottonRomInfo, CottonRomName, System16bInputInfo, CottonDIPInfo,
	CottonInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvCottonu = {
	"cottonu", "cotton", NULL, "1991",
	"Cotton (set 2, US, FD1094 317-0180)\0", "No Sound", "Sega / Success", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, CottonuRomInfo, CottonuRomName, System16bInputInfo, CottonDIPInfo,
	CottonInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvCottonj = {
	"cottonj", "cotton", NULL, "1991",
	"Cotton (set 1, Japan, FD1094 317-0179a))\0", "No Sound", "Sega / Success", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, CottonjRomInfo, CottonjRomName, System16bInputInfo, CottonDIPInfo,
	CottonInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvDdux = {
	"ddux", NULL, NULL, "1989",
	"Dynamite Dux (set 2, FD1094 317-0096)\0", NULL, "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, DduxRomInfo, DduxRomName, System16bInputInfo, DduxDIPInfo,
	DduxInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvDdux1 = {
	"ddux1", "ddux", NULL, "1989",
	"Dynamite Dux (set 1, 8751 317-0095)\0", NULL, "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B,
	NULL, Ddux1RomInfo, Ddux1RomName, System16bInputInfo, DduxDIPInfo,
	Ddux1Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvDunkshot = {
	"dunkshot", NULL, NULL, "1986",
	"Dunk Shot (FD1089 317-0022)\0", NULL, "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 4, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1089A_ENC | HARDWARE_SEGA_5358,
	NULL, DunkshotRomInfo, DunkshotRomName, DunkshotInputInfo, DunkshotDIPInfo,
	DunkshotInit, DunkshotExit, System16BFrame, NULL, DunkshotScan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvEswat = {
	"eswat", NULL, NULL, "1989",
	"E-Swat - Cyber Police (set 3, World, FD1094 317-0130)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, EswatRomInfo, EswatRomName, System16bfire3InputInfo, EswatDIPInfo,
	EswatInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvEswatj = {
	"eswatj", "eswat", NULL, "1989",
	"E-Swat - Cyber Police (set 1, Japan, FD1094 317-0128)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, EswatjRomInfo, EswatjRomName, System16bfire3InputInfo, EswatDIPInfo,
	EswatInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvEswatu = {
	"eswatu", "eswat", NULL, "1989",
	"E-Swat - Cyber Police (set 2, US, FD1094 317-0129)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, EswatuRomInfo, EswatuRomName, System16bfire3InputInfo, EswatDIPInfo,
	EswatInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvFpoint = {
	"fpoint", NULL, NULL, "1989",
	"Flash Point (set 2, Japan, FD1094 317-0127A)\0", NULL, "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC | HARDWARE_SEGA_5358,
	NULL, FpointRomInfo, FpointRomName, System16bfire1InputInfo, FpointDIPInfo,
	System16Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvFpoint1 = {
	"fpoint1", "fpoint", NULL, "1989",
	"Flash Point (set 1, Japan, FD1094 317-0127A)\0", NULL, "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, Fpoint1RomInfo, Fpoint1RomName, System16bfire1InputInfo, FpointDIPInfo,
	System16Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvGoldnaxe = {
	"goldnaxe", NULL, NULL, "1989",
	"Golden Axe (set 6, US, 8751 317-123A)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B,
	NULL, GoldnaxeRomInfo, GoldnaxeRomName, System16bfire3InputInfo, GoldnaxeDIPInfo,
	GoldnaxeInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvGoldnax1 = {
	"goldnax1", "goldnaxe", NULL, "1989",
	"Golden Axe (set 1, World, FD1094 317-0110)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, Goldnax1RomInfo, Goldnax1RomName, System16bfire3InputInfo, GoldnaxeDIPInfo,
	Goldnax1Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvGoldnax2 = {
	"goldnax2", "goldnaxe", NULL, "1989",
	"Golden Axe (set 2, US, 8751 317-0112)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B,
	NULL, Goldnax2RomInfo, Goldnax2RomName, System16bfire3InputInfo, GoldnaxeDIPInfo,
	Goldnax2Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvGoldnax3 = {
	"goldnax3", "goldnaxe", NULL, "1989",
	"Golden Axe (set 3, World, FD1094 317-0120)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, Goldnax3RomInfo, Goldnax3RomName, System16bfire3InputInfo, GoldnaxeDIPInfo,
	Goldnax3Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvGoldnaxj = {
	"goldnaxj", "goldnaxe", NULL, "1989",
	"Golden Axe (set 4, Japan, FD1094 317-0121)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, GoldnaxjRomInfo, GoldnaxjRomName, System16bfire3InputInfo, GoldnaxeDIPInfo,
	Goldnax3Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvGoldnaxu = {
	"goldnaxu", "goldnaxe", NULL, "1989",
	"Golden Axe (set 5, US, FD1094 317-0122)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, GoldnaxuRomInfo, GoldnaxuRomName, System16bfire3InputInfo, GoldnaxeDIPInfo,
	Goldnax1Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvHwchamp = {
	"hwchamp", NULL, NULL, "1987",
	"Heavyweight Champ\0", NULL, "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B,
	NULL, HwchampRomInfo, HwchampRomName, HwchampInputInfo, HwchampDIPInfo,
	HwchampInit, HwchampExit, System16BFrame, NULL, HwchampScan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvMvp = {
	"mvp", NULL, NULL, "1989",
	"MVP (set 2, US, FD1094 317-0143)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, MvpRomInfo, MvpRomName, System16bfire3InputInfo, MvpDIPInfo,
	MvpInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvMvpj = {
	"mvpj", "mvp", NULL, "1989",
	"MVP (set 1, Japan, FD1094 317-0142)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, MvpjRomInfo, MvpjRomName, System16bfire3InputInfo, MvpDIPInfo,
	MvpjInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvPasssht = {
	"passsht", NULL, NULL, "1988",
	"Passing Shot (World, 2 Players, FD1094 317-0080)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC | HARDWARE_SEGA_5358,
	NULL, PassshtRomInfo, PassshtRomName, System16bfire4InputInfo, PassshtDIPInfo,
	PassshtInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 224, 320, 3, 4
};

struct BurnDriver BurnDrvPassshta = {
	"passshta", "passsht", NULL, "1988",
	"Passing Shot (World, 4 Players, FD1094 317-0074)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL | BDF_CLONE, 4, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC | HARDWARE_SEGA_5358,
	NULL, PassshtaRomInfo, PassshtaRomName, PassshtInputInfo, PassshtaDIPInfo,
	PassshtaInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 224, 320, 3, 4
};

struct BurnDriver BurnDrvPassshtj = {
	"passshtj", "passsht", NULL, "1988",
	"Passing Shot (Japan, 4 Players, FD1094 317-0070)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL | BDF_CLONE, 4, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC | HARDWARE_SEGA_5358,
	NULL, PassshtjRomInfo, PassshtjRomName, PassshtInputInfo, PassshtaDIPInfo,
	PassshtaInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 224, 320, 3, 4
};

struct BurnDriver BurnDrvRiotcity = {
	"riotcity", NULL, NULL, "1991",
	"Riot City (Japan)\0", "Incomplete Sound", "Sega / Westone", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B,
	NULL, RiotcityRomInfo, RiotcityRomName, System16bInputInfo, RiotcityDIPInfo,
	RiotcityInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvRyukyu = {
	"ryukyu", NULL, NULL, "1990",
	"RyuKyu (Japan, FD1094 317-5023)\0", "Incomplete Sound", "Success / Sega", "System 16B",
	L"RyuKyu \u7409\u7403 (Japan, FD1094 317-5023)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, RyukyuRomInfo, RyukyuRomName, RyukyuInputInfo, RyukyuDIPInfo,
	RyukyuInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvSdib = {
	"sdib", "sdi", NULL, "1987",
	"SDI - Strategic Defense Initiative (System 16B, FD1089A 317-0028)\0", NULL, "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1089A_ENC | HARDWARE_SEGA_5358,
	NULL, SdibRomInfo, SdibRomName, SdiInputInfo, SdibDIPInfo,
	SdibInit, SdibExit, System16BFrame, NULL, SdibScan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvSdibl = {
	"sdibl", "sdi", NULL, "1987",
	"SDI - Strategic Defense Initiative (bootleg)\0", NULL, "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_5358,
	NULL, SdiblRomInfo, SdiblRomName, SdiInputInfo, SdibDIPInfo,
	SdiblInit, SdibExit, System16BFrame, NULL, SdibScan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvDefense = {
	"defense", "sdi", NULL, "1987",
	"Defense (System 16B, FD1089A 317-0028)\0", NULL, "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1089A_ENC | HARDWARE_SEGA_5358,
	NULL, DefenseRomInfo, DefenseRomName, SdiInputInfo, SdibDIPInfo,
	SdibInit, SdibExit, System16BFrame, NULL, SdibScan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvShinobi2 = {
	"shinobi2", "shinobi", NULL, "1987",
	"Shinobi (set 2, System 16B, FD1094 317-0049)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_5358 | HARDWARE_SEGA_FD1094_ENC,
	NULL, Shinobi2RomInfo, Shinobi2RomName, System16bfire3InputInfo, ShinobiDIPInfo,
	System16Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvShinobi3 = {
	"shinobi3", "shinobi", NULL, "1987",
	"Shinobi (set 3, System 16B, MC-8123B 317-0054)\0", "No Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_5358 | HARDWARE_SEGA_MC8123_ENC,
	NULL, Shinobi3RomInfo, Shinobi3RomName, System16bfire3InputInfo, ShinobiDIPInfo,
	System16Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvShinobi4 = {
	"shinobi4", "shinobi", NULL, "1987",
	"Shinobi (set 4, System 16B, unprotected)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B,
	NULL, Shinobi4RomInfo, Shinobi4RomName, System16bfire3InputInfo, ShinobiDIPInfo,
	System16Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvSjryuko = {
	"sjryuko", NULL, NULL, "1987",
	"Sukeban Jansi Ryuko (set 2, System 16B, FD1089B 317-5021)\0", "Incomplete Sound", "White Board", "System 16B",
	L"Sukeban Jansi Ryuko (set 2, System 16B, FD1089B 317-5021)\0\u30B9\u30B1\u30D0\u30F3\u96C0\u58EB \u7ADC\u5B50\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1089B_ENC | HARDWARE_SEGA_5358,
	NULL, SjryukoRomInfo, SjryukoRomName, SjryukoInputInfo, SjryukoDIPInfo,
	SjryukoInit, SjryukoExit, System16BFrame, NULL, SjryukoScan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvSonicbom = {
	"sonicbom", NULL, NULL, "1987",
	"Sonic Boom (FD1094 317-0053)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_5358 | HARDWARE_SEGA_FD1094_ENC,
	NULL, SonicbomRomInfo, SonicbomRomName, System16bInputInfo, SonicbomDIPInfo,
	SonicbomInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 224, 320, 3, 4
};

struct BurnDriver BurnDrvTetris1 = {
	"tetris1", "tetris", NULL, "1988",
	"Tetris (set 1, Japan, System 16B, FD1094 317-0091)\0", NULL, "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_5358 | HARDWARE_SEGA_FD1094_ENC,
	NULL, Tetris1RomInfo, Tetris1RomName, System16bfire1InputInfo, TetrisDIPInfo,
	System16Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvTetris2 = {
	"tetris2", "tetris", NULL, "1988",
	"Tetris (set 2, Japan, System 16B, FD1094 317-0092)\0", NULL, "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, Tetris2RomInfo, Tetris2RomName, System16bfire1InputInfo, TetrisDIPInfo,
	System16Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvTimescan = {
	"timescan", NULL, NULL, "1987",
	"Time Scanner (set 2, System 16B)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_5358,
	NULL, TimescanRomInfo, TimescanRomName, System16bDip3InputInfo, TimescanDIPInfo,
	TimescanInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 224, 320, 3, 4
};

struct BurnDriver BurnDrvToryumon = {
	"toryumon", NULL, NULL, "1994",
	"Toryumon\0", "Incomplete Sound", "Sega / Westone", "System 16B",
	L"Toryumon\0\u767B\u9F8D\u9580\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B,
	NULL, ToryumonRomInfo, ToryumonRomName, System16bfire1InputInfo, ToryumonDIPInfo,
	ToryumonInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvTturf = {
	"tturf", NULL, NULL, "1989",
	"Tough Turf (set 2, Japan, 8751 317-0104)\0", "No Sound, Missing Z80 Program", "Sega / Sunsoft", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B,
	NULL, TturfRomInfo, TturfRomName, System16bfire3InputInfo, TturfDIPInfo,
	TturfInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvTturfu = {
	"tturfu", "tturf", NULL, "1989",
	"Tough Turf (set 1, US, 8751 317-0099)\0", "Incomplete Sound", "Sega / Sunsoft", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_5358,
	NULL, TturfuRomInfo, TturfuRomName, System16bfire3InputInfo, TturfDIPInfo,
	TturfuInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvWb3 = {
	"wb3", NULL, NULL, "1988",
	"Wonder Boy III - Monster Lair (set 5, World, System 16B, 8751 317-0098)\0", NULL, "Sega / Westone", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16B,
	NULL, Wb3RomInfo, Wb3RomName, System16bInputInfo, Wb3DIPInfo,
	Wb3Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvWb32 = {
	"wb32", "wb3", NULL, "1988",
	"Wonder Boy III - Monster Lair (set 2, Japan, System 16B, FD1094 317-0085)\0", NULL, "Sega / Westone", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_5358 | HARDWARE_SEGA_FD1094_ENC,
	NULL, Wb32RomInfo, Wb32RomName, System16bInputInfo, Wb3DIPInfo,
	Wb32Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvWb33 = {
	"wb33", "wb3", NULL, "1988",
	"Wonder Boy III - Monster Lair (set 3, World, System 16B, FD1094 317-0089)\0", NULL, "Sega / Westone", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, Wb33RomInfo, Wb33RomName, System16bInputInfo, Wb3DIPInfo,
	Wb33Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvWb34 = {
	"wb34", "wb3", NULL, "1988",
	"Wonder Boy III - Monster Lair (set 4, Japan, System 16B, FD1094 317-0087)\0", NULL, "Sega / Westone", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, Wb34RomInfo, Wb34RomName, System16bInputInfo, Wb3DIPInfo,
	Wb33Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvWrestwar = {
	"wrestwar", NULL, NULL, "1988",
	"Wrestle War (set 3, World, 8751 317-0103)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_SEGA_SYSTEM16B,
	NULL, WrestwarRomInfo, WrestwarRomName, System16bInputInfo, WrestwarDIPInfo,
	WrestwarInit, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 224, 320, 3, 4
};

struct BurnDriver BurnDrvWrestwa1 = {
	"wrestwa1", "wrestwar", NULL, "1988",
	"Wrestle War (set 1, Japan, FD1094 317-0090)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, Wrestwa1RomInfo, Wrestwa1RomName, System16bInputInfo, WrestwarDIPInfo,
	Wrestwa1Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 224, 320, 3, 4
};

struct BurnDriver BurnDrvWrestwa2 = {
	"wrestwa2", "wrestwar", NULL, "1988",
	"Wrestle War (set 2, World, FD1094 317-0102)\0", "Incomplete Sound", "Sega", "System 16B",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_SEGA_SYSTEM16B | HARDWARE_SEGA_FD1094_ENC,
	NULL, Wrestwa2RomInfo, Wrestwa2RomName, System16bInputInfo, WrestwarDIPInfo,
	Wrestwa1Init, System16Exit, System16BFrame, NULL, System16Scan,
	NULL, 224, 320, 3, 4
};
