/*---------------------:::::||||||   ALCDini.C    |||||::::::-------------------------*/
/*  				Purpose: Delay library for LiquidCrystal.cpp					  */
/*  				Author: Piotr Sorys								                  */
/*------------------------------------------------------------------------------------*/

#include "delays.h"

/*----------------------------------------------------------------------------
	Function making delay of value * 10000 clock cycles
*----------------------------------------------------------------------------*/
void delay_mc(uint32_t value){
	uint32_t adelay, x;
	
	for(x=0; x < value; x++){
		for(adelay=0; adelay < 10000; adelay++){};
	}
}

/*----------------------------------------------------------------------------
	Function making delay of value * [milisecond]
*----------------------------------------------------------------------------*/
void delay_ms(uint32_t value){
	uint32_t adelay, x;
	
	adelay = value * 10060;
	
	for(x=0; x < adelay; x++){
	}
}
/*----------------------------------------------------------------------------
	Function making delay of value * [microsecond]
*----------------------------------------------------------------------------*/
void delay_us(uint32_t value){
	uint32_t adelay, x;
	
	adelay = value*10;
			
	for(x=0; x < adelay; x++){}
		
}
