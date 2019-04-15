#include <xc.h>                     		//Inclui o arquivo xc.h
#include <stdio.h>                  		//Inclui o arquivo stdio.h

#include "../Bibliotecas/config.h"  		//Inclui o arquivo config.h
#include "../Bibliotecas/LCD4b.h"		//Inclui o arquivo LCD4b.h

int T0_500ms = 0, T1_1000ms; //Vari�veis pra controle dos tempos de 500ms e 1000ms
int conta_t0 = 0, conta_t1;  //Vari�veis de contagem
char bufferLCD[16];         //Matriz para armazenamento da string para o LCD

//Fun��o de tratamento para Int. do TIMER0
void __interrupt(low_priority) int_TIMERS(void)   
{
    if (TMR0IF)                   	//Se o flag da interrup��o for 1 (TMR0IF)
    {
        T0_500ms++;             	//Incrementa a vari�-avel T0_500ms
        if (T0_500ms>=20)       	//Se T0_500ms >= 20 = 500ms
        {
            T0_500ms=0;         	//Zera a vari�vel T0_500ms
            conta_t0++;         	//Incrementa a vari�vel conta_t0
            if (conta_t0>=100)  	//Se conta_t0 >= 100 
                conta_t0=0;     	//Zera a vari�vel conta_t0
        }        
     
     TMR0 = 61;            		//Retorna valor inicial para o reg. TMR0
     TMR0IF = 0;               	//Limpa o flag da interrup��o (TMR0IF)  
    }
    
    if (TMR1IF)                   	//Se o flag da interrup��o for 1 (TMR1IF)
    {
        T1_1000ms++;            	//Incrementa a vari�vel T1_1000ms
        if (T1_1000ms>=4)       	//Se T1_1000ms >= 4 = 1000ms
        {
            T1_1000ms=0;        	//Zera a vari�vel T1_1000ms
            conta_t1++;         	//Incrementa a vari�vel conta_t1
            if (conta_t1>=100)  	//Se conta_t1 >= 100
                conta_t1=0;     	//Zera a vari�vel conta_t1
        }               
     
     TMR1H = 0x0B;           //Valor inicial para os registradores de contagem
     TMR1L = 0xDC;           //Do m�dulo TIMER1 = Equivalente a 3036
     TMR1IF = 0;             //Limpa o flag da interrup��o (TMR1IF)  
    }
}

void main(void)
{
    TRISBbits.TRISB0 = 0;       //Direciona o pino 0 da porta B como sa�da
    PORTBbits.RB0 = 0;          //Coloca em 0 todo o pino 0 da porta B
    ADCON1 = 0x0F;          //Desabilita todos os canais A/D
    
    INTCON = 0b11100000;	/* GIE/GIEH = 1 - Habilita interrup��o global
                             * PEIE/GIEL = 1 - Habilita interrup��o de perif�ricos
                           	 * TMR0IE = 1 - Habilita interrup��o para o TIMER0  
                             * Demais bits - N�o se aplicam*/
    
    T0CON = 0b11000111;     /* TMR0ON = 1 - Habilita TIMER0
                             * T08BIT = 1 - Modo de opera��o em 8 bits
                             * T0CS = 0 - Incremento pelo ciclo de m�quina
                             * T0SE = 0 - N�o se aplica
                             * PSA = 0 - Prescaler habilitado
                             * PS2, PS1, PS0 = 1 - Prescaler de 1:256
                             */ 
    
    TMR0 = 61;               //Valor inicial para o reg. TMR0
    
    T1CON = 0b00110101;      /* RD16 = 0 - Modo de escrita/leitura em 8 bits
                              * T1RUN = 0 - N�o se aplica
                              * T1CKPS1 e T1CKPS0 = 1 - Prescaler de 1:8
                              * T1OSCEN = 0 - N�o se aplica
                              * T1SYNC = 1 - N�o se aplica
                              * TMR1CS = 0 - Fonte de clock pelo ciclo de m�quina
                              * TMR1ON = 1 - M�dulo TIMER1 habilitado*/

    PIE1bits.TMR1IE = 1;	 //Habilita a interrup��o para o m�dulo TIMER1
    
    TMR1H = 0x0B;           //Valor inicial para os registradores de contagem
    TMR1L = 0xDC;           //Do m�dulo TIMER1 = Equivalente a 3036
    
    lcd_ini();                  	//Inicializa LCD
        
    //Posiciona o cursor na coluna 1 da linha 1 e escreve no LCD 
    lcd_escreve_bf(1, 1, "CONTA TMR0: 00");   	
          
    //Posiciona o cursor na coluna 1 da linha 2 e escreve no LCD    
    lcd_escreve_bf(2, 1, "CONTA TMR1: 00");   	
       
    while(1)                	//Loop principal
    {
        __delay_ms(500);      		//Atraso de 500ms
                
        PORTBbits.RB0 = ~PORTBbits.RB0; 	//Inverte o estado do pino RB0        
        
        //Escreve aa vari�vel conta_t0 na matriz bufferLCD  
        sprintf(bufferLCD, "%02d", conta_t0);    
        
        //Posiciona o cursor na coluna 13 da linha 1 e escreve no LCD
        lcd_escreve_bf(1, 13, bufferLCD);
                
        //Escreve a vari�vel conta_t1 na matriz bufferLCD  
        sprintf(bufferLCD, "%02d", conta_t1);    //Escreve no LCD
        
        //Posiciona o cursor na coluna 13 da linha 2 e escreve no LCD
        lcd_escreve_bf(2, 13, bufferLCD);
    }
}
