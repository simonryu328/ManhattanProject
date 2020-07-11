#ifndef UTIL_SERVO_H_
#define UTIL_SERVO_H_

// gives delay to slow rotation speed..

// init angle < final angle
void servo_rotate_open(uint32_t pin, uint32_t init_angle, uint32_t final_angle, uint32_t delay_factor);
// init angle > final angle
void servo_rotate_close(uint32_t pin, uint32_t init_angle, uint32_t final_angle, uint32_t delay_factor);
// = servo.write
void servo_write(uint32_t pin, uint32_t angle);
#endif
