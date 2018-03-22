#ifndef LED_H_
#define LED_H_

#include <Arduino.h>

class Led {
private:
  int pin;
  volatile byte state;
  unsigned long lastEvent;

public:
  Led();
  Led(int pin);
  ~Led();
  void run();
  int delay;
  bool on;
  void setup();
  void start();
  void stop();
};

#endif
