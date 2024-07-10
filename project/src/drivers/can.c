/*
 *
 */

#include "IntCtrl_Ip.h"

#include "can.h"

extern void CAN0_ORED_0_31_MB_IRQHandler(void);
extern void CAN1_ORED_0_31_MB_IRQHandler(void);
extern void CAN3_ORED_0_31_MB_IRQHandler(void);

const can_instance_t can_0 = {
	FlexCAN0_1_IRQn,
	CAN0_ORED_0_31_MB_IRQHandler,
	INST_FLEXCAN_0,
	&FlexCAN_State0,
	&FlexCAN_Config0
};
const can_instance_t can_1 = {
	FlexCAN1_1_IRQn,
	CAN1_ORED_0_31_MB_IRQHandler,
	INST_FLEXCAN_1,
	&FlexCAN_State1,
	&FlexCAN_Config1
};
const can_instance_t can_3 = {
	FlexCAN3_1_IRQn,
	CAN3_ORED_0_31_MB_IRQHandler,
	INST_FLEXCAN_3,
	&FlexCAN_State2,
	&FlexCAN_Config2
};

int32_t can_init(const can_instance_t* instance) {
	// Init TX interrupt. IntCtrl_Ip_Init has to be already called.
	IntCtrl_Ip_EnableIrq(instance->irq);
	IntCtrl_Ip_InstallHandler(instance->irq, instance->irq_handler, NULL_PTR);

	if (FlexCAN_Ip_Init(instance->index, instance->state, instance->config) != FLEXCAN_STATUS_SUCCESS) return -1;
	if (FlexCAN_Ip_SetStartMode(instance->index) != FLEXCAN_STATUS_SUCCESS) return -2;

	return 0;
}

int32_t can_init_receive_mailbox(const can_instance_t* instance, uint8_t mailbox, uint32_t id) {
	Flexcan_Ip_DataInfoType info = {
		.msg_id_type = FLEXCAN_MSG_ID_STD,
		.data_length = 8u,
		.is_polling = TRUE,
		.is_remote = FALSE
	};
	if (FlexCAN_Ip_ConfigRxMb(instance->index, mailbox, &info, id) != FLEXCAN_STATUS_SUCCESS) return -1;
	return 0;
}

int32_t can_deinit(const can_instance_t* instance) {
	FlexCAN_Ip_SetStopMode(instance->index);
	FlexCAN_Ip_Deinit(instance->index);
	return 0;
}

int32_t can_receive(const can_instance_t* instance, uint8_t mailbox, can_message_buffer_t* message_buffer) {
	if (FlexCAN_Ip_GetTransferStatus(instance->index, mailbox) == FLEXCAN_STATUS_SUCCESS) {
		// @todo Warning might overwrite
		FlexCAN_Ip_Receive(instance->index, mailbox, (Flexcan_Ip_MsgBuffType*) message_buffer, TRUE); // Initiate next receive.
		return 1;
	} else {
		FlexCAN_Ip_MainFunctionRead(instance->index, mailbox);
		return 0;
	}
}

int32_t can_transmit(const can_instance_t* instance, uint8_t mailbox, const can_message_buffer_t* message_buffer) {
	if (FlexCAN_Ip_GetTransferStatus(instance->index, mailbox) == FLEXCAN_STATUS_SUCCESS) {
		Flexcan_Ip_DataInfoType info = {
			.msg_id_type = FLEXCAN_MSG_ID_STD,
			.data_length = message_buffer->length,
			.is_polling = FALSE,
			.is_remote = FALSE
		};
		FlexCAN_Ip_Send(instance->index, mailbox, &info, message_buffer->id, message_buffer->data);
		return 1;
	} else {
		return 0;
	}
}
