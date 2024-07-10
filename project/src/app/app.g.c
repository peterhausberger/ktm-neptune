/*
 *
 */

/* Scheduler block scheduler0. */
#include "../middleware/scheduler.h"
#include "../drivers/timer.h"
static scheduler_t scheduler0 = {
	.interval = 250
};

#include "../drivers/dio.h"
static uint8_t _dio_in_11_value;
static uint8_t _dio_in_129_value;
static uint8_t _dio_in_154_value;
static uint8_t _dio_in_12_value;
static uint8_t _dio_in_3_value;
static uint8_t _dio_in_2_value;
static uint8_t _dio_in_0_value;
static uint8_t _dio_in_1_value;
static uint8_t _dio_in_50_value;
static uint8_t _dio_in_51_value;
static uint8_t _dio_in_52_value;
static uint8_t _dio_in_53_value;
static uint8_t _dio_out_135_value;

#include "../drivers/stspi.h"
static stspi_t _stspi0 = {
	.cs_a = &dio_out_44,
	.cs_a = &dio_out_44,
	.cs_a = &dio_out_44,
	.sclk_a = &dio_out_135,
	.sclk_b = &dio_out_135,
	.sclk_c = &dio_out_135,
	.miso_a = &dio_in_11,
	.miso_b = &dio_in_11,
	.miso_c = &dio_in_11
};

/* ADC block adc0. */
#include "../drivers/adc.h"

/* Complementary PWM block cpwma. */
#include "math.h" /* For NAN. */
#include "../middleware/complementary_pwm.h"
complementary_pwm_instance_t _cpwma = {
	&pwm_instance_6,
	&pwm_instance_5,
	NAN
};

/* Complementary PWM block cpwmb. */
#include "math.h" /* For NAN. */
#include "../middleware/complementary_pwm.h"
complementary_pwm_instance_t _cpwmb = {
	&pwm_instance_3,
	&pwm_instance_4,
	NAN
};

/* Complementary PWM block cpwmc. */
#include "math.h" /* For NAN. */
#include "../middleware/complementary_pwm.h"
complementary_pwm_instance_t _cpwmc = {
	&pwm_instance_2,
	&pwm_instance_1,
	NAN
};

/* ADS7883 block ads1. */
#include "../middleware/ads7883.h"
static ads7883_instance_t _ads7883_ads1 = {
	.spi_instance = &spi_1,
	.spi_device = &spi_1_cs_0
};

/* Block ads2. */
#include "./ads2/ads2.h"

/* ADS7883 block ads4. */
#include "../middleware/ads7883.h"
static ads7883_instance_t _ads7883_ads4 = {
	.spi_instance = &spi_4,
	.spi_device = &spi_4_cs_0
};

/* AD799x block "adi1". */
#include "../middleware/ad799x.h"
static ad799x_instance_t _adi1 = {
	.i2c_instance = &i2c_instance_1
};

/* CAN block "can3". */
#include "../drivers/can.h"
#include <string.h> /* For memcpy. */
#define DBCC_TIME_STAMP
typedef uint32_t dbcc_time_stamp_t; /* Customize the timestamp type. */
#include "./can3/MDU_V002x_TB.h"
can_obj_mdu_v002x_tb_h_t can3_database;
static can_message_buffer_t _can3_0x152_buffer;
static can_message_buffer_t _can3_0x109_buffer;
static can_message_buffer_t _can3_0x11f_buffer;
static can_message_buffer_t _can3_0x7d0_buffer;
static int16_t can3_0x7d0_TB_Request_Speed;
static double can3_0x109_VCU_Eng_Req_Torque;
static uint8_t can3_0x109_VCU_Eng_Req_Torque_Valid;
static uint8_t can3_0x109_VCU_MDU_Interlock;
static uint32_t can3_0x734_tx_timer_100us = 0;
static uint32_t can3_0x735_tx_timer_100us = 0;
static uint32_t can3_0x736_tx_timer_100us = 0;
static uint32_t can3_0x737_tx_timer_100us = 0;
static uint32_t can3_0x738_tx_timer_100us = 0;
static uint32_t can3_0x11a_tx_timer_100us = 0;
static uint32_t can3_0x11b_tx_timer_100us = 0;
static uint32_t can3_0x260_tx_timer_100us = 0;
static can_message_buffer_t _can3_0x734_transmit_buffer;
static can_message_buffer_t _can3_0x735_transmit_buffer;
static can_message_buffer_t _can3_0x736_transmit_buffer;
static can_message_buffer_t _can3_0x737_transmit_buffer;
static can_message_buffer_t _can3_0x738_transmit_buffer;
static can_message_buffer_t _can3_0x11a_transmit_buffer;
static can_message_buffer_t _can3_0x11b_transmit_buffer;
static can_message_buffer_t _can3_0x260_transmit_buffer;
static int16_t can3_0x11a_MDU_Engine_Rpm;

/* Block asw. */
#include "./asw/asw.h"

/* Diagnostic block diagnostic0. */
#include "../middleware/uds.h"
#include "./diagnostic0_database.g.h"
static uds_instance_t _diagnostic0_uds_instance = {
	.database = {
		diagnostic0_database_read_data_by_identifier, 
		diagnostic0_database_write_data_by_identifier,
		DIAGNOSTIC0_DATABASE_STORAGE_SIZE,
		diagnostic0_database_storage,
		diagnostic0_database_load,
		diagnostic0_database_store
	},
	.can_instance = &can_3,
	.can_request_id = 0x7e4,
	.can_response_id = 0x7ec,
	.store_interval = 50000
};

#include "tasks.h"

void app_init(void) {
	/* Scheduler block scheduler0. */
	scheduler_init(&scheduler0);

    dio_init();

	/* ADC block adc0. */
	adc_init(&adc_0);
	adc_start_conversion(&adc_0); // Trigger first conversion.

	/* ADC block adc1. */
	adc_init(&adc_1);
	adc_start_conversion(&adc_1); // Trigger first conversion.

	/* ADC block adc2. */
	adc_init(&adc_2);
	//adc_start_conversion(&adc_2); // Trigger first conversion.

	/* Complementary PWM block cpwma. */
	complementary_pwm_init(&_cpwma);

	/* Complementary PWM block cpwmb. */
	complementary_pwm_init(&_cpwmb);

	/* Complementary PWM block cpwmc. */
	complementary_pwm_init(&_cpwmc);

	/* ADS7883 block ads1. */
	ads7883_init(&_ads7883_ads1);

    /* Block ads2. */
    ads2_init();

	/* ADS7883 block ads4. */
	ads7883_init(&_ads7883_ads4);

	/* AD799x block "adi1". */
	ad799x_init(&_adi1);

    /* CAN block "can3". */
    can_init(&can_3);
    can_init_receive_mailbox(&can_3, 0, 0x152);
	can3_database.can_0x152_BMS_Pack_CV_Info_time_stamp_rx = UINT32_MAX - 5000;
    can_init_receive_mailbox(&can_3, 1, 0x109);
	can3_database.can_0x109_VCU_Engine_Torque_EPP_time_stamp_rx = UINT32_MAX - 500;
    can_init_receive_mailbox(&can_3, 2, 0x11f);
	can3_database.can_0x11f_VCU_EPP_Data_time_stamp_rx = UINT32_MAX - 1000;
    can_init_receive_mailbox(&can_3, 3, 0x7d0);
	can3_database.can_0x7d0_TB_Request_time_stamp_rx = UINT32_MAX - 5000;
    _can3_0x734_transmit_buffer.id = 0x734;
	_can3_0x734_transmit_buffer.length = 8;
	can3_database.can_0x734_MDU_Debug_1_tx = 1; /* By default we transmit messages. */
    _can3_0x735_transmit_buffer.id = 0x735;
	_can3_0x735_transmit_buffer.length = 8;
	can3_database.can_0x735_MDU_Debug_2_tx = 1; /* By default we transmit messages. */
    _can3_0x736_transmit_buffer.id = 0x736;
	_can3_0x736_transmit_buffer.length = 8;
	can3_database.can_0x736_MDU_Debug_3_tx = 1; /* By default we transmit messages. */
    _can3_0x737_transmit_buffer.id = 0x737;
	_can3_0x737_transmit_buffer.length = 8;
	can3_database.can_0x737_MDU_Debug_4_tx = 1; /* By default we transmit messages. */
    _can3_0x738_transmit_buffer.id = 0x738;
	_can3_0x738_transmit_buffer.length = 8;
	can3_database.can_0x738_MDU_Debug_5_tx = 1; /* By default we transmit messages. */
    _can3_0x11a_transmit_buffer.id = 0x11a;
	_can3_0x11a_transmit_buffer.length = 8;
	can3_database.can_0x11a_MDU_Speed_Torque_Info_tx = 1; /* By default we transmit messages. */
    _can3_0x11b_transmit_buffer.id = 0x11b;
	_can3_0x11b_transmit_buffer.length = 8;
	can3_database.can_0x11b_MDU_Status_Info_1_tx = 1; /* By default we transmit messages. */
    _can3_0x260_transmit_buffer.id = 0x260;
	_can3_0x260_transmit_buffer.length = 8;
	can3_database.can_0x260_MDU_Status_Info_2_tx = 1; /* By default we transmit messages. */

	stspi_init(&_stspi0);

    /* Block asw. */
    asw_init();

    /* Diagnostic block diagnostic0. */
	diagnostic0_database_init();
	uds_init(&_diagnostic0_uds_instance);	
}

void app_deinit(void) {
	/* Diagnostic block diagnostic0. */
	uds_deinit(&_diagnostic0_uds_instance);	

    /* Block asw. */
    asw_deinit();

	/* CAN block "can3". */
    can_deinit(&can_3);

	/* AD799x block "adi1". */
	ad799x_deinit(&_adi1);

	/* ADS7883 block ads4. */
	ads7883_deinit(&_ads7883_ads4);

    /* Block ads2. */
    ads2_deinit();

	/* ADS7883 block ads1. */
	ads7883_deinit(&_ads7883_ads1);

	/* Complementary PWM block cpwmc. */
	complementary_pwm_deinit(&_cpwmc);

	/* Complementary PWM block cpwmb. */
	complementary_pwm_deinit(&_cpwmb);

	/* Complementary PWM block cpwma. */
	complementary_pwm_deinit(&_cpwma);

	/* ADC block adc2. */
	adc_deinit(&adc_2);

	/* ADC block adc1. */
	adc_deinit(&adc_1);

	/* ADC block adc0. */
	adc_deinit(&adc_0);

    dio_deinit();
}

#include "OsIf_Internal.h"

void app_step(void) {
    /* scheduler0. */
	scheduler_step(&scheduler0);

	//dio_write(&dio_out_44, 1);

	if (scheduler0.cycle == 0) {
		uint64_t tmp;
		uint32_t cnt;
		while (1) {
			OsIf_SuspendAllInterrupts();
			tmp = timer_get();
			cnt = IP_EMIOS_0->CH.UC[23].CNT;
			OsIf_ResumeAllInterrupts();
			if (cnt > 4650 && cnt < 4750) break;
		}
		scheduler0._next_wakeup_timer_us = tmp + scheduler0.interval;
	}

	//diagnostic0_database.ASW_PWMCounter = IP_EMIOS_0->CH.UC[23].CNT;
	diagnostic0_database.ASW_PWMCounter = tasks_pwm_counter;

    /* adc0. */
	/* ADC block adc0. */
	//if (adc_0.conversion_finished) {
	//    adc_start_conversion(&adc_0); // Trigger next conversion.
    //}

    /* adc1. */
	/* ADC block adc1. */
	//if (adc_1.conversion_finished) {
	//    adc_start_conversion(&adc_1); // Trigger next conversion.
    //}

	//stspi_read(&_stspi0);

    /* adc2. */
	/* ADC block adc2. */
	//dio_write(&dio_out_44, 1);
	adc_start_conversion(&adc_2); // Trigger next conversion.
	//while (adc_2.conversion_finished != 1);
	//dio_write(&dio_out_44, 0);

    /* ads1. */
	//dio_write(&dio_out_44, 1);
	ads7883_start_conversion(&_ads7883_ads1);
	//while (ads7883_step(&_ads7883_ads1) == -1);
	//dio_write(&dio_out_44, 0);

    /* ads2. */
    //ads2_step();

    /* ads4. */
	//ads7883_step(&_ads7883_ads4);
	ads7883_start_conversion(&_ads7883_ads4);

	while (adc_2.conversion_finished != 1);
	while (ads7883_step(&_ads7883_ads1) == -1);
	while (ads7883_step(&_ads7883_ads4) == -1);
	//dio_write(&dio_out_44, 0);

    asw.in.interval_us = scheduler0.interval;
    //asw.in.sine = adc_2_channel_3;
    //asw.in.cosine = adc_2_channel_4;
    asw.in.sine = adc_2_channel_4;
    asw.in.cosine = adc_2_channel_3;
    asw.in.ib_raw = _ads7883_ads1.value;
    asw.in.ic_raw = ads2.cs1.value;
    asw.in.ia_raw = _ads7883_ads4.value;
    asw_inner_step();

    /* cpwma. */
	_cpwma.value = asw.out.duty_cycle_a;
    //dio_write(&dio_out_44, 1);
    complementary_pwm_step(&_cpwma);
    //dio_write(&dio_out_44, 0);

    /* cpwmb. */
    _cpwmb.value = asw.out.duty_cycle_b;
	complementary_pwm_step(&_cpwmb);

    /* cpwmc. */
    _cpwmc.value = asw.out.duty_cycle_c;
	complementary_pwm_step(&_cpwmc);



    /* dio. */
	_dio_in_11_value = dio_read(&dio_in_11);
	_dio_in_129_value = dio_read(&dio_in_129);
	_dio_in_154_value = dio_read(&dio_in_154);
	_dio_in_12_value = dio_read(&dio_in_12);
	_dio_in_3_value = dio_read(&dio_in_3);
	_dio_in_2_value = dio_read(&dio_in_2);
	_dio_in_0_value = dio_read(&dio_in_0);
	_dio_in_1_value = dio_read(&dio_in_1);
	_dio_in_50_value = dio_read(&dio_in_50);
	_dio_in_51_value = dio_read(&dio_in_51);
	_dio_in_52_value = dio_read(&dio_in_52);
	_dio_in_53_value = dio_read(&dio_in_53);

    /* adi1. */
	//dio_write(&dio_out_44, 1);
	ad799x_step(&_adi1);
	//dio_write(&dio_out_44, 0);

    /* can3. */
	can3_database.can_0x152_BMS_Pack_CV_Info_rx = 1; /* Message "BMS_Pack_CV_Info" (0x152). */
	if (can_receive(&can_3, 0, &_can3_0x152_buffer) && (_can3_0x152_buffer.id == 0x152)) {
		can3_database.can_0x152_BMS_Pack_CV_Info_time_stamp_rx = scheduler_get()->timer_100us;
		uint64_t tmp;
		memcpy(&tmp, _can3_0x152_buffer.data, 8); /* Due to aliasing, a simple pointer conversion does not work in general. */
		unpack_message(&can3_database, _can3_0x152_buffer.id, tmp, _can3_0x152_buffer.length, 0);
	}
	if ((scheduler_get()->timer_100us - can3_database.can_0x152_BMS_Pack_CV_Info_time_stamp_rx) > 5000) can3_database.can_0x152_BMS_Pack_CV_Info_rx = 0;
	//dio_write(&dio_out_44, 1);
	can3_database.can_0x109_VCU_Engine_Torque_EPP_rx = 1; /* Message "VCU_Engine_Torque_EPP" (0x109). */
	if (can_receive(&can_3, 1, &_can3_0x109_buffer) && (_can3_0x109_buffer.id == 0x109)) {
		can3_database.can_0x109_VCU_Engine_Torque_EPP_time_stamp_rx = scheduler_get()->timer_100us;
		uint64_t tmp;
		memcpy(&tmp, _can3_0x109_buffer.data, 8); /* Due to aliasing, a simple pointer conversion does not work in general. */
		unpack_message(&can3_database, _can3_0x109_buffer.id, tmp, _can3_0x109_buffer.length, 0);
	    decode_can_0x109_VCU_Eng_Req_Torque(&can3_database, &can3_0x109_VCU_Eng_Req_Torque);
	    decode_can_0x109_VCU_Eng_Req_Torque_Valid(&can3_database, &can3_0x109_VCU_Eng_Req_Torque_Valid);
	    decode_can_0x109_VCU_MDU_Interlock(&can3_database, &can3_0x109_VCU_MDU_Interlock);
	}
	//dio_write(&dio_out_44, 0);
	if ((scheduler_get()->timer_100us - can3_database.can_0x109_VCU_Engine_Torque_EPP_time_stamp_rx) > 500) can3_database.can_0x109_VCU_Engine_Torque_EPP_rx = 0;
	can3_database.can_0x11f_VCU_EPP_Data_rx = 1; /* Message "VCU_EPP_Data" (0x11f). */
	if (can_receive(&can_3, 2, &_can3_0x11f_buffer) && (_can3_0x11f_buffer.id == 0x11f)) {
		can3_database.can_0x11f_VCU_EPP_Data_time_stamp_rx = scheduler_get()->timer_100us;
		uint64_t tmp;
		memcpy(&tmp, _can3_0x11f_buffer.data, 8); /* Due to aliasing, a simple pointer conversion does not work in general. */
		unpack_message(&can3_database, _can3_0x11f_buffer.id, tmp, _can3_0x11f_buffer.length, 0);
	}
	if ((scheduler_get()->timer_100us - can3_database.can_0x11f_VCU_EPP_Data_time_stamp_rx) > 1000) can3_database.can_0x11f_VCU_EPP_Data_rx = 0;
	can3_database.can_0x7d0_TB_Request_rx = 1; /* Message "TB_Request" (0x7d0). */
	if (can_receive(&can_3, 3, &_can3_0x7d0_buffer) && (_can3_0x7d0_buffer.id == 0x7d0)) {
		can3_database.can_0x7d0_TB_Request_time_stamp_rx = scheduler_get()->timer_100us;
		uint64_t tmp;
		memcpy(&tmp, _can3_0x7d0_buffer.data, 8); /* Due to aliasing, a simple pointer conversion does not work in general. */
		unpack_message(&can3_database, _can3_0x7d0_buffer.id, tmp, _can3_0x7d0_buffer.length, 0);
	    decode_can_0x7d0_TB_Request_Speed(&can3_database, &can3_0x7d0_TB_Request_Speed);
	}
	if ((scheduler_get()->timer_100us - can3_database.can_0x7d0_TB_Request_time_stamp_rx) > 5000) can3_database.can_0x7d0_TB_Request_rx = 0;

    /* asw. */
    //asw.in.interval_us = scheduler0.interval;
    //asw.in.sine = adc_2_channel_3;
    //asw.in.cosine = adc_2_channel_4;
    //asw.in.sine = adc_2_channel_4;
    //asw.in.cosine = adc_2_channel_3;
    //asw.in.ib_raw = _ads7883_ads1.value;
    //asw.in.ic_raw = ads2.cs1.value;
    //asw.in.ia_raw = _ads7883_ads4.value;
    asw.in.rpm_request = can3_0x7d0_TB_Request_Speed;
    asw.in.torque_request = can3_0x109_VCU_Eng_Req_Torque;
    asw.in.torque_request_valid = can3_0x109_VCU_Eng_Req_Torque_Valid;
    asw.in.interlock_request = can3_0x109_VCU_MDU_Interlock;
    asw.in.commutation_type = diagnostic0_database.ASW_CommutationType;
    asw_step();

    /* dio. */
    _dio_out_135_value = asw.out.gate_driver_enable;
	dio_write(&dio_out_135, _dio_out_135_value);

    /* cpwma. */
	//dio_write(&dio_out_44, 1);
    //_cpwma.value = asw.out.duty_cycle_a;
    //complementary_pwm_step(&_cpwma);
    //dio_write(&dio_out_44, 0);

    /* cpwmb. */
    //_cpwmb.value = asw.out.duty_cycle_b;
	//complementary_pwm_step(&_cpwmb);

    /* cpwmc. */
    //_cpwmc.value = asw.out.duty_cycle_c;
	//complementary_pwm_step(&_cpwmc);

    /* can3. */
    can3_0x11a_MDU_Engine_Rpm = asw.out.measured_rpm;
	if ((can3_database.can_0x734_MDU_Debug_1_tx != 0) && /* Message "MDU_Debug_1" (0x734). */
		((scheduler_get()->timer_100us - can3_0x734_tx_timer_100us) >= 100)) {
		//dio_write(&dio_out_44, 1);
		uint64_t tmp;
		pack_message(&can3_database, 0x734, &tmp);
		memcpy(_can3_0x734_transmit_buffer.data, &tmp, 8); /* Due to aliasing, a simple pointer conversion does not work in general. */
		if (can_transmit(&can_3, 4, &_can3_0x734_transmit_buffer) == 1) {
			can3_0x734_tx_timer_100us = scheduler_get()->timer_100us;
		}
		//dio_write(&dio_out_44, 0);
	}
	if ((can3_database.can_0x735_MDU_Debug_2_tx != 0) && /* Message "MDU_Debug_2" (0x735). */
		((scheduler_get()->timer_100us - can3_0x735_tx_timer_100us) >= 100)) {
		uint64_t tmp;
		pack_message(&can3_database, 0x735, &tmp);
		memcpy(_can3_0x735_transmit_buffer.data, &tmp, 8); /* Due to aliasing, a simple pointer conversion does not work in general. */
		if (can_transmit(&can_3, 5, &_can3_0x735_transmit_buffer) == 1) {
			can3_0x735_tx_timer_100us = scheduler_get()->timer_100us;
		}
	}
	if ((can3_database.can_0x736_MDU_Debug_3_tx != 0) && /* Message "MDU_Debug_3" (0x736). */
		((scheduler_get()->timer_100us - can3_0x736_tx_timer_100us) >= 100)) {
		uint64_t tmp;
		pack_message(&can3_database, 0x736, &tmp);
		memcpy(_can3_0x736_transmit_buffer.data, &tmp, 8); /* Due to aliasing, a simple pointer conversion does not work in general. */
		if (can_transmit(&can_3, 6, &_can3_0x736_transmit_buffer) == 1) {
			can3_0x736_tx_timer_100us = scheduler_get()->timer_100us;
		}
	}
	if ((can3_database.can_0x737_MDU_Debug_4_tx != 0) && /* Message "MDU_Debug_4" (0x737). */
		((scheduler_get()->timer_100us - can3_0x737_tx_timer_100us) >= 100)) {
		uint64_t tmp;
		pack_message(&can3_database, 0x737, &tmp);
		memcpy(_can3_0x737_transmit_buffer.data, &tmp, 8); /* Due to aliasing, a simple pointer conversion does not work in general. */
		if (can_transmit(&can_3, 7, &_can3_0x737_transmit_buffer) == 1) {
			can3_0x737_tx_timer_100us = scheduler_get()->timer_100us;
		}
	}
	if ((can3_database.can_0x738_MDU_Debug_5_tx != 0) && /* Message "MDU_Debug_5" (0x738). */
		((scheduler_get()->timer_100us - can3_0x738_tx_timer_100us) >= 100)) {
		uint64_t tmp;
		pack_message(&can3_database, 0x738, &tmp);
		memcpy(_can3_0x738_transmit_buffer.data, &tmp, 8); /* Due to aliasing, a simple pointer conversion does not work in general. */
		if (can_transmit(&can_3, 8, &_can3_0x738_transmit_buffer) == 1) {
			can3_0x738_tx_timer_100us = scheduler_get()->timer_100us;
		}
	}
	if ((can3_database.can_0x11a_MDU_Speed_Torque_Info_tx != 0) && /* Message "MDU_Speed_Torque_Info" (0x11a). */
		((scheduler_get()->timer_100us - can3_0x11a_tx_timer_100us) >= 100)) {
		//encode_can_0x11a_MDU_Engine_Rpm(&can3_database, can3_0x11a_MDU_Engine_Rpm);
		uint64_t tmp;
		pack_message(&can3_database, 0x11a, &tmp);
		memcpy(_can3_0x11a_transmit_buffer.data, &tmp, 8); /* Due to aliasing, a simple pointer conversion does not work in general. */
		if (can_transmit(&can_3, 9, &_can3_0x11a_transmit_buffer) == 1) {
			can3_0x11a_tx_timer_100us = scheduler_get()->timer_100us;
		}
	}
	if ((can3_database.can_0x11b_MDU_Status_Info_1_tx != 0) && /* Message "MDU_Status_Info_1" (0x11b). */
		((scheduler_get()->timer_100us - can3_0x11b_tx_timer_100us) >= 200)) {
		uint64_t tmp;
		pack_message(&can3_database, 0x11b, &tmp);
		memcpy(_can3_0x11b_transmit_buffer.data, &tmp, 8); /* Due to aliasing, a simple pointer conversion does not work in general. */
		if (can_transmit(&can_3, 10, &_can3_0x11b_transmit_buffer) == 1) {
			can3_0x11b_tx_timer_100us = scheduler_get()->timer_100us;
		}
	}
	if ((can3_database.can_0x260_MDU_Status_Info_2_tx != 0) && /* Message "MDU_Status_Info_2" (0x260). */
		((scheduler_get()->timer_100us - can3_0x260_tx_timer_100us) >= 1000)) {
		uint64_t tmp;
		pack_message(&can3_database, 0x260, &tmp);
		memcpy(_can3_0x260_transmit_buffer.data, &tmp, 8); /* Due to aliasing, a simple pointer conversion does not work in general. */
		if (can_transmit(&can_3, 11, &_can3_0x260_transmit_buffer) == 1) {
			can3_0x260_tx_timer_100us = scheduler_get()->timer_100us;
		}
	}

    /* diagnostic0. */
    diagnostic0_database.Failure_Scheduler += scheduler0.warning;
    diagnostic0_database.GateDriver_PhaseC_LowSide_Fault = _dio_in_11_value;
    diagnostic0_database.GateDriver_PhaseC_LowSide_Ready = _dio_in_129_value;
    diagnostic0_database.GateDriver_PhaseC_HighSide_Fault = _dio_in_154_value;
    diagnostic0_database.GateDriver_PhaseC_HighSide_Ready = _dio_in_12_value;
    diagnostic0_database.GateDriver_PhaseB_HighSide_Fault = _dio_in_3_value;
    diagnostic0_database.GateDriver_PhaseB_HighSide_Ready = _dio_in_2_value;
    diagnostic0_database.GateDriver_PhaseB_LowSide_Fault = _dio_in_0_value;
    diagnostic0_database.GateDriver_PhaseB_LowSide_Ready = _dio_in_1_value;
    diagnostic0_database.GateDriver_PhaseA_LowSide_Fault = _dio_in_50_value;
    diagnostic0_database.GateDriver_PhaseA_LowSide_Ready = _dio_in_51_value;
    diagnostic0_database.GateDriver_PhaseA_HighSide_Fault = _dio_in_52_value;
    diagnostic0_database.GateDriver_PhaseA_HighSide_Ready = _dio_in_53_value;
    diagnostic0_database.PositionSensor_SineMinus = adc_0_channel_6;
    diagnostic0_database.PositionSensor_CosineMinus = adc_1_channel_2;
    diagnostic0_database.PositionSensor_SinePlus = adc_2_channel_3;
    diagnostic0_database.PositionSensor_CosinePlus = adc_2_channel_4;
    diagnostic0_database.TemperatureSensor_Motor = adc_2_channel_5;
    diagnostic0_database.PhaseB_Current = _ads7883_ads1.value;
    diagnostic0_database.Failure_ADS_1 = _ads7883_ads1.failure;
    diagnostic0_database.DC_Voltage = ads2.cs0.value;
    diagnostic0_database.Failure_ADS_2_0 = ads2.cs0.failure;
    diagnostic0_database.PhaseC_Current = ads2.cs1.value;
    diagnostic0_database.Failure_ADS_2_1 = ads2.cs1.failure;
    diagnostic0_database.PhaseA_Current = _ads7883_ads4.value;
    diagnostic0_database.Failure_ADS_4 = _ads7883_ads4.failure;
    diagnostic0_database.TemperatureSensor_PhaseA = _adi1.result_1;
    diagnostic0_database.TemperatureSensor_PhaseB = _adi1.result_2;
    diagnostic0_database.TemperatureSensor_PhaseC = _adi1.result_3;
    diagnostic0_database.Failure_ADI += _adi1.failure;
    diagnostic0_database.PhaseA_DutyCycle = asw.out.duty_cycle_a;
    diagnostic0_database.PhaseB_DutyCycle = asw.out.duty_cycle_b;
    diagnostic0_database.PhaseC_DutyCycle = asw.out.duty_cycle_c;
    diagnostic0_database.GateDriver_Enable = asw.out.gate_driver_enable;
    diagnostic0_database.ASW_OpenLoopAngle = asw.out.open_loop_angle;
    diagnostic0_database.ASW_MagneticAngle = asw.out.magnetic_angle;
    diagnostic0_database.ASW_MeasuredAngle = asw.out.measured_angle;
    diagnostic0_database.ASW_Ia = asw.out.ia;
    diagnostic0_database.ASW_Ib = asw.out.ib;
    diagnostic0_database.ASW_Ic = asw.out.ic;
    diagnostic0_database.ASW_Iabc = asw.out.iabc;
    diagnostic0_database.ASW_Id_Raw = asw.out.id_raw;
    diagnostic0_database.ASW_Iq_Raw = asw.out.iq_raw;
    diagnostic0_database.ASW_Id_Filtered = asw.out.id_filtered;
    diagnostic0_database.ASW_Iq_Filtered = asw.out.iq_filtered;
    diagnostic0_database.ASW_Udout = asw.out.udout;
    diagnostic0_database.ASW_Uqout = asw.out.uqout;

    /* diagnostic0. */
	uds_step(&_diagnostic0_uds_instance);

	//dio_write(&dio_out_44, 0);
}
