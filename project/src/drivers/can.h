/*
 *
 */

#ifndef CAN_H
#define CAN_H

#include "FlexCAN_Ip.h"
#include "IntCtrl_Ip.h"

#define CAN_MAILBOXES 32

typedef struct {
	IRQn_Type irq;
	IntCtrl_Ip_IrqHandlerType irq_handler;
	uint8_t index;
	Flexcan_Ip_StateType* state;
	const Flexcan_Ip_ConfigType* config;
} can_instance_t;

typedef struct {
    uint32_t dummy1;                    /**< Code and Status*/
    uint32_t id;                        /**< Message Buffer ID*/
    uint8_t data[64];                   /**< Data bytes of the FlexCAN message*/
    uint8_t length;                     /**< Length of data in bytes */
    uint8_t dummy2;                     /**< Identifier Acceptance Filter Hit Indicator*/
    uint32_t dummy3; 					  /**< Free-Running Counter Time Stamp*/
} can_message_buffer_t;

extern const can_instance_t can_0;
extern const can_instance_t can_1;
extern const can_instance_t can_3;

int32_t can_init(const can_instance_t* instance);
int32_t can_init_receive_mailbox(const can_instance_t* instance, uint8_t mailbox, uint32_t id);
int32_t can_deinit(const can_instance_t* instance);

int32_t can_receive(const can_instance_t* instance, uint8_t mailbox, can_message_buffer_t* message_buffer);
int32_t can_transmit(const can_instance_t* instance, uint8_t mailbox, const can_message_buffer_t* message_buffer);

#endif
