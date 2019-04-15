#include <xc.h>

//Protótipos para o módulo EUSART
void init_EUSART(void);
void escreve_EUSART(char c);
void string_EUSART(char *str);
char EUSART_le(void);
