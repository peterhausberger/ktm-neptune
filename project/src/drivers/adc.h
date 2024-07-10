/*
 *
 */

#ifndef ADC_H
#define ADC_H

#include "Adc_Sar_Ip.h"
#include "IntCtrl_Ip.h"

typedef struct {
	const uint32_t instance;
	const Adc_Sar_Ip_ConfigType* const config;
	const IRQn_Type irq_number;
	const IntCtrl_Ip_IrqHandlerType irq_handler;
	volatile uint8_t conversion_finished;
} adc_t;

extern adc_t adc_0;
extern adc_t adc_1;
extern adc_t adc_2;

extern volatile float adc_0_channel_6;
extern volatile float adc_1_channel_2;
extern volatile float adc_1_channel_43;
extern volatile float adc_2_channel_3;
extern volatile float adc_2_channel_4;
extern volatile float adc_2_channel_5;

int32_t adc_init(adc_t* instance);
int32_t adc_deinit(adc_t* instance);
int32_t adc_start_conversion(adc_t* instance);

#endif
