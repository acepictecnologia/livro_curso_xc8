#include <xc.h>                     	//Inclui o arquivo xc.h

#include "../Bibliotecas/config.h"   //Inclui o arquivo config.h

#define _XTAL_FREQ 8000000      	//Define a frequ�ncia de clock utilizada

/*Matriz de 10 elementos com os valores correspondente a cada d�gito de 0 a 9 para displays de c�todo comum*/
unsigned int digito[10] = {
                0b00111111,    //D�gito 0
                0b00000110,    //D�gito 1
                0b01011011,    //D�gito 2
                0b01001111,    //D�gito 3
                0b01100110,    //D�gito 4
                0b01101101,    //D�gito 5
                0b01111101,    //D�gito 6
                0b00000111,    //D�gito 7
                0b01111111,    //D�gito 8
                0b01101111     //D�gito 9 
                };

unsigned int tempo = 0, conta = 0;	//Vari�veis de controle de tempo e contagem
unsigned int dig1, dig2, dig3, dig4; /*Vari�veis para armazenamento do c�lculo de 
                                       d�gitos*/ 

void escreve_7seg(unsigned int num)
{
    unsigned int j;
    
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

void seleciona_7seg(unsigned int dig)
{
    dig1 = (dig / 1000); 	/*Atribui � vari�vel dig1 o valor do c�lculo             
		  para milhar da contagem*/
    dig2 = (dig / 100) % 10;	/*Atribui � vari�vel dig2 o valor do c�lculo             
		  para centena da contagem*/
    dig3 = (dig / 10) % 10;	/*Atribui � vari�vel dig3 o valor do c�lculo             
		  para dezena da contagem*/
    dig4 = dig % 10;	/*Atribui � vari�vel dig1 o valor do c�lculo             
		  para dezena da contagem*/

    
    PORTD = 0b00001111;		/*Atribui n�vel l�gico 1 aos pinos 1, 2, 3 e 
				  4, assim, todos os displays permanecer�o 
                                       desligados*/

    escreve_7seg(digito[dig1]);	/*Chama a fun��o escreve_7seg com o atributo       
				  contendo o valor correspondente � vari�vel 
				  dig1 que dever� ser entre 0 e 9 para exibir 
 				  no display 1*/

    PORTD = 0b00001110;		/*Atribui n�vel l�gico 0 ao pino 0 da porta 
				  D e n�vel l�gico 1 aos pinos 1, 2, e 3, 
                                       assim, habilita-se somente o primeiro 
                                       display para exibi��o enquanto os 
                                       demais permanecer�o desligados*/

    __delay_ms(5);			//Gera atraso de 5ms
        
    PORTD = 0b00001111;		/*Atribui n�vel l�gico 1 aos pinos 1, 2, 3 e 
				  4, assim, todos os displays permanecer�o 
                                       desligados*/

    escreve_7seg(digito[dig2]);	/*Chama a fun��o escreve_7seg com o atributo       
				  contendo o valor correspondente � vari�vel 
				  dig2 que dever� ser entre 0 e 9 para exibir 
 				  no display 2*/

    PORTD = 0b00001101;		/*Atribui n�vel l�gico 0 ao pino 1 da porta 
				  D e n�vel l�gico 1 aos pinos 0, 2, e 3, 
                                       assim, habilita-se somente o segundo 
                                       display para exibi��o enquanto os 
                                       demais permanecer�o desligados*/

    __delay_ms(5);			//Gera atraso de 5ms
        
    PORTD = 0b00001111;		/*Atribui n�vel l�gico 1 aos pinos 1, 2, 3 e 
				  4, assim, todos os displays permanecer�o 
                                       desligados*/

    escreve_7seg(digito[dig3]);	/*Chama a fun��o escreve_7seg com o atributo       
				  contendo o valor correspondente � vari�vel 
				  dig3 que dever� ser entre 0 e 9 para exibir 
 				  no display 3*/

    PORTD = 0b00001011;		/*Atribui n�vel l�gico 0 ao pino 2 da porta 
				  D e n�vel l�gico 1 aos pinos 0, 1, e 3, 
                                       assim, habilita-se somente o segundo 
                                       display para exibi��o enquanto os 
                                       demais permanecer�o desligados*/

    __delay_ms(5);			//Gera atraso de 5ms
        
    PORTD = 0b00001111;		/*Atribui n�vel l�gico 1 aos pinos 1, 2, 3 e 
				  4, assim, todos os displays permanecer�o 
                                       desligados*/

    escreve_7seg(digito[dig4]);	/*Chama a fun��o escreve_7seg com o atributo       
				  contendo o valor correspondente � vari�vel 
				  dig4 que dever� ser entre 0 e 9 para exibir 
 				  no display 4*/
    PORTD = 0b00000111;		/*Atribui n�vel l�gico 1 aos pinos 1, 2, 3 e 
				  4, assim, todos os displays permanecer�o 
                                       desligados*/
    __delay_ms(5);			//Gera atraso de 5ms
}

void main(void) {
       
    ADCON1 = 0x0F;          //Desabilita todos os canais A/D
    TRISE = 0b00000000;	//Todos os pinos da PORTA E devem ser de sa�da
    PORTE = 0b00000000;	//Atribui n�vel l�gico 0 a todos os pinos da PORTA E
    
    TRISD = 0b00000000;	//Todos os pinos da PORTA D devem ser de sa�da    
   
    while(1)
    {
        tempo++;			//Incrementa a vari�vel tempo
        
        if(tempo >= 50)		//Se tempo >= 50 (50 x 20ms = 1000ms)
        {
            conta++;		//Incrementa a vari�vel conta
            if(conta > 9999 ) 	//Se conta > 9999
		conta = 0;	//Zera a vari�vel conta
            tempo = 0;		//Zera a vari�vel tempo
        }    
            seleciona_7seg(conta);	/*Chama a fun��o seleciona_7seg com o valor 
                                       da vari�vel conta como atributo*/
                
    }
}
