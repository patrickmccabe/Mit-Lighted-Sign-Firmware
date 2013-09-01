
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
