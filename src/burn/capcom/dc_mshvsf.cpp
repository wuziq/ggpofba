#include "cps.h"

STDINPUTINFOSPEC(Drv, CpsFsi);

static struct BurnRomInfo MshvsfRomDesc[] = {
	{ "mvse.03f",      0x80000, 0xb72dc199, 1 | BRF_ESS | BRF_PRG },
	{ "mvse.04f",      0x80000, 0x6ef799f9, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05a",       0x80000, 0x1a5de0cb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsf) STD_ROM_FN(Mshvsf)

static struct BurnRomInfo MshvsfuRomDesc[] = {
	{ "mvsu.03g",      0x80000, 0x0664ab15, 1 | BRF_ESS | BRF_PRG },
	{ "mvsu.04g",      0x80000, 0x97e060ee, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05d",       0x80000, 0x921fc542, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfu) STD_ROM_FN(Mshvsfu)

static struct BurnRomInfo Mshvsfu1RomDesc[] = {
	{ "mvsu.03d",      0x80000, 0xae60a66a, 1 | BRF_ESS | BRF_PRG },
	{ "mvsu.04d",      0x80000, 0x91f67d8a, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05a",       0x80000, 0x1a5de0cb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfu1) STD_ROM_FN(Mshvsfu1)

static struct BurnRomInfo MshvsfjRomDesc[] = {
	{ "mvsj.03i",      0x80000, 0xd8cbb691, 1 | BRF_ESS | BRF_PRG },
	{ "mvsj.04i",      0x80000, 0x32741ace, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05h",       0x80000, 0x77870dc3, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfj) STD_ROM_FN(Mshvsfj)

static struct BurnRomInfo Mshvsfj1RomDesc[] = {
	{ "mvsj.03h",      0x80000, 0xfbe2115f, 1 | BRF_ESS | BRF_PRG },
	{ "mvsj.04h",      0x80000, 0xb528a367, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05g",       0x80000, 0x9515a245, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfj1) STD_ROM_FN(Mshvsfj1)

static struct BurnRomInfo Mshvsfj2RomDesc[] = {
	{ "mvsj.03g",      0x80000, 0xfdfa7e26, 1 | BRF_ESS | BRF_PRG },
	{ "mvsj.04g",      0x80000, 0xc921825f, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05a",       0x80000, 0x1a5de0cb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfj2) STD_ROM_FN(Mshvsfj2)

static struct BurnRomInfo MshvsfhRomDesc[] = {
	{ "mvsh.03f",      0x80000, 0x4f60f41e, 1 | BRF_ESS | BRF_PRG },
	{ "mvsh.04f",      0x80000, 0xdc08ec12, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05a",       0x80000, 0x1a5de0cb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfh) STD_ROM_FN(Mshvsfh)

static struct BurnRomInfo MshvsfaRomDesc[] = {
	{ "mvsa.03f",      0x80000, 0x5b863716, 1 | BRF_ESS | BRF_PRG },
	{ "mvsa.04f",      0x80000, 0x4886e65f, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05a",       0x80000, 0x1a5de0cb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfa) STD_ROM_FN(Mshvsfa)

static struct BurnRomInfo Mshvsfa1RomDesc[] = {
	{ "mvsa.03",       0x80000, 0x92ef1933, 1 | BRF_ESS | BRF_PRG },
	{ "mvsa.04",       0x80000, 0x4b24373c, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05",        0x80000, 0xac180c1c, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfa1) STD_ROM_FN(Mshvsfa1)

static struct BurnRomInfo MshvsfbRomDesc[] = {
	{ "mvsb.03g",      0x80000, 0x143895ef, 1 | BRF_ESS | BRF_PRG },
	{ "mvsb.04g",      0x80000, 0xdd8a886c, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05d",       0x80000, 0x921fc542, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfb) STD_ROM_FN(Mshvsfb)

static struct BurnRomInfo Mshvsfb1RomDesc[] = {
	{ "mvsb.03f",      0x80000, 0x9c4bb950, 1 | BRF_ESS | BRF_PRG },
	{ "mvsb.04f",      0x80000, 0xd3320d13, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05a",       0x80000, 0x1a5de0cb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfb1) STD_ROM_FN(Mshvsfb1)

struct BurnDriver BurnDrvCpsMshvsf = {
	"mshvsf", NULL, NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970625 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshvsfRomInfo, MshvsfRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMshvsfu = {
	"mshvsfu", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970827 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshvsfuRomInfo, MshvsfuRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMshvsfu1 = {
	"mshvsfu1", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970625 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Mshvsfu1RomInfo, Mshvsfu1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMshvsfj = {
	"mshvsfj", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970707 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshvsfjRomInfo, MshvsfjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMshvsfj1 = {
	"mshvsfj1", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970702 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Mshvsfj1RomInfo, Mshvsfj1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMshvsfj2 = {
	"mshvsfj2", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970625 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Mshvsfj2RomInfo, Mshvsfj2RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMshvsfh = {
	"mshvsfh", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970625 Hispanic)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshvsfhRomInfo, MshvsfhRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMshvsfa = {
	"mshvsfa", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970625 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshvsfaRomInfo, MshvsfaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMshvsfa1 = {
	"mshvsfa1", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970620 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Mshvsfa1RomInfo, Mshvsfa1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMshvsfb = {
	"mshvsfb", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970827 Brazil)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshvsfbRomInfo, MshvsfbRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsMshvsfb1 = {
	"mshvsfb1", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970625 Brazil)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Mshvsfb1RomInfo, Mshvsfb1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
