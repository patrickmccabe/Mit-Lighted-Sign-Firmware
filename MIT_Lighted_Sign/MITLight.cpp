
#include "Arduino.h"
#include "MITLight.h"
#include "SPI.h"
#include "Adafruit_WS2801.h"

MITLight:: MITLight(int dataPin, int clockPin){
  _dataPin = dataPin;
  _clockPin = clockPin;
}
