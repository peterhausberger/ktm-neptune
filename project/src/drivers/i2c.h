/*
 *
 */

#ifndef I2C_H
#define I2C_H

#include "Lpi2c_Ip.h"

typedef struct {
	uint8_t channel;
	const Lpi2c_Ip_MasterConfigType* config;
} i2c_instance_t;

typedef enum {
	I2C_STATE_IDLE = 0,
	I2C_STATE_BUSY = 2,
} i2c_state_t;

extern const i2c_instance_t i2c_instance_1;

int32_t i2c_init(const i2c_instance_t* instance);
int32_t i2c_deinit(const i2c_instance_t* instance);

int32_t i2c_receive(const i2c_instance_t* instance,
		   	   	    uint8_t* data,
				    uint32_t size,
				    uint8_t stop);
int32_t i2c_transmit(const i2c_instance_t* instance,
				     uint8_t* data,
				     uint32_t size,
				     uint8_t stop);
i2c_state_t i2c_get_state(const i2c_instance_t* instance);

#endif
