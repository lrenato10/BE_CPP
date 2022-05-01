#include "Client.hpp"
 
// SetUp Client
Client_Class MyClient("MyNetwork","password123",4210,192, 168, 5, 1, 3);

void setup() {
 
  // Setup ADC
  MyClient.setUpADC();
   
  MyClient.setUpSerialPort(115200);
  
  MyClient.setUpWIFI();
 
  // Begin UDP port
  MyClient.beginUDP();
  
}
  
void loop() {
  // Send Packet
  MyClient.startUDPpacket();
  
  for (int i=0; i<MyClient.getNumPot(); i++){
    //read potentiometer value
    MyClient.readPotValue(i);
    //send packet of data
    MyClient.sendPotValue(i);
  }
  
  MyClient.endUDPpacket();
  
  delay(10);
   
}
