
#include "Queue.h"


void Queue_Initialize(){

	Btn_MsgQueue = osMessageQueueNew(MSGQUEUE_OBJECTS, sizeof(MSGQUEUE_OBJ_t), NULL);
}

void PutToQ(const void *  msg){
	osMessageQueuePut(Btn_MsgQueue, &msg, 0U, 0U);
}

void GetFromQ(const void *  msg){
	osMessageQueueGet(Btn_MsgQueue, &msg, NULL, 0U);
}

