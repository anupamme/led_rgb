#include "Thread.h"
#include "Adafruit_DotStar.h"
#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 20

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define CLOCK_PIN 13
#define MOTOR_PIN 6

// Define the array of leds
CRGB leds[NUM_LEDS];

Thread myThread = Thread();

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
        pinMode(MOTOR_PIN, OUTPUT);  // Must be a PWM pin
        myThread.onRun(run_motor);
	   myThread.setInterval(500);
}

void loop() { 
  sunrise();
  FastLED.show();
  if(myThread.shouldRun())
		myThread.run();
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
    0xFF1493, 0xFFB6C1, 0x56D500, 0x00D52A, 
    0x00AB55, 0x00FFFF, 0x008080, 0x0000FF, 
    0x2A00D5, 0x5500AB, 0xDA70D6, 0x7F0081, 
    0xAB0055, 0xFF1493, 0xFFB6C1, 0xFFFFFF
};

//extern const TProgmemRGBPalette16 SimRainbowColors_p FL_PROGMEM =
//{
//    0x00AB55, 0x008080, 0x0000FF, 0x7F0081, 
//    0xFF1493, 0x00AB55, 0x008080, 0x0000FF, 
//    0x7F0081, 0xFF1493, 0x00AB55, 0x008080,
//    0x0000FF, 0xFF1493, 0xFFB6C1, 0xFFFFFF
//};

//extern const TProgmemRGBPalette16 SimRainbowColors_p FL_PROGMEM =
//{
//    0xFF69B4, 0xFF69B4, 0xFF69B4, 0xFF69B4,
//    0xFF69B4, 0xFF69B4, 0xFF69B4, 0xFF69B4, 
//    0x7F0081, 0x7F0081, 0x7F0081, 0x7F0081,
//    0x7F0081, 0x7F0081, 0x7F0081, 0x7F0081
//};

//extern const TProgmemRGBPalette16 SimRainbowColors_p FL_PROGMEM =
//{
//    0xFF0000, 0xD52A00, 0x56D500, 0x00D52A, 
//    0x00AB55, 0x00FFFF, 0x008080, 0x0000FF, 
//    0x2A00D5, 0x5500AB, 0x7F0081, 0xAB0055, 
//    0xD5002B, 0xFF1493, 0xFFB6C1, 0xFFFFFF
//};

static const float sunriseLength = 0.3;
static const float interval = ((float)(sunriseLength * 60) / 256)*1000;
static uint8_t heatIndex = 0; // start out at 0

void run_motor() {
 analogWrite(MOTOR_PIN, 153 );  // 60% duty cycle
 delay(500);              // play for 0.5s
 analogWrite(MOTOR_PIN, 0 );    // 0% duty cycle (off)
 delay(4000);             // wait for 4s
}

void sunrise() {
    EVERY_N_MILLISECONDS(interval ) { 
    if(heatIndex < 255)
          heatIndex += 1;
      else{
          delay(2500);
          fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
          heatIndex = 0;
      }
      CRGB color = ColorFromPalette(SimRainbowColors_p, heatIndex);
      fill_solid(leds, NUM_LEDS, color);
      analogWrite(leds, 127);
  }
}