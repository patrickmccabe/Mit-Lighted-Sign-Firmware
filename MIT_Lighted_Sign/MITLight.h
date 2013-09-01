
#ifndef MITLight_h
#define MITLight_h

#include "Arduino.h"
#include "Adafruit_WS2801.h"

class MITLight{
  
  public:
    MITLight(int dataPin, int clockPin);
    void initialize();
    
  private:
    int _dataPin;
    int _clockPin;
    Adafruit_WS2801 _LEDStrip; 
};


#endif
