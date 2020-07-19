#include "util_timer.h"
#include "util_serial.h"

uint16_t stat_change_count = 0;
uint16_t state_count_record[NUM_STATE_RECORD] = {0};
uint8_t state_record[NUM_STATE_RECORD] = {0};
uint8_t distance_reading_record[NUM_STATE_RECORD] = {0};
uint8_t distance_target_record[NUM_STATE_RECORD] = {0};

void state_debug_record()
{
    state_count_record[stat_change_count] = stat_change_count;
    state_record[stat_change_count] = (uint8_t)state;
    distance_reading_record[stat_change_count] = (uint8_t)distance_reading;
    distance_target_record[stat_change_count] = (uint8_t)distance_target;
    stat_change_count++;
}

#if 0
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
#endif

String get_state_string(uint8_t state)
{
    if (state == (uint8_t)STATE_INIT) return "STATE_INIT";
    else if (state == (uint8_t)STATE_READING) return "STATE_READING";
    else if (state == (uint8_t)STATE_FORWARD_RUN) return "STATE_FORWARD_RUN";
    else if (state == (uint8_t)STATE_STOP) return "STATE_STOP";
    else if (state == (uint8_t)STATE_ROTATE_START_RIGHT) return "STATE_ROTATE_START_RIGHT";
    else if (state == (uint8_t)STATE_ROTATE_START_LEFT) return "STATE_ROTATE_START_LEFT";
    else if (state == (uint8_t)STATE_ROTATING) return "STATE_ROTATING";
    else if (state == (uint8_t)STATE_ROTATE_DONE) return "STATE_ROTATE_DONE";
    else if (state == (uint8_t)STATE_ROTATE_TUNE_DONE) return "STATE_ROTATE_TUNE_DONE";
    else if (state == (uint8_t)STATE_TAPE_DET) return "STATE_TAPE_DET";
    else if (state == (uint8_t)STATE_FOUND) return "STATE_FOUND";
    else if (state == (uint8_t)STATE_TUNE_START) return "STATE_TUNE_START";
    else if (state == (uint8_t)STATE_SERVO) return "STATE_SERVO_TEST";
    else if (state == (uint8_t)STATE_FULL_SEARCH_START) return "STATE_FULL_SEARCH_START";
    else if (state == (uint8_t)STATE_FULL_SEARCH_STEP_DONE) return "STATE_FULL_SEARCH_STEP_DONE";
    else if (state == (uint8_t)STATE_REVERSE_START) return "STATE_REVERSE_START";
    else if (state == (uint8_t)STATE_REVERSING) return "STATE_REVERSING";
    else if (state == (uint8_t)STATE_REVERSE_DONE) return "STATE_REVERSE_DONE";
    else if (state == (uint8_t)STATE_NULL) return "STATE_NULL";

    return "ERROR";
}

void state_debug_print()
{
    Serial.begin(115200);

    for (int i = 0; i < NUM_STATE_RECORD; i++) {
        Serial.print("index: ");
        Serial.print(state_count_record[i]);
        Serial.print(" state = ");
        Serial.print(get_state_string(state_record[i]));
        Serial.print(" distance_reading: ");
        Serial.print(distance_reading_record[i]);
        Serial.print(" distance_target: ");
        Serial.println(distance_target_record[i]);
    }

    Serial.end();
}

