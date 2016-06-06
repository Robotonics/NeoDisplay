/**
 * @example CompButton.ino
 * 
 * @par How to Use
 * This example shows that when the button component on the Nextion screen is released,
 * the text of this button will plus one every time.      
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/7/10
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

#include "Nextion.h"
#include <Adafruit_NeoPixel.h>
/*
 * Declare a button object [page id:0,component id:1, component name: "b0"]. 
 */
#define PIN 4 // Neopixel x24 ring
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);
NexButton chase = NexButton(1, 3, "chase");
NexButton blue = NexButton(4, 1, "blue");
NexButton red = NexButton(4, 3, "red");
NexButton green = NexButton(4, 2, "green");
NexButton yellow = NexButton(4, 4, "yellow");
NexButton purple = NexButton(4, 5, "purple");
NexButton orange = NexButton(4, 6, "orange");
NexButton skyblue = NexButton(4, 8, "skyblue");
NexButton white = NexButton(4, 7, "white");
NexButton full = NexButton(1, 9, "full");
NexButton theatre=NexButton(1,8,"theatre");
NexButton rainbow=NexButton(1,10,"rainbow");
NexButton play=NexButton(0,3,"play");
uint32_t c;

NexTouch *nex_listen_list[] = 
{
    &chase,
    &blue,
    &red,
    &green,
    &yellow,
    &purple,
    &orange,
    &skyblue,
    &white,
    &full,
    &theatre,
    &rainbow,
    &play,
    
    NULL
};



void setup(void)
{    
    nexInit();
    //EEPROM.begin(512);
    chase.attachPop(chasePopCallback, &chase);
    blue.attachPop(bluePopCallback, &blue);
    red.attachPop(redPopCallback, &red);
    green.attachPop(greenPopCallback, &green);
    yellow.attachPop(yellowPopCallback, &yellow);
    purple.attachPop(purplePopCallback, &purple);
    orange.attachPop(orangePopCallback, &orange);
    skyblue.attachPop(skybluePopCallback, &skyblue);
    white.attachPop(whitePopCallback, &white);
    full.attachPop(fullPopCallback, &full);
    theatre.attachPop(theatrePopCallback, &theatre);
    rainbow.attachPop(rainbowPopCallback, &rainbow);
    play.attachPop(playPopCallback, &play);
    
    strip.begin();
    strip.show();
}

void loop(void)
{   
    nexLoop(nex_listen_list);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void playPopCallback(void *ptr)
{
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,255));
    strip.show();
    delay(50);
  }
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
    strip.show();
    delay(50);
  }
}

void bluePopCallback(void *ptr)
{
  c=strip.Color(0,0,200);
  
}

void redPopCallback(void *ptr)
{
 c=strip.Color(200,0,0);
}
void yellowPopCallback(void *ptr)
{
  
 c=strip.Color(150,150,0);
}

void greenPopCallback(void *ptr)
{
 c=strip.Color(0,200,0);
}

void purplePopCallback(void *ptr)
{
  c=strip.Color(127,0,255);
}

void orangePopCallback(void *ptr)
{
  c=strip.Color(150,128,0);
}

void skybluePopCallback(void *ptr)
{
  c=strip.Color(0,100,100);
}

void whitePopCallback(void *ptr)
{
  c=strip.Color(100,100,100);
}

void chasePopCallback(void *ptr)
{
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(50);
  }
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
    strip.show();
    delay(50);
  }

}

void fullPopCallback(void *ptr)
{

   for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, c ) ;
    }
      strip.show();
}

void theatrePopCallback(void *ptr)
{
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(50);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void rainbowPopCallback(void *ptr){

   for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(50);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
    
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow1(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


