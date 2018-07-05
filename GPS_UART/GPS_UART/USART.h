#include <avr/io.h>							/* Include AVR std. library file */
#include <avr/interrupt.h>

#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)	/* Define prescale value */

void USART_Init(unsigned long);				/* USART initialize function */
unsigned char USART_RxChar();						/* Data receiving function */
void USART_TxChar(char);					/* Data transmitting function */
void USART_SendString(char*);				/* Send string of USART data function */


void USART_Init(unsigned long BAUDRATE)				/* USART initialize function */
{
	UCSRA = 0b00000000;
	//UCSRB |=  (1 << TXEN) | (1 << RXCIE);				/*Polling Enable USART transmitter and receiver */
	UCSRB |= (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);	/* Interrupt Enable USART transmitter and receiver */
	
	UCSRC |= (1 << URSEL)| (1 << UCSZ0) | (1 << UCSZ1);	/* Write USCRC for 8 bit data and 1 stop bit */
	UCSRC &=  (0 << UCSZ2);
	//UBRRL = BAUD_PRESCALE;							/* Load UBRRL with lower 8 bit of prescale value */
	//UBRRH = (BAUD_PRESCALE >> 8);					/* Load UBRRH with upper 8 bit of prescale value */
	UBRRL = 0x5;
	UBRRH = 0x00;
}

unsigned char USART_RxChar()									/* Data receiving function */
{
	while (!(UCSRA & (1 << RXC)));					/* Wait until new data receive */
	return(UDR);									/* Get and return received data */
}

void USART_TxChar(char data)						/* Data transmitting function */
{
	while ((UCSRA & (1<<UDRE)) == 0x00);			/* Wait until data transmit and buffer get empty */
	UDR = data;										/* Write data to be transmitting in UDR */
}

void USART_SendString(char *str)					/* Send string of USART data function */
{
	int i=0;
	while (str[i]!= '\0')
	{
		USART_TxChar(str[i]);						/* Send each char of string till the NULL */
		i++;
	}
}
