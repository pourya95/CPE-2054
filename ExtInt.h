
#ifndef __ExtInt_H__
#define __ExtInt_H__

#include <lpc17xx.h>

//#include "Func.h"

extern "C"
{
	#include <Driver_I2C.h>
	#include <GPIO_LPC17xx.h>
	#include <cmsis_os2.h>
}


#define PINSEL_EINT0    20
#define PINSEL_EINT1    22
  

#define SBIT_EINT0      0
#define SBIT_EINT1      1  

#define SBIT_EXTMODE0   0
#define SBIT_EXTMODE1   1

#define SBIT_EXTPOLAR0  0
#define SBIT_EXTPOLAR1  1


void ExtInt_Initialize();

void EINT1_IRQHandler(void);

#endif
