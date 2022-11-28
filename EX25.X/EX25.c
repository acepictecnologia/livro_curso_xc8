#include <xc.h>                     	//Inclui o arquivo xc.h

#include "../Bibliotecas/config.h"   //Inclui o arquivo config.h

#define _XTAL_FREQ 8000000      	//Define a frequência de clock utilizada

void main(void) {
    
    unsigned int j;		//Declaração da variável j
    unsigned int num = 0b10111111;	/*Declaração da variável num contendo o 
                                       código que deve representar o número 0 no 
                                       display, considerando o display de cátodo 
                                       comum (vide tabela 14.2)*/
    
    ADCON1 = 0x0F;          //Desabilita todos os canais A/D
    TRISE = 0b00000000;	//Todos os pinos da PORTA E devem ser de saída
    PORTE = 0b00000000;	//Atribui nível lógico 0 a todos os pinos da PORTA E
    
    TRISD = 0b00000000;	//Todos os pinos da PORTA D devem ser de saída
    PORTD = 0b00001110;	/*Atribui nível lógico 0 ao pino 0 da porta D e nível 
                             lógico 1 aos pinos 1, 2, e 3, assim, habilita-se 
                             somente o primeiro display para exibição enquanto os 
                             demais permanecerão desligados*/
    
    while(1)
    {
        for(j = 0x80; j > 0; j = j >> 1)
        {
            // Armazena os dados da variável num através do 
            // pino 14 (Serial Data Input A) do 74HC595 
            if(num & j)
                PORTEbits.RE0 = 1;
            else
                PORTEbits.RE0 = 0;
            
            //Gera sinal de clock no pino 11 do 74HC595
            PORTEbits.RE1 = 1;
            PORTEbits.RE1 = 0;
        }
        
        //Habilita a passagem dos dados para os pinos Q0 a Q7 do 74HC595
        PORTEbits.RE2 = 1;
        PORTEbits.RE2 = 0;
        
        __delay_ms(3000);	//Gera um atraso de 3000 ms
    }
}

