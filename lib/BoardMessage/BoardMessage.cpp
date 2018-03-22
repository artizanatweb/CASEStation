#include <Arduino.h>
#include <ArduinoJson.h>
#include "Controller.h"
#include "BoardMessage.h"

BoardMessage::BoardMessage() {}

void BoardMessage::setup(int countControllers, Controller *controllers) {
  this->countControllers = countControllers;
  this->controllers = controllers;
}

void BoardMessage::send() {
  // StaticJsonBuffer<200> jsonBuffer;
  // JsonObject& root = jsonBuffer.createObject();

  for (int i = 0; i < this->countControllers; i++) {
    Serial.println(this->controllers[i].getRelayPin());
  }
}

void BoardMessage::receive() {
  //
}
