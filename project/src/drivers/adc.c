/*
 *
 */

#include "adc.h"

/* By default S32K342, K358 and K311 boards will have 3.3V voltage reference selected while S32K312, S32K344 and S32K396 will have 5V selected.
 * If you have S32K342 with default pin configuration or if you've manually selected 3.3V reference, please uncomment the following line: */
//#define ADC_3V3_VREF_SELECTED
#ifdef ADC_3V3_VREF_SELECTED
#define ADC_BANDGAP                     5980U /* Vbandgap ~ 1.2V on 14 bits resolution, 3.3V VrefH */
#else
#define ADC_BANDGAP                     3932U /* Vbandgap ~ 1.2V on 14 bits resolution, 5V VrefH */
#endif

extern void Adc_Sar_0_Isr(void);
extern void Adc_Sar_1_Isr(void);
extern void Adc_Sar_2_Isr(void);

adc_t adc_0 = {
	ADCHWUNIT_2_INSTANCE,
	&AdcHwUnit_2,
	ADC0_IRQn,
	Adc_Sar_0_Isr,
	0
};
adc_t adc_1 = {
	ADCHWUNIT_1_INSTANCE,
	&AdcHwUnit_1,
	ADC1_IRQn,
	Adc_Sar_1_Isr,
	0
};
adc_t adc_2 = {
	ADCHWUNIT_0_INSTANCE,
	&AdcHwUnit_0,
	ADC2_IRQn,
	Adc_Sar_2_Isr,
	0
};

volatile float adc_0_channel_6;
volatile float adc_1_channel_2;
volatile float adc_1_channel_43;
volatile float adc_2_channel_3;
volatile float adc_2_channel_4;
volatile float adc_2_channel_5;

/*
 * ADC0
 */
void AdcEndOfChainNotif2(void) {
	adc_0.conversion_finished = 1;
	adc_0_channel_6 = Adc_Sar_Ip_GetConvData(adc_0.instance, 6U) / 16383.0f;
}

/*
 * ADC1
 */
void AdcEndOfChainNotif1(void) {
	adc_1.conversion_finished = 1;
	adc_1_channel_2 = Adc_Sar_Ip_GetConvData(adc_1.instance, 2U) / 16383.0f;
	adc_1_channel_43 = Adc_Sar_Ip_GetConvData(adc_1.instance, 43U) / 16383.0f;
}

/*
 * ADC2
 */
void AdcEndOfChainNotif(void) {
	adc_2.conversion_finished = 1;
	adc_2_channel_3 = Adc_Sar_Ip_GetConvData(adc_2.instance, 3U) / 16383.0f; /* PTA11 (Internal Bandgap Channel) */
	adc_2_channel_4 = Adc_Sar_Ip_GetConvData(adc_2.instance, 4U) / 16383.0f; /* PTE2 */
	adc_2_channel_5 = Adc_Sar_Ip_GetConvData(adc_2.instance, 5U) / 16383.0f; /* PTE6 */
    /* Checks the measured ADC data conversion */
    //while (ADC_TOLERANCE(data, ADC_BANDGAP));
}

int32_t adc_init(adc_t* instance) {
	StatusType status = (StatusType) Adc_Sar_Ip_Init(instance->instance, instance->config);
    if (status != E_OK) return -1;

    IntCtrl_Ip_InstallHandler(instance->irq_number, instance->irq_handler, NULL_PTR);
    IntCtrl_Ip_EnableIrq(instance->irq_number);

    /* Call Calibration function multiple times, to mitigate instability of board source. */
    for (uint8 i = 0; i <= 5; ++i) {
        status = (StatusType) Adc_Sar_Ip_DoCalibration(instance->instance);
        if (status == E_OK) break;
    }
    if (status != E_OK) return -1;

    //Adc_Sar_Ip_EnableNotifications(ADCHWUNIT_0_INSTANCE, ADC_SAR_IP_NOTIF_FLAG_NORMAL_ENDCHAIN | ADC_SAR_IP_NOTIF_FLAG_INJECTED_ENDCHAIN);
    Adc_Sar_Ip_EnableNotifications(instance->instance, ADC_SAR_IP_NOTIF_FLAG_NORMAL_ENDCHAIN);
    return 0;
}

int32_t adc_deinit(adc_t* instance) {
	StatusType status = (StatusType) Adc_Sar_Ip_Deinit(instance->instance);
    if (status != E_OK) return -1;
    return 0;
}

int32_t adc_start_conversion(adc_t* instance) {
    /* Start a SW triggered normal conversion on ADC_SAR */
    instance->conversion_finished = FALSE;
	Adc_Sar_Ip_StartConversion(instance->instance, ADC_SAR_IP_CONV_CHAIN_NORMAL);
    return 0;
}
