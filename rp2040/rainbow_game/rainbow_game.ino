/**


COMPONENTS:
1 x rp2040 plus


**/


#include <Adafruit_NeoPixel.h>
#include <cmath>

int8_t NEO_PIXELS_COUNT = 25;
int8_t PIN_NUMBER = 1;

// Create the neopixel strip with the built in definitions NUM_NEOPIXEL and PIN_NEOPIXEL
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEO_PIXELS_COUNT, PIN_NUMBER, NEO_GRB + NEO_KHZ800);

// colours of the rainbow defined.
uint32_t red = strip.Color(255, 0, 0);
uint32_t yellow = strip.Color(255, 255, 0);
uint32_t pink = strip.Color(227, 115, 131);
uint32_t green = strip.Color(0, 255, 0);
uint32_t purple = strip.Color(160, 32, 240);
uint32_t orange = strip.Color(204, 85, 0);
uint32_t blue = strip.Color(0, 0, 255);

// colours of the rainbow in array.
uint32_t colours[7] = { red, yellow, pink, green, purple, orange, blue };

void setup() {
  Serial.begin(115200);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  for (int ledBlink = 0; ledBlink < 2; ledBlink++) {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(300);
  }

  // Set the brightness of all the neo pixels.
  strip.begin();
  strip.setBrightness(5);
  strip.show();  // Initialize all pixels to 'off'

}

// the loop function runs over and over again forever
void loop() {

}
