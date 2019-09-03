
#include "TcaTlc.h"
	
void TcaTlc_Initialize(){
	
	GPIO_SetDir(2, 0, GPIO_DIR_OUTPUT);		// TLC59116 active low Reset
	GPIO_SetDir(2, 1, GPIO_DIR_OUTPUT);		// TCA8418  active low Reset
	GPIO_PinWrite(2, 0, 0);
	GPIO_PinWrite(2, 1, 0);
	delay(100);
	GPIO_PinWrite(2, 0, 1);
	GPIO_PinWrite(2, 1, 1);
	delay(100);

	I2C_WriteBuf(LEDG_COL, MODE1_REG, 0x00); //Initialize LedGreen Module
	I2C_WriteBuf(LEDR_COL, MODE1_REG, 0x00); //Initialize LedRed Module

	///////////////Initialize KeyScan Module
	I2C_WriteBuf(KEYPAD_SCAN, CFG, 0x11);
	I2C_WriteBuf(KEYPAD_SCAN, KP_GPIO1, 0xFF);
	I2C_WriteBuf(KEYPAD_SCAN, KP_GPIO2, 0xFF);
	I2C_WriteBuf(KEYPAD_SCAN, KP_GPIO3, 0x03);

	GPIO_SetDir(2, KeyScanInt, 0); //Interrupt KeyScan direction
}

void Led_Initialize(){

	for(int i = 19; i<23;i++) //KEY_LED row gpio diriction
		GPIO_SetDir(1, i, 1);
	
	for(int i = 25; i<30;i++)	//Led gpio direction
		GPIO_SetDir(1, i, 1);
}

void delay(int d){
	
	int i=0;
	while(i<d*100)	i++;
}

