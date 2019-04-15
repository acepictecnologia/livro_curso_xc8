#include <xc.h>                     		//Inclui o arquivo xc.h
#include <stdio.h>                  		//Inclui o arquivo stdio.h

#include "../Bibliotecas/config.h"  		//Inclui o arquivo config.h
#include "../Bibliotecas/LCD4b.h"		//Inclusão do arquivo LCD4b.h

#define _XTAL_FREQ 8000000  //Define a frequência de clock utilizada

int adc = 0;		//Varável de contagem
long volt = 0;		//Variável para armazenamento da tensão (AN1)
float temp = 0;		//Variável para armazenamento da temperatura (AN0)
char bufferLCD[16];         //Matriz para armazenamento da string para o LCD

void main(void)
{   
    ADCON0 = 0b00000101; 	/*Bits 7 e 6 = 0 -Não utilizados
                            CHS<3:0> = 0001 -Seleção dos canais analógicos AN0 e 
			                 AN1
                            GO/DONE = 0 -Conversão A/D não iniciada
                            ADON = 1 -Módulo A/D habilitado */  

    
    ADCON1  = 0b00001101;   /*Bits 7 e 6 = 0 -Não utilizados
                            VCFG<1:0> = 00 -Define as tensões de referência 
                                            em GND e VDD
                            PCFG<3:0> = 1110 -Habilita canais 0 e 1 para leitura*/
   
    ADCON2 = 0b10000111;     /*ADFM = 1 -Resultado da conversão justificado à 
                                         direita.
                              Bit 6 -Não utilizado
                              ACQT<2:0> = 0 - 0 TAD
                              ADCS<2:0> = 111 - OScilador Interno para A/D*/
    
    lcd_ini();		 //Inicializa LCD
        
    //Posiciona o cursor na coluna 1 da linha 1 e escreve no LCD
    lcd_escreve_bf(1, 1, "Temp:");  
           
    //Posiciona o cursor na coluna 1 da linha 2 e escreve no LCD
    lcd_escreve_bf(2, 1, "Volt:");  
           
    while(1)                //Loop principal
    {
        __delay_ms(300);    		//Atraso de 300ms
        
        ADCON0 = 0b00000001;	//Seleciona canal AN0 para leitura
                
        __delay_us(100);          	//Atraso de 100us
                
        ADCON0bits.GO = 1;		//Inicia a conversão A/D		
        
        while (ADCON0bits.GO);	//Aguarda a finalização da conversão
        
        adc = ADRESH;		//Armazena a parte alta do resultado em adc
        
        adc = (adc << 8) + ADRESL;	/*Desloca 8 bits à esquerda e soma com a 
                                     parte baixa do resultado da conversão A/D.*/
        
        temp = ((float)adc * 5000) / 1023;	//Converte a leitura adc em tensão
        temp = temp / 10; 		//Converte a tensão em temperatura
        
        ADCON0 = 0b00000101;	//Seleciona o canal AN1 para leitura
                
        __delay_us(100);          	//Atraso de 100us
        
        ADCON0bits.GO = 1;		//Inicia a conversão A/D		
        
        while (ADCON0bits.GO);	//Aguarda a finalização da conversão
        
        adc = ADRESH;		//Armazena a parte alta do resultado em adc
        
        adc = (adc << 8) + ADRESL;	/*Desloca 8 bits à esquerda e soma com a 
                                    parte baixa do resultado da conversão A/D.*/
        
        volt = ((long)adc * 5000) / 1023;	//Converte a leitura adc em tensão
    
        //Escreve a variável temp e a constante (0xDF) na matriz bufferLCD
        sprintf(bufferLCD, "%0.1f %cC", temp, 0xDF);    
        
        //Posiciona o cursor na coluna 7 da linha 1 e escreve no LCD
        lcd_escreve_bf(1, 7, bufferLCD);   	
    
        //Escreve a variável volt na matriz bufferLCD
        sprintf(bufferLCD, "%04lu mV", volt);          
        
        //Posiciona o cursor na coluna 7 da linha 2 e escreve no LCD
        lcd_escreve_bf(2, 7, bufferLCD);   	    
         
    }
}

