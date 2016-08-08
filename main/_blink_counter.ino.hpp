#include <Arduino.h>
#include "modules.hpp"

#include "_blink_counter.hpp"

#ifdef BLINK_COUNTER_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .h file instead?
#endif
#define BLINK_COUNTER_INO_HPP

// dependences on other modules:
#include "_blink.hpp"


// implementation:


void BlinkCounter::setup()
{}


void BlinkCounter::loop()
{
    // read current LED state:
    bool currentState = digitalRead( blink->ledPin );

    // handle the input flag for reset:
    if (setReset) {
      // reset the counter:
      count = 0;
      // clear the flag:
      setReset = false;
    }

    // count the blinks:
    if (currentState == HIGH && lastState != HIGH) {
        count++;
    }

    // remember current state for later loops:
    lastState = currentState;
}
