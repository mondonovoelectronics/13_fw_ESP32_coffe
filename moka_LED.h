#include <Adafruit_NeoPixel.h>

#define LED_PIN 4
#define TANK_PIN_PULLUP 32
#define TANK_PIN_NO_PULLUP 33 // CREDO CHE IL SENSORE NON ABBIA BISOGNO DI PULLUP MA IN CASO LO PREDISPONGO
int tank_status;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, LED_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel. Avoid connecting
// on a live circuit... if you must, connect GND first.



void  moka_LED_setup() {
  strip.begin();
  strip.show(); // initialize all pixels to "off"
  pinMode(TANK_PIN_PULLUP, INPUT_PULLUP);
  pinMode(TANK_PIN_NO_PULLUP, INPUT);
}
// 0 to 255
void brighten() {
  uint16_t i, j;

  for (j = 10; j < 100; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 0, 0, j);
    }
    strip.show();
    delay(15);
  }
  delay(500);
}

// 255 to 0
void darken() {
  Serial.begin(9600);
  uint16_t i, j;

  for (j = 100; j > 10; j--) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 0, 0, j);
    }
    strip.show();
    delay(15);
    //Serial.println(j);
  }
  delay(500);
}
void LED_fading() {
  static int fading_status=0;
  if (fading_status==0){
     brighten();
     fading_status=1;
  }
  else{
    darken();
    fading_status=0;
  }
  //brighten();
  //darken();
}
void LED_off() {
  strip.clear();
  strip.show();
}

void tank_check(){
  if (digitalRead(TANK_PIN_PULLUP)==LOW)
    tank_status=0;
  else
    tank_status=1;
}

void LED_blinking(){
  static int blinking_status=0;
  uint16_t i;
  if (blinking_status==0){
      for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 100, 0, 0);
    }
    strip.show();
    delay(1000);
    blinking_status=1;
  }
  else{
    LED_off();
    delay(1000);
    blinking_status=0;
  }
}
