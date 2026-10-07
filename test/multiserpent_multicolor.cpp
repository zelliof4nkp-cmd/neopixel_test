/*Balayage k200*/

/*
strip.setPixelColor(led, strip.Color(255, 0, 0));
    strip.show();
*/

#include "Adafruit_NeoPixel.h"
#define PIN 13
#define NUMPIXELS 144
Adafruit_NeoPixel strip (NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int power =150; 
int qlenght = 5;
//int qstep = power/qlenght;

int position1 = 0; 
int direction1 = 1;

int position2 = NUMPIXELS -1; 
int direction2= -1;
int degrade = 0;
int galaxie = 0 ;
int colorIndex = 0;

/*uint32_t getCOlor(){
switch(colorIndex) {
    case 0 : return strip.Color(0 , 0, power);
    case 1 : return strip.Color(0 , power, 0);
    case 2 : return strip.Color(power,0, 0);
    case 3 : return strip.Color(power,power, 0);
}
return strip.Color(0 , 0, power);
}
*/
void setup() {
   Serial.begin(9600);
   strip.setBrightness(power);  // luminosité de la LED (maximum 255)
   strip.show();
}

void loop() {
  //int32_t color = getCOlor();

  for (int i =0; i <NUMPIXELS; i ++){

    float vague = sin((i*0.15) + galaxie *0.02);
    int bright = map(vague*100, -100,100,10,50);

    uint32_t couleurdefou = strip.gamma32(
      strip.ColorHSV(45000 + i * 300,255, bright)); 
    
      strip.setPixelColor(i, couleurdefou);

      if(random (0, 1000)<4){
        strip.setPixelColor(i,strip.Color(80,80,120));
      }
      
  }
galaxie +=20;


    for (int q =0 ;q <qlenght ;q++ ){
      int pixel ;

      if(direction1 ==1) {
        pixel = position1 -q;
      }else {
        pixel =position1 + q;
      }
    
      if (pixel >= 0 && pixel < NUMPIXELS){
      //strip.setPixelColor(pixel, color );
      uint8_t brightness = map( q, 0, qlenght, power, 0 );

      uint32_t color = strip.gamma32( 
        strip.ColorHSV( degrade+ q *1000, 255, brightness));

        strip.setPixelColor(pixel, color);
        }
        
        int pixel2 ; 
          if (direction2 == -1)
          {          
        pixel2 = position2 +q;
      }else {
        pixel2 =position2 - q;
      }
    
      if (pixel2 >= 0 && pixel2 < NUMPIXELS){
      //strip.setPixelColor(pixel, color );
      uint8_t brightness = map( q, 0, qlenght, power, 0 );

      uint32_t color2 = strip.gamma32( 
        strip.ColorHSV( degrade+ 30000 + q *1500, 255, brightness));

        strip.setPixelColor(pixel2, color2);
    }
   }
    strip.show();
    delay(14);

    degrade +=500;
    qlenght =30;
    position1 += direction1 ; 
    position2 += direction2 ;

    if (position1 >= NUMPIXELS){
      position1 = NUMPIXELS - 1; 
      direction1 = -1; 
      //colorIndex = (colorIndex +1) %4 ;  
    }
    if (position1 < 0 ){
      position1 = 0; 
      direction1 = 1; 
      //colorIndex = (colorIndex +1) %4 ;  
  }
  if (position2 >= NUMPIXELS){
      position2 = NUMPIXELS - 1; 
      direction2 = -1; 
      //colorIndex = (colorIndex +1) %4 ;  
    }
    if (position2 < 0 ){
      position2 = 0; 
      direction2 = 1; 
      //colorIndex = (colorIndex +1) %4 ;  
  }
}
    
