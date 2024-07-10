/*
 *
 */

#include "lpuart.h"

#include "Lpuart_Uart_Ip.h"
#include "Lpuart_Uart_Ip_Irq.h"

#define _CHANNEL 2

uint8_t _receive_data;

int32_t lpuart_init(void) {
	/* Initializes an UART driver*/
	Lpuart_Uart_Ip_Init(_CHANNEL, &Lpuart_Uart_Ip_xHwConfigPB_2);
	return 0;
}

int32_t lpuart_deinit(void) {
	(void) Lpuart_Uart_Ip_Deinit(_CHANNEL);
	return 0;
}

int32_t lpuart_receive(uint8_t* data) {
	// Check if receive is finished.
	uint32 remaining_bytes;
	Lpuart_Uart_Ip_StatusType status = Lpuart_Uart_Ip_GetReceiveStatus(_CHANNEL, &remaining_bytes);
    if (status == LPUART_UART_IP_STATUS_BUSY) return 0;
    if (status != LPUART_UART_IP_STATUS_SUCCESS) return -1;

    // Initiate next receive
	*data = _receive_data;
    status = Lpuart_Uart_Ip_AsyncReceive(_CHANNEL, &_receive_data, 1);
	if (status != LPUART_UART_IP_STATUS_SUCCESS) return -2;
	return 1;
}

int32_t lpuart_transmit(const uint8_t* data) {
    // Check if previous transmit is finished.
	uint32_t remaining_bytes;
    Lpuart_Uart_Ip_StatusType status = Lpuart_Uart_Ip_GetTransmitStatus(_CHANNEL, &remaining_bytes);
    if (status == LPUART_UART_IP_STATUS_BUSY) return 0;
    if (status != LPUART_UART_IP_STATUS_SUCCESS) return -1;

    // Transmit data.
	status = Lpuart_Uart_Ip_AsyncSend(_CHANNEL, data, 1);
    if (status != LPUART_UART_IP_STATUS_SUCCESS) return -2;
    return 1;
}

