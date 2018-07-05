/*
 * Counter_7Segement.c
 *
 * Created: 5/18/2018 8:23:17 AM
 * Author : Awsaf
 */ 

#define F_CPU 1000000UL 
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0xFF;
	DDRB = 0x00;
	DDRD = 0xFF;
	
	PORTD = 0xFF;
	//int i = 0;
	
	//int arr[11] = {0xC0 , 0xF9 ,0xA4 ,0xB0,0x99, 0x92,0x82,0xF8 , 0x80 ,0x90 };
	
	//PORTA = arr[0];
	PORTA = 0x00;
	
    /* Replace with your application code */
    while (1) 
    {
	/*	unsigned char x;
		x = PINB;

		if( (x&(1<<5))!=0 )
		{
			//	printf("%d\n",i) ;
			i = (i+1)%10 ;
			PORTA = arr[i] ;
			//	PORTA = 0xFF;
			_delay_ms(150);
		}
		
		if( (x&(1<<6))!=0 )
		{
			i=(i-1+10)%10 ;
			PORTA = arr[i] ;
			_delay_ms(200);
		}

		
		for (int i=0 ; i<10 ; i++)
		{
			PORTA = arr[i];
			
			_delay_ms(1500);
		}
		*/
		
    }

	
}

