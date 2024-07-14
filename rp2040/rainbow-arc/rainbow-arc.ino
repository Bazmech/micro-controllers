/**



**/


#include <Adafruit_NeoPixel.h>
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

int8_t NEO_PIXELS_COUNT = 25;
int8_t PIN_NUMBER = 1;

// Create the neopixel strip with the built in definitions NUM_NEOPIXEL and PIN_NEOPIXEL
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEO_PIXELS_COUNT, PIN_NUMBER, NEO_GRB + NEO_KHZ800);

int16_t initialDelayValue = 120;
int8_t delayValue = initialDelayValue;
int8_t currentNeoIndex = 0;
uint32_t red = strip.Color(255, 0, 0);
uint32_t yellow = strip.Color(255, 255, 0);
uint32_t pink = strip.Color(227, 115, 131);
uint32_t green = strip.Color(0, 255, 0);
uint32_t purple = strip.Color(160, 32, 240);
uint32_t orange = strip.Color(204, 85, 0);
uint32_t blue = strip.Color(0, 0, 255);

uint32_t colour[7] = { red, yellow, pink, green, purple, orange, blue };

const char* pixels[7] = { "1,9",
                     "2,8,10",
                     "3,4,7,11,19",
                     "5,6,12,18,20",
                     "13,14,17,21",
                     "15,16,22",
                     "23,24" };

// for string delimiter
std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}


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


  strip.setPixelColor(1, colour[0]);
  strip.setPixelColor(9, colour[0]);

  strip.setPixelColor(2, colour[1]);
  strip.setPixelColor(8, colour[1]);
  strip.setPixelColor(10, colour[1]);

  strip.setPixelColor(3, pink);
  strip.setPixelColor(4, pink);
  strip.setPixelColor(7, pink);
  strip.setPixelColor(11, pink);
  strip.setPixelColor(19, pink);

  strip.setPixelColor(5, green);
  strip.setPixelColor(6, green);
  strip.setPixelColor(12, green);
  strip.setPixelColor(18, green);
  strip.setPixelColor(20, green);

  strip.setPixelColor(13, purple);
  strip.setPixelColor(14, purple);
  strip.setPixelColor(17, purple);
  strip.setPixelColor(21, purple);

  strip.setPixelColor(15, orange);
  strip.setPixelColor(16, orange);
  strip.setPixelColor(22, orange);

  strip.setPixelColor(23, blue);
  strip.setPixelColor(24, blue);
  strip.show();
}

int currentIndex = 0;

// the loop function runs over and over again forever
void loop() {

  // if (currentIndex < 7) {
  //   strip.clear();
  //   for ( uint16_t pixel = 0; pixel <= currentIndex; pixel++) {
  //     std::string str = pixels[pixel];
  //     std::string delimiter = ",";
  //     std::vector<std::string> v = split (str, delimiter);

  //     Serial.println( pixels[pixel] );

  //     // for (auto i : v) {
  //     //   Serial.println(i);
  //     //   // strip.setPixelColor(i, colour[pixel]);
  //     // }

  //   }
  //   currentIndex++;
  //   strip.show();
  //   delay(500);
  // }


}


