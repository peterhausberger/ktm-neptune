#include "spi.h"

int32_t spi_init(const spi_instance_t* instance) {
	Lpspi_Ip_StatusType result;

	result = Lpspi_Ip_Init(instance);
	if (result != LPSPI_IP_STATUS_SUCCESS) return result;

	result = Lpspi_Ip_UpdateTransferMode(instance->Instance, LPSPI_IP_INTERRUPT);
	if (result != LPSPI_IP_STATUS_SUCCESS) return result;

	return 0;
}

int32_t spi_deinit(const spi_instance_t* instance) {
	return Lpspi_Ip_DeInit(instance->Instance);
}

int32_t spi_transceive(const spi_device_t* device,
					   const uint8_t* transmit_buffer,
				   	   uint8_t* receive_buffer,
				 	   uint16_t length) {
	/* Receive and transmit, full duplex. */
    return Lpspi_Ip_AsyncTransmit(device, transmit_buffer, receive_buffer, length, NULL_PTR);
}

spi_state_t spi_get_state(const spi_instance_t* instance) {
	return (spi_state_t) Lpspi_Ip_GetStatus(instance->Instance);
}
