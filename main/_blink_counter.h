#include <Arduino.h>
#include "modules.h"


#ifndef BLINK_COUNTER
#define BLINK_COUNTER



typedef struct {
  unsigned long count;
} BlinkCounterGet;

typedef struct {
  bool reset;
} BlinkCounterSet;

class BlinkCounter: public Module
{
  private:
    unsigned long _count;
    bool last_state;
    BlinkCounterGet _get;
    BlinkCounterSet _set;
  public:
    const BlinkCounterGet * get;
    const BlinkCounterSet * set;
    void setup();
    void loop();
    // initialize class members:
    BlinkCounter() :
      _count{0},
      last_state{false},
      _get{
        0,  // count
      },
      _set{
        false,  // reset
      }
    {
      get = &_get;
      set = &_set;
    };
};


BlinkCounter* blink_counter = (BlinkCounter*) ModulesRegistry::add(new BlinkCounter());


#endif
