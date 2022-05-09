#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

class Client_Server{
  protected:
    // Name of WIFI network
    String login_network;
    // Password of WIFI network
    String password_network;
    // Port of socket
    int UDP_port;
    // Chars used in UDP packet
    char SB='S', EB='E', P0='A', P1='B',P2='C', P;     

  public:
    /**
     * Contructor of Client_Server Class
     * @param network name, password, port
     */
      
    Client_Server(String login, String password, int port);
    
    /**
    * Configure serial port
    * @param baund_rate of the communication 
    */
    void setUpSerialPort(int baud_rate);

    // Differents get fonctions 
    String getLogin();
    String getPassword();
    int getPort();
        
};
