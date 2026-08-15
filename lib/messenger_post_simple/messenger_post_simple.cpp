/**
 * @file messenger_post_simple.cpp
 *
 * Simple text posting to messenger services
 */

#include "messenger_post_simple.h"

#include <HTTPClient.h>
#include <WiFiClientSecure.h>


/**
 * Post a message to Discord via WebHook URL
 *
 * @warning It skips SSL certification verification for simple implementation. NOT FOR CRITICAL USE.
 *
 * @param[in] webhook_url Discord WebHook URL
 * @param[in] message_to_post Message text to post - double-quotation must be escaped: \" (on c code: \\\")
 * @return HTTP response status code
 */
int discord_webhook_post(String webhook_url, String message_to_post) {
  WiFiClientSecure wifi_client;
  HTTPClient http_client;

  wifi_client.setInsecure();
  http_client.begin(wifi_client, webhook_url);
  http_client.addHeader("Content-Type", "application/json");
  int response_code = http_client.POST("{\"content\": \"" + message_to_post + "\"}");
  http_client.end();

  return response_code;
}
