#include <xc.h>                     		//Inclui o arquivo xc.h
#include <stdio.h>                  		//Inclui o arquivo stdio.h

#include "../Bibliotecas/config.h"  		//Inclui o arquivo config.h
#include "../Bibliotecas/LCD4b.h"		//Inclui o arquivo LCD4b.h

#define _XTAL_FREQ 8000000		//Define a frequência de clock utilizada

int T1_cnt = 0;     	    //Varável de contagem
char bufferLCD[16];         //Matriz para armazenamento da string para o LCD

void __interrupt() int_TMR(void)   //Função de tratamento para interrupções
{    
    if (TMR1IF)                //Se o flag TMR1IF (Interrupção do TIMER1) for 1
    {
     T1_cnt++;                 //Incrementa a variável T1_cnt
     if (T1_cnt >= 100)        //Se T1_cnt >= 100
         T1_cnt = 0;           //Zera a variável T1_cnt
    
    TMR1H = 0xFF;              //Retorna os valores inciais aos registradores
    TMR1L = 0xF4;              //de contagem do módulo TIMER1
    TMR1IF = 0;                //Limpa o flag da interrupção do TIMER1
    }
}

void main(void)
{
    TRISB = 0b00000000;         //Direciona os pinos da porta B como saída
    PORTB = 0b00000000;         //Coloca em 0 todos os pinos da porta B
    ADCON1 = 0x0F;              //Desabilita todos os canais A/D
    
    INTCON = 0b11000000;        /* GIE = 1  - Habilita interrupção global
                                 * PEIE = 1 - Habilita interrupção de periféricos
                                 * T0IE = 0 - Não utilizado
                                 * INTE = 0 - Não utilizado
                                 * RBIE = 0 - Não utilizado
                                 * T0IF = 0 - Não utilizado
                                 * INTF = 0 - Não utilizado
                                 * RBIE = 0 - Não utilizado
                                 */
    
    T1CON = 0b00000111;          /* T1GINV = 0 - Não se aplica
                                  * TMR1GE = 0 - Não se aplica
                                  * T1CKPS1 e T1CKPS0 = 0 - Prescaler de 1:1
                                  * T1OSCEN = 0 - Não se aplica
                                  * T1SYNC = 1 - Não se aplica
                                  * TMR1CS = 1 - Fonte de clock pelo pino T1CKI
                                  * TMR1ON = 1 - Módulo TIMER1 habilitado
                                  */

    PIE1bits.TMR1IE = 1;	     //Habilita a interrupção para o módulo TIMER1
    
    TMR1H = 0xFF;                //Valor inicial para os registradores de contagem
    TMR1L = 0xF4;               //Do módulo TIMER1 = Equivalente a 3036
    
    lcd_ini();                  //Inicializa LCD
    
    //Posiciona o cursor na coluna 6 da linha 1 e escreve no LCD        
    lcd_escreve_bf(1, 6,"TIMER1"); 
    
    //Posiciona o cursor na coluna 8 da linha 2 e escreve no LCD
    lcd_escreve_bf(2, 8, "00");     
       
    while(1)                    //Loop principal
    {
        __delay_ms(500);          //Atraso de 500ms
        
        PORTBbits.RB0 = ~PORTBbits.RB0; 	//Inverte o estado do pino RD0
               
        //Escreve a variável T1_cnt na matriz bufferLCD  
        sprintf(bufferLCD, "%02d", T1_cnt); //Escreve no LCD  
        
        //Posiciona o cursor na coluna 8 da linha 2 e escreve no LCD
        lcd_escreve_bf(2, 8, bufferLCD); 
    }
}

