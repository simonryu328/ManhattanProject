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
#endif

String get_state_string(uint8_t state)
{
    if (state == (uint8_t)STATE_INIT) return "STATE_INIT";
    else if (state == (uint8_t)STATE_READING) return "STATE_READING";
    else if (state == (uint8_t)STATE_FORWARD_RUN) return "STATE_FORWARD_RUN";
    else if (state == (uint8_t)STATE_ROTATE_START_RIGHT) return "STATE_ROTATE_START_RIGHT";
    else if (state == (uint8_t)STATE_ROTATE_START_LEFT) return "STATE_ROTATE_START_LEFT";
    else if (state == (uint8_t)STATE_ROTATING) return "STATE_ROTATING";
    else if (state == (uint8_t)STATE_ROTATE_DONE) return "STATE_ROTATE_DONE";
    else if (state == (uint8_t)STATE_ROTATE_TUNE_DONE) return "STATE_ROTATE_TUNE_DONE";
    else if (state == (uint8_t)STATE_TAPE_DET) return "STATE_TAPE_DET";
    else if (state == (uint8_t)STATE_FOUND) return "STATE_FOUND";
    else if (state == (uint8_t)STATE_TUNE_START) return "STATE_TUNE_START";
    else if (state == (uint8_t)STATE_SERVO_TEST) return "STATE_SERVO_TEST";
    else if (state == (uint8_t)STATE_FULL_SEARCH_START) return "STATE_FULL_SEARCH_START";
    else if (state == (uint8_t)STATE_FULL_SEARCH_STEP_DONE) return "STATE_FULL_SEARCH_STEP_DONE";
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

