#include "i2c.h"

const i2c_instance_t i2c_instance_1 = {LPI2C_CHANNEL_1, &I2c_Lpi2cMasterChannel1};

void i2c_slave_callback(Lpi2c_Ip_SlaveEventType event, uint8_t user_data) {
	uint32_t instance = (uint32_t) user_data;

	/*switch(event) {
	   case I2C_SLAVE_EVENT_TX_REQ:
		   Lpi2c_Ip_SlaveSetBuffer(instance, txBufferSlave, TRANSFER_SIZE);
		   break;
	   case I2C_SLAVE_EVENT_RX_REQ:
			Lpi2c_Ip_SlaveSetBuffer(instance, rxBufferSlave, TRANSFER_SIZE);
	        break;
	   default:
		   break;
	}*/
}

void i2c_master_callback(Lpi2c_Ip_MasterEventType event, uint8_t user_data) {
//	uint32 u32Instance = (uint32)userData;
//
//	switch(event)
//	{
//	   case I2C_SLAVE_EVENT_TX_REQ:
//		   Lpi2c_Ip_SlaveSetBuffer(u32Instance, txBuffer, TRANSFER_SIZE);
//		   break;
//
//	   case I2C_SLAVE_EVENT_RX_REQ:
//			Lpi2c_Ip_SlaveSetBuffer(u32Instance, rxBufferSlave, TRANSFER_SIZE);
//	        break;
//
//	   default:
//		   break;
//	}
//
	/* Cast to void to avoid compiler warnings */
 	(void) user_data;
}

/**
WARNING: Must be called after DIO init!!!
*/
int32_t i2c_init(const i2c_instance_t* instance) {
	/* Init lpi2c in master mode. */
	return Lpi2c_Ip_MasterInit(instance->channel, instance->config);
}

int32_t i2c_deinit(const i2c_instance_t* instance) {
	return Lpi2c_Ip_MasterDeinit(instance->channel);
}

int32_t i2c_receive(const i2c_instance_t* instance,
	   	   	        uint8_t* data,
				    uint32_t size,
				    uint8_t stop) {
	/* Receive data non-blocking. */
	return Lpi2c_Ip_MasterReceiveData(instance->channel, data, size, stop);
}

int32_t i2c_transmit(const i2c_instance_t* instance,
		   	   	     uint8_t* data,
				     uint32_t size,
				     uint8_t stop) {
	/* Send data non-blocking. */
	return Lpi2c_Ip_MasterSendData(instance->channel, data, size, stop);
}

i2c_state_t i2c_get_state(const i2c_instance_t* instance) {
	return (i2c_state_t) Lpi2c_Ip_MasterGetTransferStatus(instance->channel, NULL_PTR);
}
