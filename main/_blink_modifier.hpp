/** Blink modifier module

    Changes interval value on the Blink module.

*/

#include <Arduino.h>
#include "modules.hpp"


#ifndef BLINK_MODIFIER_HPP
#define BLINK_MODIFIER_HPP


#define BLINK_MODIFIER_INTERVALS_N 4
#define BLINK_MODIFIER_INTERVALS 100, 250, 500, 1000
#define BLINK_MODIFIER_NULL 42  // any value greater then BLINK_MODIFIER_INTERVALS_N


class BlinkModifier: public Module
{
  private:
    uint16_t intervals[BLINK_MODIFIER_INTERVALS_N] = {BLINK_MODIFIER_INTERVALS};
    uint8_t _index = 0;
  public:
    // members intended for read-only:
    uint8_t index = 0;  // mirrorring private member `_index`
    // member intended for write:
    bool setNextInterval = false;
    uint8_t setIntervalTo = BLINK_MODIFIER_NULL;
    // required member functions:
    void setup();
    void loop();
};


BlinkModifier* blink_modifier = (BlinkModifier*) ModulesRegistry::add(new BlinkModifier());


#endif  // #ifndef BLINK_MODIFIER_HPP
