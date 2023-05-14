#include <WiFi.h>
#include <WiFiUdp.h>
#include <SPI.h>

const char* ssid = "Batiscan";
const char* password = "BATISCAN";
const IPAddress remoteIP(192, 168, 4, 1);
const int remotePort = 4210;

WiFiUDP udp;


void setup() {
  Serial.begin(115200);


  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  udp.begin(4210);  // Initialize UDP
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    char hello[] = "ON";
    udp.beginPacket(remoteIP, remotePort);
    udp.write((uint8_t*)hello, strlen(hello));  // Typecast to uint8_t* for correct conversion
    udp.endPacket();
    Serial.println("Sent 'Hello'");
  }

  delay(1000);

  if (WiFi.status() == WL_CONNECTED) {
    char hello[] = "OFF";
    udp.beginPacket(remoteIP, remotePort);
    udp.write((uint8_t*)hello, strlen(hello));  // Typecast to uint8_t* for correct conversion
    udp.endPacket();
    Serial.println("Sent 'Hello'");
  }

  delay(1000);
}
