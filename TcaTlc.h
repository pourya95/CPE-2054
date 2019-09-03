
#ifndef __TcaTlc_H__
#define __TcaTlc_H__


#include <lpc17xx.h>

//#include "Func.h"
#include "MyI2C.h"

#define KeyScanInt 11

#define LEDG_COL   		0x60
#define LEDR_COL   		0x61
#define KEYPAD_SCAN 	0x34

#define	CFG				0x01
#define INT_STAT 		0x02
#define	KEY_LCK_EC		0x03
#define	KEY_EVENT_A		0x04
#define KP_GPIO1		0x1D
#define KP_GPIO2		0x1E
#define KP_GPIO3		0x1F

#define	MODE1_REG			0x00
#define	MODE2_REG			0x01
#define	PWM0_REG			0x02
#define	PWM1_REG			0x03
#define	PWM2_REG			0x04
#define	PWM3_REG			0x05
#define	PWM4_REG			0x06
#define	PWM5_REG			0x07
#define	PWM6_REG			0x08
#define	PWM7_REG			0x09
#define	PWM8_REG			0x0A
#define	PWM9_REG			0x0B
#define	PWM10_REG			0x0C
#define	PWM11_REG			0x0D
#define	PWM12_REG			0x0E
#define	PWM13_REG			0x0F
#define	PWM14_REG			0x10
#define	PWM15_REG			0x11
#define	GRPPWM_REG			0x12
#define	GRPFREQ_REG			0x13
#define	LEDOUT0_REG			0x14
#define	LEDOUT1_REG			0x15
#define	LEDOUT2_REG			0x16
#define	LEDOUT3_REG			0x17

extern "C"{
	#include <GPIO_lpc17xx.h>
}

void delay(int d);

void TcaTlc_Initialize();

void Led_Initialize();

#endif
