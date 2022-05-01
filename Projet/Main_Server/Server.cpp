#include "Server.hpp"
#define pin_servo D5

//operator outside of the class
int operator + (const Byte_Class& msb, const Byte_Class& lsb) {// to concatenate two bytes
  Serial.println((msb.getByte()<<8)+lsb.getByte());
  return (msb.getByte()<<8)+lsb.getByte();
}


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
  if (SB != 'S') {
      throw 2;
    }
  if (SB=='S'){
    //Byte_Value["MSB"]=UDP.read();
    //Byte_Value["LSB"]=UDP.read();
    MSB.setByte(UDP.read());
    LSB.setByte(UDP.read());
    
    EB=UDP.read();
    if (EB != 'E') {
      throw 1;
    }
    //opperateur
    //pot_value=Byte_Value["MSB"]+Byte_Value["LSB"];
    pot_value=MSB+LSB;
    //opperateur
    
    angle = map(pot_value, 0, 1023, 0, 180);
    Serial.println(pot_value);
    servo.write(angle);
  }
}

void Server_Class::servoConfig(){
  servo.attach(pin_servo); // attach servo pin
  pinMode(pin_servo, OUTPUT);
}
