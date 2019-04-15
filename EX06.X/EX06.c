#include <xc.h>                     //Inclui o arquivo xc.h

#include "../Bibliotecas/config.h"  //Inclui o arquivo config.h    

#define _XTAL_FREQ 8000000		//Define a frequência de clock utilizada

int i;		//Variável de controle para deslocamento dos bits

void piscaLeds(void);	//Protótipo da função piscaLeds()
        
void ledsEsq(void);     //Protótipo da função ledsEsq()
        
void ledsDir(void);     //Protótipo da função ledsDir()	

void main(void) {
    
    TRISB = 0b00000000;	//Direciona toda a porta B como saída	
    LATB = 0b00000000;	//Atribui nível 0 a todos os pinos da porta B
    
    while(1) {
        
        piscaLeds();	//Chama a função piscaLeds()
        
        ledsEsq();		//Chama a função ledsEsq()
        
        ledsDir();		//Chama a função ledsDir()	
        
    }
}

/*Função piscaLeds() -> Faz os LEDs conectados à porta B piscarem por 5 vezes em
  intervalos de 100ms*/

void piscaLeds(void)
{
    
    for (i=0; i<=4; i++)
        {
            LATB = 0b00000000;
            __delay_ms(100);
            LATB = 0b11111111;
            __delay_ms(100);
        }  
 
    //Acende somente o LED conectado ao pino 0 da porta B
   
    LATB = 0b00000001;
}

//Função ledEsq() faz o deslocamento à esquerda de 1 bit do registrador LATB

void ledsEsq(void)
{
    for (i=0; i<=7; i++)
        {
            __delay_ms(100);
            LATB = LATB << 1;
        } 

    //Acende somente o LED conectado ao pino 7 da porta B	
        
    LATB = 0B10000000;    
}

//Função ledDir() faz o deslocamento à direita de 1 bit do registrador LATB

void ledsDir(void)
{
   for (i=0; i<=7; i++)
        {
            __delay_ms(100);
            LATB = LATB >> 1;
        }   
}
