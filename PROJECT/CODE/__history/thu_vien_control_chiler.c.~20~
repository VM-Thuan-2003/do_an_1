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

void control_servo(){

}
