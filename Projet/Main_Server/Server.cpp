#include "Server.hpp"

void Server_Class::setUpAP(){
        Serial.println("Starting access point...");
        WiFi.softAPConfig(local_IP, gateway, subnet);        
        WiFi.softAP(login_network, password_network);
        Serial.println(WiFi.localIP());
}
void Server_Class::beginUDP(){
  UDP.begin(getPort());
  Serial.print("Listening on UDP port ");
  Serial.println(getPort());
}

void Server_Class::receivePacket(){
  // Receive packet
  UDP.parsePacket();// check presence of UDP packet
  //UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);

  SB=UDP.read();
  if (SB=='S'){
    Byte_Value["MSB"]=UDP.read();
    Byte_Value["LSB"]=UDP.read();
    EB=UDP.read();

    //opperateur
    pot_value=(Byte_Value["MSB"]<<8)+Byte_Value["LSB"];
    //opperateur
    
    angle = map(pot_value, 0, 1023, 0, 180);
    Serial.println(pot_value);
    servo.write(angle);
  }
}

void Server_Class::servoConfig(){
  servo.attach(pin_servo); // attach servo pin
  pinMode(pin_servo, OUTPUT)
}
