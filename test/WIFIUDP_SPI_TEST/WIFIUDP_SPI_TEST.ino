#include <WiFi.h>
#include <WiFiUdp.h>
#include <SPI.h>

const char* ssid = "equipe11";
const char* password = "BATISCAN";
const IPAddress MY_IP(192, 168, 4, 5);
const IPAddress remoteIP(192, 168, 4, 2);
const IPAddress gateway(192, 168, 4, 1);
const IPAddress subnet(255, 255, 255, 0);
const int remotePort = 4210;

WiFiUDP udp;


unsigned char tabBuffer[255];


void setup() {
  Serial.begin(115200);

  WiFi.config(MY_IP, gateway, subnet);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  udp.begin(4211);  // Initialize UDP

  Serial.print(WiFi.localIP());
  
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    char hello[] = "RRRR";
    udp.beginPacket(remoteIP, remotePort);
    udp.write((uint8_t*)hello, strlen(hello));  // Typecast to uint8_t* for correct conversion
    udp.endPacket();
    Serial.println("Sent 'Hello'");
  }

  delay(1000);

  

  if (WiFi.status() == WL_CONNECTED) {
    char hello[] = "GGGG";
    udp.beginPacket(remoteIP, remotePort);
    udp.write((uint8_t*)hello, strlen(hello));  // Typecast to uint8_t* for correct conversion
    udp.endPacket();
    Serial.println("Sent 'Hello'");
  }


  delay(1000);

  if (WiFi.status() == WL_CONNECTED) {
    char hello[] = "BBBB";
    udp.beginPacket(remoteIP, remotePort);
    udp.write((uint8_t*)hello, strlen(hello));  // Typecast to uint8_t* for correct conversion
    udp.endPacket();
    Serial.println("Sent 'Hello'");
  }


  delay(1000);

  
  
}
