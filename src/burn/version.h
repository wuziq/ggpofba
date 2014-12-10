// Version number, written as  vV.V.BB  or  vV.V.BBaa
// (0xVVBBaa, in BCD notation)

#define VER_MAJOR  0
#define VER_MINOR  2
#define VER_BETA  96
#define VER_ALPHA 72

#define MAKE_VERSION(a, b, c, d) ((a)* 0x100000) + ((b) * 0x010000) + ((((c) / 10) * 0x001000) + (((c) % 10) * 0x000100)) + ((((d) / 10) * 0x000010) + ((d) % 10))

#define BURN_VERSION          MAKE_VERSION(VER_MAJOR, VER_MINOR, VER_BETA, VER_ALPHA)
#define GGPOFBA_VERSION_0_25  MAKE_VERSION(0, 2, 96, 71)


