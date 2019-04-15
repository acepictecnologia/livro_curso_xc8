#include <xc.h>                     //Inclui o arquivo header xc.h
#include <stdio.h>                  //Inclui o arquivo stdio.h

#include "../Bibliotecas/config.h"	//Inclui o arquivo config.h
#include "../Bibliotecas/LCD4b.h"	//Inclui o arquivo lcd4B.h

#define _XTAL_FREQ 8000000		//Define a frequência de clock utilizada

int conta = 0;    			//Varável de contagem
int controle = 0; 			//Variável de controle para LEDs (porta B)

char bufferLCD[16];		/*Matriz para armazenamento da string para o 
                                       LCD*/

void __interrupt() int_EXT(void)   	//Função de tratamento para Int. Externa
{
    if (INT0IF)                   	//Se o flag da interrupção for 1 (INT0IF)
    {
        conta++;                	//Incrementa a variável conta
        if (conta>=10)          	//Quando conta > ou = a 10
        {
            conta = 0;          	//Zera a variável conta
            switch (++controle) 	/*Incrementa a variável controle antes de 
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
                        controle = 0;      //Zera a variável controle.
            }
        }
         INT0IF = 0;               	      //Limpa o flag da interrupção (INT0IF)
    }
}

void main(void)
{
    TRISB = 0b00000001;         /*Direciona o pino 0 da porta B como entrada
                                 e o restante como saída*/
    PORTB = 0b00000000;         //Coloca em 0 todos os pinos da porta B
    ADCON1 = 0x0F;              //Desabilita todos os canais A/D
           
    INTCON = 0b10010000;        /* GIE/GIEH  = 1  - Habilita interrupção global
                                 * PEIE/GIEL = 0 - Não utilizado
                                 * T0IE = 0 - Não utilizado
                                 * INT0IE = 1 - Habilita interrupção externa
                                 * RBIE = 0 - Não utilizado
                                 * T0IF = 0 - Não utilizado
                                 * INT0IF = 0 - Limpa flag para interrupção
                                              externa
                                 * RBIE = 0 - Não utilizado
                                 */
    
    INTCON2 = 0b11000000;       /* RBPU = 1 - Não utilizado
                                 * INTEDG0 = 1 - Interrupção na borda de subida 
                                                 no pino RB0
                                 * Demais bits não utilizados.*/ 
          
    lcd_ini();                  //Inicializa LCD
        
    //Posiciona o cursor na coluna 2 da linha 1 e escreve no LCD
    lcd_escreve_bf(1, 2, "INT. EXTERNA");
    
    //Posiciona o cursor na coluna 2 da linha 2 e escreve na LCD
    lcd_escreve_bf(2, 2, "CONTAGEM: 00");
       
    while(1)                    //Loop principal
    {
        __delay_ms(100);	    //Atraso de 100ms
        
        //Escreve o resultado da variável conta no LCD
        sprintf(bufferLCD, "%02d", conta);
        
        //Posiciona o cursor na coluna 12 da linha 2 e escreve no LCD
        lcd_escreve_bf(2, 12, bufferLCD);
    }
}

