#include "http_connection.h"
#include "prot_uart.h"

const char* board_name = "Lub Luba";
int serial_number = 17199;
int http_conn_timeout = millis();

void setup() {
    Serial.begin(115200);

    // http_conn_init("Mari", "guja7777");
    http_conn_init("AzRyGuest", "ipos.com.ge");
    uart_prot_init(115200, 16, 17);
}

void loop() {
  uart_prot_thread();
  if(millis() - http_conn_timeout > 5000 ){
    http_conn_thread();
    http_conn_timeout = millis();
  }

}
