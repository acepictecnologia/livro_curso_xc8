#include <xc.h>                     //Inclui o arquivo xc.h

#include "../Bibliotecas/config.h"  //Inclui o arquivo config.h

#define _XTAL_FREQ 8000000      	//Define a frequ�ncia de clock utilizada

void escreve_EUSART(char c);	//Prot�tipo da fun��o escreve_EUSART

void main(void)
{
    ADCON1 = 0x0F;              //Desabilita todos os canais A/D
    
    TXSTAbits.TXEN = 1;         //Habilita Transmiss�o pela EUSART
    TXSTAbits.SYNC = 0;         //Habilita modo Ass�ncrono
    RCSTAbits.SPEN = 1;         //Configura pinos RC6 e RC7 como TX e RX
    
    TXSTAbits.BRGH = 0;         //Controle de Baud Rate
    BAUDCTLbits.BRG16 = 0;	    //  ?          ?      ?	
    
    SPBRG = 12;                 //Baud Rate de 9600 bps    
    
    //Chama a fun��o escreve_EUSART com o caractere a ser transmitido
    escreve_EUSART('P');  
    escreve_EUSART('I');
    escreve_EUSART('C');    
    escreve_EUSART('1');  
    escreve_EUSART('8');
    escreve_EUSART('F');
    escreve_EUSART('4');
    escreve_EUSART('5');
    escreve_EUSART('2');
    escreve_EUSART('0'); 
         
    while(1)                //Loop principal
    {             
    }
}

//Fun��o para transmiss�o de caracteres via EUSART
void escreve_EUSART(char c)
{
  while(!TRMT);     //Aguarda a finaliza��o da transmiss�o do caractere
  TXREG = c;        //Carrega em TXREG e transmite o caractere via EUSART
}

