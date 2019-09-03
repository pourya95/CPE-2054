
#include "MyI2C.h"

extern ARM_DRIVER_I2C  Driver_I2C0;
ARM_DRIVER_I2C *I2C_0 = &Driver_I2C0;

void I2C_Initialize(){
	
	I2C_0->Initialize 	(NULL);
	I2C_0->PowerControl (ARM_POWER_FULL);
  	I2C_0->Control      (ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_STANDARD);
 	I2C_0->Control      (ARM_I2C_BUS_CLEAR, 0);
}

int32_t I2C_WriteBuf (uint8_t	DeviceAddr, uint8_t Addr, const uint8_t Data) {
  	
  	uint8_t	wr_buf[BUFFER_SIZE];
	wr_buf[0]	= Addr;
	wr_buf[1]	= Data;
	I2C_0->MasterTransmit (DeviceAddr, wr_buf, 2, false);
	while (I2C_0->GetStatus().busy);
	if (I2C_0->GetDataCount () != 2) return -1;

	return 0;
}

int32_t I2C_ReadBuf (uint8_t	DeviceAddr, uint8_t Addr, uint8_t *Data) {
	
	uint8_t a[2];
	a[0] = Addr;
	a[1] = 0;
	I2C_0->MasterTransmit (DeviceAddr, a, 1, true);
	while (I2C_0->GetStatus().busy);
	I2C_0->MasterReceive (DeviceAddr, Data, 1, false);
	while (I2C_0->GetStatus().busy);
	if (I2C_0->GetDataCount () != 1) return -1;

	return 0;
}
