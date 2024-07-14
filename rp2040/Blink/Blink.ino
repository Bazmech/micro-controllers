/**



**/


#include <Adafruit_NeoPixel.h>

int8_t NEO_PIXELS_COUNT = 30;
int8_t PIN_NUMBER = 1;
int16_t initialDelayValue = 120;
int8_t delayValue = initialDelayValue;
int8_t currentNeoIndex = 0;
int16_t red = 255;
int16_t green = 0;
int16_t blue = 0;

// Create the neopixel strip with the built in definitions NUM_NEOPIXEL and PIN_NEOPIXEL
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEO_PIXELS_COUNT, PIN_NUMBER, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);

  strip.begin();
  strip.setBrightness(5);
  strip.show();  // Initialize all pixels to 'off'
  delay(2000);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);


  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second

  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
}

// the loop function runs over and over again forever
void loop() {

  strip.setPixelColor(currentNeoIndex, red, green, blue);

  strip.show();
  delay(delayValue);

  currentNeoIndex++;

  if (currentNeoIndex >= NEO_PIXELS_COUNT) {
    if (red == 255) {
      red = 0;
      green = 255;
    } else if (green == 255) {
      green = 0;
      blue = 255;
    } else if (blue == 255) {
      blue = 0;
      red = 255;
      delayValue -= 50;
    }

    currentNeoIndex = 0;

    if (delayValue < 0) {
      delayValue = initialDelayValue;
    }
  }
  Serial.printf("Core temperature: %2.1fC\n", analogReadTemp());
}
