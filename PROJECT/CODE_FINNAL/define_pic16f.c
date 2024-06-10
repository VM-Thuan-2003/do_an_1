//! config mode to operation of pic16f877a
#include <16f877a.h>
#device  adc=10
#fuses   hs, nowdt, put, noprotect, nolvp
#use     delay(clock=20MHz) 
#use     i2c(master,slow,sda=pin_c4,scl=pin_c3)
#use     rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7, bits = 8, stream=UART_STREAM)
#use fast_io(C)
#use fast_io(D)
#use fast_io(E)
#use fast_io(B)
#use fast_io(A)

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
bool flag_10s = false;
bool isDs18b20 = false;

usi8 limitTemperature = 25;

usi16 tick_10ms;
usi16 tick_100ms;

usi8 giay_tam, bdn, tt_ht = 0;
si8 gt_mod = 0, tg_chinh = 0;

bool e_11, e_22, e_33;

usi8 eat_hh, eat_pp, eat_ss;

#define maxLevel 6

usi8 countLevel = 0;
usi8 countLevelRev = 0;

bool flag_servo;
usi8 count_servo = 0;

#define tang false
#define giam true

//! define available for ds18b20
usi16 temperature;
usi8 dt_ng;
usi16 dt_tp;
usi16 tt;

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
#endif

#ifndef ledTest
#define ledTest       pin_b5
#endif

#include <library_uart.c>

#int_timer1
void interrupt_timer1()
{
   set_timer1(59286);
   
   flag_10ms = !flag_10ms;

   tick_10ms++;

//! when tick_10ms >= 10 --> 100ms
   if(tick_10ms >= 10){
      bdn++;
      tick_10ms = 0;
      
      if(tick_100ms < 100) tick_100ms++;
      else{
         tick_100ms = 0;
         flag_10s = true;
      }
      
//! disable flag servo on --> flag_servo >> false
      if(flag_servo == true){
         if(count_servo < 100) count_servo++; // 10s
         else{
            count_servo = 0;
            flag_servo = false;
         }
      }
      else flag_servo = 0;
   }
}

void setup_initialize(){
//! set up timer 1 to timer count is 10ms of one cycle
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   set_timer1(59286);

//! enable interrupt timer 1 and read data uart
   enable_interrupts(global);
   enable_interrupts(int_timer1);
   enable_interrupts(int_rda);


//! setup mode for all gpio of pic16f877a
   set_tris_a(0xff);
   set_tris_b(0xdf);
   set_tris_d(0x00); //output_d(0x00);
   set_tris_e(0x00); //output_e(0x00);
   set_tris_c(0x98); //output_c(0x98);
 
//! setup variable initialize
   flag_10ms = false;
   flag_10s  = false;
   isDs18b20 = false;
   
   limitTemperature = 25;
   
   e_11 = true; e_22 = true; e_33 = true;
   
   eat_hh = 0x09; eat_pp = 0x30; eat_ss = 0x30;
}
