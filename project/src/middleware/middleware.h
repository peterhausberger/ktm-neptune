/*
 *
 */

#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

#include <stdint.h>

int32_t middleware_run(void);

int32_t middleware_init(void);
int32_t middleware_deinit(void);
int32_t middleware_step(void);

#endif
