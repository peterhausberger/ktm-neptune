#include "serialize.h"

#include "string.h"

/* @todo Serialization uses the target byte order (little endian in ARM)! This has to be considered in monitor. Or change it here for the Linux target. */

// int32_t diagnostic0_database_uint32_to_be(uint32_t value, uint8_t* data) {
// 	data[0] = value >> 24; /* Big-endian. */
// 	data[1] = value >> 16;
// 	data[2] = value >> 8;
// 	data[3] = value >> 0;
// 	return 4;
// }

// int32_t diagnostic0_database_be_to_uint32(const uint8_t* data, uint32_t* value) {
// 	*value = (((uint32) data[0]) << 24) + /* Big-endian. */
// 		(((uint32) data[1]) << 16) +
// 		(((uint32) data[2]) << 8) +
// 		(((uint32) data[3]) << 0);
// 	return 4;
// }

int32_t serialize_float(float value, uint8_t* data) {
	memcpy(data, &value, 4);
	return 4;
}

int32_t serialize_uint32(uint32_t value, uint8_t* data) {
	memcpy(data, &value, 4);
	return 4;
}

int32_t serialize_int32(int32_t value, uint8_t* data) {
	memcpy(data, &value, 4);
	return 4;
}

int32_t serialize_uint16(uint16_t value, uint8_t* data) {
	memcpy(data, &value, 2);
	return 2;
}

int32_t serialize_int16(int16_t value, uint8_t* data) {
	memcpy(data, &value, 2);
	return 2;
}

int32_t serialize_uint8(uint8_t value, uint8_t* data) {
	memcpy(data, &value, 1);
	return 1;
}

int32_t serialize_int8(int8_t value, uint8_t* data) {
	memcpy(data, &value, 1);
	return 1;
}

int32_t serialize_boolean(uint8_t value, uint8_t* data) {
	memcpy(data, &value, 1);
	return 1;
}

int32_t deserialize_float(const uint8_t* data, float* value) {
	memcpy(value, data, 4);
	return 4;
}

int32_t deserialize_uint32(const uint8_t* data, uint32_t* value) {
	memcpy(value, data, 4);
	return 4;
}

int32_t deserialize_int32(const uint8_t* data, int32_t* value) {
	memcpy(value, data, 4);
	return 4;
}

int32_t deserialize_uint16(const uint8_t* data, uint16_t* value) {
	memcpy(value, data, 2);
	return 2;
}

int32_t deserialize_int16(const uint8_t* data, int16_t* value) {
	memcpy(value, data, 2);
	return 2;
}

int32_t deserialize_uint8(const uint8_t* data, uint8_t* value) {
	memcpy(value, data, 1);
	return 1;
}

int32_t deserialize_int8(const uint8_t* data, int8_t* value) {
	memcpy(value, data, 1);
	return 1;
}

int32_t deserialize_boolean(const uint8_t* data, uint8_t* value) {
	memcpy(value, data, 1);
	return 1;
}
