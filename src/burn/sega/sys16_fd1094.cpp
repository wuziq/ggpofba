#include "sys16.h"
#include "fd1094.h"

#define S16_NUMCACHE 8

static unsigned char *fd1094_key; // the memory region containing key
static UINT16 *fd1094_cpuregion; // the CPU region with encrypted code
static UINT32  fd1094_cpuregionsize; // the size of this region in bytes

static UINT16* fd1094_userregion; // a user region where the current decrypted state is put and executed from
static UINT16* fd1094_cacheregion[S16_NUMCACHE]; // a cache region where S16_NUMCACHE states are stored to improve performance
static int fd1094_cached_states[S16_NUMCACHE]; // array of cached state numbers
static int fd1094_current_cacheposition; // current position in cache array


static void *fd1094_get_decrypted_base(void)
{
	if (!fd1094_key)
		return NULL;
	return fd1094_userregion;
}

/* this function checks the cache to see if the current state is cached,
   if it is then it copies the cached data to the user region where code is
   executed from, if its not cached then it gets decrypted to the current
   cache position using the functions in fd1094.c */
inline static void fd1094_setstate_and_decrypt(int state)
{
	int i;
	UINT32 addr;

	// force a flush of the prefetch cache
	m68k_set_reg(M68K_REG_PREF_ADDR, 0x1000);
	
	/* set the FD1094 state ready to decrypt.. */
	state = fd1094_set_state(fd1094_key,state);

	/* first check the cache, if its cached we don't need to decrypt it, just copy */
	for (i=0;i<S16_NUMCACHE;i++)
	{
		if (fd1094_cached_states[i] == state)
		{
			/* copy cached state */
			fd1094_userregion=fd1094_cacheregion[i];
			SekOpen(0);
			SekMapMemory((unsigned char*)fd1094_userregion, 0x000000, 0x07ffff, SM_FETCH);
			SekClose();

			return;
		}
	}

	/* mark it as cached (because it will be once we decrypt it) */
	fd1094_cached_states[fd1094_current_cacheposition]=state;

	for (addr=0;addr<fd1094_cpuregionsize/2;addr++)
	{
		UINT16 dat;
		dat = fd1094_decode(addr,fd1094_cpuregion[addr],fd1094_key,0);
		fd1094_cacheregion[fd1094_current_cacheposition][addr]=dat;
	}

	/* copy newly decrypted data to user region */
	fd1094_userregion=fd1094_cacheregion[fd1094_current_cacheposition];
	SekOpen(0);
	SekMapMemory((unsigned char*)fd1094_userregion, 0x000000, 0x07ffff, SM_FETCH);
	SekClose();

	fd1094_current_cacheposition++;

	if (fd1094_current_cacheposition>=S16_NUMCACHE)
	{
#if 1 && defined FBA_DEBUG
		bprintf(PRINT_NORMAL, _T("out of cache, performance may suffer, increase S16_NUMCACHE!\n"));
#endif
		fd1094_current_cacheposition=0;
	}
}

/* Callback for CMP.L instructions (state change) */
int __fastcall fd1094_cmp_callback(unsigned int val, int reg)
{
	if (reg == 0 && (val & 0x0000ffff) == 0x0000ffff) // ?
	{
		fd1094_setstate_and_decrypt((val & 0xffff0000) >> 16);
	}
	
	return 0;
}

/* Callback when the FD1094 enters interrupt code */
int __fastcall fd1094_int_callback (int irq)
{
	fd1094_setstate_and_decrypt(FD1094_STATE_IRQ);
	return (0x60+irq*4)/4; // vector address
}

int __fastcall fd1094_rte_callback (void)
{
	fd1094_setstate_and_decrypt(FD1094_STATE_RTE);
	
	return 0;
}

void fd1094_kludge_reset_values(void)
{
	int i;

	for (i = 0;i < 4;i++) {
		fd1094_userregion[i] = fd1094_decode(i,fd1094_cpuregion[i],fd1094_key,1);
	}
		
	SekOpen(0);
	SekMapMemory((unsigned char*)fd1094_userregion, 0x000000, 0x07ffff, SM_FETCH);
	SekClose();
}


/* function, to be called from MACHINE_RESET (every reset) */
void fd1094_machine_init(void)
{
	fd1094_setstate_and_decrypt(FD1094_STATE_RESET);
	fd1094_kludge_reset_values();

	SekOpen(0);
	SekSetCmpCallback(fd1094_cmp_callback);
	SekSetRTECallback(fd1094_rte_callback);
	SekSetIrqCallback(fd1094_int_callback);
	SekClose();
}

/* startup function, to be called from DRIVER_INIT (once on startup) */
void fd1094_driver_init()
{
	int i;

	fd1094_cpuregion = (UINT16*)System16Rom;
	fd1094_cpuregionsize = System16RomSize;
	fd1094_key = System16Key;

	/* punt if no key; this allows us to be called even for non-FD1094 games */
	if (!fd1094_key)
		return;
		
	for (i=0;i<S16_NUMCACHE;i++)
	{
		fd1094_cacheregion[i]=(UINT16*)malloc(fd1094_cpuregionsize);
	}

	/* flush the cached state array */
	for (i=0;i<S16_NUMCACHE;i++) fd1094_cached_states[i] = -1;
	
	fd1094_current_cacheposition = 0;
}
