#include "PID.h"

namespace WIP_Polygon {
	PID::PID() : 
		kp{ 1.0f }, ki{0.0f}, kd{0.0f}, output{0.0f}, prevError{0.0f}, accumulatedError{0.0f}
	{
	}
	PID::PID(float _kp, float _ki, float _kd) :
		kp{ _kp }, ki{ _ki }, kd{ _kd },
		output{ 0.0f }, prevError{0.0f}, accumulatedError{0.0f}
	{
	}
	float PID::UpdateController(float _error) {
		output = kp * _error + kd * (_error - prevError) / fixed_dt + ki * accumulatedError;
		prevError = _error;
		accumulatedError += _error * fixed_dt;
		return output;
	}
}