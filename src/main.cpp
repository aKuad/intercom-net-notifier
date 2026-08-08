/**
 * @file main.cpp
 *
 * Home intercom notifier via Internet messenger DIY with ESP32
 */

#include <Arduino.h>
#include <WiFi.h>

#include "comm_secrets.h"


/* File internal constants */
static const uint8_t ONBOARD_LED = 2; // At ESP32 Dev Module


/* Setup section - runs once */
void setup() {
  pinMode(ONBOARD_LED, OUTPUT);
  digitalWrite(ONBOARD_LED, LOW);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  if(WiFi.status() == WL_NO_SHIELD) {
    while(1) {
      digitalWrite(ONBOARD_LED, HIGH);
      delay(500);
      digitalWrite(ONBOARD_LED, LOW);
      delay(500);
    }
  }
}


/* Loop section - runs repeatedly */
void loop() {
  if(WiFi.isConnected())
    digitalWrite(ONBOARD_LED, HIGH);
  else
    digitalWrite(ONBOARD_LED, LOW);

  delay(500); // Prevent unnecessary too fast loop
}
