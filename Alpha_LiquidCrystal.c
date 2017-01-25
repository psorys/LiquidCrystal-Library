/*---------------------:::::||||||   Alpha_LiquidCrystal.c    |||||::::::-------------------------*/
/*      			Purpose: Alpha_LiquidCrystal library for LiquidCrystal.cpp					  */
/*     				Author: Piotr Sorys															  */
/*------------------------------------------------------------------------------------------------*/

#include "Alpha_LiquidCrystal.h"

/******************************************/
/**       hardware initialization        **/
/******************************************/

// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set: 
//    DL = 1; 8-bit interface data 
//    N = 0; 1-line display 
//    F = 0; 5x8 dot character font 
// 3. Display on/off control: 
//    D = 0; Display off 
//    C = 0; Cursor off 
//    B = 0; Blinking off 
// 4. Entry mode set: 
//    I/D = 1; Increment by 1 
//    S = 0; No shift 

void Alpha_LiquidCrystal_init(void){

	row_offsets[0] = 00;   // DDRAM addresses inside the HD44780 are strange: 0-nColumns-1 on line 0
	row_offsets[1] = 0x40; // 64-(63+nColumns) for line 1
	row_offsets[2] = 0x14; // 20- (19+nColumns) for line 2 --- NOTHING FROM 40-63 !
	row_offsets[3] = 0x54; // 84 - (83+nColumns) for line 3  -- so 80 characters tops out at #103 !

			alpha_lcd_8bit_init();
	
			_data_pins[0] = 0;
			_data_pins[1] = 1;
			_data_pins[2] = 2;
			_data_pins[3] = 3; 
			_data_pins[4] = 4;
			_data_pins[5] = 5;
			_data_pins[6] = 6;
			_data_pins[7] = 7; 
	
	
	_setCursFlag = 0;
	_direction = LCD_Right;
	
	Alpha_LiquidCrystal_begin(16, 2, 0x04); 
	
}

void Alpha_LiquidCrystal_begin(uint8_t cols, uint8_t lines, uint8_t dotsize){
	numcols=_numcols=cols;    //there is an implied lack of trust; the private version can't be munged up by the user.
	numlines=_numlines=lines;
	row_offsets[2] = cols + row_offsets[0];  //should autoadjust for 16/20 or whatever columns now
	row_offsets[3] = cols + row_offsets[1];
	Alpha_LiquidCrystal_begin2( cols,  lines,  dotsize);
	
}

void Alpha_LiquidCrystal_begin2(uint8_t cols, uint8_t lines, uint8_t dotsize){  
	
	uint8_t displayfunction = LCD_8BITMODE | LCD_2LINE | LCD_5x8DOTS;
	
	//wait til the vdd rises to at least 4.5V
	delay_ms(50);

	// Now we pull both RS and R/W low to begin commands
	lcdpin_RSset(false);
	lcdpin_Eset(false);
		
			
	// finally, set # lines, font size, etc.
	command(LCD_FUNCTIONSET | displayfunction);  
	
	// turn the display on with no cursor or blinking default
	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
  lcd_display();
	
	// clear it off
	lcd_clear();
	
	// Initialize to default text direction (for romance languages)
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	// set the entry mode
	command(LCD_ENTRYMODESET | _displaymode);	
	
}

///******************************************/
///**  high level commands, for the user!   */
///******************************************/

void lcd_clear(){
	command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
	//delayPerHome => more than 1.5 ms
	delay_ms(2);
	
	_scroll_count = 0;
}

void lcd_home()
{
	command(LCD_RETURNHOME); 
	//delayPerHome
	delay_ms(2);
	
	_scroll_count = 0;
}

// Turn the display on/off (quickly)
void lcd_noDisplay() {
	_displaycontrol &= ~LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);  //both chips
}
void lcd_display() {
	_displaycontrol |= LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);   //both chips
}

// Turns the underline cursor on/off
void lcd_noCursor() {
	_displaycontrol &= ~LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void lcd_cursor() {
	_displaycontrol |= LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void lcd_noBlink() {
	_displaycontrol &= ~LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void lcd_blink() {
	_displaycontrol |= LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void lcd_scrollDisplayLeft(void) {
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT); 
	_scroll_count++;
	if (_scroll_count >= 40) _scroll_count -= 40;   //  -39< scroll_count<39
}
void lcd_scrollDisplayRight(void) {
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);  //both chips
	_scroll_count--;
	if (_scroll_count <= -40) _scroll_count += 40;
}

// This is for text that flows Left to Right
void lcd_leftToRight(void) {
	_displaymode |= LCD_ENTRYLEFT;
	_direction = LCD_Right;
	command(LCD_ENTRYMODESET | _displaymode);     //both chips
}

// This is for text that flows Right to Left
void lcd_rightToLeft(void) {
	_displaymode &= ~LCD_ENTRYLEFT;
	_direction = LCD_Left;
	command(LCD_ENTRYMODESET | _displaymode);    //both chips
}


// Allows us to fill the first 8 CGRAM locations with custom characters
void lcd_createChar(uint8_t location, uint8_t charmap[]) {    
	location &= 0x7; // we only have 8 locations 0-7
		command(LCD_SETCGRAMADDR | (location << 3));
	
    uint32_t i;
	
		for ( i = 0; i<8; i++) {
			send8bits(charmap[i], true);
		}
}

void lcd_setCursor(uint8_t col, uint8_t row){     // this can be called by the user but is also called before writing some characters.
	
//	if ( row > _numlines ) {
//		row = _numlines-1;    // we count rows starting w/0
//	}
	
	_y = row;
	_x = col;
	_setCursFlag = 0;                                                 //user did a setCursor--clear the flag that may have been set in write()
	int8_t high_bit = row_offsets[row] & 0x40;                        // this keeps coordinates pegged to a spot on the LCD screen even if the user scrolls right or
	int8_t  offset = col + (row_offsets[row] &0x3f)  + _scroll_count; //left under program control. Previously setCursor was pegged to a location in DDRAM
	//the 3 guantities we add are each <40
	if (offset > 39) offset -= 40;                                    // if the display is autoscrolled this method does not work, however.
	if (offset < 0) offset += 40;
	offset |= high_bit;
	command(LCD_SETDDRAMADDR | (int)offset );
	
}

// This will 'right justify' text from the cursor 
void lcd_autoscroll(void) {           //to count the number of times we scrolled; here we'd need to keep track of microseconds and divide. I'm not going there.
	_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);   //both chips
}

// This will 'left justify' text from the cursor
void lcd_noAutoscroll(void) {
	_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;   //both chips
	command(LCD_ENTRYMODESET | _displaymode);
}


///*************************************************/
///**  mid level commands, for sending data/cmds   */
///*************************************************/

void command(uint8_t value) {
	send8bits(value, false);
	//delay_ms(2000);
	
}
void write_strd(char str[])	{
	
	uint32_t len = strlen(str);
	uint8_t value;
	char temp;
	
	for(int i = 0; i <= ( len - 1); i++ ){
		temp = str[i];
		value = (int)temp;
				
		write (value);
		delay_ms(250);
		
	}
	
}

void write_str(char str[])	{
	
	uint32_t len = strlen(str);
	uint8_t value;
	char temp;
	
	for(int i = 0; i <= ( len - 1); i++ ){
		temp = str[i];
		value = (int)temp;
				
		write (value);
			
	}
	
}

void write(uint8_t value) {

			
		if ((_scroll_count != 0) || (_setCursFlag != 0) ) lcd_setCursor(_x,_y);   //first we call setCursor and send the character
		if ((value != '\r') && (value != '\n') ) 
				send8bits(value, true);

		_setCursFlag = 0;
		if (_direction == LCD_Right) {                    // then we update the x & y location for the NEXT character
			_x++;
			if ((value == '\r') ||(_x >= _numcols) ) {      //romance languages go left to right
				
				_x = 0;
				_y++;
				_setCursFlag = 1;          //we'll need a setCursor() before the next char to move to begin of next line
			}
		} else {
			_x--;
			if ( (value == '\n') || (_x < 0)) {   //emulate right to left text mode which is built in but would be defeated by my code above
				_x = _numcols-1;
				_y++;
				_setCursFlag = 1;
			}
		}
		if (_y >= _numlines) _y = 0;   //wrap last line up to line 0
		
		
}



///****************************************/
///**  low level data pushing commands   **/
///****************************************/

void send8bits(uint8_t value, bool mode) {
	
	lcdpin_RSset(mode);
	
//	pinval_set(0, value & 0x01);
//	pinval_set(1, value & 0x02);
//	pinval_set(2, value & 0x04);
//	pinval_set(3, value & 0x08);	
//	pinval_set(4, value & 0x10);
//	pinval_set(5, value & 0x20);
//	pinval_set(6, value & 0x40);
//	pinval_set(7, value & 0x80);
	
	for (int i = 0; i < 8; i++) {
		pinval_set(i, (value >> i) & 0x01);
  }

	lcdpin_Eset(true);
	delay_us(2);
	lcdpin_Eset(false);
	delay_us(2);
	
	delay_us(DELAYPERCHAR); 
}
 
