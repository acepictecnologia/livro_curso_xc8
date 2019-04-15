/*
 * File:   EX02.c
 * Author: Sandrini
 *
 * Created on 2 de Abril de 2019, 07:50
 */


#include <xc.h>

#include "../Bibliotecas/config.h" 

#define _XTAL_FREQ 8000000      	//Define a frequência de clock utilizada

void main(void)
{
    TRISB = 0b00000000; 	//Configura os pinos da porta B como saída
    PORTB = 0b00000000; 	//Coloca toda porta B em nível lógico 0
    
    TRISBbits.RB0 = 1;  	//Configura o pino 0 da porta B como entrada
    TRISCbits.RC0 = 1;  	//Configura o pino 0 da porta C como entrada
    TRISAbits.RA4 = 1;  	//Configura o pino 4 da porta A como entrada
    
    while(1)
    {
        if (PORTBbits.RB0 == 1)     //Se B1 for pressionado
        {
            PORTBbits.RB5 ^= 1;     //Inverte o estado do pino 5 da porta B
            while (PORTBbits.RB0);  //Enquanto B1 estiver pressionado, aguarda
        }       
        if (PORTCbits.RC0 == 1)     //Se B2 for pressionado
        {
            PORTBbits.RB6 ^= 1;     //Inverte o estado do pino 6 da porta B
            while (PORTCbits.RC0);  //Enquanto B2 estiver pressionado, aguarda
        }
        if (PORTAbits.RA4 == 1)     //Se B3 for pressionado 
        {
            PORTBbits.RB7 ^= 1;     //Inverte o estado do pino 7 da porta B
            while (PORTAbits.RA4);  //Enquanto B3 estiver pressionado, aguarda
        }
        __delay_ms(50);             //Atraso de 50ms
    }
}

