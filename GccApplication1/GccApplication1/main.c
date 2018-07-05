/*
 * GccApplication1.c
 *
 * Created: 5/17/2018 6:13:56 PM
 * Author : Awsaf
 */ 
#define F_CPU 1000000UL // or whatever may be your frequency

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0x00;
	DDRA = 0xFF;
	int i=0;
	PORTA = 0x00 ;
	// setting DDR of PORT C
	while(1)
	{
		unsigned char x;
		x = PINB;

		//	PORTA = x;

		if( (x&(1<<5))!=0 )
		{
			//	printf("%d\n",i) ;
			i = (i+1)%16 ;
			PORTA = i ;
			//	PORTA = 0xFF;
			_delay_ms(150);
		}
		
		if( (x&(1<<6))!=0 )
		{
			i=(i-1+16)%16 ;
			PORTA = i ;
			_delay_ms(200);
		}

	}
}

