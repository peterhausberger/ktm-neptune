#include "complementary_pwm.h"

#define _DEAD_TIME (0.016f) /* . */

static float _bound(float value) {
    if (value < 0.0f) return 0.0f;
    if (value > 1.0f) return 1.0f;
    return value;
}

int32_t complementary_pwm_init(const complementary_pwm_instance_t* instance) {
    int32_t result;
    if ((result = pwm_init(instance->high_side_pwm)) != 0) return result;
    if ((result = pwm_init(instance->low_side_pwm)) != 0) return result;
    return 0;
}

int32_t complementary_pwm_deinit(const complementary_pwm_instance_t* instance) {
    int32_t result;
    if ((result = pwm_deinit(instance->low_side_pwm)) != 0) return result;
    if ((result = pwm_deinit(instance->high_side_pwm)) != 0) return result;
    return 0;
}

#include "../drivers/dio.h"

int32_t complementary_pwm_step(const complementary_pwm_instance_t* instance) {
    float high_side_value, low_side_value;
    if ((instance->value >= 0.0f) && (instance->value <= 1.0f)) {
        high_side_value = _bound(instance->value - _DEAD_TIME);
        low_side_value = _bound(instance->value + _DEAD_TIME);
    } else {
        /* Make sure both PWM signals are 0. The low side is inverted, so set a duty cycle of 1. */
        high_side_value = 0.0f;
        low_side_value = 1.0f; 
    }

    int32_t result;
    //dio_write(&dio_out_44, 1);
    if ((result = pwm_set_duty_cycle(instance->high_side_pwm, high_side_value)) != 0) return result;
    //dio_write(&dio_out_44, 0);
    if ((result = pwm_set_duty_cycle(instance->low_side_pwm, low_side_value)) != 0) return result;

    return 0;
}
