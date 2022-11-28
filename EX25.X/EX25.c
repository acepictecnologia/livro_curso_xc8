#include <xc.h>                     	//Inclui o arquivo xc.h

#include "../Bibliotecas/config.h"   //Inclui o arquivo config.h

#define _XTAL_FREQ 8000000      	//Define a frequ�ncia de clock utilizada

void main(void) {
    
    unsigned int j;		//Declara��o da vari�vel j
    unsigned int num = 0b10111111;	/*Declara��o da vari�vel num contendo o 
                                       c�digo que deve representar o n�mero 0 no 
                                       display, considerando o display de c�todo 
                                       comum (vide tabela 14.2)*/
    
    ADCON1 = 0x0F;          //Desabilita todos os canais A/D
    TRISE = 0b00000000;	//Todos os pinos da PORTA E devem ser de sa�da
    PORTE = 0b00000000;	//Atribui n�vel l�gico 0 a todos os pinos da PORTA E
    
    TRISD = 0b00000000;	//Todos os pinos da PORTA D devem ser de sa�da
    PORTD = 0b00001110;	/*Atribui n�vel l�gico 0 ao pino 0 da porta D e n�vel 
                             l�gico 1 aos pinos 1, 2, e 3, assim, habilita-se 
                             somente o primeiro display para exibi��o enquanto os 
                             demais permanecer�o desligados*/
    
    while(1)
    {
        for(j = 0x80; j > 0; j = j >> 1)
        {
            // Armazena os dados da vari�vel num atrav�s do 
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

