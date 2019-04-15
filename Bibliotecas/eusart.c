#include "eusart.h"	//Inclus�o do arquivo eusart.h

//Fun��o de inicializa��o do m�dulo EUSART
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
