#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

typedef struct {
    const uint32_t interval;
    uint32_t cycle;
    uint64_t _next_wakeup_timer_us;
    uint32_t timer_100us;
    uint8_t warning;
} scheduler_t;

scheduler_t* scheduler_get(void);

void scheduler_init(scheduler_t* instance);
void scheduler_step(scheduler_t* instance);

#endif
