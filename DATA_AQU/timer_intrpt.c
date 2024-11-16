#include "header.h"
extern int flag;
void TIMER_Handler(void) __irq
{
//	extern int temp;
	flag=1;
	T0IR=1;
	VICVectAddr=0;
}
void config_timer0(u32 tc)
{
	T0PC=0;
	T0PR=15000000-1;
	T0TC=0;
	T0TCR=1;
	T0MR0=tc;
	T0MCR=3;
	
}
void config_vic_timer0(void)
{
	VICIntSelect=0;
	VICVectCntl0=4|(1<<5);
	VICVectAddr0=(u32)TIMER_Handler;
	VICIntEnable=(1<<4);
}




