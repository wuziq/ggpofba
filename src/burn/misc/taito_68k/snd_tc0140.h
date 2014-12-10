/*Taito sound controller
=========================
Part of FBAs Taito 68k hardware drivers
Credits: Mame team, Raine team
Coding by KEV, with help from Treble Winner and Jan_Klaassen
*/
// taken from MAME
#ifndef __tc0140_H__
#define __tc0140_H__

void tc0140_port_w(unsigned char d);
void tc0140_comm_w(unsigned char d);
unsigned char tc0140_comm_r();

void tc0140_slave_port_w(unsigned char d);
void tc0140_slave_comm_w(unsigned char d);
unsigned char tc0140_slave_comm_r();

void tc0140_scan(int nAction);

#endif



