#include <xc.h>                     //Inclui o arquivo xc.h

#include "../Bibliotecas/config.h"  //Inclui o arquivo config.h    

#define _XTAL_FREQ 8000000		//Define a frequ�ncia de clock utilizada

void main(void) {
    
 int i;		//Vari�vel de controle
    
 TRISB = 0b00000000;	//Direciona toda a porta B como sa�da	
 LATB = 0b00000000;	//Atribui n�vel 0 a todos os pinos da porta B
    
 while(1) {
              
     //Este c�digo representa o que deseja-se fazer

     /*Primeiro -> Faz os LEDs conectados � porta B piscarem por 5 vezes em
     intervalos de 100ms*/
     for (i=0; i<=4; i++)
     {
         LATB = 0b00000000;
         __delay_ms(100);
         LATB = 0b11111111;
         __delay_ms(100);
     }
       
     //Depois acenderemos somente o LED conectado ao pino 0 da porta B

     LATB = 0b00000001;
        
     /*Faremos aqui um la�o for de 0 a 7 (<=) onde temos um delay de 100ms e 
       ap�s faremos o deslocamento � esquerda de 1 bit do registrador LATB
       Assim, primeiramente LATB = 0b00000001, vai para LATB=0b00000010...*/

     for (i=0; i<=7; i++)
     {
         __delay_ms(100);
         LATB = LATB << 1;
     }
        
     /*Ao final LATB = 0b00000000;
        
       ent�o
        
       Depois acenderemos somente o LED conectado ao pino 7 da porta B*/
        
     LATB = 0B10000000;        
        
     /*Faremos aqui um la�o for de 0 a 7 (<=) onde temos um delay de 100ms e ap�s 
       faremos o deslocamento � direita de 1 bit do registrador LATB
       Assim, primeiramente LATB = 0b10000000, vai para LATB=0b01000000....*/

     for (i=0; i<=7; i++)
     {
         __delay_ms(100);
         LATB = LATB >> 1;
     }  
  }
}


