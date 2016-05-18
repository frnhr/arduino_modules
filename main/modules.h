#include <Arduino.h>


#ifndef MODULES
#define MODULES


#define MODULE_MAX_N 10

class Module;

class ModulesRegistry
{
//	private:
	public:
		static Module* modules[MODULE_MAX_N];
		static uint8_t count;
		static Module* add(Module* module);
};


uint8_t ModulesRegistry::count = 0;

class Module
{
	public:
		virtual void setup();
		virtual void loop();
};

Module* ModulesRegistry::add(Module* module) {

	ModulesRegistry::modules[ModulesRegistry::count] = module;
	ModulesRegistry::count++;
	return module;
};

Module* ModulesRegistry::modules[MODULE_MAX_N] = {};

#endif
