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
  WiFiClientSecure wifi;
  HTTPClient http;

  wifi.setInsecure();
  http.begin(wifi, webhook_url);
  http.addHeader("Content-Type", "application/json");
  int http_status = http.POST("{\"content\":\"" + message_to_post + "\"}");
  http.end();

  return http_status;
}


/**
 * Post a message to LINE via Messaging API
 *
 * @note It sends a message to all friends (registered users) of specified token's account
 *
 * @warning It skips SSL certification verification for simple implementation. NOT FOR CRITICAL USE.
 *
 * @param[in] channel_access_token Messaging API channel access token
 * @param[in] message_to_post Message text to post - double-quotation must be escaped: \" (on c code: \\\")
 * @return HTTP response status code
 */
int line_broadcast_post(String channel_access_token, String message_to_post) {
  WiFiClientSecure wifi;
  HTTPClient http;

  wifi.setInsecure();
  http.begin(wifi, "https://api.line.me/v2/bot/message/broadcast");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + channel_access_token);
  int http_status = http.POST("{\"messages\":[{\"type\":\"text\",\"text\":\"" +  message_to_post + "\"}]}");
  http.end();

  return http_status;
}
