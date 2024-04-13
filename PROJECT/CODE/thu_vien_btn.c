#define level_menu 5

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
      delay_ms(12);
      if(!input(pin)){
         if(giu_nha) while(!input(pin));
         else delay_ms(5);
         return true;   
      }
      return false;
   }
   return false;
}
