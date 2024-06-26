/** CAN message encoder/decoder: automatically generated - do not edit
  * Generated by dbcc: See https://github.com/howerj/dbcc */
#ifndef MDU_V002X_TB_H
#define MDU_V002X_TB_H

/* If the contents of this file have caused breaking changes for you, you could try using
   an older version of the generator. You can specify this on the command line with
   the -n option. */
#define DBCC_GENERATOR_VERSION (3)

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" { 
#endif

#ifndef PREPACK
#define PREPACK
#endif

#ifndef POSTPACK
#define POSTPACK
#endif

#ifndef DBCC_TIME_STAMP
#define DBCC_TIME_STAMP
typedef uint32_t dbcc_time_stamp_t; /* Time stamp for message; you decide on units */
#endif

#ifndef DBCC_STATUS_ENUM
#define DBCC_STATUS_ENUM
typedef enum {
	DBCC_SIG_STAT_UNINITIALIZED_E = 0, /* Message never sent/received */
	DBCC_SIG_STAT_OK_E            = 1, /* Message ok */
	DBCC_SIG_STAT_ERROR_E         = 2, /* Encode/Decode/Timestamp/Any error */
} dbcc_signal_status_e;
#endif

#define CAN_ID_VCU_ENGINE_TORQUE_EPP (265) /* 0x109 */
#define CAN_ID_MDU_SPEED_TORQUE_INFO (282) /* 0x11a */
#define CAN_ID_MDU_STATUS_INFO_1 (283) /* 0x11b */
#define CAN_ID_VCU_EPP_DATA (287) /* 0x11f */
#define CAN_ID_BMS_PACK_CV_INFO (338) /* 0x152 */
#define CAN_ID_MDU_STATUS_INFO_2 (608) /* 0x260 */
#define CAN_ID_DASH_BIKE_INFO (1370) /* 0x55a */
#define CAN_ID_VCU_VEHICLE_INFO (1408) /* 0x580 */
#define CAN_ID_MDU_DEBUG_1 (1844) /* 0x734 */
#define CAN_ID_MDU_DEBUG_2 (1845) /* 0x735 */
#define CAN_ID_MDU_DEBUG_3 (1846) /* 0x736 */
#define CAN_ID_MDU_DEBUG_4 (1847) /* 0x737 */
#define CAN_ID_MDU_DEBUG_5 (1848) /* 0x738 */
#define CAN_ID_TB_REQUEST (2000) /* 0x7d0 */

typedef PREPACK struct {
	/* VCU_Eng_Req_Torque: Torque Request from VCU. This Torque shall be applied on the engine. */
	/* scaling 0.1, offset 0.0, units Nm  */
	int16_t VCU_Eng_Req_Torque;
	/* VCU_CRC_109: CRC-5 Checksum */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t VCU_CRC_109;
	/* VCU_Alive_Counter_109: Counter is increased every message until overflow */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t VCU_Alive_Counter_109;
	/* VCU_Engine_Direction_Req: Request from VCU regarding rotor torque direction. */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t VCU_Engine_Direction_Req;
	/* VCU_Eng_Req_Torque_Valid: Validity bit of \"VCU_Eng_Req_Torque\" signal */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t VCU_Eng_Req_Torque_Valid;
	/* VCU_MDU_Interlock: VCU Request for MDU state \"Drive\" */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t VCU_MDU_Interlock;
} POSTPACK can_0x109_VCU_Engine_Torque_EPP_t;

typedef PREPACK struct {
	/* MDU_Engine_Rpm: Speed of the engine */
	/* scaling 1.0, offset 0.0, units rpm  */
	int16_t MDU_Engine_Rpm;
	/* MDU_Eng_Act_RPM_Gradient: The gradient and therefore the derivative of the RPM signal */
	/* scaling 10.0, offset 0.0, units rpm/s  */
	int16_t MDU_Eng_Act_RPM_Gradient;
	/* MDU_Eng_Actual_Torque: Current engine torque */
	/* scaling 0.2, offset 0.0, units Nm  */
	int16_t MDU_Eng_Actual_Torque;
	/* MDU_CRC_11A: CRC-5 Checksum */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_CRC_11A;
	/* MDU_Alive_Counter_11A: Counter is increased every message until overflow */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_Alive_Counter_11A;
	/* MDU_Engine_Rpm_Validity: Validity of the \"MDU_Engine_Rpm\" signals */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_Engine_Rpm_Validity;
	/* MDU_Eng_Act_Trq_Validity: Validity of the \"MDU_Eng_Actual_Torque\" signals */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_Eng_Act_Trq_Validity;
} POSTPACK can_0x11a_MDU_Speed_Torque_Info_t;

typedef PREPACK struct {
	/* MDU_Max_Torque_Avl: Maximum Torque wich can be generated by the Engine at the current speed. (Acceleration) */
	/* scaling 0.1, offset 0.0, units Nm  */
	int16_t MDU_Max_Torque_Avl;
	/* MDU_Min_Torque_Avl: Minimum Torque wich can be generated by the Engine at the current speed. (Regeneration) */
	/* scaling 0.1, offset 0.0, units Nm  */
	int16_t MDU_Min_Torque_Avl;
	/* MDU_Max_Torque_Derating: Maximum Torque wich can be generated by the Engine at the current speed, considering derating effects of MDU/Engine (Acceleration) */
	/* scaling 0.1, offset 0.0, units Nm  */
	int16_t MDU_Max_Torque_Derating;
	/* MDU_Min_Torque_Derating: Minimum Torque wich can be generated by the Engine at the current speed, considering derating effects of MDU/Engine (Regeneration) */
	/* scaling 0.1, offset 0.0, units Nm  */
	int16_t MDU_Min_Torque_Derating;
} POSTPACK can_0x11b_MDU_Status_Info_1_t;

typedef PREPACK struct {
	/* VCU_CRC_11F: CRC-5 Checksum for message 11F */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t VCU_CRC_11F;
	/* VCU_Vehicle_State: The Signal indicates the actual Vehicle State. */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t VCU_Vehicle_State;
	/* VCU_Regen_Mode_Response: VCU sends Regen Mode response based on DASH request. */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t VCU_Regen_Mode_Response;
	/* VCU_Alive_Counter_11F: Alive Counter of message 11F */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t VCU_Alive_Counter_11F;
	/* VCU_Drive_Mode_Status: Indicates the drive mode status of the vehicle. */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t VCU_Drive_Mode_Status;
	/* VCU_TC_Status_Response: The Signal indicates the Traction Control status. */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t VCU_TC_Status_Response;
} POSTPACK can_0x11f_VCU_EPP_Data_t;

typedef PREPACK struct {
	/* BMS_Current_Pack: Measurement of battery pack current */
	/* scaling 0.2, offset 0.0, units A  */
	int16_t BMS_Current_Pack;
	/* BMS_Voltage_Pack: Measurement BMS pack voltage (sum of cell voltages) */
	/* scaling 0.1, offset 0.0, units V  */
	uint16_t BMS_Voltage_Pack;
	/* DASH_CRC_152: CRC of signal 152 */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t DASH_CRC_152;
	/* DASH_Alive_Counter_152: Alive counter for signal 152 */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t DASH_Alive_Counter_152;
	/* BMS_Regeneration_Allowed: Flag indicates if regeneration is allowed according to BAT_T201_BMS_SW_REQUIREMENT_SPECIFICATION */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t BMS_Regeneration_Allowed;
	/* BMS_Status_FET: Actual power contactor state. */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t BMS_Status_FET;
} POSTPACK can_0x152_BMS_Pack_CV_Info_t;

typedef PREPACK struct {
	/* MDU_Engine_Temp: Actual Temperature of the Engine */
	/* scaling 0.5, offset 98.0, units �C  */
	int16_t MDU_Engine_Temp;
	/* MDU_Temp: Actual Temperature of the MDU */
	/* scaling 0.5, offset 34.0, units �C  */
	int8_t MDU_Temp;
	/* MDU_CRC_260: CRC-5 Checksum */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_CRC_260;
	/* MDU_State: Indicates the actual state of the MDU */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_State;
	/* MDU_Alive_Counter_260: Counter is increased every message until overflow */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_Alive_Counter_260;
	/* MDU_Engine_Direction_Resp: Respond from MDU regarding rotor torque direction. */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_Engine_Direction_Resp;
	/* MDU_Malfunction_Indica_LED: Status of the MIL lamp  */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_Malfunction_Indica_LED;
	/* MDU_General_Failure_LED: Activation signal for general failure LED */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_General_Failure_LED;
	/* MDU_Failure: Indicates MDU failure */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_Failure;
	/* MDU_Overspeed_Warning: Indicates Engine Overspeed */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_Overspeed_Warning;
	/* MDU_Warning: Indicates MDU warning request for Limp Home Mode */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_Warning;
	/* MDU_Temp_Warning: Indicates MDU Temperature Warning */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_Temp_Warning;
	/* MDU_Engine_Temp_Warning: Indicates Engine Temperature Warning */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_Engine_Temp_Warning;
} POSTPACK can_0x260_MDU_Status_Info_2_t;

typedef PREPACK struct {
	/* DASH_Odo_Meter_Extended: Dash sends odometer value extended */
	/* scaling 0.1, offset 0.0, units km  */
	uint32_t DASH_Odo_Meter_Extended;
} POSTPACK can_0x55a_DASH_Bike_Info_t;

typedef PREPACK struct {
	/* VCU_Hourmeter: Indicates the \"Active Time\" of the vehicle */
	/* scaling 0.1, offset 0.0, units h  */
	uint16_t VCU_Hourmeter;
	/* VCU_Est_Range: Estimated remaining range of the vehicle */
	/* scaling 5.0, offset 0.0, units km  */
	uint8_t VCU_Est_Range;
	/* VCU_Est_Riding_Time: Estimated remaining riding time of the vehicle */
	/* scaling 1.0, offset 0.0, units min  */
	uint8_t VCU_Est_Riding_Time;
	/* VCU_Drivecycle_Detected: The Signal indicates that a Drivecycle of the Vehicle was detected */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t VCU_Drivecycle_Detected;
} POSTPACK can_0x580_VCU_Vehicle_Info_t;

typedef PREPACK struct {
	/* MDU_Limited_Torq_Req: Limited torque demand */
	/* scaling 0.1, offset 0.0, units Nm  */
	int16_t MDU_Limited_Torq_Req;
	/* MDU_Phase_A_volt: Imposed Phase A Voltage */
	/* scaling 0.0, offset 0.0, units V  */
	int16_t MDU_Phase_A_volt;
	/* MDU_Phase_B_volt: Imposed Phase B Voltage */
	/* scaling 0.0, offset 0.0, units V  */
	int16_t MDU_Phase_B_volt;
	/* MDU_Received_Torq_Req: Received torque demand */
	/* scaling 0.1, offset 0.0, units Nm  */
	int16_t MDU_Received_Torq_Req;
} POSTPACK can_0x734_MDU_Debug_1_t;

typedef PREPACK struct {
	/* MDU_Phase_A_amps: Motor Current, Phase A  */
	/* scaling 0.0, offset 0.0, units A  */
	int16_t MDU_Phase_A_amps;
	/* MDU_Phase_B_amps: Motor Current, Phase B  */
	/* scaling 0.0, offset 0.0, units A  */
	int16_t MDU_Phase_B_amps;
	/* MDU_Phase_C_amps: Motor Current, Phase B  */
	/* scaling 0.0, offset 0.0, units A  */
	int16_t MDU_Phase_C_amps;
	/* MDU_Phase_C_volt: Imposed Phase C Voltage */
	/* scaling 0.0, offset 0.0, units V  */
	int16_t MDU_Phase_C_volt;
} POSTPACK can_0x735_MDU_Debug_2_t;

typedef PREPACK struct {
	/* MDU_DC_Bus_amps_calc: DC-Bus Current, calculated */
	/* scaling 0.0, offset 0.0, units A  */
	int16_t MDU_DC_Bus_amps_calc;
	/* MDU_Iq_measured: Measured quadrature Current */
	/* scaling 0.0, offset 0.0, units A  */
	int16_t MDU_Iq_measured;
	/* MDU_Iq_request: Requested quadrature Current */
	/* scaling 0.0, offset 0.0, units A  */
	int16_t MDU_Iq_request;
	/* MDU_DC_Bus_volt: DC-Bus Voltage */
	/* scaling 0.0, offset 0.0, units V  */
	uint16_t MDU_DC_Bus_volt;
	/* MDU_gate_ready: Gate Driver Ready */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_gate_ready;
} POSTPACK can_0x736_MDU_Debug_3_t;

typedef PREPACK struct {
	/* MDU_Id_measured: Measured DC-Current */
	/* scaling 0.0, offset 0.0, units A  */
	int16_t MDU_Id_measured;
	/* MDU_Id_request: Requested DC-Current */
	/* scaling 0.0, offset 0.0, units A  */
	int16_t MDU_Id_request;
	/* MDU_uq_measured: Measured quadrature Voltage Uq */
	/* scaling 0.0, offset 0.0, units V  */
	int16_t MDU_uq_measured;
	/* MDU_uq_request: Requested quadrature Voltage Uq */
	/* scaling 0.0, offset 0.0, units V  */
	int16_t MDU_uq_request;
} POSTPACK can_0x737_MDU_Debug_4_t;

typedef PREPACK struct {
	/* MDU_u_mod: Voltage Module */
	/* scaling 0.0, offset 0.0, units V  */
	int16_t MDU_u_mod;
	/* MDU_ud_measured: Measured DC-Voltage Ud */
	/* scaling 0.0, offset 0.0, units V  */
	int16_t MDU_ud_measured;
	/* MDU_ud_request: Requested DC Voltage Ud */
	/* scaling 0.0, offset 0.0, units V  */
	int16_t MDU_ud_request;
	/* MDU_power_calc: Calculated electrical Inverter Power Output */
	/* scaling 0.0, offset 0.0, units kW  */
	int16_t MDU_power_calc;
	/* MDU_gate_fault: Gate Driver Fault */
	/* scaling 1.0, offset 0.0, units none  */
	uint8_t MDU_gate_fault;
} POSTPACK can_0x738_MDU_Debug_5_t;

typedef PREPACK struct {
	int16_t TB_Request_Speed; /* scaling 1.0, offset 0.0, units rpm  */
} POSTPACK can_0x7d0_TB_Request_t;

typedef PREPACK struct {
	dbcc_time_stamp_t can_0x109_VCU_Engine_Torque_EPP_time_stamp_rx;
	dbcc_time_stamp_t can_0x11a_MDU_Speed_Torque_Info_time_stamp_rx;
	dbcc_time_stamp_t can_0x11b_MDU_Status_Info_1_time_stamp_rx;
	dbcc_time_stamp_t can_0x11f_VCU_EPP_Data_time_stamp_rx;
	dbcc_time_stamp_t can_0x152_BMS_Pack_CV_Info_time_stamp_rx;
	dbcc_time_stamp_t can_0x260_MDU_Status_Info_2_time_stamp_rx;
	dbcc_time_stamp_t can_0x55a_DASH_Bike_Info_time_stamp_rx;
	dbcc_time_stamp_t can_0x580_VCU_Vehicle_Info_time_stamp_rx;
	dbcc_time_stamp_t can_0x734_MDU_Debug_1_time_stamp_rx;
	dbcc_time_stamp_t can_0x735_MDU_Debug_2_time_stamp_rx;
	dbcc_time_stamp_t can_0x736_MDU_Debug_3_time_stamp_rx;
	dbcc_time_stamp_t can_0x737_MDU_Debug_4_time_stamp_rx;
	dbcc_time_stamp_t can_0x738_MDU_Debug_5_time_stamp_rx;
	dbcc_time_stamp_t can_0x7d0_TB_Request_time_stamp_rx;
	unsigned can_0x109_VCU_Engine_Torque_EPP_status : 2;
	unsigned can_0x109_VCU_Engine_Torque_EPP_tx : 1;
	unsigned can_0x109_VCU_Engine_Torque_EPP_rx : 1;
	unsigned can_0x11a_MDU_Speed_Torque_Info_status : 2;
	unsigned can_0x11a_MDU_Speed_Torque_Info_tx : 1;
	unsigned can_0x11a_MDU_Speed_Torque_Info_rx : 1;
	unsigned can_0x11b_MDU_Status_Info_1_status : 2;
	unsigned can_0x11b_MDU_Status_Info_1_tx : 1;
	unsigned can_0x11b_MDU_Status_Info_1_rx : 1;
	unsigned can_0x11f_VCU_EPP_Data_status : 2;
	unsigned can_0x11f_VCU_EPP_Data_tx : 1;
	unsigned can_0x11f_VCU_EPP_Data_rx : 1;
	unsigned can_0x152_BMS_Pack_CV_Info_status : 2;
	unsigned can_0x152_BMS_Pack_CV_Info_tx : 1;
	unsigned can_0x152_BMS_Pack_CV_Info_rx : 1;
	unsigned can_0x260_MDU_Status_Info_2_status : 2;
	unsigned can_0x260_MDU_Status_Info_2_tx : 1;
	unsigned can_0x260_MDU_Status_Info_2_rx : 1;
	unsigned can_0x55a_DASH_Bike_Info_status : 2;
	unsigned can_0x55a_DASH_Bike_Info_tx : 1;
	unsigned can_0x55a_DASH_Bike_Info_rx : 1;
	unsigned can_0x580_VCU_Vehicle_Info_status : 2;
	unsigned can_0x580_VCU_Vehicle_Info_tx : 1;
	unsigned can_0x580_VCU_Vehicle_Info_rx : 1;
	unsigned can_0x734_MDU_Debug_1_status : 2;
	unsigned can_0x734_MDU_Debug_1_tx : 1;
	unsigned can_0x734_MDU_Debug_1_rx : 1;
	unsigned can_0x735_MDU_Debug_2_status : 2;
	unsigned can_0x735_MDU_Debug_2_tx : 1;
	unsigned can_0x735_MDU_Debug_2_rx : 1;
	unsigned can_0x736_MDU_Debug_3_status : 2;
	unsigned can_0x736_MDU_Debug_3_tx : 1;
	unsigned can_0x736_MDU_Debug_3_rx : 1;
	unsigned can_0x737_MDU_Debug_4_status : 2;
	unsigned can_0x737_MDU_Debug_4_tx : 1;
	unsigned can_0x737_MDU_Debug_4_rx : 1;
	unsigned can_0x738_MDU_Debug_5_status : 2;
	unsigned can_0x738_MDU_Debug_5_tx : 1;
	unsigned can_0x738_MDU_Debug_5_rx : 1;
	unsigned can_0x7d0_TB_Request_status : 2;
	unsigned can_0x7d0_TB_Request_tx : 1;
	unsigned can_0x7d0_TB_Request_rx : 1;
	can_0x109_VCU_Engine_Torque_EPP_t can_0x109_VCU_Engine_Torque_EPP;
	can_0x11a_MDU_Speed_Torque_Info_t can_0x11a_MDU_Speed_Torque_Info;
	can_0x11b_MDU_Status_Info_1_t can_0x11b_MDU_Status_Info_1;
	can_0x11f_VCU_EPP_Data_t can_0x11f_VCU_EPP_Data;
	can_0x152_BMS_Pack_CV_Info_t can_0x152_BMS_Pack_CV_Info;
	can_0x260_MDU_Status_Info_2_t can_0x260_MDU_Status_Info_2;
	can_0x55a_DASH_Bike_Info_t can_0x55a_DASH_Bike_Info;
	can_0x580_VCU_Vehicle_Info_t can_0x580_VCU_Vehicle_Info;
	can_0x734_MDU_Debug_1_t can_0x734_MDU_Debug_1;
	can_0x735_MDU_Debug_2_t can_0x735_MDU_Debug_2;
	can_0x736_MDU_Debug_3_t can_0x736_MDU_Debug_3;
	can_0x737_MDU_Debug_4_t can_0x737_MDU_Debug_4;
	can_0x738_MDU_Debug_5_t can_0x738_MDU_Debug_5;
	can_0x7d0_TB_Request_t can_0x7d0_TB_Request;
} POSTPACK can_obj_mdu_v002x_tb_h_t;

int unpack_message(can_obj_mdu_v002x_tb_h_t *o, const unsigned long id, uint64_t data, uint8_t dlc, dbcc_time_stamp_t time_stamp);
int pack_message(can_obj_mdu_v002x_tb_h_t *o, const unsigned long id, uint64_t *data);
int print_message(const can_obj_mdu_v002x_tb_h_t *o, const unsigned long id, FILE *output);

int decode_can_0x109_VCU_Eng_Req_Torque(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x109_VCU_Eng_Req_Torque(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x109_VCU_CRC_109(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x109_VCU_CRC_109(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x109_VCU_Alive_Counter_109(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x109_VCU_Alive_Counter_109(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x109_VCU_Engine_Direction_Req(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x109_VCU_Engine_Direction_Req(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x109_VCU_Eng_Req_Torque_Valid(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x109_VCU_Eng_Req_Torque_Valid(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x109_VCU_MDU_Interlock(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x109_VCU_MDU_Interlock(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);


int decode_can_0x11a_MDU_Engine_Rpm(const can_obj_mdu_v002x_tb_h_t *o, int16_t *out);
int encode_can_0x11a_MDU_Engine_Rpm(can_obj_mdu_v002x_tb_h_t *o, int16_t in);
int decode_can_0x11a_MDU_Eng_Act_RPM_Gradient(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x11a_MDU_Eng_Act_RPM_Gradient(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x11a_MDU_Eng_Actual_Torque(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x11a_MDU_Eng_Actual_Torque(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x11a_MDU_CRC_11A(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x11a_MDU_CRC_11A(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x11a_MDU_Alive_Counter_11A(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x11a_MDU_Alive_Counter_11A(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x11a_MDU_Engine_Rpm_Validity(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x11a_MDU_Engine_Rpm_Validity(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x11a_MDU_Eng_Act_Trq_Validity(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x11a_MDU_Eng_Act_Trq_Validity(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);


int decode_can_0x11b_MDU_Max_Torque_Avl(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x11b_MDU_Max_Torque_Avl(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x11b_MDU_Min_Torque_Avl(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x11b_MDU_Min_Torque_Avl(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x11b_MDU_Max_Torque_Derating(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x11b_MDU_Max_Torque_Derating(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x11b_MDU_Min_Torque_Derating(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x11b_MDU_Min_Torque_Derating(can_obj_mdu_v002x_tb_h_t *o, double in);


int decode_can_0x11f_VCU_CRC_11F(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x11f_VCU_CRC_11F(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x11f_VCU_Vehicle_State(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x11f_VCU_Vehicle_State(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x11f_VCU_Regen_Mode_Response(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x11f_VCU_Regen_Mode_Response(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x11f_VCU_Alive_Counter_11F(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x11f_VCU_Alive_Counter_11F(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x11f_VCU_Drive_Mode_Status(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x11f_VCU_Drive_Mode_Status(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x11f_VCU_TC_Status_Response(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x11f_VCU_TC_Status_Response(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);


int decode_can_0x152_BMS_Current_Pack(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x152_BMS_Current_Pack(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x152_BMS_Voltage_Pack(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x152_BMS_Voltage_Pack(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x152_DASH_CRC_152(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x152_DASH_CRC_152(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x152_DASH_Alive_Counter_152(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x152_DASH_Alive_Counter_152(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x152_BMS_Regeneration_Allowed(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x152_BMS_Regeneration_Allowed(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x152_BMS_Status_FET(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x152_BMS_Status_FET(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);


int decode_can_0x260_MDU_Engine_Temp(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x260_MDU_Engine_Temp(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x260_MDU_Temp(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x260_MDU_Temp(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x260_MDU_CRC_260(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x260_MDU_CRC_260(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x260_MDU_State(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x260_MDU_State(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x260_MDU_Alive_Counter_260(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x260_MDU_Alive_Counter_260(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x260_MDU_Engine_Direction_Resp(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x260_MDU_Engine_Direction_Resp(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x260_MDU_Malfunction_Indica_LED(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x260_MDU_Malfunction_Indica_LED(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x260_MDU_General_Failure_LED(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x260_MDU_General_Failure_LED(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x260_MDU_Failure(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x260_MDU_Failure(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x260_MDU_Overspeed_Warning(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x260_MDU_Overspeed_Warning(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x260_MDU_Warning(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x260_MDU_Warning(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x260_MDU_Temp_Warning(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x260_MDU_Temp_Warning(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x260_MDU_Engine_Temp_Warning(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x260_MDU_Engine_Temp_Warning(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);


int decode_can_0x55a_DASH_Odo_Meter_Extended(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x55a_DASH_Odo_Meter_Extended(can_obj_mdu_v002x_tb_h_t *o, double in);


int decode_can_0x580_VCU_Hourmeter(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x580_VCU_Hourmeter(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x580_VCU_Est_Range(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x580_VCU_Est_Range(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x580_VCU_Est_Riding_Time(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x580_VCU_Est_Riding_Time(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);
int decode_can_0x580_VCU_Drivecycle_Detected(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x580_VCU_Drivecycle_Detected(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);


int decode_can_0x734_MDU_Limited_Torq_Req(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x734_MDU_Limited_Torq_Req(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x734_MDU_Phase_A_volt(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x734_MDU_Phase_A_volt(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x734_MDU_Phase_B_volt(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x734_MDU_Phase_B_volt(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x734_MDU_Received_Torq_Req(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x734_MDU_Received_Torq_Req(can_obj_mdu_v002x_tb_h_t *o, double in);


int decode_can_0x735_MDU_Phase_A_amps(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x735_MDU_Phase_A_amps(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x735_MDU_Phase_B_amps(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x735_MDU_Phase_B_amps(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x735_MDU_Phase_C_amps(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x735_MDU_Phase_C_amps(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x735_MDU_Phase_C_volt(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x735_MDU_Phase_C_volt(can_obj_mdu_v002x_tb_h_t *o, double in);


int decode_can_0x736_MDU_DC_Bus_amps_calc(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x736_MDU_DC_Bus_amps_calc(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x736_MDU_Iq_measured(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x736_MDU_Iq_measured(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x736_MDU_Iq_request(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x736_MDU_Iq_request(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x736_MDU_DC_Bus_volt(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x736_MDU_DC_Bus_volt(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x736_MDU_gate_ready(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x736_MDU_gate_ready(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);


int decode_can_0x737_MDU_Id_measured(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x737_MDU_Id_measured(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x737_MDU_Id_request(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x737_MDU_Id_request(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x737_MDU_uq_measured(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x737_MDU_uq_measured(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x737_MDU_uq_request(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x737_MDU_uq_request(can_obj_mdu_v002x_tb_h_t *o, double in);


int decode_can_0x738_MDU_u_mod(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x738_MDU_u_mod(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x738_MDU_ud_measured(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x738_MDU_ud_measured(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x738_MDU_ud_request(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x738_MDU_ud_request(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x738_MDU_power_calc(const can_obj_mdu_v002x_tb_h_t *o, double *out);
int encode_can_0x738_MDU_power_calc(can_obj_mdu_v002x_tb_h_t *o, double in);
int decode_can_0x738_MDU_gate_fault(const can_obj_mdu_v002x_tb_h_t *o, uint8_t *out);
int encode_can_0x738_MDU_gate_fault(can_obj_mdu_v002x_tb_h_t *o, uint8_t in);


int decode_can_0x7d0_TB_Request_Speed(const can_obj_mdu_v002x_tb_h_t *o, int16_t *out);
int encode_can_0x7d0_TB_Request_Speed(can_obj_mdu_v002x_tb_h_t *o, int16_t in);


#ifdef __cplusplus
} 
#endif

#endif
