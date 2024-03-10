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

#ifndef btn0
#define btn0 pin_b
#endif

#ifndef btn1
#define btn1 pin_b
#endif

#ifndef btn2
#define btn2 pin_b
#endif

#ifndef btn3
#define btn3 pin_b
#endif

#ifndef btn4
#define btn4 pin_b
#endif

#ifndef btn5
#define btn5 pin_b
#endif

#define btn_limit_temp_up btn0
#define btn_limit_temp_dw btn1

void set_up_port(){
   
}


