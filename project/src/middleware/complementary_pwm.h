/*
 *
 */

#ifndef COMPLEMENTARY_PWM_H
#define COMPLEMENTARY_PWM_H

#include "../drivers/pwm.h"

typedef struct {
	const pwm_instance_t* high_side_pwm; /* . */
	const pwm_instance_t* low_side_pwm; /* . */
    float value;
} complementary_pwm_instance_t;

int32_t complementary_pwm_init(const complementary_pwm_instance_t* instance);
int32_t complementary_pwm_deinit(const complementary_pwm_instance_t* instance);
int32_t complementary_pwm_step(const complementary_pwm_instance_t* instance);

#endif