/**
 * @file main.cpp
 *
 * Home intercom notifier via Internet messenger DIY with ESP32
 */

#include <Arduino.h>
#include <WiFi.h>

#include "messenger_post_simple.h"
#include "comm_secrets.h"


/* File internal constants */
static const uint8_t ONBOARD_LED  = 2;  // At ESP32 Dev Module
static const uint8_t INTERCOM_SIG = 4;
static const uint8_t TEST_KEY     = 15;


/* Setup section - runs once */
void setup() {
  pinMode(ONBOARD_LED, OUTPUT);
  digitalWrite(ONBOARD_LED, LOW);
  pinMode(TEST_KEY, INPUT);
  pinMode(INTERCOM_SIG, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  // When no Wi-Fi module detected, blink indication and do nothing more
  if(WiFi.status() == WL_NO_SHIELD) {
    while(1) {
      digitalWrite(ONBOARD_LED, HIGH); delay(500);
      digitalWrite(ONBOARD_LED, LOW);  delay(500);
    }
  }
}


/* Loop section - runs repeatedly */
void loop() {
  // Wi-Fi connected indication
  if(WiFi.isConnected())
    digitalWrite(ONBOARD_LED, HIGH);
  else
    digitalWrite(ONBOARD_LED, LOW);

  // On signal detected process
  if(WiFi.isConnected() && (digitalRead(INTERCOM_SIG) || digitalRead(TEST_KEY))) {
    discord_webhook_post(DISCORD_WEBHOOK_URL, "Doorbell rang");
    line_broadcast_post(LINE_CHANNEL_ACCESS_TOKEN, "Doorbell rang");

    // Quick blink for signal detected indication
    digitalWrite(ONBOARD_LED,  LOW); delay(100);
    digitalWrite(ONBOARD_LED, HIGH); delay(100);
    digitalWrite(ONBOARD_LED,  LOW); delay(100);
    digitalWrite(ONBOARD_LED, HIGH); delay(100);
  }

  delay(250); // Prevent unnecessary too fast loop
}
