#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_AMG88xx.h>

 const char* ssid = "Office-2.4G";
 const char* password = "office!786";
 const char* serverUrl = "https://4f128325-6310-4039-b8ce-bd9875fec2c3-00-qb0bd3bkn7o9.sisko.replit.dev/update";
//const char* serverUrl = "http://192.168.1.14:5000/update";
//const char* serverUrl = "http://192.168.1.14:5000/upload"; https://4f128325-6310-4039-b8ce-bd9875fec2c3-00-qb0bd3bkn7o9.sisko.replit.dev/

Adafruit_AMG88xx amg;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  if (!amg.begin()) {
    Serial.println("AMG88xx not detected!");
    while (1);
  }
}

void loop() {
  float pixels[64];
  amg.readPixels(pixels);

  String json = "{\"tempGrid\":[";
  for (int i = 0; i < 64; i++) {
    json += String(pixels[i], 1);
    if (i < 63) json += ",";
  }
  json += "]}";

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(json);
    http.end();
  }

  delay(1000); // send every second
}
