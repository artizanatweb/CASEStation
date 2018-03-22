#include <Arduino.h>
#include "Controller.h"
#include "Button.h"
#include "Led.h"
#include "Relay.h"

Controller::Controller() {}

Controller::Controller(int pinButton, int pinRelay, int pinLed, byte relayState) {
  this->pinButton = pinButton;
  this->pinRelay = pinRelay;
  this->pinLed = pinLed;
  this->defaultRelayState = relayState;

  this->buttonDelay = 500;

  this->button = Button(this->pinButton);
  this->led = Led(this->pinLed);
  this->relay = Relay(this->pinRelay, this->defaultRelayState);
}

void Controller::setup() {
  this->button.setup();
  this->relay.setup();
  this->led.setup();

  this->lastEvent = millis();
}

void Controller::execute() {
  this->led.run();

  long now = millis();

  byte buttonState = this->button.get();
  if (!(HIGH == buttonState)) {
    return;
  }

  if (now - this->lastEvent < this->buttonDelay) {
    return;
  }
  this->lastEvent = now;

  bool relayChanged = this->relay.change();
  byte relayState = this->relay.get();
  if (this->defaultRelayState == relayState) {
    this->led.stop();
    return;
  }

  if (!this->defaultRelayState == relayState) {
    this->led.start();
    return;
  }
}
