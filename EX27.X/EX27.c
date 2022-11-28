#include <xc.h>                     	//Inclui o arquivo xc.h

#include "../Bibliotecas/config.h"   //Inclui o arquivo config.h

#define _XTAL_FREQ 8000000      	//Define a frequência de clock utilizada

/*Matriz de 10 elementos com os valores correspondente a cada dígito de 0 a 9 para displays de cátodo comum*/
unsigned int digito[10] = {
                0b00111111,    //Dígito 0
                0b00000110,    //Dígito 1
                0b01011011,    //Dígito 2
                0b01001111,    //Dígito 3
                0b01100110,    //Dígito 4
                0b01101101,    //Dígito 5
                0b01111101,    //Dígito 6
                0b00000111,    //Dígito 7
                0b01111111,    //Dígito 8
                0b01101111     //Dígito 9 
                };

unsigned int tempo = 0, conta = 0;	//Variáveis de controle de tempo e contagem
unsigned int dig1, dig2, dig3, dig4; /*Variáveis para armazenamento do cálculo de 
                                       dígitos*/ 

void escreve_7seg(unsigned int num)
{
    unsigned int j;
    
    for(j = 0x80; j > 0; j = j >> 1)
    {
        // Armazena os dados de num através do 
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
    dig1 = (dig / 1000); 	/*Atribui à variável dig1 o valor do cálculo             
		  para milhar da contagem*/
    dig2 = (dig / 100) % 10;	/*Atribui à variável dig2 o valor do cálculo             
		  para centena da contagem*/
    dig3 = (dig / 10) % 10;	/*Atribui à variável dig3 o valor do cálculo             
		  para dezena da contagem*/
    dig4 = dig % 10;	/*Atribui à variável dig1 o valor do cálculo             
		  para dezena da contagem*/

    
    PORTD = 0b00001111;		/*Atribui nível lógico 1 aos pinos 1, 2, 3 e 
				  4, assim, todos os displays permanecerão 
                                       desligados*/

    escreve_7seg(digito[dig1]);	/*Chama a função escreve_7seg com o atributo       
				  contendo o valor correspondente à variável 
				  dig1 que deverá ser entre 0 e 9 para exibir 
 				  no display 1*/

    PORTD = 0b00001110;		/*Atribui nível lógico 0 ao pino 0 da porta 
				  D e nível lógico 1 aos pinos 1, 2, e 3, 
                                       assim, habilita-se somente o primeiro 
                                       display para exibição enquanto os 
                                       demais permanecerão desligados*/

    __delay_ms(5);			//Gera atraso de 5ms
        
    PORTD = 0b00001111;		/*Atribui nível lógico 1 aos pinos 1, 2, 3 e 
				  4, assim, todos os displays permanecerão 
                                       desligados*/

    escreve_7seg(digito[dig2]);	/*Chama a função escreve_7seg com o atributo       
				  contendo o valor correspondente à variável 
				  dig2 que deverá ser entre 0 e 9 para exibir 
 				  no display 2*/

    PORTD = 0b00001101;		/*Atribui nível lógico 0 ao pino 1 da porta 
				  D e nível lógico 1 aos pinos 0, 2, e 3, 
                                       assim, habilita-se somente o segundo 
                                       display para exibição enquanto os 
                                       demais permanecerão desligados*/

    __delay_ms(5);			//Gera atraso de 5ms
        
    PORTD = 0b00001111;		/*Atribui nível lógico 1 aos pinos 1, 2, 3 e 
				  4, assim, todos os displays permanecerão 
                                       desligados*/

    escreve_7seg(digito[dig3]);	/*Chama a função escreve_7seg com o atributo       
				  contendo o valor correspondente à variável 
				  dig3 que deverá ser entre 0 e 9 para exibir 
 				  no display 3*/

    PORTD = 0b00001011;		/*Atribui nível lógico 0 ao pino 2 da porta 
				  D e nível lógico 1 aos pinos 0, 1, e 3, 
                                       assim, habilita-se somente o segundo 
                                       display para exibição enquanto os 
                                       demais permanecerão desligados*/

    __delay_ms(5);			//Gera atraso de 5ms
        
    PORTD = 0b00001111;		/*Atribui nível lógico 1 aos pinos 1, 2, 3 e 
				  4, assim, todos os displays permanecerão 
                                       desligados*/

    escreve_7seg(digito[dig4]);	/*Chama a função escreve_7seg com o atributo       
				  contendo o valor correspondente à variável 
				  dig4 que deverá ser entre 0 e 9 para exibir 
 				  no display 4*/
    PORTD = 0b00000111;		/*Atribui nível lógico 1 aos pinos 1, 2, 3 e 
				  4, assim, todos os displays permanecerão 
                                       desligados*/
    __delay_ms(5);			//Gera atraso de 5ms
}

void main(void) {
       
    ADCON1 = 0x0F;          //Desabilita todos os canais A/D
    TRISE = 0b00000000;	//Todos os pinos da PORTA E devem ser de saída
    PORTE = 0b00000000;	//Atribui nível lógico 0 a todos os pinos da PORTA E
    
    TRISD = 0b00000000;	//Todos os pinos da PORTA D devem ser de saída    
   
    while(1)
    {
        tempo++;			//Incrementa a variável tempo
        
        if(tempo >= 50)		//Se tempo >= 50 (50 x 20ms = 1000ms)
        {
            conta++;		//Incrementa a variável conta
            if(conta > 9999 ) 	//Se conta > 9999
		conta = 0;	//Zera a variável conta
            tempo = 0;		//Zera a variável tempo
        }    
            seleciona_7seg(conta);	/*Chama a função seleciona_7seg com o valor 
                                       da variável conta como atributo*/
                
    }
}
