#ifndef F_CPU
#define F_CPU 1000000 // or whatever may be your frequency
#endif

#include <avr/io.h>                    // adding header files
#include <util/delay.h>
#include <avr/interrupt.h>               // for _delay_ms()

volatile unsigned char count=0;

ISR(INT1_vect)//increment
{

	count = (count+1)%16;
	PORTA = count;
	_delay_ms(300);

	GIFR = GIFR | 0b11100000;

}


ISR(INT2_vect)//decrement
{

	count = (count-1+16)%16;
	PORTA = count;
	_delay_ms(300);
	GIFR = GIFR | 0b11100000;

}

int main(void)
{
	//DDRB=0;
	DDRA=0xFF;
	
	MCUCR = MCUCR | 0b00001000;
	MCUCR = MCUCR & 0b11111011;

	MCUCSR = MCUCSR & 0b10111111;

	GICR = GICR | (1 << INT2) | ( 1 << INT1);

	sei();
	
	
	// setting DDR of PORT C

	PORTA = count;

	while(1)
	{
	
	}

}
