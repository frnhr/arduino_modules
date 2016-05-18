#include <Arduino.h>
#include "modules.h"


#ifndef BLINK
#define BLINK


class Blink: public Module
{
	public:
		unsigned int interval;
		unsigned int last_millis;
		void setup();
		void loop();
};


#endif
