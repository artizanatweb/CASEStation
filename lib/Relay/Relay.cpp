#include <Arduino.h>
#include "Relay.h"

Relay::Relay() {
  //
}

Relay::Relay(int pin, byte defaultState) {
  this->pin = pin;
  this->state = defaultState;
  this->delay = 1000;
  this->lastEvent = 0;
}

Relay::~Relay() {
  //
}

void Relay::setup() {
  /* code */
  pinMode(this->pin, OUTPUT);
  digitalWrite(this->pin, this->state);
  this->lastEvent = millis();
}

bool Relay::change() {
  long now = millis();

  if (now - this->lastEvent < this->delay) {
    return false;
  }
  this->lastEvent = now;

  this->state = this->get();
  this->state = !this->state;

  digitalWrite(this->pin, this->state);
  return true;
}

byte Relay::get() {
  return digitalRead(this->pin);
}

void Relay::set(byte state) {
  if (this->get() == state) {
    return;
  }

  this->change();
}
