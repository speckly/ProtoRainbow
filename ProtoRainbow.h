#include "RainbowSettings.h"

uint8_t newR;
uint8_t newG;
uint8_t newB;

int colorMap[64]; //this is an array containing hue values, which is mapped every color shift based on hueOffset, 64 elements
int loadPixel[3]; //singular pixel memory

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
  int imageHeight = 32;
  int imageWidth = 64;
 
  //create the hue map
  for (int i = 0; i < imageWidth; i++)
  {
    hue = (wavelength * (i + hueOffset) * (360/imageWidth)) % 360;
    colorMap[i] = hue;
  } 

  //draw pixels on panel 1
  for (int r = 0; r < pixelCount; r++){ 
    if (ani[r] == 1){
      readcolors = hue2rgb(colorMap[r % 64]);
      display.drawPixelRGB888(r % imageWidth , r / imageWidth, readcolors.CRed, readcolors.CGreen, readcolors.CBlue);
    }
  }
  //panel 2, x overflows from 64, since we defined one buffer
  for (int r = 0; r < pixelCount; r++){ //mirrored face
    if (ani[r] == 1){
      readcolors = hue2rgb(colorMap[r % 64]);
      display.drawPixelRGB888(r % imageWidth + 2 * (64 - r % imageWidth) - 1, r / imageWidth + remov, readcolors.CRed, readcolors.CGreen, readcolors.CBlue);
    }
  }
}
