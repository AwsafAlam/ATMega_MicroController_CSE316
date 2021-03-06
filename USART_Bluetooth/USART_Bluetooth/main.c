#define F_CPU 8000000UL		/* Define CPU clock Frequency e.g. here its 8MHz */

#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <util/delay.h>						/* Include AVR std. library file */
#include <avr/interrupt.h>
#include "lcd.h" //Can be download from the bottom of this article



#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)	/* Define prescale value */

void USART_Init(unsigned long BAUDRATE)				/* USART initialize function */
{
	UCSRB |= (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);				/* Enable USART transmitter and receiver */
	UCSRC |= (1 << URSEL)| (1 << UCSZ0) | (1 << UCSZ1);	/* Write USCRC for 8 bit data and 1 stop bit */
	UBRRL = BAUD_PRESCALE;							/* Load UBRRL with lower 8 bit of prescale value */
	UBRRH = (BAUD_PRESCALE >> 8);					/* Load UBRRH with upper 8 bit of prescale value */
}

char USART_RxChar()									/* Data receiving function */
{
	while (!(UCSRA & (1 << RXC)));					/* Wait until new data receive */
	return(UDR);									/* Get and return received data */
}

void USART_TxChar(char data)						/* Data transmitting function */
{
	UDR = data;										/* Write data to be transmitting in UDR */
	while (!(UCSRA & (1<<UDRE)));					/* Wait until data transmit and buffer get empty */
}

int main(void)
{
	
	DDRA = 0xFF;
	DDRD = 0xFF;
	DDRC = 0xFF;
	Lcd4_Init();
	
	
	PORTA |= (1<<PORTA1);
	USART_Init(9600);                /* initialize USART with 9600 baud rate */
	sei();
	
	while (1)
	{
		PORTA |= (1<<PORTA1);
		
		
	}
}

ISR (USART_RXC_vect)
{
	uint8_t oldsrg = SREG;
	cli();
	char received_char = UDR;
	
	Lcd4_Set_Cursor(1,1);
	Lcd4_Write_Char(received_char);
	
	PORTA = received_char;
	_delay_ms(600);
	
	PORTA= 0x00;
	_delay_ms(50);
	
	PORTA= 0xFF;
	_delay_ms(100);
	
	PORTA= 0x00;
	_delay_ms(100);
	
	
	SREG = oldsrg;
}