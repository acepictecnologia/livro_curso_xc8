#include <xc.h>                     		//Inclui o arquivo xc.h

#include <stdio.h>                  		//Inclui o arquivo stdio.h

#include "../Bibliotecas/config.h"  		//Inclui o arquivo config.h
#include "../Bibliotecas/LCD4b.h"		//Inclui o arquivo LCD4b.h

#define _XTAL_FREQ 8000000		//Define a frequência de clock utilizada

int seg = 0, min = 0, hor = 0;  //Varáveis de controle de horário
char bufferLCD[16];         //Matriz para armazenamento da string para o LCD

void __interrupt() int_TMR(void)    //Função de tratamento para interrupção
{
    if (TMR1IF)                 //Se o flag TMR1IF (Interrupção do TIMER1) for 1
    {
     seg++;                     //Incrementa a variável seg
     
     if (seg > 59)              //Se seg > 59
     {
         seg = 0;               //Zera a variável seg
         min++;                 //Incrementa a variável min
         if (min > 59)          //Se min > 59
         {
             min = 0;           //Zera a variável min
             hor++;             //Incrementa a variável hor
             if (hor > 23)      //Se hor > 23
                 hor = 0;       //zera a variável hor
         }
     }
        TMR1H = 0x80;           //Retorna os valores inciais aos registradores
        TMR1L = 0x00;           //de contagem do módulo TIMER1
        TMR1IF = 0;             //Limpa o flag da interrupção do TIMER1
    }
}

void main(void)
{
    TRISB = 0b00000001;         //Direciona o pino 0 da porta B como entrada
    TRISA = 0b00010000;         //Direciona o pino 4 da porta A como entrada
    
    ADCON1 = 0x0F;              //Desabilita todos os canais A/D
    
    INTCON = 0b11000000;        /* GIE = 1  - Habilita interrupção global
                                 * PEIE = 1 - Habilita interrupção de 
                                              periféricos
                                 * T0IE = 0 - Não utilizado
                                 * INTE = 0 - Não utilizado
                                 * RBIE = 0 - Não utilizado
                                 * T0IF = 0 - Não utilizado
                                 * INTF = 0 - Não utilizado
                                 * RBIE = 0 - Não utilizado
                                 */
    
    T1CON = 0b00001111;          /* T1GINV = 0 - Não se aplica
                                 * TMR1GE = 0 - Não se aplica
                                 * T1CKPS1 e T1CKPS0 = 1 - Prescaler de 1:1
                                 * T1OSCEN = 1 - Habilita cristal externo em RC0 
                                                 e RC1
                                 * T1SYNC = 1 - Não se aplica
                                 * TMR1CS = 1 - Fonte de clock externa
                                 * TMR1ON = 1 - Módulo TIMER1 habilitado
                                 */

    PIE1bits.TMR1IE = 1;	//Habilita a interrupção para o módulo TIMER1
    
    TMR1H = 0x80;           //Valor inicial para os registradores de contagem
    TMR1L = 0x00;           //Do módulo TIMER1 = Equivalente a 32768
    
    lcd_ini();              //Inicializa LCD
        
    //Posiciona o cursor na coluna 4 da linha 1 e escreve no LCD
    lcd_escreve_bf(1, 4, "RTC TIMER1"); 
    
    //Posiciona o cursor na coluna 5 da linha 2 e escreve no LCD
    lcd_escreve_bf(2, 5, "00:00:00"); 
       
    while(1)                            //Loop principal
    {
        __delay_ms(200);                //Atraso de 200ms
        
        if (PORTBbits.RB0)          	//Se B1 Pressionado
        {
            min++;                  	//Incrementa a variável min
            if (min > 59) min = 0;  	//Se min > 59, zera a variável
        }
        
        if (PORTAbits.RA4)          	//Se B3 Pressionado
        {
            hor++;                  	//Incrementa a variável hor
            if(hor > 23) hor = 0;   	//Se hor > 23, zera a variável
        }
            
        //Escreve as variáveis hor, min e seg na matriz bufferLCD
        sprintf(bufferLCD, "%02d:%02d:%02d", hor, min, seg); 	 
        
        //Posiciona o cursor na coluna 5 da linha 2 e escreve no LCD
        lcd_escreve_bf(2, 5, bufferLCD); 
    }
}

