#ifndef CRC_H
#define CRC_H

#include <stdint.h>

uint8_t crc_5(uint64_t data, uint8_t bit_length, uint8_t mask);

#endif