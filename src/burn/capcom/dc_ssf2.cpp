#include "cps.h"

STDINPUTINFOSPEC(Drv, CpsFsi);

static int DrvInit()
{
	if (Cps2Init()) {
		return 1;
	}

	nCpsGfxScroll[3] = 0;

	return 0;
}

static int Ssf2tbInit()
{
	Ssf2tb = 1;

	if (Cps2Init()) {
		return 1;
	}

	nCpsGfxScroll[3] = 0;

	return 0;
}

static int Ssf2tbExit()
{
	Ssf2tb = 0;
	
	return CpsExit();
}

static struct BurnRomInfo Ssf2RomDesc[] = {
	{ "ssfe.03",       0x80000, 0xa597745d, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "ssfe.04",       0x80000, 0xb082aa67, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.05",       0x80000, 0x02b9c137, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.06",       0x80000, 0x70d470c5, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.07",       0x80000, 0x2409001d, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2) STD_ROM_FN(Ssf2)

static struct BurnRomInfo Ssf2uRomDesc[] = {
	{ "ssfu.03a",      0x80000, 0x72f29c33, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "ssfu.04a",      0x80000, 0x935cea44, 1 | BRF_ESS | BRF_PRG },
	{ "ssfu.05",       0x80000, 0xa0acb28a, 1 | BRF_ESS | BRF_PRG },
	{ "ssfu.06",       0x80000, 0x47413dcf, 1 | BRF_ESS | BRF_PRG },
	{ "ssfu.07",       0x80000, 0xe6066077, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2u) STD_ROM_FN(Ssf2u)

static struct BurnRomInfo Ssf2aRomDesc[] = {
	{ "ssfa.03b",      0x80000, 0x83a059bf, 1 | BRF_ESS | BRF_PRG },
	{ "ssfa.04a",      0x80000, 0x5d873642, 1 | BRF_ESS | BRF_PRG },
	{ "ssfa.05",       0x80000, 0xf8fb4de2, 1 | BRF_ESS | BRF_PRG },
	{ "ssfa.06b",      0x80000, 0x3185d19d, 1 | BRF_ESS | BRF_PRG },
	{ "ssfa.07",       0x80000, 0x36e29217, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2a) STD_ROM_FN(Ssf2a)

static struct BurnRomInfo Ssf2ar1RomDesc[] = {
	{ "ssfa.03a",      0x80000, 0xd2a3c520, 1 | BRF_ESS | BRF_PRG },
	{ "ssfa.04a",      0x80000, 0x5d873642, 1 | BRF_ESS | BRF_PRG },
	{ "ssfa.05",       0x80000, 0xf8fb4de2, 1 | BRF_ESS | BRF_PRG },
	{ "ssfa.06",       0x80000, 0xaa8acee7, 1 | BRF_ESS | BRF_PRG },
	{ "ssfa.07",       0x80000, 0x36e29217, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2ar1) STD_ROM_FN(Ssf2ar1)

static struct BurnRomInfo Ssf2jRomDesc[] = {
	{ "ssfj.03b",      0x80000, 0x5c2e356d, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.04a",      0x80000, 0x013bd55c, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.05",       0x80000, 0x0918d19a, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.06b",      0x80000, 0x014e0c6d, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.07",       0x80000, 0xeb6a9b1b, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2j) STD_ROM_FN(Ssf2j)

static struct BurnRomInfo Ssf2jr1RomDesc[] = {
	{ "ssfj.03a",      0x80000, 0x0bbf1304, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.04a",      0x80000, 0x013bd55c, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.05",       0x80000, 0x0918d19a, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.06",       0x80000, 0xd808a6cd, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.07",       0x80000, 0xeb6a9b1b, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2jr1) STD_ROM_FN(Ssf2jr1)

static struct BurnRomInfo Ssf2jr2RomDesc[] = {
	{ "ssfj.03",       0x80000, 0x7eb0efed, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.04",       0x80000, 0xd7322164, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.05",       0x80000, 0x0918d19a, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.06",       0x80000, 0xd808a6cd, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.07",       0x80000, 0xeb6a9b1b, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2jr2) STD_ROM_FN(Ssf2jr2)

static struct BurnRomInfo Ssf2tbRomDesc[] = {
	{ "ssfe.3tc",      0x80000, 0x496a8409, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.4tc",      0x80000, 0x4b45c18b, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.5t",       0x80000, 0x6a9c6444, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.6tb",      0x80000, 0xe4944fc3, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.7t",       0x80000, 0x2c9f4782, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2tb) STD_ROM_FN(Ssf2tb)

static struct BurnRomInfo Ssf2tbr1RomDesc[] = {
	{ "ssfe.3t",       0x80000, 0x1e018e34, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.4t",       0x80000, 0xac92efaf, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.5t",       0x80000, 0x6a9c6444, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.6t",       0x80000, 0xf442562b, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.7t",       0x80000, 0x2c9f4782, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2tbr1) STD_ROM_FN(Ssf2tbr1)

static struct BurnRomInfo Ssf2tbjRomDesc[] = {
	{ "ssfj.3t",       0x80000, 0x980d4450, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.4t",       0x80000, 0xb4dc1906, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.5t",       0x80000, 0xa7e35fbc, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.6t",       0x80000, 0xcb592b30, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.7t",       0x80000, 0x1f239515, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2tbj) STD_ROM_FN(Ssf2tbj)

struct BurnDriver BurnDrvCpsSsf2 = {
	"ssf2", NULL, NULL, "1993",
	"Super Street Fighter II - the new challengers (super street fighter 2 930911 etc)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2RomInfo, Ssf2RomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSsf2u = {
	"ssf2u", "ssf2", NULL, "1993",
	"Super Street Fighter II - the new challengers (super street fighter 2 930911 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2uRomInfo, Ssf2uRomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSsf2a = {
	"ssf2a", "ssf2", NULL, "1993",
	"Super Street Fighter II - the new challengers (super street fighter 2 931005 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2aRomInfo, Ssf2aRomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSsf2ar1 = {
	"ssf2ar1", "ssf2", NULL, "1993",
	"Super Street Fighter II - the new challengers (super street fighter 2 930914 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2ar1RomInfo, Ssf2ar1RomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSsf2j = {
	"ssf2j", "ssf2", NULL, "1993",
	"Super Street Fighter II - the new challengers (super street fighter 2 931005 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2jRomInfo, Ssf2jRomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSsf2jr1 = {
	"ssf2jr1", "ssf2", NULL, "1993",
	"Super Street Fighter II - the new challengers (super street fighter 2 930911 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2jr1RomInfo, Ssf2jr1RomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSsf2jr2 = {
	"ssf2jr2", "ssf2", NULL, "1993",
	"Super Street Fighter II - the new challengers (super street fighter 2 930910 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2jr2RomInfo, Ssf2jr2RomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSsf2tb = {
	"ssf2tb", "ssf2", NULL, "1993",
	"Super Street Fighter II - the tournament battle (931119 etc)\0", "Linkup feature not implemented", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2tbRomInfo, Ssf2tbRomName, DrvInputInfo, NULL,
	Ssf2tbInit, Ssf2tbExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSsf2tbr1 = {
	"ssf2tbr1", "ssf2", NULL, "1993",
	"Super Street Fighter II - the tournament battle (930911 etc)\0", "Linkup feature not implemented", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2tbr1RomInfo, Ssf2tbr1RomName, DrvInputInfo, NULL,
	Ssf2tbInit, Ssf2tbExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsSsf2tbj = {
	"ssf2tbj", "ssf2", NULL, "1993",
	"Super Street Fighter II - the tournament battle (930911 Japan)\0", "Linkup feature not implemented", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2tbjRomInfo, Ssf2tbjRomName, DrvInputInfo, NULL,
	Ssf2tbInit, Ssf2tbExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
