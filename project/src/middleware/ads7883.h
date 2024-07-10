/*
 *
 */

#ifndef ADS7883_H
#define ADS7883_H

#include "../drivers/spi.h"

typedef struct {
	const spi_instance_t* spi_instance;
	const spi_device_t* spi_device;
	uint8_t conversion_running;
	float value;
	uint32_t failure;
	uint64_t duration;
	uint8_t _transmit_buffer[2];
	uint8_t _receive_buffer[2];
} ads7883_instance_t;

int32_t ads7883_init(ads7883_instance_t* instance);
int32_t ads7883_deinit(ads7883_instance_t* instance);
int32_t ads7883_step(ads7883_instance_t* instance);

int32_t ads7883_start_conversion(ads7883_instance_t* instance);

#endif
