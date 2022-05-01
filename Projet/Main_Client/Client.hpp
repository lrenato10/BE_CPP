#include "Client_Server.hpp"
#include "Byte_Class.hpp" 
#include <map>
#include <Servo.h>
#include <Adafruit_ADS1X15.h>

class Client_Class : public Client_Server {
  private:
    Adafruit_ADS1115 ads;
    WiFiUDP UDP;
    IPAddress remote_IP;
    Byte_Class MSB=0;
    Byte_Class LSB=0;
    std::map<String, byte> TwoBytes;
    int16_t adc[3];
    short int numPot;
    
  public:
      Client_Class(String login, String password, int port, byte octet1, byte octet2, byte octet3, byte octet4, short int npot) :
      Client_Server::Client_Server(login, password, port) , remote_IP(octet1, octet2, octet3, octet4), numPot(npot)
      {};
      
      void setUpADC();
      void setUpWIFI();
      void beginUDP();
      std::map<String, byte> MSBandLSB(int16_t adc_value);
      void readPotValue(short int index_pot);
      void sendPotValue(short int index_pot);
      short int getNumPot();
      void startUDPpacket();
      void endUDPpacket();
      
};
