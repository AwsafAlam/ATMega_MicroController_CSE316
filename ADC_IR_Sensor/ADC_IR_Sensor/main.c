#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "LCD_display.h"

int main(void)
{
	init();
	
	//Configure ADC
	//Enable interrupts function in ADC
	//8-bit or 10-bit
	// 1 000 000 / 50 000 = 20  1000 000 / 20 000 = 5
	
	ADCSRA |= 1<<ADPS2;
	ADMUX |= 1<< ADLAR;
	ADMUX |= 1<<REFS0; //Setting Reference voltage
	ADCSRA |= 1<<ADIE;
	ADCSRA |= 1<<ADEN;
	
	//Start the first conversion
	//Enable global interrupt
	sei();
	ADCSRA |= 1<<ADSC;
	
	 /* Replace with your application code */
    while (1) 
    {
	
	}
}


ISR(ADC_vect){
	
	SendCommand(0x80 + 5);
	float a = ((ADCH-7)/255.0)*5.0;
	SendFloat(a);
	
	//SendNumber(ADCH);
	//Start next Convertion
	ADCSRA |= 1<<ADSC;
	
}
//******************









