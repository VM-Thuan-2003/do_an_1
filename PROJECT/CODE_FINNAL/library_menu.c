
void menu(){
   if (push_btn(false,bt0)) countLevel++;

   if (countLevel >= maxLevel) countLevel = 0;
   
   if(countLevel != countLevelRev){
      countLevelRev = countLevel;
      lcd_clear();
   }
   
   switch(countLevel){
      case 0:
//! function to read time rtc from ds1307 sensor
         ds1307_read_time(8);

//! function to read temperature from ds18b20 sensor
         ds18b20_read_temp();

//! display info rtc and temperature for user
         lcd_dis_xx_yy_zz(4,0,dec_gio_ds,dec_phut_ds,dec_giay_ds,1,1,1);
         lcd_dis_temperature(2,1,dt_ng,dt_tp);

//! control delay and servo
         control_temperature(dt_ng,limitTemperature);
         control_servo();
         break;
      case 1:
//! function to read temperature from ds18b20 sensor
         ds18b20_read_temp();

//! change limit temperature
         limitTemperature += tick_btn(1,bt2);
         limitTemperature -= tick_btn(1,bt1);

//! display info temperature limit and sensor
         lcd_dis_temperature(2,0,dt_ng,dt_tp);
         lcd_dis_temperature_limit(2,1,limitTemperature);

//! when button 3 is true --> return menu 0
         if(tick_btn(1,bt3)) countLevel = 0;
         
         break;
      case 2:
//! function to read time rtc from ds1307 sensor
         ds1307_read_time(8);

//!
         lcd_setCursor(1,0);
         lcd_data("cai dat dong ho");
         if(bdn < 5){
            if(gt_mod != 0) xu_ly_choptat();
            phim_chon_hthi_mode();
            phim_up();
            phim_dw();
         }
         else if(bdn >= 10){
            bdn = 0;
            if(tg_chinh < 20) tg_chinh++;
            else{
               gt_mod = 0; tt_ht = 0;
               e_11 = true; e_22 = true; e_33 = true;
            }
            if(giay_tam!=giay_ds){
               giay_tam = giay_ds;
            }
         }
         giai_ma_gpg_ntn_thu_lcd();
         log_mode();
         break;
      case 3:
         lcd_setCursor(1,0);
         lcd_data("t/g cho ca an");
         if(bdn < 5){
            if(gt_mod != 0) xu_ly_choptat();
            phim_chon_mode_alarm();
            phim_up_eat();
            phim_dw_eat();
         }
         else if(bdn >= 10){
            bdn = 0;
            if(tg_chinh < 20) tg_chinh++;
            else{
               gt_mod = 0;
               e_11 = true; e_22 = true; e_33 = true;
            }
         }
         giai_ma_gpg_alarm_lcd();
         log_mode_alarm();
         break;
      case 4:
         lcd_setCursor(1,0);
         lcd_data("check com esp");
         lcd_setCursor(1,1);
//!         lcd_data(ccsc);
         if(tick_btn(1,bt3)) countLevel = 0;
         break;
      default:
         lcd_setCursor(2,0);
         lcd_data("Information");
         lcd_setCursor(0,1);
         lcd_data("Version: V1.0.0");

//! when button 3 is true --> return menu 0
         if(tick_btn(1,bt3)) countLevel = 0;
         break;
   }
}
