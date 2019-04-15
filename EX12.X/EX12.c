#include <xc.h>                     //Inclui o arquivo header xc.h
#include <stdio.h>                  //Inclui o arquivo stdio.h

#include "../Bibliotecas/config.h"	//Inclui o arquivo config.h
#include "../Bibliotecas/LCD4b.h"	//Inclui o arquivo lcd4B.h

#define _XTAL_FREQ 8000000		//Define a frequ�ncia de clock utilizada

int conta = 0;    			//Var�vel de contagem
int controle = 0; 			//Vari�vel de controle para LEDs (porta B)

char bufferLCD[16];		/*Matriz para armazenamento da string para o 
                                       LCD*/

void __interrupt() int_EXT(void)   	//Fun��o de tratamento para Int. Externa
{
    if (INT0IF)                   	//Se o flag da interrup��o for 1 (INT0IF)
    {
        conta++;                	//Incrementa a vari�vel conta
        if (conta>=10)          	//Quando conta > ou = a 10
        {
            conta = 0;          	//Zera a vari�vel conta
            switch (++controle) 	/*Incrementa a vari�vel controle antes de 
 				  ser testada*/
            {
                case 1: PORTBbits.RB4 = 1; //Caso seja 1, liga o LED do pino RB4
                break;
                case 2: PORTBbits.RB5 = 1; //Caso seja 2, liga o LED do pino RB5
                break;
                case 3: PORTBbits.RB6 = 1; //Caso seja 3, liga o LED do pino RB6
                break;
                case 4: PORTBbits.RB7 = 1; //Caso seja 4, liga o LED do pino RB7
                break;
                case 5: PORTB = 0b00000000; //Caso seja 5, apaga todos os LEDs
                        controle = 0;      //Zera a vari�vel controle.
            }
        }
         INT0IF = 0;               	      //Limpa o flag da interrup��o (INT0IF)
    }
}

void main(void)
{
    TRISB = 0b00000001;         /*Direciona o pino 0 da porta B como entrada
                                 e o restante como sa�da*/
    PORTB = 0b00000000;         //Coloca em 0 todos os pinos da porta B
    ADCON1 = 0x0F;              //Desabilita todos os canais A/D
           
    INTCON = 0b10010000;        /* GIE/GIEH  = 1  - Habilita interrup��o global
                                 * PEIE/GIEL = 0 - N�o utilizado
                                 * T0IE = 0 - N�o utilizado
                                 * INT0IE = 1 - Habilita interrup��o externa
                                 * RBIE = 0 - N�o utilizado
                                 * T0IF = 0 - N�o utilizado
                                 * INT0IF = 0 - Limpa flag para interrup��o
                                              externa
                                 * RBIE = 0 - N�o utilizado
                                 */
    
    INTCON2 = 0b11000000;       /* RBPU = 1 - N�o utilizado
                                 * INTEDG0 = 1 - Interrup��o na borda de subida 
                                                 no pino RB0
                                 * Demais bits n�o utilizados.*/ 
          
    lcd_ini();                  //Inicializa LCD
        
    //Posiciona o cursor na coluna 2 da linha 1 e escreve no LCD
    lcd_escreve_bf(1, 2, "INT. EXTERNA");
    
    //Posiciona o cursor na coluna 2 da linha 2 e escreve na LCD
    lcd_escreve_bf(2, 2, "CONTAGEM: 00");
       
    while(1)                    //Loop principal
    {
        __delay_ms(100);	    //Atraso de 100ms
        
        //Escreve o resultado da vari�vel conta no LCD
        sprintf(bufferLCD, "%02d", conta);
        
        //Posiciona o cursor na coluna 12 da linha 2 e escreve no LCD
        lcd_escreve_bf(2, 12, bufferLCD);
    }
}

