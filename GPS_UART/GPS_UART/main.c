#define F_CPU 1600000UL
#define SREG   _SFR_IO8(0x3f)

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD.h"
#include "USART.h"
#include "GPS_Data.h"

int LCD_pos = 0;


int main() {
	
    GGA_Index=0;
	memset(GGA_Buffer, 0, Buffer_Size);
	memset(degrees_buffer,0,degrees_buffer_size);
	
    LCD_init();                      /* initialize LCD16x2 */
    //_delay_ms(3000);                 /* wait for GPS receiver to initialize */
    SendCommand(CLEAR_SCREEN);
    SendCommand(0x80+2);
   
    SendString("$");
    //SendCommand(CLEAR_SCREEN);
    //SendCommand(0x80);
    //unsigned char a;
	USART_Init(9600); 
	_delay_ms(5000);               /* initialize USART with 9600 baud rate */
	sei();
	
	//stdin = fdevopen(NULL , USART_RxChar);
    while (1)
    {
			//_delay_ms(1000);
			//LCD_String_xy(1,0,"UTC Time: ");
			//get_gpstime();                         /* Extract Time in UTC */
			//SendString(Time_Buffer);
			//LCD_pos++;
			//SendString(" - ");
			
			//LCD_String_xy(2,0,"Lat: ");
			//SendString("Lat: ");
			
			//a = USART_RxChar();
			//SendCharacter(a);
			
			//get_latitude(GGA_Pointers[0]);         /* Extract Latitude */
			//SendString(degrees_buffer);            /* display latitude in degree */
			//memset(degrees_buffer,0,degrees_buffer_size);
			
			//LCD_String_xy(3,0,"Long: ");
			//get_longitude(GGA_Pointers[2]);        /* Extract Longitude */
			//SendString(degrees_buffer);            /* display longitude in degree */
			//memset(degrees_buffer,0,degrees_buffer_size);
			
			//LCD_String_xy(4,0,"Alt: ");
			//get_altitude(GGA_Pointers[7]);         /* Extract Altitude in meters*/
			//SendString(Altitude_Buffer);
			
	}
		return 0;
}


	
ISR (USART_RXC_vect)
{
	uint8_t oldsrg = SREG;
	cli();
	char received_char = USART_RxChar();
	SendCommand(0x80 + LCD_pos);
	SendCharacter(received_char);
	LCD_pos ++;
	//SendString("int");
	//LCD_pos ++;
	
	if(LCD_pos == 15){
		LCD_pos = 64;
	//	_delay_ms(500);
	}
	else if(LCD_pos == 79){
		LCD_pos = 0;
		//_delay_ms(1000);
		SendCommand(CLEAR_SCREEN);
		SendCommand(0x80);
	}
	
	
	if(received_char =='$'){
		SendCommand(0x80);
		SendCommand(CLEAR_SCREEN);
		SendString("$");  
		//SendCommand(0x80);
		SendCharacter(received_char);
		LCD_pos ++;
		
		GGA_Index = 0;
		CommaCounter = 0;
		IsItGGAString = false;
	}
	else if(IsItGGAString == true){                                             // if true save GGA info. into buffer 
		if(received_char == ',' ) GGA_Pointers[CommaCounter++] = GGA_Index;     // store instances of ',' in buffer 
		GGA_Buffer[GGA_Index++] = received_char;
		SendCharacter(received_char);
		LCD_pos++;
		//_delay_ms(1000);
	}
	else if(GGA_CODE[0] == 'G' && GGA_CODE[1] == 'G' && GGA_CODE[2] == 'A'){    // check for GGA string
		SendCommand(0x80);
		SendString("GGA");
		//SendCommand(0x80+3);
		LCD_pos += 3;
		
		_delay_ms(2000);
			
		IsItGGAString = true;
		GGA_CODE[0] = 0; GGA_CODE[1] = 0; GGA_CODE[2] = 0;
	}
	else{
		GGA_CODE[0] = GGA_CODE[1];  GGA_CODE[1] = GGA_CODE[2]; GGA_CODE[2] = received_char; 
	}
	SREG = oldsrg;
}
