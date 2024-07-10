/*
*   Copyright 2021 NXP
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be used strictly
*   in accordance with the applicable license terms.  By expressly accepting
*   such terms or by downloading, installing, activating and/or otherwise using
*   the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms.  If you do not agree to
*   be bound by the applicable license terms, then you may not retain,
*   install, activate or otherwise use the software.
*
*   This file contains sample code only. It is not part of the production code deliverables.
*/

/**
*   @file main.c
*
*   @addtogroup main_module main module documentation
*   @{
*/

#include <stdio.h>

/* User includes */
#include "Lpuart_Uart_Ip.h"
#include "Lpuart_Uart_Ip_Irq.h"
#include "Clock_Ip.h"
#include "IntCtrl_Ip.h"
#include "Siul2_Port_Ip.h"
#include "string.h"

#include "drivers/can.h"
#include "drivers/spi.h"
#include "drivers/dio.h"
#include "drivers/timer.h"
#include "drivers/nvm.h"

#include "middleware/middleware.h"

#include "middleware/mw_diagnostic.h"

#include "devices/fs26.h"

#include "middleware/ads7883.h"

#include "app/tasks.h"

/* Welcome messages displayed at the console */
#define WELCOME_MSG_1 "Hello, This message is sent via Uart!\r\n"
#define WELCOME_MSG_2 "Have a nice day!\r\n"

/* Error message displayed at the console, in case data is received erroneously */
#define ERROR_MSG "An error occurred! The application will stop!\r\n"

/* Length of the message to be received from the console */
#define MSG_LEN  50U

/* Define channel */
#define UART_LPUART_INTERNAL_CHANNEL  2
#define UART_FLEXIO_TX_CHANNEL  0
#define UART_FLEXIO_RX_CHANNEL  1

boolean User_Str_Cmp(const uint8 * pBuffer1, const uint8 * pBuffer2, const uint32 length)
{
    uint32 idx = 0;
    for (idx = 0; idx < length; idx++)
    {
        if(pBuffer1[idx] != pBuffer2[idx])
        {
            return FALSE;
        }
    }
    return TRUE;
}

//boolean Send_Data(Receiver_Module_Type receiver, const uint8* pBuffer, uint32 length)
//{
//    volatile Lpuart_Uart_Ip_StatusType lpuartStatus = LPUART_UART_IP_STATUS_ERROR;
//    volatile Flexio_Uart_Ip_StatusType flexioStatus = FLEXIO_UART_IP_STATUS_ERROR;
//    uint32 remainingBytes;
//    uint32 T_timeout = 0xFFFFFF;
//    uint8 Rx_Buffer[MSG_LEN];
//
//    memset(Rx_Buffer, 0 , MSG_LEN);
//
//    if (receiver == FLEXIO_RECEIVER)
//    {
//        /* Uart_AsyncReceive transmit data */
//        flexioStatus = Flexio_Uart_Ip_AsyncReceive(UART_FLEXIO_RX_CHANNEL, Rx_Buffer, length);
//        if (FLEXIO_UART_IP_STATUS_SUCCESS != flexioStatus)
//        {
//            return FALSE;
//        }
//        /* Uart_AsyncSend transmit data */
//        lpuartStatus = Lpuart_Uart_Ip_AsyncSend(UART_LPUART_INTERNAL_CHANNEL, pBuffer, length);
//        if (LPUART_UART_IP_STATUS_SUCCESS != lpuartStatus)
//        {
//            return FALSE;
//        }
//
//        /* Check for no on-going transmission */
//        do
//        {
//            lpuartStatus = Lpuart_Uart_Ip_GetTransmitStatus(UART_LPUART_INTERNAL_CHANNEL, &remainingBytes);
//        } while (LPUART_UART_IP_STATUS_BUSY == lpuartStatus && 0 < T_timeout--);
//
//        T_timeout = 0xFFFFFF;
//
//        do
//        {
//            flexioStatus = Flexio_Uart_Ip_GetStatus(UART_FLEXIO_RX_CHANNEL, &remainingBytes);
//        } while (FLEXIO_UART_IP_STATUS_BUSY == flexioStatus && 0 < T_timeout--);
//
//        if ((FLEXIO_UART_IP_STATUS_SUCCESS != flexioStatus) || (LPUART_UART_IP_STATUS_SUCCESS != lpuartStatus))
//        {
//            return FALSE;
//        }
//    }
//    else
//    {
//        /* Uart_AsyncReceive transmit data */
//        lpuartStatus = Lpuart_Uart_Ip_AsyncReceive(UART_LPUART_INTERNAL_CHANNEL, Rx_Buffer, length);
//        if (LPUART_UART_IP_STATUS_SUCCESS != lpuartStatus)
//        {
//            return FALSE;
//        }
//        /* Uart_AsyncSend transmit data */
//        flexioStatus = Flexio_Uart_Ip_AsyncSend(UART_FLEXIO_TX_CHANNEL, pBuffer, length);
//        if (FLEXIO_UART_IP_STATUS_SUCCESS != flexioStatus)
//        {
//            return FALSE;
//        }
//
//        /* Check for no on-going transmission */
//        do
//        {
//            flexioStatus = Flexio_Uart_Ip_GetStatus(UART_FLEXIO_TX_CHANNEL, &remainingBytes);
//        } while (FLEXIO_UART_IP_STATUS_BUSY == flexioStatus && 0 < T_timeout--);
//
//        do
//        {
//            lpuartStatus = Lpuart_Uart_Ip_GetReceiveStatus(UART_LPUART_INTERNAL_CHANNEL, &remainingBytes);
//        } while (LPUART_UART_IP_STATUS_BUSY == lpuartStatus && 0 < T_timeout--);
//
//        if ((FLEXIO_UART_IP_STATUS_SUCCESS != flexioStatus) || (LPUART_UART_IP_STATUS_SUCCESS != lpuartStatus))
//        {
//            return FALSE;
//        }
//    }
//
//    if(!User_Str_Cmp(pBuffer, (const uint8 *)Rx_Buffer, length))
//    {
//        return FALSE;
//    }
//
//    return TRUE;
//}

boolean echo_data(void)
{
    volatile Lpuart_Uart_Ip_StatusType lpuartStatus = LPUART_UART_IP_STATUS_ERROR;
    uint32 remainingBytes;
    uint32 T_timeout = 0xFFFFFF;
    uint8 Rx_Buffer[MSG_LEN];
    uint32 length = 1;

    static j = 1;

    memset(Rx_Buffer, 0 , MSG_LEN);

    sprintf(Rx_Buffer, "Hello %d!\r\n", j);
    ++j;

    /* Uart_AsyncReceive transmit data */
/*            lpuartStatus = Lpuart_Uart_Ip_AsyncReceive(UART_LPUART_INTERNAL_CHANNEL, Rx_Buffer, length);
            if (LPUART_UART_IP_STATUS_SUCCESS != lpuartStatus)
            {
                return FALSE;
            }

            do
            {
                lpuartStatus = Lpuart_Uart_Ip_GetReceiveStatus(UART_LPUART_INTERNAL_CHANNEL, &remainingBytes);
            } while (LPUART_UART_IP_STATUS_BUSY == lpuartStatus && 0 < T_timeout--);*/

            T_timeout = 0xFFFFFF;

        /* Uart_AsyncSend transmit data */
        //lpuartStatus = Lpuart_Uart_Ip_AsyncSend(UART_LPUART_INTERNAL_CHANNEL, Rx_Buffer, length);
    	//lpuartStatus = Lpuart_Uart_Ip_AsyncSend(UART_LPUART_INTERNAL_CHANNEL, (const uint8 *)WELCOME_MSG_1, strlen(WELCOME_MSG_1));
    	lpuartStatus = Lpuart_Uart_Ip_AsyncSend(UART_LPUART_INTERNAL_CHANNEL, (const uint8 *)Rx_Buffer, strlen(Rx_Buffer));
    	if (LPUART_UART_IP_STATUS_SUCCESS != lpuartStatus)
        {
            return FALSE;
        }

        volatile uint32 i = 100000;
        while (i > 0) {
        	i = i - 1;
        }

        /* Check for no on-going transmission */
        do
        {
            lpuartStatus = Lpuart_Uart_Ip_GetTransmitStatus(UART_LPUART_INTERNAL_CHANNEL, &remainingBytes);
        } while (LPUART_UART_IP_STATUS_BUSY == lpuartStatus && 0 < T_timeout--);

        if (LPUART_UART_IP_STATUS_SUCCESS != lpuartStatus)
        {
            return FALSE;
        }

    return TRUE;
}

static can_message_buffer_t _can0_rx;
static can_message_buffer_t _can0_tx;
static can_message_buffer_t _can1_rx;
static can_message_buffer_t _can1_tx;

int can_main_loop(void) {
	// Receive over UART ...
    /* Uart_AsyncReceive transmit data */
	volatile Lpuart_Uart_Ip_StatusType lpuartStatus = LPUART_UART_IP_STATUS_ERROR;
    uint8 input = 0;
	uint8 Rx_Buffer[MSG_LEN];
    uint32 length = 1;
	uint32 remainingBytes;
	uint32 T_timeout = 0xFFFFFF;
	/*if (LPUART_UART_IP_STATUS_SUCCESS != lpuartStatus) {
		return -1;
	}*/
    /*do {
    	lpuartStatus = Lpuart_Uart_Ip_GetReceiveStatus(UART_LPUART_INTERNAL_CHANNEL, &remainingBytes);
    } while (LPUART_UART_IP_STATUS_BUSY == lpuartStatus && 0 < T_timeout--);*/
	if (Lpuart_Uart_Ip_GetReceiveStatus(UART_LPUART_INTERNAL_CHANNEL, &remainingBytes) == LPUART_UART_IP_STATUS_BUSY) {
		//Rx_Buffer[0] = 0;
	} else {
		input = Rx_Buffer[0];
		lpuartStatus = Lpuart_Uart_Ip_AsyncReceive(UART_LPUART_INTERNAL_CHANNEL, Rx_Buffer, length);
	}

    // Can transmit
    if (input == '0') {
    	Lpuart_Uart_Ip_AsyncSend(UART_LPUART_INTERNAL_CHANNEL, "CAN0 TX\r\n", strlen("CAN0 TX\r\n"));
    	while (Lpuart_Uart_Ip_GetTransmitStatus(UART_LPUART_INTERNAL_CHANNEL, &remainingBytes) == LPUART_UART_IP_STATUS_BUSY) {};
    	_can0_tx.id = 0x200;
    	_can0_tx.length = 8;
    	_can0_tx.data[0] = 'H';
    	_can0_tx.data[1] = 'e';
    	_can0_tx.data[2] = 'l';
    	_can0_tx.data[3] = 'l';
    	_can0_tx.data[4] = 'o';
    	_can0_tx.data[5] = ' ';
    	_can0_tx.data[6] = '1';
    	_can0_tx.data[7] = 0;
    	can_transmit(&can_0, 1, &_can0_tx);
    } else if (input == '1') {
    	Lpuart_Uart_Ip_AsyncSend(UART_LPUART_INTERNAL_CHANNEL, "CAN1 TX\r\n", strlen("CAN1 TX\r\n"));
		while (Lpuart_Uart_Ip_GetTransmitStatus(UART_LPUART_INTERNAL_CHANNEL, &remainingBytes) == LPUART_UART_IP_STATUS_BUSY) {};
    	_can1_tx.id = 0x100;
		_can1_tx.length = 8;
		_can1_tx.data[0] = 'H';
		_can1_tx.data[1] = 'e';
		_can1_tx.data[2] = 'l';
		_can1_tx.data[3] = 'l';
		_can1_tx.data[4] = 'o';
		_can1_tx.data[5] = ' ';
		_can1_tx.data[6] = '0';
		_can1_tx.data[7] = 0;
		can_transmit(&can_1, 1, &_can1_tx);
    }

    // Can receieve
    if (can_receive(&can_0, 0, &_can0_rx) && _can0_rx.length > 0) {
    	Lpuart_Uart_Ip_AsyncSend(UART_LPUART_INTERNAL_CHANNEL, "CAN0 RX: ", strlen("CAN0 RX: "));
    	while (Lpuart_Uart_Ip_GetTransmitStatus(UART_LPUART_INTERNAL_CHANNEL, &remainingBytes) == LPUART_UART_IP_STATUS_BUSY) {};

    	Lpuart_Uart_Ip_AsyncSend(UART_LPUART_INTERNAL_CHANNEL, _can0_rx.data, strlen(_can0_rx.data));
    	while (Lpuart_Uart_Ip_GetTransmitStatus(UART_LPUART_INTERNAL_CHANNEL, &remainingBytes) == LPUART_UART_IP_STATUS_BUSY) {};

    	Lpuart_Uart_Ip_AsyncSend(UART_LPUART_INTERNAL_CHANNEL, "\r\n", strlen("\r\n"));
    	while (Lpuart_Uart_Ip_GetTransmitStatus(UART_LPUART_INTERNAL_CHANNEL, &remainingBytes) == LPUART_UART_IP_STATUS_BUSY) {};
    }
    if (can_receive(&can_1, 0, &_can1_rx) && _can1_rx.length > 0) {
    	Lpuart_Uart_Ip_AsyncSend(UART_LPUART_INTERNAL_CHANNEL, "CAN1 RX: ", strlen("CAN0 RX: "));
    	while (Lpuart_Uart_Ip_GetTransmitStatus(UART_LPUART_INTERNAL_CHANNEL, &remainingBytes) == LPUART_UART_IP_STATUS_BUSY) {};

    	Lpuart_Uart_Ip_AsyncSend(UART_LPUART_INTERNAL_CHANNEL, _can1_rx.data, strlen(_can1_rx.data));
    	while (Lpuart_Uart_Ip_GetTransmitStatus(UART_LPUART_INTERNAL_CHANNEL, &remainingBytes) == LPUART_UART_IP_STATUS_BUSY) {};

    	Lpuart_Uart_Ip_AsyncSend(UART_LPUART_INTERNAL_CHANNEL, "\r\n", strlen("\r\n"));
    	while (Lpuart_Uart_Ip_GetTransmitStatus(UART_LPUART_INTERNAL_CHANNEL, &remainingBytes) == LPUART_UART_IP_STATUS_BUSY) {};
    }
}

int fs26SpiTransferFunction(uint8_t *TxBuffer, uint8_t *RxBuffer, uint16_t Length)
{
	Lpspi_Ip_StatusType spiStat;

	spiStat = Lpspi_Ip_SyncTransmit(&spi_3_cs_0,
			TxBuffer, RxBuffer, Length, 1000);

	return (int)spiStat;
}

#define _ERROR() { for(;;) {ASM_KEYWORD(BREAKPOINT_INSTR);} }

static void _busy_delay(int us) {
	for (int i = 0; i < (us * 80); ++i) { // 1 iteration takes two cycles (with O2 optimization), so the clock frequency (160 MHz) is divided by 2.
		__asm("nop");
	}
}

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void) {
    /* Init clock  */
    Clock_Ip_Init(&Clock_Ip_aClockConfig[0]);

#if defined (FEATURE_CLOCK_IP_HAS_SPLL_CLK)
    while (CLOCK_IP_PLL_LOCKED != Clock_Ip_GetPllStatus()) {
        /* Busy wait until the System PLL is locked */
    }

    Clock_Ip_DistributePll();
#endif

    /* Initialize IRQs */
    IntCtrl_Ip_Init(&IntCtrlConfig_0);

    //dio_init();

    /* Initializes an UART driver*/
    //Lpuart_Uart_Ip_Init(UART_LPUART_INTERNAL_CHANNEL, &Lpuart_Uart_Ip_xHwConfigPB_2);

	if (middleware_init() < 0) return -1;

    spi_init(&spi_3);

	/* Initialize the FS26 to stop it from resetting */
	fs26_initialize(&fs26SpiTransferFunction);

    //i2c_init();

    /*spi_init();
    int32 spi_result = spi_transceive();
    if (spi_result == 0) {
    	Lpuart_Uart_Ip_AsyncSend(UART_LPUART_INTERNAL_CHANNEL, "SPI failed\r\n", strlen("SPI failed\r\n"));
    } else {
    	Lpuart_Uart_Ip_AsyncSend(UART_LPUART_INTERNAL_CHANNEL, "SPI succeeded\r\n", strlen("SPI succeeded\r\n"));
    }
	while (Lpuart_Uart_Ip_GetTransmitStatus(UART_LPUART_INTERNAL_CHANNEL, &remainingBytes) == LPUART_UART_IP_STATUS_BUSY) {};*/

	/*int32 i2c_result = i2c_transceive();
    if (i2c_result != 0) {
    	MW_DIAGNOSTIC_LOG("I2C failed.");
    } else {
    	MW_DIAGNOSTIC_LOG("I2C succeeded.");
    }*/

    // Run middleware
    //if (middleware_run() < 0) return -1;

	uint64 start = timer_get();


	// NVM Test
	/*if (nvm_init() != 0) _ERROR();
	char nvm_read_buffer[96];
	if (nvm_read(nvm_read_buffer, 96) != 0) _ERROR();
	MW_DIAGNOSTIC_LOG("NVM read:");
	MW_DIAGNOSTIC_LOG(nvm_read_buffer);

	char* nvm_write_buffer = "This is a NVM test with a max of 100 chars ...";
	if (nvm_write(nvm_write_buffer, 96) != 0) _ERROR();
	while (1) {
		int32 nvm_result = nvm_write_completed();
		if (nvm_result == 0) continue;
		if (nvm_result == 1) break;
		_ERROR();
	}

	MW_DIAGNOSTIC_LOG("NVM write completed.");*/

	// Busy wait test
	{
		uint64 start_timer = timer_get();
		_busy_delay(10000);
		uint64 end_timer = timer_get();
		MW_DIAGNOSTIC_LOG("Busy wait duration = %ld us.", end_timer - start_timer);
	}

	tasks_init();
	tasks_start();

	uint64 end = timer_get();

	MW_DIAGNOSTIC_LOG("Duration = %ld us.", end - start);

	spi_init(&spi_1);

	ads7883_instance_t voltage_sensor;
	voltage_sensor.spi_instance = &spi_1;
	voltage_sensor.spi_device = &spi_1_cs_0;
	ads7883_init(&voltage_sensor);

	uint64 last_conversion_timer = 0;
	for (int i = 0; 1; ++i) {
		uint64 currentTimer = timer_get();
		if ((currentTimer - last_conversion_timer) > 1000000) {
			ads7883_start_conversion(&voltage_sensor);
			//MW_DIAGNOSTIC_LOG("Start conversion.");
			last_conversion_timer = timer_get();
		}

		if (voltage_sensor.conversion_running && ads7883_step(&voltage_sensor) == 0) {
			MW_DIAGNOSTIC_LOG("Value = %f. Timer = %ld us.", (double) voltage_sensor.value, timer_get() - last_conversion_timer);
		}
	}

	/*start = timer_get();

	double ia =   4.2;
	double ib =   6.6;
	double ic =   0.3;
	double id = 198.6;
	for (int i = 0; i < 1000000; ++i) {
		ia = ib + ic;
		ib = ic - id;
		ic = ia * id;
		id = ia / ib;
	}

	end = timer_get();

	sprintf(buffer, "Duration int = %d us. ia = %f. ib = %f. ic = %f. id = %f.\r\n", end - start, ia, ib, ic, id);
	Lpuart_Uart_Ip_AsyncSend(UART_LPUART_INTERNAL_CHANNEL, buffer, strlen(buffer));
	while (Lpuart_Uart_Ip_GetTransmitStatus(UART_LPUART_INTERNAL_CHANNEL, &remainingBytes) == LPUART_UART_IP_STATUS_BUSY) {};*/

    return 0;
}

/** @} */
