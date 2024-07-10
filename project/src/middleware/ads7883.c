#include "ads7883.h"

#include "math.h"

#include "../drivers/timer.h"

int32_t ads7883_init(ads7883_instance_t* instance) {
	instance->conversion_running = 0;
	instance->value = NAN;
	instance->failure = 0;
	instance->_receive_buffer[0] = 0xff;
	instance->_receive_buffer[1] = 0xff;

	if (spi_get_state(instance->spi_instance) != SPI_STATE_UNINIT) return 0;
	
	if (spi_init(instance->spi_instance) != 0) {instance->failure |= 0x80000000; return -1;}
	return 0;
}

int32_t ads7883_deinit(ads7883_instance_t* instance) {
	if (spi_get_state(instance->spi_instance) == SPI_STATE_UNINIT) return 0;
	
	if (spi_deinit(instance->spi_instance) != 0) {instance->failure |= 0x40000000; return -1;}
	return 0;
}

int32_t ads7883_step(ads7883_instance_t* instance) {
	if (instance->conversion_running) {
		if (spi_get_state(instance->spi_instance) != SPI_STATE_IDLE) {++instance->failure; return -1;}
		instance->conversion_running = 0;

		if (((instance->_receive_buffer[1] & 0xc0) != 0) || ((instance->_receive_buffer[0] & 0x03) != 0)) {
			instance->value = NAN;
			++instance->failure; 
			return -2;
		} 
		
		int32_t result = (((int32_t) instance->_receive_buffer[1]) << 6) + (((int32_t) instance->_receive_buffer[0]) >> 2);
		instance->value = result / 4095.0f; /* 12 bit. */
	}

	return 0;
}

int32_t ads7883_start_conversion(ads7883_instance_t* instance) {
	if (instance->conversion_running) {++instance->failure; return -1;}
	if (spi_get_state(instance->spi_instance) != SPI_STATE_IDLE) {++instance->failure; return -2;}

	if (spi_transceive(instance->spi_device, instance->_transmit_buffer, instance->_receive_buffer, 2) != 0) {++instance->failure; return -3;}
	instance->conversion_running = 1;

	return 0;
}