#ifndef _HTTP_CONNECTION_H_
#define _HTTP_CONNECTION_H_

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include <Arduino.h>
#include "ThingsBoard.h"
#include "prot_uart.h"

typedef struct{
  String wifi_name;
  String wifi_pass;
  const char* server_name;
  int serverPort;
  char strftime_buf[64];
  StaticJsonDocument<200> jsonDoc;

}http_con_t;

uint8_t http_conn_init(String wifi_name, String wifi_pass);

void http_conn_thread(prot_uart_t* base);

#endif