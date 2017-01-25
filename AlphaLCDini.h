#ifndef AlphaLCDini_h
#define AlphaLCDini_h

#include "MKL46Z4.h"
#include "delays.h"
#include "stdbool.h"

const uint32_t DataMask[] = {1UL<<16, 1UL<<7, 1UL<<6, 1UL<<14, 1UL<<15, 1UL<<16, 1UL<<17, 1UL<<9};

const int D0_mask = 1UL<<16;
const int D1_mask = 1UL<<7;
const int D2_mask = 1UL<<6;
const int D3_mask = 1UL<<14;

const int D4_mask = 1UL<<15;
const int D5_mask = 1UL<<16;
const int D6_mask = 1UL<<17;
const int D7_mask = 1UL<<9;

const int E_mask  = 1UL<<13;
const int RW_mask = 1UL<<11;
const int RS_mask = 1UL<<10;

void alpha_lcd_8bit_init (void);
void alpha_lcd_4bit_init (void);
void lcdpin_Eset (bool);
void lcdpin_RWset (bool);
void lcdpin_RSset (bool);
//void pinMode( int, char);
void pinval_set( int, uint8_t);
//uint8_t pinval_read(int);
	
#endif



