
#include "TimerMutex.h"


int timerflag=0;
int timerflag1=0;
int timerflag2=0;

osTimerId_t timerLed2_id;
osTimerId_t timerLed1_id;
osTimerId_t timerLed_id;

void Timer_Initialize(){

	timerLed2_id 	= osTimerNew(timerLed2, osTimerPeriodic, NULL, NULL);
	timerLed1_id 	= osTimerNew(timerLed1, osTimerPeriodic, NULL, NULL);  
	timerLed_id 	= osTimerNew(timerLed, osTimerPeriodic, NULL, NULL); 
}

void Timer_Start(){

	osTimerStart(timerLed2_id, 2000);
	osTimerStart(timerLed1_id, 1000);
	osTimerStart(timerLed_id, 500);
}


void Mutex_Initialize(){

	mutexI2C_id = osMutexNew(NULL);
	mutexQueue_id = osMutexNew(NULL);
	mutexLed_id = osMutexNew(NULL);
}

void timerLed (void *argument) {

	timerflag++;
  	if(timerflag%2==0)		
  		GPIO_PinWrite(1,25,1);
	else	
		GPIO_PinWrite(1,25,0);
}

void timerLed1 (void *argument) {

	timerflag1++;
  	if(timerflag1%2==0)		
  		GPIO_PinWrite(1,27,1);	
	else 						
		GPIO_PinWrite(1,27,0);
}

void timerLed2 (void *argument) {
	
	timerflag2++;
  	if(timerflag2%2==0)		
  		GPIO_PinWrite(1,29,1);	
	else 						
		GPIO_PinWrite(1,29,0);
}


