#include "dio.h"

typedef struct {
	const dio_t* cs_a;
	const dio_t* cs_b;
	const dio_t* cs_c;
	const dio_t* sclk_a;
	const dio_t* sclk_b;
	const dio_t* sclk_c;
	const dio_t* miso_a;
	const dio_t* miso_b;
	const dio_t* miso_c;
	uint16_t read_a;
	uint16_t read_b;
	uint16_t read_c;
} stspi_t;

void stspi_init(const stspi_t* instance);
void stspi_deinit(const stspi_t* instance);

void stspi_read(stspi_t* instance);
