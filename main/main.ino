#include <Arduino.h>
#include "modules.h"

// modules:
#include "_blink.ino.h"
#include "_blink_modifier.ino.h"


void setup()
{
	uint8_t i;
	Serial.begin(9600);
	Serial.println("SETUP");
	for (i=0; i<ModulesRegistry::count; i++) {
		ModulesRegistry::modules[i]->setup();
	}
}


void loop()
{
	uint8_t i;
	for (i=0; i<ModulesRegistry::count; i++) {
		ModulesRegistry::modules[i]->loop();
	}
}
