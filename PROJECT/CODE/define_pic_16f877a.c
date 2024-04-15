#include <16f877a.h>
#device  adc=10
#fuses   hs, nowdt, put, noprotect, nolvp
#use     delay(clock=20MHz) 
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

#ifndef bt4
#define bt4    pin_b4
#endif

#ifndef pinServo
#define pinServo    pin_c1
#endif

#ifndef pinCold
#define pinCold     pin_d6
#endif

#ifndef pinHot
#define pinHot      pin_d7
#endif

usi8 gh_nd = 25;

usi8 giay_tam, bdn, tt_ht = 0;
si8 gt_mod = 0, tg_chinh = 0;

#define tang 0
#define giam 1

bool e_11, e_22, e_33;

usi8 eat_hh, eat_pp, eat_ss;

bool flag_servo;
usi8 count_servo = 0;

#int_timer1
void interrupt_timer1()
{
   bdn++;
   set_timer1(3036);
   if(flag_servo == true){
      if(count_servo < 100) count_servo++; // 10s
      else{
         count_servo = 0;
         flag_servo = false;
      }
   }
}

void set_up_init(){
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   set_timer1(3036);
   
   enable_interrupts(global);
   enable_interrupts(int_timer1);
   
   setup_timer_2(t2_div_by_16, 249, 1);
   set_pwm2_duty(0);
   
   tt_ht = 0;
   bdn = 0; gt_mod = 0;
   
   e_11 = true;
   e_22 = true;
   e_33 = true;
   
   flag_servo = false;
   
   gh_nd = 25;
   eat_hh = 0x09; eat_pp = 0x34; eat_ss = 0x01;
   
   set_tris_a(0xff);
   set_tris_b(0xff);
   set_tris_d(0x00); output_d(0x00);
   set_tris_e(0x00); output_e(0x00);
   set_tris_c(0x00); output_c(0x00);
}


