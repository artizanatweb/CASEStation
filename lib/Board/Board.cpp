#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "Controller.h"
#include "Board.h"

Board::Board() {}

Board::Board(const char* ssid, const char* password, unsigned int localPort, String remoteIP) {
  this->ssid = ssid;
  this->password = password;
  this->localPort = localPort;
  this->remoteIP = remoteIP;
}

void Board::setup(int countControllers, Controller *controllers) {
  this->countControllers = countControllers;
  this->controllers = controllers;

  WiFi.mode(WIFI_STA);
  WiFi.begin(this->ssid, this->password);

  long startTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    /* code */
    delay(500);
    Serial.println(".");
    long now = millis();
    if (now - startTime > this->connectionWait) {
      this->connected = false;
      break;
    }
  }
  Serial.println("WiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  this->Udp.begin(this->localPort);
}

void Board::send() {
  if (!this->connected) {
    return;
  }

  StaticJsonBuffer<255> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["type"] = "station";
  root["action"] = "status";
  JsonObject& relays = root.createNestedObject("relays");
  for (int i = 0; i < this->countControllers; i++) {
    String relayPin = String(this->controllers[i].getRelayPin());
    relays[relayPin] = this->controllers[i].getRelayState();
  }

  root.printTo(Serial);
  Serial.println("");
}

void Board::receive() {
  // {"type":"server","action":"change","relays":{"4":0,"13":1}}
  if (!this->connected) {
    return;
  }

  int packetSize = Udp.parsePacket();
  if (!packetSize) {
    // Serial.println("No packet!");
    return;
  }

  int len = this->Udp.read(this->incomingBuffer, 255);
  if (!(0 < len)) {
    Serial.println("Empty packet!");
    return;
  }

  this->incomingBuffer[len] = 0;
  // Serial.println(this->incomingBuffer);

  StaticJsonBuffer<255> jsonBuffer;
  JsonObject& message = jsonBuffer.parse(this->incomingBuffer);
  if (!message.success()) {
    Serial.println("Can't parse message!");
    return;
  }

  Serial.println("Received message:");
  message.printTo(Serial);
  Serial.println("");

  if (!(strcmp(message["type"],"server") == 0)) {
    Serial.println("Message is not from server!");
    return;
  }

  if (strcmp(message["action"], "status") == 0) {
    this->send();
    return;
  }

  if (!(strcmp(message["action"], "change") == 0)) {
    Serial.println("Message is not change request!");
    return;
  }

  JsonObject& relays = message["relays"];

  for (int i = 0; i < this->countControllers; i++) {
    String relayPin = String(this->controllers[i].getRelayPin());
    if (!relays[relayPin].success()) {
      Serial.println("Pin number '" + relayPin + "' not found!");
      continue;
    }

    this->controllers[i].setRelayPin(relays[relayPin].as<int>());
  }

  Serial.printf("Received packet from IP: %s", this->Udp.remoteIP().toString().c_str());
  Serial.println("");
  int sameIp = (strcmp(this->Udp.remoteIP().toString().c_str(), this->remoteIP.c_str()) == 0) ? 1 : 0;
  Serial.println(sameIp);
}
