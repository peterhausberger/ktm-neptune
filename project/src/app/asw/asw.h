#include "../../drivers/nvm.h"
#include "../diagnostic0_database.g.h"

/* ================ LUTs for u_d and u_q. ===================== */

#define _DC_VOLTAGE 50.0f

/*#include "ud_data.h"
#include "uq_data.h"
#include "../../middleware/lut.h"

//const lut_t _ud_lut = {&_ud_lut_data[0][0], _UD_LUT_ROWS, _UD_LUT_COLS};
const lut_t _ud_lut = {ud_data, UD_DATA_COLS, UD_DATA_ROWS};
const lut_t _uq_lut = {uq_data, UQ_DATA_COLS, UQ_DATA_ROWS};*/

/* ============================================================ */

/* ================ LUTs for i_d and i_q. ===================== */

#include "id_t200_hv.h"
#include "iq_t200_hv.h"
#include "../../middleware/lut.h"

//const lut_t _ud_lut = {&_ud_lut_data[0][0], _UD_LUT_ROWS, _UD_LUT_COLS};
const lut_t _id_lut = {id_t200_hv, ID_T200_HV_COLS, ID_T200_HV_ROWS};
const lut_t _iq_lut = {iq_t200_hv, IQ_T200_HV_COLS, IQ_T200_HV_ROWS};

/* ============================================================ */


#define PI 3.14159265358979323846f

#define _SQRT3_2 0.86602540378f

#define _1_SQRT3 (1 / sqrtf(3))
#define _2_SQRT3 (2 / sqrtf(3))

#define _POLE_PAIRS 3
#define _MAX_TORQUE_NM 10.0f

#define _CURRENT_OFFSET_A (-340.0f - 0.17f)
#define _CURRENT_FACTOR_A 680.0f
#define _CURRENT_OFFSET_B (-340.0f - 0.67f)
#define _CURRENT_FACTOR_B 680.0f
#define _CURRENT_OFFSET_C (-338.0f + 0.32f)
#define _CURRENT_FACTOR_C 680.0f

#define _IQD_LPF_TF 0.5f // 0.005f
#define _SAMPLING_TIME 0.000250f
#define _IQD_LPF_ALPHA (_IQD_LPF_TF / (_IQD_LPF_TF + _SAMPLING_TIME))

#define _SINE_MIN 0.15f
#define _SINE_MAX 0.7f

#define _L 0.000435f
#define _R 0.03906f


//#define _SINE_OFFSET -1.23f /* For T200 Motor! */
//#define _SINE_OFFSET 0.48f
#define _SINE_OFFSET (0.48f - 0.15f) /*
// This value should be correct after switching sine/cosine!
//#define _SINE_OFFSET (0.48f - 0.15f - 1.5f + 2.03f) /* The offset parameter is determined by aligning the motor to phase A. The negative
							   value of the angle measured at this position is set as offset, so that the measured
							   angle after correction at phase A is 0.
							   Note that when using n pole pairs, the offset value can have n correct values. E.g.
							   with 3 pole pairs the correct offsets are 2/3 pi apart (i.e. 0, +2.09, -2.09). */
#define _SINE_SCALE -1.0f /* The scale parameter is determined by comparing the measured angle and the open loop
							angle in open loop mode. Both angles must have the same slope. The value is
							either 1 or -1. */

static float _measured_angle = 1000;

static float _prev_angle_rad = 0.0f;

typedef struct {
	float min;
	float _max;
	float _previous;
} zero_crossing_detector_t;

void zero_crossing_detector_init(zero_crossing_detector_t* instance, float min) {
	instance->min = min;
	instance->_max = 0;
	instance->_previous = 0;
}

uint8_t zero_crossing_detector_step(zero_crossing_detector_t* instance, float value) {
	uint8_t result = 0;

	if (fabsf(value) > instance->_max) instance->_max = fabsf(value);

	if ((value > 0 && instance->_previous <= 0) ||
	    (value < 0 && instance->_previous >= 0)) {
		if (instance->_max >= instance->min) {
			result = 1;
			instance->_max = 0;
		}
	}

	instance->_previous = value;

	return result;
}

// ====== PID =========

typedef struct {
	float kp;
	float ki;
	float kd;
	float sampling_time;
	float upper_limit;
	float lower_limit;
	float rate;
	float _previous_error;
	float _previous_integral;
	float _previous_output;
} pid_controller_t;

void pid_controller_init(pid_controller_t* instance) {
	instance->_previous_error = 0;
	instance->_previous_integral = 0;
	instance->_previous_output = 0;
}

float pid_controller_step(pid_controller_t* instance, float error) {
	float proportional = instance->kp * error;

	float integral = instance->_previous_integral + instance->ki * instance->sampling_time * 0.5f * (error + instance->_previous_error);
	if (integral > instance->upper_limit) integral = instance->upper_limit;
	else if (integral < instance->lower_limit) integral = instance->lower_limit;

	float derivative = instance->kd * (error - instance->_previous_error) / instance->sampling_time;

	float output = proportional + integral + derivative;
	if (output > instance->upper_limit) output = instance->upper_limit;
	else if (output < instance->lower_limit) output = instance->lower_limit;

	float rate = (output - instance->_previous_output) / instance->sampling_time;
	if (rate > instance->rate) output = instance->_previous_output + instance->rate * instance->sampling_time;
	else if (rate < -instance->rate) output = instance->_previous_output - instance->rate * instance->sampling_time;

	instance->_previous_error = error;
	instance->_previous_integral = integral;
	instance->_previous_output = output;

	return output;
}

// ====================

pid_controller_t _d_pid_controller;
pid_controller_t _q_pid_controller;

zero_crossing_detector_t _sine_zero_crossing_detector;
int32_t _previous_sine_zero_crossing_timer = 0;

float _previous_angle_for_rpm_calculation = 0;

struct {
	struct {
		float interval_us;
		uint8_t interlock_request;
		float rpm_request;
		uint8_t torque_request_valid;
		float torque_request;
		float sine;
		float cosine;
		float ia_raw;
		float ib_raw;
		float ic_raw;
		uint8_t commutation_type;
	} in;
	struct {
		uint8_t gate_driver_enable;
		float duty_cycle_a;
		float duty_cycle_b;
		float duty_cycle_c;
		float open_loop_angle;
		float magnetic_angle;
		float measured_angle;
		float measured_rpm;
		float ia;
		float ib;
		float ic;
		float iabc;
		float id_raw;
		float iq_raw;
		float id_filtered;
		float iq_filtered;
		float udout;
		float uqout;
	} out;
} asw;

float _magnetic_angles[100];
float _electric_angular_velocity_radps;

static void _step_encoder(void) {
	/* Normalize */
	float sine_normalized = ((asw.in.sine - _SINE_MIN) / (_SINE_MAX - _SINE_MIN)) * 2 - 1;
	float cosine_normalized = ((asw.in.cosine - _SINE_MIN) / (_SINE_MAX - _SINE_MIN)) * 2 - 1;

	float angle = atan2f(sine_normalized, cosine_normalized);
	angle = remainderf(angle * _SINE_SCALE + _SINE_OFFSET, 2 * PI);

	if (angle == angle) {
		if (_measured_angle > 100) _measured_angle = angle;
		_measured_angle = 0 * _measured_angle + 1 * angle;
		asw.out.measured_angle = _measured_angle;
	}

	/* Calculate magnetic angle. */
	float mag_angle_measured_rad = remainderf(asw.out.measured_angle * _POLE_PAIRS, 2 * PI);
	//if (mag_angle_rad < -PI) mag_angle_rad = PI + mag_angle_rad;
	//if (mag_angle_rad > PI) mag_angle_rad = mag_angle_rad - 2 * PI;
	asw.out.magnetic_angle = mag_angle_measured_rad;
	_magnetic_angles[scheduler0.cycle % 100] = asw.out.magnetic_angle;


	/* Calculate RPM. */
	if (zero_crossing_detector_step(&_sine_zero_crossing_detector, sine_normalized)) {
		float interval = (scheduler0.timer_100us - _previous_sine_zero_crossing_timer) / 10000.0f;
		_previous_sine_zero_crossing_timer = scheduler0.timer_100us;
		asw.out.measured_rpm = (60.0 / interval) / 2;
	}

	/* Second RPM measurement method. */
	if (scheduler0.cycle % 4 == 0) { /* Every 1 ms. For up to 5000 rpm. @todo Rework! */
		float angular_velocity_radps = remainderf(asw.out.measured_angle - _previous_angle_for_rpm_calculation, 2 * PI) / 0.001f;
		float angular_velocity_rps = angular_velocity_radps / (2.0f * PI);
		float angular_velocity_rpm = angular_velocity_rps * 60.0f;
		if (diagnostic0_database.ASW_RPM != diagnostic0_database.ASW_RPM) diagnostic0_database.ASW_RPM = 0; // @todo Remove
		diagnostic0_database.ASW_RPM = diagnostic0_database.ASW_RPM * 0.99f + angular_velocity_rpm * 0.01f;
		_previous_angle_for_rpm_calculation = asw.out.measured_angle;
		_electric_angular_velocity_radps = (diagnostic0_database.ASW_RPM / 60.0f) * 2.0f * PI * _POLE_PAIRS;
	}

	/* Calculate the BEMF voltage. */
	diagnostic0_database.ASW_Ubemf = diagnostic0_database.ASW_RPM / diagnostic0_database.ASW_Motor_KV;
}

static void _step_alpha_beta_currents(void){
    // calculate clarke transform
    float i_alpha, i_beta;
    if(asw.out.ic != asw.out.ic){
        // if only two measured currents
        i_alpha = asw.out.ia;
        i_beta = _1_SQRT3 * asw.out.ia + _2_SQRT3 * asw.out.ib;
    }else if(asw.out.ia != asw.out.ia){
        // if only two measured currents
        float a = -asw.out.ic - asw.out.ib;
        i_alpha = a;
        i_beta = _1_SQRT3 * a + _2_SQRT3 * asw.out.ib;
    }else if(asw.out.ib != asw.out.ib){
        // if only two measured currents
        float b = -asw.out.ia - asw.out.ic;
        i_alpha = asw.out.ia;
        i_beta = _1_SQRT3 * asw.out.ib + _2_SQRT3 * b;
    } else {
        // signal filtering using identity a + b + c = 0. Assumes measurement error is normally distributed.
        float mid = (1.f/3) * (asw.out.ia + asw.out.ib + asw.out.ic);
        float a = asw.out.ia - mid;
        float b = asw.out.ib - mid;
        i_alpha = a;
        i_beta = _1_SQRT3 * a + _2_SQRT3 * b;
    }

    diagnostic0_database.ASW_Currents_Ialpha = i_alpha;
    diagnostic0_database.ASW_Currents_Ibeta = i_beta;
}

static void _step_currents(void) {
	asw.out.ia = asw.in.ia_raw * _CURRENT_FACTOR_A + _CURRENT_OFFSET_A;
	asw.out.ib = asw.in.ib_raw * _CURRENT_FACTOR_B + _CURRENT_OFFSET_B;
	asw.out.ic = asw.in.ic_raw * _CURRENT_FACTOR_C + _CURRENT_OFFSET_C;

	//asw.out.ia = -asw.out.ia;
	//asw.out.ib = -asw.out.ib;
	//asw.out.ic = -asw.out.ic;

	/*float temp = asw.out.ib;
	asw.out.ib = asw.out.ic;
	asw.out.ic = temp;*/

	/* Sensor plausibilisation. */
	if (asw.out.ia > 200 || asw.out.ia < -200) asw.out.ia = NAN;
	if (asw.out.ib > 200 || asw.out.ib < -200) asw.out.ib = NAN;
	if (asw.out.ic > 200 || asw.out.ic < -200) asw.out.ic = NAN;

	asw.out.ic = NAN;

	/* Fill possible gaps. */
	if (asw.out.ia != asw.out.ia) asw.out.ia = -asw.out.ib - asw.out.ic;
	if (asw.out.ib != asw.out.ib) asw.out.ib = -asw.out.ia - asw.out.ic;
	if (asw.out.ic != asw.out.ic) asw.out.ic = -asw.out.ia - asw.out.ib;

	/* Calculate zero current. */
	asw.out.iabc = asw.out.ia + asw.out.ib + asw.out.ic;

	/* Calculate alpha and beta currents. */
	/*diagnostic0_database.ASW_Currents_Ialpha = 2.0f / 3.0f * (asw.out.ia - 0.5f * asw.out.ib - 0.5f * asw.out.ic);
	diagnostic0_database.ASW_Currents_Ibeta = 2.0f / 3.0f * (_SQRT3_2 * asw.out.ib - _SQRT3_2 * asw.out.ic);
	diagnostic0_database.ASW_Currents_Idc_Raw = sqrtf(diagnostic0_database.ASW_Currents_Ialpha * diagnostic0_database.ASW_Currents_Ialpha + diagnostic0_database.ASW_Currents_Ibeta * diagnostic0_database.ASW_Currents_Ibeta);
	if (diagnostic0_database.ASW_Currents_Idc_Raw == diagnostic0_database.ASW_Currents_Idc_Raw) {
		diagnostic0_database.ASW_Currents_Idc_Filtered = diagnostic0_database.ASW_Currents_Idc_Filtered * _IQD_LPF_ALPHA + diagnostic0_database.ASW_Currents_Idc_Raw * (1 - _IQD_LPF_ALPHA);
	}*/
	_step_alpha_beta_currents();

	/* Calculate I_d and I_q. */
	//float angle = asw.out.magnetic_angle - PI / 2; // @todo Is this correct?
	float angle = asw.out.magnetic_angle;
	//angle = _magnetic_angles[(scheduler0.cycle - 14) % 100];
	//float phi = atanf(diagnostic0_database.ASW_Motor_L / diagnostic0_database.ASW_Motor_R * _electric_angular_velocity_radps);
	//angle = angle - phi;
	asw.out.id_raw = (2.0 / 3.0) * (cosf(angle) * asw.out.ia +
									cosf(angle - 2.0 * PI / 3.0) * asw.out.ib + 
									cosf(angle - 4.0 * PI / 3.0) * asw.out.ic);
	asw.out.iq_raw = (2.0 / 3.0) * (-sinf(angle) * asw.out.ia -
									sinf(angle - 2.0 * PI / 3.0) * asw.out.ib - 
									sinf(angle - 4.0 * PI / 3.0) * asw.out.ic);
    //float ct = cosf(angle);
    //float st = sinf(angle);
    //_sincos(angle, &st, &ct);
    //asw.out.id_raw = diagnostic0_database.ASW_Currents_Ialpha * ct + diagnostic0_database.ASW_Currents_Ibeta * st;
    //asw.out.iq_raw = diagnostic0_database.ASW_Currents_Ibeta * ct - diagnostic0_database.ASW_Currents_Ialpha * st;

    /*float temp = asw.out.id_raw;
    asw.out.id_raw = asw.out.iq_raw;
    asw.out.iq_raw = temp;*/

	/* Filter I_d and I_q. */
	//if (asw.out.iabc < 10 && asw.out.iabc > -10) {
		if (asw.out.id_raw == asw.out.id_raw) asw.out.id_filtered = asw.out.id_filtered * _IQD_LPF_ALPHA + asw.out.id_raw * (1 - _IQD_LPF_ALPHA);
		if (asw.out.iq_raw == asw.out.iq_raw) asw.out.iq_filtered = asw.out.iq_filtered * _IQD_LPF_ALPHA + asw.out.iq_raw * (1 - _IQD_LPF_ALPHA);
	//}
}

static void _step_gate_driver(void) {
    float step_frequency_hz = 1000000.0 / asw.in.interval_us;

	float ud = diagnostic0_database.ASW_Ud;
	float uq = diagnostic0_database.ASW_Uq;

	asw.out.open_loop_angle = NAN;
	
	if (asw.in.interlock_request) {
	if (asw.in.commutation_type == 0 || asw.in.commutation_type == 1 || asw.in.commutation_type == 2) {
		float mag_angle_rad;
		if (asw.in.commutation_type == 1) { /* "Closed loop". */
			mag_angle_rad = asw.out.magnetic_angle;

			// Compensate delay
			mag_angle_rad += _electric_angular_velocity_radps * 0.00006f;

			/*if (diagnostic0_database.ASW_Iref == diagnostic0_database.ASW_Iref) {
				uq = (diagnostic0_database.ASW_Iref * diagnostic0_database.ASW_Motor_R + diagnostic0_database.ASW_Ubemf) / _DC_VOLTAGE;
			}

			if (asw.in.torque_request_valid) {
				ud = lut_lookup(&_ud_lut, asw.in.torque_request, diagnostic0_database.ASW_RPM) / _DC_VOLTAGE;
				uq = lut_lookup(&_uq_lut, asw.in.torque_request, diagnostic0_database.ASW_RPM) / _DC_VOLTAGE;
			}*/
		} else if (asw.in.commutation_type == 2) { /* Real closed loop. */
			mag_angle_rad = asw.out.magnetic_angle;

			// Compensate delay
			mag_angle_rad += _electric_angular_velocity_radps * 0.00006f; // + 1 cycle

			/* Set the parameters */
			_d_pid_controller.kp = diagnostic0_database.ASW_DQControl_Id_Kp;
			_d_pid_controller.ki = diagnostic0_database.ASW_DQControl_Id_Ki;
			_d_pid_controller.kd = diagnostic0_database.ASW_DQControl_Id_Kd;
			_d_pid_controller.sampling_time = _SAMPLING_TIME;
			_d_pid_controller.lower_limit = -diagnostic0_database.ASW_DQControl_Limit;
			_d_pid_controller.upper_limit = diagnostic0_database.ASW_DQControl_Limit;
			//_d_pid_controller.upper_limit = 0;
			_d_pid_controller.rate = diagnostic0_database.ASW_DQControl_Rate;

			_q_pid_controller.kp = diagnostic0_database.ASW_DQControl_Iq_Kp;
			_q_pid_controller.ki = diagnostic0_database.ASW_DQControl_Iq_Ki;
			_q_pid_controller.kd = diagnostic0_database.ASW_DQControl_Iq_Kd;
			_q_pid_controller.sampling_time = _SAMPLING_TIME;
			_q_pid_controller.lower_limit = -diagnostic0_database.ASW_DQControl_Limit;
			//_q_pid_controller.lower_limit = 0;
			_q_pid_controller.upper_limit = diagnostic0_database.ASW_DQControl_Limit;
			_q_pid_controller.rate = diagnostic0_database.ASW_DQControl_Rate;
			
			float id_reference;
			float iq_reference;

			if (asw.in.torque_request_valid == 0) {
				id_reference = lut_lookup(&_id_lut, 0, asw.in.torque_request);
				iq_reference = lut_lookup(&_iq_lut, 0, asw.in.torque_request);
			}

			if (diagnostic0_database.ASW_Iref == diagnostic0_database.ASW_Iref) {
				id_reference = 0;
				iq_reference = diagnostic0_database.ASW_Iref;
			}
						
			float id_error = id_reference - asw.out.id_filtered;
			float ud_volt = pid_controller_step(&_d_pid_controller, id_error);

			const float _L_Q = 0.00032f;
			//ud_volt = ud_volt - _electric_angular_velocity_radps * asw.out.iq_filtered * _L_Q;

			ud = ud_volt / _DC_VOLTAGE;

			float iq_error = iq_reference - asw.out.iq_filtered;
			float uq_volt = pid_controller_step(&_q_pid_controller, iq_error);

			const float _L_D = 0.00055f;
			const float _LAMBDA_PM = 0.038f;
			//uq_volt = uq_volt + _electric_angular_velocity_radps * (asw.out.id_filtered * _L_D + _LAMBDA_PM);

			uq = uq_volt / _DC_VOLTAGE;
		} else { /* "Open loop". */
			float rot_speed_request_radps = asw.in.rpm_request / 60.0 * 2.0 * PI;

			float angle_difference_per_step_rad = rot_speed_request_radps / step_frequency_hz;

			asw.out.open_loop_angle = _prev_angle_rad;
			float next_angle_rad = remainderf(_prev_angle_rad + angle_difference_per_step_rad, 2 * PI);
			//if (next_angle_rad < -PI) next_angle_rad = PI + next_angle_rad;
			//if (next_angle_rad > PI) next_angle_rad = next_angle_rad - 2 * PI;
			_prev_angle_rad = next_angle_rad;

			mag_angle_rad = remainderf(_prev_angle_rad * _POLE_PAIRS, 2 * PI);
		}

		//float u_a = uq * (-sinf(angle_rad) * 0.5 + 0.5);
		//float u_b = uq * (-sinf(angle_rad - 2.0 * PI / 3.0) * 0.5 + 0.5);
		//float u_c = uq * (-sinf(angle_rad - 4.0 * PI / 3.0) * 0.5 + 0.5);

		float amplitude = sqrtf(ud * ud + uq * uq);
		if (amplitude > 0.5f) {
			ud = ud / (amplitude / 0.5f);
			uq = uq / (amplitude / 0.5f);
			amplitude = 0.5f;
		}

		asw.out.udout = ud;
		asw.out.uqout = uq;

		/*float u_a = ud * cosf(mag_angle_rad) - uq * sinf(mag_angle_rad) + 0.5;
		float u_b = ud * cosf(mag_angle_rad - 2.0 * PI / 3.0) - uq * sinf(mag_angle_rad - 2.0 * PI / 3.0) + 0.5;
		float u_c = ud * cosf(mag_angle_rad - 4.0 * PI / 3.0) - uq * sinf(mag_angle_rad - 4.0 * PI / 3.0) + 0.5;*/

	      // Inverse park transform
		  float _ca = cosf(mag_angle_rad);
		  float _sa = sinf(mag_angle_rad);
		  float Ualpha =  _ca * ud - _sa * uq;  // -sin(angle) * Uq;
	      float Ubeta =  _sa * ud + _ca * uq;    //  cos(angle) * Uq;

	      // Clarke transform
	      float u_a = Ualpha;
	      float u_b = -0.5f * Ualpha + _SQRT3_2 * Ubeta;
	      float u_c = -0.5f * Ualpha - _SQRT3_2 * Ubeta;

	      //float min = u_a;
	      //if (u_b < min) min = u_b;
	      //if (u_c < min) min = u_c;
	      //u_a = u_a + 0.5;
	      //u_b = u_b + 0.5;
	      //u_c = u_c + 0.5;
	      u_a = u_a + amplitude;
	      u_b = u_b + amplitude;
	      u_c = u_c + amplitude;

		asw.out.duty_cycle_a = u_a;
		asw.out.duty_cycle_b = u_b;
		asw.out.duty_cycle_c = u_c;
	} else if (asw.in.commutation_type == 3) { /* Align to phase A. */
		asw.out.duty_cycle_a = uq;
		asw.out.duty_cycle_b = 0;
		asw.out.duty_cycle_c = 0;
	} else if (asw.in.commutation_type == 4) { /* Align to phase B. */
		asw.out.duty_cycle_a = 0;
		asw.out.duty_cycle_b = uq;
		asw.out.duty_cycle_c = 0;
	} else if (asw.in.commutation_type == 5) { /* Align to phase C. */
		asw.out.duty_cycle_a = 0;
		asw.out.duty_cycle_b = 0;
		asw.out.duty_cycle_c = uq;
	} else { /* All opened. */
		asw.out.duty_cycle_a = NAN;
		asw.out.duty_cycle_b = NAN;
		asw.out.duty_cycle_c = NAN;
	}
	} else {
		pid_controller_init(&_d_pid_controller);
		pid_controller_init(&_q_pid_controller);
		asw.out.duty_cycle_a = NAN;
		asw.out.duty_cycle_b = NAN;
		asw.out.duty_cycle_c = NAN;
	}

	asw.out.gate_driver_enable = asw.in.interlock_request;
}

int32_t asw_init(void) {
	asw.in.interval_us = NAN;
	asw.in.interlock_request = 0;
	asw.in.rpm_request = NAN;
	asw.in.torque_request_valid = 0;
	asw.in.torque_request = NAN;
	asw.in.sine = NAN;
	asw.in.cosine = NAN;
	asw.in.commutation_type = 0;

	asw.out.gate_driver_enable = 0;
	asw.out.duty_cycle_a = NAN;
	asw.out.duty_cycle_b = NAN;
	asw.out.duty_cycle_c = NAN;
	asw.out.measured_angle = NAN;

	asw.out.id_filtered = 0;
	asw.out.iq_filtered = 0;

	zero_crossing_detector_init(&_sine_zero_crossing_detector, 0.5f);

	pid_controller_init(&_d_pid_controller);
	_d_pid_controller.kp = 0.1;
	_d_pid_controller.ki = 1;
	_d_pid_controller.kd = 0;
	_d_pid_controller.sampling_time = _SAMPLING_TIME;
	_d_pid_controller.lower_limit = -0.5;
	_d_pid_controller.upper_limit = 0;
	_d_pid_controller.rate = 10;

	pid_controller_init(&_q_pid_controller);
	_q_pid_controller.kp = 0.1;
	_q_pid_controller.ki = 1;
	_q_pid_controller.kd = 0;
	_q_pid_controller.sampling_time = _SAMPLING_TIME;
	_q_pid_controller.lower_limit = -0.5;
	_q_pid_controller.upper_limit = 0.5;
	_q_pid_controller.rate = 10;

	return 0;
}

int32_t asw_deinit(void) {
	return 0;
}

int32_t asw_inner_step(void) {
	_step_encoder();

	_step_currents();

	_step_gate_driver();
}

int32_t asw_step(void) {
	//_step_encoder();

	//_step_currents();

	//_step_gate_driver();

	return 0;
}
