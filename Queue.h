
#ifndef __Queue_H__
#define __Queue_H__

#include <lpc17xx.h>

extern "C"
{
	#include <Driver_I2C.h>
	#include <GPIO_LPC17xx.h>
	#include <cmsis_os2.h>
}


#define MSGQUEUE_OBJECTS 16                     // number of Message Queue Objects

typedef struct {                                // object data type
  uint8_t Data;
  uint8_t Idx;
} MSGQUEUE_OBJ_t;    

osMessageQueueId_t Btn_MsgQueue;

void Queue_Initialize();
void PutToQ(const void *  msg);
void GetFromQ(const void *  msg);

#endif
