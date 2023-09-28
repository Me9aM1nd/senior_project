#include <WiFi.h>
#include <HTTPClient.h>

#define LED 2

const char* ssid = "guja papa";
const char* password = "gujaguja";

String serverName = "https://api.tago.io/data";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

String data = "[{\"variable\": \"temperature\",\"value\": 27,\"metadata\": {\"color\": \"red\"},\"group\": \"1631814703672\",\"unit\": \"C\",\"time\": \"2021-09-16T17:51:43.672Z\"},]";

void setup() {

  pinMode(LED, OUTPUT);
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");


}

void loop() {
  blink();
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      String serverPath = serverName;
  
      http.begin(serverPath.c_str());

      http.addHeader("device-token", "591203f8-b30e-4407-9818-d7650ed23ac4", true, false);
      http.addHeader("Content-Type", "application/json", true, false);

      // Serial.println(http.getString());
      int httpResponseCode = http.POST(data);
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }

}

void blink(){
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
}
