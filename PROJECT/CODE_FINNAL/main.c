#include <library_project.c>

void loop(){
//! function to read time rtc from ds1307 sensor
   ds1307_read_time(8);

//! function to read temperature from ds18b20 sensor
   ds18b20_read_temp();

//! function to access for change limit temperature, change time for time rtc, change time clock for eat fish, check com with esp, log version sys
   menu();

}

void main(){

//! setup enviroments
   setup_initialize();

//! setup ds1307 rtc
   ds1307_setup();

//! setup lcd display
   lcd_setup();

//! display info include: name project and name university
   log_lcd_initialize();

   while(true){

//! loop function is function suport in process of system
      loop();
   }
}