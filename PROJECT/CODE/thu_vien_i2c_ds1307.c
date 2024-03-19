#define ds13_addr_wr 0xd0
#define ds13_addr_rd 0xd1
//cap nhat time: giay-phut-gio-thu-ngay-thang-nam-madk_msds
usi8 time_w[9]={0x31,0x15,0x15,0x04,0x25,0x10,0x23,0x90,0x92}; // bcd
usi8 time_r[9]={0x30,0x30,0x10,0x08,0x20,0x02,0x20,0x90,0x96}; // dec

#define dec_giay_ds  time_r[0]
#define dec_phut_ds  time_r[1]
#define dec_gio_ds   time_r[2]
#define dec_thu_ds   time_r[3]
#define dec_ngay_ds  time_r[4]
#define dec_thang_ds time_r[5]
#define dec_nam_ds   time_r[6]

#define dec_ma_qd   time_w[8] 
#define dec_ma_ds   time_r[8]  

usi8 ds1307_decToBcd(usi8 val) {
    return ((val / 10 * 16) + (val % 10));
}

usi8 ds1307_bcdToDec(usi8 val) {
    return ((val / 16 * 10) + (val % 16));
}

void ds1307_read_dec_time(usi8 j){
   i2c_start();
   i2c_write(ds13_addr_wr);
   i2c_write(0x00);
   i2c_start();
   i2c_write(ds13_addr_rd);
   for(usi8 i = 0; i< j; i++) 
      time_r[i] = ds1307_bcdToDec(i2c_read());
   i2c_read(0);
   i2c_stop();
}

void ds1307_update_bcd_time(){
   i2c_start();
   i2c_write(ds13_addr_wr);
   i2c_write(0x00);
   for(usi8 i = 0; i < 9; i++)
      i2c_write(ds1307_decToBcd(time_r[i]));
   i2c_stop();
}

void ds1307_init(){
   ds1307_read_dec_time(9);
   if(dec_ma_qd != dec_ma_ds)
      i2c_start();
      i2c_write(ds13_addr_wr);
      i2c_write(0x00);
      for(usi8 i = 0; i < 9; i++) 
         i2c_write(time_w[i]);
      i2c_stop();
}
