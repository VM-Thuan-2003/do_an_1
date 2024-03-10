#define lcd_cols 16
#define lcd_rows 2

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En 0B00000100  // Enable bit
#define Rw 0B00000010  // Read/Write bit
#define Rs 0B00000001  // Register select bit

void write4bits(usi8 value);
void expanderWrite(usi8 _data);
void pulseEnable(usi8 _data);
void lcd_command(usi8 value);
void lcd_display();
void lcd_clear();
void lcd_home();
void lcd_send(usi8 value, usi8 mode);
void lcd_data(usi8 value);

usi8 _displayfunction;
usi8 _displaycontrol;
usi8 _displaymode;
usi8 _numlines;
usi8 _cols;
usi8 _rows;
usi8 _backlightval;

void lcd_init(){
   _cols = lcd_cols; // 16
   _rows = lcd_rows; // 2
   _backlightval = LCD_NOBACKLIGHT; // back light is off
   
   i2c_setup_write(); // setup i2c
   _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
   
   _displayfunction |= LCD_2LINE;
   _numlines = _rows; // 2
   
   delay_ms(40);
   
   expanderWrite(_backlightval); // back light is on
   delay_ms(100);
   
   /*
   It is try to set use 4bit in 3 time
   write4bits(0x03 << 4);
   delay_ms(5);
   
   write4bits(0x03 << 4);
   delay_ms(5);
   
   write4bits(0x03 << 4);
   delay_ms(5);
   */
   
   write4bits(0x02 << 4); // set using 4bit for lcd16x2
   
   lcd_command(LCD_FUNCTIONSET | _displayfunction);
   
   _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
   lcd_display();
   
   lcd_clear();
   
   _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
   lcd_command(LCD_ENTRYMODESET | _displaymode);
   
   lcd_home();
}

void lcd_clear(){
   lcd_command(LCD_CLEARDISPLAY);
   delay_ms(20);
}

void lcd_home(){
   lcd_command(LCD_RETURNHOME);
   delay_ms(20);
}

void lcd_setCursor(usi8 col, usi8 row){
   int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
   if ( row > _numlines ) {
      row = _numlines-1;
   }
   lcd_command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void lcd_display() {
   _displaycontrol |= LCD_DISPLAYON;
   lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void lcd_command(usi8 value){
   lcd_send(value,0);
}

void lcd_data(usi8 value){
   lcd_send(value,Rs);
}

void lcd_send(usi8 value, usi8 mode) {
   usi8 highnib=value&0xf0;
   usi8 lownib=(value<<4)&0xf0;
   write4bits((highnib)|mode);
   write4bits((lownib)|mode); 
}

void write4bits(usi8 value) {
   expanderWrite(value);
   pulseEnable(value);
}

void expanderWrite(usi8 _data){
   i2c_write_1byte(_data|_backlightval);
}

void pulseEnable(usi8 _data){
   expanderWrite(_data | En);
   delay_us(1);
   expanderWrite(_data & ~En);
   delay_us(50);
}

/* Library modify in User*/
void lcd_log_info(usi16 time_s, bool ena_time){
   lcd_setCursor(1,0);
   lcd_data("Do an 1 - HKII");
   lcd_setCursor(3,1);
   lcd_data("SPKT-TPHCM");
   if(ena_time == enable){
      delay_ms(time_s*1000);
      lcd_clear();
   }
}
