#include <FastLED.h>

#define PIN 6
#define pixelLen 25//MUST BE SET BEFORE DOWNLOAD

CRGB strip[pixelLen];

boolean smartDelay(int ms) {
  long startMs = millis(); //get the time
  while (millis() < (startMs + ms)) {
    yield(); //do nothing?
    if (Serial.available()) {
      return false; //back out to get new command
    }
  }
  return true;
}

void rain(byte r, byte g, byte b, int delayMs) {
  int trailLen = 1;//round(pixelLen/delayMs);
  int offset = 4 + trailLen;
  int k;
  for (int q = 0; q < offset; q++) {
    for (int i = 0; i < (pixelLen + trailLen + 1); i = i + offset) {
      if ((i + q) >= 0 && (i + q) < pixelLen) {
        strip[i + q] = CRGB(r, g, b);
      }
      for (int w = 0; w < trailLen; w++) {
        k = w + 1;
        int rf = round(r / (k * k));
        int gf = round(g / (k * k));
        int bf = round(b / (k * k));
        int curpos = i + q - k;
        if (curpos >= 0 && curpos < pixelLen) {
          strip[curpos] = CRGB(rf, gf, bf);
        }
        if ((i + q - (trailLen + 1)) >= 0 && (i + q - (trailLen + 1)) < pixelLen) {
          strip[i + q - (trailLen + 1)] = CRGB(0,255,0);
        }
        smartDelay(2);
      }
    }
    FastLED.setBrightness(50);
    FastLED.show();
    smartDelay(delayMs);
  }
}

void setup() {
  Serial.begin(115200);

  FastLED.addLeds<NEOPIXEL, PIN>(strip, pixelLen).setCorrection(TypicalLEDStrip);

  Serial.println("Box_Online");
}

void loop() {
//  fill_solid( strip, pixelLen, CRGB(0,255,0));
  rain(255,0,0,100);
}
