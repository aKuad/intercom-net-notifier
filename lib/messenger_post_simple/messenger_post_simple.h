/**
 * @file messenger_post_simple.h
 *
 * Simple text posting to messenger services
 */

#ifndef _MESSENGER_POST_SIMPLE_H_
#define _MESSENGER_POST_SIMPLE_H_

#include <WString.h>


int discord_webhook_post(String webhook_url, String message_to_post);
int line_broadcast_post(String access_token, String message_to_post);


#endif /* _MESSENGER_POST_SIMPLE_H_ */
