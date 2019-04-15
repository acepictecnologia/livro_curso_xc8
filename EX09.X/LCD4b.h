#include <xc.h>				//Inclui o arquivo xc.h	

#define _XTAL_FREQ 8000000

#define EN_DIR   TRISEbits.TRISE1  //Atribui o nome EN_DIR ao bit 1 do reg. TRISE
#define RS_DIR   TRISEbits.TRISE0  //Atribui o nome RS_DIR ao bit 0 do reg. TRISE
#define DT4_DIR  TRISDbits.TRISD4  //Atribui o nome DT4_DIR ao bit 4 do reg. TRISD
#define DT5_DIR  TRISDbits.TRISD5  //Atribui o nome DT5_DIR ao bit 5 do reg. TRISD
#define DT6_DIR  TRISDbits.TRISD6  //Atribui o nome DT6_DIR ao bit 6 do reg. TRISD
#define DT7_DIR  TRISDbits.TRISD7  //Atribui o nome DT7_DIR ao bit 7 do reg. TRISD

#define EN       PORTEbits.RE1    //Atribui o nome EN ao pino 1 da porta E
#define RS       PORTEbits.RE0    //Atribui o nome RS ao pino 0 da porta E
#define DT4      PORTDbits.RD4    //Atribui o nome DT4 ao pino 4 da porta D
#define DT5      PORTDbits.RD5    //Atribui o nome DT5 ao pino 5 da porta D
#define DT6      PORTDbits.RD6    //Atribui o nome DT6 ao pino 6 da porta D
#define DT7      PORTDbits.RD7    //Atribui o nome DT7 ao pino 7 da porta D

//Protótipos das funções para o LCD 
void lcd_ini(void);
char set_bit(char cmd, char comp);
void lcd_cmd(char cmd);
void lcd_envia_byte(char nivel, char dado);


