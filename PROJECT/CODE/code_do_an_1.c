#include <thu_vien_do_an_1.c>
si16 temp;
void main(){
   set_up_port();
   lcd_init();
   lcd_log_info(1,enable);
   while(true){
      if(ds18b20_read_temp_c2(&temp))
         ds18b20_lcd_data(temp,0,0);
      else ds18b20_no_ds18b(0,0);
   }
}  
