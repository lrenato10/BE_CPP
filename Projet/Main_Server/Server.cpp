#include "Server.hpp"
#define pin_servo0 D5
#define pin_servo1 D6
#define pin_servo2 D7

/**
 * Operator to concatenate MSB and LSB
 * Operator of Byte_Class outside of this class
 */
//int operator + (const Byte_Class& msb, const Byte_Class& lsb) {// to concatenate two bytes
//  return (msb.getByte()<<8)+lsb.getByte();
//}

/**
 * @brief Configure and start the access point 
 */
void Server_Class::setUpAP(){
  Serial.println("Starting access point...");
  WiFi.softAPConfig(local_IP, gateway, subnet);        
  WiFi.softAP(login_network, password_network);
  Serial.println(WiFi.softAPIP());
}

/**
  * @brief Configure UDP port 
  */
void Server_Class::beginUDP(){
  UDP.begin(getPort());
  Serial.print("Listening on UDP port ");
  Serial.println(getPort());
}

/**
 * Receive the packet from client 
 * Syncronise the begin of the packet read 
 * Read and stock the angles for the servo motor in the STL map
 */
void Server_Class::receivePacket(){
  // Receive packet
  UDP.parsePacket();// check presence of UDP packet
  //UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);

  P=UDP.read();
  if (P != SB) {
      failure_counter++;
      if (failure_counter>100)
        throw 2;
    }
  if (P==SB){
    failure_counter=0;
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
  
    P=UDP.read();
    if (P != EB) {
      throw 1;
    }
  }
}

/**
 * @brief Write motor angles to servo motors and in the screen
 */
void Server_Class::writeMotorAngles(){
  Serial.print("Angle0: ");
  Serial.println(Servos_Angle["servo0"]);
  servo0.write(Servos_Angle["servo0"]);

  Serial.print("Angle1: ");
  Serial.println(Servos_Angle["servo1"]);
  servo1.write(Servos_Angle["servo1"]);

  Serial.print("Angle2: ");
  Serial.println(Servos_Angle["servo2"]);
  servo2.write(Servos_Angle["servo2"]);

  Serial.println(" ");
}

/**
 * @brief Configure servo motors 
 */
void Server_Class::servoConfig(){
  
  servo0.attach(pin_servo0); // attach servo pin
  pinMode(pin_servo0, OUTPUT);
  servo1.attach(pin_servo1); // attach servo pin
  pinMode(pin_servo1, OUTPUT);
  servo2.attach(pin_servo2); // attach servo pin
  pinMode(pin_servo2, OUTPUT);
}
