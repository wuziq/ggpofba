/*
 * Define QUARK_LOG_MODULE and include ggpo_log.h.
 */

#if defined(QUARK_LOG) && defined(FBA_DEBUG)

#if defined(__cplusplus)
extern "C" void QuarkLog(char *fmt, ...);
#else
extern void QuarkLog(char *fmt, ...);
#endif

#  define QUARK_LOG_STR(x)  QuarkLog("  %s @ %s: %s.\n", QUARK_LOG_MODULE, __FUNCTION__, x)
#  define QUARK_LOG_VAR(x)  QuarkLog("  %s @ %s: %s = %d.\n", QUARK_LOG_MODULE, __FUNCTION__, #x, x)
#  define QUARK_LOG_VAR2(y, x)  QuarkLog("  %s @ %s: %s %s = %d.\n", QUARK_LOG_MODULE, __FUNCTION__, y, #x, x)
#else
#  define QUARK_LOG_STR(x)
#  define QUARK_LOG_VAR(x)
#  define QUARK_LOG_VAR2(y, x)
#endif
