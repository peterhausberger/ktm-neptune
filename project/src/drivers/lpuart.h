/*
 *
 */

#ifndef LPUART_H
#define LPUART_H

#include <stdint.h>

int32_t lpuart_init(void);
int32_t lpuart_deinit(void);

int32_t lpuart_receive(uint8_t* data);
int32_t lpuart_transmit(const uint8_t* data);

#endif
