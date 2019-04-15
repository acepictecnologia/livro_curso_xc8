#include <xc.h>                     		//Inclui o arquivo xc.h
#include <stdio.h>                  		//Inclui o arquivo stdio.h

#include "../Bibliotecas/config.h"  		//Inclui o arquivo config.h
#include "../Bibliotecas/LCD4b.h"		//Inclus�o do arquivo LCD4b.h

#define _XTAL_FREQ 8000000  //Define a frequ�ncia de clock utilizada

int adc = 0;		//Var�vel de contagem
long volt = 0;		//Vari�vel para armazenamento da tens�o (AN1)
float temp = 0;		//Vari�vel para armazenamento da temperatura (AN0)
char bufferLCD[16];         //Matriz para armazenamento da string para o LCD

void main(void)
{   
    ADCON0 = 0b00000101; 	/*Bits 7 e 6 = 0 -N�o utilizados
                            CHS<3:0> = 0001 -Sele��o dos canais anal�gicos AN0 e 
			                 AN1
                            GO/DONE = 0 -Convers�o A/D n�o iniciada
                            ADON = 1 -M�dulo A/D habilitado */  

    
    ADCON1  = 0b00001101;   /*Bits 7 e 6 = 0 -N�o utilizados
                            VCFG<1:0> = 00 -Define as tens�es de refer�ncia 
                                            em GND e VDD
                            PCFG<3:0> = 1110 -Habilita canais 0 e 1 para leitura*/
   
    ADCON2 = 0b10000111;     /*ADFM = 1 -Resultado da convers�o justificado � 
                                         direita.
                              Bit 6 -N�o utilizado
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
                
        ADCON0bits.GO = 1;		//Inicia a convers�o A/D		
        
        while (ADCON0bits.GO);	//Aguarda a finaliza��o da convers�o
        
        adc = ADRESH;		//Armazena a parte alta do resultado em adc
        
        adc = (adc << 8) + ADRESL;	/*Desloca 8 bits � esquerda e soma com a 
                                     parte baixa do resultado da convers�o A/D.*/
        
        temp = ((float)adc * 5000) / 1023;	//Converte a leitura adc em tens�o
        temp = temp / 10; 		//Converte a tens�o em temperatura
        
        ADCON0 = 0b00000101;	//Seleciona o canal AN1 para leitura
                
        __delay_us(100);          	//Atraso de 100us
        
        ADCON0bits.GO = 1;		//Inicia a convers�o A/D		
        
        while (ADCON0bits.GO);	//Aguarda a finaliza��o da convers�o
        
        adc = ADRESH;		//Armazena a parte alta do resultado em adc
        
        adc = (adc << 8) + ADRESL;	/*Desloca 8 bits � esquerda e soma com a 
                                    parte baixa do resultado da convers�o A/D.*/
        
        volt = ((long)adc * 5000) / 1023;	//Converte a leitura adc em tens�o
    
        //Escreve a vari�vel temp e a constante (0xDF) na matriz bufferLCD
        sprintf(bufferLCD, "%0.1f %cC", temp, 0xDF);    
        
        //Posiciona o cursor na coluna 7 da linha 1 e escreve no LCD
        lcd_escreve_bf(1, 7, bufferLCD);   	
    
        //Escreve a vari�vel volt na matriz bufferLCD
        sprintf(bufferLCD, "%04lu mV", volt);          
        
        //Posiciona o cursor na coluna 7 da linha 2 e escreve no LCD
        lcd_escreve_bf(2, 7, bufferLCD);   	    
         
    }
}

