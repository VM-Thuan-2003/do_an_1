
usi8 tang_or_giam_bcd(unsigned int8 x, int1 sel){
   usi8 y, dv, ch, v;
   ch = (x>>4);
   dv = x& 0x0f;
   y = ch*10 + dv;
   if(sel == 0) y++;
   else         y--;
   ch = y/10; dv = y%10;
   v = (ch<<4)|dv;
   return v;
}

void tat_bat_2led_chinh(){
   if(gt_mod == 1 || gt_mod == 4) { e_11 = ~e_11; e_22 = true; e_33 = true;}
   else if(gt_mod == 2 || gt_mod == 5) { e_11 = true; e_22 = ~e_22; e_33 = true;}
   else if(gt_mod == 3 || gt_mod == 6) { e_11 = true; e_22 = true; e_33 = ~e_33;}
   else { e_11 = true; e_22 = true; e_33 = true;}
}

void giai_ma_gpg_lcd(){
   lcd_dis_xx_yy_zz(4,1,dec_gio_ds,dec_phut_ds,dec_giay_ds,e_33, e_22, e_11);
}

void giai_ma_ntn_lcd(){
   lcd_dis_xx_yy_zz(4,1,dec_ngay_ds,dec_thang_ds,dec_nam_ds,e_33, e_22, e_11);
}

void giai_ma_thu_lcd(){
   lcd_dis_xx_yy_zz(4,1,0x00,dec_thu_ds,0x00,0, e_22, 0);
}

void giai_ma_gpg_ntn_thu_lcd(){
   if(gt_mod == 0){
      if(tt_ht == 0 || tt_ht == 1) giai_ma_gpg_lcd();
      if(tt_ht == 2) giai_ma_ntn_lcd();
      if(tt_ht == 3) giai_ma_thu_lcd();
   }
   else{
      if(gt_mod < 4)       giai_ma_gpg_lcd();
      else if(gt_mod < 7)  giai_ma_ntn_lcd();
      else if(gt_mod == 7) giai_ma_thu_lcd();
   }
}

void xu_ly_choptat(){
   if(gt_mod != 0){
      tat_bat_2led_chinh();
   }
   else { e_11 = true; e_22 = true; e_33 = true;}
   
}

void phim_chon_hthi_mode(){
   if(nhan_btn_giu(2, bt3)){
      tt_ht = 1;
      if(tt_ht == 1){
         gt_mod++;
         if(gt_mod < 4) tt_ht = 1;
         else if(gt_mod < 7) tt_ht = 2;
         else if(gt_mod == 7) tt_ht = 3;
         else{
            gt_mod = 0;
            tt_ht = 0;
            dem_menu_tong_curr = 0;
         }
      }
      tg_chinh = 0;
      giai_ma_gpg_ntn_thu_lcd();
   }
}
void tang_giay(){
   if(giay_ds == 0x59) giay_ds = 0;
   else giay_ds = tang_or_giam_bcd(giay_ds, tang);
   ds1307_save_ds(0,giay_ds);
}
void tang_phut(){
   if(phut_ds == 0x59) phut_ds = 0;
   else phut_ds = tang_or_giam_bcd(phut_ds, tang);
   ds1307_save_ds(1,phut_ds);
}
void tang_gio(){
   if(gio_ds == 0x23) gio_ds = 0;
   else gio_ds = tang_or_giam_bcd(gio_ds, tang);
   ds1307_save_ds(2,gio_ds);
}
void chinh_tang_gpg(){
   switch(gt_mod){
      case 1:
         tang_giay();
         break;
      case 2:
         tang_phut();
         break;
      case 3:
         tang_gio();
         break;
      default: break;
   }
}
void tang_nam(){
   if(nam_ds == 0x99) nam_ds = 0;
   else nam_ds = tang_or_giam_bcd(nam_ds, tang);
   ds1307_save_ds(6,nam_ds);
}
void tang_thang(){
   if(thang_ds == 0x12) thang_ds = 1;
   else thang_ds = tang_or_giam_bcd(thang_ds, tang);
   ds1307_save_ds(5,thang_ds);
}
void tang_ngay(){
   if(ngay_ds == 0x31) ngay_ds = 1;
   else ngay_ds = tang_or_giam_bcd(ngay_ds, tang);
   ds1307_save_ds(4,ngay_ds);
}
void chinh_tang_ntn(){
   switch(gt_mod){
      case 4:
         tang_nam();
         break;
      case 5:
         tang_thang();
         break;
      case 6:
         tang_ngay();
         break;
      default: break;
   }
}
void chinh_tang_thu(){
   if(thu_ds == 8) thu_ds = 2;
   else thu_ds++;
   ds1307_save_ds(3,thu_ds);
}

void phim_up(){
   if(nhan_btn_giu(1, bt1)){
      tg_chinh = 0;
      if(gt_mod<4) chinh_tang_gpg();
      else if(gt_mod<7) chinh_tang_ntn();
      else if(gt_mod==7) chinh_tang_thu();
      e_11 = true; e_22 = true; e_33 = true;
      giai_ma_gpg_ntn_thu_lcd();
   }
}
void giam_giay(){
   if(giay_ds == 0) giay_ds = 0x59;
   else giay_ds = tang_or_giam_bcd(giay_ds,giam);
   ds1307_save_ds(0,giay_ds);
}
void giam_phut(){
   if(phut_ds == 0) phut_ds = 0x59;
   else phut_ds = tang_or_giam_bcd(phut_ds,giam);
   ds1307_save_ds(1,phut_ds);
}
void giam_gio(){
   if(gio_ds == 0) gio_ds = 0x23;
   else gio_ds = tang_or_giam_bcd(gio_ds,giam);
   ds1307_save_ds(2,gio_ds);
}
void chinh_giam_gpg(){
   switch(gt_mod){
      case 1:
         giam_giay();
         break;
      case 2:
         giam_phut();
         break;
      case 3:
         giam_gio();
         break;
      default: break;
   }
}
void giam_nam(){
   if(nam_ds == 0x0) nam_ds = 0x99;
   else nam_ds = tang_or_giam_bcd(nam_ds, giam);
   ds1307_save_ds(6,nam_ds);
}
void giam_thang(){
   if(thang_ds == 0x1) thang_ds = 12;
   else thang_ds = tang_or_giam_bcd(thang_ds, giam);
   ds1307_save_ds(5,thang_ds);
}
void giam_ngay(){
   if(ngay_ds == 0x1) ngay_ds = 21;
   else ngay_ds = tang_or_giam_bcd(ngay_ds, giam);
   ds1307_save_ds(4,ngay_ds);
}
void chinh_giam_ntn(){
   switch(gt_mod){
      case 1:
         giam_nam();
         break;
      case 2:
         giam_thang();
         break;
      case 3:
         giam_ngay();
         break;
      default: break;
   }
}
void chinh_giam_thu(){
   if(thu_ds == 2) thu_ds = 8;
   else thu_ds--;
   ds1307_save_ds(3,thu_ds);
}
void phim_dw(){
   if(nhan_btn_giu(1, bt2)){
      tg_chinh = 0;
      if(gt_mod<4) chinh_giam_gpg();
      else if(gt_mod<7) chinh_giam_ntn();
      else if(gt_mod==7) chinh_giam_thu();
      e_11 = true; e_22 = true; e_33 = true;
      giai_ma_gpg_ntn_thu_lcd();
   }
}
void log_mode(){
   lcd_setCursor(0, 1);
   if(tt_ht == 0) lcd_data(" N ");
   else if(tt_ht == 1) lcd_data("GPG");
   else if(tt_ht == 2) lcd_data("NTN");
   else if(tt_ht == 3) lcd_data(" T ");
   lcd_setCursor(13, 1);
   lcd_data(gt_mod + 0x30);
   if(gt_mod != 0){
      lcd_data(tg_chinh/10 + 0x30); lcd_data(tg_chinh%10 + 0x30);
   }
   else
      lcd_data("__");
}
