#include "esp_system.h"
#include <WiFi.h>
#include "ThingSpeak.h"
#include <WebServer.h>
#include <ArduinoJson.h>

WebServer web_server(80);

int temp, hum, gas, sMos;

const char* ssid = "RUPAM";
const char* password = "#Radon690";
const int myChannelNumber = 2984730;
const char* myApiKey = "ZDBONK761KBCEX6N";
const char* server = "api.thingspeak.com";

WiFiClient client; // Declare globally (important!)

void handleSensorData() {
  StaticJsonDocument<200> doc;
  doc["temperature"] = temp;
  doc["humidity"] = hum;
  doc["gas"] = gas;
  doc["soil"] = sMos;

  String response;
  serializeJson(doc, response);
  Serial.println("Sending JSON: " + response);  // <-- debug print

  web_server.send(200, "application/json", response);
}


void setup() {
  Serial.begin(115200);
  esp_log_level_set("*", ESP_LOG_VERBOSE);
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".\n");
  }

  Serial.println("Connected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  //  Move server setup here
  web_server.on("/sensor-data", handleSensorData);
  web_server.enableCORS(true);
  web_server.begin();

  ThingSpeak.begin(client); // Only once, after WiFi is connected
}


void loop() {

  web_server.handleClient();

  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    int data2 = data.toInt();
    Serial.println(data2);
    int q = data2 / 100;
    int r = data2 % 100;
    switch (q) {
      case 1:
        Serial.print("Humidity: ");
        Serial.println(r);
        hum = r;
        break;
      case 2:
        Serial.print("Temperature: ");
        Serial.println(r);
        temp = r;
        break;
      case 3:
        Serial.print("Gas: ");
        Serial.println(r);
        gas = r;
        break;
      case 4:
        Serial.print("Soil Moisture: ");
        Serial.println(r);
        sMos = r;
        break;
    }
  }

  // Upload to ThingSpeak
  ThingSpeak.setField(1, hum);
  ThingSpeak.setField(2, temp);
  ThingSpeak.setField(3, gas);
  ThingSpeak.setField(4, sMos);

  int x = ThingSpeak.writeFields(myChannelNumber, myApiKey);

  if (x == 200) {
    Serial.println("Data uploaded successfully");
  } else {
    Serial.println("Upload failed. HTTP error: " + String(x));
  }

  delay(15000); // Wait to avoid ThingSpeak rate limits
}
