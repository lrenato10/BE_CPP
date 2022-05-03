/*
 * Some remarks:
 * 1 - This class was created to facilitate the operator overloading of somme of two bytes (MSB+LSB) used in Server.cpp
 * 2 - Operator outside of the class because it doesn't change either LSB or MSB (objects of the this class)
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

/**
 * Operator to concatenate MSB and LSB
 * Operator of Byte_Class outside of the class
 */
int operator + (const Byte_Class& msb, const Byte_Class& lsb);
