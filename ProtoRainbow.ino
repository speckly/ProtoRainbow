/*********
   By speck MUhahaha
  *********/
#include "ProtoRainbow.h"
#include "RainbowSettings.h"
#include "Frames.h"
#include <Arduino.h>
#include "Adafruit_GFX.h"
#include "Framebuffer_GFX.h"      
#include "PxMatrix.h"
#include "FastLED.h"
#define P_LAT 22  
#define P_A 19
#define P_B 23
#define P_C 18
#define P_D 5
#define P_E 15
#define P_OE 2

//replace 197 with your number of leds (just my number)
CRGB matrixleds[197];
int ledcount = 197;
int hueOffset = 0;

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
TaskHandle_t Task1;
TaskHandle_t Task2;

// Pins for LED MATRIX
#define matrix_width 128
#define matrix_height 32

// This defines the 'on' time of the display is us. The larger this number,
// the brighter the display. If too large the ESP will crash
uint8_t display_draw_time=10; //10-50 is usually fine


void useless_px(){
  for (int i = 0; i < 37; i++){
    matrixleds[i] = CRGB(0, 0, 0);
  }
  for (int i = 160; i < 191; i++){
    matrixleds[i] = CRGB(0, 0, 0);
  }
}

//rainbow scroll for WS2812B
void rainbow_wave(uint8_t thisSpeed, uint8_t deltaHue, int framedelay, int counts) {     
// uint8_t thisHue = beatsin8(thisSpeed,0,255);
  for (int i = 0; i < (counts + 1); i++){            
    uint8_t thisHue = beat8(thisSpeed,255);                   
    fill_rainbow(matrixleds, ledcount, thisHue, deltaHue);   
    delay(framedelay);        
    useless_px();
    FastLED.show();
  }
}
void Task2code( void * pvParameters ){   //function by jtingf, idk what it kind of does 
 
  for(;;){
  delay(1); 
  display.display(50); //was60  

  }
}

void setup() {
  Serial.begin(9600);
  setCpuFrequencyMhz(160);
 xTaskCreatePinnedToCore(
    Task2code,   
    "Task2",      
    11000,       
    NULL,        
    24,          
    &Task2,     
    0);         
  display.begin(16);
  display.setMuxDelay(1,1,1,1,1);
  display.setPanelsWidth(2);
  display.setFastUpdate(true);
  FastLED.addLeds<WS2812,4>(matrixleds, ledcount);  // "4" is the pin you connect your WS2812 matrix to !
  display.setBrightness(155);
  FastLED.setBrightness(155);
}


void loop() {
  //display.clearDisplay();
  hueOffset += 1; 
  if (hueOffset == (72*loopEvent + 1)){ //insert event on the (loopEvent)th RGB cycle
    //your event goes here, here it blinks on every second cycle
    for (int h = 0; h < 7; h++){
      display.clearDisplay();
      switch (h){
        case 0:
        case 6:
        draw_face(blink1, h);
        rainbow_wave(50, 10, animation_delay, 4); //this function serves as a delay but to include the scrolling of WS2812B's, since there aint async or maybe im stupid
        break;
        case 1:
        case 5:
        draw_face(blink2, h);
        rainbow_wave(50, 10, animation_delay, 4);
        break;
        case 2:
        case 4:
        draw_face(blink3, h);
        rainbow_wave(50, 10, animation_delay, 4);
        break;
        case 3:
        draw_face(blink4, h);
        rainbow_wave(50, 10, animation_delay, 8);
        break;
      }
    }
    hueOffset = 7;

  }
  else{
    draw_face(def, hueOffset);
    rainbow_wave(50, 10, frame_delay, 1);
  }
}
