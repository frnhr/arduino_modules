#include <Arduino.h>
#include "modules.hpp"


#ifndef BLINK_COUNTER_HPP
#define BLINK_COUNTER_HPP



class BlinkCounter: public Module
{
  private:
    bool lastState = false;
  public:
    // members intended for read-only:
    uint16_t count = 0;
    // member intended for write:
    bool setReset = false;
    // required member functions:
    void setup();
    void loop();
    // empty module constructor, can usually not used and be ommited:
    BlinkCounter() {};
};


BlinkCounter* blink_counter = (BlinkCounter*) ModulesRegistry::add(new BlinkCounter());


#endif  // #ifndef BLINK_COUNTER_HPP
