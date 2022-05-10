#include "Server.hpp"

// Set up Server with network name, password, port, remote IP (4 octets)   
Server_Class MyServer("MyNetwork","password123",4210,192, 168, 5, 1);

void setup() {
  
  // Configure servo motors, serial port, Access point and UDP
  
  MyServer.servoConfig();
  MyServer.setUpSerialPort(115200);
  MyServer.setUpAP();
  MyServer.beginUDP();
 
}
 
void loop() {
  
  // Receive UDP packets from client while trying and catching exceptions every 1 ms 
  
  try {
    MyServer.receivePacket();
    MyServer.writeMotorAngles();
  } catch(int e) {
    if(e==1)
      Serial.println("Did not receive the whole packet");
    else if(e==2)
      Serial.println("Loss of communication");
    else
      Serial.println("Exception unknown");
  }
  delay(1);
}
