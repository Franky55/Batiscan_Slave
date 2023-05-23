#include <WiFi.h>
#include <WiFiUdp.h>
#include <SPI.h>

const char* ssid = "Batiscan";
const char* password = "BATISCAN";
const IPAddress MY_IP(192, 168, 4, 5);
const IPAddress remoteIP(192, 168, 4, 4);
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
  udp.begin(4210);  // Initialize UDP

  Serial.print(WiFi.localIP());
  
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    char hello[] = "ON111";
    udp.beginPacket(remoteIP, remotePort);
    udp.write((uint8_t*)hello, strlen(hello));  // Typecast to uint8_t* for correct conversion
    udp.endPacket();
    Serial.println("Sent 'Hello'");
  }

  delay(1000);
  int val = udp.available();
  Serial.println(val);

  udp.read(tabBuffer, val);

  if(tabBuffer[3] == '1')
  {
    digitalWrite(13, HIGH);
  }

  if(tabBuffer[3] == '0')
  {
    digitalWrite(13, LOW);
  }

  

  if (WiFi.status() == WL_CONNECTED) {
    char hello[] = "OFF00";
    udp.beginPacket(remoteIP, remotePort);
    udp.write((uint8_t*)hello, strlen(hello));  // Typecast to uint8_t* for correct conversion
    udp.endPacket();
    Serial.println("Sent 'Hello'");
  }


  delay(1000);

  int val1 = udp.available();
  Serial.println(val1);
  udp.read(tabBuffer, val1);

  if(tabBuffer[3] == '1')
  {
    digitalWrite(13, HIGH);
  }

  if(tabBuffer[3] == '0')
  {
    digitalWrite(13, LOW);
  }

  
}
