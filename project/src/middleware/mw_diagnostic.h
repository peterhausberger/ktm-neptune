/*
 *
 */

#ifndef MW_DIAGNOSTIC_H
#define MW_DIAGNOSTIC_H

#include <stdint.h>

#define MW_DIAGNOSTIC_LOG(...) { \
	sprintf(mw_diagnostic_buffer, __VA_ARGS__); \
	mw_diagnostic_log(mw_diagnostic_buffer); \
}

extern char mw_diagnostic_buffer[];

int32_t mw_diagnostic_init(void);
int32_t mw_diagnostic_deinit(void);

int32_t mw_diagnostic_log(const char* s);

#endif
