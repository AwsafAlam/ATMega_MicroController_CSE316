#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
#endif
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h" //Can be download from the bottom of this article

ISR(ADC_vect){
	
	//SendCommand(0x80 + 5);
	float a = ((ADCH)/255.0)*5.0;
	char charVal[10];

	//4 is mininum width, 3 is precision; float value is copied onto buff
	dtostrf(a, 4, 3, charVal);
	Lcd4_Set_Cursor(1,1);
	Lcd4_Write_String(charVal);
	
	//Start next Convertion
	ADCSRA |= 1<<ADSC;
	
}


int main(void)
{
	DDRD = 0xFF;
	DDRC = 0xFF;
	Lcd4_Init();
	
	ADCSRA |= 1<<ADPS2;
	ADMUX |= 1<< ADLAR;
	ADMUX |= 1<<REFS0; //Setting Reference voltage
	ADCSRA |= 1<<ADIE;
	ADCSRA |= 1<<ADEN;
	
	//Start the first conversion
	//Enable global interrupt
	sei();
	ADCSRA |= 1<<ADSC;
	
	while(1)
	{
	}
}