#include <xc.h>

#include "config.h"		//Inclui o arquivo config.h

#define _XTAL_FREQ 8000000      	//Define a frequência de clock utilizada

void main(void)
{
    TRISB = 0b00000000; 	//Configura os pinos da porta B como saída
    PORTB = 0b00000000; 	//Coloca toda porta B em nível lógico 0

    while(1)
    {
     PORTB = ~PORTB;    	/* Alterna todos os pinos da porta D entre nível lógico 
                            1 e nível lógico 0*/
     
     __delay_ms(500);    	//Atraso de 500ms   
    }
}
