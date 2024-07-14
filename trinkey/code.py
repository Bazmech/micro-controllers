import time
import board
import neopixel
import random
import usb_hid
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keyboard_layout_us import KeyboardLayoutUS
from adafruit_hid.keycode import Keycode  # pylint: disable=unused-import
from digitalio import DigitalInOut, Pull
import touchio

pixels = neopixel.NeoPixel(board.NEOPIXEL, 1, brightness=0.1, auto_write=False)

keyboard = Keyboard(usb_hid.devices)
keyboard_layout = KeyboardLayoutUS(keyboard)  # We're in the US :)

# create the switch, add a pullup, start it with not being pressed
button = DigitalInOut(board.SWITCH)
button.switch_to_input(pull=Pull.DOWN)
button_state = False

# create the captouch element and start it with not touched
touch = touchio.TouchIn(board.TOUCH)
touch_state = False

ctrlAltDelete = (Keycode.CONTROL, Keycode.ALT, Keycode.DELETE)

lock_windows = (Keycode.WINDOWS, Keycode.L)
lock_mac = (Keycode.CONTROL, Keycode.COMMAND, Keycode.Q)
spotlight_mac = (Keycode.COMMAND, Keycode.SPACE)

r = 255
g = 1
b = 1
phase = 1
led_rotations = 1
led_rotations_max = 3

Violet = (148, 0, 211)
Indigo = (75, 0, 130)
Blue = (0, 0, 255)
Green = (0, 255, 0)
Yellow = (255, 255, 0)
Orange = (255, 127, 0)
Red = (255, 0 , 0)


def rainbow():
    pixels.fill(Red)
    pixels.show()
    time.sleep(1)
    pixels.fill(Orange)
    pixels.show()
    time.sleep(1)
    pixels.fill(Yellow)
    pixels.show()
    time.sleep(1)
    pixels.fill(Green)
    pixels.show()
    time.sleep(1)
    pixels.fill(Blue)
    pixels.show()
    time.sleep(1)
    pixels.fill(Indigo)
    pixels.show()
    time.sleep(1)
    pixels.fill(Violet)
    pixels.show()
    time.sleep(1)

def colourCycle():
    global r, g, b, pixels, phase, led_rotations

    if led_rotations < led_rotations_max:
        if phase == 1:
            pixels.fill((r, g, b))
            pixels.show()
            r -= 1
            g += 1
            if r == 1:
                phase = 2
        elif phase == 2:
            pixels.fill((r, g, b))
            pixels.show()
            g -= 1
            b += 1
            if g == 1:
                phase = 3
        elif phase == 3:
            pixels.fill((r, g, b))
            pixels.show()
            b -= 1
            r += 1
            if b == 1:
                phase = 1
                led_rotations += 1

        time.sleep(0.01)
    elif led_rotations == led_rotations_max:
        pixels.fill((0, 0, 0))
        pixels.show()

# our helper function will press the keys themselves
def make_keystrokes(keys, delay):
    if isinstance(keys, str):  # If it's a string...
        keyboard_layout.write(keys)  # ...Print the string
    elif isinstance(keys, int):  # If its a single key
        keyboard.press(keys)  # "Press"...
        keyboard.release_all()  # ..."Release"!
    elif isinstance(keys, (list, tuple)):  # If its multiple keys
        keyboard.press(*keys)  # "Press"...
        keyboard.release_all()  # ..."Release"!
    time.sleep(delay)

def buttonPressed():
    global pixels, led_rotations, led_rotations_max
    print("Button Pressed")
    led_rotations = led_rotations_max + 1
    pixels.fill((255, 255, 0))
    pixels.show()

def buttonReleased():
    global pixels, phase, led_rotations, led_rotations_max
    print("Button released.")
    if isinstance(lock_mac, (list, tuple)) and isinstance(lock_mac[0], dict):  # Is it multiple instructions?
        for k in lock_mac:
            make_keystrokes(k['keys'], k['delay'])
    else:
        make_keystrokes(lock_mac, delay=0)
    pixels.fill((0, 0, 0))
    pixels.show()
    r = 255
    g = 1
    b = 1
    phase = 1
    led_rotations = led_rotations_max - 1


def touched():
    global pixels, led_rotations, r, g, b, led_rotations_max
    print("touched.")
    led_rotations = led_rotations_max + 1
    pixels.fill((0, 255, 255))
    pixels.show()
    # colourCycle()
    # make_keystrokes(lock_windows, delay=1)
    make_keystrokes(spotlight_mac, delay=0.5)
    make_keystrokes("code", delay=0.5)
    make_keystrokes(Keycode.ENTER, delay=0)
    rainbow()

def untouched():
    global pixels, phase, led_rotations, r, g, b, led_rotations_max
    print("untouched.")
    pixels.fill((0, 0, 0))
    pixels.show()
    r = 255
    g = 1
    b = 1
    phase = 1
    # led_rotations = led_rotations_max - 1

while True:
    colourCycle()

    if button.value and not button_state:
        buttonPressed()
        button_state = True

    if not button.value and button_state:
        buttonReleased()
        button_state = False

    if touch.value and not touch_state:
        touched()
        touch_state = True
    if not touch.value and touch_state:
        untouched()
        touch_state = False
