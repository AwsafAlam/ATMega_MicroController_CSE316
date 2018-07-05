#define F_CPU 1000000UL		/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>		/* Include AVR std. library file */
#include <stdio.h>		/* Include std. library file */
#include <util/delay.h>		/* Include Delay header file */

int main(void)
{
	DDRD |= (1<<PD5);	/* Make OC1A pin as output */
	TCNT1 = 0;		/* Set timer1 count zero */
/*	ICR1 = 2499;		
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
*/
	//Configure TIMER1
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)

	ICR1=1499;  //fPWM=50Hz (Period = 20ms Standard).

	DDRD|=(1<<PD4)|(1<<PD5);   //PWM Pins as Out

	while(1)
	{

		OCR1A=97;   //0 degree
		_delay_ms(500);
		OCR1A=316;  //90 degree
		_delay_ms(500);
		
		OCR1A=425;  //135 degree
		_delay_ms(500);

		OCR1A=535;  //180 degree
		_delay_ms(500);

	}
}