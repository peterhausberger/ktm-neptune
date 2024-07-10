/*
 *
 */

#ifndef PWM_H
#define PWM_H

#include "Emios_Pwm_Ip.h"

typedef struct {
	uint8_t instance;
	const Emios_Pwm_Ip_ChannelConfigType* config;
} pwm_instance_t;

extern const pwm_instance_t pwm_instance_1;
extern const pwm_instance_t pwm_instance_2;
extern const pwm_instance_t pwm_instance_3;
extern const pwm_instance_t pwm_instance_4;
extern const pwm_instance_t pwm_instance_5;
extern const pwm_instance_t pwm_instance_6;

int32_t pwm_init(const pwm_instance_t* instance);
int32_t pwm_deinit(const pwm_instance_t* instance);
int32_t pwm_set_duty_cycle(const pwm_instance_t* instance, float duty_cycle);

#endif
