#include <Arduino.h>
#include "modules.h"
#include "_blink.h"
#include "_blink_counter.h"


#ifdef BLINK_COUNTER_IMPLEMENTATION
#error The .ino.h file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .h file instead?
#endif
#define BLINK_COUNTER_IMPLEMENTATION



void BlinkCounter::setup()
{
}


void BlinkCounter::loop()
{
    bool current_state = digitalRead( blink->ledPin );
    if (current_state == HIGH && last_state != HIGH) {
        _count++;
        Serial.println(_count);
    }
    _get.count = _count;
    last_state = current_state;
}
