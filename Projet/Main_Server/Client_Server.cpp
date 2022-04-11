#include "Client_Server.hpp"

void Client_Server::setUpSerialPort(int baud_rate){
  Serial.begin(baud_rate);
  Serial.println();
}
