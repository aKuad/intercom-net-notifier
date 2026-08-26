/**
 * @file main.cpp
 *
 * Home intercom notifier via Internet messenger DIY with ESP32
 */

#include <Arduino.h>
#include <WiFi.h>

#include "messenger_post_simple.h"
#include "comm_secrets.h"

#define TEST_KEY_ENABLE


/* File internal constants */
static const uint32_t SIG_INTERVAL_MS = 10000;
static const uint8_t  ONBOARD_LED     = 2;  // At ESP32 Dev Module
static const uint8_t  INTERCOM_SIG    = 4;
#ifdef TEST_KEY_ENABLE
  static const uint8_t TEST_KEY = 15;
#endif

/* Setup section - runs once */
void setup() {
  pinMode(ONBOARD_LED, OUTPUT);
  digitalWrite(ONBOARD_LED, LOW);
  pinMode(INTERCOM_SIG, INPUT);
  #ifdef TEST_KEY_ENABLE
    pinMode(TEST_KEY, INPUT);
  #endif

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
  // Wi-Fi connected LED indication
  if(WiFi.isConnected())
    digitalWrite(ONBOARD_LED, HIGH);
  else
    digitalWrite(ONBOARD_LED, LOW);

  // Signal detected process dispatch condition checking
  #ifdef TEST_KEY_ENABLE
    bool signal_detected = WiFi.isConnected() && (digitalRead(INTERCOM_SIG) || digitalRead(TEST_KEY));
  #else
    bool signal_detected = WiFi.isConnected() && digitalRead(INTERCOM_SIG);
  #endif

  // On signal detected process
  if(signal_detected) {
    discord_webhook_post(DISCORD_WEBHOOK_URL, "Doorbell rang");
    line_broadcast_post(LINE_CHANNEL_ACCESS_TOKEN, "Doorbell rang");

    // Quick blink for signal detected indication
    digitalWrite(ONBOARD_LED,  LOW); delay(100);
    digitalWrite(ONBOARD_LED, HIGH); delay(100);
    digitalWrite(ONBOARD_LED,  LOW); delay(100);
    digitalWrite(ONBOARD_LED, HIGH); delay(100);

    delay(SIG_INTERVAL_MS);
  }

  delay(250); // Prevent unnecessary too fast loop
}
