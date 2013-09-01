
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


// sets the color of an individual pixel
void MITLight:: setPixel(int pixel, uint32_t color){
  _LEDStrip.setPixelColor(pixel,color);
}



// updates the LED strip to display the colors that were set by setPixel
void MITLight:: updateDisplay(){
  _LEDStrip.show();
}



// sets the major and minor colors of the MIT Logo
void MITLight::setMajorAndMinorColors(uint32_t majorColor, uint32_t minorColor) {
  int i;
  
  for (i=0; i < _LEDStrip.numPixels(); i++) { // iterate through all of the pixels
    if(i<12 ||  i>14){                        // if the pixel is a part of the major colors
      _LEDStrip.setPixelColor(i, majorColor); // set the color of that pixel to the major color
    }
    else{                                     // else if the pixel is a part of the minor colors
      _LEDStrip.setPixelColor(i, minorColor); // set the color of that pixel to the minor color
    }
  }
  
  _LEDStrip.show();                           // display the pixels
  
}


// iterates through each pixel, setting them all to the same color
// with some delay between each pixel
void MITLight::colorWipe(uint32_t color, uint8_t wait) {
  int i;
  
  for (i=0; i < _LEDStrip.numPixels(); i++) {
    _LEDStrip.setPixelColor(i, color);
    _LEDStrip.show();
    delay(wait);
  }
}

