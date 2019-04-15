#include "LCD4b.h"

void lcd_ini()
{		      	//Inc�cio da fun��o lcd_ini()	
char i;                 	//Vari�vel de controle para envio dos comandos

TRISD = 0b00000000;     	//Todos os pinos da porta D configurados como sa�da
TRISEbits.TRISE1 = 0;   	//Pino 1 da porta E configurado como sa�da
TRISEbits.TRISE0 = 0;   	//Pino 0 da porta E configurado como sa�da

PORTD = 0b00000000;     	//Toda porta D em n�vel l�gico 0
PORTEbits.RE0 = 0;      	//Pino 0 da porta E em n�vel 0
PORTEbits.RE1 = 0;      	//Pino 1 da porta E em n�vel 0

__delay_ms(15);         	//Atraso de 15ms

//Envia o comando 0x30 ao LCD por 3 vezes, em intervalos de 5ms
for(i=0;i<=2;i++)
   {
   lcd_cmd(0x30);
   __delay_ms(5);
   }

   lcd_cmd(0x02);	  //LCD deve trabalhar com 4 bits de dados
   __delay_us(40);	  //Atraso de 40us 
   lcd_cmd(0x28);   //Comunica��o em 4 bits, display de 2 linhas e matriz 7X5
   __delay_us(40);  //Atraso de 40us
   lcd_cmd(0x01);   //Limpa a mem�ria do LCD
   __delay_ms(2);   //Atraso de 2ms
   lcd_cmd(0x0C);   //Liga o display sem cursor
   __delay_us(40);  //Atraso de 40us
   lcd_cmd(0x06);   //Deslocamento do cursor � direita ap�s um novo caractere
   __delay_us(40);  //Atraso de 40us

}		  //Final da fun��o lcd_ini()


char set_bit(char cmd, char comp)
{   //In�cio da fun��o set_bit()
    //Compara as vari�veis cmd e comp  
    if ((cmd & comp) >= 1)  //Se o resultado for maior ou igual a 1
        return 1;           //Retorna o valor 1
    else                    //Se n�o
        return 0;           //Retorna o valor 0
}   //Final da fun��o set_bit()


void lcd_cmd(char cmd)
{   //In�cio da fun��o lcd_cmd()
    /*Faz a chamada � a fun��o set_bit() com os valores a serem comparados. O 
      valor retornado ser� atribu�do a cada 1 dos pinos D4, D5, D6 e D7 do LCD*/
    PORTDbits.RD4 = set_bit(cmd,0b00010000);
    PORTDbits.RD5 = set_bit(cmd,0b00100000);
    PORTDbits.RD6 = set_bit(cmd,0b01000000);
    PORTDbits.RD7 = set_bit(cmd,0b10000000);
    
    PORTEbits.RE1 = 1;  //Coloca o pino 1 da porta E (EN) em 1
    PORTEbits.RE1 = 0;  //Coloca o pino 1 da porta E (EN) em 0

    __delay_us(100);    //Atraso de 100us
        
    /*Faz a chamada � a fun��o set_bit() com os valores a serem comparados. O 
      valor retornado ser� atribu�do a cada 1 dos pinos D4, D5, D6 e D7 do LCD*/
    PORTDbits.RD4 = set_bit(cmd,0b00000001);
    PORTDbits.RD5 = set_bit(cmd,0b00000010);
    PORTDbits.RD6 = set_bit(cmd,0b00000100);
    PORTDbits.RD7 = set_bit(cmd,0b00001000);
    
    PORTEbits.RE1 = 1;  //Coloca o pino 1 da porta E (EN) em 1
    PORTEbits.RE1 = 0;  //Coloca o pino 1 da porta E (EN) em 0	    
}   //Final da fun��o lcd_cmd()
	

void lcd_envia_byte(char nivel, char dado)
{			 //In�cio da fun��o lcd_envia_byte()
    PORTEbits.RE0 = nivel;  //Habilita comando ou escrita para o LCD
    __delay_us(100);          //Atraso de 100us
    PORTEbits.RE1 = 0;      //Coloca o pino 1 da porta E (EN) em 0
    lcd_cmd(dado);          //chama a fun��o lcd_cmd com o par�metro 'dado'
}

void lcd_escreve_bf(char lin, char col, char *str)
{
    char end;                   /*Vari�vel de controle para o posicionamento 
                                  do cursor*/

    if (lin == 1) {             //Caso a vari�vel lin seja 1
        end = col + 0x80 - 1;	//Posiciona o cursor na coluna informada
    } 
    else if(lin == 2) {         //Caso a vari�vel lin seja 2
        end = col + 0xC0 - 1;	//Posiciona o cursor na coluna informada
    }

    lcd_envia_byte(0,end); 		/*Posiciona o cursor de acordo com a vari�vel 
                                end*/

    //Escreve a string no LCD
    while (*str){			
        lcd_envia_byte(1,*str);
        str++;
    }
}


