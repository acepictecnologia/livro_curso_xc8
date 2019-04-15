#include <xc.h>                     	//Inclui o arquivo header xc.h
#include <stdio.h>                  	//Inclui o arquivo stdio.h 

#include "../Bibliotecas/config.h"  	//Inclui o arquivo config.h
#include "../Bibliotecas/LCD4b.h"    //Inclui o arquivo LCD4b.h

int conta = 0;                 	//Variável de contagem
char bufferLCD[16];		//Matriz de mensagens para o LCD

void main(void)
{
    ADCON1 = 0x0F;              	//Desabilita todos os canais A/D
       
    lcd_ini();                  	//Inicializa LCD
               
    //Posiciona o cursor na coluna 1 da linha 1 e escreve no LCD
        lcd_escreve_bf(1, 1, "CONTAGEM: 000");
       
    while(1)                    	//Loop principal
    {         
        //Armazena string na matriz bufferLCD
        sprintf(bufferLCD, "%03d", conta);
        
        //Posiciona o cursor na coluna 11 da linha 1 e escreve no LCD
        lcd_escreve_bf(1, 11, bufferLCD);
        
        conta++;			//Incrementa variável conta
        
        //Se a variável conta for maior ou igual a 1000, retorna o seu valor a 0
        if (conta >= 1000) conta = 0;
               
        __delay_ms(1000);      	//Atraso de 1000ms
    }
}

