/*
 * Dot_Matrix.c
 *
 * Created: 6/24/2018 4:49:34 PM
 * Author : Awsaf
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	MCUCSR = (1<<JTD);  MCUCSR = (1<<JTD); //Turninng JTAG OFF for IO use of PORT C
	 
	DDRA = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x00;
	
	//int rows[8] = {PORTA0 , PORTA1 , PORTA2,PORTA3,PORTA4,PORTA5,PORTA6,PORTA7};
	//int col[8] = {PORTC0 , PORTC1 , PORTC2,PORTC3,PORTC4,PORTC5,PORTC6,PORTC7};
	
	//int val[8] =  {1,2,4,8,16,32,64,128};
	PORTA = 0xFF;
	//int i =0;
	//int j = 64;
	
    while (1) 
    {
		/*for (int k = 0 ; k< 200 ; k++)
		{
			for (int n = 0 ; n< 8 ; n++)
			{
				PORTA = val[n];
			}
		}
		//PORTA = i;
		PORTC = j;
		
		if (i == 64)
		{
			i=0;
		}
		else{
			i++;
		}
		if (j == 0)
		{
			j=64;
		}
		else if(j != i){
			j--;
		}
		
		
		_delay_ms(200);
		*/
    }
}

