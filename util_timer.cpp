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
volatile uint32_t full_search_count = 0;
volatile uint32_t full_search_count_max = 0;
volatile uint32_t read_count = 0;
volatile uint32_t sonic_measure_count_tune_done = 0;
volatile uint32_t reverse_count = 0;
volatile uint32_t reverse_count_done = 0;
volatile uint32_t rotate_count_small = ROTATE_COUNT_TUNE_SMALL;

// NOT using timer2
// timer1 stops the motor if sonic sees distance less than DISTANCE_MIN 
// if tape is detected go to state = STATE_TAPE_DET (except when its rotating)
void timer1_ISR(HardwareTimer * Timerx) {
#if 1
  count++;
  rotate_count++;
  reverse_count++;

  if(state != STATE_NULL && state != STATE_SERVO && state != STATE_INIT) {
    if ((distance_reading_instant < DISTANCE_MIN) && (read_count > NUM_READING)) {
      // state = STATE_NULL for debugging purposes.
      // Later implementation will have state should go to STATE_STOP, then use servos to
      // pick up and deposit can, and go back to STATE_INIT to repeat entire searching process.
      //state = STATE_NULL;
      state = STATE_SERVO;
    }
  }

  if (distance_reading_instant > DISTANCE_READ_TO_NULL) {
    state = STATE_NULL;
  }

#if 1
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

#endif
}

// not using this.
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

// averages the array of readings to find distance_reading
uint32_t average_distance(volatile uint32_t *arr)
{
  uint32_t sum = 0;
  for (int i = 0; i < NUM_READING; i++) {
    sum += arr[i];
  }

  return (uint32_t)((double)sum/(double)NUM_READING);
}

void timerSetup() {
  HardwareTimer *Timerx = new HardwareTimer(TIM1);
  Timerx->pause();
  Timerx->setOverflow(TIMER_PERIOD, MICROSEC_FORMAT);
  Timerx->refresh();
  Timerx->resume();

  Timerx = new HardwareTimer(TIM2);
  Timerx->pause();
  Timerx->setOverflow(TIMER_PERIOD, MICROSEC_FORMAT);
  Timerx->refresh();
  Timerx->resume();

  Timerx = new HardwareTimer(TIM3);
  Timerx->pause();
  Timerx->setOverflow(TIMER_PERIOD, MICROSEC_FORMAT);
  Timerx->refresh();
  Timerx->resume();

  Timerx = new HardwareTimer(TIM4);
  Timerx->pause();
  Timerx->setOverflow(TIMER_PERIOD, MICROSEC_FORMAT);
  Timerx->refresh();
  Timerx->resume();
  
#if 0
    for (int i = 1; i <= 4; i++) {
        HardwareTimer timer(TIM1);
        timer.pause();
        timer.setOverflow(TIMER_PERIOD, MICROSEC_FORMAT);
        timer.refresh();
        timer.resume();
    }
#endif
}
