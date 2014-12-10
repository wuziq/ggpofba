#include "cps.h"

STDINPUTINFOSPEC(Drv, CpsFsi);

static struct BurnRomInfo Sfa2RomDesc[] = {
	{ "sz2u.03",       0x80000, 0x84a09006, 1 | BRF_ESS | BRF_PRG },
	{ "sz2u.04",       0x80000, 0xac46e5ed, 1 | BRF_ESS | BRF_PRG },
	{ "sz2u.05",       0x80000, 0x6c0c79d3, 1 | BRF_ESS | BRF_PRG },
	{ "sz2u.06",       0x80000, 0xc5c8eb63, 1 | BRF_ESS | BRF_PRG },
	{ "sz2u.07",       0x80000, 0x5de01cc5, 1 | BRF_ESS | BRF_PRG },
	{ "sz2u.08",       0x80000, 0xbea11d56, 1 | BRF_ESS | BRF_PRG },

	{ "sz2.13m",      0x400000, 0x4d1f1f22, 3 | BRF_GRA },
	{ "sz2.15m",      0x400000, 0x19cea680, 3 | BRF_GRA },
	{ "sz2.17m",      0x400000, 0xe01b4588, 3 | BRF_GRA },
	{ "sz2.19m",      0x400000, 0x0feeda64, 3 | BRF_GRA },
	{ "sz2.14m",      0x100000, 0x0560c6aa, 3 | BRF_GRA },
	{ "sz2.16m",      0x100000, 0xae940f87, 3 | BRF_GRA },
	{ "sz2.18m",      0x100000, 0x4bc3c8bc, 3 | BRF_GRA },
	{ "sz2.20m",      0x100000, 0x39e674c0, 3 | BRF_GRA },

	{ "sz2.01a",      0x020000, 0x1bc323cf, 4 | BRF_ESS | BRF_PRG },
	{ "sz2.02a",      0x020000, 0xba6a5013, 4 | BRF_ESS | BRF_PRG },

	{ "sz2.11m",      0x200000, 0xaa47a601, 5 | BRF_SND },
	{ "sz2.12m",      0x200000, 0x2237bc53, 5 | BRF_SND },
};


STD_ROM_PICK(Sfa2) STD_ROM_FN(Sfa2)

static struct BurnRomInfo Sfz2jRomDesc[] = {
	{ "sz2j.03a",      0x80000, 0x97461e28, 1 | BRF_ESS | BRF_PRG },
	{ "sz2j.04a",      0x80000, 0xae4851a9, 1 | BRF_ESS | BRF_PRG },
	{ "sz2.05",        0x80000, 0x98e8e992, 1 | BRF_ESS | BRF_PRG },
	{ "sz2.06",        0x80000, 0x5b1d49c0, 1 | BRF_ESS | BRF_PRG },
	{ "sz2j.07a",      0x80000, 0xd910b2a2, 1 | BRF_ESS | BRF_PRG },
	{ "sz2.08",        0x80000, 0x0fe8585d, 1 | BRF_ESS | BRF_PRG },

	{ "sz2.13m",      0x400000, 0x4d1f1f22, 3 | BRF_GRA },
	{ "sz2.15m",      0x400000, 0x19cea680, 3 | BRF_GRA },
	{ "sz2.17m",      0x400000, 0xe01b4588, 3 | BRF_GRA },
	{ "sz2.19m",      0x400000, 0x0feeda64, 3 | BRF_GRA },
	{ "sz2.14m",      0x100000, 0x0560c6aa, 3 | BRF_GRA },
	{ "sz2.16m",      0x100000, 0xae940f87, 3 | BRF_GRA },
	{ "sz2.18m",      0x100000, 0x4bc3c8bc, 3 | BRF_GRA },
	{ "sz2.20m",      0x100000, 0x39e674c0, 3 | BRF_GRA },

	{ "sz2.01a",      0x020000, 0x1bc323cf, 4 | BRF_ESS | BRF_PRG },
	{ "sz2.02a",      0x020000, 0xba6a5013, 4 | BRF_ESS | BRF_PRG },

	{ "sz2.11m",      0x200000, 0xaa47a601, 5 | BRF_SND },
	{ "sz2.12m",      0x200000, 0x2237bc53, 5 | BRF_SND },
};


STD_ROM_PICK(Sfz2j) STD_ROM_FN(Sfz2j)

static struct BurnRomInfo Sfz2aRomDesc[] = {
	{ "sz2a.03a",      0x80000, 0x30d2099f, 1 | BRF_ESS | BRF_PRG },
	{ "sz2a.04a",      0x80000, 0x1cc94db1, 1 | BRF_ESS | BRF_PRG },
	{ "sz2.05",        0x80000, 0x98e8e992, 1 | BRF_ESS | BRF_PRG },
	{ "sz2.06",        0x80000, 0x5b1d49c0, 1 | BRF_ESS | BRF_PRG },
	{ "sz2a.07a",      0x80000, 0x0aed2494, 1 | BRF_ESS | BRF_PRG },
	{ "sz2.08",        0x80000, 0x0fe8585d, 1 | BRF_ESS | BRF_PRG },

	{ "sz2.13m",      0x400000, 0x4d1f1f22, 3 | BRF_GRA },
	{ "sz2.15m",      0x400000, 0x19cea680, 3 | BRF_GRA },
	{ "sz2.17m",      0x400000, 0xe01b4588, 3 | BRF_GRA },
	{ "sz2.19m",      0x400000, 0x0feeda64, 3 | BRF_GRA },
	{ "sz2.14m",      0x100000, 0x0560c6aa, 3 | BRF_GRA },
	{ "sz2.16m",      0x100000, 0xae940f87, 3 | BRF_GRA },
	{ "sz2.18m",      0x100000, 0x4bc3c8bc, 3 | BRF_GRA },
	{ "sz2.20m",      0x100000, 0x39e674c0, 3 | BRF_GRA },

	{ "sz2.01a",      0x020000, 0x1bc323cf, 4 | BRF_ESS | BRF_PRG },
	{ "sz2.02a",      0x020000, 0xba6a5013, 4 | BRF_ESS | BRF_PRG },

	{ "sz2.11m",      0x200000, 0xaa47a601, 5 | BRF_SND },
	{ "sz2.12m",      0x200000, 0x2237bc53, 5 | BRF_SND },
};


STD_ROM_PICK(Sfz2a) STD_ROM_FN(Sfz2a)

static struct BurnRomInfo Sfz2bRomDesc[] = {
	{ "sz2b.03b",      0x80000, 0x1ac12812, 1 | BRF_ESS | BRF_PRG },
	{ "sz2b.04b",      0x80000, 0xe4ffaf68, 1 | BRF_ESS | BRF_PRG },
	{ "sz2b.05a",      0x80000, 0xdd224156, 1 | BRF_ESS | BRF_PRG },
	{ "sz2b.06a",      0x80000, 0xa45a75a6, 1 | BRF_ESS | BRF_PRG },
	{ "sz2b.07a",      0x80000, 0x7d19d5ec, 1 | BRF_ESS | BRF_PRG },
	{ "sz2b.08",       0x80000, 0x92b66e01, 1 | BRF_ESS | BRF_PRG },

	{ "sz2.13m",      0x400000, 0x4d1f1f22, 3 | BRF_GRA },
	{ "sz2.15m",      0x400000, 0x19cea680, 3 | BRF_GRA },
	{ "sz2.17m",      0x400000, 0xe01b4588, 3 | BRF_GRA },
	{ "sz2.19m",      0x400000, 0x0feeda64, 3 | BRF_GRA },
	{ "sz2.14m",      0x100000, 0x0560c6aa, 3 | BRF_GRA },
	{ "sz2.16m",      0x100000, 0xae940f87, 3 | BRF_GRA },
	{ "sz2.18m",      0x100000, 0x4bc3c8bc, 3 | BRF_GRA },
	{ "sz2.20m",      0x100000, 0x39e674c0, 3 | BRF_GRA },

	{ "sz2.01a",      0x020000, 0x1bc323cf, 4 | BRF_ESS | BRF_PRG },
	{ "sz2.02a",      0x020000, 0xba6a5013, 4 | BRF_ESS | BRF_PRG },

	{ "sz2.11m",      0x200000, 0xaa47a601, 5 | BRF_SND },
	{ "sz2.12m",      0x200000, 0x2237bc53, 5 | BRF_SND },
};


STD_ROM_PICK(Sfz2b) STD_ROM_FN(Sfz2b)

static struct BurnRomInfo Sfz2br1RomDesc[] = {
	{ "sz2b.03",       0x80000, 0xe6ce530b, 1 | BRF_ESS | BRF_PRG },
	{ "sz2b.04",       0x80000, 0x1605a0cb, 1 | BRF_ESS | BRF_PRG },
	{ "sz2b.05",       0x80000, 0x4b442a7c, 1 | BRF_ESS | BRF_PRG },
	{ "sz2.06",        0x80000, 0x5b1d49c0, 1 | BRF_ESS | BRF_PRG },
	{ "sz2b.07",       0x80000, 0x947e8ac6, 1 | BRF_ESS | BRF_PRG },
	{ "sz2b.08",       0x80000, 0x92b66e01, 1 | BRF_ESS | BRF_PRG },

	{ "sz2.13m",      0x400000, 0x4d1f1f22, 3 | BRF_GRA },
	{ "sz2.15m",      0x400000, 0x19cea680, 3 | BRF_GRA },
	{ "sz2.17m",      0x400000, 0xe01b4588, 3 | BRF_GRA },
	{ "sz2.19m",      0x400000, 0x0feeda64, 3 | BRF_GRA },
	{ "sz2.14m",      0x100000, 0x0560c6aa, 3 | BRF_GRA },
	{ "sz2.16m",      0x100000, 0xae940f87, 3 | BRF_GRA },
	{ "sz2.18m",      0x100000, 0x4bc3c8bc, 3 | BRF_GRA },
	{ "sz2.20m",      0x100000, 0x39e674c0, 3 | BRF_GRA },

	{ "sz2.01a",      0x020000, 0x1bc323cf, 4 | BRF_ESS | BRF_PRG },
	{ "sz2.02a",      0x020000, 0xba6a5013, 4 | BRF_ESS | BRF_PRG },

	{ "sz2.11m",      0x200000, 0xaa47a601, 5 | BRF_SND },
	{ "sz2.12m",      0x200000, 0x2237bc53, 5 | BRF_SND },
};


STD_ROM_PICK(Sfz2br1) STD_ROM_FN(Sfz2br1)

static struct BurnRomInfo Sfz2hRomDesc[] = {
	{ "sz2h.03" ,      0x80000, 0xbfeddf5b, 1 | BRF_ESS | BRF_PRG },
	{ "sz2h.04",       0x80000, 0xea5009fb, 1 | BRF_ESS | BRF_PRG },
	{ "sz2b.05",       0x80000, 0x4b442a7c, 1 | BRF_ESS | BRF_PRG },
	{ "sz2.06",        0x80000, 0x5b1d49c0, 1 | BRF_ESS | BRF_PRG },
	{ "sz2b.07",       0x80000, 0x947e8ac6, 1 | BRF_ESS | BRF_PRG },
	{ "sz2b.08",       0x80000, 0x92b66e01, 1 | BRF_ESS | BRF_PRG },

	{ "sz2.13m",      0x400000, 0x4d1f1f22, 3 | BRF_GRA },
	{ "sz2.15m",      0x400000, 0x19cea680, 3 | BRF_GRA },
	{ "sz2.17m",      0x400000, 0xe01b4588, 3 | BRF_GRA },
	{ "sz2.19m",      0x400000, 0x0feeda64, 3 | BRF_GRA },
	{ "sz2.14m",      0x100000, 0x0560c6aa, 3 | BRF_GRA },
	{ "sz2.16m",      0x100000, 0xae940f87, 3 | BRF_GRA },
	{ "sz2.18m",      0x100000, 0x4bc3c8bc, 3 | BRF_GRA },
	{ "sz2.20m",      0x100000, 0x39e674c0, 3 | BRF_GRA },

	{ "sz2.01a",      0x020000, 0x1bc323cf, 4 | BRF_ESS | BRF_PRG },
	{ "sz2.02a",      0x020000, 0xba6a5013, 4 | BRF_ESS | BRF_PRG },

	{ "sz2.11m",      0x200000, 0xaa47a601, 5 | BRF_SND },
	{ "sz2.12m",      0x200000, 0x2237bc53, 5 | BRF_SND },
};

STD_ROM_PICK(Sfz2h) STD_ROM_FN(Sfz2h)

static struct BurnRomInfo Sfz2nRomDesc[] = {
	{ "sz2n.03" ,      0x80000, 0x58924741, 1 | BRF_ESS | BRF_PRG },
	{ "sz2n.04",       0x80000, 0x592a17c5, 1 | BRF_ESS | BRF_PRG },
	{ "sz2b.05",       0x80000, 0x4b442a7c, 1 | BRF_ESS | BRF_PRG },
	{ "sz2.06",        0x80000, 0x5b1d49c0, 1 | BRF_ESS | BRF_PRG },
	{ "sz2n.07",       0x80000, 0x8e184246, 1 | BRF_ESS | BRF_PRG },
	{ "sz2.08",        0x80000, 0x0fe8585d, 1 | BRF_ESS | BRF_PRG },

	{ "sz2.13m",      0x400000, 0x4d1f1f22, 3 | BRF_GRA },
	{ "sz2.15m",      0x400000, 0x19cea680, 3 | BRF_GRA },
	{ "sz2.17m",      0x400000, 0xe01b4588, 3 | BRF_GRA },
	{ "sz2.19m",      0x400000, 0x0feeda64, 3 | BRF_GRA },
	{ "sz2.14m",      0x100000, 0x0560c6aa, 3 | BRF_GRA },
	{ "sz2.16m",      0x100000, 0xae940f87, 3 | BRF_GRA },
	{ "sz2.18m",      0x100000, 0x4bc3c8bc, 3 | BRF_GRA },
	{ "sz2.20m",      0x100000, 0x39e674c0, 3 | BRF_GRA },

	{ "sz2.01a",      0x020000, 0x1bc323cf, 4 | BRF_ESS | BRF_PRG },
	{ "sz2.02a",      0x020000, 0xba6a5013, 4 | BRF_ESS | BRF_PRG },

	{ "sz2.11m",      0x200000, 0xaa47a601, 5 | BRF_SND },
	{ "sz2.12m",      0x200000, 0x2237bc53, 5 | BRF_SND },
};

STD_ROM_PICK(Sfz2n) STD_ROM_FN(Sfz2n)

static struct BurnRomInfo Sfz2ajRomDesc[] = {
	{ "szaj.03a",      0x80000, 0xa3802fe3, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "szaj.04a",      0x80000, 0xe7ca87c7, 1 | BRF_ESS | BRF_PRG },
	{ "szaj.05a",      0x80000, 0xc88ebf88, 1 | BRF_ESS | BRF_PRG },
	{ "szaj.06a",      0x80000, 0x35ed5b7a, 1 | BRF_ESS | BRF_PRG },
	{ "szaj.07a",      0x80000, 0x975dcb3e, 1 | BRF_ESS | BRF_PRG },
	{ "szaj.08a",      0x80000, 0xdc73f2d7, 1 | BRF_ESS | BRF_PRG },

	{ "sz2.13m",      0x400000, 0x4d1f1f22, 3 | BRF_GRA },
	{ "sz2.15m",      0x400000, 0x19cea680, 3 | BRF_GRA },
	{ "sz2.17m",      0x400000, 0xe01b4588, 3 | BRF_GRA },
	{ "sz2.19m",      0x400000, 0x0feeda64, 3 | BRF_GRA },
	{ "sz2.14m",      0x100000, 0x0560c6aa, 3 | BRF_GRA },
	{ "sz2.16m",      0x100000, 0xae940f87, 3 | BRF_GRA },
	{ "sz2.18m",      0x100000, 0x4bc3c8bc, 3 | BRF_GRA },
	{ "sz2.20m",      0x100000, 0x39e674c0, 3 | BRF_GRA },

	{ "sz2.01a",      0x020000, 0x1bc323cf, 4 | BRF_ESS | BRF_PRG },
	{ "sz2.02a",      0x020000, 0xba6a5013, 4 | BRF_ESS | BRF_PRG },

	{ "sz2.11m",      0x200000, 0xaa47a601, 5 | BRF_SND },
	{ "sz2.12m",      0x200000, 0x2237bc53, 5 | BRF_SND },
};


STD_ROM_PICK(Sfz2aj) STD_ROM_FN(Sfz2aj)

static struct BurnRomInfo Sfz2ahRomDesc[] = {
	{ "szah.03",       0x80000, 0x06f93d1d, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "szah.04",       0x80000, 0xe62ee914, 1 | BRF_ESS | BRF_PRG },
	{ "szah.05",       0x80000, 0x2b7f4b20, 1 | BRF_ESS | BRF_PRG },
	{ "sza.06",        0x80000, 0x0abda2fc, 1 | BRF_ESS | BRF_PRG },
	{ "sza.07",        0x80000, 0xe9430762, 1 | BRF_ESS | BRF_PRG },
	{ "sza.08",        0x80000, 0xb65711a9, 1 | BRF_ESS | BRF_PRG },

	{ "sz2.13m",      0x400000, 0x4d1f1f22, 3 | BRF_GRA },
	{ "sz2.15m",      0x400000, 0x19cea680, 3 | BRF_GRA },
	{ "sz2.17m",      0x400000, 0xe01b4588, 3 | BRF_GRA },
	{ "sz2.19m",      0x400000, 0x0feeda64, 3 | BRF_GRA },
	{ "sz2.14m",      0x100000, 0x0560c6aa, 3 | BRF_GRA },
	{ "sz2.16m",      0x100000, 0xae940f87, 3 | BRF_GRA },
	{ "sz2.18m",      0x100000, 0x4bc3c8bc, 3 | BRF_GRA },
	{ "sz2.20m",      0x100000, 0x39e674c0, 3 | BRF_GRA },

	{ "sz2.01a",      0x020000, 0x1bc323cf, 4 | BRF_ESS | BRF_PRG },
	{ "sz2.02a",      0x020000, 0xba6a5013, 4 | BRF_ESS | BRF_PRG },

	{ "sz2.11m",      0x200000, 0xaa47a601, 5 | BRF_SND },
	{ "sz2.12m",      0x200000, 0x2237bc53, 5 | BRF_SND },
};


STD_ROM_PICK(Sfz2ah) STD_ROM_FN(Sfz2ah)

static struct BurnRomInfo Sfz2abRomDesc[] = {
	{ "szab.03",       0x80000, 0xcb436eca, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "szab.04",       0x80000, 0x14534bea, 1 | BRF_ESS | BRF_PRG },
	{ "szab.05",       0x80000, 0x7fb10658, 1 | BRF_ESS | BRF_PRG },
	{ "sza.06",        0x80000, 0x0abda2fc, 1 | BRF_ESS | BRF_PRG },
	{ "sza.07",        0x80000, 0xe9430762, 1 | BRF_ESS | BRF_PRG },
	{ "sza.08",        0x80000, 0xb65711a9, 1 | BRF_ESS | BRF_PRG },

	{ "sz2.13m",      0x400000, 0x4d1f1f22, 3 | BRF_GRA },
	{ "sz2.15m",      0x400000, 0x19cea680, 3 | BRF_GRA },
	{ "sz2.17m",      0x400000, 0xe01b4588, 3 | BRF_GRA },
	{ "sz2.19m",      0x400000, 0x0feeda64, 3 | BRF_GRA },
	{ "sz2.14m",      0x100000, 0x0560c6aa, 3 | BRF_GRA },
	{ "sz2.16m",      0x100000, 0xae940f87, 3 | BRF_GRA },
	{ "sz2.18m",      0x100000, 0x4bc3c8bc, 3 | BRF_GRA },
	{ "sz2.20m",      0x100000, 0x39e674c0, 3 | BRF_GRA },

	{ "sz2.01a",      0x020000, 0x1bc323cf, 4 | BRF_ESS | BRF_PRG },
	{ "sz2.02a",      0x020000, 0xba6a5013, 4 | BRF_ESS | BRF_PRG },

	{ "sz2.11m",      0x200000, 0xaa47a601, 5 | BRF_SND },
	{ "sz2.12m",      0x200000, 0x2237bc53, 5 | BRF_SND },
};


STD_ROM_PICK(Sfz2ab) STD_ROM_FN(Sfz2ab)

static struct BurnRomInfo Sfz2aaRomDesc[] = {
	{ "szaa.03",       0x80000, 0x88e7023e, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "szaa.04",       0x80000, 0xae8ec36e, 1 | BRF_ESS | BRF_PRG },
	{ "szaa.05",       0x80000, 0xf053a55e, 1 | BRF_ESS | BRF_PRG },
	{ "szaa.06",       0x80000, 0xcfc0e7a8, 1 | BRF_ESS | BRF_PRG },
	{ "szaa.07",       0x80000, 0x5feb8b20, 1 | BRF_ESS | BRF_PRG },
	{ "szaa.08",       0x80000, 0x6eb6d412, 1 | BRF_ESS | BRF_PRG },

	{ "sz2.13m",      0x400000, 0x4d1f1f22, 3 | BRF_GRA },
	{ "sz2.15m",      0x400000, 0x19cea680, 3 | BRF_GRA },
	{ "sz2.17m",      0x400000, 0xe01b4588, 3 | BRF_GRA },
	{ "sz2.19m",      0x400000, 0x0feeda64, 3 | BRF_GRA },
	{ "sz2.14m",      0x100000, 0x0560c6aa, 3 | BRF_GRA },
	{ "sz2.16m",      0x100000, 0xae940f87, 3 | BRF_GRA },
	{ "sz2.18m",      0x100000, 0x4bc3c8bc, 3 | BRF_GRA },
	{ "sz2.20m",      0x100000, 0x39e674c0, 3 | BRF_GRA },

	{ "sz2.01a",      0x020000, 0x1bc323cf, 4 | BRF_ESS | BRF_PRG },
	{ "sz2.02a",      0x020000, 0xba6a5013, 4 | BRF_ESS | BRF_PRG },

	{ "sz2.11m",      0x200000, 0xaa47a601, 5 | BRF_SND },
	{ "sz2.12m",      0x200000, 0x2237bc53, 5 | BRF_SND },
};


STD_ROM_PICK(Sfz2aa) STD_ROM_FN(Sfz2aa)

struct BurnDriver BurnDrvCpsSfa2 = {
	"sfa2", NULL, NULL, "1996",
	"Street Fighter Alpha 2 (960306 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfa2RomInfo, Sfa2RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfz2j = {
	"sfz2j", "sfa2", NULL, "1996",
	"Street Fighter Zero 2 (960227 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfz2jRomInfo, Sfz2jRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfz2a = {
	"sfz2a", "sfa2", NULL, "1996",
	"Street Fighter Zero 2 (960227 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfz2aRomInfo, Sfz2aRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfz2b = {
	"sfz2b", "sfa2", NULL, "1996",
	"Street Fighter Zero 2 (960531 Brazil)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfz2bRomInfo, Sfz2bRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfz2br1 = {
	"sfz2br1", "sfa2", NULL, "1996",
	"Street Fighter Zero 2 (960304 Brazil)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfz2br1RomInfo, Sfz2br1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfz2h = {
	"sfz2h", "sfa2", NULL, "1996",
	"Street Fighter Zero 2 (960304 Hispanic)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfz2hRomInfo, Sfz2hRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfz2n = {
	"sfz2n", "sfa2", NULL, "1996",
	"Street Fighter Zero 2 (960229 Oceania)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfz2nRomInfo, Sfz2nRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfz2aj = {
	"sfz2aj", "sfz2aa", NULL, "1996",
	"Street Fighter Zero 2 Alpha (960805 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfz2ajRomInfo, Sfz2ajRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfz2ah = {
	"sfz2ah", "sfz2aa", NULL, "1996",
	"Street Fighter Zero 2 Alpha (960813 Hispanic)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfz2ahRomInfo, Sfz2ahRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfz2ab = {
	"sfz2ab", "sfz2aa", NULL, "1996",
	"Street Fighter Zero 2 Alpha (960813 Brazil)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING |BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfz2abRomInfo, Sfz2abRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSfz2aa = {
	"sfz2aa", "sfa2", NULL, "1996",
	"Street Fighter Zero 2 Alpha (960826 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfz2aaRomInfo, Sfz2aaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
