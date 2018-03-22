#include <Arduino.h>
#include "Button.h"

Button::Button() {}

Button::Button(int pin) {
  this->pin = pin;
  this->delay = 500;
  this->lastEvent = 0;
}

void Button::setup() {
  pinMode(this->pin, INPUT);
  this->lastEvent = millis();
  this->status = digitalRead(this->pin);
}

byte Button::get() {
  this->status = digitalRead(this->pin);
  return this->status;
}
