#include "delays.h"
#include "Alpha_LiquidCrystal.h"
#include "AlphaLCDini.h"
#include <string.h>

void setup(void);

int main(void) {

setup();

while(1) {
	
	write(smile_tab);
	delay_ms(400);
	lcd_setCursor(0, 0);
	write(blink_tab);
	delay_ms(400);
	lcd_setCursor(0, 0);
	
}


}

void setup(){

	uint8_t smiley[8] = {0x00, 0x11, 0x00, 0x00, 0x11, 0x0E, 0x00, 0x00};
	uint8_t smile_tab = 0x00;

	uint8_t blink[8] = {0x00, 0x13, 0x00, 0x00, 0x11, 0x0E, 0x00, 0x00};
	uint8_t blink_tab = 0x01;


	Alpha_LiquidCrystal_init();
	lcd_createChar(0, smiley);
	lcd_createChar(1, blink);

	lcd_cursor();
	lcd_clear();
	lcd_blink();

	write_strd(" Hello World!!!  Hello World!!! ");
	delay_ms(2000);

	lcd_setCursor(0, 1);

	for(int i = 0; i<8; i++){
		write(smile_tab);
		write_str(" ");
	}

	delay_ms(5000);
	lcd_clear();
	lcd_noBlink();
	lcd_noCursor();
}
	
	
