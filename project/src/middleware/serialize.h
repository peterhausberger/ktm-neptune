#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <stdint.h>

int32_t serialize_float(float value, uint8_t* data);
int32_t serialize_uint32(uint32_t value, uint8_t* data);
int32_t serialize_int32(int32_t value, uint8_t* data);
int32_t serialize_uint16(uint16_t value, uint8_t* data);
int32_t serialize_int16(int16_t value, uint8_t* data);
int32_t serialize_uint8(uint8_t value, uint8_t* data);
int32_t serialize_int8(int8_t value, uint8_t* data);
int32_t serialize_boolean(uint8_t value, uint8_t* data);

int32_t deserialize_float(const uint8_t* data, float* value);
int32_t deserialize_uint32(const uint8_t* data, uint32_t* value);
int32_t deserialize_int32(const uint8_t* data, int32_t* value);
int32_t deserialize_uint16(const uint8_t* data, uint16_t* value);
int32_t deserialize_int16(const uint8_t* data, int16_t* value);
int32_t deserialize_uint8(const uint8_t* data, uint8_t* value);
int32_t deserialize_int8(const uint8_t* data, int8_t* value);
int32_t deserialize_boolean(const uint8_t* data, uint8_t* value);

#endif
