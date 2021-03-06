#ifndef UTIL_TIMER_H_
#define UTIL_TIMER_H_

#include <Arduino.h>
// define constants that are used by the timer. some other stuff are also here like full_search_count, distance
#define TIMER_PERIOD 10
#define DISTANCE_MAX 300
#define DISTANCE_MIN 5
#define NUM_READING 2
#define DISTANCE_MARGIN 4 // 2cm distance margin
#define DISTANCE_MARGIN_TUNE 3
#define ROTATE_COUNT_90DEG 800
#define ROTATE_COUNT_120DEG 1000
#define ROTATE_COUNT_180DEG 2000
#define ROTATE_COUNT_60DEG 500
#define ROTATE_COUNT_30DEG 250
#define ROTATE_COUNT_10DEG 100
#define ROTATE_COUNT_5DEG 42
#define ROTATE_COUNT_TUNE_RIGHT 150
#define ROTATE_COUNT_TUNE_LEFT 90
#define ROTATE_COUNT_TUNE_SMALL 120
#define ROTATE_COUNT_TUNE_MED 160
#define REVERSE_COUNT 300
#define COUNT_DET_FAR 0
#define COUNT_DET_CLOSE 4
#define COUNT_DET_MID 2
#define DISTANCE_CLOSE 30
#define DISTANCE_FAR 60
#define FULL_SEARCH_COUNT_MAX_INIT 15
#define FULL_SEARCH_COUNT_MAX_NEXT 15
#define TIMER_FREQUENCY (1000000 / TIMER_PERIOD)
#define DISTANCE_READ_TO_NULL 1300

typedef enum {
  STATE_INIT = 0,
  STATE_READING, //not used currently, can delete
  STATE_FORWARD_RUN, //reads distance reading and STATE_TUNE_START if off course
  STATE_STOP, // robot has successfully travelled to the can
  STATE_ROTATE_START_RIGHT,
  STATE_ROTATE_START_LEFT,
  STATE_ROTATING, //use rotate_count to control time of rotation
  STATE_ROTATE_DONE, // this is when the robot has detected a tape, and finihsed rotation
  STATE_ROTATE_TUNE_DONE, // rotate in small steps to find can
  STATE_TAPE_DET, 
  STATE_FOUND, //not used
  STATE_TUNE_START, 
  STATE_SERVO,
  STATE_FULL_SEARCH_START,
  STATE_FULL_SEARCH_STEP_DONE,
  STATE_REVERSE_START,
  STATE_REVERSING,
  STATE_REVERSE_DONE,
  STATE_NULL // turns off motor, displays numbers for debugging
} State_t;

void timer_init();
void timer1_ISR(HardwareTimer * Timerx);
void timer2_ISR(HardwareTimer * Timerx);
uint32_t average_distance(volatile uint32_t *arr);
void timer1_resume();
void timer1_pause();
void timer2_resume();
void timer2_pause();
void timerSetup();

extern volatile uint32_t count;
extern volatile uint32_t rotate_count;
extern volatile uint32_t tape_reading;
extern volatile uint32_t state;
extern volatile uint32_t rotate_count_done;
extern volatile uint32_t rotate_speed;
extern volatile uint32_t sonic_measure_count_tune_done;
extern volatile uint32_t distance_reading;
extern volatile uint32_t distance_reading_instance[NUM_READING];
extern volatile uint32_t distance_reading_instant;
extern volatile uint32_t distance_target;
extern volatile uint32_t tune_flag;
extern volatile uint32_t read_count;
extern volatile uint32_t full_search_count;
extern volatile uint32_t full_search_count_max;
extern volatile uint32_t reverse_count;
extern volatile uint32_t reverse_count_done;
extern volatile uint32_t rotate_count_small;

#endif
