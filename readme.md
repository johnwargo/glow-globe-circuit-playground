# Glow Globe Circuit Playground

My children were born in late October, so we always make a big deal out of the holiday. Its also a great opportunity to do some cool projects. A few of years ago I created a remote-controlled flame throwing pumpkin (which I hope to publish someday) and last year, due to COVID restrictions, we passed out candy using a Candypult (candy catapult) I created out of some boards and rubber bands; the kids love it!

Last year I purchased some plastic globes and my wife frosted the inside to make them translucent. The plan was create a sound activated Glow Globe, put a microcontroller, microphone, LEDs, and a battery inside and do some cool light flickering based on sounds nearby. I started with an Adafruit Feather microcontroller and the [SparkFun Electret Microphone Breakout](https://www.sparkfun.com/products/12758), but no matter what I did, I could never get the microphone to accurately measure sound level. I played around with it last year and again this year and almost gave up.

I recently joined Oracle as a product manager and discovered the [Oracle Education Foundation](https://oraclefoundation.org/index.html) and quickly volunteered to help in their Hello Circuit Playground program. The program uses the [Adafruit Circuit Playground](https://learn.adafruit.com/introducing-circuit-playground/overview) to help teach high school students Design Thinking and microcontroller-based project development. When I started working with the Circuit Playground, I quickly realized that it was the perfect platform for my Glow Globe project., mostly because it has a ring of NeoPixels, a microphone, and an easy to use SDK.

I copied my original Feather project code into a new folder and rewrote it for the Circuit Playground. The sketch included in this repository does the following:

1. Flash the Circuit Playground's LEDS Green to let you know the sketch is running. 
2. Next, it starts slowly fading up and down random Halloweeny colors (Yellow, Orange, Purple) (the sketch randomly selects the color but also how long it takes to fade all the way up, then down).
3. Listens for sounds nearby (using the microphone) and flashes the LEDs Red whenever it detects sound above a specific threshold.

The sketch uses several configuration settings:

```c
// The range of audio values we'll use to trigger the Red LED
#define micMin 70
#define micMax 100

// Change the following to `true` to enable output to the Serial monitor
#define debug false
```

The `micMin` and `micMax` values control the range of sound levels that trigger the LEDs Red. Circuit Playground microphone values range from 0 to 100, but I didn't want the Red LEDs to trigger unless the nearby sound was louder than background noise. Leave `micMax` at 100, I was never able to get a sound value from the microphone that high in my testing. I played around with the `micMin` value until it worked just right for me.

When testing your code, set the value of the `debug` setting to `true` to enable sending debug information to the Serial Monitor.

To add additional colors to the color fading process, simply add values to this array:

```c
int colors[4][3] = {
  {255, 255, 0},  // Yellow
  {255, 165, 3},  // Orange
  {128, 0, 128},  // Purple
  {255, 255, 255} // White
};
```

Be sure to change the fir array dimension (`[4]`) if you add or remove colors from the array.

## Assembly

My wife and I will assemble the globes this week and publish the process with pictures. Stay tuned.
