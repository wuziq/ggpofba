/*Taito sound controller
=========================
Part of FBAs Taito 68k hardware drivers
Credits: Mame team, Raine team
Coding by KEV, with help from Treble Winner and Jan_Klaassen
*/
///////////
// based on MAMEs taito_snd.c
//
#include "taito.h"

//#define logstuff // uncomment to enable basic logging

#define TC0140SYT_PORT01_FULL		(0x01)
#define TC0140SYT_PORT23_FULL		(0x02)
#define TC0140SYT_PORT01_FULL_MASTER	(0x04)
#define TC0140SYT_PORT23_FULL_MASTER	(0x08)

unsigned char slave_data[4]={0,0,0,0};
unsigned char master_data[4]={0,0,0,0};
unsigned char main_mode=0;
unsigned char slave_mode=0;
unsigned char status=0;
bool nmi_enabled=true;
bool nmi_req=false;

#define irq_check() { if (nmi_enabled&&nmi_req){ ZetNmi(); ;nmi_req=false; }}

void tc0140_port_w(unsigned char d)
{
	main_mode=d;
#ifdef logstuff
	bprintf(PRINT_NORMAL, "tc0140_port_w %x\n",d);
#endif
}

void tc0140_comm_w(unsigned char d)
{
#ifdef logstuff
	bprintf(PRINT_NORMAL, "tc0140_comm_w %x\n",d);
#endif

	switch (main_mode)	{
	case 0x00:
		slave_data[main_mode++]=d;
		return;

	case 0x01:
		slave_data[main_mode++]=d;
		status |= TC0140SYT_PORT01_FULL;
		nmi_req=true;
		return;

	case 0x02:
		slave_data[main_mode++]=d;
		return;

	case 0x03:
		slave_data[main_mode++]=d;
		status |= TC0140SYT_PORT23_FULL;
		nmi_req=true;
		return;

	case 0x04:
		if (!d)
		{
			ZetReset();
		}
		return;
	default:
		return;

	}

}


unsigned char tc0140_comm_r()
{
#ifdef logstuff
	bprintf(PRINT_NORMAL, "tc0140_comm_r %x\n",main_mode);
#endif
	switch(main_mode)
	{
	case 0x00:
		return master_data[main_mode++];
	case 0x01:
		status&=~TC0140SYT_PORT01_FULL_MASTER;
		return master_data[main_mode++];
	case 0x02:
		return master_data[main_mode++];
	case 0x03:
		status&=~TC0140SYT_PORT23_FULL_MASTER;
		return master_data[main_mode++];
	case 0x04:
		return status;
	default:
		return 0;

	}
}

//slave

void tc0140_slave_port_w(unsigned char d)
{
#ifdef logstuff
	bprintf(PRINT_NORMAL, "tc0140_slave_port_w %x\n",d);
#endif
	slave_mode=d;
}

void tc0140_slave_comm_w(unsigned char d)
{
#ifdef logstuff
	bprintf(PRINT_NORMAL, "tc0140_slave_comm_w %x\n",d);
#endif
	switch (slave_mode)
	{
	case 0x00:
		master_data[slave_mode++]=d;
		irq_check();
		return;
	case 0x01:
		master_data[slave_mode++]=d;
		status|= TC0140SYT_PORT01_FULL_MASTER;
		irq_check();
		return;
	case 0x02: master_data[slave_mode ++] = d;
		irq_check();
		return;
	case 0x03: master_data[slave_mode ++] = d;
		status |= TC0140SYT_PORT23_FULL_MASTER;
		irq_check();
		return;
	case 0x04:
		irq_check();
		return;
	case 0x05:
		nmi_enabled =0;
		irq_check();
		return;
	case 0x06:
		nmi_enabled=1;
		irq_check();
		return;
	default:
		irq_check();
		return;
	}

}

unsigned char tc0140_slave_comm_r()
{
#ifdef logstuff
	bprintf(PRINT_NORMAL, "tc0140_slave_comm_r %x\n",slave_mode);
#endif
	switch(slave_mode)
	{
	case 0x00:
		irq_check();
		return slave_data[slave_mode++];
	case 0x01:
		status &=~TC0140SYT_PORT01_FULL;
		irq_check();
		return slave_data[slave_mode++];
	case 0x02:
		irq_check();
		return slave_data[slave_mode++];
	case 0x03:
		status &= ~TC0140SYT_PORT23_FULL;
		irq_check();
		return slave_data[slave_mode++];
	case 0x04:
		irq_check();
		return status;
	default:
		irq_check();
		return 0;
	}
}


void tc0140_scan(int /*nAction*/)
{
	SCAN_VAR(slave_data);
	SCAN_VAR(master_data);
	SCAN_VAR(main_mode);
	SCAN_VAR(slave_mode);
	SCAN_VAR(status);
	SCAN_VAR(nmi_enabled);
	SCAN_VAR(nmi_req);
}



