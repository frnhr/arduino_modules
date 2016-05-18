#include <Arduino.h>
#include "modules.h"
#include "_blink.h"

#ifdef BLINK_IMPLEMENTATION
	#error The .ino.h file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .h file instead?
#endif
#define BLINK_IMPLEMENTATION


Blink* blink = (Blink*) ModulesRegistry::add(new Blink());


#define BLINK_LED 13


void Blink::setup()
{
	blink->interval = 1000;
	pinMode(BLINK_LED, OUTPUT);
}


void Blink::loop()
{
	unsigned long millis_now = millis();
	// Is it yet time to switch LED state?
	if (millis_now - blink->last_millis < blink->interval) {
		return;
	}
	// toggle the LED:
	digitalWrite( BLINK_LED, !digitalRead(BLINK_LED) );
	// remember the time, for future loops:
	blink->last_millis = millis_now;
}
