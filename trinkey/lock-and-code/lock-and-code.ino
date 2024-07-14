#include <Adafruit_NeoPixel.h>
#include "Adafruit_FreeTouch.h"
#include "HID-Project.h"  // https://github.com/NicoHood/HID

// Create the neopixel strip with the built in definitions NUM_NEOPIXEL and PIN_NEOPIXEL
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NEOPIXEL, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// Create the two touch pads on pins 1 and 2:
Adafruit_FreeTouch touch = Adafruit_FreeTouch(PIN_TOUCH, OVERSAMPLE_4, RESISTOR_20K, FREQ_MODE_NONE);

int16_t neo_brightness_low = 10;  // initialize with 20 brightness (out of 255)
int16_t neo_brightness_high = 230;
long firstPixelHue = 0;
bool pushing = false;
bool touching = false;

void setup() {
  Serial.begin(9600);
  //while (!Serial);
  strip.begin();
  strip.setBrightness(neo_brightness_low);
  strip.show();  // Initialize all pixels to 'off'

  if (!touch.begin())
    Serial.print("Failed to begin touch on pin ");
  Serial.println(PIN_TOUCH);

  pinMode(PIN_SWITCH, INPUT_PULLDOWN);

  // Sends a clean report to the host. This is important on any Arduino type.
  Consumer.begin();
}

void loop() {

  // listen for commands
  if (Serial.available() > 0) {

    // read command
    String command = Serial.readStringUntil('\n');

    // run command
    if (command == "ping") {

      // send response
      Serial.print("pong");
      Serial.print("\n");
    }
  }

  if (pushing == false && touching == false) {
    strip.rainbow(firstPixelHue);
    firstPixelHue += 100;
    strip.show();
    delay(10);
  }

  if (firstPixelHue > 65535) {
    firstPixelHue = 1;
  }

  // measure the captouches
  bool current_touch = touch.measure() > 240;

  if (current_touch != touching) {
    Serial.print("Touch: ");
    Serial.println(touch.measure());
    if (current_touch) {
      Serial.println("Touching");
      strip.setBrightness(neo_brightness_high);
      strip.show();
    } else {
      Serial.println("Released");
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_SPACE);
      Keyboard.releaseAll();
      delay(10);
      Keyboard.write(KEY_C);
      Keyboard.write(KEY_O);
      Keyboard.write(KEY_D);
      Keyboard.write(KEY_E);
      Keyboard.write(KEY_RETURN);
      strip.setBrightness(neo_brightness_low);
    }
    touching = current_touch;
  }

  // check mechswitch
  bool curr_switch = digitalRead(PIN_SWITCH);
  if (curr_switch != pushing) {
    if (curr_switch) {
      Serial.println("Pressed");
      strip.setBrightness(neo_brightness_high);
      strip.show();
    } else {
      Serial.println("Released");
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
      Keyboard.press(KEY_Q);
      Keyboard.releaseAll();
      strip.setBrightness(neo_brightness_low);
    }
    pushing = curr_switch;
  }
}
