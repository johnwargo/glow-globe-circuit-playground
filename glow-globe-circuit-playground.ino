// https://github.com/adafruit/Adafruit_CircuitPlayground
#include <Adafruit_CircuitPlayground.h>
#include <math.h>

// The range of audio values we'll use to trigger the Red LED
#define micMin 70
#define micMax 100
#define newRange 255

// Change the following to `true` to enable output to the Serial monitor
#define debug false

const int oldRange = micMax - micMin;

int colors[4][3] = {
  {255, 255, 0}, // Yellow
  {255, 165, 3}, // Orange
  {128, 0, 128}, // Purple
  {255, 255, 255}      // White
};

bool direction = true;
int brightness = 0;
int delayVal = 1;
int selectedColor = 3;

void setup() {
  if (debug) {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Sketch initialing");
  }

  // Initialize the Circuit Playground board
  CircuitPlayground.begin();
  // initialize the random number generator
  randomSeed(analogRead(0));
  // Turn all of the LEDs green to let everyone know we're ready to go
  setAllPixels(0, 255, 0);
  // wait a second (literally)
  delay(1000);
  // clear all of the LEDs (turn them off)
  CircuitPlayground.clearPixels();
  printColor();
}

void loop() {
  float soundValue;
  int brightness;

  soundValue = CircuitPlayground.mic.soundPressureLevel(10);
  if ( soundValue >= micMin && soundValue <= micMax) {
    // then go red with intensity based on sound level
    //https://stackoverflow.com/questions/929103/convert-a-number-range-to-another-range-maintaining-ratio
    brightness = round(((soundValue- micMin) * newRange) / oldRange);
    if (debug) {
      Serial.println("Sound value: " + String(soundValue) + ", Brightness: " + String(brightness));
    }
    goRed(brightness);
  } else {
    fadeCycle();
  }
}

void setAllPixels(int red, int green, int blue) {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, red, green, blue);
  }
}

void goRed(int brightness) {
  // Set all LEDs to Red
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 255, 0, 0);
  }
  // Set brightness based on sound volume
  CircuitPlayground.setBrightness(brightness);
}

void fadeCycle() {
  // Fade LED colors up/down with a randomly changing color
  // Set the pixels to the selected color
  setAllPixels(colors[selectedColor][0], colors[selectedColor][1], colors[selectedColor][2]);
  if (direction) {
    // we're fading up
    brightness++;
    if (brightness > 255) {
      direction = false;
      return;
    }
  } else {
    // we're fading down
    brightness--;
    if (brightness < 1) {
      direction = true;
      // Change color
      selectedColor = random(4);
      // pick a new random delay value
      delayVal = random(10) + 1;
      printColor();
      return;
    }
  }
  CircuitPlayground.setBrightness(brightness);
  // Wait our random delay value - makes the fade all happen at different speeds
  delay(delayVal);
}

void printColor() {
  if (debug) {
    Serial.println("Color changed to " + String(selectedColor) + "(" + colors[selectedColor][0] + ", " + colors[selectedColor][1] + ", " + colors[selectedColor][2] + ")");
  }
}
