/*---------------------:::::||||||   ALCDini.C    |||||::::::-------------------------*/
/*      						Purpose: ALCDini library for LiquidCrystal.cpp		  */
/*     							Author: Piotr Sorys									  */
/*------------------------------------------------------------------------------------*/
#include "AlphaLCDini.h"

void alpha_lcd_8bit_init (void) {
/*------------------------------------------------------------------------------------*/
/*------------------Function that initializes Alphanumeric LCD------------------------*/
/*------------------------------------------------------------------------------------*/

		SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
		SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;	//Enable Clock to Port A, B & C (thus for ease of connection)
		
		PORTB->PCR[9] = PORT_PCR_MUX(1UL);			//Pin PTB9 is GPIO
		PORTA->PCR[17] = PORT_PCR_MUX(1UL);			//Pin PTA17 is GPIO
		PORTA->PCR[16] = PORT_PCR_MUX(1UL);			//Pin PTA16 is GPIO
		PORTA->PCR[15] = PORT_PCR_MUX(1UL);			//Pin PTA15 is GPIO
		PORTA->PCR[14] = PORT_PCR_MUX(1UL);			//Pin PTA14 is GPIO
		PORTA->PCR[6] = PORT_PCR_MUX(1UL);			//Pin PTA6 is GPIO
		PORTA->PCR[7] = PORT_PCR_MUX(1UL);			//Pin PTA7 is GPIO
		PORTC->PCR[16] = PORT_PCR_MUX(1UL);			//Pin PTC16 is GPIO
		
		PORTC->PCR[13]  = PORT_PCR_MUX(1UL);			//Pin PTC13 is GPIO
		PORTC->PCR[11] = PORT_PCR_MUX(1UL);			//Pin PTC11 is GPIO
		PORTC->PCR[10] = PORT_PCR_MUX(1UL);			//Pin PTC10 is GPIO
	
	//Enable Pins as OUTPUTS
		FPTB->PDDR |= DataMask[7];			//set PTB9 as output
		FPTA->PDDR |= DataMask[6];			//set PTA17 as output
		FPTA->PDDR |= DataMask[5];			//set PTA16 as output
		FPTA->PDDR |= DataMask[4];			//set PTA15 as output
		FPTA->PDDR |= DataMask[3];			//set PTA14 as output
		FPTA->PDDR |= DataMask[2];			//set PTA6 as output
		FPTA->PDDR |= DataMask[1];			//set PTA7 as output
		FPTC->PDDR |= DataMask[0];			//set PTC16 as output
		FPTC->PDDR |= E_mask;		  	//set PTC13 as output
		FPTC->PDDR |= RW_mask;			//set PTC11 as output
		FPTC->PDDR |= RS_mask;			//set PTC10 as output
		
		//precautious bits clear
		FPTB->PCOR = DataMask[7];			//clear PTB9
		FPTA->PCOR = DataMask[6];			//clear PTA17
		FPTA->PCOR = DataMask[5];			//clear PTA16
		FPTA->PCOR = DataMask[4];			//clear PTA15
		FPTA->PCOR = DataMask[3];			//clear PTA14
		FPTA->PCOR = DataMask[2];			//clear PTA6
		FPTA->PCOR = DataMask[1];			//clear PTC7
		FPTC->PCOR = DataMask[0];			//clear PTC16
		FPTC->PCOR = E_mask;				//clear PTC13
		FPTC->PCOR = RW_mask;			//clear PTC11
		FPTC->PCOR = RS_mask;			//clear PTC10
	}

void alpha_lcd_4bit_init (void) {
/*------------------------------------------------------------------------------------*/
/*------------------Function that initializes Alphanumeric LCD------------------------*/
/*------------------------------------------------------------------------------------*/

	
		SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
		SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;	//Enable Clock to Port A, B & C (thus for ease of connection)
		
		PORTB->PCR[9] = PORT_PCR_MUX(1UL);			//Pin PTB9 is GPIO
		PORTA->PCR[17] = PORT_PCR_MUX(1UL);			//Pin PTA17 is GPIO
		PORTA->PCR[16] = PORT_PCR_MUX(1UL);			//Pin PTA16 is GPIO
		PORTA->PCR[15] = PORT_PCR_MUX(1UL);			//Pin PTA15 is GPIO
		PORTA->PCR[14] = PORT_PCR_MUX(1UL);			//Pin PTA14 is GPIO
		PORTA->PCR[6] = PORT_PCR_MUX(1UL);			//Pin PTA6 is GPIO
		PORTA->PCR[7] = PORT_PCR_MUX(1UL);			//Pin PTA7 is GPIO
		PORTC->PCR[16] = PORT_PCR_MUX(1UL);			//Pin PTC16 is GPIO
		
		PORTC->PCR[13]  = PORT_PCR_MUX(1UL);			//Pin PTC13 is GPIO
		PORTC->PCR[11] = PORT_PCR_MUX(1UL);			//Pin PTC11 is GPIO
		PORTC->PCR[10] = PORT_PCR_MUX(1UL);			//Pin PTC10 is GPIO
	
	//Enable Pins as OUTPUTS
		FPTB->PDDR |= DataMask[7];			//set PTB9 as output
		FPTA->PDDR |= DataMask[6];			//set PTA17 as output
		FPTA->PDDR |= DataMask[5];			//set PTA16 as output
		FPTA->PDDR |= DataMask[4];			//set PTA15 as output
		FPTA->PDDR |= DataMask[3];			//set PTA14 as output
		FPTA->PDDR |= DataMask[2];			//set PTA6 as output
		FPTA->PDDR |= DataMask[1];			//set PTA7 as output
		FPTC->PDDR |= DataMask[0];			//set PTC16 as output
		FPTC->PDDR |= E_mask;		  	//set PTC13 as output
		FPTC->PDDR |= RW_mask;			//set PTC11 as output
		FPTC->PDDR |= RS_mask;			//set PTC10 as output
		
		//precautious bits clear
		FPTB->PCOR = DataMask[0];			//clear PTB9
		FPTA->PCOR = DataMask[1];			//clear PTA17
		FPTA->PCOR = DataMask[2];			//clear PTA16
		FPTA->PCOR = DataMask[3];			//clear PTA15
		FPTA->PCOR = DataMask[4];			//clear PTA14
		FPTA->PCOR = DataMask[5];			//clear PTA6
		FPTA->PCOR = DataMask[6];			//clear PTC7
		FPTC->PCOR = DataMask[7];			//clear PTC16
		FPTC->PCOR = E_mask;				//clear PTC13
		FPTC->PCOR = RW_mask;			//clear PTC11
		FPTC->PCOR = RS_mask;			//clear PTC10
		
	}


void lcdpin_Eset (bool State){
/*--------------------------------::: FUNCTION THAT WRITES TO E PIN :::-----------------------*/
	if (State == true){
		FPTC->PSOR = E_mask;
	}
	else if (State == false){
		FPTC->PCOR = E_mask;
	}
 /*----------------------------:::End of E_WRITEtoPIN FUNCTION:::--------------------------*/
}
void lcdpin_RWset (bool State){		//Read from LCD / Write to LCD - usually we want to keep it low to write only
/*-------------------------::: FUNCTION THAT WRITES TO RW PIN :::-----------------------------*/
	if (State == true){
		FPTC->PSOR = RW_mask;
	}
	else if (State == false){
		FPTC->PCOR = RW_mask;
	}
 /*------------------------:::End of	READ/WRITE_WRITEtoPIN FUNCTION:::----------------------*/
}

void lcdpin_RSset (bool State){		//Register select
/*-----------------------::: FUNCTION THAT WRITES TO RS PIN :::------------------------------*/
	if (State == true){
		FPTC->PSOR = RS_mask;
	}
	else if (State == false){
		FPTC->PCOR = RS_mask;
	}
 /*-------------------------:::End of	RESET_WRITEtoPIN FUNCTION:::-------------------------*/
}

void pinval_set( int pin, uint8_t State){

 if(pin == 0 & State == 1)
	 FPTC->PSOR = D0_mask;
 else if(pin == 0 & State == 0)
	 FPTC->PCOR = D0_mask;
 
 else if(pin == 1 & State == 1)
	 FPTA->PSOR = D1_mask;
 else if(pin == 1 & State == 0)
	 FPTA->PCOR = D1_mask;
 
  else if(pin == 2 & State == 1)
	 FPTA->PSOR = D2_mask;
 else if(pin == 2 & State == 0)
	 FPTA->PCOR = D2_mask;
 
  else if(pin == 3 & State == 1)
	 FPTA->PSOR = D3_mask;
 else if(pin == 3 & State == 0)
	 FPTA->PCOR = D3_mask;
 
 else if(pin == 4 & State == 1)
	 FPTA->PSOR = D4_mask;
 else if(pin == 4 & State == 0)
	 FPTA->PCOR = D4_mask;
 
 else if(pin == 5 & State == 1)
	 FPTA->PSOR = D5_mask;
 else if(pin == 5 & State == 0)
	 FPTA->PCOR = D5_mask;
 
  else if(pin == 6 & State == 1)
	 FPTA->PSOR = D6_mask;
 else if(pin == 6 & State == 0)
	 FPTA->PCOR = D6_mask;
 
  else if(pin == 7 & State == 1)
	 FPTB->PSOR = D7_mask;
 else if(pin == 7 & State == 0)
	 FPTB->PCOR = D7_mask;
}
	


