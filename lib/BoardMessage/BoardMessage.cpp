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
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["type"] = "station";
  root["action"] = "status";
  JsonObject& relays = root.createNestedObject("relays");
  for (int i = 0; i < this->countControllers; i++) {
    String relayPin = String(this->controllers[i].getRelayPin());
    relays[relayPin] = this->controllers[i].getRelayState();
  }

  root.printTo(Serial);
  Serial.println("");
}

void BoardMessage::receive() {
  //
}
