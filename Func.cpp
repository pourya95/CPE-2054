
#include "Func.h"


void LedDefaultColor(){

	DataGreen[0][3] = 0x05;
	DataGreen[1][3] = 0x01;
	DataGreen[2][3] = 0x01;
	DataGreen[3][3] = 0x01;

	DataRed[0][3] = 0x01;
	DataRed[1][3] = 0x01;
	DataRed[2][3] = 0x01;
	DataRed[3][3] = 0x05;
}

void mainThread( void *argument){
	
	Timer_Start();
	
	osThreadNew(keyRead, NULL, NULL);
	osThreadNew(keyScan, NULL, NULL);
	osThreadNew(turnOnLed, NULL, NULL);
	
}

void keyRead(void *arg){
	uint8_t Btn;
	MSGQUEUE_OBJ_t msgBtn;
	msgBtn.Idx = 0;
	while(true){
		// read key from i2c
		osMutexAcquire(mutexI2C_id,osWaitForever);
		I2C_ReadBuf(KEYPAD_SCAN, KEY_EVENT_A, &Btn);
		osMutexRelease(mutexI2C_id);
		// write key to queue
		msgBtn.Data=Btn;
		//osMutexAcquire(mutexQueue_id,osWaitForever);
		////osMessageQueuePut(Btn_MsgQueue, &msgBtn, 0U, 0U);
		PutToQ(&msgBtn);
		//osMutexRelease(mutexQueue_id);
	}
}

void keyScan(void *arg){
													
	char KeyCodes[56] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x2F, 0x30, 0x31, 0x32,	//1-6 	| 7-10,47,48  | 49 50
											 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x39, 0x3A, 0x3B, 0x51,	//11-16 | 17-20,57,58 | 59 X
											 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x43, 0x44, 0x45, 0x51,	//21-26 | 27-30,67,68 | 69 X
											 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x4D, 0x4E, 0x4F, 0x50}; //31-36 | 37-40,77,78 | 79 80
											
	uint8_t Btn;
	MSGQUEUE_OBJ_t msgBtn;
	while(true){
		// read key from queue
		osMutexAcquire(mutexQueue_id,osWaitForever);
		//osMessageQueueGet(Btn_MsgQueue, &msgBtn, NULL, 0U);
		GetFromQ(&msgBtn);
		osMutexRelease(mutexQueue_id);
		Btn = msgBtn.Data;
		int state;
		if((Btn & 0x80) != 0x80)	state = Released;  // key state - pressed or released
		else state = Pressed;
		Btn = (Btn & 0x7F);
		osMutexAcquire(mutexI2C_id,osWaitForever);
		osMutexAcquire(mutexLed_id,osWaitForever);
		// key decode
		for(int i=0; i<56; i++)
		{
			if(Btn == KeyCodes[i])
			{
				if((i<6) || (13<i && i<20) || (27<i && i<34) || (41<i && i<48))  	//first section
				{
					if(state == Pressed)
						turnRedBtn(i/14,i%14);
					else
						turnGreenBtn(i/14,i%14);
				}
				else if((5<i && i<12) || (19<i && i<26) || (33<i && i<40) || (47<i && i<54))	//second section
				{
						if(state == Pressed)
						turnGreenBtn(i/14,i%14);
					else
						turnRedBtn(i/14,i%14);
				}
				else if(i == 55)		//reset
				{
					if(state == Pressed)
					{
						clearLed();
						turnOffBtn(i/14,i%14);
					}
					else
						turnRedBtn(i/14,i%14);
				}
				else if(i == 13)		//set
				{
					if(state == Pressed)
					{
						turnOffBtn(i/14,i%14);
					}
					else
						turnGreenBtn(i/14,i%14);
				}
				else   							//third section
				{
					if(state == Pressed)
						turnGreenBtn(i/14,i%14);
					else
						turnYellowBtn(i/14,i%14);		
				}
				break;
			}
		}
		osMutexRelease(mutexLed_id);
		osMutexRelease(mutexI2C_id);
	}
	
}

void turnOnLed(void *arg){
	
	while(true){
		osMutexAcquire(mutexI2C_id,osWaitForever);
		osMutexAcquire(mutexLed_id,osWaitForever);
		for(int i=0; i<4; i++){		
			for(int j=0; j<4; j++){
				setLedRow(i);
				I2C_WriteBuf(LEDR_COL, LEDOUT0_REG+j, DataRed[i][j]);  //DataRed
				I2C_WriteBuf(LEDG_COL, LEDOUT0_REG+j, DataGreen[i][j]);				//DataGreen	
				}
				//osDelay(1);
				turnOffLed();   				
		}
		osMutexRelease(mutexLed_id);
		osMutexRelease(mutexI2C_id);
	}
}

void setLedRow(int r){
	
	GPIO_PinWrite(1, 22, (1==r+1)?0:1);		
	GPIO_PinWrite(1, 21, (2==r+1)?0:1);	
	GPIO_PinWrite(1, 20, (3==r+1)?0:1);	
	GPIO_PinWrite(1, 19, (4==r+1)?0:1);	
}


void turnGreenBtn(int Row, int Col){
	
	int Num = Col % 4;
	Col = Col / 4;
	switch(Num)
	{
		case 0:
				DataGreen[Row][Col] 	= DataGreen[Row][Col] | 0x01;
				DataRed[Row][Col] 		= DataRed[Row][Col] & 0xF6;
				break;		
		case 1:
				DataGreen[Row][Col] 	= DataGreen[Row][Col] | 0x04;
				DataRed[Row][Col] 		= DataRed[Row][Col] & 0xF3;			
				break;
		case 2:
				DataGreen[Row][Col] 	= DataGreen[Row][Col] | 0x10;
				DataRed[Row][Col] 		= DataRed[Row][Col] & 0x6F;
				break;
		case 3:
				DataGreen[Row][Col] 	= DataGreen[Row][Col] | 0x40;
				DataRed[Row][Col] 		= DataRed[Row][Col] & 0x3F;
				break;
	};
}

void turnRedBtn(int Row, int Col){
	
	int Num = Col % 4;
	Col = Col / 4;
	switch(Num)
	{
		case 0:
				DataRed[Row][Col] 			= DataRed[Row][Col] | 0x01;
				DataGreen[Row][Col] 		= DataGreen[Row][Col] & 0xF6;
				break;		
		case 1:
				DataRed[Row][Col] 			= DataRed[Row][Col] | 0x04;
				DataGreen[Row][Col] 		= DataGreen[Row][Col] & 0xF3;			
				break;
		case 2:
				DataRed[Row][Col] 			= DataRed[Row][Col] | 0x10;
				DataGreen[Row][Col] 		= DataGreen[Row][Col] & 0x6F;
				break;
		case 3:
				DataRed[Row][Col] 			= DataRed[Row][Col] | 0x40;
				DataGreen[Row][Col] 		= DataGreen[Row][Col] & 0x3F;
				break;
	};
}

void turnYellowBtn(int Row, int Col){
	
	int Num = Col % 4;
	Col = Col / 4;
	switch(Num)
	{
		case 0:
				DataRed[Row][Col] 			= DataRed[Row][Col] | 0x01;
				DataGreen[Row][Col] 		= DataGreen[Row][Col] | 0x01;
				break;		
		case 1:
				DataRed[Row][Col] 			= DataRed[Row][Col] | 0x04;
				DataGreen[Row][Col] 		= DataGreen[Row][Col] | 0x04;			
				break;
		case 2:
				DataRed[Row][Col] 			= DataRed[Row][Col] | 0x10;
				DataGreen[Row][Col] 		= DataGreen[Row][Col] | 0x10;
				break;
		case 3:
				DataRed[Row][Col] 			= DataRed[Row][Col] | 0x40;
				DataGreen[Row][Col] 		= DataGreen[Row][Col] | 0x40;
				break;
	};
}

void turnOffBtn(int Row, int Col){
	
	int Num = Col % 4;
	Col = Col / 4;
	switch(Num)
	{
		case 0:
				DataRed[Row][Col] 			= DataRed[Row][Col] & 0xF6;
				DataGreen[Row][Col] 		= DataGreen[Row][Col] & 0xF6;
				break;		
		case 1:
				DataRed[Row][Col] 			= DataRed[Row][Col] & 0xF3;
				DataGreen[Row][Col] 		= DataGreen[Row][Col] & 0xF3;			
				break;
		case 2:
				DataRed[Row][Col] 			= DataRed[Row][Col] & 0x6F;
				DataGreen[Row][Col] 		= DataGreen[Row][Col] & 0x6F;
				break;
		case 3:
				DataRed[Row][Col] 			= DataRed[Row][Col] & 0x3F;
				DataGreen[Row][Col] 		= DataGreen[Row][Col] & 0x3F;
				break;
	};
}

void turnOffLed(){
	
	I2C_WriteBuf(LEDG_COL, LEDOUT0_REG, 0x00);
	I2C_WriteBuf(LEDG_COL, LEDOUT1_REG, 0x00);
	I2C_WriteBuf(LEDG_COL, LEDOUT2_REG, 0x00);
	I2C_WriteBuf(LEDG_COL, LEDOUT3_REG, 0x00);
	I2C_WriteBuf(LEDR_COL, LEDOUT0_REG, 0x00);
	I2C_WriteBuf(LEDR_COL, LEDOUT1_REG, 0x00);
	I2C_WriteBuf(LEDR_COL, LEDOUT2_REG, 0x00);
	I2C_WriteBuf(LEDR_COL, LEDOUT3_REG, 0x00);
}

void clearLed(){
	
	for(int i=0; i<4; i++)
	{		
		for(int j=0; j<4; j++)
		{
			if(j != 3)
			{	
			DataGreen[i][j] = 0x00;
			DataRed[i][j] = 0x00;
			}
		}
	}
}


