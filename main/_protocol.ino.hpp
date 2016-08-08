#include <Arduino.h>
#include "modules.hpp"

#include "_protocol.hpp"


#ifdef PROTOCOL_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .h file instead?
#endif
#define PROTOCOL_INO_HPP


void Protocol::setup()
{}


void Protocol::loop()
{
  // we are only conserned with handling incomming commands:
  if (setCommand[0] == '\0') {
    // (empty strings start with a null-character)
    return;
  }

  if (setReplyPrinter) {
    // reply printer must also be set
    // TODO use Serial only in DEBUG mode!
    Serial.print(F("Got a command but no printer!\n"));
    return;
  }
  // store reply_printer locally to avoid accidental overwrite by other modules:
  replyPrinter = setReplyPrinter;


  // we'll need a fancy String object, for simplr parsing:
  String command = setCommand;

  // set busy flag (just in case we have to handle this command over multiple cycles):
  busy = true;

  // status buffer:
  if (command == "status") {
    // calculate how many lines are going to be in the reply:
    int status_reply_count = 0;
    #ifdef MAGNETOMETER_HPP
    status_reply_count += 1;
    #endif
    #ifdef MAG_CALIBRATION_HPP
    status_reply_count += 1;
    #endif
    #ifdef COMPASS_HPP
    status_reply_count += 1;
    #endif
    // first line of the reply, with the number of lines to follow:
    reply_printer->print(F("status "));
    reply_printer->print(status_reply_count);
    reply_printer->print(F("\n"));

    #ifdef MAGNETOMETER_HPP
    reply_printer->print(F("mag_current: "));
    if (!magnetometer->inited) {
      reply_printer->print(F("not initiated\n"));
    } else {
      reply_printer->print(magnetometer->m_x);
      reply_printer->print(F(" "));
      reply_printer->print(magnetometer->m_y);
      reply_printer->print(F(" "));
      reply_printer->print(magnetometer->m_z);
      reply_printer->print(F("\n"));
    }
    #endif  //#ifdef MAGNETOMETER_HPP

    #ifdef MAG_CALIBRATION_HPP
    reply_printer->print(F("mag_calibration: "));
    if (!mag_calibration->inited) {
      reply_printer->print(F("not initiated\n"));
    } else {
      reply_printer->print(F("("));
      reply_printer->print(mag_calibration->x_min);
      reply_printer->print(F(","));
      reply_printer->print(mag_calibration->x_max);
      reply_printer->print(F("), ("));
      reply_printer->print(mag_calibration->y_min);
      reply_printer->print(F(","));
      reply_printer->print(mag_calibration->x_max);
      reply_printer->print(F("), ("));
      reply_printer->print(mag_calibration->z_min);
      reply_printer->print(F(","));
      reply_printer->print(mag_calibration->z_max);
      reply_printer->print(F(")"));
      reply_printer->print(F("\n"));
    }
    #endif  //#ifdef MAG_CALIBRATION_HPP

    #ifdef COMPASS_HPP
    reply_printer->print(F("mag_azimuth: "));
    if (!compass->inited) {
      reply_printer->print(F("not initiated\n"));
    } else {
      reply_printer->print(rad2deg(compass->azimuth));
      reply_printer->print(F("\n"));
    }
    #endif  //#ifdef COMPASS_HPP


  #ifdef BLINK_HPP
  } else if (command.substring(0, 10) == "blink set ") {
    String pattern_id = command.substring(10);
    char buff[pattern_id.length() + 1];
    pattern_id.toCharArray(buff, pattern_id.length() + 1);
    blink->set_pattern = (int8_t) atoi(buff);
    reply_printer->print(F("ok 1\n"));
    reply_printer->print(F("blink_pattern: "));
    reply_printer->print(blink->set_pattern);
    reply_printer->print(F("\n"));
  #endif  // #ifdef BLINK_HPP

  #ifdef ENCODER_HPP
  } else if (command == "enc az") {
    reply_printer->print(F("enc_az 1\n"));
    reply_printer->print(rad2deg(encoder->azimuth));
    reply_printer->print(F("\n"));

  } else if (command.substring(0, 11) == "enc az set ") {
    String new_az = command.substring(11);
    char buff[new_az.length() + 1];
    new_az.toCharArray(buff, new_az.length() + 1);
    encoder->set_azimuth = deg2rad(atol(buff));
    reply_printer->print(F("ok 0\n"));
  #endif  // #ifdef ENCODER_HPP

  #ifdef MAG_CALIBRATION_HPP
  } else if (command == "calibrate") {
    reply_printer->print(F("ok 1\n"));
    reply_printer->print(F("calibrating...\n"));
    mag_calibration->set_start_calibration = true;

  } else if (command == "cancel" && mag_calibration->calibrating) {
    reply_printer->print(F("ok 1\n"));
    reply_printer->print(F("calibration canceled\n"));
    mag_calibration->set_cancel_calibration = true;

  } else if (command == "save" && mag_calibration->calibrating) {
    reply_printer->print(F("ok 1\n"));
    reply_printer->print(F("calibration saved\n"));
    mag_calibration->set_save_calibration = true;

#endif  // #ifdef MAG_CALIBRATION_HPP

#ifdef COMPASS_HPP
} else if (command == "mag az") {
    reply_printer->print(F("mag_az 1\n"));
    reply_printer->print(rad2deg(compass->azimuth));
    reply_printer->print(F("\n"));
  #endif  // #ifdef COMPASS_HPP

  } else if (command == "" || command == "help") {
    int help_reply_count = 2;
    #ifdef CLOCK_H
    help_reply_count += 2;
    #endif

    reply_printer->print(F("help "));
    reply_printer->print(help_reply_count);
    reply_printer->print(F("\n"));
    reply_printer->print(F("available commands:\n"));
    reply_printer->print(F("status\n"));
    /*
    #ifdef SENSORS_H
    reply_printer->print(F("data\n"));
    #endif
    */

  } else {
    reply_printer->print(F("error 2\n"));
    reply_printer->print(F("unknown command\n"));
    reply_printer->print(command);
    reply_printer->print(F("\n"));
  }

  // reset flags:
  set.command[0] = '\0';
  get.busy = false;

  // also clear reference to the printer, for good measure:
  set.reply = NULL;
  reply_printer = NULL;
}
