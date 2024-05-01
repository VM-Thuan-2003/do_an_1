#define level_menu 6

usi8 dl_count;

usi8 dem_menu_tong_curr = 0;
usi8 dem_menu_tong_prev = 1;

bool nhan_btn_giu(usi16 dl, usi8 pin){
   if(!input(pin)){
      dl_count += 1; delay_us(25);
      if(dl_count >= dl){
         dl_count = 0;
         return true;
      }
      return false;
   }
   return false;
}

bool nhan_btn_nha(bool giu_nha, usi8 pin){
   if(!input(pin)){
      delay_ms(20);
      if(!input(pin)){
         if(giu_nha) while(!input(pin));
         //else delay_ms(5);
         return true;   
      }
      return false;
   }
   return false;
}

void test_btn(){
   if(!input(bt0)){
      delay_ms(20);
      if(!input(bt0)){
         lcd_setCursor(0,0);
         lcd_data("nut 0");
         while(!input(bt0));
      }
   }
   
   if(!input(bt1)){
      delay_ms(20);
      if(!input(bt1)){
         lcd_setCursor(0,0);
         lcd_data("nut 1");
         while(!input(bt1));
      }
   }
   
   if(!input(bt2)){
      delay_ms(20);
      if(!input(bt2)){
         lcd_setCursor(0,0);
         lcd_data("nut 2");
         while(!input(bt2));
      }
   }
   
   if(!input(bt3)){
      delay_ms(20);
      if(!input(bt3)){
         lcd_setCursor(0,0);
         lcd_data("nut 3");
         while(!input(bt3));
      }
   }
}
