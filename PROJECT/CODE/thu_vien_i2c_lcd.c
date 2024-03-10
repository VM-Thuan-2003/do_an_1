#define pcf8574_addr_wr 0x4E //0b01001110
#define pcf8574_addr_rd 0x4F //0b01001111

void i2c_reset(){
   i2c_start();
   i2c_stop();
}

void i2c_setup_write(){
   i2c_start();
   i2c_write(pcf8574_addr_wr);
}

void i2c_write_1byte(usi8 payload){
   i2c_start();
   i2c_write(pcf8574_addr_wr);
   i2c_write(payload);
   i2c_stop();
}
