#include <Arduino.h>
#include "modules.h"


#ifndef BLINK_MODIFIER
#define BLINK_MODIFIER


#define BLINK_MODIFIER_INTERVALS_N 3
#define BLINK_MODIFIER_INTERVALS 100, 500, 1000
#define BLINK_MODIFIER_BUTTON 2
#define BLINK_MODIFIER_DEADTIME 200


typedef struct {
	unsigned long intervals[BLINK_MODIFIER_INTERVALS_N];
} BlinkModifierInternal;
BlinkModifierInternal _blink_modifier_internal = {
	{BLINK_MODIFIER_INTERVALS},
};

typedef struct {
	bool reset;
} BlinkModifierSet;
BlinkModifierSet _blink_modifier_set = {
};

typedef struct {
	unsigned long * intervals;
} BlinkModifierGet;
BlinkModifierGet _blink_modifier_get = {
  _blink_modifier_internal.intervals,
};

class BlinkModifier: public Module
{
	private:
		bool button_pushed;
	public:
		BlinkModifier();
		BlinkModifierSet* set;
		BlinkModifierGet* get;
		unsigned char index;
		unsigned long last_press;
		void setup();
		void loop();
};

BlinkModifier::BlinkModifier()
{
	this->set = &_blink_modifier_set;
	this->get = &_blink_modifier_get;
}

BlinkModifier* blink_modifier = (BlinkModifier*) ModulesRegistry::add(new BlinkModifier());

#endif
