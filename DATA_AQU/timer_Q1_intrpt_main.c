#include "header.h"
int temp,ldr,flag;
main()
{
	float a,f;
	config_timer0(2);
	config_vic_timer0();
	uart0_init(9600);
	adc_init();
	spi_init();

	while(1)
	{
		if(flag)
		{
			temp=adc_read(1);
			ldr=mcp3204(2);
			uart0_tx_string("Temprature : ");
			a=(temp*3.3)/1023;
			a=(a-0.5)/0.01;
			uart0_float(a);
			uart0_tx_string(" degree C \r\nLight : ");
			f=(4096-ldr);
			f=(f/4096)*100;
			uart0_float(f);
			uart0_tx_string(" %\r\n");
			flag=0;
		}
	}
}



