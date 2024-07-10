#ifndef DIAGNOSTIC0_DATABASE_H
#define DIAGNOSTIC0_DATABASE_H

#include "math.h" /* For NAN. */

#include "../middleware/serialize.h"

typedef struct {
    uint32_t Version;
    uint8_t GateDriver_PhaseA_HighSide_Ready;
    uint8_t GateDriver_PhaseA_HighSide_Fault;
    uint8_t GateDriver_PhaseA_LowSide_Ready;
    uint8_t GateDriver_PhaseA_LowSide_Fault;
    uint8_t GateDriver_PhaseB_HighSide_Ready;
    uint8_t GateDriver_PhaseB_HighSide_Fault;
    uint8_t GateDriver_PhaseB_LowSide_Ready;
    uint8_t GateDriver_PhaseB_LowSide_Fault;
    uint8_t GateDriver_PhaseC_HighSide_Ready;
    uint8_t GateDriver_PhaseC_HighSide_Fault;
    uint8_t GateDriver_PhaseC_LowSide_Ready;
    uint8_t GateDriver_PhaseC_LowSide_Fault;
    float PositionSensor_SinePlus;
    float PositionSensor_CosinePlus;
    float PositionSensor_SineMinus;
    float PositionSensor_CosineMinus;
    float TemperatureSensor_Motor;
    float TemperatureSensor_PhaseA;
    float TemperatureSensor_PhaseB;
    float TemperatureSensor_PhaseC;
    float PhaseA_Current;
    float PhaseB_Current;
    float PhaseC_Current;
    float DC_Voltage;
    float PhaseA_DutyCycle;
    float PhaseB_DutyCycle;
    float PhaseC_DutyCycle;
    uint8_t GateDriver_Enable;
    uint8_t ASW_CommutationType;
    float ASW_Iref;
    float ASW_Ud;
    float ASW_Uq;
    float ASW_OpenLoopAngle;
    float ASW_MagneticAngle;
    float ASW_MeasuredAngle;
    float ASW_RPM;
    float ASW_Ubemf;
    float ASW_Ia;
    float ASW_Ib;
    float ASW_Ic;
    float ASW_Iabc;
    float ASW_Currents_Ialpha;
    float ASW_Currents_Ibeta;
    float ASW_Currents_Idc_Raw;
    float ASW_Currents_Idc_Filtered;
    float ASW_Id_Raw;
    float ASW_Iq_Raw;
    float ASW_Id_Filtered;
    float ASW_Iq_Filtered;
    float ASW_Udout;
    float ASW_Uqout;
    float ASW_DQControl_Id_Kp;
    float ASW_DQControl_Id_Ki;
    float ASW_DQControl_Id_Kd;
    float ASW_DQControl_Iq_Kp;
    float ASW_DQControl_Iq_Ki;
    float ASW_DQControl_Iq_Kd;
    float ASW_DQControl_Limit;
    float ASW_DQControl_Rate;
    float ASW_Motor_Udc;
    float ASW_Motor_PolePairs;
    float ASW_Motor_KV;
    float ASW_Motor_R;
    float ASW_Motor_L;
    uint32_t ASW_PWMCounter;
    uint32_t Failure_Scheduler;
    uint32_t Failure_ADS_1;
    uint32_t Failure_ADS_2_0;
    uint32_t Failure_ADS_2_1;
    uint32_t Failure_ADS_4;
    uint32_t Failure_ADI;
} diagnostic0_database_t;

diagnostic0_database_t diagnostic0_database;
#define DIAGNOSTIC0_DATABASE_STORAGE_SIZE 32 /* Size of the database in the nonvolatile memory. */
uint8_t diagnostic0_database_storage[32]; /* Temporary storage of the database in the nonvolatile memory. */

void diagnostic0_database_init(void) {
	diagnostic0_database.Version = 1010000;
	diagnostic0_database.GateDriver_PhaseA_HighSide_Ready = 0;
	diagnostic0_database.GateDriver_PhaseA_HighSide_Fault = 0;
	diagnostic0_database.GateDriver_PhaseA_LowSide_Ready = 0;
	diagnostic0_database.GateDriver_PhaseA_LowSide_Fault = 0;
	diagnostic0_database.GateDriver_PhaseB_HighSide_Ready = 0;
	diagnostic0_database.GateDriver_PhaseB_HighSide_Fault = 0;
	diagnostic0_database.GateDriver_PhaseB_LowSide_Ready = 0;
	diagnostic0_database.GateDriver_PhaseB_LowSide_Fault = 0;
	diagnostic0_database.GateDriver_PhaseC_HighSide_Ready = 0;
	diagnostic0_database.GateDriver_PhaseC_HighSide_Fault = 0;
	diagnostic0_database.GateDriver_PhaseC_LowSide_Ready = 0;
	diagnostic0_database.GateDriver_PhaseC_LowSide_Fault = 0;
	diagnostic0_database.PositionSensor_SinePlus = NAN;
	diagnostic0_database.PositionSensor_CosinePlus = NAN;
	diagnostic0_database.PositionSensor_SineMinus = NAN;
	diagnostic0_database.PositionSensor_CosineMinus = NAN;
	diagnostic0_database.TemperatureSensor_Motor = NAN;
	diagnostic0_database.TemperatureSensor_PhaseA = NAN;
	diagnostic0_database.TemperatureSensor_PhaseB = NAN;
	diagnostic0_database.TemperatureSensor_PhaseC = NAN;
	diagnostic0_database.PhaseA_Current = NAN;
	diagnostic0_database.PhaseB_Current = NAN;
	diagnostic0_database.PhaseC_Current = NAN;
	diagnostic0_database.DC_Voltage = NAN;
	diagnostic0_database.PhaseA_DutyCycle = NAN;
	diagnostic0_database.PhaseB_DutyCycle = NAN;
	diagnostic0_database.PhaseC_DutyCycle = NAN;
	diagnostic0_database.GateDriver_Enable = 0;
	diagnostic0_database.ASW_CommutationType = 1;
	diagnostic0_database.ASW_Iref = NAN;
	diagnostic0_database.ASW_Ud = 0;
	diagnostic0_database.ASW_Uq = 0;
	diagnostic0_database.ASW_OpenLoopAngle = NAN;
	diagnostic0_database.ASW_MagneticAngle = NAN;
	diagnostic0_database.ASW_MeasuredAngle = NAN;
	diagnostic0_database.ASW_RPM = NAN;
	diagnostic0_database.ASW_Ubemf = NAN;
	diagnostic0_database.ASW_Ia = NAN;
	diagnostic0_database.ASW_Ib = NAN;
	diagnostic0_database.ASW_Ic = NAN;
	diagnostic0_database.ASW_Iabc = NAN;
	diagnostic0_database.ASW_Currents_Ialpha = NAN;
	diagnostic0_database.ASW_Currents_Ibeta = NAN;
	diagnostic0_database.ASW_Currents_Idc_Raw = NAN;
	diagnostic0_database.ASW_Currents_Idc_Filtered = 0.0f;
	diagnostic0_database.ASW_Id_Raw = NAN;
	diagnostic0_database.ASW_Iq_Raw = NAN;
	diagnostic0_database.ASW_Id_Filtered = NAN;
	diagnostic0_database.ASW_Iq_Filtered = NAN;
	diagnostic0_database.ASW_Udout = NAN;
	diagnostic0_database.ASW_Uqout = NAN;
	diagnostic0_database.ASW_DQControl_Id_Kp = 5;
	diagnostic0_database.ASW_DQControl_Id_Ki = 50;
	diagnostic0_database.ASW_DQControl_Id_Kd = 0;
	diagnostic0_database.ASW_DQControl_Iq_Kp = 5;
	diagnostic0_database.ASW_DQControl_Iq_Ki = 50;
	diagnostic0_database.ASW_DQControl_Iq_Kd = 0;
	diagnostic0_database.ASW_DQControl_Limit = 25;
	diagnostic0_database.ASW_DQControl_Rate = 500;
	diagnostic0_database.ASW_Motor_Udc = 50;
	diagnostic0_database.ASW_Motor_PolePairs = 3;
	diagnostic0_database.ASW_Motor_KV = 120;
	diagnostic0_database.ASW_Motor_R = 0.13;
	diagnostic0_database.ASW_Motor_L = 0.003;
	diagnostic0_database.ASW_PWMCounter = 0;
	diagnostic0_database.Failure_Scheduler = 0;
	diagnostic0_database.Failure_ADS_1 = 0;
	diagnostic0_database.Failure_ADS_2_0 = 0;
	diagnostic0_database.Failure_ADS_2_1 = 0;
	diagnostic0_database.Failure_ADS_4 = 0;
	diagnostic0_database.Failure_ADI = 0;
}

int32_t diagnostic0_database_read_data_by_identifier(uint16 did, uint8* data, uint8 length) {
    switch (did) {
		case 0x4100:
			return serialize_uint32(diagnostic0_database.Version, data);
		case 0x4101:
			return serialize_boolean(diagnostic0_database.GateDriver_PhaseA_HighSide_Ready, data);
		case 0x4102:
			return serialize_boolean(diagnostic0_database.GateDriver_PhaseA_HighSide_Fault, data);
		case 0x4103:
			return serialize_boolean(diagnostic0_database.GateDriver_PhaseA_LowSide_Ready, data);
		case 0x4104:
			return serialize_boolean(diagnostic0_database.GateDriver_PhaseA_LowSide_Fault, data);
		case 0x4105:
			return serialize_boolean(diagnostic0_database.GateDriver_PhaseB_HighSide_Ready, data);
		case 0x4106:
			return serialize_boolean(diagnostic0_database.GateDriver_PhaseB_HighSide_Fault, data);
		case 0x4107:
			return serialize_boolean(diagnostic0_database.GateDriver_PhaseB_LowSide_Ready, data);
		case 0x4108:
			return serialize_boolean(diagnostic0_database.GateDriver_PhaseB_LowSide_Fault, data);
		case 0x4109:
			return serialize_boolean(diagnostic0_database.GateDriver_PhaseC_HighSide_Ready, data);
		case 0x410a:
			return serialize_boolean(diagnostic0_database.GateDriver_PhaseC_HighSide_Fault, data);
		case 0x410b:
			return serialize_boolean(diagnostic0_database.GateDriver_PhaseC_LowSide_Ready, data);
		case 0x410c:
			return serialize_boolean(diagnostic0_database.GateDriver_PhaseC_LowSide_Fault, data);
		case 0x410d:
			return serialize_float(diagnostic0_database.PositionSensor_SinePlus, data);
		case 0x410e:
			return serialize_float(diagnostic0_database.PositionSensor_CosinePlus, data);
		case 0x410f:
			return serialize_float(diagnostic0_database.PositionSensor_SineMinus, data);
		case 0x4110:
			return serialize_float(diagnostic0_database.PositionSensor_CosineMinus, data);
		case 0x4111:
			return serialize_float(diagnostic0_database.TemperatureSensor_Motor, data);
		case 0x4112:
			return serialize_float(diagnostic0_database.TemperatureSensor_PhaseA, data);
		case 0x4113:
			return serialize_float(diagnostic0_database.TemperatureSensor_PhaseB, data);
		case 0x4114:
			return serialize_float(diagnostic0_database.TemperatureSensor_PhaseC, data);
		case 0x4115:
			return serialize_float(diagnostic0_database.PhaseA_Current, data);
		case 0x4116:
			return serialize_float(diagnostic0_database.PhaseB_Current, data);
		case 0x4117:
			return serialize_float(diagnostic0_database.PhaseC_Current, data);
		case 0x4118:
			return serialize_float(diagnostic0_database.DC_Voltage, data);
		case 0x4119:
			return serialize_float(diagnostic0_database.PhaseA_DutyCycle, data);
		case 0x411a:
			return serialize_float(diagnostic0_database.PhaseB_DutyCycle, data);
		case 0x411b:
			return serialize_float(diagnostic0_database.PhaseC_DutyCycle, data);
		case 0x411c:
			return serialize_boolean(diagnostic0_database.GateDriver_Enable, data);
		case 0x411d:
			return serialize_uint8(diagnostic0_database.ASW_CommutationType, data);
		case 0x411e:
			return serialize_float(diagnostic0_database.ASW_Iref, data);
		case 0x411f:
			return serialize_float(diagnostic0_database.ASW_Ud, data);
		case 0x4120:
			return serialize_float(diagnostic0_database.ASW_Uq, data);
		case 0x4121:
			return serialize_float(diagnostic0_database.ASW_OpenLoopAngle, data);
		case 0x4122:
			return serialize_float(diagnostic0_database.ASW_MagneticAngle, data);
		case 0x4123:
			return serialize_float(diagnostic0_database.ASW_MeasuredAngle, data);
		case 0x4124:
			return serialize_float(diagnostic0_database.ASW_RPM, data);
		case 0x4125:
			return serialize_float(diagnostic0_database.ASW_Ubemf, data);
		case 0x4126:
			return serialize_float(diagnostic0_database.ASW_Ia, data);
		case 0x4127:
			return serialize_float(diagnostic0_database.ASW_Ib, data);
		case 0x4128:
			return serialize_float(diagnostic0_database.ASW_Ic, data);
		case 0x4129:
			return serialize_float(diagnostic0_database.ASW_Iabc, data);
		case 0x412a:
			return serialize_float(diagnostic0_database.ASW_Currents_Ialpha, data);
		case 0x412b:
			return serialize_float(diagnostic0_database.ASW_Currents_Ibeta, data);
		case 0x412c:
			return serialize_float(diagnostic0_database.ASW_Currents_Idc_Raw, data);
		case 0x412d:
			return serialize_float(diagnostic0_database.ASW_Currents_Idc_Filtered, data);
		case 0x412e:
			return serialize_float(diagnostic0_database.ASW_Id_Raw, data);
		case 0x412f:
			return serialize_float(diagnostic0_database.ASW_Iq_Raw, data);
		case 0x4130:
			return serialize_float(diagnostic0_database.ASW_Id_Filtered, data);
		case 0x4131:
			return serialize_float(diagnostic0_database.ASW_Iq_Filtered, data);
		case 0x4132:
			return serialize_float(diagnostic0_database.ASW_Udout, data);
		case 0x4133:
			return serialize_float(diagnostic0_database.ASW_Uqout, data);
		case 0x4134:
			return serialize_float(diagnostic0_database.ASW_DQControl_Id_Kp, data);
		case 0x4135:
			return serialize_float(diagnostic0_database.ASW_DQControl_Id_Ki, data);
		case 0x4136:
			return serialize_float(diagnostic0_database.ASW_DQControl_Id_Kd, data);
		case 0x4137:
			return serialize_float(diagnostic0_database.ASW_DQControl_Iq_Kp, data);
		case 0x4138:
			return serialize_float(diagnostic0_database.ASW_DQControl_Iq_Ki, data);
		case 0x4139:
			return serialize_float(diagnostic0_database.ASW_DQControl_Iq_Kd, data);
		case 0x413a:
			return serialize_float(diagnostic0_database.ASW_DQControl_Limit, data);
		case 0x413b:
			return serialize_float(diagnostic0_database.ASW_DQControl_Rate, data);
		case 0x413c:
			return serialize_float(diagnostic0_database.ASW_Motor_Udc, data);
		case 0x413d:
			return serialize_float(diagnostic0_database.ASW_Motor_PolePairs, data);
		case 0x413e:
			return serialize_float(diagnostic0_database.ASW_Motor_KV, data);
		case 0x413f:
			return serialize_float(diagnostic0_database.ASW_Motor_R, data);
		case 0x4140:
			return serialize_float(diagnostic0_database.ASW_Motor_L, data);
		case 0x4141:
			return serialize_uint32(diagnostic0_database.ASW_PWMCounter, data);
		case 0x4142:
			return serialize_uint32(diagnostic0_database.Failure_Scheduler, data);
		case 0x4143:
			return serialize_uint32(diagnostic0_database.Failure_ADS_1, data);
		case 0x4144:
			return serialize_uint32(diagnostic0_database.Failure_ADS_2_0, data);
		case 0x4145:
			return serialize_uint32(diagnostic0_database.Failure_ADS_2_1, data);
		case 0x4146:
			return serialize_uint32(diagnostic0_database.Failure_ADS_4, data);
		case 0x4147:
			return serialize_uint32(diagnostic0_database.Failure_ADI, data);
		case 0x4148:
			return serialize_uint32(nvm_failure, data);
		default:
			return 0;
    }
}

int32_t diagnostic0_database_write_data_by_identifier(uint16 did, const uint8* data, uint8 length) {
    switch (did) {
		case 0x411d:
			return deserialize_uint8(data, &diagnostic0_database.ASW_CommutationType);
		case 0x411e:
			return deserialize_float(data, &diagnostic0_database.ASW_Iref);
		case 0x411f:
			return deserialize_float(data, &diagnostic0_database.ASW_Ud);
		case 0x4120:
			return deserialize_float(data, &diagnostic0_database.ASW_Uq);
		case 0x4134:
			return deserialize_float(data, &diagnostic0_database.ASW_DQControl_Id_Kp);
		case 0x4135:
			return deserialize_float(data, &diagnostic0_database.ASW_DQControl_Id_Ki);
		case 0x4136:
			return deserialize_float(data, &diagnostic0_database.ASW_DQControl_Id_Kd);
		case 0x4137:
			return deserialize_float(data, &diagnostic0_database.ASW_DQControl_Iq_Kp);
		case 0x4138:
			return deserialize_float(data, &diagnostic0_database.ASW_DQControl_Iq_Ki);
		case 0x4139:
			return deserialize_float(data, &diagnostic0_database.ASW_DQControl_Iq_Kd);
		case 0x413a:
			return deserialize_float(data, &diagnostic0_database.ASW_DQControl_Limit);
		case 0x413b:
			return deserialize_float(data, &diagnostic0_database.ASW_DQControl_Rate);
		case 0x413c:
			return deserialize_float(data, &diagnostic0_database.ASW_Motor_Udc);
		case 0x413d:
			return deserialize_float(data, &diagnostic0_database.ASW_Motor_PolePairs);
		case 0x413e:
			return deserialize_float(data, &diagnostic0_database.ASW_Motor_KV);
		case 0x413f:
			return deserialize_float(data, &diagnostic0_database.ASW_Motor_R);
		case 0x4140:
			return deserialize_float(data, &diagnostic0_database.ASW_Motor_L);
		case 0x4141:
			return deserialize_uint32(data, &diagnostic0_database.ASW_PWMCounter);
		default:
			return 0;
    }
}

/*
 * Load data from storage/nonvolatile memory.
 */
int32_t diagnostic0_database_load(void) {
	int32_t i = 0;
	i += deserialize_float(&diagnostic0_database_storage[i], &diagnostic0_database.ASW_DQControl_Id_Kp);
	i += deserialize_float(&diagnostic0_database_storage[i], &diagnostic0_database.ASW_DQControl_Id_Ki);
	i += deserialize_float(&diagnostic0_database_storage[i], &diagnostic0_database.ASW_DQControl_Id_Kd);
	i += deserialize_float(&diagnostic0_database_storage[i], &diagnostic0_database.ASW_DQControl_Iq_Kp);
	i += deserialize_float(&diagnostic0_database_storage[i], &diagnostic0_database.ASW_DQControl_Iq_Ki);
	i += deserialize_float(&diagnostic0_database_storage[i], &diagnostic0_database.ASW_DQControl_Iq_Kd);
	i += deserialize_float(&diagnostic0_database_storage[i], &diagnostic0_database.ASW_DQControl_Limit);
	i += deserialize_float(&diagnostic0_database_storage[i], &diagnostic0_database.ASW_DQControl_Rate);
	return i;
}

/*
 * Store data to nonvolatile memory.
 */
int32_t diagnostic0_database_store(void) {
	int32_t i = 0;
	i += serialize_float(diagnostic0_database.ASW_DQControl_Id_Kp, &diagnostic0_database_storage[i]);
	i += serialize_float(diagnostic0_database.ASW_DQControl_Id_Ki, &diagnostic0_database_storage[i]);
	i += serialize_float(diagnostic0_database.ASW_DQControl_Id_Kd, &diagnostic0_database_storage[i]);
	i += serialize_float(diagnostic0_database.ASW_DQControl_Iq_Kp, &diagnostic0_database_storage[i]);
	i += serialize_float(diagnostic0_database.ASW_DQControl_Iq_Ki, &diagnostic0_database_storage[i]);
	i += serialize_float(diagnostic0_database.ASW_DQControl_Iq_Kd, &diagnostic0_database_storage[i]);
	i += serialize_float(diagnostic0_database.ASW_DQControl_Limit, &diagnostic0_database_storage[i]);
	i += serialize_float(diagnostic0_database.ASW_DQControl_Rate, &diagnostic0_database_storage[i]);
	return i;
}

#endif
