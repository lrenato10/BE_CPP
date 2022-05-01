#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

class Client_Server{
  protected:
      String login_network;
      String password_network;
      int UDP_port;
      char SB='S', EB='E', P0='A', P1='B',P2='C', P;     

  public:
      Client_Server(String login, String password, int port){
        login_network = login;
        password_network = password;
        UDP_port = port;
      }
      void setUpSerialPort(int baud_rate);

      //gets
      String getLogin(){
        return login_network; 
      }
      String getPassword(){
        return password_network; 
      }
      int getPort(){
        return UDP_port; 
      }
        
};
