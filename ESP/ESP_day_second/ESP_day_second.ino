#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <time.h>
// #include "prot_uart.h"


// const char* ssid = "AzRy Guest";
// const char* password = "ipos.com.ge";

// const int GEORGIAN_TIMEZONE_OFFSET = 4 * 3600; // 4 hours ahead of UTC

// struct tm timeinfo;

// const char* board_name = "Lub Luba";
// int serial_number = 17199;

void setup() {
    Serial.begin(115200);

    // uart_prot_init(115200, 16, 17);

    // WiFi.begin(ssid, password);
    // while (WiFi.status() != WL_CONNECTED) {
    //     delay(1000);
    //     Serial.println("Connecting to WiFi...");
    // }
    
    // Serial.println("Connected to WiFi");
    // configTime(GEORGIAN_TIMEZONE_OFFSET, 0, "pool.ntp.org");
}

void loop() {
    // if (WiFi.status() == WL_CONNECTED) {
    //     http_thread();
    // }
    // uart_prot_thread();

    // delay(5000); // Wait before reconnecting
}

// void http_thread(){
//   HTTPClient http;
//   const char* serverIP = "10.131.31.87";
//   int serverPort = 3000;
  
//   http.begin("http://" + String(serverIP) + ":" + String(serverPort));
//   http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
//   getLocalTime(&timeinfo);
//   char strftime_buf[64];
//   StaticJsonDocument<200> jsonDoc;
//   strftime(strftime_buf, sizeof(strftime_buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
//   jsonDoc["name"] = board_name;
//   jsonDoc["Serial_id"] = serial_number;
//   jsonDoc["temperature"] = temp;
//   jsonDoc["blod_preasure"] = preasure;
//   jsonDoc["hart_rate"] = hart_rate;
//   jsonDoc["saturation"] = saturation;
//   jsonDoc["timestamp"] = strftime_buf;
//   String jsonString;
//   serializeJson(jsonDoc, jsonString);
  
//   int httpResponseCode = http.POST(jsonString);
  
//   if (httpResponseCode > 0) {
//       String response = http.getString();
//       Serial.println("HTTP Response Code: " + String(httpResponseCode));
//       Serial.println("Response: " + response);
//   } else {
//       Serial.println("Error sending POST request");
//   }
  
//   http.end();
// }

// void analyze_stm_packet(){

//   Serial.println("received data ");

//   memcpy(&rame,  &STM_RX_BUF[UART_MESSAGE_ID_INDEX], UART_MESSAGE_PARAM_SIZE);
//   serial_number = rame;
//   Serial.print("serial id: ");
//   Serial.println(serial_number);

//   memcpy(&rame,  &STM_RX_BUF[UART_MESSAGE_TEMP_INDEX], UART_MESSAGE_PARAM_SIZE);
//   temp = ((float)rame)/100;
//   Serial.print("temperature: ");
//   Serial.println(temp);

//   memcpy(&rame,  &STM_RX_BUF[UART_MESSAGE_PRESS_INDEX], UART_MESSAGE_PARAM_SIZE);
//   preasure = ((float)rame)/100;
//   Serial.print("blood preasure: ");
//   Serial.println(preasure);

//   memcpy(&rame,  &STM_RX_BUF[UART_MESSAGE_RATE_INDEX], UART_MESSAGE_PARAM_SIZE);
//   hart_rate = ((float)rame)/100;
//   Serial.print("heart rate: ");
//   Serial.println(hart_rate);

//   memcpy(&rame,  &STM_RX_BUF[UART_MESSAGE_SAT_INDEX], UART_MESSAGE_PARAM_SIZE);
//   saturation = ((float)rame)/100;
//   Serial.print("saturation: ");
//   Serial.println(saturation);  
  

// }
