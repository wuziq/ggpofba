#include "cps.h"

STDINPUTINFOSPEC(Drv, CpsFsi);

static struct BurnRomInfo XmvsfRomDesc[] = {
	{ "xvse.03f",      0x80000, 0xdb06413f, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "xvse.04f",      0x80000, 0xef015aef, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.05a",       0x80000, 0x7db6025d, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.06a",       0x80000, 0xe8e2c75c, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.07",        0x80000, 0x08f0abed, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.08",        0x80000, 0x81929675, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.09",        0x80000, 0x9641f36b, 1 | BRF_ESS | BRF_PRG },

	{ "xvs.13m",      0x400000, 0xf6684efd, 3 | BRF_GRA },			 //  9
	{ "xvs.15m",      0x400000, 0x29109221, 3 | BRF_GRA },
	{ "xvs.17m",      0x400000, 0x92db3474, 3 | BRF_GRA },
	{ "xvs.19m",      0x400000, 0x3733473c, 3 | BRF_GRA },
	{ "xvs.14m",      0x400000, 0xbcac2e41, 3 | BRF_GRA },
	{ "xvs.16m",      0x400000, 0xea04a272, 3 | BRF_GRA },
	{ "xvs.18m",      0x400000, 0xb0def86a, 3 | BRF_GRA },
	{ "xvs.20m",      0x400000, 0x4b40ff9f, 3 | BRF_GRA },

	{ "xvs.01",       0x020000, 0x3999e93a, 4 | BRF_ESS | BRF_PRG }, // 17
	{ "xvs.02",       0x020000, 0x101bdee9, 4 | BRF_ESS | BRF_PRG },

	{ "xvs.11m",      0x200000, 0x9cadcdbc, 5 | BRF_SND },
	{ "xvs.12m",      0x200000, 0x7b11e460, 5 | BRF_SND },
};


STD_ROM_PICK(Xmvsf) STD_ROM_FN(Xmvsf)

static struct BurnRomInfo Xmvsfr1RomDesc[] = {
	{ "xvse.03d",      0x80000, 0x5ae5bd3b, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "xvse.04d",      0x80000, 0x5eb9c02e, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.05a",       0x80000, 0x7db6025d, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.06a",       0x80000, 0xe8e2c75c, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.07",        0x80000, 0x08f0abed, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.08",        0x80000, 0x81929675, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.09",        0x80000, 0x9641f36b, 1 | BRF_ESS | BRF_PRG },

	{ "xvs.13m",      0x400000, 0xf6684efd, 3 | BRF_GRA },			 //  9
	{ "xvs.15m",      0x400000, 0x29109221, 3 | BRF_GRA },
	{ "xvs.17m",      0x400000, 0x92db3474, 3 | BRF_GRA },
	{ "xvs.19m",      0x400000, 0x3733473c, 3 | BRF_GRA },
	{ "xvs.14m",      0x400000, 0xbcac2e41, 3 | BRF_GRA },
	{ "xvs.16m",      0x400000, 0xea04a272, 3 | BRF_GRA },
	{ "xvs.18m",      0x400000, 0xb0def86a, 3 | BRF_GRA },
	{ "xvs.20m",      0x400000, 0x4b40ff9f, 3 | BRF_GRA },

	{ "xvs.01",       0x020000, 0x3999e93a, 4 | BRF_ESS | BRF_PRG }, // 17
	{ "xvs.02",       0x020000, 0x101bdee9, 4 | BRF_ESS | BRF_PRG },

	{ "xvs.11m",      0x200000, 0x9cadcdbc, 5 | BRF_SND },
	{ "xvs.12m",      0x200000, 0x7b11e460, 5 | BRF_SND },
};


STD_ROM_PICK(Xmvsfr1) STD_ROM_FN(Xmvsfr1)

static struct BurnRomInfo XmvsfuRomDesc[] = {
	{ "xvsu.03k",      0x80000, 0x8739ef61, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "xvsu.04k",      0x80000, 0xe11d35c1, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.05a",       0x80000, 0x7db6025d, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.06a",       0x80000, 0xe8e2c75c, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.07",        0x80000, 0x08f0abed, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.08",        0x80000, 0x81929675, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.09",        0x80000, 0x9641f36b, 1 | BRF_ESS | BRF_PRG },

	{ "xvs.13m",      0x400000, 0xf6684efd, 3 | BRF_GRA },			 //  9
	{ "xvs.15m",      0x400000, 0x29109221, 3 | BRF_GRA },
	{ "xvs.17m",      0x400000, 0x92db3474, 3 | BRF_GRA },
	{ "xvs.19m",      0x400000, 0x3733473c, 3 | BRF_GRA },
	{ "xvs.14m",      0x400000, 0xbcac2e41, 3 | BRF_GRA },
	{ "xvs.16m",      0x400000, 0xea04a272, 3 | BRF_GRA },
	{ "xvs.18m",      0x400000, 0xb0def86a, 3 | BRF_GRA },
	{ "xvs.20m",      0x400000, 0x4b40ff9f, 3 | BRF_GRA },

	{ "xvs.01",       0x020000, 0x3999e93a, 4 | BRF_ESS | BRF_PRG }, // 17
	{ "xvs.02",       0x020000, 0x101bdee9, 4 | BRF_ESS | BRF_PRG },

	{ "xvs.11m",      0x200000, 0x9cadcdbc, 5 | BRF_SND },
	{ "xvs.12m",      0x200000, 0x7b11e460, 5 | BRF_SND },
};


STD_ROM_PICK(Xmvsfu) STD_ROM_FN(Xmvsfu)

static struct BurnRomInfo Xmvsfur1RomDesc[] = {
	{ "xvsu.03h",      0x80000, 0x5481155a, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "xvsu.04h",      0x80000, 0x1e236388, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.05a",       0x80000, 0x7db6025d, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.06a",       0x80000, 0xe8e2c75c, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.07",        0x80000, 0x08f0abed, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.08",        0x80000, 0x81929675, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.09",        0x80000, 0x9641f36b, 1 | BRF_ESS | BRF_PRG },

	{ "xvs.13m",      0x400000, 0xf6684efd, 3 | BRF_GRA },			 //  9
	{ "xvs.15m",      0x400000, 0x29109221, 3 | BRF_GRA },
	{ "xvs.17m",      0x400000, 0x92db3474, 3 | BRF_GRA },
	{ "xvs.19m",      0x400000, 0x3733473c, 3 | BRF_GRA },
	{ "xvs.14m",      0x400000, 0xbcac2e41, 3 | BRF_GRA },
	{ "xvs.16m",      0x400000, 0xea04a272, 3 | BRF_GRA },
	{ "xvs.18m",      0x400000, 0xb0def86a, 3 | BRF_GRA },
	{ "xvs.20m",      0x400000, 0x4b40ff9f, 3 | BRF_GRA },

	{ "xvs.01",       0x020000, 0x3999e93a, 4 | BRF_ESS | BRF_PRG }, // 17
	{ "xvs.02",       0x020000, 0x101bdee9, 4 | BRF_ESS | BRF_PRG },

	{ "xvs.11m",      0x200000, 0x9cadcdbc, 5 | BRF_SND },
	{ "xvs.12m",      0x200000, 0x7b11e460, 5 | BRF_SND },
};


STD_ROM_PICK(Xmvsfur1) STD_ROM_FN(Xmvsfur1)

static struct BurnRomInfo XmvsfjRomDesc[] = {
	{ "xvsj.03i",      0x80000, 0xef24da96, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "xvsj.04i",      0x80000, 0x70a59b35, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.05a",       0x80000, 0x7db6025d, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.06a",       0x80000, 0xe8e2c75c, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.07",        0x80000, 0x08f0abed, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.08",        0x80000, 0x81929675, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.09",        0x80000, 0x9641f36b, 1 | BRF_ESS | BRF_PRG },

	{ "xvs.13m",      0x400000, 0xf6684efd, 3 | BRF_GRA },			 //  9
	{ "xvs.15m",      0x400000, 0x29109221, 3 | BRF_GRA },
	{ "xvs.17m",      0x400000, 0x92db3474, 3 | BRF_GRA },
	{ "xvs.19m",      0x400000, 0x3733473c, 3 | BRF_GRA },
	{ "xvs.14m",      0x400000, 0xbcac2e41, 3 | BRF_GRA },
	{ "xvs.16m",      0x400000, 0xea04a272, 3 | BRF_GRA },
	{ "xvs.18m",      0x400000, 0xb0def86a, 3 | BRF_GRA },
	{ "xvs.20m",      0x400000, 0x4b40ff9f, 3 | BRF_GRA },

	{ "xvs.01",       0x020000, 0x3999e93a, 4 | BRF_ESS | BRF_PRG }, // 17
	{ "xvs.02",       0x020000, 0x101bdee9, 4 | BRF_ESS | BRF_PRG },

	{ "xvs.11m",      0x200000, 0x9cadcdbc, 5 | BRF_SND },
	{ "xvs.12m",      0x200000, 0x7b11e460, 5 | BRF_SND },
};


STD_ROM_PICK(Xmvsfj) STD_ROM_FN(Xmvsfj)

static struct BurnRomInfo Xmvsfjr1RomDesc[] = {
	{ "xvsj.03d",      0x80000, 0xbeb81de9, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "xvsj.04d",      0x80000, 0x23d11271, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.05a",       0x80000, 0x7db6025d, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.06a",       0x80000, 0xe8e2c75c, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.07",        0x80000, 0x08f0abed, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.08",        0x80000, 0x81929675, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.09",        0x80000, 0x9641f36b, 1 | BRF_ESS | BRF_PRG },

	{ "xvs.13m",      0x400000, 0xf6684efd, 3 | BRF_GRA },			 //  9
	{ "xvs.15m",      0x400000, 0x29109221, 3 | BRF_GRA },
	{ "xvs.17m",      0x400000, 0x92db3474, 3 | BRF_GRA },
	{ "xvs.19m",      0x400000, 0x3733473c, 3 | BRF_GRA },
	{ "xvs.14m",      0x400000, 0xbcac2e41, 3 | BRF_GRA },
	{ "xvs.16m",      0x400000, 0xea04a272, 3 | BRF_GRA },
	{ "xvs.18m",      0x400000, 0xb0def86a, 3 | BRF_GRA },
	{ "xvs.20m",      0x400000, 0x4b40ff9f, 3 | BRF_GRA },

	{ "xvs.01",       0x020000, 0x3999e93a, 4 | BRF_ESS | BRF_PRG }, // 17
	{ "xvs.02",       0x020000, 0x101bdee9, 4 | BRF_ESS | BRF_PRG },

	{ "xvs.11m",      0x200000, 0x9cadcdbc, 5 | BRF_SND },
	{ "xvs.12m",      0x200000, 0x7b11e460, 5 | BRF_SND },
};


STD_ROM_PICK(Xmvsfjr1) STD_ROM_FN(Xmvsfjr1)

static struct BurnRomInfo Xmvsfjr2RomDesc[] = {
	{ "xvsj.03c",      0x80000, 0x180656a1, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "xvsj.04c",      0x80000, 0x5832811c, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.05",        0x80000, 0x030e0e1e, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.06",        0x80000, 0x5d04a8ff, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.07",        0x80000, 0x08f0abed, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.08",        0x80000, 0x81929675, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.09",        0x80000, 0x9641f36b, 1 | BRF_ESS | BRF_PRG },

	{ "xvs.13m",      0x400000, 0xf6684efd, 3 | BRF_GRA },			 //  9
	{ "xvs.15m",      0x400000, 0x29109221, 3 | BRF_GRA },
	{ "xvs.17m",      0x400000, 0x92db3474, 3 | BRF_GRA },
	{ "xvs.19m",      0x400000, 0x3733473c, 3 | BRF_GRA },
	{ "xvs.14m",      0x400000, 0xbcac2e41, 3 | BRF_GRA },
	{ "xvs.16m",      0x400000, 0xea04a272, 3 | BRF_GRA },
	{ "xvs.18m",      0x400000, 0xb0def86a, 3 | BRF_GRA },
	{ "xvs.20m",      0x400000, 0x4b40ff9f, 3 | BRF_GRA },

	{ "xvs.01",       0x020000, 0x3999e93a, 4 | BRF_ESS | BRF_PRG }, // 17
	{ "xvs.02",       0x020000, 0x101bdee9, 4 | BRF_ESS | BRF_PRG },

	{ "xvs.11m",      0x200000, 0x9cadcdbc, 5 | BRF_SND },
	{ "xvs.12m",      0x200000, 0x7b11e460, 5 | BRF_SND },
};


STD_ROM_PICK(Xmvsfjr2) STD_ROM_FN(Xmvsfjr2)

static struct BurnRomInfo XmvsfaRomDesc[] = {
	{ "xvsa.03k",      0x80000, 0xd0cca7a8, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "xvsa.04k",      0x80000, 0x8c8e76fd, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.05a",       0x80000, 0x7db6025d, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.06a",       0x80000, 0xe8e2c75c, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.07",        0x80000, 0x08f0abed, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.08",        0x80000, 0x81929675, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.09",        0x80000, 0x9641f36b, 1 | BRF_ESS | BRF_PRG },

	{ "xvs.13m",      0x400000, 0xf6684efd, 3 | BRF_GRA },			 //  9
	{ "xvs.15m",      0x400000, 0x29109221, 3 | BRF_GRA },
	{ "xvs.17m",      0x400000, 0x92db3474, 3 | BRF_GRA },
	{ "xvs.19m",      0x400000, 0x3733473c, 3 | BRF_GRA },
	{ "xvs.14m",      0x400000, 0xbcac2e41, 3 | BRF_GRA },
	{ "xvs.16m",      0x400000, 0xea04a272, 3 | BRF_GRA },
	{ "xvs.18m",      0x400000, 0xb0def86a, 3 | BRF_GRA },
	{ "xvs.20m",      0x400000, 0x4b40ff9f, 3 | BRF_GRA },

	{ "xvs.01",       0x020000, 0x3999e93a, 4 | BRF_ESS | BRF_PRG }, // 17
	{ "xvs.02",       0x020000, 0x101bdee9, 4 | BRF_ESS | BRF_PRG },

	{ "xvs.11m",      0x200000, 0x9cadcdbc, 5 | BRF_SND },
	{ "xvs.12m",      0x200000, 0x7b11e460, 5 | BRF_SND },
};


STD_ROM_PICK(Xmvsfa) STD_ROM_FN(Xmvsfa)

static struct BurnRomInfo Xmvsfar1RomDesc[] = {
	{ "xvsa.03e",      0x80000, 0x9bdde21c, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "xvsa.04e",      0x80000, 0x33300edf, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.05a",       0x80000, 0x7db6025d, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.06a",       0x80000, 0xe8e2c75c, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.07",        0x80000, 0x08f0abed, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.08",        0x80000, 0x81929675, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.09",        0x80000, 0x9641f36b, 1 | BRF_ESS | BRF_PRG },
	
	{ "xvs.13m",      0x400000, 0xf6684efd, 3 | BRF_GRA },			 //  9
	{ "xvs.15m",      0x400000, 0x29109221, 3 | BRF_GRA },
	{ "xvs.17m",      0x400000, 0x92db3474, 3 | BRF_GRA },
	{ "xvs.19m",      0x400000, 0x3733473c, 3 | BRF_GRA },
	{ "xvs.14m",      0x400000, 0xbcac2e41, 3 | BRF_GRA },
	{ "xvs.16m",      0x400000, 0xea04a272, 3 | BRF_GRA },
	{ "xvs.18m",      0x400000, 0xb0def86a, 3 | BRF_GRA },
	{ "xvs.20m",      0x400000, 0x4b40ff9f, 3 | BRF_GRA },

	{ "xvs.01",       0x020000, 0x3999e93a, 4 | BRF_ESS | BRF_PRG }, // 17
	{ "xvs.02",       0x020000, 0x101bdee9, 4 | BRF_ESS | BRF_PRG },

	{ "xvs.11m",      0x200000, 0x9cadcdbc, 5 | BRF_SND },
	{ "xvs.12m",      0x200000, 0x7b11e460, 5 | BRF_SND },
};


STD_ROM_PICK(Xmvsfar1) STD_ROM_FN(Xmvsfar1)

static struct BurnRomInfo XmvsfhRomDesc[] = {
	{ "xvsh.03a",      0x80000, 0xd4fffb04, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "xvsh.04a",      0x80000, 0x1b4ea638, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.05a",       0x80000, 0x7db6025d, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.06a",       0x80000, 0xe8e2c75c, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.07",        0x80000, 0x08f0abed, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.08",        0x80000, 0x81929675, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.09",        0x80000, 0x9641f36b, 1 | BRF_ESS | BRF_PRG },

	{ "xvs.13m",      0x400000, 0xf6684efd, 3 | BRF_GRA },			 //  9
	{ "xvs.15m",      0x400000, 0x29109221, 3 | BRF_GRA },
	{ "xvs.17m",      0x400000, 0x92db3474, 3 | BRF_GRA },
	{ "xvs.19m",      0x400000, 0x3733473c, 3 | BRF_GRA },
	{ "xvs.14m",      0x400000, 0xbcac2e41, 3 | BRF_GRA },
	{ "xvs.16m",      0x400000, 0xea04a272, 3 | BRF_GRA },
	{ "xvs.18m",      0x400000, 0xb0def86a, 3 | BRF_GRA },
	{ "xvs.20m",      0x400000, 0x4b40ff9f, 3 | BRF_GRA },

	{ "xvs.01",       0x020000, 0x3999e93a, 4 | BRF_ESS | BRF_PRG }, // 17
	{ "xvs.02",       0x020000, 0x101bdee9, 4 | BRF_ESS | BRF_PRG },

	{ "xvs.11m",      0x200000, 0x9cadcdbc, 5 | BRF_SND },
	{ "xvs.12m",      0x200000, 0x7b11e460, 5 | BRF_SND },
};


STD_ROM_PICK(Xmvsfh) STD_ROM_FN(Xmvsfh)

static struct BurnRomInfo XmvsfbRomDesc[] = {
	{ "xvsb.03h",      0x80000, 0x05baccca, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "xvsb.04h",      0x80000, 0xe350c755, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.05a",       0x80000, 0x7db6025d, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.06a",       0x80000, 0xe8e2c75c, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.07",        0x80000, 0x08f0abed, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.08",        0x80000, 0x81929675, 1 | BRF_ESS | BRF_PRG },
	{ "xvs.09",        0x80000, 0x9641f36b, 1 | BRF_ESS | BRF_PRG },

	{ "xvs.13m",      0x400000, 0xf6684efd, 3 | BRF_GRA },			 //  9
	{ "xvs.15m",      0x400000, 0x29109221, 3 | BRF_GRA },
	{ "xvs.17m",      0x400000, 0x92db3474, 3 | BRF_GRA },
	{ "xvs.19m",      0x400000, 0x3733473c, 3 | BRF_GRA },
	{ "xvs.14m",      0x400000, 0xbcac2e41, 3 | BRF_GRA },
	{ "xvs.16m",      0x400000, 0xea04a272, 3 | BRF_GRA },
	{ "xvs.18m",      0x400000, 0xb0def86a, 3 | BRF_GRA },
	{ "xvs.20m",      0x400000, 0x4b40ff9f, 3 | BRF_GRA },

	{ "xvs.01",       0x020000, 0x3999e93a, 4 | BRF_ESS | BRF_PRG }, // 17
	{ "xvs.02",       0x020000, 0x101bdee9, 4 | BRF_ESS | BRF_PRG },
	{ "xvs.11m",      0x200000, 0x9cadcdbc, 5 | BRF_SND },
	{ "xvs.12m",      0x200000, 0x7b11e460, 5 | BRF_SND },
};


STD_ROM_PICK(Xmvsfb) STD_ROM_FN(Xmvsfb)

struct BurnDriver BurnDrvCpsXmvsf = {
	"xmvsf", NULL, NULL, "1996",
	"X-Men vs Street Fighter (961004 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, XmvsfRomInfo, XmvsfRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsXmvsfr1 = {
	"xmvsfr1", "xmvsf", NULL, "1996",
	"X-Men vs Street Fighter (960910 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Xmvsfr1RomInfo, Xmvsfr1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsXmvsfu = {
	"xmvsfu", "xmvsf", NULL, "1996",
	"X-Men vs Street Fighter (961023 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, XmvsfuRomInfo, XmvsfuRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsXmvsfur1 = {
	"xmvsfur1", "xmvsf", NULL, "1996",
	"X-Men vs Street Fighter (961004 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Xmvsfur1RomInfo, Xmvsfur1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsXmvsfj = {
	"xmvsfj", "xmvsf", NULL, "1996",
	"X-Men vs Street Fighter (961004 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, XmvsfjRomInfo, XmvsfjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsXmvsfjr1 = {
	"xmvsfjr1", "xmvsf", NULL, "1996",
	"X-Men vs Street Fighter (960910 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Xmvsfjr1RomInfo, Xmvsfjr1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsXmvsfjr2 = {
	"xmvsfjr2", "xmvsf", NULL, "1996",
	"X-Men vs Street Fighter (960909 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Xmvsfjr2RomInfo, Xmvsfjr2RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsXmvsfa = {
	"xmvsfa", "xmvsf", NULL, "1996",
	"X-Men vs Street Fighter (961023 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, XmvsfaRomInfo, XmvsfaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsXmvsfar1 = {
	"xmvsfar1", "xmvsf", NULL, "1996",
	"X-Men vs Street Fighter (960919 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Xmvsfar1RomInfo, Xmvsfar1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsXmvsfh = {
	"xmvsfh", "xmvsf", NULL, "1996",
	"X-Men vs Street Fighter (961004 Hispanic)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, XmvsfhRomInfo, XmvsfhRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsXmvsfb = {
	"xmvsfb", "xmvsf", NULL, "1996",
	"X-Men vs Street Fighter (961023 Brazil)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, XmvsfbRomInfo, XmvsfbRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
