#include <xc.h>

#include "config.h"		//Inclui o arquivo config.h

#define _XTAL_FREQ 8000000      	//Define a frequ�ncia de clock utilizada

void main(void)
{
    TRISB = 0b00000000; 	//Configura os pinos da porta B como sa�da
    PORTB = 0b00000000; 	//Coloca toda porta B em n�vel l�gico 0

    while(1)
    {
     PORTB = ~PORTB;    	/* Alterna todos os pinos da porta D entre n�vel l�gico 
                            1 e n�vel l�gico 0*/
     
     __delay_ms(500);    	//Atraso de 500ms   
    }
}
