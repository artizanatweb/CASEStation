#ifndef CONTROLLERPINS_H_
#define CONTROLLERPINS_H_

#include <Arduino.h>

struct ControllerPins {
    int button;
    int relay;
    int led;
    byte relayState;
    void test();
};

#endif
