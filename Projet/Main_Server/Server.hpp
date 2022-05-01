#include "Client_Server.hpp"
#include "Byte_Class.hpp" 
#include <vector>
#include <Servo.h>

class Server_Class : public Client_Server {
  private:
    WiFiUDP UDP;
    IPAddress local_IP;
    IPAddress gateway;
    IPAddress subnet;//mask
    Servo servo; // create servo object
    Byte_Class MSB=0;
    Byte_Class LSB=0;
    int angle=0;
    short int pot_value;

  public:
      Server_Class(String login, String password, int port, byte octet1, byte octet2, byte octet3, byte octet4) :
      Client_Server::Client_Server(login, password, port) , local_IP(octet1, octet2, octet3, octet4),
      gateway(octet1, octet2, octet3, octet4), subnet(255,255,255,0) {};
      
      void setUpAP();
      void beginUDP();
      void receivePacket();
      void servoConfig();
};
