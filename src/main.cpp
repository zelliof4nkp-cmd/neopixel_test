/*Balayage multicolors*/

#include "Adafruit_NeoPixel.h"
#define PIN 3
#define micro_d 2
#define NUMPIXELS 15
unsigned long time=0;
String last_couleur;
Adafruit_NeoPixel strip (NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int power=255;
bool etat_micro;

void setup() {
   strip.begin();
   strip.setBrightness(power);  // luminosité de la LED (maximum 255)
   Serial.begin(9600);
   pinMode(micro_d,INPUT_PULLUP);
}

void set_colors(int red,int green, int bleu,String couleur){
    if (millis() >= time+1000 && couleur != last_couleur){
        time=millis();
        last_couleur=couleur;
        Serial.print(etat_micro);
        Serial.println(" "+couleur);
        for (int i =0;i < NUMPIXELS;i++){
            strip.setPixelColor(i, strip.Color(red, green, bleu));
        }
    strip.show();
    }


    
}

void loop() {


 delay(50);

etat_micro= digitalRead(micro_d);
//Serial.println(etat_micro);

if (etat_micro ==true){
    set_colors(255,0,0,"red");//rouge
}
else
    set_colors(0,255,0,"green");//rouge
}