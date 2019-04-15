#include <xc.h>                     		//Inclui o arquivo xc.h

#include <stdio.h>                  		//Inclui o arquivo stdio.h

#include "../Bibliotecas/config.h"  		//Inclui o arquivo config.h
#include "../Bibliotecas/LCD4b.h"		//Inclui o arquivo LCD4b.h

int T0_10s = 0;              //Vari�vel pra controle do tempo em 10s
int conta5s = 0, conta10s;   //Vari�veis de contagem
char bufferLCD[16];         //Matriz para armazenamento da string para o LCD

//Fun��o de tratamento para Int. do TIMER0
void __interrupt(low_priority) int_TMR0(void)   
{
    if (TMR0IF)                   	//Se o flag da interrup��o for 1 (TMR0IF)
    {
        conta5s++;                  //Incrementa a vari�vel conta5s
        T0_10s++;                   //Incrementa a vari�vel T0_10s
        if (T0_10s>=2)              //se T0_10s >= 2
        {
            T0_10s=0;               //zera a vari�vel t0_10s
            conta10s++;             //Incrementa a vari�vel conta10s
         }
        if (conta5s>=100) conta5s=0; 	//Se conta5s >= 100, zera conta5s
        if (conta10s>=50) conta10s=0; 	//Se conta10s >= 50, zera conta10s
     }
     TMR0 = 26474;              	    //Retorna valor inicial para o reg. TMR0
     TMR0IF = 0;               	    //Limpa o flag da interrup��o (T0IF)    
}

void main(void)
{
    TRISBbits.TRISB0 = 0;       //Direciona o pino 0 da porta B como sa�da
    PORTBbits.RB0 = 0;          //Coloca em 0 todo o pino 0 da porta B
    ADCON1 = 0x0F;              //Desabilita todos os canais A/D
    
    INTCON = 0b10100000;        /* GIE/GIEH  = 1  - Habilita interrup��o global
                                 * PEIE/GIEL = 0 - N�o utilizado
                                 * TMR0IE = 1 - Habilita interrup��o pelo TIMER0
                                 * INT0IE = 0 - N�o utilizado
                                 * RBIE = 0 - N�o utilizado
                                 * TMR0IF = 0 - Flag de overflow p/ o TIMER0
                                 * INT0IF = 0 - N�o utilizado
                                 * RBIE = 0 - N�o utilizado */
    
    T0CON = 0b10000111;         /* TMR0ON = 1 - Habilita TIMER0
                                 * T08BIT = 0 - Modo de opera��o em 16 bits
                                 * T0CS = 0 - Incremento pelo ciclo de m�quina
                                 * T0SE = 0 - N�o se aplica
                                 * PSA = 0 - Prescaler habilitado
                                 * PS2, PS1, PS0 = 1 - Prescaler de 1:256*/ 
    
    TMR0 = 26474;                //Valor inicial para o reg. TMR0
    
    lcd_ini();                   //Inicializa LCD
        
    //Posiciona o cursor na coluna 1 da linha 1 e escreve no LCD    
    lcd_escreve_bf(1, 1, "CONTA 5s : 00");              
    
    //Posiciona o cursor na coluna 1 da linha 2
    lcd_escreve_bf(2, 1, "CONTA 10s: 00");     
       
    while(1)                     //Loop principal
    {
        __delay_ms(500);                   //Atraso de 500ms
        
        PORTBbits.RB0 = ~PORTBbits.RB0;  //Inverte o estado do pino 0 da porta B
        
        //Escreve na vari�vel conta na matriz bufferLCD
        sprintf(bufferLCD, "%02d", conta5s);     
        
        //Posiciona o cursor na coluna 12 da linha 1 e escreve no LCD
        lcd_escreve_bf(1, 12, bufferLCD);
                 
        //Escreve na vari�vel conta na matriz bufferLCD
        sprintf(bufferLCD, "%02d", conta10s);   
        
        //Posiciona o cursor na coluna 12 da linha 2 e escreve no LCD
        lcd_escreve_bf(2, 12, bufferLCD);
    }
}
