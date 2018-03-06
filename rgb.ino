//turn on 30 led to pink
//wait for 5 sec
//transition to green 
//wait for 5 sec
//transition to blue 
//wait for 5 sec
//repeat


#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 30 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    11
#define CLOCKPIN   13
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

// Runs 10 LEDs at a time along strip, cycling through red, green and blue.
// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.
 
int head  = 0; // Index of first 'on' and 'off' pixels
// pink color
uint8_t r = 255;
uint8_t g = 105;
uint8_t b = 180;
uint8_t state = 0;
int brightness = 0;    // how bright the LED is
int fadeamount = 10;    // how many points to fade the LED by

void flush(){
  for (int i = 0; i < NUMPIXELS; i++){
    strip.setPixelColor(i, 0, 0, 0);
  }
}

void loop() {

 if (brightness > 255) {
   brightness = 255;
 }
 if (brightness < 255 / 2 && fadeamount < 0) {
   fadeamount = -fadeamount;
 }
 if(head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
   delay(5000);
   if(state == 0){
     r = 0;
     g = 255;
     b = 0;
     state = 1;
     fadeamount = -fadeamount;
   }
   else {
     if (state == 1){
        r = 0;
        g = 0;
        b = 255;
        state = 2;
        fadeamount = -fadeamount; 
     }
     else {
        r = 255;
        g = 105;
        b = 180;
        state = 0; 
        fadeamount = -fadeamount; 
     }
     
   }
   head = 0;                       //  Yes, reset head index to start
   flush();
 }

 // 'On' pixel at head
  Serial.println("\nr, g, b: " + String(r) + ", " + String(g) + ", " + String(b));
  strip.setPixelColor(head, r, g, b);
  strip.setBrightness(brightness);
  //strip.setPixelColor(tail, 34, 56, 89);     // 'Off' pixel at tail
  strip.begin();
  strip.show();                     // Refresh strip
  delay(100)
  head = head + 1;
  brightness = brightness + fadeamount;
}