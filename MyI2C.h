
#ifndef __MyI2C_H__
#define __MyI2C_H__

#include <lpc17xx.h>

extern "C" {
#include <Driver_I2C.h>	
}

#define BUFFER_SIZE	2

void I2C_Initialize();

int32_t I2C_WriteBuf (uint8_t	DeviceAddr, uint8_t Addr, const uint8_t Data);
int32_t I2C_ReadBuf (uint8_t	DeviceAddr, uint8_t Addr, uint8_t *Data);

#endif
