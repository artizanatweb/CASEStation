#include <Arduino.h>
#include "Led.h"

Led::Led() {
  //
}

Led::Led(int pin) {
  this->pin = pin;
  this->state = HIGH;
  this->lastEvent = 0;
  this->delay = 500;
}

Led::~Led() {
  //
}

void Led::setup() {
  pinMode(this->pin, OUTPUT);
  digitalWrite(this->pin, this->state);
  this->lastEvent = millis();
  this->on = false;
}

void Led::run() {
  if (!this->on) {
    return;
  }

  long now = millis();

  if (now - this->lastEvent < this->delay) {
    return;
  }
  this->lastEvent = now;

  this->state = digitalRead(this->pin);
  this->state = !this->state;

  digitalWrite(this->pin, this->state);
}

void Led::start() {
  if (this->on) {
    return;
  }

  this->on = true;
}

void Led::stop() {
  if (!this->on) {
    return;
  }

  this->on = false;
  this->state = HIGH;
  digitalWrite(this->pin, this->state);
}
