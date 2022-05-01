#include "Client.hpp"

void Client_Class::setUpADC(){
  ads.begin();
}

void Client_Class::setUpWIFI(){
  // Begin WiFi
  WiFi.begin(login_network, password_network);
  WiFi.mode(WIFI_STA);
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(login_network);
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
}

void Client_Class::beginUDP(){
  UDP.begin(UDP_port);
  Serial.print("Opening UDP port ");
  Serial.println(UDP_port);
}

std::map<String, byte> Client_Class::MSBandLSB(int16_t adc_value){
  TwoBytes["MSB"]=byte(adc_value>>8);
  TwoBytes["LSB"]=byte(adc_value&0xff);
  return TwoBytes;
}

void Client_Class::readPotValue(short int index_pot){
  adc[index_pot] = ads.readADC_SingleEnded(index_pot);
  Serial.print("AIN");
  Serial.print(index_pot);
  Serial.print(": ");
  Serial.println(adc[index_pot]);
  MSBandLSB(adc[index_pot]);
}

void Client_Class::sendPotValue(short int index_pot){
  UDP.write(P0+index_pot);//works if P0 P1 and P2 are sequential in ASCII table
  UDP.write(TwoBytes["MSB"]);
  UDP.write(TwoBytes["LSB"]);
}

short int Client_Class::getNumPot()
{
  return numPot;
}


void Client_Class::startUDPpacket(){
  UDP.beginPacket(remote_IP, UDP_port);
  UDP.write(SB);
}

void Client_Class::endUDPpacket(){
  UDP.write(EB);
  UDP.endPacket();
}
