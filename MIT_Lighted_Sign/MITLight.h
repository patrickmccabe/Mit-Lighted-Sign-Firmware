
#ifndef MITLight_h
#define MITLight_h

#include "Arduino.h"

class MITLight{
  
  public:
    MITLight(int dataPin, int clockPin);
    
  private:
    int _dataPin;
    int _clockPin;
    
 
};


#endif
