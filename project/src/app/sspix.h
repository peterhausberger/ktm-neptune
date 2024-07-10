#include "math.h"

float sspi_ia;
float sspi_ib;
float sspi_ic;

#define _ia_cs (&dio_out_44)
#define _ib_cs (&dio_out_44)
#define _ic_cs (&dio_out_44)
#define _ia_clk (&dio_out_135)
#define _ib_clk (&dio_out_135)
#define _ic_clk (&dio_out_135)
#define _ia_miso (&dio_in_11)
#define _ib_miso (&dio_in_11)
#define _ic_miso (&dio_in_11)

static float _convert(uint16_t raw) {
	if (raw & 0xc003) return NAN;
	return ((raw >> 2) / 4095.f);
}

void sspi_step(void) {
	OsIf_SuspendAllInterrupts();

	uint16_t ia_data = 0;
	uint16_t ib_data = 0;
	uint16_t ic_data = 0;

	dio_reset(_ia_cs);
	dio_reset(_ib_cs);
	dio_reset(_ic_cs);

	for (uint8 i = 15; i < 16; --i) {
		// Second sampling of data or NOPS?

		dio_reset(_ia_clk);
		dio_reset(_ib_clk);
		dio_reset(_ic_clk);

		ia_data |= dio_read(_ia_miso) << i;
		ib_data |= dio_read(_ib_miso) << i;
		ic_data |= dio_read(_ic_miso) << i;

		dio_set(_ia_clk);
		dio_set(_ib_clk);
		dio_set(_ic_clk);
	}

	// NOPS?

	dio_set(_ia_cs);
	dio_set(_ib_cs);
	dio_set(_ic_cs);

	OsIf_ResumeAllInterrupts();

	// Convert data
	sspi_ia = _convert(ia_data);
	sspi_ib = _convert(ib_data);
	sspi_ic = _convert(ic_data);
}
