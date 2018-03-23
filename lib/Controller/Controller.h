#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <Arduino.h>
#include "Button.h"
#include "Led.h"
#include "Relay.h"

class Controller {
public:
  Controller();
  Controller(int pinButton, int pinRelay, int pinLed, byte relayState);
  void setup();
  bool execute();
  int buttonDelay;
  int getRelayState();
  int getRelayPin();
private:
  int pinButton;
  int pinRelay;
  int pinLed;
  byte defaultRelayState;
  unsigned long lastEvent;
  Button button;
  Led led;
  Relay relay;
};

#endif
