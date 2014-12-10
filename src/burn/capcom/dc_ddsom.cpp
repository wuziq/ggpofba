#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"},
  {"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start"},
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Attack"     , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Jump"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Select"     , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},
  {"P1 Use"        , BIT_DIGITAL, CpsInp001+7, "p1 fire 4"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Attack"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Jump"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Select"     , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},
  {"P2 Use"        , BIT_DIGITAL, CpsInp000+7, "p2 fire 4"},

  {"P3 Coin"       , BIT_DIGITAL, CpsInp020+6, "p3 coin"},
  {"P3 Start"      , BIT_DIGITAL, CpsInp020+2, "p3 start"},
  {"P3 Up"         , BIT_DIGITAL, CpsInp011+3, "p3 up"},
  {"P3 Down"       , BIT_DIGITAL, CpsInp011+2, "p3 down"},
  {"P3 Left"       , BIT_DIGITAL, CpsInp011+1, "p3 left"},
  {"P3 Right"      , BIT_DIGITAL, CpsInp011+0, "p3 right"},
  {"P3 Attack"     , BIT_DIGITAL, CpsInp011+4, "p3 fire 1"},
  {"P3 Jump"       , BIT_DIGITAL, CpsInp011+5, "p3 fire 2"},
  {"P3 Select"     , BIT_DIGITAL, CpsInp011+6, "p3 fire 3"},
  {"P3 Use"        , BIT_DIGITAL, CpsInp011+7, "p3 fire 4"},

  {"P4 Coin"       , BIT_DIGITAL, CpsInp020+7, "p4 coin"},
  {"P4 Start"      , BIT_DIGITAL, CpsInp020+3, "p4 start"},
  {"P4 Up"         , BIT_DIGITAL, CpsInp010+3, "p4 up"},
  {"P4 Down"       , BIT_DIGITAL, CpsInp010+2, "p4 down"},
  {"P4 Left"       , BIT_DIGITAL, CpsInp010+1, "p4 left"},
  {"P4 Right"      , BIT_DIGITAL, CpsInp010+0, "p4 right"},
  {"P4 Attack"     , BIT_DIGITAL, CpsInp010+4, "p4 fire 1"},
  {"P4 Jump"       , BIT_DIGITAL, CpsInp010+5, "p4 fire 2"},
  {"P4 Select"     , BIT_DIGITAL, CpsInp010+6, "p4 fire 3"},
  {"P4 Use"        , BIT_DIGITAL, CpsInp010+7, "p4 fire 4"},

  {"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp021+2, "service"},
};

STDINPUTINFO(Drv);

static struct BurnRomInfo DdsomRomDesc[] = {
	{ "dd2e.03e",      0x80000, 0x449361AF, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dd2e.04e",      0x80000, 0x5B7052B6, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.05e",      0x80000, 0x788D5F60, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.06e",      0x80000, 0xE0807E1E, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.07",       0x80000, 0xbb777a02, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.08",       0x80000, 0x30970890, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.09",       0x80000, 0x99e2194d, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.10",       0x80000, 0xe198805e, 1 | BRF_ESS | BRF_PRG },

	{ "dd2.13m",      0x400000, 0xa46b4e6e, 3 | BRF_GRA },			 // 8
	{ "dd2.15m",      0x400000, 0xd5fc50fc, 3 | BRF_GRA },
	{ "dd2.17m",      0x400000, 0x837c0867, 3 | BRF_GRA },
	{ "dd2.19m",      0x400000, 0xbb0ec21c, 3 | BRF_GRA },
	{ "dd2.14m",      0x200000, 0x6d824ce2, 3 | BRF_GRA },
	{ "dd2.16m",      0x200000, 0x79682ae5, 3 | BRF_GRA },
	{ "dd2.18m",      0x200000, 0xacddd149, 3 | BRF_GRA },
	{ "dd2.20m",      0x200000, 0x117fb0c0, 3 | BRF_GRA },

	{ "dd2.01",       0x020000, 0x99d657e5, 4 | BRF_ESS | BRF_PRG }, // 16
	{ "dd2.02",       0x020000, 0x117a3824, 4 | BRF_ESS | BRF_PRG },

	{ "dd2.11m",      0x200000, 0x98d0c325, 5 | BRF_SND },
	{ "dd2.12m",      0x200000, 0x5ea2e7fa, 5 | BRF_SND },
};


STD_ROM_PICK(Ddsom) STD_ROM_FN(Ddsom)

static struct BurnRomInfo Ddsomr1RomDesc[] = {
	{ "dd2e.03d",      0x80000, 0x6c084ab5, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dd2e.04d",      0x80000, 0x9b94a947, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.05d",      0x80000, 0x5d6a63c6, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.06d",      0x80000, 0x31bde8ee, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.07",       0x80000, 0xbb777a02, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.08",       0x80000, 0x30970890, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.09",       0x80000, 0x99e2194d, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.10",       0x80000, 0xe198805e, 1 | BRF_ESS | BRF_PRG },

	{ "dd2.13m",      0x400000, 0xa46b4e6e, 3 | BRF_GRA },			 // 8
	{ "dd2.15m",      0x400000, 0xd5fc50fc, 3 | BRF_GRA },
	{ "dd2.17m",      0x400000, 0x837c0867, 3 | BRF_GRA },
	{ "dd2.19m",      0x400000, 0xbb0ec21c, 3 | BRF_GRA },
	{ "dd2.14m",      0x200000, 0x6d824ce2, 3 | BRF_GRA },
	{ "dd2.16m",      0x200000, 0x79682ae5, 3 | BRF_GRA },
	{ "dd2.18m",      0x200000, 0xacddd149, 3 | BRF_GRA },
	{ "dd2.20m",      0x200000, 0x117fb0c0, 3 | BRF_GRA },

	{ "dd2.01",       0x020000, 0x99d657e5, 4 | BRF_ESS | BRF_PRG }, // 16
	{ "dd2.02",       0x020000, 0x117a3824, 4 | BRF_ESS | BRF_PRG },

	{ "dd2.11m",      0x200000, 0x98d0c325, 5 | BRF_SND },
	{ "dd2.12m",      0x200000, 0x5ea2e7fa, 5 | BRF_SND },
};


STD_ROM_PICK(Ddsomr1) STD_ROM_FN(Ddsomr1)

static struct BurnRomInfo Ddsomr2RomDesc[] = {
	{ "dd2e.03b",      0x80000, 0xcd2deb66, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dd2e.04b",      0x80000, 0xbfee43cc, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.05b",      0x80000, 0x049ab19d, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.06b",      0x80000, 0x3994fb8b, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.07",       0x80000, 0xbb777a02, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.08",       0x80000, 0x30970890, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.09",       0x80000, 0x99e2194d, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.10",       0x80000, 0xe198805e, 1 | BRF_ESS | BRF_PRG },

	{ "dd2.13m",      0x400000, 0xa46b4e6e, 3 | BRF_GRA },			 // 8
	{ "dd2.15m",      0x400000, 0xd5fc50fc, 3 | BRF_GRA },
	{ "dd2.17m",      0x400000, 0x837c0867, 3 | BRF_GRA },
	{ "dd2.19m",      0x400000, 0xbb0ec21c, 3 | BRF_GRA },
	{ "dd2.14m",      0x200000, 0x6d824ce2, 3 | BRF_GRA },
	{ "dd2.16m",      0x200000, 0x79682ae5, 3 | BRF_GRA },
	{ "dd2.18m",      0x200000, 0xacddd149, 3 | BRF_GRA },
	{ "dd2.20m",      0x200000, 0x117fb0c0, 3 | BRF_GRA },

	{ "dd2.01",       0x020000, 0x99d657e5, 4 | BRF_ESS | BRF_PRG }, // 16
	{ "dd2.02",       0x020000, 0x117a3824, 4 | BRF_ESS | BRF_PRG },

	{ "dd2.11m",      0x200000, 0x98d0c325, 5 | BRF_SND },
	{ "dd2.12m",      0x200000, 0x5ea2e7fa, 5 | BRF_SND },
};


STD_ROM_PICK(Ddsomr2) STD_ROM_FN(Ddsomr2)

static struct BurnRomInfo Ddsomr3RomDesc[] = {
	{ "dd2e.03a",      0x80000, 0x6de67678, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dd2e.04a",      0x80000, 0x0e45739a, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.05a",      0x80000, 0x3dce8025, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.06a",      0x80000, 0x51bafbef, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.07",       0x80000, 0xbb777a02, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.08",       0x80000, 0x30970890, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.09",       0x80000, 0x99e2194d, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.10",       0x80000, 0xe198805e, 1 | BRF_ESS | BRF_PRG },

	{ "dd2.13m",      0x400000, 0xa46b4e6e, 3 | BRF_GRA },			 // 8
	{ "dd2.15m",      0x400000, 0xd5fc50fc, 3 | BRF_GRA },
	{ "dd2.17m",      0x400000, 0x837c0867, 3 | BRF_GRA },
	{ "dd2.19m",      0x400000, 0xbb0ec21c, 3 | BRF_GRA },
	{ "dd2.14m",      0x200000, 0x6d824ce2, 3 | BRF_GRA },
	{ "dd2.16m",      0x200000, 0x79682ae5, 3 | BRF_GRA },
	{ "dd2.18m",      0x200000, 0xacddd149, 3 | BRF_GRA },
	{ "dd2.20m",      0x200000, 0x117fb0c0, 3 | BRF_GRA },

	{ "dd2.01",       0x020000, 0x99d657e5, 4 | BRF_ESS | BRF_PRG }, // 16
	{ "dd2.02",       0x020000, 0x117a3824, 4 | BRF_ESS | BRF_PRG },

	{ "dd2.11m",      0x200000, 0x98d0c325, 5 | BRF_SND },
	{ "dd2.12m",      0x200000, 0x5ea2e7fa, 5 | BRF_SND },
};


STD_ROM_PICK(Ddsomr3) STD_ROM_FN(Ddsomr3)

static struct BurnRomInfo DdsomuRomDesc[] = {
	{ "dd2u.03g",      0x80000, 0xfb089b39, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dd2u.04g",      0x80000, 0xcd432b73, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.05g",       0x80000, 0x5eb1991c, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.06g",       0x80000, 0xc26b5e55, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.07",        0x80000, 0x909a0b8b, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.08",        0x80000, 0xe53c4d01, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.09",        0x80000, 0x5f86279f, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.10",        0x80000, 0xad954c26, 1 | BRF_ESS | BRF_PRG },

	{ "dd2.13m",      0x400000, 0xa46b4e6e, 3 | BRF_GRA },			 // 8
	{ "dd2.15m",      0x400000, 0xd5fc50fc, 3 | BRF_GRA },
	{ "dd2.17m",      0x400000, 0x837c0867, 3 | BRF_GRA },
	{ "dd2.19m",      0x400000, 0xbb0ec21c, 3 | BRF_GRA },
	{ "dd2.14m",      0x200000, 0x6d824ce2, 3 | BRF_GRA },
	{ "dd2.16m",      0x200000, 0x79682ae5, 3 | BRF_GRA },
	{ "dd2.18m",      0x200000, 0xacddd149, 3 | BRF_GRA },
	{ "dd2.20m",      0x200000, 0x117fb0c0, 3 | BRF_GRA },

	{ "dd2.01",       0x020000, 0x99d657e5, 4 | BRF_ESS | BRF_PRG }, // 16
	{ "dd2.02",       0x020000, 0x117a3824, 4 | BRF_ESS | BRF_PRG },

	{ "dd2.11m",      0x200000, 0x98d0c325, 5 | BRF_SND },
	{ "dd2.12m",      0x200000, 0x5ea2e7fa, 5 | BRF_SND },
};


STD_ROM_PICK(Ddsomu) STD_ROM_FN(Ddsomu)

static struct BurnRomInfo Ddsomur1RomDesc[] = {
	{ "dd2u.03d",      0x80000, 0x0f700d84, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dd2u.04d",      0x80000, 0xb99eb254, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.05d",       0x80000, 0xb23061f3, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.06d",       0x80000, 0x8bf1d8ce, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.07",        0x80000, 0x909a0b8b, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.08",        0x80000, 0xe53c4d01, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.09",        0x80000, 0x5f86279f, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.10",        0x80000, 0xad954c26, 1 | BRF_ESS | BRF_PRG },

	{ "dd2.13m",      0x400000, 0xa46b4e6e, 3 | BRF_GRA },			 // 8
	{ "dd2.15m",      0x400000, 0xd5fc50fc, 3 | BRF_GRA },
	{ "dd2.17m",      0x400000, 0x837c0867, 3 | BRF_GRA },
	{ "dd2.19m",      0x400000, 0xbb0ec21c, 3 | BRF_GRA },
	{ "dd2.14m",      0x200000, 0x6d824ce2, 3 | BRF_GRA },
	{ "dd2.16m",      0x200000, 0x79682ae5, 3 | BRF_GRA },
	{ "dd2.18m",      0x200000, 0xacddd149, 3 | BRF_GRA },
	{ "dd2.20m",      0x200000, 0x117fb0c0, 3 | BRF_GRA },

	{ "dd2.01",       0x020000, 0x99d657e5, 4 | BRF_ESS | BRF_PRG }, // 16
	{ "dd2.02",       0x020000, 0x117a3824, 4 | BRF_ESS | BRF_PRG },

	{ "dd2.11m",      0x200000, 0x98d0c325, 5 | BRF_SND },
	{ "dd2.12m",      0x200000, 0x5ea2e7fa, 5 | BRF_SND },
};


STD_ROM_PICK(Ddsomur1) STD_ROM_FN(Ddsomur1)

static struct BurnRomInfo DdsomjRomDesc[] = {
	{ "dd2j.03g",      0x80000, 0xe6c8c985, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dd2j.04g",      0x80000, 0x8386c0bd, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.05g",       0x80000, 0x5eb1991c, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.06g",       0x80000, 0xc26b5e55, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.07",        0x80000, 0x909a0b8b, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.08",        0x80000, 0xe53c4d01, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.09",        0x80000, 0x5f86279f, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.10",        0x80000, 0xad954c26, 1 | BRF_ESS | BRF_PRG },

	{ "dd2.13m",      0x400000, 0xa46b4e6e, 3 | BRF_GRA },			 // 8
	{ "dd2.15m",      0x400000, 0xd5fc50fc, 3 | BRF_GRA },
	{ "dd2.17m",      0x400000, 0x837c0867, 3 | BRF_GRA },
	{ "dd2.19m",      0x400000, 0xbb0ec21c, 3 | BRF_GRA },
	{ "dd2.14m",      0x200000, 0x6d824ce2, 3 | BRF_GRA },
	{ "dd2.16m",      0x200000, 0x79682ae5, 3 | BRF_GRA },
	{ "dd2.18m",      0x200000, 0xacddd149, 3 | BRF_GRA },
	{ "dd2.20m",      0x200000, 0x117fb0c0, 3 | BRF_GRA },

	{ "dd2.01",       0x020000, 0x99d657e5, 4 | BRF_ESS | BRF_PRG }, // 16
	{ "dd2.02",       0x020000, 0x117a3824, 4 | BRF_ESS | BRF_PRG },

	{ "dd2.11m",      0x200000, 0x98d0c325, 5 | BRF_SND },
	{ "dd2.12m",      0x200000, 0x5ea2e7fa, 5 | BRF_SND },
};


STD_ROM_PICK(Ddsomj) STD_ROM_FN(Ddsomj)

static struct BurnRomInfo Ddsomjr1RomDesc[] = {
	{ "dd2j.03b",      0x80000, 0x965d74e5, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dd2j.04b",      0x80000, 0x958eb8f3, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.05b",       0x80000, 0xd38571ca, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.06b",       0x80000, 0x6d5a3bbb, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.07",        0x80000, 0x909a0b8b, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.08",        0x80000, 0xe53c4d01, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.09",        0x80000, 0x5f86279f, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.10",        0x80000, 0xad954c26, 1 | BRF_ESS | BRF_PRG },

	{ "dd2.13m",      0x400000, 0xa46b4e6e, 3 | BRF_GRA },			 // 8
	{ "dd2.15m",      0x400000, 0xd5fc50fc, 3 | BRF_GRA },
	{ "dd2.17m",      0x400000, 0x837c0867, 3 | BRF_GRA },
	{ "dd2.19m",      0x400000, 0xbb0ec21c, 3 | BRF_GRA },
	{ "dd2.14m",      0x200000, 0x6d824ce2, 3 | BRF_GRA },
	{ "dd2.16m",      0x200000, 0x79682ae5, 3 | BRF_GRA },
	{ "dd2.18m",      0x200000, 0xacddd149, 3 | BRF_GRA },
	{ "dd2.20m",      0x200000, 0x117fb0c0, 3 | BRF_GRA },

	{ "dd2.01",       0x020000, 0x99d657e5, 4 | BRF_ESS | BRF_PRG }, // 16
	{ "dd2.02",       0x020000, 0x117a3824, 4 | BRF_ESS | BRF_PRG },

	{ "dd2.11m",      0x200000, 0x98d0c325, 5 | BRF_SND },
	{ "dd2.12m",      0x200000, 0x5ea2e7fa, 5 | BRF_SND },
};


STD_ROM_PICK(Ddsomjr1) STD_ROM_FN(Ddsomjr1)

static struct BurnRomInfo DdsomaRomDesc[] = {
	{ "dd2a.03g",      0x80000, 0x0b4fec22, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dd2a.04g",      0x80000, 0x055b7019, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.05g",       0x80000, 0x5eb1991c, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.06g",       0x80000, 0xc26b5e55, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.07",        0x80000, 0x909a0b8b, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.08",        0x80000, 0xe53c4d01, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.09",        0x80000, 0x5f86279f, 1 | BRF_ESS | BRF_PRG },
	{ "dd2.10",        0x80000, 0xad954c26, 1 | BRF_ESS | BRF_PRG },

	{ "dd2.13m",      0x400000, 0xa46b4e6e, 3 | BRF_GRA },			 // 8
	{ "dd2.15m",      0x400000, 0xd5fc50fc, 3 | BRF_GRA },
	{ "dd2.17m",      0x400000, 0x837c0867, 3 | BRF_GRA },
	{ "dd2.19m",      0x400000, 0xbb0ec21c, 3 | BRF_GRA },
	{ "dd2.14m",      0x200000, 0x6d824ce2, 3 | BRF_GRA },
	{ "dd2.16m",      0x200000, 0x79682ae5, 3 | BRF_GRA },
	{ "dd2.18m",      0x200000, 0xacddd149, 3 | BRF_GRA },
	{ "dd2.20m",      0x200000, 0x117fb0c0, 3 | BRF_GRA },

	{ "dd2.01",       0x020000, 0x99d657e5, 4 | BRF_ESS | BRF_PRG }, // 16
	{ "dd2.02",       0x020000, 0x117a3824, 4 | BRF_ESS | BRF_PRG },

	{ "dd2.11m",      0x200000, 0x98d0c325, 5 | BRF_SND },
	{ "dd2.12m",      0x200000, 0x5ea2e7fa, 5 | BRF_SND },
};


STD_ROM_PICK(Ddsoma) STD_ROM_FN(Ddsoma)

static struct BurnRomInfo DdsombRomDesc[] = {
	{ "dd2b.03a",      0x80000, 0xe8ce7fbb, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "dd2b.04a",      0x80000, 0x6b679664, 1 | BRF_ESS | BRF_PRG },
	{ "dd2b.05a",      0x80000, 0x9b2534eb, 1 | BRF_ESS | BRF_PRG },
	{ "dd2b.06a",      0x80000, 0x3b21ba59, 1 | BRF_ESS | BRF_PRG },
	{ "dd2b.07",       0x80000, 0xfce2558d, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.08",       0x80000, 0x30970890, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.09",       0x80000, 0x99e2194d, 1 | BRF_ESS | BRF_PRG },
	{ "dd2e.10",       0x80000, 0xe198805e, 1 | BRF_ESS | BRF_PRG },

	{ "dd2.13m",      0x400000, 0xa46b4e6e, 3 | BRF_GRA },			 // 8
	{ "dd2.15m",      0x400000, 0xd5fc50fc, 3 | BRF_GRA },
	{ "dd2.17m",      0x400000, 0x837c0867, 3 | BRF_GRA },
	{ "dd2.19m",      0x400000, 0xbb0ec21c, 3 | BRF_GRA },
	{ "dd2.14m",      0x200000, 0x6d824ce2, 3 | BRF_GRA },
	{ "dd2.16m",      0x200000, 0x79682ae5, 3 | BRF_GRA },
	{ "dd2.18m",      0x200000, 0xacddd149, 3 | BRF_GRA },
	{ "dd2.20m",      0x200000, 0x117fb0c0, 3 | BRF_GRA },

	{ "dd2.01",       0x020000, 0x99d657e5, 4 | BRF_ESS | BRF_PRG }, // 16
	{ "dd2.02",       0x020000, 0x117a3824, 4 | BRF_ESS | BRF_PRG },

	{ "dd2.11m",      0x200000, 0x98d0c325, 5 | BRF_SND },
	{ "dd2.12m",      0x200000, 0x5ea2e7fa, 5 | BRF_SND },
};

STD_ROM_PICK(Ddsomb) STD_ROM_FN(Ddsomb)

struct BurnDriver BurnDrvCpsDdsom = {
	"ddsom", NULL, NULL, "1996",
	"Dungeons & Dragons - shadow over mystara (960619 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,4,HARDWARE_CAPCOM_CPS2,
	NULL, DdsomRomInfo, DdsomRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDdsomr1 = {
	"ddsomr1", "ddsom", NULL, "1996",
	"Dungeons & Dragons - shadow over mystara (960223 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, Ddsomr1RomInfo, Ddsomr1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDdsomr2 = {
	"ddsomr2", "ddsom", NULL, "1996",
	"Dungeons & Dragons - shadow over mystara (960209 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, Ddsomr2RomInfo, Ddsomr2RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDdsomr3 = {
	"ddsomr3", "ddsom", NULL, "1996",
	"Dungeons & Dragons - shadow over mystara (960208 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, Ddsomr3RomInfo, Ddsomr3RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDdsomu = {
	"ddsomu", "ddsom", NULL, "1996",
	"Dungeons & Dragons - shadow over mystara (960619 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, DdsomuRomInfo, DdsomuRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDdsomur1 = {
	"ddsomur1", "ddsom", NULL, "1996",
	"Dungeons & Dragons - shadow over mystara (960209 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, Ddsomur1RomInfo, Ddsomur1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDdsomj = {
	"ddsomj", "ddsom", NULL, "1996",
	"Dungeons & Dragons - shadow over mystara (960619 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, DdsomjRomInfo, DdsomjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDdsomjr1 = {
	"ddsomjr1", "ddsom", NULL, "1996",
	"Dungeons & Dragons - shadow over mystara (960206 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, Ddsomjr1RomInfo, Ddsomjr1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDdsoma = {
	"ddsoma", "ddsom", NULL, "1996",
	"Dungeons & Dragons - shadow over mystara (960619 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, DdsomaRomInfo, DdsomaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsDdsomb = {
	"ddsomb", "ddsom", NULL, "1996",
	"Dungeons & Dragons - shadow over mystara (960223 Brazil)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,4,HARDWARE_CAPCOM_CPS2,
	NULL, DdsombRomInfo, DdsombRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
