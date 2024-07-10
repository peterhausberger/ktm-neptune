/*
 * A sector has a size of 8192 (0x2000) bytes.
 * An erase call erases a whole sector.
 * A sector contains 64 quadpages per 128 bytes each.
 *
 * A single write call can only write within a quadpage.
 * A write call must be 8-byte-aligned (address and length).
 *
 * An erase must be called before calling write:
 * 	   "A program operation changes the logic value of a bit from 1 to 0, this means that a program operation 
 *      from 0 to 1 is not allowed and the Flash memory needs to be erased before any program operation."
 *
 * A single read call can read even more than 1 sector.  
 * 
 * Further information can be found here: https://www.mouser.com/pdfDocs/S32K3MemoriesGuide.pdf
 *
 * 
 */

#include "nvm.h"

#include "C40_Ip.h"

#define _MASTER_ID 0U
#define _SECTOR_ADDRESS 0x00600000U // 0x00600000U
#define _SECTOR C40_CODE_ARRAY_0_BLOCK_2_S256 // C40_CODE_ARRAY_0_BLOCK_2_S256

uint32_t nvm_failure = 0;

uint8_t* _data = 0;
uint32_t _length = 0;
enum {
	_STATE_IDLE,
	_STATE_WAIT_FOR_ERASE_FINISHED,
	_STATE_WAIT_FOR_WRITE_FINISHED
} _state = _STATE_IDLE;

int32_t nvm_init(void) {
	nvm_failure = 0;
	
	/* Initialize C40 driver. */
	if (C40_Ip_Init(&C40_Ip_InitCfg) != STATUS_C40_IP_SUCCESS) {
		nvm_failure |= NVM_FAILURE_INIT;
		return -1;
	}

	/* Unlock sector if needed */
	C40_Ip_StatusType status = C40_Ip_GetLock(_SECTOR);
	if (status == STATUS_C40_IP_SECTOR_PROTECTED) {
		status = C40_Ip_ClearLock(_SECTOR, _MASTER_ID);
	}
	if (status != STATUS_C40_IP_SUCCESS) {
		nvm_failure |= NVM_FAILURE_INIT;
		return -1;
	}

	return 0;
}

int32_t nvm_deinit(void) {
	return 0;
}

int32_t nvm_read_sync(uint8_t* data, uint32_t length) {	
	/* Read data. */
	C40_Ip_StatusType status = C40_Ip_Read(_SECTOR_ADDRESS, length, data);

	/* Check job result. */
    if (status != STATUS_C40_IP_SUCCESS) {
		nvm_failure |= NVM_FAILURE_READ;
    	return -1;
    }

    return 0;
}

int32_t nvm_write(const uint8_t* data, uint32_t length) {
	if (_state != _STATE_IDLE) {
		++nvm_failure;
		return -1;
	}

	_state = _STATE_WAIT_FOR_ERASE_FINISHED;
	if (C40_Ip_MainInterfaceSectorErase(_SECTOR, 0) != STATUS_C40_IP_SUCCESS) {
		_state = _STATE_IDLE;
		++nvm_failure;
		return -1;
	}

	// Align length to 8 byte.
	// @todo There might be a "segmentation fault" since data might be too short.
	uint32_t remainder = length % 8;
	if (remainder != 0) length += (8 - remainder);

	_data = data;
	_length = length;

	return 0;
}

void nvm_step(void) {
	switch (_state) {
		case _STATE_IDLE:
			break;
		case _STATE_WAIT_FOR_ERASE_FINISHED: {
			C40_Ip_StatusType status = C40_Ip_MainInterfaceSectorEraseStatus();
			if (status == STATUS_C40_IP_SUCCESS) {
				_state = _STATE_WAIT_FOR_WRITE_FINISHED;
				status = C40_Ip_MainInterfaceWrite(_SECTOR_ADDRESS, _length, _data, _MASTER_ID); // @todo Write must be aligned to 8 byte aligned and <= 128 byte.
				if (status != STATUS_C40_IP_SUCCESS) {
					_state = _STATE_IDLE;
					++nvm_failure;
				}
			} else if (status != STATUS_C40_IP_BUSY) {
				_state = _STATE_IDLE;
				++nvm_failure;
			}
			break;
		}
		case _STATE_WAIT_FOR_WRITE_FINISHED: {
			C40_Ip_StatusType status = C40_Ip_MainInterfaceWriteStatus();
			if (status == STATUS_C40_IP_SUCCESS) {
				_state = _STATE_IDLE;
			} else if (status != STATUS_C40_IP_BUSY) {
				_state = _STATE_IDLE;
				++nvm_failure;
			}
			break;
		}
		default:
			_state = _STATE_IDLE;
			++nvm_failure;
	}
}
