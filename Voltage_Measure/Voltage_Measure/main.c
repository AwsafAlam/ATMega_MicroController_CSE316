#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "lcd.h"

#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7


int main(void)
{
	//init();
	DDRD = 0xFF;
	DDRC = 0xFF;
	
	//Configure ADC
	//Enable interrupts function in ADC
	//8-bit or 10-bit
	// 1 000 000 / 50 000 = 20  1000 000 / 20 000 = 5
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
	
	int i;
	
	/* Replace with your application code */
	while (1)
	{
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("electroSome LCD Hello World");
		for(i=0;i<15;i++)
		{
			_delay_ms(500);
			Lcd4_Shift_Left();
		}
		for(i=0;i<15;i++)
		{
			_delay_ms(500);
			Lcd4_Shift_Right();
		}
		Lcd4_Clear();
		Lcd4_Set_Cursor(2,1);
		Lcd4_Write_Char('e');
		Lcd4_Write_Char('S');
		_delay_ms(2000);
		
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

