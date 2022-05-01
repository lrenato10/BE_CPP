#include "Byte_Class.hpp" 
#include <Arduino.h>

char Byte_Class::getByte() const{
  return b;
}

void Byte_Class::setByte(char value){
  b=value;
}
