#include "Client_Server.hpp"

/**
 * Contructor of Client_Server Class
 * @param network name, password, port
 */
Client_Server::Client_Server(String login, String password, int port){
  login_network = login;
  password_network = password;
  UDP_port = port;
}

/**
 * Configure serial port
 * @param baund_rate of the communication 
 */
void Client_Server::setUpSerialPort(int baud_rate){
  Serial.begin(baud_rate);
  Serial.println();
}

// Differents get fonctions  
String Client_Server::getLogin(){
  return login_network; 
}
String Client_Server::getPassword(){
  return password_network; 
}
int Client_Server::getPort(){
  return UDP_port; 
}
