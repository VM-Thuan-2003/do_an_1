#include <thu_vien_do_an_1.c>

void select_menu(){
   dem_menu_tong_curr += nhan_btn_nha(1,bt0);
   if(dem_menu_tong_curr >= level_menu)
      dem_menu_tong_curr = 0;
   else{
      if(dem_menu_tong_curr != dem_menu_tong_prev){
         dem_menu_tong_prev = dem_menu_tong_curr;
         lcd_clear();
         reset_all_dem();
      }
      switch(dem_menu_tong_curr){
         case 0:
            /* hien thi man hinh chinh */
            lcd_dis_xx_yy_zz(4,0,dec_gio_ds,dec_phut_ds,dec_giay_ds);
            lcd_setCursor(2,1);
            lcd_data("ND: ");
            lcd_dis_2num_dot(dt_ng, 6, 1, enable, disable);
            lcd_dis_3num_dot(dt_tp_real, 8, 1, enable, enable);
            lcd_data(" oC");
            break;
         case 1:
            /* 
               hien thi nhiet do - nhiet do gioi han
               chinh nhiet do gioi han 
            */
            //dem_menu_1 += nhan_btn_nha(1,bt1);
            lcd_setCursor(0,0);
            lcd_data("menu 1");
            break;
         case 2:
            /*
               hien thi thoi gian va
               cai dat thoi gian - thoi gian dong bo
            */
            lcd_setCursor(0,0);
            lcd_data("menu 2.");
            break;
          case 3:
            /* cai dat thoi gian - thoi gian cho ca an*/
            lcd_setCursor(0,0);
            lcd_data("menu 3.");
            break;
          default:
            /* hien thi thong tin sp */
            lcd_setCursor(0,0);
            lcd_data("menu 4.");
            break;
      }
   }
}

void main(){
   set_up_init();
   lcd_init();
   lcd_log_info(1,enable);
   ds1307_init();
   ds18b20_khoi_tao();
   while(true){
      ds1307_read_dec_time(8);
      ds18b20_read_temp();
      select_menu();
   }
}  
