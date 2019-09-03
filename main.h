
#ifndef __main_H__
#define __main_H__

#include <lpc17xx.h>

extern "C"
{
#include <Driver_I2C.h>
#include <GPIO_LPC17xx.h>
#include <cmsis_os2.h>
}

#include "MyI2C.h"
#include "TcaTlc.h"
#include "TimerMutex.h"
#include "Queue.h"
#include "ExtInt.h"
#include "Func.h"


#endif
