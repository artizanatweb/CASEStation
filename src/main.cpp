#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "Controller.h"
#include "ControllerPins.h"
#include "Board.h"

struct ControllerPins pins[] = {
    {D1, D2, D3, HIGH},
    {D6, D7, D8, HIGH},
};

const int countControllers = sizeof(pins) / sizeof(ControllerPins);

Controller controllers[countControllers];

const char* ssid = "";
const char* password = "";

unsigned int localPort = 4210;
String remoteIP = "192.168.33.155";

Board board = Board(ssid, password, localPort, remoteIP);

// WiFiUDP Udp;

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

    board.setup(countControllers, controllers);
}

void loop() {
    // put your main code here, to run repeatedly:
    board.receive();

    bool changes = false;

    for (int i = 0; i < countControllers; i++) {
      if (controllers[i].execute()) {
        changes = true;
      }
    };

    if (!changes) {
      return;
    }

    // changes found!
    // report to client/server
    board.send();
}
