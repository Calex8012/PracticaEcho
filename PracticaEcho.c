#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

#define __DEBUG_SERIAL__ //Si comentas esta linea se deshabilita el debug por serial y el PIN_C6 puede ser usado en forma digital I/O

#ifdef __DEBUG_SERIAL__
   #define TX_232        PIN_C6
   #define RX_232        PIN_C7
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1,RCV=RX_232)
   #use fast_io(c)
#endif

int flagSerial=1;
char caracter;
int contador_buffer=0;
char buffer[30]={""};

#INT_RDA
void isr_RDA(void){
   flagSerial=1;
   caracter=getc();
   buffer[contador_buffer]=caracter;
   contador_buffer+=1;
}

void main (void){
   while(TRUE){
      set_tris_c(0x80);
      putc(caracter);
   }
}
