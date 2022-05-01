class Byte_Class{
  private:
      char b;
  public:
      
      Byte_Class(char b){
        this->b=b;
      }
      char getByte() const;
      void setByte(char value);
};
