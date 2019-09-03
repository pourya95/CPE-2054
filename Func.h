
#ifndef __Func_H__
#define __Func_H__

#include <lpc17xx.h>

extern "C"
{
#include <Driver_I2C.h>
#include <GPIO_LPC17xx.h>
#include <cmsis_os2.h>
}

#include "MyI2C.h"
#include "TimerMutex.h"
#include "Queue.h"
#include "TcaTlc.h"
#include "ExtInt.h"
#include "main.h"


#define RED 		0
#define GREEN 		1

#define Pressed 	1
#define Released 	0 


static uint8_t DataRed[4][4],DataGreen[4][4];


void setLedRow(int r);
void turnGreenBtn(int Row, int Col);
void turnRedBtn(int Row, int Col);
void turnYellowBtn(int Row, int Col);
void turnOffBtn(int Row, int Col);
void turnOffLed();

void clearLed();
void LedDefaultColor();


void mainThread( void *argument);

void turnOnLed(void *arg);
void keyScan(void *arg);
void keyRead(void *arg);


void EINT1_IRQHandler(void);

int32_t I2C_WriteBuf (uint8_t	DeviceAddr, uint8_t Addr, const uint8_t Data);
int32_t I2C_ReadBuf (uint8_t	DeviceAddr, uint8_t Addr, uint8_t *Data);


#endif
