/*************************************************************************

  Rainbow Islands C-Chip Protection

  2002-Feb rewritten by Robert Gallagher

    - A replacement romset was coded, then inserted into a Rainbow Islands Extra PCB.
      This replacement would break into the gameplay, and begin dumping all possible data from
      the games C-chip to the display. The data was collected, recorded (photos) then added
      to this driver
    - C-chip data are all handled internally with arrays (no longer using JB1-F89 from Jumping)
    - More accurate emulation of C-chip (allowing writes, only returning data when requested...)
    - Aspects of the C-chip are more accurately 'simulated' by dynamically updating data, rather
      than relying on hard-coded data from the Jumping bootleg
    - GOAL IN Y-coordinates are randomized, from a collected set of possibles, similar to a real machine
    - None of the data present has been 'made up', everything has been verified with real hardware
    - Many thanks to Tormod Tjaberg for dumping the Rainbow Islands Extra c-chip data
      making RIE fully playable


  BANK 0  000 - 002  set by the 68000 during initialization
	      003 - 006  joystick and other input bits
	      008        coin counters and lock-out
	      00D        round number for world data request
	      01D        internal use
  BANK 1  000        internal use
          001 - 002  round height (LSB first)
	      004 - 0ff  unknown data
          100        request round data
	      101 - 140  walking on the rainbow offsets
	      141        round number for round data request
	      142 - 145  round address (MSB first)
	      148        boss or secret room flag
          149        request goal-in data
	      14A - 155  goal-in data
  BANK 2  000 - 01f  rainbow dissolve graphics
	      020 - 03f  rainbow smashing graphics
	      040 - 061  unused data
  BANK 4  002 - XXX  monster animation sequences /
	                 starts with directory of 2-byte offsets
  BANK 5  000        request world data
          002 - XXX  monster property records /
	                 starts with directory of 2-byte offsets
  BANK 6  002 - 141  unknown, has $20 bytes per world
  BANK 7  002 - XXX  monster to Bubble Bobble sprite mapping


*************************************************************************/

#include "taito.h"

static unsigned char* CRAM[8];

static int current_bank=0;
static int extra_version=1;
/*************************************
 *
 * C-Chip bank data
 *
 *************************************/

static void request_round_data(void)
{
	int round = CRAM[1][0x141]; /* 0...49 */

	memcpy(CRAM[1], CROM_BANK1, sizeof CROM_BANK1);
	memcpy(CRAM[2], CROM_BANK2, sizeof CROM_BANK2);

	CRAM[1][1] = cchip_round_height[round] >> 0;
	CRAM[1][2] = cchip_round_height[round] >> 8;

	CRAM[1][0x142] = cchip_round_address[round] >> 24;
	CRAM[1][0x143] = cchip_round_address[round] >> 16;
	CRAM[1][0x144] = cchip_round_address[round] >> 8;
	CRAM[1][0x145] = cchip_round_address[round] >> 0;

	/* set the secret room or boss flag */

	CRAM[1][0x148] = (round >= 40 || round % 4 == 3);
}

static void request_world_data(void)
{
	int world = CRAM[0][0x00D] / 4; /* 0...9 */

	if (extra_version)
	{
		static const unsigned int world_swap[] =
		{
			8, 7, 6, 4, 0, 2, 3, 5, 1, 9
		};

		world = world_swap[world];
	}


	/* first two bytes in each bank are left unchanged  */

	memcpy(CRAM[4] + 2, CROM_BANK4[world].data, CROM_BANK4[world].size);
	memcpy(CRAM[5] + 2, CROM_BANK5[world].data, CROM_BANK5[world].size);
	memcpy(CRAM[7] + 2, CROM_BANK7[world].data, CROM_BANK7[world].size);

		/* banks 5 and 6 are different in the extra version */

	if (extra_version)
	{
		int i;

		for (i = 0; i < 8; i++)
		{
			unsigned int patch = cchip_extra_patch[world][i];

			if (patch != 0)
			{
				CRAM[5][CRAM[5][2] + 22 * i + 18] = patch >> 0;
				CRAM[5][CRAM[5][2] + 22 * i + 19] = patch >> 8;
			}
		}

		memcpy(CRAM[6] + 2, CROM_BANK6_EXTRA, sizeof CROM_BANK6_EXTRA);
	}
	else
	{
		memcpy(CRAM[6] + 2, CROM_BANK6, sizeof CROM_BANK6);
	}

}

static void request_goalin_data(void)
{
	int n = rand() % 15;

	CRAM[1][0x14B] = 0x00; /* x coordinates */
	CRAM[1][0x14D] = 0x10;
	CRAM[1][0x14F] = 0x20;
	CRAM[1][0x151] = 0x38;
	CRAM[1][0x153] = 0x50;
	CRAM[1][0x155] = 0x60;

	CRAM[1][0x14A] = cchip_goalin[n][0]; /* y coordinates */
	CRAM[1][0x14C] = cchip_goalin[n][1];
	CRAM[1][0x14E] = cchip_goalin[n][2];
	CRAM[1][0x150] = cchip_goalin[n][3];
	CRAM[1][0x152] = cchip_goalin[n][4];
	CRAM[1][0x154] = cchip_goalin[n][5];
}

void cchip_timer()
{
	if (CRAM[1][0x100] == 1)
	{
		request_round_data();

		CRAM[1][0x100] = 0xFF;
	}

	if (CRAM[5][0x000] == 1)
	{
		request_world_data();

		CRAM[5][0x000] = 0xFF;
	}

	if (CRAM[1][0x149] == 1)
	{
		request_goalin_data();

		CRAM[1][0x149] = 0xFF;
	}
/* todo
	coin_lockout_w(1, CRAM[0][8] & 0x80);
	coin_lockout_w(0, CRAM[0][8] & 0x40);
	coin_counter_w(1, CRAM[0][8] & 0x20);
	coin_counter_w(0, CRAM[0][8] & 0x10);
*/
	CRAM[0][3] = rainbowInput[0];
	CRAM[0][4] = rainbowInput[1];
	CRAM[0][5] = rainbowInput[2];
	CRAM[0][6] = rainbowInput[3];

}

/*************************************
 *
 * C-Chip reads and writes
 *
 *************************************/

void rainbow_cchip_bank_w(unsigned char d)
{
//	bprintf(PRINT_NORMAL, "rainbow_cchip_bank_w %x\n",d);
	current_bank = d & 7;
}

void rainbow_cchip_ram_w(unsigned int a,unsigned char d)
{
//	bprintf(PRINT_NORMAL, "rainbow_cchip_ram_w %x to %x in bank %x\n",d,a,current_bank);
	CRAM[current_bank][a] = d;
}

unsigned char rainbow_cchip_ctrl_r()
{
//	bprintf(PRINT_NORMAL, "rainbow_cchip_ctrl_r\n");
	return 1;
}

unsigned char rainbow_cchip_ram_r (unsigned int a)
{
//	bprintf(PRINT_NORMAL, "rainbow_cchip_ram_r %x bank %x\n",a,current_bank);
	return CRAM[current_bank][a];
}

/*************************************
 *
 * C-Chip initialization
 *
 *************************************/

void rainbow_cchip_init(int version)
{
	extra_version=version;
	for (int i = 0; i < 8; i++)
	{
		CRAM[i] = (unsigned char*)malloc(0x400);
		memset(CRAM[i],0xFF,0x400);
	}

}

void rainbow_cchip_exit()
{
	for (int i = 0; i < 8; i++)
	{
		free(CRAM[i]);
	}
}

void rainbow_cchip_scan(int /*nAction*/)
{
	for (int i = 0; i < 8; i++)
	{
		SCAN_VAR(CRAM[i]);
	}
	SCAN_VAR(current_bank);
	SCAN_VAR(extra_version);
}



