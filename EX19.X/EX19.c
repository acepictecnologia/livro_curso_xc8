#include <xc.h>                     //Inclui o arquivo xc.h
#include <stdio.h>                  //Inclui o arquivo stdio.h

#include "../Bibliotecas/config.h"  		//Inclui o arquivo config.h
#include "../Bibliotecas/LCD4b.h"		//Inclus�o do arquivo LCD4b.h

#define _XTAL_FREQ 8000000		//Define a frequ�ncia de clock utilizada

int T2_1s = 0, conta=0;     /*Vari�veis de controle para o tempo de 1 segundo e
                            de contagem*/ 
char bufferLCD[16];         //Matriz para armazenamento da string para o LCD

void __interrupt() int_TMR2(void)	//Fun��o de tratamento para interrup��o
{
    if (TMR2IF)                 	//Se flag TMR2IF (Interrup��o do TIMER2) = 1
    {
     T2_1s++;                   	//Incrementa a vari�vel T2_1s
     
     if (T2_1s >= 40)           	//Se T2_1s >= 40 (25ms x 40 = 1000ms)
     {
         T2_1s = 0;               	//Zera a vari�vel T2_1s
         conta++;                 	//Incrementa a vari�vel conta
         if (conta > 99) conta = 0;	//Se conta > 99, faz conta = 0;
     }   
        TMR2 = 0;;           	//Retorna o valor incial ao reg. TMR2
        
        TMR2IF = 0;          	//Limpa o flag da interrup��o do TIMER2
    }
}

void main(void)
{   
    ADCON1 = 0x0F;              //Desabilita todos os canais A/D
    
    INTCON = 0b11000000;        /* GIE = 1  - Habilita interrup��o global
                                 * PEIE = 1 - Habilita interrup��o de 
                                              perif�ricos
                                 * T0IE = 0 - N�o utilizado
                                 * INTE = 0 - N�o utilizado
                                 * RBIE = 0 - N�o utilizado
                                 * T0IF = 0 - N�o utilizado
                                 * INTF = 0 - N�o utilizado
                                 * RBIE = 0 - N�o utilizado
                                 */
    
    T2CON = 0b01100111;          /* -  = 0 - N�o se aplica
                                 * TOUTPS<3:0> = 1100 - Postscaler de 1:13
                                 * TMR2ON = 1 - Habilita m�dulo Timer 2
                                 * T2CKPS<1:0> = 11 - Prescaler de 1:16
                                 */
    
    PR2 = 240;                  //Atribui-se o 240 ao reg. PR2

    PIE1bits.TMR2IE = 1;	    //Habilita a interrup��o para o m�dulo TIMER2
    
    TMR2 = 0;                   //Atribui-se o valor 0 ao reg. TMR2
    
    lcd_ini();                  //Inicializa LCD
        
    //Posiciona o cursor na coluna 6 da linha 1 e escreve no LCD
    lcd_escreve_bf(1, 6, "TIMER2");     
    
    //Posiciona o cursor na coluna 8 da linha 2 e escreve no LCD
    lcd_escreve_bf(2, 8, "00");     
       
    while(1)                        //Loop principal
    {
        __delay_ms(300);            //Atraso de 300ms
                   
        //Escreve a vari�vel conta na matriz bufferLCD  
        sprintf(bufferLCD, "%02d", conta);     
        
        //Posiciona o cursor na coluna 8 da linha 2 e escreve no LCD
        lcd_escreve_bf(2, 8, bufferLCD);     
    }
}

