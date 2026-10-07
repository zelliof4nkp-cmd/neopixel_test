#include <Adafruit_NeoPixel.h>

#define LED_PIN 13
const int LED_COUNT = 144;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Paramètres vagues
float waveOffset = 0;

// Positions animaux
float dolphinPos = 0.0;
float jellyPos = 0.5;
bool jellyBlink = true;

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(120);
}

void loop() {
  // Vagues
  for (int i = 0; i < LED_COUNT; i++) {
    float wave = sin(i * 0.5 + waveOffset) * 40;
    int r = 0;
    int g = constrain(50 + wave, 0, 150);
    int b = constrain(100 + wave, 0, 255);
    strip.setPixelColor(i, strip.Color(r, g, b));
  }

  // Dauphin (LED bleue claire)
  int dolphinLED = (int)(dolphinPos * LED_COUNT);
  if (dolphinLED < LED_COUNT) strip.setPixelColor(dolphinLED, strip.Color(0, 200, 255));

  // Méduse (LED rose/violette clignotante)
  int jellyLED = (int)(jellyPos * LED_COUNT);
  if (jellyLED < LED_COUNT) {
    if (jellyBlink) strip.setPixelColor(jellyLED, strip.Color(255, 0, 200));
    else strip.setPixelColor(jellyLED, strip.Color(150, 0, 150));
  }

  strip.show();

  // Mise à jour animation
  waveOffset += 0.5;       // vagues rapides
  dolphinPos += 0.01;      // dauphin avance
  jellyPos += 0.008;       // méduse avance
  jellyBlink = !jellyBlink;

  if (dolphinPos > 1.0) dolphinPos = 0;
  if (jellyPos > 1.0) jellyPos = 0;

  delay(20);
}