#include "Client.hpp"

/**
 * @brief Configure ADC converter ADS1115 
 */ 
void Client_Class::setUpADC(){
  ads.begin();
}

/**
 * @brief Configuration and verification of WIFI connection 
 */ 
void Client_Class::setUpWIFI(){
  WiFi.begin(login_network, password_network);
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.print(login_network);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

/**
 * @brief Configure UDP port 
 */
void Client_Class::beginUDP(){
  UDP.begin(UDP_port);
  Serial.print("Opening UDP port ");
  Serial.println(UDP_port);
}

/**
 * Separate a number of 16 bits in two bytes (MSB and LSB)
 * @param adc_value value from ADC
 * @return TwoBytes map with MSB and LSB
 */
std::map<String, byte> Client_Class::MSBandLSB(int16_t adc_value){
  TwoBytes["MSB"]=byte(adc_value>>8);
  TwoBytes["LSB"]=byte(adc_value&0xff);
  return TwoBytes;
}

/**
 * @brief Read potentiometer value of a specific channel (index_pot)
 */
void Client_Class::readPotValue(short int index_pot){
  adc[index_pot] = ads.readADC_SingleEnded(index_pot);
  Serial.print("AIN");
  Serial.print(index_pot);
  Serial.print(": ");
  Serial.println(adc[index_pot]);
  MSBandLSB(adc[index_pot]);
}

/**
 * @brief Send potentiometer value of a specific channel (index_pot) to the server via UDP
 */
void Client_Class::sendPotValue(short int index_pot){
  UDP.write(P0+index_pot);//works if P0 P1 and P2 are sequential in ASCII table
  UDP.write(TwoBytes["MSB"]);
  UDP.write(TwoBytes["LSB"]);
}

/**
 * @brief Begin UDP packet and send start byte
 */
void Client_Class::startUDPpacket(){
  UDP.beginPacket(remote_IP, UDP_port);
  UDP.write(SB);
}

/**
 * @brief Finish UDP packet and send end byte
 */
void Client_Class::endUDPpacket(){
  UDP.write(EB);
  UDP.endPacket();
}

short int Client_Class::getNumPot()
{
  return numPot;
}
