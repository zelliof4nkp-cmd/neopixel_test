/*Balayage multicolors*/

#include "Adafruit_NeoPixel.h"
#define PIN 13
#define NUMPIXELS 144
Adafruit_NeoPixel strip (NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int power =40; 

void setup() {
   strip.begin();
   strip.setBrightness(power);  // luminosité de la LED (maximum 255)
   Serial.begin(9600);
}

void set_light(int led){
    //randomSeed(analogRead(A0));//peut etre 
    int rouge = random(15, 255);//remplacer le powr par 255
    //randomSeed(analogRead(A1));
    int vert = random(15, 255);
    //randomSeed(analogRead(A2));
    int bleu = random(15, 255);

    rouge= (rouge * rouge) / 255; // Augmente les valeurs
    vert = (vert * vert) / 255;
    bleu = (bleu * bleu) / 255;

    strip.setPixelColor(led, strip.Color(rouge, vert, bleu));
    strip.show();
    delay(20);
}

void loop() {

  for (int i =0;i < NUMPIXELS;i++){
    set_light(i);
  }
    
  for (int i =NUMPIXELS-1;i > 0;i--){
    set_light(i);
  }

}
