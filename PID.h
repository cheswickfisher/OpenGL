#ifndef PID_H
#define PID_H
#include "Preferences.h"
namespace WIP_Polygon {
	class PID {
		public:
            float kp;
            float ki;
            float kd;
            float output;
            float prevError;
            float accumulatedError;

            PID();
            PID(float _kp, float _ki, float _kd);
            float UpdateController(float _error);
	};
}
#endif