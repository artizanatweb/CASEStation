#ifndef RELAY_H_
#define RELAY_H_

#include <Arduino.h>

class Relay {
private:
  int pin;
  volatile byte state;
  unsigned long lastEvent;
  int delay;

public:
  Relay();
  Relay(int pin, byte defaultState);
  ~Relay();
  byte get();
  bool change();
  void setup();
  void set(byte state);
};

#endif
