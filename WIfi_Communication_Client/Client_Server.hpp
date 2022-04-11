#include <Arduino.h>

class Client_Server{
  private:
      String login_network = "Network";
      String password_network = "password";
      int UDP_port = 4210;

  public:
      void setUpSerialPort(int baud_rate);
        
};
