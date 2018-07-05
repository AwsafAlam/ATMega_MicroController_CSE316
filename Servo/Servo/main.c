/*
 * Servo.c
 *
 * Created: 6/26/2018 5:41:34 AM
 * Author : Awsaf
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL

#include <util/delay.h>
#include <avr/interrupt.h>               // for _delay_ms()

void unlock(){
		OCR1A = ICR1 - 500;
		_delay_ms(700);
		OCR1A = ICR1 - 2200;
		_delay_ms(700);
	
}

ISR(INT1_vect)//increment
{
	unlock();
	//_delay_ms(1000);
	GIFR = GIFR | 0b11100000;
}


int main(void)
{
    /* Replace with your application code */
	DDRD = 0xFF;
	TCCR1A |= 1 << WGM11 | 1<< COM1A0 | 1<< COM1A1;
	TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1<< CS10;
	
	ICR1 = 19999;
		
	
	MCUCR = MCUCR | 0b00001000;
	MCUCR = MCUCR & 0b11111011;

	MCUCSR = MCUCSR & 0b10111111;

	GICR = GICR | ( 1 << INT1);

	sei();
	
	
    while (1) 
    {
/*		OCR1A = ICR1 - 500;
		_delay_ms(500);
		OCR1A = ICR1 - 2200;
		_delay_ms(500);
  */
  }
}

