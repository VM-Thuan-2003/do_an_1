#define maxLevel 5

usi8 countLevel = 0;
usi8 countLevelRev = 0;
void menu(){
   if (push_btn(false,bt3)) countLevel++;

   if (countLevel >= maxLevel) countLevel = 0;
   
   if(countLevel != countLevelRev){
      countLevelRev = countLevel;
      lcd_clear();
   }
   
   switch(countLevel){
      case 0:
         lcd_dis_xx_yy_zz(4,0,dec_gio_ds,dec_phut_ds,dec_giay_ds,1,1,1);
         
         break;
      case 1:
      
         break;
      case 2:
      
         break;
      case 3:
      
         break;
      case 4:
      
         break;
      default:
      
         break;
   }
}