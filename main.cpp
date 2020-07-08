#include <Arduino.h>
#include <Servo.h>
#include "util_lcd.h"
#include "util_sonic.h"
#include "util_timer.h"
#include "util_motor.h"
#include "pin_define.h"
#include "util_serial.h"

Servo servo;

void setup() {
  lcd_init();
  timer_init();
  // sonic & tape sensor
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT_PULLDOWN);
  pinMode(TAPESENSOR, INPUT_PULLDOWN);
}
// distance_target is DISTANCE_MAX in the beginning
void loop() {
#if 1
  // distance_reading_instance: array containing the current distance reading and previous 9 readings
  // distance_reading: average of the array
  // read_count: needs to do 100 readings before any state is initiated
  // read distance only in STATE_FORWARD_RUN, ROTATE TUNE DONE, STATE_INIT AND FULL SEARCH STEP DONE
  if (state == STATE_FORWARD_RUN || state == STATE_ROTATE_TUNE_DONE || state == STATE_FULL_SEARCH_STEP_DONE || state == STATE_INIT) {
    distance_reading_instance[read_count % NUM_READING] = get_distance();
    distance_reading_instant = distance_reading_instance[read_count % NUM_READING];
    distance_reading = average_distance(distance_reading_instance);
    read_count++;
  }
#endif
#if 1
  if (state == STATE_INIT)
  {
    motor_stop();
    lcd_print_str_number("STATE INIT", distance_reading);
    //do 100 readings before moving robot
    if (read_count > 100) {
      state_debug_record();
      state = STATE_FULL_SEARCH_START;
      // state = STATE_SERVO_TEST;
    }

  } else if (state == STATE_FORWARD_RUN) {
    lcd_print_str_num4("STATE RUN", distance_reading, distance_target, 0, distance_reading_instant);
    motor_run(RUN_FORWARD_SPEED);
    if(distance_reading > distance_target + DISTANCE_MARGIN) {
      state_debug_record();
      state = STATE_TUNE_START;
      //state = STATE_NULL;
    } else {
      if(distance_reading < distance_target) {
        distance_target = distance_reading;
      }
      state = STATE_FORWARD_RUN;
    }

  } else if (state == STATE_TAPE_DET) {
    // if tape is detected the robot will rotate right by about 90 deg, then go to FULL_SEARCH_START
    motor_stop();
    rotate_count = 0;
    rotate_count_done = ROTATE_COUNT_90DEG;
    rotate_speed = ROTATE_SPEED_MIN;
    state_debug_record();
    state = STATE_ROTATE_START_RIGHT;
    lcd_print_str_number("STATE TAPE DET", distance_reading);

  } else if (state == STATE_ROTATE_START_RIGHT) {

    motor_rotate_right(rotate_speed);
    state_debug_record();
    state = STATE_ROTATING;

  } else if (state == STATE_ROTATE_START_LEFT) {

    motor_rotate_left(rotate_speed);
    state_debug_record();
    state = STATE_ROTATING;

  } else if (state == STATE_ROTATING) {

    lcd_print_str_number("STATE ROTATING", distance_reading);
    if (rotate_count > rotate_count_done) {
      if (tune_flag) {
        state_debug_record();
        state = STATE_ROTATE_TUNE_DONE;
      } else if (full_search_count) { 
        state_debug_record();
        state = STATE_FULL_SEARCH_STEP_DONE;
        } else {
        state_debug_record();
        state = STATE_ROTATE_DONE;
      }
    }

  } else if (state == STATE_ROTATE_TUNE_DONE) {

    motor_stop();
    // this is needed to set timer to its frequency
    analogWriteFrequency(TIMER_FREQUENCY);
    delay(10);
    sonic_measure_count_tune_done++;
    // loop wait untils sonic takes 10 readings when stationary
    if(sonic_measure_count_tune_done > NUM_READING) {
      lcd_print_str_num4("STATE TUNE STEP DONE", distance_reading, distance_target, tune_flag, distance_reading_instant);
      rotate_count = 0;
      if (distance_reading < distance_target + DISTANCE_MARGIN_TUNE) {

        tune_flag = 0;
        distance_target = distance_reading;
        state_debug_record();
        state = STATE_FORWARD_RUN;

      } else {
        #if 1
        rotate_count = 0;
        rotate_count_done = ROTATE_COUNT_TUNE_LEFT;
        rotate_speed = ROTATE_SPEED_MIN;
        state_debug_record();
        #endif
        state = STATE_ROTATE_START_LEFT;
        tune_flag++;
        //state = STATE_NULL;
      }
      sonic_measure_count_tune_done = 0;
    }

  } else if (state == STATE_ROTATE_DONE) {
    // this state is when the robot finishes rotating right after detecting a tape.
    // After rotatation, the state changes to STATE_FULL_SEARCH_START
    motor_stop();
    distance_target = DISTANCE_MAX;
    state_debug_record();
    state = STATE_FULL_SEARCH_START;

  } else if (state == STATE_TUNE_START) {
    // turns tune flag on, first will rotate right, and continuously rotate left in small steps, stopping after each step and searching for a can distance <= distance_target
    motor_stop();
    lcd_print_str_num4("STATE TUNE START", distance_reading, distance_target, 0, 0);
    rotate_count = 0;
    sonic_measure_count_tune_done = 0;
    rotate_count_done = ROTATE_COUNT_TUNE_RIGHT;
    rotate_speed = ROTATE_SPEED_MIN;
    state_debug_record();
    state = STATE_ROTATE_START_RIGHT;
    tune_flag = 1;

  } else if (state == STATE_STOP) {
    // robot has found a can. It should now use two servos to sweep the can and rotate the platform.
    lcd_print_str_number("STATE STOP", distance_reading);
    motor_stop();
    state = STATE_SERVO_TEST;
    // distance_target = DISTANCE_MAX;

  } else if (state == STATE_FULL_SEARCH_START) {
    // robot rotates right in FULL_SEARCH_COUNT_MAX (set in 10) steps, and finds the minimum distance
    // from all readings and set that as distance_target. Then the robot will rotate left in 
    // small steps (FINE_TUNE), finding distance_target again. See STATE_FULL_SEARCH_STEP_DONE for this.
    motor_stop();
    full_search_count++;
    sonic_measure_count_tune_done = 0;
    rotate_count = 0;
    rotate_count_done = ROTATE_COUNT_TUNE_SMALL;
    rotate_speed = ROTATE_SPEED_MIN;
    state_debug_record();
    state = STATE_ROTATE_START_RIGHT;

  } else if (state == STATE_FULL_SEARCH_STEP_DONE) {
    
    motor_stop();
    analogWriteFrequency(TIMER_FREQUENCY);
    delay(10);
    sonic_measure_count_tune_done++;

     if(sonic_measure_count_tune_done > NUM_READING) {
       lcd_print_str_num4("STATE SEARCH STEP DONE", distance_reading, distance_target, full_search_count, distance_reading_instant);
       if(full_search_count < FULL_SEARCH_COUNT_MAX) {
        if(distance_reading < distance_target) {
          distance_target = distance_reading;
        }
        state = STATE_FULL_SEARCH_START;
       } else {
         state = STATE_ROTATE_TUNE_DONE;
         full_search_count = 0;
       }
      sonic_measure_count_tune_done = 0;
    }

  } else if (state == STATE_SERVO_TEST) {
    // servo test
    servo.detach();
    servo.attach(SERVOPIN);
    
    servo.write(0);
    lcd_print_number(0);
    delay(2000);
    
    servo.write(45);
    lcd_print_number(45);
    delay(2000);

    servo.write(90);
    lcd_print_number(90);
    delay(2000);

    servo.detach();
    servo.attach(SERVOPIN_L);
    
    servo.write(0);
    lcd_print_number(0);
    delay(2000);
    
    servo.write(45);
    lcd_print_number(45);
    delay(2000);

    servo.write(90);
    lcd_print_number(90);
    delay(2000);

  } else if (state == STATE_NULL) {
    // for debugging
    motor_stop();
    lcd_print_str_number("STATE NULL", distance_reading);
    delay(1000);
    lcd_print_str_number("dt", distance_target);
    delay(1000);
    lcd_print_array(0, distance_reading_instance);
    delay(1000);
    lcd_print_str_number("count", read_count);
    delay(1000);

    state_debug_print();

  }
  #endif
}





