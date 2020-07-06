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

  // sonic for tape sensor
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT_PULLDOWN);
  pinMode(TAPESENSOR, INPUT_PULLDOWN);
}

void loop() {

#if 1
  if (state != STATE_NULL) {
    distance_reading_instance[read_count % NUM_READING] = get_distance();
    distance_reading_instant = distance_reading_instance[read_count % NUM_READING];
    //lcd_print_str_number("main loop1", 1);
    distance_reading = average_distance(distance_reading_instance);
    //lcd_print_str_number("main loop2", 2);
    read_count++;
    //lcd_print_str_number("main loop3", distance_reading);
    //lcd_print_array(0, distance_reading_instance); 
  }
#endif
#if 1
  if (state == STATE_INIT)
  {
    motor_stop();
    lcd_print_str_number("STATE INIT", distance_reading);
    if (read_count > 100) {
      state_debug_record();
      state = STATE_FORWARD_RUN;
      //state = STATE_SERVO_TEST;
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
    
    motor_stop();
    rotate_count = 0;
    rotate_count_done = ROTATE_COUNT_180DEG;
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

    //lcd_print_str_number("STATE ROTATING", distance_reading);
    if (rotate_count > rotate_count_done) {
      if (tune_flag) {
        state_debug_record();
        state = STATE_ROTATE_TUNE_DONE;
      } else {
        state_debug_record();
        state = STATE_ROTATE_DONE;
      }
    }

  } else if (state == STATE_ROTATE_TUNE_DONE) {

    motor_stop();
    analogWriteFrequency(100000);
    delay(10);
    sonic_measure_count_tune_done++;

    if(sonic_measure_count_tune_done > NUM_READING) {
      lcd_print_str_num4("STATE TUNE STEP DONE", distance_reading, distance_target, tune_flag, distance_reading_instant);
      rotate_count = 0;
      if (distance_reading < distance_target + DISTANCE_MARGIN) {

        tune_flag = 0;
        distance_target = distance_reading;
        state_debug_record();
        state = STATE_FORWARD_RUN;

      } else {

        rotate_count = 0;
        rotate_count_done = ROTATE_COUNT_TUNE_LEFT;
        rotate_speed = ROTATE_SPEED_MIN;
        state_debug_record();
        state = STATE_ROTATE_START_LEFT;
        tune_flag++;
        //state = STATE_NULL;
      }
      sonic_measure_count_tune_done = 0;
    }

  } else if (state == STATE_ROTATE_DONE) {
    
    motor_stop();
    distance_target = DISTANCE_MAX;
    state_debug_record();
    state = STATE_TUNE_START;

  } else if (state == STATE_TUNE_START) {
    
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

    lcd_print_str_number("STATE STOP", distance_reading);
    motor_stop();
    distance_target = DISTANCE_MAX;

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





