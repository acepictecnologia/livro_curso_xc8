#include <xc.h>			//Inclui o arquivo header xc.h

#include "../Bibliotecas/config.h"	//Inclui o arquivo config.h

#define _XTAL_FREQ 8000000      	//Define a frequência de clock utilizada

//Protótipos das funções para o LCD 
void lcd_ini(void);
char set_bit(char cmd, char comp);
void lcd_cmd(char cmd);
void lcd_envia_byte(char nivel, char dado);

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
}			//Final da função principal (main)

void lcd_ini()
{		      	//Incício da função lcd_ini()	
char i;                 	//Variável de controle para envio dos comandos

TRISD = 0b00000000;     	//Todos os pinos da porta D configurados como saída
TRISEbits.TRISE1 = 0;   	//Pino 1 da porta E configurado como saída
TRISEbits.TRISE0 = 0;   	//Pino 0 da porta E configurado como saída

PORTD = 0b00000000;     	//Toda porta D em nível lógico 0
PORTEbits.RE0 = 0;      	//Pino 0 da porta E em nível 0
PORTEbits.RE1 = 0;      	//Pino 1 da porta E em nível 0

__delay_ms(15);         	//Atraso de 15ms

//Envia o comando 0x30 ao LCD por 3 vezes, em intervalos de 5ms
for(i=0;i<=2;i++)
   {
   lcd_cmd(0x30);
   __delay_ms(5);
   }

   lcd_cmd(0x02);	  //LCD deve trabalhar com 4 bits de dados
   __delay_us(40);	  //Atraso de 40us 
   lcd_cmd(0x28);   //Comunicação em 4 bits, display de 2 linhas e matriz 7X5
   __delay_us(40);  //Atraso de 40us
   lcd_cmd(0x01);   //Limpa a memória do LCD
   __delay_ms(2);   //Atraso de 2ms
   lcd_cmd(0x0C);   //Liga o display sem cursor
   __delay_us(40);  //Atraso de 40us
   lcd_cmd(0x06);   //Deslocamento do cursor à direita após um novo caractere
   __delay_us(40);  //Atraso de 40us

}		  //Final da função lcd_ini()


char set_bit(char cmd, char comp)
{   //Início da função set_bit()
    //Compara as variáveis cmd e comp  
    if ((cmd & comp) >= 1)  //Se o resultado for maior ou igual a 1
        return 1;           //Retorna o valor 1
    else                    //Se não
        return 0;           //Retorna o valor 0
}   //Final da função set_bit()


void lcd_cmd(char cmd)
{   //Início da função lcd_cmd()
    /*Faz a chamada à a função set_bit() com os valores a serem comparados. O 
      valor retornado será atribuído a cada 1 dos pinos D4, D5, D6 e D7 do LCD*/
    PORTDbits.RD4 = set_bit(cmd,0b00010000);
    PORTDbits.RD5 = set_bit(cmd,0b00100000);
    PORTDbits.RD6 = set_bit(cmd,0b01000000);
    PORTDbits.RD7 = set_bit(cmd,0b10000000);
    
    PORTEbits.RE1 = 1;  //Coloca o pino 1 da porta E (EN) em 1
    PORTEbits.RE1 = 0;  //Coloca o pino 1 da porta E (EN) em 0

    __delay_us(100);    //Atraso de 100us
        
    /*Faz a chamada à a função set_bit() com os valores a serem comparados. O 
      valor retornado será atribuído a cada 1 dos pinos D4, D5, D6 e D7 do LCD*/
    PORTDbits.RD4 = set_bit(cmd,0b00000001);
    PORTDbits.RD5 = set_bit(cmd,0b00000010);
    PORTDbits.RD6 = set_bit(cmd,0b00000100);
    PORTDbits.RD7 = set_bit(cmd,0b00001000);
    
    PORTEbits.RE1 = 1;  //Coloca o pino 1 da porta E (EN) em 1
    PORTEbits.RE1 = 0;  //Coloca o pino 1 da porta E (EN) em 0	    
}   //Final da função lcd_cmd()
	

void lcd_envia_byte(char nivel, char dado)
{			 //Início da função lcd_envia_byte()
    PORTEbits.RE0 = nivel;  //Habilita comando ou escrita para o LCD
    __delay_us(100);          //Atraso de 100us
    PORTEbits.RE1 = 0;      //Coloca o pino 1 da porta E (EN) em 0
    lcd_cmd(dado);          //chama a função lcd_cmd com o parâmetro 'dado'
}

