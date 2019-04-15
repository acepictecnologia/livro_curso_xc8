#include <xc.h>                     //Inclui o arquivo xc.h

#include "../Bibliotecas/config.h"  //Inclui o arquivo config.h 

#define _XTAL_FREQ 8000000

//Define nomes a registradores e pinos de determinadas portas
#define All_leds_dir TRISB		
#define All_leds     PORTB

#define L6 PORTBbits.RB5
#define L7 PORTBbits.RB6
#define L8 PORTBbits.RB7

#define B1_dir TRISBbits.TRISB0
#define B2_dir TRISCbits.TRISC0
#define B3_dir TRISAbits.TRISA4

#define B1 PORTBbits.RB0
#define B2 PORTCbits.RC0
#define B3 PORTAbits.RA4


void main(void)
{
    All_leds_dir = 0b00000000;	//Configura os pinos da porta B como saída
    All_leds     = 0b00000000;	//Coloca toda porta B em nível lógico 0
    
    B1_dir = 1;			//Configura o pino 0 da porta B como entrada
    B2_dir = 1;			//Configura o pino 0 da porta C como entrada
    B3_dir = 1;			//Configura o pino 4 da porta A como entrada    

    while(1)
    {
        if (B1 == 1)		//Se pino 0 da porta B = 1	
        {
            L6 = ~L6;  		//Inverte o estado do pino 5 da porta B
            while (B1);  	//Enquanto B1 estiver pressionado, aguarda
        }  
        
        if (B2 == 1)		//Se pino 0 da porta C = 1
        {
            L7 = ~L7;  		//Inverte o estado do pino 6 da porta B
            while (B2);  	//Enquanto B2 estiver pressionado, aguarda
        }

        if (B3 == 1)        //Se pino 4 da porta A = 1
        {
           L8 = ~L8; 		//Inverte o estado do pino 7 da porta B
           while (B3);  	//Enquanto B3 estiver pressionado, aguarda
        }
        
        __delay_ms(50);     //Atraso de 50ms
    }
}

