#include <18F4620.h>
#include <stdlib.h>

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

int flagSerial=0,indiceBuffRX=0;
char caracter;

#define MAX_SIZE_BUFFRX 30
char buffRX[MAX_SIZE_BUFFRX];


#INT_RDA
void isr_RDA(void){
   buffRX[indiceBuffRX]=getc();
   indiceBuffRX++;
   flagSerial=1;
   caracter=getc();
   if(indiceBuffRX>MAX_SIZE_BUFFRX){
      indiceBuffRX=0;
   }
   
}

void main (void){
   
   set_tris_c(0x80);
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_RDA);
   while(1){
      if(flagSerial==1){
         for(int8 indiceRecorridoBuffRX=0;indiceRecorridoBuffRX<indiceBuffRX;indiceRecorridoBuffRX++){
            printf("%c",(buffRX[indiceRecorridoBuffRX]));
            putc(caracter);
         }

         //printf("Caracter %c, Valor %u, Hexa %x",caracter+1,caracter+1,caracter+1);
         flagSerial=0;//limpiando la bandera
      }
         
   }
}
   

