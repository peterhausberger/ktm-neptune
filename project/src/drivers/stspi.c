/*
 * Software triple SPI
 *
 * Current limitations:
 *  - Only read operations are currently supported.
 *  - Only 16 bit words are currently supported.
 *  - Clock is not configureable.
 */

#include "stspi.h"

void stspi_init(const stspi_t* instance) {
	dio_set(instance->cs_a);
	dio_set(instance->cs_b);
	dio_set(instance->cs_c);

	dio_set(instance->sclk_a);
	dio_set(instance->sclk_b);
	dio_set(instance->sclk_c);
}

void stspi_deinit(const stspi_t* instance) {
}

void stspi_read(stspi_t* instance) {
	OsIf_SuspendAllInterrupts();

	dio_reset(instance->cs_a);
	dio_reset(instance->cs_b);
	dio_reset(instance->cs_c);

	instance->read_a = 0;
	instance->read_b = 0;
	instance->read_c = 0;

	for (uint8 i = 15; i <= 15; --i) {
		// Second sampling of data or NOPS?

		dio_reset(instance->sclk_a);
		dio_reset(instance->sclk_b);
		dio_reset(instance->sclk_c);

		instance->read_a |= dio_read(instance->miso_a) << i;
		instance->read_b |= dio_read(instance->miso_b) << i;
		instance->read_c |= dio_read(instance->miso_c) << i;

		dio_set(instance->sclk_a);
		dio_set(instance->sclk_b);
		dio_set(instance->sclk_c);
	}

	// NOPS?

	dio_set(instance->cs_a);
	//dio_set(instance->cs_b);
	//dio_set(instance->cs_c);

	OsIf_ResumeAllInterrupts();
}
