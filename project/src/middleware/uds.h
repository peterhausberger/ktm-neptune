#ifndef UDS_H
#define UDS_H

#include "../drivers/can.h"
#include "../drivers/nvm.h"

typedef struct {
	int32_t (*read_data_by_identifier)(uint16_t, uint8_t*, uint8_t);
	int32_t (*write_data_by_identifier)(uint16_t, const uint8_t*, uint8_t);
	const uint32_t storage_size;
	uint8_t* storage;
	int32_t (*load)(void);
	int32_t (*store)(void);
} uds_database_t;

typedef struct {
	const uds_database_t database;
	const can_instance_t* can_instance;
	uint32_t can_request_id;
	uint32_t can_response_id;
	int32_t store_interval; /* Store interval in 100us. */
	can_message_buffer_t _can_request_message_buffer;
	can_message_buffer_t _can_response_message_buffer;
	uint32_t _next_store_timestamp; /* Store timestamp in 100us. */
} uds_instance_t;

int32_t uds_init(uds_instance_t* instance);
int32_t uds_deinit(uds_instance_t* instance);
int32_t uds_step(uds_instance_t* instance);

#endif
