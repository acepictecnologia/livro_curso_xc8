#include <xc.h>                     		//Inclui o arquivo xc.h
#include <stdio.h>                  		//Inclui o arquivo stdio.h

#include "../Bibliotecas/config.h"  		//Inclui o arquivo config.h
#include "../Bibliotecas/LCD4b.h"		//Inclui do arquivo LCD4b.h


#define _XTAL_FREQ 8000000        	//Define a frequência de clock utilizada

int adc = 0;    			//Variável de armazenamento da conversão A/D
char bufferLCD[16];         //Matriz para armazenamento da string para o LCD

void main(void)
{
    TRISAbits.RA0 = 1;
    ADCON0 = 0b00000001; 	/*Bits 7 e 6 = 0 ?Não utilizados
                            CHS<3:0> = 0000 ?Seleção do canal analógico AN0
                            GO/DONE = 0 ?Conversão A/D não iniciada
                            ADON = 1 ?Módulo A/D habilitado */  

    
    ADCON1  = 0b00001110;   /*Bits 7 e 6 = 0 ?Não utilizados
                            VCFG<1:0> = 00 ?Define as tensões de referência 
                                            em GND e VDD
                            PCFG<3:0> = 1110 ?Habilita canal 0 para leitura*/
   
    ADCON2 = 0b10000111;    /*ADFM = 1 ? Resultado da conversão justificado à 
                                         direita.
                            Bit 6 ? Não utilizado
                            ACQT<2:0> = 0 ? 0 TAD
                            ADCS<2:0> = 111 ? OScilador Interno para A/D*/
    
    lcd_ini();             		//Inicializa LCD
        
    //Posiciona o cursor na coluna 4 da linha 1 e escreve no LCD
    lcd_escreve_bf(1, 4, "CANAL AN0:");   	
    
    //Posiciona o cursor na coluna 7 da linha 1 e escreve no LCD
    lcd_escreve_bf(2, 7,"0000");   		
          
    while(1)                	//Loop principal
    {
        __delay_ms(300);    	//Atraso de 100ms
        
        ADCON0bits.GO = 1;		//Inicia a conversão A/D		
        
        while (ADCON0bits.GO);	//Aguarda a finalização da conversão
        
        adc = ADRESH;		//Armazena a parte alta do resultado em adc
        
        adc = (adc << 8) + ADRESL;	/*Desloca 8 bits à esquerda e soma com a 
                                      parte baixa do resultado da conversão A/D.*/
        
        //Escreve a variável adc no bufferLCD
        sprintf(bufferLCD, "%04d", adc);	 
        
        //Posiciona o cursor na coluna 7 da linha 1 e escreve no LCD 
        lcd_escreve_bf(2, 7, bufferLCD);   	
    }
}

