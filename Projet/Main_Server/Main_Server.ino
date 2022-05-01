#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "Server.hpp"

// UDP
Server_Class MyServer("Rede","senha123",4210,192, 168, 4, 1);


// UDP Buffer
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer for communication

//std::map<String ,byte> Byte_Value; //pot values in byte



void setup() {

  MyServer.servoConfig();
  
  // Setup LED pin
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Setup serial port ========== debug
  MyServer.setUpSerialPort(115200);
 
  // Begin Access Point
  MyServer.setUpAP();
 
  // Begin listening to UDP port
  MyServer.beginUDP();
 
}
 
void loop() {
  try {
    MyServer.receivePacket();
  } catch(int e) {
    if (e==1)
      Serial.println("Error EB!!!!!!!!!!!!!!!!!!!!!");
    else if (e==2)
      Serial.println("Error SB!!!!!!!!!!!!!!!!!!!!!");
  }
  
  
  if (packetBuffer[0]){
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Empty");
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }      
 
}
