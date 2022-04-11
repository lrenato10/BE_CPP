#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <map>

#define pot A0
// Set WiFi credentials
#define WIFI_SSID "Rede"
#define WIFI_PASS "senha123"
 
// UDP
WiFiUDP UDP;
IPAddress remote_IP(192,168,4,1);//server adress
#define UDP_PORT 4210



std::map<String ,byte> Byte_Value; //pot values in byte

char SB='S', EB='E';

void setup() {
 
  // Setup IO
  pinMode(pot, INPUT);
   
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
  
  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  WiFi.mode(WIFI_STA);
  
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
 
  // Begin UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Opening UDP port ");
  Serial.println(UDP_PORT);
  
}
  
void loop() {
 
  // Read button
  short int pot_angle = analogRead(pot);
  Serial.println(pot_angle);
  //opperateur
  Byte_Value["MSB"]=byte(pot_angle>>8);
  Byte_Value["LSB"]=byte(pot_angle&0xff);
  //opperateur
  
  // Send Packet
  UDP.beginPacket(remote_IP, UDP_PORT);
  //packet of data
  UDP.write(SB);
  UDP.write(Byte_Value["MSB"]);
  UDP.write(Byte_Value["LSB"]);
  UDP.write(EB);
  //
  UDP.endPacket();
  delay(100);
   
}
