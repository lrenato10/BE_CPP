#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Servo.h>
#include <Arduino.h>
#include <map>
 
// Set AP credentials
#define AP_SSID "Rede"
#define AP_PASS "senha123"
 
// UDP
WiFiUDP UDP;
IPAddress local_IP(192,168,4,1);//server IP
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);//masque
#define UDP_PORT 4210

#define pin_servo D5
Servo servo; // create servo object

// UDP Buffer
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer for communication
short int pot_value;
char SB='S', EB='E';
std::map<String ,byte> Byte_Value; //pot values in byte

int angle=0;

void setup() {

  //servo
  servo.attach(pin_servo); // attach servo pin
  pinMode(pin_servo, OUTPUT);
  
  // Setup LED pin
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Setup serial port ========== debug
  Serial.begin(115200);
  Serial.println();
 
  // Begin Access Point
  Serial.println("Starting access point...");
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.println(WiFi.localIP());
 
  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);
 
}
 
void loop() {
 
  // Receive packet
  UDP.parsePacket();// check presence of UDP packet
  //UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);

  SB=UDP.read();
  if (SB=='S'){
    Byte_Value["MSB"]=UDP.read();
    Byte_Value["LSB"]=UDP.read();
    EB=UDP.read();

    //opperateur
    pot_value=(Byte_Value["MSB"]<<8)+Byte_Value["LSB"];
    //opperateur
    
    angle = map(pot_value, 0, 1023, 0, 180);
    Serial.println(pot_value);
    servo.write(angle);
  }

  
  if (packetBuffer[0]){
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Empty");
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }      
 
} 