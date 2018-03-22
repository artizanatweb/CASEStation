#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "Controller.h"
#include "ControllerPins.h"

struct ControllerPins pins[] = {
    {D1, D2, D3, HIGH},
    {D6, D7, D8, HIGH},
};

const int countControllers = sizeof(pins) / sizeof(ControllerPins);

Controller controllers[countControllers];

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);

    for (int i = 0; i < countControllers; i++) {
      ControllerPins pin = pins[i];
      Controller controller = Controller(
        pin.button, pin.relay, pin.led, pin.relayState
      );
      controller.setup();
      controllers[i] = controller;
    };
}

void loop() {
    // put your main code here, to run repeatedly:
    for (int i = 0; i < countControllers; i++) {
      controllers[i].execute();
    };
}
