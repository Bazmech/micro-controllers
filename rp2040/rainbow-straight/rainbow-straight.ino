/**



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
uint32_t colour[7] = { red, yellow, pink, green, purple, orange, blue };

// Matrix of lines to crete bottom lef to top right.
// There will be a better way then this but this works for me while I'm learing.
int pixels[9][5] = {
  { 24, -1, -1, -1, -1 },
  { 15, 23, -1, -1, -1 },
  { 14, 22, 16, -1, -1 },
  { 5, 13, 17, 21, -1 },
  { 4, 6, 12, 18, 20 },
  { 3, 7, 11, 19, -1 },
  { 2, 8, 10, -1, -1 },
  { 1, 9, -1, -1, -1 },
  { 0, -1, -1, -1, -1 }
};

void setup() {
  Serial.begin(115200);

  strip.begin();
  strip.setBrightness(5);
  strip.show();  // Initialize all pixels to 'off'
  delay(500);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);


  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second

  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
}

int currentIndex = 0;

// the loop function runs over and over again forever
void loop() {

  if (currentIndex < 8) {
    for (int pixelLine = 0; pixelLine <= currentIndex; pixelLine++) {
      for (int pinIndex = 0; pinIndex < sizeof(pixels[pixelLine]) / sizeof(pixels[pixelLine][0]); pinIndex++) {
        if (pixels[pixelLine][pinIndex] != -1) {
          strip.setPixelColor(pixels[pixelLine][pinIndex], colour[currentIndex - pixelLine]);
          strip.show();
        }
      }
    }

    currentIndex++;

    delay(200);
  }
}
