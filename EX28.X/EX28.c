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

unsigned int sel_digito = 0, conta = 0; //Variáveis de seleção de dígitos e contagem
unsigned int dig1, dig2, dig3, dig4;	 /*Variáveis para armazenamento do cálculo de 
                                       dígitos*/

void escreve_7seg(unsigned int num);	 //Protótipo da função escreve_7seg(..)

//Função de tratamento para Int. do TIMER0
void __interrupt(low_priority) int_TMR0(void)   
{
    //Executa a interrupção a cada 5ms, conforme o ajuste inicial para o TIMER 0	
    if (TMR0IF)                 //Se o flag da interrupção for 1 (TMR0IF)
    {
      sel_digito++;			//Incrementa a variável sel_digito	
      if (sel_digito>4) sel_digito = 1;	/*Caso sel_digito seja maior que 4, 
                                                atribui-se o valor 1 a ele*/	      
      switch(sel_digito)			//Verifica o valor de sel_digito
      {
         //Dependendo do valor de sel_digito, executa um dos casos a seguir 
case 1:   PORTD = 0b00001111;	
                   escreve_7seg(digito[dig1]);
                   PORTD = 0b00001110;
              break;
         case 2:   PORTD = 0b00001111;
                   escreve_7seg(digito[dig2]);
                   PORTD = 0b00001101;
              break;
         case 3:   PORTD = 0b00001111;
                   escreve_7seg(digito[dig3]);
                   PORTD = 0b00001011;
              break;
         case 4:   PORTD = 0b00001111;
                   escreve_7seg(digito[dig4]);
                   PORTD = 0b00000111;
              break;
      }
     
    }

     TMR0 = 31;              	     //Retorna valor inicial para o reg. TMR0
     TMR0IF = 0;               	     //Limpa o flag da interrupção (T0IF)
}

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
}

void main(void) {
       
    ADCON1 = 0x0F;          //Desabilita todos os canais A/D
    TRISE = 0b00000000;	//Todos os pinos da PORTA E devem ser de saída
    PORTE = 0b00000000;	//Atribui nível lógico 0 a todos os pinos da PORTA E
    
    TRISD = 0b00000000;	//Todos os pinos da PORTA D devem ser de saída    
    
    INTCON = 0b10100000;   /* GIE/GIEH  = 1  - Habilita interrupção global
                            * PEIE/GIEL = 0 - Não utilizado
                            * TMR0IE = 1 - Habilita interrupção pelo TIMER0
                            * INT0IE = 0 - Não utilizado
                            * RBIE = 0 - Não utilizado
                            * TMR0IF = 0 - Flag de overflow p/ o TIMER0
                            * INT0IF = 0 - Não utilizado
                            * RBIE = 0 - Não utilizado
                            */
    
    T0CON = 0b11000101;    /* TMR0ON = 1 - Habilita TIMER0
                            * T08BIT = 1 - Modo de operação em 8 bits
                            * T0CS = 0 - Incremento pelo ciclo de máquina
                            * T0SE = 0 - Não se aplica
                            * PSA = 0 - Prescaler habilitado
                            * PS2 = 1, PS1 = 0, PS0 = 1 - Prescaler de 1:64
                            */ 
    TMR0 = 31;              	//Valor inicial para o reg. TMR0 para 5ms    
    
    while(1)
    {
        conta++;			//Incrementa a variável conta
        if(conta>9999) conta = 0;	//Caso seja maior que 9999, zera a variável
        seleciona_7seg(conta); 	/*Chama a função selecionar_7seg atribuindo 
  a variável conta*/  
        __delay_ms(1000);		//Gera atraso de 1 segundo        
    }
}

