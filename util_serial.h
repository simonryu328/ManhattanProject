#ifndef UTIL_SERIAL_H_
#define UTIL_SERIAL_H_

#define NUM_STATE_RECORD 128
// just for debugging purposes. Download PuTTY if you want to use it
void state_debug_record();
void state_debug_print();
void state_debug_print_instance();
void state_debug_print_i(String s, uint32_t a, uint32_t b, uint32_t c, uint32_t d);
#endif
