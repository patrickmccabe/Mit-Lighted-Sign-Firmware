#include "SPI.h"
#include "Adafruit_WS2801.h"



#define dataPin  3    // Yellow wire on Adafruit Pixels
#define clockPin 4    // Green wire on Adafruit Pixels
#define lightSensor A0

boolean lightSensitive = false;

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin);

char incoming[40];
int in_index = 0;
int decode_index = 0;

int majorityR;
int majorityG;
int majorityB;
int minorityR;
int minorityG; 
int minorityB; 
int lightThreshold = 0;

boolean demo = true;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(3000);
  strip.begin();
  pinMode(lightSensor, INPUT);
  // Update LED contents, to start they are all 'off'
  strip.show();
}


void loop() {
  // Some example procedures showing how to display to the pixels
  
  //if (listen()){ //listen for serial data from the processing sketch
  // decode(); //decode that data recieved
  // displayWirelessColors();
  //}
  
  if(Serial.available()){
     Serial.readBytesUntil('D',incoming,13);
     decode();
     //displayWirelessColors();
     demo = false;
  }
  
  colorWipe(Color(0, 0, 0), 40);
  delay(500);
 
  if((lightSensitive && analogRead(lightSensor) >= lightThreshold) || lightSensitive == false){  // runs lights if in light sensitive mode and it is dark, or if not in light sensitive mode.
  
    if(demo == false){
      displayWirelessColors(); 
      delay(20000);
    }
  
    pcolorWipe(Color(255, 0, 0), 0);
    delay(2000);
    pcolorWipe(Color(0, 255, 0), 0);
    delay(2000);
    pcolorWipe(Color(0, 0, 255), 0);
    delay(2000);
  
    colorWipe(Color(255, 0, 0), 40);
    delay(1000);
    colorWipe(Color(0, 255, 0), 80);
    delay(1000);
    colorWipe(Color(0, 0, 255), 120);
    delay(1000);
  
  
    uint32_t colors[] = {Color(255,0,0), Color(0,255,0), Color(0,0,255), Color(100,255,0), Color(0,100,255), Color(0,255,100)};
    streamCheckard(colors,6,15,300);
  
    rainbow(40);
    rainbowCycle(10);
    
  }
  
}

void streamCheckard(uint32_t colors[],int sizeOfArray, int times, int wait){
  uint32_t lights[20];
  for(int i=0; i<20; i++){
    lights[i] = Color(0,0,0);
  }
  for(int i=0; i<times; i++){ // stream for the correct number of times
    for(int j=0; j<sizeOfArray; j++){ // loop through the colors
      lights[0] = colors[j];
      for(int k=0; k<20; k++){ // display the LED lights
        strip.setPixelColor(k,lights[k]);
      }
      strip.show();
      delay(wait);
      for(int l=19; l>0; l--){ // shift the lights
        lights[l] = lights[l-1];
      }
    }
  }
}



void displayWirelessColors(){
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
      if(i < 12 ||  i>14){
        strip.setPixelColor(i, Color(majorityR, majorityG, majorityB));
        strip.show();
      }
      else{
        strip.setPixelColor(i, Color(minorityR, minorityG, minorityB));
        strip.show();
      }
  }
}

void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;
  
  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}


// fill the dots one after the other with said color
// good for testing purposes
void pcolorWipe(uint32_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
      if(i < 12 ||  i>14){
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
      }
      else{
        strip.setPixelColor(i, Color(255,85,0));
        strip.show();
      }
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

boolean listen(){
  int bite=0; 
  long start = millis();
 
  //read in the incomming data, block for a while, then timeout if taking too long
  
  while(millis() - start < 7000) {
    if(Serial.available()){      
       bite = Serial.read();
       if(in_index == 4 ){
         //rainbow(20);
       }
       incoming[in_index++] = bite;
       if(bite == 'D'){ //stop reading
         in_index=0;
         return true;
       }
    }
    else{
      delay(3);
    }
  }
  in_index=0;
  return false; //if got here, then timed out
}


void decode(){
  
  if(incoming[decode_index++] == 'M'){
    majorityR = incoming[decode_index++];
    majorityG = incoming[decode_index++];
    majorityB = incoming[decode_index++];  
  }      
  
  if(incoming[decode_index++] == 'm' ){
     minorityR = incoming[decode_index++];
     minorityG = incoming[decode_index++];
     minorityB = incoming[decode_index++];
  }   
  if(incoming[decode_index++] == 'l'){
    lightSensitive = (incoming[decode_index++] == 1);
    lightThreshold = int(incoming[decode_index]) + 900;
  }
                
 decode_index=0;
}
