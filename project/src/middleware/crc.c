#include "crc.h"

/**
 * Calculates a 5 bit CRC.
 *
 * @param data
 * @param bit_length Number of bits used for CRC calculation.
 * @param mask
 */
uint8_t crc_5(uint64_t data, uint8_t bit_length, uint8_t mask) {
	uint8_t crc = 0;
    uint8_t i;
    for (i = 0; i < bit_length; ++i) {
        //bit = (data[i / 8] >> (7 - (i % 8))) & 1;
    	uint8_t bit = (data >> i) & 1;
        //console.log('Crc5.calc: Bit at position ' + i + ' = 0b' + bit);
        if (((crc >> 4) & 1) != bit) {
            crc = (crc << 1) ^ mask;
        } else {
            crc = crc << 1;
        }
        crc = crc & 0x1F;
        //console.log('Crc5.calc: CRC at position ' + i + ' = 0b' + crc.toString(2));
    }
    return crc;
}