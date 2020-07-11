#ifndef UTIL_MOTOR_H_
#define UTIL_MOTOR_H_

#include <Arduino.h>

// 350
// 200
#define PWM_FREQUENCY 1000
#define ROTATE_SPEED_MIN 800
#define RUN_FORWARD_SPEED 400
#define RUN_REVERSE_SPEED 200
//I ADDED MOTOR OFFSET TO THE RIGHT WHEEL BC IT WAS SLOWER DUE TO WEIGHT DISTRIBUTION ISSUE. JUST SET TO 0 IF U DONT NEED IT
#define MOTOR_OFFSET 50

// define functions
void motor_run(uint32_t speed);
void motor_reverse(uint32_t speed);
void motor_stop();
void motor_rotate_left(uint32_t speed);
void motor_rotate_right(uint32_t speed);
void motor_pwm_stop();

#endif