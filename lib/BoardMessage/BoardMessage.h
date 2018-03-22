#ifndef CSMESSAGE_H_
#define CSMESSAGE_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include "Controller.h"

class BoardMessage {
public:
  BoardMessage();
  void setup(int countControllers, Controller *controllers);
  void receive();
  void send();
  int countControllers;
  Controller *controllers;
};

#endif
