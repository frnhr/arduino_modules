#include <Arduino.h>
#include "modules.hpp"

#include "_button.hpp"


#ifdef BUTTON_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .h file instead?
#endif
#define BUTTON_INO_HPP


void Button::setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(BUTTON_PIN, HIGH);
}


void Button::loop()
{
  // get once, use multiple times:
  unsigned long millisNow = millis();

  // after state change, don't read anything for a short time:
  if (millisNow - lastPushMillis < BUTTON_DEADTIME) {
    return;
  }

  // read the button state:
  bool buttonPushed = !digitalRead(BUTTON_PIN);  // NO switch to GND

  // detect new press of a button:
  if (buttonPushed && !stillPressed) {
    // set public flag:
    pressed = true;
    // remember this time privately:
    lastPushMillis = millisNow;
    // keep track of button state privately to prevent double detection:
    stillPressed = true;
  }

  // if button is not pressed:
  if (!buttonPushed) {

    // if just released, engagne the deadzone countdown:
    if (stillPressed) {
      lastPushMillis = millisNow;
    }

    // clear the related flags:
    pressed = false;
    stillPressed = false;
  }

  // TODO implement press-and-hold detection here, something like this:
  /*
  if (buttonPushed && (millisNow - lastPushMillis > BUTTON_HOLD_MILLIS) {
    // set a public and a private flag
  }
  */



  // TODO this kind of inter-module logic is better implemented in a separate module, usually named `status`:

  // use the button value:
  #ifdef BLINK_MODIFIER_HPP
    if (button->pressed) {
      // set the action:
      blink_modifier->setNextInterval = true;
      // debug:
      //Serial.println("PRESS");
      // clear the flag:
      button->pressed = false;
    }
  #endif

}
