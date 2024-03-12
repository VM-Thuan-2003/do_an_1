#include <16f887.h>
#device  adc=10
#fuses   hs, nowdt, put, noprotect, nolvp
#use     delay(clock=20000000) // 20MHz
#use     i2c(master,slow,sda=pin_c4,scl=pin_c3)
#use     rs232(baud=9600, xmit=pin_c6,rcv=pin_c7)

/* Define name again to accordant user */
#define usi8  unsigned int8
#define usi16 unsigned int16
#define usi32 unsigned int32
#define si8   signed   int8
#define si16  signed   int16
#define si32  signed   int32

#define bool int1

#define enable  1
#define disable 0

#define on  1
#define off 0

#ifndef bt0
#define bt0    pin_b0
#endif 

#ifndef bt1
#define bt1    pin_b1
#endif

#ifndef bt2
#define bt2    pin_b2
#endif

#ifndef bt3
#define bt3    pin_b3
#endif

#ifndef pinServo
#define pinServo    pin_c1
#endif

void set_up_port(){
   set_tris_a(0xff);
   set_tris_b(0xff);
   set_tris_d(0x00); output_d(0x00);
   set_tris_e(0x00); output_e(0x00);
   set_tris_c(0x00); output_c(0x00);
}


