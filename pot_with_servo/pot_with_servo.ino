#include "Servo.h"

#define pin_pot A0
#define pin_servo D5

Servo servo; // création de l'objet "servo"

void setup() {
   servo.attach(pin_servo); // attache le servo au pin spécifié
   pinMode(pin_pot, INPUT);
   pinMode(pin_servo, OUTPUT);
   Serial.begin(9600); // ouvre le port série
}

void loop() {
   int val = analogRead(pin_pot); // lit la valeur actuelle du potentiomètre
   // mise à l'échelle pour renvoyer la position entre 0 et 180°
   val = map(val, 0, 1023, 0, 180);
  
   Serial.println(val);
   Serial.println();
   
   servo.write(val);
   delay(100); // attend 100 ms
}
