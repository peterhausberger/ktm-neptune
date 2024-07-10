#include "uds.h"

#include "scheduler.h"
#include "serialize.h"

typedef enum {
	_SID_READ_DATA_BY_IDENTIFIER_REQUEST = 0x22,
	_SID_READ_DATA_BY_IDENTIFIER_RESPONSE = 0x62,
	_SID_WRITE_DATA_BY_IDENTIFIER_REQUEST = 0x2e,
	_SID_WRITE_DATA_BY_IDENTIFIER_RESPONSE = 0x6e,
} _sid_t;

int32_t uds_init(uds_instance_t* instance) {
	// Init CAN RX mailbox.
	can_init_receive_mailbox(instance->can_instance, CAN_MAILBOXES - 2, instance->can_request_id);

	/* Initialize NVM. */
	/* @todo Currently UDS is the only module which uses the NVM. If it is used by other modules in future, remove this from here. */
	int32_t nvm_init_result = nvm_init();
	if (nvm_init_result != 0) return nvm_init_result;

	/* Load data from NVM. */
	if (instance->database.storage_size > 0) {
		int32_t nvm_read_result = nvm_read_sync(instance->database.storage, instance->database.storage_size); /* Synchronous read. */
		if (nvm_read_result != 0) {
			return nvm_read_result;
		}
		int32_t length = instance->database.load();
		if (length != instance->database.storage_size) {
			return -1;
		}
	}

	/* Init timer. */
	instance->_next_store_timestamp = instance->store_interval;
	
	return 0;
}

int32_t uds_deinit(uds_instance_t* instance) {
	(void) instance; // Parameter not used.

	return 0;
}

int32_t uds_step(uds_instance_t* instance) {
	/* Is a UDS request pending? */
	if (can_receive(instance->can_instance, CAN_MAILBOXES - 2, &instance->_can_request_message_buffer)) {
		if (instance->_can_request_message_buffer.id != instance->can_request_id) return -1; // Inconsistency.
		uint8_t pci = instance->_can_request_message_buffer.data[0];
		uint8_t service_id = instance->_can_request_message_buffer.data[1];
		//uint16 data_id = (((uint16) instance->_can_request_message_buffer.data[2]) << 8) + instance->_can_request_message_buffer.data[3]; /* Big-endian. */
		uint16_t data_id;
		deserialize_uint16(&instance->_can_request_message_buffer.data[2], &data_id);

		switch (service_id) {
			case _SID_READ_DATA_BY_IDENTIFIER_REQUEST: {
				int32_t length = instance->database.read_data_by_identifier(data_id, &instance->_can_response_message_buffer.data[4], 4);
				instance->_can_response_message_buffer.id = instance->can_response_id;
				instance->_can_response_message_buffer.length = 4 + length;
				instance->_can_response_message_buffer.data[0] = 3 + length;
				instance->_can_response_message_buffer.data[1] = _SID_READ_DATA_BY_IDENTIFIER_RESPONSE;
				instance->_can_response_message_buffer.data[2] = instance->_can_request_message_buffer.data[2];
				instance->_can_response_message_buffer.data[3] = instance->_can_request_message_buffer.data[3];
				can_transmit(instance->can_instance, CAN_MAILBOXES - 1, &instance->_can_response_message_buffer);
				break;
			}
			case _SID_WRITE_DATA_BY_IDENTIFIER_REQUEST: {
				int32_t length = instance->database.write_data_by_identifier(data_id, &instance->_can_request_message_buffer.data[4], instance->_can_request_message_buffer.length - 4);
				instance->_can_response_message_buffer.id = instance->can_response_id;
				instance->_can_response_message_buffer.length = 4;
				instance->_can_response_message_buffer.data[0] = 3;
				instance->_can_response_message_buffer.data[1] = _SID_WRITE_DATA_BY_IDENTIFIER_RESPONSE;
				instance->_can_response_message_buffer.data[2] = instance->_can_request_message_buffer.data[2];
				instance->_can_response_message_buffer.data[3] = instance->_can_request_message_buffer.data[3];
				can_transmit(instance->can_instance, CAN_MAILBOXES - 1, &instance->_can_response_message_buffer);
				break;
			}
			default:
				break;
		}
	}

	/* Should database be stored to NVM? */
	if (scheduler_get()->timer_100us >= instance->_next_store_timestamp) {
		instance->_next_store_timestamp = scheduler_get()->timer_100us + instance->store_interval;
		int32_t length = instance->database.store();
		int32_t nvm_write_result = nvm_write(instance->database.storage, instance->database.storage_size); /* @todo Assure that NVM is not busy with the last write. */
		if (nvm_write_result != 0) return nvm_write_result;
	}
	nvm_step();

	return 0;
}
