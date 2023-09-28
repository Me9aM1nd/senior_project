#ifndef _MAILBOX_H_
#define _MAILBOX_H_

#include <Arduino.h>
#include <WiFi.h>
#include <ESP_Mail_Client.h>

void mailbox_init(String wifi_name, String wifi_pass);
void mailbox_thread(void);

#endif