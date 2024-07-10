/*
 *
 */

#ifndef DIO_H
#define DIO_H

#include "Siul2_Port_Ip.h"
#include "Siul2_Dio_Ip.h"

typedef struct {
	Siul2_Dio_Ip_GpioType* port;
	Siul2_Dio_Ip_PinsChannelType pin;
	uint16_t pin_reversed;
	uint16_t mask;
	uint16_t mask_inverted;
} dio_t;

extern const dio_t dio_in_11;
extern const dio_t dio_in_129;
extern const dio_t dio_in_154;
extern const dio_t dio_in_12;
extern const dio_t dio_in_71;
extern const dio_t dio_in_70;
extern const dio_t dio_in_130;
extern const dio_t dio_in_134;
extern const dio_t dio_in_3;
extern const dio_t dio_in_2;
extern const dio_t dio_in_0;
extern const dio_t dio_in_1;
extern const dio_t dio_in_50;
extern const dio_t dio_in_51;
extern const dio_t dio_in_52;
extern const dio_t dio_in_53;
extern const dio_t dio_in_29;
extern const dio_t dio_in_60;
extern const dio_t dio_in_43;

extern const dio_t dio_out_135;
extern const dio_t dio_out_44;

int32_t dio_init(void);
int32_t dio_deinit(void);
void dio_write(const dio_t* instance, uint16_t value);
inline void dio_set(const dio_t* instance) {
	instance->port->PGPDO |= instance->mask;
}
inline void dio_reset(const dio_t* instance) {
	instance->port->PGPDO &= instance->mask_inverted;
}
inline uint16_t dio_read(const dio_t* instance) {
	return (instance->port->PGPDI & instance->mask) >> instance->pin_reversed;
}

#endif
