#include <xc.h>                     	//Inclui o arquivo xc.h

#include "../Bibliotecas/config.h"   //Inclui o arquivo config.h

#define _XTAL_FREQ 8000000      	//Define a frequ�ncia de clock utilizada

void escreve_7seg(unsigned int num)
{
    unsigned int j;		//Declara��o da vari�vel j
    
    for(j = 0x80; j > 0; j = j >> 1)
    {
        // Armazena os dados de num atrav�s do 
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
}

void main(void) {
       
    ADCON1 = 0x0F;          //Desabilita todos os canais A/D
    TRISE = 0b00000000;	//Todos os pinos da PORTA E devem ser de sa�da
    PORTE = 0b00000000;	//Atribui n�vel l�gico 0 a todos os pinos da PORTA E
    
    TRISD = 0b00000000;	//Todos os pinos da PORTA D devem ser de sa�da    
    
    while(1)
    {
        PORTD = 0b00001110;		/*Atribui n�vel l�gico 0 ao pino 0 da porta 
				  D e n�vel l�gico 1 aos pinos 1, 2, e 3, 
                                       assim, habilita-se somente o primeiro 
                                       display para exibi��o enquanto os 
                                       demais permanecer�o desligados*/

        
        escreve_7seg(0b10111111); 	/*Chama a fun��o escreve_7seg com o atributo       
				contendo o c�digo que deve representar o 
				n�mero 0 no display (vide tabela 14.2)*/

        
        __delay_ms(5);		//Gera atraso de 5ms
        
        PORTD = 0b00001101;		/*Atribui n�vel l�gico 0 ao pino 1 da porta 
				  D e n�vel l�gico 1 aos pinos 0, 2, e 3, 
                                       assim, habilita-se somente o segundo 
                                       display para exibi��o enquanto os 
                                       demais permanecer�o desligados*/
        
        escreve_7seg(0b10000110);	/*Chama a fun��o escreve_7seg com o atributo       
				contendo o c�digo que deve representar o 
				n�mero 1 no display (vide tabela 14.2)*/
        
        __delay_ms(5);		//Gera atraso de 5ms
        
        PORTD = 0b00001011;		/*Atribui n�vel l�gico 0 ao pino 2 da porta 
				  D e n�vel l�gico 1 aos pinos 0, 1, e 3, 
                                       assim, habilita-se somente o terceiro 
                                       display para exibi��o enquanto os 
                                       demais permanecer�o desligados*/

        
        escreve_7seg(0b11011011);	/*Chama a fun��o escreve_7seg com o atributo       
				contendo o c�digo que deve representar o 
				n�mero 2 no display (vide tabela 14.2)*/
        
        __delay_ms(5);		//Gera atraso de 5ms
        
        PORTD = 0b00000111;		/*Atribui n�vel l�gico 0 ao pino 3 da porta 
				  D e n�vel l�gico 1 aos pinos 0, 1, e 2, 
                                       assim, habilita-se somente o quarto 
                                       display para exibi��o enquanto os 
                                       demais permanecer�o desligados*/

        
        escreve_7seg(0b11001111); 	/*Chama a fun��o escreve_7seg com o atributo       
				contendo o c�digo que deve representar o 
				n�mero 3 no display (vide tabela 14.2)*/
	
        
        __delay_ms(5);		//Gera atraso de 5ms
        
    }
}  
