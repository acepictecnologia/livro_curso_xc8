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

unsigned int sel_digito = 0, conta = 0; //Vari�veis de sele��o de d�gitos e contagem
unsigned int dig1, dig2, dig3, dig4;	 /*Vari�veis para armazenamento do c�lculo de 
                                       d�gitos*/

void escreve_7seg(unsigned int num);	 //Prot�tipo da fun��o escreve_7seg(..)

//Fun��o de tratamento para Int. do TIMER0
void __interrupt(low_priority) int_TMR0(void)   
{
    //Executa a interrup��o a cada 5ms, conforme o ajuste inicial para o TIMER 0	
    if (TMR0IF)                 //Se o flag da interrup��o for 1 (TMR0IF)
    {
      sel_digito++;			//Incrementa a vari�vel sel_digito	
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
     TMR0IF = 0;               	     //Limpa o flag da interrup��o (T0IF)
}

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
}

void main(void) {
       
    ADCON1 = 0x0F;          //Desabilita todos os canais A/D
    TRISE = 0b00000000;	//Todos os pinos da PORTA E devem ser de sa�da
    PORTE = 0b00000000;	//Atribui n�vel l�gico 0 a todos os pinos da PORTA E
    
    TRISD = 0b00000000;	//Todos os pinos da PORTA D devem ser de sa�da    
    
    INTCON = 0b10100000;   /* GIE/GIEH  = 1  - Habilita interrup��o global
                            * PEIE/GIEL = 0 - N�o utilizado
                            * TMR0IE = 1 - Habilita interrup��o pelo TIMER0
                            * INT0IE = 0 - N�o utilizado
                            * RBIE = 0 - N�o utilizado
                            * TMR0IF = 0 - Flag de overflow p/ o TIMER0
                            * INT0IF = 0 - N�o utilizado
                            * RBIE = 0 - N�o utilizado
                            */
    
    T0CON = 0b11000101;    /* TMR0ON = 1 - Habilita TIMER0
                            * T08BIT = 1 - Modo de opera��o em 8 bits
                            * T0CS = 0 - Incremento pelo ciclo de m�quina
                            * T0SE = 0 - N�o se aplica
                            * PSA = 0 - Prescaler habilitado
                            * PS2 = 1, PS1 = 0, PS0 = 1 - Prescaler de 1:64
                            */ 
    TMR0 = 31;              	//Valor inicial para o reg. TMR0 para 5ms    
    
    while(1)
    {
        conta++;			//Incrementa a vari�vel conta
        if(conta>9999) conta = 0;	//Caso seja maior que 9999, zera a vari�vel
        seleciona_7seg(conta); 	/*Chama a fun��o selecionar_7seg atribuindo 
  a vari�vel conta*/  
        __delay_ms(1000);		//Gera atraso de 1 segundo        
    }
}

