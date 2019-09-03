
#include "main.h"


int main()
{

	SystemCoreClockUpdate();
	
	SystemInit();
	
	osKernelInitialize();  	//Initialize CMSIS_RTOS

	I2C_Initialize();      	//Initialize I2C

	TcaTlc_Initialize();  	//Initialize Tcl & Tca

	Led_Initialize();	   	//Initialize Led Row & Control Leds

	//ExtInt_Initialize();	//Initialize External Interrupt

	LedDefaultColor();		//Default Keys Color

	Timer_Initialize();		//Initialize Os Timers
	
	Mutex_Initialize();		//Initialize Os Mutex

	Queue_Initialize();		//Initialize Queue

	osThreadNew(mainThread, NULL, NULL);

	osKernelStart();

	//return 0;

}

