
#ifndef MITLight_h
#define MITLight_h

#include "Arduino.h"
#include "Adafruit_WS2801.h"

class MITLight{
  
  public:
    MITLight(int dataPin, int clockPin);
    void initialize();
    uint32_t createColorFromRGB(byte R, byte G, byte B);
    void setPixel(int pixel, uint32_t color);
    void setMajorAndMinorColors(uint32_t majorColor, uint32_t minorColor);
    void colorWipe(uint32_t color, uint8_t wait);
    
  private:
    int _dataPin;
    int _clockPin;
    Adafruit_WS2801 _LEDStrip; 
};


#endif
