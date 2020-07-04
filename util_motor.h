#ifndef UTIL_MOTOR_H_
#define UTIL_MOTOR_H_

#include <Arduino.h>

#define ROTATE_SPEED_MIN 200
#define RUN_FORWARD_SPEED 200
#define MOTOR_OFFSET 40

// define functions
void motor_run(uint32_t speed);
void motor_reverse(uint32_t speed);
void motor_stop();
void motor_rotate_left(uint32_t speed);
void motor_rotate_right(uint32_t speed);
void motor_pwm_stop();

#endif