/*
 * The original implementation were:
 *  - Siul2_Dio_Ip_WritePin(instance->port, instance->pin, value)
 *  - Siul2_Dio_Ip_ReadPin(instance->port, instance->pin)
 * Since this is very inefficient, an optimized version is used.
 */

#include "dio.h"

#define _INIT(port, pin) {port, pin, 15U - pin, (uint16_t) 1U << (15U - pin), (uint16_t) ~(1U << (15U - pin))}

const dio_t dio_in_11 = _INIT(PTA_L_HALF, 11U); /* P8B > EXT_GPIO1 (PTA11/GPIO11). */
const dio_t dio_in_129 = _INIT(PTE_L_HALF, 1U); /* P8B > EXT_GPIO2 (PTE1/GPIO129). */
const dio_t dio_in_154 = _INIT(PTE_H_HALF, 10U); /* P8B > EXT_GPIO3 (PTE26/GPIO154). */
const dio_t dio_in_12 = _INIT(PTA_L_HALF, 12U); /* P8B > EXT_GPIO4 (PTA12/GPIO12). */
const dio_t dio_in_71 = _INIT(PTC_L_HALF, 7U); /* P5 > LPUART1_TX (PTC7/GPIO71) */
const dio_t dio_in_70 = _INIT(PTC_L_HALF, 6U); /* P5 > LPUART1_RX (PTC6/GPIO70). */
const dio_t dio_in_130 = _INIT(PTE_L_HALF, 2U); /* P5 > LPUART1_CTS (PTE2/GPIO130). */
const dio_t dio_in_134 = _INIT(PTE_L_HALF, 6U); /* P5 > LPUART1_RTS (PTE6/GPIO134). */
const dio_t dio_in_3 = _INIT(PTA_L_HALF, 3U); /* P2/LPUART0_TX (PTA3/GPIO3). */
const dio_t dio_in_2 = _INIT(PTA_L_HALF, 2U); /* P2/LPUART0_RX (PTA2/GPIO2). */
const dio_t dio_in_0 = _INIT(PTA_L_HALF, 0U); /* P2/LPUART0_CTS (PTA0/GPIO0). */
const dio_t dio_in_1 = _INIT(PTA_L_HALF, 1U); /* P2/LPUART0_RTS (PTA1/GPIO1). */
const dio_t dio_in_50 = _INIT(PTB_H_HALF, 2U); /* P25/LPUART13_TX (PTB18/GPIO50). */
const dio_t dio_in_51 = _INIT(PTB_H_HALF, 3U); /* P25/LPUART13_RX (PTB19/GPIO51). */
const dio_t dio_in_52 = _INIT(PTB_H_HALF, 4U); /* P25/LPUART14_TX (PTB20/GPIO52). */
const dio_t dio_in_53 = _INIT(PTB_H_HALF, 5U); /* P25/LPUART14_RX (PTB21/GPIO53). */
const dio_t dio_in_29 = _INIT(PTA_H_HALF, 13U); /* SP1_MOSI. */
const dio_t dio_in_60 = _INIT(PTB_H_HALF, 12U); /* SP1_MOSI. */
const dio_t dio_in_43 = _INIT(PTB_L_HALF, 11U); /* SP1_MOSI. */

const dio_t dio_out_135 = _INIT(PTE_L_HALF, 7U); /* P8A/PWM_CH7 (PTE7/GPIO135). */
const dio_t dio_out_44 = _INIT(PTB_L_HALF, 12U); /* P8A > PWM_CH0 (PTB12/GPIO44). */

int32_t dio_init(void) {
    /* Initialize all pins using the Port driver */
    Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
    return 0;
}

int32_t dio_deinit(void) {
	return 0;
}

/*
 * The original implementation was: Siul2_Dio_Ip_WritePin(instance->port, instance->pin, value)
 * Since this is very inefficient, an optimized version is used.
 */
void dio_write(const dio_t* instance, uint16_t value) {
	if (value) dio_set(instance);
	else dio_reset(instance);
}

