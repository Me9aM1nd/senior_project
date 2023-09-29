#include "http_connection.h"
#include "prot_uart.h"
#include "mailbox.h"
#include "screen_manager.h"

const char* board_name = "Lub Luba";
int serial_number = 17199;
int http_conn_timeout = millis();
prot_uart_t* base_p;

void setup() {
    Serial.begin(115200);
 
    // http_conn_init("Mari", "guja7777");
    http_conn_init("guja", "");
    base_p = uart_prot_init(115200, 3, 1);
    // mailbox_init("Mari", "guja7777");
    screen_manager_init();
}

void loop() {
  uart_prot_thread();
  if(millis() - http_conn_timeout > 5000 ){
    base_p->params.DIA = 96;
    base_p->params.SYS = 126;
    http_conn_thread(base_p);
    http_conn_timeout = millis();
  }
  screen_manager_loop();

  // mailbox_thread();
}
