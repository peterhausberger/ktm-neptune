#define PI 3.14159265358979323846f

#define _SQRT3_2 0.86602540378f

#define _POLE_PAIRS 3
#define _MAX_TORQUE_NM 10.0f

#define _CURRENT_OFFSET_A (-340.0f - 0.17f)
#define _CURRENT_FACTOR_A 680.0f
#define _CURRENT_OFFSET_B (-340.0f - 0.67f)
#define _CURRENT_FACTOR_B 680.0f
#define _CURRENT_OFFSET_C (-338.0f + 0.32f)
#define _CURRENT_FACTOR_C 680.0f

#define _IQD_LPF_TF 0.5f // 0.005f
#define _SAMPLING_TIME 0.0005f
#define _IQD_LPF_ALPHA (_IQD_LPF_TF / (_IQD_LPF_TF + _SAMPLING_TIME))

#define _SINE_MIN 0.15f
#define _SINE_MAX 0.7f

//#define _SINE_OFFSET (0.25f - PI / 2)
#define _SINE_OFFSET -1.23f /* The offset parameter is determined by aligning the motor to phase A. The negative
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
	float limit;
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
	if (integral > instance->limit) integral = instance->limit;
	else if (integral < -instance->limit) integral = -instance->limit;

	float derivative = instance->kd * (error - instance->_previous_error) / instance->sampling_time;

	float output = proportional + integral + derivative;
	if (output > instance->limit) output = instance->limit;
	else if (output < -instance->limit) output = -instance->limit;

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

zero_crossing_detector_t _angle_zero_crossing_detector;
int32_t _previous_angle_zero_crossing_timer = 0;

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
		float ud;
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

static void _step_encoder(void) {
	/* Normalize */
	float sine_normalized = ((asw.in.sine - _SINE_MIN) / (_SINE_MAX - _SINE_MIN)) * 2 - 1;
	float cosine_normalized = ((asw.in.cosine - _SINE_MIN) / (_SINE_MAX - _SINE_MIN)) * 2 - 1;

	float angle = atan2(sine_normalized, cosine_normalized);
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

	/* Calculate RPM. */
	if (zero_crossing_detector_step(&_angle_zero_crossing_detector, _measured_angle)) {
		float interval = (scheduler0.timer_100us - _previous_angle_zero_crossing_timer) / 10000.0f;
		_previous_angle_zero_crossing_timer = scheduler0.timer_100us;
		asw.out.measured_rpm = (60.0 / interval) / 2;
	}
}

static void _step_currents(void) {
	asw.out.ia = asw.in.ia_raw * _CURRENT_FACTOR_A + _CURRENT_OFFSET_A;
	asw.out.ib = asw.in.ib_raw * _CURRENT_FACTOR_B + _CURRENT_OFFSET_B;
	asw.out.ic = asw.in.ic_raw * _CURRENT_FACTOR_C + _CURRENT_OFFSET_C;

	/* Sensor plausibilisation. */
	if (asw.out.ia > 300 || asw.out.ia < -300) asw.out.ia = NAN;
	if (asw.out.ib > 300 || asw.out.ib < -300) asw.out.ib = NAN;
	if (asw.out.ic > 300 || asw.out.ic < -300) asw.out.ic = NAN;

	/* Fill possible gaps. */
	if (asw.out.ia != asw.out.ia) asw.out.ia = -asw.out.ib - asw.out.ic;
	if (asw.out.ib != asw.out.ib) asw.out.ib = -asw.out.ia - asw.out.ic;
	if (asw.out.ic != asw.out.ic) asw.out.ic = -asw.out.ia - asw.out.ib;

	/* Calculate zero current. */
	asw.out.iabc = asw.out.ia + asw.out.ib + asw.out.ic;
	
	/* Calculate I_d and I_q. */
	asw.out.id_raw = (2.0 / 3.0) * (cosf(asw.out.magnetic_angle) * asw.out.ia + 
										cosf(asw.out.magnetic_angle - 2.0 * PI / 3.0) * asw.out.ib + 
										cosf(asw.out.magnetic_angle - 4.0 * PI / 3.0) * asw.out.ic);
	asw.out.iq_raw = (2.0 / 3.0) * (-sinf(asw.out.magnetic_angle) * asw.out.ia - 
										sinf(asw.out.magnetic_angle - 2.0 * PI / 3.0) * asw.out.ib - 
										sinf(asw.out.magnetic_angle - 4.0 * PI / 3.0) * asw.out.ic);

	/* Filter I_d and I_q. */
	if (asw.out.iabc < 10 && asw.out.iabc > -10) {
		if (asw.out.id_raw == asw.out.id_raw) asw.out.id_filtered = asw.out.id_filtered * _IQD_LPF_ALPHA + asw.out.id_raw * (1 - _IQD_LPF_ALPHA);
		if (asw.out.iq_raw == asw.out.iq_raw) asw.out.iq_filtered = asw.out.iq_filtered * _IQD_LPF_ALPHA + asw.out.iq_raw * (1 - _IQD_LPF_ALPHA);
	}
}

static void _step_gate_driver(void) {
    float step_frequency_hz = 1000000.0 / asw.in.interval_us;

	float ud = asw.in.ud;
	float uq = asw.in.torque_request / _MAX_TORQUE_NM;

	asw.out.open_loop_angle = NAN;
	
	if (asw.in.interlock_request) {
	if (asw.in.commutation_type == 0 || asw.in.commutation_type == 1 || asw.in.commutation_type == 2) {
		float mag_angle_rad;
		if (asw.in.commutation_type == 1) { /* "Closed loop". */
			mag_angle_rad = asw.out.magnetic_angle;
		} else if (asw.in.commutation_type == 2) { /* Real closed loop. */
			mag_angle_rad = asw.out.magnetic_angle;

			float id_reference = 0;
			float id_error = id_reference - asw.out.id_filtered;
			ud = pid_controller_step(&_d_pid_controller, id_error);

			float iq_reference = asw.in.torque_request;
			float iq_error = iq_reference - asw.out.iq_filtered;
			uq = pid_controller_step(&_q_pid_controller, iq_error);
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

		asw.out.udout = ud;
		asw.out.uqout = uq;

		float u_a = ud * cosf(mag_angle_rad) - uq * sinf(mag_angle_rad) + 0.5;
		float u_b = ud * cosf(mag_angle_rad - 2.0 * PI / 3.0) - uq * sinf(mag_angle_rad - 2.0 * PI / 3.0) + 0.5;
		float u_c = ud * cosf(mag_angle_rad - 4.0 * PI / 3.0) - uq * sinf(mag_angle_rad - 4.0 * PI / 3.0) + 0.5;

		// Inverse park transform
		//float Ualpha = -sinf(mag_angle_rad) * uq;  // -sin(angle) * Uq;
		//float Ubeta = cosf(mag_angle_rad) * uq;    //  cos(angle) * Uq;

		// Inverse Clarke transform
		//float u_a = (Ualpha + uq) * 0.5;
		//float u_b = (-0.5 * Ualpha + _SQRT3_2 * Ubeta + uq) * 0.5;
		//float u_c = (-0.5 * Ualpha - _SQRT3_2 * Ubeta + uq) * 0.5;

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

	zero_crossing_detector_init(&_angle_zero_crossing_detector, PI / 2);

	pid_controller_init(&_d_pid_controller);
	_d_pid_controller.kp = 0.1;
	_d_pid_controller.ki = 1;
	_d_pid_controller.kd = 0;
	_d_pid_controller.sampling_time = _SAMPLING_TIME;
	_d_pid_controller.limit = 0.2;
	_d_pid_controller.rate = 10;

	pid_controller_init(&_q_pid_controller);
	_q_pid_controller.kp = 0.1;
	_q_pid_controller.ki = 1;
	_q_pid_controller.kd = 0;
	_q_pid_controller.sampling_time = _SAMPLING_TIME;
	_q_pid_controller.limit = 0.2;
	_q_pid_controller.rate = 10;

	return 0;
}

int32_t asw_deinit(void) {
	return 0;
}

int32_t asw_step(void) {
	_step_encoder();

	_step_currents();

	_step_gate_driver();

	return 0;
}
