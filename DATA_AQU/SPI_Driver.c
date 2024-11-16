/*SPI Driver*/
#include "header.h"
#define cs0 (1<<7)
#define SPIF ((S0SPSR>>7)&1)
void spi_init(void)
{
	PINSEL0|=0x1500;//p0.4 p0.5 p0.6 scl MISO MOSI
	IODIR0=cs0;	  //p0.7 op dir
	IOSET0=cs0;	  //disselect slave
	S0SPCR=0x20;  //cpol=cpha=0, msb first, master mode select spi intrrupt disselect
	S0SPCCR=15;	  //spi freq is 1 mbps
}

u8 spi_read(u8 data)
{
	S0SPDR=data; //data from master to slave
	while(SPIF==0);	 //wait for data trinsmit
	return S0SPDR;	 //data slave to master
}


/////////////////////////////////////////////////
//////// mcp 3204 ///////////////////////////////
u32 mcp3204(u8 ch_num)
{
	u32 result;
	u8 low=0,high=0;
	ch_num=ch_num<<6;  //setting ch num to last 2 bits
	IOCLR0=cs0;		   //select slave
	spi_read(0x06);
	high=spi_read(ch_num);	  //send ch num to slave
	low=spi_read(0x0);
	IOSET0=cs0;	 //disselect slave
	high=high&0x0f;
	result=(high<<8)|low;  // taking 12 bits result recived from slaveqqqqqqqqqq
	return result;
}


