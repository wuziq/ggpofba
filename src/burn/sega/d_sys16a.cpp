#include "sys16.h"

/*====================================================
Input defs
====================================================*/

#define A(a, b, c, d) {a, b, (unsigned char*)(c), d}

static struct BurnInputInfo System16aInputList[] = {
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

	{"Service"           , BIT_DIGITAL  , System16InputPort0 + 3 , "service"   },
	{"Diagnostics"       , BIT_DIGITAL  , System16InputPort0 + 2 , "diag"      },
	{"Reset"             , BIT_DIGITAL  , &System16Reset         , "reset"     },
	{"Dip 1"             , BIT_DIPSWITCH, System16Dip + 0        , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH, System16Dip + 1        , "dip"       },
};

STDINPUTINFO(System16a);

static struct BurnInputInfo System16afire1InputList[] = {
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

	{"Service"           , BIT_DIGITAL  , System16InputPort0 + 3 , "service"   },
	{"Diagnostics"       , BIT_DIGITAL  , System16InputPort0 + 2 , "diag"      },
	{"Reset"             , BIT_DIGITAL  , &System16Reset         , "reset"     },
	{"Dip 1"             , BIT_DIPSWITCH, System16Dip + 0        , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH, System16Dip + 1        , "dip"       },
};

STDINPUTINFO(System16afire1);

static struct BurnInputInfo System16afire3InputList[] = {
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

	{"Service"           , BIT_DIGITAL  , System16InputPort0 + 3 , "service"   },
	{"Diagnostics"       , BIT_DIGITAL  , System16InputPort0 + 2 , "diag"      },
	{"Reset"             , BIT_DIGITAL  , &System16Reset         , "reset"     },
	{"Dip 1"             , BIT_DIPSWITCH, System16Dip + 0        , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH, System16Dip + 1        , "dip"       },
};

STDINPUTINFO(System16afire3);

static struct BurnInputInfo System16aDip3InputList[] = {
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

	{"Service"           , BIT_DIGITAL  , System16InputPort0 + 3 , "service"   },
	{"Diagnostics"       , BIT_DIGITAL  , System16InputPort0 + 2 , "diag"      },
	{"Reset"             , BIT_DIGITAL  , &System16Reset         , "reset"     },
	{"Dip 1"             , BIT_DIPSWITCH, System16Dip + 0        , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH, System16Dip + 1        , "dip"       },
	{"Dip 3"             , BIT_DIPSWITCH, System16Dip + 2        , "dip"       },
};

STDINPUTINFO(System16aDip3);

static struct BurnInputInfo MjleagueInputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , System16InputPort0 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , System16InputPort0 + 4, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL  , System16InputPort0 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , System16InputPort0 + 5, "p2 start"  },

	{"P1 Up"             , BIT_DIGITAL  , System16InputPort3 + 2, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , System16InputPort3 + 3, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , System16InputPort3 + 0, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , System16InputPort3 + 1, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , System16InputPort1 + 7, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL  , System16InputPort1 + 0, "p1 fire 2" },
	{"P1 Fire 3"         , BIT_DIGITAL  , System16InputPort1 + 1, "p1 fire 3" },
	{"P1 Fire 4"         , BIT_DIGITAL  , System16InputPort1 + 2, "p1 fire 4" },
	{"P1 Fire 5"         , BIT_DIGITAL  , System16InputPort1 + 3, "p1 fire 5" },
	A("P1 Bat Swing"     , BIT_ANALOG_REL, &System16AnalogPort0,  "p1 z-axis" ),

	{"P1 Up"             , BIT_DIGITAL  , System16InputPort3 + 6, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , System16InputPort3 + 7, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , System16InputPort3 + 4, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , System16InputPort3 + 5, "p1 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , System16InputPort2 + 7, "p2 fire 1" },
	{"P2 Fire 2"         , BIT_DIGITAL  , System16InputPort2 + 0, "p2 fire 2" },
	{"P2 Fire 3"         , BIT_DIGITAL  , System16InputPort2 + 1, "p2 fire 3" },
	{"P2 Fire 4"         , BIT_DIGITAL  , System16InputPort2 + 2, "p2 fire 4" },
	{"P2 Fire 5"         , BIT_DIGITAL  , System16InputPort2 + 3, "p2 fire 5" },
	A("P2 Bat Swing"     , BIT_ANALOG_REL, &System16AnalogPort1,  "p2 z-axis" ),

	{"Service"           , BIT_DIGITAL  , System16InputPort0 + 3 , "service"   },
	{"Diagnostics"       , BIT_DIGITAL  , System16InputPort0 + 2 , "diag"      },
	{"Reset"             , BIT_DIGITAL  , &System16Reset         , "reset"     },
	{"Dip 1"             , BIT_DIPSWITCH, System16Dip + 0        , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH, System16Dip + 1        , "dip"       },
};

STDINPUTINFO(Mjleague);

static struct BurnInputInfo QuartetInputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , System16InputPort0 + 6, "p1 coin"   },
	{"Coin 2"            , BIT_DIGITAL  , System16InputPort1 + 6, "p2 coin"   },
	{"Coin 3"            , BIT_DIGITAL  , System16InputPort2 + 6, "p3 coin"   },
	{"Coin 4"            , BIT_DIGITAL  , System16InputPort3 + 6, "p4 coin"   },

	{"P1 Up"             , BIT_DIGITAL  , System16InputPort0 + 1, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , System16InputPort0 + 0, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , System16InputPort0 + 3, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , System16InputPort0 + 2, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , System16InputPort0 + 4, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL  , System16InputPort0 + 5, "p1 fire 2" },

	{"P2 Up"             , BIT_DIGITAL  , System16InputPort1 + 1, "p2 up"     },
	{"P2 Down"           , BIT_DIGITAL  , System16InputPort1 + 0, "p2 down"   },
	{"P2 Left"           , BIT_DIGITAL  , System16InputPort1 + 3, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL  , System16InputPort1 + 2, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , System16InputPort1 + 4, "p2 fire 1" },
	{"P2 Fire 2"         , BIT_DIGITAL  , System16InputPort1 + 5, "p2 fire 2" },
	
	{"P3 Up"             , BIT_DIGITAL  , System16InputPort2 + 1, "p1 up"     },
	{"P3 Down"           , BIT_DIGITAL  , System16InputPort2 + 0, "p1 down"   },
	{"P3 Left"           , BIT_DIGITAL  , System16InputPort2 + 3, "p1 left"   },
	{"P3 Right"          , BIT_DIGITAL  , System16InputPort2 + 2, "p1 right"  },
	{"P3 Fire 1"         , BIT_DIGITAL  , System16InputPort2 + 4, "p1 fire 1" },
	{"P3 Fire 2"         , BIT_DIGITAL  , System16InputPort2 + 5, "p1 fire 2" },

	{"P4 Up"             , BIT_DIGITAL  , System16InputPort3 + 1, "p2 up"     },
	{"P4 Down"           , BIT_DIGITAL  , System16InputPort3 + 0, "p2 down"   },
	{"P4 Left"           , BIT_DIGITAL  , System16InputPort3 + 3, "p2 left"   },
	{"P4 Right"          , BIT_DIGITAL  , System16InputPort3 + 2, "p2 right"  },
	{"P4 Fire 1"         , BIT_DIGITAL  , System16InputPort3 + 4, "p2 fire 1" },
	{"P4 Fire 2"         , BIT_DIGITAL  , System16InputPort3 + 5, "p2 fire 2" },

	{"Service 1"         , BIT_DIGITAL  , System16InputPort0 + 7 , "service"   },
	{"Service 2"         , BIT_DIGITAL  , System16InputPort1 + 7 , "service2"  },
	{"Service 3"         , BIT_DIGITAL  , System16InputPort2 + 7 , "service3"  },
	{"Service 4"         , BIT_DIGITAL  , System16InputPort3 + 7 , "service4"  },
	{"Reset"             , BIT_DIGITAL  , &System16Reset         , "reset"     },
	{"Dip 1"             , BIT_DIPSWITCH, System16Dip + 0        , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH, System16Dip + 1        , "dip"       },
};

STDINPUTINFO(Quartet);

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

static struct BurnInputInfo Sjryuko1InputList[] = {
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

STDINPUTINFO(Sjryuko1);

#undef A

/*====================================================
Dip defs
====================================================*/

#define SYSTEM16A_COINAGE(dipval)								\
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
	
static struct BurnDIPInfo AfighterDIPList[]=
{
	// Default Values
	{0x13, 0xff, 0xff, 0xff, NULL                                 },
	{0x14, 0xff, 0xff, 0xfc, NULL                                 },

	// Dip 1
	SYSTEM16A_COINAGE(0x13)

	// Dip 2
	{0   , 0xfe, 0   , 2   , "Cabinet"                            },
	{0x14, 0x01, 0x01, 0x00, "Upright"                            },
	{0x14, 0x01, 0x01, 0x01, "Cocktail"                           },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x14, 0x01, 0x02, 0x02, "Off"                                },
	{0x14, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x14, 0x01, 0x0c, 0x08, "2"                                  },
	{0x14, 0x01, 0x0c, 0x0c, "3"                                  },
	{0x14, 0x01, 0x0c, 0x04, "4"                                  },
	{0x14, 0x01, 0x0c, 0x00, "Infinite"                           },
	
	{0   , 0xfe, 0   , 4   , "Bonus Life"                         },
	{0x14, 0x01, 0x30, 0x30, "10000 - 20000"                      },
	{0x14, 0x01, 0x30, 0x20, "20000 - 40000"                      },
	{0x14, 0x01, 0x30, 0x10, "30000 - 60000"                      },
	{0x14, 0x01, 0x30, 0x00, "40000 - 80000"                      },
	
	{0   , 0xfe, 0   , 2   , "Difficulty"                         },
	{0x14, 0x01, 0x40, 0x40, "Normal"                             },
	{0x14, 0x01, 0x40, 0x00, "Hard"                               },

	{0   , 0xfe, 0   , 2   , "Allow Continue"                     },
	{0x14, 0x01, 0x80, 0x00, "No"                                 },
	{0x14, 0x01, 0x80, 0x80, "Yes"                                },
};

STDDIPINFO(Afighter);

static struct BurnDIPInfo AlexkiddDIPList[]=
{
	// Default Values
	{0x13, 0xff, 0xff, 0xff, NULL                                 },
	{0x14, 0xff, 0xff, 0xfc, NULL                                 },

	// Dip 1
	SYSTEM16A_COINAGE(0x13)

	// Dip 2
	{0   , 0xfe, 0   , 2   , "Continues"                          },
	{0x14, 0x01, 0x01, 0x01, "Only before level 5"                },
	{0x14, 0x01, 0x01, 0x00, "Unlimited"                          },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x14, 0x01, 0x02, 0x02, "Off"                                },
	{0x14, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x14, 0x01, 0x0c, 0x0c, "3"                                  },
	{0x14, 0x01, 0x0c, 0x08, "4"                                  },
	{0x14, 0x01, 0x0c, 0x04, "5"                                  },
	{0x14, 0x01, 0x0c, 0x00, "240"                                },
	
	{0   , 0xfe, 0   , 4   , "Bonus Life"                         },
	{0x14, 0x01, 0x30, 0x20, "10000"                              },
	{0x14, 0x01, 0x30, 0x30, "20000"                              },
	{0x14, 0x01, 0x30, 0x10, "40000"                              },
	{0x14, 0x01, 0x30, 0x00, "None"                               },
	
	{0   , 0xfe, 0   , 4   , "Timer Adjust"                       },
	{0x14, 0x01, 0xc0, 0x80, "70"                                 },
	{0x14, 0x01, 0xc0, 0xc0, "60"                                 },
	{0x14, 0x01, 0xc0, 0x40, "50"                                 },
	{0x14, 0x01, 0xc0, 0x00, "40"                                 },
};

STDDIPINFO(Alexkidd);

static struct BurnDIPInfo AliensynDIPList[]=
{
	// Default Values
	{0x11, 0xff, 0xff, 0xff, NULL                                 },
	{0x12, 0xff, 0xff, 0xfd, NULL                                 },

	// Dip 1
	SYSTEM16A_COINAGE(0x11)

	// Dip 2
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x12, 0x01, 0x02, 0x02, "Off"                                },
	{0x12, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x12, 0x01, 0x0c, 0x08, "2"                                  },
	{0x12, 0x01, 0x0c, 0x0c, "3"                                  },
	{0x12, 0x01, 0x0c, 0x04, "4"                                  },
	{0x12, 0x01, 0x0c, 0x00, "127"                                },
	
	{0   , 0xfe, 0   , 4   , "Timer"                              },
	{0x12, 0x01, 0x30, 0x00, "150"                                },
	{0x12, 0x01, 0x30, 0x10, "160"                                },
	{0x12, 0x01, 0x30, 0x20, "170"                                },
	{0x12, 0x01, 0x30, 0x30, "180"                                },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x12, 0x01, 0xc0, 0x80, "Easy"                               },
	{0x12, 0x01, 0xc0, 0xc0, "Normal"                             },
	{0x12, 0x01, 0xc0, 0x40, "Hard"                               },
	{0x12, 0x01, 0xc0, 0x00, "Hardest"                            },
};

STDDIPINFO(Aliensyn);

static struct BurnDIPInfo BodyslamDIPList[]=
{
	// Default Values
	{0x13, 0xff, 0xff, 0xff, NULL                                 },
	{0x14, 0xff, 0xff, 0xfc, NULL                                 },

	// Dip 1
	SYSTEM16A_COINAGE(0x13)

	// Dip 2
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x14, 0x01, 0x02, 0x02, "Off"                                },
	{0x14, 0x01, 0x02, 0x00, "On"                                 },
};

STDDIPINFO(Bodyslam);

static struct BurnDIPInfo FantzoneDIPList[]=
{
	// Default Values
	{0x13, 0xff, 0xff, 0xff, NULL                                 },
	{0x14, 0xff, 0xff, 0xfc, NULL                                 },

	// Dip 1
	SYSTEM16A_COINAGE(0x13)

	// Dip 2
	{0   , 0xfe, 0   , 2   , "Cabinet"                            },
	{0x14, 0x01, 0x01, 0x00, "Upright"                            },
	{0x14, 0x01, 0x01, 0x01, "Cocktail"                           },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x14, 0x01, 0x02, 0x02, "Off"                                },
	{0x14, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x14, 0x01, 0x0c, 0x08, "2"                                  },
	{0x14, 0x01, 0x0c, 0x0c, "3"                                  },
	{0x14, 0x01, 0x0c, 0x04, "4"                                  },
	{0x14, 0x01, 0x0c, 0x00, "240"                                },
	
	{0   , 0xfe, 0   , 4   , "Extra Ship Cost"                    },
	{0x14, 0x01, 0x30, 0x30, "5000"                               },
	{0x14, 0x01, 0x30, 0x20, "10000"                              },
	{0x14, 0x01, 0x30, 0x10, "15000"                              },
	{0x14, 0x01, 0x30, 0x00, "20000"                              },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x14, 0x01, 0xc0, 0x80, "Easy"                               },
	{0x14, 0x01, 0xc0, 0xc0, "Normal"                             },
	{0x14, 0x01, 0xc0, 0x40, "Hard"                               },
	{0x14, 0x01, 0xc0, 0x00, "Hardest"                            },
};

STDDIPINFO(Fantzone);

static struct BurnDIPInfo MjleagueDIPList[]=
{
	// Default Values
	{0x1b, 0xff, 0xff, 0xff, NULL                                 },
	{0x1c, 0xff, 0xff, 0xd0, NULL                                 },

	// Dip 1
	SYSTEM16A_COINAGE(0x1b)

	// Dip 2
	{0   , 0xfe, 0   , 2   , "Cabinet"                            },
	{0x1c, 0x01, 0x01, 0x00, "Upright"                            },
	{0x1c, 0x01, 0x01, 0x01, "Cocktail"                           },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x1c, 0x01, 0x02, 0x02, "Off"                                },
	{0x1c, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Starting Points"                    },
	{0x1c, 0x01, 0x0c, 0x0c, "2000"                               },
	{0x1c, 0x01, 0x0c, 0x08, "3000"                               },
	{0x1c, 0x01, 0x0c, 0x04, "5000"                               },
	{0x1c, 0x01, 0x0c, 0x00, "10000"                              },
	
	{0   , 0xfe, 0   , 2   , "Team Select"                        },
	{0x1c, 0x01, 0x10, 0x02, "Off"                                },
	{0x1c, 0x01, 0x10, 0x10, "On"                                 },
};

STDDIPINFO(Mjleague);

static struct BurnDIPInfo QuartetDIPList[]=
{
	// Default Values
	{0x21, 0xff, 0xff, 0xff, NULL                                 },
	{0x22, 0xff, 0xff, 0xfe, NULL                                 },

	// Dip 1
	SYSTEM16A_COINAGE(0x21)

	// Dip 2
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x22, 0x01, 0x01, 0x01, "Off"                                },
	{0x22, 0x01, 0x01, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Credit Power"                       },
	{0x22, 0x01, 0x06, 0x04, "500"                                },
	{0x22, 0x01, 0x06, 0x06, "1000"                               },
	{0x22, 0x01, 0x06, 0x02, "2000"                               },
	{0x22, 0x01, 0x06, 0x00, "9000"                               },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x22, 0x01, 0x18, 0x10, "Easy"                               },
	{0x22, 0x01, 0x18, 0x18, "Normal"                             },
	{0x22, 0x01, 0x18, 0x08, "Hard"                               },
	{0x22, 0x01, 0x18, 0x00, "Hardest"                            },
	
	{0   , 0xfe, 0   , 2   , "Coin During Game"                   },
	{0x22, 0x01, 0x20, 0x20, "Power"                              },
	{0x22, 0x01, 0x20, 0x00, "Credit"                             },
	
	{0   , 0xfe, 0   , 2   , "Free Play"                          },
	{0x22, 0x01, 0x40, 0x40, "Off"                                },
	{0x22, 0x01, 0x40, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 2   , "Service Mode"                       },
	{0x22, 0x01, 0x80, 0x80, "Off"                                },
	{0x22, 0x01, 0x80, 0x00, "On"                                 },
};

STDDIPINFO(Quartet);

static struct BurnDIPInfo Quart2DIPList[]=
{
	// Default Values
	{0x13, 0xff, 0xff, 0xff, NULL                                 },
	{0x14, 0xff, 0xff, 0xfe, NULL                                 },

	// Dip 1
	SYSTEM16A_COINAGE(0x13)

	// Dip 2
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x14, 0x01, 0x01, 0x01, "Off"                                },
	{0x14, 0x01, 0x01, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Credit Power"                       },
	{0x14, 0x01, 0x06, 0x04, "500"                                },
	{0x14, 0x01, 0x06, 0x06, "1000"                               },
	{0x14, 0x01, 0x06, 0x02, "2000"                               },
	{0x14, 0x01, 0x06, 0x00, "9000"                               },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x14, 0x01, 0x18, 0x10, "Easy"                               },
	{0x14, 0x01, 0x18, 0x18, "Normal"                             },
	{0x14, 0x01, 0x18, 0x08, "Hard"                               },
	{0x14, 0x01, 0x18, 0x00, "Hardest"                            },
};

STDDIPINFO(Quart2);

static struct BurnDIPInfo SdiDIPList[]=
{
	// Default Values
	{0x15, 0xff, 0xff, 0xff, NULL                                 },
	{0x16, 0xff, 0xff, 0xfd, NULL                                 },

	// Dip 1
	SYSTEM16A_COINAGE(0x15)

	// Dip 2
	{0   , 0xfe, 0   , 2   , "Allow Continue"                     },
	{0x16, 0x01, 0x01, 0x01, "No"                                 },
	{0x16, 0x01, 0x01, 0x00, "Yes"                                },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x16, 0x01, 0x02, 0x02, "Off"                                },
	{0x16, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x16, 0x01, 0x0c, 0x08, "2"                                  },
	{0x16, 0x01, 0x0c, 0x0c, "3"                                  },
	{0x16, 0x01, 0x0c, 0x04, "4"                                  },
	{0x16, 0x01, 0x0c, 0x00, "Free"                               },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x16, 0x01, 0x30, 0x20, "Easy"                               },
	{0x16, 0x01, 0x30, 0x30, "Normal"                             },
	{0x16, 0x01, 0x30, 0x10, "Hard"                               },
	{0x16, 0x01, 0x30, 0x00, "Hardest"                            },
	
	{0   , 0xfe, 0   , 4   , "Bonus Life"                         },
	{0x16, 0x01, 0xc0, 0x80, "Every 50000"                        },
	{0x16, 0x01, 0xc0, 0xc0, "50000"                              },
	{0x16, 0x01, 0xc0, 0x40, "100000"                             },
	{0x16, 0x01, 0xc0, 0x00, "None"                               },
};

STDDIPINFO(Sdi);

static struct BurnDIPInfo ShinobiDIPList[]=
{
	// Default Values
	{0x15, 0xff, 0xff, 0xff, NULL                                 },
	{0x16, 0xff, 0xff, 0xfc, NULL                                 },

	// Dip 1
	SYSTEM16A_COINAGE(0x15)

	// Dip 2
	{0   , 0xfe, 0   , 2   , "Cabinet"                            },
	{0x16, 0x01, 0x01, 0x00, "Upright"                            },
	{0x16, 0x01, 0x01, 0x01, "Cocktail"                           },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x16, 0x01, 0x02, 0x02, "Off"                                },
	{0x16, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x16, 0x01, 0x0c, 0x08, "2"                                  },
	{0x16, 0x01, 0x0c, 0x0c, "3"                                  },
	{0x16, 0x01, 0x0c, 0x04, "5"                                  },
	{0x16, 0x01, 0x0c, 0x00, "240"                                },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x16, 0x01, 0x30, 0x20, "Easy"                               },
	{0x16, 0x01, 0x30, 0x30, "Normal"                             },
	{0x16, 0x01, 0x30, 0x10, "Hard"                               },
	{0x16, 0x01, 0x30, 0x00, "Hardest"                            },
	
	{0   , 0xfe, 0   , 2   , "Enemy Bullet Speed"                 },
	{0x16, 0x01, 0x40, 0x40, "Slow"                               },
	{0x16, 0x01, 0x40, 0x00, "Fast"                               },
	
	{0   , 0xfe, 0   , 2   , "Language"                           },
	{0x16, 0x01, 0x80, 0x80, "Japanese"                           },
	{0x16, 0x01, 0x80, 0x00, "English"                            },
};

STDDIPINFO(Shinobi);

static struct BurnDIPInfo Sjryuko1DIPList[]=
{
	// Default Values
	{0x1c, 0xff, 0xff, 0xff, NULL                                 },
	{0x1d, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	SYSTEM16A_COINAGE(0x1c)
	
	// Dip 2
};

STDDIPINFO(Sjryuko1);

static struct BurnDIPInfo TetrisDIPList[]=
{
	// Default Values
	{0x11, 0xff, 0xff, 0xff, NULL                                 },
	{0x12, 0xff, 0xff, 0xfd, NULL                                 },

	// Dip 1
	SYSTEM16A_COINAGE(0x11)

	// Dip 2
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x12, 0x01, 0x02, 0x02, "Off"                                },
	{0x12, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Difficulty"                         },
	{0x12, 0x01, 0x30, 0x20, "Easy"                               },
	{0x12, 0x01, 0x30, 0x30, "Normal"                             },
	{0x12, 0x01, 0x30, 0x10, "Hard"                               },
	{0x12, 0x01, 0x30, 0x00, "Hardest"                            },
};

STDDIPINFO(Tetris);

static struct BurnDIPInfo TimescanDIPList[]=
{
	// Default Values
	{0x13, 0xff, 0xff, 0xff, NULL                                 },
	{0x14, 0xff, 0xff, 0xf5, NULL                                 },
	{0x15, 0xff, 0xff, 0xff, NULL                                 },

	// Dip 1
	SYSTEM16A_COINAGE(0x13)

	// Dip 2
	{0   , 0xfe, 0   , 2   , "Cabinet"                            },
	{0x14, 0x01, 0x01, 0x00, "Cocktail"                           },
	{0x14, 0x01, 0x01, 0x01, "Upright"                            },
	
	{0   , 0xfe, 0   , 16  , "Bonus"                              },
	{0x14, 0x01, 0x1e, 0x16, "Replay 1000000/2000000"             },
	{0x14, 0x01, 0x1e, 0x14, "Replay 1200000/2500000"             },
	{0x14, 0x01, 0x1e, 0x12, "Replay 1500000/3000000"             },
	{0x14, 0x01, 0x1e, 0x10, "Replay 2000000/4000000"             },
	{0x14, 0x01, 0x1e, 0x1c, "Replay 1000000"                     },
	{0x14, 0x01, 0x1e, 0x1e, "Replay 1200000"                     },
	{0x14, 0x01, 0x1e, 0x1a, "Replay 1500000"                     },
	{0x14, 0x01, 0x1e, 0x18, "Replay 1800000"                     },
	{0x14, 0x01, 0x1e, 0x0e, "Extra Ball 100000"                  },
	{0x14, 0x01, 0x1e, 0x0c, "Extra Ball 200000"                  },
	{0x14, 0x01, 0x1e, 0x0a, "Extra Ball 300000"                  },
	{0x14, 0x01, 0x1e, 0x08, "Extra Ball 400000"                  },
	{0x14, 0x01, 0x1e, 0x06, "Extra Ball 500000"                  },
	{0x14, 0x01, 0x1e, 0x04, "Extra Ball 600000"                  },
	{0x14, 0x01, 0x1e, 0x02, "Extra Ball 700000"                  },
	{0x14, 0x01, 0x1e, 0x00, "None"                               },
	
	{0   , 0xfe, 0   , 2   , "Match"                              },
	{0x14, 0x01, 0x20, 0x00, "Off"                                },
	{0x14, 0x01, 0x20, 0x20, "On"                                 },
	
	{0   , 0xfe, 0   , 2   , "Pin Rebound"                        },
	{0x14, 0x01, 0x40, 0x40, "Well"                               },
	{0x14, 0x01, 0x40, 0x00, "A Little"                           },
	
	{0   , 0xfe, 0   , 2   , "Lives"                              },
	{0x14, 0x01, 0x80, 0x80, "3"                                  },
	{0x14, 0x01, 0x80, 0x00, "5"                                  },
	
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

static struct BurnDIPInfo Wb31DIPList[]=
{
	// Default Values
	{0x13, 0xff, 0xff, 0xff, NULL                                 },
	{0x14, 0xff, 0xff, 0xfc, NULL                                 },

	// Dip 1
	SYSTEM16A_COINAGE(0x13)

	// Dip 2
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                        },
	{0x14, 0x01, 0x02, 0x02, "Off"                                },
	{0x14, 0x01, 0x02, 0x00, "On"                                 },
	
	{0   , 0xfe, 0   , 4   , "Lives"                              },
	{0x14, 0x01, 0x0c, 0x00, "2"                                  },
	{0x14, 0x01, 0x0c, 0x0c, "3"                                  },
	{0x14, 0x01, 0x0c, 0x08, "4"                                  },
	{0x14, 0x01, 0x0c, 0x04, "5"                                  },
	
	{0   , 0xfe, 0   , 2   , "Bonus Life"                         },
	{0x14, 0x01, 0x10, 0x10, "5k, 10k, 18k, 30k"                  },
	{0x14, 0x01, 0x10, 0x00, "5k, 15k, 30k"                       },
	
	{0   , 0xfe, 0   , 2   , "Difficulty"                         },
	{0x14, 0x01, 0x20, 0x20, "Normal"                             },
	{0x14, 0x01, 0x20, 0x00, "Hard"                               },
	
	{0   , 0xfe, 0   , 2   , "Invincible Mode"                    },
	{0x14, 0x01, 0x40, 0x40, "No"                                 },
	{0x14, 0x01, 0x40, 0x00, "Yes"                                },
};

STDDIPINFO(Wb31);

#undef SYSTEM16A_COINAGE

/*====================================================
Rom defs
====================================================*/

static struct BurnRomInfo AfighterRomDesc[] = {
	{ "10353",         0x08000, 0x5a757dc9, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "10350",         0x08000, 0xf2cd6b3f, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "10352",         0x08000, 0xf8abb143, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "10349",         0x08000, 0x4b434c37, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "10351",         0x08000, 0xede21d8d, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "10348",         0x08000, 0xe51e3012, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "10281",         0x10000, 0x30e92cda, SYS16_ROM_TILES | BRF_GRA },
	{ "10282",         0x10000, 0xb67b8910, SYS16_ROM_TILES | BRF_GRA },
	{ "10283",         0x10000, 0xe7dbfd2d, SYS16_ROM_TILES | BRF_GRA },
	
	{ "10285",         0x08000, 0x98aa3d04, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10289",         0x08000, 0xc59d1b98, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10286",         0x08000, 0x8da050cf, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10290",         0x08000, 0x39354223, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10287",         0x08000, 0x7989b74a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10291",         0x08000, 0x6e4b245c, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10288",         0x08000, 0xd3ce551a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10292",         0x08000, 0xcef289a3, SYS16_ROM_SPRITES | BRF_GRA },

	{ "10284",         0x08000, 0x8ff09116, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Afighter);
STD_ROM_FN(Afighter);

static struct BurnRomInfo AlexkiddRomDesc[] = {
	{ "10447.43",      0x10000, 0x29e87f71, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "10445.26",      0x10000, 0x25ce5b6f, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "10448.42",      0x10000, 0x05baedb5, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "10446.25",      0x10000, 0xcd61d23c, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "10431.95",      0x08000, 0xa7962c39, SYS16_ROM_TILES | BRF_GRA },
	{ "10432.94",      0x08000, 0xdb8cd24e, SYS16_ROM_TILES | BRF_GRA },
	{ "10433.93",      0x08000, 0xe163c8c2, SYS16_ROM_TILES | BRF_GRA },
	
	{ "10437.10",      0x08000, 0x522f7618, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10441.11",      0x08000, 0x74e3a35c, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10438.17",      0x08000, 0x738a6362, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10442.18",      0x08000, 0x86cb9c14, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10439.23",      0x08000, 0xb391aca7, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10443.24",      0x08000, 0x95d32635, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10440.29",      0x08000, 0x23939508, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10444.30",      0x08000, 0x82115823, SYS16_ROM_SPRITES | BRF_GRA },

	{ "10434.12",      0x08000, 0x77141cce, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "7751.bin",      0x00400, 0x6a9534fc, SYS16_ROM_7751PROG | BRF_ESS | BRF_PRG },
	
	{ "10435.1",       0x08000, 0xad89f6e3, SYS16_ROM_7751DATA | BRF_SND },
	{ "10436.2",       0x08000, 0x96c76613, SYS16_ROM_7751DATA | BRF_SND },
};


STD_ROM_PICK(Alexkidd);
STD_ROM_FN(Alexkidd);

static struct BurnRomInfo Alexkid1RomDesc[] = {
	{ "epr10429.42",   0x10000, 0xbdf49eca, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10427.26",   0x10000, 0xf6e3dd29, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10430.43",   0x10000, 0x89e3439f, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10428.25",   0x10000, 0xdbed3210, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "10431.95",      0x08000, 0xa7962c39, SYS16_ROM_TILES | BRF_GRA },
	{ "10432.94",      0x08000, 0xdb8cd24e, SYS16_ROM_TILES | BRF_GRA },
	{ "10433.93",      0x08000, 0xe163c8c2, SYS16_ROM_TILES | BRF_GRA },
	
	{ "10437.10",      0x08000, 0x522f7618, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10441.11",      0x08000, 0x74e3a35c, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10438.17",      0x08000, 0x738a6362, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10442.18",      0x08000, 0x86cb9c14, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10439.23",      0x08000, 0xb391aca7, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10443.24",      0x08000, 0x95d32635, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10440.29",      0x08000, 0x23939508, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10444.30",      0x08000, 0x82115823, SYS16_ROM_SPRITES | BRF_GRA },

	{ "10434.12",      0x08000, 0x77141cce, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "7751.bin",      0x00400, 0x6a9534fc, SYS16_ROM_7751PROG | BRF_ESS | BRF_PRG },
	
	{ "10435.1",       0x08000, 0xad89f6e3, SYS16_ROM_7751DATA | BRF_SND },
	{ "10436.2",       0x08000, 0x96c76613, SYS16_ROM_7751DATA | BRF_SND },
};


STD_ROM_PICK(Alexkid1);
STD_ROM_FN(Alexkid1);

static struct BurnRomInfo Aliensy1RomDesc[] = {
	{ "epr10699.43",   0x08000, 0x3fd38d17, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10696.26",   0x08000, 0xd734f19f, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10700.42",   0x08000, 0x3b04b252, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10697.25",   0x08000, 0xf2bc123d, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "10701",         0x08000, 0x92171751, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "10698",         0x08000, 0xc1e4fdc0, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "10739",         0x10000, 0xa29ec207, SYS16_ROM_TILES | BRF_GRA },
	{ "10740",         0x10000, 0x47f93015, SYS16_ROM_TILES | BRF_GRA },
	{ "10741",         0x10000, 0x4970739c, SYS16_ROM_TILES | BRF_GRA },
	
	{ "10709.b1",      0x10000, 0xaddf0a90, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10713.b5",      0x10000, 0xececde3a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10710.b2",      0x10000, 0x992369eb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10714.b6",      0x10000, 0x91bf42fb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10711.b3",      0x10000, 0x29166ef6, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10715.b7",      0x10000, 0xa7c57384, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10712.b4",      0x10000, 0x876ad019, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10716.b8",      0x10000, 0x40ba1d48, SYS16_ROM_SPRITES | BRF_GRA },

	{ "10705",         0x08000, 0x777b749e, SYS16_ROM_Z80PROG | BRF_ESS |BRF_PRG },
	
	{ "7751.bin",      0x00400, 0x6a9534fc, SYS16_ROM_7751PROG | BRF_ESS | BRF_PRG },
	
	{ "10706",         0x08000, 0xaa114acc, SYS16_ROM_7751DATA | BRF_SND },
	{ "10707",         0x08000, 0x800c1d82, SYS16_ROM_7751DATA | BRF_SND },
	{ "10708",         0x08000, 0x5921ef52, SYS16_ROM_7751DATA | BRF_SND },
};


STD_ROM_PICK(Aliensy1);
STD_ROM_FN(Aliensy1);

static struct BurnRomInfo Aliensy2RomDesc[] = {
	{ "10808",         0x08000, 0xe669929f, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "10806",         0x08000, 0x9f7f8fdd, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "10809",         0x08000, 0x9a424919, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "10807",         0x08000, 0x3d2c3530, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "10701",         0x08000, 0x92171751, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "10698",         0x08000, 0xc1e4fdc0, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "10739",         0x10000, 0xa29ec207, SYS16_ROM_TILES | BRF_GRA },
	{ "10740",         0x10000, 0x47f93015, SYS16_ROM_TILES | BRF_GRA },
	{ "10741",         0x10000, 0x4970739c, SYS16_ROM_TILES | BRF_GRA },
	
	{ "10709.b1",      0x10000, 0xaddf0a90, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10713.b5",      0x10000, 0xececde3a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10710.b2",      0x10000, 0x992369eb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10714.b6",      0x10000, 0x91bf42fb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10711.b3",      0x10000, 0x29166ef6, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10715.b7",      0x10000, 0xa7c57384, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10712.b4",      0x10000, 0x876ad019, SYS16_ROM_SPRITES | BRF_GRA },
	{ "10716.b8",      0x10000, 0x40ba1d48, SYS16_ROM_SPRITES | BRF_GRA },

	{ "10705",         0x08000, 0x777b749e, SYS16_ROM_Z80PROG | BRF_ESS |BRF_PRG },
	
	{ "7751.bin",      0x00400, 0x6a9534fc, SYS16_ROM_7751PROG | BRF_ESS | BRF_PRG },
	
	{ "10706",         0x08000, 0xaa114acc, SYS16_ROM_7751DATA | BRF_SND },
	{ "10707",         0x08000, 0x800c1d82, SYS16_ROM_7751DATA | BRF_SND },
	{ "10708",         0x08000, 0x5921ef52, SYS16_ROM_7751DATA | BRF_SND },
};


STD_ROM_PICK(Aliensy2);
STD_ROM_FN(Aliensy2);

static struct BurnRomInfo BodyslamRomDesc[] = {
	{ "epr-10066.b9",  0x08000, 0x6cd53290, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-10063.b6",  0x08000, 0xdd849a16, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-10067.b10", 0x08000, 0xdb22a5ce, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-10064.b7",  0x08000, 0x53d6b7e0, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-10068.b11", 0x08000, 0x15ccc665, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-10065.b8",  0x08000, 0x0e5fa314, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr-10321.c9",  0x08000, 0xcd3e7cba, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-10322.c10", 0x08000, 0xb53d3217, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-10323.c11", 0x08000, 0x915a3e61, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr-10012.c5",  0x08000, 0x990824e8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-10016.b2",  0x08000, 0xaf5dc72f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-10013.c6",  0x08000, 0x9a0919c5, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-10017.b3",  0x08000, 0x62aafd95, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-10027.c7",  0x08000, 0x3f1c57c7, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-10028.b4",  0x08000, 0x80d4946d, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-10015.c8",  0x08000, 0x582d3b6a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-10019.b5",  0x08000, 0xe020c38b, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr-10026.b1",  0x08000, 0x123b69b8, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "7751.bin",      0x00400, 0x6a9534fc, SYS16_ROM_7751PROG | BRF_ESS | BRF_PRG },
	
	{ "epr-10029.c1",  0x08000, 0x7e4aca83, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-10030.c2",  0x08000, 0xdcc1df0b, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-10031.c3",  0x08000, 0xea3c4472, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-10032.c4",  0x08000, 0x0aabebce, SYS16_ROM_7751DATA | BRF_SND },
	
	{ "317-0015.mcu",  0x01000, 0x00000000, BRF_NODUMP },
};


STD_ROM_PICK(Bodyslam);
STD_ROM_FN(Bodyslam);

static struct BurnRomInfo DumpmtmtRomDesc[] = {
	{ "epr-7704a.b9",  0x08000, 0x96de6c7b, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7701a.b6",  0x08000, 0x786d1009, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7705a.b10", 0x08000, 0xfc584391, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7702a.b7",  0x08000, 0x2241a8fd, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7706a.b11", 0x08000, 0x6bbcc9d0, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7703a.b8",  0x08000, 0xfcb0cd40, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr-7707a.c9",  0x08000, 0x45318738, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-7708a.c10", 0x08000, 0x411be9a4, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-7709a.c11", 0x08000, 0x74ceb5a8, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr-7715.c5",   0x08000, 0xbf47e040, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7719.b2",   0x08000, 0xfa5c5d6c, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-10013.c6",  0x08000, 0x9a0919c5, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-10017.b3",  0x08000, 0x62aafd95, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7717.c7",   0x08000, 0xfa64c86d, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7721.b4",   0x08000, 0x62a9143e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-10015.c8",  0x08000, 0x582d3b6a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-10019.b5",  0x08000, 0xe020c38b, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr-7710a.b1",  0x08000, 0xa19b8ba8, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "7751.bin",      0x00400, 0x6a9534fc, SYS16_ROM_7751PROG | BRF_ESS | BRF_PRG },
	
	{ "epr-7711.c1",   0x08000, 0xefa9aabd, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7712.c2",   0x08000, 0x7bcd85cf, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7713.c3",   0x08000, 0x33f292e7, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7714.c4",   0x08000, 0x8fd48c47, SYS16_ROM_7751DATA | BRF_SND },
	
	{ "317-00xx.mcu",  0x01000, 0x00000000, BRF_NODUMP },
};


STD_ROM_PICK(Dumpmtmt);
STD_ROM_FN(Dumpmtmt);

static struct BurnRomInfo FantzoneRomDesc[] = {
	{ "epr7385a.43",   0x08000, 0x4091af42, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr7382a.26",   0x08000, 0x77d67bfd, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr7386a.42",   0x08000, 0xb0a67cd0, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr7383a.25",   0x08000, 0x5f79b2a9, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "7387.41",       0x08000, 0x0acd335d, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "7384.24",       0x08000, 0xfd909341, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "7388.95",       0x08000, 0x8eb02f6b, SYS16_ROM_TILES | BRF_GRA },
	{ "7389.94",       0x08000, 0x2f4f71b8, SYS16_ROM_TILES | BRF_GRA },
	{ "7390.93",       0x08000, 0xd90609c6, SYS16_ROM_TILES | BRF_GRA },
	
	{ "7392.10",       0x08000, 0x5bb7c8b6, SYS16_ROM_SPRITES | BRF_GRA },
	{ "7396.11",       0x08000, 0x74ae4b57, SYS16_ROM_SPRITES | BRF_GRA },
	{ "7393.17",       0x08000, 0x14fc7e82, SYS16_ROM_SPRITES | BRF_GRA },
	{ "7397.18",       0x08000, 0xe05a1e25, SYS16_ROM_SPRITES | BRF_GRA },
	{ "7394.23",       0x08000, 0x531ca13f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "7398.24",       0x08000, 0x68807b49, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr7535a.12",   0x08000, 0xbc1374fa, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Fantzone);
STD_ROM_FN(Fantzone);

static struct BurnRomInfo Fantzon1RomDesc[] = {
	{ "7385.43",       0x08000, 0x5cb64450, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "7382.26",       0x08000, 0x3fda7416, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "7386.42",       0x08000, 0x15810ace, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "7383.25",       0x08000, 0xa001e10a, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "7387.41",       0x08000, 0x0acd335d, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "7384.24",       0x08000, 0xfd909341, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "7388.95",       0x08000, 0x8eb02f6b, SYS16_ROM_TILES | BRF_GRA },
	{ "7389.94",       0x08000, 0x2f4f71b8, SYS16_ROM_TILES | BRF_GRA },
	{ "7390.93",       0x08000, 0xd90609c6, SYS16_ROM_TILES | BRF_GRA },
	
	{ "7392.10",       0x08000, 0x5bb7c8b6, SYS16_ROM_SPRITES | BRF_GRA },
	{ "7396.11",       0x08000, 0x74ae4b57, SYS16_ROM_SPRITES | BRF_GRA },
	{ "7393.17",       0x08000, 0x14fc7e82, SYS16_ROM_SPRITES | BRF_GRA },
	{ "7397.18",       0x08000, 0xe05a1e25, SYS16_ROM_SPRITES | BRF_GRA },
	{ "7394.23",       0x08000, 0x531ca13f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "7398.24",       0x08000, 0x68807b49, SYS16_ROM_SPRITES | BRF_GRA },

	{ "7535.12",       0x08000, 0x0cb2126a, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Fantzon1);
STD_ROM_FN(Fantzon1);

static struct BurnRomInfo MjleagueRomDesc[] = {
	{ "epr-7404.9b",   0x08000, 0xec1655b5, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7401.6b",   0x08000, 0x2befa5e0, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7405.10b",  0x08000, 0x7a4f4e38, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7402.7b",   0x08000, 0xb7bef762, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7406a.11b", 0x08000, 0xbb743639, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7403a.8b",  0x08000, 0x0a39a4d0, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr-7051.9a",   0x08000, 0x10ca255a, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-7052.10a",  0x08000, 0x2550db0e, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-7053.11a",  0x08000, 0x5bfea038, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr-7055.5a",   0x08000, 0x1fb860bd, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7059.2b",   0x08000, 0x3d14091d, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7056.6a",   0x08000, 0xb35dd968, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7060.3b",   0x08000, 0x61bb3757, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7057.7a",   0x08000, 0x3e5a2b6f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7061.4b",   0x08000, 0xc808dad5, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7058.8a",   0x08000, 0xb543675f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7062.5b",   0x08000, 0x9168eb47, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr-7054c.1b",  0x08000, 0x4443b744, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "7751.bin",      0x00400, 0x6a9534fc, SYS16_ROM_7751PROG | BRF_ESS | BRF_PRG },
	
	{ "epr-7063.1a",   0x08000, 0x45d8908a, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7065.2a",   0x08000, 0x8c8f8cff, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7064.3a",   0x08000, 0x159f6636, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7066.4a",   0x08000, 0xf5cfa91f, SYS16_ROM_7751DATA | BRF_SND },
};


STD_ROM_PICK(Mjleague);
STD_ROM_FN(Mjleague);

static struct BurnRomInfo QuartetRomDesc[] = {
	{ "epr-7458a.9b",  0x08000, 0x42e7b23e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7455a.6b",  0x08000, 0x01631ab2, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7459a.10b", 0x08000, 0x6b540637, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7456a.7b",  0x08000, 0x31ca583e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7460.11b",  0x08000, 0xa444ea13, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7457.8b",   0x08000, 0x3b282c23, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr-7461.9c",   0x08000, 0xf6af07f2, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-7462.10c",  0x08000, 0x7914af28, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-7463.11c",  0x08000, 0x827c5603, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr-7465.5c",   0x08000, 0x8a1ab7d7, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7469.2b",   0x08000, 0xcb65ae4f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7466.6c",   0x08000, 0xb2d3f4f3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7470.3b",   0x08000, 0x16fc67b1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7467.7c",   0x08000, 0x0af68de2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7471.4b",   0x08000, 0x13fad5ac, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7468.8c",   0x08000, 0xddfd40c0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7472.5b",   0x08000, 0x8e2762ec, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr-7464.1b",   0x08000, 0x9f291306, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "7751.bin",      0x00400, 0x6a9534fc, SYS16_ROM_7751PROG | BRF_ESS | BRF_PRG },
	
	{ "epr-7473.1c",   0x08000, 0x06ec75fa, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7475.2c",   0x08000, 0x7abd1206, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7474.3c",   0x08000, 0xdbf853b8, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7476.4c",   0x08000, 0x5eba655a, SYS16_ROM_7751DATA | BRF_SND },
	
	{ "315-5194.mcu",  0x01000, 0x00000000, BRF_NODUMP },
	
	{ "pal16r6a.22g",  0x00104, 0x00000000, BRF_NODUMP }, // PLD
	{ "pal16r6a.23g",  0x00104, 0x00000000, BRF_NODUMP }, // PLD
	{ "pls153.8j",     0x000eb, 0x0fe1eefd, BRF_OPT }, // PLD
};


STD_ROM_PICK(Quartet);
STD_ROM_FN(Quartet);

static struct BurnRomInfo Quartet1RomDesc[] = {
	{ "epr-7458.9b",   0x08000, 0x0096499f, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7455.6b",   0x08000, 0xda934390, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7459.10b",  0x08000, 0xd130cf61, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7456.7b",   0x08000, 0x7847149f, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7460.11b",  0x08000, 0xa444ea13, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7457.8b",   0x08000, 0x3b282c23, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr-7461.9c",   0x08000, 0xf6af07f2, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-7462.10c",  0x08000, 0x7914af28, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-7463.11c",  0x08000, 0x827c5603, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr-7465.5c",   0x08000, 0x8a1ab7d7, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7469.2b",   0x08000, 0xcb65ae4f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7466.6c",   0x08000, 0xb2d3f4f3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7470.3b",   0x08000, 0x16fc67b1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7467.7c",   0x08000, 0x0af68de2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7471.4b",   0x08000, 0x13fad5ac, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7468.8c",   0x08000, 0xddfd40c0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7472.5b",   0x08000, 0x8e2762ec, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr-7464.1b",   0x08000, 0x9f291306, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "7751.bin",      0x00400, 0x6a9534fc, SYS16_ROM_7751PROG | BRF_ESS | BRF_PRG },
	
	{ "epr-7473.1c",   0x08000, 0x06ec75fa, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7475.2c",   0x08000, 0x7abd1206, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7474.3c",   0x08000, 0xdbf853b8, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7476.4c",   0x08000, 0x5eba655a, SYS16_ROM_7751DATA | BRF_SND },
	
	{ "315-5194.mcu",  0x01000, 0x00000000, BRF_NODUMP },
	
	{ "pal16r6a.22g",  0x00104, 0x00000000, BRF_NODUMP }, // PLD
	{ "pal16r6a.23g",  0x00104, 0x00000000, BRF_NODUMP }, // PLD
	{ "pls153.8j",     0x000eb, 0x0fe1eefd, BRF_OPT }, // PLD
};


STD_ROM_PICK(Quartet1);
STD_ROM_FN(Quartet1);

static struct BurnRomInfo Quart21RomDesc[] = {
	{ "epr-7695.b9",   0x08000, 0x67177cd8, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7692.b6",   0x08000, 0x50f50b08, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7696.b10",  0x08000, 0x4273c3b7, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7693.b7",   0x08000, 0x0aa337bb, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7697.b11",  0x08000, 0x3a6a375d, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7694.b8",   0x08000, 0xd87b2ca2, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr-7698.c9",   0x08000, 0x547a6058, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-7699.c10",  0x08000, 0x77ec901d, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-7700.c11",  0x08000, 0x7e348cce, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr-7465.5c",   0x08000, 0x8a1ab7d7, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7469.2b",   0x08000, 0xcb65ae4f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7466.6c",   0x08000, 0xb2d3f4f3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7470.3b",   0x08000, 0x16fc67b1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7467.7c",   0x08000, 0x0af68de2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7471.4b",   0x08000, 0x13fad5ac, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7468.8c",   0x08000, 0xddfd40c0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7472.5b",   0x08000, 0x8e2762ec, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr-7464.1b",   0x08000, 0x9f291306, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "7751.bin",      0x00400, 0x6a9534fc, SYS16_ROM_7751PROG | BRF_ESS | BRF_PRG },
	
	{ "epr-7473.1c",   0x08000, 0x06ec75fa, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7475.2c",   0x08000, 0x7abd1206, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7474.3c",   0x08000, 0xdbf853b8, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7476.4c",   0x08000, 0x5eba655a, SYS16_ROM_7751DATA | BRF_SND },
	
	{ "317-0010.mcu",  0x01000, 0x00000000, BRF_NODUMP },
};


STD_ROM_PICK(Quart21);
STD_ROM_FN(Quart21);

static struct BurnRomInfo Quart2RomDesc[] = {
	{ "epr-7728.b9",   0x08000, 0x56a8c88e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7725.b6",   0x08000, 0xee15fcc9, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7729.b10",  0x08000, 0xbc242123, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7726.b7",   0x08000, 0x9d1c48e7, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7697.b11",  0x08000, 0x3a6a375d, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr-7694.b8",   0x08000, 0xd87b2ca2, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr-7698.c9",   0x08000, 0x547a6058, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-7699.c10",  0x08000, 0x77ec901d, SYS16_ROM_TILES | BRF_GRA },
	{ "epr-7700.c11",  0x08000, 0x7e348cce, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr-7465.5c",   0x08000, 0x8a1ab7d7, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7469.2b",   0x08000, 0xcb65ae4f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7466.6c",   0x08000, 0xb2d3f4f3, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7470.3b",   0x08000, 0x16fc67b1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7467.7c",   0x08000, 0x0af68de2, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7471.4b",   0x08000, 0x13fad5ac, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7468.8c",   0x08000, 0xddfd40c0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr-7472.5b",   0x08000, 0x8e2762ec, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr-7464.1b",   0x08000, 0x9f291306, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "7751.bin",      0x00400, 0x6a9534fc, SYS16_ROM_7751PROG | BRF_ESS | BRF_PRG },
	
	{ "epr-7473.1c",   0x08000, 0x06ec75fa, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7475.2c",   0x08000, 0x7abd1206, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7474.3c",   0x08000, 0xdbf853b8, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr-7476.4c",   0x08000, 0x5eba655a, SYS16_ROM_7751DATA | BRF_SND },
};


STD_ROM_PICK(Quart2);
STD_ROM_FN(Quart2);

static struct BurnRomInfo SdiRomDesc[] = {
	{ "epr10970.43",   0x08000, 0xb8fa4a2c, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10968.26",   0x08000, 0xa3f97793, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10971.42",   0x08000, 0xc44a0328, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10969.25",   0x08000, 0x455d15bd, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10755.41",   0x08000, 0x405e3969, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10752.24",   0x08000, 0x77453740, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr10756.95",   0x10000, 0x44d8a506, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10757.94",   0x10000, 0x497e1740, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10758.93",   0x10000, 0x61d61486, SYS16_ROM_TILES | BRF_GRA },
	
	{ "b1.rom",        0x10000, 0x30e2c50a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "b5.rom",        0x10000, 0x794e3e8b, SYS16_ROM_SPRITES | BRF_GRA },
	{ "b2.rom",        0x10000, 0x6a8b3fd0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "b6.rom",        0x10000, 0x602da5d5, SYS16_ROM_SPRITES | BRF_GRA },
	{ "b3.rom",        0x10000, 0xb9de3aeb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "b7.rom",        0x10000, 0x0a73a057, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr10759.12",   0x08000, 0xd7f9649f, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Sdi);
STD_ROM_FN(Sdi);

static struct BurnRomInfo ShinobiRomDesc[] = {
	{ "epr12010.43",   0x10000, 0x7df7f4a2, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12008.26",   0x10000, 0xf5ae64cd, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12011.42",   0x10000, 0x9d46e707, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12009.25",   0x10000, 0x7961d07e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr11264.95",   0x10000, 0x46627e7d, SYS16_ROM_TILES | BRF_GRA },
	{ "epr11265.94",   0x10000, 0x87d0f321, SYS16_ROM_TILES | BRF_GRA },
	{ "epr11266.93",   0x10000, 0xefb4af87, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr11290.10",   0x10000, 0x611f413a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11294.11",   0x10000, 0x5eb00fc1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11291.17",   0x10000, 0x3c0797c0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11295.18",   0x10000, 0x25307ef8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11292.23",   0x10000, 0xc29ac34e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11296.24",   0x10000, 0x04a437f8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11293.29",   0x10000, 0x41f41063, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11297.30",   0x10000, 0xb6e1fd72, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr11267.12",   0x08000, 0xdd50b745, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "7751.bin",      0x00400, 0x6a9534fc, SYS16_ROM_7751PROG | BRF_ESS | BRF_PRG },
	
	{ "epr11268.1",    0x08000, 0x6d7966da, SYS16_ROM_7751DATA | BRF_SND },
};


STD_ROM_PICK(Shinobi);
STD_ROM_FN(Shinobi);

static struct BurnRomInfo Shinobi1RomDesc[] = {
	{ "epr11262.42",   0x10000, 0xd4b8df12, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11260.27",   0x10000, 0x2835c95d, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11263.43",   0x10000, 0xa2a620bd, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr11261.25",   0x10000, 0xa3ceda52, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr11264.95",   0x10000, 0x46627e7d, SYS16_ROM_TILES | BRF_GRA },
	{ "epr11265.94",   0x10000, 0x87d0f321, SYS16_ROM_TILES | BRF_GRA },
	{ "epr11266.93",   0x10000, 0xefb4af87, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr11290.10",   0x10000, 0x611f413a, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11294.11",   0x10000, 0x5eb00fc1, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11291.17",   0x10000, 0x3c0797c0, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11295.18",   0x10000, 0x25307ef8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11292.23",   0x10000, 0xc29ac34e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11296.24",   0x10000, 0x04a437f8, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11293.29",   0x10000, 0x41f41063, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr11297.30",   0x10000, 0xb6e1fd72, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr11267.12",   0x08000, 0xdd50b745, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "7751.bin",      0x00400, 0x6a9534fc, SYS16_ROM_7751PROG | BRF_ESS | BRF_PRG },
	
	{ "epr11268.1",    0x08000, 0x6d7966da, SYS16_ROM_7751DATA | BRF_SND },

	{ "317-0050.key",  0x02000, 0x82c39ced, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Shinobi1);
STD_ROM_FN(Shinobi1);

static struct BurnRomInfo Sjryuko1RomDesc[] = {
	{ "epr12251.43",   0x08000, 0x1af3cd0b, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12249.26",   0x08000, 0x743d467d, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12252.42",   0x08000, 0x7ae309d6, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12250.25",   0x08000, 0x52c40f19, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
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
	
	{ "epr12227.12",   0x08000, 0x5b12409d, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "7751.bin",      0x00400, 0x6a9534fc, SYS16_ROM_7751PROG | BRF_ESS | BRF_PRG },
	
	{ "epr12228.1",    0x08000, 0x6b2e6aef, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr12229.2",    0x08000, 0xb7aa015c, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr12230.4",    0x08000, 0xd0f61fd4, SYS16_ROM_7751DATA | BRF_SND },
	{ "epr12231.5",    0x08000, 0x780bdc57, SYS16_ROM_7751DATA | BRF_SND },
};


STD_ROM_PICK(Sjryuko1);
STD_ROM_FN(Sjryuko1);

static struct BurnRomInfo TetrisRomDesc[] = {
	{ "epr12201.rom",  0x08000, 0x338e9b51, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12200.rom",  0x08000, 0xfb058779, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "epr12202.rom",  0x10000, 0x2f7da741, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12203.rom",  0x10000, 0xa6e58ec5, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12204.rom",  0x10000, 0x0ae98e23, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr12169.b1",   0x08000, 0xdacc6165, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12170.b5",   0x08000, 0x87354e42, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12205.rom",  0x08000, 0x6695dc99, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "317-0093.key",  0x02000, 0xe0064442, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Tetris);
STD_ROM_FN(Tetris);

static struct BurnRomInfo Tetris3RomDesc[] = {
	{ "epr12201a.43",  0x08000, 0x9250e5cf, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12200a.26",  0x08000, 0x85d4b0ff, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "epr12202.rom",  0x10000, 0x2f7da741, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12203.rom",  0x10000, 0xa6e58ec5, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12204.rom",  0x10000, 0x0ae98e23, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr12169.b1",   0x08000, 0xdacc6165, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12170.b5",   0x08000, 0x87354e42, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12205.rom",  0x08000, 0x6695dc99, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "317-0093a.key", 0x02000, 0x7ca4a8ee, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Tetris3);
STD_ROM_FN(Tetris3);

static struct BurnRomInfo Timesca1RomDesc[] = {
	{ "epr10540a.43",  0x08000, 0x76848b0b, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10537a.26",  0x08000, 0x4ddc434a, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10541.42",   0x08000, 0xcc6d945e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10538.25",   0x08000, 0x68379473, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10542.41",   0x08000, 0x10217dfa, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr10539.24",   0x08000, 0x10943b2e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },

	{ "epr10543.95",   0x08000, 0x07dccc37, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10544.94",   0x08000, 0x84fb9a3a, SYS16_ROM_TILES | BRF_GRA },
	{ "epr10545.93",   0x08000, 0xc8694bc0, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr10548.10",   0x08000, 0xaa150735, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10552.11",   0x08000, 0x6fcbb9f7, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10549.17",   0x08000, 0x2f59f067, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10553.18",   0x08000, 0x8a220a9f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10550.23",   0x08000, 0xf05069ff, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10554.24",   0x08000, 0xdc64f809, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10551.29",   0x08000, 0x435d811f, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr10555.30",   0x08000, 0x2143c471, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr10546.12",   0x08000, 0x1ebee5cc, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "7751.bin",      0x00400, 0x6a9534fc, SYS16_ROM_7751PROG | BRF_ESS | BRF_PRG },
	
	{ "epr10547.1",    0x08000, 0xd24ffc4b, SYS16_ROM_7751DATA | BRF_SND },
};


STD_ROM_PICK(Timesca1);
STD_ROM_FN(Timesca1);

static struct BurnRomInfo Wb31RomDesc[] = {
	{ "epr12084.bin",  0x10000, 0xb6deb654, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12082.bin",  0x10000, 0x38dc5b15, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12085.bin",  0x10000, 0x0962098b, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	{ "epr12083.bin",  0x10000, 0x3d631a8e, SYS16_ROM_PROG | BRF_ESS | BRF_PRG },
	
	{ "epr12086.bin",  0x10000, 0x45b949df, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12087.bin",  0x10000, 0x6f0396b7, SYS16_ROM_TILES | BRF_GRA },
	{ "epr12088.bin",  0x10000, 0xba8c0749, SYS16_ROM_TILES | BRF_GRA },
	
	{ "epr12090.b1",   0x10000, 0xaeeecfca, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12094.b5",   0x10000, 0x615e4927, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12091.b2",   0x10000, 0x8409a243, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12095.b6",   0x10000, 0xe774ec2c, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12092.b3",   0x10000, 0x5c2f0d90, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12096.b7",   0x10000, 0x0cd59d6e, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12093.b4",   0x10000, 0x4891e7bb, SYS16_ROM_SPRITES | BRF_GRA },
	{ "epr12097.b8",   0x10000, 0xe645902c, SYS16_ROM_SPRITES | BRF_GRA },

	{ "epr12089.bin",  0x08000, 0x8321eb0b, SYS16_ROM_Z80PROG | BRF_ESS | BRF_PRG },
	
	{ "317-0084.key",  0x02000, 0x2c58dafa, SYS16_ROM_KEY | BRF_ESS | BRF_PRG },
};


STD_ROM_PICK(Wb31);
STD_ROM_FN(Wb31);

/*====================================================
Memory Handlers
====================================================*/

void System16APPI0WritePortA(UINT8 data)
{
	System16SoundLatch = data & 0xff;
}

void System16APPI0WritePortB(UINT8 data)
{
	System16VideoControl = data;
	System16VideoEnable = data & 0x10;
	if (!System16ScreenFlip) System16ScreenFlip = data & 0x80;
}

void System16APPI0WritePortC(UINT8 data)
{
	if (!(data & 0x80)) ZetNmi();
	System16ColScroll = ~data & 0x04;
	System16RowScroll = ~data & 0x02;
}

unsigned short __fastcall System16AReadWord(unsigned int a)
{
	switch (a) {
		case 0xc40000:
		case 0xc40002:
		case 0xc40004:
		case 0xc40006:
		case 0xc41000:
		case 0xc41002:
		case 0xc41004:
		case 0xc41006:
		case 0xc42000:
		case 0xc42002:
		case 0xc42004:
		case 0xc42006: {
			SEK_DEF_READ_WORD(0, a);
		}

		case 0xc60000: {
			return 0;
		}
	}
	
#if 0 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("68000 Read Word -> 0x%06X\n"), a);
#endif

	return 0xffff;
}

unsigned char __fastcall System16AReadByte(unsigned int a)
{
	switch (a) {
		case 0xc40001:
		case 0xc40003: 
		case 0xc40005:
		case 0xc40007: {
			return ppi8255_r(0, a - (0xc40000) >> 1);
		}
		
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
		
		case 0xc60000: {
			return 0;
		}
	}
	
#if 0 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("68000 Read Byte -> 0x%06X\n"), a);
#endif

	return 0xff;
}

void __fastcall System16AWriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0xc40000:
		case 0xc40002:
		case 0xc40004:
		case 0xc40006: {
			SEK_DEF_WRITE_WORD(0, a, d);
			return;
		}
		
		case 0xc60000: {
			return;
		}
	}		

#if 0 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("68000 Write Word -> 0x%06X, 0x%04X\n"), a, d);
#endif
}

void __fastcall System16AWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0xc40001:
		case 0xc40003: 
		case 0xc40005:
		case 0xc40007: {
			ppi8255_w(0, a - (0xc40000) >> 1, d & 0xff);
			return;
		}
	}

#if 0 && defined FBA_DEBUG
	bprintf(PRINT_NORMAL, _T("68000 Write Byte -> 0x%06X, 0x%02X\n"), a, d);
#endif
}

static short MjleagueTrack1X = 0;
static short MjleagueTrack1Y = 0;
static short MjleagueTrack2X = 0;
static short MjleagueTrack2Y = 0;
static short MjleagueBat1 = 0;
static short MjleagueBat2 = 0;

void MjleagueMakeAnalogInputs()
{
	if (System16InputPort3[0]) MjleagueTrack1X -= 0x04;
	if (System16InputPort3[1]) MjleagueTrack1X += 0x04;
	if (MjleagueTrack1X >= 0x100) MjleagueTrack1X = 0;
	if (MjleagueTrack1X < 0) MjleagueTrack1X = 0xfc;
	
	if (System16InputPort3[2]) MjleagueTrack1Y -= 0x04;
	if (System16InputPort3[3]) MjleagueTrack1Y += 0x04;
	if (MjleagueTrack1Y >= 0x100) MjleagueTrack1Y = 0;
	if (MjleagueTrack1Y < 0) MjleagueTrack1Y = 0xfc;
	
	if (System16InputPort3[4]) MjleagueTrack2X -= 0x04;
	if (System16InputPort3[5]) MjleagueTrack2X += 0x04;
	if (MjleagueTrack2X >= 0x100) MjleagueTrack2X = 0;
	if (MjleagueTrack2X < 0) MjleagueTrack2X = 0xfc;
	
	if (System16InputPort3[6]) MjleagueTrack2Y -= 0x04;
	if (System16InputPort3[7]) MjleagueTrack2Y += 0x04;
	if (MjleagueTrack2Y >= 0x100) MjleagueTrack2Y = 0;
	if (MjleagueTrack2Y < 0) MjleagueTrack2Y = 0xfc;
	
	MjleagueBat1 = 0x80 + (System16AnalogPort0 >> 4);
	MjleagueBat2 = 0x80 + (System16AnalogPort1 >> 4);
}

unsigned char __fastcall MjleagueReadByte(unsigned int a)
{
	switch (a) {
		case 0xc41001: {
			UINT8 buttons = 0x3f - System16Input[0];
			UINT8 analog1 = (System16VideoControl & 4) ? MjleagueTrack1Y : MjleagueTrack1X;
			UINT8 analog2 = (System16VideoControl & 4) ? MjleagueTrack2Y : MjleagueTrack2X;
			
			buttons |= (analog1 & 0x80) >> 1;
			buttons |= (analog2 & 0x80);
			
			return buttons;
		}
		
		case 0xc41003: {
			UINT8 analog = (System16VideoControl & 4) ? MjleagueTrack1Y : MjleagueTrack1X;
			return ((0xff - System16Input[1]) & 0x80) | (analog & 0x7f);
		}
		
		case 0xc41005: {
			if (System16VideoControl & 4) {
				return (MjleagueBat1 >> 4) | (MjleagueBat2 & 0xf0);
			} else {
				static UINT8 last_buttons1 = 0;
				static UINT8 last_buttons2 = 0;
				UINT8 buttons1 = 0xff - System16Input[1];
				UINT8 buttons2 = 0xff - System16Input[2];

				if (!(buttons1 & 0x01))
					last_buttons1 = 0;
				else if (!(buttons1 & 0x02))
					last_buttons1 = 1;
				else if (!(buttons1 & 0x04))
					last_buttons1 = 2;
				else if (!(buttons1 & 0x08))
					last_buttons1 = 3;

				if (!(buttons2 & 0x01))
					last_buttons2 = 0;
				else if (!(buttons2 & 0x02))
					last_buttons2 = 1;
				else if (!(buttons2 & 0x04))
					last_buttons2 = 2;
				else if (!(buttons2 & 0x08))
					last_buttons2 = 3;

				return last_buttons1 | (last_buttons2 << 4);
			}
		}
		
		case 0xc41007: {
			UINT8 analog = (System16VideoControl & 4) ? MjleagueTrack2Y : MjleagueTrack2X;
			return ((0xff - System16Input[2]) & 0x80) | (analog & 0x7f);
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

unsigned char __fastcall QuartetReadByte(unsigned int a)
{
	switch (a) {
		case 0xc41001: {
			return 0xff - System16Input[0];
		}
		
		case 0xc41003: {
			return 0xff - System16Input[1];
		}
		
		case 0xc41005: {
			return 0xff - System16Input[2];
		}
		
		case 0xc41007: {
			return 0xff - System16Input[3];
		}
		
		case 0xc42001: {
			return System16Dip[0];
		}

		case 0xc42003: {
			return System16Dip[1];
		}
		
		case 0xc60000: {
			return 0;
		}
	}
	
	return 0xff;
}

static short SdiTrack1X = 0;
static short SdiTrack1Y = 0;
static short SdiTrack2X = 0;
static short SdiTrack2Y = 0;

void SdiMakeAnalogInputs()
{
	SdiTrack1X += (System16AnalogPort0 >> 8) & 0xff;
	SdiTrack1Y -= (System16AnalogPort1 >> 8) & 0xff;
	
	SdiTrack2X += (System16AnalogPort2 >> 8) & 0xff;
	SdiTrack2Y -= (System16AnalogPort3 >> 8) & 0xff;
}

unsigned char __fastcall SdiReadByte(unsigned int a)
{
	switch (a) {
		case 0xc41001: {
			return 0xff - System16Input[0];
		}
		
		case 0xc41003: {
			return (System16VideoControl & 4) ? SdiTrack1Y : SdiTrack1X;
		}
		
		case 0xc41005: {
			return 0xff - System16Input[1];
		}
		
		case 0xc41007: {
			return (System16VideoControl & 4) ? SdiTrack2Y : SdiTrack2X;
		}
		
		case 0xc42001: {
			return System16Dip[0];
		}

		case 0xc42003: {
			return System16Dip[1];
		}
		
		case 0xc60000: {
			return 0xff;
		}
	}

	return 0xff;
}

static UINT8 MahjongInputNum;

unsigned short __fastcall Sjryuko1ReadWord(unsigned int a)
{
	SEK_DEF_READ_WORD(0, a);
	
	return 0xffff;
}

unsigned char __fastcall Sjryuko1ReadByte(unsigned int a)
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

void __fastcall Sjryuko1WriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0xc40001: {
			System16SoundLatch = d & 0xff;
			ZetNmi();
			return;
		}
		
		case 0xc40003: {
			if ((System16VideoControl ^ d) & 0xc) {
				if (((System16VideoControl ^ d) & 4) && (d & 4)) MahjongInputNum = (MahjongInputNum + 1) % 6;
			}
			System16VideoControl = d;
			System16VideoEnable = d & 0x10;
			return;
		}
	}
}

/*====================================================
Driver Inits
====================================================*/

static int AfighterInit()
{
	FD1089_Decrypt = fd1089_decrypt_0018;
	
	int nRet = System16Init();
	
	return nRet;
}

static int Alexkid1Init()
{
	FD1089_Decrypt = fd1089_decrypt_alexkidd;
	
	int nRet = System16Init();
	
	return nRet;
}

static int Aliensy1Init()
{
	FD1089_Decrypt = fd1089_decrypt_0033;
	
	int nRet = System16Init();
	
	if (!nRet) {
		// Handle different sprite rom layout
		unsigned char *pTemp = (unsigned char*)malloc(System16SpriteRomSize);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, System16SpriteRomSize);
			memcpy(System16Sprites + 0x00000, pTemp + 0x00000, 0x10000);
			memcpy(System16Sprites + 0x10000, pTemp + 0x20000, 0x10000);
			memcpy(System16Sprites + 0x20000, pTemp + 0x40000, 0x10000);
			memcpy(System16Sprites + 0x30000, pTemp + 0x60000, 0x10000);
			memcpy(System16Sprites + 0x40000, pTemp + 0x10000, 0x10000);
			memcpy(System16Sprites + 0x50000, pTemp + 0x30000, 0x10000);
			memcpy(System16Sprites + 0x60000, pTemp + 0x50000, 0x10000);
			memcpy(System16Sprites + 0x70000, pTemp + 0x70000, 0x10000);
		} else {
			nRet = 1;
		}
		free(pTemp);		
	}
	
	return nRet;
}

void Bodyslam_Sim8751()
{
	UINT8 flag = ((System16Ram[0x200 + 1] << 8) | System16Ram[0x200 + 0]) >> 8;
	UINT8 tick = ((System16Ram[0x200 + 1] << 8) | System16Ram[0x200 + 0]) & 0xff;
	UINT8 sec  = ((System16Ram[0x202 + 1] << 8) | System16Ram[0x202 + 0]) >> 8;
	UINT8 min  = ((System16Ram[0x202 + 1] << 8) | System16Ram[0x202 + 0]) & 0xff;

	/* out of time? set the flag */
	if (tick == 0 && sec == 0 && min == 0)
		flag = 1;
	else
	{
		if (tick != 0)
			tick--;
		else
		{
			/* the game counts 64 ticks per second */
			tick = 0x40;

			/* seconds are counted in BCD */
			if (sec != 0)
				sec = (sec & 0xf) ? sec - 1 : (sec - 0x10) + 9;
			else
			{
				sec = 0x59;

				/* minutes are counted normally */
				if (min != 0)
					min--;
				else
				{
					flag = 1;
					tick = sec = min = 0;
				}
			}
		}
	}
	
	*((unsigned short*)(System16Ram + 0x200)) = (flag << 8) + tick;
	*((unsigned short*)(System16Ram + 0x202)) = (sec << 8) + min;
}

static int BodyslamInit()
{
	Simulate8751 = Bodyslam_Sim8751;

	int nRet = System16Init();
	
	return nRet;
}

static int MjleagueInit()
{
	System16MakeAnalogInputsDo = MjleagueMakeAnalogInputs;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekSetReadByteHandler(0, MjleagueReadByte);
		SekClose();
	}
	
	return nRet;
}

static int MjleagueExit()
{
	MjleagueTrack1X = 0;
	MjleagueTrack1Y = 0;
	MjleagueTrack2X = 0;
	MjleagueTrack2Y = 0;
	MjleagueBat1 = 0;
	MjleagueBat2 = 0;
	
	return System16Exit();
}

static int MjleagueScan(int nAction,int *pnMin)
{
	if (pnMin != NULL) {					// Return minimum compatible version
		*pnMin =  0x029660;
	}
	
	if (nAction & ACB_DRIVER_DATA) {
		SCAN_VAR(MjleagueTrack1X);
		SCAN_VAR(MjleagueTrack1Y);
		SCAN_VAR(MjleagueTrack2X);
		SCAN_VAR(MjleagueTrack2Y);
		SCAN_VAR(MjleagueBat1);
		SCAN_VAR(MjleagueBat2);
	}
	
	return System16Scan(nAction, pnMin);;
}

void Quartet_Sim8751()
{
	// X-Scroll Values
	*((unsigned short*)(System16TextRam + 0xff8)) = ((System16Ram[0x0d14 + 1] << 8) | System16Ram[0x0d14 + 0]);
	*((unsigned short*)(System16TextRam + 0xffa)) = ((System16Ram[0x0d18 + 1] << 8) | System16Ram[0x0d18 + 0]);
	
	// Page Values
	*((unsigned short*)(System16TextRam + 0xe9e)) = ((System16Ram[0x0d1c + 1] << 8) | System16Ram[0x0d1c + 0]);
	*((unsigned short*)(System16TextRam + 0xe9c)) = ((System16Ram[0x0d1e + 1] << 8) | System16Ram[0x0d1e + 0]);
}

static int QuartetInit()
{
	Simulate8751 = Quartet_Sim8751;

	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekSetReadByteHandler(0, QuartetReadByte);
		SekClose();
	}
	
	return nRet;
}

static int SdiInit()
{
	FD1089_Decrypt = fd1089_decrypt_0027;
	
	System16MakeAnalogInputsDo = SdiMakeAnalogInputs;
	
	// Start off with some sprite rom and let the load routine add on the rest
	System16SpriteRomSize = 0x70000 - 0x60000;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekSetReadByteHandler(0, SdiReadByte);
		SekClose();
		
		// Handle different sprite rom layout
		unsigned char *pTemp = (unsigned char*)malloc(System16SpriteRomSize);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, System16SpriteRomSize);
			memcpy(System16Sprites + 0x00000, pTemp + 0x00000, 0x10000);
			memcpy(System16Sprites + 0x10000, pTemp + 0x20000, 0x10000);
			memcpy(System16Sprites + 0x20000, pTemp + 0x40000, 0x10000);
			memcpy(System16Sprites + 0x40000, pTemp + 0x10000, 0x10000);
			memcpy(System16Sprites + 0x50000, pTemp + 0x30000, 0x10000);
			memcpy(System16Sprites + 0x60000, pTemp + 0x50000, 0x10000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}
	
	return nRet;
}

static int SdiExit()
{
	SdiTrack1X = 0;
	SdiTrack1Y = 0;
	SdiTrack2X = 0;
	SdiTrack2Y = 0;

	return System16Exit();
}

static int SdiScan(int nAction,int *pnMin)
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

static int ShinobiInit()
{
	int nRet = System16Init();
	
	if (!nRet) {
		// Handle different sprite rom layout
		unsigned char *pTemp = (unsigned char*)malloc(System16SpriteRomSize);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, System16SpriteRomSize);
			memcpy(System16Sprites + 0x00000, pTemp + 0x00000, 0x10000);
			memcpy(System16Sprites + 0x10000, pTemp + 0x20000, 0x10000);
			memcpy(System16Sprites + 0x20000, pTemp + 0x40000, 0x10000);
			memcpy(System16Sprites + 0x30000, pTemp + 0x60000, 0x10000);
			memcpy(System16Sprites + 0x40000, pTemp + 0x10000, 0x10000);
			memcpy(System16Sprites + 0x50000, pTemp + 0x30000, 0x10000);
			memcpy(System16Sprites + 0x60000, pTemp + 0x50000, 0x10000);
			memcpy(System16Sprites + 0x70000, pTemp + 0x70000, 0x10000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}
	
	return nRet;
}

static int Sjryuko1Init()
{
	FD1089_Decrypt = fd1089_decrypt_5021;
	
	int nRet = System16Init();
	
	if (!nRet) {
		SekOpen(0);
		SekSetWriteByteHandler(0, Sjryuko1WriteByte);
		SekSetReadByteHandler(0, Sjryuko1ReadByte);
		SekSetReadWordHandler(0, Sjryuko1ReadWord);
		SekClose();
		
		// Handle different sprite rom layout
		unsigned char *pTemp = (unsigned char*)malloc(System16SpriteRomSize);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, System16SpriteRomSize);
			memcpy(System16Sprites + 0x00000, pTemp + 0x00000, 0x10000);
			memcpy(System16Sprites + 0x10000, pTemp + 0x20000, 0x10000);
			memcpy(System16Sprites + 0x20000, pTemp + 0x40000, 0x10000);
			memcpy(System16Sprites + 0x30000, pTemp + 0x60000, 0x10000);
			memcpy(System16Sprites + 0x40000, pTemp + 0x10000, 0x10000);
			memcpy(System16Sprites + 0x50000, pTemp + 0x30000, 0x10000);
			memcpy(System16Sprites + 0x60000, pTemp + 0x50000, 0x10000);
			memcpy(System16Sprites + 0x70000, pTemp + 0x70000, 0x10000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}
	
	return nRet;
}

static int Sjryuko1Exit()
{
	MahjongInputNum = 0;
	
	return System16Exit();
}

static int Sjryuko1Scan(int nAction,int *pnMin)
{
	if (pnMin != NULL) {					// Return minimum compatible version
		*pnMin =  0x029660;
	}
	
	if (nAction & ACB_DRIVER_DATA) {
		SCAN_VAR(MahjongInputNum);
	}
	
	return System16Scan(nAction, pnMin);;
}

static int Timesca1Init()
{
	FD1089_Decrypt = fd1089_decrypt_0024;
	
	int nRet = System16Init();
	
	return nRet;
}

static int Wb31Init()
{
	int nRet = System16Init();
	
	if (!nRet) {
		// Handle different sprite rom layout
		unsigned char *pTemp = (unsigned char*)malloc(System16SpriteRomSize);
		if (pTemp) {
			memcpy(pTemp, System16Sprites, System16SpriteRomSize);
			memcpy(System16Sprites + 0x00000, pTemp + 0x00000, 0x10000);
			memcpy(System16Sprites + 0x10000, pTemp + 0x20000, 0x10000);
			memcpy(System16Sprites + 0x20000, pTemp + 0x40000, 0x10000);
			memcpy(System16Sprites + 0x30000, pTemp + 0x60000, 0x10000);
			memcpy(System16Sprites + 0x40000, pTemp + 0x10000, 0x10000);
			memcpy(System16Sprites + 0x50000, pTemp + 0x30000, 0x10000);
			memcpy(System16Sprites + 0x60000, pTemp + 0x50000, 0x10000);
			memcpy(System16Sprites + 0x70000, pTemp + 0x70000, 0x10000);
		} else {
			nRet = 1;
		}
		free(pTemp);
	}
	
	return nRet;
}

/*====================================================
Driver defs
====================================================*/

struct BurnDriver BurnDrvAFighter = {
	"afighter", NULL, NULL, "1986",
	"Action Fighter, FD1089A 317-0018\0", NULL, "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_SEGA_SYSTEM16A | HARDWARE_SEGA_FD1089A_ENC,
	NULL, AfighterRomInfo, AfighterRomName, System16aInputInfo, AfighterDIPInfo,
	AfighterInit, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 224, 320, 3, 4
};

struct BurnDriver BurnDrvAlexkidd = {
	"alexkidd", NULL, NULL, "1986",
	"Alex Kidd: The Lost Stars (set 2, unprotected)\0", "Incomplete Sound", "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16A,
	NULL, AlexkiddRomInfo, AlexkiddRomName, System16aInputInfo, AlexkiddDIPInfo,
	System16Init, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvAlexkid1 = {
	"alexkid1", "alexkidd", NULL, "1986",
	"Alex Kidd: The Lost Stars (set 1, FD1089A 317-unknown)\0", "Incomplete Sound", "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16A | HARDWARE_SEGA_FD1089A_ENC,
	NULL, Alexkid1RomInfo, Alexkid1RomName, System16aInputInfo, AlexkiddDIPInfo,
	Alexkid1Init, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvAliensy1 = {
	"aliensy1", "aliensyn", NULL, "1987",
	"Alien Syndrome (set 1, System 16A, FD1089A 317-0033)\0", "Incomplete Sound", "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16A | HARDWARE_SEGA_FD1089A_ENC,
	NULL, Aliensy1RomInfo, Aliensy1RomName, System16afire1InputInfo, AliensynDIPInfo,
	Aliensy1Init, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvAliensy2 = {
	"aliensy2", "aliensyn", NULL, "1987",
	"Alien Syndrome (set 2, System 16A, FD1089A 317-0033)\0", "Incomplete Sound", "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16A | HARDWARE_SEGA_FD1089A_ENC,
	NULL, Aliensy2RomInfo, Aliensy2RomName, System16afire1InputInfo, AliensynDIPInfo,
	Aliensy1Init, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvBodyslam = {
	"bodyslam", NULL, NULL, "1986",
	"Body Slam (8751 317-0015)\0", NULL, "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16A,
	NULL, BodyslamRomInfo, BodyslamRomName, System16aInputInfo, BodyslamDIPInfo,
	BodyslamInit, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvDumpmtmt = {
	"dumpmtmt", "bodyslam", NULL, "1986",
	"Dump Matsumoto (Japan, 8751 317-unknown)\0", NULL, "Sega", "System 16A",
	 L"Dump Matsumoto (Japan, 8751 317-unknown)\0\u30C0\u30F3\u30D7\u677E\u672C\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16A,
	NULL, DumpmtmtRomInfo, DumpmtmtRomName, System16aInputInfo, BodyslamDIPInfo,
	BodyslamInit, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvFantzone = {
	"fantzone", NULL, NULL, "1986",
	"Fantasy Zone (set 2, unprotected)\0", NULL, "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16A,
	NULL, FantzoneRomInfo, FantzoneRomName, System16aInputInfo, FantzoneDIPInfo,
	System16Init, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvFantzon1 = {
	"fantzon1", "fantzone", NULL, "1986",
	"Fantasy Zone (set 1, unprotected)\0", NULL, "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16A,
	NULL, Fantzon1RomInfo, Fantzon1RomName, System16aInputInfo, FantzoneDIPInfo,
	System16Init, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvMjleague = {
	"mjleague", NULL, NULL, "1985",
	"Major League\0", "Incomplete Sound", "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_SEGA_SYSTEM16A,
	NULL, MjleagueRomInfo, MjleagueRomName, MjleagueInputInfo, MjleagueDIPInfo,
	MjleagueInit, MjleagueExit, System16AFrame, NULL, MjleagueScan,
	NULL, 224, 320, 3, 4
};

struct BurnDriver BurnDrvQuartet = {
	"quartet", NULL, NULL, "1986",
	"Quartet (Rev A, 8751 317-unknown)\0", "Incomplete Sound", "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 4, HARDWARE_SEGA_SYSTEM16A,
	NULL, QuartetRomInfo, QuartetRomName, QuartetInputInfo, QuartetDIPInfo,
	QuartetInit, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvQuartet1 = {
	"quartet1", "quartet", NULL, "1986",
	"Quartet (8751 315-5194)\0", "Incomplete Sound", "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 4, HARDWARE_SEGA_SYSTEM16A,
	NULL, Quartet1RomInfo, Quartet1RomName, QuartetInputInfo, QuartetDIPInfo,
	QuartetInit, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvQuart21 = {
	"quart21", "quartet", NULL, "1986",
	"Quartet 2 (8751 317-0010)\0", "Incomplete Sound", "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16A,
	NULL, Quart21RomInfo, Quart21RomName, System16aInputInfo, Quart2DIPInfo,
	QuartetInit, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvQuart2 = {
	"quart2", "quartet", NULL, "1986",
	"Quartet 2 (unprotected)\0", "Incomplete Sound", "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16A,
	NULL, Quart2RomInfo, Quart2RomName, System16aInputInfo, Quart2DIPInfo,
	System16Init, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvSdi = {
	"sdi", NULL, NULL, "1987",
	"SDI - Strategic Defense Initiative (Europe, System 16A, FD1089B 317-0027)\0", NULL, "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16A | HARDWARE_SEGA_FD1089B_ENC,
	NULL, SdiRomInfo, SdiRomName, SdiInputInfo, SdiDIPInfo,
	SdiInit, SdiExit, System16AFrame, NULL, SdiScan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvShinobi = {
	"shinobi", NULL, NULL, "1987",
	"Shinobi (set 5, System 16A, unprotected)\0", "Incomplete Sound", "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16A,
	NULL, ShinobiRomInfo, ShinobiRomName, System16afire3InputInfo, ShinobiDIPInfo,
	ShinobiInit, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvShinobi1 = {
	"shinobi1", "shinobi", NULL, "1987",
	"Shinobi (set 1, System 16A, FD1094 317-0050)\0", "Incomplete Sound", "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16A | HARDWARE_SEGA_FD1094_ENC,
	NULL, Shinobi1RomInfo, Shinobi1RomName, System16afire3InputInfo, ShinobiDIPInfo,
	ShinobiInit, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvSjryuko1 = {
	"sjryuko1", "sjryuko", NULL, "1987",
	"Sukeban Jansi Ryuko (set 1, System 16A, FD1089B 317-5021)\0", "Incomplete Sound", "White Board", "System 16A",
	L"Sukeban Jansi Ryuko (set 1, System 16A, FD1089B 317-5021)\0\u30B9\u30B1\u30D0\u30F3\u96C0\u58EB \u7ADC\u5B50\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16A | HARDWARE_SEGA_FD1089B_ENC,
	NULL, Sjryuko1RomInfo, Sjryuko1RomName, Sjryuko1InputInfo, Sjryuko1DIPInfo,
	Sjryuko1Init, Sjryuko1Exit, System16AFrame, NULL, Sjryuko1Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvTetris = {
	"tetris", NULL, NULL, "1988",
	"Tetris (set 4, Japan, System 16A, FD1094 317-0093)\0", NULL, "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_SYSTEM16A | HARDWARE_SEGA_FD1094_ENC,
	NULL, TetrisRomInfo, TetrisRomName, System16afire1InputInfo, TetrisDIPInfo,
	System16Init, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvTetris3 = {
	"tetris3", "tetris", NULL, "1988",
	"Tetris (set 3, Japan, System 16A, FD1094 317-0093a)\0", NULL, "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16A | HARDWARE_SEGA_FD1094_ENC,
	NULL, Tetris3RomInfo, Tetris3RomName, System16afire1InputInfo, TetrisDIPInfo,
	System16Init, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvTimesca1 = {
	"timesca1", "timescan", NULL, "1987",
	"Time Scanner (set 1, System 16A, FD1089B 317-0024)\0", "Incomplete Sound", "Sega", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_SEGA_SYSTEM16A | HARDWARE_SEGA_FD1089B_ENC,
	NULL, Timesca1RomInfo, Timesca1RomName, System16aDip3InputInfo, TimescanDIPInfo,
	Timesca1Init, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 224, 320, 3, 4
};

struct BurnDriver BurnDrvWb31 = {
	"wb31", "wb3", NULL, "1988",
	"Wonder Boy III - Monster Lair (set 1, System 16A, FD1094 317-0084)\0", NULL, "Sega / Westone", "System 16A",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_SYSTEM16A | HARDWARE_SEGA_FD1094_ENC,
	NULL, Wb31RomInfo, Wb31RomName, System16aInputInfo, Wb31DIPInfo,
	Wb31Init, System16Exit, System16AFrame, NULL, System16Scan,
	NULL, 320, 224, 4, 3
};
