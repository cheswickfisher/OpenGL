#ifndef PREFERENCES_H
#define PREFERENCES_H

const float SCREEN_WIDTH = 1360.0f;
const float SCREEN_HEIGHT = 768.0f;
const float a = SCREEN_WIDTH / SCREEN_HEIGHT;
const float fps = 100;
const float fixed_dt = 1 / fps;
extern float deltaTime;

//physics constraint vars
const float depen_mtp = 0.05f;
const int solver_iterations = 3;
const float e = 1.0f; //setting these as universal variables for now
const float angular_drag = 1.0f; //setting these as universal variables for now
#endif
