#include "Adafruit_NeoPixel.h"
#include <math.h>

#define PIN 13
#define NUMPIXELS 144

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int power = 200;
int qlenghtMain = 30;   // Queue grandes comètes
int qlenghtMini = 6;    // Queue mini-comètes

// Grandes comètes
float position1 = 0;
int direction1 = 1;
float position2 = NUMPIXELS-1;
int direction2 = -1;

int degrade = 0;
int galaxie = 0;

// Mini-comètes
struct MiniComete {
  float pos;
  int dir;
  bool active;
};
MiniComete miniCometes[8];
bool miniActive = false;

// Flash central étendu aléatoire avec intensité variable
bool flashActive = false;
float flashCenter = 0;

// Mélange couleurs
uint32_t blendColors(uint32_t c1, uint32_t c2){
  uint8_t r1 = (c1 >> 16) & 0xFF;
  uint8_t g1 = (c1 >> 8) & 0xFF;
  uint8_t b1 = c1 & 0xFF;

  uint8_t r2 = (c2 >> 16) & 0xFF;
  uint8_t g2 = (c2 >> 8) & 0xFF;
  uint8_t b2 = c2 & 0xFF;

  return strip.Color(
    min(255, r1+r2),
    min(255, g1+g2),
    min(255, b1+b2)
  );
}

// Traînée exponentielle
float tailFade(int q, int qlen){
  float x = (float)q/qlen;
  return exp(-1.2*x);
}

void setup(){
  Serial.begin(9600);
  strip.setBrightness(power);
  strip.show();
}

// Dessin mini-comètes
void drawMiniCometes(){
  for(int i=0;i<8;i++){
    if(!miniCometes[i].active) continue;
    for(int q=0;q<qlenghtMini;q++){
      int pixel = (int)miniCometes[i].pos + (miniCometes[i].dir==1?-q:q);
      if(pixel>=0 && pixel<NUMPIXELS){
        uint8_t brightness = power*tailFade(q,qlenghtMini);
        uint32_t color = strip.gamma32(strip.Color(brightness, brightness/2, brightness));
        uint32_t existing = strip.getPixelColor(pixel);
        strip.setPixelColor(pixel, blendColors(existing,color));
      }
    }
    miniCometes[i].pos += miniCometes[i].dir*1.5;
    if(miniCometes[i].pos<0 || miniCometes[i].pos>=NUMPIXELS) miniCometes[i].active=false;
  }

  // Vérifie si toutes mini-comètes sont terminées
  bool anyActive=false;
  for(int i=0;i<8;i++) if(miniCometes[i].active) anyActive=true;
  if(!anyActive) flashActive=false; // Flash s’éteint après explosion
  if(!anyActive) miniActive=false;
}

void loop(){
  strip.clear();

  // Fond galaxie
  for(int i=0;i<NUMPIXELS;i++){
    float vague = sin((i*0.15) + galaxie*0.02);
    int bright = map(vague*100,-100,100,10,50);
    uint32_t couleur = strip.gamma32(strip.ColorHSV(45000 + i*300,255,bright));
    strip.setPixelColor(i,couleur);
    if(random(0,1000)<4) strip.setPixelColor(i,strip.Color(80,80,120));
  }
  galaxie+=20;

  if(!miniActive){
    // Grandes comètes
    for(int q=0;q<qlenghtMain;q++){
      int pixel1 = (int)position1 + (direction1==1?-q:q);
      if(pixel1>=0 && pixel1<NUMPIXELS){
        uint8_t brightness = power*tailFade(q,qlenghtMain);
        uint32_t color = strip.gamma32(strip.ColorHSV(degrade+q*1000,255,brightness));
        strip.setPixelColor(pixel1, blendColors(strip.getPixelColor(pixel1),color));
      }

      int pixel2 = (int)position2 + (direction2==-1?q:-q);
      if(pixel2>=0 && pixel2<NUMPIXELS){
        uint8_t brightness = power*tailFade(q,qlenghtMain);
        uint32_t color = strip.gamma32(strip.ColorHSV(degrade+30000+q*1500,255,brightness));
        strip.setPixelColor(pixel2, blendColors(strip.getPixelColor(pixel2),color));
      }
    }

    // Avance grandes comètes
    position1 += direction1*1.8;
    position2 += direction2*1.8;

    // Rebond
    if(position1>=NUMPIXELS-1){position1=NUMPIXELS-1;direction1=-1;}
    if(position1<=0){position1=0;direction1=1;}
    if(position2>=NUMPIXELS-1){position2=NUMPIXELS-1;direction2=-1;}
    if(position2<=0){position2=0;direction2=1;}

    // Collision
    if(abs((int)position1-(int)position2)<3){
      miniActive=true;
      flashActive=true;
      flashCenter = (position1+position2)/2;

      // Init 8 mini-comètes espacées de 4 LEDs
      for(int i=0;i<8;i++){
        miniCometes[i].pos = flashCenter + (i-3.5)*4;
        miniCometes[i].dir = (i%2==0?-1:1);
        miniCometes[i].active=true;
      }

      // Reset grandes comètes
      position1=0; direction1=1;
      position2=NUMPIXELS-1; direction2=-1;
    }
  }else{
    drawMiniCometes();
  }
    // Flash central aléatoire avec dégradé d'intensité
  if(flashActive){
    for(int f=-10; f<=10; f++){
      int p = (int)flashCenter + f;
      if(p>=0 && p<NUMPIXELS){
        if(random(0,100) < 60){ // 60% chance d’allumer cette LED
          uint8_t intensity = random(20, 80); // intensité variable pour effet “vivant”
          strip.setPixelColor(p, strip.Color(intensity, intensity, intensity));
        }
      }
    }
  }
  strip.show();
  delay(10);
  degrade+=500;
}