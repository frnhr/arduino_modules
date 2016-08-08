#include <Arduino.h>
#include "modules.hpp"

#include "_blink_modifier.hpp"

#include "_blink.hpp"


#ifdef BLINK_MODIFIER_IMPLEMENTATION
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .h file instead?
#endif
#define BLINK_MODIFIER_IMPLEMENTATION



void BlinkModifier::setup()
{

  // TODO move this to protocol:
  Serial.print(F("Intervals: "));
  for (int i = 0; i < BLINK_MODIFIER_INTERVALS_N; i++) {
    if (i > 0) Serial.print(F(", "));
    Serial.print(intervals[i]);
  }
  Serial.println();
  Serial.println("index: ");
  Serial.println(index);

  // override default blink interval:
  // (for this to work, this module has to be included after blink module)
  blink->interval = intervals[index];
}


void BlinkModifier::loop()
{

  // handle next interval setter flag:
  if (setNextInterval) {
    // icrement the value:
    _index++;
    // make sure it doesn't overflow:
    if (_index >= BLINK_MODIFIER_INTERVALS_N) {
      _index = 0;
    }
    // clear the flag:
    setNextInterval = false;
  }

  // handle the interval setter:
  if (setIntervalTo != BLINK_MODIFIER_NULL) {
    // make sure value if valid:
    if ((setIntervalTo > 0) && (setIntervalTo < BLINK_MODIFIER_INTERVALS_N)) {
      // set the private member to givven value:
      _index = setIntervalTo;
    }
    // clear the setter:
    setIntervalTo = BLINK_MODIFIER_NULL;
  }

  // copy private value to publicaly accessable member:
  // this way we can make sure that "_index" can be changed only via
  // `setInvervalTo` member.
  index = _index;
}
