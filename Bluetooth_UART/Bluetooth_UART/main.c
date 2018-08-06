#define F_CPU  8000000L
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define USART_BaudRate 9600
#define BAUD_PRESCALE  (F_CPU / (USART_BaudRate *16L) -1)
#define UART_RxCHAR() { while((UCSRA & 1<<RXC)==0); }
#define UART_TxCHAR(ch) { while(!(UCSRA & 1<<UDRE)); UDR=ch; }


void UART_Init()
{
	UCSRB |= (1<<RXEN) ;// | (1<<TXEN);
	UCSRC |= (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1)  | (1<<USBS);  // 8 BIT CHARACTER
	UBRRL = (unsigned char) BAUD_PRESCALE;
	UBRRH = (unsigned char)(BAUD_PRESCALE >> 8) ;

}


volatile unsigned char inc;


int main(void)
{
	UART_Init();

	DDRA = 0xFF;
	PORTA |= (1<<PORTA0); //initial value
	_delay_ms(500);
	unsigned char  ch;
	while(1)
	{
		PORTA |= (1<<PORTA0); //initial value
		UART_RxCHAR(); //get a CHARACTER
		ch = UDR;

		if(ch == '1'){
			PORTA = 0xFF;
			_delay_ms(500);
			PORTA = 0x00;
			_delay_ms(500);
		}
		else if(ch != '\0'){
			PORTA |= (1<<PORTA2);
			_delay_ms(500);
			PORTA &= ~(1<<PORTA2);
			_delay_ms(500);
		}
		else{
			PORTA = ch;
		}

		//if(ch!=13 && ch!=10)
		 //  PORTA = ch; //
		_delay_ms(500);
		PORTA = 0x00;
		_delay_ms(200);
		//break;
	
		
	}

	return 0;

}