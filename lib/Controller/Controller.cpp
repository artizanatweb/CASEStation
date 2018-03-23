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

  this->changeRelayState = false;
  this->newRelayState = this->defaultRelayState;

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

bool Controller::execute() {
  this->led.run();

  long now = millis();

  if (!this->checkTime(now)) {
    return false;
  }

  if (!this->changeRelayState) {
    // no server request
    // proceed to check hardware button
    byte buttonState = this->button.get();
    if (!(HIGH == buttonState)) {
      return false;
    }

    this->relay.change();
  } else {
    // server request to change relay state
    this->changeRelayState = false;
    this->relay.set(this->newRelayState);
  }
  this->lastEvent = now;

  byte relayState = this->relay.get();
  if (this->defaultRelayState == relayState) {
    this->led.stop();
    return true;
  }

  if (!this->defaultRelayState == relayState) {
    this->led.start();
    return true;
  }

  return false;
}

int Controller::getRelayState() {
  int relayState = (this->defaultRelayState == this->relay.get()) ? 0 : 1;
  return relayState;
}

int Controller::getRelayPin() {
  return this->pinRelay;
}

void Controller::setRelayPin(int value) {
  byte state = this->defaultRelayState;
  if (value == 1) {
    state = !state;
  }

  this->changeRelayState = true;
  this->newRelayState = state;
}

bool Controller::checkTime(long now) {
  if (now - this->lastEvent < this->buttonDelay) {
    return false;
  }

  return true;
}
