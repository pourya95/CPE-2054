
#ifndef __TimerMutex_H__
#define __TimerMutex_H__

#include <lpc17xx.h>

extern "C"
{
	#include <Driver_I2C.h>
	#include <GPIO_LPC17xx.h>
	#include <cmsis_os2.h>
}

osTimerId_t timerLed2_id;
osTimerId_t timerLed1_id;
osTimerId_t timerLed_id;

osMutexId_t mutexI2C_id; 
osMutexId_t mutexQueue_id; 
osMutexId_t mutexLed_id; 

void Timer_Initialize();
void Timer_Start();

void Mutex_Initialize();

void timerLed2 ( void *argument);
void timerLed1 ( void *argument);
void timerLed (void *argument);


#endif
