#include <xc.h>                     	//Inclui o arquivo xc.h

#include "../Bibliotecas/config.h"  	//Inclui o arquivo config.h

#define _XTAL_FREQ 8000000      	//Define a frequência de clock utilizada

char dado[4];    	//Vetor p/ armazenamento de dados recebidas pela serial

char i=0;       	//Variável de controle para recepção de dados

//Protótipos para as funções transmissão e recepção serial
void init_EUSART(void);
void escreve_EUSART(char c);
void string_EUSART(char *c);
char EUSART_le(void);

void main(void)
{
    TRISB = 0b00000000;         //Configura os pinos da porta B como saída
    PORTB = 0b00000000;         //Todos os pinos da porta B em 0

    ADCON1 = 0x0F;              //Desabilita todos os canais A/D
    
    init_EUSART();              //Chama a função p/ inicialização do módulo EUSART
           
    //Envio texto inicial pelo módulo EUSART 
    string_EUSART("Microcontrolador PIC18F4520\r\n");
    string_EUSART("LD1 - ACENDE LED.\r\n");
    string_EUSART("DL1 - APAGA LED.\r\n");
       
    while(1)                   	//Loop principal
    {        
        if (RCIF)               /*Verifica o flag de interrupção para a 
                                recepção do módulo USART, caso seja 1*/
        {
           dado[i] = EUSART_le();  	/*Recebe um caractere de cada vez e 
                                  	armazena em dado com a posição i*/ 
	                  
           if (dado[i] == 0x0D)  	//Se o caractere 0x0D (CR) for recebido
            {
            //Se a string contida no vetor dado = LD1
            if (dado[0] == 'L' && dado[1] == 'D' && dado[2] == '1')
            {
                 PORTBbits.RB0 = 1;	 	//Acende o LED L1
                 string_EUSART("L1");   	//Envia L1 pela serial 
            }
            //Se a string contida no vetor dado = DL1
            if (dado[0] == 'D' && dado[1] == 'L' && dado[2] == '1')
            {
                 PORTBbits.RB0 = 0;  	//Apaga o LED L1
                 string_EUSART("L0");       	//Envia L0 pela serial
            }
 	            
            i=0;				//retorna a variável i a 0
            }
            else i++ ;              		/*Se o caractere recebido for 
                                    		diferente de 0x0d, incrementa a
variável i;*/       
        }
    }
}

//Função de inicialização do módulo EUSART ? Transmissão e recepção
void init_EUSART(void)
{
    TXSTAbits.TXEN = 1;         //Habilita Transmissão pela EUSART
    RCSTAbits.CREN = 1;         //Habilita Recepção pela EUSART
    TXSTAbits.SYNC = 0;         //Habilita modo Assíncrono
    RCSTAbits.SPEN = 1;         //Configura pinos RC6 e RC7 como TX e RX
    
    TXSTAbits.BRGH = 0;         //Controle de Baud Rate
    BAUDCTLbits.BRG16 = 0;
    
    SPBRG = 12;                 //Baud Rate de 9600 bps    
}

//Função para transmissão de caracteres via EUSART
void escreve_EUSART(char c)
{
  while(!TRMT);     //Aguarda a finalização do envio do caractere
  TXREG = c;        //Carrega em TXREG e transmite o caractere via EUSART
}

//Função para transmissão de strings pela serial
void string_EUSART(char *str)
{
  while(*str!='\0')
  {
      escreve_EUSART(*str);
      str++;
  }
}

//Faz a leitura do caractere recebido pela serial
char EUSART_le(void)
{ 
  while(!RCIF);     //Enquanto RCIF = 0, aguarda a chegado do caractere
  return RCREG;     //Retorna o caractere recebido
}

