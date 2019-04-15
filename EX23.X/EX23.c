#include <xc.h>                     	//Inclui o arquivo xc.h

#include "../Bibliotecas/config.h"  	//Inclui o arquivo config.h

#define _XTAL_FREQ 8000000      	//Define a frequ�ncia de clock utilizada

char dado[4];    	//Vetor p/ armazenamento de dados recebidas pela serial

char i=0;       	//Vari�vel de controle para recep��o de dados

//Prot�tipos para as fun��es transmiss�o e recep��o serial
void init_EUSART(void);
void escreve_EUSART(char c);
void string_EUSART(char *c);
char EUSART_le(void);

void main(void)
{
    TRISB = 0b00000000;         //Configura os pinos da porta B como sa�da
    PORTB = 0b00000000;         //Todos os pinos da porta B em 0

    ADCON1 = 0x0F;              //Desabilita todos os canais A/D
    
    init_EUSART();              //Chama a fun��o p/ inicializa��o do m�dulo EUSART
           
    //Envio texto inicial pelo m�dulo EUSART 
    string_EUSART("Microcontrolador PIC18F4520\r\n");
    string_EUSART("LD1 - ACENDE LED.\r\n");
    string_EUSART("DL1 - APAGA LED.\r\n");
       
    while(1)                   	//Loop principal
    {        
        if (RCIF)               /*Verifica o flag de interrup��o para a 
                                recep��o do m�dulo USART, caso seja 1*/
        {
           dado[i] = EUSART_le();  	/*Recebe um caractere de cada vez e 
                                  	armazena em dado com a posi��o i*/ 
	                  
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
 	            
            i=0;				//retorna a vari�vel i a 0
            }
            else i++ ;              		/*Se o caractere recebido for 
                                    		diferente de 0x0d, incrementa a
vari�vel i;*/       
        }
    }
}

//Fun��o de inicializa��o do m�dulo EUSART ? Transmiss�o e recep��o
void init_EUSART(void)
{
    TXSTAbits.TXEN = 1;         //Habilita Transmiss�o pela EUSART
    RCSTAbits.CREN = 1;         //Habilita Recep��o pela EUSART
    TXSTAbits.SYNC = 0;         //Habilita modo Ass�ncrono
    RCSTAbits.SPEN = 1;         //Configura pinos RC6 e RC7 como TX e RX
    
    TXSTAbits.BRGH = 0;         //Controle de Baud Rate
    BAUDCTLbits.BRG16 = 0;
    
    SPBRG = 12;                 //Baud Rate de 9600 bps    
}

//Fun��o para transmiss�o de caracteres via EUSART
void escreve_EUSART(char c)
{
  while(!TRMT);     //Aguarda a finaliza��o do envio do caractere
  TXREG = c;        //Carrega em TXREG e transmite o caractere via EUSART
}

//Fun��o para transmiss�o de strings pela serial
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

