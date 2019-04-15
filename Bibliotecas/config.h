// CONFIG1H
#pragma config OSC = HS	//Seleção do oscilador a cristal maior que 4MHz.
#pragma config FCMEN = OFF	//Desabilitada a monitoração por falha no clock
#pragma config IESO = OFF	/*Desabilitada comutação para oscilador 
			  interno/externo*/

// CONFIG2L
#pragma config PWRT = ON	//Habilitado Power-up Timer
#pragma config BOREN = OFF	//Desabilitado Brown-out Reset
#pragma config BORV = 3	//Tensão p/ Brown Out Reset

// CONFIG2H
#pragma config WDT = OFF		//Desabilitado o Watchdog Timer
#pragma config WDTPS = 32768	//Postscale para Watchdog Timer

// CONFIG3H
#pragma config CCP2MX = PORTC	/*Entrada/Saída do módulo CCP2 é multiplexado 
				  com RC1*/
#pragma config PBADEN = OFF  	/*Pinos 0 a 4 da Porta B configurados como 
				  pinos de I/O no reset*/
#pragma config LPT1OSC = OFF    
#pragma config MCLRE = ON     	/*Habilitado pino MCLR; desabilitado pino de 
				  entrada RE3*/

// CONFIG4L
#pragma config STVREN = ON      
#pragma config LVP = OFF        	//Habilitada programação por baixa tensão 
#pragma config XINST = OFF      

// CONFIG5L
#pragma config CP0 = OFF        
#pragma config CP1 = OFF        
#pragma config CP2 = OFF        
#pragma config CP3 = OFF        

// CONFIG5H
#pragma config CPB = OFF        
#pragma config CPD = OFF        
// CONFIG6L
#pragma config WRT0 = OFF       
#pragma config WRT1 = OFF       
#pragma config WRT2 = OFF       
#pragma config WRT3 = OFF   
    
// CONFIG6H
#pragma config WRTC = OFF       
#pragma config WRTB = OFF       
#pragma config WRTD = OFF       

// CONFIG7L
#pragma config EBTR0 = OFF      
#pragma config EBTR1 = OFF      
#pragma config EBTR2 = OFF      
#pragma config EBTR3 = OFF      

// CONFIG7H
#pragma config EBTRB = OFF  

