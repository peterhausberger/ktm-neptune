/*
 * Max clock frequency supported by the device is 100 kHz (in standard mode).
 *
 * Current clock frequency is 52.083 kHz.
 *
 * The max. I2C package length is 28 Bit (7 Bit address, 16 Bit data, 5 Bit overhead)
 * This corresponds to ca. 540 us, which are about 2.2 cycles (250 us each).
 */

#include "ad799x.h"

#include "math.h"

#define _ADDRESS 0x28
//#define _ADDRESS 0x21
//#define _ADDRESS 0x22
//#define _ADDRESS 0x23
//#define _ADDRESS 0x24

#define _TIMEOUT 6 // Timeout in cycles. 6 cycles x 250 us/cycle = 1500 us.

static int32_t _convert(int8_t channel, const uint8_t* buffer, float* result) {
	if ((buffer[0] & 0x40) != 0) return -1;
	if (((buffer[0] >> 4) & 0x03) != channel) return -1;
		
	uint16_t data = (((uint16_t) (buffer[0] & 0x0f)) << 8) + buffer[1];
	*result = data / 4095.0f;
	return 0;
}

/*
 * Waits until the last I2C command was completed and converts the result if everything
 * was successfull.
 *
 * @param channel Channel of the last I2C read command (beginning with 0)
 *                or -1 if not applicable (i.e. for write commmands)
 *
 * @return 0 I2C command was finished and the state machine can proceed.
 * 		   1 Wait in the current state
 */
static int32_t _wait_and_convert(ad799x_instance_t* instance, int8_t channel, float* result) {
	boolean timeout = (++instance->_timeout >= _TIMEOUT);
	i2c_state_t s = i2c_get_state(instance->i2c_instance);
	if (s == I2C_STATE_IDLE) {
		if (channel >= 0) {
			if (_convert(channel, instance->_buffer, result) != 0) instance->failure = 1;
		}
		return 0;
	} else if (s == I2C_STATE_BUSY && !timeout) {
		return 1;
	} else if (s == I2C_STATE_BUSY && timeout) {
		instance->failure = 1;
		return 0;
	} else if (!timeout) {
		instance->failure = 1;
		return 1;
	} else {
		instance->failure = 1;
		return 0;
	}
}

int32_t ad799x_init(ad799x_instance_t* instance) {
	instance->state = AD799X_STATE_INIT;
	
	instance->result_1 = NAN;
	instance->result_2 = NAN;
	instance->result_3 = NAN;
	instance->result_4 = NAN;

	return i2c_init(instance->i2c_instance);
}

int32_t ad799x_deinit(ad799x_instance_t* instance) {
	return i2c_deinit(instance->i2c_instance);
}

// @todo Make asynchronous with state machine!
int32_t ad799x_step(ad799x_instance_t* instance) {
	instance->failure = 0;
		
	switch (instance->state) {
		case AD799X_STATE_RX_2:
			if (_wait_and_convert(instance, 2, &instance->result_3)) break;

			/* No break, continue with the INIT state. */

		case AD799X_STATE_INIT:
			instance->_buffer[0] = 0x70; /* Channel 1, 2 and 3. */
			instance->_timeout = 0;
			if (i2c_transmit(instance->i2c_instance, instance->_buffer, 1, false) != 0) {
				instance->failure = 1;
				break;
			}

			instance->state = AD799X_STATE_TX;
			break;
		
		case AD799X_STATE_TX:
			if (_wait_and_convert(instance, -1, 0)) break;
				
			instance->_timeout = 0;
			if (i2c_receive(instance->i2c_instance, instance->_buffer, 2, false) != 0) {
				instance->failure = 1;
				break;
			}
			
			instance->state = AD799X_STATE_RX_0;
			break;

		case AD799X_STATE_RX_0:
			if (_wait_and_convert(instance, 0, &instance->result_1)) break;
				
			instance->_timeout = 0;
			if (i2c_receive(instance->i2c_instance, instance->_buffer, 2, false) != 0) {
				instance->failure = 1;
				break;
			}
			
			instance->state = AD799X_STATE_RX_1;
			break;

		case AD799X_STATE_RX_1:
			if (_wait_and_convert(instance, 1, &instance->result_2)) break;
				
			instance->_timeout = 0;
			if (i2c_receive(instance->i2c_instance, instance->_buffer, 2, true) != 0) {
				instance->failure = 1;
				break;
			}
			
			instance->state = AD799X_STATE_RX_2;
			break;

		default:
			/* Undefined state. */
			instance->failure = 1;
			instance->state = AD799X_STATE_INIT;
	}

	return 0;
}
