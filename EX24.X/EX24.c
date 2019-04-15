#include <xc.h>                     		//Inclui o arquivo xc.h
#include <stdio.h>                  		//Inclui o arquivo stdio.h

#include "../Bibliotecas/config.h"      	//Inclui o arquivo config.h
#include "../Bibliotecas/eusart.h"

#define _XTAL_FREQ 8000000      	//Define a frequência de clock utilizada

char i=0;       	//Variável de controle para recepção de dados
int adc = 0;        //Varável para armazenamento do ADC
long volt = 0;      //Variável de armazenamento da conversão para temperatura
float temp = 0;     //Variável de armazenamento da conversão para tensão
char dado[4];       //Variável para recepção de dados pela serial
char bufferEUSART[50];  //Matriz para armazenamento de dados para envio à serial

/*função de tratamento da ocorrência da interrupção, no caso a interrupção pela recepção de dados pelo módulo EUSART*/
void __interrupt() trata_serial(void)
{
    if (RCIF)			/*Verifica o flag de interrupção para a
                        recepção do módulo USART, caso seja 1*/

        {
           dado[i] = EUSART_le();  	/*Recebe um caractere de cada vez e 
                                  	armazena em dado com a posição i*/ 
	                  
           if (dado[i] == 0x0D)  	//Se o caractere 0x0D (CR) for recebido
            {
            //Se a string contida na matriz dado = LD1
            if (dado[0] == 'L' && dado[1] == 'D' && dado[2] == '1')
            {
                 PORTBbits.RB0 = 1;	 		//Acende o LED L1                 
            }
             
            //Se a string contida na matriz dado = DL1
            if (dado[0] == 'D' && dado[1] == 'L' && dado[2] == '1')
            {
                 PORTBbits.RB0 = 0;  		//Apaga o LED L1                 
            }
 	            
            i=0;					//retorna a variável i a 0
            }
            else i++ ;              /*Se o caractere recebido for diferente de 
                                      0x0d incrementa a variável i;*/              
        }
    RCIF = 0;                       //Retorna o valor 0 ao flag da interrupção   
}

void main(void)
{
    TRISB = 0b00000000;    //Configura os pinos da porta B como saída
    PORTB = 0b00000000;    //Todos os pinos da porta B em 0
    
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
    
    PIE1bits.RCIE = 1;     //Habilita recepção pela serial
    INTCONbits.GIE = 1;    //Habilita interrupção global
    INTCONbits.PEIE = 1;   //Habilita interrupção de periféricos
    
    init_EUSART();          //Chama a função p/ inicialização do módulo EUSART
                 
    //Transmite string inicial pela serial 
    string_EUSART("Conversao A/D: Canais AN0 e AN1\r\n");
    
    while(1)                	//Loop principal
    {   
        __delay_ms(1000);    	//Atraso de 100ms

        ADCON0bits.CHS0 = 0;	//Seleciona canal AN0 para leitura
        //ADCON0 = 0b11000001	//Seleciona canal AN0 para leitura

        __delay_us(100);         	//Atraso de 100us
        
        ADCON0bits.GO = 1;		//Inicia a conversão A/D		
        
        while (ADCON0bits.GO);	//Aguarda a finalização da conversão
        
        adc = ADRESH;		//Armazena a parte alta do resultado em adc
        
        adc = (adc << 8) + ADRESL;	/*Desloca 8 bits à esquerda e soma com a 
                                      parte baixa do resultado da conversão A/D.*/
        
        temp = ((float)adc * 5000) / 1023;	//Converte a leitura adc em tensão
        temp = temp / 10; 		//Converte a tensão em temperatura
        
        ADCON0bits.CHS0 = 1;	//Seleciona o canal AN1 para leitura
        
        __delay_us(100);         	//Atraso de 100us
        
        ADCON0bits.GO = 1;		//Inicia a conversão A/D		
        
        while (ADCON0bits.GO);	//Aguarda a finalização da conversão
        
        adc = ADRESH;		//Armazena a parte alta do resultado em adc
        
        adc = (adc << 8) + ADRESL;	/*Desloca 8 bits à esquerda e soma com a 
                                      parte baixa do resultado da conversão A/D.*/
        
        volt = ((long)adc * 5000) / 1023;	//Converte a leitura adc em tensão
    
        /*Armazena em bufferEUSART a string formatada com as informações 
          de temperatura e tensão*/	
        sprintf(bufferEUSART, "Temp: %0.1f C - Volt: %04lu mV\r\n", temp, volt); 
        
        //Transmite o conteúdo de bufferEUSART pela Serial
        string_EUSART(bufferEUSART);
    }
}

