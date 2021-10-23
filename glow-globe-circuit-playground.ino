// https://github.com/adafruit/Adafruit_CircuitPlayground
#include <Adafruit_CircuitPlayground.h>
#include <math.h>

#define micMin 70
#define micMax 100
#define debug true

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
int oldRange = micMax - micMin;
int newRange = 255;

void setup() {
  if (debug) {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Sketch initialing");
  }

  // Initialize the Circuit Playground board
  CircuitPlayground.begin();

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
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 255, 0, 0);
  }
  CircuitPlayground.setBrightness(brightness);
}

void fadeCycle() {
  setAllPixels(colors[selectedColor][0], colors[selectedColor][1], colors[selectedColor][2]);
  // fade up/down white (ghostly)
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
