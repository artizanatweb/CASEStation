#ifndef BUTTON_H_
#define BUTTON_H_

#include <Arduino.h>

class Button {
public:
  Button();
  Button(int pin);
  void setup();
  byte get();
  int delay;
private:
  int pin;
  volatile byte status;
  unsigned long lastEvent;
};

#endif
