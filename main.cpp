#include <Arduino.h>
#include <Servo.h>
#include "util_lcd.h"
#include "util_sonic.h"
#include "util_timer.h"
#include "util_motor.h"
#include "pin_define.h"

#define PWM_FREQUENCY 1000

Servo servo;

void setup() {

  lcd_init();
  timer_init();

  #if 0
  pinMode(SERVOPIN, OUTPUT);
  servo.attach(SERVOPIN);
  #endif

  // sonic for tape sensor
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT_PULLDOWN);
  pinMode(TAPESENSOR, INPUT_PULLDOWN);

}

void loop() {

// testing servo
#if 0
  servo.write(0);
  lcd_print_number(-90);
  delay(2000);
  
  servo.write(45);
  lcd_print_number(-45);
  delay(2000);

  servo.write(90);
  lcd_print_number(0);
  delay(2000);
#endif

#if 0
  uint32_t distance_cm = get_distance();
  lcd_print_str_number("distance cm:", distance_cm);
  delay(10);
#endif

#if 0
  uint32_t pin_read = analogRead(V_3_3);
  lcd_print_str_number("Current voltage", (double)pin_read);
  delay(3000);
#endif

#if 0
  lcd_print_str_number("Tape Sensor: ", tape_reading);
  delay(300);
#endif

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
      //state = STATE_TUNE_START;
      state = STATE_SERVO_TEST;
    }

  } else if (state == STATE_FORWARD_RUN) {
    lcd_print_str_number("STATE RUN", distance_reading);
    motor_run(RUN_FORWARD_SPEED);

    if(distance_reading > distance_target + DISTANCE_MARGIN) {
      state = STATE_TUNE_START;
      //state = STATE_NULL;
    } else {
      distance_target = distance_reading;
      state = STATE_FORWARD_RUN;
    }

  } else if (state == STATE_TAPE_DET) {
    
    motor_stop();
    rotate_count = 0;
    rotate_count_done = ROTATE_COUNT_90DEG;
    rotate_speed = ROTATE_SPEED_MIN;
    state = STATE_ROTATE_START_RIGHT;
    lcd_print_str_number("STATE TAPE DET", distance_reading);

  } else if (state == STATE_ROTATE_START_RIGHT) {

    motor_rotate_right(rotate_speed);
    state = STATE_ROTATING;

  } else if (state == STATE_ROTATE_START_LEFT) {

    motor_rotate_left(rotate_speed);
    state = STATE_ROTATING;

  } else if (state == STATE_ROTATING) {

    //lcd_print_str_number("STATE ROTATING", distance_reading);
    if (rotate_count > rotate_count_done) {
      if (tune_flag) {
        state = STATE_ROTATE_TUNE_DONE;
      } else {
        state = STATE_ROTATE_DONE;
      }
    }

  } else if (state == STATE_ROTATE_TUNE_DONE) {
    
    rotate_count = 0;
    motor_stop();
    if (distance_reading < distance_target + DISTANCE_MARGIN) {
      tune_flag = 0;
      state = STATE_FORWARD_RUN;
    } else {
      rotate_count = 0;
      rotate_count_done = ROTATE_COUNT_10DEG;
      rotate_speed = ROTATE_SPEED_MIN;
      state = STATE_ROTATE_START_LEFT;
      tune_flag++;
      lcd_print_str_number("STATE TUNE STEP DONE", tune_flag);
      //state = STATE_NULL;
    }

  } else if (state == STATE_ROTATE_DONE) {
    
    motor_stop();
    state = STATE_FORWARD_RUN;

  } else if (state == STATE_TUNE_START) {
    
    motor_stop();
    lcd_print_str_number("STATE TUNE", distance_reading);
    rotate_count = 0;
    rotate_count_done = ROTATE_COUNT_60DEG;
    rotate_speed = ROTATE_SPEED_MIN;
    state = STATE_ROTATE_START_RIGHT;
    tune_flag = 1;

  } else if (state == STATE_FOUND) {

    lcd_print_str_number("STATE FOUND", distance_reading);
    distance_target = distance_reading;
    state = STATE_FORWARD_RUN;

  } else if (state == STATE_STOP) {

    lcd_print_str_number("STATE STOP", distance_reading);
    motor_stop();
    distance_reading = DISTANCE_MAX;

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
  }
  #endif
}





