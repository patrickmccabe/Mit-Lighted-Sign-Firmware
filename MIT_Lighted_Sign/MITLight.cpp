
#include "Arduino.h"
#include "MITLight.h"
#include "SPI.h"

MITLight:: MITLight(int dataPin, int clockPin){
  _dataPin = dataPin;
  _clockPin = clockPin;
}


void MITLight:: initialize(){
  _LEDStrip = Adafruit_WS2801(25, _dataPin, _clockPin); // creates the LED strip object
  _LEDStrip.begin();                                    // initialize the LED strip object
  _LEDStrip.show();                     // Update LED contents, to start they are all 'off'
}



// A helper method - takes three bytes representing an RGB color and returns a
// 24 bit color
uint32_t MITLight:: createColorFromRGB(byte R, byte G, byte B){
  uint32_t color;
  color = R;
  color <<= 8;
  color |= G;
  color <<= 8;
  color |= B;
  return color;
}
