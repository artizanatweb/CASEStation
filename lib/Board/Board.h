#ifndef BOARD_H_
#define BOARD_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "Controller.h"
#include "WiFiConfig.h"

class Board {
public:
  Board();
  Board(WiFiConfig& wificonfig);
  void setup(int countControllers, Controller *controllers);
  void receive();
  void send();
  int countControllers;
  Controller *controllers;
private:
  const char* ssid;
  const char* password;
  unsigned int localPort;
  unsigned int remotePort;
  WiFiUDP Udp;
  char incomingBuffer[255];
  bool connected = true;
  const int connectionWait = 5000;
  String remoteIP;
  IPAddress remoteIPObj;
};

#endif
