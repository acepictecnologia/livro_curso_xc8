#include <xc.h>                     		//Inclui o arquivo header xc.h
#include <stdio.h>                  		//Inclui o arquivo stdio.h 

#include "../Bibliotecas/config.h"  		//Inclui o arquivo config.h
#include "../Bibliotecas/LCD4b.h"       	//Inclui o arquivo LCD4b.h

int conta = 0;                 	//Variável de contagem
char bufferLCD[16];

void main(void)
{
    ADCON1 = 0x0F;              //Desabilita todos os canais A/D
       
    lcd_ini();                  //Inicializa LCD
               
    lcd_envia_byte(0,0x80);     //Posiciona o cursor na coluna 1 da linha 1
    
    sprintf(bufferLCD, "CONTAGEM: 000"); 
    
    lcd_escreve_bf(bufferLCD);
       
    while(1)                    //Loop principal
    { 
        lcd_envia_byte(0,0x8A); //Posiciona o cursor na coluna 11 da linha 1
    
        //Armazena em bufferLCD a string a ser enviada ao LCD
        sprintf(bufferLCD, "%03d", conta);
        
        lcd_escreve_bf(bufferLCD);
        
        conta++;
        
        if (conta > 999) conta = 0;
               
        __delay_ms(1000);      //Atraso de 500ms
    }
}

