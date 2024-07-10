#ifndef SPI_H
#define SPI_H

#include "Lpspi_Ip.h"

typedef Lpspi_Ip_ConfigType spi_instance_t;
typedef Lpspi_Ip_ExternalDeviceType spi_device_t;
typedef enum {
	SPI_STATE_UNINIT = 0u, /**< Module is not initialized. */
	SPI_STATE_IDLE = 1u,   /**< Module is not used. */
	SPI_STATE_BUSY = 2u,   /**< A transfer is in progress. */
	SPI_STATE_FAULT = 3u   /**< During last transfer a fault occurred. */
} spi_state_t;

#define spi_1 Lpspi_Ip_PhyUnitConfig_SpiPhyUnit_0_Instance_1
#define spi_2 Lpspi_Ip_PhyUnitConfig_SpiPhyUnit_1_Instance_2
#define spi_3 Lpspi_Ip_PhyUnitConfig_SpiPhyUnit_2_Instance_3
#define spi_4 Lpspi_Ip_PhyUnitConfig_SpiPhyUnit_3_Instance_4

#define spi_1_cs_0 Lpspi_Ip_DeviceAttributes_SpiExternalDevice_0_Instance_1
#define spi_1_cs_1 Lpspi_Ip_DeviceAttributes_SpiExternalDevice_1_Instance_1
#define spi_2_cs_0 Lpspi_Ip_DeviceAttributes_SpiExternalDevice_2_Instance_2
#define spi_2_cs_1 Lpspi_Ip_DeviceAttributes_SpiExternalDevice_3_Instance_2
#define spi_3_cs_0 Lpspi_Ip_DeviceAttributes_SpiExternalDevice_4_Instance_3
#define spi_4_cs_0 Lpspi_Ip_DeviceAttributes_SpiExternalDevice_5_Instance_4

int32_t spi_init(const spi_instance_t* instance);
int32_t spi_deinit(const spi_instance_t* instance);
int32_t spi_transceive(const spi_device_t* device,
					   const uint8_t* transmit_buffer,
					   uint8_t* receive_buffer,
					   uint16_t length);
spi_state_t spi_get_state(const spi_instance_t* instance);


#endif
