#include "Byte_Class.hpp" 
#include <Arduino.h>

/**
 * Contructor of Byte_Class Class
 * @param value of byte
 */
Byte_Class::Byte_Class(char b){
  this->b=b;
}

char Byte_Class::getByte() const{
  return b;
}

void Byte_Class::setByte(char value){
  b=value;
}

/**
 * Operator to concatenate MSB and LSB
 * Operator of Byte_Class outside of the class
 */
int operator + (const Byte_Class& msb, const Byte_Class& lsb) {// to concatenate two bytes
  return (msb.getByte()<<8)+lsb.getByte();
}
