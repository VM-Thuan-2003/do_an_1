//! button place
//! bt3 - bt2 - bt1 - bt0

usi8 countPush = 0;
usi8 countTick = 0;

bool push_btn(bool isRelease, usi8 pin){
//! isRelease == 0 --> push button is hold
//! isRelease == 1 --> push button is release
   if(!input(pin)){
      if(flag_10ms == true) countPush++;
//! check if countPush == 2 (20ms) --> debound button
      if(countPush >= 1){
         if(!input(pin)){
            if(isRelease == false) while(!input(pin));
            countPush = 0;
            return true;
         }
         return false;
      }
      return false;
   }
//!   countPush = 0;
   return false;
}

bool tick_btn(usi8 delay, usi8 pin){
//! dl is time delay that compute with 10ms for dl is 1
   if(!input(pin)){
      if(flag_10ms == true) countTick++;
//! check if countTick >= delay (delay * 10ms) --> time delay wanna to tick rising signal
      if(countTick >= delay){
         countTick = 0;
         return true;
      }
      return false;
   }
//!   countTick = 0;
   return false;
}
