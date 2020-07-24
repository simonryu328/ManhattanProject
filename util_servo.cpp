#include "pin_define.h"
#include <Servo.h>
#include "util_lcd.h"
#include "util_servo.h"

Servo servo_sweep;

void servo_rotate_open(uint32_t pin, uint32_t init_angle, uint32_t final_angle, uint32_t delay_factor) {
    servo_sweep.detach();
    servo_sweep.attach(pin);
    
    for(uint32_t i = init_angle; i < final_angle; i++) {
        servo_sweep.write(i);
        delay(delay_factor);
    }
    servo_sweep.detach();
}

void servo_rotate_close(uint32_t pin, uint32_t init_angle, uint32_t final_angle, uint32_t delay_factor) {
    servo_sweep.detach();
    servo_sweep.attach(pin);
    
    for(uint32_t i = init_angle; i > final_angle; i--) {
        servo_sweep.write(i);
        delay(delay_factor);
    }
    servo_sweep.detach();
}

void servo_write(uint32_t pin, uint32_t angle) {
    servo_sweep.detach();
    servo_sweep.attach(pin);
    servo_sweep.write(angle);
    servo_sweep.detach();
}

void servo_sweep_scoop() {
    servo_rotate_open(SERVOPIN_L, 90, 160, 20);
    delay(1000);
    servo_rotate_close(SERVOPIN, 135, 0, 6);
    delay(1000);
    servo_rotate_open(SERVOPIN, 0, 135, 6);
    delay(1000);
    servo_rotate_close(SERVOPIN_L, 160, 30, 10);
}