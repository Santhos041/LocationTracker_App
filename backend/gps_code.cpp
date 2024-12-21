
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>  // Use <WiFi.h> for ESP8266

const char* ssid = "santhosh";
const char* password = "santhosh";

const char* serverIP = "192.168.1.10";
const int serverPort = 3000;

TinyGPSPlus gps;
SoftwareSerial ss(D2, D1);  // RX on D1, TX on D2 for NodeMCU

WiFiClient client;

void setup() {
  Serial.begin(115200);  // Match serial monitor baud rate
  ss.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  while (ss.available() > 0) {
    gps.encode(ss.read());

    if (gps.location.isUpdated()) {
      float latitude = gps.location.lat();
      float longitude = gps.location.lng();
      
      Serial.print("Latitude: "); Serial.println(latitude, 6);
      Serial.print("Longitude: "); Serial.println(longitude, 6);

      if (client.connect(serverIP, serverPort)) {
        String postData = "latitude=" + String(latitude, 6) + "&longitude=" + String(longitude, 6);
        client.println("POST /gpsdata HTTP/1.1");
        client.println("Host: " + String(serverIP));
        client.println("Content-Type: application/x-www-form-urlencoded");
        client.println("Content-Length: " + String(postData.length()));
        client.println();
        client.print(postData);
        client.stop();
      }
    }
  }
}