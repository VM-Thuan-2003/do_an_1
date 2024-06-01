#include <touch.c>
#define search_rom       0xf0
#define read_rom         0x33
#define match_rom        0x55
#define skip_rom         0xcc
#define alarm_search     0xec
#define read_scratchpad  0xbe
#define write_scratchpad 0x4e
#define copy_scratchpad  0x48
#define convert_t        0x44

si16 temperature;
usi8 dt_ng, dt_ngt;
usi16 dt_tp, dt_tpt;
usi16 tt;

bool ds18b20_start(){
   output_low(pin_ds18b20);
   output_drive(pin_ds18b20);
   delay_us(500);
   output_float(pin_ds18b20);
   delay_us(100);
   if(!input(pin_ds18b20)){
      delay_us(400);
      return true;
   }
   return false;
}

void ds18b20_write_bit(bool value){
   output_low(pin_ds18b20);
   output_drive(pin_ds18b20);
   delay_us(2);
   output_bit(pin_ds18b20, value);
   delay_us(80);
   output_float(pin_ds18b20);
   delay_us(2);
}

void ds18b20_write_byte(int8 value){
   for(int8 i = 0; i < 8; i++)
      ds18b20_write_bit(bit_test(value,i));
}

bool ds18b20_read_bit(){
   bool value;
   output_low(pin_ds18b20);
   output_drive(pin_ds18b20);
   delay_us(2);
   output_float(pin_ds18b20);
   delay_us(5);
   value = input(pin_ds18b20);
   delay_us(100);
   return value;
}

int8 ds18b20_read_byte(){
   int8 value = 0;
   for(int8 i = 0; i < 8; i++)
      shift_right(&value,1,ds18b20_read_bit());
   return value;
}

bool ds18b20_read_temp_c2(int16 *raw_temp_value){
   if(!ds18b20_start())
      return false;
   ds18b20_write_byte(skip_rom);
   ds18b20_write_byte(convert_t);
   while(ds18b20_read_byte() == 0);
   if(!ds18b20_start())
      return false;
   ds18b20_write_byte(skip_rom);
   ds18b20_write_byte(read_scratchpad);
   *raw_temp_value = ds18b20_read_byte();
   *raw_temp_value |= (int16)(ds18b20_read_byte()) << 8;
   return true;
}

void ds18b20_read_temp(){
   if(ds18b20_read_temp_c2(&temperature)){
      isDs18b20 = true;
      dt_ng = temperature>>4;
      tt = temperature & 0x000f;
      dt_tp = (tt*625)/10;
   }
   else isDs18b20 = false;
}