#include <Arduino.h>
#include "modules.h"
#include "_blink_modifier.h"
#include "_blink.h"


#ifdef BLINK_MODIFIER_IMPLEMENTATION
#error The .ino.h file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .h file instead?
#endif
#define BLINK_MODIFIER_IMPLEMENTATION



void BlinkModifier::setup()
{
  pinMode(BLINK_MODIFIER_BUTTON, INPUT_PULLUP);
  digitalWrite(BLINK_MODIFIER_BUTTON, HIGH);
  index = 0;
  Serial.print(F("Intervals: "));
  for (int i = 0; i < BLINK_MODIFIER_INTERVALS_N; i++) {
    if (i > 0) Serial.print(F(", "));
    Serial.print(intervals[i]);
  }
  Serial.println();
  blink->interval = intervals[0];
}


void BlinkModifier::loop()
{
  unsigned long millis_now = millis();
  bool button_pushed = !digitalRead(BLINK_MODIFIER_BUTTON);

  if (millis_now - last_press < BLINK_MODIFIER_DEADTIME) {
    return;
  }

  if (button_pushed && ! last_button_pushed) {
    index++;
    if (index >= BLINK_MODIFIER_INTERVALS_N) {
      index = 0;
    }
    blink->interval = intervals[ index ];
    Serial.print(F("Interval: "));
    Serial.print(blink->interval);
    Serial.print(F(" (index: "));
    Serial.print(index);
    Serial.println(F(")"));
	#ifdef BLINK_COUNTER
	Serial.print(F("Count: "));
	Serial.println(blink_counter->get->count);
  blink_counter->set->reset = true;
	#endif
  }
  last_button_pushed = button_pushed;
  last_press = millis_now;

}
