/*Balayage multicolors*/

#include "Adafruit_NeoPixel.h"
#define PIN  13
#define NUMPIXELS 144+15
Adafruit_NeoPixel strip (NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int power=80;

void setup() {
   strip.begin();
   strip.setBrightness(power);  // luminosité de la LED (maximum 255)
   Serial.begin(9600);
}

void set_light(int led){
    
    int rouge = random(15, power);
    int vert = random(15, power);
    int bleu = random(15, power);

    rouge= (rouge * rouge) / power; // Augmente les valeurs
    vert = (vert * vert) / power;
    bleu = (bleu * bleu) / power;

    strip.setPixelColor(led, strip.Color(rouge, vert, bleu));
    strip.show();
    delay(50);
}

void loop() {

  for (int i =0;i < NUMPIXELS;i++){
    set_light(i);
  }

  strip.fill(0,0,0);

  for (int i =NUMPIXELS-1;i > 0;i--){
    set_light(i);
  }

  strip.fill(0,0,0);

}
