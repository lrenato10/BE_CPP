/*
 * Some remarks:
 * 1 - This class was created to facilitate the operator overloading of somme of two bytes (MSB+LSB) used in Server.cpp
 * 2 - Normally the operator code would be in the Byte_Class.cpp but the Arduino IDE would not allow it so it was placed in the Server.cpp 
 */

class Byte_Class{
  private:
      // Value of byte
      char b;
  public:
      Byte_Class(char b){
        this->b=b;
      }
      char getByte() const;
      void setByte(char value);
};
