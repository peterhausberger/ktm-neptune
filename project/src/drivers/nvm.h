/*
 *
 */

#ifndef NVM_H
#define NVM_H

#include <stdint.h>

#define NVM_FAILURE_INIT 0x80000000
#define NVM_FAILURE_READ 0x40000000
#define NVM_FAILURE_WRITE 0x3fffffff

extern uint32_t nvm_failure;

int32_t nvm_init(void);
int32_t nvm_deinit(void);

int32_t nvm_read_sync(uint8_t* data, uint32_t length);

int32_t nvm_write(const uint8_t* data, uint32_t length);

void nvm_step(void);

#endif
