#include <Arduino.h>
#include "modules.hpp"


#ifndef BUTTON_HPP
#define BUTTON_HPP


#define BUTTON_PIN 2
#define BUTTON_DEADTIME 100


class Button: public Module
{
  private:
    bool lastPushMillis = 0;
    bool stillPressed = false;
  public:
    bool pressed = false;  // it is ok to clear this flag from other modules
    void setup();
    void loop();
    Button(){};
};


Button* button = (Button*) ModulesRegistry::add(new Button());


#endif  // #ifndef BUTTON_HPP
