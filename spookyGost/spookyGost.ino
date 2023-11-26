#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

// Lights:
#define PIN_NEO_PIXEL 4  // Arduino pin that connects to NeoPixel
#define NUM_PIXELS 200    // The number of LEDs (pixels) on NeoPixel

// eyeballs (ultrasonic motor)
int trigPin = 9;    // TRIG pin
int echoPin = 8;    // ECHO pin
float duration_us, distance_cm;

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

//average
#include <AverageValue.h>
// Number of values to calculate with. Prevents memory problems
const long MAX_VALUES_NUM = 15;
AverageValue<long> averageValue(MAX_VALUES_NUM);

void setup() {
//lights
  NeoPixel.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)

//Eyes
  Serial.begin (9600);
  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);

}

void loop() {
   // generate 10-microsecond pulse to TRIG pin
  digitalWrite(trigPin, HIGH);
 // delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  //delay(10);


//average
averageValue.push(distance_cm);

float sensAvg = averageValue.average();
Serial.println("sensAvg:");
Serial.println(sensAvg);

if (sensAvg <= 800) {
  if (sensAvg <= 150) {
//light
//if (distance_cm <= 100){
  // for (int pixel = 0; pixel < 300; pixel++) {           // for each pixel
  //   NeoPixel.setPixelColor(pixel, NeoPixel.Color(225,0,0));  // it only takes effect if pixels.show() is called
  //   NeoPixel.show();
  //   NeoPixel.clear();
  // }
  for (int pixel = 0; pixel < 55; pixel++) {      //     TOP
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(225,0,0));  // it only takes effect if pixels.show() is called
  }
  for (int pixel = 55; pixel < 90; pixel++) {      //     R ARM
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(195,50,50));  // it only takes effect if pixels.show() is called
  }
  for (int pixel = 90; pixel < 150; pixel++) {      //     BASE
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(195,100,100));  // it only takes effect if pixels.show() is called
  }
  NeoPixel.show();  // send the updated pixel colors to the NeoPixel hardware.
  
  for (int pixel = 150; pixel < 190; pixel++) {       //    L ARM
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(195,50,50));  // it only takes effect if pixels.show() is called
  }
}

  
  else{

//light
//if (distance_cm <= 100){
  for (int pixel = 0; pixel < 55; pixel++) {      //     TOP
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(130,40,255));  // it only takes effect if pixels.show() is called
  }
  for (int pixel = 55; pixel < 90; pixel++) {      //     R ARM
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(30,10,225));  // it only takes effect if pixels.show() is called
  }
  for (int pixel = 90; pixel < 150; pixel++) {      //     BASE
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(0,0,225));  // it only takes effect if pixels.show() is called
  }
  NeoPixel.show();  // send the updated pixel colors to the NeoPixel hardware.
  for (int pixel = 150; pixel < 190; pixel++) {       //    L ARM
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(30,10,225));  // it only takes effect if pixels.show() is called
  }
}

}
else {
  //delay(2000);
 NeoPixel.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
  NeoPixel.show();
}
}

