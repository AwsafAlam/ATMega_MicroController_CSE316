#ifndef F_CPU
#define F_CPU 1000000 // or whatever may be your frequency
#endif

#include <avr/io.h>                    // adding header files
#include <util/delay.h>
#include <avr/interrupt.h>               // for _delay_ms()

volatile unsigned char count=0;

ISR(INT1_vect)//increment
{
	PORTA = 0x00;
	
	_delay_ms(500);
	GIFR = GIFR | 0b11100000;

}


ISR(INT2_vect)//decrement
{
PORTA = 0x00;

	_delay_ms(500);
	GIFR = GIFR | 0b11100000;
}

int main(void)
{
	//DDRB=0;
	DDRA=0xFF;
	
	MCUCR |= (1<<ISC01)| (1<<ISC00);
	MCUCR |= (1<<ISC11)| (1<<ISC10);
	
	
	GICR |= (1 << INT0) | ( 1 << INT1);

	sei();
	
	
	// setting DDR of PORT C

	
	while(1)
	{
	PORTA = 0xFF;
		
	}

}
