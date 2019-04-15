#include <xc.h>                     		//Inclui o arquivo xc.h
#include <stdio.h>                  		//Inclui o arquivo stdio.h

#include "../Bibliotecas/config.h"  		//Inclui o arquivo config.h
#include "../Bibliotecas/LCD4b.h"		//Inclui do arquivo LCD4b.h


#define _XTAL_FREQ 8000000        	//Define a frequ�ncia de clock utilizada

int adc = 0;    			//Vari�vel de armazenamento da convers�o A/D
char bufferLCD[16];         //Matriz para armazenamento da string para o LCD

void main(void)
{
    TRISAbits.RA0 = 1;
    ADCON0 = 0b00000001; 	/*Bits 7 e 6 = 0 ?N�o utilizados
                            CHS<3:0> = 0000 ?Sele��o do canal anal�gico AN0
                            GO/DONE = 0 ?Convers�o A/D n�o iniciada
                            ADON = 1 ?M�dulo A/D habilitado */  

    
    ADCON1  = 0b00001110;   /*Bits 7 e 6 = 0 ?N�o utilizados
                            VCFG<1:0> = 00 ?Define as tens�es de refer�ncia 
                                            em GND e VDD
                            PCFG<3:0> = 1110 ?Habilita canal 0 para leitura*/
   
    ADCON2 = 0b10000111;    /*ADFM = 1 ? Resultado da convers�o justificado � 
                                         direita.
                            Bit 6 ? N�o utilizado
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
        
        ADCON0bits.GO = 1;		//Inicia a convers�o A/D		
        
        while (ADCON0bits.GO);	//Aguarda a finaliza��o da convers�o
        
        adc = ADRESH;		//Armazena a parte alta do resultado em adc
        
        adc = (adc << 8) + ADRESL;	/*Desloca 8 bits � esquerda e soma com a 
                                      parte baixa do resultado da convers�o A/D.*/
        
        //Escreve a vari�vel adc no bufferLCD
        sprintf(bufferLCD, "%04d", adc);	 
        
        //Posiciona o cursor na coluna 7 da linha 1 e escreve no LCD 
        lcd_escreve_bf(2, 7, bufferLCD);   	
    }
}

