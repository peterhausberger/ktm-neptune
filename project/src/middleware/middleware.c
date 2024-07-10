/*
 *
 */

//#include <stdio.h>

#include "mw_diagnostic.h"

#include "middleware.h"

#include "../drivers/lpuart.h"
#include "../drivers/timer.h"

#include "../app/app.g.h"

int32_t middleware_run(void) {
	if (middleware_init() < 0) return -1;

	while (1) {
		if (middleware_step() < 0) return -2;
	}

	if (middleware_deinit() < 0) return -3;

	return 0;
}

int32_t middleware_init(void) {
	mw_diagnostic_init();

	app_init();

	return 0;
}

int32_t middleware_deinit(void) {
	app_deinit();
	return 0;
}

int32_t middleware_step(void) {
	app_step();
	
	/*char str3[80];
	sprintf(str3, "%f", *x2cModel.outports.bnvm_avg_torque);
	mw_diagnostic_log(str3);*/

	/*uint16 duty_cycle = 0;
	for (; duty_cycle < 0x5000; ++duty_cycle) {
		pwm_set_duty_cycle(duty_cycle);
		TestDelay(10000);
	}*/

	/*uint8 received_char;
	if (lpuart_receive(&received_char)) {
		while (lpuart_transmit(&received_char) == 0);
	}

	_timer = timer_get();*/

	return 0;
}

