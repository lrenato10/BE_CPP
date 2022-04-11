#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "Client_Server.hpp"

// UDP
Server_Class MyServer("Rede","senha123",4210,192, 168, 4, 1);

#define pin_servo D5

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

  MyServer.receivePacket()
  if (packetBuffer[0]){
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Empty");
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }      
 
}
