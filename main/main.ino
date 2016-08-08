// Include Ardiono.h is needed for many custom IDEs, and doesn't hurt Arduino IDE:
#include <Arduino.h>


// Number of modules in your app:
#define MODULE_MAX_N 10
// (2 * MODULE_MAX_N) bytes of SRAM will be reserved

// Include code for working with modules:
#include "modules.h"

// Include actual modules:
#include "_blink.ino.hpp"
//#include "_blink_counter.ino.hpp"
#include "_blink_modifier.ino.hpp"
// This include is all that is required to include a module in the code.
// If a module is removed from here, it will not be compiled.
// Order of includes matters.
// If a module depends on another module, it will include it even if not specified here
// (so, including _blink.h is not strictly necessary here, it will be included from _blink_modifier.h anyway).


void setup()
{
  Serial.begin(9600);
  // Call setup() for every module:
  unsigned int i;
  for (i = 0; i < ModulesRegistry::count; i++) {
    ModulesRegistry::modules[i]->setup();
  }
}


void loop()
{
  // Call loop() for every module:
  unsigned int i;
  for (i = 0; i < ModulesRegistry::count; i++) {
    ModulesRegistry::modules[i]->loop();
  }


}
