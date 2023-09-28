#include "http_connection.h"

#define ACCESS_TOKEN "8eeJ3E5UcMufKyxCdnKQ"

const int GEORGIAN_TIMEZONE_OFFSET = 4 * 3600; // 4 hours ahead of UTC

struct tm timeinfo;

WiFiClient http_client;
ThingsBoard tb(http_client);
http_con_t conn;

uint8_t http_conn_init(String wifi_name, String wifi_pass){
  conn.wifi_name = wifi_name;
  conn.wifi_pass = wifi_pass;
  conn.server_name = "demo.thingsboard.io";
  conn.serverPort = 3000; 
  

  WiFi.begin(wifi_name, wifi_pass);
  for(int q = 0; q < 10; q++){
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Connected to WiFi");
      configTime(GEORGIAN_TIMEZONE_OFFSET, 0, "pool.ntp.org");
      return 1;
    }
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Could not connect to WiFi");

  return 0;
}

void http_conn_thread(prot_uart_t* base){

  if (WiFi.status() == WL_CONNECTED) {
    
    strftime(conn.strftime_buf, sizeof(conn.strftime_buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
    
     if (!tb.connect(conn.server_name, ACCESS_TOKEN)) {       
          Serial.println("Failed to connect");      
        return;     
      }   
    
    tb.sendTelemetryData("name", "JANI");
    tb.sendTelemetryData("serial ID", base->params.serial_ID);

    if(base->params.temp)tb.sendTelemetryData("temp", base->params.temp);
    if(base->params.DIA) tb.sendTelemetryData("blood_preasure_DIA", base->params.DIA);
    if(base->params.SYS) tb.sendTelemetryData("blood_preasure_SYS", base->params.SYS);
    if(base->params.heart_rate) tb.sendTelemetryData("blood_pulse", base->params.heart_rate);
    if(base->params.saturation)tb.sendTelemetryData("saturation", base->params.saturation);
    tb.sendTelemetryData("latitude", 41.779397);
    tb.sendTelemetryData("longitude", 44.774352);
    tb.sendTelemetryData("timestamp", conn.strftime_buf);
  }

  
}

