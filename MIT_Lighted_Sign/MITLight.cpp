
#include "Arduino.h"
#include "MITLight.h"
#include "SPI.h"

MITLight:: MITLight(int dataPin, int clockPin){
  _dataPin = dataPin;
  _clockPin = clockPin;
}


