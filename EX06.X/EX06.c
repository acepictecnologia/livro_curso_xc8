#include <xc.h>                     //Inclui o arquivo xc.h

#include "../Bibliotecas/config.h"  //Inclui o arquivo config.h    

#define _XTAL_FREQ 8000000		//Define a frequ�ncia de clock utilizada

int i;		//Vari�vel de controle para deslocamento dos bits

void piscaLeds(void);	//Prot�tipo da fun��o piscaLeds()
        
void ledsEsq(void);     //Prot�tipo da fun��o ledsEsq()
        
void ledsDir(void);     //Prot�tipo da fun��o ledsDir()	

void main(void) {
    
    TRISB = 0b00000000;	//Direciona toda a porta B como sa�da	
    LATB = 0b00000000;	//Atribui n�vel 0 a todos os pinos da porta B
    
    while(1) {
        
        piscaLeds();	//Chama a fun��o piscaLeds()
        
        ledsEsq();		//Chama a fun��o ledsEsq()
        
        ledsDir();		//Chama a fun��o ledsDir()	
        
    }
}

/*Fun��o piscaLeds() -> Faz os LEDs conectados � porta B piscarem por 5 vezes em
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

//Fun��o ledEsq() faz o deslocamento � esquerda de 1 bit do registrador LATB

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

//Fun��o ledDir() faz o deslocamento � direita de 1 bit do registrador LATB

void ledsDir(void)
{
   for (i=0; i<=7; i++)
        {
            __delay_ms(100);
            LATB = LATB >> 1;
        }   
}
