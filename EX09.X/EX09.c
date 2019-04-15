#include <xc.h>			//Inclui o arquivo header xc.h

#include "../Bibliotecas/config.h"	//Inclui o arquivo config.h
#include "LCD4b.h"                  //Inclui o arquivo LCD4b.h

#define _XTAL_FREQ 8000000      	//Define a frequência de clock utilizada

void main(void)
{			    //Início da função principal (main)	
    ADCON1 = 0x0F;              //Desabilita todos os canais A/D
    
    lcd_ini();                  //Inicializa LCD

    lcd_envia_byte(0,0x083);    //Posiciona o cursor na coluna 3 da linha 1
    
    //Escreve a palavra PIC18F4520 a partir da coluna 3 da linha 1
    lcd_envia_byte(1,'P');      
    lcd_envia_byte(1,'I');
    lcd_envia_byte(1,'C');
    lcd_envia_byte(1,'1');
    lcd_envia_byte(1,'8');
    lcd_envia_byte(1,'F');
    lcd_envia_byte(1,'4');
    lcd_envia_byte(1,'5');
    lcd_envia_byte(1,'2');
    lcd_envia_byte(1,'0');
    
    lcd_envia_byte(0,0xc3); //Posiciona o cursor na coluna 3 da linha 2
    
    //Escreve a palavra LCD 8 BITS a partir da coluna 3 da linha 2
    lcd_envia_byte(1,'L');
    lcd_envia_byte(1,'C');
    lcd_envia_byte(1,'D');
    lcd_envia_byte(1,' ');
    lcd_envia_byte(1,'4');
    lcd_envia_byte(1,' ');
    lcd_envia_byte(1,'B');
    lcd_envia_byte(1,'I');
    lcd_envia_byte(1,'T');
    lcd_envia_byte(1,'S');

    while(1)                //Loop principal
    {
    }
}

