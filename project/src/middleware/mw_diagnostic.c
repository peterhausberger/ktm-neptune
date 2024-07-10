/*
 *
 */

#include "../drivers/lpuart.h"

#include "mw_diagnostic.h"

char mw_diagnostic_buffer[1000];

int32_t mw_diagnostic_init(void) {
	return lpuart_init();
}

int32_t mw_diagnostic_deinit(void) {
	return lpuart_deinit();
}

int32_t mw_diagnostic_log(const char* s) {
	uint32_t i = 0;
	while (s[i] != 0) {
		while (lpuart_transmit((uint8_t*) &s[i]) == 0);
		++i;
	}
	while (lpuart_transmit((uint8_t*) "\r") == 0);
	while (lpuart_transmit((uint8_t*) "\n") == 0);
	return 0;
}
