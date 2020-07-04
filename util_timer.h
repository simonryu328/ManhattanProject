#ifndef UTIL_TIMER_H_
#define UTIL_TIMER_H_

#include <Arduino.h>

#define TIMER_PERIOD 10
#define DISTANCE_MAX 100
#define DISTANCE_MIN 5
#define NUM_READING 10
#define DISTANCE_MARGIN 2 // 2cm distance margin
#define ROTATE_COUNT_90DEG 800
#define ROTATE_COUNT_60DEG 500
#define ROTATE_COUNT_30DEG 250
#define ROTATE_COUNT_10DEG 100
#define ROTATE_COUNT_5DEG 42

typedef enum {
  STATE_INIT = 11,
  STATE_READING,
  STATE_FORWARD_RUN,
  STATE_STOP,
  STATE_ROTATE_START_RIGHT,
  STATE_ROTATE_START_LEFT,
  STATE_ROTATING,
  STATE_ROTATE_DONE,
  STATE_ROTATE_TUNE_DONE,
  STATE_TAPE_DET,
  STATE_FOUND,
  STATE_TUNE_START,
  STATE_SERVO_TEST,
  STATE_NULL
} State_t;

void timer_init();
void timer1_ISR(HardwareTimer * Timerx);
void timer2_ISR(HardwareTimer * Timerx);
uint32_t average_distance(volatile uint32_t *arr);
void timer1_resume();
void timer1_pause();
void timer2_resume();
void timer2_pause();

extern volatile uint32_t count;
extern volatile uint32_t rotate_count;
extern volatile uint32_t tape_reading;
extern volatile uint32_t state;
extern volatile uint32_t rotate_count_done;
extern volatile uint32_t rotate_speed;
extern volatile uint32_t distance_reading;
extern volatile uint32_t distance_reading_instance[NUM_READING];
extern volatile uint32_t distance_reading_instant;
extern volatile uint32_t distance_target;
extern volatile uint32_t tune_flag;
extern volatile uint32_t read_count;

#endif
