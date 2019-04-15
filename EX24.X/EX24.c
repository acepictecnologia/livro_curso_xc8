#include <xc.h>                     		//Inclui o arquivo xc.h
#include <stdio.h>                  		//Inclui o arquivo stdio.h

#include "../Bibliotecas/config.h"      	//Inclui o arquivo config.h
#include "../Bibliotecas/eusart.h"

#define _XTAL_FREQ 8000000      	//Define a frequ�ncia de clock utilizada

char i=0;       	//Vari�vel de controle para recep��o de dados
int adc = 0;        //Var�vel para armazenamento do ADC
long volt = 0;      //Vari�vel de armazenamento da convers�o para temperatura
float temp = 0;     //Vari�vel de armazenamento da convers�o para tens�o
char dado[4];       //Vari�vel para recep��o de dados pela serial
char bufferEUSART[50];  //Matriz para armazenamento de dados para envio � serial

/*fun��o de tratamento da ocorr�ncia da interrup��o, no caso a interrup��o pela recep��o de dados pelo m�dulo EUSART*/
void __interrupt() trata_serial(void)
{
    if (RCIF)			/*Verifica o flag de interrup��o para a
                        recep��o do m�dulo USART, caso seja 1*/

        {
           dado[i] = EUSART_le();  	/*Recebe um caractere de cada vez e 
                                  	armazena em dado com a posi��o i*/ 
	                  
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
 	            
            i=0;					//retorna a vari�vel i a 0
            }
            else i++ ;              /*Se o caractere recebido for diferente de 
                                      0x0d incrementa a vari�vel i;*/              
        }
    RCIF = 0;                       //Retorna o valor 0 ao flag da interrup��o   
}

void main(void)
{
    TRISB = 0b00000000;    //Configura os pinos da porta B como sa�da
    PORTB = 0b00000000;    //Todos os pinos da porta B em 0
    
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
    
    PIE1bits.RCIE = 1;     //Habilita recep��o pela serial
    INTCONbits.GIE = 1;    //Habilita interrup��o global
    INTCONbits.PEIE = 1;   //Habilita interrup��o de perif�ricos
    
    init_EUSART();          //Chama a fun��o p/ inicializa��o do m�dulo EUSART
                 
    //Transmite string inicial pela serial 
    string_EUSART("Conversao A/D: Canais AN0 e AN1\r\n");
    
    while(1)                	//Loop principal
    {   
        __delay_ms(1000);    	//Atraso de 100ms

        ADCON0bits.CHS0 = 0;	//Seleciona canal AN0 para leitura
        //ADCON0 = 0b11000001	//Seleciona canal AN0 para leitura

        __delay_us(100);         	//Atraso de 100us
        
        ADCON0bits.GO = 1;		//Inicia a convers�o A/D		
        
        while (ADCON0bits.GO);	//Aguarda a finaliza��o da convers�o
        
        adc = ADRESH;		//Armazena a parte alta do resultado em adc
        
        adc = (adc << 8) + ADRESL;	/*Desloca 8 bits � esquerda e soma com a 
                                      parte baixa do resultado da convers�o A/D.*/
        
        temp = ((float)adc * 5000) / 1023;	//Converte a leitura adc em tens�o
        temp = temp / 10; 		//Converte a tens�o em temperatura
        
        ADCON0bits.CHS0 = 1;	//Seleciona o canal AN1 para leitura
        
        __delay_us(100);         	//Atraso de 100us
        
        ADCON0bits.GO = 1;		//Inicia a convers�o A/D		
        
        while (ADCON0bits.GO);	//Aguarda a finaliza��o da convers�o
        
        adc = ADRESH;		//Armazena a parte alta do resultado em adc
        
        adc = (adc << 8) + ADRESL;	/*Desloca 8 bits � esquerda e soma com a 
                                      parte baixa do resultado da convers�o A/D.*/
        
        volt = ((long)adc * 5000) / 1023;	//Converte a leitura adc em tens�o
    
        /*Armazena em bufferEUSART a string formatada com as informa��es 
          de temperatura e tens�o*/	
        sprintf(bufferEUSART, "Temp: %0.1f C - Volt: %04lu mV\r\n", temp, volt); 
        
        //Transmite o conte�do de bufferEUSART pela Serial
        string_EUSART(bufferEUSART);
    }
}

