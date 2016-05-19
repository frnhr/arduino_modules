/** Blink module
 *
 *  A variation on classic blink.ino example
 *
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
class Blink: public Module
{
private:  // members available only from this module
	// (blink has none)
public:  // members available from everywhere
	// public member variables:
	int ledPin;
	int ledState;
	unsigned int interval;
	unsigned int previousMillis;
	// public member functions:
	void setup();
	void loop();

	// Initialization of member variables (both private and public):
	Blink():
		ledState{LOW},
		ledPin{13},
		interval{1000}
		// Defaults are often ok, no need to explicitly initialize every member here
		// though it is a good practice to do so.
		// Also, keep the same order in definitions to avoid unnecessary compiler warnings.
	{};
};

// Instantiate the module class:
Blink* blink = (Blink*) ModulesRegistry::add(new Blink());


#endif  // #ifndef BLINK
