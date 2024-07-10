/*
 *
 */

#ifndef AD799X_H
#define AD799X_H

#include "../drivers/i2c.h"

typedef enum {
	AD799X_STATE_INIT,
	AD799X_STATE_TX,
	AD799X_STATE_RX_0,
	AD799X_STATE_RX_1,
	AD799X_STATE_RX_2,
} ad799x_state_t;

typedef struct {
	const i2c_instance_t* i2c_instance;
	ad799x_state_t state;
	float result_1;
	float result_2;
	float result_3;
	float result_4;
	uint8_t failure;
	uint8_t _buffer[2];
	uint32_t _timeout;
} ad799x_instance_t;

int32_t ad799x_init(ad799x_instance_t* instance);
int32_t ad799x_deinit(ad799x_instance_t* instance);

int32_t ad799x_step(ad799x_instance_t* instance);

#endif
