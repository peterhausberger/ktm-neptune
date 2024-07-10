/*
 *
 */

#include "Std_Types.h"

#include "KIN1.h"

#include "timer.h"

//extern uint32_t SystemCoreClock;
//#define CLOCK_CONV (1.0F / (double) SystemCoreClock) * 1000000.0F
//#define CLOCK_CONV (1.0F / (double) 80000000.0) * 1000000.0F

#define CLOCK_MHZ 160

static uint64_t _cyccnt_upper_32bit;
static uint32_t _prev_cyccnt;

static uint64_t _timer_get(void) {
    uint32_t cyccnt = KIN1_DWT_CYCCNT;
	if (cyccnt < _prev_cyccnt) _cyccnt_upper_32bit += UINT32_MAX;
	_prev_cyccnt = cyccnt;

	return (_cyccnt_upper_32bit + cyccnt);
}

void timer_init(void) {
    KIN1_InitCycleCounter();
    KIN1_ResetCycleCounter();
    KIN1_EnableCycleCounter();

    _cyccnt_upper_32bit = 0;
    _prev_cyccnt = 0;
}

/*
 * @return The current timer in us.
 * @note It is important that the timer is called regularly (at least once every 26 s for 160 MHz).
 */
uint64_t timer_get(void) {
	return (_timer_get() / CLOCK_MHZ);
}