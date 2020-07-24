#include "util_motor.h"
#include "pin_define.h"
#include "util_timer.h"

volatile uint32_t motor_offset_right = MOTOR_OFFSET;
volatile uint32_t motor_offset_left = 0;

void motor_stop() {
    pwm_start(MOTOR_A_FORWARD, PWM_FREQUENCY, 0, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_B_FORWARD, PWM_FREQUENCY, 0, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_A_REVERSE, PWM_FREQUENCY, 0, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_B_REVERSE, PWM_FREQUENCY, 0, RESOLUTION_10B_COMPARE_FORMAT);
    analogWriteFrequency(TIMER_FREQUENCY);
    delay(10);
}

void motor_pwm_stop() {
    pwm_stop(MOTOR_A_FORWARD);
    pwm_stop(MOTOR_B_FORWARD);
    pwm_stop(MOTOR_A_REVERSE);
    pwm_stop(MOTOR_B_REVERSE);
    analogWriteFrequency(TIMER_FREQUENCY);
    delay(10);
}

// 0 < speed < 1024

void motor_run(uint32_t speed) {

    uint32_t right_speed = speed + motor_offset_right;
    if(speed + motor_offset_right > 1023) {
        right_speed = 1023;
    }

    pwm_start(MOTOR_A_FORWARD, PWM_FREQUENCY, speed + motor_offset_left, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_B_FORWARD, PWM_FREQUENCY, right_speed, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_A_REVERSE, PWM_FREQUENCY, 0, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_B_REVERSE, PWM_FREQUENCY, 0, RESOLUTION_10B_COMPARE_FORMAT);
    analogWriteFrequency(TIMER_FREQUENCY);
    delay(10);
}

void motor_reverse(uint32_t speed) {

    uint32_t right_speed = speed + motor_offset_right;
    if(speed + motor_offset_right > 1023) {
        right_speed = 1023;
    }

    pwm_start(MOTOR_A_FORWARD, PWM_FREQUENCY, 0, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_B_FORWARD, PWM_FREQUENCY, 0, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_A_REVERSE, PWM_FREQUENCY, speed + motor_offset_left, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_B_REVERSE, PWM_FREQUENCY, right_speed, RESOLUTION_10B_COMPARE_FORMAT);
    analogWriteFrequency(TIMER_FREQUENCY);
    delay(10);
}

void motor_rotate_right(uint32_t speed) {
    uint32_t right_speed = speed + motor_offset_right;
    if(speed + motor_offset_right > 1023) {
        right_speed = 1023;
    }

    pwm_start(MOTOR_A_FORWARD, PWM_FREQUENCY, speed, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_B_REVERSE, PWM_FREQUENCY, right_speed, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_A_REVERSE, PWM_FREQUENCY, 0, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_B_FORWARD, PWM_FREQUENCY, 0, RESOLUTION_10B_COMPARE_FORMAT);
    analogWriteFrequency(TIMER_FREQUENCY);
    delay(10);
}

void motor_rotate_left(uint32_t speed) {
    uint32_t right_speed = speed + motor_offset_right;
    if(speed + motor_offset_right > 1023) {
        right_speed = 1023;
    }

    pwm_start(MOTOR_A_REVERSE, PWM_FREQUENCY, speed, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_B_FORWARD, PWM_FREQUENCY, right_speed, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_A_FORWARD, PWM_FREQUENCY, 0, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_B_REVERSE, PWM_FREQUENCY, 0, RESOLUTION_10B_COMPARE_FORMAT);
    analogWriteFrequency(TIMER_FREQUENCY);
    delay(10);
}