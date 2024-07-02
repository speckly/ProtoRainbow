//ProtoRainbow library by speck 
//https://linktr.ee/speckles

#pragma once
#include "PxMatrix.h"
#include "RainbowSettings.h"
#include <math.h>

#define P_LAT 22  
#define P_A 19
#define P_B 23
#define P_C 18
#define P_D 5
#define P_E 15
#define P_OE 2
PxMATRIX display(128,32,P_LAT, P_OE,P_A,P_B,P_C,P_D);


uint8_t newR;
uint8_t newG;
uint8_t newB;

int colorMap[64]; //this is an array containing hue values, which is mapped every color shift based on hueOffset, 64 elements
int loadPixel[3]; //singular pixel memory
int hue = 0;

struct colors {
  uint8_t CRed;
  uint8_t CGreen;
  uint8_t CBlue;
};


struct colors hue2rgb(int hue){
  newR = 0;
  newB = 0;
  newG = 0;
  struct colors outcolors;
  switch (hue/60){
      case 0: //cycle 1- R max G inc B 0 where hue < 60
      newR = 255;
      newG = (hue % 60) * 4.25; //4.25 ratio hue:rgb 
      break;
      case 1: //cycle 2 - R dec G max B 0, hue < 120 
      newR = 255 - (hue % 60) * 4.25;
      newG = 255; 
      break;
      case 2: //cycle 3 - R 0 G max B inc, hue < 180
      newG = 255;
      newB = (hue % 60) * 4.25;
      break;
      case 3: //cycle 4 - r 0 G dec B max, hue < 240
      newG = 255 - (hue % 60) * 4.25;
      newB = 255;
      break;
      case 4: //cycle 5 - R inc G 0 B max, hue < 300
      newR = (hue % 60) * 4.25;
      newB = 255;
      break;
      case 5: //cycle 6 - B decreases to oblivion, hue >= 300
      newR = 255;
      newB = 255 - (hue % 60) * 4.25;
      break;
     }
  outcolors.CRed = newR;
  outcolors.CGreen = newG;
  outcolors.CBlue = newB;
  return outcolors;
}

void draw_face(const uint8_t ani[], int hueOffset){
  struct colors readcolors;
  //create the hue map
  for (int i = 0; i < imageWidth; i++)
  {
    hue = (wavelength * (i + hueOffset) * (360/imageWidth)) % 360;
    colorMap[i] = hue;
  } 
  xsine_offset = round(sin((((xsine_period*hueOffset*360/(72*loopEvent))+xsine_phase)%360 )*(M_PI/180))*xsine_amp + xsine_amp);
  ysine_offset = round(sin(((ysine_period*hueOffset*360/(72*loopEvent))%360)*(M_PI/180))*ysine_amp);

  //draw pixels on panel 1
  display.clearDisplay();
  for (int r = 0; r < pixelCount; r++){ 
    if (ani[r] == 1){
      readcolors = hue2rgb(colorMap[r % 64]);
      display.drawPixelRGB888(r % imageWidth - xsine_offset, (r / imageWidth) + ysine_offset, readcolors.CRed, readcolors.CGreen, readcolors.CBlue);
    }
  }
  //panel 2, x overflows from 64, since we defined one buffer
  for (int r = 0; r < pixelCount; r++){ //mirrored face
    if (ani[r] == 1){
      readcolors = hue2rgb(colorMap[r % 64]);
      display.drawPixelRGB888(r % imageWidth + 2 * (64 - r % imageWidth) - 1 + xsine_offset, (r / imageWidth) + ysine_offset, readcolors.CRed, readcolors.CGreen, readcolors.CBlue);
    }
  }
}
