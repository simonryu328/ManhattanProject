#include "util_sonic.h"

uint32_t get_distance (void)
{
  // local time measures the time that the echo pin stays high, which is later convered to local_distance_cm
	uint32_t local_time=0;
	
  // turn off TRIGGER pin
  digitalWrite(TRIGGERPIN, 0);
	delay_us(2);

	// TRIGGER pin sends a 10 us pulse then turns off
  digitalWrite(TRIGGERPIN, 1);
	delay_us(10);  // wait for 10 us
  digitalWrite(TRIGGERPIN, LOW);
  
	while (!digitalRead(ECHOPIN));  // wait for the ECHO pin to go high
	while (digitalRead(ECHOPIN))    // while the pin is high
  {
    local_time++;   // measure time for which the ECHO pin is high
    delay_us(1);
  }

  // this is the formula i got when converting the time to distance
  uint32_t local_distance_cm = local_time * 10 / 142;
	return local_distance_cm;
}

// delay in microseconds
void delay_us(uint32_t us)
{
  if (us != 0) {
    uint32_t start = getCurrentMicros();
    do {
      yield();
    } while (getCurrentMicros() - start < us);
  }
}