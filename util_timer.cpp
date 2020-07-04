#include "util_timer.h"
#include "pin_define.h"
#include "util_sonic.h"
#include "util_lcd.h"

volatile uint32_t count = 0;
volatile uint32_t rotate_count = 0;
volatile uint32_t rotate_count_done = 0;
volatile uint32_t tape_reading = 0;
volatile uint32_t distance_reading = 0;
volatile uint32_t distance_reading_instance[NUM_READING];
volatile uint32_t distance_reading_instant = DISTANCE_MAX;
volatile uint32_t state = STATE_INIT;
volatile uint32_t distance_target = DISTANCE_MAX;
volatile uint32_t rotate_speed;
volatile uint32_t tune_flag = 0;
volatile uint32_t read_count = 0;

void timer1_ISR(HardwareTimer * Timerx) {
#if 1
  count++;
  rotate_count++;

  if ((distance_reading_instant < DISTANCE_MIN) && (read_count > NUM_READING)) {
    state = STATE_STOP;
  }

  tape_reading = digitalRead(TAPESENSOR);
  if ((state != STATE_TAPE_DET) && 
    (state != STATE_ROTATE_START_RIGHT) && 
    (state != STATE_ROTATING)) {
    if (tape_reading){
      state = STATE_TAPE_DET;
    }
  } else {

  }
#endif
}

uint32_t timer2_count = 0;
void timer2_ISR(HardwareTimer * Timerx) {
#if 0
  timer2_count++;
  if ((state != STATE_TAPE_DET) && 
    (state != STATE_ROTATE_START_RIGHT) && 
    (state != STATE_ROTATING)) {
    if (tape_reading){
      state = STATE_TAPE_DET;
    }
  } else {

  }
#endif
}

void timer_init() {

    #if 1
    HardwareTimer *Timerx1 = new HardwareTimer(TIM1);
    Timerx1->setMode(1, TIMER_OUTPUT_COMPARE);
    Timerx1->setOverflow(TIMER_PERIOD, MICROSEC_FORMAT);
    Timerx1->attachInterrupt(1, timer1_ISR);
    Timerx1->resume();
    #endif

    #if 0
    HardwareTimer *Timer2 = new HardwareTimer(TIM2);
    Timer2->setMode(1, TIMER_OUTPUT_COMPARE);
    Timer2->setOverflow(TIMER_PERIOD, MICROSEC_FORMAT);
    Timer2->attachInterrupt(1, timer2_ISR);
    Timer2->resume();
    #endif

}

void timer1_pause()
{
  HardwareTimer *Timer1 = new HardwareTimer(TIM1);
  Timer1->pause();
}

void timer1_resume()
{
  HardwareTimer *Timer1 = new HardwareTimer(TIM1);
  Timer1->resume();
}

void timer2_pause()
{
  HardwareTimer *Timer2 = new HardwareTimer(TIM2);
  Timer2->pause();
}

void timer2_resume()
{
  HardwareTimer *Timer2 = new HardwareTimer(TIM2);
  Timer2->resume();
}

uint32_t average_distance(volatile uint32_t *arr)
{
  uint32_t sum = 0;
  for (int i = 0; i < NUM_READING; i++) {
    sum += arr[i];
  }

  return (uint32_t)((double)sum/(double)NUM_READING);
}