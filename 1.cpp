#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void setup() {
  // ... الكود السابق
  
  // إعداد خادم الويب
  server.on("/status", HTTP_GET, []() {
    String json = "{";
    json += "\"online\":" + String(internetConnected ? 1 : 0) + ",";
    json += "\"smsCount\":" + String(smsCount) + ",";
    json += "\"timestamp\":" + String(millis());
    json += "}";
    
    server.send(200, "application/json", json);
  });
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();  // معالجة طلبات الويب
  // ... باقي الكود
}
