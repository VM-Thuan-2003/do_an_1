#include <16f877a.h>
#fuses   hs, nowdt, put, noprotect, nolvp
#use     delay(clock=20MHz) 
#use     i2c(master,slow,sda=pin_c4,scl=pin_c3)
#use     rs232(baud=9600, xmit=pin_c6,rcv=pin_c7)

void main(){
   set_tris_b (0x00);
   set_tris_d (0x00);
   output_bit(PIN_B5, 0);
   output_bit(PIN_D6, 0); 
   output_bit(PIN_D7, 0); 
   while(1){
   output_bit(PIN_B5, 1);
   output_bit(PIN_D6, 1);
   output_bit(PIN_D7, 0);
   delay_ms(1000);
   output_bit(PIN_B5, 0);
   output_bit(PIN_D6, 0); 
   output_bit(PIN_D7, 1); 
   delay_ms(1000);
   }
}
