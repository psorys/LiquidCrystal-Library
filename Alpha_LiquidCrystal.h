#ifndef Alpha_LiquidCrystal_h
#define Alpha_LiquidCrystal_h

#include "AlphaLCDini.h"
#include "delays.h"
#include "stdbool.h"
#include <stdlib.h>
#include <string.h>


uint8_t numlines;
uint8_t numcols;

uint8_t _rs_pin;	// LOW: command.  HIGH: character.
uint8_t _rw_pin;	// LOW: write to LCD.  HIGH: read from LCD.
uint8_t _enable_pin; // activated by a HIGH pulse.

int8_t _scroll_count;
int8_t _x, _y,_setCursFlag;
uint8_t _direction;

uint8_t _data_pins[8];
uint8_t _numcols;
uint8_t _numlines;
uint8_t row_offsets[4];

uint8_t _displaycontrol;   //display on/off, cursor on/off, blink on/off
uint8_t _displaymode;      //text direction


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
#define LCD_Right 0
#define LCD_Left 1

#define DELAYPERCHAR 400
	
	void Alpha_LiquidCrystal_init(void);
	void Alpha_LiquidCrystal_begin(uint8_t cols, uint8_t lines, uint8_t dotsize);
	void Alpha_LiquidCrystal_begin2(uint8_t cols, uint8_t lines, uint8_t dotsize);
	
	void lcd_clear(void);
	void lcd_home(void);

	void lcd_noDisplay(void);
	void lcd_display(void);
	void lcd_noBlink(void);
	void lcd_blink(void);
	void lcd_noCursor(void);
	void lcd_cursor(void);
	
	void lcd_scrollDisplayLeft(void);
	void lcd_scrollDisplayRight(void);
	void lcd_leftToRight(void);
	void lcd_rightToLeft(void);
	void lcd_autoscroll(void);
	void lcd_noAutoscroll(void);
	
	void lcd_createChar(uint8_t, uint8_t[]);
	void lcd_setCursor(uint8_t, uint8_t);
	
	void write_strd(char []);	
	void write_str(char []);	

	void write(uint8_t);
	void command(uint8_t);
	
	
	void send8bits(uint8_t, bool);
	
#endif

