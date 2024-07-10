/*
 *
 */

#include "pwm.h"

#include "Emios_Mcl_Ip.h"

const pwm_instance_t pwm_instance_1 = {EMIOS_PWM_IP_I0_CH1_CFG, &Emios_Pwm_Ip_I0_Ch1};
const pwm_instance_t pwm_instance_2 = {EMIOS_PWM_IP_I0_CH2_CFG, &Emios_Pwm_Ip_I0_Ch2};
const pwm_instance_t pwm_instance_3 = {EMIOS_PWM_IP_I0_CH3_CFG, &Emios_Pwm_Ip_I0_Ch3};
const pwm_instance_t pwm_instance_4 = {EMIOS_PWM_IP_I0_CH4_CFG, &Emios_Pwm_Ip_I0_Ch4};
const pwm_instance_t pwm_instance_5 = {EMIOS_PWM_IP_I0_CH5_CFG, &Emios_Pwm_Ip_I0_Ch5};
const pwm_instance_t pwm_instance_6 = {EMIOS_PWM_IP_I0_CH6_CFG, &Emios_Pwm_Ip_I0_Ch6};

#define _INSTANCE_0 (uint8_t) 0U
#define _CHANNEL_23 (uint8_t) 23U

#define _CORE_FREQUENCEY_MHZ 160U
#define _TARGET_FREQUENCY_KHZ 16U
#define _COUNTER_PERIOD ((uint32_t) (_CORE_FREQUENCEY_MHZ * 1000) / _TARGET_FREQUENCY_KHZ)

#define _CENTERED TRUE

static uint8_t _initialized = 0;

int32_t pwm_init(const pwm_instance_t* instance) {
	if (!_initialized) {
		/* Initialize Emios_Mcl driver */
		//Emios_Mcl_Ip_Init(_INSTANCE_0, &Emios_Mcl_Ip_0_Config_BOARD_INITPERIPHERALS);

		/* Set new period for the channels that used external counter bus */
		//Emios_Mcl_Ip_SetCounterBusPeriod(INSTANCE_0, CHANNEL_23, 0x5000);
		Emios_Mcl_Ip_SetCounterBusPeriod(_INSTANCE_0, _CHANNEL_23, _COUNTER_PERIOD);

		_initialized = 1;
	}

    /* Initialize Emios_Pwm_Ip driver */
    //Emios_Pwm_Ip_InitChannel(EMIOS_PWM_IP_VS_0_I0_CH4_CFG, &Emios_Pwm_Ip_VS_0_I0_Ch4);
    Emios_Pwm_Ip_InitChannel(instance->instance, instance->config);

    return 0;
}

int32_t pwm_deinit(const pwm_instance_t* instance) {
    /* De-Initialize Emios_Pwm_Ip driver */
    //Emios_Pwm_Ip_DeInitChannel(INSTANCE_0, CHANNEL_4);
    Emios_Pwm_Ip_DeInitChannel(instance->instance, instance->config->ChannelId);

    // @todo Call Emios_Mcl_Ip_Deinit.

    return 0;
}

/*int32_t pwm_set_duty_cycle(const pwm_instance_t* instance, float duty_cycle) {
    Emios_Pwm_Ip_SetDutyCycle(instance->instance, instance->config->ChannelId, (uint16_t) (duty_cycle * _COUNTER_PERIOD));

	#if _CENTERED
    	float phase_shift = (1 - duty_cycle) / 2;
    	Emios_Pwm_Ip_SetPhaseShift(instance->instance, instance->config->ChannelId, (uint16_t) (phase_shift * _COUNTER_PERIOD));
	#endif

    return 0;
}*/

int32_t pwm_set_duty_cycle(const pwm_instance_t* instance, float value) {
	uint16_t duty_cycle = (uint16_t) (value * _COUNTER_PERIOD);
	uint16_t phase_shift = (_COUNTER_PERIOD - duty_cycle) / 2;

	IP_EMIOS_0->CH.UC[instance->config->ChannelId].A = phase_shift;
	IP_EMIOS_0->CH.UC[instance->config->ChannelId].B = phase_shift + duty_cycle;

    return 0;
}
