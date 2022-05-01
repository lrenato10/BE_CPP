#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <map>

#define pot A0
// Set WiFi credentials
#define WIFI_SSID "MyNetwork"
#define WIFI_PASS "password123"
 
// UDP
WiFiUDP UDP;
IPAddress remote_IP(192,168,5,1);//server adress
#define UDP_PORT 4210



std::map<String ,byte> Byte_Value; //pot values in byte

char SB='S', EB='E', P0='A', P1='B',P2='C';
int16_t adc0, adc1, adc2;

void setup() {
 
  // Setup IO
  pinMode(pot, INPUT);

  // Setup ADC
  ads.begin();
   
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
  // Send Packet
  UDP.beginPacket(remote_IP, UDP_PORT);
  
  UDP.write(SB);
  
  // Read pot
  UDP.write(P0);
  adc0 = ads.readADC_SingleEnded(0);
  Serial.print("AIN0: ");
  Serial.println(adc0);
  //opperateur
  Byte_Value["MSB"]=byte(adc0>>8);
  Byte_Value["LSB"]=byte(adc0&0xff);
  //packet of data
  UDP.write(Byte_Value["MSB"]);
  UDP.write(Byte_Value["LSB"]);

  UDP.write(P1);
  adc1 = ads.readADC_SingleEnded(1);
  Serial.print("AIN1: ");
  Serial.println(adc1);
  //opperateur
  Byte_Value["MSB"]=byte(adc1>>8);
  Byte_Value["LSB"]=byte(adc1&0xff);
  //packet of data
  UDP.write(Byte_Value["MSB"]);
  UDP.write(Byte_Value["LSB"]);

  UDP.write(P2);
  adc2 = ads.readADC_SingleEnded(2);
  Serial.print("AIN2: ");
  Serial.println(adc2);
  //opperateur
  Byte_Value["MSB"]=byte(adc2>>8);
  Byte_Value["LSB"]=byte(adc2&0xff);
  //packet of data
  UDP.write(Byte_Value["MSB"]);
  UDP.write(Byte_Value["LSB"]);

  UDP.write(EB);
  //
  UDP.endPacket();
  delay(100);
   
}
