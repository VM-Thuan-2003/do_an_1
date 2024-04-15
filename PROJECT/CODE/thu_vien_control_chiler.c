void control_temperature(int8 nd_ss, int8 gh){
   if(nd_ss > gh){
   // water is hot
      output_bit(pinCold, 1);
      output_bit(pinHot,  0);
   }
   else{
   // water is cold
      output_bit(pinCold, 0);
      output_bit(pinHot,  1);
   }
}

void servo_degree_0(){
   unsigned int i;
   for(i = 0; i < 50; i++){
      output_bit(pinServo, 1);
      Delay_us(800); // pulse of 800us
      output_bit(pinServo, 0);
      Delay_us(19200);
   }
}

void servo_degree_90(){
   unsigned int i;
   for(i = 0; i < 50; i++){
      output_bit(pinServo, 1);
      Delay_us(1500); // pulse of 1500us
      output_bit(pinServo, 0);
      Delay_us(18500);
   }
}

void servo_degree_180(){
   unsigned int i;
   for(i = 0; i < 50; i++){
      output_bit(pinServo, 1);
      Delay_us(2200); // pulse of 2200us
      output_bit(pinServo, 0);
      Delay_us(17800);
   }
}

void control_servo(){
   if(dec_gio_ds == dec_gio_eat && dec_phut_ds == dec_phut_eat && dec_giay_ds == dec_giay_eat){
      flag_servo = true;
   }
   if(flag_servo){
      servo_degree_90();
      //output_bit(pinServo, 1);
   }
   else{
      servo_degree_0();
      //output_bit(pinServo, 0);
   }
}
