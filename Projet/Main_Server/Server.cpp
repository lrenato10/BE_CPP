#include "Server.hpp"
#define pin_servo0 D5
#define pin_servo1 D6
#define pin_servo2 D7

//operator outside of the class
int operator + (const Byte_Class& msb, const Byte_Class& lsb) {// to concatenate two bytes
  Serial.println((msb.getByte()<<8)+lsb.getByte());
  return (msb.getByte()<<8)+lsb.getByte();
}


void Server_Class::setUpAP(){
        Serial.println("Starting access point...");
        WiFi.softAPConfig(local_IP, gateway, subnet);        
        WiFi.softAP(login_network, password_network);
        Serial.println(WiFi.softAPIP());
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
    P=UDP.read();
    if (P==P0){
      MSB.setByte(UDP.read());
      LSB.setByte(UDP.read());
      
      // Opperateur (MSB+LSB) = concatenate most significant byte with less significant byte
      Servos_Angle["servo0"] = map(MSB+LSB, 0, 17600, 0, 180);//STL map of angle and arduino map to convert the value of potentiometer in angle
    }
    P=UDP.read();
    if (P==P1){
      MSB.setByte(UDP.read());
      LSB.setByte(UDP.read());
      Servos_Angle["servo1"] = map(MSB+LSB, 0, 17600, 0, 180);
    }
    P=UDP.read();
    if (P==P2){
      MSB.setByte(UDP.read());
      LSB.setByte(UDP.read());
      Servos_Angle["servo2"] = map(MSB+LSB, 0, 17600, 0, 180);
    }
  
    EB=UDP.read();
    if (EB != 'E') {
      throw 1;
    }

    Serial.println(Servos_Angle["servo0"]);
    servo0.write(Servos_Angle["servo0"]);

    Serial.println(Servos_Angle["servo1"]);
    servo1.write(Servos_Angle["servo1"]);
    
    Serial.println(Servos_Angle["servo2"]);
    servo2.write(Servos_Angle["servo2"]);
  }
}

void Server_Class::servoConfig(){
  
  servo0.attach(pin_servo0); // attach servo pin
  pinMode(pin_servo0, OUTPUT);
  servo1.attach(pin_servo1); // attach servo pin
  pinMode(pin_servo1, OUTPUT);
  servo2.attach(pin_servo2); // attach servo pin
  pinMode(pin_servo2, OUTPUT);
}
