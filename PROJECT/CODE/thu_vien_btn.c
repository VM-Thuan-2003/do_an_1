#define level_menu 5

usi8 dl_count;

usi8 dem_menu_tong_curr = 0;
usi8 dem_menu_tong_prev = 1;

usi8 dem_menu_1 = 0;
usi8 dem_menu_2 = 0;
usi8 dem_menu_3 = 0;
usi8 dem_menu_4 = 0;

void reset_all_dem(void){
   dem_menu_1 = 0;
   dem_menu_2 = 0;
   dem_menu_3 = 0;
   dem_menu_4 = 0;
}

bool nhan_btn_giu(usi16 dl, usi8 pin){
   if(!input(pin)){
      dl_count += 1; delay_us(500);
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
         else delay_ms(10);
         return true;   
      }
      return false;
   }
   return false;
}
