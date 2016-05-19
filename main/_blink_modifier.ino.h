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
  blink_modifier->index = 0;
  Serial.print(F("Intervals: "));
  for (int i = 0; i < BLINK_MODIFIER_INTERVALS_N; i++) {
    if (i > 0) Serial.print(F(", "));
    Serial.print(blink_modifier->intervals[i]);
  }
  Serial.println();
  blink->interval = blink_modifier->intervals[0];
}


void BlinkModifier::loop()
{
  unsigned long millis_now = millis();
  bool button_pushed = !digitalRead(BLINK_MODIFIER_BUTTON);

  if (millis_now - blink_modifier->last_press < BLINK_MODIFIER_DEADTIME) {
    return;
  }

  if (button_pushed && ! blink_modifier->button_pushed) {
    blink_modifier->index++;
    if (blink_modifier->index >= BLINK_MODIFIER_INTERVALS_N) {
      blink_modifier->index = 0;
    }
    blink->interval = blink_modifier->intervals[ blink_modifier->index ];
    Serial.print(F("Interval: "));
    Serial.print(blink->interval);
    Serial.print(F(" (index: "));
    Serial.print(blink_modifier->index);
    Serial.println(F(")"));
  }
  blink_modifier->button_pushed = button_pushed;
  blink_modifier->last_press = millis_now;

}
