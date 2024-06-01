//! config mode to operation of pic16f877a
#include <16f877a.h>
#device  adc=10
#fuses   hs, nowdt, put, noprotect, nolvp
#use     delay(clock=20MHz) 
#use     i2c(master,slow,sda=pin_c4,scl=pin_c3)
#use     rs232(baud=9600, xmit=pin_c6,rcv=pin_c7)

//! define name again to user
#define usi8  unsigned int8
#define usi16 unsigned int16
#define usi32 unsigned int32
#define si8   signed   int8
#define si16  signed   int16
#define si32  signed   int32
#define bool int1

//! define variables
bool flag_10ms = false;
bool isDs18b20 = false;

//! define button to use
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

//! define pin sensors
#define pin_ds18b20 pin_a0

//! define pin controls
#ifndef pinServo
#define pinServo    pin_c1
#endif

#ifndef pinDLCold
#define pinDLCold     pin_d6
#endif

#ifndef pinDLHot
#define pinDLHot      pin_d7

#ifndef ledTest
#define ledTest      pin_b5

#int_timer1
void interrupt_timer1()
{
   set_timer1(59286);
   flag_10ms = !flag_10ms;
}

void setup_initialize(){
//! set up timer 1 to timer count is 10ms of one cycle
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   set_timer1(59286);

//! enable interrupt timer 1
   enable_interrupts(global);
   enable_interrupts(int_timer1);

//! setup mode for all gpio of pic16f877a
   set_tris_a(0xff);
   set_tris_b(0xdf);
   set_tris_d(0x00); output_d(0x00);
   set_tris_e(0x00); output_e(0x00);
   set_tris_c(0x00); output_c(0x00);

//! setup variable initialize
   flag_10ms = false;
   isDs18b20 = false;
}
