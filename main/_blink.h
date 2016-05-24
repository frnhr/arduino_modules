/** Blink module

    A variation on classic blink.ino example

*/

// Start every module with at least these two includes:
#include <Arduino.h>
#include "modules.h"

// Here include any modules that depend on this one:
// (blink module has no dependences)


// This guard enables module's header file to be included multiple times:
#ifndef BLINK
#define BLINK


// Module:
class Blink
{
  private:  // members available only from this module
    // (blink has none)
  public:  // members available from everywhere
    // public member variables:
  	static int ledPin;
  	static int ledState;
    static unsigned long interval;
    static unsigned long previousMillis;
    static void setup();
    static void loop();
};
int Blink::ledPin = 13;
int Blink::ledState = 0;
unsigned long Blink::interval = 1000;
unsigned long Blink::previousMillis = 0;


#endif  // #ifndef BLINK
