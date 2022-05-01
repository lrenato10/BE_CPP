#include "Client_Server.hpp"
#include <map>
#include <Servo.h>
#include <Adafruit_ADS1X15.h>

class Client_Class : public Client_Server {
  private:
    //ADC object
    Adafruit_ADS1115 ads;
    //UDP object
    WiFiUDP UDP;
    //IP of server
    IPAddress remote_IP;
    //Map of two bytes (MSB and LSB)
    std::map<String, byte> TwoBytes;
    //Number of potentiometers
    short int numPot;
    //Array of ADC values
    int16_t adc[];
    
  public:
    /**
     * Contructor of Client Class with heritage of  Client_Server Classs
     * @param network name, password, port, remote IP (4 octets), number of potentiometers
     */ 
    Client_Class(String login, String password, int port, byte octet1, byte octet2, byte octet3, byte octet4, short int npot) :
    Client_Server::Client_Server(login, password, port) , remote_IP(octet1, octet2, octet3, octet4), numPot(npot)
    {//adc[npot];
    };
    /**
     * @brief Configure ADC converter ADS1115 
     */ 
    void setUpADC();
    
    /**
     * @brief Configuration and verification of WIFI connection 
     */
    void setUpWIFI();
    
    /**
    * @brief Configure UDP port 
    */
    void beginUDP();
    
    /**
     * Separate a number of 16 bits in two bytes (MSB and LSB)
     * @param adc_value value from ADC
     * @return TwoBytes map with MSB and LSB
     */ 
    std::map<String, byte> MSBandLSB(int16_t adc_value);

    /**
     * @brief Read potentiometer value of a specific channel (index_pot)
     */
    void readPotValue(short int index_pot);

    /**
     * @brief Send potentiometer value of a specific channel (index_pot) to the server via UDP
     */
    void sendPotValue(short int index_pot);

    /**
     * @brief Begin UDP packet and send start byte
     */
    void startUDPpacket();

    /**
     * @brief Finish UDP packet and send end byte
     */
    void endUDPpacket();

    short int getNumPot();
};
