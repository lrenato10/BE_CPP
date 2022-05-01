#include "Client.hpp"
 
// Set up Client with network name, password, port, remote IP (4 octets), number of potentiometers   
Client_Class MyClient("MyNetwork","password123",4210,192, 168, 5, 1, 3);

void setup() {
  
  // Configure ADC, SerialPort, WIFI and UDP
  
  MyClient.setUpADC();  
  MyClient.setUpSerialPort(115200);
  MyClient.setUpWIFI();
  MyClient.beginUDP(); 
}
  
void loop() {
  
  // Reading values from potentiometers and send it to server by UDP packet every 10 ms
  
  MyClient.startUDPpacket();
  
  for (int channel_i=0; channel_i<MyClient.getNumPot(); channel_i++){
    MyClient.readPotValue(channel_i);
    MyClient.sendPotValue(channel_i);
  }
  Serial.println(" ");
    
  MyClient.endUDPpacket();
  
  delay(10);
}
