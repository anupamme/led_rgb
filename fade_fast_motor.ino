#include "Adafruit_DotStar.h"
#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 30

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
      // Uncomment/edit one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
//      FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
      // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
      
      // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, RGB>(leds, NUM_LEDS);

      // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
       FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
        pinMode( 6 , OUTPUT);  // Must be a PWM pin
}

void loop() { 
  sunrise();
  
  FastLED.show();
    FastLED.delay(1000/10); 
}

extern const TProgmemRGBPalette16 SimColors_p FL_PROGMEM =
{
    CRGB::Blue,
    CRGB::Aqua,
    CRGB::Purple,
    CRGB::Green,
    
    CRGB::Blue,
    CRGB::Aqua,
    CRGB::Purple,
    CRGB::Green,
    
    CRGB::Blue,
    CRGB::Aqua,
    CRGB::Purple,
    CRGB::Green,
    
    CRGB::Blue,
    CRGB::Aqua,
    CRGB::Purple,
    CRGB::Green
};

extern const TProgmemRGBPalette16 SimRainbowColors_p FL_PROGMEM =
{
    0xFF0000, 0xD52A00, 0x56D500, 0x00D52A, 
    0x00AB55, 0x00FFFF, 0x008080, 0x0000FF, 
    0x2A00D5, 0x5500AB, 0x7F0081, 0xAB0055, 
    0xD5002B, 0xFF1493, 0xFFB6C1, 0xFFFFFF
};
static const float sunriseLength = 0.3;
// how often (in seconds) should the heat color increase?
  // for the default of 30 minutes, this should be about every 7 seconds
  // 7 seconds x 256 gradient steps = 1,792 seconds = ~30 minutes
//  static const uint8_t interval = (sunriseLength * 60) / 256;
  static const float interval = ((float)(sunriseLength * 60) / 256)*1000;
static uint8_t heatIndex = 0; // start out at 0

void change_color() {
    if(heatIndex < 255)
          heatIndex += 10;
        if (heatIndex > 255)
            heatIndex = 255;
      else{
//          delay(2500);
//          fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
          heatIndex = 0;
      }
      CRGB color = ColorFromPalette(SimRainbowColors_p, heatIndex);
      fill_solid(leds, NUM_LEDS, color);
}



void sunrise() {
    
    analogWrite( 6 , 153 );  // 60% duty cycle
 delay(500);              // play for 0.5s

 analogWrite( 6 , 0 );    // 0% duty cycle (off)
//    change_color()  
    
    
 delay(4000);             // wait for 4s
     
    EVERY_N_MILLISECONDS(interval ) { 
    change_color();
  }
}