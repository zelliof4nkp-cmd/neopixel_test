#include "Adafruit_NeoPixel.h"
#define PIN  13
#define NUMPIXELS 15
Adafruit_NeoPixel strip (NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
   strip.begin();
   strip.setBrightness(255);  // luminosité de la LED (maximum 255)
   Serial.begin(9600);
}

void loop() {
   strip.setPixelColor(0, strip.Color(255, 0, 0));
   strip.show();
   delay(500);
   Serial.println("Pix 0");
   //strip.clear();

   strip.setPixelColor(1, strip.Color(0, 0, 255));
   strip.show();
   delay(500);
   Serial.println("Pix 1");
   //strip.clear();

   strip.setPixelColor(2, strip.Color(255, 255, 255));
   strip.show();
   delay(500);
   Serial.println("Pix 2");
   //strip.clear();

}