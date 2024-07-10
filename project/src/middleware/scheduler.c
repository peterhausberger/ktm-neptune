#include "scheduler.h"

#include "../drivers/timer.h"

#include "OsIf_Internal.h"

static scheduler_t* _instance;

scheduler_t* scheduler_get(void) {
    return _instance;
}

void scheduler_init(scheduler_t* instance) {
    _instance = instance;
    
    instance->cycle = UINT32_MAX;
    instance->_next_wakeup_timer_us = 0;
    instance->timer_100us = 0;
    instance->warning = 0;

    timer_init();
}

void scheduler_step(scheduler_t* instance) {
    ++instance->cycle;

    //OsIf_SuspendAllInterrupts();
    uint64_t timer;
    if (instance->_next_wakeup_timer_us == 0) {
    	instance->warning = 0;
    	instance->_next_wakeup_timer_us = (timer = timer_get());
    } else if ((timer = timer_get()) >= instance->_next_wakeup_timer_us) {
        instance->warning = 1;
    } else {
	    instance->warning = 0;
        while ((timer = timer_get()) < instance->_next_wakeup_timer_us);
    }

    instance->_next_wakeup_timer_us += instance->interval;
    instance->timer_100us = timer / 100;
    //OsIf_ResumeAllInterrupts();
}
