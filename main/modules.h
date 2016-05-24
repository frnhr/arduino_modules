#include <Arduino.h>


// modules.h will be included multiple times, it needs an include guard:
#ifndef MODULES
#define MODULES


// This value can be defined in main.ino, so check before defining:
#ifndef MODULE_MAX_N
#define MODULE_MAX_N 10  // default value for MODULE_MAX_N
#endif
// 2 bytes are reserved for every module


// Implementation of Module Registry class, statically...


class Module;

class ModulesRegistry
{
    // private:
  public:
    static Module* modules[MODULE_MAX_N];
    static uint8_t count;
    static Module* add(Module* module);
};

Module* ModulesRegistry::add(Module* module) {
  ModulesRegistry::modules[ModulesRegistry::count] = module;
  ModulesRegistry::count++;
  return module;
};

Module* ModulesRegistry::modules[MODULE_MAX_N] = {};
uint8_t ModulesRegistry::count = 0;


// Implementation of Module abstract class...


class Module
{
  public:
    virtual void setup();
    virtual void loop();
};


#endif
