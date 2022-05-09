#include "Client_Server.hpp"
#include "Byte_Class.hpp" 
#include <map>
#include <Servo.h>

class Server_Class : public Client_Server {
  private:
    //UDP object
    WiFiUDP UDP;
    // Local IP address
    IPAddress local_IP;
    // Gateway address
    IPAddress gateway;
    // Mask of subnet
    IPAddress subnet;
    // Create servo objects
    Servo servo0, servo1, servo2;
    // Map of servo motor and its wanted angle
    std::map<String, int> Servos_Angle;
    // Most Significant Byte of UDP message
    Byte_Class MSB=0;
    // Less Significant Byte of UDP message
    Byte_Class LSB=0;
    // Angles of servo motor
    int angle0=0, angle1=0,angle2=0;
    // Counter of connection loss
    short int failure_counter=0;

  public:
     /**
      * Contructor of Server Class with heritage of  Client_Server Classs
      * @param network name, password, port, local IP (4 octets), gateway IP, subnet mask 
      */ 
      Server_Class(String login, String password, int port, byte octet1, byte octet2, byte octet3, byte octet4) :
      Client_Server::Client_Server(login, password, port) , local_IP(octet1, octet2, octet3, octet4),
      gateway(octet1, octet2, octet3, octet4), subnet(255,255,255,0) {};
      /**
       * @brief Configure and start the access point 
       */
      void setUpAP();

      /**
        * @brief Configure UDP port 
        */
      void beginUDP();

      /**
        * Receive the packet from client 
        * Syncronise the begin of the packet read 
        * Read and stock the angles for the servo motor in the STL map
        */
      void receivePacket();

      /**
       * @brief Write motor angles to servo motors and in the screen
       */      
      void writeMotorAngles();

      /**
       * @brief Configure servo motors 
       */
      void servoConfig();
};
