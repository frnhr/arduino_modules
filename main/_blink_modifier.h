#include <Arduino.h>
#include "modules.h"


#ifndef BLINK_MODIFIER
#define BLINK_MODIFIER


#define BLINK_MODIFIER_INTERVALS_N 4
#define BLINK_MODIFIER_INTERVALS 100, 250, 500, 1000
#define BLINK_MODIFIER_BUTTON 2
#define BLINK_MODIFIER_DEADTIME 100


class BlinkModifier: public Module
{
  private:
    unsigned long intervals[BLINK_MODIFIER_INTERVALS_N];
    bool button_pushed;
  public:
    unsigned char index;
    unsigned long last_press;
    void setup();
    void loop();
    // initialize class members:
    BlinkModifier() :
      intervals{BLINK_MODIFIER_INTERVALS},
      button_pushed{false},
      index{0},
      last_press{0}
    {};
};


BlinkModifier* blink_modifier = (BlinkModifier*) ModulesRegistry::add(new BlinkModifier());


#endif
